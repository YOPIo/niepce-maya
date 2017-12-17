#include "pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
Pixel <T>::Pixel (T r, T g, T b) :
  r_ (r), g_ (g), b_ (b)
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator [] (const size_t idx) -> T&
{
  return rgb_[idx];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator [] (const size_t idx) const -> T
{
  return rgb_[idx];
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator + (const Pixel &p) const -> Pixel <T>
{
  return Pixel (r_ + p.r_, g_ + p.g_, b_ + p.g_);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator - (const Pixel &p) const -> Pixel <T>
{
  return Pixel (r_ - p.r_, g_ - p.g_, b_ - p.g_);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator * (T t) const -> Pixel <T>
{
  return Pixel (r_ * t, g_ * t, b_ * t);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator / (T t) const -> Pixel <T>
{
  return Pixel (r_ / t, g_ / t, b_ / t);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator += (const Pixel& p) -> Pixel <T>&
{
  this->r_ += p.r_;
  this->g_ += p.g_;
  this->b_ += p.b_;
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator -= (const Pixel& p) -> Pixel <T>&
{
  this->r_ -= p.r_;
  this->g_ -= p.g_;
  this->b_ -= p.b_;
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator *= (T t) -> Pixel <T>&
{
  this->r_ *= t;
  this->g_ *= t;
  this->b_ *= t;
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Pixel <T>::operator /= (T t) -> Pixel <T>&
{
  this->r_ /= t;
  this->g_ /= t;
  this->b_ /= t;
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
template class Pixel <Float>;
template class Pixel <int>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
