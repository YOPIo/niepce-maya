#include "scene_creator.h"
#include "../core/geometry.h"
#include "../camera/camera.h"
#include "../shape/triangle.h"
#include "../shape/sphere.h"
#include "../texture/constant_texture.h"
#include "../material/matte.h"
#include "../primitive/individual.h"
#include "../light/area.h"
#include "../scene/scene.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto CreateCornellBox ()
  -> std::pair <std::shared_ptr <Camera>, std::shared_ptr <Scene>>
{
  // Positions
  std::vector <Point3f> positions (28);
  // Cornell box
  positions[ 0] = Point3f (-1.0,   0.0, -1.0);
  positions[ 1] = Point3f (-1.0,   0.0,  1.0);
  positions[ 2] = Point3f ( 1.0,   0.0, -1.0);
  positions[ 3] = Point3f ( 1.0,   0.0,  1.0);
  positions[ 4] = Point3f (-1.0,   2.0, -1.0);
  positions[ 5] = Point3f (-1.0,   2.0,  1.0);
  positions[ 6] = Point3f ( 1.0,   2.0, -1.0);
  positions[ 7] = Point3f ( 1.0,   2.0,  1.0);
  positions[ 8] = Point3f (-0.5, 1.999, -0.5);
  positions[ 9] = Point3f (-0.5, 1.999,  0.5);
  positions[10] = Point3f ( 0.5, 1.999, -0.5);
  positions[11] = Point3f ( 0.5, 1.999,  0.5);
  // Short block (right side)
  positions[12] = Point3f ( 0.13, 0.0, 0.00);
  positions[13] = Point3f (-0.05, 0.0, 0.57);
  positions[14] = Point3f ( 0.70, 0.0, 0.17);
  positions[15] = Point3f ( 0.53, 0.0, 0.75);
  positions[16] = Point3f ( 0.13, 0.6, 0.00);
  positions[17] = Point3f (-0.05, 0.6, 0.57);
  positions[18] = Point3f ( 0.70, 0.6, 0.17);
  positions[19] = Point3f ( 0.53, 0.6, 0.75);
  // Tall block (left side)
  positions[20] = Point3f (-0.14, 0.0, -0.67);
  positions[21] = Point3f (-0.71, 0.0, -0.49);
  positions[22] = Point3f ( 0.04, 0.0, -0.09);
  positions[23] = Point3f (-0.53, 0.0,  0.09);
  positions[24] = Point3f (-0.14, 1.2, -0.67);
  positions[25] = Point3f (-0.71, 1.2, -0.49);
  positions[26] = Point3f ( 0.04, 1.2, -0.09);
  positions[27] = Point3f (-0.53, 1.2,  0.09);


  // Mesh construction
  const std::shared_ptr<TriangleMesh> mesh (CreateTriangleMesh (12, positions));


  // Texture construction
  const TexturePtr <Spectrum> white_t
    (CreateConstantTexture <Spectrum> (Spectrum (0.75, 0.75, 0.75, 1.0)));
  const TexturePtr <Spectrum> red_t
    (CreateConstantTexture <Spectrum> (Spectrum (0.75, 0.3, 0.3, 1.0)));
  const TexturePtr <Spectrum> green_t
    (CreateConstantTexture <Spectrum> (Spectrum (0.3, 0.75, 0.3, 1.0)));


  // Shape construction
  std::vector <ShapePtr> shapes (32);
  {
    // Cornell box
    // Floor
    shapes[0] = CreateTriangle (mesh, {0, 1, 2});
    shapes[1] = CreateTriangle (mesh, {1, 3, 2});
    // Ceiling
    shapes[2] = CreateTriangle (mesh, {4, 6, 7});
    shapes[3] = CreateTriangle (mesh, {4, 7, 5});
    // Back wall
    shapes[4] = CreateTriangle (mesh, {0, 2, 4});
    shapes[5] = CreateTriangle (mesh, {2, 6, 4});
    // Right wall
    shapes[6] = CreateTriangle (mesh, {2, 3, 7});
    shapes[7] = CreateTriangle (mesh, {2, 7, 6});
    // Left wall
    shapes[8] = CreateTriangle (mesh, {0, 4, 1});
    shapes[9] = CreateTriangle (mesh, {1, 4, 5});
    // Light
    shapes[10] = CreateTriangle (mesh, {8, 11,  9});
    shapes[11] = CreateTriangle (mesh, {8, 10, 11});
  }
  {
    // Short block (right side)
    // Top
    shapes[12] = CreateTriangle (mesh, {16, 17, 19});
    shapes[13] = CreateTriangle (mesh, {16, 19, 18});
    // Left
    shapes[14] = CreateTriangle (mesh, {12, 13, 16});
    shapes[15] = CreateTriangle (mesh, {13, 17, 16});
    // Right
    shapes[16] = CreateTriangle (mesh, {14, 18, 15});
    shapes[17] = CreateTriangle (mesh, {15, 18, 19});
    // Front
    shapes[18] = CreateTriangle (mesh, {13, 15, 19});
    shapes[19] = CreateTriangle (mesh, {13, 19, 17});
    // Back
    shapes[20] = CreateTriangle (mesh, {12, 18, 14});
    shapes[21] = CreateTriangle (mesh, {12, 16, 18});
  }
  {
    // Tall block (left side)
    // Top
    shapes[22] = CreateTriangle (mesh, {24, 27, 26});
    shapes[23] = CreateTriangle (mesh, {24, 25, 27});
    // Left
    shapes[24] = CreateTriangle (mesh, {20, 21, 24});
    shapes[25] = CreateTriangle (mesh, {21, 25, 24});
    // Right
    shapes[26] = CreateTriangle (mesh, {22, 26, 23});
    shapes[27] = CreateTriangle (mesh, {23, 26, 27});
    // Front
    shapes[28] = CreateTriangle (mesh, {23, 27, 25});
    shapes[29] = CreateTriangle (mesh, {23, 25, 21});
    // Back
    shapes[30] = CreateTriangle (mesh, {22, 24, 26});
    shapes[31] = CreateTriangle (mesh, {20, 24, 22});
  }


  // Material construction
  const MaterialPtr white_m (CreateMatte (white_t));
  const MaterialPtr red_m   (CreateMatte (red_t));
  const MaterialPtr green_m (CreateMatte (green_t));


  // Light construction
  const LightPtr light (CreateAreaLight (Spectrum (6.0)));


  // Primitive construction
  std::vector <IndividualPtr> individuals (32);
  {
    // Cornell box
    individuals[ 0] = CreateIndividual (shapes[ 0], white_m, nullptr);
    individuals[ 1] = CreateIndividual (shapes[ 1], white_m, nullptr);
    individuals[ 2] = CreateIndividual (shapes[ 2], white_m, nullptr);
    individuals[ 3] = CreateIndividual (shapes[ 3], white_m, nullptr);
    individuals[ 4] = CreateIndividual (shapes[ 4], white_m, nullptr);
    individuals[ 5] = CreateIndividual (shapes[ 5], white_m, nullptr);
    individuals[ 6] = CreateIndividual (shapes[ 6],   red_m, nullptr);
    individuals[ 7] = CreateIndividual (shapes[ 7],   red_m, nullptr);
    individuals[ 8] = CreateIndividual (shapes[ 8], green_m, nullptr);
    individuals[ 9] = CreateIndividual (shapes[ 9], green_m, nullptr);
    individuals[10] = CreateIndividual (shapes[10], nullptr,   light);
    individuals[11] = CreateIndividual (shapes[11], nullptr,   light);
  }
  {
    // Short block
    for (int i = 12; i < 22; ++i)
    {
      individuals[i] = CreateIndividual (shapes[i], white_m, nullptr);
    }
  }
  {
    // Tall block
    for (int i = 22; i < 32; ++i)
    {
      individuals[i] = CreateIndividual (shapes[i], white_m, nullptr);
    }
  }


  // Scene construction
  std::shared_ptr <Scene> scene
    (std::make_shared <Scene> (individuals));

  // Define rendering image resolution
  const unsigned width  (360);
  const unsigned height (360);

  // Camera construction
  const Point3f  position (Point3f  (0.0, 1.0, 3.2));
  const Point3f  lookat   (Point3f  (0.0, 1.0, 0.0));
  const Vector3f up       (Vector3f (0.0, 1.0, 0.0));
  const Float    fov      (45.0);

  std::shared_ptr <Camera> camera (std::make_shared <Camera> (position,
                                                              lookat,
                                                              up,
                                                              fov,
                                                              (Float)kWidth / (Float)kHeight));

  // scene->LoadIbl ("../../assets/IBL.hdr");
  return std::make_pair (camera, scene);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateSphereScene ()
  -> std::pair <std::shared_ptr <Camera>, std::shared_ptr <Scene>>
{
  // Shape construction
  std::vector <ShapePtr> spheres (3);
  spheres[0] = CreateSphere (1.0, Point3f (0,    1, 0));
  spheres[1] = CreateSphere (1e8, Point3f (0, -1e8, 0));
  spheres[2] = CreateSphere (  2, Point3f (8,    8, 8));

  // texture construction
  TexturePtr <Spectrum> white (CreateConstantTexture (Spectrum (0.75)));

  // Material construction
  MaterialPtr material (CreateMatte (white));

  // Light construction
  LightPtr light (CreateAreaLight (Spectrum (8.0)));

  // Individual primitive construction
  std::vector <IndividualPtr> individuals (3);
  individuals[0] = CreateIndividual(spheres[0], material, nullptr);
  individuals[1] = CreateIndividual(spheres[1], material, nullptr);
  individuals[2] = CreateIndividual(spheres[2],  nullptr,   light);

  // Scene construction
  const std::shared_ptr <Scene> scene (std::make_shared <Scene> (individuals));


  // Camera construction
  const Point3f  position (Point3f  (0.0, 3.0, 8.0));
  const Point3f  lookat   (Point3f  (0.0, 1.0, 0.0));
  const Vector3f up       (Vector3f (0.0, 1.0, 0.0));
  const Float    fov      (40.0);

  std::shared_ptr <Camera> camera (std::make_shared <Camera> (position,
                                                              lookat,
                                                              up,
                                                              fov,
                                                              (Float)kWidth / (Float)kHeight));
  // scene->LoadIbl ("../../assets/IBL.hdr");
  return std::make_pair (camera, scene);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
