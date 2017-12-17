#include "sampler_utils.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto SampleUniforwDisk (const Sample2f& sample) -> Point2f
{
  const Float r     (std::sqrt (sample[0]));
  const Float theta (2.0 * kPi * sample[1]);
  return Sample2f (r * std::cos (theta), r * std::sin (theta));
}
/*
// ---------------------------------------------------------------------------
*/
// Return [-1, 1] on the circle
auto SampleConcentricDisk (const Sample2f& sample) -> Sample2f
{
  // Map uniform random numbers to [-1, 1]^2
  const Vector2f offset (2.0 * sample - Point2f::One ());

  // Handle degeneracy at the origin
  if (offset.s == 0 && offset.t == 0)
  {
    return Sample2f::Zero ();
  }

  Float r, theta;
  if (std::abs (offset.s) > std::abs (offset.t))
  {
    r     = offset.s;
    theta = kPi / 4.0 * (offset.t / offset.s);
  }
  else
  {
    r     = offset.t;
    theta = kPi / 2.0 - kPi / 4.0 * (offset.s / offset.t);
  }
  return r * Sample2f (std::cos (theta), std::sin (theta));
}
/*
// ---------------------------------------------------------------------------
*/
auto SampleCosineHemisphere (const Sample2f& sample) -> Vector3f
{
  const Sample2f d = SampleConcentricDisk (sample);
  const Float    z = std::sqrt (std::fmax (0.0, 1.0 - d.s * d.s - d.t * d.t));
  return Vector3f (d.s, d.t, z);
}
/*
// ---------------------------------------------------------------------------
*/
auto SampleIsoscelesRightTriangle (const Sample2f& sample) -> Sample2f
{
  const Float s = std::sqrt (sample[0]);
  return Sample2f (1 - s, sample[1] * s);
}
/*
// ---------------------------------------------------------------------------
*/
auto SampleUniformTriangle (const Sample2f& sample) -> Point2f
{
  const Float su = std::sqrt (sample[0]);
  return Point2f (1.0 - su, sample[1] * su);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
