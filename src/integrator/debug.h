#ifndef _NORMAL_H_
#define _NORMAL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "sample_integrator.h"
#include "../scene/scene.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class DebugIntegrator : public SampleIntegrator
{
  /* DebugIntegrator constructors */
public:
  DebugIntegrator () = delete;
  DebugIntegrator
  (
    const std::shared_ptr<Camera>&  camera,
    const std::shared_ptr<Sampler>& sampler
  );


  /* DebugIntegrator destructor */
public:
  virtual ~DebugIntegrator () = default;


  /* DebugIntegrator public operators*/
public:
  DebugIntegrator (const DebugIntegrator&  debug) = default;
  DebugIntegrator (      DebugIntegrator&& debug) = default;

  auto operator = (const DebugIntegrator&  debug) -> DebugIntegrator& = default;
  auto operator = (      DebugIntegrator&& debug) -> DebugIntegrator& = default;


  /* DebugIntegrator public methods */
public:
  auto Render (const Scene& scene) const -> void override final;


  /* DebugIntegrator private methods */
private:
  auto RenderNormal   (const Scene& scene, const Ray& ray) const -> Spectrum;
  auto RenderTangent  (const Scene& scene, const Ray& ray) const -> Spectrum;
  auto RenderBinormal (const Scene& scene, const Ray& ray) const -> Spectrum;

}; // class DebugIntegrator
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _NORMAL_H_
