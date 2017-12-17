#ifndef _OBJECT_H_
#define _OBJECT_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Object
{
  /* Object constructors */
public:
  Object () = default;;


  /* Object destructor */
public:
  virtual ~Object () = default;


  /* Object public operators*/
public:
  Object (const Object&  obj) = default;
  Object (      Object&& obj) = default;

  auto operator = (const Object&  obj) -> Object& = default;
  auto operator = (      Object&& obj) -> Object& = default;


  /* Object public interface */
public:
  // For debugging and dumping
  virtual auto ToString () const -> std::string = 0;

}; // class Object
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _OBJECT_H_
