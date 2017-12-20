#include "sphere.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Sphere::Sphere
(
 const Transform& t,
       Float      radius
) :
  Shape   (t),
  radius_ (radius)
{}
/*
// ---------------------------------------------------------------------------
*/
Sphere::Sphere
(
 const Point3f& center,
       Float    radius
) :
  Shape   (Transform (Translate (static_cast<Vector3f> (center)))),
  center_ (center),
  radius_ (radius)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::SurfaceArea () const -> Float
{
  return 4.0 * kPi * radius_ * radius_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::LocalBounds () const -> Bounds3f
{
  return Bounds3f ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::WorldBounds () const -> Bounds3f
{
  return Bounds3f ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::IsIntersect
(
 const Ray&          ray,
 SurfaceInteraction* si
)
const -> bool
{
  /*
  // Transform ray in the world coordinate system to
  // object coordinate system
  const Ray local_ray (WorldToLocal (ray));

  // Prepare for solving equation
  const Float a (local_ray.direction.x * local_ray.direction.x +
                 local_ray.direction.y * local_ray.direction.y +
                 local_ray.direction.z * local_ray.direction.z);
  const Float b (2.0 * (local_ray.direction.x * local_ray.origin.x +
                        local_ray.direction.y * local_ray.origin.y +
                        local_ray.direction.z * local_ray.origin.z));
  const Float c (local_ray.origin.x * local_ray.origin.x +
                 local_ray.origin.y * local_ray.origin.y +
                 local_ray.origin.z * local_ray.origin.z -
                 radius_ * radius_);

  // Solve quadratic
  const Float discrim (b * b - 4.0 * a * c);
  if (discrim < 0)
  {
    return false;
  }
  const Float sqrt_discrim (std::sqrt (discrim));
  const Float q  (b < 0 ? -0.5 * (b - sqrt_discrim) : -0.5 * (b + sqrt_discrim));
  const Float t0 (q / a);
  const Float t1 (c / q);
  const Float t  (t0 < t1 ? t0 : t1);

  const Point3f position (local_ray (t));

  const Float z (std::sqrt (position.x * position.x + position.y * position.y));
  const Float inv_z (1.0 / z);
  const Float theta   (std::acos (Clamp (position.z / radius_, -1, 1)));
  const Float cos_phi (position.x * inv_z);
  const Float sin_phi (position.y * inv_z);
  const Vector3f dpdu (-360 * position.y, 360 * position.x, 0.0);
  const Vector3f dpdv (position.z * cos_phi, position.z * sin_phi,
                       -radius_ * std::sin (theta));

  *si = SurfaceInteraction (LocalToWorld (position),
                            -ray.direction,
                            LocalToWorld (position - LocalCenter ()),
                            t,
                            Point2f::Zero (),
                            dpdu,
                            dpdv,
                            Normal3f (),
                            Normal3f ());
  return true;
  */

  const Float kSphereEpsilon = 1e-5;

  const Vector3f o_to_p (WorldCenter () - ray.origin);
  const Float b         (Dot (o_to_p, ray.direction));
  const Float c         (b * b - Dot (o_to_p, o_to_p) + radius_ * radius_);

  if (c < 0.0)
  {
    return false;
  }

  const Float sqrt_c (std::sqrt (c));
  const Float t1 (b - sqrt_c);
  const Float t2 (b + sqrt_c);

  if (t1 < kSphereEpsilon && t2 < kSphereEpsilon)
  {
    return false;
  }

  // Ray intersect with sphere
  // Compute hit position, normal, etc...
  const Point3f  position (t1 > kSphereEpsilon ? ray (t1) : ray (t2));
  const Float    t        (t1 > kSphereEpsilon ? t1       : t2);
  const Normal3f normal   (position - WorldCenter ());
  Vector3f tangent, binormal;
  OrthoNormalBasis (normal, &tangent, &binormal);

  *si = SurfaceInteraction (position,
                            Normalize (-ray.direction),
                            normal,
                            t,
                            Point2f::Zero (),
                            tangent,
                            binormal,
                            Normal3f (),
                            Normal3f ());
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::Sample (const Sample2f& sample) const -> Interaction
{
  // TODO: implementation
  return Interaction ();
  
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::Pdf () const -> Float
{
  // TODO: implementation
  return -1.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::ToString () const -> std::string
{
  std::string str ("");
  str += "Shape type: Sphere\n";
  str += "Radius         : " +  std::to_string (radius_);
  str += "World Position : [" +  WorldCenter ().ToString () + "]\n";
  return str;
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::WorldCenter () const -> Point3f
{
  return LocalToWorld (Point3f::Zero ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::LocalCenter () const -> Point3f
{
  return Point3f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Sphere::Radius () const -> Float
{
  return radius_;
}
/*
// ---------------------------------------------------------------------------
*/
auto operator << (std::ostream& os, const Sphere& sphere) -> std::ostream&
{
  os << "Shape type: Sphere\n";
  os << "[Radius: " << sphere.Radius () << "]";
  os << "[World Position: " << sphere.WorldCenter ().ToString () + "]\n";
  return os;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateSphere
(
 Float radius,
 const Point3f& position
)
-> std::shared_ptr <Sphere>
{
  const std::shared_ptr <Sphere> sphere (std::make_shared <Sphere> (position, radius));
  return std::move (sphere);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
