/*
// ---------------------------------------------------------------------------
*/
#include "defines.h"
#include "accessor.h"
#include "../shape/triangle.h"
#include "../material/matte.h"
#include "../light/area.h"
#include "../primitive/individual.h"
#include "../scene/scene.h"
#include "../camera/camera.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto ConstructPrimitives (std::vector <IndividualPtr>* primitives) -> MStatus
{
    MStatus status;
    primitives->clear ();

    // Get all shading engines in the scene.
    MItDependencyNodes shading_engines (MFn::kShadingEngine);
    
    // Loop over the shading engine
    for (; !shading_engines.isDone () ; shading_engines.next ())
    {
        // Get material from current shading engine
        // Debug: すべてのシェイプはMatteを持つ
        MaterialPtr debug_mtl = CreateMatte (Spectrum (0.75));

        // Get all of the shapes that are attached curennt material.
        std::vector <ShapePtr> shapes;
        ConstructTriangles (shading_engines, &shapes);        

        // Attach the material to the shapes
        for (const auto& s : shapes)
        {
            primitives->push_back (CreateIndividual (s, debug_mtl, nullptr));            
        }        
    }

    return status;
}
/*
// ---------------------------------------------------------------------------
*/
auto ConstructTriangles
(
    MItDependencyNodes&     shading_engine,
    std::vector <ShapePtr>* shapes
)
-> MStatus
{
    MStatus status;
    shapes->clear ();

    // Access to geometries
    MFnSet shading_set (shading_engine.thisNode ());

    // Get selection list from set object
    MSelectionList members;
    shading_set.getMembers (members, false);
    for (uint32_t m = 0; m < members.length (); ++m)
    {
        // Get DagPath and MObject from current member
        MDagPath dag_path;        
        MObject  component;
        members.getDagPath (m, dag_path, component);

        // Build mesh from dag path
        MFnMesh  mesh (dag_path);        
        // debug
        // MGlobal::displayInfo ("Full dag path" + dag_path.fullPathName ());

        // Build a geometry request and add requirements to it.
        MHWRender::MGeometryRequirements requirements;

        // Build descriptors to request the positions, normals and UVs.
        auto position_descriptor
            = MHWRender::MVertexBufferDescriptor ("",
                                                  MHWRender::MGeometry::kPosition,
                                                  kNiepceRenderingQuality,
                                                  3);
        auto normal_descriptor
            = MHWRender::MVertexBufferDescriptor ("",
                                                  MHWRender::MGeometry::kNormal,
                                                  kNiepceRenderingQuality,
                                                  3);            
        auto texcoord_descriptor
            = MHWRender::MVertexBufferDescriptor (mesh.currentUVSetName (),
                                                  MHWRender::MGeometry::kTexture,
                                                  kNiepceRenderingQuality,
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
                                                 0,
                                                 component,
                                                 MHWRender::MGeometry::kUnsignedInt32);

        // Add the index descriptor to the requirements
        requirements.addIndexingRequirement (indices_descriptor);

        // Create a GeometryExtractor to get the geometry
        MHWRender::MGeometryExtractor geometries (requirements,
                                                  dag_path,
                                                  // smooth
                                                  MHWRender::kPolyGeom_Normal,
                                                  &status);
        NIEPCE_CHECK_MSTATUS (status, "Failed to get geometries.");        

        // Get the number of vertices and number of primitives
        const uint32_t num_vertices   (geometries.vertexCount ());
        const uint32_t num_primitives (geometries.primitiveCount (indices_descriptor));
        
        // Get positions
        // Todo: Get normals and texcoords.        
        Float* pos = new Float [num_vertices * position_descriptor.stride ()];
        // HACKME: わからないけど、これじゃないとうまく取得できない（アライメントされてないから？）
        // Point3f* pos = new Point3f [num_vertices]; <- こっちで直接データを取得したい
        status = geometries.populateVertexBuffer ((void*)pos,
                                                  num_vertices,
                                                  position_descriptor);
        NIEPCE_CHECK_MSTATUS (status, "Failed to get geometries.");
        // Float から Point3 へ型を変換
        std::vector <Point3f> positions (num_vertices);
        for (int i = 0; i < num_vertices; ++i)
        {
            positions[i] = Point3f (pos[3 * i + 0], pos[3 * i + 1], pos[3 * i + 2]);
            // MGlobal::displayInfo (positions[i].ToString ().c_str ());
        }        

        // Contruct a triangle mesh from position
       const std::shared_ptr <TriangleMesh> t_mesh = niepce::CreateTriangleMesh (num_primitives, positions);

        // Get indices to the geometry positions
        // Todo: Get indices of normal and texcoord.
        std::vector <uint32_t> indices (3 * num_primitives);
        geometries.populateIndexBuffer (indices.data (), num_primitives, indices_descriptor);

        // Create triangle shape
        for (uint32_t idx = 0; idx < num_primitives; ++idx)
        {
            const std::array <Index, 3> p_idx = {indices[3 * idx + 0],
                                                 indices[3 * idx + 1],
                                                 indices[3 * idx + 2]};
            std::shared_ptr <Triangle> t = CreateTriangle (t_mesh, p_idx);           
            shapes->push_back (t);
        }
    } // End of for
    
    return status;
}
/*
// ---------------------------------------------------------------------------
*/
auto ConstructCamera
(
    std::shared_ptr<Camera>* camera,
    MDagPath*                path
)
-> MStatus
{
    MStatus status;

    // Find a path of renderable camera from maya    
    FindRenderableCamera (path);

    // TODO: 行列でカメラの位置などを返す関数をつくる
    // Create MFnCamera to get camera position, direciton and up vectors    
    const MFnCamera m_camera (*path, &status);
    NIEPCE_CHECK_MSTATUS (status, "Failed to create MFnCamera.");

    // Get eye point in world system coordinate
    const MPoint eye_position (m_camera.eyePoint (MSpace::kWorld, &status));
    NIEPCE_CHECK_MSTATUS (status, "Failed to get eye point of camera.");

    // Get camera direction in world system coordinate
    const MVector view_direction (m_camera.viewDirection (MSpace::kWorld, &status));
    NIEPCE_CHECK_MSTATUS (status, "Failed to get view direction of camera.");

    // Get camera up vector in world system coordinate
    const MVector up_direction (m_camera.upDirection (MSpace::kWorld, &status));
    NIEPCE_CHECK_MSTATUS (status, "Faild to get up direction of camera.");

    // Convert MPoint to niepce::Point3f and MVector to niepce::Vector3f
    niepce::Point3f  position  (eye_position.x, eye_position.y, eye_position.z);
    niepce::Vector3f direction (view_direction.x, view_direction.y, view_direction.z);
    niepce::Vector3f up        (up_direction.x, up_direction.y, up_direction.z);

    MGlobal::displayInfo ( ("position  : " + position.ToString ()).c_str () );
    MGlobal::displayInfo ( ("direction : " + direction.ToString ()).c_str () );
    MGlobal::displayInfo ( ("up        : " + up.ToString ()).c_str ());

    // Construct a camera for niepce renderer
    *camera = std::make_shared <Camera> (position, direction, up, 45, 16.0 / 9.0);

    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
auto FindRenderableCamera (MDagPath* path) -> MStatus
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
}
/*
// ---------------------------------------------------------------------------
*/