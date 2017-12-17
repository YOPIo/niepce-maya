#ifndef _PATH_TRACER_H_
#define _PATH_TRACER_H_
/*
// ---------------------------------------------------------------------------
*/
#ifdef _OPENMP
#include <omp.h>
#endif
/*
// ---------------------------------------------------------------------------
*/
#include "sample_integrator.h"
#include "../scene/scene.h"
#include "../memory/arena_allocator.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class PathTracer : public SampleIntegrator
{
  /* PathTracer public constructors */
public:
  PathTracer () = delete;
  PathTracer
  (
      const std::shared_ptr<Camera>&  camera,
      const std::shared_ptr<Sampler>& sampler,
      std::uint8_t max_depths
  );

  /* PathTracer public destructor */
  virtual ~PathTracer ();


  /* PathTracer public operators*/
public:
  PathTracer (const PathTracer&  render) = default;
  PathTracer (      PathTracer&& render) = default;

  auto operator = (const PathTracer&  render) -> PathTracer& = default;
  auto operator = (      PathTracer&& render) -> PathTracer& = default;

  /* PathTracer public methods */
public:
  auto Render (const Scene& scene) const -> void override;


  /* Pathtracer private methods */
 private:
  auto Radiance
  (
      const Scene&    scene,
      const Ray&      ray,
      ArenaAllocator* mem
  )
  const -> Spectrum;

  auto RussianRoulette (Float threshold, int depth) const -> Float;


  /* PathTracer private data */
private:
  // The number of maximum trials that try to find possible paths
  const std::uint8_t kMaxDepths_;

}; // class PathTracer
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _PATH_TRACER_H_
