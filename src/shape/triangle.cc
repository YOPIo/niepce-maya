#include "triangle.h"
#include "../sampler/sampler_utils.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// TriangleMesh class
// ---------------------------------------------------------------------------
*/
TriangleMesh::TriangleMesh
(
    uint32_t _num_faces,
    uint32_t _num_positions,
    uint32_t _num_normals,
    uint32_t _num_texcoords,
    Point3f*  const _positions,
    Normal3f* const _normals,
    Point2f*  const _texcoord
) :
    num_faces     (_num_faces),
    num_positions (_num_positions),
    num_normals   (_num_normals),
    num_texcoords (_num_texcoords),
    positions     (_positions),
    normals       (_normals),
    texcoords     (_texcoord)
{}
/*
// ---------------------------------------------------------------------------
// Triangle class
// ---------------------------------------------------------------------------
*/
Triangle::Triangle
(
 const std::shared_ptr <TriangleMesh>& mesh,
 const std::array <uint32_t, 3>& pos,
 const std::array <uint32_t, 3>& nor,
 const std::array <uint32_t, 3>& tex
) :
  mesh_    (mesh),
  pos_idx_ (pos),
  nor_idx_ (nor),
  tex_idx_ (tex),
  Shape    (Transform::Identity ())
{}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::SurfaceArea() const -> Float
{
    const Point3f& p0 (mesh_->positions[pos_idx_[0]]);
    const Point3f& p1 (mesh_->positions[pos_idx_[1]]);
    const Point3f& p2 (mesh_->positions[pos_idx_[2]]);

    return 0.5 * Cross (p1 - p0, p2 - p0).Length();
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::LocalBounds () const -> Bounds3f
{
  // Because all of vertices located in world coordinate, transform them to local coordinate
  // TODO: implementation
  return Bounds3f ({});
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::WorldBounds () const -> Bounds3f
{
    const Point3f& p0 (mesh_->positions[pos_idx_[0]]);
    const Point3f& p1 (mesh_->positions[pos_idx_[1]]);
    const Point3f& p2 (mesh_->positions[pos_idx_[2]]);
    return Bounds3f ({p0, p1, p2});
}
/*
// ---------------------------------------------------------------------------
// Reference: Fast, Minimum Storage Ray/Triangle Intersection
// ---------------------------------------------------------------------------
*/
auto Triangle::IsIntersect
(
 const Ray&          ray,
 SurfaceInteraction* interaction
)
const -> bool
{
  // Get vertices which representing a triangle face
  const Point3f& p0 (mesh_->positions[pos_idx_[0]]);
  const Point3f& p1 (mesh_->positions[pos_idx_[1]]);
  const Point3f& p2 (mesh_->positions[pos_idx_[2]]);


  // Find vectors for two edges sharing vertex0
  const Vector3f edge0 = p1 - p0;
  const Vector3f edge1 = p2 - p0;

  const Vector3f pvec = Cross (ray.direction, edge1);

  const Float det = Dot (edge0, pvec);
  if (std::abs (det) < kEpsilon)
  {
    return false;
  }
  Float inv_det = 1.0 / det;

  const Vector3f tvec = ray.origin - p0;
  const Float    u    = Dot (tvec, pvec) * inv_det;
  if (u < 0.0 || u > 1.0)
  {
    return false;
  }

  const Vector3f qvec = Cross (tvec, edge0);
  const Float    v    = Dot (ray.direction, qvec) * inv_det;
  if (v < 0.0 || u + v > 1.0)
  {
    return false;
  }

  const Float t = Dot (edge1, qvec) * inv_det;
  if (std::abs (t) < kEpsilon)
  {
    return false;
  }
  if (t <= kEpsilon)
  {
    return false;
  }

  // Ray intersect with triangle shape
  // Compute hit position, normal, uv coodinate etc...
  const Point3f  position = ray (t);
  const Normal3f normal   = Normalize (Cross (edge0, edge1));
  const Vector3f outgoing = Normalize (-ray.direction);

  // Get UV coordinate, if present
  const Point2f uv0 (GetTexcoord (0));
  const Point2f uv1 (GetTexcoord (1));
  const Point2f uv2 (GetTexcoord (2));

  // Compute the texcoord
  const Float   uv (1.0 - u - v);
  const Point2f texcoord (uv * uv0 + u * uv1 + v * uv2);

  // Compute partial derivatives dpdu and dpdv
  const Vector2f duv02 (uv0 - uv2);
  const Vector2f duv12 (uv1 - uv2);
  const Vector3f dp02  (p0 - p2);
  const Vector3f dp12  (p1 - p2);
  const Float    determinant (duv02.u * duv12.v - duv02.v * duv12.u);

  // Conpute triangle partial derivatives
  Vector3f dpdu, dpdv;
  if (determinant < 1e-5)
  {
      inv_det = 1.0 / determinant;
      dpdu = ( duv12.v * dp02 - duv02.v * dp12) * inv_det;
      dpdv = (-duv12.u * dp02 + duv02.u * dp12) * inv_det;
  }
  if (determinant >= 1e-5 || Cross (dpdu, dpdv).LengthSquared () == 0)
  {
    OrthoNormalBasis (normal, &dpdu, &dpdv);
  }

  // Initialize SurfaceInteraction
  *interaction = SurfaceInteraction (position,
                                     outgoing,
                                     normal,
                                     t,
                                     texcoord,
                                     dpdu,
                                     dpdv,
                                     Normal3f (0, 0, 0),
                                     Normal3f (0, 0, 0));
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::Sample (const Sample2f& sample) const -> Interaction
{
  const Point2f b (SampleUniformTriangle (sample));

  // Get triangle vertices
  const Point3f& p0 (mesh_->positions[pos_idx_[0]]);
  const Point3f& p1 (mesh_->positions[pos_idx_[1]]);
  const Point3f& p2 (mesh_->positions[pos_idx_[2]]);

  Interaction it;
  it.position = b[0] * p0 + b[1] * p1 + (1 - b[0] - b[1]) * p2;
  // Compute surface normal for sampled point on triangle
  it.normal = (Normal3f (Cross (p1 - p0, p2 - p0)));

  /*
  // Ensure correct orientation of the geometric normal; follow the same
  // approach as was used in Triangle::Intersect().
  if (mesh->n)
  {
    Normal3f ns(b[0] * mesh->n[v[0]] + b[1] * mesh->n[v[1]] +
                (1 - b[0] - b[1]) * mesh->n[v[2]]);
    it.normal = Faceforward(it.n, ns);
  }
  else if (reverseOrientation ^ transformSwapsHandedness)
    it.normal *= -1;
  */

  // Compute error bounds for sampled point on triangle
  // Point3f pAbsSum = Abs(b[0] * p0) + Abs(b[1] * p1) + Abs((1 - b[0] - b[1]) * p2);
  // it.pError = gamma(6) * Vector3f(pAbsSum.x, pAbsSum.y, pAbsSum.z);
  return it;
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::GetTexcoord (uint32_t idx) const -> Point2f
{
    if (mesh_->texcoords == nullptr)
    {
        return Point2f::Zero ();
    }

    if  (0 <= idx && idx <= 2)
    {
        return mesh_->texcoords [tex_idx_[idx]];
    }

    return Point2f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::Pdf () const -> Float
{
  return 1.0 / SurfaceArea ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::ToString () const -> std::string
{
  std::string str ("Triangle Shape");
  return str;
}
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
-> std::shared_ptr <TriangleMesh>
{
    return std::make_shared <TriangleMesh> (num_faces,
                                            num_positions,
                                            num_normals,
                                            num_texcoords,
                                            positions,
                                            normals,
                                            texcoord);
}
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
-> std::shared_ptr <Triangle>
{
    return std::make_shared <Triangle> (mesh_ptr,
                                        position_idxs,
                                        normal_idxs,
                                        texcoord_idxs);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
