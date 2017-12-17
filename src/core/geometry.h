#ifndef _GEMOETRY_H_
#define _GEMOETRY_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
template <typename T>
auto operator << (std::ostream& os, const BoundingBox2<T>& b) -> std::ostream&;
template <typename T>
auto operator << (std::ostream& os, const BoundingBox3<T>& b) -> std::ostream&;
/*
// ---------------------------------------------------------------------------
// Forward declarations
// Point2
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Point2<T>& p0, const Point2<T>& p1) -> bool;
template <typename T>
auto operator != (const Point2<T>& p0, const Point2<T>& p1) -> bool;
template <typename T>
auto operator +  (const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>;
template <typename T>
auto operator -  (const Point2<T>& p0, const Point2<T>& p1) -> Vector2<T>;
template <typename T>
auto operator *  (const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>;
template <typename T, typename U>
auto operator *  (const Point2<T>&  p,                 U t) -> Point2<T>;
template <typename T, typename U>
auto operator *  (               T  t, const Point2<T>&  p) -> Point2<T>;
template <typename T, typename U>
auto operator /  (const Point2<T>&  p,                 T t) -> Point2<T>;
template <typename T>
auto operator << (std::ostream&    os, const  Point2<T>& p) -> std::ostream&;
/*
// ---------------------------------------------------------------------------
// Point3
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Point3<T>& p0, const Point3<T>& p1) -> bool;
template <typename T>
auto operator != (const Point3<T>& p0, const Point3<T>& p1) -> bool;
template <typename T>
auto operator +  (const Point3<T>& p0, const Point3<T>& p1) -> Point3<T>;
template <typename T>
auto operator -  (const Point3<T>& p0, const Point3<T>& p1) -> Vector3<T>;
template <typename T>
auto operator *  (const Point3<T>& p0, const Point3<T>& p1) -> Point3<T>;
template <typename T, typename U>
auto operator *  (const Point3<T>& p0,                 U t) -> Point3<T>;
template <typename T, typename U>
auto operator *  (                U t, const Point3<T>&  p) -> Point3<T>;
template <typename T, typename U>
auto operator /  (const Point3<T>&  p,                 U t) -> Point3<T>;
template <typename T>
auto operator << (std::ostream&    os, const  Point3<T>& p) -> std::ostream&;
/*
// ---------------------------------------------------------------------------
// Point4
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Point4<T>& p0, const Point4<T>& p1) -> bool;
template <typename T>
auto operator != (const Point4<T>& p0, const Point4<T>& p1) -> bool;
template <typename T>
auto operator +  (const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>;
template <typename T>
auto operator -  (const Point4<T>& p0, const Point4<T>& p1) -> Vector3<T>;
template <typename T>
auto operator *  (const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>;
template <typename T, typename U>
auto operator *  (const Point4<T>& p0,                 U t) -> Point4<T>;
template <typename T, typename U>
auto operator *  (                U t, const Point4<T>&  p) -> Point4<T>;
template <typename T, typename U>
auto operator /  (const Point4<T>&  p,                 U t) -> Point4<T>;
template <typename T>
auto operator << (std::ostream&    os, const  Point4<T>& p) -> std::ostream&;
/*
// ---------------------------------------------------------------------------
// Vector2
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Vector2<T>& p0, const Vector2<T>& p1) -> bool;
template <typename T>
auto operator != (const Vector2<T>& p0, const Vector2<T>& p1) -> bool;
template <typename T>
auto operator +  (const Vector2<T>& p0, const Vector2<T>& p1) -> Vector2<T>;
template <typename T>
auto operator -  (const Vector2<T>& p0, const Vector2<T>& p1) -> Vector2<T>;
template <typename T>
auto operator *  (const Vector2<T>& v0, const Vector2<T>& v1) -> Vector2<T>;
template <typename T, typename U>
auto operator *  (const Vector2<T>&  p,                 U  t) -> Vector2<T>;
template <typename T, typename U>
auto operator *  (                U  t, const Vector2<T>&  p) -> Vector2<T>;
template <typename T, typename U>
auto operator /  (const Vector2<T>&  p,                 U  t) -> Vector2<T>;
template <typename T>
auto operator << (std::ostream&     os, const Vector2<T>&  v) -> std::ostream&;
/*
// ---------------------------------------------------------------------------
// Vector3
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Vector3<T>& p0, const Vector3<T>& p1) -> bool;
template <typename T>
auto operator != (const Vector3<T>& p0, const Vector3<T>& p1) -> bool;
template <typename T>
auto operator +  (const Vector3<T>& p0, const Vector3<T>& p1) -> Vector3<T>;
template <typename T>
auto operator -  (const Vector3<T>& p0, const Vector3<T>& p1) -> Vector3<T>;
template <typename T>
auto operator *  (const Vector3<T>& v0, const Vector3<T>& v1) -> Vector3<T>;
template <typename T, typename U>
auto operator *  (const Vector3<T>& p0,                  U t) -> Vector3<T>;
template <typename T, typename U>
auto operator *  (                 U t, const Vector3<T>&  p) -> Vector3<T>;
template <typename T, typename U>
auto operator /  (const Vector3<T>&  p,                  U t) -> Vector3<T>;
template <typename T>
auto operator << (std::ostream&     os, const  Vector3<T>& v) -> std::ostream&;
/*
// ---------------------------------------------------------------------------
// Vector4
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Vector4<T>& p0, const Vector4<T>& p1) -> bool;
template <typename T>
auto operator != (const Vector4<T>& p0, const Vector4<T>& p1) -> bool;
template <typename T>
auto operator +  (const Vector4<T>& p0, const Vector4<T>& p1) -> Vector4<T>;
template <typename T>
auto operator -  (const Vector4<T>& p0, const Vector4<T>& p1) -> Vector4<T>;
template <typename T>
auto operator *  (const Vector4<T>& v0, const Vector4<T>& v1) -> Vector4<T>;
template <typename T, typename U>
auto operator *  (const Vector4<T>& p0,                  U t) -> Vector4<T>;
template <typename T, typename U>
auto operator *  (                 U t, const Vector4<T>&  p) -> Vector4<T>;
template <typename T, typename U>
auto operator /  (const Vector4<T>&  p,                  U t) -> Vector4<T>;
template <typename T>
auto operator << (std::ostream&     os, const  Vector4<T>& v) -> std::ostream&;
/*
// ---------------------------------------------------------------------------
// Normal3
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Normal3<T>& p0, const Normal3<T>& p1) -> bool;
template <typename T>
auto operator != (const Normal3<T>& p0, const Normal3<T>& p1) -> bool;
template <typename T>
auto operator +  (const Normal3<T>& p0, const Normal3<T>& p1) -> Normal3<T>;
template <typename T>
auto operator -  (const Normal3<T>& p0, const Normal3<T>& p1) -> Normal3<T>;
template <typename T, typename U>
auto operator *  (const Normal3<T>& p0,                  U t) -> Normal3<T>;
template <typename T, typename U>
auto operator *  (                 U t, const Normal3<T>&  p) -> Normal3<T>;
template <typename T>
auto operator /  (const Normal3<T>&  p,                  T t) -> Normal3<T>;
template <typename T>
auto operator << (std::ostream&     os, const  Normal3<T>& n) -> std::ostream&;
/*
// ---------------------------------------------------------------------------
// Maxrix4x4
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1) -> bool;
template <typename T>
auto operator != (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1) -> bool;
template <typename T>
auto operator +  (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1)
  -> Matrix4x4<T>;
template <typename T>
auto operator -  (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1)
  -> Matrix4x4<T>;
template <typename T>
auto operator *  (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1)
  -> Matrix4x4<T>;
template <typename T>
auto operator *  (const Matrix4x4<T>&  m, const    Point4<T>&  p) -> Point4<T>;
template <typename T>
auto operator *  (const Matrix4x4<T>&  m, const   Vector4<T>&  v) -> Vector4<T>;
template <typename T, typename U>
auto operator *  (const Matrix4x4<T>&  m,                    U t)
  -> Matrix4x4<T>;
template <typename T>
auto operator *  (std::ostream&       os, const Matrix4x4<T>&  m)
-> std::ostream&;
/*
// ---------------------------------------------------------------------------
// Global operators
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const  Point2<T>& p, const Vector2<T>& v) -> Point2<T>;
template <typename T>
auto operator + (const Vector2<T>& v, const  Point2<T>& p) -> Point2<T>;
template <typename T>
auto operator + (const  Point3<T>& p, const Vector3<T>& v) -> Point3<T>;
template <typename T>
auto operator + (const Vector3<T>& v, const  Point3<T>& p) -> Point3<T>;
template <typename T>
auto operator + (const  Point4<T>& p, const Vector4<T>& v) -> Point4<T>;
template <typename T>
auto operator + (const Vector4<T>& v, const  Point4<T>& p) -> Point4<T>;
/*
// ---------------------------------------------------------------------------
// Geometry utility functions
// ---------------------------------------------------------------------------
*/
template <typename T> auto Distance (const Point2<T>&, const Point2<T>&) -> T;
template <typename T> auto Distance (const Point3<T>&, const Point3<T>&) -> T;
/*
// ---------------------------------------------------------------------------
*/
template <typename T> auto OrthoNormalBasis
(
    const Normal3<T>& normal,
          Vector3<T>* tangent,
          Vector3<T>* binormal
) -> void;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Min (const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>;
template <typename T>
auto Min (const Point3<T>& p0, const Point3<T>& p1) -> Point3<T>;
template <typename T>
auto Min (const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Max (const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>;
template <typename T>
auto Max (const Point3<T>& p0, const Point3<T>& p1) -> Point3<T>;
template <typename T>
auto Max (const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Vector2<T>& v0, const Vector2<T>& v1) -> T;
template <typename T>
auto Dot (const  Point2<T>&  p, const Vector2<T>&  v) -> T;
template <typename T>
auto Dot (const Vector2<T>&  v, const  Point2<T>&  p) -> T;
template <typename T>
auto Dot (const Vector3<T>& v0, const Vector3<T>& v1) -> T;
template <typename T>
auto Dot (const  Point3<T>&  p, const Vector3<T>&  v) -> T;
template <typename T>
auto Dot (const Vector3<T>&  v, const  Point3<T>&  p) -> T;
template <typename T>
auto Dot (const Normal3<T>& n0, const Normal3<T>& n1) -> T;
template <typename T>
auto Dot (const Vector3<T>&  v, const Normal3<T>&  n) -> T;
template <typename T>
auto Dot (const Normal3<T>& v0, const Vector3<T>& v1) -> T;
template <typename T>
auto Dot (const  Point3<T>&  p, const Normal3<T>&  n) -> T;
template <typename T>
auto Dot (const Normal3<T>&  n, const  Point3<T>&  p) -> T;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Vector2<T>& v0, const Vector2<T>& v1) -> T;
template <typename T>
auto Cross (const  Point2<T>&  p, const Vector2<T>&  v) -> T;
template <typename T>
auto Cross (const Vector2<T>&  v, const  Point2<T>&  p) -> T;
template <typename T>
auto Cross (const Vector3<T>& v0, const Vector3<T>& v1) -> Vector3<T>;
template <typename T>
auto Cross (const  Point3<T>&  p, const Vector3<T>&  v) -> Vector3<T>;
template <typename T>
auto Cross (const Vector3<T>&  v, const  Point3<T>&  p) -> Vector3<T>;
template <typename T>
auto Cross (const Normal3<T>& n0, const Normal3<T>& n1) -> Normal3<T>;
template <typename T>
auto Cross (const Vector3<T>&  v, const Normal3<T>&  n) -> Vector3<T>;
template <typename T>
auto Cross (const Normal3<T>&  n, const Vector3<T>&  v) -> Vector3<T>;
template <typename T>
auto Cross (const  Point3<T>&  p, const Normal3<T>&  n) -> Vector3<T>;
template <typename T>
auto Cross (const Normal3<T>&  n, const  Point3<T>&  p) -> Vector3<T>;
/*
// ---------------------------------------------------------------------------
*/
template <typename T> auto Normalize (const Vector2<T>& v) -> Vector2<T>;
template <typename T> auto Normalize (const Vector3<T>& v) -> Vector3<T>;
template <typename T> auto Normalize (const Vector4<T>& v) -> Vector4<T>;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Union (const BoundingBox2<T>& b0, const BoundingBox2<T>& b1)
  -> BoundingBox2<T>;
template <typename T>
auto Union (const BoundingBox3<T>& b0, const BoundingBox3<T>& b2)
  -> BoundingBox3<T>;
/*
// ---------------------------------------------------------------------------
*/
template <typename T> auto SphericalTheta (const Vector3<T>& v) -> T;
template <typename T> auto SphericalPhi   (const Vector3<T>& v) -> T;
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Inverse (const Matrix4x4<T>& m) -> Matrix4x4<T>;
/*
// ---------------------------------------------------------------------------
// Class definitions
// ---------------------------------------------------------------------------
*/
template <typename T>
class Point2
{
  /* Point2<T> public constructors */
 public:
  Point2<T> ()
  {};

  Point2<T> (const T& t) :
      x (t),
      y (t)
  {}

  Point2<T> (const T& t0, const T& t1) :
      x (t0),
      y (t1)
  {}


  /* Point2<T> public destructor */
 public:
  virtual ~Point2<T> () = default;


  /* Point2<T> public operators */
 public:
  Point2<T> (const Point2<T>&  p) = default;
  Point2<T> (      Point2<T>&& p) = default;

  auto operator = (const Point2<T>&  p) -> Point2<T>& = default;
  auto operator = (      Point2<T>&& p) -> Point2<T>& = default;

  auto operator [] (std::size_t idx) const -> T
  {
    return xy [idx];
  }

  auto operator [] (std::size_t idx) -> T&
  {
    return xy [idx];
  }

  auto operator - () const -> Point2<T>
  {
    return Point2<T> (-x, -y);
  }

  auto operator += (const Vector2<T>& v) -> Point2<T>&
  {
    x += v.x;
    y += v.y;
    return *this;
  }

  auto operator -= (const Vector2<T>& v) -> Point2<T>&
  {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  auto operator *= (const T& t) -> Point2<T>&
  {
    x *= static_cast<T> (t);
    y *= static_cast<T> (t);
    return *this;
  }

  auto operator /= (const T& t) -> Point2<T>&
  {
    const T inv = static_cast<T> (1.0 / t);
    x *= static_cast<T> (inv);
    y *= static_cast<T> (inv);
    return *this;
  }

  /* Point2 public methods */
public:
  auto ToString () -> std::string
  {
    std::string str ("[");
    str += std::to_string (x) + ", " + std::to_string (y) + "]";
    return str;
  }


  /* Point2<T> public constant values */
public:
  static constexpr auto Max () -> Point2<T>
  {
    return Point2<T> (std::numeric_limits<T>::max ());
  }

  static constexpr auto Min () -> Point2<T>
  {
    return Point2<T> (std::numeric_limits<T>::min ());
  }

  static constexpr auto Infinity () -> Point2<T>
  {
    return Point2<T> (std::numeric_limits<T>::infinity ());
  }

  static constexpr auto Lowest () -> Point2<T>
  {
    return Point2<T> (std::numeric_limits<T>::lowest ());
  }

  static constexpr auto NaN () -> Point2<T>
  {
    return Point2<T> (std::numeric_limits<T>::quite_NaN ());
  }

  static constexpr auto One () -> Point2<T>
  {
    return Point2<T> (static_cast<T> (1.0));
  }

  static constexpr auto Zero () -> Point2<T>
  {
    return Point2<T> (static_cast<T> (0.0));
  }


  /* Point2<T> public data */
 public:
  union
  {
    struct { T x, y; };
    struct { T u, v; };
    struct { T s, t; };
    T xy [2];
    T uv [2];
    T st [2];
  };

}; // class Point2
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Point3
{
  /* Point3<T> public constructors */
 public:
  Point3<T> () :
      x (static_cast<T> (0)),
      y (static_cast<T> (0)),
      z (static_cast<T> (0))
  {};

  Point3<T> (const T& t) :
      x (t),
      y (t),
      z (t)
  {}

  Point3<T> (const T& t0, const T& t1, const T& t2) :
      x (t0),
      y (t1),
      z (t2)
  {}

  /* Point3<T> public destructor */
 public:
  virtual ~Point3<T> () = default;


  /* Point3<T> public operators */
 public:
  Point3<T> (const Point3<T>&  p) = default;
  Point3<T> (      Point3<T>&& p) = default;

  auto operator = (const Point3<T>&  p) -> Point3<T>& = default;
  auto operator = (      Point3<T>&& p) -> Point3<T>& = default;

  operator Vector3<T> () const
  {
    return Vector3<T> (x, y, z);
  }

  auto operator [] (std::size_t idx) const -> T
  {
    return xyz [idx];
  }

  auto operator [] (std::size_t idx) -> T&
  {
    return xyz [idx];
  }

  auto operator - () const -> Point3<T>
  {
    return Point3<T> (-x, -y, -z);
  }

  auto operator += (const Vector2<T>& v) -> Point3<T>&
  {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  auto operator -= (const Vector2<T>& v) -> Point3<T>&
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  auto operator *= (const T& t) -> Point3<T>&
  {
    x *= static_cast<T> (t);
    y *= static_cast<T> (t);
    z *= static_cast<T> (t);
    return *this;
  }

  auto operator /= (const T& t) -> Point3<T>&
  {
    const T inv = static_cast<T> (1.0 / t);
    x *= static_cast<T> (inv);
    y *= static_cast<T> (inv);
    z *= static_cast<T> (inv);
    return *this;
  }


  /* Point3 public methods */
public:
  auto ToString () -> std::string
  {
    std::string str ("[");
    str += std::to_string (x) + ", " + std::to_string (y) + ", " +
           std::to_string (z) + "]";
    return str;
  }


  /* Point3<T> public constant values */
public:
  static constexpr auto Max () -> Point3<T>
  {
    return Point3<T> (std::numeric_limits<T>::max ());
  }

  static constexpr auto Min () -> Point3<T>
  {
    return Point3<T> (std::numeric_limits<T>::min ());
  }

  static constexpr auto Infinity () -> Point3<T>
  {
    return Point3<T> (std::numeric_limits<T>::infinity ());
  }

  static constexpr auto Lowest () -> Point3<T>
  {
    return Point3<T> (std::numeric_limits<T>::lowest ());
  }

  static constexpr auto NaN () -> Point3<T>
  {
    return Point3<T> (std::numeric_limits<T>::quite_NaN ());
  }

  static constexpr auto One () -> Point3<T>
  {
    return Point3<T> (static_cast<T> (1.0));
  }

  static constexpr auto Zero () -> Point3<T>
  {
    return Point3<T> (static_cast<T> (0.0));
  }


  /* Point3<T> public data */
 public:
  union
  {
    struct { T x, y, z; };
    struct { T r, g, b; };
    struct { T s, t, u; };
    T xyz [3];
    T rgb [3];
    T stu [3];
  };

}; // class Point3
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Point4
{
  /* Point4<T> public constructors */
 public:
  Point4<T> () :
      x (static_cast<T> (0)),
      y (static_cast<T> (0)),
      z (static_cast<T> (0)),
      w (static_cast<T> (0))
  {};

  Point4<T> (const T& t) :
      x (t),
      y (t),
      z (t),
      w (t)
  {}

  Point4<T> (const T& t0, const T& t1, const T& t2, const T& t3) :
      x (t0),
      y (t1),
      z (t2),
      w (t3)
  {}

  /* Point4<T> public destructor */
 public:
  virtual ~Point4<T> () = default;


  /* Point4<T> public operators */
 public:
  Point4<T> (const Point4<T>&  p) = default;
  Point4<T> (      Point4<T>&& p) = default;

  auto operator = (const Point4<T>&  p) -> Point4<T>& = default;
  auto operator = (      Point4<T>&& p) -> Point4<T>& = default;

  auto operator [] (std::size_t idx) const -> T
  {
    return xyzw [idx];
  }

  auto operator [] (std::size_t idx) -> T&
  {
    return xyzw [idx];
  }

  auto operator - () const -> Point4<T>
  {
    return Point4<T> (-x, -y, -z, -w);
  }

  auto operator += (const Vector2<T>& v) -> Point4<T>&
  {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }

  auto operator -= (const Vector2<T>& v) -> Point4<T>&
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }

  auto operator *= (const T& t) -> Point4<T>&
  {
    x *= static_cast<T> (t);
    y *= static_cast<T> (t);
    z *= static_cast<T> (t);
    w *= static_cast<T> (t);
    return *this;
  }

  auto operator /= (const T& t) -> Point4<T>&
  {
    const T& inv = static_cast<T> (1.0 / t);
    x *= static_cast<T> (inv);
    y *= static_cast<T> (inv);
    z *= static_cast<T> (inv);
    w *= static_cast<T> (inv);
    return *this;
  }


  /* Point4 public methods */
public:
  auto ToString () -> std::string
  {
    std::string str ("[");
    str += std::to_string (x) + ", " + std::to_string (y) + ", " +
           std::to_string (z) + ", " + std::to_string (w) + "]";
    return str;
  }


  /* Point4<T> public constant values */
public:
  static constexpr auto Max () -> Point4<T>
  {
    return Point4<T> (std::numeric_limits<T>::max ());
  }

  static constexpr auto Min () -> Point4<T>
  {
    return Point4<T> (std::numeric_limits<T>::min ());
  }

  static constexpr auto Infinity () -> Point4<T>
  {
    return Point4<T> (std::numeric_limits<T>::infinity ());
  }

  static constexpr auto Lowest () -> Point4<T>
  {
    return Point4<T> (std::numeric_limits<T>::lowest ());
  }

  static constexpr auto NaN () -> Point4<T>
  {
    return Point4<T> (std::numeric_limits<T>::quite_NaN ());
  }

  static constexpr auto One () -> Point4<T>
  {
    return Point4<T> (static_cast<T> (1.0));
  }

  static constexpr auto Zero () -> Point4<T>
  {
    return Point4<T> (static_cast<T> (0.0));
  }


  /* Point4<T> public data */
 public:
  union
  {
    struct { T x, y, z, w; };
    struct { T r, g, b, a; };
    T xyzw [4];
    T rgba [4];
  };

}; // class Point4
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Vector2
{
  /* Vector2<T> public constructors */
 public:
  Vector2<T> ()
  {};

  Vector2<T> (const T& t) :
      x (t),
      y (t)
  {}

  Vector2<T> (const T& t0, const T& t1) :
      x (t0),
      y (t1)
  {}


  /* Vector2<T> public destructor */
 public:
  virtual ~Vector2<T> () = default;


  /* Vector2<T> public operators */
 public:
  Vector2<T> (const Vector2<T>&  p) = default;
  Vector2<T> (      Vector2<T>&& p) = default;

  auto operator = (const Vector2<T>&  p) -> Vector2<T>& = default;
  auto operator = (      Vector2<T>&& p) -> Vector2<T>& = default;

  auto operator [] (std::size_t idx) const -> T
  {
    return xy [idx];
  }

  auto operator [] (std::size_t idx) -> T&
  {
    return xy [idx];
  }

  auto operator - () const -> Vector2<T>
  {
    return Vector2<T> (-x, -y);
  }

  auto operator += (const Vector2<T>& v) -> Vector2<T>&
  {
    x += v.x;
    y += v.y;
    return *this;
  }

  auto operator -= (const Vector2<T>& v) -> Vector2<T>&
  {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  auto operator *= (const T& t) -> Vector2<T>&
  {
    x *= static_cast<T> (t);
    y *= static_cast<T> (t);
    return *this;
  }

  auto operator /= (const T& t) -> Vector2<T>&
  {
    const T inv = static_cast<T> (1.0 / t);
    x *= static_cast<T> (inv);
    y *= static_cast<T> (inv);
    return *this;
  }


  /* Vector2<T> public methods */
 public:
  auto LengthSquared () const noexcept -> T
  {
    return x * x + y * y;
  }

  auto Length () const noexcept -> T
  {
    return std::sqrt ( LengthSquared() );
  }

  auto HasNaNs () const noexcept -> bool
  {
    return std::isnan (x) || std::isnan (y);
  }

  auto ToString () -> std::string
  {
    std::string str ("[");
    str += std::to_string (x) + ", " + std::to_string (y) + "]";
    return str;
  }


  /* Vector2<T> public constant values */
public:
  static constexpr auto Max () -> Vector2<T>
  {
    return Vector2<T> (std::numeric_limits<T>::max ());
  }

  static constexpr auto Min () -> Vector2<T>
  {
    return Vector2<T> (std::numeric_limits<T>::min ());
  }

  static constexpr auto Infinity () -> Vector2<T>
  {
    return Vector2<T> (std::numeric_limits<T>::infinity ());
  }

  static constexpr auto Lowest () -> Vector2<T>
  {
    return Vector2<T> (std::numeric_limits<T>::lowest ());
  }

  static constexpr auto NaN () -> Vector2<T>
  {
    return Vector2<T> (std::numeric_limits<T>::quite_NaN ());
  }

  static constexpr auto One () -> Vector2<T>
  {
    return Vector2<T> (static_cast<T> (1.0));
  }

  static constexpr auto Zero () -> Vector2<T>
  {
    return Vector2<T> (static_cast<T> (0.0));
  }


  /* Vector2<T> public data */
 public:
  union
  {
    struct { T x, y; };
    struct { T u, v; };
    struct { T s, t; };
    T xy [2];
    T uv [2];
    T st [2];
  };

}; // class Vector2
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Vector3
{
  /* Vector3<T> public constructors */
 public:
  Vector3<T> () :
      x (static_cast<T> (0)),
      y (static_cast<T> (0)),
      z (static_cast<T> (0))
  {};

  Vector3<T> (const T& t) :
      x (t),
      y (t),
      z (t)
  {}

  Vector3<T> (const T& t0, const T& t1, const T& t2) :
      x (t0),
      y (t1),
      z (t2)
  {}

  /* Vector3<T> public destructor */
 public:
  virtual ~Vector3<T> ()
  {};

  /* Vector3<T> public operators */
 public:
  Vector3<T> (const Vector3<T>&  p) = default;
  Vector3<T> (      Vector3<T>&& p) = default;

  auto operator = (const Vector3<T>&  p) -> Vector3<T>& = default;
  auto operator = (      Vector3<T>&& p) -> Vector3<T>& = default;

  operator Point3<T> () const
  {
    return Vector3<T> (x, y, z);
  }

  operator Normal3<T> () const
  {
    return Normal3<T> (x, y, z);
  }

  auto operator [] (std::size_t idx) const -> T
  {
    return xyz [idx];
  }

  auto operator [] (std::size_t idx) -> T&
  {
    return xyz [idx];
  }

  auto operator - () const -> Vector3<T>
  {
    return Vector3<T> (-x, -y, -z);
  }

  auto operator += (const Vector3<T>& v) -> Vector3<T>&
  {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  auto operator -= (const Vector3<T>& v) -> Vector3<T>&
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  auto operator *= (const T& t) -> Vector3<T>&
  {
    x *= static_cast<T> (t);
    y *= static_cast<T> (t);
    z *= static_cast<T> (t);
    return *this;
  }

  auto operator *= (const Vector3<T>& v) -> Vector3<T>&
  {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  auto operator /= (const T& t) -> Vector3<T>&
  {
    const T inv = static_cast<T> (1.0 / t);
    x *= static_cast<T> (inv);
    y *= static_cast<T> (inv);
    z *= static_cast<T> (inv);
    return *this;
  }


  /* Vector3<T> public constant values */
public:
  static constexpr auto Max () -> Vector3<T>
  {
    return Vector3<T> (std::numeric_limits<T>::max ());
  }

  static constexpr auto Min () -> Vector3<T>
  {
    return Vector3<T> (std::numeric_limits<T>::min ());
  }

  static constexpr auto Infinity () -> Vector3<T>
  {
    return Vector3<T> (std::numeric_limits<T>::infinity ());
  }

  static constexpr auto Lowest () -> Vector3<T>
  {
    return Vector3<T> (std::numeric_limits<T>::lowest ());
  }

  static constexpr auto NaN () -> Vector3<T>
  {
    return Vector3<T> (std::numeric_limits<T>::quite_NaN ());
  }

  static constexpr auto One () -> Vector3<T>
  {
    return Vector3<T> (static_cast<T> (1.0));
  }

  static constexpr auto Zero () -> Vector3<T>
  {
    return Vector3<T> (static_cast<T> (0.0));
  }


  /* Vector3<T> public methods */
 public:
  auto LengthSquared () const noexcept -> T
  {
    return x * x + y * y + z * z;
  }

  auto Length () const noexcept -> T
  {
    return std::sqrt ( LengthSquared() );
  }

  auto HasNaNs () const noexcept -> bool
  {
    return std::isnan (x) || std::isnan (y) || std::isnan (z);
  }

  auto ToString () -> std::string
  {
    std::string str ("[");
    str += std::to_string (x) + ", " + std::to_string (y) + ", " +
           std::to_string (z) + "]";
    return str;
  }


  /* Vector3<T> public data */
 public:
  union
  {
    struct { T x, y, z; };
    struct { T r, g, b; };
    struct { T s, t, u; };
    T xyz [3];
    T rgb [3];
    T stu [3];
  };

}; // class Vector3
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Vector4
{
  /* Vector4<T> public constructors */
 public:
  Vector4<T> () :
      x (static_cast<T> (0)),
      y (static_cast<T> (0)),
      z (static_cast<T> (0)),
      w (static_cast<T> (0))
  {};

  Vector4<T> (const T& t) :
      x (t),
      y (t),
      z (t),
      w (t)
  {}

  Vector4<T> (const T& t0, const T& t1, const T& t2, const T& t3) :
      x (t0),
      y (t1),
      z (t2),
      w (t3)
  {}

  /* Vector4<T> public destructor */
 public:
  virtual ~Vector4<T> ()
  {};

  /* Vector4<T> public operators */
 public:
  Vector4<T> (const Vector4<T>&  p) = default;
  Vector4<T> (      Vector4<T>&& p) = default;

  auto operator = (const Vector4<T>&  p) -> Vector4<T>& = default;
  auto operator = (      Vector4<T>&& p) -> Vector4<T>& = default;

  auto operator [] (std::size_t idx) const -> T
  {
    return xyzw [idx];
  }

  auto operator [] (std::size_t idx) -> T&
  {
    return xyzw [idx];
  }

  auto operator - () const -> Vector4<T>
  {
    return Vector4<T> (-x, -y, -z, -w);
  }

  auto operator += (const Vector4<T>& v) -> Vector4<T>&
  {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }

  auto operator -= (const Vector4<T>& v) -> Vector4<T>&
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }

  auto operator *= (const T& t) -> Vector4<T>&
  {
    x *= static_cast<T> (t);
    y *= static_cast<T> (t);
    z *= static_cast<T> (t);
    w *= static_cast<T> (t);
    return *this;
  }

  auto operator *= (const Vector4<T>& v) -> Vector4<T>
  {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }
  auto operator /= (const T& t) -> Vector4<T>&
  {
    const T& inv = static_cast<T> (1.0 / t);
    x *= static_cast<T> (inv);
    y *= static_cast<T> (inv);
    z *= static_cast<T> (inv);
    w *= static_cast<T> (inv);
    return *this;
  }


  /* Vector4<T> public constant values */
public:
  static constexpr auto Max () -> Vector4<T>
  {
    return Vector4<T> (std::numeric_limits<T>::max ());
  }

  static constexpr auto Min () -> Vector4<T>
  {
    return Vector4<T> (std::numeric_limits<T>::min ());
  }

  static constexpr auto Infinity () -> Vector4<T>
  {
    return Vector4<T> (std::numeric_limits<T>::infinity ());
  }

  static constexpr auto Lowest () -> Vector4<T>
  {
    return Vector4<T> (std::numeric_limits<T>::lowest ());
  }

  static constexpr auto NaN () -> Vector4<T>
  {
    return Vector4<T> (std::numeric_limits<T>::quite_NaN ());
  }

  static constexpr auto One () -> Vector4<T>
  {
    return Vector4<T> (static_cast<T> (1.0));
  }

  static constexpr auto Zero () -> Vector4<T>
  {
    return Vector4<T> (static_cast<T> (0.0));
  }


  /* Vector4<T> public methods */
 public:
  auto LengthSquared () const noexcept -> T
  {
    return x * x + y * y + z * z + w * w;
  }

  auto Length () const noexcept -> T
  {
    return std::sqrt ( LengthSquared() );
  }

  auto HasNaNs () const noexcept -> bool
  {
    return std::isnan (x) || std::isnan (y) || std::isnan (z) || std::isnan (w);
  }

  auto ToString () -> std::string
  {
    std::string str ("[");
    str += std::to_string (x) + ", " + std::to_string (y) + ", " +
           std::to_string (z) + ", " + std::to_string (w) + "]";
    return str;
  }


  /* Vector4<T> public data */
 public:
  union
  {
    struct { T x, y, z, w; };
    struct { T r, g, b, a; };
    T xyzw [4];
    T rgba [4];
  };

}; // class Vector4
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Normal3
{
  /* Normal3<T> public constructors */
 public:
  Normal3<T> () :
      x (static_cast<T> (0)),
      y (static_cast<T> (0)),
      z (static_cast<T> (0))
  {
    this->Normalize ();
  };

  Normal3<T> (const T& t) :
      x (t),
      y (t),
      z (t)
  {
    this->Normalize ();
  }

  Normal3<T> (const T& t0, const T& t1, const T& t2) :
      x (t0),
      y (t1),
      z (t2)
  {
    this->Normalize ();
  }


  /* Normal3<T> public destructor */
 public:
  virtual ~Normal3<T> () = default;


  /* Normal3<T> public operators */
 public:
  Normal3<T> (const Normal3<T>&  p) = default;
  Normal3<T> (      Normal3<T>&& p) = default;

  auto operator = (const Normal3<T>&  p) -> Normal3<T>& = default;
  auto operator = (      Normal3<T>&& p) -> Normal3<T>& = default;

  auto operator [] (std::size_t idx) const -> T
  {
    return xyz [idx];
  }

  auto operator [] (std::size_t idx) -> T&
  {
    return xyz [idx];
  }

  operator Vector3<T> () const
  {
    return Vector3<T> (x, y, z);
  }

  auto operator += (const Normal3<T>& v) -> Normal3<T>&
  {
    x += v.x;
    y += v.y;
    z += v.z;
    this->Normalize ();
    return *this;
  }

  auto operator -= (const Normal3<T>& v) -> Normal3<T>&
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    this->Normalize ();
    return *this;
  }

  auto operator *= (const T& t) -> Normal3<T>&
  {
    x *= static_cast<T> (t);
    y *= static_cast<T> (t);
    z *= static_cast<T> (t);
    this->Normalize ();
    return *this;
  }

  auto operator /= (const T& t) -> Normal3<T>&
  {
    const T inv = static_cast<T> (1.0 / t);
    x *= static_cast<T> (inv);
    y *= static_cast<T> (inv);
    z *= static_cast<T> (inv);
    this->Normalize ();
    return *this;
  }


  /* Normal3<T> public methods */
 public:
  auto LengthSquared () const noexcept -> T
  {
    return x * x + y * y + z * z;
  }

  auto Length () const noexcept -> T
  {
    return std::sqrt ( LengthSquared() );
  }

  auto HasNaNs () const noexcept -> bool
  {
    return std::isnan (x) || std::isnan (y) || std::isnan (z);
  }

  auto ToString () -> std::string
  {
    std::string str ("[");
    str += std::to_string (x) + ", " + std::to_string (y) + ", " +
           std::to_string (z) + ", ]";
    return str;
  }


  /* Normal3<T> private methods */
 private:
  auto Normalize () -> void
  {
    const T inv (1.0 / Length ());
    x *= inv;
    y *= inv;
    z *= inv;
  }


  /* Normal3<T> public data */
 public:
  union
  {
    struct { T x, y, z; };
    struct { T r, g, b; };
    struct { T s, t, u; };
    T xyz [3];
    T rgb [3];
    T stu [3];
  };

}; // class Normal3
/*
// ---------------------------------------------------------------------------
*/
class Ray
{
  /* Ray public constructors */
 public:
  Ray () :
      origin    (),
      direction ()
  {};

  Ray (const Point3f& p, const Vector3f& v) :
      origin    (p),
      direction (Normalize (v))
  {}

  /* Ray public destructor */
 public:
  virtual ~Ray ()
  {};

  /* Ray public operators */
 public:
  Ray (const Ray&  ray) = default;
  Ray (      Ray&& ray) = default;

  auto operator = (const Ray&  ray) -> Ray& = default;
  auto operator = (      Ray&& ray) -> Ray& = default;

  auto operator () (Float t) const -> Point3f
  {
    return origin + direction * t;
  }

  /* Ray public data */
 public:
  Point3f  origin;
  Vector3f direction;

}; // class Ray
/*
// ---------------------------------------------------------------------------
*/
class RayDifferential : public Ray
{
  /* RayDifferential constructors */
 public:
  RayDifferential () :
      origin_x    (),
      origin_y    (),
      direction_x (),
      direction_y (),
      has_differentials (false)
  {}

  RayDifferential (const Point3f& origin, const Vector3f& direction) :
      Ray (origin, direction)
  {}


  /* RayDifferential destructor */
 public:
  virtual ~RayDifferential ();


  /* RayDifferential public operators*/
 public:
  RayDifferential (const RayDifferential&  ray) = default;
  RayDifferential (      RayDifferential&& ray) = default;

  auto operator = (const RayDifferential&  ray) -> RayDifferential& = default;
  auto operator = (      RayDifferential&& ray) -> RayDifferential& = default;


  /* RayDifferential public methods */
 public:
  auto ComputeDifferentials (Float s) -> void
  {
    origin_x    = origin + (origin_x - origin) * s;
    origin_y    = origin + (origin_y - origin) * s;
    direction_x = direction + (direction_x - direction) * s;
    direction_y = direction + (direction_y - direction) * s;
  }


  /* RayDifferential public data */
 public:
  Point3f  origin_x, origin_y;
  Vector3f direction_x, direction_y;
  bool     has_differentials;

}; // class RayDifferential
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class BoundingBox2
{
  /* BoundingBox2 public constructors */
 public:
  BoundingBox2 ()
  {}

  BoundingBox2
  (
      const Point2<T>& min,
      const Point2<T>& max
  ) :
      min_ (min),
      max_ (max)
  {}

  /* BoundingBox2 public destructor */
 public:
  virtual ~BoundingBox2 () = default;


  /* BoundingBox2 public operators */
 public:
  BoundingBox2 (const BoundingBox2&  bounds) = default;
  BoundingBox2 (      BoundingBox2&& bounds) = default;

  auto operator = (const BoundingBox2&  bounds) -> BoundingBox2& = default;
  auto operator = (      BoundingBox2&& bounds) -> BoundingBox2& = default;

  auto operator [] (std::size_t idx) const -> Point2<T>
  {
    return idx == 0 ? min_ : max_;
  }

  auto operator [] (std::size_t idx) -> Point2<T>&
  {
    return idx == 0 ? min_ : max_;
  }


  /* Boundingbox2 public methods */
 public:
  auto Max () const -> Point2<T>
  {
    return max_;
  }

  auto Min () const -> Point2<T>
  {
    return min_;
  }

  auto SetMax(const Point2<T>& max) -> void
  {
    max_ = max;
  }

  auto SetMin(const Point2<T>& min) -> void
  {
    min_ = min;
  }

  // Each corner is arranged in the order of Morton order.
  auto Corner(std::size_t idx) const -> Point2<T>
  {
    return Point2<T> ((*this)[(idx & 1) ? 1 : 0].x,
                      (*this)[(idx & 2) ? 1 : 0].y);
  }

  auto Diagonal() const -> Vector2<T>
  {
    return max_ - min_;
  }

  auto SurfaceArea() const -> T
  {
    const Vector2<T> d = Diagonal();
    return d.x * d.y;
  }

  /* Boundingbox2 private data */
 private:
  Point2<T> min_;
  Point2<T> max_;

}; // class BoundingBox2
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class BoundingBox3
{
  /* BoundingBox3 public constructors */
 public:
  BoundingBox3 () :
      min_ (Point3<T>::Max    ()),
      max_ (Point3<T>::Lowest ())
  {}

  BoundingBox3
  (
      const Point3<T>& min,
      const Point3<T>& max
   ) :
      min_ (min),
      max_ (max)
  {}

  BoundingBox3 (std::initializer_list<Point3<T>> list) :
      min_ (Point3<T>::Max    ()),
      max_ (Point3<T>::Lowest ())
  {
    for (const auto& p : list)
    {
      min_ = Min (min_, p);
      max_ = Max (max_, p);
    }
  }

  /* BoundingBox3 public destructor */
 public:
  virtual ~BoundingBox3 () = default;


  /* BoundingBox3 public operators */
 public:
  BoundingBox3 (const BoundingBox3&  bounds) = default;
  BoundingBox3 (      BoundingBox3&& bounds) = default;

  auto operator = (const BoundingBox3&  bounds) -> BoundingBox3& = default;
  auto operator = (      BoundingBox3&& bounds) -> BoundingBox3& = default;

  auto operator [] (std::size_t idx) const -> Point3<T>
  {
    return idx == 0 ? min_ : max_;
  }

  auto operator [] (std::size_t idx) -> Point3<T>&
  {
    return idx == 0 ? min_ : max_;
  }


  /* Boundingbox3 public methods */
 public:
  auto GetMax () const -> Point3<T>
  {
    return max_;
  }

  auto GetMin () const -> Point3<T>
  {
    return min_;
  }

  auto SetMax(const Point3<T>& max) -> void
  {
    max_ = max;
  }

  auto SetMin(const Point3<T>& min) -> void
  {
    min_ = min;
  }

  auto Centroid () const -> Point3<T>
  {
    return (max_ + min_) * 0.5;
  }

  // Each corner is arranged in the order of Morton order.
  auto Corner(std::size_t idx) const -> Point3<T>
  {
    return Point3<T> ((*this)[(idx & 1) ? 1 : 0].x,
                      (*this)[(idx & 2) ? 1 : 0].y,
                      (*this)[(idx & 4) ? 1 : 0].z);
  }

  auto Diagonal() const -> Vector3<T>
  {
    return max_ - min_;
  }

  auto SurfaceArea () const -> T
  {
    const Vector3<T> d = Diagonal ();
    return 2.0 * (d.x * d.y + d.y * d.z + d.z * d.x);
  }

  auto Volume () const -> T
  {
    const Vector3<T> d = Diagonal();
    return d.x * d.y * d.z;
  }

  auto MaxExtent () const -> int
  {
    const Vector3<T> v = Diagonal();
    if (v.x > v.y && v.x > v.z) { return 0; }
    if (v.y > v.z) { return 1; }
    return 2;
  }

  auto IsIntersect (const Ray& ray) const -> bool
  {
    T t_near = std::numeric_limits<T>::min ();
    T t_far  = std::numeric_limits<T>::max ();
    for (int axis = 0; axis < 3; ++axis)
    {
      // Ray-Slab intersection test
      T inv_ray_dir = 1.0 / ray.direction[axis];
      T t0 = (min_[axis] - ray.origin[axis]) * inv_ray_dir;
      T t1 = (max_[axis] - ray.origin[axis]) * inv_ray_dir;

      if (t0 > t1)
      {
        std::swap (t0, t1);
      }

      // Update
      t_near = t0 < t_near ? t0 : t_near;
      t_far  = t1 > t_far  ? t1 : t_far;

      // Intersection check
      if (t_far <= t_near)
      {
        return false;
      }
    }
    return true;
  }


  /* Boundingbox3 private data */
 private:
  Point3<T> min_;
  Point3<T> max_;

}; // class BoundingBox3
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
class Matrix4x4
{
  /* Matrix public constructor */
public:
  Matrix4x4 ()
  {
    this->ToIdentity();
  };

  Matrix4x4 (T m00, T m01, T m02, T m03,
             T m10, T m11, T m12, T m13,
             T m20, T m21, T m22, T m23,
             T m30, T m31, T m32, T m33) :
      matrix ({m00, m10, m20, m30,
               m01, m11, m21, m31,
               m02, m12, m22, m32,
               m03, m13, m23, m33})
  {}

  Matrix4x4 (const std::array<std::array<Float, 4>, 4>& a) :
    matrix ({a[0][0], a[0][1], a[0][2], a[0][3],
             a[1][0], a[1][1], a[1][2], a[1][3],
             a[2][0], a[2][1], a[2][2], a[2][3],
             a[3][0], a[3][1], a[3][2], a[3][3]})
  {}

  Matrix4x4 (const std::array<Float, 16>& a) :
    matrix (a)
  {}


  /* Matrix public destructor */
public:
  virtual ~Matrix4x4 () = default;

  Matrix4x4 (const Matrix4x4&  m) = default;
  Matrix4x4 (      Matrix4x4&& m) = default;


  /* Matrix operators */
 public:
  auto operator = (const Matrix4x4&  m) -> Matrix4x4& = default;
  auto operator = (      Matrix4x4&& m) -> Matrix4x4& = default;


  inline auto operator () (size_t row, size_t col) const noexcept -> T
  {
    return matrix[col * 4 + row];
  }

  inline auto operator () (size_t row, size_t col) noexcept -> T&
  {
    return matrix[col * 4 + row];
  }

  auto operator += (const Matrix4x4& m) -> Matrix4x4&
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)(i, j) += m (i, j);
      }
    }
    return (*this);
  }

  auto operator -= (const Matrix4x4& m) -> Matrix4x4&
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)(i, j) -= m(i, j);
      }
    }
    return (*this);
  }

  auto operator *= (const Matrix4x4& m) -> Matrix4x4&
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)(i, j) = (*this)(i, 0) * m(0, j) + (*this)(i, 1) * m(i, 1) +
                        (*this)(i, 2) * m(2, j) + (*this)(i, 3) * m(i, 3);
      }
    }
    return *this;
  }

  template <typename U>
  auto operator *= (U t) -> Matrix4x4&
  {
    const U tt (static_cast<T> (t));
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)(i, j) *= tt;
      }
    }
    return *this;
  }

  /* Matrix4x4 public methods */
 public:
  auto ToIdentity () -> void
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        if (i == j) { (*this)(i, j) = 1; continue; }
        (*this)(i, j) = 0;
      }
    }
  }

  auto HasNaNs () -> bool
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        if ( IsNaN( (*this)(i, j) ) ) { return true; }
      }
    }
    return false;
  }


  /* Matrix4x4 public data */
 public:
  union
  {
    std::array<T, 16> matrix;
    // Column-major
    struct
    {
      union
      {
        std::array<T, 4> col0;
        T m00, m10, m20, m30;
      };
      union
      {
        std::array<T, 4> col1;
        T m01, m11, m21, m31;
      };
      union
      {
        std::array<T, 4> col2;
        T m02, m12, m22, m32;
      };
      union
      {
        std::array<T, 4> col3;
        T m03, m13, m23, m33;
      };
    };
  };

}; // class Matrix4x4
/*
// ---------------------------------------------------------------------------
// Point2
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Point2<T>& p0, const Point2<T>& p1) -> bool
{
  return !(p0.x < p1.x) && !(p0.y < p1.y) &&
         !(p0.x > p1.x) && !(p0.y > p1.y);
}
/*
// ---------------------------------------------------------------------------
*/
template<typename T>
auto operator != (const Point2<T>& p0, const Point2<T>& p1) -> bool
{
  return !(p0 == p1);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>
{
  return Point2<T> (p0.x + p1.x, p0.y + p1.y);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator - (const Point2<T>& p0, const Point2<T>& p1) -> Vector2<T>
{
  return Vector2<T> (p0.x - p1.x, p0.y - p1.y);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator * (const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>
{
  return Point2<T> (p0.x * p1.x, p0.y * p1.y);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (const Point2<T>& p, U t) -> Point2<T>
{
  const T tt (static_cast<T> (t));
  return Point2<T> (p.x * tt, p.y * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (U t, const Point2<T>& p) -> Point2<T>
{
  const T tt (static_cast<T> (t));
  return Point2<T> (p.x * tt, p.y * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator /  (const Point2<T>& p, U t) -> Point2<T>
{
  const T inv = static_cast<T> (1.0 / t);
  return Point2<T> (p.x * inv, p.y * inv);
}
/*
// ---------------------------------------------------------------------------
// Point3
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Point3<T>& p0, const Point3<T>& p1) -> bool
{
  return !(p0.x < p1.x) && !(p0.y < p1.y) && !(p0.z < p1.z) &&
         !(p0.x > p1.x) && !(p0.y > p1.y) && !(p0.z > p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator != (const Point3<T>& p0, const Point3<T>& p1) -> bool
{
  return !(p0 == p1);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator +  (const Point3<T>& p0, const Point3<T>& p1) -> Point3<T>
{
  return Point3<T> (p0.x + p1.x, p0.y + p1.y, p0.z + p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator - (const Point3<T>& p0, const Point3<T>& p1) -> Vector3<T>
{
  return Vector3<T> (p0.x - p1.x, p0.y - p1.y, p0.z - p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator * (const Point3<T>& p0, const Point3<T>& p1) -> Point3<T>
{
  return Point3<T> (p0.x * p1.x, p0.y * p1.y, p0.z * p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (const Point3<T>& p, U t) -> Point3<T>
{
  const T tt (static_cast<T> (t));
  return Point3<T> (p.x * tt, p.y * tt, p.z * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (U t, const Point3<T>& p) -> Point3<T>
{
  const T tt (static_cast<U> (t));
  return Point3<T> (p.x * tt, p.y * tt, p.z * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator /  (const Point3<T>& p, U t) -> Point3<T>
{
  const T inv (static_cast<T> (1.0 / t));
  return Point3<T> (p.x * inv, p.y * inv, p.z * inv);
}
/*
// ---------------------------------------------------------------------------
// Point4
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Point4<T>& p0, const Point4<T>& p1) -> bool
{
  return !(p0.x < p1.x) && !(p0.y < p1.y) && !(p0.z < p1.z) && !(p0.w < p1.w) &&
         !(p0.x > p1.x) && !(p0.y > p1.y) && !(p0.z > p1.z) && !(p0.w > p1.w);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator != (const Point4<T>& p0, const Point4<T>& p1) -> bool
{
  return !(p0 == p1);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>
{
  return Point4<T> (p0.x + p1.x, p0.y + p1.y, p0.z + p1.z, p0.w + p1.w);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator - (const Point4<T>& p0, const Point4<T>& p1) -> Vector4<T>
{
  return Vector4<T> (p0.x - p1.x, p0.y - p1.y, p0.z - p1.z, p0.w - p1.w);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator * (const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>
{
  return Point4<T> (p0.x * p1.x, p0.y * p1.y, p0.z * p1.z, p0.w * p1.w);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (const Point4<T>& p, U t) -> Point4<T>
{
  const T tt (static_cast<T> (t));
  return Point4<T> (p.x * tt, p.y * tt, p.z * tt, p.w * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator *  (const T& t, const Point4<T>& p) -> Point4<T>
{
  const T tt (static_cast<T> (t));
  return Point4<T> (p.x * tt, p.y * tt, p.z * tt, p.w * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator /  (const Point4<T>& p, U t) -> Point4<T>
{
  const T inv = static_cast<T> (1.0 / t);
  return Point4<T> (p.x * inv, p.y * inv, p.z * inv, p.w * inv);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator / (const Vector4<T>& v0, const Vector4<T>& v1) -> Vector4<T>
{
  return Vector4<T> (v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w);
}
/*
// ---------------------------------------------------------------------------
// Vector2
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Vector2<T>& p0, const Vector2<T>& p1) -> bool
{
  return !(p0.x < p1.x) && !(p0.y < p1.y) &&
         !(p0.x > p1.x) && !(p0.y > p1.y);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator != (const Vector2<T>& p0, const Vector2<T>& p1) -> bool
{
  return !(p0 == p1);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator +  (const Vector2<T>& p0, const Vector2<T>& p1) -> Vector2<T>
{
  return Vector2<T> (p0.x + p1.x, p0.y + p1.y);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator -  (const Vector2<T>& p0, const Vector2<T>& p1) -> Vector2<T>
{
  return Vector2<T> (p0.x - p1.x, p0.y - p1.y);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator *  (const Vector2<T>& v0, const Vector2<T>& v1) -> Vector2<T>
{
  return Vector2<T> (v0.x * v1.x, v0.y * v1.y);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator *  (const Vector2<T>& p, U t) -> Vector2<T>
{
  const T tt (static_cast<T> (t));
  return Vector2<T> (p.x * tt, p.y * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator *  (U t, const Vector2<T>& p) -> Vector2<T>
{
  const T tt (static_cast<T> (t));
  return Vector2<T> (p.x * tt, p.y * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator /  (const Vector2<T>& p, U t) -> Vector2<T>
{
  const T inv = static_cast<T> (1.0 / t);
  return Vector2<T> (p.x * inv, p.y * inv);
}
/*
// ---------------------------------------------------------------------------
// Vector3
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Vector3<T>& p0, const Vector3<T>& p1) -> bool
{
  return !(p0.x < p1.x) && !(p0.y < p1.y) && !(p0.z < p1.z) &&
         !(p0.x > p1.x) && !(p0.y > p1.y) && !(p0.z > p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator != (const Vector3<T>& p0, const Vector3<T>& p1) -> bool
{
  return !(p0 == p1);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Vector3<T>& p0, const Vector3<T>& p1) -> Vector3<T>
{
  return Vector3<T> (p0.x + p1.x, p0.y + p1.y, p0.z + p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Normal3<T>& n, const Vector3<T>& v) -> Vector3<T>
{
  return Vector3<T> (n.x + v.x, n.y + v.y, n.z + v.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Vector3<T>& v, const Normal3<T>& n) -> Vector3<T>
{
  return Vector3<T> (n.x + v.x, n.y + v.y, n.z + v.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator - (const Vector3<T>& p0, const Vector3<T>& p1) -> Vector3<T>
{
  return Vector3<T> (p0.x - p1.x, p0.y - p1.y, p0.z - p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator * (const Vector3<T>& v0, const Vector3<T>& v1) -> Vector3<T>
{
  return Vector3<T> (v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator *  (const Vector3<T>& p, U t) -> Vector3<T>
{
  const T tt (static_cast<T> (t));
  return Vector3<T> (p.x * tt, p.y * tt, p.z * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator *  (U t, const Vector3<T>& p) -> Vector3<T>
{
  const T tt (static_cast<T> (t));
  return Vector3<T> (p.x * tt, p.y * tt, p.z * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator / (const Vector3<T>& p, U t) -> Vector3<T>
{
  const T inv (static_cast<T> (1.0 / t));
  return Vector3<T> (p.x * inv, p.y * inv, p.z * inv);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator / (const Vector3<T>& v0, const Vector3<T>& v1) -> Vector3<T>
{
  return Vector3<T> (v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}
/*
// ---------------------------------------------------------------------------
// Vector4
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Vector4<T>& p0, const Vector4<T>& p1) -> bool
{
  return !(p0.x < p1.x) && !(p0.y < p1.y) && !(p0.z < p1.z) && !(p0.w < p1.w) &&
         !(p0.x > p1.x) && !(p0.y > p1.y) && !(p0.z > p1.z) && !(p0.w > p1.w);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator != (const Vector4<T>& p0, const Vector4<T>& p1) -> bool
{
  return !(p0 == p1);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Vector4<T>& p0, const Vector4<T>& p1) -> Vector4<T>
{
  return Vector4<T> (p0.x + p1.x, p0.y + p1.y, p0.z + p1.z, p0.w + p1.w);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator - (const Vector4<T>& p0, const Vector4<T>& p1) -> Vector4<T>
{
  return Vector4<T> (p0.x - p1.x, p0.y - p1.y, p0.z - p1.z, p0.w - p1.w);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator * (const Vector4<T>& v0, const Vector4<T>& v1) -> Vector4<T>
{
  return Vector4<T> (v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (const Vector4<T>& p, U t) -> Vector4<T>
{
  const T tt (static_cast<T> (t));
  return Vector4<T> (p.x * tt, p.y * tt, p.z * tt, p.w * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (U t, const Vector4<T>& p) -> Vector4<T>
{
  const T tt (static_cast<T> (t));
  return Vector4<T> (p.x * tt, p.y * tt, p.z * tt, p.w * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator /  (const Vector4<T>& p, U t) -> Vector4<T>
{
  const T inv = static_cast<T> (1.0 / t);
  return Vector4<T> (p.x * inv, p.y * inv, p.z * inv, p.w * inv);
}
/*
// ---------------------------------------------------------------------------
// Normal3
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Normal3<T>& p0, const Normal3<T>& p1) -> bool
{
  return !(p0.x < p1.x) && !(p0.y < p1.y) && !(p0.z < p1.z) &&
         !(p0.x > p1.x) && !(p0.y > p1.y) && !(p0.z > p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator != (const Normal3<T>& p0, const Normal3<T>& p1) -> bool
{
  return !(p0 == p1);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Normal3<T>& p0, const Normal3<T>& p1) -> Normal3<T>
{
  return Normal3<T> (p0.x + p1.x, p0.y + p1.y, p0.z + p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator - (const Normal3<T>& p0, const Normal3<T>& p1) -> Normal3<T>
{
  return Normal3<T> (p0.x - p1.x, p0.y - p1.y, p0.z - p1.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (const Normal3<T>& n, U t) -> Normal3<T>
{
  const T tt (static_cast<T> (t));
  return Normal3<T> (n.x * tt, n.y * tt, n.z * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (U t, const Normal3<T>& n) -> Normal3<T>
{
  const T tt (static_cast<T> (t));
  return Normal3<T> (n.x * tt, n.y * tt, n.z * tt);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator /  (const Normal3<T>& p, U t) -> Normal3<T>
{
  const T inv = static_cast<T> (1.0 / t);
  return Normal3<T> (p.x * inv, p.y * inv, p.z * inv);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Point2<T>& p, const Vector2<T>& v) -> Point2<T>
{
  return Point2<T> (p.x + v.x, p.y + v.y);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Vector2<T>& v, const  Point2<T>& p) -> Point2<T>
{
  return Point2<T> (p.x + v.x, p.y + v.y);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Point3<T>& p, const Vector3<T>& v) -> Point3<T>
{
  return Point3<T> (p.x + v.x, p.y + v.y, p.z + v.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Vector3<T>& v, const  Point3<T>& p) -> Point3<T>
{
  return Point3<T> (p.x + v.x, p.y + v.y, p.z + v.z);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Point4<T>& p, const Vector4<T>& v) -> Point4<T>
{
  return Point4<T> (p.x + v.x, p.y + v.y, p.z + v.z, p.w + v.w);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Vector4<T>& v, const  Point4<T>& p) -> Point4<T>
{
  return Point4<T> (p.x + v.x, p.y + v.y, p.z + v.z, p.w + v.w);
}
/*
// ---------------------------------------------------------------------------
// Matrix4x4
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator == (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1) -> bool
{
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0 ; j < 4; ++j)
    {
      if (m0 (i, j) != m1 (i, j))
      {
        return false;
      }
    }
  }
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator != (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1) -> bool
{
  return !(m0 == m1);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator + (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1)
-> Matrix4x4<T>
{
  return Matrix4x4<T> (m0 (0, 0) + m1 (0, 0), m0 (0, 1) + m1 (0, 1),
                       m0 (0, 2) + m1 (0, 2), m0 (0, 3) + m1 (0, 2),
                       m0 (1, 0) + m1 (1, 0), m0 (1, 1) + m1 (1, 1),
                       m0 (1, 2) + m1 (1, 2), m0 (1, 3) + m1 (1, 2),
                       m0 (2, 0) + m1 (2, 0), m0 (2, 1) + m1 (2, 1),
                       m0 (2, 2) + m1 (2, 2), m0 (2, 3) + m1 (2, 2),
                       m0 (3, 0) + m1 (3, 0), m0 (3, 1) + m1 (3, 1),
                       m0 (3, 2) + m1 (3, 2), m0 (3, 3) + m1 (3, 2));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator - (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1)
-> Matrix4x4<T>
{
  return Matrix4x4<T> (m0 (0, 0) - m1 (0, 0), m0 (0, 1) - m1 (0, 1),
                       m0 (0, 2) - m1 (0, 2), m0 (0, 3) - m1 (0, 2),
                       m0 (1, 0) - m1 (1, 0), m0 (1, 1) - m1 (1, 1),
                       m0 (1, 2) - m1 (1, 2), m0 (1, 3) - m1 (1, 2),
                       m0 (2, 0) - m1 (2, 0), m0 (2, 1) - m1 (2, 1),
                       m0 (2, 2) - m1 (2, 2), m0 (2, 3) - m1 (2, 2),
                       m0 (3, 0) - m1 (3, 0), m0 (3, 1) - m1 (3, 1),
                       m0 (3, 2) - m1 (3, 2), m0 (3, 3) - m1 (3, 2));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator * (const Matrix4x4<T>& m0, const Matrix4x4<T>& m1)
-> Matrix4x4<T>
{
  Matrix4x4<T> ret;
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
      {
        ret (i, j) = m0 (i, 0) * m1 (0, j) +
                     m0 (i, 1) * m1 (i, 1) +
                     m0 (i, 2) * m1 (2, j) +
                     m0 (i, 3) * m1 (i, 3);
      }
  }
  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator * (const Matrix4x4<T>& m, const Point4<T>& p) -> Point4<T>
{
  Point4<T> ret;
  for (int row = 0; row < 4; ++row)
  {
    for (int col = 0; col < 4; ++col)
    {
      ret[row] += (m (row, col)) * p[row];
    }
  }
  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator * (const Matrix4x4<T>& m, const Vector4<T>& v) -> Vector4<T>
{
  Vector4<T> ret;
  for (int row = 0; row < 4; ++row)
  {
    for (int col = 0; col < 4; ++col)
    {
      ret[row] += (m (row, col)) * v[row];
    }
  }
  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename U>
auto operator * (const Matrix4x4<T>& m, U t) -> Matrix4x4<T>
{
  Matrix4x4<T> ret (m);
  const T tt (static_cast<T> (t));
  for (int row = 0; row < 4; ++row)
  {
    for (int col = 0; col < 4; ++col)
    {
      m (row, col) *= tt;
    }
  }
  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const Matrix4x4<T>& m) -> std::ostream&
{
  os << "[" << m (0, 0) << ", " << m (0, 1) << ", " << m (0, 2) << ", " << m (0, 3) << "]\n";
  os << "[" << m (1, 0) << ", " << m (1, 1) << ", " << m (1, 2) << ", " << m (1, 3) << "]\n";
  os << "[" << m (2, 0) << ", " << m (2, 1) << ", " << m (2, 2) << ", " << m (2, 3) << "]\n";
  os << "[" << m (3, 0) << ", " << m (3, 1) << ", " << m (3, 2) << ", " << m (3, 3) << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Distance (const Point2<T>& p0, const Point2<T>& p1) -> T
{
  return (p0 - p1).Length ();
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Distance (const Point3<T>& p0, const Point3<T>& p1) -> T
{
  return (p0 - p1).Length ();
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto OrthoNormalBasis
(
    const Normal3<T>& normal,
          Vector3<T>* tangent,
          Vector3<T>* binormal
) -> void
{
  if (std::abs (normal.x) > std::abs (normal.y))
  {
    *tangent = Vector3<T>(-normal.z, 0, normal.x) /
               std::sqrt(normal.x * normal.x + normal.z * normal.z);
  }
  else
  {
    *tangent = Vector3<T>(0, normal.z, -normal.y) /
               std::sqrt(normal.y * normal.y + normal.z * normal.z);
  }
  *binormal = Cross(normal, *tangent);
  return ;

  if (std::abs (normal.x) > kEpsilon)
  {
    *tangent = Normalize (Cross (Vector3f (1.0, 0.0, 0.0), normal));
  }
  else
  {
    *tangent = Normalize (Cross (Vector3f (0.0, 1.0, 0.0), normal));
  }
  *binormal = Normalize (Cross (normal, *tangent));
  *tangent  += Vector3f::Zero ();
  *binormal += Vector3f::Zero ();
  return ;

  /*
  // Building an Orthonormal Basis from a 3D Unit Vector Without Normalization
  if (normal.z < -0.9999999f) // Handle the singularity
  {
    *tangent  = Vector3f ( 0.0f ,-1.0f ,0.0f);
    *binormal = Vector3f (-1.0f , 0.0f ,0.0f);
    *binormal = Cross (normal, *tangent);
    return ;
  }
  const Float a = 1.0f / (1.0f + normal.z);
  const Float b = -normal.x * normal.y * a ;
  *tangent  = Vector3f (1.0f - normal.x * normal.x * a, b, -normal.x);
  *binormal = Vector3f (b, 1.0f - normal.y * normal.y * a, -normal.y);
  *binormal = Cross (normal, *tangent);

  *tangent  += Vector3f::Zero ();
  *binormal += Vector3f::Zero ();
  return ;
  */

  // Building an Orthonormal Basis, Revisited
  if(normal.z < 0.0)
  {
    const T a (1.0f / (1.0f - normal.z));
    const T b (normal.x * normal.y * a);
    *tangent  =
        Normalize (Vector3<T> (1.0f - normal.x * normal.x * a, -b, normal.x));
    *binormal =
        Normalize (Vector3<T> (b, normal.y * normal.y * a - 1.0f, -normal.y));
  }
  else
  {
    const T a = 1.0f / (1.0f + normal.z);
    const T b = -normal.x * normal.y * a;
    *tangent  = Vector3<T> (1.0f - normal.x * normal.x * a, b, -normal.x);
    *binormal = Vector3<T> (b, 1.0f - normal.y * normal.y * a, -normal.y);
  }
  *tangent  += Vector3f::Zero ();
  *binormal += Vector3f::Zero ();
  return ;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Min (const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>
{
  return Point2<T> (std::min (p0.x, p1.x),
                    std::min (p0.y, p1.y));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Min (const Point3<T>& p0, const Point3<T>& p1) -> Point3<T>
{
  return Point3<T> (std::min (p0.x, p1.x),
                    std::min (p0.y, p1.y),
                    std::min (p0.z, p1.z));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Min (const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>
{
  return Point4<T> (std::min (p0.x, p1.x),
                    std::min (p0.y, p1.y),
                    std::min (p0.z, p1.z),
                    std::min (p0.w, p1.w));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Max (const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>
{
  return Point2<T> (std::max (p0.x, p1.x),
                    std::max (p0.y, p1.y));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Max (const Point3<T>& p0, const Point3<T>& p1) -> Point3<T>
{
  return Point3<T> (std::max (p0.x, p1.x),
                    std::max (p0.y, p1.y),
                    std::max (p0.z, p1.z));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Max (const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>
{
  return Point4<T> (std::max (p0.x, p1.x),
                    std::max (p0.y, p1.y),
                    std::max (p0.z, p1.z),
                    std::max (p0.w, p1.w));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Vector2<T>& v0, const Vector2<T>& v1) -> T
{
  return v0.x * v1.x + v0.y * v1.y;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const  Point2<T>& p, const Vector2<T>& v) -> T
{
  return p.x * v.x + p.y * v.y;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Vector2<T>& v, const  Point2<T>& p) -> T
{
  return p.x * v.x + p.y * v.y;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const  Point2<T>& p0, const  Point2<T>& p1) -> T
{
  return p0.x * p1.x + p1.y * p1.y;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Vector3<T>& v0, const Vector3<T>& v1) -> T
{
  return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const  Point3<T>& p, const Vector3<T>& v) -> T
{
  return p.x * v.x + p.y * v.y + p.z * v.z;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Vector3<T>& v, const  Point3<T>& p) -> T
{
  return p.x * v.x + p.y * v.y + p.z * v.z;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Normal3<T>& n0, const Normal3<T>& n1) -> T
{
  return n0.x * n1.x + n0.y * n1.y + n0.z * n1.z;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Vector3<T>& v, const Normal3<T>& n) -> T
{
  return v.x * n.x + v.y * n.y + v.z * n.z;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Normal3<T>& n, const Vector3<T>& v) -> T
{
  return v.x * n.x + v.y * n.y + v.z * n.z;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Point3<T>& p, const Normal3<T>& n) -> T
{
  return p.x * n.x + p.y * n.y + p.z * n.z;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Dot (const Normal3<T>& n, const Point3<T>& p) -> T
{
  return p.x * n.x + p.y * n.y + p.z * n.z;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Vector2<T>& v0, const Vector2<T>& v1) -> T
{
  return v0.x * v1.y - v0.y * v1.x;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Point2<T>& p, const Vector2<T>& v) -> T
{
  return p.x * v.y - p.y * v.x;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Vector2<T>& v, const Point2<T>& p) -> T
{
  return v.x * p.y - v.y * p.x;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Vector3<T>& v0, const Vector3<T>& v1) -> Vector3<T>
{
  return Vector3<T> (v0.y * v1.z - v0.z * v1.y,
                     v0.z * v1.x - v0.x * v1.z,
                     v0.x * v1.y - v0.y * v1.x);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Point3<T>& p, const Vector3<T>& v) -> Vector3<T>
{
  return Vector3<T> (p.y * v.z - p.z * v.y,
                     p.z * v.x - p.x * v.z,
                     p.x * v.y - p.y * v.x);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Vector3<T>& v, const Point3<T>& p) -> Vector3<T>
{
  return Vector3<T> (v.y * p.z - v.z * p.y,
                     v.z * p.x - v.x * p.z,
                     v.x * p.y - v.y * p.x);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Normal3<T>& n0, const Normal3<T>& n1) -> Normal3<T>
{
  return Normal3<T> (n0.y * n1.z - n0.z * n1.y,
                     n0.z * n1.x - n0.x * n1.z,
                     n0.x * n1.y - n0.y * n1.x);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Vector3<T>& v, const Normal3<T>& n) -> Vector3<T>
{
  return Vector3<T> (v.y * n.z - v.z * n.y,
                     v.z * n.x - v.x * n.z,
                     v.x * n.y - v.y * n.x);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Normal3<T>& n, const Vector3<T>& v) -> Vector3<T>
{
  return Vector3<T> (n.y * v.z - n.z * v.y,
                     n.z * v.x - n.x * v.z,
                     n.x * v.y - n.y * v.x);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Point3<T>& p, const Normal3<T>& n) -> Vector3<T>
{
  return Vector3<T> (p.y * n.z - p.z * n.y,
                     p.z * n.x - p.x * n.z,
                     p.x * n.y - p.y * n.x);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Cross (const Normal3<T>& n, const Point3<T>& p) -> Vector3<T>
{
  return Vector3<T> (n.y * p.z - n.z * p.y,
                     n.z * p.x - n.x * p.z,
                     n.x * p.y - n.y * p.x);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Normalize (const Vector2<T>& v) -> Vector2<T>
{
  return v / v.Length ();
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Normalize (const Vector3<T>& v) -> Vector3<T>
{
  return v / v.Length ();
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Normalize (const Vector4<T>& v) -> Vector4<T>
{
  return v / v.Length ();
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Sqrt (const Vector2<T>& v) -> Vector2<T>
{
  return Vector2<T> (std::sqrt (v.x), std::sqrt (v.y));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Sqrt (const Vector3<T>& v) -> Vector3<T>
{
  return Vector3<T> (std::sqrt (v.x), std::sqrt (v.y), std::sqrt (v.z));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Sqrt (const Vector4<T>& v) -> Vector4<T>
{
  return Vector4<T> (std::sqrt (v.x), std::sqrt (v.y), std::sqrt (v.z), std::sqrt (v.w));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Union (const BoundingBox2<T>& bounds0, const BoundingBox2<T>& bounds1)
-> BoundingBox2<T>
{
  return BoundingBox2<T> (Min (bounds0.GetMin (), bounds1.GetMin ()),
                          Max (bounds0.GetMax (), bounds1.GetMax ()));
}

template <typename T>
auto Union (const BoundingBox3<T>& bounds0, const BoundingBox3<T>& bounds1)
-> BoundingBox3<T>
{
  return BoundingBox3<T> (Min (bounds0.GetMin (), bounds1.GetMin ()),
                          Max (bounds0.GetMax (), bounds1.GetMax ()));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const Point2<T>& p) -> std::ostream&
{
  os << "[" << p.x << ", " << p.y << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const Point3<T>& p) -> std::ostream&
{
  os << "[" << p.x << ", " << p.y << ", " << p.z << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const Point4<T>& p) -> std::ostream&
{
  os << "[" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const Vector2<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const Vector3<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const Vector4<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const Normal3<T>& n) -> std::ostream&
{
  os << "[" << n.x << ", " << n.y << ", " << n.z << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const BoundingBox2<T>& bounds) -> std::ostream&
{
  os << "[min: " << bounds.GetMin () << ", max: " << bounds.GetMax () << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator << (std::ostream& os, const BoundingBox3<T>& bounds) -> std::ostream&
{
  os << "[min: " << bounds.GetMin () << ", max: " << bounds.GetMax () << "]";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto SphericalTheta (const Vector3<T>& v) -> T
{
  return std::acos (Clamp (v.z, -1.0, 1.0));
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto SphericalPhi   (const Vector3<T>& v) -> T
{
  const Float p = std::atan2 (v.y, v.x);
  return (p < 0) ? (p + 2 * kPi) : p;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto operator * (const Matrix4x4<T>& m, const Vector3<T>& v) -> Vector3<T>
{
  return Vector3f (m.m00 * v.x + m.m01 * v.y + m.m02 * v.z,
                   m.m10 * v.x + m.m11 * v.y + m.m12 * v.z,
                   m.m20 * v.x + m.m21 * v.y + m.m22 * v.z);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto SphericalToCartesian (Float sin_theta, Float cos_theta, Float phi)
-> Vector3f
{
  return Vector3f (sin_theta * std::cos (phi),
                   sin_theta * std::sin (phi),
                   cos_theta);
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
inline auto Inverse (const Matrix4x4<T>& m) -> Matrix4x4<T>
{
  Float buf;
  Matrix4x4<T> tmp (m);
  Matrix4x4<T> ret;
  for(int i = 0; i < 4; ++i)
  {
    buf = 1.0 / tmp (i, i);
    if (std::isnan (buf))
    {
      // TODO: error
    }
    for(int j = 0; j < 4; ++j)
    {
      tmp (i, j) *= buf;
      ret (i, j) *= buf;
    }
    for(int j = 0; j < 4; ++j)
    {
      if(i != j)
      {
        buf = tmp (j, i);
        for(int k = 0; k < 4; ++k)
        {
          tmp (j, k) -= tmp (i, k) * buf;
          ret (j, k) -= ret (i, k) * buf;
        }
      }
    }
  }
  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _GEMOETRY_H_
