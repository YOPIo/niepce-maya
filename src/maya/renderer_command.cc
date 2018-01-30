/*
// ---------------------------------------------------------------------------
*/
#include <maya/MDagPath.h>
#include <maya/MGlobal.h>
#include <maya/MRenderView.h>
#include <maya/MString.h>
#include <string>
#include <algorithm>
/*
// ---------------------------------------------------------------------------
*/
#include "defines.h"
#include "renderer_command.h"
#include "render_view.h"
#include "maya_tracer.h"
#include "accessor.h"
/*
// ---------------------------------------------------------------------------
*/
#include "../camera/camera.h"
#include "../sampler/random_sampler.h"
#include "../scene/scene.h"
#include "../sampler/random_sampler.h"
#include "../integrator/path_tracer.h"
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

    // Camera construction
    // todo: カメラの実装が適当なので、修正する
    MDagPath path;
    std::shared_ptr <niepce::Camera> camera;
    status = niepce::ConstructCamera (&camera, &path);
    NIEPCE_CHECK_MSTATUS (status, "Faild to construct a camera.");

    // Sampler construction
    std::shared_ptr <niepce::Sampler> sampler = niepce::CreateRandomSampler ();

    // Primitive construction    
    std::vector <niepce::IndividualPtr> primitives;
    niepce::ConstructPrimitives (&primitives);

    // Scene construction for niepce renderer
    niepce::Scene scene (primitives);

    // Integrator construction
    std::shared_ptr <niepce::PathTracer> tracer
        = std::make_shared <niepce::PathTracer> (camera, sampler, 8);

    /*
    // ----------------------------------------------------------------------
    // Render-view update test (start)
    // ----------------------------------------------------------------------
    */
    constexpr uint32_t kTileSize = 32;
    const auto resolution = NiepceRenderView::GetResolution ();

    const uint32_t num_tiles_width  = std::ceil ((double)resolution.first / (double)kTileSize);
    const uint32_t num_tiles_height = std::ceil ((double)resolution.second / (double)kTileSize);

    // Data
    std::unique_ptr <RV_PIXEL []> pixels (new RV_PIXEL[kTileSize * kTileSize]);
    for (uint32_t sy = 0; sy < kTileSize; ++sy)
    {
        for (uint32_t sx = 0; sx < kTileSize; ++sx)
        {
            pixels[sy * kTileSize + sx].r = 30.0;
            pixels[sy * kTileSize + sx].g = 30.0;
            pixels[sy * kTileSize + sx].b = 30.0;
            pixels[sy * kTileSize + sx].a = 1.0;
        }
    }

    MRenderView::doesRenderEditorExist ();

    status = MRenderView::setCurrentCamera (path);
    NIEPCE_CHECK_MSTATUS (status, "");

    status = MRenderView::startRender (resolution.first - 1, resolution.second - 1);
    NIEPCE_CHECK_MSTATUS (status, "");
   
    for (uint32_t y = 0; y < num_tiles_height; ++y)
    {
        for (uint32_t x = 0; x < num_tiles_width; ++x)
        {            
            const uint32_t left   = x * kTileSize;
            const uint32_t right  = std::min ((x + 1) * kTileSize - 1, resolution.first - 1);
            const uint32_t bottom = y * kTileSize;
            const uint32_t top    = std::min ((y + 1) * kTileSize - 1, resolution.second - 1);

            // MGlobal::displayInfo ( (std::to_string (left) + ", " + std::to_string (top) + ", " + std::to_string (right) + ", " + std::to_string (bottom)).c_str ());


            status = MRenderView::updatePixels (left, right, bottom, top,
                                                pixels.get (), // data
                                                true, // HDR format flag
                                                0);    // The number of AOVs
            NIEPCE_CHECK_MSTATUS (status, "");

            status = MRenderView::refresh (left, right, bottom, top);
            NIEPCE_CHECK_MSTATUS (status, "");

            // Sleep (50);
        }
    }

    status = MRenderView::endRender ();
    NIEPCE_CHECK_MSTATUS (status, "");

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