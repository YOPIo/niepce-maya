#include "scene.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Scene::Scene
(
 const std::vector <IndividualPtr>& aggregate,
 const AcceleratorType& type
) :
  accel_type_ (type)
{
  if (accel_type_ == AcceleratorType::kNone)
  {
    root_.reset (new Aggregate (aggregate));
  }
  else if (accel_type_ == AcceleratorType::kSah)
  {
    root_.reset (new BVH (aggregate));
  }
  else
  {
    std::cerr << "Unknown accelerator type was selected." << std::endl;
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto Scene::Construct
(
 const AcceleratorType& type,
 const std::vector <IndividualPtr>& primitives
)
-> void
{
  // TODO:
}
/*
// ---------------------------------------------------------------------------
*/
auto Scene::IsIntersect
(
    const Ray&          ray,
    SurfaceInteraction* interaction
)
const -> bool
{
  if (root_)
  {
    return root_->IsIntersect (ray, interaction);
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
*/
auto Scene::LoadIbl (const std::string& filepath) -> void
{
  ibl_.reset (new Ibl (filepath));
}
/*
// ---------------------------------------------------------------------------
*/
auto Scene::SampleIbl (const niepce::Ray &ray) const -> Spectrum
{
  return ibl_->Emission (ray);
}
/*
// ---------------------------------------------------------------------------
*/
auto Scene::HasIbl () const -> bool
{
  return ibl_ ? true : false;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
