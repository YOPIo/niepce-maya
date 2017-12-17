#ifndef _MICROFACET_H_
#define _MICROFACET_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "bxdf.h"
#include "bsdf_utils.h"
#include "fresnel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class MicrofacetDistribution
{
  /* MicrofacetDistribution constructors */
public:
  MicrofacetDistribution () = delete;
  MicrofacetDistribution (const Point2f& alpha, bool sample_visible = true);


  /* MicrofacetDistribution destructor */
public:
  virtual ~MicrofacetDistribution () = default;


  /* MicrofacetDistribution public methods */
public:
  // Sample microfacet normal vector
  virtual auto SampleMicrofacetNormal
  (
   const Vector3f& half,
   const Sample2f& sample
  )
  const -> Vector3f = 0;

  // Distribution Function D (wh)
  virtual auto Distribution (const Vector3f& half) const -> Float = 0;

  virtual auto Lambda (const Vector3f& outgoing) const -> Float = 0;

  // G (wo, wi)
  auto MaskingShadowing
  (
   const Vector3f& outgoing,
   const Vector3f& incident
  )
  const -> Float;

  // G1 (w)
  auto Masking (const Vector3f& v) const -> Float;

  auto Pdf
  (
   const Vector3f& outgoing,
   const Vector3f& incident,
   const Vector3f& half
  )
  const -> Float;


  /* MicrofacetDistribution public operators*/
public:
  MicrofacetDistribution (const MicrofacetDistribution&  md) = default;
  MicrofacetDistribution (      MicrofacetDistribution&& md) = default;

  auto operator = (const MicrofacetDistribution&  md) -> MicrofacetDistribution& = default;
  auto operator = (      MicrofacetDistribution&& md) -> MicrofacetDistribution& = default;


  /* MicrofacetDistribution protected data */
protected:
  const Point2f alpha_;
  const bool    sample_visible_;

}; // class MicrofacetDistribution
/*
// ---------------------------------------------------------------------------
// BeckmannDistribution
// ---------------------------------------------------------------------------
*/
class BeckmannDistribution : public MicrofacetDistribution
{
  /* BeckmannDistribution constructors */
public:
  BeckmannDistribution ();
  BeckmannDistribution (const Point2f& alpha, bool sample_visible = true);


  /* BeckmannDistribution destructor */
public:
  virtual ~BeckmannDistribution () = default;


  /* BeckmannDistribution public methods */
public:
  // Sample microfacet normal vector
  auto SampleMicrofacetNormal
  (
   const Vector3f& half,
   const Sample2f& sample
  )
  const -> Vector3f override final;

  // Distribution Function D (wh)
  auto Distribution (const Vector3f& half) const -> Float override final;

  auto Lambda (const Vector3f& outgoing) const -> Float override final;


  /* BeckmannDistribution public operators*/
public:
  BeckmannDistribution (const BeckmannDistribution&  beckmann) = default;
  BeckmannDistribution (      BeckmannDistribution&& beckmann) = default;

  auto operator = (const BeckmannDistribution&  beckmann)
    -> BeckmannDistribution& = default;
  auto operator = (      BeckmannDistribution&& beckmann)
    -> BeckmannDistribution& = default;

}; // class BeckmannDistribution
/*
// ---------------------------------------------------------------------------
// Microfacet Reflection
// ---------------------------------------------------------------------------
*/
class MicrofacetReflection : public Bxdf
{
  /* MicrofacetReflection constructors */
 public:
  MicrofacetReflection () = delete;
  MicrofacetReflection
  (
      const Spectrum&               reflectance,
      const MicrofacetDistribution* distribution,
      const Fresnel*                fresnel
  );


  /* MicrofacetReflection destructor */
 public:
  virtual ~MicrofacetReflection () = default;


  /* MicrofacetReflection public operators*/
 public:
  MicrofacetReflection (const MicrofacetReflection&  mf) = default;
  MicrofacetReflection (      MicrofacetReflection&& mf) = default;

  auto operator = (const MicrofacetReflection&  mf) -> MicrofacetReflection&
      = default;
  auto operator = (      MicrofacetReflection&& mf) -> MicrofacetReflection&
      = default;


  /* MicrofacetReflection public methods */
 public:
  auto Pdf
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Float override final;

  auto Evaluate
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Spectrum override final;

  auto EvaluateAndSample
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
            Vector3f* incident, /* BSDF coordinate system */
      const Sample2f& sample,
            Float*    pdf,
            BsdfType* type
  )
  const -> Spectrum override final;

  auto ToString () const -> std::string override final;


  /* MicrofacetReflection private data */
 private:
  const Spectrum                reflectance_;
  const MicrofacetDistribution* distribution_;
  const Fresnel*                fresnel_;

}; // class MicrofacetReflection
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MICROFACET_H_
