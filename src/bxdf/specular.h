#ifndef _SPECULAR_H_
#define _SPECULAR_H_
/*
// ---------------------------------------------------------------------------
*/
#include "bxdf.h"
#include "bsdf_utils.h"
#include "fresnel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// SpecularReflection
// ---------------------------------------------------------------------------
*/
class SpecularReflection : public Bxdf
{
  /* SpecularReflection constructors */
public:
  SpecularReflection () = delete;
  SpecularReflection
  (
      const Spectrum& reflectance,
      const Fresnel*  fresnel
  );


  /* SpecularReflection destructor */
public:
  virtual ~SpecularReflection () = default;


  /* SpecularReflection public operators*/
public:
  SpecularReflection (const SpecularReflection&  specular) = default;
  SpecularReflection (      SpecularReflection&& specular) = default;

  auto operator = (const SpecularReflection&  specular) -> SpecularReflection&
      = default;
  auto operator = (      SpecularReflection&& specular) -> SpecularReflection&
      = default;


  /* SpecularReflection public methods */
 public:
  auto IsDelta () const -> bool override final
  {
    return true;
  };

  auto Pdf
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Float override final;

  auto Evaluate
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Spectrum override final;

  auto EvaluateAndSample
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
            Vector3f* incident, /* BSDF coordinate system */
      const Sample2f& sample,
            Float*    pdf,
            BsdfType* type
  )
  const -> Spectrum override final;

  auto ToString () const -> std::string override final;


  /* SpecularReflection private data */
private:
  const Spectrum reflectance_;
  const Fresnel* fresnel_;

}; // class SpecularReflection
/*
// ---------------------------------------------------------------------------
// SpecularTransmission
// ---------------------------------------------------------------------------
*/
class SpecularTransmission : public Bxdf
{
  /* SpecularTransmission constructors */
 public:
  SpecularTransmission () = delete;
  SpecularTransmission
  (
      const Spectrum& transmission,
            Float     ior_i,
            Float     ior_o
  );


  /* SpecularTransmission destructor */
 public:
  virtual ~SpecularTransmission () = default;


  /* SpecularTransmission public operators*/
 public:
  SpecularTransmission (const SpecularTransmission&  specular) = default;
  SpecularTransmission (      SpecularTransmission&& specular) = default;

  auto operator = (const SpecularTransmission&  specular)
      -> SpecularTransmission& = default;
  auto operator = (      SpecularTransmission&& specular)
      -> SpecularTransmission& = default;


  /* SpecularTransmission public methods */
 public:
  auto IsDelta () const -> bool override final
  {
    return true;
  };

  auto Pdf
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Float override final;

  auto Evaluate
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Spectrum override final;

  auto EvaluateAndSample
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
            Vector3f* incident, /* BSDF coordinate system */
      const Sample2f& sample,
            Float*    pdf,
            BsdfType* type
  )
  const -> Spectrum override final;

  auto ToString () const -> std::string override final;


  /* Specular Transmission private data */
 private:
  const Spectrum          transmission_;
  const FresnelDielectric fresnel_;
        Float             ior_i_;
        Float             ior_o_;

}; // class SpecularTransmission
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SPECULAR_H_
