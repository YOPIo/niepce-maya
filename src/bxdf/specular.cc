#include "specular.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Specular Reflection
// ---------------------------------------------------------------------------
*/
SpecularReflection::SpecularReflection
(
    const Spectrum& reflectance,
    const Fresnel*  fresnel
) :
  Bxdf (BsdfType (BsdfType::kReflection | BsdfType::kSpecular)),
  reflectance_ (reflectance),
  fresnel_     (fresnel)
{}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularReflection::Pdf
(
 const Vector3f& outgoing,
 const Vector3f& incident
)
const -> Float
{
  return 0.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularReflection::Evaluate
(
 const Vector3f& outgoing,
 const Vector3f& incident
)
const -> Spectrum
{
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularReflection::EvaluateAndSample
(
 const Vector3f& outgoing,
       Vector3f* incident,
 const Sample2f& sample,
       Float*    pdf,
       BsdfType *type
)
const -> Spectrum
{
  *incident = Vector3f (-outgoing.x, -outgoing.y, outgoing.z);

  // Delta function
  *pdf = 1.0;

  return fresnel_->Evaluate (CosTheta (*incident)) * reflectance_ /
         std::abs (CosTheta (*incident));
}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularReflection::ToString () const -> std::string
{
  return std::string ("Specular Reflection");
}
/*
// ---------------------------------------------------------------------------
// Specular Transmission
// ---------------------------------------------------------------------------
*/
SpecularTransmission::SpecularTransmission
(
    const Spectrum& transmission,
          Float     ior_i,
          Float     ior_o
) :
    Bxdf (BsdfType (BsdfType::kTransmission | BsdfType::kSpecular)),
    transmission_ (transmission),
    fresnel_      (FresnelDielectric (ior_i, ior_o)),
    ior_i_  (ior_i),
    ior_o_   (ior_o)
{}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularTransmission::Pdf
(
    const Vector3f& outgoing,
    const Vector3f& incident
)
const -> Float
{
  return 0.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularTransmission::Evaluate
(
    const Vector3f& outgoing,
    const Vector3f& incident
)
const -> Spectrum
{
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularTransmission::EvaluateAndSample
(
    const Vector3f& outgoing,
          Vector3f* incident,
    const Sample2f& sample,
          Float*    pdf,
          BsdfType* type
)
const -> Spectrum
{
  const bool  is_entering (CosTheta (outgoing) > 0);
  const Float ior_i (is_entering ? ior_i_ : ior_o_);
  const Float ior_t (is_entering ? ior_o_ : ior_i_);

  // Refraction
  const Normal3f n (Dot (outgoing, Vector3f (0, 0, 1)) < 0 ?
                    -Vector3f (0, 0, 1) : Vector3f (0, 0, 1));

  // Compute the refacted direction
  if (!Refract(outgoing, n, ior_i / ior_t, incident))
  {
    // Handle case: total reflection
    return Spectrum::Zero ();
  }

  *pdf = 1.0;

  const Spectrum t (transmission_ *
                   (Spectrum::One () - fresnel_.Evaluate(CosTheta (*incident))));

  return t / std::abs (CosTheta (*incident));
}
/*
// ---------------------------------------------------------------------------
*/
auto SpecularTransmission::ToString () const -> std::string
{
  return std::string ("Specular Transmission");
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
