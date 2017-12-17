#include "transform.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Transform::Transform () :
    matrix_     (),
    inv_matrix_ (Inverse (matrix_))
{}
/*
// ---------------------------------------------------------------------------
*/
Transform::Transform (Float m00, Float m01, Float m02, Float m03,
                      Float m10, Float m11, Float m12, Float m13,
                      Float m20, Float m21, Float m22, Float m23,
                      Float m30, Float m31, Float m32, Float m33) :
    matrix_     (Matrix4x4f (m00, m01, m02, m03,
                             m10, m11, m12, m13,
                             m20, m21, m22, m23,
                             m30, m31, m32, m33)),
    inv_matrix_ (Inverse(matrix_))
{}
/*
// ---------------------------------------------------------------------------
*/
Transform::Transform (const Matrix4x4f& m) :
    matrix_     (m),
    inv_matrix_ ( Inverse(m) )
{}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::operator == (const Transform& t) const -> bool
{
  return t.matrix_ == matrix_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::operator != (const Transform& t) const -> bool
{
  return t.matrix_ != matrix_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::operator () (size_t row, size_t col) const noexcept -> Float
{
  return matrix_ (row, col);
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::operator () (size_t row, size_t col) noexcept -> Float&
{
  return matrix_ (row, col);
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::At (size_t row, size_t col) const -> Float
{
  if (row >= 4 || col >= 4)
  {
    throw std::out_of_range ("Matrix range error.");
  }
  return matrix_ (row, col);
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::At (size_t row, size_t col) -> Float&
{
  if (row >= 4 || col >= 4)
  {
    throw std::out_of_range ("Matrix range error.");
  }
  return matrix_ (row, col);
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::GetMatrix () const -> Matrix4x4f
{
  return matrix_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::GetInvMatrix() const -> Matrix4x4f
{
  return inv_matrix_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::IsIdentity() const -> bool
{
  return (matrix_ (0, 0) == 1.f && matrix_ (0, 1) == 0.f &&
          matrix_ (0, 2) == 0.f && matrix_ (0, 3) == 0.f &&
          matrix_ (1, 0) == 0.f && matrix_ (1, 1) == 1.f &&
          matrix_ (1, 2) == 0.f && matrix_ (1, 3) == 0.f &&
          matrix_ (2, 0) == 0.f && matrix_ (2, 1) == 0.f &&
          matrix_ (2, 2) == 1.f && matrix_ (2, 3) == 0.f &&
          matrix_ (3, 0) == 0.f && matrix_ (3, 1) == 0.f &&
          matrix_ (3, 2) == 0.f && matrix_ (3, 3) == 1.f);
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::ToIdentity() -> void
{
  matrix_.ToIdentity();
  inv_matrix_ = Inverse (matrix_);
}
/*
// ---------------------------------------------------------------------------
// Transform global operators
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t,  const Point3f& p) -> Point3f
{
  const Float x = p.x, y = p.y, z = p.z;
  const Float px = t (0, 0) * x + t (0, 1) * y + t (0, 2) * z + t (0, 3);
  const Float py = t (1, 0) * x + t (1, 1) * y + t (1, 2) * z + t (1, 3);
  const Float pz = t (2, 0) * x + t (2, 1) * y + t (2, 2) * z + t (2, 3);
  const Float pw = t (3, 0) * x + t (3, 1) * y + t (3, 2) * z + t (3, 3);
  return pw == 1 ? Point3f (px, py, pz) : Point3f (px, py, pz) / pw;
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t, const Vector3f& v) -> Vector3f
{
  const Float x = v.x, y = v.y, z = v.z;
  return Vector3f (t (0, 0) * x + t (0, 1) * y + t (0, 2) * z,
                   t (1, 0) * x + t (1, 1) * y + t (1, 2) * z,
                   t (2, 0) * x + t (2, 1) * y + t (2, 2) * z);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t ,const Normal3f& n) -> Normal3f
{
  const Float x = n.x, y = n.y, z = n.z;
  const Matrix4x4f inv (t.GetInvMatrix ());
  return Normal3f (inv (0, 0) * x + inv (1, 0) * y + inv (2, 0) * z,
                   inv (0, 1) * x + inv (1, 1) * y + inv (2, 1) * z,
                   inv (0, 2) * x + inv (1, 2) * y + inv (2, 2) * z);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t, const Ray& ray) -> Ray
{
  const Point3f  origin    (t * ray.origin);
  const Vector3f direction (t * ray.direction);
  return Ray (origin, direction);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t, const Bounds3f& bbox) -> Bounds3f
{
  // TODO:
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::Identity () -> Transform
{
  return Transform ();
}
/*
// ---------------------------------------------------------------------------
// Transformable
// ---------------------------------------------------------------------------
*/
Transformable::Transformable () :
  transform_ ()
{}
/*
// ---------------------------------------------------------------------------
*/
Transformable::Transformable (const Transform& t) :
  transform_ (t)
{}
/*
// ---------------------------------------------------------------------------
*/
template <class T>
auto Transformable::WorldToLocal (const T &t) const -> T
{
  return Transform (transform_.GetInvMatrix ()) * t;
}
template auto Transformable::WorldToLocal (const Ray& t) const -> Ray;
template auto Transformable::WorldToLocal (const Vector3f& t) const -> Vector3f;
template auto Transformable::WorldToLocal (const Point3f&  t) const -> Point3f;
template auto Transformable::WorldToLocal (const Normal3f& t) const -> Normal3f;
/*
// ---------------------------------------------------------------------------
*/
template <class T>
auto Transformable::LocalToWorld (const T &t) const -> T
{
  return transform_ * t;
}
template auto Transformable::LocalToWorld (const Ray& t) const -> Ray;
template auto Transformable::LocalToWorld (const Vector3f& t) const -> Vector3f;
template auto Transformable::LocalToWorld (const Point3f&  t) const -> Point3f;
template auto Transformable::LocalToWorld (const Normal3f& t) const -> Normal3f;
// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
auto Translate(const Vector3f& delta) -> Transform
{
  return Transform (1.f, 0.f, 0.f, delta.x,
                    0.f, 1.f, 0.f, delta.y,
                    0.f, 0.f, 1.f, delta.z,
                    0.f, 0.f, 0.f,     1.f);
}
/*
// ---------------------------------------------------------------------------
*/
auto Scale(Float x, Float y, Float z) -> Transform
{
  return Transform(  x, 0.f, 0.f, 0.f,
                   0.f,   y, 0.f, 0.f,
                   0.f, 0.f,   z, 0.f,
                   0.f, 0.f, 0.f, 1.f);
}
/*
// ---------------------------------------------------------------------------
*/
auto RotateX(Float theta) -> Transform
{
  const Float sin_t = std::sin (ToRadians(theta));
  const Float cos_t = std::cos (ToRadians(theta));
  return Transform(1.f,   0.f,   0.f,  0.f,
                   0.f, cos_t, -sin_t, 0.f,
                   0.f, sin_t,  cos_t, 0.f,
                   0.f,   0.f,   0.f,  1.f);
}
/*
// ---------------------------------------------------------------------------
*/
auto RotateY(Float theta) -> Transform
{
  const Float sin_t = std::sin (ToRadians(theta));
  const Float cos_t = std::cos (ToRadians(theta));
  return Transform( cos_t, 0.f, sin_t, 0.f,
                      0.f, 1.f,   0.f, 0.f,
                   -sin_t, 0.f, cos_t, 0.f,
                      0.f, 0.f,   0.f, 1.f);
}
/*
// ---------------------------------------------------------------------------
*/
auto RotateZ(Float theta) -> Transform
{
  const Float sin_t = std::sin (ToRadians(theta));
  const Float cos_t = std::cos (ToRadians(theta));
  return Transform(cos_t, -sin_t, 0.f, 0.f,
                   sin_t,  cos_t, 0.f, 0.f,
                     0.f,    0.f, 1.f, 0.f,
                     0.f,    0.f, 0.f, 1.f);
}
/*
// ---------------------------------------------------------------------------
*/
// Rodriguez rotation formula
auto Rotate(Float theta, const Vector3f& axis) -> Transform
{
  const Vector3f     n = Normalize(axis);
  const    Float sin_t = std::sin (ToRadians(theta));
  const    Float cos_t = std::cos (ToRadians(theta));
  const    Float     c = (1.f - cos_t);

  Matrix4x4f ret;
  ret (0, 0) = n.x * n.x * c + cos_t;
  ret (0, 1) = n.x * n.y * c - n.z * sin_t;
  ret (0, 2) = n.z * n.x * c + n.y * sin_t;
  ret (0, 3) = 0.f;

  ret (1, 0) = n.x * n.y * c + n.z * sin_t;
  ret (1, 1) = n.y * n.y * c + cos_t;
  ret (1, 2) = n.y * n.z * c - n.x * sin_t;
  ret (1, 3) = 0.f;

  ret (2, 0) = n.z * n.x * c + n.y * sin_t;
  ret (2, 1) = n.y * n.z * c + n.x * sin_t;
  ret (2, 2) = n.z * n.z * c + cos_t;
  ret (2, 3) = 0.f;

  ret (3, 0) = 0.f;
  ret (3, 1) = 0.f;
  ret (3, 2) = 0.f;
  ret (3, 3) = 1.f;

  return Transform(ret);
}
/*
// ---------------------------------------------------------------------------
*/
auto LookAt(const Point3f&  position,
            const Point3f&  target,
            const Vector3f& up) -> Transform
{
  Vector3f ez (Normalize (target - position));
  Vector3f ex (Normalize (Cross(up, ez)));
  Vector3f ey (Normalize (Cross(ez, ex)));

  return Transform (ex.x, ey.x, ez.x, position.x,
                    ex.y, ey.y, ez.y, position.y,
                    ex.z, ey.z, ez.z, position.z,
                     0.f,  0.f,  0.f,        1.f);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
