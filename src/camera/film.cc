#include "film.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Film::Film
(
 const char*       filename,
 const Point2u32i& full_resolution
) :
  filename_        (filename),
  full_resolution_ (full_resolution)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Film::SetPixel (const Point2u32i& target, const XyzPixel& data) -> void
{
  if (full_resolution_.x <= target.x || full_resolution_.y <= target.y)
  {
    // Todo: Throw range over exception
    return;
  }
  pixles_[target.x * full_resolution_.y + target.x] = data;
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::GetPixel (const Point2u32i &target, XyzPixel *data) const -> void
{
  if (full_resolution_.x <= target.x || full_resolution_.y <= target.y)
  {
    // Todo: Throw range over exception
    return;
  }
  *data = pixles_[target.x * full_resolution_.y + target.x];
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
