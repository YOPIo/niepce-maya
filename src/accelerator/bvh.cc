#include "bvh.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Data structure for BVH
// ---------------------------------------------------------------------------
BVH::Node::Node (const Bounds3f& bounds,
                 Node*           left,
                 Node*           right) :
    bounds_   (bounds),
    childlen_ ({std::unique_ptr<Node> (left), std::unique_ptr<Node> (right)}),
    first_    (0),
    last_     (0)
{}

BVH::Node::Node (const Bounds3f&         bounds,
                 std::unique_ptr<Node>&& left,
                 std::unique_ptr<Node>&& right) :
    bounds_   (bounds),
    childlen_ ({std::move (left), std::move (right)}),
    first_    (0),
    last_     (0)
{}

BVH::Node::Node (const Bounds3f& bounds,
                 size_t           first,
                 size_t           last) :
    bounds_   (bounds),
    childlen_ ({nullptr, nullptr}),
    first_    (first),
    last_     (last)
{}

BVH::Node::~Node ()
{}

inline auto BVH::Node::IsLeaf      () const -> bool
{
  return (childlen_[0] == nullptr && childlen_[1] == nullptr);
}
inline auto BVH::Node::IsInterior  () const -> bool
{
  return (childlen_[0] != nullptr && childlen_[1] != nullptr);
}

inline auto BVH::Node::WorldBounds () const -> Bounds3f
{
  return bounds_;
}

inline auto BVH::Node::Firstsize_t  () const -> size_t
{
  return first_;
}
inline auto BVH::Node::Lastsize_t   () const -> size_t
{
  return last_;
}
inline auto BVH::Node::LeftNode    () const -> const Node* const
{
  return childlen_[0].get ();
}
inline auto BVH::Node::RightNode   () const -> const Node* const
{
  return childlen_[1].get ();
}

// ---------------------------------------------------------------------------
// BVH
// ---------------------------------------------------------------------------
BVH::BVH ()
{
  // Report a error
}

BVH::BVH (const std::vector<std::shared_ptr<Individual>>& primitives) :
    aggregate_ (primitives)
{
  // Handling case
  if (primitives.size() == 0)
  {
    std::cerr << "Error (BVH)" << std::endl;
    return ;
  }

  std::vector<std::shared_ptr<Individual>> copy (primitives);
  std::vector<std::shared_ptr<Individual>> ordered;

  // Build BVH with SAH algorithm
  root_.reset (RecursiveConstruct (&copy, &ordered));

  std::swap (aggregate_, ordered);
}

BVH::~BVH ()
{}

auto BVH::WorldBounds () const -> Bounds3f
{
  // TODO: Implementation
  return Bounds3f ();
}

auto BVH::LocalBounds () const -> Bounds3f
{
  // TODO: Implementation
  return Bounds3f ();
}

auto BVH::SurfaceArea () const -> Float
{
  // TODO: Implementation
  return -1.0;
}

auto BVH::IsIntersect
(
 const Ray&          ray,
 SurfaceInteraction* interaction
)
const -> bool
{
  if (aggregate_.size () == 0)
  {
    return false;
  }
  return RecursiveIntersect (root_.get (), ray, interaction);
}

auto BVH::RecursiveIntersect
(
    const Node* const   node,
    const Ray&          ray,
    SurfaceInteraction* interaction
)
const -> bool
{
  // Ray-Bounding box intersection chcck
  const Bounds3f bounds = node->WorldBounds ();

  if (bounds.IsIntersect (ray))
  {
    // Current node is leaf node, then find a nearest primitive from ray
    if (node->IsLeaf ())
    {
      return LeafIntersect (node, ray, interaction);
    }
    // Current node is interior node
    if (node->IsInterior ())
    {
      // Intersect test
      SurfaceInteraction temp0, temp1;
      const bool left  = RecursiveIntersect (node->LeftNode  (), ray, &temp0);
      const bool right = RecursiveIntersect (node->RightNode (), ray, &temp1);

      // Choose a nearest primitive
      const Float dist0 = Distance (temp0.position, ray.origin);
      const Float dist1 = Distance (temp1.position, ray.origin);

      if (left && dist0 <= dist1)
      {
        *interaction = temp0;
        return std::move (left);
      }
      if (right && dist0 > dist1)
      {
        *interaction = temp1;
        return std::move (right);
      }
    }
  }
  // No intersection
  return false;
}

auto BVH::LeafIntersect
(
    const Node* const   node,
    const Ray&          ray,
    SurfaceInteraction* interaction
)
const -> bool
{
  bool is_hit = false;
  // Intersect test
  for (unsigned int i = node->Firstsize_t (); i <= node->Lastsize_t (); ++i)
  {
    SurfaceInteraction temp;
    if (aggregate_[i]->IsIntersect (ray, &temp))
    {
      // Update nearest shape from ray
      if (temp.distance <= interaction->distance)
      {
        // Update surface interaction
        *interaction = temp;
        interaction->primitive= aggregate_[i];
        is_hit = true;
      }
    }
  }
  return is_hit;
}

auto BVH::RecursiveConstruct
(
    std::vector<std::shared_ptr<Individual>>* original,
    std::vector<std::shared_ptr<Individual>>* ordered
)
const -> Node*
{
  // Compute bounding box of all primitives in 'original'
  Bounds3f bounds;
  for (auto& p : *original)
  {
    bounds = Union (bounds, p->WorldBounds ());
  }

  // ---------------------------------------------------------------------------
  // Create a leaf node if size of 'aggregate' is one
  // ---------------------------------------------------------------------------
  if (original->size () == 1)
  {
    return CreateLeaf (original, ordered);
  }

  // ---------------------------------------------------------------------------
  // Continue to build
  // BVH is built by SAH (surface area heuristic) algorithm
  // ---------------------------------------------------------------------------

  // Decide a split axis
  const unsigned int axis = bounds.MaxExtent ();

  // ---------------------------------------------------------------------------
  // Partition primitives into two groups
  // 1. Sort by split axis
  // 2. Computing each cost
  // 3. Find a minimum cost
  // 4. Decide to creating a leaf node or continue to build
  // ---------------------------------------------------------------------------

  constexpr unsigned int num_leafs = 4; // May be best
  // Need not to divide more
  if (original->size() <= num_leafs)
  {
    return CreateLeaf (original, ordered);
  }

  // 1. Sort by split axis
  auto sorting =
      [axis](const std::shared_ptr<Primitive>& p0, const std::shared_ptr<Primitive>& p1)
      {
        const Bounds3f bounds0 = p0->WorldBounds ();
        const Bounds3f bounds1 = p1->WorldBounds ();
        return bounds0.Centroid ()[axis] < bounds1.Centroid ()[axis];
      };
  std::sort (original->begin(), original->end(), sorting);

  // 2. Computing each cost
  Float* costs = new Float [original->size ()];
  for (int i = 0; i < original->size (); ++i)
  {
    Bounds3f bounds0, bounds1;
    for (int j = 0; j < i; ++j)
    {
      bounds0 = Union (bounds0, (*original)[j]->WorldBounds ());
    }
    for (int j = i; j < original->size (); ++j)
    {
      bounds1 = Union (bounds1, (*original)[j]->WorldBounds ());
    }
    // Evalate cost
    costs[i] = (static_cast<Float>(i)                     * bounds0.SurfaceArea () +
                static_cast<Float>(original->size () - i) * bounds1.SurfaceArea ())
        / bounds.SurfaceArea ();
  }

  // 3. Find a minimum cost
  int   middle   = 0;
  Float min_cost = original->size ();
  for (int i = 1; i < original->size (); ++i)
  {
    if (costs[i] < min_cost)
    {
      middle   = i;
      min_cost = costs[i];
    }
  }
  delete [] costs;

  // 4. Decide to creating a leaf node or continue to build
  // Create leaf
  if (min_cost == original->size ())
  {
    return CreateLeaf (original, ordered);
  }

  // Continue to build
  std::vector<std::shared_ptr<Individual>> left  (original->begin(), original->begin() + middle);
  std::vector<std::shared_ptr<Individual>> right (original->begin() + middle, original->end());

  // Create interior node
  Node* left_node  = RecursiveConstruct (&left,  ordered);
  Node* right_node = RecursiveConstruct (&right, ordered);

  return new Node (bounds, left_node, right_node);
}

auto BVH::CreateLeaf
(
    std::vector<std::shared_ptr<Individual>>* leaf,
    std::vector<std::shared_ptr<Individual>>* ordered
)
const -> BVH::Node*
{
  // Compute indices where is first and where is last
  const uint64_t first = ordered->size ();
  const uint64_t last  = first + leaf->size () - 1;

  // Compute bounds
  // Store primitives
  Bounds3f bounds;
  for (auto& p : *leaf)
  {
    bounds = Union (bounds, p->WorldBounds ());
    ordered->push_back (p);
  }

  // Create leaf node
  return new Node (bounds, first, last);
}

}  // namespace niepce
