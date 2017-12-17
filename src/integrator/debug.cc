#include "debug.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
DebugIntegrator::DebugIntegrator
(
 const std::shared_ptr<Camera>&  camera,
 const std::shared_ptr<Sampler>& sampler
) :
  SampleIntegrator (camera, sampler)
{}
/*
// ---------------------------------------------------------------------------
*/
auto DebugIntegrator::Render (const Scene &scene) const -> void
{
  std::unique_ptr<Spectrum[]> normal   (new Spectrum [kHeight * kWidth]);
  std::unique_ptr<Spectrum[]> tangent  (new Spectrum [kHeight * kWidth]);
  std::unique_ptr<Spectrum[]> binormal (new Spectrum [kHeight * kWidth]);

  for (int y = 0; y < kHeight; ++y)
  {
    for (int x = 0; x < kWidth; ++x)
    {
      const int idx = (kHeight - y - 1) * kWidth + x;
      const Ray ray
        (camera_->GenerateRay ((Float(x) - 0.5) / (Float)kWidth,
                               (Float(y) - 0.5) / (Float)kHeight,
                               sampler_->Get2D ()));
      normal[idx]   = RenderNormal (scene, ray);
      tangent[idx]  = RenderTangent (scene, ray);
      binormal[idx] = RenderBinormal (scene, ray);
    }
  }

  // Save a image as "image.png"
  unsigned char* data = new unsigned char [kWidth * kHeight * 4];
  auto hdr_to_int = [](Float v) -> int
  {
    if (v < 0.0) { v = 0; }
    if (v > 1.0) { v = 1; }
    if (std::isnan(v))
    {
      std::cout << "NaN detected" << std::endl;
      v = 0;
    }
    return std::pow (v, 1.0 / 2.2) * 255.0 + 0.5;
  };

  // Convert to stb image format
  for (int i = 0; i < kWidth * kHeight; i++)
  {
    data[3 * i + 0] = hdr_to_int (normal[i].x);
    data[3 * i + 1] = hdr_to_int (normal[i].y);
    data[3 * i + 2] = hdr_to_int (normal[i].z);
  }
  stbi_write_png("normal.png", kWidth, kHeight, 3, (void*)data, kWidth * 3);

  // Convert to stb image format
  for (int i = 0; i < kWidth * kHeight; i++)
  {
    data[3 * i + 0] = hdr_to_int (tangent[i].x);
    data[3 * i + 1] = hdr_to_int (tangent[i].y);
    data[3 * i + 2] = hdr_to_int (tangent[i].z);
  }
  stbi_write_png("tangent.png", kWidth, kHeight, 3, (void*)data, kWidth * 3);

  // Convert to stb image format
  for (int i = 0; i < kWidth * kHeight; i++)
  {
    data[3 * i + 0] = hdr_to_int (binormal[i].x);
    data[3 * i + 1] = hdr_to_int (binormal[i].y);
    data[3 * i + 2] = hdr_to_int (binormal[i].z);
  }
  stbi_write_png("binormal.png", kWidth, kHeight, 3, (void*)data, kWidth * 3);

  delete [] data;

  return ;
}
/*
// ---------------------------------------------------------------------------
*/
auto DebugIntegrator::RenderNormal (const Scene& scene, const Ray& ray) const -> Spectrum
{
  SurfaceInteraction si;
  const bool isect (scene.IsIntersect (ray, &si));
  if (isect)
  {
    Normal3f n (si.normal);
    Spectrum color (n.r, n.g, n.b, 0.0);
    return 0.5 * (color + Spectrum::One ());
  }
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto DebugIntegrator::RenderTangent  (const Scene& scene, const Ray& ray) const
  -> Spectrum
{
  SurfaceInteraction si;
  const bool isect (scene.IsIntersect (ray, &si));
  if (isect)
  {
    Vector3f t, b;
    OrthoNormalBasis(si.normal, &t, &b);

    // Vector3f t (Normalize (si.dpdu));

    return 0.5 * (Spectrum (t.x, t.y, t.z, 0.0) + Spectrum::One ());
  }
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto DebugIntegrator::RenderBinormal (const Scene& scene, const Ray& ray) const
  -> Spectrum
{
  SurfaceInteraction si;
  const bool isect (scene.IsIntersect (ray, &si));
  if (isect)
  {
    Normal3f n (si.normal);
    Vector3f t, b;
    OrthoNormalBasis(si.normal, &t, &b);

    // Vector3f t (Normalize (si.dpdu));
    // Vector3f b (Cross (n, t));

    Spectrum color (b.r, b.g, b.b, 0.0);
    return 0.5 * (color + Spectrum::One ());
  }
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
