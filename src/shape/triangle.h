#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "shape.h"
#include "vertex.h"
#include "../core/geometry.h"
#include "../core/object.h"
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
 Index num_faces,
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
 const std::array <Index, 3>& pos_idx,
 const std::array <Index, 3>& nor_idx = {0, 0, 0},
 const std::array <Index, 3>& tex_idx = {0, 0, 0}
)
-> std::shared_ptr<Triangle>;
/*
// ---------------------------------------------------------------------------
// TriangleMesh
// ---------------------------------------------------------------------------
*/
class TriangleMesh : public Object
{
  /* TriangleMesh constructors */
public:
  TriangleMesh () = delete;
  TriangleMesh
  (
   Index num_faces,
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
  auto GetPosition (Index idx) const -> Point3f;
  auto GetNormal   (Index idx) const -> Normal3f;
  auto GetTexcoord (Index idx) const -> Point2f;

  auto NumPosition () const -> Index;
  auto NumNormal   () const -> Index;
  auto NumTexcoord () const -> Index;
  auto NumFaces    () const -> Index;


  /* Triangle public override method */
public:
  auto ToString () const -> std::string override final;

  /* TriangleMesh private data */
private:
  const Index num_faces_;
  const Index num_positions_;
  const Index num_normals_;
  const Index num_texcoords_;

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
   const std::array <Index, 3>& pos,
   const std::array <Index, 3>& nor,
   const std::array <Index, 3>& tex
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
  const std::shared_ptr <TriangleMesh> mesh_;
  const std::array <Index, 3> pos_idx_;
  const std::array <Index, 3> nor_idx_;
  const std::array <Index, 3> tex_idx_;
}; // class Triangle
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TRIANGLE_H_
