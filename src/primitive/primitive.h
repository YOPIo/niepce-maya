#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../core/interaction.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Interface of primitive type
//
// Primitive (Interface)
//  |
//  | -- Individual (Shape and Material/Light)
//  |
//  | -- Aggregate (Individuals)
//  |
//  | -- BVH (Individuals)
// ---------------------------------------------------------------------------
*/
class Primitive
{
protected:
  typedef SurfaceInteraction HitRecord;


  /* Primitive methdos */
 public:
  Primitive ();
  virtual ~Primitive ();

  Primitive (const Primitive&  primitive) = default;
  Primitive (      Primitive&& primitive) = default;


  /* Primitive public operators */
 public:
  auto operator = (const Primitive&  primitive) -> Primitive& = default;
  auto operator = (      Primitive&& primitive) -> Primitive& = default;


  /* Primitive public interfaces */
 public:
  // Return bounding box in world or local space coordinate
  virtual auto WorldBounds () const -> Bounds3f = 0;
  virtual auto LocalBounds () const -> Bounds3f = 0;

  // Return surface area of a primitive
  virtual auto SurfaceArea () const -> Float = 0;


  virtual auto IsIntersect
  (
   const Ray&       ray,
         HitRecord* record
  )
  const -> bool = 0;
};
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _PRIMITIVE_H_
