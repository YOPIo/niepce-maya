#ifndef _MAYA_RENDERER_COMMAND_H_
#define _MAYA_RENDERER_COOMAND_H_

/*
// ---------------------------------------------------------------------------
// Description :
// A mel command that calling pre-rendering processing. This command is called
// by button where located at the Render-View.
// ---------------------------------------------------------------------------
*/
#include <maya/MPxCommand.h>
/*
// ---------------------------------------------------------------------------
*/
namespace plugins
{
/*
// ---------------------------------------------------------------------------
*/
class RendererCommand : public MPxCommand
{
public:
    RendererCommand () = default;
    virtual ~RendererCommand () = default;

public:
    RendererCommand (const RendererCommand&  creator) = default;
    RendererCommand (      RendererCommand&& creator) = default;

    auto operator = (const RendererCommand&  creator) -> RendererCommand&
        = default;
    auto operator = (      RendererCommand&& creator) -> RendererCommand&
        = default;

    /* RendererCommand public methods */
public:
    // This method is called by MFnPlugin.registerCommand ()
    // Return pointer
    static auto creator () -> void*;

    // This method is called when mel command named niepceBeginPreRendering
    // at the Maya.
    // Perform pre-rendering.
    auto doIt (const MArgList& args) -> MStatus override final;


    /* RendererCommand private methods */
private:
    auto BeginRendering () -> void;


public:
    // RendererCommand private data
    // 
    static const MString kCommandName;
};
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _MAYA_RENDERER_COMMAND_H_