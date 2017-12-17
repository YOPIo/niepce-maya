#ifndef _MICROFACET_REFLECTION_H_
#define _MICROFACET_REFLECTION_H_
/*
// ---------------------------------------------------------------------------
*/
#include "microfacet_distribution.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class MicrofacetReflection : public Bxdf
{
  /* MicrofacetReflection constructors */
public:
  MicrofacetReflection () = delete;
  MicrofacetReflection
  (
    const Spectrum&                                reflectance,
    const std::shared_ptr<MicrofacetDistribution>& distribution,
    const std::shared_ptr<Fresnel>&                fresnel
  );


  /* MicrofacetReflection destructor */
public:
  virtual ~MicrofacetReflection ();


  /* MicrofacetReflection public operators*/
public:
  MicrofacetReflection (const MicrofacetReflection&  mr) = default;
  MicrofacetReflection (      MicrofacetReflection&& mr) = default;
  auto operator = (const MicrofacetReflection&  mr) -> MicrofacetReflection& = default;
  auto operator = (      MicrofacetReflection&& mr) -> MicrofacetReflection& = default;


  /* MicrofacetReflection public methods */
 public:
public:
  auto SampleIncident
  (
      const Vector3f& outgoing /* Shading (local) system coordinates */,
      const Sample2f& sample   /* random number                      */
  )
  const -> Vector3f override final;

  auto Evaluate
  (
      const Vector3f& incident, /* Shading (local) system coordinates */
      const Vector3f& outgoing  /* Shading (local) system coordinates */
  )
  const -> Spectrum override final;

  auto Pdf
  (
      const Vector3f& incident, /* Shading (local) system coordinates */
      const Vector3f& outgoing  /* Shading (local) system coordinates */
  )
  const -> Float override final;

  auto Reflectance (const SurfaceInteraction& si) const -> Spectrum override final;

  auto Emission (const SurfaceInteraction& si) const -> Spectrum override final;


  /* MicrofacetReflection private data */
private:
  const Spectrum                reflectance_;
  const Spectrum                emission_;
  const std::shared_ptr<MicrofacetDistribution> distribution_;
  const std::shared_ptr<Fresnel>                fresnel_;

  // const MicrofacetDistribution* distribution_;
  // const Fresnel*                fresnel_;


}; // class MicrofacetReflection
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce

#endif // _MICROFACET_REFLECTION_H_
