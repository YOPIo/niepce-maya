#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
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
// Forward decralations
// ---------------------------------------------------------------------------
*/
class Transform;
class Transformable;
/*
// ---------------------------------------------------------------------------
*/
class Transform
{
  /* Transform public constructors */
 public:
  Transform ();

  Transform (Float m00, Float m01, Float m02, Float m03,
             Float m10, Float m11, Float m12, Float m13,
             Float m20, Float m21, Float m22, Float m23,
             Float m30, Float m31, Float m32, Float m33);

  Transform (const Matrix4x4f& m);


  /* Transform private destructor */
  virtual ~Transform () = default;


  /* Transform public operators */
 public:
  Transform (const Transform&  t) = default;
  Transform (      Transform&& t) = default;

  auto operator = (const Transform&  t) -> Transform& = default;
  auto operator = (      Transform&& t) -> Transform& = default;

  auto operator == (const Transform& t) const -> bool;
  auto operator != (const Transform& t) const -> bool;

  auto operator () (size_t row, size_t col) const noexcept -> Float;
  auto operator () (size_t row, size_t col)       noexcept -> Float&;


  /* Transform public methods */
 public:
  auto At (size_t row, size_t col) const -> Float;
  auto At (size_t row, size_t col)       -> Float&;

  auto GetMatrix    () const -> Matrix4x4f;
  auto GetInvMatrix () const -> Matrix4x4f;

  auto Row     (size_t idx) const -> std::array<Float, 4>;
  auto SetRow  (size_t idx, std::array<Float, 4>& row) -> void;
  auto SwapRow (size_t row0, size_t row1) -> void;

  auto Column     (size_t idx) const -> std::array<Float, 4>;
  auto SetColumn  (size_t idx, std::array<Float, 4>& col) -> void;
  auto SwapColumn (size_t col0, size_t col1) -> void;

  auto IsIdentity () const -> bool;
  auto ToIdentity ()       -> void;


  /* Transform public static methods */
public:
  static auto Identity () -> Transform;


  /* Transform private data */
 private:
  Matrix4x4f matrix_;
  Matrix4x4f inv_matrix_;
};
/*
// ---------------------------------------------------------------------------
*/
class Transformable
{
  /* Transformable constructors */
public:
  Transformable ();

  Transformable (const Transform& t);


  /* Transformable destructor */
public:
  virtual ~Transformable () = default;


  /* Transformable public operators*/
public:
  Transformable (const Transformable&  t) = default;
  Transformable (      Transformable&& t) = default;

  auto operator = (const Transformable&  t) -> Transformable& = default;
  auto operator = (      Transformable&& t) -> Transformable& = default;


  /* Transformable public methods */
public:
  template <class T>
  auto WorldToLocal (const T& t) const -> T;

  template <class T>
  auto LocalToWorld (const T& t) const -> T;


  /* Transformable protected data */
protected:
  Transform transform_;

}; // class Transformable
/*
// ---------------------------------------------------------------------------
// Transform global operators
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t, const Point3f& p)     -> Point3f;
auto operator * (const Transform& t, const Vector3f& v)    -> Vector3f;
auto operator * (const Transform& t, const Normal3f& n)    -> Normal3f;
auto operator * (const Transform& t, const Ray& ray)       -> Ray;
auto operator * (const Transform& t, const Bounds3f& bbox) -> Bounds3f;
/*
// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
*/
auto Translate (const Vector3f& delta)             -> Transform;
auto Scale     (Float x, Float y, Float z)         -> Transform;
auto RotateX   (Float theta)                       -> Transform;
auto RotateY   (Float theta)                       -> Transform;
auto RotateZ   (Float theta)                       -> Transform;
auto Rotate    (Float theta, const Vector3f& axis) -> Transform;
auto LookAt    (const Point3f&  position,
                const Point3f&  look,
                const Vector3f& up)                -> Transform;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif //_TRANSFORM_H_
