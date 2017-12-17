#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../core/niepce.h"
#include "../core/geometry.h"
//#include "../core/interaction.h"
//#include "../bxdf/bxdf_record.h"

namespace niepce
{

enum LightType
{
  kPoint      = 1 << 0,
  kDirection  = 1 << 1,
  kArea       = 1 << 2,
  kImageBased = 1 << 3
};

// TODO: Add transform
class Light
{
 public:
  /* Light constructors */
  Light () = delete;
  Light (LightType  type);
  virtual ~Light ();

  Light (const Light&  light) = default;
  Light (      Light&& light) = default;

  /* Light operators*/
  auto operator = (const Light&  light) -> Light& = default;
  auto operator = (      Light&& light) -> Light& = default;


  /* Light public method */
 public:
  auto Type       () const -> LightType;
  auto NumSamples () const -> uint32_t;


  /* Light public interface */
 public:
  // Return emission of this light
  virtual auto Emission
  (
   const Ray& ray
  )
  const -> Spectrum = 0;


  /* Light data interface */
 protected:
  const LightType type_;
  const uint32_t  num_samples_;

}; // class Light

}  // namespace niepce

#endif // _LIGHT_H_
