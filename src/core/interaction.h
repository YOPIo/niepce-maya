#ifndef _INTERACTION_H_
#define _INTERACTION_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct Interaction
{
  /* Interaction constructors */
  Interaction () :
    position (Point3f::Max ()),
    outgoing (),
    normal   (),
    distance (std::numeric_limits<Float>::max ())
  {}

  Interaction
  (
      const Point3f&  p,
      const Vector3f& dir,
      const Normal3f& n,
            Float     dis
  ) :
    position (p),
    outgoing (dir),
    normal   (n),
    distance (dis)
  {}

  /* Interaction destructor */
  virtual ~Interaction ()
  {}

  Interaction (const Interaction&  interaction) = default;
  Interaction (      Interaction&& interaction) = default;


  /* Interaction operators */
  auto operator = (const Interaction&  interaction) -> Interaction& = default;
  auto operator = (      Interaction&& interaction) -> Interaction& = default;


  /* Interaction protected data */
public:
  Point3f  position; // Position where ray has intersected in world coordinates
  Vector3f outgoing; // Normalized outgoing direction in world coordinates
  Normal3f normal;   // Surface normal at the position
  Float    distance; // t: Distance between ray origin to surface point

}; // class Interaction
/*
// ---------------------------------------------------------------------------
*/
struct SurfaceInteraction : public Interaction
{
  /* SurfaceInteraction public constructors */
 public:
  SurfaceInteraction () :
    Interaction (),
    texcoord    (),
    dpdu (), dpdv (),
    dndu (), dndv (),
    primitive (nullptr)
  {}

  SurfaceInteraction
  (
      const Point3f&  p,
      const Vector3f& o,
      const Normal3f& n,
            Float     d
  ) :
    Interaction (p, o, n, d),
    primitive (nullptr)
  {}

  SurfaceInteraction
  (
      const Interaction& i,
      const Point2f&     t,
      const Vector3f&    dpdu,
      const Vector3f&    dpdv,
      const Normal3f&    dndu,
      const Normal3f&    dndv
   ) :
    Interaction (i),
    texcoord    (t),
    dpdu        (dpdu),
    dpdv        (dpdv),
    dndu        (dndu),
    dndv        (dndv),
    primitive (nullptr)
  {
    shading.normal = i.normal;
    shading.dpdu   = dpdu;
    shading.dpdv   = dpdv;
    shading.dndu   = dndu;
    shading.dndv   = dndv;
  }

  SurfaceInteraction
  (
      const Point3f&  p,
      const Vector3f& d,
      const Normal3f& n,
            Float     dis,
      const Point2f&  t,
      const Vector3f& dpdu,
      const Vector3f& dpdv,
      const Normal3f& dndu,
      const Normal3f& dndv
  ) :
    Interaction (p, d, n, dis),
    texcoord    (t),
    dpdu        (dpdu),
    dpdv        (dpdv),
    dndu        (dndu),
    dndv        (dndv),
    primitive (nullptr)
  {
    shading.normal = n;
    shading.dpdu   = dpdu;
    shading.dpdv   = dpdv;
    shading.dndu   = dndu;
    shading.dndv   = dndv;
  }

  SurfaceInteraction
  (
      const Point3f&  p,
      const Vector3f& d,
      const Normal3f& n,
            Float     dis,
      const Point2f&  t,
      const Vector3f& dpdu,
      const Vector3f& dpdv,
      const Normal3f& dndu,
      const Normal3f& dndv,
      const Normal3f& sn,
      const Vector3f& sdpdu,
      const Vector3f& sdpdv,
      const Normal3f& sdndu,
      const Normal3f& sdndv
  ) :
    Interaction (p, d, n, dis),
    texcoord    (t),
    dpdu        (dpdu),
    dpdv        (dpdv),
    dndu        (dndu),
    dndv        (dndv),
    primitive (nullptr)
  {
    shading.normal = sn;
    shading.dpdu   = sdpdu;
    shading.dpdv   = sdpdv;
    shading.dndu   = sdndu;
    shading.dndv   = sdndv;
  }


  /* SurfaceInteraction public destructor */
  virtual ~SurfaceInteraction () = default;


  /* Surfaceinteraction operators */
 public:
  SurfaceInteraction (const SurfaceInteraction&  surface) = default;
  SurfaceInteraction (      SurfaceInteraction&& surface) = default;

  auto operator = (const SurfaceInteraction&  surface) -> SurfaceInteraction& = default;
  auto operator = (      SurfaceInteraction&& surface) -> SurfaceInteraction& = default;


  /* SurfaceInteraction data */
public:
  Point2f  texcoord;

  Vector3f dpdx, dpdy;
  Float    dudx, dudy, dvdx, dvdy;

  Vector3f dpdu, dpdv;
  Normal3f dndu, dndv;

  struct
  {
    Normal3f normal;
    Vector3f dpdu, dpdv;
    Normal3f dndu, dndv;
  } shading;

  std::shared_ptr<Individual> primitive;

}; // class SurfaceInteraction
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _INTERACTION_H_
