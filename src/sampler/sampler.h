#ifndef _SAMPLER_H_
#define _SAMPLER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Sampler
{
  /* Sampler public constructors */
 public:
  Sampler ();

  /* Sampler public destructor */
 public:
  virtual ~Sampler () = default;

  /* Sampler public operators */
 public:
  Sampler (const Sampler&  sampler) = default;
  Sampler (      Sampler&& sampler) = default;

  auto operator = (const Sampler&  sampler) -> Sampler& = default;
  auto operator = (      Sampler&& sampler) -> Sampler& = default;


  /* Sampler public interfaces */
 public:
  // - [0, 1)
  virtual auto Get1D () -> Sample1f = 0;

  // - [0, 1)^2
  virtual auto Get2D () -> Sample2f = 0;

}; // class Sampler
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SAMPLER_H_
