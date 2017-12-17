#include "microfacet_test.h"
#include "../texture/texture.h"
#include "../bxdf/fresnel.h"
#include "../bxdf/microfacet.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Microfacet::Microfacet
(
    const std::shared_ptr<Texture<Spectrum>>& reflectance,
    const std::shared_ptr<Texture<Spectrum>>& transmittance,
    const std::shared_ptr<Texture<Float>>&    rough_u,
    const std::shared_ptr<Texture<Float>>&    rough_v,
    const std::shared_ptr<Texture<Float>>&    ior
) :
    Material       (),
    reflectance_   (reflectance),
    transmittance_ (transmittance),
    roughness_u_   (rough_u),
    roughness_v_   (rough_v),
    ior_           (ior)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Microfacet::AllocateBsdf
(
    const SurfaceInteraction& si,
          ArenaAllocator*     mem
)
const -> Bsdf*
{
  Bsdf* bsdf (mem->Allocate<Bsdf> (si));

  const Spectrum r       (reflectance_->Evaluate (si));
  const Float    rough_u (roughness_u_->Evaluate (si));
  const Float    rough_v (roughness_v_->Evaluate (si));
  const MicrofacetDistribution* d
      (mem->Allocate<BeckmannDistribution> (Point2f (rough_u, rough_v), false));

  const Float    ior (ior_->Evaluate (si));
  //const Fresnel* f   (mem->Allocate<FresnelDielectric> (1.5, 1.0));
  const Fresnel* f   (mem->Allocate<FresnelNull> ());
  Bxdf* microfacet (mem->Allocate<MicrofacetReflection> (r, d, f));
  bsdf->Push (microfacet);

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
