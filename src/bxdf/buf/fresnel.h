#ifndef _FRESNEL_H_
#define _FRESNEL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "bxdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Fresnel reflection/refraction utils
// ---------------------------------------------------------------------------
*/
auto FresnelReflectionConductor
(
    Float cos_theta_i,
    const Spectrum& incident_ior, /* Index of refraction for incident    */
    const Spectrum& transmit_ior, /* Index of refraction for transmitted */
    const Spectrum& absorption
)
-> Spectrum;
/*
// ---------------------------------------------------------------------------
*/
auto FresnelReflectionDielectric
(
    Float cos_theta_i,  /* Cos theta value for incident        */
    Float incident_ior, /* Index of refraction for incident    */
    Float transmit_ior  /* Index of refraction for transmitted */
)
-> Float;
/*
// ---------------------------------------------------------------------------
// Fresnel interface
// ---------------------------------------------------------------------------
*/
class Fresnel
{
  /* Fresnel constructors */
public:
  Fresnel ();


  /* Fresnel destructor */
public:
  virtual ~Fresnel ();


  /* Fresnel public operators*/
public:
  Fresnel (const Fresnel&  fresnel) = default;
  Fresnel (      Fresnel&& fresnel) = default;

  auto operator = (const Fresnel&  fresnel) -> Fresnel& = default;
  auto operator = (      Fresnel&& fresnel) -> Fresnel& = default;


  /* Fresnel public interface */
public:
  // Cosine of the angle made by the incoming direction and the surface normal
  // It Returns the amount of light reflected by the surface
  virtual auto Evaluate (Float cos_theta_incident) const -> Spectrum = 0;

}; // class Fresnel
/*
// ---------------------------------------------------------------------------
*/
class FresnelConductors : public Fresnel
{
  /* FresnelConductors constructors */
public:
  FresnelConductors () = delete;
  FresnelConductors
  (
      const Spectrum& incident_ior,
      const Spectrum& transmit_ior,
      const Spectrum& absorption
  );


  /* FresnelConductors destructor */
public:
  virtual ~FresnelConductors ();


  /* FresnelConductors public operators*/
public:
  FresnelConductors (const FresnelConductors&  f) = default;
  FresnelConductors (      FresnelConductors&& f) = default;

  auto operator = (const FresnelConductors&  f) -> FresnelConductors& = default;
  auto operator = (      FresnelConductors&& f) -> FresnelConductors& = default;


  /* FresnelConductors public method */
 public:
  auto Evaluate (Float cos_theta_incident) const -> Spectrum override final;


  /* FresnelConductors private data */
  Spectrum incident_ior_; // Index of refraction for incident
  Spectrum transmit_ior_; // Index of refraction for transmitted
  Spectrum absorption_;   // Absorption coefficient

}; // class FresnelConductors
/*
// ---------------------------------------------------------------------------
*/
class FresnelDielectrics : public Fresnel
{
  /* FresnelDielectrics constructors */
public:
  FresnelDielectrics () = delete;
  FresnelDielectrics
  (
      Float incident_ior,
      Float transmit_ior
  );


  /* FresnelDielectrics destructor */
public:
  virtual ~FresnelDielectrics ();


  /* FresnelDielectrics public operators*/
public:
  FresnelDielectrics (const FresnelDielectrics&  f) = default;
  FresnelDielectrics (      FresnelDielectrics&& f) = default;

  auto operator = (const FresnelDielectrics&  f) -> FresnelDielectrics& = default;
  auto operator = (      FresnelDielectrics&& f) -> FresnelDielectrics& = default;


  /* FresnelDielectrics public method */
 public:
  auto Evaluate (Float cos_theta_incident) const -> Spectrum;


  /* FresnelDielectrics private data */
private:
  Float incident_ior_; // Index of refraction for incident
  Float transmit_ior_; // Index of refraction for transmitted


}; // class FresnelDielectrics
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FRESNEL_H_
