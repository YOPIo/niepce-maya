#ifndef _SAMPLE_INTEGRATOR_H_
#define _SAMPLE_INTEGRATOR_H_
/*
// ---------------------------------------------------------------------------
*/
#include "integrator.h"
#include "../core/interaction.h"
#include "../sampler/sampler.h"
#include "../camera/camera.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
// ---------------------------------------------------------------------------
// Interface of integrator
// SampleIntegrator store a pointer to a Sampler class
// ---------------------------------------------------------------------------
class SampleIntegrator : public Integrator
{
  /* SampleIntegrator public constructors */
 public:
  SampleIntegrator () = delete;
  SampleIntegrator
  (
      const std::shared_ptr<Camera>&  camera,
      const std::shared_ptr<Sampler>& sampler
  );

  /* SampleIntegrator public destructor */
  virtual ~SampleIntegrator ();

  /* SampleIntegrator operators*/
 public:
  SampleIntegrator (const SampleIntegrator&  integrator) = default;
  SampleIntegrator (      SampleIntegrator&& integrator) = default;

  auto operator = (const SampleIntegrator&  integrator) -> SampleIntegrator& = default;
  auto operator = (      SampleIntegrator&& integrator) -> SampleIntegrator& = default;


  /* SamplerIntegrator interface methods */
 public:
  // Render a scene, then store a result to Film in Camera class
  virtual auto Render (const Scene& scene) const -> void override = 0;


  /* SampleIntegrator prtected data */
 protected:
  std::shared_ptr<Camera>  camera_;
  std::shared_ptr<Sampler> sampler_;

}; // class SampleIntegrator
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SAMPLE_INTEGRATOR_H_
