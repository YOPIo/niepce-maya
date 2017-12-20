#ifndef _LAMBERT_H_
#define _LAMBERT_H_
/*
// ---------------------------------------------------------------------------
*/
#include "bsdf_utils.h"
#include "bxdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Lambert : public Bxdf
{
  /* Lambert constructors */
public:
  Lambert () = delete;
  Lambert (const Spectrum& reflectance);


  /* Lambert destructor */
public:
   ~Lambert () = default;


  /* Lambert public operators*/
public:
  Lambert (const Lambert&  brdf) = default;
  Lambert (      Lambert&& brdf) = default;

  auto operator = (const Lambert&  brdf) -> Lambert& = default;
  auto operator = (      Lambert&& brdf) -> Lambert& = default;


  /* Lambert override methods */
public:
  auto Pdf
  (
      const Vector3f& outgoing,
      const Vector3f& incident
  )
  const -> Float override final;

  auto Evaluate
  (
      const Vector3f& outgoing,
      const Vector3f& incident
  )
  const -> Spectrum override final;

  auto EvaluateAndSample
  (
      const Vector3f& outgoing,
            Vector3f* incident,
      const Sample2f& sample,
            Float*    pdf,
            BsdfType* type
  )
  const -> Spectrum override final;

  auto ToString () const -> std::string override final;


  /* Lambert private data */
 private:
  Spectrum reflectance_;

}; // class Lambert
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _LAMBERT_H_
