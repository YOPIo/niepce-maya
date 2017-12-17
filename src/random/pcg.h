#ifndef _PCG_H_
#define _PCG_H_

#include "../core/niepce.h"

namespace niepce
{

class PCG
{
 public:
  PCG();
  PCG(uint32_t seed);
  virtual ~PCG();

  PCG(const PCG& pcg) = default;
  PCG(PCG&& pcg)      = default;

  auto operator = (const PCG& pcg) -> PCG& = default;
  auto operator = (PCG&& pcg)      -> PCG& = default;

  /* Public methods */
  auto Next01()     -> Float;
  auto NextUInt32() -> uint32_t;

 private:
  /* Private const values */
  static constexpr uint64_t kDefaultState  = 0x853c49e6748fea9bULL;
  static constexpr uint64_t kDefaultStream = 0xda3e39cb94b95bdbULL;
  static constexpr uint64_t kPcgMult       = 0x5851f42d4c957f2dULL;

  /* Private member data */
  uint64_t state_;
  uint64_t inc_;
};


}  // namespace niepce

#endif // _PCG_H_
