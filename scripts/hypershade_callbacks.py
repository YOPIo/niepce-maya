import maya.cmds     as mc
import maya.mel      as mel
import maya.OpenMaya as om

# Callback function
# This function is called when hypershade is creating
def hyperShadePanelBuildCreateMenuCallback ():
    mc.menuItem (label = "niepce")
    mc.menuItem (divider = True)


# Callback function
# This function is called to figure out Maya's nodes and our original custom node
def hyperShadePanelBuildCreateSubMenuCallback ():    
    return "rendernode/niepce/surface"


# Callback function
# This function is called when plugin was loaded/unloaded
# This method works that does hypershade need to update or not.
def hyperShadePanelPluginChangeCallback (classification, changeType):    
    if 'rendernode/niepce' in classification:
        # Need to update
        return 1
    # Need not to update
    return 0


# Callback function
def createRenderNodeSelectNodeCategoriesCallback (flag, treeLister):
    if flag == "allWithNiepceUp":
        mc.treeLister (treeLister, edit = True, selectPath = "niepce")


# Callback function
# This method is called when some plugin changes to need to close 'Create Render Node'
# dialog
def createRenderNodePluginChangeCallback (classification):
    om.MGlobal.displayInfo ("Classification " + classification)
    if 'rendernode/niepce' in classification:
        # Need to close
        return 1
    # Need not to close
    return 0


# Callback function
# This method is called when Maya want to get classification for custom shading node.
def renderNodeClassificationCallback ():
    return 'rendernode/niepce'


# Function that return mel command as string
def createSurfaceNodeCommand (type):
    classification = mc.getClassification (type)

    for c in classification:
        mat = mc.shadingNode (type, asShader = True)
        shadingGroup = mc.sets (renderable = True,
                                noSurfaceShader = True,
                                empty = True,
                                name = mat + "SG")
        mc.connectAttr (mat + ".outColor", shadingGroup + ".surfaceShader")

    return ""


# Callback function
# This method is called when treelister or node would create from node editor
# Return mel command that appropriates for creating node
# postCommand is mel command that evaluates at last    
def createRenderNodeCommandCallback (postCommand, type):    
    if mc.getClassification (type, satisfies = 'rendernode/niepce/surface'):        
        # Type of current node is registered in surface classification
        #
        # Return a command as mel command string
        #  - Creating shading group node
        #  - Connect shading node's outColor to shading group's surfaceShader        
        python_cmd_str = ("import hypershade_callbacks;"
                          "hypershade_callbacks.createSurfaceNodeCommand (\\\"{0}\\\")").format (type)
        return "string $cmd = \"{0}\"; python ($cmd);".format (python_cmd_str)
    else:
        # om.MGlobal.displayError ("Faild to create render node.")
        return ""


# Callback function
# This method is called to decide to be used as material.
def nodeCanBeUsedAsMaterialCallback (nodeId, nodeOwner):
    if "niepce" == nodeOwner:
        return 1
    return 0
    
    

# Callback function
# This methods is called to add custom renderer classification to node tree lister
def buildRenderNodeTreeListerContentCallback (renderNodeTreeLister,
                                              postCommand,
                                              filterString):
    # Add 'surface' classification to 'rendernode/niepce/'
    mel_str = 'addToRenderNodeTreeLister ("{0}", "{1}", "{2}", "{3}", "{4}", "{5}");'
    melCommand = mel_str.format (renderNodeTreeLister,
                                 postCommand,
                                 "Niepce/Surface",
                                 "rendernode/niepce/surface",
                                 "-asShader",
                                 "")
    mel.eval (melCommand)


# Callback functions
# Hypershade registration
def registerHypershade ():
    hypershadeCallbacks = [("hyperShadePanelBuildCreateMenu",       hyperShadePanelBuildCreateMenuCallback),
                           ("hyperShadePanelBuildCreateSubMenu",    hyperShadePanelBuildCreateSubMenuCallback),
                           ("hyperShadePanelPluginChange",          hyperShadePanelPluginChangeCallback),
                           #("createRenderNodeSelectNodeCategories", createRenderNodeSelectNodeCategoriesCallback),
                           ("createRenderNodePluginChange",         createRenderNodePluginChangeCallback),
                           ("renderNodeClassification",             renderNodeClassificationCallback),
                           ("createRenderNodeCommand",              createRenderNodeCommandCallback),
                           ("nodeCanBeUsedAsMaterial",              nodeCanBeUsedAsMaterialCallback),
                           ("buildRenderNodeTreeListerContent",     buildRenderNodeTreeListerContentCallback) ]

    # Add callbacks
    for hook, callback in hypershadeCallbacks:
        mc.callbacks (addCallback = callback, hook = hook, owner = "niepce")