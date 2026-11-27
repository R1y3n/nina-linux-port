#pragma once
#include "../../lt_renderer_abi.h"
#include <cstdint>

struct TalonRenderState
{
    bool valid = false;

    bool hasAlphaBlendEnable = false;
    bool alphaBlendEnable = false;
    bool hasSrcBlend = false;
    bool hasDestBlend = false;
    uint32 srcBlend = 0;
    uint32 destBlend = 0;

    bool hasAlphaTestEnable = false;
    bool alphaTestEnable = false;
    bool hasAlphaRef = false;
    uint32 alphaRef = 0;
    bool hasAlphaFunc = false;
    uint32 alphaFunc = 0;

    bool hasZEnable = false;
    bool zEnable = true;
    bool hasZWriteEnable = false;
    bool zWriteEnable = true;
    bool hasZFunc = false;
    uint32 zFunc = 4; // D3DCMP_LESSEQUAL
    bool hasFogEnable = false;
    bool fogEnable = true;
    bool hasFogColor = false;
    uint32 fogColor = 0;
    bool hasCullMode = false;
    uint32 cullMode = 0;

    bool hasStage0ColorOp = false;
    uint32 stage0ColorOp = 0;
    bool hasStage0AlphaOp = false;
    uint32 stage0AlphaOp = 0;
};

class TalonRenderStateSystem final
{
public:
    static TalonRenderStateSystem &Instance();

    TalonRenderState Decode(const SharedTexture *texture) const;
    TalonRenderState Decode(const StateChangeCompat *stateChange) const;

    // D3D8 blend values used by Talon. Returned GLenum is expressed as uint32
    // here so this shared ABI-facing header does not need to include OpenGL.
    uint32 MapBlendToGL(uint32 d3dBlend) const;
    uint32 MapCompareToGL(uint32 d3dCompare) const;
    float AlphaRef01(const TalonRenderState &state, float fallback) const;

private:
    TalonRenderStateSystem() = default;
};
