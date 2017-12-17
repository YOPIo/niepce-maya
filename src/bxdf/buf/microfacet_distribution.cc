#include "microfacet_distribution.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
MicrofacetDistribution::MicrofacetDistribution () :
    alpha_          (Point2f (0.5)),
    sample_visibly_ (false)
{}
/*
// ---------------------------------------------------------------------------
*/
MicrofacetDistribution::MicrofacetDistribution
(
    const Point2f& alpha,
    bool  sample_visibly
) :
    alpha_          (alpha),
    sample_visibly_ (sample_visibly)
{}
MicrofacetDistribution::~MicrofacetDistribution ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetDistribution::Pdf
(
    const Vector3f &outgoing, /* Shading (local) system coordinates    */
    const Vector3f &wm        /* Computed by SampleMicrofacetNormal () */
)
const -> Float
{
  if (sample_visibly_)
  {
    return Distribution (wm) * MaskingFunction (outgoing) * std::abs (Dot (outgoing, wm)) /
           std::abs (CosTheta (outgoing));
  }
  return Distribution (wm) * std::abs (CosTheta (wm));
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetDistribution::MaskingFunction (const Vector3f &w) const -> Float
{
  return 1.0 / (1.0 + Lambda (w));
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetDistribution::MaskingShadowFunction
(
   const Vector3f& outgoing, /* Shading (local) system coordinates */
   const Vector3f& incident  /* Shading (local) system coordinates */
)
const -> Float
{
  return MaskingFunction (outgoing) * MaskingFunction (incident);
}
/*
// ---------------------------------------------------------------------------
*/
TrowbridgeReitzDistribution::TrowbridgeReitzDistribution () :
    MicrofacetDistribution ()
{
  // Show Message
}
/*
// ---------------------------------------------------------------------------
*/
TrowbridgeReitzDistribution::TrowbridgeReitzDistribution
(
 const Point2f& alpha,
 bool  sample_visibly
) :
    MicrofacetDistribution (alpha, sample_visibly)
{}
/*
// ---------------------------------------------------------------------------
*/
TrowbridgeReitzDistribution::~TrowbridgeReitzDistribution ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitzDistribution::SampleMicrofacetNormal
(
 const Vector3f& outgoing, /* Shading (local) system coordinates */
 const Point2f&  sample    /* Sampled random numbers             */
)
const -> Vector3f
{
  if (!sample_visibly_)
  {
    Float tan2_theta, phi;
    if (alpha_.x == alpha_.y)
    {
      // Isotropic case
      tan2_theta = alpha_.x * alpha_.x * sample[0] / (1.0 - sample[0]);
      phi = 2.0 * kPi * sample[1];
    }
    else
    {
      // Anisotropic case
      phi = std::atan(alpha_.y / alpha_.x * std::tan(2.0 * kPi * sample[1] + 0.5 * kPi));
      if (sample[1] > 0.5)
      {
        phi += kPi;
      }
      const Float sin_phi = std::sin(phi);
      const Float cos_phi = std::cos(phi);
      const Float alphax2 = alpha_.x * alpha_.x;
      const Float alphay2 = alpha_.y * alpha_.y;
      const Float alpha2  = 1.0 / (cos_phi * cos_phi / alphax2 + sin_phi * sin_phi / alphay2);
      tan2_theta = sample[0] / (1.0 - sample[0]) * alpha2;
    }

    // Compute normal direction from angle information sampled above
    const Float cos_theta = 1.0 / std::sqrt (1.0 + tan2_theta);
    const Float sin_theta = std::sqrt (std::max(0.0, 1.0 - cos_theta * cos_theta));
    Vector3f microfacet = Vector3f (sin_theta * std::cos(phi), sin_theta * std::sin(phi), cos_theta);

    if (microfacet.z < 0.0)
    {
      microfacet = -1.0 * microfacet;
    }

    return microfacet;
  }

  std::cerr << "Unimplemented GGX" << std::endl;
  return Vector3f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitzDistribution::Distribution
(
    const Vector3f &wm /* Computed by SampleMicrofacetNormal () */
)
const -> Float
{
  const Float tan2_theta = Tan2Theta (wm);
  if (std::isnan (tan2_theta))
  {
    return 0;
  }

  const Float cos4_theta = Cos2Theta (wm) * Cos2Theta (wm);
  const Float e =
        (Cos2Phi (wm) / (alpha_.x * alpha_.x) +
         Sin2Phi (wm) / (alpha_.y * alpha_.y)) * tan2_theta;

  return 1 / (kPi * alpha_.x * alpha_.y * cos4_theta * (1 + e) * (1 + e));
}
/*
// ---------------------------------------------------------------------------
*/
auto TrowbridgeReitzDistribution::Lambda (const Vector3f& w) const -> Float
{
  const Float abs_tan_theta = std::abs (TanTheta (w));
  if (std::isinf (abs_tan_theta))
  {
    return 0.0;
  }

  // Compute _alpha_ for direction _w_
  const Float alpha =
      std::sqrt (Cos2Phi (w) * alpha_.x * alpha_.x + Sin2Phi(w) * alpha_.y * alpha_.y);
  const Float alpha2_tan2_theta = (alpha * abs_tan_theta) * (alpha * abs_tan_theta);

  return (-1 + std::sqrt(1.f + alpha2_tan2_theta)) / 2.0;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
