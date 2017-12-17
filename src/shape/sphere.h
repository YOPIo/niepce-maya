#ifndef _SPHERE_H_
#define _SPHERE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "shape.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Sphere : public Shape
{
  /* Sphere public constructors */
 public:
  Sphere () = delete;
  Sphere
  (
   const Transform& t,
         Float      radius
  )
;
  Sphere
  (
   const Point3f& p,
         Float    radius
  );


  /* Sphere public destructor */
public:
  virtual ~Sphere () = default;


  /* Sphere public operators */
  Sphere (const Sphere&  sphere) = default;
  Sphere (      Sphere&& sphere) = default;

  auto operator = (const Sphere&  sphere) -> Sphere& = default;
  auto operator = (      Sphere&& sphere) -> Sphere& = default;


  /* Sphere public methods */
public:
  // Reture Surface Area
  auto SurfaceArea () const -> Float override final;

  // Get a bounding box at the local coordinate system
  auto LocalBounds () const -> Bounds3f override final;

  // Get a bounding box at the world coordinate system
  auto WorldBounds () const -> Bounds3f override final;

  // Check intersection with shape
  auto IsIntersect
  (
      const Ray&          ray,
      SurfaceInteraction* surface
  )
  const -> bool override;

  // Sample a point on the surface of the shape
  auto Sample (const Point2f& rnd) const -> Interaction override final;

  // Return the PDF
  auto Pdf () const -> Float override final;

  auto ToString () const -> std::string override final;

  auto WorldCenter () const -> Point3f;
  auto LocalCenter () const -> Point3f;
  auto Radius      () const -> Float;


  /* Sphere private data */
private:
  const Point3f center_;
  const Float   radius_;
};
/*
// ---------------------------------------------------------------------------
*/
auto operator << (std::ostream& os, const Sphere& sphere) -> std::ostream&;
/*
// ---------------------------------------------------------------------------
*/
auto CreateSphere
(
 Float radius,
 const Point3f& position
)
-> std::shared_ptr< Sphere>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SPHERE_H_
