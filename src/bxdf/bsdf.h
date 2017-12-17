#ifndef _BSDF_H_
#define _BSDF_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../core/interaction.h"
#include "bxdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Bsdf
{
 private:
  struct Shading
  {
    Shading (const Normal3f& n) :
        normal (n)
    {
      OrthoNormalBasis(n, &tangent, &binormal);
    }
    Shading
    (
     const Normal3f& n,
     const Vector3f& t,
     const Vector3f& b
    ) :
      normal   (n),
      tangent  (t),
      binormal (b)
    {}
    Normal3f normal;
    Vector3f tangent;
    Vector3f binormal;
  };
  static constexpr size_t kMaxBxdfs = 8;
  typedef std::array<Bxdf*, kMaxBxdfs> BxdfPtrs;

  /* Bsdf constructors */
 public:
  Bsdf (const SurfaceInteraction& si, Float ior = 1.0);


  /* Bsdf destructor */
 private:
  virtual ~Bsdf ();


  /* Bsdf public operators*/
 public:
  Bsdf (const Bsdf&  bsdf) = default;
  Bsdf (      Bsdf&& bsdf) = default;

  auto operator = (const Bsdf&  bsdf) -> Bsdf& = default;
  auto operator = (      Bsdf&& bsdf) -> Bsdf& = default;


  /* Bsdf public methods*/
 public:
  auto WorldToLocal (const Vector3f& w) const -> Vector3f;
  auto LocalToWorld (const Vector3f& w) const -> Vector3f;


  /* Bsdf public overridable methods */
 public:
  auto Evaluate
  (
      const Vector3f& world_outgoing,
      const Vector3f& world_incident,
            BsdfType  sample_type = BsdfType::kAll
  )
  const -> Spectrum;

  auto EvaluateAndSample
  (
      const Vector3f& world_outgoing,
            Vector3f* world_incident,
      const Sample2f& sample,
            Float*    pdf,
      const BsdfType& sampling_type,
            BsdfType* sampled_type
  )
  const -> Spectrum;

  auto Pdf
  (
      const Vector3f& world_outgoing,
      const Vector3f& world_incident,
      const BsdfType& sample_type
  )
  const -> Float;

  auto Push (Bxdf* bxdf_ptr) -> void;

  auto NumBxdf () const -> size_t;

  auto NumMatchingTypes (BsdfType type) const -> size_t;

  auto ToString () const -> std::string;


  /* Bsdf private data */
private:
  const Normal3f geometry_normal_;
  const Shading  shading_;
  Float    ior_;
  BxdfPtrs bxdfs_;
  size_t   num_bxdfs_;

}; // class Bsdf
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BSDF_H_
