#include "render_view.h"
#include "defines.h"
#include <maya/MDagPath.h>
#include <maya/MDrawContext.h>
#include <maya/MFnCamera.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnMesh.h>
#include <maya/MFnSet.h>
#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MFnTransform.h>
#include <maya/MFrameContext.h>
#include <maya/MGeometryExtractor.h>
#include <maya/MGlobal.h>
#include <maya/MHWGeometry.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MItSelectionList.h>
#include <maya/MIOStream.h>
#include <maya/MSelectionList.h>
#include <maya/MPlug.h>
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../camera/camera.h"
#include "../shape/triangle.h"
#include "../primitive/individual.h"
#include "../scene/scene.h"
#include "../material/matte.h"
/*
// ---------------------------------------------------------------------------
*/
namespace plugins
{
/*
// ---------------------------------------------------------------------------
*/
auto NiepceRenderView::RegistserRenderer () -> MStatus
{
    // Register renderer via python command
    MStatus status;

    // Import python module
    MString cmd ("import niepce_renderer, hypershade_callbacks");
    status = MGlobal::executePythonCommand (cmd);
    if (status != MStatus::kSuccess)
    {
        MGlobal::displayError ("Failed to import python module.");
        return status;
    }

    // Call function to register renderer
    // See registerRenderer function on detail
    cmd = "niepce_renderer.registerRenderer (); hypershade_callbacks.registerHypershade ()";
    return MGlobal::executePythonCommand (cmd);
}
/*
// ---------------------------------------------------------------------------
*/
auto NiepceRenderView::UnregisterRenderer () -> MStatus
{
    // Unregister renderer via python command    
    // Call function to unregister renderer
    MString cmd ("niepce_renderer.unregisterRenderer ()");
    return MGlobal::executePythonCommand (cmd);    
}
/*
// ---------------------------------------------------------------------------
*/
auto NiepceRenderView::GetResolution () -> std::pair <uint32_t, uint32_t>
{
    // If failed to get resolution, then return 960x540 as default
    uint32_t width  (960);
    uint32_t height (540);

    // Find 'defaultResolution' node
    MSelectionList list;
    MGlobal::getSelectionListByName ("defaultResolution", list);

    // If 'defaultResolution' was found, the number of list is bigger than
    // zero
    if (list.length () > 0)
    {
        // 'defaultResolution' was Found
        // Get dependency node from list
        MObject node;
        list.getDependNode (0, node);
        MFnDependencyNode dnode (node);

        // Get attributes which width and height from dependency node
        MPlug plug_width  (dnode.findPlug ("width"));
        MPlug plug_height (dnode.findPlug ("height"));
        width  = plug_width.asInt ();
        height = plug_height.asInt ();
    }
  
    return std::make_pair (width, height);
}
/*
// ---------------------------------------------------------------------------
auto NiepceRenderView::ConstructSceneForNiepce (niepce::Scene* scene) -> MStatus
{    
    MStatus status;

    std::vector <niepce::IndividualPtr> primitives;    

    // Debug
    const niepce::MaterialPtr mat (niepce::CreateMatte (niepce::Spectrum (0.75, 0.75, 0.75, 1.0)));

    // Get all shading engines at the current scene
    MItDependencyNodes shading_engines (MFn::kShadingEngine);
    
    // Loop for shading engines
    for (; !shading_engines.isDone (); shading_engines.next ())
    {
        MFnDependencyNode shading_node (shading_engines.thisNode ());
        MGlobal::displayInfo (shading_node.name ());

        // Material processing ...
        MItDependencyGraph materials (shading_node.findPlug ("surfaceShader"),
                                      MFn::kDependencyNode,
                                      MItDependencyGraph::kUpstream,
                                      MItDependencyGraph::kDepthFirst,
                                      MItDependencyGraph::kNodeLevel);
        for (; !materials.isDone (); materials.next ())
        {
            MFnDependencyNode mat (materials.thisNode ());
            MGlobal::displayInfo ("SurfaceShader : " + mat.name ());
        }

        // Access to geometries...
    
        // Create sets node
        MFnSet  shading_set (shading_engines.thisNode ());

        // Get selection list from set object
        MSelectionList members;
        shading_set.getMembers (members, false);
        for (int m = 0; m < members.length (); ++m)
        {
            // Get DagPath and MObject from current member
            MDagPath dag_path;        
            MObject  component;
            members.getDagPath (m, dag_path, component);

            // Build mesh from dag path
            MFnMesh  mesh (dag_path);
            // mesh.syncObject ();
           
            // Valid data type specification, default is float
            MHWRender::MGeometry::DataType data_type = MHWRender::MGeometry::kFloat;
#ifdef NIEPCE_FLOAT_IS_DOUBLE
            data_type = MHWRender::MGeometry::kDouble;
#endif

            // Build a geometry request and add requirements to it.
            MHWRender::MGeometryRequirements requirements;

            // Build descriptors to request the positions, normals and UVs.
            auto position_descriptor
                = MHWRender::MVertexBufferDescriptor ("",
                                                      MHWRender::MGeometry::kPosition,
                                                      data_type,
                                                      3);
            auto normal_descriptor
                = MHWRender::MVertexBufferDescriptor ("",
                                                      MHWRender::MGeometry::kNormal,
                                                      data_type,
                                                      3);            
            auto texcoord_descriptor
                = MHWRender::MVertexBufferDescriptor (mesh.currentUVSetName (),
                                                      MHWRender::MGeometry::kTexture,
                                                      data_type,
                                                      2);

            // Add the descriptors to the geometry requirements
            requirements.addVertexRequirement (position_descriptor);
            requirements.addVertexRequirement (normal_descriptor);            
            requirements.addVertexRequirement (texcoord_descriptor);

            // Build a index descriptor to request the indices
            auto indices_descriptor
                = MHWRender::MIndexBufferDescriptor (MHWRender::MIndexBufferDescriptor::kTriangle,
                                                     "",
                                                     MHWRender::MGeometry::kTriangles,
                                                     3,
                                                     component,
                                                     MHWRender::MGeometry::kUnsignedInt32);

            // Add the index descriptor to the requirements
            requirements.addIndexingRequirement (indices_descriptor);

            // Create a GeometryExtractor to get the geometry
            MHWRender::MGeometryExtractor geometries (requirements,
                                                      dag_path,
                                                      MHWRender::kPolyGeom_BaseMesh,
                                                      &status);
            NIEPCE_CHECK_MSTATUS (status, "Failed to get geometries.");

            // Debug : show current shapes
            // MGlobal::displayInfo (dag_path.fullPathName ());

            // Get the number of vertices and number of primitives
            const unsigned num_vertices   (geometries.vertexCount ());
            const unsigned num_primitives (geometries.primitiveCount (indices_descriptor));

            // Get positions
            // Todo: Get normals and texcoords.
            niepce::Float* positions = new niepce::Float [num_vertices * position_descriptor.stride ()];            
            status = geometries.populateVertexBuffer (positions,
                                                      num_vertices,
                                                      position_descriptor);            

            // Get indices to the geometry positions            
            // Todo: Get indices of normal and texcoord.
            std::vector <uint32_t> indices (3 * num_primitives);
            geometries.populateIndexBuffer (indices.data (), num_primitives, indices_descriptor);
                        
            // Create triangles
            std::vector <niepce::ShapePtr> triangles;
            CreateTriangles (&triangles,     // Results
                             num_primitives, // The number of faces
                             num_vertices,   // The number of positions
                             0,              // The number of normals
                             0,              // The number of texcoords
                             positions,      // Positions pointer
                             nullptr,        // Normals pointer
                             nullptr,        // Texcoord pointer
                             indices,        // Index of positions
                             {},             // Index of normals
                             {});            // Index of texcoords

            // Debug
            for (const auto& t : triangles)
            {
                std::tuple <niepce::Point3f, niepce::Point3f, niepce::Point3f> tri
                    = dynamic_cast <niepce::Triangle*> (t.get ())->GetPosition ();

                MString str0 ( (std::to_string (std::get <0> (tri).x) + ", "
                    + std::to_string (std::get <0> (tri).y) + ","
                    + std::to_string (std::get <0> (tri).z) + " : ").c_str () );
                MString str1 ( (std::to_string (std::get <1> (tri).x) + ", "
                    + std::to_string (std::get <1> (tri).y) + ","
                    + std::to_string (std::get <1> (tri).z) + " : ").c_str () );
                MString str2 ( (std::to_string (std::get <2> (tri).x) + ", "
                    + std::to_string (std::get <2> (tri).y) + ","
                    + std::to_string (std::get <2> (tri).z)).c_str () );

                MGlobal::displayInfo (str0 + str1 + str2);
            }

            // Create individual primitive
            for (const auto& shape : triangles)
            {
                niepce::IndividualPtr individual
                    = niepce::CreateIndividual (shape, mat, nullptr);
                primitives.push_back (individual);
            }

            // Free memories                             
            delete [] positions;
        }        
    }

    MGlobal::displayInfo ( ("The number of primitives : " + std::to_string (primitives.size ())).c_str () );

    *scene = niepce::Scene (primitives);

    return status;
}
*/
/*
// ---------------------------------------------------------------------------
// Find a renderable camera
// If found  : MStatus::kSuccess
// otherwize : MStatus::kFailure
// ---------------------------------------------------------------------------
*/
auto NiepceRenderView::GetRenderableCamera (MDagPath* path) -> MStatus
{    
    // Get all camera in the scene
    MItDependencyNodes cameras_nodes (MFn::kCamera);

    // Loop over the camera in the scene
    for (; !cameras_nodes.isDone (); cameras_nodes.next ())
    {
        MFnCamera camera (cameras_nodes.thisNode ());
        // Check renderable parameter as true or not.
        if (camera.findPlug ("renderable").asBool ())
        {
            camera.getPath (*path);
            MGlobal::displayInfo (path->fullPathName ());
            return MStatus::kSuccess;
        }      
    }
    return MStatus::kFailure;
}
/*
// ---------------------------------------------------------------------------
*/
auto NiepceRenderView::GetNiepceCamera
(
    const MDagPath& path,
    MStatus* status
)
-> std::shared_ptr <niepce::Camera>
{
    // Create MFnCamera to get camera position, direciton and up vectors    
    const MFnCamera m_camera (path, status);
    NIEPCE_CHECK_MSTATUS (*status, "Failed to create MFnCamera.");

    // Get eye point in world system coordinate
    const MPoint eye_position (m_camera.eyePoint (MSpace::kWorld, status));
    NIEPCE_CHECK_MSTATUS (*status, "Failed to get eye point of camera.");

    // Get camera direction in world system coordinate
    const MVector view_direction (m_camera.viewDirection (MSpace::kWorld, status));
    NIEPCE_CHECK_MSTATUS (*status, "Failed to get view direction of camera.");

    // Get camera up vector in world system coordinate
    const MVector up_direction (m_camera.upDirection (MSpace::kWorld, status));
    NIEPCE_CHECK_MSTATUS (*status, "Faild to get up direction of camera.");

    // Convert MPoint to niepce::Point3f and MVector to niepce::Vector3f
    const niepce::Point3f  position  (ToNiepcePoint3 (eye_position));
    const niepce::Vector3f direction (ToNiepceVector3 (view_direction));
    const niepce::Vector3f up        (ToNiepceVector3 (up_direction));

    std::shared_ptr <niepce::Camera> camera
        (std::make_shared <niepce::Camera> (position,
                                            direction,
                                            up));
    return std::move (camera);
}
/*
// ---------------------------------------------------------------------------

auto NiepceRenderView::CreateTriangles
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
-> void
{
    // Convert positions to niepce::Point3f.
    niepce::Point3f* positions_ptr (new niepce::Point3f [num_positions]);
    for (size_t i = 0; i < num_positions; ++i)
    {
        const niepce::Point3f p (positions[3 * i + 0],
                                 positions[3 * i + 1],
                                 positions[3 * i + 2]);
        positions_ptr[i] = p;
    }

    niepce::Normal3f* normals_ptr (nullptr);
    // Convert normals to niepce::Normal3f if present.
    if (normals != nullptr)
    {
        // Todo: implementation
    }

    niepce::Point2f* texcoords_ptr (nullptr);
    // Convert texcoords to niepce::Point2f if present.
    if (texcoords != nullptr)
    {
        // Todo: implementation
    }

    // Create niepce::TriangleMesh
    const auto mesh (niepce::CreateTriangleMesh (num_faces,
                                                 num_positions,
                                                 num_normals,
                                                 num_texcoords,
                                                 positions_ptr,
                                                 normals_ptr,
                                                 texcoords_ptr));

    // Create niepce::Triangle shapes
    // 1. allocate (resize) size of std::vector
    *triangles = std::vector <niepce::ShapePtr> (num_faces);
    // 2. Create triangles 
    for (int n = 0; n < num_faces; ++n)
    {
        const std::array <uint32_t, 3> p_idx_array 
            = {position_indices[3 * n + 0],
               position_indices[3 * n + 1],
               position_indices[3 * n + 2]};
        const std::array <uint32_t, 3> n_idx_array
            = {0};
        const std::array <uint32_t, 3> t_idx_array
            = {0};

        triangles->at (n) = niepce::CreateTriangle (mesh,
                                               p_idx_array,
                                               n_idx_array,
                                               t_idx_array);
    }
}
*/
/*
// ---------------------------------------------------------------------------
*/
} // namespace plugins