#ifndef _IMAGE_MAP_TEXTURE_H_
#define _IMAGE_MAP_TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "texture.h"
#include "../core/image.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class ImageMapTexture : public Texture <Spectrum>
{
  /* ImageMapTexture constructors */
public:
  ImageMapTexture () = delete;
  ImageMapTexture (const char* filename);


  /* ImageMapTexture destructor */
public:
  virtual ~ImageMapTexture () = default;


  /* ImageMapTexture public operators*/
public:
  ImageMapTexture (const ImageMapTexture&  tex) = default;
  ImageMapTexture (      ImageMapTexture&& tex) = default;

  auto operator = (const ImageMapTexture&  tex) -> ImageMapTexture& = default;
  auto operator = (      ImageMapTexture&& tex) -> ImageMapTexture& = default;


  /* ImageMapTexture public data */
public:
  auto Evaluate (const SurfaceInteraction& si) const -> Spectrum override final;
  auto ToString () const -> std::string override final;


  /* ImageMapTexture private data */
private:
  ImagePtr <Float> image_;

}; // class ImageMapTexture

}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _IMAGE_MAP_TEXTURE_H_
