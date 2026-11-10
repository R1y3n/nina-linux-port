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

// The Canvas callback sees this object only through the five-entry virtual
// interface reconstructed from d3d.ren at 0x100463C8.  These MUST be native
// non-static member functions: on Win32 MSVC emits the stock __thiscall ABI
// automatically (ECX=this, remaining arguments on the stack).  Declaring
// free functions __thiscall is rejected by MSVC (C3865), while changing them
// to __cdecl/__fastcall would compile but would not match the game callback.
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
};

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

        // Overflow or a driver that unexpectedly refused the persistent map: retain
        // the old driver-managed upload path on a separate VBO. This keeps the
        // optimization strictly non-functional; a crowded FX frame cannot corrupt
        // geometry by wrapping over data the GPU may still be reading.
        if (st.streamFallbackVbo)
        {
            GLTrackedNamedBufferSubData(st.streamFallbackVbo, 0, static_cast<GLsizeiptr>(bytes), data, GLUploadCategory::FX);
            glf.VertexArrayVertexBuffer(st.vao, 0, st.streamFallbackVbo, 0, sizeof(FXVertex));
            return true;
        }
        return false;
    }

    // PolyGrid vertex construction already expands the grid using LTObject::m_vScale
    // as Talon's cell/world scale.  Running those positions through the generic
    // object helper above applied m_vScale a second time (scale squared), producing
    // enormous grids which appeared to slide with the camera as they hit the near
    // plane.  PolyGrids need rotation + translation here, but no second scale.
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
            // D3D8: SRCBLEND=ZERO, DESTBLEND=SRCCOLOR.  This computes
            // framebuffer * sourceColor.  The previous GL_DST_COLOR/ZERO pair
            // multiplied the source by the framebuffer and discarded destination
            // alpha semantics, which is not Talon's stock PolyGrid mode.
            GLStateBlendFunc(GL_ZERO, GL_SRC_COLOR);
        else
            GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        GLStateDepthMask(GL_FALSE);
    }

    static GLenum MapD3DBlend(int b)
    {
        // D3DBLEND values used by Talon's ParticleSystem::m_nSrcBlend/m_nDestBlend.
        switch (b)
        {
        case 1:
            return GL_ZERO; // ZERO
        case 2:
            return GL_ONE; // ONE
        case 3:
            return GL_SRC_COLOR; // SRCCOLOR
        case 4:
            return GL_ONE_MINUS_SRC_COLOR; // INVSRCCOLOR
        case 5:
            return GL_SRC_ALPHA; // SRCALPHA
        case 6:
            return GL_ONE_MINUS_SRC_ALPHA; // INVSRCALPHA
        case 7:
            return GL_DST_ALPHA; // DESTALPHA
        case 8:
            return GL_ONE_MINUS_DST_ALPHA; // INVDESTALPHA
        case 9:
            return GL_DST_COLOR; // DESTCOLOR
        case 10:
            return GL_ONE_MINUS_DST_COLOR; // INVDESTCOLOR
        case 11:
            return GL_SRC_ALPHA_SATURATE; // SRCALPHASAT
        default:
            return GL_ZERO;
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

    // The game-facing DrawPoly manager does NOT expose the full D3DBLEND enum.
    // d3d.ren 0x100234E3 accepts API values 1..6 verbatim and maps every other
    // value to D3DBLEND_ONE (2).  ParticleSystems use the full 1..11 mapping
    // above, so keep this Canvas-specific conversion separate.
    static GLenum MapCanvasBlend(uint32 value)
    {
        const int d3d = (value >= 1u && value <= 6u) ? static_cast<int>(value) : 2;
        return MapD3DBlend(d3d);
    }

    static uint32 MapCanvasColorOp(uint32 value)
    {
        // d3d.ren 0x100235C1..0x100235F2 maps the public DrawPoly values:
        // 1 SELECTARG1, 2 SELECTARG2, 3 MODULATE, 4 ADD, 5 ADDSIGNED.
        // Unsupported values fall back to MODULATE (public value 3).
        return (value >= 1u && value <= 5u) ? value : 3u;
    }

    static uint32 MapCanvasAlphaOp(uint32 value)
    {
        // Same five public operations, but the retail invalid-value fallback at
        // 0x100235FF..0x10023630 is SELECTARG1 (public value 1).
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
                                     ? (particleDstBlend == 2) // D3DBLEND_ONE: stock additive-style particle destination
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

        // Talon/D3D11 PolyGrid default blend state is BLEND_STATE_Alpha.
        // Additive and multiply flags override that default, but an otherwise
        // ordinary PolyGrid is still SRC_ALPHA/INV_SRC_ALPHA and does not write Z.
        // Treating alpha==255 grids as opaque changes the composition of layered
        // water/plasma surfaces and is not stock behavior.
        ApplyBlend(grid.m_Base);
        GLStateDisable(GL_CULL_FACE);
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);

        if (!FXStreamUpload(verts.data(), verts.size() * sizeof(FXVertex)))
            return;
        GLStateBindVertexArray(FXState().vao);

        // F10 PolyGrid source/blend probe.  For multiply PolyGrids the stock
        // framebuffer equation is ZERO/SRCCOLOR, so after.rgb = before.rgb * source.rgb.
        // Sampling a pixel immediately before and after this draw lets us recover the
        // actual source RGB reaching the blend unit without changing the render path.
        // We also log the triangle-centroid UV and interpolated diffuse color so the
        // inferred source can be split into texture and palette terms.
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
            LOG_SESSION("FX3D POLYGRID-BLENDPROBE grid=%p unavailable (no visible probe triangle or framebuffer readback failed)", &grid);
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

        // AVP2 d3d.ren LineSystem path is 0x10024A60.  It explicitly
        // disables D3DRENDERSTATE_FOGENABLE before drawing and restores fog on
        // exit.  LineSystems therefore never receive Talon object/world fog.
        GLUniform1i(FXState().uFogEnabled, 0);
        GLUniform1i(FXState().uFogAdditive, 0);

        // The LineSystem routine itself never selects additive/multiply state.
        // It is emitted from the translucent scene phase with the normal Talon
        // SRCALPHA/INVSRCALPHA blend.  Keep this explicit so FX state from a
        // previously drawn ParticleSystem/PolyGrid cannot bleed into the lines.
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
        // d3d.ren uses its truncate-toward-zero float->int helper at 0x1003B9DC
        // and then consumes the low byte of the result.
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
        // d3d.ren 0x100226E9 passes ordinary Canvas primitive XYZ through the
        // current ViewParams transform.  ReallyClose canvases select the special
        // matrix path via Canvas flags bit 6 (0x10022624..0x1002262F).
        if (reallyClose)
            return world;
        const LTVector rel = world - LTVector{scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z};
        LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                scene->m_rRotation.z, scene->m_rRotation.w};
        return cq.Conjugate().Rotate(rel);
    }

    static void DecodeD3DColor(uint32 c, float &r, float &g, float &b, float &a)
    {
        // D3DCOLOR is packed ARGB; on little-endian memory the bytes are B,G,R,A.
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
    // Exact logical defaults installed by d3d.ren 0x100224AE:
    // alphaBlend=0, zEnable=1, zWrite=1, src=5(SRCALPHA),
    // dst=6(INVSRCALPHA), state5=1, colorOp=3(MODULATE),
    // alphaOp=2(SELECTARG2 / diffuse alpha).
    const uint32 defaults[8] = {0, 1, 1, 5, 6, 1, 3, 2};
    for (uint32 i = 0; i < 8u; ++i)
        mgr.m_State[i] = defaults[i];
}

int DrawPolyMgrCompat::SetState(uint32 index, uint32 value)
{
    if (index >= 8u)
        return 1;
    m_State[index] = value;
    return 0;
}

int DrawPolyMgrCompat::GetState(uint32 index, uint32 *value)
{
    if (!value || index >= 8u)
        return 1;
    *value = m_State[index];
    return 0;
}

int DrawPolyMgrCompat::SetTexture(const char *name)
{
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
    if (!x || !y)
        return 1;

    // Exact d3d.ren behavior:
    //   0x10022A73 returns globals 0x10061810/0x10061814.
    // Texture setup (for example 0x10034D5B..0x10034D72) writes the
    // reciprocal *scaled* texture dimensions to those globals for the active
    // stage.  Returning (1,1) here breaks effects which construct/pan UVs in
    // texel units -- integer advances simply wrap onto the same sample.
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
        // With no texture selected there is no active RTexture scale.  The
        // value is irrelevant to an untextured primitive; keep a neutral
        // result and make the condition explicit in the diagnostic.
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
    if (!m_pScene || !m_pCanvas || !src || count < 3)
        return 1;

    const size_t n = std::min<size_t>(static_cast<size_t>(count), MAX_FX_VERTS);
    std::vector<FXVertex> verts;
    verts.reserve(n);
    const bool reallyClose = (m_pCanvas->m_Base.m_dwFlags & FLAG_REALLYCLOSE) != 0;
    // d3d.ren 0x10022715..0x1002275C enters the same special transform/clip
    // branch when either the Canvas is ReallyClose OR DrawPrim flags bit 0x40
    // is present.  Do not discard that per-draw override.
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
        // DrawPoly state 5 maps through d3d.ren 0x100228B8/0x10022990
        // to the old D3D texture-address state: game value 1 -> WRAP,
        // value 2 -> CLAMP (D3D address value 3).  Talon applies it to the
        // active stage before each DrawPrimitiveUP.
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
    // Exact primitive topology used by d3d.ren 0x1002274C/0x100227E7:
    // D3DPT_TRIANGLEFAN (6).
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
        // Capture compatibility: avoid persistent-storage flags entirely.
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

    // Retail d3d.ren enters the particle draw with ParticleSystem::m_pCurTexture
    // already tracking the active Sprite frame.  In a replacement renderer we
    // can occasionally observe the tracker one step earlier than that cached
    // field, so resolve the same resource chain without involving SpriteRenderer.
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
            LOG_SESSION("FX3D PARTICLE-MATERIAL-UNRESOLVED system=%p curTex=%p sprite=%p trackerSprite=%p curAnim=%p curFrame=%p frameTex=%p count=%d",
                        system, system->m_pCurTexture, system->m_pSprite, system->m_SpriteTracker.m_pSprite,
                        system->m_SpriteTracker.m_pCurAnim, system->m_SpriteTracker.m_pCurFrame,
                        system->m_SpriteTracker.m_pCurFrame ? system->m_SpriteTracker.m_pCurFrame->m_pTexture : nullptr,
                        system->m_nParticles);
        return false;
    }

    Texture *tex = TextureManager::Instance().Ensure(shared, false);
    if (!tex || !tex->texture)
        return false;

    // d3d.ren 0x10008C90 derives the particle UV inset from the active D3D
    // texture dimensions and draws particles in chunks of 128.  Preserve the
    // stock two-texel inset to avoid bleeding from mip/filter borders.
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

    // Retail batches 128 particles at a time (0x10008F4F..0x10008FA6).  Apart
    // from matching the stock submission granularity this prevents one large
    // dynamic upload from monopolising the shared FX buffer on particle-heavy
    // scenes.
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

        // m_fSize is the billboard half extent.  The previous OpenGL path
        // multiplied it by two and then applied +/- that value, making every
        // particle four times stock width/height.  d3d.ren's projected quad
        // builder subtracts/adds one m_fSize-derived extent around the centre.
        const float sz = std::max(0.0f, std::fabs(part->m_fSize));
        if (logParticles)
        {
            minSize = std::min(minSize, sz);
            maxSize = std::max(maxSize, sz);
        }

        // Mirror d3d.ren's projected particle-frustum rejection before writing
        // the quad.  Keep the test conservative because the particle is a
        // camera-facing square, not a point.
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
        LOG_SESSION("FX3D PARTICLES system=%p count=%d visited=%d drawn=%d culled=%d batches=%d tex=%p gl=%u texSize=%ux%u texSource=%s sprite=%p trackerFrame=%p size=[%.3f,%.3f] objColor=(%u,%u,%u,%u) flags=%08X flags2=%08X blend=%d/%d effectiveBlend=%d/%d sysFlags=%08X radius=%.2f",
                    system, system->m_nParticles, visited, drawn, culled, batches, shared, unsigned(tex->texture), tex->width, tex->height,
                    textureSource, system->m_pSprite, system->m_SpriteTracker.m_pCurFrame,
                    minSize == 1.0e30f ? 0.0f : minSize, maxSize,
                    unsigned(system->m_Base.m_nColorR), unsigned(system->m_Base.m_nColorG),
                    unsigned(system->m_Base.m_nColorB), unsigned(system->m_Base.m_nColorA),
                    system->m_Base.m_dwFlags, system->m_Base.m_dwFlags2,
                    system->m_nSrcBlend, system->m_nDestBlend, srcBlend, dstBlend,
                    system->m_dwSystemFlags, system->m_fParticleRadius);

    return true;
}

bool FXRenderer::RenderPolyGrid(SceneDesc *scene, PolyGridCompat *grid)
{
    if (!StockRenderOptions::Instance().DrawPolyGrids())
        return true;
    if (!scene || !grid)
        return false;

    // Retail d3d.ren's PolyGrid renderer (0x1002BE60) only requires the
    // heightfield and a >=2x2 grid before vertex construction.  PolyGrids are
    // a special visibility class and can arrive before all optional cached
    // index metadata is populated, so do not reject the whole object merely
    // because m_dwIndices is zero.
    if (!grid->m_pData || grid->m_dwWidth < 2 || grid->m_dwHeight < 2)
    {
        static int rejectBudget = 64;
        if (LogIsSessionEnabled() && ((rejectBudget > 0 && rejectBudget--)))
            LOG_SESSION("FX3D POLYGRID-REJECT grid=%p data=%p size=%ux%u indices=%p indexCount=%u tris=%u reason=BAD_GEOMETRY",
                        grid, grid->m_pData, grid->m_dwWidth, grid->m_dwHeight,
                        grid->m_pIndices, grid->m_dwIndices, grid->m_dwTris);
        return false;
    }

    // d3d.ren reads PolyGrid::m_pSprite / m_SpriteTracker directly; this is
    // a PolyGrid material resource, not a call through SpriteRenderer.  Talon
    // can populate the tracker lazily, so accept the current tracked frame
    // first and fall back to the first frame of the PolyGrid sprite resource.
    SharedTexture *shared = nullptr;
    const char *materialSource = "NONE";
    SpriteEntryCompat *materialFrame = grid->m_SpriteTracker.m_pCurFrame;
    if (materialFrame && materialFrame->m_pTexture)
    {
        shared = materialFrame->m_pTexture;
        materialSource = "TRACKER-FRAME";
    }

    // Stock Talon SetPolyGridTexture() loads an SPR resource.  A direct DTX
    // passed to this API fails in the original renderer, so keep the replacement
    // renderer on the same contract: PolyGrid base materials come from the
    // SpriteTracker/Sprite animation frames only.  Do not reinterpret m_pSprite
    // as a SharedTexture.
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

    // Do not chase a FileIdentifier through SpriteCompat here.  AVP2's live
    // Sprite object has an inline 8-byte tag at +0x14
    const char *materialResourceName = nullptr;

    const uint32 vertexCount = grid->m_dwWidth * grid->m_dwHeight;
    if (vertexCount < 4 || vertexCount > 1024u * 1024u)
        return false;

    std::vector<FXVertex> base(vertexCount);

    const float wm1 = static_cast<float>(grid->m_dwWidth - 1);
    const float hm1 = static_cast<float>(grid->m_dwHeight - 1);

    // Match d3d11_avp2::CPolyGridData::CalcVertexDataEssentials(). Talon's
    // PolyGrid uses dimension/(dimension-1) when turning LTObject scale into
    // the local cell spacing. This is also the basis used by the UV generator.
    const float xInc = grid->m_Base.m_vScale.x * static_cast<float>(grid->m_dwWidth) / wm1;
    const float zInc = grid->m_Base.m_vScale.z * static_cast<float>(grid->m_dwHeight) / hm1;
    const float yScale = grid->m_Base.m_vScale.y * 2.0f;

    const float startX = -(wm1 * 0.5f) * xInc;
    const float startZ = -(hm1 * 0.5f) * zInc;

    // Stock LithTech PolyGrid UV generation (drawpolygrid.cpp):
    //   fXScale = m_xScale / ((width-1) * fXInc)
    //   fUInc   = fXInc * fXScale * fPGUScale
    // which simplifies to m_xScale/(width-1) for the normal, non-bumpmapped path.
    // The D3D11 port's min(xInc,zInc) correction was an approximation and changes
    // the authored repeat rate on non-square grids.
    constexpr float kPolyGridPanScale = 0.001f;

    const float runtimeScaleX = std::isfinite(grid->m_fScaleX) ? grid->m_fScaleX : 0.0f;
    const float runtimeScaleY = std::isfinite(grid->m_fScaleY) ? grid->m_fScaleY : 0.0f;
    const float rawPanX = std::isfinite(grid->m_fPanX) ? grid->m_fPanX : 0.0f;
    const float rawPanY = std::isfinite(grid->m_fPanY) ? grid->m_fPanY : 0.0f;

    // Talon PolyGrid texture scale is world-space isotropic.  The grid can be
    // extremely non-square (the live water case is ~1024 x 4096 world units),
    // so using the same normalized UV span on X and Z stretches the texture.
    // Normalize both axes against the smaller world-space cell increment, then
    // keep the AVP2/Talon 2x repeat convention.
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

            // Exact retail table addressing from d3d.ren 0x1002BC50 and
            // 0x1002BE6C.  PolyGrid flag bit 0x2 switches the height bytes
            // to an unsigned 0..255 lookup.  Otherwise the signed -128..127
            // height is biased by 128.
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
                        // Stock non-environment PolyGrids force diffuse alpha to
                        // 255. Environment-mapped PolyGrids use 128 and combine
                        // that with the object's overall alpha.
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
        // Stock uses the engine-authored triangle list when present.
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

    // Some Talon PolyGrids do not keep a persistent index list.  d3d.ren has
    // enough width/height information to render the regular grid directly;
    // provide the equivalent canonical topology instead of making the effect
    // disappear.  Also use this path if the supplied list was unusable.
    bool generatedTopology = false;
    if (verts.empty())
    {
        generatedTopology = true;
        for (uint32 y = 0; y + 1 < grid->m_dwHeight && verts.size() + 6 <= MAX_FX_VERTS; ++y)
        {
            for (uint32 x = 0; x + 1 < grid->m_dwWidth && verts.size() + 6 <= MAX_FX_VERTS; ++x)
            {
                const uint32 i0 = y * grid->m_dwWidth + x;
                const uint32 i1 = i0 + 1;
                const uint32 i2 = i0 + grid->m_dwWidth;
                const uint32 i3 = i2 + 1;

                // CW in Talon's local grid convention. Culling is disabled for
                // PolyGrids, so this primarily preserves interpolation parity.
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

    // F10 diagnostic: dump the exact authored PolyGrid render state rather than
    // inferring it from the visual result.  SharedTexture StateChange can override
    // the object flags' default alpha/add/multiply selection, so record both.
    static uint32 pgStateLogDivider = 0;
    if (LogIsSessionEnabled() && ((pgStateLogDivider++ % 30u) == 0u))
    {
        const auto *baseST = reinterpret_cast<const SharedTextureCompat *>(shared);
        const auto *envST = reinterpret_cast<const SharedTextureCompat *>(grid->m_pEnvMap);
        const auto *baseLinkedST = baseST ? baseST->m_pLinkedTexture : nullptr;
        const auto *envLinkedST = envST ? envST->m_pLinkedTexture : nullptr;
        const TalonRenderState baseRS = TalonRenderStateSystem::Instance().Decode(shared);
        const TalonRenderState envRS = TalonRenderStateSystem::Instance().Decode(grid->m_pEnvMap);
        const TalonRenderState baseLinkedRS = TalonRenderStateSystem::Instance().Decode(reinterpret_cast<SharedTexture *>(const_cast<SharedTextureCompat *>(baseLinkedST)));
        const TalonRenderState envLinkedRS = TalonRenderStateSystem::Instance().Decode(reinterpret_cast<SharedTexture *>(const_cast<SharedTextureCompat *>(envLinkedST)));

        uint32 effectiveSrc = (grid->m_Base.m_dwFlags2 & FLAG2_ADDITIVE) ? 2u :
                              (grid->m_Base.m_dwFlags2 & FLAG2_MULTIPLY) ? 1u : 5u;
        uint32 effectiveDst = (grid->m_Base.m_dwFlags2 & FLAG2_ADDITIVE) ? 2u :
                              (grid->m_Base.m_dwFlags2 & FLAG2_MULTIPLY) ? 3u : 6u;
        bool effectiveBlendEnable = true;
        if (baseRS.valid)
        {
            if (baseRS.hasAlphaBlendEnable) effectiveBlendEnable = baseRS.alphaBlendEnable;
            if (baseRS.hasSrcBlend) effectiveSrc = baseRS.srcBlend;
            if (baseRS.hasDestBlend) effectiveDst = baseRS.destBlend;
        }

        LOG_SESSION("FX3D POLYGRID-STATE grid=%p flags=%08X flags2=%08X baseBlend=%s effectiveBlend=%d %u(%s)/%u(%s) "
                    "baseTex=%p baseType=%u baseLinked=%p baseSC=%p baseRSvalid=%d envTex=%p envType=%u envLinked=%p envSC=%p envRSvalid=%d "
                    "envCvar=%d envOn=%d envOnly=%d objRGBA=(%u,%u,%u,%u) size=%ux%u pos=(%.3f %.3f %.3f) objScale=(%.6f %.6f %.6f) "
                    "polyScale=(%.9f %.9f) pan=(%.9f %.9f) startUV=(%.9f %.9f) uvStep=(%.9f %.9f) uvSpan=(%.9f %.9f)",
                    grid, grid->m_Base.m_dwFlags, grid->m_Base.m_dwFlags2, PolyGridBaseBlendName(grid->m_Base),
                    effectiveBlendEnable ? 1 : 0, effectiveSrc, D3DBlendName(effectiveSrc), effectiveDst, D3DBlendName(effectiveDst),
                    shared, baseST ? baseST->m_eTexType : 0u, baseST ? baseST->m_pLinkedTexture : nullptr, baseST ? baseST->m_pStateChange : nullptr, baseRS.valid ? 1 : 0,
                    grid->m_pEnvMap, envST ? envST->m_eTexType : 0u, envST ? envST->m_pLinkedTexture : nullptr, envST ? envST->m_pStateChange : nullptr, envRS.valid ? 1 : 0,
                    FXState().envMapPolyGrids ? 1 : 0, stockEnvMap ? 1 : 0, (grid->m_Base.m_dwFlags & FLAG_ENVIRONMENTMAP) ? 1 : 0,
                    unsigned(grid->m_Base.m_nColorR), unsigned(grid->m_Base.m_nColorG), unsigned(grid->m_Base.m_nColorB), unsigned(grid->m_Base.m_nColorA),
                    grid->m_dwWidth, grid->m_dwHeight, grid->m_Base.m_vPos.x, grid->m_Base.m_vPos.y, grid->m_Base.m_vPos.z,
                    grid->m_Base.m_vScale.x, grid->m_Base.m_vScale.y, grid->m_Base.m_vScale.z,
                    runtimeScaleX, runtimeScaleY, rawPanX, rawPanY, startU, startV, uStep, vStep, uStep * wm1, vStep * hm1);

        auto dumpSC = [&](const char *which, const SharedTextureCompat *st)
        {
            if (!st || !st->m_pStateChange) return;
            const auto *sc = reinterpret_cast<const StateChangeCompat *>(st->m_pStateChange);
            const uint32 rsCount = sc->m_RenderList.size();
            const uint32 tsCount = sc->m_TextureList.size();
            LOG_SESSION("FX3D POLYGRID-SC %s grid=%p sc=%p renderStates=%u textureStates=%u", which, grid, sc, rsCount, tsCount);
            if (rsCount <= 32u && sc->m_RenderList.m_pFirst)
                for (uint32 i = 0; i < rsCount; ++i)
                    LOG_SESSION("FX3D POLYGRID-SC-RS %s grid=%p i=%u state=%u value=%u(0x%08X)", which, grid, i,
                                sc->m_RenderList.m_pFirst[i].m_dwRenderStateType, sc->m_RenderList.m_pFirst[i].m_dwRenderState,
                                sc->m_RenderList.m_pFirst[i].m_dwRenderState);
            if (tsCount <= 32u && sc->m_TextureList.m_pFirst)
                for (uint32 i = 0; i < tsCount; ++i)
                    LOG_SESSION("FX3D POLYGRID-SC-TS %s grid=%p i=%u stage=%u state=%u value=%u(0x%08X)", which, grid, i,
                                sc->m_TextureList.m_pFirst[i].m_dwStage, sc->m_TextureList.m_pFirst[i].m_dwTextureStateType,
                                sc->m_TextureList.m_pFirst[i].m_dwTextureState, sc->m_TextureList.m_pFirst[i].m_dwTextureState);
        };
        auto dumpLinkedTexture = [&](const char *which, const SharedTextureCompat *st, const TalonRenderState &rs)
        {
            if (!st) return;
            const auto *td = reinterpret_cast<const TextureDataCompat *>(st->m_pEngineData);
            float detScale = 0.0f;
            int detAngle = 0;
            uint32 iFlags = 0, userFlags = 0;
            uint32 w = 0, h = 0;
            const char *cmd = st->m_szCommandString ? st->m_szCommandString : "";
            if (td)
            {
                detScale = td->m_DtxHeader.m_Extra.m_fDetTexScale;
                detAngle = td->m_DtxHeader.m_Extra.m_nDetTexAngle;
                iFlags = static_cast<uint32>(td->m_DtxHeader.m_nIFlags);
                userFlags = static_cast<uint32>(td->m_DtxHeader.m_nUserFlags);
                w = td->m_DtxHeader.m_wBaseWidth;
                h = td->m_DtxHeader.m_wBaseHeight;
                if ((!cmd || !*cmd) && td->m_DtxHeader.m_szCommandString[0])
                    cmd = td->m_DtxHeader.m_szCommandString;
            }
            LOG_SESSION("FX3D POLYGRID-LINKED %s grid=%p st=%p type=%u linked=%p sc=%p rsvalid=%d engineData=%p renderData=%p dtx=%ux%u detScale=%.9f detAngle=%d iFlags=%08X userFlags=%08X cmd='%s'",
                        which, grid, st, st->m_eTexType, st->m_pLinkedTexture, st->m_pStateChange, rs.valid ? 1 : 0,
                        st->m_pEngineData, st->m_pRenderData, w, h, detScale, detAngle, iFlags, userFlags, cmd ? cmd : "");
        };

        dumpSC("BASE", baseST);
        dumpSC("BASE-LINKED", baseLinkedST);
        dumpSC("ENV", envST);
        dumpSC("ENV-LINKED", envLinkedST);
        dumpLinkedTexture("BASE-LINKED", baseLinkedST, baseLinkedRS);
        dumpLinkedTexture("ENV-LINKED", envLinkedST, envLinkedRS);
    }

    // Diagnostic: stock PolyGrid diffuse is authored by the 256-entry color table;
    // it is not fed through world light-grid or AmbientLight.  Log the actually
    // referenced palette range alongside both SceneDesc ambient channels so we
    // can distinguish a PolyGrid-source mismatch from a too-dark destination
    // framebuffer (important for ZERO/SRCCOLOR multiply grids).
    static int logBudget = 96;
    static uint32 sessionLogDivider = 0;
    const bool logThisPolyGrid = LogIsSessionEnabled() && ((logBudget > 0 && logBudget--) || ((sessionLogDivider++ % 30u) == 0u));
    if (logThisPolyGrid)
    {
        float pgMinR=255.0f, pgMinG=255.0f, pgMinB=255.0f;
        float pgMaxR=0.0f, pgMaxG=0.0f, pgMaxB=0.0f;
        double pgSumR=0.0, pgSumG=0.0, pgSumB=0.0;
        for (uint32 pi=0; pi<vertexCount; ++pi)
        {
            const int8 ph=grid->m_pData[pi];
            const uint32 pci=(grid->m_Base.m_dwFlags & 0x2u)
                ? static_cast<uint32>(static_cast<uint8>(grid->m_pData[pi]))
                : static_cast<uint32>(static_cast<int>(ph)+128);
            const PGColorCompat &pc=grid->m_aColorTable[pci];
            pgMinR=std::min(pgMinR,pc.r); pgMinG=std::min(pgMinG,pc.g); pgMinB=std::min(pgMinB,pc.b);
            pgMaxR=std::max(pgMaxR,pc.r); pgMaxG=std::max(pgMaxG,pc.g); pgMaxB=std::max(pgMaxB,pc.b);
            pgSumR+=pc.r; pgSumG+=pc.g; pgSumB+=pc.b;
        }
        const float pgInvCount=vertexCount ? (1.0f/static_cast<float>(vertexCount)) : 0.0f;
        RenderStruct *diagRS=FXRenderer::Instance().GetRenderStruct();


        LOG_SESSION("FX3D POLYGRID-LIGHTDIAG grid=%p paletteUsed min=(%.1f %.1f %.1f) max=(%.1f %.1f %.1f) avg=(%.1f %.1f %.1f) sceneWMAmbient=(%.3f %.3f %.3f) sceneVertexTint=(%.3f %.3f %.3f) renderAmbient=%.6f blend=%s",
                    grid, pgMinR,pgMinG,pgMinB, pgMaxR,pgMaxG,pgMaxB,
                    float(pgSumR*pgInvCount),float(pgSumG*pgInvCount),float(pgSumB*pgInvCount),
                    scene->m_vGlobalWMAmbient.x,scene->m_vGlobalWMAmbient.y,scene->m_vGlobalWMAmbient.z,
                    scene->m_vGlobalVertexTint.x,scene->m_vGlobalVertexTint.y,scene->m_vGlobalVertexTint.z,
                    diagRS ? diagRS->m_fAmbientLight : -999.0f, PolyGridBaseBlendName(grid->m_Base));
        LOG_SESSION("FX3D POLYGRID grid=%p size=%ux%u gridVerts=%u drawVerts=%u tris=%u indices=%u badIndices=%u topology=%s tex=%p materialSource=%s slotIsSprite=%u sprite=%p trackerSprite=%p trackerAnim=%p trackerFrame=%p selectedFrame=%p env=%p pos=(%.2f %.2f %.2f) scale=(%.3f %.3f %.3f) step=(%.3f %.3f) polyScale=(%.3f %.3f) uvStep=(%.6f %.6f) pan=(%.3f %.3f) startUV=(%.6f %.6f) colorA=%u flags=%08X flags2=%08X",
                    grid, grid->m_dwWidth, grid->m_dwHeight, vertexCount, unsigned(verts.size()), unsigned(verts.size() / 3),
                    grid->m_dwIndices, badIndices, generatedTopology ? "GENERATED" : "ENGINE",
                    shared, materialSource, materialSlotIsSprite ? 1u : 0u,
                    grid->m_pSprite, grid->m_SpriteTracker.m_pSprite, grid->m_SpriteTracker.m_pCurAnim,
                    grid->m_SpriteTracker.m_pCurFrame, materialFrame, grid->m_pEnvMap,
                    grid->m_Base.m_vPos.x, grid->m_Base.m_vPos.y, grid->m_Base.m_vPos.z,
                    grid->m_Base.m_vScale.x, grid->m_Base.m_vScale.y, grid->m_Base.m_vScale.z,
                    xInc, zInc, runtimeScaleX, runtimeScaleY, uStep, vStep, rawPanX, rawPanY, startU, startV,
                    unsigned(grid->m_Base.m_nColorA), grid->m_Base.m_dwFlags, grid->m_Base.m_dwFlags2);
    }

    if (LogIsSessionEnabled() && !shared)
    {
        static std::unordered_set<const PolyGridCompat *> s_loggedUnresolvedMaterial;
        static uint32 unresolvedSessionDivider = 0;
        const bool firstUnresolved = s_loggedUnresolvedMaterial.insert(grid).second;
        const bool sessionUnresolved = LogIsSessionEnabled() && ((unresolvedSessionDivider++ % 30u) == 0u);
        if (firstUnresolved || sessionUnresolved)
        {
            SpriteAnimCompat *curAnim = grid->m_SpriteTracker.m_pCurAnim;
            LOG_SESSION("FX3D POLYGRID-MATERIAL-UNRESOLVED grid=%p materialSource=%s resource='%s' slotIsSprite=%u sprite=%p spriteAnims=%p spriteAnimCount=%u trackerSprite=%p curAnim=%p curAnimFrames=%p curAnimFrameCount=%u curFrame=%p curFrameTex=%p",
                        grid, materialSource, materialResourceName ? materialResourceName : "", materialSlotIsSprite ? 1u : 0u, grid->m_pSprite,
                        (materialSlotIsSprite && grid->m_pSprite) ? grid->m_pSprite->m_pAnims : nullptr,
                        (materialSlotIsSprite && grid->m_pSprite) ? grid->m_pSprite->m_nAnims : 0u,
                        grid->m_SpriteTracker.m_pSprite, curAnim,
                        curAnim ? curAnim->m_pFrames : nullptr, curAnim ? curAnim->m_nFrames : 0u,
                        grid->m_SpriteTracker.m_pCurFrame,
                        grid->m_SpriteTracker.m_pCurFrame ? grid->m_SpriteTracker.m_pCurFrame->m_pTexture : nullptr);
        }
    }

    // Frequency/water deformation is produced by Talon by updating m_pData;
    // d3d.ren itself consumes the current height bytes each draw.  Track a
    // cheap hash so F10 proves whether the engine is feeding animated water.
    static int animBudget = 128;
    if (LogIsSessionEnabled() && animBudget > 0)
    {
        static std::unordered_map<const PolyGridCompat *, uint32> s_pgHash;
        uint32 dataHash = 2166136261u;
        int minH = 127, maxH = -128;
        for (uint32 i = 0; i < vertexCount; ++i)
        {
            const int v = static_cast<int>(grid->m_pData[i]);
            minH = std::min(minH, v);
            maxH = std::max(maxH, v);
            dataHash ^= static_cast<uint8>(grid->m_pData[i]);
            dataHash *= 16777619u;
        }
        auto hit = s_pgHash.find(grid);
        if (hit == s_pgHash.end() || hit->second != dataHash)
        {
            s_pgHash[grid] = dataHash;
            if (LogIsSessionEnabled() && ((animBudget > 0 && animBudget--)))
                LOG_SESSION("FX3D POLYGRID-DATA grid=%p hash=%08X range=[%d,%d] changed=1", grid, dataHash, minH, maxH);
        }
    }

    DrawPolyGridVertices(scene, *grid, shared, grid->m_pEnvMap, verts);

    // Exact Talon renderer/client handshake.  Retail d3d.ren does NOT set
    // FLAG_WASDRAWN here.  It sets FLAG_INTERNAL1 (bit 30) in LTObject::m_Flags
    // to say "the renderer saw this object".  CClientMgr consumes that bit on
    // the next client update, clears the internal bookkeeping bits, and then
    // sets FLAG_WASDRAWN for the ClientShell.  CPolyGridFX::Update() tests that
    // engine-produced FLAG_WASDRAWN before updating plasma bytes / surface state.
    // Writing bit 4 directly bypasses this protocol and can be cleared before the 
    // FX update ever sees it.
    grid->m_Base.m_dwFlags |= FLAG_INTERNAL1;

    static std::unordered_set<const PolyGridCompat *> s_loggedRendererSeen;
    if (LogIsSessionEnabled() && (s_loggedRendererSeen.insert(grid).second))
        LOG_SESSION("FX3D POLYGRID-RENDERER-SEEN grid=%p flags=%08X bit=FLAG_INTERNAL1 path=STOCK-TALON-HANDSHAKE",
                    grid, grid->m_Base.m_dwFlags);

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

    // d3d.ren 0x10024C05 begins at object+0x1F8 and walks node+0x40 until
    // the object+0x1B8 sentinel is reached.  Keep exactly that ownership
    // model, but batch consecutive segments into our streaming VBO.
    std::vector<FXVertex> verts;
    verts.reserve(2048);

    const bool reallyClose = (system->m_Base.m_dwFlags & FLAG_REALLYCLOSE) != 0;
    const float nearZ = reallyClose ? 0.01f : 1.0f;
    uint32 guard = 0;
    uint32 sourceLines = 0;
    uint32 drawnLines = 0;
    uint32 clippedLines = 0;
    uint32 rejectedLines = 0;
    uint32 batches = 0;

    auto flush = [&]()
    {
        if (verts.empty())
            return;
        DrawLineVertices(scene, system->m_Base, verts);
        verts.clear();
        ++batches;
    };

    while (line && line != sentinel && guard++ < 65536)
    {
        ++sourceLines;
        const LSPointCompat &p0 = line->m_Points[0];
        const LSPointCompat &p1 = line->m_Points[1];

        const LTVector c0 = ObjectLocalToCamera(scene, system->m_Base, {p0.m_vPos.x, p0.m_vPos.y, p0.m_vPos.z});
        const LTVector c1 = ObjectLocalToCamera(scene, system->m_Base, {p1.m_vPos.x, p1.m_vPos.y, p1.m_vPos.z});

        // Exact retail color contract from 0x10024CB1..0x10024E35:
        // point RGB is converted independently from 0..1 to bytes; object RGB
        // is not multiplied in.  Point alpha * LTObject::m_nColorA supplies
        // final alpha for each endpoint.
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

        // Retail clips the two transformed vertices against the full six-plane
        // view volume before issuing D3DPT_LINELIST (0x10024E35..0x10024E8F).
        // OpenGL performs the side/far clipping for us.  Clip the near plane
        // here so a segment crossing the eye never reaches clip space with a
        // negative/zero W; endpoint color is interpolated exactly as clipping
        // requires.
        if (v0.pos.z < nearZ && v1.pos.z < nearZ)
        {
            ++rejectedLines;
            line = line->m_pNext;
            continue;
        }
        if (v0.pos.z < nearZ)
        {
            const float denom = v1.pos.z - v0.pos.z;
            if (std::fabs(denom) < 1.0e-8f)
            {
                ++rejectedLines;
                line = line->m_pNext;
                continue;
            }
            v0 = LerpLineVertex(v0, v1, (nearZ - v0.pos.z) / denom);
            ++clippedLines;
        }
        else if (v1.pos.z < nearZ)
        {
            const float denom = v0.pos.z - v1.pos.z;
            if (std::fabs(denom) < 1.0e-8f)
            {
                ++rejectedLines;
                line = line->m_pNext;
                continue;
            }
            v1 = LerpLineVertex(v1, v0, (nearZ - v1.pos.z) / denom);
            ++clippedLines;
        }

        if (verts.size() + 2 > MAX_FX_VERTS)
            flush();
        verts.push_back(v0);
        verts.push_back(v1);
        ++drawnLines;
        line = line->m_pNext;
    }

    flush();

    static int logBudget = 128;
    if (LogIsSessionEnabled() && ((logBudget > 0 && logBudget--)))
        LOG_SESSION("FX3D LINESYSTEM system=%p lines=%u drawn=%u clipped=%u rejected=%u batches=%u alpha=%u flags=%08X flags2=%08X reallyClose=%d path=D3D-0x10024A60",
                    system, sourceLines, drawnLines, clippedLines, rejectedLines, batches,
                    static_cast<unsigned>(system->m_Base.m_nColorA),
                    system->m_Base.m_dwFlags, system->m_Base.m_dwFlags2, reallyClose ? 1 : 0);

    // An empty/fully clipped system is a successful no-op, not a renderer
    // callback failure.
    return true;
}

bool FXRenderer::RenderCanvas(SceneDesc *scene, CanvasCompat *canvas)
{
    if (!StockRenderOptions::Instance().DrawCanvases())
        return true;
    if (!scene || !canvas || !canvas->m_pFn)
        return false;

    // Renderer-owned GL state is mirrored on the CPU, avoiding synchronous
    // state queries around the Talon Canvas callback.
    const avp2::render::GLStateSnapshot oldState =
        avp2::render::GLStateCache::Instance().Capture();

    DrawPolyMgrCompat mgr{};
    ResetCanvasManager(mgr, scene, canvas);

    // d3d.ren 0x10022491..0x1002249F: callback(mgr, canvas, userdata),
    // cdecl (caller removes 12 bytes).
    canvas->m_pFn(&mgr, canvas, canvas->m_pFnUserData);

    // The D3D Canvas manager restores its saved texture-stage state in
    // 0x10022645 after the callback.  Our texture addressing lives on the
    // GL texture object itself, so explicitly restore the renderer baseline.
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

    const int oldSrc = m_state.psSrcBlendOverride;
    const int oldDst = m_state.psDestBlendOverride;
    const bool oldEnv = m_state.envMapPolyGrids;
    m_state.psSrcBlendOverride = static_cast<int>(getFloat("PSSrcBlend", -1.0f));
    m_state.psDestBlendOverride = static_cast<int>(getFloat("PSDestBlend", -1.0f));
    m_state.envMapPolyGrids = getFloat("EnvMapPolyGrids", 1.0f) != 0.0f;

    static int budget = 24;
    if (LogIsSessionEnabled() && ((oldSrc != m_state.psSrcBlendOverride || oldDst != m_state.psDestBlendOverride || oldEnv != m_state.envMapPolyGrids || budget > 0) && (budget > 0 && budget--)))
        LOG_SESSION("FX3D STOCK-CVARS PSSrcBlend=%d PSDestBlend=%d EnvMapPolyGrids=%d",
                    m_state.psSrcBlendOverride, m_state.psDestBlendOverride, m_state.envMapPolyGrids ? 1 : 0);
}

FXRenderer &FXRenderer::Instance()
{
    static FXRenderer v;
    return v;
}