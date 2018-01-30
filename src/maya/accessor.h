/*
// ---------------------------------------------------------------------------
// Maya からカメラ、ジオメトリ、マテリアル情報を取得する
// ---------------------------------------------------------------------------
*/
#ifndef _ACCESSOR_H_
#define _ACCESSOR_H_
/*
// ---------------------------------------------------------------------------
// OpenMaya libs
// ---------------------------------------------------------------------------
*/
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
// niepce libs
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Construct niepce renderer system primitives from scene in maya.
// This function call 'ConstructTriangles' and ...
// ---------------------------------------------------------------------------
*/
auto ConstructPrimitives (std::vector <IndividualPtr>* primitives) -> MStatus;
/*
// ---------------------------------------------------------------------------
// Construct a camera from scene in maya
// ---------------------------------------------------------------------------
*/
auto ConstructCamera (std::shared_ptr<Camera>* camera, MDagPath* path) -> MStatus;
/*
// ---------------------------------------------------------------------------
// Access to geometries at the current scene in maya, converting all of them
// to niepce renderer file system triangle shape.
// ---------------------------------------------------------------------------
*/
auto ConstructTriangles
(
    MItDependencyNodes&     shading_endgine,
    std::vector <ShapePtr>* shapes
)
-> MStatus;
/*
// ---------------------------------------------------------------------------
// Find a renderable camera from the scene.
// Store the MDagPath of camera which is found at first to the argument.
// Return MStatus::kSuccess if present or MStatus::kFailure otherwise
// ---------------------------------------------------------------------------
*/
auto FindRenderableCamera (MDagPath* path) -> MStatus;
/*
// ---------------------------------------------------------------------------
*/
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _ACCESSOR_H_