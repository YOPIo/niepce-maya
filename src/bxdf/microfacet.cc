#include "microfacet.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Microfacet Distribution
// ---------------------------------------------------------------------------
*/
MicrofacetDistribution::MicrofacetDistribution
(
 const Point2f& alpha,
       bool     sample_visible
) :
  alpha_          (alpha),
  sample_visible_ (sample_visible)
{}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetDistribution::MaskingShadowing
(
 const Vector3f& outgoing,
 const Vector3f& incident
)
const -> Float
{
  return Masking (outgoing) * Masking (incident);
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetDistribution::Masking(const Vector3f &v) const -> Float
{
  return 1.0 / (1.0 + Lambda (v));
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetDistribution::Pdf
(
 const Vector3f& outgoing,
 const Vector3f& incident,
 const Vector3f& half
)
const -> Float
{
  if (sample_visible_)
  {
    return Distribution (half) * Masking (outgoing) *
           std::abs (Dot (outgoing, half)) / std::abs (CosTheta (outgoing));
  }
  return Distribution (half) * std::abs (CosTheta (half));
}
/*
// ---------------------------------------------------------------------------
// BeckmannDistribution
// ---------------------------------------------------------------------------
*/
BeckmannDistribution::BeckmannDistribution
(
 const Point2f& alpha,
 bool  sample_visible
) :
  MicrofacetDistribution (alpha, sample_visible)
{}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::SampleMicrofacetNormal
(
 const Vector3f& outgoing,
 const Sample2f& sample
)
const -> Vector3f
{
  if (!sample_visible_)
  {
    Float tan2_theta, phi;
    if (alpha_.x == alpha_.y)
    {
      // Isotropic
      const Float log_sample (std::log (1.0 - sample[0]));
      tan2_theta = -alpha_.x * alpha_.x * log_sample;
      phi        = 2.0 * kPi * sample[1];
    }
    else
    {

    }
    const Float cos_theta (1.0 / std::sqrt (1.0 + tan2_theta));
    const Float sin_theta
      (std::sqrt (std::fmax (0.0, 1.0 - cos_theta * cos_theta)));

    Vector3f half (sin_theta * std::cos (phi),
                   sin_theta * std::sin (phi),
                   cos_theta);
    if (!IsSameHemisphere(half, outgoing))
    {
      half = -half;
    }
    return half;
  }
  // TODO: 
}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::Distribution (const Vector3f& half) const -> Float
{
  const Float tan2_theta (Tan2Theta (half));
  if (std::isinf (tan2_theta))
  {
    return 0;
  }
  const Float cos4_theta (Cos2Theta (half) * Cos2Theta (half));

  /*
  if (alpha_.x == alpha_.y)
  {
    // Isotropic
    return std::exp (-tan2_theta / (alpha_.x * alpha_.y)) /
           (alpha_.x * alpha_.y) * kPi * cos4_theta;
  }
  */
  // Anisotropic
  return std::exp (-tan2_theta * ((Cos2Phi (half)) / (alpha_.x * alpha_.x) +
                                  (Sin2Phi (half)) / (alpha_.y * alpha_.y))) /
         kPi * alpha_.x * alpha_.y * cos4_theta;
}
/*
// ---------------------------------------------------------------------------
*/
auto BeckmannDistribution::Lambda (const Vector3f& outgoing) const -> Float
{
  const Float tan_theta (std::abs (TanTheta (outgoing)));
  if (std::isinf (tan_theta)) { return 0; }

  const Float alpha (alpha_.x * alpha_.x * Cos2Phi (outgoing) +
                     alpha_.y * alpha_.y * Sin2Phi (outgoing));

  const Float a (1.0 / (alpha * tan_theta));

  return 0.5 * (std::erf (a) - 1.0 + std::exp (-a * a) / (a * kSqrtPi));
}
/*
// ---------------------------------------------------------------------------
// Microfacet Reflection
// ---------------------------------------------------------------------------
*/
MicrofacetReflection::MicrofacetReflection
(
 const Spectrum&               reflectance,
 const MicrofacetDistribution* distribution,
 const Fresnel*                fresnel
) :
  Bxdf (BsdfType(BsdfType (BsdfType::kReflection | BsdfType::kGlossy))),
  reflectance_  (reflectance),
  distribution_ (distribution),
  fresnel_      (fresnel)
{}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Pdf
(
 const Vector3f& outgoing,
 const Vector3f& incident
)
const -> Float
{
  if (!IsSameHemisphere (outgoing, incident))
  {
    return 0.0;
  }

  const Vector3f half (Normalize (outgoing + incident));
  return distribution_->Pdf (outgoing, incident, half) /
         (4.0 * Dot (outgoing, half));
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Evaluate
(
 const Vector3f& outgoing,
 const Vector3f& incident
)
const -> Spectrum
{
  const Float cos_theta_o (std::abs (CosTheta (outgoing)));
  const Float cos_theta_i (std::abs (CosTheta (incident)));
  if (cos_theta_i == 0 || cos_theta_o == 0)
  {
    return Spectrum::Zero ();
  }

  // half_angle_vector
  const Vector3f half (Normalize (outgoing + incident));
  if (half.x == 0 || half.y == 0 || half.z == 0)
  {
    return Spectrum::Zero ();
  }

  const Spectrum d (distribution_->Distribution (half));
  const Spectrum g (distribution_->MaskingShadowing (outgoing, incident));
  const Spectrum f (fresnel_->Evaluate (Dot (incident, half)));

  return reflectance_ * d * g * f / (4.0 * cos_theta_i * cos_theta_o);
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::EvaluateAndSample
(
 const Vector3f& outgoing,
       Vector3f* incident,
 const Sample2f& sample,
       Float*    pdf,
       BsdfType *type
)
const -> Spectrum
{
  if (outgoing.z == 0)
  {
    return Spectrum::Zero ();
  }

  // Sample half-angle vector and reflected direction
  const Vector3f half
    (distribution_->SampleMicrofacetNormal (outgoing, sample));

  *incident = Reflect (outgoing, static_cast<Normal3f> (half));

  if (!IsSameHemisphere (outgoing, *incident))
  {
    return Spectrum::Zero ();
  }

  // Compute the PDF
  *pdf = distribution_->Pdf(outgoing, *incident, half) /
         (4.0 * Dot (outgoing, half));

  return Evaluate (outgoing, *incident);
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::ToString () const -> std::string
{
  return std::string ("Microfacet Reflection");
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
