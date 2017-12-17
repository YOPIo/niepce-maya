#include "lambert.h"
#include "../sampler/sampler_utils.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Lambert::Lambert (const Spectrum& reflectance) :
    Bxdf         (BsdfType (BsdfType::kDiffuse | BsdfType::kReflection)),
    reflectance_ (reflectance)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Evaluate
(
    const Vector3f& outgoing, /* BSDF coordinate system */
    const Vector3f& incident  /* BSDF coordinate system */
)
const -> Spectrum
{
  return reflectance_ / kPi;
}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::EvaluateAndSample
(
 const Vector3f& outgoing, /* BSDF coordinate system */
       Vector3f* incident, /* BSDF coordinate system */
 const Sample2f& sample,
       Float*    pdf,
       BsdfType* type
)
const -> Spectrum
{
  // Sample incident in the shading (local) coordinates system
  *incident = SampleCosineHemisphere (sample);

  // Compute PDF
  *pdf = Pdf (outgoing, *incident);

  // Store sampled type of BxDF
  *type = Type ();

  return Evaluate (outgoing, *incident);
}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Pdf
(
 const Vector3f& outgoing, /* BSDF coordinate system */
 const Vector3f& incident  /* BSDF coordinate system */
)
const -> Float
{
  return CosTheta (incident) / kPi;
}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::ToString () const -> std::string
{
  return std::string ("lambert");
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
