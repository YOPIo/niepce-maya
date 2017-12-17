#include "image_map.h"
#include "../core/interaction.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
ImageMapTexture::ImageMapTexture (const char* filename) :
  Texture <Spectrum> ()
{
  image_ = LoadImage <Float> (filename);
}
/*
// ---------------------------------------------------------------------------
*/
auto ImageMapTexture::Evaluate (const SurfaceInteraction &si) const -> Spectrum
{
  // Convert [0, 1)^2 to pixel (x, y)
  const uint32_t width  (image_->GetWidth ());
  const uint32_t height (image_->GetHeight ());

  const size_t x (width * si.texcoord.s);
  const size_t y (height * si.texcoord.t);

  // TODO: Create convertor
  const Pixel <Float> p ((*image_) (x, y));
  return Spectrum (p.r_, p.g_, p.g_, 0.0);
}
/*
// ---------------------------------------------------------------------------
*/
auto ImageMapTexture::ToString () const -> std::string
{
  return std::string ("Map texture");
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
