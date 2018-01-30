#ifndef _NIEPCE_H_
#define _NIEPCE_H_
/*
// ---------------------------------------------------------------------------
// STD includes
// ---------------------------------------------------------------------------
*/
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Global typedefs
// ---------------------------------------------------------------------------
*/
#ifdef NIEPCE_FLOAT_IS_DOUBLE
typedef double Float;
#else  
typedef float  Float;
#endif // NIEPCE_FLOAT_IS_DOUBLE

typedef uint32_t Index;

// ---------------------------------------------------------------------------
// Class forward declarations
// ---------------------------------------------------------------------------
template <typename T> class Point2;
template <typename T> class Point3;
template <typename T> class Point4;
template <typename T> class Vector2;
template <typename T> class Vector3;
template <typename T> class Vector4;
template <typename T> class Normal3;
template <typename T> class Matrix4x4;
template <typename T> class BoundingBox2;
template <typename T> class BoundingBox3;
class Ray;
class Interaction;
class SurfaceInteraction;
class ArenaAllocator;
class XorShift;
class Sampler;
class RandomSampler;
class Shape;
struct TriangleMesh;
class Triangle;
template <typename ReturnType> class Texture;
template <typename ReturnType> class ConstantTexure;
class Bxdf;
class BsdfRecord;
class LambertianBrdf;
class Material;
class Lambert;
class Light;
class AreaLight;
class Primitive;
class Individual;
class Aggreagate;
class StaticPrimitive;
class BVH;
class Scene;
class Integrator;
class SampleIntegrator;
class PathTracer;
class Camera;
class Object;
template <typename T> class Pixel;
template <typename T> class Image3;

typedef Point2<Float>       Point2f;
typedef Point2<int>         Point2i;
typedef Point2<uint32_t>    Point2u32i;
typedef Point3<Float>       Point3f;
typedef Point3<int>         Point3i;
typedef Point4<Float>       Point4f;
typedef Point4<int>         Point4i;
typedef Vector2<Float>      Vector2f;
typedef Vector2<int>        Vector2i;
typedef Vector3<Float>      Vector3f;
typedef Vector3<int>        Vector3i;
typedef Vector4<Float>      Vector4f;
typedef Vector4<int>        Vector4i;
typedef Normal3<Float>      Normal3f;
typedef Normal3<int>        Normal3i;
typedef Matrix4x4<Float>    Matrix4x4f;
typedef Matrix4x4<int>      Matrix4x4i;
typedef BoundingBox2<Float> Bounds2f;
typedef BoundingBox2<int>   Bounds2i;
typedef BoundingBox2<uint32_t> Bounds2u32i;
typedef BoundingBox3<Float> Bounds3f;
typedef BoundingBox3<int>   Bounds3i;
typedef Float    Sample1f;
typedef Point2f  Sample2f;
typedef Vector4f Spectrum;
typedef Image3 <Float> Image3f;
typedef Image3 <int>   Image3i;

typedef std::shared_ptr <Shape>      ShapePtr;
typedef std::shared_ptr <Material>   MaterialPtr;
typedef std::shared_ptr <Light>      LightPtr;
typedef std::shared_ptr <Individual> IndividualPtr;
template <typename T> using ImagePtr   = std::shared_ptr <Image3 <T>>;
template <typename T> using TexturePtr = std::shared_ptr <Texture <T>>;
typedef std::shared_ptr <Sampler>  SamplerPtr;
/*
// ---------------------------------------------------------------------------
// Render settings
// ---------------------------------------------------------------------------
*/
// TODO: Create RenderSetting struct or class
const unsigned int kWidth        = 960 / 4;
const unsigned int kHeight       = 540 / 4;
const unsigned int kSuperSamples = 8  / 2; // 8
const unsigned int kSamples      = 64 / 2; // 64
/*
// ---------------------------------------------------------------------------
// Global constant expression
// ---------------------------------------------------------------------------
*/
constexpr Float kInfinity = std::numeric_limits<Float>::infinity();
constexpr Float kFloatMax = std::numeric_limits<Float>::max();
constexpr Float kEpsilon  = std::numeric_limits<Float>::epsilon();
constexpr Float kPi       = 3.14159265358979323846;
constexpr Float kInvPi    = 0.31830988618379067153;
constexpr Float kSqrtPi   = 1.77245385090551602729;


// ---------------------------------------------------------------------------
// Global inline functions
// ---------------------------------------------------------------------------
inline auto Clamp(Float value, Float min = 0.f, Float max = 1.0) -> Float
{
  if (value < min) { return min; }
  if (value > max) { return max; }
  return value;
}

inline auto Lerp(Float t, Float s1, Float s2) -> Float
{
    return (1.0 - t) * s1 + t * s2;
}

template <typename T>
inline auto IsNaN(const T val) -> bool
{
  return std::isnan(val);
}

template<>
inline auto IsNaN(const int val) -> bool
{
  return false;
}

// Convert to radians from degree
inline auto ToRadians (Float degree) -> Float
{
  return (kPi / 180.f) * degree;
}

// Convert to degrees from radian
inline auto ToDegrees (Float radian) -> Float
{
  return (180.f / kPi) * radian;
}

// inline auto NearInteraction () -> Interaction;
// ---------------------------------------------------------------------------
// Solve quadratic equation $at^2 + bt + c = 0$
// Return boolean value whether solution were found or not.
// ---------------------------------------------------------------------------
inline auto SolveQuadratic(Float a, Float b, Float c, Float* t0, Float* t1) -> bool
{
  const Float discrim = b * b - 4 * a * c;
  if (discrim < 0.f) { return false;  }
  const Float sqrt_discrim = std::sqrt(discrim);

  Float q;
  if (b < 0.f) { q = -0.5f * (b - sqrt_discrim); }
  else         { q = -0.5f * (b + sqrt_discrim); }
  *t0 = q / a;
  *t1 = c / q;
  if (*t0 > *t1) { std::swap(*t0, *t1); }

  return true;
}

inline auto FloatToBits(float f) -> uint32_t
{
  uint32_t ui;
  std::memcpy(&ui, &f, sizeof(float));
  return ui;
}

inline auto BitsToFloat(uint32_t ui) -> float
{
  float f;
  std::memcpy(&f, &ui, sizeof(ui));
  return f;
}

inline auto FloatToBis(double d) -> uint64_t
{
  uint64_t ui;
  std::memcpy(&ui, &d, sizeof(double));
  return ui;
}

inline auto BitsToFloat(uint64_t ui) -> double
{
  double d;
  std::memcpy(&d, &ui, sizeof(ui));
  return d;
}

inline auto NextFloatUp(float v) -> float
{
  // Handle infinity and negative zero.
  if ( std::isinf(v) && v > 0.f ) { return v; }
  if (v == -0.f) { return v = 0.f;  }

  uint32_t ui = FloatToBits(v);
  if (v >= 0) { ++ui; }
  else        { --ui; }

  return BitsToFloat(ui);
}

inline auto NextFloatDown(float v) -> float
{
  // Handle infinity and posiive zero.
  if ( std::isinf(v) && v < 0.f ) { return v; }
  if (v == 0.f) { v = -0.f; }

  uint32_t ui = FloatToBits(v);
  if (v > 0.f) { --ui; }
  else         { ++ui; }

  return BitsToFloat(ui);
}

inline auto NextFloatUp(double v, int delta = 1) -> double
{
  // Handle infinity and negative zero.
  if ( std::isinf(v) && v > 0.f ) { return v; }
  if (v == -0.f) { return v = 0.f;  }

  uint64_t ui = FloatToBits(v);
  if (v >= 0) { ui += delta; }
  else        { ui -= delta; }

  return BitsToFloat(ui);
}

inline auto NextFloatDown(double v, int delta = 1) -> double
{
  // Handle infinity and posiive zero.
  if ( std::isinf(v) && v < 0.f ) { return v; }
  if (v == 0.f) { v = -0.f; }

  uint64_t ui = FloatToBits(v);
  if (v > 0.f) { ui -= delta; }
  else         { ui += delta; }

  return BitsToFloat(ui);
}

inline constexpr auto Gamma (int n ) -> Float
{
  return (n * kEpsilon) / (1 - n * kEpsilon);
}

inline auto GetFileExtension (const std::string& str) -> std::string
{
  int path_i = str.find_last_of("/") + 1;
  int ext_i  = str.find_last_of(".");
  std::string ext      = str.substr(ext_i, str.size() - ext_i);

  return ext;
}

inline auto GetFileName (const std::string& str) -> std::string
{
  auto pos = str.find_last_of("/") + 1;
  return str.substr (pos, str.size () - pos);
}

}; // namespace niepce

#endif // _NIEPCE_H_
