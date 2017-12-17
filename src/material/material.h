#ifndef _MATERIAL_H_
#define _MATERIAL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../bxdf/bsdf.h"
#include "../memory/arena_allocator.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Material
{
public:
  /* Material public constructors */
  Material ();


  /* Material public destructor */
  virtual ~Material () = default;


  Material (const Material&  mat) = default;
  Material (      Material&& mat) = default;


  /* Material public operators */
public:
  auto operator = (const Material&  mat) -> Material& = default;
  auto operator = (      Material&& mat) -> Material& = default;


  /* Material public infterface */
public:
  virtual auto AllocateBsdf
  (
      const SurfaceInteraction& si,
            ArenaAllocator*     mem
  )
  const -> Bsdf* = 0;

}; // class Material
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATERIAL_H_
