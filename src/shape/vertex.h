#ifndef _VERTEX_H_
#define _VERTEX_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct Vertex
{
  /* Vertex constructors */
  Vertex () :
    position (nullptr),
    normal   (nullptr),
    texcoord (nullptr)
  {}
  Vertex (const std::shared_ptr<Point3f>& p) :
    position (p),
    normal   (nullptr),
    texcoord (nullptr)
  {}
  Vertex
  (
   const std::shared_ptr<Point3f>&  p,
   const std::shared_ptr<Normal3f>& n,
   const std::shared_ptr<Point2f>&  t
  ) :
    position (p),
    normal   (n),
    texcoord (t)
  {}


  /* Vertex destructor */
  virtual ~Vertex ()
  {};


  /* Vertex operators */
  Vertex (const Vertex&  tm) = default;
  Vertex (      Vertex&& tm) = default;

  auto operator = (const Vertex&  tm) -> Vertex& = default;
  auto operator = (      Vertex&& tm) -> Vertex& = default;


  /* Vertex data */
  std::shared_ptr<Point3f>  position;
  std::shared_ptr<Normal3f> normal;
  std::shared_ptr<Point2f>  texcoord;
};
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _VERTEX_H_
