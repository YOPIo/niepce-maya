#ifndef _IBL_H_
#define _IBL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "light.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Ibl : public Light
{
  /* Ibl constructors */
public:
  Ibl () = delete;
  Ibl (const std::string& filepath);


  /* Ibl destructor */
public:
  virtual ~Ibl () = default;


  /* Ibl public operators*/
public:
  Ibl (const Ibl&  ibl) = default;
  Ibl (      Ibl&& ibl) = default;

  auto operator = (const Ibl&  ibl) -> Ibl& = default;
  auto operator = (      Ibl&& ibl) -> Ibl& = default;


  /* Light public interface */
public:
  auto Emission
  (
   const Ray& ray
  )
  const -> Spectrum;

  auto Load (const std::string& filepath) -> void;


  /* Light private data */
private:
  ImagePtr <Float> image_;

}; // class Ibl
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IBL_H_
