#ifndef _DEFINES_H_
#define _DEFINES_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include <maya/MGlobal.h>
#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MFloatVector.h>
/*
// ---------------------------------------------------------------------------
*/
#define NIEPCE_MAYA_VENDOR_STRING  "YOPIo"
#define NIEPCE_MAYA_VERSION_STRING "0.1.0"
/*
// ---------------------------------------------------------------------------
*/
#define NIEPCE_CHECK_MSTATUS(status, msg) \
{\
    MStatus s = (status);\
    if (s != MStatus::kSuccess)\
    {\
        MGlobal::displayError ("Niepce : " + MString ((msg)));\
    }\
}
/*
// ---------------------------------------------------------------------------
*/
namespace plugins
{
/*
// ---------------------------------------------------------------------------
*/
namespace classification
{
static const MString kHyperShade ("shader/surface");
static const MString kRenderNode ("rendernode/niepce/surface");
static const MString kViewport   ("drawdb/shader/surface");
static const MString kAll = kHyperShade + ":" + kRenderNode + ":" + kViewport;
};
/*
// ---------------------------------------------------------------------------
*/
inline auto ToNiepceVector3 (const MFloatVector& v) -> niepce::Vector3f
{
    return niepce::Vector3f (static_cast <niepce::Float> (v.x),
                             static_cast <niepce::Float> (v.y),
                             static_cast <niepce::Float> (v.z));
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace plugins
/*
// ---------------------------------------------------------------------------
*/
#endif // _DEFINES_H_