#include "renderer_command.h"
#include "render_view.h"
#include <maya/MGlobal.h>
#include <string>
/*
// ---------------------------------------------------------------------------
*/
namespace plugins
{
/*
// ---------------------------------------------------------------------------
*/
auto RendererCommand::creator () -> void*
{
    return new RendererCommand ();
}
/*
// ---------------------------------------------------------------------------
*/
auto RendererCommand::doIt (const MArgList& args) -> MStatus
{
    std::pair <uint32_t, uint32_t> resolution
        = RenderView::GetResolution ();
    std::string str = std::to_string (resolution.first) + ", "
                    + std::to_string (resolution.second);
    MGlobal::displayInfo (str.c_str ());
    RenderView::GetShadingEngines ();
    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
// NOTICE: Do not change kCommandName value because python plugin refers to
//         command this name.
// ---------------------------------------------------------------------------
*/
const MString RendererCommand::kCommandName = "niepceBeginPreRendering";
/*
// ---------------------------------------------------------------------------
*/
} // namespace plugins
/*
// ---------------------------------------------------------------------------
*/