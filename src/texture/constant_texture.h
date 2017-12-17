#ifndef _CONSTANT_TEXTURE_H_
#define _CONSTANT_TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
template <typename ValueType> class ConstantTexture;
/*
// ---------------------------------------------------------------------------
// Function for ConstantTexture
// ---------------------------------------------------------------------------
*/
template <typename ValueType>
auto CreateConstantTexture (const ValueType& data)
  -> std::shared_ptr <ConstantTexture<ValueType>>;
/*
// ---------------------------------------------------------------------------
*/
template <typename ValueType>
class ConstantTexture : public Texture <ValueType>
{
  /* ConstantTexture public Constructors */
 public:
  ConstantTexture () = default;
  ConstantTexture (const ValueType& value);


  /* ConstantTexture public destructor */
public:
  virtual ~ConstantTexture () = default;


  /* ConstantTexture public operators*/
public:
  ConstantTexture (const ConstantTexture&  texture) = default;
  ConstantTexture (      ConstantTexture&& texture) = default;

  auto operator = (const ConstantTexture&  texture) -> ConstantTexture&
      = default;
  auto operator = (      ConstantTexture&& texture) -> ConstantTexture&
      = default;


  /* ConstantTexture public methods  */
public:
  auto Evaluate (const SurfaceInteraction& si) const
    -> ValueType override final;

  auto ToString () const -> std::string override final;


  /* ConstantTexture private data */
private:
  ValueType value_;
}; // class ConstantTexture
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _CONSTANT_TEXTURE_H_
