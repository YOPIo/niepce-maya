#include "image.h"
/*
// ---------------------------------------------------------------------------
*/
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb_image.h"
#endif // STB_IMAGE_IMPLEMENTATION

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ext/stb_image_write.h"
#endif // STB_IMAGE_WRITE_IMPLEMENTATION
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Image3
// ---------------------------------------------------------------------------
*/
template <typename T>
Image3 <T>::Image3 (size_t width, size_t height) :
  resolution_ (width, height),
  data_       (new Pixel <T> [width * height])
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image3 <T>::operator () (size_t x, size_t y) -> Pixel <T>&
{
  return data_ [y * resolution_.x + x];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image3 <T>::operator () (size_t x, size_t y) const -> Pixel <T>
{
  return data_ [y * resolution_.x + x];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image3 <T>::At (size_t x, size_t y) -> Pixel <T>&
{
  return data_ [y * resolution_.x + x];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image3 <T>::At (size_t x, size_t y) const -> Pixel <T>
{
  return data_ [y * resolution_.x + x];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image3 <T>::GetWidth () const -> uint32_t
{
  return resolution_.x;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Image3 <T>::GetHeight () const -> uint32_t
{
  return resolution_.y;
}
/*
// ---------------------------------------------------------------------------
*/
template class Image3 <Float>;
template class Image3 <int>;
/*
// ---------------------------------------------------------------------------
// Functions for Image3 <T>
// ---------------------------------------------------------------------------
*/
template <typename T>
auto CreateImage3 (size_t width, size_t height) -> ImagePtr <T>
{
  return std::make_shared <Image3 <T>> (width, height);
}
/*
// ---------------------------------------------------------------------------
*/
template auto CreateImage3 <Float> (size_t width, size_t height)
  -> ImagePtr <Float>;
template auto CreateImage3 <int>   (size_t width, size_t height)
  -> ImagePtr <int>;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto LoadImage (const char* filename) -> ImagePtr <T>
{
  // Load width, height and image data as rgb (0 - 255)
  int width, height, n;
  unsigned char* data = stbi_load (filename, &width, &height, &n, 3);
  if (data == NULL)
  {
    // File was not found
    throw std::exception ();
    return nullptr;
  }

  // Allocate memory
  ImagePtr <T> ret (CreateImage3 <T> (width, height));

  // Copy data
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      // return std::pow (v, 1.0 / 2.2) * 255.0 + 0.5;
      const T r (data[y * width * n + 3 * x + 0] / 255.0);
      const T g (data[y * width * n + 3 * x + 1] / 255.0);
      const T b (data[y * width * n + 3 * x + 2] / 255.0);
      (*ret) (x, y) = Pixel <T> (r, g, b);
    }
  }

  // Free original image
  stbi_image_free (data);

  return std::move (ret);
}
/*
// ---------------------------------------------------------------------------
*/
template auto LoadImage <Float> (const char* filename) -> ImagePtr <Float>;
template auto LoadImage <int>   (const char* filename) -> ImagePtr <int>;
/*
// ---------------------------------------------------------------------------
*/
template <typename Float>
auto LoadHdrImage (const char* filename) -> ImagePtr <Float>
{

  stbi_hdr_to_ldr_gamma(2.2f);
  stbi_hdr_to_ldr_scale(1.0f);

  int width, height, n;
  float* data = stbi_loadf (filename, &width, &height, &n, 4);

  // Allocate memory
  ImagePtr <Float> ret (CreateImage3 <Float> (width, height));

  // Copy data
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      const Float r (data[y * width * n + 3 * x + 0]);
      const Float g (data[y * width * n + 3 * x + 1]);
      const Float b (data[y * width * n + 3 * x + 2]);
      (*ret) (x, y) = Pixel <Float> (r, g, n);
    }
  }

  // Free original image
  stbi_image_free (data);

  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto WriteImage
(
 const char*        filename,
 const ImagePtr<T>& img
)
-> void
{
  const uint32_t width  (img->GetWidth  ());
  const uint32_t height (img->GetHeight ());

  unsigned char* data = new unsigned char [width * height * 3];

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      data[y * width * 3 + 3 * x + 0] = 255.0 * (*img) (x, y).r_;
      data[y * width * 3 + 3 * x + 1] = 255.0 * (*img) (x, y).g_;
      data[y * width * 3 + 3 * x + 2] = 255.0 * (*img) (x, y).b_;
    }
  }

  stbi_write_png (filename, width, height, 3, (void*)data, width * 3);

  delete [] data;
}
/*
// ---------------------------------------------------------------------------
*/
template
auto WriteImage <Float>
(
 const char*            filename,
 const ImagePtr<Float>& img
)
-> void;

template
auto WriteImage <int>
(
 const char*          filename,
 const ImagePtr<int>& img
)
-> void;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto SaveAs (const char* filename, const Image3 <T>& img) -> void
{
  const uint32_t width  (img.GetWidth  ());
  const uint32_t height (img.GetHeight ());

  auto hdr_to_int = [](Float v) -> int
  {
    if (v < 0.0) { v = 0; }
    if (v > 1.0) { v = 1; }
    if (std::isnan(v))
    {
      std::cout << "NaN detected" << std::endl;
      v = 0;
    }
    return std::pow (v, 1.0 / 2.2) * 255.0 + 0.5;
  };

  unsigned char* data = new unsigned char [width * height * 3];

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      data[y * width * 3 + 3 * x + 0] = hdr_to_int (img (x, y).r_);
      data[y * width * 3 + 3 * x + 1] = hdr_to_int (img (x, y).g_);
      data[y * width * 3 + 3 * x + 2] = hdr_to_int (img (x, y).b_);
    }
  }

  stbi_write_png (filename, width, height, 3, (void*)data, width * 3);

  delete [] data;
}
/*
// ---------------------------------------------------------------------------
*/
template auto SaveAs (const char* filename, const Image3 <Float>& img) -> void;
template auto SaveAs (const char* filename, const Image3 <int>&   img) -> void;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
