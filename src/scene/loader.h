#ifndef _LOADER_H_
#define _LOADER_H_

#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../texture/image_map.h"
#include "../light/area.h"
#include "../shape/sphere.h"
#include "../shape/vertex.h"
#include "../shape/triangle.h"
#include "../random/xorshift.h"
/*
#include "../material/lambert.h"
#include "../material/glass.h"
*/

namespace niepce
{

auto LoadObj (const std::string& filepath) -> UnorderedScene;

auto LoadRtcamp5 () -> UnorderedScene;

}  // namespace niepce

#endif // _LOADER_H_
