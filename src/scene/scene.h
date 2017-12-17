#ifndef _SCENE_H_
#define _SCENE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../core/interaction.h"
#include "../texture/texture.h"
#include "../texture/constant_texture.h"
#include "../texture/image_map.h"
#include "../bxdf/bxdf.h"
#include "../bxdf/lambert.h"
#include "../material/material.h"
#include "../material/matte.h"
#include "../shape/vertex.h"
#include "../shape/shape.h"
#include "../shape/triangle.h"
#include "../shape/sphere.h"
#include "../light/light.h"
#include "../light/area.h"
#include "../light/ibl.h"
#include "../accelerator/bvh.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
enum AcceleratorType
{
  kNone,
  kSah,
  kBvh
};
/*
// ---------------------------------------------------------------------------
*/
class Scene
{
  /* Scene constructors */
public:
  Scene () = default;
  Scene
  (
   const std::vector <IndividualPtr>& aggregate,
   const AcceleratorType& type = AcceleratorType::kNone
  );


  /* Scene public destructor */
  virtual ~Scene () = default;


  /* Scene public operators*/
public:
  Scene (const Scene&  scene) = default;
  Scene (      Scene&& scene) = default;

  auto operator = (const Scene&  scene) -> Scene& = default;
  auto operator = (      Scene&& scene) -> Scene& = default;


  /* Scene public methods */
public:
  // (Re)Construct a SAH BVH or Kdtree
  // If primitives are given, current scene are going to be destroyed and
  // replace
  auto Construct
  (
   const AcceleratorType& type,
   const std::vector <IndividualPtr>& primitives
  )
  -> void;

  // Ray-Shape intersection test, return primitive pointer
  auto IsIntersect
  (
   const Ray&          ray,
   SurfaceInteraction* interaction
  )
  const -> bool;

  // Load IBL image
  // If HDR image have already loaded, it will be freed
  auto LoadIbl   (const std::string& filepath) -> void;
  auto HasIbl    () const -> bool;
  auto SampleIbl (const Ray& ray) const -> Spectrum;

  /* Scene private data */
private:
  // Primitives
  std::shared_ptr<Primitive> root_;

  // Store point/area light sources
  std::vector <LightPtr> lights_;

  // Store only infinite lights
  std::shared_ptr<Ibl> ibl_;

  AcceleratorType accel_type_;
}; // class Scene
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SCENE_H_
