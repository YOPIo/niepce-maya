#ifndef _PIXEL_H_
#define _PIXEL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Pixel
{
  /* Pixel constructors */
public:
  Pixel () = default;
  Pixel (T r, T g, T b);


  /* Pixel destructor */
public:
  virtual ~Pixel () = default;


  /* Pixel public operators*/
public:
  Pixel (const Pixel&  pixel) = default;
  Pixel (      Pixel&& pixel) = default;

  auto operator = (const Pixel&  pixel) -> Pixel& = default;
  auto operator = (      Pixel&& pixel) -> Pixel& = default;

  auto operator [] (const size_t idx)       -> T&;
  auto operator [] (const size_t idx) const -> T;

  auto operator + (const Pixel& p) const -> Pixel;
  auto operator - (const Pixel& p) const -> Pixel;
  auto operator * (T t)        const -> Pixel;
  auto operator / (T t)        const -> Pixel;

  auto operator += (const Pixel& p) -> Pixel&;
  auto operator -= (const Pixel& p) -> Pixel&;
  auto operator *= (T t) -> Pixel&;
  auto operator /= (T t) -> Pixel&;

  /* Pixel public data */
public:
  union
  {
    struct { T r_, g_, b_; };
    std::array <T, 3> rgb_;
  };

}; // class Pixel
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _PIXEL_H_
