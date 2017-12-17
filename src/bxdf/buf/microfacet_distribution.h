#ifndef _MICROFACET_DISTRIBUTION_H_
#define _MICROFACET_DISTRIBUTION_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "fresnel.h"
#include "bxdf.h"
/*
// ---------------------------------------------------------------------------
*/
class MicrofacetDistribution;
class TrowbridgeReitzDistribution;
// class BeckmannDistribution; // Unimplemented
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
  MicrofacetDistribution ();
  MicrofacetDistribution
  (
      const Point2f& alpha,
      bool  sample_visibly
  );


  /* MicrofacetDistribution destructor */
 public:
  virtual ~MicrofacetDistribution ();


  /* MicrofacetDistribution public operators*/
 public:
  MicrofacetDistribution (const MicrofacetDistribution&  md) = default;
  MicrofacetDistribution (      MicrofacetDistribution&& md) = default;

  auto operator = (const MicrofacetDistribution&  md) -> MicrofacetDistribution& = default;
  auto operator = (      MicrofacetDistribution&& md) -> MicrofacetDistribution& = default;


  /* MicrofacetDistribution public interfaces */
 public:
  // Sample Microfacet normal vector
  virtual auto SampleMicrofacetNormal
  (
      const Vector3f& outgoing, /* Shading (local) system coordinates */
      const Point2f&  u         /* Sampled random numbers             */
  )
  const -> Vector3f = 0;

  // Microfacet distribution function
  virtual auto Distribution
  (
      const Vector3f& wn /* Computed by SampleMicrofacetNormal () */
  )
  const -> Float = 0;

  virtual auto MaskingFunction (const Vector3f& wn) const -> Float;
  virtual auto MaskingShadowFunction
  (
      const Vector3f& outgoing, /* Shading (local) system coordinates */
      const Vector3f& incident  /* Shading (local) system coordinates */
  )
  const -> Float;


  /* MicrofacetDistribution protected interface */
 protected:
  virtual auto Lambda
  (
      const Vector3f& wn /* Computed by SampleMicrofacetNormal () */
  )
  const -> Float = 0;


  /* MicrofacetDistribution public methods */
 public:
  auto Pdf
  (
      const Vector3f& outgoing,         /* Shading (local) system coordinates    */
      const Vector3f& microfacet_normal /* Computed by SampleMicrofacetNormal () */
  )
  const -> Float;


  /* MicrofacetDistribution protected data */
 protected:
  const Point2f alpha_;
  const bool    sample_visibly_;


}; // class MicrofacetDistribution
/*
// ---------------------------------------------------------------------------
*/
class TrowbridgeReitzDistribution : public MicrofacetDistribution
{
  /* TrowbridgeReitzDistribution constructors */
 public:
  TrowbridgeReitzDistribution ();
  TrowbridgeReitzDistribution
  (
      const Point2f& alpha,
      bool  sample_visibly
   );


  /* TrowbridgeReitzDistribution destructor */
 public:
  virtual ~TrowbridgeReitzDistribution ();


  /* TrowbridgeReitzDistribution public operators*/
 public:
  TrowbridgeReitzDistribution (const TrowbridgeReitzDistribution&  ggx) = default;
  TrowbridgeReitzDistribution (      TrowbridgeReitzDistribution&& ggx) = default;

  auto operator = (const TrowbridgeReitzDistribution&  ggx) -> TrowbridgeReitzDistribution& = default;
  auto operator = (      TrowbridgeReitzDistribution&& ggx) -> TrowbridgeReitzDistribution& = default;


  /* TrowbridgeReits public methods */
 public:
  auto SampleMicrofacetNormal
  (
      const Vector3f& outgoing, /* Shading (local) system coordinates */
      const Point2f&  u         /* Sampled random numbers             */
  )
  const -> Vector3f override final;

  auto Distribution
  (
      const Vector3f& wn /* Computed by SampleMicrofacetNormal () */
  )
  const -> Float override final;


  /* TrowbridgeReitzDistribution protected methods*/
 protected:
  auto Lambda (const Vector3f& w) const -> Float override final;


}; // class TrowbridgeReitzDistribution
/*
// ---------------------------------------------------------------------------
*/
typedef TrowbridgeReitzDistribution Ggx;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MICROFACET_DISTRIBUTION_H_
