#include "defines.h"
#include "renderer_command.h"
#include "render_view.h"
#include <maya/MDagPath.h>
#include <maya/MGlobal.h>
#include <maya/MRenderView.h>
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
// Begin rendering processing
// ---------------------------------------------------------------------------
*/
auto RendererCommand::doIt (const MArgList& args) -> MStatus
{
    MStatus status;

    // Get rendering resolution
    std::pair <uint32_t, uint32_t> resolution (NiepceRenderView::GetResolution ());

    // Call doesRenderEditorExist() to make sure that a Render View exists.
    // If this returns false, then Maya is operating in batch mode.
    MRenderView::doesRenderEditorExist ();
    NIEPCE_CHECK_MSTATUS (status, "");

    // Call setCurrentCamera() to specify the name of the camera that is
    // being rendered.
    MDagPath camera;
    status = NiepceRenderView::GetRenderableCamera (camera);
    NIEPCE_CHECK_MSTATUS (status, "");
    status = MRenderView::setCurrentCamera (MDagPath (camera));
    NIEPCE_CHECK_MSTATUS (status, "");

    // Call startRender() to inform the Render View that you are about to
    // start sending either a full image or a region update.
    status = MRenderView::startRender (resolution.first, resolution.second);
    NIEPCE_CHECK_MSTATUS (status, "");


    // Test
    std::unique_ptr <RV_PIXEL []> pixels (new RV_PIXEL [resolution.first * resolution.second]);
    for (int y = 0; y < resolution.second; ++y)
    {
        for (int x = 0; x < resolution.first; ++x)
        {
            pixels[y * resolution.first + x].r = 100.0;
            pixels[y * resolution.first + x].g = 20.0;
            pixels[y * resolution.first + x].b = 5.0;
            pixels[y * resolution.first + x].a = 1.0;
        }
    }

    // The image or image region is sent to the Render View as a series of
    // one or more tiles. For each tile, send the tile's image data using
    // the updatePixels() method. Call the refresh() method to refresh
    // the Render View after each tile has been sent.    
    status = MRenderView::updatePixels (0,                    // Left
                                        resolution.first - 1, // Right
                                        0,                    // Bottom
                                        resolution.second -1, // Top
                                        pixels.get (),        // Buffer
                                        false,                // HDR format flag
                                        0);                   // The number of AOVs                                        
    NIEPCE_CHECK_MSTATUS (status, "");
    status = MRenderView::refresh (0,                      // Left
                                   resolution.first - 1,   // Right
                                   0,                      // Bottom
                                   resolution.second - 1); // Top
    NIEPCE_CHECK_MSTATUS (status, "");

    // Call endRender() to signal the Render View that all
    // image data has been sent.
    status = MRenderView::endRender ();
    NIEPCE_CHECK_MSTATUS (status, "");


    // Test
    NiepceRenderView::ConstructSceneForNiepce ();

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