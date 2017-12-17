#ifndef _BVH_H_
#define _BVH_H_

#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../primitive/aggregate.h"
#include "../primitive/individual.h"
#include "../material/material.h"

namespace niepce
{

class BVH : public Primitive
{
  /* BVH Node declaration */
 private:
  class Node
  {
   public:
    Node () = delete;
    // Constructor for leaf node
    Node (const Bounds3f& bounds,
          Node*           left,
          Node*           right);
    // Constructor for interior node
    Node (const Bounds3f& bounds,
          std::unique_ptr<Node>&& left,
          std::unique_ptr<Node>&& right);
    Node (const Bounds3f& bounds,
          size_t           first,
          size_t           last);

    virtual ~Node ();

    Node (const Node&  node) = delete;
    Node (      Node&& node) = delete;

    /* BVH::Node operators */
   public:
    auto operator = (const Node&  node) -> Node& = delete;
    auto operator = (      Node&& node) -> Node& = delete;

    /* BVH::Node methods */
    inline auto IsLeaf      () const -> bool;
    inline auto IsInterior  () const -> bool;
    inline auto WorldBounds () const -> Bounds3f;
    inline auto Firstsize_t  () const -> size_t;
    inline auto Lastsize_t   () const -> size_t;
    inline auto LeftNode    () const -> const Node* const;
    inline auto RightNode   () const -> const Node* const;

    // BVH::Node data
   private:
    const Bounds3f bounds_;
    // Reference indices
    const size_t first_;
    const size_t last_;
    // Childlen node
    const std::array<std::unique_ptr<Node>, 2> childlen_;
  };

 public:
  /* BVH constructors */
  BVH ();
  BVH (const std::vector<std::shared_ptr<Individual>>& primitives);
  virtual ~BVH ();

  BVH (const BVH&  bvh) = delete;
  BVH (      BVH&& bvh) = default;


  /* BVH operators*/
 public:
  auto operator = (const BVH&  bvh) -> BVH& = delete;
  auto operator = (      BVH&& bvh) -> BVH& = default;


  /* BVH public methods */
 public:
  // Return bounding box in world or local space coordinate
  auto WorldBounds () const -> Bounds3f override;
  auto LocalBounds () const -> Bounds3f override;

  // Return surface area of a primitive
  auto SurfaceArea () const -> Float override;

  // Ray-Shape intersection test
  // 1. Return a nearest primitive
  // 2. Store a interaction information
  auto IsIntersect
  (
      const Ray&          ray,
      SurfaceInteraction* interaction
  )
  const -> bool override final;

  /* BVH private methods */
 private:
  // Intersection check
  auto RecursiveIntersect
  (
      const Node* const   node,
      const Ray&          ray,
      SurfaceInteraction* interaction
  )
  const -> bool;

  // Intersection check
  auto LeafIntersect
  (
      const Node* const   node,
      const Ray&          ray,
      SurfaceInteraction* interaction
  )
  const -> bool;

  // Build BVH
  auto RecursiveConstruct
  (
      std::vector<std::shared_ptr<Individual>>* original,
      std::vector<std::shared_ptr<Individual>>* ordered
  )
  const -> Node*;

  auto CreateLeaf
  (
      std::vector<std::shared_ptr<Individual>>* leaf,
      std::vector<std::shared_ptr<Individual>>* ordered
  ) const -> Node*;

  /* BVH private data */
 private:
  std::unique_ptr<Node> root_;
  std::vector<std::shared_ptr<Individual>> aggregate_;
}; // class BVH


}  // namespace niepce

#endif // _BVH_H_
