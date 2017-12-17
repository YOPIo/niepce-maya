#include "specular.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
FresnelSpecular::FresnelSpecular () :
    Bxdf (BxdfType (BxdfType::kReflection | BxdfType::kTransmission | BxdfType::kSpecular)),
    reflectance_   (Spectrum (0.5)),
    transmittance_ (Spectrum (0.5)),
    ior_outside_   (1.0),
    ior_inside_    (1.23)
{}
/*
// ---------------------------------------------------------------------------
*/
FresnelSpecular::FresnelSpecular
(
    const Spectrum& reflectance,
    const Spectrum& transmittance,
          Float     ior_outside,   /* Index of refraction above the surface */
          Float     ior_inside     /* Index of refraction below the surface */
) :
    Bxdf (BxdfType (BxdfType::kReflection | BxdfType::kTransmission | BxdfType::kSpecular)),
    reflectance_   (reflectance),
    transmittance_ (transmittance),
    ior_outside_   (ior_outside),
    ior_inside_    (ior_inside)
{}
/*
// ---------------------------------------------------------------------------
*/
FresnelSpecular::~FresnelSpecular ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelSpecular::Sample
(
    const Vector3f& outgoing,
    const Sample2f& sample,
          Vector3f* incident,
          Float*    pdf
)
const -> Spectrum
{
  /*
  const Float f = FresnelReflectionDielectric (CosTheta (outgoing), ior_outside_, ior_inside_);

  // Ray reflect at the surface
  if (sample[0] < f)
  {
    *incident = Vector3f (-outgoing.x, -outgoing.y, outgoing.z);
    *pdf      = f;
    return f * reflectance_ / std::abs (CosTheta (*incident));
  }

  // Ray refract at the surface

  // Figure out ray come from inside of shape or not
  const bool  is_entering = CosTheta (outgoing) > 0 ? true : false;
  const Float ior0 = is_entering ? ior_outside_ : ior_inside_;
  const Float ior1 = is_entering ? ior_inside_  : ior_outside_;

  // Compute the ray direction for transmission
  const Normal3f normal = is_entering ? Normal3f (0, 0, 1) : Normal3f (0, 0, -1);
  if (!Refract(outgoing, normal, ior0 / ior1, incident))
  {
    // Total reflection occur
    return Spectrum::Zero ();
  }
  Spectrum ft = transmittance_ * (1.0 - f) * (ior0 * ior0) / (ior1 * ior1);
  *pdf = 1.0 - f;
  return ft / std::abs (Cos2Theta (*incident));
  */
}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelSpecular::SampleIncident
(
    const Vector3f &outgoing,
    const Sample2f &sample
)
const -> Vector3f
{
  assert (true);
  return Vector3f ();
}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelSpecular::Evaluate
(
    const Vector3f& incident,
    const Vector3f& outgoing
)
const -> Spectrum
{
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelSpecular::Pdf
(
    const Vector3f& incident,
    const Vector3f& outgoing
)
const -> Float
{
  return 0.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelSpecular::Reflectance (const niepce::SurfaceInteraction &si) const -> Spectrum
{
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto FresnelSpecular::Emission (const niepce::SurfaceInteraction &si) const -> Spectrum
{
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
