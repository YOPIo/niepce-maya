#include "mirror.h"
#include "../texture/texture.h"
#include "../bxdf/fresnel.h"
#include "../bxdf/specular.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Mirror::Mirror (const std::shared_ptr<Texture<Spectrum>>& reflectance) :
  reflectance_ (reflectance)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Mirror::AllocateBsdf
(
 const SurfaceInteraction& si,
       ArenaAllocator*     mem
)
const -> Bsdf*
{
  Bsdf* bsdf (mem->Allocate<Bsdf> (si));
  Spectrum r (reflectance_->Evaluate (si));
  Fresnel* f (mem->Allocate<FresnelNull> ());
  Bxdf* specular (mem->Allocate<SpecularReflection> (r, f));
  bsdf->Push (specular);

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
