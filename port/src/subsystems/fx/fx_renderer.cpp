#include "../textures/texture_manager.h"
#include "../renderer/frame_constants.h"
#include "../world/world_renderer.h"
#include "lt_renderer_abi.h"
#include "gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "shaders/shader_manager.h"
#include "utils/log.h"
#include "utils/math.h"
#include "subsystems/renderer/fog_state.h"
#include "subsystems/textures/Texture.h"
#include "subsystems/renderer/Console.h"
#include "subsystems/textures/texture_manager.h"
#include "subsystems/fx/fx_renderer.h"
#include "subsystems/renderer/stock_render_options.h"
#include "subsystems/renderer/talon_render_state.h"

#include "shaders/shader_resources.h"

#include <GL/gl.h>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifndef __thiscall
#define __thiscall __attribute__((thiscall))
#endif

struct DrawPolyMgrCompat
{
    virtual int __thiscall DrawPrim(CanvasPrimVertexCompat *src, int32 count, uint32 flags);
    virtual int __thiscall SetState(uint32 index, uint32 value);
    virtual int __thiscall GetState(uint32 index, uint32 *value);
    virtual int __thiscall SetTexture(const char *name);
    virtual int __thiscall GetScale(float *x, float *y);

    SceneDesc *m_pScene = nullptr;
    CanvasCompat *m_pCanvas = nullptr;
    SharedTexture *m_pTexture = nullptr;
    uint32 m_State[8]{};
};
/*
struct DrawPolyMgrCompat
{
    virtual int DrawPrim(CanvasPrimVertexCompat *src, int32 count, uint32 flags);
    virtual int SetState(uint32 index, uint32 value);
    virtual int GetState(uint32 index, uint32 *value);
    virtual int SetTexture(const char *name);
    virtual int GetScale(float *x, float *y);

    SceneDesc *m_pScene = nullptr;
    CanvasCompat *m_pCanvas = nullptr;
    SharedTexture *m_pTexture = nullptr;
    uint32 m_State[8]{};
};*/

namespace
{
    struct FXVertex
    {
        LTVector pos;
        LTFloatPt uv;
        PGColor color;
    };

    static FXRendererState &FXState() { return FXRenderer::Instance().State(); }
    constexpr size_t MAX_FX_VERTS = 1024 * 1024;
    constexpr size_t FX_STREAM_FRAMES = 3;
    constexpr size_t FX_STREAM_SEGMENT_BYTES = MAX_FX_VERTS * sizeof(FXVertex);
    constexpr size_t FX_STREAM_TOTAL_BYTES = FX_STREAM_SEGMENT_BYTES * FX_STREAM_FRAMES;

    static size_t AlignUp64(size_t v) { return (v + 63u) & ~size_t(63u); }

    static bool FXStreamUpload(const void *data, size_t bytes)
    {
        auto &st = FXState();
        if (!data || bytes == 0 || bytes > FX_STREAM_SEGMENT_BYTES)
            return false;

        if (st.streamMapped)
        {
            const size_t aligned = AlignUp64(st.streamCursorBytes);
            if (aligned + bytes <= FX_STREAM_SEGMENT_BYTES)
            {
                const size_t absolute = st.streamFrameSlot * FX_STREAM_SEGMENT_BYTES + aligned;
                std::memcpy(static_cast<unsigned char *>(st.streamMapped) + absolute, data, bytes);
                st.streamCursorBytes = aligned + bytes;
                st.streamUsedThisFrame = true;
                GLUploadStats::Instance().RecordStreamWrite(GLUploadCategory::FX, bytes);
                glf.VertexArrayVertexBuffer(st.vao, 0, st.vbo, static_cast<GLintptr>(absolute), sizeof(FXVertex));
                return true;
            }
        }

        if (st.streamFallbackVbo)
        {
            GLTrackedNamedBufferSubData(st.streamFallbackVbo, 0, static_cast<GLsizeiptr>(bytes), data, GLUploadCategory::FX);
            glf.VertexArrayVertexBuffer(st.vao, 0, st.streamFallbackVbo, 0, sizeof(FXVertex));
            return true;
        }
        return false;
    }

    static LTVector PolyGridLocalToCamera(const SceneDesc *scene, const LTObjectCompat &o, LTVector local)
    {
        LTRotation oq{o.m_rRot.x, o.m_rRot.y, o.m_rRot.z, o.m_rRot.w};
        LTVector world = oq.Rotate(local) + LTVector {o.m_vPos.x, o.m_vPos.y, o.m_vPos.z};

        if (o.m_dwFlags & FLAG_REALLYCLOSE)
            return world;

        LTVector rel = world - LTVector {scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z};
        LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                      scene->m_rRotation.z, scene->m_rRotation.w};
        return cq.Conjugate().Rotate(rel);
    }

    static void SetupProjection(SceneDesc *scene, bool reallyClose)
    {
        const float tanX = std::tan(scene->m_fFovX * 0.5f);
        const float tanY = std::tan(scene->m_fFovY * 0.5f);
        const float nearZ = reallyClose ? 0.01f : 1.0f;
        const float farZ = std::max(nearZ + 1.0f, scene->m_fFarZ);

        FrameConstants::Instance().Apply(scene, tanX, tanY, nearZ, farZ);
    }

    static void ApplyBlend(const LTObjectCompat &o)
    {
        GLStateEnable(GL_BLEND);
        if (o.m_dwFlags2 & FLAG2_ADDITIVE)
            GLStateBlendFunc(GL_ONE, GL_ONE);
        else if (o.m_dwFlags2 & FLAG2_MULTIPLY)
            GLStateBlendFunc(GL_ZERO, GL_SRC_COLOR);
        else
            GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        GLStateDepthMask(GL_FALSE);
    }

    static GLenum MapD3DBlend(int b)
    {
        switch (b)
        {
        case 1: return GL_ZERO;
        case 2: return GL_ONE;
        case 3: return GL_SRC_COLOR;
        case 4: return GL_ONE_MINUS_SRC_COLOR;
        case 5: return GL_SRC_ALPHA;
        case 6: return GL_ONE_MINUS_SRC_ALPHA;
        case 7: return GL_DST_ALPHA;
        case 8: return GL_ONE_MINUS_DST_ALPHA;
        case 9: return GL_DST_COLOR;
        case 10: return GL_ONE_MINUS_DST_COLOR;
        case 11: return GL_SRC_ALPHA_SATURATE;
        default: return GL_ZERO;
        }
    }

    static const char *D3DBlendName(uint32 b)
    {
        switch (b)
        {
        case 1: return "ZERO";
        case 2: return "ONE";
        case 3: return "SRCCOLOR";
        case 4: return "INVSRCCOLOR";
        case 5: return "SRCALPHA";
        case 6: return "INVSRCALPHA";
        case 7: return "DESTALPHA";
        case 8: return "INVDESTALPHA";
        case 9: return "DESTCOLOR";
        case 10: return "INVDESTCOLOR";
        case 11: return "SRCALPHASAT";
        default: return "UNKNOWN";
        }
    }

    static const char *PolyGridBaseBlendName(const LTObjectCompat &o)
    {
        if (o.m_dwFlags2 & FLAG2_ADDITIVE) return "ADD ONE/ONE";
        if (o.m_dwFlags2 & FLAG2_MULTIPLY) return "MULTIPLY ZERO/SRCCOLOR";
        return "ALPHA SRCALPHA/INVSRCALPHA";
    }

    static GLenum MapCanvasBlend(uint32 value)
    {
        const int d3d = (value >= 1u && value <= 6u) ? static_cast<int>(value) : 2;
        return MapD3DBlend(d3d);
    }

    static uint32 MapCanvasColorOp(uint32 value)
    {
        return (value >= 1u && value <= 5u) ? value : 3u;
    }

    static uint32 MapCanvasAlphaOp(uint32 value)
    {
        return (value >= 1u && value <= 5u) ? value : 1u;
    }

    static void ApplyVolumetricFogUniforms()
    {
        GLUniform1i(FXState().uVFogEnabled, g_fogState.vFog ? 1 : 0);
        GLUniform1f(FXState().uVFogMinY, g_fogState.vFogMinY);
        GLUniform1f(FXState().uVFogMaxY, g_fogState.vFogMaxY);
        GLUniform1f(FXState().uVFogMinYVal, g_fogState.vFogMinYVal);
        GLUniform1f(FXState().uVFogMaxYVal, g_fogState.vFogMaxYVal);
        GLUniform1f(FXState().uVFogDensity, g_fogState.vFogDensity);
        GLUniform1f(FXState().uVFogMax, g_fogState.vFogMax);
    }

    static void DrawVertices(SceneDesc *scene, const LTObjectCompat &o,
                             SharedTexture *shared, std::vector<FXVertex> &verts,
                             int particleSrcBlend = 0, int particleDstBlend = 0)
    {
        if (verts.empty())
            return;
        if (verts.size() > MAX_FX_VERTS)
            verts.resize(MAX_FX_VERTS - (MAX_FX_VERTS % 3));

        Texture *tex = TextureManager::Instance().Ensure(shared, false);

        FXState().shader->Use();
        GLUniform1i(FXState().uCanvasOps, 0);
        GLUniform1i(FXState().uEnvMapEnabled, 0);
        SetupProjection(scene, (o.m_dwFlags & FLAG_REALLYCLOSE) != 0);
        GLUniform1i(FXState().uTextured, tex && tex->texture ? 1 : 0);
        GLStateBindTextureUnit(0, tex ? tex->texture : 0);
        const bool rc = (o.m_dwFlags & FLAG_REALLYCLOSE) != 0;
        const bool fogOn = g_fogState.enabled && !rc && !(o.m_dwFlags & FLAG_FOGDISABLE);
        GLUniform1i(FXState().uFogEnabled, fogOn ? 1 : 0);
        ApplyVolumetricFogUniforms();
        const bool particleBlendValid = particleSrcBlend >= 1 && particleSrcBlend <= 11 &&
                                        particleDstBlend >= 1 && particleDstBlend <= 11;
        const bool additiveFog = particleBlendValid
                                     ? (particleDstBlend == 2)
                                     : ((o.m_dwFlags2 & FLAG2_ADDITIVE) != 0);
        GLUniform1i(FXState().uFogAdditive, additiveFog ? 1 : 0);

        ApplyBlend(o);
        if (particleBlendValid)
        {
            GLStateEnable(GL_BLEND);
            GLStateBlendFunc(MapD3DBlend(particleSrcBlend), MapD3DBlend(particleDstBlend));
            GLStateDepthMask(GL_FALSE);
        }
        GLStateDisable(GL_CULL_FACE);
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);

        if (!FXStreamUpload(verts.data(), verts.size() * sizeof(FXVertex)))
            return;
        GLStateBindVertexArray(FXState().vao);
        glf.DrawArrays(GL_TRIANGLES_, 0, static_cast<GLsizei>(verts.size()));

        GLStateDepthMask(GL_TRUE);
    }

    static void DrawPolyGridVertices(SceneDesc *scene, const PolyGridCompat &grid,
                                     SharedTexture *shared, SharedTexture *envShared,
                                     std::vector<FXVertex> &verts)
    {
        if (verts.empty())
            return;
        if (verts.size() > MAX_FX_VERTS)
            verts.resize(MAX_FX_VERTS - (MAX_FX_VERTS % 3));

        Texture *tex = TextureManager::Instance().Ensure(shared, false);
        Texture *env = (FXState().envMapPolyGrids && envShared)
                           ? TextureManager::Instance().Ensure(envShared, false)
                           : nullptr;

        FXState().shader->Use();
        GLUniform1i(FXState().uCanvasOps, 0);
        SetupProjection(scene, (grid.m_Base.m_dwFlags & FLAG_REALLYCLOSE) != 0);
        GLUniform1i(FXState().uTextured, tex && tex->texture ? 1 : 0);
        GLStateBindTextureUnit(0, tex ? tex->texture : 0);
        const bool envOn = env && env->texture;
        GLUniform1i(FXState().uEnvMapEnabled, envOn ? 1 : 0);
        GLStateBindTextureUnit(1, envOn ? env->texture : 0);

        const bool rc = (grid.m_Base.m_dwFlags & FLAG_REALLYCLOSE) != 0;
        const bool fogOn = g_fogState.enabled && !rc && !(grid.m_Base.m_dwFlags & FLAG_FOGDISABLE);
        GLUniform1i(FXState().uFogEnabled, fogOn ? 1 : 0);
        ApplyVolumetricFogUniforms();
        GLUniform1i(FXState().uFogAdditive, (grid.m_Base.m_dwFlags2 & FLAG2_ADDITIVE) ? 1 : 0);

        ApplyBlend(grid.m_Base);
        GLStateDisable(GL_CULL_FACE);
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);

        if (!FXStreamUpload(verts.data(), verts.size() * sizeof(FXVertex)))
            return;
        GLStateBindVertexArray(FXState().vao);

        bool pgProbeValid = false;
        int pgProbeX = 0, pgProbeY = 0;
        float pgProbeU = 0.0f, pgProbeV = 0.0f;
        float pgProbeR = 0.0f, pgProbeG = 0.0f, pgProbeB = 0.0f;
        unsigned char pgBefore[4] = {0,0,0,0};
        static uint32 pgProbeDivider = 0;
        const bool pgDoProbe = LogIsSessionEnabled() &&
                               ((grid.m_Base.m_dwFlags2 & FLAG2_MULTIPLY) != 0) &&
                               ((pgProbeDivider++ % 30u) == 0u);
        if (pgDoProbe && verts.size() >= 3)
        {
            GLint vp[4] = {0,0,0,0};
            glGetIntegerv(GL_VIEWPORT, vp);
            const float tanX = std::tan(scene->m_fFovX * 0.5f);
            const float tanY = std::tan(scene->m_fFovY * 0.5f);
            for (size_t ti = 0; ti + 2 < verts.size(); ti += 3)
            {
                const FXVertex &a = verts[ti + 0];
                const FXVertex &b = verts[ti + 1];
                const FXVertex &c = verts[ti + 2];
                const float cz = (a.pos.z + b.pos.z + c.pos.z) * (1.0f / 3.0f);
                if (!(cz > 1.0f))
                    continue;
                const float cx = (a.pos.x + b.pos.x + c.pos.x) * (1.0f / 3.0f);
                const float cy = (a.pos.y + b.pos.y + c.pos.y) * (1.0f / 3.0f);
                const float ndcX = cx / (tanX * cz);
                const float ndcY = cy / (tanY * cz);
                if (ndcX < -0.85f || ndcX > 0.85f || ndcY < -0.85f || ndcY > 0.85f)
                    continue;
                pgProbeX = vp[0] + static_cast<int>((ndcX * 0.5f + 0.5f) * float(vp[2]));
                pgProbeY = vp[1] + static_cast<int>((ndcY * 0.5f + 0.5f) * float(vp[3]));
                pgProbeU = (a.uv.x + b.uv.x + c.uv.x) * (1.0f / 3.0f);
                pgProbeV = (a.uv.y + b.uv.y + c.uv.y) * (1.0f / 3.0f);
                pgProbeR = (a.color.x + b.color.x + c.color.x) * (1.0f / 3.0f);
                pgProbeG = (a.color.y + b.color.y + c.color.y) * (1.0f / 3.0f);
                pgProbeB = (a.color.z + b.color.z + c.color.z) * (1.0f / 3.0f);
                glReadPixels(pgProbeX, pgProbeY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pgBefore);
                pgProbeValid = (glGetError() == GL_NO_ERROR);
                break;
            }
        }

        glf.DrawArrays(GL_TRIANGLES_, 0, static_cast<GLsizei>(verts.size()));

        if (pgDoProbe && pgProbeValid)
        {
            unsigned char pgAfter[4] = {0,0,0,0};
            glReadPixels(pgProbeX, pgProbeY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pgAfter);
            const GLenum pgErr = glGetError();
            if (pgErr == GL_NO_ERROR)
            {
                const float br = pgBefore[0] * (1.0f / 255.0f);
                const float bg = pgBefore[1] * (1.0f / 255.0f);
                const float bb = pgBefore[2] * (1.0f / 255.0f);
                const float ar = pgAfter[0] * (1.0f / 255.0f);
                const float ag = pgAfter[1] * (1.0f / 255.0f);
                const float ab = pgAfter[2] * (1.0f / 255.0f);
                const float sr = (br > 1.0f/255.0f) ? (ar / br) : -1.0f;
                const float sg = (bg > 1.0f/255.0f) ? (ag / bg) : -1.0f;
                const float sb = (bb > 1.0f/255.0f) ? (ab / bb) : -1.0f;
                const float tr = (sr >= 0.0f && pgProbeR > 1.0e-5f) ? (sr / pgProbeR) : -1.0f;
                const float tg = (sg >= 0.0f && pgProbeG > 1.0e-5f) ? (sg / pgProbeG) : -1.0f;
                const float tb = (sb >= 0.0f && pgProbeB > 1.0e-5f) ? (sb / pgProbeB) : -1.0f;
                LOG_SESSION("FX3D POLYGRID-BLENDPROBE grid=%p xy=(%d,%d) uv=(%.6f %.6f) diffuse=(%.4f %.4f %.4f) before=(%u %u %u) after=(%u %u %u) inferredSource=(%.4f %.4f %.4f) inferredTexture=(%.4f %.4f %.4f) equation=ZERO/SRCCOLOR",
                            &grid, pgProbeX, pgProbeY, pgProbeU, pgProbeV,
                            pgProbeR, pgProbeG, pgProbeB,
                            unsigned(pgBefore[0]), unsigned(pgBefore[1]), unsigned(pgBefore[2]),
                            unsigned(pgAfter[0]), unsigned(pgAfter[1]), unsigned(pgAfter[2]),
                            sr, sg, sb, tr, tg, tb);
            }
            else
            {
                LOG_SESSION("FX3D POLYGRID-BLENDPROBE grid=%p readbackAfterError=0x%04X", &grid, unsigned(pgErr));
            }
        }
        else if (pgDoProbe && !pgProbeValid)
        {
            LOG_SESSION("FX3D POLYGRID-BLENDPROBE grid=%p unavailable", &grid);
        }

        GLStateDepthMask(GL_TRUE);

        static int envLogBudget = 24;
        if (LogIsSessionEnabled() && (envOn && (envLogBudget > 0 && envLogBudget--)))
            LOG_SESSION("FX3D POLYGRID-ENVMAP grid=%p env=%p GL=%u cvar=1 path=CAMSPACE-REFLECTION/MODULATE2X",
                        &grid, envShared, env->texture);
    }

    static void DrawLineVertices(SceneDesc *scene, const LTObjectCompat &o,
                                 const std::vector<FXVertex> &verts)
    {
        if (verts.size() < 2)
            return;

        FXState().shader->Use();
        GLUniform1i(FXState().uCanvasOps, 0);
        GLUniform1i(FXState().uEnvMapEnabled, 0);
        SetupProjection(scene, (o.m_dwFlags & FLAG_REALLYCLOSE) != 0);
        GLUniform1i(FXState().uTextured, 0);
        GLStateBindTextureUnit(0, 0);

        GLUniform1i(FXState().uFogEnabled, 0);
        GLUniform1i(FXState().uFogAdditive, 0);

        GLStateEnable(GL_BLEND);
        GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLStateDepthMask(GL_FALSE);
        GLStateDisable(GL_CULL_FACE);
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);
        glLineWidth(1.0f);

        if (!FXStreamUpload(verts.data(), verts.size() * sizeof(FXVertex)))
            return;
        GLStateBindVertexArray(FXState().vao);
        glf.DrawArrays(GL_LINES, 0, static_cast<GLsizei>(verts.size()));

        GLStateDepthMask(GL_TRUE);
    }

    static uint8 TalonLineByte(float v)
    {
        return static_cast<uint8>(static_cast<int32>(v));
    }

    static FXVertex LerpLineVertex(const FXVertex &a, const FXVertex &b, float t)
    {
        FXVertex r{};
        r.pos.x = a.pos.x + (b.pos.x - a.pos.x) * t;
        r.pos.y = a.pos.y + (b.pos.y - a.pos.y) * t;
        r.pos.z = a.pos.z + (b.pos.z - a.pos.z) * t;
        r.uv.x = 0.0f;
        r.uv.y = 0.0f;
        r.color.x = a.color.x + (b.color.x - a.color.x) * t;
        r.color.y = a.color.y + (b.color.y - a.color.y) * t;
        r.color.z = a.color.z + (b.color.z - a.color.z) * t;
        r.color.a = a.color.a + (b.color.a - a.color.a) * t;
        return r;
    }

    static LTVector CanvasWorldToCamera(const SceneDesc *scene, LTVector world, bool reallyClose)
    {
        if (reallyClose)
            return world;
        const LTVector rel = world - LTVector{scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z};
        LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                scene->m_rRotation.z, scene->m_rRotation.w};
        return cq.Conjugate().Rotate(rel);
    }

    static void DecodeD3DColor(uint32 c, float &r, float &g, float &b, float &a)
    {
        a = ((c >> 24) & 0xFFu) / 255.0f;
        r = ((c >> 16) & 0xFFu) / 255.0f;
        g = ((c >> 8) & 0xFFu) / 255.0f;
        b = ((c) & 0xFFu) / 255.0f;
    }

} // namespace

static void ResetCanvasManager(DrawPolyMgrCompat &mgr, SceneDesc *scene, CanvasCompat *canvas)
{
    mgr.m_pScene = scene;
    mgr.m_pCanvas = canvas;
    mgr.m_pTexture = nullptr;
    const uint32 defaults[8] = {0, 1, 1, 5, 6, 1, 3, 2};
    for (uint32 i = 0; i < 8u; ++i)
        mgr.m_State[i] = defaults[i];
}

int DrawPolyMgrCompat::SetState(uint32 index, uint32 value)
{
    if (!this)
        return 1;
    if (index >= 8u)
        return 1;
    m_State[index] = value;
    return 0;
}

int DrawPolyMgrCompat::GetState(uint32 index, uint32 *value)
{
    if (!this || !value || index >= 8u)
        return 1;
    *value = m_State[index];
    return 0;
}

int DrawPolyMgrCompat::SetTexture(const char *name)
{
    if (!this)
        return 1;
    if (!name)
    {
        m_pTexture = nullptr;
        return 0;
    }
    RenderStruct *rs = FXRenderer::Instance().GetRenderStruct();
    if (!rs || !rs->GetSharedTexture)
        return 1;
    SharedTexture *shared = rs->GetSharedTexture(name);
    if (!shared)
        return 1;
    Texture *tex = TextureManager::Instance().Ensure(shared, false);
    if (!tex || !tex->texture)
        return 1;
    m_pTexture = shared;

    static int budget = 24;
    if (LogIsSessionEnabled() && ((budget > 0 && budget--)))
        LOG_SESSION("FX3D CANVAS SetTexture name='%s' shared=%p gl=%u", name, shared, unsigned(tex->texture));
    return 0;
}

int DrawPolyMgrCompat::GetScale(float *x, float *y)
{
    if (!this || !x || !y)
        return 1;

    Texture *tex = TextureManager::Instance().GetCached(m_pTexture);
    if (!tex && m_pTexture)
        tex = TextureManager::Instance().Ensure(m_pTexture, false);

    if (tex)
    {
        const uint32 sw = std::max<uint32>(1u, tex->scaledWidth);
        const uint32 sh = std::max<uint32>(1u, tex->scaledHeight);
        *x = 1.0f / static_cast<float>(sw);
        *y = 1.0f / static_cast<float>(sh);

        static int budget = 48;
        if (LogIsSessionEnabled() && ((budget > 0 && budget--)))
            LOG_SESSION("FX3D CANVAS GetScale tex=%p gl=%u scaled=%ux%u -> (%.8f %.8f) path=D3D-0x10022A73/RTextureScale",
                        m_pTexture, unsigned(tex->texture), unsigned(sw), unsigned(sh), *x, *y);
    }
    else
    {
        *x = 1.0f;
        *y = 1.0f;
        static int budget = 12;
        if (LogIsSessionEnabled() && ((budget > 0 && budget--)))
            LOG_SESSION("FX3D CANVAS GetScale tex=NULL -> (1,1) path=D3D-0x10022A73/no-active-texture");
    }
    return 0;
}

int DrawPolyMgrCompat::DrawPrim(CanvasPrimVertexCompat *src, int32 count, uint32 flags)
{
    if (!this || !m_pScene || !m_pCanvas || !src || count < 3)
        return 1;

    const size_t n = std::min<size_t>(static_cast<size_t>(count), MAX_FX_VERTS);
    std::vector<FXVertex> verts;
    verts.reserve(n);
    const bool reallyClose = (m_pCanvas->m_Base.m_dwFlags & FLAG_REALLYCLOSE) != 0;
    const bool specialProjection = reallyClose || ((flags & 0x40u) != 0);

    for (size_t i = 0; i < n; ++i)
    {
        const CanvasPrimVertexCompat &in = src[i];
        const LTVector cam = CanvasWorldToCamera(m_pScene, {in.x, in.y, in.z}, specialProjection);
        float r, g, b, a;
        DecodeD3DColor(in.diffuse, r, g, b, a);
        verts.push_back({cam, LTFloatPt(in.u, in.v), PGColor(r, g, b, a)});
    }

    Texture *tex = TextureManager::Instance().Ensure(m_pTexture, false);
    FXState().shader->Use();
    SetupProjection(m_pScene, specialProjection);
    GLUniform1i(FXState().uTextured, tex && tex->texture ? 1 : 0);
    GLStateBindTextureUnit(0, tex ? tex->texture : 0);
    if (tex && tex->texture)
    {
        const GLint wrap = (m_State[5] == 2u) ? GL_CLAMP_TO_EDGE_ : GL_REPEAT;
        glf.TextureParameteri(tex->texture, GL_TEXTURE_WRAP_S_, wrap);
        glf.TextureParameteri(tex->texture, GL_TEXTURE_WRAP_T_, wrap);
    }
    GLUniform1i(FXState().uEnvMapEnabled, 0);
    GLUniform1i(FXState().uCanvasOps, 1);
    const uint32 colorOp = MapCanvasColorOp(m_State[6]);
    const uint32 alphaOp = MapCanvasAlphaOp(m_State[7]);
    GLUniform1i(FXState().uCanvasColorOp, static_cast<GLint>(colorOp));
    GLUniform1i(FXState().uCanvasAlphaOp, static_cast<GLint>(alphaOp));

    const LTObjectCompat &o = m_pCanvas->m_Base;
    const bool fogOn = g_fogState.enabled && !specialProjection && !(o.m_dwFlags & FLAG_FOGDISABLE);
    GLUniform1i(FXState().uFogEnabled, fogOn ? 1 : 0);
    ApplyVolumetricFogUniforms();
    GLUniform1i(FXState().uFogAdditive, (m_State[0] && m_State[4] == 2u) ? 1 : 0);

    if (m_State[0])
        GLStateEnable(GL_BLEND);
    else
        GLStateDisable(GL_BLEND);
    GLStateBlendFunc(MapCanvasBlend(m_State[3]), MapCanvasBlend(m_State[4]));
    if (m_State[1])
        GLStateEnable(GL_DEPTH_TEST);
    else
        GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthFunc(GL_LEQUAL);
    GLStateDepthMask(m_State[2] ? GL_TRUE : GL_FALSE);
    GLStateDisable(GL_CULL_FACE);
    if (specialProjection)
        GLStateDepthRange(0.0, 0.1);

    static int canvasDrawBudget = 80;
    if (LogIsSessionEnabled() && ((canvasDrawBudget > 0 && canvasDrawBudget--)))
        LOG_SESSION("FX3D CANVAS-DRAW canvas=%p verts=%d flags=%08x rc=%d special=%d tex=%p "
                    "state=[blend:%u z:%u zw:%u src:%u dst:%u addr:%u cop:%u->%u aop:%u->%u]",
                    m_pCanvas, int(count), unsigned(flags), reallyClose ? 1 : 0, specialProjection ? 1 : 0, m_pTexture,
                    unsigned(m_State[0]), unsigned(m_State[1]), unsigned(m_State[2]),
                    unsigned(m_State[3]), unsigned(m_State[4]), unsigned(m_State[5]),
                    unsigned(m_State[6]), unsigned(colorOp), unsigned(m_State[7]), unsigned(alphaOp));

    if (!FXStreamUpload(verts.data(), verts.size() * sizeof(FXVertex)))
    {
        if (specialProjection)
            GLStateDepthRange(0.0, 1.0);
        return 0;
    }
    GLStateBindVertexArray(FXState().vao);
    glf.DrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(verts.size()));

    if (specialProjection)
        GLStateDepthRange(0.0, 1.0);

    return 0;
}

bool FXRenderer::Init()
{
    auto *shader = avp2::render::ShaderManager::Instance().CreateGraphicsFromResources("fx.main",
                                                                                       avp2::render::ShaderResourceId::FxVertex,
                                                                                       avp2::render::ShaderResourceId::FxFragment);
    if (!shader)
        return false;
    FXState().shader = shader;

    FXState().uTanHalfFovX = shader->Uniform("uTanHalfFovX");
    FXState().uTanHalfFovY = shader->Uniform("uTanHalfFovY");
    FXState().uNearZ = shader->Uniform("uNearZ");
    FXState().uFarZ = shader->Uniform("uFarZ");
    FXState().uTextured = shader->Uniform("uTextured");
    FXState().uFogEnabled = shader->Uniform("uFogEnabled");
    FXState().uFogColor = shader->Uniform("uFogColor");
    FXState().uFogNear = shader->Uniform("uFogNear");
    FXState().uFogFar = shader->Uniform("uFogFar");
    FXState().uFogAdditive = shader->Uniform("uFogAdditive");
    FXState().uVFogEnabled = shader->Uniform("uVFogEnabled");
    FXState().uVFogMinY = shader->Uniform("uVFogMinY");
    FXState().uVFogMaxY = shader->Uniform("uVFogMaxY");
    FXState().uVFogMinYVal = shader->Uniform("uVFogMinYVal");
    FXState().uVFogMaxYVal = shader->Uniform("uVFogMaxYVal");
    FXState().uVFogDensity = shader->Uniform("uVFogDensity");
    FXState().uVFogMax = shader->Uniform("uVFogMax");
    FXState().uEnvMapEnabled = shader->Uniform("uEnvMapEnabled");
    FXState().uEnvMap = shader->Uniform("uEnvMap");
    FXState().uCanvasOps = shader->Uniform("uCanvasOps");
    FXState().uCanvasColorOp = shader->Uniform("uCanvasColorOp");
    FXState().uCanvasAlphaOp = shader->Uniform("uCanvasAlphaOp");

    glf.CreateVertexArrays(1, &FXState().vao);
    glf.CreateBuffers(1, &FXState().vbo);
    glf.CreateBuffers(1, &FXState().streamFallbackVbo);
    if (glf.MapNamedBufferRange && !GLRenderDocCaptureCompatEnabled())
    {
        const GLbitfield streamFlags = GL_MAP_WRITE_BIT_ | GL_MAP_PERSISTENT_BIT_ | GL_MAP_COHERENT_BIT_;
        glf.NamedBufferStorage(FXState().vbo,
                               static_cast<GLsizeiptr>(FX_STREAM_TOTAL_BYTES), nullptr, streamFlags);
        FXState().streamMapped = glf.MapNamedBufferRange(
            FXState().vbo, 0, static_cast<GLsizeiptr>(FX_STREAM_TOTAL_BYTES), streamFlags);
    }
    else
    {
        glf.NamedBufferStorage(FXState().vbo,
                               static_cast<GLsizeiptr>(FX_STREAM_SEGMENT_BYTES), nullptr, GL_DYNAMIC_STORAGE_BIT_);
        FXState().streamMapped = nullptr;
    }
    glf.NamedBufferStorage(FXState().streamFallbackVbo,
                           static_cast<GLsizeiptr>(FX_STREAM_SEGMENT_BYTES), nullptr, GL_DYNAMIC_STORAGE_BIT_);

    glf.VertexArrayVertexBuffer(FXState().vao, 0, FXState().vbo, 0, sizeof(FXVertex));

    glf.EnableVertexArrayAttrib(FXState().vao, 0);
    glf.VertexArrayAttribFormat(FXState().vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(FXVertex, pos.x));
    glf.VertexArrayAttribBinding(FXState().vao, 0, 0);

    glf.EnableVertexArrayAttrib(FXState().vao, 1);
    glf.VertexArrayAttribFormat(FXState().vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(FXVertex, uv.x));
    glf.VertexArrayAttribBinding(FXState().vao, 1, 0);

    glf.EnableVertexArrayAttrib(FXState().vao, 2);
    glf.VertexArrayAttribFormat(FXState().vao, 2, 4, GL_FLOAT, GL_FALSE, offsetof(FXVertex, color.x));
    glf.VertexArrayAttribBinding(FXState().vao, 2, 0);

    LOG_SESSION("FXRenderer::Init: persistent stream %s, segment=%zu KB x %zu",
                FXState().streamMapped ? "ON" : "FALLBACK", FX_STREAM_SEGMENT_BYTES / 1024, FX_STREAM_FRAMES);
    LOG_SESSION("FXRenderer::Init");
    return true;
}

void FXRenderer::AdvanceStreamFrame()
{
    auto &st = FXState();
    if (!st.streamMapped || !glf.FenceSync || !glf.ClientWaitSync || !glf.DeleteSync)
    {
        st.streamCursorBytes = 0;
        st.streamUsedThisFrame = false;
        return;
    }

    if (st.streamUsedThisFrame)
    {
        if (st.streamFences[st.streamFrameSlot])
            glf.DeleteSync(st.streamFences[st.streamFrameSlot]);
        st.streamFences[st.streamFrameSlot] = glf.FenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE_, 0);
    }

    const uint32_t next = (st.streamFrameSlot + 1u) % static_cast<uint32_t>(FX_STREAM_FRAMES);
    if (st.streamFences[next])
    {
        const GLenum wait = glf.ClientWaitSync(st.streamFences[next], GL_SYNC_FLUSH_COMMANDS_BIT_, GL_TIMEOUT_IGNORED_);
        if (wait == GL_WAIT_FAILED_)
            LOG_SESSION("FX persistent stream: glClientWaitSync failed on slot %u", next);
        glf.DeleteSync(st.streamFences[next]);
        st.streamFences[next] = nullptr;
    }
    st.streamFrameSlot = next;
    st.streamCursorBytes = 0;
    st.streamUsedThisFrame = false;
}

void FXRenderer::Term()
{
    for (void *&fence : FXState().streamFences)
    {
        if (fence && glf.DeleteSync)
        {
            glf.DeleteSync(fence);
            fence = nullptr;
        }
    }
    FXState().streamMapped = nullptr;
    if (FXState().streamFallbackVbo)
        glf.DeleteBuffers(1, &FXState().streamFallbackVbo);
    if (FXState().vbo)
        glf.DeleteBuffers(1, &FXState().vbo);
    if (FXState().vao)
        GLStateDeleteVertexArrays(1, &FXState().vao);
    avp2::render::ShaderManager::Instance().Release("fx.main");
    FXState().vbo = FXState().streamFallbackVbo = FXState().vao = 0;
    FXState().shader = nullptr;
}

bool FXRenderer::RenderParticleSystem(SceneDesc *scene, ParticleSystemCompat *system)
{
    if (!StockRenderOptions::Instance().DrawParticles())
        return true;
    if (!scene || !system || system->m_nParticles <= 0)
        return false;

    SharedTexture *shared = system->m_pCurTexture;
    const char *textureSource = shared ? "CURTEXTURE" : "NONE";
    if (!shared && system->m_SpriteTracker.m_pCurFrame &&
        system->m_SpriteTracker.m_pCurFrame->m_pTexture)
    {
        shared = system->m_SpriteTracker.m_pCurFrame->m_pTexture;
        textureSource = "TRACKER-FRAME";
    }

    auto findTextureInAnim = [&](SpriteAnimCompat *anim) -> SharedTexture *
    {
        if (!anim || !anim->m_pFrames || anim->m_nFrames == 0 || anim->m_nFrames > 4096)
            return nullptr;
        for (uint32 i = 0; i < anim->m_nFrames; ++i)
            if (anim->m_pFrames[i].m_pTexture)
                return anim->m_pFrames[i].m_pTexture;
        return nullptr;
    };

    if (!shared)
    {
        shared = findTextureInAnim(system->m_SpriteTracker.m_pCurAnim);
        if (shared)
            textureSource = "TRACKER-ANIM";
    }
    if (!shared && system->m_pSprite && system->m_pSprite->m_pAnims &&
        system->m_pSprite->m_nAnims > 0 && system->m_pSprite->m_nAnims <= 256)
    {
        for (uint32 ai = 0; ai < system->m_pSprite->m_nAnims && !shared; ++ai)
            shared = findTextureInAnim(&system->m_pSprite->m_pAnims[ai]);
        if (shared)
            textureSource = "SPRITE-ANIM";
    }
    if (!shared)
    {
        static std::unordered_set<const ParticleSystemCompat *> s_unresolved;
        if (LogIsSessionEnabled() && (s_unresolved.insert(system).second))
            LOG_SESSION("FX3D PARTICLE-MATERIAL-UNRESOLVED system=%p count=%d", system, system->m_nParticles);
        return false;
    }

    Texture *tex = TextureManager::Instance().Ensure(shared, false);
    if (!tex || !tex->texture)
        return false;

    const float tw = static_cast<float>(std::max(1u, tex->width));
    const float th = static_cast<float>(std::max(1u, tex->height));
    const float minU = std::min(0.5f, 2.0f / tw);
    const float minV = std::min(0.5f, 2.0f / th);
    const float maxU = std::max(minU, (tw - 2.0f) / tw);
    const float maxV = std::max(minV, (th - 2.0f) / th);

    int srcBlend = system->m_nSrcBlend;
    int dstBlend = system->m_nDestBlend;
    if (FXState().psSrcBlendOverride >= 1 && FXState().psSrcBlendOverride <= 11)
        srcBlend = FXState().psSrcBlendOverride;
    if (FXState().psDestBlendOverride >= 1 && FXState().psDestBlendOverride <= 11)
        dstBlend = FXState().psDestBlendOverride;

    constexpr int kStockParticleBatch = 128;
    std::vector<FXVertex> verts;
    verts.reserve(kStockParticleBatch * 6);

    const bool reallyClose = (system->m_Base.m_dwFlags & FLAG_REALLYCLOSE) != 0;
    const float nearZ = reallyClose ? 0.01f : 1.0f;
    const float farZ = std::max(nearZ + 1.0f, scene->m_fFarZ);
    const float tanX = std::max(1.0e-6f, std::tan(scene->m_fFovX * 0.5f));
    const float tanY = std::max(1.0e-6f, std::tan(scene->m_fFovY * 0.5f));

    LTParticleCompat *part = system->m_ParticleHead.m_pNext;
    int visited = 0, drawn = 0, culled = 0, batches = 0;
    static int logBudget = 96;
    const bool logParticles = LogIsSessionEnabled() && logBudget > 0;
    float minSize = 1.0e30f, maxSize = 0.0f;

    auto flush = [&]()
    {
        if (verts.empty())
            return;
        DrawVertices(scene, system->m_Base, shared, verts, srcBlend, dstBlend);
        verts.clear();
        ++batches;
    };

    while (part && part != &system->m_ParticleHead &&
           visited < system->m_nParticles && visited < 100000)
    {
        ++visited;
        LTParticleCompat *next = part->m_pNext;

        LTVector c = ObjectLocalToCamera(scene, system->m_Base,
                                         {part->m_vPos.x, part->m_vPos.y, part->m_vPos.z});

        const float sz = std::max(0.0f, std::fabs(part->m_fSize));
        if (logParticles)
        {
            minSize = std::min(minSize, sz);
            maxSize = std::max(maxSize, sz);
        }

        bool outside = !std::isfinite(c.x) || !std::isfinite(c.y) || !std::isfinite(c.z) ||
                       !std::isfinite(sz) || c.z + sz < nearZ || c.z - sz > farZ;
        if (!outside && c.z > 1.0e-6f)
        {
            const float halfX = c.z * tanX + sz;
            const float halfY = c.z * tanY + sz;
            outside = (c.x < -halfX || c.x > halfX || c.y < -halfY || c.y > halfY);
        }
        if (outside || sz <= 0.0f)
        {
            ++culled;
            part = next;
            continue;
        }

        const float r = std::clamp((part->m_vColor.x / 255.0f) * (system->m_Base.m_nColorR / 255.0f), 0.0f, 1.0f);
        const float g = std::clamp((part->m_vColor.y / 255.0f) * (system->m_Base.m_nColorG / 255.0f), 0.0f, 1.0f);
        const float b = std::clamp((part->m_vColor.z / 255.0f) * (system->m_Base.m_nColorB / 255.0f), 0.0f, 1.0f);
        const float a = std::clamp(part->m_fAlpha * (system->m_Base.m_nColorA / 255.0f), 0.0f, 1.0f);

        const LTVector p0{c.x - sz, c.y + sz, c.z};
        const LTVector p1{c.x + sz, c.y + sz, c.z};
        const LTVector p2{c.x + sz, c.y - sz, c.z};
        const LTVector p3{c.x - sz, c.y - sz, c.z};

        verts.push_back({p0, LTFloatPt(minU, minV), PGColor(r, g, b, a)});
        verts.push_back({p1, LTFloatPt(maxU, minV), PGColor(r, g, b, a)});
        verts.push_back({p2, LTFloatPt(maxU, maxV), PGColor(r, g, b, a)});
        verts.push_back({p0, LTFloatPt(minU, minV), PGColor(r, g, b, a)});
        verts.push_back({p2, LTFloatPt(maxU, maxV), PGColor(r, g, b, a)});
        verts.push_back({p3, LTFloatPt(minU, maxV), PGColor(r, g, b, a)});
        ++drawn;

        if (drawn % kStockParticleBatch == 0)
            flush();

        part = next;
    }
    flush();

    if (drawn <= 0)
        return false;

    if (logParticles && (logBudget > 0 && logBudget--))
        LOG_SESSION("FX3D PARTICLES system=%p count=%d visited=%d drawn=%d culled=%d batches=%d tex=%p",
                    system, system->m_nParticles, visited, drawn, culled, batches, shared);

    return true;
}

bool FXRenderer::RenderPolyGrid(SceneDesc *scene, PolyGridCompat *grid)
{
    if (!StockRenderOptions::Instance().DrawPolyGrids())
        return true;
    if (!scene || !grid)
        return false;

    if (!grid->m_pData || grid->m_dwWidth < 2 || grid->m_dwHeight < 2)
        return false;

    SharedTexture *shared = nullptr;
    const char *materialSource = "NONE";
    SpriteEntryCompat *materialFrame = grid->m_SpriteTracker.m_pCurFrame;
    if (materialFrame && materialFrame->m_pTexture)
    {
        shared = materialFrame->m_pTexture;
        materialSource = "TRACKER-FRAME";
    }

    const bool materialSlotIsSprite = (grid->m_pSprite != nullptr);

    auto findTextureInAnim = [&](SpriteAnimCompat *anim) -> SharedTexture *
    {
        if (!anim || !anim->m_pFrames || anim->m_nFrames == 0 || anim->m_nFrames > 4096)
            return nullptr;
        for (uint32 fi = 0; fi < anim->m_nFrames; ++fi)
        {
            SpriteEntryCompat *f = &anim->m_pFrames[fi];
            if (f->m_pTexture)
            {
                materialFrame = f;
                materialSource = "SPR-ANIM-FRAME";
                return f->m_pTexture;
            }
        }
        return nullptr;
    };

    if (!shared)
        shared = findTextureInAnim(grid->m_SpriteTracker.m_pCurAnim);

    if (!shared && grid->m_pSprite &&
        grid->m_pSprite->m_pAnims &&
        grid->m_pSprite->m_nAnims > 0 && grid->m_pSprite->m_nAnims <= 256)
    {
        for (uint32 ai = 0; ai < grid->m_pSprite->m_nAnims && !shared; ++ai)
            shared = findTextureInAnim(&grid->m_pSprite->m_pAnims[ai]);
    }

    const char *materialResourceName = nullptr;

    const uint32 vertexCount = grid->m_dwWidth * grid->m_dwHeight;
    if (vertexCount < 4 || vertexCount > 1024u * 1024u)
        return false;

    std::vector<FXVertex> base(vertexCount);

    const float wm1 = static_cast<float>(grid->m_dwWidth - 1);
    const float hm1 = static_cast<float>(grid->m_dwHeight - 1);

    const float xInc = grid->m_Base.m_vScale.x * static_cast<float>(grid->m_dwWidth) / wm1;
    const float zInc = grid->m_Base.m_vScale.z * static_cast<float>(grid->m_dwHeight) / hm1;
    const float yScale = grid->m_Base.m_vScale.y * 2.0f;

    const float startX = -(wm1 * 0.5f) * xInc;
    const float startZ = -(hm1 * 0.5f) * zInc;

    constexpr float kPolyGridPanScale = 0.001f;

    const float runtimeScaleX = std::isfinite(grid->m_fScaleX) ? grid->m_fScaleX : 0.0f;
    const float runtimeScaleY = std::isfinite(grid->m_fScaleY) ? grid->m_fScaleY : 0.0f;
    const float rawPanX = std::isfinite(grid->m_fPanX) ? grid->m_fPanX : 0.0f;
    const float rawPanY = std::isfinite(grid->m_fPanY) ? grid->m_fPanY : 0.0f;

    constexpr float kTalonPolyGridRepeat = 2.0f;
    const float minInc = std::max(1.0e-6f, std::min(std::fabs(xInc), std::fabs(zInc)));
    const float uStep = (xInc * runtimeScaleX * kTalonPolyGridRepeat) / (wm1 * minInc);
    const float vStep = (zInc * runtimeScaleY * kTalonPolyGridRepeat) / (hm1 * minInc);

    const float startU = std::fmod(rawPanX * kPolyGridPanScale, 1.0f);
    const float startV = std::fmod(rawPanY * kPolyGridPanScale, 1.0f);
    const float objectAlpha = static_cast<float>(grid->m_Base.m_nColorA) / 255.0f;
    const float objectR = static_cast<float>(grid->m_Base.m_nColorR) / 255.0f;
    const float objectG = static_cast<float>(grid->m_Base.m_nColorG) / 255.0f;
    const float objectB = static_cast<float>(grid->m_Base.m_nColorB) / 255.0f;
    const bool stockEnvMap = FXState().envMapPolyGrids && grid->m_pEnvMap != nullptr;

    for (uint32 y = 0; y < grid->m_dwHeight; ++y)
    {
        for (uint32 x = 0; x < grid->m_dwWidth; ++x)
        {
            const uint32 i = y * grid->m_dwWidth + x;
            const int8 h = grid->m_pData[i];

            const uint32 ci = (grid->m_Base.m_dwFlags & 0x2u)
                                  ? static_cast<uint32>(static_cast<uint8>(grid->m_pData[i]))
                                  : static_cast<uint32>(static_cast<int>(h) + 128);
            const PGColorCompat &c = grid->m_aColorTable[ci];

            LTVector cam = PolyGridLocalToCamera(scene, grid->m_Base,
                                             {startX + x * xInc, h * yScale, startZ + y * zInc});

            auto normColor = [](float value) -> float
            {
                if (!std::isfinite(value))
                    return 0.0f;
                return std::clamp(value, 0.0f, 255.0f) * (1.0f / 255.0f);
            };

            const bool multiplyBlend = (grid->m_Base.m_dwFlags2 & FLAG2_MULTIPLY) != 0;
            const float polyStageScale = (!stockEnvMap && multiplyBlend) ? 2.0f : 1.0f;

            base[i] = {
                LTVector(cam.x, cam.y, cam.z),
                LTFloatPt(startU + static_cast<float>(x) * uStep,
                          startV + static_cast<float>(y) * vStep),
                PGColor(normColor(c.r) * objectR * polyStageScale,
                        normColor(c.g) * objectG * polyStageScale,
                        normColor(c.b) * objectB * polyStageScale,
                        stockEnvMap ? ((128.0f / 255.0f) * objectAlpha) : 1.0f)};
        }
    }

    std::vector<FXVertex> verts;
    const uint32 canonicalIndexCount = (grid->m_dwWidth - 1u) * (grid->m_dwHeight - 1u) * 6u;
    verts.reserve(std::min<uint32>(grid->m_dwIndices ? grid->m_dwIndices : canonicalIndexCount,
                                   static_cast<uint32>(MAX_FX_VERTS)));

    uint32 badIndices = 0;
    if (grid->m_pIndices && grid->m_dwIndices >= 3)
    {
        for (uint32 i = 0; i + 2 < grid->m_dwIndices && verts.size() + 3 <= MAX_FX_VERTS; i += 3)
        {
            const uint16 a = grid->m_pIndices[i + 0];
            const uint16 b = grid->m_pIndices[i + 1];
            const uint16 c = grid->m_pIndices[i + 2];
            if (a >= vertexCount || b >= vertexCount || c >= vertexCount)
            {
                ++badIndices;
                continue;
            }
            verts.push_back(base[a]);
            verts.push_back(base[b]);
            verts.push_back(base[c]);
        }
    }

    if (verts.empty())
    {
        for (uint32 y = 0; y + 1 < grid->m_dwHeight && verts.size() + 6 <= MAX_FX_VERTS; ++y)
        {
            for (uint32 x = 0; x + 1 < grid->m_dwWidth && verts.size() + 6 <= MAX_FX_VERTS; ++x)
            {
                const uint32 i0 = y * grid->m_dwWidth + x;
                const uint32 i1 = i0 + 1;
                const uint32 i2 = i0 + grid->m_dwWidth;
                const uint32 i3 = i2 + 1;

                verts.push_back(base[i0]);
                verts.push_back(base[i2]);
                verts.push_back(base[i1]);
                verts.push_back(base[i1]);
                verts.push_back(base[i2]);
                verts.push_back(base[i3]);
            }
        }
    }

    if (verts.empty())
        return false;

    DrawPolyGridVertices(scene, *grid, shared, grid->m_pEnvMap, verts);

    grid->m_Base.m_dwFlags |= FLAG_INTERNAL1;
    return true;
}

bool FXRenderer::RenderLineSystem(SceneDesc *scene, LineSystemCompat *system)
{
    if (!StockRenderOptions::Instance().DrawLineSystems())
        return true;
    if (!scene || !system)
        return false;

    LSLineCompat *const sentinel = &system->m_LineHead;
    LSLineCompat *line = sentinel->m_pNext;
    if (!line || line == sentinel)
        return true;

    std::vector<FXVertex> verts;
    verts.reserve(2048);

    const bool reallyClose = (system->m_Base.m_dwFlags & FLAG_REALLYCLOSE) != 0;
    const float nearZ = reallyClose ? 0.01f : 1.0f;
    uint32 guard = 0;

    auto flush = [&]()
    {
        if (verts.empty())
            return;
        DrawLineVertices(scene, system->m_Base, verts);
        verts.clear();
    };

    while (line && line != sentinel && guard++ < 65536)
    {
        const LSPointCompat &p0 = line->m_Points[0];
        const LSPointCompat &p1 = line->m_Points[1];

        const LTVector c0 = ObjectLocalToCamera(scene, system->m_Base, {p0.m_vPos.x, p0.m_vPos.y, p0.m_vPos.z});
        const LTVector c1 = ObjectLocalToCamera(scene, system->m_Base, {p1.m_vPos.x, p1.m_vPos.y, p1.m_vPos.z});

        const uint8 r0 = TalonLineByte(p0.m_fR * 255.0f);
        const uint8 g0 = TalonLineByte(p0.m_fG * 255.0f);
        const uint8 b0 = TalonLineByte(p0.m_fB * 255.0f);
        const uint8 a0 = TalonLineByte(p0.m_fA * static_cast<float>(system->m_Base.m_nColorA));
        const uint8 r1 = TalonLineByte(p1.m_fR * 255.0f);
        const uint8 g1 = TalonLineByte(p1.m_fG * 255.0f);
        const uint8 b1 = TalonLineByte(p1.m_fB * 255.0f);
        const uint8 a1 = TalonLineByte(p1.m_fA * static_cast<float>(system->m_Base.m_nColorA));

        FXVertex v0{c0, LTFloatPt(0, 0), PGColor(r0 / 255.0f, g0 / 255.0f, b0 / 255.0f, a0 / 255.0f)};
        FXVertex v1{c1, LTFloatPt(0, 0), PGColor(r1 / 255.0f, g1 / 255.0f, b1 / 255.0f, a1 / 255.0f)};

        if (v0.pos.z < nearZ && v1.pos.z < nearZ)
        {
            line = line->m_pNext;
            continue;
        }
        if (v0.pos.z < nearZ)
        {
            const float denom = v1.pos.z - v0.pos.z;
            if (std::fabs(denom) < 1.0e-8f)
            {
                line = line->m_pNext;
                continue;
            }
            v0 = LerpLineVertex(v0, v1, (nearZ - v0.pos.z) / denom);
        }
        else if (v1.pos.z < nearZ)
        {
            const float denom = v0.pos.z - v1.pos.z;
            if (std::fabs(denom) < 1.0e-8f)
            {
                line = line->m_pNext;
                continue;
            }
            v1 = LerpLineVertex(v1, v0, (nearZ - v1.pos.z) / denom);
        }

        if (verts.size() + 2 > MAX_FX_VERTS)
            flush();
        verts.push_back(v0);
        verts.push_back(v1);
        line = line->m_pNext;
    }

    flush();
    return true;
}
/*
bool FXRenderer::RenderCanvas(SceneDesc *scene, CanvasCompat *canvas)
{
    if (!StockRenderOptions::Instance().DrawCanvases())
        return true;
    if (!scene || !canvas || !canvas->m_pFn)
        return false;

    const avp2::render::GLStateSnapshot oldState =
        avp2::render::GLStateCache::Instance().Capture();

    DrawPolyMgrCompat mgr{};
    ResetCanvasManager(mgr, scene, canvas);

    canvas->m_pFn(&mgr, canvas, canvas->m_pFnUserData);

    if (mgr.m_pTexture)
    {
        Texture *restoreTex = TextureManager::Instance().Ensure(mgr.m_pTexture, false);
        if (restoreTex && restoreTex->texture)
        {
            glf.TextureParameteri(restoreTex->texture, GL_TEXTURE_WRAP_S_, GL_REPEAT);
            glf.TextureParameteri(restoreTex->texture, GL_TEXTURE_WRAP_T_, GL_REPEAT);
        }
    }

    avp2::render::GLStateCache::Instance().Restore(oldState);
    return true;
}
*/

bool FXRenderer::RenderCanvas(SceneDesc *scene, CanvasCompat *canvas)
{
    if (!StockRenderOptions::Instance().DrawCanvases())
        return true;
    if (!scene || !canvas || !canvas->m_pFn)
        return false;

    const avp2::render::GLStateSnapshot oldState =
        avp2::render::GLStateCache::Instance().Capture();

    // Create host-side manager and set vtable/fields
    DrawPolyMgrCompat mgr{};
    ResetCanvasManager(mgr, scene, canvas);

    // Call the canvas routine passing &mgr as the first parameter
    // d3d.ren prototype: typedef void (*CanvasCallbackFn)(DrawPolyMgrCompat *pMgr, CanvasCompat *pCanvas, void *pUserData);
    canvas->m_pFn(&mgr, canvas, canvas->m_pFnUserData);

    if (mgr.m_pTexture)
    {
        Texture *restoreTex = TextureManager::Instance().Ensure(mgr.m_pTexture, false);
        if (restoreTex && restoreTex->texture)
        {
            glf.TextureParameteri(restoreTex->texture, GL_TEXTURE_WRAP_S_, GL_REPEAT);
            glf.TextureParameteri(restoreTex->texture, GL_TEXTURE_WRAP_T_, GL_REPEAT);
        }
    }

    avp2::render::GLStateCache::Instance().Restore(oldState);
    return true;
}

void FXRenderer::SetRenderStruct(RenderStruct *rs)
{
    m_state.renderStruct = rs;
    ReadConsoleVariables();
}

void FXRenderer::ReadConsoleVariables()
{
    auto getFloat = [](const char *name, float fallback) -> float
    {
        return Console::Instance().GetFloat(name, fallback);
    };

    m_state.psSrcBlendOverride = static_cast<int>(getFloat("PSSrcBlend", -1.0f));
    m_state.psDestBlendOverride = static_cast<int>(getFloat("PSDestBlend", -1.0f));
    m_state.envMapPolyGrids = getFloat("EnvMapPolyGrids", 1.0f) != 0.0f;
}

FXRenderer &FXRenderer::Instance()
{
    static FXRenderer v;
    return v;
}
