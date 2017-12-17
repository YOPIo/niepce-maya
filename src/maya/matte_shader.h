#ifndef _MAYA_MATTE_SHADER_H_
#define _MAYA_MATTE_SHADER_H_
/*
// ---------------------------------------------------------------------------
*/
#include <maya/MPxNode.h>
/*
// ---------------------------------------------------------------------------
*/
namespace plugins
{
/*
// ---------------------------------------------------------------------------
*/
class MatteShader : public MPxNode
{
public:
    MatteShader()  = default;
    ~MatteShader() = default;

    MatteShader (const MatteShader&  matte) = default;
    MatteShader (      MatteShader&& matte) = default;

    auto operator = (const MatteShader&  matte) -> MatteShader& = default;
    auto operator = (      MatteShader&& matte) -> MatteShader& = default;

public:
    // creator () method allows Maya to instantiate instances of this node.
    // This method is called by every time a instance of the node is
    // requested by createNode command or MFnDependencyNode::create ()
    static auto creator ()    -> void*;
    static auto initialize () -> MStatus;

    auto compute
    (
        const MPlug&      plug,
              MDataBlock& block
    )
    -> MStatus override final;

    auto postConstructor () -> void override final;

public:
    static MTypeId id;

protected:
    // Member variables
    // Emission
    static MObject aEmission;
    static MObject aEmissionR;
    static MObject aEmissionG;
    static MObject aEmissionB;

    // Reflectance        
    static MObject aReflectance;   // Input reflectance component
    static MObject aReflectanceR;  // Input reflectance red component
    static MObject aReflectanceG;  // Input reflectance green component
    static MObject aReflectanceB;  // Input reflectance blue component

    // Out color
    static MObject aOutColor;      // Output reflectance component
    static MObject aOutColorR;     // Output reflectance red component
    static MObject aOutColorG;     // Output reflectance green component
    static MObject aOutColorB;     // Output reflectance blue component    
};
/*
// ---------------------------------------------------------------------------
*/
} // namespace plugins
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATTE_SHADER_H_