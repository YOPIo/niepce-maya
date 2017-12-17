#ifndef _SPECULAR_REFLECTION_H_
#define _SPECULAR_REFLECTION_H_
/*
// ---------------------------------------------------------------------------
*/
#include "bxdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
class SpecularReflection : public Bxdf
{
  /* SpecularReflection constructors */
 public:
  SpecularReflection ();


  /* SpecularReflection destructor */
 public:
  virtual ~SpecularReflection ();


  /* SpecularReflection public methods */
 public:
  auto SampleIncident
  (
      const Vector3f& outgoing /* Shading (local) system coordinates */,
      const Sample2f& sample   /* random number                      */
  )
  const -> Vector3f;

  auto Evaluate
  (
      const Vector3f& incident, /* Shading (local) system coordinates */
      const Vector3f& outgoing  /* Shading (local) system coordinates */
  )
  const -> Spectrum;

  auto Pdf
  (
      const Vector3f& incident, /* Shading (local) system coordinates */
      const Vector3f& outgoing  /* Shading (local) system coordinates */
  )
  const -> Float = 0;

  auto Reflectance (const SurfaceInteraction& si) const -> Spectrum;

  auto Emission (const SurfaceInteraction& si) const -> Spectrum;


  /* SpecularReflection public operators*/
 public:
  SpecularReflection (const SpecularReflection&  specular) = default;
  SpecularReflection (      SpecularReflection&& specular) = default;

  auto operator = (const SpecularReflection&  specular) -> SpecularReflection& = default;
  auto operator = (      SpecularReflection&& specular) -> SpecularReflection& = default;

}; // class SpecularReflection
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SPECULAR_REFLECTION_H_
