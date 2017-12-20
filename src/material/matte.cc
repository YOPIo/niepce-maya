#include "matte.h"
#include "../texture/constant_texture.h"
#include "../bxdf/lambert.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Matte::Matte (const std::shared_ptr<Texture<Spectrum>>& reflectance) :
  reflectance_ (reflectance)
{}
/*
// ---------------------------------------------------------------------------
*/
Matte::Matte (const Spectrum& reflectance) :
  reflectance_ (CreateConstantTexture (reflectance))
{}
/*
// ---------------------------------------------------------------------------
*/
auto Matte::AllocateBsdf
(
 const SurfaceInteraction& si,
       ArenaAllocator*     mem
)
const -> Bsdf*
{
  // Generate BSDF
  Bsdf* bsdf = mem->Allocate <Bsdf> (si);

  // Create lambertian BRDF
  Spectrum reflectance (reflectance_->Evaluate (si));
  Bxdf*    lambert = mem->Allocate<Lambert> (reflectance);
  bsdf->Push (lambert);

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMatte (const TexturePtr <Spectrum>& reflectance) -> MaterialPtr
{
  return std::make_shared <Matte> (reflectance);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateMatte (const Spectrum& reflectance) -> MaterialPtr
{
  return std::make_shared <Matte> (reflectance);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
