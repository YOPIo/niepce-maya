#include "render_view.h"
#include "defines.h"
#include <maya/MFnDependencyNode.h>
#include <maya/MFnSet.h>
#include <maya/MGlobal.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MSelectionList.h>
#include <maya/MPlug.h>
#include <string>
/*
// ---------------------------------------------------------------------------
*/
namespace plugins
{
/*
// ---------------------------------------------------------------------------
*/
auto RenderView::RegistserRenderer () -> MStatus
{
    // Register renderer via python command
    MStatus status;

    // Import python module
    MString cmd ("import niepce_renderer");
    status = MGlobal::executePythonCommand (cmd);
    if (status != MStatus::kSuccess)
    {
        return status;
    }

    // Call function to register renderer
    // See registerRenderer function on detail
    cmd = "niepce_renderer.registerRenderer ()";
    return MGlobal::executePythonCommand (cmd);
}
/*
// ---------------------------------------------------------------------------
*/
auto RenderView::UnregisterRenderer () -> MStatus
{
    // Unregister renderer via python command    
    // Call function to unregister renderer
    MString cmd ("niepce_renderer.unregisterRenderer ()");
    return MGlobal::executePythonCommand (cmd);    
}
/*
// ---------------------------------------------------------------------------
*/
auto RenderView::GetResolution () -> std::pair <uint32_t, uint32_t>
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
*/
auto RenderView::GetShadingEngines () -> MStatus
{
    MStatus status;

    // Listup all shading engine
    MItDependencyNodes shadings (MFn::kShadingEngine);

    // Loop for shading engines
    for (; !shadings.isDone (); shadings.next ())
    {
        MFnDependencyNode shading_node (shadings.thisNode ());
        MItDependencyGraph material_graph
            (shading_node.findPlug ("surfaceShader"),
             MFn::kDependencyNode,
             MItDependencyGraph::kUpstream,
             MItDependencyGraph::kDepthFirst,
             MItDependencyGraph::kNodeLevel);
        // Loop for material (surface shader) in current shading engine
        for (; !material_graph.isDone (); material_graph.next ())
        {
            MFnDependencyNode material (material_graph.thisNode ());
            // Get material's attribute
            MPlug reflectance (material.findPlug ("refrectance", &status));
            CHECK_MSTATUS (status);

            // Reflectance attribute should have 3 node (RGB)
            if (reflectance.numChildren () == 3)
            {
                // Get reflectance RGB
                MPlug plug_r (reflectance.child (0));
                MPlug plug_g (reflectance.child (1));
                MPlug plug_b (reflectance.child (2));

                float r (plug_r.asFloat ());
                float g (plug_g.asFloat ());
                float b (plug_b.asFloat ());

                MGlobal::displayInfo (plug_r.asString ());
            }
        }
    

        MObject obj (shadings.thisNode ());        
        MFnSet shading_set (obj);

        MSelectionList member;
        shading_set.getMembers (member, true);

       
    }
    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
auto RenderView::GetMaterialInfos () -> MStatus
{
    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/