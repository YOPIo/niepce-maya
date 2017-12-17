#include "oren_layar.h"
#include "bsdf_utils.h"
#include "../sampler/sampler_utils.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
OrenLayer::OrenLayer
(
 const Spectrum& reflectance,
 Float sigma
) :
  Bxdf (BsdfType (BsdfType::kDiffuse | BsdfType::kReflection)),
  reflectance_ (reflectance),
  a_ (1.0 - (sigma * sigma / (2.0 * sigma * sigma + 0.33))),
  b_ (0.45 * sigma * sigma / (sigma * sigma + 0.09))
{}
/*
// ---------------------------------------------------------------------------
*/
auto OrenLayer::Pdf
(
 const Vector3f& outgoing,
 const Vector3f& incident
)
const -> Float
{
  if (IsSameHemisphere (outgoing, incident))
  {
    return std::abs (Cos2Theta (incident)) / kInvPi;
  }
  return 0.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto OrenLayer::Evaluate
(
 const Vector3f& outgoing,
 const Vector3f& incident
)
const -> Spectrum
{
  // Compute sin\phi_i, sin\phi_o, cos\phi_i and cos\phi_o
  const Float cos_phi_i (CosPhi (incident));
  const Float cos_phi_o (CosPhi (outgoing));
  const Float sin_phi_i (SinPhi (incident));
  const Float sin_phi_o (SinPhi (outgoing));
  const Float max_cos_phi
    (std::fmax (0.0, cos_phi_i * cos_phi_o + sin_phi_i * sin_phi_o));

  const Float sin_theta_i (SinTheta (incident));
  const Float sin_theta_o (SinTheta (outgoing));

  Float sin_alpha (sin_theta_i);
  Float tan_beta (sin_theta_o / std::abs (CosTheta (outgoing)));
  if (std::abs (CosTheta (incident)) > std::abs (CosTheta (outgoing)))
  {
    // Incident is larger than outgoing
    sin_alpha = sin_phi_o;
    tan_beta  = sin_theta_i / std::abs (CosTheta (incident));
  }

  // Compute BRDF
  return reflectance_ * kInvPi * (a_ + b_ * max_cos_phi * sin_alpha * tan_beta);
}
/*
// ---------------------------------------------------------------------------
*/
auto OrenLayer::EvaluateAndSample
(
 const Vector3f& outgoing,
       Vector3f* incident,
 const Sample2f& sample,
       Float*    pdf,
       BsdfType* type
)
const -> Spectrum
{
  // Sample next ray direction (incident) in BSDF coordinate system
  *incident = SampleCosineHemisphere (sample);
  if (outgoing.z < 0)
  {
    incident->z *= -1;
  }

  // Compute PDF
  *pdf = Pdf (outgoing, *incident);

  // Evaluate Oren-Layar BRDF
  return Evaluate (outgoing, *incident);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
