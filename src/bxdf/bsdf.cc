#include "bsdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Bsdf::Bsdf (const SurfaceInteraction& si, Float ior) :
  geometry_normal_ (si.normal),
  /*
  shading_ (Shading (si.normal,
                     Normalize (si.dpdu),
                     Normalize (Cross (si.normal, si.dpdu)))),
  */
  shading_         (Shading (si.normal)),
  ior_             (ior),
  bxdfs_           ({nullptr}),
  num_bxdfs_       (0)
{}
/*
// ---------------------------------------------------------------------------
*/
Bsdf::~Bsdf ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::WorldToLocal (const Vector3f &w) const -> Vector3f
{
  return Vector3f (Dot (shading_.tangent,  w),
                   Dot (shading_.binormal, w),
                   Dot (shading_.normal,   w));
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::LocalToWorld (const Vector3f &w) const -> Vector3f
{
  return Vector3f (shading_.tangent.x * w.x + shading_.binormal.x * w.y +
                   shading_.normal.x * w.z,
                   shading_.tangent.y * w.x + shading_.binormal.y * w.y +
                   shading_.normal.y * w.z,
                   shading_.tangent.z * w.x + shading_.binormal.z * w.z +
                   shading_.normal.z * w.z );
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::Evaluate
(
 const Vector3f& world_outgoing,
 const Vector3f& world_incident,
       BsdfType  sample_type
)
  const -> Spectrum
{
  const Vector3f wi = WorldToLocal (world_incident);
  const Vector3f wo = WorldToLocal (world_outgoing);

  if (wo.z == 0)
  {
    return Spectrum::Zero ();
  }

  const bool is_reflecting = Dot (world_incident, geometry_normal_) *
                             Dot (world_outgoing, geometry_normal_) > 0;

  Spectrum f (0.f);
  for (size_t i = 0; i < num_bxdfs_; ++i)
  {
    if (bxdfs_[i]->Matches (sample_type) &&
        (( is_reflecting && (bxdfs_[i]->Type () & BsdfType::kReflection)) ||
         (!is_reflecting && (bxdfs_[i]->Type () & BsdfType::kTransmission))))
    {
      f += bxdfs_[i]->Evaluate (wo, wi);
    }
  }

  return f;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::EvaluateAndSample
(
 const Vector3f& world_outgoing,
       Vector3f* world_incident,
 const Sample2f& sample,
       Float*    pdf,
 const BsdfType& sampling_type,
       BsdfType* sampled_type
)
  const -> Spectrum
{
  // Choose which _BxDF_ to sample
  size_t matching_bxdfs = NumMatchingTypes (sampling_type);
  if (matching_bxdfs == 0)
  {
    *pdf = 0;
    *sampled_type = BsdfType::kNull;
    return Spectrum::Zero ();
  }
  size_t comp =
    std::min (static_cast<size_t> (std::floor(sample[0] * matching_bxdfs)),
              matching_bxdfs - 1);

  // Get _BxDF_ pointer for chosen component
  Bxdf *sample_bxdf = nullptr;
  int count = comp;
  for (const auto& bxdf : bxdfs_)
  {
    if (bxdf->Matches (sampling_type) && count-- == 0)
    {
      sample_bxdf = bxdf;
      break;
    }
  }

  if (sample_bxdf == nullptr)
  {
    std::cerr << "No BxDF was chosen." << std::endl;
    *pdf = 0;
    *sampled_type = BsdfType::kNull;
    return Spectrum::Zero ();
  }

  // Remap _BxDF_ sample _u_ to $[0,1)^2$
  const Point2f remapped_sample
    (std::min (sample[0] * matching_bxdfs - comp,1 - kEpsilon), sample[1]);

  // Sample chosen _BxDF_
  Vector3f local_incident;
  const Vector3f local_outgoing = WorldToLocal (world_outgoing);
  if (local_outgoing.z == 0)
  {
    return Spectrum::Zero ();
  }

  *pdf = 0;
  *sampled_type = sample_bxdf->Type ();
  Spectrum f = sample_bxdf->EvaluateAndSample (local_outgoing,
                                               &local_incident,
                                               remapped_sample,
                                               pdf,
                                               sampled_type);

  *world_incident = LocalToWorld (local_incident);

  if (*pdf == 0)
  {
    // PDF zero processing
    *sampled_type = BsdfType::kNull;
    return Spectrum::Zero ();
  }

  // Compute overall PDF with all matching _BxDF_s
  if (!(sample_bxdf->Type () & BsdfType::kSpecular) && matching_bxdfs > 1)
  {
    for (const auto& bxdf : bxdfs_)
    {
      if (bxdf != sample_bxdf && bxdf->Matches (sampling_type))
      {
        *pdf += bxdf->Pdf (local_outgoing, local_incident);
      }
    }
  }
  if (matching_bxdfs > 1)
  {
    *pdf /= matching_bxdfs;
  }


  // Compute value of BSDF for sampled direction
  if (!(sampling_type & BsdfType::kSpecular) && matching_bxdfs > 1)
  {
    const bool is_reflecting = Dot (*world_incident, geometry_normal_) *
                               Dot ( world_outgoing, geometry_normal_) > 0;
    f = 0;
    for (const auto& bxdf : bxdfs_)
    {
      if (bxdf->Matches (sampling_type) &&
          (( is_reflecting && (sample_bxdf->Type () & BsdfType::kReflection)) ||
           (!is_reflecting && (sample_bxdf->Type () & BsdfType::kTransmission))))
      {
        f += sample_bxdf->Evaluate (local_outgoing, local_incident);
      }
    }
  }

  return f;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::Pdf
(
 const Vector3f& world_outgoing,
 const Vector3f& world_incident,
 const BsdfType& sample_type
)
  const -> Float
{
  const Vector3f local_outgoing (WorldToLocal (world_outgoing));
  const Vector3f local_incident (LocalToWorld (world_incident));

  if (num_bxdfs_ == 0.f || local_outgoing.z == 0)
  {
    return 0.0;
  }

  Float pdf = 0.f;
  int matching_bxdfs = 0;
  for (const auto& bxdf : bxdfs_)
  {
    if (bxdf->Matches (sample_type))
    {
      ++matching_bxdfs;
      pdf += bxdf->Pdf (local_outgoing, local_incident);
    }
  }
  return matching_bxdfs > 0 ? pdf / matching_bxdfs : 0.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::Push (Bxdf* bxdf_ptr) -> void
{
  if (num_bxdfs_ >= kMaxBxdfs)
  {
    // TODO: Error
    return ;
  }
  bxdfs_[num_bxdfs_++] = bxdf_ptr;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::NumBxdf () const -> size_t
{
  return num_bxdfs_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::NumMatchingTypes (BsdfType type) const -> size_t
{
  size_t res (0);
  for (size_t i = 0; i < num_bxdfs_; ++i)
  {
    if (bxdfs_[i]->Matches (type))
    {
      ++res;
    }
  }
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::ToString () const -> std::string
{
  std::string str = "BSDF: \n";

  if (NumBxdf () > 0)
  {
    str += "Number of BxDFs: " + std::to_string (NumBxdf()) + "\n";
  }

  return str;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
