#include "sample_integrator.h"

namespace niepce
{

SampleIntegrator::SampleIntegrator
(
    const std::shared_ptr<Camera>&  camera,
    const std::shared_ptr<Sampler>& sampler
) :
    camera_  (camera),
    sampler_ (sampler)
{}

SampleIntegrator::~SampleIntegrator ()
{}

}  // namespace niepce
