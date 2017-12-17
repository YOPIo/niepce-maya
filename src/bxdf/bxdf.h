#ifndef _BXDF_H_
#define _BXDF_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/object.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
enum BsdfType : uint64_t
{
  kNull         = 0,
  kReflection   = 1 << 1,
  kTransmission = 1 << 2,
  kDiffuse      = 1 << 3,
  kGlossy       = 1 << 4,
  kSpecular     = 1 << 5,
  kAll          = kReflection   |
                  kTransmission |
                  kDiffuse      |
                  kGlossy       |
                  kSpecular
};
/*
// ---------------------------------------------------------------------------
*/
class Bxdf : public Object
{
  /* Bxdf constructors */
 public:
  Bxdf (BsdfType type);


  /* Bxdf destructor */
 public:
  virtual ~Bxdf ();


  /* Bxdf public operators*/
 public:
  Bxdf (const Bxdf&  bxdf) = default;
  Bxdf (      Bxdf&& bxdf) = default;

  auto operator = (const Bxdf&  bxdf) -> Bxdf& = default;
  auto operator = (      Bxdf&& bxdf) -> Bxdf& = default;


  /* Bxdf public methods */
 public:
  auto Type () const -> BsdfType
  {
    return type_;
  }

  auto Matches (BsdfType type) const -> bool
  {
    return (type & type_) == type_;
  }


  /* Bxdf public overridable methods */
 public:
  virtual auto IsDelta    () const -> bool { return false; };
  virtual auto IsEmitting () const -> bool { return false; };


  /* Bxdf public interfaces */
 public:
  virtual auto Pdf
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Float = 0;

  virtual auto Evaluate
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
      const Vector3f& incident  /* BSDF coordinate system */
  )
  const -> Spectrum = 0;

  virtual auto EvaluateAndSample
  (
      const Vector3f& outgoing, /* BSDF coordinate system */
            Vector3f* incident, /* BSDF coordinate system */
      const Sample2f& sample,
            Float*    pdf,
            BsdfType* type
  )
  const -> Spectrum = 0;


  /* Bxdf override methods */
  virtual auto ToString () const -> std::string override = 0;


  /* Bxdf protected data */
 protected:
  BsdfType type_;

}; // class Bxdf
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _BXDF_H_
