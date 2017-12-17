#include "constant_texture.h"
#include "../core/geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// ConstantTexture
// ---------------------------------------------------------------------------
*/
template <typename ValueType>
ConstantTexture <ValueType>::ConstantTexture (const ValueType& value) :
  value_ (value),
  Texture <ValueType> ()
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename ValueType>
auto ConstantTexture <ValueType>::Evaluate (const SurfaceInteraction& si) const
  -> ValueType
{
  return value_;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename ValueType>
auto ConstantTexture <ValueType>::ToString () const -> std::string
{
  return std::string ("constant texture.");
}
/*
// ---------------------------------------------------------------------------
*/
template class ConstantTexture <Float>;
template class ConstantTexture <Spectrum>;
/*
// ---------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------
*/
template <typename ValueType>
auto CreateConstantTexture (const ValueType& data)
  -> std::shared_ptr <ConstantTexture<ValueType>>
{
  auto ret (std::make_shared <ConstantTexture <ValueType>> (data));
  return std::move (ret);
}
/*
// ---------------------------------------------------------------------------
*/
template auto CreateConstantTexture (const Float& data)
  -> std::shared_ptr <ConstantTexture <Float>>;
template auto CreateConstantTexture (const Spectrum& data)
  -> std::shared_ptr <ConstantTexture <Spectrum>>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
