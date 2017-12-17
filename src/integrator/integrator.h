#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
/*
// ---------------------------------------------------------------------------
*/
// #define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ext/stb_image_write.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
// ---------------------------------------------------------------------------
// Interface
// All rendering system inherit this class
// ---------------------------------------------------------------------------
class Integrator
{
  /* Integrator public constructors */
public:
  Integrator ();


  /* Integrator public destructor */
 public:
  virtual ~Integrator ();


  /* Integrator public operators*/
public:
  Integrator (const Integrator&  integrator) = default;
  Integrator (      Integrator&& integrator) = default;

  auto operator = (const Integrator&  integrator) -> Integrator& = default;
  auto operator = (      Integrator&& integrator) -> Integrator& = default;

  /* Integrator public interface */
public:
  virtual auto Render (const Scene& scene) const -> void = 0;

}; // class Integrator
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _INTEGRATOR_H_
