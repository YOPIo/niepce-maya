#include "glass.h"
#include "../texture/texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Glass::Glass
(
 const std::shared_ptr<Texture<Spectrum>>& reflectance,
 const std::shared_ptr<Texture<Spectrum>>& transmittance,
 const std::shared_ptr<Texture<Float>>&    ior
) :
  reflectance_   (reflectance),
  transmittance_ (transmittance),
  ior_           (ior)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Glass::AllocateBsdf
(
 const SurfaceInteraction& si,
       ArenaAllocator*     mem
)
const -> Bsdf*
{
  Bsdf* bsdf (mem->Allocate<Bsdf> (si));

  const Spectrum t   (transmittance_->Evaluate (si));
  const Float    eta (ior_->Evaluate (si));

  Bxdf* bxdf;
  bxdf = mem->Allocate<SpecularTransmission> (t, 1.0, eta);
  bsdf->Push (bxdf);

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
