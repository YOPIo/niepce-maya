#ifndef _MICROFACET_TEST_H_
#define _MICROFACET_TEST_H_
/*
// ---------------------------------------------------------------------------
*/
#include "material.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Microfacet : public Material
{
  /* Microfacet constructors */
 public:
  Microfacet () = delete;
  Microfacet
  (
      const std::shared_ptr<Texture<Spectrum>>& reflectance,
      const std::shared_ptr<Texture<Spectrum>>& transmittance,
      const std::shared_ptr<Texture<Float>>&    rough_u,
      const std::shared_ptr<Texture<Float>>&    rough_v,
      const std::shared_ptr<Texture<Float>>&    ior
  );


  /* Microfacet destructor */
 public:
  virtual ~Microfacet () = default;


  /* Microfacet public operators*/
 public:
  Microfacet (const Microfacet&  mat) = default;
  Microfacet (      Microfacet&& mat) = default;

  auto operator = (const Microfacet&  mat) -> Microfacet& = default;
  auto operator = (      Microfacet&& mat) -> Microfacet& = default;


  /* Microfacet public infterface */
public:
  auto AllocateBsdf
  (
      const SurfaceInteraction& si,
            ArenaAllocator*     mem
  )
  const -> Bsdf* override final;


  /* Microfacet private data */
 private:
  std::shared_ptr<Texture<Spectrum>> reflectance_;
  std::shared_ptr<Texture<Spectrum>> transmittance_;
  std::shared_ptr<Texture<Float>>    roughness_u_;
  std::shared_ptr<Texture<Float>>    roughness_v_;
  std::shared_ptr<Texture<Float>>    ior_;

}; // class Microfacet
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MICROFACET_TEST_H_
