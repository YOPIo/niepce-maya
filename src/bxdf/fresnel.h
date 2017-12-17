#ifndef _FRESNEL_H_
#define _FRESNEL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Fresnel
{
  /* Fresnel constructors */
public:
  Fresnel ();


  /* Fresnel destructor */
public:
  virtual ~Fresnel () = default;


  /* Fresnel public operators*/
public:
  Fresnel (const Fresnel&  f) = default;
  Fresnel (      Fresnel&& f) = default;

  auto operator = (const Fresnel&  f) -> Fresnel& = default;
  auto operator = (      Fresnel&& f) -> Fresnel& = default;


  /* Fresnel public interface */
public:
  virtual auto Evaluate (Float cos_i) const -> Spectrum = 0;

}; // class Fresnel
/*
// ---------------------------------------------------------------------------
*/
class FresnelConductor : public Fresnel
{
  /* FresnelConductor constructors */
public:
  FresnelConductor () = delete;
  FresnelConductor
  (
   const Spectrum& ior_i,
   const Spectrum& ior_t,
   const Spectrum& absorption
  );

  /* FresnelConductor destructor */
public:
  virtual ~FresnelConductor () = default;


  /* FresnelConductor public operators*/
public:
  FresnelConductor (const FresnelConductor&  f) = default;
  FresnelConductor (      FresnelConductor&& f) = default;

  auto operator = (const FresnelConductor&  f) -> FresnelConductor& = default;
  auto operator = (      FresnelConductor&& f) -> FresnelConductor& = default;


  /* FresnelConductor public methods */
public:
  auto Evaluate (Float cos_i) const -> Spectrum override final;


  /* Fresnel private methods */
private:
  Spectrum ior_i_;
  Spectrum ior_t_;
  Spectrum absorption_;

}; // class FresnelConductor
/*
// ---------------------------------------------------------------------------
*/
class FresnelDielectric : public Fresnel
{
  /* FresnelDielectric constructors */
public:
  FresnelDielectric () = delete;
  FresnelDielectric
  (
   Float ior_i,
   Float ior_t
  );


  /* FresnelDielectric destructor */
public:
  virtual ~FresnelDielectric () = default;


  /* FresnelDielectric public operators*/
public:
  FresnelDielectric (const FresnelDielectric&  f) = default;
  FresnelDielectric (      FresnelDielectric&& f) = default;

  auto operator = (const FresnelDielectric&  f) -> FresnelDielectric& = default;
  auto operator = (      FresnelDielectric&& f) -> FresnelDielectric& = default;


  /* FresnelDielectric public methods */
  auto Evaluate (Float cos_theta_i) const -> Spectrum override final;


  /* FresnelDielectric private data */
private:
  Float ior_i_;
  Float ior_t_;

}; // class FresnelDielectric
/*
// ---------------------------------------------------------------------------
*/
class FresnelNull : public Fresnel
{
  /* FresnelNull constructors */
public:
  FresnelNull ();


  /* FresnelNull destructor */
public:
  virtual ~FresnelNull () = default;


  /* FresnelNull public operators*/
public:
  FresnelNull (const FresnelNull&  f) = default;
  FresnelNull (      FresnelNull&& f) = default;

  auto operator = (const FresnelNull&  f) -> FresnelNull& = default;
  auto operator = (      FresnelNull&& f) -> FresnelNull& = default;


  /* FresnelNull public methods */
public:
  auto Evaluate (Float cos_theta_i) const -> Spectrum override final;

}; // class FresnelNull
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FRESNEL_H_
