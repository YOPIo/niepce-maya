#ifndef _CAMERA_H_
#define _CAMERA_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../sampler/sampler_utils.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Camera
{
  /* Camera constructors */
 public:
  Camera ()
  {};

  Camera
  (
    const Point3f&  position,
    const Vector3f& direction,
    const Vector3f& up
  )
  {
      Vector3f u, v, w;
      Float theta = 35 * kPi / 180.0;
      Float half_height = std::tan (theta / 2);
      Float half_width  = 16.0 / 9.0 * half_height;

      origin_ = position;
      w = Normalize (direction);
      u = Normalize (Cross (up, w));
      v = Cross (w, u);

      lower_left_corner_ = Point3f (-half_width, -half_height, -1.0);
      lower_left_corner_ = Point3f (origin_ + -1.0 * u * half_width  +
          -1.0 * v * half_height +
          -1.0 * w);
      horizontal_ = 2.0 * half_width  * u;
      vertical_   = 2.0 * half_height * v;    
  }

  Camera
  (
      const Point3f&  position,
      const Point3f&  lookat,
      const Vector3f& vup,
      Float           vfov,
      Float           aspect
  )
  {
    Vector3f u, v, w;
    Float theta = vfov * kPi / 180.0;
    Float half_height = std::tan (theta / 2);
    Float half_width  = aspect * half_height;

    origin_ = position;
    w = Normalize (position - lookat);
    u = Normalize (Cross (vup, w));
    v = Cross (w, u);

    lower_left_corner_ = Point3f (-half_width, -half_height, -1.0);
    lower_left_corner_ = Point3f (origin_ + -1.0 * u * half_width  +
                                            -1.0 * v * half_height +
                                            -1.0 * w);
    horizontal_ = 2.0 * half_width  * u;
    vertical_   = 2.0 * half_height * v;
  };


  /* Camera destructor */
 public:
  virtual ~Camera ()
  {};


  /* Camera public operators*/
 public:
  Camera (const Camera&  camera) = default;
  Camera (      Camera&& camera) = default;

  auto operator = (const Camera&  camera) -> Camera& = default;
  auto operator = (      Camera&& camera) -> Camera& = default;


  /* Camera public methods */
 public:
  virtual auto GenerateRay (Float s, Float t, const Sample2f& sample) -> Ray
  {
    const Point2f  rd = SampleConcentricDisk (sample);
    return Ray (origin_, lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_);
  }


  /* Camera private data */
 public:
  Point3f  origin_;
  Point3f  lower_left_corner_;
  Vector3f horizontal_;
  Vector3f vertical_;


}; // class Camera
/*
// ---------------------------------------------------------------------------
*/
class ThinCamera : public Camera
{
  /* ThinCamera constructors */
 public:
  ThinCamera ();
  ThinCamera
  (
      const Point3f&  position,
      const Point3f&  lookat,
      const Vector3f& vup,
      Float           vfov,
      Float           aspect,
      Float           aperture,
      Float           focus_dist
  ) :
      Camera ()
  {
    lens_radius_ = aperture / 2.0;

    Float theta = vfov * kPi / 180.0;
    Float half_height = std::tan (theta / 2);
    Float half_width  = aspect * half_height;

    origin_ = position;
    w = Normalize (position - lookat);
    u = Normalize (Cross (vup, w));
    v = Cross (w, u);

    lower_left_corner_ = Point3f (-half_width, -half_height, -1.0);
    lower_left_corner_ = Point3f (origin_ + -focus_dist * u * half_width  +
                                            -focus_dist * v * half_height +
                                            -focus_dist * w);
    horizontal_ = 2.0 * half_width  * u * focus_dist;
    vertical_   = 2.0 * half_height * v * focus_dist;
  };


  /* ThinCamera destructor */
 public:
  virtual ~ThinCamera ()
  {};


  /* ThinCamera public operators*/
 public:
  ThinCamera (const ThinCamera&  camera) = default;
  ThinCamera (      ThinCamera&& camera) = default;

  auto operator = (const ThinCamera&  camera) -> ThinCamera& = default;
  auto operator = (      ThinCamera&& camera) -> ThinCamera& = default;


  /* ThinCamera public methods */
 public:
  auto GenerateRay (Float s, Float t, const Sample2f& sample) -> Ray override
  {
    const Point2f  rd = SampleConcentricDisk (sample) * lens_radius_;
    const Vector3f offset = u * rd.x + v * rd.y;

    return Ray (origin_ + offset, lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_ - offset);
  }


  /* ThinCamera private data */
 private:
  Vector3f u, v, w;
  Float    lens_radius_;

}; // class ThinCamera
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _CAMERA_H_

/*
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../sampler/sampler.h"

namespace niepce
{

class Camera
{
public:
  Camera() {}
  Camera (const Point3f&  p,
          const Point3f&  at,
          const Vector3f& u) :
    position_  (p),
    direction_ (Normalize (at - p)),
    up_        (Normalize (u))
  {
    // Distance, camera position to sensor
    const Float distance    = 25;
    const Float sensor_size = 30;

    const Vector3f sensor_x  = Normalize (Cross (direction_, up_)) * sensor_size *
      (static_cast<Float>(kWidth)) / static_cast<Float>(kHeight);
    const Vector3f sensor_y  = Normalize (Cross (sensor_x, direction_)) * sensor_size;
    const Point3f  center    = position_ + direction_ * distance;

    sensor = Sensor (sensor_x, sensor_y, center);
  }
  virtual ~Camera()
  {}

  Camera (const Camera& camera) = default;
  Camera (Camera&& camera)      = default;


  auto operator = (const Camera& camera) -> Camera& = default;
  auto operator = (Camera&& camera)      -> Camera& = default;


public:
  auto GenerateRayDof
  (
   unsigned int    x,
   unsigned int    y,
   unsigned int    sx,
   unsigned int    sy,
   const Sample2f& sample0,
   const Sample2f& sample1
  )
  -> Ray
  {
    const Float lens_radius    = 0.1;
    const Float focal_distance = 0.1;

    const Float r1 = 2.0 * sample0[0], dx = r1 < 1.0 ? std::sqrt (r1) - 1.0 : 1.0 - std::sqrt (2.0 - r1);
    const Float r2 = 2.0 * sample0[1], dy = r2 < 1.0 ? std::sqrt (r2) - 1.0 : 1.0 - std::sqrt (2.0 - r2);

    Vector3f dir = sensor.x * (((sx + 0.5 + dx) / 2.0 + x) / kWidth - 0.5) +
                   sensor.y * (((sy + 0.5 + dy) / 2.0 + y) / kHeight- 0.5) + direction_;

    // レイがレンズにあたって屈折することでDOFが発生する。そのシミュレーション。
    Ray ray (position_ + dir * 0.2, Normalize(dir));

    const Sample2f lens_position = SampleConcentricDisk (sample1) * lens_radius;

    const Float   ft      = std::fabs (focal_distance / Dot (ray.direction, direction_));
    const Point3f p_focus = ray (ft);

    ray.origin    = ray.origin + Vector3f (lens_position.x, lens_position.y, 0.f);
    ray.direction = Normalize(p_focus - ray.origin);

    return ray;
  }
  auto GenerateRay
  (
   unsigned int    x,
   unsigned int    y,
   unsigned int    sx,
   unsigned int    sy
  )
  -> Ray
  {
    const Float rate = 0.5;
    const Float r1 = static_cast<Float>(sx) * rate + rate / 2.0;
    const Float r2 = static_cast<Float>(sy) * rate + rate / 2.0;

    // Position on the sensor
    const Point3f screen_position = sensor.center +
      sensor.x * (Float)((r1 + x) / static_cast<Float>(kWidth)  - 0.5) +
      sensor.y * (Float)((r2 + y) / static_cast<Float>(kHeight) - 0.5);

    const Vector3f ray_dir = Normalize(screen_position - position_);
    return  Ray(position_, ray_dir);
  }

  // ---------------------------------------------------------------------------
  // Camera private data
  // ---------------------------------------------------------------------------
private:
  struct Sensor
  {
    Sensor() = default;
    Sensor(const Vector3f& x_,
           const Vector3f& y_,
           const Point3f&  center_) :
      x(x_), y(y_), center(center_)
    {}
    ~Sensor()
    {}

    Vector3f x;
    Vector3f y;
    Point3f  center;
  } sensor;

  Point3f  position_;
  Vector3f direction_;
  Vector3f up_;
};

}  // namespace niepce

#endif // _CAMERA_H_
*/
