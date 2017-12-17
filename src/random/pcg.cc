#include "pcg.h"

namespace niepce
{

PCG::PCG()
{}

PCG::PCG(uint32_t seed) :
    state_(0u),
    inc_( (seed << 1u | 1u) )
{
  NextUInt32();
  state_ += kDefaultState;
  NextUInt32();
}

PCG::~PCG()
{}

auto PCG::Next01() -> Float
{
  return static_cast<Float>( NextUInt32() ) / std::numeric_limits<uint32_t>::max();
}

auto PCG::NextUInt32() -> uint32_t
{
  const uint64_t old_state = state_;
  state_ = old_state * kPcgMult + inc_;
  const uint32_t xorshifted = static_cast<uint32_t>( ((old_state >> 18u) ^ old_state) >> 27u);
  const uint32_t rot        = static_cast<uint32_t>(old_state >> 59u);
  return (xorshifted >> rot) | (xorshifted << ((~rot + 1u) & 31));
}

}  // namespace niepce
