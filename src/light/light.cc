#include "light.h"

namespace niepce
{

Light::Light (LightType  type) :
    type_        (type),
    num_samples_ (16) // Magic number, こんなもんでいいんじゃない??
{}

Light::~Light ()
{}

auto Light::Type () const -> LightType
{
  return type_;
}

auto Light::NumSamples () const -> uint32_t
{
  return num_samples_;
}

}  // namespace niepce
