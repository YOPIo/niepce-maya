#ifndef _MATERIAL_PARAM_
#define _MATERIAL_PARAM_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct MaterialParam
{
  MaterialParam ()
  {}
  MaterialParam (const Spectrum& reflect) :
    reflectance (reflect)
  {}
  virtual ~MaterialParam ()
  {}

  MaterialParam (const MaterialParam&  param) = default;
  MaterialParam (      MaterialParam&& param) = default;

  auto operator = (const MaterialParam& param) -> MaterialParam& = default;
  auto operator = (     MaterialParam&& param) -> MaterialParam& = default;

  // Sampled value
  const Spectrum reflectance;
};
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATERIAL_PARAM_
