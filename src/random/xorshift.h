#ifndef _XORSHIFT_H_
#define _XORSHIFT_H_

#include <cstdint>
#include <limits>

namespace niepce
{

class XorShift
{
  /* Xorshift public constructors */
 public:
  XorShift ();
  XorShift (std::uint_fast32_t seed);


  /* Xorshift public destructor */
 public:
  virtual ~XorShift();


  /* Xorshift public operators */
 public:
  XorShift (const XorShift&  rnd) = default;
  XorShift (      XorShift&& rnd) = default;

  auto operator = (const XorShift&  rnd) -> XorShift& = default;
  auto operator = (      XorShift&& rnd) -> XorShift& = default;


  /* Xorshift public methods */
 public:
  // Reset the seed
  // Give:
  //   - seed
  auto SetSeed (std::uint_fast32_t seed) -> void;

  // Generate the random number in [0, 1)
  // Return:
  //   - Random number in [0, 1)
  auto Next01 () -> float;

  // Generate the random number in [0, 2^32)
  // Return:
  //   - Random number in [0, 2^32)
  auto Next () -> std::uint_fast32_t;


 private:
  std::uint_fast32_t x_;
  std::uint_fast32_t y_;
  std::uint_fast32_t z_;
  std::uint_fast32_t w_;
};

}  // namespace niepce

#endif // _XORSHIFT_H_
