#include "bsdf_utils.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto CosTheta (const Vector3f& w) -> Float
{
  return w.z;
}
/*
// ---------------------------------------------------------------------------
*/
auto Cos2Theta (const Vector3f& w) -> Float
{
  return w.z * w.z;
}
/*
// ---------------------------------------------------------------------------
*/
auto SinTheta (const Vector3f& w) -> Float
{
  return std::sqrt (Sin2Theta (w));
}
/*
// ---------------------------------------------------------------------------
*/
auto Sin2Theta (const Vector3f& w) -> Float
{
  return std::fmax (0.0, 1.0 - Cos2Theta (w));
}
/*
// ---------------------------------------------------------------------------
*/
auto TanTheta (const Vector3f& w) -> Float
{
  return SinTheta (w) / CosTheta (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto Tan2Theta (const Vector3f& w) -> Float
{
  return Sin2Theta (w) / Cos2Theta (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto CosPhi (const Vector3f& w) -> Float
{
  const Float sin_theta = SinTheta (w);
  return (sin_theta == 0) ? 1.0 : Clamp(w.x / sin_theta, -1.0, 1.0);
}
/*
// ---------------------------------------------------------------------------
*/
auto Cos2Phi (const Vector3f& w) -> Float
{
  return CosPhi (w) * CosPhi (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto SinPhi (const Vector3f& w) -> Float
{
  const Float sin_theta = SinTheta (w);
  return (sin_theta == 0) ? 0.0 : Clamp(w.y / sin_theta, -1.0, 1.0);
}
/*
// ---------------------------------------------------------------------------
*/
auto Sin2Phi (const Vector3f& w) -> Float
{
  return SinPhi (w) * SinPhi (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto IsSameHemisphere (const Vector3f& outgoing, const Vector3f& incident) -> bool
{
  // TODO:
  return (outgoing.z * incident.z > 0);
}
/*
// ---------------------------------------------------------------------------
*/
auto Reflect (const Vector3f& w, const Normal3f& n) -> Vector3f
{
  return -w + 2.0 * Dot (w, n) * static_cast<Vector3f> (n);
}
/*
// ---------------------------------------------------------------------------
*/
auto Refract
(
    const Vector3f& direction,
    const Normal3f& normal,
          Float     ior,
          Vector3f* refracted
)
-> bool
{
  const Float cos_theta_i   (Dot (normal, direction));
  const Float sin_2_theta_i (std::max (0.0, 1.0 - cos_theta_i * cos_theta_i));
  const Float sin_2_theta_t (ior * ior * sin_2_theta_i);

  if (sin_2_theta_t >= 1)
  {
    // Total reflection was occured
    return false;
  }

  const Float cos_theta_t (std::sqrt (1.0 - sin_2_theta_t));
  *refracted = ior * -direction + (ior * cos_theta_i - cos_theta_t) *
               static_cast<Vector3f> (normal);

  return true;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
