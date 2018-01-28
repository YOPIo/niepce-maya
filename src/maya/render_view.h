#ifndef _NIEPCE_RENDER_VIEW_H_
#define _NIEPCE_RENDER_VIEW_H_
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MGlobal.h>
#include <cstdint>
#include <utility>

#include "../core/niepce.h"
#include "../core/geometry.h"
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
class NiepceRenderView
{
    /* NiepceRenderView public constructors */
public:
    NiepceRenderView ()  = default;
    ~NiepceRenderView () = default;

    NiepceRenderView (const NiepceRenderView&  rv) = default;
    NiepceRenderView (      NiepceRenderView&& rv) = default;

    auto operator = (const NiepceRenderView&  rv) -> NiepceRenderView& = default;
    auto operator = (      NiepceRenderView&& rv) -> NiepceRenderView& = default;


    /* NiepceRenderView public static methods */
public:
    // Register the renderer as "Niepce Renderer" via python command
    static auto RegistserRenderer  () -> MStatus;

    // Unregister the renderer as "Niepce Renderer" via python command
    static auto UnregisterRenderer () -> MStatus;

    // Return size of image resolution
    static auto GetResolution () -> std::pair <uint32_t, uint32_t>;
      
    //  
    static auto ConstructSceneForNiepce (niepce::Scene* scene) -> MStatus;

    // Get first renderable camera
    //  - MStatus::kSuccess : Found renderable camera
    //  - MStatus::kFailure : Could not find renderable camera
    static auto GetRenderableCamera (MDagPath* path) -> MStatus;

    static auto GetNiepceCamera
    (
        const MDagPath& path,
        MStatus* status
    )
    -> std::shared_ptr <niepce::Camera>;

    /* NiepceRenderView private methods */
private:
    static auto CreateTriangles
    (
        std::vector <niepce::ShapePtr>* triangles,
        size_t num_faces,
        size_t num_positions,
        size_t num_normals,
        size_t num_texcoords,
        niepce::Float* const positions,
        niepce::Float* const normals,
        niepce::Float* const texcoords,
        const std::vector <uint32_t>& position_indices,
        const std::vector <uint32_t>& normal_indices,
        const std::vector <uint32_t>& texcoord_indices
    )
    -> void;   
};
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _NIEPCE_RENDER_VIEW_H_