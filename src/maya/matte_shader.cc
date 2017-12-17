#include "matte_shader.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MFloatVector.h>
/*
// ---------------------------------------------------------------------------
*/
namespace plugins
{
/*
// ---------------------------------------------------------------------------
// Input values
// ---------------------------------------------------------------------------
*/
MObject MatteShader::aReflectance;
MObject MatteShader::aReflectanceR;
MObject MatteShader::aReflectanceG;
MObject MatteShader::aReflectanceB;
MObject MatteShader::aEmission;
MObject MatteShader::aEmissionR;
MObject MatteShader::aEmissionG;
MObject MatteShader::aEmissionB;
/*
// ---------------------------------------------------------------------------
// Output value
// ---------------------------------------------------------------------------
*/
MObject MatteShader::aOutColor;
MObject MatteShader::aOutColorR;
MObject MatteShader::aOutColorG;
MObject MatteShader::aOutColorB;
// From 0x00000000 to 0x0007ffff in local test
MTypeId MatteShader::id (0x81000);
/*
// ---------------------------------------------------------------------------
*/
auto MatteShader::creator () -> void*
{
    // Implementation is simple, just return MatteShader object
    return new MatteShader ();
}
/*
// ---------------------------------------------------------------------------
*/
auto MatteShader::initialize () -> MStatus
{
    MStatus status;
    MFnNumericAttribute attr;

    // Create input attribute Emission
    aEmissionR = attr.create ("emissionR",
                              "er",
                              MFnNumericData::kFloat,
                              0,
                              &status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (attr.setKeyable (true));
    CHECK_MSTATUS (attr.setStorable (true));
    CHECK_MSTATUS (attr.setDefault (0.0))

    aEmissionG = attr.create ("emissionG",
                              "eg",
                              MFnNumericData::kFloat,
                              0,
                              &status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (attr.setKeyable (true));
    CHECK_MSTATUS (attr.setStorable (true));
    CHECK_MSTATUS (attr.setDefault (0.0))

    aEmissionB = attr.create ("emissionB",
                              "eb",
                              MFnNumericData::kFloat,
                              0,
                              &status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (attr.setKeyable (true));
    CHECK_MSTATUS (attr.setStorable (true));
    CHECK_MSTATUS (attr.setDefault (0.0))

    aEmission = attr.create ("emission",
                             "e",
                             aEmissionR,
                             aEmissionG,
                             aEmissionB,
                             &status);    
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (attr.setKeyable (true));
    CHECK_MSTATUS (attr.setStorable (true));
    CHECK_MSTATUS (attr.setDefault (0.0, 0.0, 0.0));
    CHECK_MSTATUS (attr.setUsedAsColor (true));

    // Create input attribute Reflectance
    aReflectanceR = attr.create ("reflectanceR",
                                 "rr",
                                 MFnNumericData::kFloat,
                                 0,
                                 &status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (attr.setKeyable (true));
    CHECK_MSTATUS (attr.setStorable (true));
    CHECK_MSTATUS (attr.setDefault (0.0))

    aReflectanceG = attr.create ("reflectanceG",
                                 "rg",
                                 MFnNumericData::kFloat,
                                 0,
                                 &status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (attr.setKeyable (true));
    CHECK_MSTATUS (attr.setStorable (true));
    CHECK_MSTATUS (attr.setDefault (0.0))

    aReflectanceB = attr.create ("reflectanceB",
                                 "rb",
                                 MFnNumericData::kFloat,
                                 0,
                                 &status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (attr.setKeyable (true));
    CHECK_MSTATUS (attr.setStorable (true));
    CHECK_MSTATUS (attr.setDefault (0.0))

    aReflectance = attr.create ("reflectance",
                                "r",
                                 aReflectanceR,
                                 aReflectanceG,
                                 aReflectanceB,
                                 &status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (attr.setKeyable (true));
    CHECK_MSTATUS (attr.setStorable (true));
    CHECK_MSTATUS (attr.setDefault (0.5, 0.5, 0.5));
    CHECK_MSTATUS (attr.setUsedAsColor (true));

    // Output attribute creation
    aOutColorR = attr.create ("outColorR",
                              "orr",
                              MFnNumericData::kFloat,
                              0,
                              &status);
    CHECK_MSTATUS (status);   

    aOutColorG = attr.create ("outColorG",
                              "org",
                               MFnNumericData::kFloat,
                               0,
                               &status);
    CHECK_MSTATUS (status);    

    aOutColorB = attr.create ("outColorB",
                              "orb",
                               MFnNumericData::kFloat,
                               0,
                               &status);
    CHECK_MSTATUS (status);
    
    aOutColor = attr.create ("outColor",
                             "or",
                             aOutColorR,
                             aOutColorG,
                             aOutColorB,
                             &status);
    CHECK_MSTATUS (status);
    CHECK_MSTATUS (attr.setHidden (false));
    CHECK_MSTATUS (attr.setReadable (true));
    CHECK_MSTATUS (attr.setWritable (false));

    // Add the attributes
    CHECK_MSTATUS (addAttribute (aOutColor));
    CHECK_MSTATUS (addAttribute (aEmission));
    CHECK_MSTATUS (addAttribute (aReflectance));

    CHECK_MSTATUS (attributeAffects (aEmissionR, aOutColor));
    CHECK_MSTATUS (attributeAffects (aEmissionG, aOutColor));
    CHECK_MSTATUS (attributeAffects (aEmissionB, aOutColor));
    CHECK_MSTATUS (attributeAffects (aReflectanceR, aOutColor));
    CHECK_MSTATUS (attributeAffects (aReflectanceG, aOutColor));
    CHECK_MSTATUS (attributeAffects (aReflectanceB, aOutColor));
    
    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
auto MatteShader::compute
(
    const MPlug&      plug,
          MDataBlock& block
)
-> MStatus
{    
    if ((plug != aOutColor && (plug.parent () != aOutColor)))
    {
        return MStatus::kUnknownParameter;
    }

    MStatus status;
    MFloatVector input
        = block.inputValue (aReflectance, &status).asFloatVector ();
    CHECK_MSTATUS (status);

    MDataHandle handle = block.outputValue (aOutColor, &status);
    CHECK_MSTATUS (status);
    MFloatVector& output = handle.asFloatVector ();
    output = input;
    handle.setClean ();

    return MStatus::kSuccess;
}
/*
// ---------------------------------------------------------------------------
*/
auto MatteShader::postConstructor () -> void
{
    setMPSafe (true);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace plugins
/*
// ---------------------------------------------------------------------------
*/