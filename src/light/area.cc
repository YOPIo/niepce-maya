#include "area.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
AreaLight::AreaLight () :
    Light (static_cast<LightType> (LightType::kArea))
{}
/*
// ---------------------------------------------------------------------------
*/
AreaLight::AreaLight (const Spectrum& emission) :
    Light (static_cast<LightType> (LightType::kArea)),
    emission_ (emission)
{}
/*
// ---------------------------------------------------------------------------
*/
AreaLight::~AreaLight ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto AreaLight::Emission
(
 const Ray& ray
)
const -> Spectrum
{
  return emission_;
}
// ---------------------------------------------------------------------------
// Creator function
// ---------------------------------------------------------------------------
auto CreateAreaLight (const Spectrum& emission) -> LightPtr
{
  std::shared_ptr<Light> light (new AreaLight (emission));
  return std::move (light);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
