#include "fresnel.h"

namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto FresnelReflectionConductor
(
    Float cos_theta_i,
    const Spectrum& incident_ior, /* Index of refraction for incident    */
    const Spectrum& transmit_ior, /* Index of refraction for transmitted */
    const Spectrum& absorption
)
-> Spectrum
{
  /*
  cos_theta_i = Clamp (cos_theta_i, -1.0, 1.0);
  const Spectrum ior = transmit_ior / incident_ior;
  const Spectrum k   = absorption / incident_ior;

  const Float cos_theta_i2 = cos_theta_i * cos_theta_i;
  const Float sin_theta_i2 = 1.0 - cos_theta_i2;

  const Spectrum ior2 = ior * ior;
  const Spectrum k2   = k * k;

  const Spectrum t0 = k2 - k2 - Spectrum (sin_theta_i2);
  const Spectrum a2plusb2 = Sqrt(t0 * t0 + 4.0 * ior2 * k2);


  const Spectrum t1 = a2plusb2 + Spectrum (cos_theta_i2);
  const Spectrum a = Sqrt(0.5 * (a2plusb2 + t0));
  const Spectrum t2 = (Float)2 * cos_theta_i * a;
  const Spectrum rs = (t1 - t2) / (t1 + t2);

  const Spectrum t3 = cos_theta_i2 * a2plusb2 + Spectrum (sin_theta_i2) * Spectrum (sin_theta_i2);
  const Spectrum t4 = t2 * sin_theta_i2;
  const Spectrum rp = rs * (t3 - t4) / (t3 + t4);

  return 0.5 * (rp + rs);
  */
}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelReflectionDielectric
(
    Float cos_theta_i,  /* Cos theta value for incident        */
    Float incident_ior, /* Index of refraction for incident    */
    Float transmit_ior  /* Index of refraction for transmitted */
)
-> Float
{
  cos_theta_i = Clamp (cos_theta_i, -1.0, 1.0);
  // Potentially swap indices of refraction
  bool entering = cos_theta_i > 0.f;
  if (!entering)
  {
    std::swap(incident_ior, transmit_ior);
    cos_theta_i = std::abs (cos_theta_i);
  }

  // Compute 'cos theta_o' using Snell's law
  const Float sin_theta_i = std::sqrt (std::fmax (0.0, 1 - cos_theta_i * cos_theta_i));
  const Float sin_theta_t = incident_ior / transmit_ior * sin_theta_i;
  // Handle case: total internal reflection occur
  if (sin_theta_t > 1.0)
  {
    return 1.0;
  }
  const Float cos_theta_t = std::sqrt (std::fmax (0.0, 1 - sin_theta_t * sin_theta_t));

  // Compute the fresnel refrectance
  const Float parallel      = ((transmit_ior * cos_theta_i) - (incident_ior * cos_theta_t)) /
                              ((transmit_ior * cos_theta_i) + (incident_ior * cos_theta_t));
  const Float perpendicular = ((incident_ior * cos_theta_i) - (transmit_ior * cos_theta_t)) /
                              ((incident_ior * cos_theta_i) + (transmit_ior * cos_theta_t));

  return 0.5 * (parallel * parallel + perpendicular * perpendicular);
}
/*
// ---------------------------------------------------------------------------
*/
Fresnel::Fresnel ()
{}
/*
// ---------------------------------------------------------------------------
*/
Fresnel::~Fresnel ()
{}
/*
// ---------------------------------------------------------------------------
*/
FresnelConductors::FresnelConductors
(
    const Spectrum& incident_ior,
    const Spectrum& transmit_ior,
    const Spectrum& absorption
) :
    incident_ior_ (incident_ior),
    transmit_ior_ (transmit_ior),
    absorption_   (absorption)
{}
/*
// ---------------------------------------------------------------------------
*/
FresnelConductors::~FresnelConductors ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelConductors::Evaluate (Float cos_theta_incident) const -> Spectrum
{
  return FresnelReflectionConductor (cos_theta_incident, incident_ior_, transmit_ior_, absorption_);
}
/*
// ---------------------------------------------------------------------------
*/
FresnelDielectrics::FresnelDielectrics
(
    Float incident_ior,
    Float transmit_ior
) :
    incident_ior_ (incident_ior),
    transmit_ior_ (transmit_ior)
{}
/*
// ---------------------------------------------------------------------------
*/
FresnelDielectrics::~FresnelDielectrics ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelDielectrics::Evaluate (Float cos_theta_incident) const -> Spectrum
{
  return FresnelReflectionDielectric (cos_theta_incident, incident_ior_, transmit_ior_);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
