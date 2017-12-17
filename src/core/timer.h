#ifndef _TIMER_h_
#define _TIMER_h_

#include <chrono>
#include <functional>
#include <iostream>

namespace niepce
{

class Timer
{
  /* Timer constructors */
public:
  Timer () :
    start_ (std::chrono::system_clock::now ()),
    t_     (30),
    final_ (265)
  {}

  /* Timer destructor */
public:
  virtual ~Timer ()
  {};


  /* Timer public operators*/
public:
  Timer (const Timer&  timer) = default;
  Timer (      Timer&& timer) = default;

  auto operator = (const Timer&  timer) -> Timer& = default;
  auto operator = (      Timer&& timer) -> Timer& = default;


  /* Timer public methods */
public:
  auto IsPassed30 () -> bool
  {
    const auto now  = std::chrono::system_clock::now ();
    const auto diff = now - now_;
    if (std::chrono::duration_cast<std::chrono::seconds> (diff) > t_)
    {
      now_ = now;
      return true;
    }
    return false;
  }

  auto IsNeedFinalProcess () -> bool
  {
    const auto now  = std::chrono::system_clock::now ();
    const auto diff = now - start_;
    if (std::chrono::duration_cast<std::chrono::seconds> (diff) > final_)
    {
      std::cout << "Time up" << std::endl;
      return true;
    }
    return false;
  }


  /* Timer private methods */
private:
  std::chrono::system_clock::time_point start_;
  std::chrono::system_clock::time_point now_;
  std::chrono::system_clock::time_point end_;

  const std::chrono::seconds t_;
  const std::chrono::seconds final_;
}; // class Timer


}  // namespace niepce

#endif // _TIMER_h_
