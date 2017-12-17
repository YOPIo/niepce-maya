#include "aggregate.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Aggregate::Aggregate ()
{}
/*
// ---------------------------------------------------------------------------
*/
Aggregate::Aggregate (const std::vector<std::shared_ptr<Individual>>& aggregate) :
  aggregate_ (aggregate)
{}
/*
// ---------------------------------------------------------------------------
*/
Aggregate::~Aggregate ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto Aggregate::WorldBounds () const -> Bounds3f
{}
/*
// ---------------------------------------------------------------------------
*/
auto Aggregate::LocalBounds () const -> Bounds3f
{}
/*
// ---------------------------------------------------------------------------
*/
auto Aggregate::SurfaceArea () const -> Float
{}
/*
// ---------------------------------------------------------------------------
*/
auto Aggregate::IsIntersect
(
 const Ray&       ray,
       HitRecord* interaction
)
const -> bool
{
  bool is_hit = false;
  for (const auto& p : aggregate_)
  {
    HitRecord temp;
    if (p->IsIntersect (ray, &temp))
    {
      if (temp.distance < interaction->distance)
      {
        // Update nearest primitive
        *interaction = temp;
        interaction->primitive = p;
        is_hit = true;
      }
    }
  }
  return is_hit;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
