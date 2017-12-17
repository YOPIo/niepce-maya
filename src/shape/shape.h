#ifndef _SHAPE_H_
#define _SHAPE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../core/interaction.h"
#include "../core/transform.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Shape : public Transformable
{
  /* Shape public constructors */
 public:
  Shape () = delete;
  Shape (const Transform& t);


  /* Shape public destructor */
 public:
  virtual ~Shape () = default;


  /* Shape public operators  */
 public:
  Shape (const Shape& shape) = default;
  Shape (Shape&&      shape) = default;

  auto operator = (const Shape& shape) -> Shape& = default;
  auto operator = (Shape&&      shape) -> Shape& = default;


  /* Shape public interface */
 public:
  // Reture Surface Area
  virtual auto SurfaceArea () const -> Float = 0;

  // Get a bounding box at the local coordinate system
  virtual auto LocalBounds () const -> Bounds3f = 0;

  // Get a bounding box at the world coordinate system
  virtual auto WorldBounds () const -> Bounds3f = 0;

  // Check intersection with shape
  virtual auto IsIntersect
  (
      const Ray&          ray,
      SurfaceInteraction* surface
  )
  const -> bool = 0;

  // Sample a point on the surface of the shape
  virtual auto Sample (const Sample2f& sample) const -> Interaction = 0;

  // Return the PDF
  virtual auto Pdf () const -> Float = 0;

  virtual auto ToString () const -> std::string = 0;
};
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SHAPE_H_
