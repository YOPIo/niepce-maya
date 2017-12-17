#ifndef _AGGREGATE_H_
#define _AGGREGATE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "primitive.h"
#include "individual.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Interface for aggregate primitive
// ---------------------------------------------------------------------------
*/
class Aggregate : public Primitive
{
public:
  /* Aggregate constructors */
  Aggregate ();
  Aggregate (const std::vector<std::shared_ptr<Individual>>& aggregate);
  virtual ~Aggregate ();

  Aggregate (const Aggregate&  aggregate) = default;
  Aggregate (      Aggregate&& aggregate) = default;


  /* Aggregate operators*/
  auto operator = (const Aggregate&  aggregate) -> Aggregate& = default;
  auto operator = (      Aggregate&& aggregate) -> Aggregate& = default;


  /* Aggreagate public override methods */
public:
  // Return bounding box in world or local space coordinate
  virtual auto WorldBounds () const -> Bounds3f override final;
  virtual auto LocalBounds () const -> Bounds3f override final;

  // Return surface area of a primitive
  virtual auto SurfaceArea () const -> Float override final;

  // Ray-Shape intersection test
  // 1. Return a nearest primitive
  // 2. Store a interaction information
  virtual auto IsIntersect
  (
   const Ray&       ray,
         HitRecord* record
  )
  const -> bool override final;

  // Aggrgate protected data
protected:
  std::vector<std::shared_ptr<Individual>> aggregate_;
}; // class Aggregate
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _AGGREGATE_H_
