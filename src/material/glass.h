#ifndef _GLASS_H_
#define _GLASS_H_
/*
// ---------------------------------------------------------------------------
*/
#include "material.h"
#include "../bxdf/specular.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Glass : public Material
{
  /* Glass constructors */
public:
  Glass () = delete;
  Glass
  (
   const std::shared_ptr<Texture<Spectrum>>& reflectance,
   const std::shared_ptr<Texture<Spectrum>>& transmittance,
   const std::shared_ptr<Texture<Float>>&    ior
  );


  /* Glass destructor */
public:
  virtual ~Glass () = default;


  /* Glass public operators*/
public:
  Glass (const Glass&  glass) = default;
  Glass (      Glass&& glass) = default;

  auto operator = (const Glass&  glass) -> Glass& = default;
  auto operator = (      Glass&& glass) -> Glass& = default;


  /* Glass public methods */
public:
  auto AllocateBsdf
  (
      const SurfaceInteraction& si,
            ArenaAllocator*     mem
  )
  const -> Bsdf* override final;


  /* Glass private data */
private:
  std::shared_ptr<Texture<Spectrum>> reflectance_;
  std::shared_ptr<Texture<Spectrum>> transmittance_;
  std::shared_ptr<Texture<Float>>    ior_;

}; // class Glass
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
#endif // _GLASS_H_
