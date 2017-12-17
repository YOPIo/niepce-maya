/*
// ---------------------------------------------------------------------------
*/
#include <maya/MDrawRegistry.h>
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MRenderView.h> // For update Render View
#include <maya/MPxCommand.h>
/*
// ---------------------------------------------------------------------------
*/
#include "defines.h"
#include "renderer_command.h"
#include "matte_shader.h"
#include "render_view.h"
/*
// ---------------------------------------------------------------------------
*/
namespace plugins
{
/*
// ---------------------------------------------------------------------------
// Global variables for Maya
// ---------------------------------------------------------------------------
*/
static const MString kRendererName  = "Niepce";
static const MString kPluginCmdName = "niepce";
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
auto initializePlugin (MObject obj) -> MStatus
{
    MStatus status;
    // Register the plugins
    MFnPlugin plugin (obj,
                      NIEPCE_MAYA_VENDOR_STRING,
                      NIEPCE_MAYA_VERSION_STRING,
                      "Any",
                      &status);
    NIEPCE_CHECK_MSTATUS (status, "Failed to register plugins.");    


    // Register a command to carry on pre-rendering.
    plugin.registerCommand (plugins::RendererCommand::kCommandName,
                            plugins::RendererCommand::creator);


    // Register the renderer as Niepce Renderer
    plugins::RenderView::RegistserRenderer ();


    // Register surface shaders
    CHECK_MSTATUS (plugin.registerNode ("nMatte",
                                        plugins::MatteShader::id,
                                        plugins::MatteShader::creator,
                                        plugins::MatteShader::initialize,
                                        MPxNode::kDependNode,
                                        &plugins::classification::kAll));
    // Update hypershade
    MString cmd ("if (`window -exists createRenderNodeWindow`)\
                  {\
                      refreshCreateRenderNodeWindow (\"" + plugins::classification::kAll + "\");\
                  }");
    CHECK_MSTATUS (MGlobal::executeCommand (cmd));

    MGlobal::displayInfo ("loaded.");    

    return MStatus::kSuccess;    
}
/*
// ---------------------------------------------------------------------------
*/
auto uninitializePlugin (MObject obj) -> MStatus
{    
    MFnPlugin plugin (obj);

    // Unregister pre render command
    plugin.deregisterCommand (plugins::RendererCommand::kCommandName);


    // Unregister renderer
    plugins::RenderView::UnregisterRenderer ();


    // plugin.deregisterDisplayFilter ("Niepce");    
    CHECK_MSTATUS (plugin.deregisterNode (plugins::MatteShader::id));    
    MString cmd ("if (`window -exists createRenderNodeWindow`)\
                  {\
                      refreshCreateRenderNodeWindow (\"" + plugins::classification::kAll + "\");\
                  }");
    CHECK_MSTATUS (MGlobal::executeCommand (cmd));

    return MStatus::kSuccess;    
}
/*
// ---------------------------------------------------------------------------
*/