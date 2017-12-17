#ifndef _FILTER_H_
#define _FILTER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../core/image.h"
#include "../core/pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto NonLocalMeansFilter
(
 const ImagePtr <T>& src,
       Float         sigma,
       Float         h
)
-> ImagePtr <T>
{
  const int kKernelSize (5);
  const int kWindowSize (13);

  const int width  (src->GetWidth ());
  const int height (src->GetHeight ());

  using Kernel = std::array <T, kKernelSize * kKernelSize * 3>;

  // Allocate memory to result image
  ImagePtr <T> result = CreateImage3 <T> (width, height);

  // Creat a kernel from image indices x and y
  auto create_kernel = [&src] (int tx, int ty) -> Kernel
  {
    const int w (src->GetWidth ());
    const int h (src->GetHeight ());

    int idx (0);
    Kernel kernel;

    for (int y = ty - kKernelSize / 2; y < ty + kKernelSize / 2; ++y)
    {
      for (int x = tx - kKernelSize / 2; x < tx + kKernelSize / 2; ++x)
      {
        int ix = std::max (0, x);
            ix = std::min (ix, w - 1);
        int iy = std::max (0, y);
            iy = std::min (iy, h - 1);

        Pixel <T> p = (*src) (ix, iy);
        kernel [idx++] = p.r_;
        kernel [idx++] = p.g_;
        kernel [idx++] = p.b_;
      }
    }
  };

  // Compute distance
  auto compute_distance = [] (const Kernel& k0, const Kernel& k1) -> Float
  {
    assert (k0.size () == k1.size ());

    T acculated (0);
    for (int i = 0; i < k0.size (); ++i)
    {
      acculated = (k0[i] - k1[i]) * (k0[i] - k1[i]);
    }
    return acculated;
  };

  // Loop for image
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      // Create kernel based on current pixel (x, y)
      const Kernel main_kernel = create_kernel (x, y);

      Pixel <T> pixel (0, 0, 0);
      T sum (0);
      // Loop for support window
      for (int sy = y - kWindowSize / 2; sy < y + kWindowSize / 2; ++sy)
      {
        for (int sx = x - kWindowSize / 2; sx < x + kWindowSize / 2; ++sx)
        {
          int ix = std::max (0, sx);
              ix = std::min (ix, width - 1);
          int iy = std::max (0, sy);
              iy = std::min (iy, height - 1);

          // Create support window's kernel
          Kernel support_kernel = create_kernel (ix, iy);

          const auto d   (compute_distance (main_kernel, support_kernel));
          const auto arg
            (-std::fmax (d - 2.0 * sigma * sigma, 0.0) * sigma / (h * h));
          const auto weight (std::exp (arg));

          sum   += weight;
          pixel += (*src) (ix, iy) * weight;
        }
      }
      (*result) (x, y) = pixel / sum;
    }
  }

  return std::move (result);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILTER_H_
