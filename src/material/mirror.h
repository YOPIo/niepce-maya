#ifndef _MIRROR_H_
#define _MIRROR_H_
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
class Mirror : public Material
{
  /* Mirror constructors */
public:
  Mirror () = delete;
  Mirror (const std::shared_ptr<Texture<Spectrum>>& reflectance);


  /* Mirror destructor */
public:
  virtual ~Mirror () = default;


  /* Mirror public operators*/
public:
  Mirror (const Mirror&  mirror) = default;
  Mirror (      Mirror&& mirror) = default;

  auto operator = (const Mirror&  mirror) -> Mirror& = default;
  auto operator = (      Mirror&& mirror) -> Mirror& = default;


  /* Mirror public methods */
public:
  auto AllocateBsdf
  (
   const SurfaceInteraction& si,
         ArenaAllocator*     mem
  )
  const -> Bsdf* override final;


  /* Mirror private data */
private:
  std::shared_ptr<Texture<Spectrum>> reflectance_;

}; // class Mirror
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MIRROR_H_
