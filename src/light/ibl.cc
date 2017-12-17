#include "ibl.h"
#include "../core/image.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Ibl::Ibl (const std::string& filepath) :
    Light (LightType::kImageBased)
{
  Load (filepath);
}
/*
// ---------------------------------------------------------------------------
*/
auto Ibl::Emission
(
 const Ray& ray
)
const -> Spectrum
{
  // Rotate the IBL
  const Float angle = kPi / 2;
  Matrix4x4<Float> m (std::cos (angle), -std::sin (angle), 0, 0,
                      std::sin (angle),  std::cos (angle), 0, 0,
                                     0,                 0, 0, 0,
                                     0,                 0, 0, 0);


  // Transform to light coordinates system
  const Vector3f direction = Normalize (ray.direction);

  // Float u = 0.5 + std::atan2 (direction.y, direction.x) / (2.0 * kPi);
  // Float v = 0.5 - std::asin (direction.y) / kPi;
  // u = Clamp (u, 0, 1);
  // v = Clamp (v, 0, 1);

  // Compute (u, v) from outgoing direction in spherical coordinate system
  const Float theta = SphericalTheta (direction);
  const Float phi   = SphericalPhi (direction);

  const Point2f st (phi / (2.0 * kPi), theta / kPi);

  const uint32_t width  (image_->GetWidth ());
  const uint32_t height (image_->GetHeight ());

  // return image_ (Point2f (u, v));
  const Pixel <Float> p ((*image_) (st[0] * width, st[1] * height));

  return Spectrum (p.r_, p.g_, p.b_, 0.0);
}
/*
// ---------------------------------------------------------------------------
*/
auto Ibl::Load (const std::string& filepath) -> void
{
  image_ = LoadImage <Float> (filepath.c_str ());
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
