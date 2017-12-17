#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "shape.h"
#include "vertex.h"
#include "../core/geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Forward decralations in this header
// ---------------------------------------------------------------------------
*/
class TriangleMesh;
class Triangle;
/*
// ---------------------------------------------------------------------------
*/
auto CreateTriangleMesh
(
 size_t num_faces,
 const std::vector <Point3f>&  positions,
 const std::vector <Normal3f>& normals   = {},
 const std::vector <Point2f>&  texcoords = {}
)
-> std::shared_ptr<TriangleMesh>;
/*
// ---------------------------------------------------------------------------
*/
auto CreateTriangle
(
 const std::shared_ptr <TriangleMesh>& mesh,
 const std::array <size_t, 3>& pos_idx,
 const std::array <size_t, 3>& nor_idx = {0, 0, 0},
 const std::array <size_t, 3>& tex_idx = {0, 0, 0}
)
-> std::shared_ptr<Triangle>;
/*
// ---------------------------------------------------------------------------
// TriangleMesh
// ---------------------------------------------------------------------------
*/
class TriangleMesh
{
  /* TriangleMesh constructors */
public:
  TriangleMesh () = delete;
  TriangleMesh
  (
   size_t num_faces,
   const std::vector <Point3f>&  position,
   const std::vector <Normal3f>& normals,
   const std::vector <Point2f>&  texcoords
  );


  /* TriangleMesh destructor */
public:
  virtual ~TriangleMesh () = default;


  /* TriangleMesh public operators*/
public:
  TriangleMesh (const TriangleMesh&  tri) = default;
  TriangleMesh (      TriangleMesh&& tri) = default;

  auto operator = (const TriangleMesh&  tri) -> TriangleMesh& = default;
  auto operator = (      TriangleMesh&& tri) -> TriangleMesh& = default;


  /* TriangleMesh public methods */
public:
  auto GetPosition (size_t idx) const -> Point3f;
  auto GetNormal   (size_t idx) const -> Normal3f;
  auto GetTexcoord (size_t idx) const -> Point2f;

  auto NumPosition () const -> size_t;
  auto NumNormal   () const -> size_t;
  auto NumTexcoord () const -> size_t;
  auto NumFaces    () const -> size_t;

  /* TriangleMesh private data */
private:
  const size_t num_faces_;
  const size_t num_positions_;
  const size_t num_normals_;
  const size_t num_texcoords_;

  std::unique_ptr <Point3f []>  positions_;
  std::unique_ptr <Normal3f []> normals_;
  std::unique_ptr <Point2f []>  texcoords_;
}; // class TriangleMesh
/*
// ---------------------------------------------------------------------------
// Triangle
// ---------------------------------------------------------------------------
*/
class Triangle : public Shape
{
  /* Triangle constructors */
public:
  Triangle () = default;
  Triangle
  (
   const std::shared_ptr<TriangleMesh>& mesh,
   const std::array <size_t, 3>& pos,
   const std::array <size_t, 3>& nor,
   const std::array <size_t, 3>& tex
  );


  /* Triangle public destructor */
public:
  ~Triangle () = default;


  /* Triangle public operators */
public:
  Triangle (const Triangle&  t) = default;
  Triangle (      Triangle&& t) = default;

  auto operator = (const Triangle&  t) -> Triangle& = default;
  auto operator = (      Triangle&& t) -> Triangle& = default;


  /* Triangle override methods */
public:
  // Return surface area of triangle
  auto SurfaceArea () const -> Float override;

  // Return bounding box in object coordinate
  auto LocalBounds () const -> Bounds3f override;

  // Return bounding box in world coordinate
  auto WorldBounds () const -> Bounds3f override;

  // Intersection test
  auto IsIntersect
  (
   const Ray&          ray,
   SurfaceInteraction* surface
  )
  const -> bool override;

  // Sample a point on the surface of the shape
  auto Sample (const Sample2f& sample) const -> Interaction override final;

  // Return the PDF
  auto Pdf () const -> Float override final;

  auto ToString () const -> std::string override final;


  /* Triangle private data */
public:
  std::shared_ptr <TriangleMesh> mesh_;
  std::array <size_t, 3> pos_idx_;
  std::array <size_t, 3> nor_idx_;
  std::array <size_t, 3> tex_idx_;
}; // class Triangle
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TRIANGLE_H_
