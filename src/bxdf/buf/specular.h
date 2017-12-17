#ifndef _SPECULAR_H_
#define _SPECULAR_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "bxdf.h"
#include "fresnel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class FresnelSpecular : public Bxdf
{
  /* FresnelSpecular constructors */
 public:
  FresnelSpecular ();
  FresnelSpecular
  (
      const Spectrum& reflectance,
      const Spectrum& transmittance,
            Float     ior_outside,   /* Index of refraction above the surface */
            Float     ior_inside     /* Index of refraction below the surface */
  );


  /* FresnelSpecular destructor */
 public:
  virtual ~FresnelSpecular ();


  /* FresnelSpecular public operators*/
 public:
  FresnelSpecular (const FresnelSpecular&  fs) = default;
  FresnelSpecular (      FresnelSpecular&& fs) = default;

  auto operator = (const FresnelSpecular&  fs) -> FresnelSpecular& = default;
  auto operator = (      FresnelSpecular&& fs) -> FresnelSpecular& = default;


  /* FresnelSpecular public methods */
 public:
  auto Sample
  (
      const Vector3f& outgoing,
      const Sample2f& sample,
            Vector3f* incident,
            Float*    pdf
  )
  const -> Spectrum override final;

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


  /* FresnelSpecular private data */
 private:
  const Spectrum reflectance_;
  const Spectrum transmittance_;
  const Float    ior_outside_;   /* Index of refraction above the surface */
  const Float    ior_inside_;    /* Index of refraction below the surface */

}; // class FresnelSpecular
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SPECULAR_H_
