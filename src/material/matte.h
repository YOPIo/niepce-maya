#ifndef _MATTE_H_
#define _MATTE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "material.h"
#include "../sampler/sampler.h"
#include "../texture/constant_texture.h"
#include "../texture/image_map.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto CreateMatte (const TexturePtr <Spectrum>& reflectance) -> MaterialPtr;
/*
// ---------------------------------------------------------------------------
*/
class Matte : public Material
{
  /* Matte constructors */
public:
  Matte () = delete;
  Matte (const std::shared_ptr<Texture<Spectrum>>& reflectance);


  /* Matte public destructor */
  virtual ~Matte () = default;


  /* Matte operators*/
public:
  Matte (const Matte&  matte) = default;
  Matte (      Matte&& matte) = default;

  auto operator = (const Matte&  matte) -> Matte& = default;
  auto operator = (      Matte&& matte) -> Matte& = default;


  /* Matte public methods */
public:
  auto AllocateBsdf
  (
   const SurfaceInteraction& si,
         ArenaAllocator*     mem
  )
  const -> Bsdf* override final;


  /* Matte private data */
private:
  TexturePtr<Spectrum> reflectance_;
}; // class Matte
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATTE_H_
