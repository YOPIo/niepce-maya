#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "primitive.h"
#include "../shape/shape.h"
#include "../material/material.h"
#include "../light/light.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Interface for a single primitive
// ---------------------------------------------------------------------------
*/
class Individual : public Primitive
{
  /* Individual public constructors */
 public:
  Individual ();
  Individual
  (
   const std::shared_ptr<Shape>&    shape,
   const std::shared_ptr<Material>& material,
   const std::shared_ptr<Light>&    light
  );


  /* Individual public destructor */
  virtual ~Individual ();

  Individual (const Individual&  individual) = default;
  Individual (      Individual&& individual) = default;

  /* Individual operators*/
 public:
  auto operator = (const Individual&  individual) -> Individual& = default;
  auto operator = (      Individual&& individual) -> Individual& = default;


  /* Individual override methods */
 public:
  // Return bounding box in world or local space coordinate
  virtual auto WorldBounds () const -> Bounds3f override final;
  virtual auto LocalBounds () const -> Bounds3f override final;

  // Return surface area of a primitive
  virtual auto SurfaceArea () const -> Float override final;

  // Intersection test, if ray hits shape, return true otherwise false
  virtual auto IsIntersect
  (
   const Ray&       ray,
         HitRecord* record
  )
  const -> bool override final;


  /* Individual public methods */
 public:
  auto GetAreaLight () const -> std::shared_ptr<Light>;
  auto GetMaterial  () const -> std::shared_ptr<Material>;
  auto GetShape     () const -> std::shared_ptr<Shape>;


  /* Individual private data */
 private:
  // Getter methods, return its pointer if present, otherwise nullptr
  std::shared_ptr<Shape>    shape_;
  std::shared_ptr<Material> material_;
  std::shared_ptr<Light>    ligth_;

}; // class Individual
/*
// ---------------------------------------------------------------------------
*/
auto CreateIndividual
(
 const ShapePtr&    shape,
 const MaterialPtr& material,
 const LightPtr&    light
)
-> IndividualPtr;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _INDIVIDUAL_H_
