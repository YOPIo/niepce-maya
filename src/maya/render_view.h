#ifndef _RENDER_VIEW_H_
#define _RENDER_VIEW_H_
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MGlobal.h>
#include <cstdint>
#include <utility>
/*
// ---------------------------------------------------------------------------
// Description :
// This class performs that following.
//  - Registering renderer as Niepce Renderer using python command
// ---------------------------------------------------------------------------
*/
namespace plugins
{
/*
// ---------------------------------------------------------------------------
*/
class RenderView
{
    /* RenderView public constructors */
public:
    RenderView ()  = default;
    ~RenderView () = default;

    RenderView (const RenderView&  rv) = default;
    RenderView (      RenderView&& rv) = default;

    auto operator = (const RenderView&  rv) -> RenderView& = default;
    auto operator = (      RenderView&& rv) -> RenderView& = default;


    /* RenderView public static methods */
public:
    // Register the renderer as "Niepce Renderer" via python command
    static auto RegistserRenderer  () -> MStatus;
    // Unregister the renderer as "Niepce Renderer" via python command
    static auto UnregisterRenderer () -> MStatus;

    static auto GetResolution () -> std::pair <uint32_t, uint32_t>;

    static auto GetShadingEngines () -> MStatus;
    static auto GetMaterialInfos  () -> MStatus;

private:
    /* RenderView private methods */

};
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _RENDER_VIEW_H_