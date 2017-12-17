#ifndef _SAMPLER_UTILS_H_
#define _SAMPLER_UTILS_H_
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
auto SampleUniformDisk            (const Sample2f& sample) -> Sample2f;
auto SampleConcentricDisk         (const Sample2f& sample) -> Sample2f;
auto SampleCosineHemisphere       (const Sample2f& sample) -> Vector3f;
auto SampleIsoscelesRightTriangle (const Sample2f& sample) -> Sample2f;
auto SampleUniformTriangle        (const Sample2f& sample) -> Point2f;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SAMPLER_UTILS_H_
