#include "individual.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Individual::Individual () :
  Primitive (),
  shape_    (nullptr),
  material_ (nullptr),
  ligth_    (nullptr)
{}
/*
// ---------------------------------------------------------------------------
*/
Individual::Individual
(
 const std::shared_ptr<Shape>&    shape,
 const std::shared_ptr<Material>& material,
 const std::shared_ptr<Light>&    light
) :
  Primitive (),
  shape_    (shape),
  material_ (material),
  ligth_    (light)
{}
/*
// ---------------------------------------------------------------------------
*/
Individual::~Individual ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto Individual::WorldBounds () const -> Bounds3f
{
    // Todo : implementation
    return Bounds3f ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Individual::LocalBounds () const -> Bounds3f
{
    // Todo : implementation
    return Bounds3f ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Individual::SurfaceArea () const -> Float
{
    // Todo : implementation
    return -1.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto Individual::IsIntersect
(
 const Ray&       ray,
       HitRecord* interaction
)
const -> bool
{
  if (shape_)
  {
    return shape_->IsIntersect (ray, interaction);
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
auto Individual::GetAreaLight () const -> LightPtr
{
  if (ligth_ != nullptr)
  {
    return ligth_;
  }
  // TODO: Reprot a error
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto Individual::GetMaterial () const -> MaterialPtr
{
  if (material_ != nullptr)
  {
    return material_;
  }
  // TODO: Report a error
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto Individual::GetShape () const -> std::shared_ptr<Shape>
{
  if (shape_ != nullptr)
  {
    return shape_;
  }
  // TODO: Reprot a error
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateIndividual
(
 const ShapePtr&    shape,
 const MaterialPtr& material,
 const LightPtr&    light
)
-> IndividualPtr
{
  return std::make_shared <Individual> (shape, material, light);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
