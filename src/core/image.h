#ifndef _IMAGE_H_
#define _IMAGE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "geometry.h"
#include "pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Class forward declaration
// ---------------------------------------------------------------------------
*/
template <typename T> class Image3;
/*
// ---------------------------------------------------------------------------
// Functions for Image3
// ---------------------------------------------------------------------------
*/
template <typename T>
auto CreateImage3  (size_t width, size_t height) -> ImagePtr <T>;
template <typename T>
auto LoadImage     (const char* filename) -> ImagePtr <T>;
template <typename T>
auto LoadHdrxImage (const char* filename) -> ImagePtr <T>;

// delete ?
template <typename T>
auto WriteImage    (const char* filename, const ImagePtr <T>& img) -> void;

template <typename T>
auto SaveAs (const char* filename, const Image3 <T>& img) -> void;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Image3
{
  /* Image3 constructors */
public:
  Image3 () = default;
  Image3 (size_t width, size_t height);


  /* Image3 destructor */
public:
  virtual ~Image3 () = default;


  /* Image3 public operators*/
public:
  Image3 (const Image3&  img) = default;
  Image3 (      Image3&& img) = default;

  auto operator = (const Image3&  img) -> Image3& = default;
  auto operator = (      Image3&& img) -> Image3& = default;

  auto operator () (size_t x, size_t y)       -> Pixel <T>&;
  auto operator () (size_t x, size_t y) const -> Pixel <T>;


  /* Image3 public methods */
public:
  auto At (size_t x, size_t y)       -> Pixel <T>&;
  auto At (size_t x, size_t y) const -> Pixel <T>;

  auto GetWidth  () const -> uint32_t;
  auto GetHeight () const -> uint32_t;


  /* Image3 private data */
private:
  std::unique_ptr <Pixel <T> []> data_;
  Point2u32i resolution_;
}; // class Image3
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IMAGE_H_
