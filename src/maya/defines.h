#ifndef _DEFINES_H_
#define _DEFINES_H_
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MGlobal.h>
#include <maya/MStatus.h>
#include <maya/MString.h>
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
        MGlobal::displayError ("Niepce :" + MString ((msg)));\
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
}
/*
// ---------------------------------------------------------------------------
*/
#endif // _DEFINES_H_