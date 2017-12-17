#include "loader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../ext/tiny_obj_loader.h"

namespace niepce
{

auto LoadObj (const std::string& filepath) -> UnorderedScene
{
  UnorderedScene res;

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t>    shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err;

  const bool result = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filepath.c_str ());
  if (!result || !err.empty ())
  {
    // Error
    return res;
  }

  // ---------------------------------------------------------------------------
  // Generate positions, normals and texcoords
  // ---------------------------------------------------------------------------

  const std::size_t num_vertices = attrib.vertices.size ();
  std::cout << "Number of vertices : " << num_vertices << std::endl;

  std::vector<std::shared_ptr<Point3f>> positions (num_vertices / 3, nullptr);
  for (std::size_t i = 0; i < num_vertices / 3; ++i)
  {
    positions[i].reset (new Point3f (attrib.vertices[3 * i + 0],
                                     attrib.vertices[3 * i + 1],
                                     attrib.vertices[3 * i + 2]));
  }

  // Get the number of normals and copy them
  const std::size_t num_normals = attrib.normals.size ();
  std::cout << "Number of normals : " << num_normals << std::endl;

  std::vector<std::shared_ptr<Normal3f>> normals (num_normals / 3, nullptr);
  for (std::size_t i = 0; i < num_normals / 3; ++i)
  {
    normals[i].reset (new Normal3f (attrib.normals[3 * i + 0],
                                    attrib.normals[3 * i + 1],
                                    attrib.normals[3 * i + 2]));
  }

  // Get the number of texcoord and copy them
  const std::size_t num_texcoords = attrib.texcoords.size ();
  std::cout << "Number of texcoords : " << num_texcoords << std::endl;

  std::vector<std::shared_ptr<Point2f>> texcoords (num_texcoords / 2, nullptr);
  for (std::size_t i = 0; i < num_texcoords / 2; ++i)
  {
    texcoords[i].reset (new Point2f (attrib.texcoords[2 * i + 0],
                                     attrib.texcoords[2 * i + 1]));
  }
  // ---------------------------------------------------------------------------
  // Build faces
  // ---------------------------------------------------------------------------
  // Loop over shapes

  // Texture tests
  std::shared_ptr<Texture<Spectrum>> tex (new ImageMapTexture ("./assets/eye_textures/10.png"));
  const std::shared_ptr<Material> lambert (new Lambert (tex, tex));

  for (const auto& s : shapes)
  {
    // Loop over faces
    std::size_t index_offset = 0;
    for (std::size_t f = 0; f < s.mesh.num_face_vertices.size (); ++f)
    {
      // Must be 3
      int fv = s.mesh.num_face_vertices[f];
      if (fv != 3)
      {
        std::cout << "Face must be triangle" << std::endl;
      }
      std::array<std::shared_ptr<Vertex>, 3> t_vertex;
      for (std::size_t v = 0; v < fv; v++)
      {
        // あやしい
        tinyobj::index_t idx = s.mesh.indices[index_offset + v];

        // Get position, normal and texcoord
        const std::shared_ptr<Point3f>  p = positions[idx.vertex_index];;
        const std::shared_ptr<Normal3f> n = (!normals.empty ())   ? normals[idx.normal_index]     : nullptr;;
        const std::shared_ptr<Point2f>  t = (!texcoords.empty ()) ? texcoords[idx.texcoord_index] : nullptr;

        t_vertex[v] = CreateVertex (p, n, t);
      }
      index_offset += fv;
      // Create triangle shape from vertices
      std::shared_ptr<Shape> triangle = CreateTriangleShape (t_vertex[0], t_vertex[1], t_vertex[2]);

      // Create primitive
      res.push_back (CreateStaticPrimitive (triangle, lambert));
    }
  }


  // ---------------------------------------------------------------------------
  // ありえないDebugとりあえず、ちゃんんとメモりのどっかに保存されているか??
  // ---------------------------------------------------------------------------
  /*
  for (const auto& p : res)
  {
    Triangle* t = dynamic_cast<Triangle*> (p->GetShape().get());

    std::cout << *(t->vertices_[0]->position) << std::endl;
    std::cout << *(t->vertices_[1]->position) << std::endl;
    std::cout << *(t->vertices_[2]->position) << std::endl << std::endl;;

    std::cout << *(t->vertices_[0]->normal) << std::endl;;
    std::cout << *(t->vertices_[1]->normal) << std::endl;;
    std::cout << *(t->vertices_[2]->normal) << std::endl;;
    std::cout << *(t->vertices_[0]->texcoord) << std::endl;;
    std::cout << *(t->vertices_[1]->texcoord) << std::endl;;
  }
  */
  return std::move (res);
}


auto LoadRtcamp5 () -> UnorderedScene
{
  UnorderedScene res;

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t>    shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err;

  const bool result =
    tinyobj::LoadObj(&attrib, &shapes, &materials, &err, "./assets/rtcamp_scene.obj");
  if (!result || !err.empty ())
  {
    std::cout << "Could not load rtcamp.obj" << std::endl;
    std::cout << err << std::endl;
    // Error
    return res;
  }

  // ---------------------------------------------------------------------------
  // Generate positions, normals and texcoords
  // ---------------------------------------------------------------------------
  // Get the number of positions and copy them
  const std::size_t num_vertices = attrib.vertices.size ();
  std::vector<std::shared_ptr<Point3f>> positions (num_vertices / 3, nullptr);
  for (std::size_t i = 0; i < num_vertices / 3; ++i)
  {
    positions[i].reset (new Point3f (attrib.vertices[3 * i + 0],
                                     attrib.vertices[3 * i + 1],
                                     attrib.vertices[3 * i + 2]));
  }

  // Get the number of normals and copy them
  const std::size_t num_normals = attrib.normals.size ();
  std::vector<std::shared_ptr<Normal3f>> normals (num_normals / 3, nullptr);
  for (std::size_t i = 0; i < num_normals / 3; ++i)
  {
    normals[i].reset (new Normal3f (attrib.normals[3 * i + 0],
                                    attrib.normals[3 * i + 1],
                                    attrib.normals[3 * i + 2]));
  }

  // Get the number of texcoord and copy them
  const std::size_t num_texcoords = attrib.texcoords.size ();
  std::vector<std::shared_ptr<Point2f>> texcoords (num_texcoords / 2, nullptr);
  for (std::size_t i = 0; i < num_texcoords / 2; ++i)
  {
    texcoords[i].reset (new Point2f (attrib.texcoords[2 * i + 0],
                                     attrib.texcoords[2 * i + 1]));
  }

  // ---------------------------------------------------------------------------
  // Build faces
  // ---------------------------------------------------------------------------
  // Color decision
  auto red = [] (Float val) -> Float
  {
    if (val < 0.5)
    {
      return val;
    }
    return -val + 1.0;
  };
  auto green = [] (Float val) -> Float
  {
    return 0.5 * val;
  };
  auto blue = [] (Float val) -> Float
  {
    return -0.5 * val + 0.5;
  };
  auto color_decision = [&red, &green, &blue] (Float distance) -> Spectrum
  {
    return Spectrum
    (
        Clamp (red   (distance) * 1.85, 0, 1),
        Clamp (green (distance) * 1.85, 0, 1),
        Clamp (blue  (distance) * 1.85, 0, 1),
        0
    );
  };

  // Load eye textures
  /*
  std::array<std::shared_ptr<Texture<Spectrum>>, 13> eye_texs;
  for (unsigned int i = 0; i < 13; ++i)
  {
    const std::string filepath = "./assets/eye_textures/" + std::to_string (i) + ".png";
    eye_texs[i].reset (new ImageMapTexture (filepath));
  }
  */

  // For choosing a texture
  XorShift rng;

  // Create light
  std::shared_ptr<Light> light (new AreaLight (Spectrum (4.3)));

  static int n = 0;
  for (const auto& s : shapes)
  {
    // Material creation
    std::shared_ptr<Material> mat;
    std::shared_ptr<Light>    light;
    if (s.name.find ("light") != s.name.npos)
    {
      light = std::shared_ptr<Light> (new AreaLight (Spectrum (8.0)));
    }
    else if (s.name.find ("domino78") != s.name.npos)
    {
      const std::shared_ptr<Texture<Spectrum>> t
          (new ImageMapTexture ("./assets/eye_textures/smile.png"));
      const std::shared_ptr<Texture<Spectrum>> reflect
          (new ConstantTexture<Spectrum> (color_decision (n++ / 58.0)));
      mat = std::shared_ptr<Material> (new Lambert (t, t));
    }
    else if (s.name.find ("domino") != s.name.npos)
    {
      // Choose a texture
      int idx = static_cast<int> (rng.Next01() * 12 + 0.5);
      if (idx > 12) idx = 12;
      if (idx <  0) idx = 0;

      // Create reflectance texture
      const std::shared_ptr<Texture<Spectrum>> reflect
          (new ConstantTexture<Spectrum> (color_decision (n++ / 58.0)));
      mat = std::shared_ptr<Material> (new Lambert (nullptr, reflect));
    }
    else
    {
      const std::shared_ptr<Texture<Spectrum>> reflect
        (new ConstantTexture<Spectrum> (Spectrum (0.69)));
      mat = std::shared_ptr<Material> (new Lambert (nullptr, reflect));

      /*
      const std::shared_ptr<Texture<Spectrum>> reflect
          (new ConstantTexture<Spectrum> (0.99));
      mat = std::shared_ptr<Material> (new Phong (nullptr, reflect, 100));
      */
    }

    // Loop over faces
    std::size_t index_offset = 0;
    for (std::size_t f = 0; f < s.mesh.num_face_vertices.size (); ++f)
    {
      // Create vertices for creating a triangle
      int fv = s.mesh.num_face_vertices[f];
      if (fv != 3)
      {
        std::cout << "Face must be triangle" << std::endl;
      }
      std::array<std::shared_ptr<Vertex>, 3> t_vertex ({nullptr});
      for (std::size_t v = 0; v < fv; v++)
      {
        // あやしい
        tinyobj::index_t idx = s.mesh.indices[index_offset + v];

        // Get position, normal and texcoord
        const std::shared_ptr<Point3f>  p = positions[idx.vertex_index];;
        const std::shared_ptr<Normal3f> n = (!normals.empty ())   ? normals[idx.normal_index]     : nullptr;
        const std::shared_ptr<Point2f>  t = (!texcoords.empty ()) ? texcoords[idx.texcoord_index] : nullptr;

        t_vertex[v] = CreateVertex (p, n, t);
      }
      index_offset += fv;
      // Create triangle shape from vertices
      const std::shared_ptr<Shape> triangle = CreateTriangleShape (t_vertex[0], t_vertex[1], t_vertex[2]);

      // Push them
      res.push_back (CreateStaticPrimitive (triangle, mat, light));
    }
  }

  // Add center sphere
  const std::shared_ptr<Texture<Spectrum>> t (new ConstantTexture<Spectrum> (0.98));
  const std::shared_ptr<Shape>    sphere (new Sphere (Point3f (0, 2.3, 0), 2.3));
  const std::shared_ptr<Material> glass  (new Glass  (nullptr, t, 1.25));
  res.push_back (CreateStaticPrimitive (sphere, glass));

  std::cout << "Load done." << std::endl;

  return res;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
