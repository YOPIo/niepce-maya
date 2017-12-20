#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "shape.h"
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
struct TriangleMesh;
class  Triangle;
/*
// ---------------------------------------------------------------------------
// TriangleMesh
// ---------------------------------------------------------------------------
*/
struct TriangleMesh
{
    /* TriangleMesh constructors */
    TriangleMesh () = delete;
    TriangleMesh
    (
        uint32_t num_faces,
        uint32_t num_positions,
        uint32_t num_normals,
        uint32_t num_texcoords,
        Point3f*  const positions,
        Normal3f* const normals,
        Point2f*  const texcoord
    );


    /* TriangleMesh destructor */
    virtual ~TriangleMesh () = default;


    /* TriangleMesh public operators*/
    TriangleMesh (const TriangleMesh&  tri) = delete;
    TriangleMesh (      TriangleMesh&& tri) = default;

    auto operator = (const TriangleMesh&  tri) -> TriangleMesh& = delete;
    auto operator = (      TriangleMesh&& tri) -> TriangleMesh& = default;


    /* TriangleMesh public data */
    const uint32_t num_faces;
    const uint32_t num_positions;
    const uint32_t num_normals;
    const uint32_t num_texcoords;

    const std::unique_ptr <Point3f []>  positions;
    const std::unique_ptr <Normal3f []> normals;
    const std::unique_ptr <Point2f []>  texcoords;
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
   const std::array <uint32_t, 3>& pos,
   const std::array <uint32_t, 3>& nor,
   const std::array <uint32_t, 3>& tex
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


  /* Triangle private method */
private:
    auto GetTexcoord (uint32_t idx) const -> Point2f;


  /* Triangle private data */
public:
  std::shared_ptr <TriangleMesh> mesh_;
  std::array <uint32_t, 3> pos_idx_;
  std::array <uint32_t, 3> nor_idx_;
  std::array <uint32_t, 3> tex_idx_;
}; // class Triangle
/*
// ---------------------------------------------------------------------------
*/
auto CreateTriangleMesh
(
    uint32_t num_faces,
    uint32_t num_positions,
    uint32_t num_normals,
    uint32_t num_texcoords,
    Point3f*  const positions,
    Normal3f* const normals,
    Point2f*  const texcoord
)
-> std::shared_ptr <TriangleMesh>;
/*
// ---------------------------------------------------------------------------
*/
auto CreateTriangle
(
    const std::shared_ptr <TriangleMesh>& mesh_ptr,
    const std::array <uint32_t, 3>& position_idxs,
    const std::array <uint32_t, 3>& normal_idxs,
    const std::array <uint32_t, 3>& texcoord_idxs
)
-> std::shared_ptr <Triangle>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TRIANGLE_H_
