import maya.cmds     as mc
import maya.OpenMaya as om

# Allow to select niepce renderer from Render View and Render settings#
def registerRenderer ():
    # Defore register the renderer, you need to register command to eval the render
    
    try:
        # Register renderer
        mc.renderer ("niepce", rendererUIName = "Niepce Renderer")
        
        # Attach globals node
        mc.renderer ("niepce", edit = True, addGlobalsNode = "defaulRenderGlobals")
        mc.renderer ("niepce", edit = True, addGlobalsTab = ("Common", "createMayaSoftwareCommonGlobalsTab","updateMayaSoftwareCommonGlobalsTab"))
        
        # Pre render support
        #  - Render region is not supported
        #  - Batch render is not support
        mc.renderer ("niepce",
                     edit = True,
                     renderProcedure = "niepceBeginPreRendering",
                     commandRenderProcedure = "",
                     renderRegionProcedure = "",
                     batchRenderProcedure = "",
                     cancelBatchRenderProcedure = "")
    except:
        om.MGlobal.displayError ("Faild to register renderer.")


# Delete niepce renderer node from Maya
def unregisterRenderer ():
    try:
        mc.renderer ("niepce", edit = True, unregisterRenderer = True)
    except:
        om.MGlobal.displayError ("Faild to unregister renderer.")