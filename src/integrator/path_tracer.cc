#include "path_tracer.h"
#include "../filter/filter.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
PathTracer::PathTracer
(
    const std::shared_ptr<Camera>&  camera,
    const std::shared_ptr<Sampler>& sampler,
    std::uint8_t max_depths
) :
    SampleIntegrator (camera, sampler),
    kMaxDepths_      (max_depths)
{}
/*x
// ---------------------------------------------------------------------------
*/
PathTracer::~PathTracer ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Render (const Scene& scene) const -> void
{
  // Create image buffer
  ImagePtr <Float> image (CreateImage3 <Float> (kWidth, kHeight));

#ifdef _OPENMP
  std::cout << "Avairable OpenMP num threads: " << omp_get_num_procs () << std::endl;
#endif

  for (int y = 0; y < kHeight; y ++)
  {
    std::cerr << "Rendering (y = " << y << ") " << (100.0 * y / (kHeight - 1)) << "%" << std::endl;
    // OpenMP
#ifdef _OPENMP
#pragma omp parallel for schedule(dynamic, 1)
#endif
    for (int x = 0; x < kWidth; x ++)
    {
      const int image_index = (kHeight - y - 1) * kWidth + x;
      ArenaAllocator mem;
      // Super samples
      for (int sy = 0; sy < kSuperSamples; sy ++)
      {
        for (int sx = 0; sx < kSuperSamples; sx ++)
        {
          Pixel <Float> p;
          Spectrum accumulated_radiance = Spectrum::Zero ();
          for (int s = 0; s < kSamples; s ++)
          {
            // const Ray ray = camera_->GenerateRay (x, y, sx, sy);
            const Sample2f sample0 = SampleConcentricDisk (sampler_->Get2D ());
            const Sample2f sample1 = SampleConcentricDisk (sampler_->Get2D ());
            const Ray ray = camera_->GenerateRay ((Float(x + (Float)sx / kSuperSamples) - 0.5) / (Float)kWidth,
                                                  (Float(y + (Float)sy / kSuperSamples) - 0.5) / (Float)kHeight,
                                                  sampler_->Get2D ());

            accumulated_radiance = accumulated_radiance +
                Radiance(scene, ray, &mem) / (Float)kSamples / (Float)(kSuperSamples * kSuperSamples);
            p = Pixel <Float> (accumulated_radiance.r, accumulated_radiance.g, accumulated_radiance.b);
          }
          (*image) (x, kHeight - y - 1) = (*image) (x, kHeight - y - 1) + p;
        }
      }
    } // End openmp
  }

  WriteImage("test.png", image);
  SaveAs ("final_without_filter.png", *image);
  auto filtered = NonLocalMeansFilter (image, 0.2, 0.2);
  SaveAs ("final_with_filter.png", *filtered);

  return ;
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::Radiance
(
    const Scene&    scene,
    const Ray&      first_ray,
    ArenaAllocator* mem
)
const -> Spectrum
{
  Spectrum l (Spectrum::Zero ());
  Spectrum f (Spectrum::One ());

  Ray ray (first_ray);

  for (int path = 0; ; ++path)
  {
    // Intersection test
    SurfaceInteraction si;
    const bool inter = scene.IsIntersect (ray, &si);
    if (!inter)
    {
      // No intersection
      if (scene.HasIbl ())
      {
        l += f * scene.SampleIbl (ray);
      }
      break;
    }

    // Get BSDF or light
    const MaterialPtr material = si.primitive->GetMaterial ();
    const LightPtr    light    = si.primitive->GetAreaLight ();

    // Intersection point has emission
    if (light != nullptr)
    {
      // Add contribution
      l += f * light->Emission (ray);
      break;
    }

    // Sample incident direction
    // Compute the PDF
    Vector3f incident;
    Float    pdf (0);
    BsdfType sampled_type (BsdfType::kNull);

    // Allocate BSDF
    const Bsdf*    bsdf       = material->AllocateBsdf (si, mem);
    const Spectrum bsdf_value = bsdf->EvaluateAndSample (si.outgoing,
                                                         &incident,
                                                         sampler_->Get2D (),
                                                         &pdf,
                                                         BsdfType::kAll,
                                                         &sampled_type);

    // Handle case
    if (std::fabs (pdf) < kEpsilon)
    {
      std::cerr << "PDF: 0" << std::endl;
      break;
    }

    // Update weight
    const Float cos_t (std::abs (Dot (si.outgoing, si.normal)));
    f *= (bsdf_value *  cos_t / pdf);

    // Generate next ray
    ray = Ray (si.position, incident);

    // Terminate with russian roulette
    Float q (std::max ({l.x, l.y, l.z}));
    if (path >= kMaxDepths_)
    {
      if (sampler_->Get1D () > q)
      {
        break;
      }
    }
    else
    {
      q = 1.0;
    }
    f *= 1.0 / q;
  } // End for loop

  return l;
}
/*
// ---------------------------------------------------------------------------
*/
auto PathTracer::RussianRoulette (Float threshold, int depth) const -> Float
{
  if (depth > kMaxDepths_)
  {
    if (sampler_->Get1D () > threshold)
    {
      // break
      return -1.0;
    }
    return threshold;
  }
  return 1.0;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
