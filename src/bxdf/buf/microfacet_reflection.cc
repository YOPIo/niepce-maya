#include "microfacet_reflection.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
MicrofacetReflection::~MicrofacetReflection ()
{}
/*
// ---------------------------------------------------------------------------
*/
MicrofacetReflection::MicrofacetReflection
(
    const Spectrum&                                reflectance,
    const std::shared_ptr<MicrofacetDistribution>& distribution,
    const std::shared_ptr<Fresnel>&                fresnel
) :
  Bxdf          (BxdfType (BxdfType::kReflection | BxdfType::kGlossy)),
  reflectance_  (reflectance),
  distribution_ (distribution),
  fresnel_      (fresnel)
{}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::SampleIncident
(
    const Vector3f &outgoing, /* BSDF local system coordinates */
    const Sample2f &sample
)
const -> Vector3f
{
  // Horizontal perfectly toward the surface
  if (outgoing.z == 0)
  {
    return Spectrum::Zero ();
  }

  // Sample the micorfacet normal
  const Vector3f wh = distribution_->SampleMicrofacetNormal (outgoing, sample);
  // TODO: Check micorfacet normal and outgoing are located in same hemisphere

  // Compute the incident direction in BSDF local system coordinates
  return Reflect (outgoing, wh);
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Evaluate
(
    const Vector3f &incident, /* BSDF local system coordinates */
    const Vector3f &outgoing  /* BSDF local system coordinates */
)
const -> Spectrum
{
  // Compute the microfacet normal
  const Vector3f microfacet_normal   = Normalize (incident + outgoing);
  const Float    cos_t_with_outgoing = std::abs (CosTheta (outgoing));
  const Float    cos_t_with_incident = std::abs (CosTheta (incident));

  // Handle cases
  if (microfacet_normal.x == microfacet_normal.y &&
      microfacet_normal.y == microfacet_normal.z &&
      microfacet_normal.z == 0)
  {
    return Spectrum::Zero ();
  }
  if (cos_t_with_incident == 0 || cos_t_with_outgoing == 0)
  {
    return Spectrum::Zero ();
  }

  const Spectrum f = fresnel_->Evaluate (Dot (incident, microfacet_normal));

  return reflectance_ + distribution_->Distribution(microfacet_normal) *
         distribution_->MaskingShadowFunction (outgoing, incident) * f /
         (4.0 * cos_t_with_incident * cos_t_with_outgoing);
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Pdf
(
    const Vector3f &incident, /* BSDF local system coordinates */
    const Vector3f &outgoing  /* BSDF local system coordinates */
)
const -> Float
{
  // TODO: Check incident and outgoing are located in same hemisphere

  // Compute the micorfacet normal
  const Vector3f micorfacet_normal = Normalize (incident + outgoing);
  return distribution_->Pdf(outgoing, incident) / (4.0 * Dot (incident, outgoing));
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Reflectance
(
    const SurfaceInteraction &si
)
const -> Spectrum
{
  return reflectance_;
}
/*
// ---------------------------------------------------------------------------
*/
auto MicrofacetReflection::Emission
(
    const SurfaceInteraction &si
)
const -> Spectrum
{
  return emission_;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
