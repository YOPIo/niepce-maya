#ifndef _OREN_LAYAR_H_
#define _OREN_LAYAR_H_
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
*/
class OrenLayer : public Bxdf
{
  /* OrenLayer constructors */
public:
  OrenLayer () = delete;
  OrenLayer
  (
   const Spectrum& reflectance,
   Float sigma
  );


  /* OrenLayer destructor */
public:
  virtual ~OrenLayer () = default;


  /* OrenLayer public operators*/
public:
  OrenLayer (const OrenLayer&  ol) = default;
  OrenLayer (      OrenLayer&& ol) = default;

  auto operator = (const OrenLayer&  ol) -> OrenLayer& = default;
  auto operator = (      OrenLayer&& ol) -> OrenLayer& = default;


  /* OrenLayer public override methods */
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


  /* OrenLayer private data */
private:
  const Float a_;
  const Float b_;
  const Spectrum reflectance_;
}; // class OrenLayer
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _OREN_LAYAR_H_
