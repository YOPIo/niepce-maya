#ifndef _RANDOM_SAMPLER_H_
#define _RANDOM_SAMPLER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "sampler.h"
#include "../random/xorshift.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto CreateRandomSampler () -> SamplerPtr;
/*
// ---------------------------------------------------------------------------
*/
class RandomSampler : public Sampler
{
  /* RandomSampler public constructors */
 public:
  RandomSampler ();

  /* RandomSampler public destructor */
 public:
  virtual ~RandomSampler () = default;


  /* RandomSampler public operators */
 public:
  RandomSampler (const RandomSampler&  sampler) = default;
  RandomSampler (      RandomSampler&& sampler) = default;

  auto operator = (const RandomSampler&  sampler) -> RandomSampler& = default;
  auto operator = (      RandomSampler&& sampler) -> RandomSampler& = default;


  /* RandomSampler public methods */
 public:
  auto Get1D () -> Sample1f override final;

  auto Get2D () -> Sample2f override final;


  /* RandomSampler private data */
 private:
  XorShift rng_;

}; // class RandomSampler
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _RANDOM_SAMPLER_H_
