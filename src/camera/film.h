#ifndef _FILM_H_
#define _FILM_H_
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
// Change class name XyzPixle to Pixel after delete Pixel class in core/pixel
// ---------------------------------------------------------------------------
*/
struct XyzPixel
{
  union
  {
    struct { Float x, y, z; };
    std::array <Float, 3> xyz;
  };
};
/*
// ---------------------------------------------------------------------------
*/
class Film
{
  /* Film constructors */
public:
  Film () = delete;
  Film
  (
   const char*       filename,
   const Point2u32i& full_resolution
  );


  /* Film destructor */
public:
  virtual ~Film () = default;


  /* Film public operators*/
public:
  Film (const Film&  film) = delete;
  Film (      Film&& film) = default;

  auto operator = (const Film&  film) -> Film& = delete;
  auto operator = (      Film&& film) -> Film& = default;


  /* Film public methods */
public:
  auto SetPixel (const Point2u32i& target, const XyzPixel& data)       -> void;
  auto GetPixel (const Point2u32i& target,       XyzPixel* data) const -> void;


  /* FIlm private data */
private:
  const std::string filename_;
  const Point2u32i  full_resolution_;

  std::unique_ptr <XyzPixel []> pixles_;
}; // class Film
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILM_H_
