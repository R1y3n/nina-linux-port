#include "talon_render_state.h"
#include <GL/gl.h>
#include <algorithm>

namespace
{
    // Direct3D 8 render-state ids used by the retail Talon renderer.
    constexpr uint32 D3DRS_ZENABLE = 7;
    constexpr uint32 D3DRS_ZWRITEENABLE = 14;
    constexpr uint32 D3DRS_ALPHATESTENABLE = 15;
    constexpr uint32 D3DRS_SRCBLEND = 19;
    constexpr uint32 D3DRS_DESTBLEND = 20;
    constexpr uint32 D3DRS_CULLMODE = 22;
    constexpr uint32 D3DRS_ZFUNC = 23;
    constexpr uint32 D3DRS_ALPHAREF = 24;
    constexpr uint32 D3DRS_ALPHAFUNC = 25;
    constexpr uint32 D3DRS_ALPHABLENDENABLE = 27;
    constexpr uint32 D3DRS_FOGENABLE = 28;
    constexpr uint32 D3DRS_FOGCOLOR = 34;

    constexpr uint32 D3DTSS_COLOROP = 1;
    constexpr uint32 D3DTSS_ALPHAOP = 4;
}

TalonRenderStateSystem &TalonRenderStateSystem::Instance()
{
    static TalonRenderStateSystem s;
    return s;
}

TalonRenderState TalonRenderStateSystem::Decode(const SharedTexture *texture) const
{
    if (!texture)
        return {};
    const auto *st = reinterpret_cast<const SharedTextureCompat *>(texture);
    return Decode(reinterpret_cast<const StateChangeCompat *>(st->m_pStateChange));
}

TalonRenderState TalonRenderStateSystem::Decode(const StateChangeCompat *sc) const
{
    TalonRenderState out{};
    if (!sc)
        return out;

    const uint32 rsCount = sc->m_RenderList.size();
    const uint32 tsCount = sc->m_TextureList.size();
    if (rsCount > 32 || tsCount > 32)
        return out;
    out.valid = true;

    for (uint32 i = 0; i < rsCount; ++i)
    {
        const RenderStateCompat &rs = sc->m_RenderList.m_pFirst[i];
        switch (rs.m_dwRenderStateType)
        {
        case D3DRS_ZENABLE:
            out.hasZEnable = true;
            out.zEnable = rs.m_dwRenderState != 0;
            break;
        case D3DRS_ZWRITEENABLE:
            out.hasZWriteEnable = true;
            out.zWriteEnable = rs.m_dwRenderState != 0;
            break;
        case D3DRS_ALPHATESTENABLE:
            out.hasAlphaTestEnable = true;
            out.alphaTestEnable = rs.m_dwRenderState != 0;
            break;
        case D3DRS_SRCBLEND:
            out.hasSrcBlend = true;
            out.srcBlend = rs.m_dwRenderState;
            break;
        case D3DRS_DESTBLEND:
            out.hasDestBlend = true;
            out.destBlend = rs.m_dwRenderState;
            break;
        case D3DRS_CULLMODE:
            out.hasCullMode = true;
            out.cullMode = rs.m_dwRenderState;
            break;
        case D3DRS_ZFUNC:
            out.hasZFunc = true;
            out.zFunc = rs.m_dwRenderState;
            break;
        case D3DRS_ALPHAREF:
            out.hasAlphaRef = true;
            out.alphaRef = rs.m_dwRenderState & 0xFFu;
            break;
        case D3DRS_ALPHAFUNC:
            out.hasAlphaFunc = true;
            out.alphaFunc = rs.m_dwRenderState;
            break;
        case D3DRS_ALPHABLENDENABLE:
            out.hasAlphaBlendEnable = true;
            out.alphaBlendEnable = rs.m_dwRenderState != 0;
            break;
        case D3DRS_FOGENABLE:
            out.hasFogEnable = true;
            out.fogEnable = rs.m_dwRenderState != 0;
            break;
        case D3DRS_FOGCOLOR:
            out.hasFogColor = true;
            out.fogColor = rs.m_dwRenderState;
            break;
        default:
            break;
        }
    }

    for (uint32 i = 0; i < tsCount; ++i)
    {
        const TextureStateCompat &ts = sc->m_TextureList.m_pFirst[i];
        if (ts.m_dwStage != 0)
            continue;
        if (ts.m_dwTextureStateType == D3DTSS_COLOROP)
        {
            out.hasStage0ColorOp = true;
            out.stage0ColorOp = ts.m_dwTextureState;
        }
        else if (ts.m_dwTextureStateType == D3DTSS_ALPHAOP)
        {
            out.hasStage0AlphaOp = true;
            out.stage0AlphaOp = ts.m_dwTextureState;
        }
    }
    return out;
}

uint32 TalonRenderStateSystem::MapBlendToGL(uint32 b) const
{
    switch (b)
    {
    case 1:
        return GL_ZERO; // D3DBLEND_ZERO
    case 2:
        return GL_ONE; // D3DBLEND_ONE
    case 3:
        return GL_SRC_COLOR; // D3DBLEND_SRCCOLOR
    case 4:
        return GL_ONE_MINUS_SRC_COLOR; // D3DBLEND_INVSRCCOLOR
    case 5:
        return GL_SRC_ALPHA; // D3DBLEND_SRCALPHA
    case 6:
        return GL_ONE_MINUS_SRC_ALPHA; // D3DBLEND_INVSRCALPHA
    case 7:
        return GL_DST_ALPHA; // D3DBLEND_DESTALPHA
    case 8:
        return GL_ONE_MINUS_DST_ALPHA; // D3DBLEND_INVDESTALPHA
    case 9:
        return GL_DST_COLOR; // D3DBLEND_DESTCOLOR
    case 10:
        return GL_ONE_MINUS_DST_COLOR; // D3DBLEND_INVDESTCOLOR
    case 11:
        return GL_SRC_ALPHA_SATURATE; // D3DBLEND_SRCALPHASAT
    default:
        return GL_ZERO;
    }
}

uint32 TalonRenderStateSystem::MapCompareToGL(uint32 c) const
{
    switch (c)
    {
    case 1:
        return GL_NEVER;
    case 2:
        return GL_LESS;
    case 3:
        return GL_EQUAL;
    case 4:
        return GL_LEQUAL;
    case 5:
        return GL_GREATER;
    case 6:
        return GL_NOTEQUAL;
    case 7:
        return GL_GEQUAL;
    case 8:
        return GL_ALWAYS;
    default:
        return GL_LEQUAL;
    }
}

float TalonRenderStateSystem::AlphaRef01(const TalonRenderState &s, float fallback) const
{
    if (!s.hasAlphaRef)
        return fallback;
    return std::clamp(static_cast<float>(s.alphaRef) / 255.0f, 0.0f, 1.0f);
}
