#include "fresnel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Fresnel Interface
// ---------------------------------------------------------------------------
*/
Fresnel::Fresnel ()
{}
/*
// ---------------------------------------------------------------------------
// Fresnel Conductor
// ---------------------------------------------------------------------------
*/
FresnelConductor::FresnelConductor
(
 const Spectrum& ior_i,
 const Spectrum& ior_t,
 const Spectrum& absorption
) :
  ior_i_      (ior_i),
  ior_t_      (ior_t),
  absorption_ (absorption)
{}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelConductor::Evaluate (Float cos_theta_i) const -> Spectrum
{
  const Float cos_i = Clamp (cos_theta_i, -1.0, 1.0);
  const Spectrum ior   = ior_t_ / ior_i_;
  const Spectrum ior_k = absorption_ / ior_i_;

  const Float cos_theta_i2 = cos_theta_i * cos_theta_i;
  const Float sin_theta_i2 = 1.0 - cos_theta_i2;

  const Spectrum ior2   = ior * ior;
  const Spectrum ior_k2 = ior_k * ior_k;

  const Spectrum t0 = ior2 - ior_k2 - Spectrum (sin_theta_i2);
  const Spectrum ab = Sqrt (t0 * t0 + 4.0 * ior2 * ior2);
  const Spectrum t1 = ab + Spectrum (cos_theta_i2);
  const Spectrum a  = Sqrt (Spectrum (0.5) * (ab + t0));
  const Spectrum t2 = 2.0 * cos_theta_i * a;
  const Spectrum rs = (t1 - t2) / (t1 + t2);
  const Spectrum t3 = Spectrum (cos_theta_i2) * ab +
                      Spectrum (sin_theta_i2 * sin_theta_i2);
  const Spectrum t4 = t2 * sin_theta_i2;
  const Spectrum rp = rs * (t3 - t4) / (t3 + t4);

  return 0.5 * (rp + rs);
}
/*
// ---------------------------------------------------------------------------
// FresnelDielectric
// ---------------------------------------------------------------------------
*/
FresnelDielectric::FresnelDielectric
(
 Float ior_i,
 Float ior_t
) :
  ior_i_ (ior_i),
  ior_t_ (ior_t)
{}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelDielectric::Evaluate (Float cos_theta_i) const -> Spectrum
{
  // Copy
  Float ior_i (ior_i_);
  Float ior_t (ior_t_);

  cos_theta_i = Clamp(cos_theta_i, -1.0, 1.0);
  const bool is_entering (cos_theta_i > 0);
  if (!is_entering)
  {
    std::swap (ior_i, ior_t);
    cos_theta_i = std::abs (cos_theta_i);
  }

  const Float sin_theta_i
      (std::sqrt (std::fmax (0.0, 1.0 - cos_theta_i * cos_theta_i)));
  const Float sin_theta_t (ior_i / ior_t * sin_theta_i);

  if (sin_theta_t >= 1)
  {
    return 1.0;
  }

  const Float cos_theta_t
      (std::sqrt (std::fmax (0.0, 1.0 - sin_theta_t * sin_theta_t)));
  const Float l (((ior_t * cos_theta_i) - (ior_i * cos_theta_t)) /
                 ((ior_t * cos_theta_i) + (ior_i * cos_theta_t)));
  const Float r (((ior_i * cos_theta_i) - (ior_t * cos_theta_t)) /
                 ((ior_i * cos_theta_i) + (ior_t * cos_theta_t)));
  return (r * r + l * l) * 0.5;
}
/*
// ---------------------------------------------------------------------------
// FresnelNull
// ---------------------------------------------------------------------------
*/
FresnelNull::FresnelNull ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelNull::Evaluate(Float cos_theta_i) const -> Spectrum
{
  return Spectrum (1.0);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce

