#include "triangle.h"
#include "../sampler/sampler_utils.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
TriangleMesh::TriangleMesh
(
 Index num_faces,
 const std::vector <Point3f>&  positions,
 const std::vector <Normal3f>& normals,
 const std::vector <Point2f>&  texcoords
) :
  num_faces_     (num_faces),
  num_positions_ (positions.size ()),
  num_normals_   (normals.size ()),
  num_texcoords_ (texcoords.size ())
{
  positions_ = nullptr;
  normals_   = nullptr;
  texcoords_ = nullptr;

  // Copy positions
  if (num_positions_ > 0)
  {
    // Allocate memory
    positions_.reset (new Point3f [num_positions_]);
    for (Index i = 0; i < num_positions_; ++i)
    {
      positions_[i] = positions[i];
    }
  }

  // Copy normals
  if (num_normals_ > 0)
  {
    // Allocate memory
    normals_.reset (new Normal3f [num_normals_]);
    for (Index i = 0; i < num_normals_; ++i)
    {
      normals_[i] = normals[i];
    }
  }

  // Copy texcoords
  if (num_texcoords_ > 0)
  {
    // Allocate memory
    texcoords_.reset (new Point2f [num_normals_]);
    for (Index i = 0; i < num_texcoords_; ++i)
    {
      texcoords_[i] = texcoords[i];
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::GetPosition (Index idx) const -> Point3f
{
  if (idx < num_positions_)
  {
    return positions_[idx];
  }
  throw std::out_of_range ("Out of range.");
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::GetNormal (Index idx) const -> Normal3f
{
  if (normals_ == nullptr)
  {
    return Normal3f (0, 1, 0);
  }

  if (idx < num_normals_)
  {
    return normals_[idx];
  }
  throw std::out_of_range ("Out of range.");
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::GetTexcoord (Index idx) const -> Point2f
{
  if (texcoords_ == nullptr)
  {
    return Point2f::Zero ();
  }

  if (idx < num_texcoords_)
  {
    return texcoords_[idx];
  }
  throw std::out_of_range ("Out of range.");
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::NumPosition () const -> Index
{
  return num_positions_;
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::NumNormal () const -> Index
{
  return num_normals_;
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::NumTexcoord () const -> Index
{
  return num_texcoords_;
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::NumFaces () const -> Index
{
  return num_faces_;
}
/*
// ---------------------------------------------------------------------------
*/
auto TriangleMesh::ToString () const -> std::string
{
    return "";
}
/*
// ---------------------------------------------------------------------------
// Triangle
// ---------------------------------------------------------------------------
*/
Triangle::Triangle
(
 const std::shared_ptr<TriangleMesh>& mesh,
 const std::array <Index, 3>& pos,
 const std::array <Index, 3>& nor,
 const std::array <Index, 3>& tex
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
    const Point3f& p0 (mesh_->GetPosition (pos_idx_[0]));
    const Point3f& p1 (mesh_->GetPosition (pos_idx_[1]));
    const Point3f& p2 (mesh_->GetPosition (pos_idx_[2]));
  return 0.5 * Cross(p1 - p0, p2 - p0).Length();
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
  const Point3f& p0 (mesh_->GetPosition (pos_idx_[0]));
  const Point3f& p1 (mesh_->GetPosition (pos_idx_[1]));
  const Point3f& p2 (mesh_->GetPosition (pos_idx_[2]));
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
  const Point3f& p0 (mesh_->GetPosition (pos_idx_[0]));
  const Point3f& p1 (mesh_->GetPosition (pos_idx_[1]));
  const Point3f& p2 (mesh_->GetPosition (pos_idx_[2]));


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
  const Point2f uv0 (mesh_->GetTexcoord (tex_idx_[0]));
  const Point2f uv1 (mesh_->GetTexcoord (tex_idx_[1]));
  const Point2f uv2 (mesh_->GetTexcoord (tex_idx_[2]));

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
  const Point3f& p0 (mesh_->GetPosition (pos_idx_[0]));
  const Point3f& p1 (mesh_->GetPosition (pos_idx_[1]));
  const Point3f& p2 (mesh_->GetPosition (pos_idx_[2]));

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
auto Triangle::Pdf () const -> Float
{
  return 1.0 / SurfaceArea ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Triangle::ToString () const -> std::string
{  
  Point3f p0 (mesh_->GetPosition (pos_idx_[0]));
  Point3f p1 (mesh_->GetPosition (pos_idx_[1]));
  Point3f p2 (mesh_->GetPosition (pos_idx_[2])); 
  const std::string str ("[" + p0.ToString () + "," + p1.ToString () + ", " + p2.ToString() + "]");
  return str;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateTriangleMesh
(
 Index num_faces,
 const std::vector <Point3f>&  positions,
 const std::vector <Normal3f>& normals,
 const std::vector <Point2f>&  texcoords
)
-> std::shared_ptr <TriangleMesh>
{
  const std::shared_ptr <TriangleMesh> mesh
    (std::make_shared <TriangleMesh> (num_faces, positions, normals, texcoords));
  return std::move (mesh);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateTriangle
(
 const std::shared_ptr <TriangleMesh>& mesh,
 const std::array <Index, 3>& p_idx,
 const std::array <Index, 3>& n_idx,
 const std::array <Index, 3>& t_idx
)
-> std::shared_ptr<Triangle>
{
  const std::shared_ptr <Triangle> tri
    (std::make_shared <Triangle> (mesh, p_idx, n_idx, t_idx));
  return std::move (tri);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
