#include "subsystems/renderer/Console.h"
#include "../renderer/frame_constants.h"
#include "subsystems/renderer/stock_render_options.h"
#include "../renderer/talon_render_state.h"
#include "sky_renderer.h"
#include "world_renderer.h"
#include "world_model_renderer.h"
#include "world_surface_fx.h"
#include "world_lightmap_system.h"
#include "world_pvs.h"
#include "../textures/texture_manager.h"
#include "../sprites/sprite_renderer.h"
#include "../fx/fx_renderer.h"
#include "../renderer/renderer_core.h"
#include "../../gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "utils/log.h"
#include "subsystems/renderer/fog_state.h"
#include "../../shaders/shader.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>

namespace
{
    static GLint U(const char *name)
    {
        auto *shader = WorldRenderer::Instance().State().worldShader;
        return shader ? shader->Uniform(name) : -1;
    }

    static SharedTexture *ResolveSkyBatchTexture(const WorldBatch &b)
    {
        if (b.animatedSurface &&
            (b.animatedSurface->m_dwFlags & SURF_SPRITEANIMATE) &&
            b.animatedSurface->m_pTexture)
            return b.animatedSurface->m_pTexture;
        return b.texture;
    }

    static void ApplySkyBlend(WorldBlendMode blend, const TalonRenderState &state)
    {
        // Stock sky classifies the object by its first surface, then applies
        // each texture's state changes independently (0x10019510..0x10019553).
        // Opaque defaults are SRCALPHA/ONE with blending disabled
        // (0x100197C3..0x100197F8); translucent defaults are SRCALPHA/
        // INVSRCALPHA, or ONE/ONE for additive (0x10013BA0).
        const bool enabled = state.hasAlphaBlendEnable ? state.alphaBlendEnable
                                                       : blend != WorldBlendMode::Solid;
        const uint32 defaultSrc = blend == WorldBlendMode::Additive ? 2u : 5u;
        const uint32 defaultDst = blend == WorldBlendMode::Alpha ? 6u : 2u;
        const uint32 src = state.hasSrcBlend ? state.srcBlend : defaultSrc;
        const uint32 dst = state.hasDestBlend ? state.destBlend : defaultDst;
        if (enabled)
            GLStateEnable(GL_BLEND);
        else
            GLStateDisable(GL_BLEND);
        GLStateBlendFunc(
            static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(src)),
            static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(dst)));
        GLUniform1i(U("uFogAdditive"), enabled && src == 2u && dst == 2u ? 1 : 0);
        // Sky is a painter pass, including opaque layers.
        GLStateDepthMask(GL_FALSE);
    }

    constexpr size_t SKY_CLIP_MAX_VERTS = 65536u;
    constexpr size_t SKY_STREAM_FRAMES = 3u;
    constexpr size_t SKY_STREAM_SEGMENT_BYTES = SKY_CLIP_MAX_VERTS * sizeof(WorldVertexGPU);
    constexpr size_t SKY_STREAM_TOTAL_BYTES = SKY_STREAM_SEGMENT_BYTES * SKY_STREAM_FRAMES;

    static size_t AlignSkyStream(size_t v) { return (v + 63u) & ~size_t(63u); }

    static bool EnsureSkyClipStream()
    {
        auto &st = SkyRenderer::Instance().State();
        if (st.clipVbo || st.clipFallbackVbo)
            return st.clipVbo || st.clipFallbackVbo;

        glf.CreateBuffers(1, &st.clipVbo);
        glf.CreateBuffers(1, &st.clipFallbackVbo);

        if (st.clipVbo && glf.MapNamedBufferRange && glf.FenceSync && glf.ClientWaitSync && glf.DeleteSync)
        {
            const GLbitfield flags = GL_MAP_WRITE_BIT_ | GL_MAP_PERSISTENT_BIT_ | GL_MAP_COHERENT_BIT_;
            glf.NamedBufferStorage(st.clipVbo, static_cast<GLsizeiptr>(SKY_STREAM_TOTAL_BYTES), nullptr, flags);
            st.clipMapped = glf.MapNamedBufferRange(st.clipVbo, 0, static_cast<GLsizeiptr>(SKY_STREAM_TOTAL_BYTES), flags);
            if (!st.clipMapped)
            {
                glf.DeleteBuffers(1, &st.clipVbo);
                st.clipVbo = 0;
            }
        }
        else if (st.clipVbo)
        {
            glf.DeleteBuffers(1, &st.clipVbo);
            st.clipVbo = 0;
        }

        if (st.clipFallbackVbo)
            glf.NamedBufferStorage(st.clipFallbackVbo, static_cast<GLsizeiptr>(SKY_STREAM_SEGMENT_BYTES), nullptr, GL_DYNAMIC_STORAGE_BIT_);

        static bool logged = false;
        if (LogIsSessionEnabled() && (!logged))
        {
            logged = true;
            LOG_SESSION("SkyRenderer clip stream %s, segment=%zu KB x %zu",
                        st.clipMapped ? "ON" : "FALLBACK", SKY_STREAM_SEGMENT_BYTES / 1024, SKY_STREAM_FRAMES);
        }
        return st.clipVbo || st.clipFallbackVbo;
    }

    static bool UploadSkyClipVertices(const std::vector<WorldVertexGPU> &vertices)
    {
        if (vertices.empty() || vertices.size() > SKY_CLIP_MAX_VERTS || !EnsureSkyClipStream())
            return false;

        auto &st = SkyRenderer::Instance().State();
        const size_t bytes = vertices.size() * sizeof(WorldVertexGPU);
        if (st.clipMapped && st.clipVbo)
        {
            const size_t aligned = AlignSkyStream(st.clipCursorBytes);
            if (aligned + bytes <= SKY_STREAM_SEGMENT_BYTES)
            {
                const size_t absolute = size_t(st.clipFrameSlot) * SKY_STREAM_SEGMENT_BYTES + aligned;
                std::memcpy(static_cast<unsigned char *>(st.clipMapped) + absolute, vertices.data(), bytes);
                st.clipCursorBytes = aligned + bytes;
                st.clipUsedThisFrame = true;
                GLUploadStats::Instance().RecordWorldStreamWrite(GLWorldUploadKind::SkyClip, bytes);
                glf.VertexArrayVertexBuffer(WorldRenderer::Instance().State().vao, 0, st.clipVbo,
                                            static_cast<GLintptr>(absolute), sizeof(WorldVertexGPU));
                WorldSurfaceFxSystem::Instance().BindUvOverride(st.clipVbo);
                return true;
            }
        }

        if (st.clipFallbackVbo)
        {
            GLTrackedWorldNamedBufferSubData(st.clipFallbackVbo, 0, static_cast<GLsizeiptr>(bytes),
                                             vertices.data(), GLWorldUploadKind::SkyClip);
            glf.VertexArrayVertexBuffer(WorldRenderer::Instance().State().vao, 0, st.clipFallbackVbo, 0, sizeof(WorldVertexGPU));
            WorldSurfaceFxSystem::Instance().BindUvOverride(st.clipFallbackVbo);
            return true;
        }
        return false;
    }
    static void SetSkyIdentityReset()
    {
        static const float I[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        GLUniform1i(U("uUseWmDrawState"), 0);
        GLUniform1ui(U("uLegacyDrawFlags"), 0u);
        GLUniform1i(U("uSkyDxt5AlphaOnly"), 0);
        GLUniform1i(U("uSkyHorizonFogGradient"), 0);
        GLUniform1i(U("uSkyClipCameraSpace"), 0);
        GLUniform1i(U("uUseWorld"), 0);
        GLUniformMatrix4fv(U("uWorld"), 1, GL_FALSE, I);
        GLUniform4f(U("uObjectColor"), 1, 1, 1, 1);
    }
}

SkyRenderer &SkyRenderer::Instance()
{
    static SkyRenderer v;
    return v;
}

void SkyRenderer::UploadPortalGeometry()
{
    if (m_state.portalVbo)
        glf.DeleteBuffers(1, &m_state.portalVbo);
    m_state.portalVbo = 0;
    if (m_state.portalVertices.empty())
        return;
    glf.CreateBuffers(1, &m_state.portalVbo);
    if (m_state.portalVbo)
        glf.NamedBufferStorage(m_state.portalVbo,
                               static_cast<GLsizeiptr>(m_state.portalVertices.size() * sizeof(WorldVertexGPU)),
                               m_state.portalVertices.data(), 0);
}

void SkyRenderer::AdvanceStreamFrame()
{
    auto &st = m_state;
    if (!st.clipMapped || !glf.FenceSync || !glf.ClientWaitSync || !glf.DeleteSync)
    {
        st.clipCursorBytes = 0;
        st.clipUsedThisFrame = false;
        return;
    }

    if (st.clipUsedThisFrame)
    {
        if (st.clipFences[st.clipFrameSlot])
            glf.DeleteSync(st.clipFences[st.clipFrameSlot]);
        st.clipFences[st.clipFrameSlot] = glf.FenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE_, 0);
    }

    const uint32 next = (st.clipFrameSlot + 1u) % static_cast<uint32>(SKY_STREAM_FRAMES);
    if (st.clipFences[next])
    {
        const GLenum wait = glf.ClientWaitSync(st.clipFences[next], GL_SYNC_FLUSH_COMMANDS_BIT_, GL_TIMEOUT_IGNORED_);
        if (wait == GL_WAIT_FAILED_)
            LOG_SESSION("SkyRenderer clip stream: glClientWaitSync failed on slot %u", next);
        glf.DeleteSync(st.clipFences[next]);
        st.clipFences[next] = nullptr;
    }
    st.clipFrameSlot = next;
    st.clipCursorBytes = 0;
    st.clipUsedThisFrame = false;
}

void SkyRenderer::Term()
{
    for (void *&fence : m_state.clipFences)
    {
        if (fence && glf.DeleteSync)
        {
            glf.DeleteSync(fence);
            fence = nullptr;
        }
    }
    m_state.clipMapped = nullptr;
    if (m_state.portalVbo)
        glf.DeleteBuffers(1, &m_state.portalVbo);
    if (m_state.clipVbo)
        glf.DeleteBuffers(1, &m_state.clipVbo);
    if (m_state.clipFallbackVbo)
        glf.DeleteBuffers(1, &m_state.clipFallbackVbo);
    m_state.portalVbo = 0;
    m_state.clipVbo = 0;
    m_state.clipFallbackVbo = 0;
    m_state.clipCursorBytes = 0;
    m_state.clipFrameSlot = 0;
    m_state.clipUsedThisFrame = false;
    m_state.portalVertices.clear();
    m_state.portalSpans.clear();
}

static uint32 GetSkyFirstSurfaceFlagsStock(const WorldModelInstanceCompat *wm)
{
    if (!wm || !wm->m_pOriginalBsp || !wm->m_pOriginalBsp->m_pPolies ||
        wm->m_pOriginalBsp->m_dwPolies == 0)
        return 0;
    WorldPolyCompat *p = wm->m_pOriginalBsp->m_pPolies[0];
    return (p && p->m_pSurface) ? p->m_pSurface->m_dwFlags : 0;
}

static WorldBlendMode GetSkyBlendStock(const WorldModelInstanceCompat *wm)
{
    // d3d.ren 0x100197AB..0x100197FD classifies the WHOLE sky WorldModel
    // from its first surface flags (0x10019880), not from LTObject alpha and
    // not independently per material batch.
    const uint32 f = GetSkyFirstSurfaceFlagsStock(wm);
    if ((f & SURF_TRANSPARENT) == 0)
        return WorldBlendMode::Solid;
    return (f & SURF_ADDITIVE) ? WorldBlendMode::Additive : WorldBlendMode::Alpha;
}

static void SetSkyWorldIdentityTransform(const WorldModelInstanceCompat *wm)
{
    static const float I[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    GLUniform1i(U("uUseWmDrawState"), 0);
    GLUniform1ui(U("uLegacyDrawFlags"), 3u);
    GLUniform1i(U("uSkyDxt5AlphaOnly"), 0);
    GLUniform1i(U("uSkyHorizonFogGradient"), 0);
    GLUniform1i(U("uUseWorld"), 0);
    GLUniformMatrix4fv(U("uWorld"), 1, GL_FALSE, I);
    if (wm)
    {
        const LTObjectCompat &o = wm->m_Base;
        GLUniform4f(U("uObjectColor"), o.m_nColorR / 255.0f, o.m_nColorG / 255.0f,
                    o.m_nColorB / 255.0f, o.m_nColorA / 255.0f);
    }
    else
        GLUniform4f(U("uObjectColor"), 1, 1, 1, 1);
}

static void LogSkyTextureD3DState(const char *objectName, SharedTexture *baseShared,
                                  Texture *base, uint32 firstSurf,
                                  const WorldModelInstanceCompat *wm)
{
    if (!LogIsSessionEnabled())
        return;
    if (!baseShared)
        return;
    static std::unordered_set<uintptr_t> logged;
    const uintptr_t key = (reinterpret_cast<uintptr_t>(baseShared) ^
                           (reinterpret_cast<uintptr_t>(wm) >> 4));
    if (logged.size() >= 128 || !logged.insert(key).second)
        return;

    auto *st = reinterpret_cast<SharedTextureCompat *>(baseShared);

    TextureManager::Instance().LogRawDiagnostic(baseShared, objectName ? objectName : "SkyTexture");
    if (base && base->bppIdent == BPP_S3TC_DXT5)
        TextureManager::Instance().LogDXT5AlphaDiagnostic(baseShared, objectName ? objectName : "SkyTexture");
    std::string cmd;
    if (st->m_szCommandString)
    {
        const char *q = st->m_szCommandString;
        for (size_t i = 0; i < 512 && q[i]; ++i)
        {
            const unsigned char ch = static_cast<unsigned char>(q[i]);
            cmd.push_back((ch >= 32 && ch < 127) ? char(ch) : ' ');
        }
    }

    uint32 rsCount = 0, tsCount = 0;
    StateChangeCompat *sc = nullptr;
    if (st->m_pStateChange)
    {
        sc = reinterpret_cast<StateChangeCompat *>(st->m_pStateChange);
        rsCount = sc->m_RenderList.size();
        tsCount = sc->m_TextureList.size();
        if (rsCount > 64)
            rsCount = 64;
        if (tsCount > 64)
            tsCount = 64;
    }

    const LTObjectCompat *o = wm ? &wm->m_Base : nullptr;
    LOG_SESSION("World3D SKY-D3D object='%s' firstSurf=%08X rgba=(%u %u %u %u) tex=%p GL=%u scaled=%ux%u mipOffset=%u iFlags=%08X userFlags=%08X stockFmt=%u prefer16=%u force4444=%u mips=%u bilinear=%u trilinear=%u minFilter=%04X magFilter=%04X linked=%p texType=%u state=%p rs=%u ts=%u cmd='%s'",
                objectName ? objectName : "?", firstSurf,
                o ? o->m_nColorR : 255, o ? o->m_nColorG : 255, o ? o->m_nColorB : 255, o ? o->m_nColorA : 255,
                baseShared, base ? base->texture : 0, base ? base->scaledWidth : 0, base ? base->scaledHeight : 0,
                base ? base->mipOffset : 0,
                base ? base->dtxIFlags : 0u, base ? base->dtxUserFlags : 0u,
                base ? static_cast<unsigned>(base->stockFormatClass) : 0u,
                (base && (base->dtxIFlags & 0x0002u)) ? 1u : 0u,
                (base && (base->dtxIFlags & 0x0080u)) ? 1u : 0u,
                base ? base->mipLevels : 0u, base ? unsigned(base->stockBilinear) : 0u,
                base ? unsigned(base->stockTrilinear) : 0u,
                base ? unsigned(base->glMinFilter) : 0u, base ? unsigned(base->glMagFilter) : 0u,
                st->m_pLinkedTexture, st->m_eTexType, st->m_pStateChange,
                rsCount, tsCount, cmd.c_str());
    if (sc)
    {
        for (uint32 i = 0; i < rsCount; ++i)
        {
            const RenderStateCompat &r = sc->m_RenderList.m_pFirst[i];
            LOG_SESSION("World3D SKY-D3D-RS object='%s' i=%u state=%u value=%08X",
                        objectName ? objectName : "?", i, r.m_dwRenderStateType, r.m_dwRenderState);
        }
        for (uint32 i = 0; i < tsCount; ++i)
        {
            const TextureStateCompat &t = sc->m_TextureList.m_pFirst[i];
            LOG_SESSION("World3D SKY-D3D-TS object='%s' i=%u stage=%u state=%u value=%08X",
                        objectName ? objectName : "?", i, t.m_dwStage, t.m_dwTextureStateType, t.m_dwTextureState);
        }
    }
}

static Texture *ApplySkyWorldMaterial(const WorldBatch &b, const char *objectName, uint32 firstSurf, const WorldModelInstanceCompat *wm)
{
    // Dedicated Talon sky path (d3d.ren 0x10019351..0x10019558): the sky
    // polygon builder binds the surface BASE texture and scales the authored
    // SPolyVertex::m_fScaledU/V by that texture's active RTexture U/V scale.
    // It does not enter the normal WorldModel linked-detail/envmap material
    // combiner at 0x1000A538.  Using ApplyWorldMaterial here incorrectly adds
    // a second transformed UV set to cloud shells (p1s1 uses linked detail
    // textures with very large scales), producing the characteristic long
    // smeared bands.
    SharedTexture *baseShared = ResolveSkyBatchTexture(b);
    Texture *base = TextureManager::Instance().GetOrEnsure(baseShared);
    GLStateBindTextureUnit(0, base ? base->texture : 0);
    const bool horizonCloud2Dxt5 = objectName && std::strcmp(objectName, "clouds2") == 0 &&
                                   base && base->bppIdent == BPP_S3TC_DXT5 && base->width == 256u && base->height == 512u;
    GLUniform1i(U("uSkyDxt5AlphaOnly"),
                (horizonCloud2Dxt5 && TextureManager::Instance().DXT5AlphaOnlyEnabled()) ? 1 : 0);

    // p1s1's TranslucentWorldModel named Horizon is the authored
    // blackgradient2.dtx fog belt.  Match it narrowly by the sky object name,
    // transparent first-surface classification, 16x256 texture shape, and the
    // stock ViewModes/Fog command table so unrelated black textures are never
    // recoloured.
    bool horizonFogGradient = false;
    if (objectName && std::strcmp(objectName, "Horizon") == 0 && base &&
        base->scaledWidth == 16u && base->scaledHeight == 256u &&
        (firstSurf & SURF_TRANSPARENT) != 0u && baseShared)
    {
        const auto *hs = reinterpret_cast<const SharedTextureCompat *>(baseShared);
        const char *cmd = hs ? hs->m_szCommandString : nullptr;
        horizonFogGradient = cmd && std::strstr(cmd, "ViewModes") && std::strstr(cmd, "Fog");
    }
    GLUniform1i(U("uSkyHorizonFogGradient"), horizonFogGradient ? 1 : 0);
    if (horizonFogGradient)
    {
        static bool logged = false;
        if (LogIsSessionEnabled() && (!logged))
        {
            logged = true;
            const auto *hs = reinterpret_cast<const SharedTextureCompat *>(baseShared);
            LOG_SESSION("World3D SKY-HORIZON-FOG object='%s' GL=%u size=%ux%u fogRGB=(%.4f %.4f %.4f) cmd='%s' path=TEXTURE-ALPHA/FOG-RGB",
                        objectName, base->texture, base->scaledWidth, base->scaledHeight,
                        g_fogState.r, g_fogState.g, g_fogState.b, hs && hs->m_szCommandString ? hs->m_szCommandString : "");
        }
    }

    const float baseW = (base && base->scaledWidth) ? float(base->scaledWidth)
                                                    : ((base && base->width) ? float(base->width) : 1.0f);
    const float baseH = (base && base->scaledHeight) ? float(base->scaledHeight)
                                                     : ((base && base->height) ? float(base->height) : 1.0f);
    const float uvScaleX = (b.animatedSurface && baseW > 0.0f) ? (b.uvNormWidth / baseW) : 1.0f;
    const float uvScaleY = (b.animatedSurface && baseH > 0.0f) ? (b.uvNormHeight / baseH) : 1.0f;

    // Sky uses only the base texture coordinate set.  Explicitly clear any
    // linked stage left by a previous normal-world draw.
    GLStateBindTextureUnit(4, 0);
    GLUniform1i(U("uLinkedTexMode"), 0);
    GLUniform1i(U("uUseWorldMaterialParams"), 0);
    GLUniform4f(U("uLinkedParams0"), uvScaleX, uvScaleY, baseW, baseH);
    GLUniform4f(U("uLinkedParams1"), 1.0f, 1.0f, 0.0f, 1.0f);
    GLUniform4f(U("uLinkedParams2"), 1.0f, 0.0f, 0.0f, 0.0f);

    LogSkyTextureD3DState(objectName, baseShared, base, firstSurf, wm);

    if (baseShared)
    {
        auto *st = reinterpret_cast<SharedTextureCompat *>(baseShared);
        if (st->m_pLinkedTexture)
        {
            static std::unordered_set<uintptr_t> s_logged;
            const uintptr_t key = reinterpret_cast<uintptr_t>(baseShared);
            if (LogIsSessionEnabled() && (s_logged.size() < 64 && s_logged.insert(key).second))
                LOG_SESSION("World3D SKY-MATERIAL base=%p GL=%u size=%.0fx%.0f linked=%p texType=%u path=BASE-ONLY/D3D-0x10019351",
                            baseShared, base ? base->texture : 0, baseW, baseH,
                            st->m_pLinkedTexture, st->m_eTexType);
        }
    }
    return base;
}

static LTVector SkyProbeQRotate(const LTRotation &rot, const LTVector &v, bool inverse)
{
    float x = rot.x, y = rot.y, z = rot.z, w = rot.w;
    const float len = std::sqrt(x * x + y * y + z * z + w * w);
    if (len > 1.0e-8f)
    {
        x /= len;
        y /= len;
        z /= len;
        w /= len;
    }
    if (inverse)
    {
        x = -x;
        y = -y;
        z = -z;
    }
    // q*v*q^-1, matching the GLSL qrotate implementation.
    const float cx1 = y * v.z - z * v.y;
    const float cy1 = z * v.x - x * v.z;
    const float cz1 = x * v.y - y * v.x;
    const float tx = cx1 + w * v.x;
    const float ty = cy1 + w * v.y;
    const float tz = cz1 + w * v.z;
    const float cx2 = y * tz - z * ty;
    const float cy2 = z * tx - x * tz;
    const float cz2 = x * ty - y * tx;
    return {v.x + 2.0f * cx2, v.y + 2.0f * cy2, v.z + 2.0f * cz2};
}

static bool SkyProbeIsHorizon(const char *objectName)
{
    if (!objectName)
        return false;
    return std::strcmp(objectName, "Horizon") == 0 ||
           std::strcmp(objectName, "horizon") == 0;
}

static void LogHorizonSkyPolyProbe(const SceneDesc *skyScene, const WorldPolyCompat *poly,
                                   const WorldBatch *batch, const char *objectName)
{
    if (!LogIsSessionEnabled())
        return;
    if (!skyScene || !poly || !batch || !SkyProbeIsHorizon(objectName))
        return;

    static std::unordered_set<uintptr_t> loggedPolys;
    const uintptr_t key = reinterpret_cast<uintptr_t>(poly);
    if (loggedPolys.size() >= 64 || !loggedPolys.insert(key).second)
        return;

    SharedTexture *shared = ResolveSkyBatchTexture(*batch);
    Texture *tex = TextureManager::Instance().Ensure(shared, false);
    const float tw = (tex && tex->scaledWidth) ? float(tex->scaledWidth) : ((tex && tex->width) ? float(tex->width) : 1.0f);
    const float th = (tex && tex->scaledHeight) ? float(tex->scaledHeight) : ((tex && tex->height) ? float(tex->height) : 1.0f);
    const float uScale = (tw > 0.0f) ? 1.0f / tw : 1.0f;
    const float vScale = (th > 0.0f) ? 1.0f / th : 1.0f;
    const float tanX = std::tan(std::max(0.01f, skyScene->m_fFovX * 0.5f));
    const float tanY = std::tan(std::max(0.01f, skyScene->m_fFovY * 0.5f));
    const float zn = 0.01f;
    const float zf = std::max(2.0f, skyScene->m_fFarZ);
    const float A = (zf + zn) / (zf - zn);
    const float B = (-2.0f * zf * zn) / (zf - zn);
    const LTPlaneCompat *pl = poly->m_pPlane ? reinterpret_cast<const LTPlaneCompat *>(poly->m_pPlane) : nullptr;
    const float side = pl ? (pl->m_vNormal.x * skyScene->m_vPos.x + pl->m_vNormal.y * skyScene->m_vPos.y +
                             pl->m_vNormal.z * skyScene->m_vPos.z - pl->m_fDist)
                          : 0.0f;

    LOG_SESSION("World3D SKY-HORIZON-PROBE poly=%p index=%u verts=%u surf=%08X lmFlags=%04X center=(%.4f %.4f %.4f) planeN=(%.6f %.6f %.6f) planeD=%.6f side=%.6f tex=%p GL=%u size=%.0fx%.0f uvScale=(%.9f %.9f)",
                poly, unsigned(poly->m_wIndex), unsigned(poly->m_wNumVerts),
                poly->m_pSurface ? poly->m_pSurface->m_dwFlags : 0u, unsigned(poly->m_wLMPlaneAndFlags),
                poly->m_vCenter.x, poly->m_vCenter.y, poly->m_vCenter.z,
                pl ? pl->m_vNormal.x : 0.0f, pl ? pl->m_vNormal.y : 0.0f, pl ? pl->m_vNormal.z : 0.0f, pl ? pl->m_fDist : 0.0f,
                side, shared, tex ? tex->texture : 0, tw, th, uScale, vScale);

    const SPolyVertexCompat *pv = poly->m_Vertices;
    const uint32 n = std::min<uint32>(poly->m_wNumVerts, 32u);
    for (uint32 i = 0; i < n; ++i)
    {
        if (!pv[i].m_pPoints)
            continue;
        const LTVector P = pv[i].m_pPoints->m_vVec;
        const LTVector D{P.x - skyScene->m_vPos.x, P.y - skyScene->m_vPos.y, P.z - skyScene->m_vPos.z};
        const LTVector C = SkyProbeQRotate(skyScene->m_rRotation, D, true);
        const float clipX = C.x / tanX;
        const float clipY = C.y / tanY;
        const float clipZ = A * C.z + B;
        const float clipW = C.z;
        const float invW = (std::fabs(clipW) > 1.0e-8f) ? (1.0f / clipW) : 0.0f;
        const float ndcX = clipX * invW, ndcY = clipY * invW, ndcZ = clipZ * invW;
        LOG_SESSION("World3D SKY-HORIZON-VERT poly=%u v=%u P=(%.6f %.6f %.6f) rawUV=(%.6f %.6f) uv=(%.9f %.9f) rgba=(%u %u %u %u) cam=(%.6f %.6f %.6f) clip=(%.6f %.6f %.6f %.6f) ndc=(%.6f %.6f %.6f)",
                    unsigned(poly->m_wIndex), unsigned(i), P.x, P.y, P.z,
                    pv[i].m_fScaledU, pv[i].m_fScaledV, pv[i].m_fScaledU * uScale, pv[i].m_fScaledV * vScale,
                    unsigned(pv[i].m_nColorR), unsigned(pv[i].m_nColorG), unsigned(pv[i].m_nColorB), unsigned(pv[i].m_nColorA),
                    C.x, C.y, C.z, clipX, clipY, clipZ, clipW, ndcX, ndcY, ndcZ);
    }
}

static bool FindSkyPolySpan(const WorldModelCache *c, const WorldPolyCompat *poly,
                            const WorldBatch *&outBatch, const PolySpan *&outSpan)
{
    outBatch = nullptr;
    outSpan = nullptr;
    if (!c || !poly)
        return false;
    for (const WorldBatch &b : c->batches)
        for (const PolySpan &span : b.spans)
            if (span.poly == poly)
            {
                outBatch = &b;
                outSpan = &span;
                return true;
            }
    return false;
}

static WorldVertexGPU LerpSkyClipVertex(const WorldVertexGPU &a, const WorldVertexGPU &b, float t)
{
    WorldVertexGPU o{};
    const float *A = reinterpret_cast<const float *>(&a);
    const float *B = reinterpret_cast<const float *>(&b);
    float *O = reinterpret_cast<float *>(&o);
    constexpr size_t N = sizeof(WorldVertexGPU) / sizeof(float);
    for (size_t i = 0; i < N; ++i)
        O[i] = A[i] + (B[i] - A[i]) * t;
    return o;
}

static LTVector SkyClipCameraPoint(const SceneDesc *skyScene, const WorldVertexGPU &v)
{
    const LTVector P{v.x, v.y, v.z};
    const LTVector D{P.x - skyScene->m_vPos.x, P.y - skyScene->m_vPos.y, P.z - skyScene->m_vPos.z};
    return SkyProbeQRotate(skyScene->m_rRotation, D, true);
}

// d3d.ren 0x10019351 transforms the complete SPolyVertex polygon to camera
// space, calls the 0x1000AFB1 clipper with mask 0x3F, and only then projects
// and DrawPrimitive(D3DPT_TRIANGLEFAN).  Do the equivalent in source/world
// space here so attributes are generated at the clipped polygon edges before
// we triangulate the fan for OpenGL.
static bool ClipSkyPolygonD3D(const SceneDesc *skyScene, std::vector<WorldVertexGPU> &poly)
{
    if (!skyScene || poly.size() < 3)
        return false;
    const float tx = std::max(1.0e-6f, std::tan(skyScene->m_fFovX * 0.5f));
    const float ty = std::max(1.0e-6f, std::tan(skyScene->m_fFovY * 0.5f));
    const float nz = 0.01f;

    // d3d.ren clips after transforming the polygon to camera space.  Do the
    // same literally.  The sky BSP lives around -116000 world units; clipping
    // in world space and then storing a generated point back at that magnitude
    // loses enough float precision that a 0.01-unit near-plane intersection can
    // jump across the plane as the camera moves.  That produced the large
    // intermittent angular holes in the Horizon ring.
    for (WorldVertexGPU &v : poly)
    {
        const LTVector c = SkyClipCameraPoint(skyScene, v);
        v.x = c.x;
        v.y = c.y;
        v.z = c.z;
    }

    auto clipPlane = [&](auto dist) -> bool
    {
        if (poly.size() < 3)
            return false;
        std::vector<WorldVertexGPU> out;
        out.reserve(poly.size() + 2);
        WorldVertexGPU prev = poly.back();
        float dp = dist(LTVector{prev.x, prev.y, prev.z});
        bool inp = dp >= 0.0f;
        for (const WorldVertexGPU &cur : poly)
        {
            const float dc = dist(LTVector{cur.x, cur.y, cur.z});
            const bool inc = dc >= 0.0f;
            if (inp != inc)
            {
                const float denom = dp - dc;
                float t = (std::fabs(denom) > 1.0e-12f) ? (dp / denom) : 0.0f;
                t = std::clamp(t, 0.0f, 1.0f);
                out.push_back(LerpSkyClipVertex(prev, cur, t));
            }
            if (inc)
                out.push_back(cur);
            prev = cur;
            dp = dc;
            inp = inc;
        }
        poly.swap(out);
        return poly.size() >= 3;
    };

    // Sky objects are a painter pass with depth test/write disabled.  Keep the
    // near and four side planes, but intentionally do NOT clip against the
    // normal world's far plane.  The authored Talon sky shell can extend past
    // SceneDesc::m_fFarZ, and clipping it there produces the large triangular
    // holes seen at the horizon.  Sky fog already has its own independent
    // SkyFogNearZ/SkyFogFarZ range.
    if (!clipPlane([&](const LTVector &c)
                   { return c.z - nz; }))
        return false;
    if (!clipPlane([&](const LTVector &c)
                   { return c.x + c.z * tx; }))
        return false;
    if (!clipPlane([&](const LTVector &c)
                   { return c.z * tx - c.x; }))
        return false;
    if (!clipPlane([&](const LTVector &c)
                   { return c.y + c.z * ty; }))
        return false;
    if (!clipPlane([&](const LTVector &c)
                   { return c.z * ty - c.y; }))
        return false;
    return poly.size() >= 3;
}

struct SkyWorldDrawRun
{
    const WorldBatch *batch = nullptr;
    uint32 firstVertex = 0;
    uint32 vertexCount = 0;
    uint32 spanCount = 0;
};

static bool AppendOneSkyWorldSpan(SceneDesc *skyScene, const WorldBatch &b, const PolySpan &span,
                                  const char *objectName, uint32 firstSurf,
                                  std::vector<WorldVertexGPU> &vertices,
                                  std::vector<SkyWorldDrawRun> &runs,
                                  uint64_t &tris)
{
    WorldPolyCompat *srcPoly = span.poly;
    if (!skyScene || !srcPoly || srcPoly->m_wNumVerts < 3 || srcPoly->m_wNumVerts > 128)
        return false;

    SharedTexture *shared = ResolveSkyBatchTexture(b);
    Texture *t = TextureManager::Instance().GetOrEnsure(shared);
    const float iw = (t && t->scaledWidth) ? 1.0f / float(t->scaledWidth) : 1.0f;
    const float ih = (t && t->scaledHeight) ? 1.0f / float(t->scaledHeight) : 1.0f;
    LTVector N{0, 0, 0};
    if (srcPoly->m_pPlane)
        N = reinterpret_cast<const LTPlaneCompat *>(srcPoly->m_pPlane)->m_vNormal;

    std::vector<WorldVertexGPU> clipped;
    clipped.reserve(srcPoly->m_wNumVerts + 8u);
    for (uint32 i = 0; i < srcPoly->m_wNumVerts; ++i)
    {
        const SPolyVertexCompat &sv = srcPoly->m_Vertices[i];
        if (!sv.m_pPoints)
            return false;
        const LTVector &q = sv.m_pPoints->m_vVec;
        clipped.push_back({q.x, q.y, q.z,
                           sv.m_fScaledU * iw, sv.m_fScaledV * ih, 0.0f, 0.0f,
                           sv.m_nColorR / 255.0f, sv.m_nColorG / 255.0f, sv.m_nColorB / 255.0f, sv.m_nColorA / 255.0f,
                           0.0f, 0.0f, srcPoly->m_vCenter.x, srcPoly->m_vCenter.y, srcPoly->m_vCenter.z, N.x, N.y, N.z,
                           0.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 0.0f});
    }

    const uint32 before = static_cast<uint32>(clipped.size());
    if (!ClipSkyPolygonD3D(skyScene, clipped))
        return false;

    const uint32 fanVerts = static_cast<uint32>((clipped.size() - 2u) * 3u);
    if (!fanVerts)
        return false;
    const uint32 first = static_cast<uint32>(vertices.size());
    vertices.reserve(vertices.size() + fanVerts);
    for (size_t i = 1; i + 1 < clipped.size(); ++i)
    {
        vertices.push_back(clipped[0]);
        vertices.push_back(clipped[i]);
        vertices.push_back(clipped[i + 1]);
    }

    // Preserve the exact BSP painter order.  We only merge adjacent spans
    // that belong to the same cached material batch, so alpha-blended sky
    // layers retain primitive order while avoiding one draw call per polygon.
    if (runs.empty() || runs.back().batch != &b ||
        runs.back().firstVertex + runs.back().vertexCount != first)
    {
        SkyWorldDrawRun r{};
        r.batch = &b;
        r.firstVertex = first;
        r.vertexCount = fanVerts;
        r.spanCount = 1;
        runs.push_back(r);
    }
    else
    {
        runs.back().vertexCount += fanVerts;
        ++runs.back().spanCount;
    }
    tris += fanVerts / 3u;

    if (LogIsSessionEnabled())
    {
        static uint32 clipBudget = 512;
        if (LogIsSessionEnabled() && (clipBudget))
        {
            --clipBudget;
            float minZ = 1.0e30f, maxZ = -1.0e30f;
            float minNdcX = 1.0e30f, maxNdcX = -1.0e30f, minNdcY = 1.0e30f, maxNdcY = -1.0e30f;
            const float tx = std::max(1.0e-6f, std::tan(skyScene->m_fFovX * 0.5f));
            const float ty = std::max(1.0e-6f, std::tan(skyScene->m_fFovY * 0.5f));
            for (const WorldVertexGPU &cv : clipped)
            {
                minZ = std::min(minZ, cv.z);
                maxZ = std::max(maxZ, cv.z);
                if (cv.z > 1.0e-6f)
                {
                    const float nx = cv.x / (cv.z * tx);
                    const float ny = cv.y / (cv.z * ty);
                    minNdcX = std::min(minNdcX, nx);
                    maxNdcX = std::max(maxNdcX, nx);
                    minNdcY = std::min(minNdcY, ny);
                    maxNdcY = std::max(maxNdcY, ny);
                }
            }
            const float vpL = float(skyScene->m_rcViewport.m_nLeft);
            const float vpT = float(skyScene->m_rcViewport.m_nTop);
            const float vpW = float(skyScene->m_rcViewport.m_nRight - skyScene->m_rcViewport.m_nLeft);
            const float vpH = float(skyScene->m_rcViewport.m_nBottom - skyScene->m_rcViewport.m_nTop);
            const float sx0 = vpL + (minNdcX * 0.5f + 0.5f) * vpW;
            const float sx1 = vpL + (maxNdcX * 0.5f + 0.5f) * vpW;
            const float sy0 = vpT + (0.5f - maxNdcY * 0.5f) * vpH;
            const float sy1 = vpT + (0.5f - minNdcY * 0.5f) * vpH;
            LOG_SESSION("World3D SKY-SPAN-BUILD object='%s' poly=%u before=%u after=%u tris=%u surf=%08X tex=%p GL=%u size=%ux%u bpp=%u screen=(%.1f,%.1f)-(%.1f,%.1f) ndc=(%.3f,%.3f)-(%.3f,%.3f) z=%.6f..%.6f cameraSpace=1",
                        objectName ? objectName : "?", unsigned(srcPoly->m_wIndex), before, unsigned(clipped.size()), unsigned(fanVerts / 3u),
                        firstSurf, shared, t ? t->texture : 0, t ? t->scaledWidth : 0, t ? t->scaledHeight : 0, t ? t->bppIdent : 0,
                        sx0, sy0, sx1, sy1, minNdcX, minNdcY, maxNdcX, maxNdcY, minZ, maxZ);
        }
    }
    return true;
}

static void SubmitSkyWorldRuns(WorldModelInstanceCompat *wm,
                               const std::vector<WorldVertexGPU> &vertices,
                               const std::vector<SkyWorldDrawRun> &runs,
                               WorldBlendMode blend,
                               const char *objectName, uint32 firstSurf,
                               uint32 &draws)
{
    if (vertices.empty() || runs.empty())
        return;

    // One transient sky geometry allocation per WorldModel, then one draw for
    // each contiguous material run. The allocation comes from a persistently
    // mapped three-frame ring; overflow/unsupported drivers retain a separate
    // SubData fallback VBO so the optimization cannot corrupt in-flight data.
    if (!UploadSkyClipVertices(vertices))
        return;
    GLUniform1i(U("uSkyClipCameraSpace"), 1);
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);

    uint32 submittedSpans = 0;
    for (const SkyWorldDrawRun &run : runs)
    {
        if (!run.batch || !run.vertexCount)
            continue;
        Texture *t = ApplySkyWorldMaterial(*run.batch, objectName, firstSurf, wm);
        SharedTexture *runShared = ResolveSkyBatchTexture(*run.batch);
        const TalonRenderState d3d = TalonRenderStateSystem::Instance().Decode(runShared);
        GLStateBindTextureUnit(1, WorldLightmapSystem::Instance().State().atlas);
        GLUniform1i(U("uTextured"), t && t->texture ? 1 : 0);
        GLUniform1i(U("uFullBrightTexture"), (t && t->fullBright) ? 1 : 0);
        GLUniform1i(U("uLightmapped"), 0);
        GLUniform1i(U("uNoLight"), 1);
        // The dedicated stock sky draw never enters the chromakey object
        // pass (0x10013E00). FLAG2_CHROMAKEY alone must not introduce a
        // 0.5 cutoff: it removes DM-PYRAMID's low-alpha cloud textures.
        // Texture state changes can explicitly enable/disable alpha testing.
        const bool alphaTest = d3d.hasAlphaTestEnable && d3d.alphaTestEnable;
        const float textureAlphaRef = t ? t->alphaRef : run.batch->alphaRef;
        const float ar = TalonRenderStateSystem::Instance().AlphaRef01(
            d3d, textureAlphaRef > 0.0f ? textureAlphaRef : 0.0f);
        GLUniform1i(U("uAlphaTest"), alphaTest ? 1 : 0);
        GLUniform1f(U("uAlphaRef"), ar);
        GLUniform1i(U("uAlphaFunc"), d3d.hasAlphaFunc ? static_cast<GLint>(d3d.alphaFunc) : 5);
        GLUniform1ui(U("uTexFxMask"), 0);
        GLUniform1i(U("uPanSkyEnabled"), 0);
        GLStateBindTextureUnit(3, 0);
        ApplySkyBlend(blend, d3d);
        glf.DrawArrays(GL_TRIANGLES_, static_cast<GLint>(run.firstVertex), static_cast<GLsizei>(run.vertexCount));
        ++draws;
        submittedSpans += run.spanCount;
    }
    GLUniform1i(U("uSkyClipCameraSpace"), 0);

    if (LogIsSessionEnabled())
    {
        static uint32 batchBudget = 128;
        if (LogIsSessionEnabled() && (batchBudget))
        {
            --batchBudget;
            LOG_SESSION("World3D SKY-BATCH object='%s' spans=%u runs=%u verts=%u tris=%u draws=%u path=ONE-UPLOAD/CONTIGUOUS-MATERIAL-RUNS",
                        objectName ? objectName : "?", submittedSpans, unsigned(runs.size()), unsigned(vertices.size()),
                        unsigned(vertices.size() / 3u), unsigned(runs.size()));
        }
    }
}

// Exact d3d.ren 0x1001955E BSP traversal for sky WorldModels.  Stock does
// not flatten the original BSP into an unordered batch draw: it walks the
// original BSP against the sky-camera position, renders only polygons whose
// plane faces the camera (dot(N,C)-D > 0), and visits the two node children in
// the same painter order before returning to 0x10019691.
static void DrawSkyWorldBspExact(SceneDesc *skyScene, WorldModelInstanceCompat *wm,
                                 WorldModelCache *c,
                                 const char *objectName, uint32 firstSurf,
                                 std::vector<WorldVertexGPU> &vertices,
                                 std::vector<SkyWorldDrawRun> &runs,
                                 uint64_t &tris,
                                 uint32 &visited, uint32 &facing, uint32 &rejected)
{
    if (!skyScene || !wm || !wm->m_pOriginalBsp || !wm->m_pOriginalBsp->m_pRootNode)
        return;

    NodeCompat *node = wm->m_pOriginalBsp->m_pRootNode;
    NodeCompat *stack[2048];
    uint32 sp = 0;
    while (node || sp)
    {
        if (!node)
        {
            node = stack[--sp];
            continue;
        }
        if (node->m_nFlags & 0x3u)
        {
            node = (sp ? stack[--sp] : nullptr);
            continue;
        }

        ++visited;
        WorldPolyCompat *poly = node->m_pPoly;
        bool front = false;
        if (poly && poly->m_pPlane)
        {
            const LTPlaneCompat *pl = reinterpret_cast<const LTPlaneCompat *>(poly->m_pPlane);
            const LTVector &C = skyScene->m_vPos;
            const float side = pl->m_vNormal.x * C.x + pl->m_vNormal.y * C.y + pl->m_vNormal.z * C.z - pl->m_fDist;
            front = (side > 0.0f); // d3d.ren compares against exact 0.0 at 0x1001964D.
        }

        const uint32 choose = front ? 1u : 0u;
        if (front && poly && poly->m_pSurface && !(poly->m_pSurface->m_dwFlags & SURF_INVISIBLE))
        {
            ++facing;
            const WorldBatch *b = nullptr;
            const PolySpan *span = nullptr;
            if (FindSkyPolySpan(c, poly, b, span) && b && span)
            {
                LogHorizonSkyPolyProbe(skyScene, poly, b, objectName);
                AppendOneSkyWorldSpan(skyScene, *b, *span, objectName, firstSurf, vertices, runs, tris);
            }
        }
        else if (poly)
            ++rejected;

        // 0x1001966E..0x10019683: push child[choose], immediately continue
        // with child[!choose].  This preserves Talon's BSP painter ordering.
        NodeCompat *deferred = node->m_pSides[choose];
        NodeCompat *immediate = node->m_pSides[choose ? 0 : 1];
        if (deferred && sp < 2048)
            stack[sp++] = deferred;
        node = immediate;
    }
}

static LTVector ComputeSkyViewPos(const SceneDesc *scene, const MainWorldCompat *world)
{
    LTVector pct{0.5f, 0.5f, 0.5f};
    if (scene && world && scene->m_nDrawMode == DRAWMODE_NORMAL)
    {
        const LTVector d{
            world->m_vExtentsMax.x - world->m_vExtentsMin.x,
            world->m_vExtentsMax.y - world->m_vExtentsMin.y,
            world->m_vExtentsMax.z - world->m_vExtentsMin.z};
        if (fabsf(d.x) > 1e-6f)
            pct.x = (scene->m_vPos.x - world->m_vExtentsMin.x) / d.x;
        if (fabsf(d.y) > 1e-6f)
            pct.y = (scene->m_vPos.y - world->m_vExtentsMin.y) / d.y;
        if (fabsf(d.z) > 1e-6f)
            pct.z = (scene->m_vPos.z - world->m_vExtentsMin.z) / d.z;
    }

    return {
        scene->m_SkyDef.m_vViewMin.x + (scene->m_SkyDef.m_vViewMax.x - scene->m_SkyDef.m_vViewMin.x) * pct.x,
        scene->m_SkyDef.m_vViewMin.y + (scene->m_SkyDef.m_vViewMax.y - scene->m_SkyDef.m_vViewMin.y) * pct.y,
        scene->m_SkyDef.m_vViewMin.z + (scene->m_SkyDef.m_vViewMax.z - scene->m_SkyDef.m_vViewMin.z) * pct.z};
}

static void DrawOneSkyWorldModel(SceneDesc *skyScene, MainWorldCompat *world, WorldModelInstanceCompat *wm,
                                 uint32 &draws, uint64_t &tris)
{
    if (!skyScene || !world || !wm || !(wm->m_Base.m_dwFlags & FLAG_VISIBLE) || !wm->m_pOriginalBsp)
        return;
    WorldModelCache *c = WorldRenderer::Instance().WorldModels().GetOrCreateCache(world, wm->m_pOriginalBsp);
    if (!c || !WorldRenderer::Instance().WorldModels().BindGeometry(c))
        return;

    // Sky brushes are fullbright. Disable the per-cache Gouraud SSBO here;
    // sky never receives normal world/model lighting.
    GLUniform1i(U("uGpuVertexLight"), 0);
    GLUniform1ui(U("uVertexLightVertexBase"), 0u);
    GLUniform1ui(U("uVertexLightDataBase"), 0u);
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 6, 0);
    // d3d.ren 0x1001955E renders sky WorldModels directly from the original
    // BSP tree in sky-space. Unlike an ordinary WorldModel draw, the sky path
    // does not apply the LTObject instance position/rotation transform before
    // traversing/submitting the BSP. Applying it here double-transforms the
    // authored sky layers (most visibly the large p1s1 cloud shells).
    SetSkyWorldIdentityTransform(wm);
    GLUniform1i(U("uUseGridLight"), 0);
    // Do NOT disable fog here. Stock d3d.ren leaves FogEnable alone and swaps
    // FOGSTART/FOGEND to SkyFogNearZ/SkyFogFarZ for the entire sky phase.
    const bool skyObjectFog = g_fogState.enabled && ((wm->m_Base.m_dwFlags & FLAG_FOGDISABLE) == 0);
    GLUniform1i(U("uFogEnabled"), skyObjectFog ? 1 : 0);

    const uint32 firstSurf = GetSkyFirstSurfaceFlagsStock(wm);
    const WorldBlendMode skyBlend = GetSkyBlendStock(wm);
    uint32 visited = 0, facing = 0, rejected = 0;
    std::vector<WorldVertexGPU> skyVertices;
    std::vector<SkyWorldDrawRun> skyRuns;
    skyVertices.reserve(2048);
    skyRuns.reserve(8);
    DrawSkyWorldBspExact(skyScene, wm, c, wm->m_pOriginalBsp->m_szWorldName, firstSurf,
                         skyVertices, skyRuns, tris, visited, facing, rejected);
    SubmitSkyWorldRuns(wm, skyVertices, skyRuns, skyBlend, wm->m_pOriginalBsp->m_szWorldName, firstSurf, draws);
    static std::unordered_set<uintptr_t> s_skyTraversalLogged;
    const uintptr_t tkey = reinterpret_cast<uintptr_t>(wm->m_pOriginalBsp);
    if (LogIsSessionEnabled() && (s_skyTraversalLogged.size() < 128 && s_skyTraversalLogged.insert(tkey).second))
        LOG_SESSION("World3D SKY-BSP-D3D object='%s' nodes=%u facing=%u rejected=%u root=%p path=0x1001955E",
                    wm->m_pOriginalBsp->m_szWorldName, visited, facing, rejected, wm->m_pOriginalBsp->m_pRootNode);

    glf.VertexArrayVertexBuffer(WorldRenderer::Instance().State().vao, 0, WorldRenderer::Instance().State().vbo, 0, sizeof(WorldVertexGPU));
    GLUniform1ui(U("uLegacyDrawFlags"), 2u);
    GLUniform1i(U("uWorldModelLightmapGouraud"), 0);
    GLUniform1i(U("uWorldModelGouraud"), 0);
    GLUniform1i(U("uWorldModelBakedOnly"), 0);
    SetSkyIdentityReset();
}

static bool IsSkyPortalFrontFacing(const WorldPolyCompat *poly, const SceneDesc *scene)
{
    if (!poly || !scene || !poly->m_pPlane)
        return true;

    const LTPlaneCompat *plane = reinterpret_cast<const LTPlaneCompat *>(poly->m_pPlane);
    const float side = plane->m_vNormal.x * scene->m_vPos.x +
                       plane->m_vNormal.y * scene->m_vPos.y +
                       plane->m_vNormal.z * scene->m_vPos.z - plane->m_fDist;
    return side >= -0.01f;
}

void SkyRenderer::Render(SceneDesc *scene, MainWorldCompat *world, uint32 &draws, uint64_t &tris)
{
    if (!StockRenderOptions::Instance().DrawSky())
        return;
    if (!scene || !world || !scene->m_pSkyObjects || scene->m_nSkyObjects <= 0 ||
        !SkyRenderer::Instance().State().portalVbo || SkyRenderer::Instance().State().portalVertices.empty() || SkyRenderer::Instance().State().portalSpans.empty())
        return;

    // SURF_SKY polygons whose plane faces the normal world camera.
    uint32 visiblePortalPolys = 0;
    uint32 visiblePortalVerts = 0;
    uint32 backfacePortalPolys = 0;
    for (const SkyPortalSpan &span : SkyRenderer::Instance().State().portalSpans)
    {
        if (!span.poly || !span.vertexCount)
            continue;
        if (!IsSkyPortalFrontFacing(span.poly, scene))
        {
            ++backfacePortalPolys;
            continue;
        }
        ++visiblePortalPolys;
        visiblePortalVerts += span.vertexCount;
    }

    // 1) Keep building the portal stencil for diagnostics/fog seeding only.
    //    Sky surfaces themselves never write color or depth.
    //    surfaces themselves never
    //    write color or depth.
    WorldRenderer::Instance().SetupScene(scene);
    GLStateEnable(GL_STENCIL_TEST);
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);
    GLStateDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    WorldRenderer::Instance().State().worldShader->Use();
    SetSkyIdentityReset();
    GLUniform1i(U("uTextured"), 0);
    GLUniform1i(U("uLinkedTexMode"), 0);
    GLStateBindTextureUnit(4, 0);
    GLUniform1i(U("uUseWorldMaterialParams"), 0);
    GLUniform4f(U("uLinkedParams0"), 1.0f, 1.0f, 1.0f, 1.0f);
    GLUniform4f(U("uLinkedParams1"), 1.0f, 1.0f, 0.0f, 1.0f);
    GLUniform4f(U("uLinkedParams2"), 1.0f, 1.0f, 0.0f, 0.0f);
    GLUniform1i(U("uLightmapped"), 0);
    GLUniform1i(U("uNoLight"), 1);
    GLUniform1i(U("uFogEnabled"), 0);
    GLUniform1ui(U("uTexFxMask"), 0u);
    GLUniform1i(U("uPanSkyEnabled"), 0);
    GLStateBindTextureUnit(3, 0);
    glf.VertexArrayVertexBuffer(WorldRenderer::Instance().State().vao, 0, SkyRenderer::Instance().State().portalVbo, 0, sizeof(WorldVertexGPU));
    WorldSurfaceFxSystem::Instance().BindUvOverride(SkyRenderer::Instance().State().portalVbo);
    GLStateBindVertexArray(WorldRenderer::Instance().State().vao);
    for (const SkyPortalSpan &span : SkyRenderer::Instance().State().portalSpans)
    {
        if (!span.poly || !span.vertexCount || !IsSkyPortalFrontFacing(span.poly, scene))
            continue;
        glf.DrawArrays(GL_TRIANGLES_, static_cast<GLint>(span.firstVertex), static_cast<GLsizei>(span.vertexCount));
    }

    // Stock Talon never exposes the renderer clear colour through a
    // valid sky opening.
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glStencilMask(0x00);
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    GLStateDisable(GL_BLEND);
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);
    GLUniform1i(U("uTextured"), 0);
    GLUniform1i(U("uNoLight"), 1);
    GLUniform1i(U("uFogEnabled"), 0);
    GLUniform1ui(U("uLegacyDrawFlags"), 0u);
    GLUniform1i(U("uSkyHorizonFogGradient"), 1);
    GLUniform4f(U("uObjectColor"), 1.0f, 1.0f, 1.0f, 1.0f);
    for (const SkyPortalSpan &span : SkyRenderer::Instance().State().portalSpans)
    {
        if (!span.poly || !span.vertexCount || !IsSkyPortalFrontFacing(span.poly, scene))
            continue;
        glf.DrawArrays(GL_TRIANGLES_, static_cast<GLint>(span.firstVertex), static_cast<GLsizei>(span.vertexCount));
    }
    GLUniform1i(U("uSkyHorizonFogGradient"), 0);

    // 2) Render the SceneDesc sky object list as the background, WITHOUT our
    //    custom exact-polygon stencil.
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    GLStateDisable(GL_STENCIL_TEST);
    glStencilMask(0xFF);

    if (LogIsSessionEnabled())
    {
        static uint32 noStencilBudget = 32;
        if (LogIsSessionEnabled() && (noStencilBudget > 0))
        {
            --noStencilBudget;
            LOG_SESSION("World3D SKY-BACKGROUND-NOSTENCIL portals=%u frontFacing=%u verts=%u skyObjects=%d path=SKY-FIRST/WORLD-OCCLUDES",
                        static_cast<unsigned>(SkyRenderer::Instance().State().portalSpans.size()), visiblePortalPolys, visiblePortalVerts, scene->m_nSkyObjects);
        }
    }

    // Stock Talon treats m_pSkyObjects as an ordered painter list.  The sky
    // state block explicitly sets D3DRS_ZWRITEENABLE=FALSE and
    // D3DRS_ZENABLE=FALSE before walking the array.  Depth-testing these
    // objects changes authored cloud/nebula layering even when we preserve the
    // array order, because an earlier layer can reject a later one.
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);

    SceneDesc sky = *scene;
    sky.m_vPos = ComputeSkyViewPos(scene, world);

    // Do not invent an enormous sky far plane.  Keep the scene's supplied
    // projection range; sky fog has its own independent near/far values.
    sky.m_fFarZ = scene->m_fFarZ;

    uint32 skyWM = 0, skySprites = 0, skyPoly = 0;

    // d3d.ren 0x100196DF/0x100196FA replaces the normal FOGSTART/FOGEND
    // with SkyFogNearZ/SkyFogFarZ while rendering the sky object list. Keep
    // FogEnable and FogColor unchanged, exactly like the stock renderer.
    const float worldFogNear = g_fogState.nearZ;
    const float worldFogFar = g_fogState.farZ;
    g_fogState.nearZ = g_fogState.skyNearZ;
    g_fogState.farZ = g_fogState.skyFarZ;
    WorldRenderer::Instance().SetupScene(&sky);
    // d3d.ren 0x1002D55A passes 0x3C23D70A (0.01f) to the dedicated
    // sky-view constructor at 0x1000F5E3.  Do not reuse the normal world's
    // 1.0-unit near plane for sky BSP clipping.
    FrameConstants::Instance().Apply(&sky, 0.01f, std::max(0.02f, sky.m_fFarZ));

    static std::unordered_set<uintptr_t> s_skyProjectionLogged;
    const uintptr_t projKey = reinterpret_cast<uintptr_t>(world);
    if (LogIsSessionEnabled() && (s_skyProjectionLogged.size() < 32 && s_skyProjectionLogged.insert(projKey).second))
    {
        LOG_SESSION("World3D SKY-PROJECTION-PROBE viewport=(%d %d %d %d) fov=(%.9f %.9f) tanHalf=(%.9f %.9f) near=0.010000 far=%.6f worldCam=(%.6f %.6f %.6f) skyCam=(%.6f %.6f %.6f) worldExtMin=(%.6f %.6f %.6f) worldExtMax=(%.6f %.6f %.6f) skyViewMin=(%.6f %.6f %.6f) skyViewMax=(%.6f %.6f %.6f) portals=%u visiblePortals=%u visibleVerts=%u",
                    sky.m_rcViewport.m_nLeft, sky.m_rcViewport.m_nTop, sky.m_rcViewport.m_nRight, sky.m_rcViewport.m_nBottom,
                    sky.m_fFovX, sky.m_fFovY, std::tan(std::max(0.01f, sky.m_fFovX * 0.5f)), std::tan(std::max(0.01f, sky.m_fFovY * 0.5f)), sky.m_fFarZ,
                    scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z, sky.m_vPos.x, sky.m_vPos.y, sky.m_vPos.z,
                    world->m_vExtentsMin.x, world->m_vExtentsMin.y, world->m_vExtentsMin.z,
                    world->m_vExtentsMax.x, world->m_vExtentsMax.y, world->m_vExtentsMax.z,
                    scene->m_SkyDef.m_vViewMin.x, scene->m_SkyDef.m_vViewMin.y, scene->m_SkyDef.m_vViewMin.z,
                    scene->m_SkyDef.m_vViewMax.x, scene->m_SkyDef.m_vViewMax.y, scene->m_SkyDef.m_vViewMax.z,
                    static_cast<unsigned>(SkyRenderer::Instance().State().portalSpans.size()), visiblePortalPolys, visiblePortalVerts);
    }

    // Exhaustive portal source dump for one sky setup.  Log the original source
    // polygons/vertices (not just the generated triangle VBO) so D3D portal
    // bounds/projection can be reconstructed offline byte-for-byte.
    static std::unordered_set<uintptr_t> s_skyPortalDumped;
    if (LogIsSessionEnabled() && (s_skyPortalDumped.size() < 32 && s_skyPortalDumped.insert(projKey).second))
    {
        LOG_SESSION("World3D SKY-ALL-SCENE scene=%p renderContext=%p drawMode=%d skyObjects=%d skyArray=%p viewport=(%d %d %d %d) fov=(%.9f %.9f) nearWorld=%.9f far=%.9f rot=(%.9f %.9f %.9f %.9f) fogEnabled=%u fogColor=(%.9f %.9f %.9f) fogWorld=(%.9f %.9f) fogSky=(%.9f %.9f)",
                    scene, scene->m_pRenderContext, scene->m_nDrawMode, scene->m_nSkyObjects, scene->m_pSkyObjects,
                    scene->m_rcViewport.m_nLeft, scene->m_rcViewport.m_nTop, scene->m_rcViewport.m_nRight, scene->m_rcViewport.m_nBottom,
                    scene->m_fFovX, scene->m_fFovY, 1.0f, scene->m_fFarZ,
                    scene->m_rRotation.x, scene->m_rRotation.y, scene->m_rRotation.z, scene->m_rRotation.w,
                    g_fogState.enabled ? 1u : 0u, g_fogState.r, g_fogState.g, g_fogState.b, worldFogNear, worldFogFar, g_fogState.skyNearZ, g_fogState.skyFarZ);
        for (uint32 psi = 0; psi < SkyRenderer::Instance().State().portalSpans.size(); ++psi)
        {
            const SkyPortalSpan &ps = SkyRenderer::Instance().State().portalSpans[psi];
            bool vis = ps.poly && ps.vertexCount != 0;
            LOG_SESSION("World3D SKY-ALL-PORTAL i=%u poly=%p firstVertex=%u vertexCount=%u visible=%u surfFlags=%08X polyIndex=%u verts=%u",
                        psi, ps.poly, ps.firstVertex, ps.vertexCount, vis ? 1u : 0u,
                        (ps.poly && ps.poly->m_pSurface) ? ps.poly->m_pSurface->m_dwFlags : 0u,
                        ps.poly ? unsigned(ps.poly->m_wIndex) : 0u, ps.poly ? unsigned(ps.poly->m_wNumVerts) : 0u);
            if (ps.poly)
            {
                uint32 n = std::min<uint32>(ps.poly->m_wNumVerts, 64u);
                for (uint32 vi = 0; vi < n; ++vi)
                {
                    const SPolyVertexCompat &v = ps.poly->m_Vertices[vi];
                    LTVector P = v.m_pPoints ? v.m_pPoints->m_vVec : LTVector{0, 0, 0};
                    LOG_SESSION("World3D SKY-ALL-PORTAL-VERT i=%u v=%u point=%p P=(%.9f %.9f %.9f) rawUV=(%.9f %.9f)", psi, vi, v.m_pPoints, P.x, P.y, P.z, v.m_fScaledU, v.m_fScaledV);
                }
            }
        }
    }

    // IMPORTANT: SceneDesc::m_pSkyObjects is already the engine-provided sky
    // layer order. Stock d3d.ren (0x10019768..0x10019866) walks this array
    // linearly and renders each supported object immediately. Do not regroup
    // by type and do not globally distance-sort translucent sky brushes: both
    // destroy authored cloud/sky layering.
    for (int i = 0; i < scene->m_nSkyObjects; ++i)
    {
        auto *obj = reinterpret_cast<LTObjectCompat *>(scene->m_pSkyObjects[i]);
        if (!obj || !(obj->m_dwFlags & FLAG_VISIBLE))
            continue;

        static int skyOrderBudget = 96;
        if (LogIsSessionEnabled() && ((skyOrderBudget > 0 && skyOrderBudget--)))
            LOG_SESSION("World3D SKY-ORDER index=%d type=%u flags=%08X flags2=%08X pos=(%.2f %.2f %.2f)",
                        i, unsigned(obj->m_nObjectType), obj->m_dwFlags, obj->m_dwFlags2,
                        obj->m_vPos.x, obj->m_vPos.y, obj->m_vPos.z);

        switch (obj->m_nObjectType)
        {
        case OT_WORLDMODEL:
            DrawOneSkyWorldModel(&sky, world,
                                 reinterpret_cast<WorldModelInstanceCompat *>(obj), draws, tris);
            ++skyWM;
            break;

        case OT_POLYGRID:
            FXRenderer::Instance().RenderPolyGrid(&sky, reinterpret_cast<PolyGridCompat *>(obj));
            WorldRenderer::Instance().State().worldShader->Use();
            ++skyPoly;
            break;

        case OT_SPRITE:
            SpriteRenderer::Instance().Render(&sky, reinterpret_cast<SpriteInstanceCompat *>(obj));
            WorldRenderer::Instance().State().worldShader->Use();
            ++skySprites;
            break;

        default:
            break;
        }

        // Sprite/PolyGrid helpers are normal-scene renderers and may alter Z
        // state internally.  Stock's sky state block keeps Z off across the
        // entire ordered list, so reassert it after each object.
        GLStateDisable(GL_DEPTH_TEST);
        GLStateDepthMask(GL_FALSE);
    }

    // Restore the normal-world fog range before re-entering the ordinary
    // scene. WorldRenderer::Instance().SetupScene(scene) below pushes these values back to the shader.
    g_fogState.nearZ = worldFogNear;
    g_fogState.farZ = worldFogFar;

    GLStateDisable(GL_STENCIL_TEST);
    glStencilMask(0xFF);
    GLStateDepthMask(GL_TRUE);
    glClear(GL_DEPTH_BUFFER_BIT); // sky depth must not occlude the real world
    glf.VertexArrayVertexBuffer(WorldRenderer::Instance().State().vao, 0, WorldRenderer::Instance().State().vbo, 0, sizeof(WorldVertexGPU));
    WorldRenderer::Instance().SetupScene(scene);
    const bool wf = Console::Instance().GetFloat("Wireframe", 0.0f) != 0.0f;
    glPolygonMode(GL_FRONT_AND_BACK, wf ? GL_LINE : GL_FILL);

    static int budget = 64;
    if (LogIsSessionEnabled() && ((budget > 0 && budget--)))
        LOG_SESSION("World3D SKY DRAW visiblePortals=%u/%u backfacePortals=%u visiblePortalVerts=%u/%u skyObjects=%d wm=%u sprites=%u polygrids=%u pvs=%d order=PROVIDED painterZ=OFF skyFog=%d near=%.2f far=%.2f projFar=%.2f skyPos=(%.2f %.2f %.2f)",
                    visiblePortalPolys, static_cast<unsigned>(SkyRenderer::Instance().State().portalSpans.size()), backfacePortalPolys,
                    visiblePortalVerts, static_cast<unsigned>(SkyRenderer::Instance().State().portalVertices.size()), scene->m_nSkyObjects,
                    skyWM, skySprites, skyPoly, WorldPVS::Instance().State().haveStaticPVS ? 1 : 0, g_fogState.enabled ? 1 : 0,
                    g_fogState.skyNearZ, g_fogState.skyFarZ, sky.m_fFarZ, sky.m_vPos.x, sky.m_vPos.y, sky.m_vPos.z);
}
