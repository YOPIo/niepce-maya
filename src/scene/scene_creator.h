#ifndef _SCENE_CREATOR_H_
#define _SCENE_CREATOR_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto CreateCornellBox ()
  -> std::pair <std::shared_ptr <Camera>, std::shared_ptr <Scene>>;

auto CreateSphereScene ()
  -> std::pair <std::shared_ptr <Camera>, std::shared_ptr <Scene>>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SCENE_CREATOR_H_
