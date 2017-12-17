#ifndef _AREA_H_
#define _AREA_H_
/*
// ---------------------------------------------------------------------------
*/
#include "light.h"
#include "../shape/shape.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
// ---------------------------------------------------------------------------
// AreaLight class
// ---------------------------------------------------------------------------
class AreaLight : public Light
{
  /* AreaLight public constructors */
 public:
  AreaLight ();
  AreaLight (const Spectrum& emission);

  /* AreaLight public destructor */
 public:
  virtual ~AreaLight ();

  AreaLight (const AreaLight&  area) = default;
  AreaLight (      AreaLight&& area) = default;


  /* AreaLight operators*/
 public:
  auto operator = (const AreaLight& area) -> AreaLight& = default;
  auto operator = (AreaLight&& area)      -> AreaLight& = default;


  /* AreaLight override methods */
 public:
  auto Emission
  (
   const Ray& ray
  )
  const -> Spectrum override final;


  /* AreaLight private data */
 private:
  Spectrum emission_;

}; // class AreaLight
/*
// ---------------------------------------------------------------------------
*/
auto CreateAreaLight (const Spectrum& emission) -> LightPtr;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _AREA_H_
