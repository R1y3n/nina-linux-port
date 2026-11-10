#include "../textures/texture_manager.h"
#include "../renderer/frame_constants.h"
#include "../world/world_renderer.h"
#include "lt_renderer_abi.h"
#include "subsystems/textures/Texture.h"
#include "subsystems/textures/texture_manager.h"
#include "gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "shaders/shader_manager.h"
#include "gl_renderer.h"
#include "utils/log.h"
//#include "utils/math.h"
#include "subsystems/renderer/fog_state.h"
#include "subsystems/sprites/sprite_renderer.h"
#include "subsystems/renderer/stock_render_options.h"
#include "subsystems/renderer/talon_render_state.h"
#include "subsystems/timing/high_refresh_timing.h"

#include "shaders/shader_resources.h"

#include <GL/gl.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

namespace
{

    struct SpriteVertexGPU
    {
        LTVector pos;
        LTFloatPt uv;
        PGColor color;
    };

    static SpriteRendererState &SpriteState()
    {
        return SpriteRenderer::Instance().State();
    }

    static SpriteVertexGPU LerpSpriteVertex(const SpriteVertexGPU &a,
                                            const SpriteVertexGPU &b,
                                            float t)
    {
        SpriteVertexGPU out{};
        out.pos = a.pos + (b.pos - a.pos) * t;
        out.uv = a.uv + (b.uv - a.uv) * t;
        out.color = a.color + (b.color - a.color) * t;
        return out;
    }

    static void ClipSpriteTrianglesToNearPlane(std::vector<SpriteVertexGPU> &verts,
                                               float nearZ,
                                               bool &clippedAny)
    {
        clippedAny = false;
        if (verts.empty() || (verts.size() % 3u) != 0u)
            return;

        std::vector<SpriteVertexGPU> clipped;
        clipped.reserve(verts.size() * 2u);

        for (size_t tri = 0; tri < verts.size(); tri += 3u)
        {
            SpriteVertexGPU input[4] = {verts[tri], verts[tri + 1u], verts[tri + 2u], {}};
            SpriteVertexGPU output[4]{};
            int inputCount = 3;
            int outputCount = 0;

            SpriteVertexGPU prev = input[inputCount - 1];
            bool prevInside = prev.pos.z >= nearZ;

            for (int i = 0; i < inputCount; ++i)
            {
                const SpriteVertexGPU cur = input[i];
                const bool curInside = cur.pos.z >= nearZ;

                if (curInside != prevInside)
                {
                    const float dz = cur.pos.z - prev.pos.z;
                    if (std::fabs(dz) > 1e-8f)
                    {
                        const float t = std::clamp((nearZ - prev.pos.z) / dz, 0.0f, 1.0f);
                        SpriteVertexGPU hit = LerpSpriteVertex(prev, cur, t);
                        hit.pos.z = nearZ;
                        output[outputCount++] = hit;
                        clippedAny = true;
                    }
                }

                if (curInside)
                    output[outputCount++] = cur;
                else
                    clippedAny = true;

                prev = cur;
                prevInside = curInside;
            }

            if (outputCount < 3)
                continue;

            for (int i = 1; i + 1 < outputCount; ++i)
            {
                clipped.push_back(output[0]);
                clipped.push_back(output[i]);
                clipped.push_back(output[i + 1]);
            }
        }

        verts.swap(clipped);
    }

    struct DecalClipVertex
    {
        LTVector world;
        LTFloatPt uv;
    };

    static WorldPolyCompat *ResolveSpriteClipperPoly(const SceneDesc *scene, uint32 hPoly)
    {
        // AVP2/Talon HPOLY is a packed 16:16 handle. d3d.ren's resolver shifts
        // the world index from the high word and passes the complete handle to the
        // selected WorldBsp, whose low word is the polygon index.
        if (!scene || !scene->m_pRenderContext || hPoly == 0xFFFFFFFFu)
            return nullptr;

        MainWorldCompat *world = reinterpret_cast<MainWorldCompat *>(scene->m_pRenderContext->m_pMainWorld);
        if (!world || !world->m_WorldModels.m_pArray)
            return nullptr;

        const uint32 worldIndex = (hPoly >> 16) & 0xFFFFu;
        const uint32 polyIndex = hPoly & 0xFFFFu;
        if (worldIndex >= world->m_WorldModels.m_dwElements)
            return nullptr;

        WorldDataCompat *wd = world->m_WorldModels.m_pArray[worldIndex];
        WorldBspCompat *bsp = wd ? wd->m_pOriginalBsp : nullptr;
        if (!bsp || !bsp->m_pPolies || polyIndex >= bsp->m_dwPolies)
            return nullptr;

        return bsp->m_pPolies[polyIndex];
    }

    static bool ClipRotatableSpriteToPoly(const SceneDesc *scene, uint32 hPoly,
                                          std::vector<DecalClipVertex> &verts)
    {
        if (hPoly == 0xFFFFFFFFu)
            return true;

        WorldPolyCompat *poly = ResolveSpriteClipperPoly(scene, hPoly);
        if (!poly || !poly->m_pPlane || poly->m_wNumVerts < 3 || poly->m_wNumVerts > 40)
            return false;

        const LTPlaneCompat *srcPlane = reinterpret_cast<const LTPlaneCompat *>(poly->m_pPlane);
        const LTVector polyNormal{srcPlane->m_vNormal.x, srcPlane->m_vNormal.y, srcPlane->m_vNormal.z};

        // Stock d3d_ClipSprite first rejects a clipped sprite when the camera is
        // not on the front side of its host polygon.
        const LTVector camera{scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z};
        if (polyNormal.dot(camera) - srcPlane->m_fDist <= 0.01f)
            return false;

        const SPolyVertexCompat *pv = poly->m_Vertices;
        std::vector<DecalClipVertex> input;
        std::vector<DecalClipVertex> output;
        input.reserve(48);
        output.reserve(48);

        for (uint32 i = 0; i < poly->m_wNumVerts && !verts.empty(); ++i)
        {
            const uint32 prevIndex = (i + poly->m_wNumVerts - 1) % poly->m_wNumVerts;
            if (!pv[i].m_pPoints || !pv[prevIndex].m_pPoints)
                return false;

            const LTVector &curP = pv[i].m_pPoints->m_vVec;
            const LTVector &prevP = pv[prevIndex].m_pPoints->m_vVec;
            const LTVector cur{curP.x, curP.y, curP.z};
            const LTVector prev{prevP.x, prevP.y, prevP.z};
            const LTVector edge = cur - prev;
            // Stock d3d.ren / d3d11_avp2 use cross(polyNormal, edge).
            // Reversing these operands flips every clip half-space and can clip
            // the entire impact sprite away even when it lies inside its host poly.
            LTVector edgeNormal = (polyNormal.cross(edge)).normalize();
            if (edgeNormal.length() <= 1e-8f)
                continue;
            const float edgeDist = edgeNormal.dot(cur);

            input.swap(verts);
            output.clear();
            if (input.empty())
                break;

            DecalClipVertex a = input.back();
            float da = edgeNormal.dot(a.world) - edgeDist;
            bool aInside = da > 0.0f;

            for (const DecalClipVertex &b : input)
            {
                const float db = edgeNormal.dot(b.world) - edgeDist;
                const bool bInside = db > 0.0f;

                if (aInside != bInside)
                {
                    const float denom = da - db;
                    if (std::fabs(denom) > 1e-8f)
                    {
                        const float t = da / denom;
                        DecalClipVertex x;
                        x.world = a.world + (b.world - a.world) * t;
                        x.uv.x = a.uv.x + (b.uv.x - a.uv.x) * t;
                        x.uv.y = a.uv.y + (b.uv.y - a.uv.y) * t;
                        output.push_back(x);
                    }
                }
                if (bInside)
                    output.push_back(b);

                a = b;
                da = db;
                aInside = bInside;
            }

            verts.swap(output);
            if (verts.size() > 48)
                return false;
        }

        return verts.size() >= 3;
    }

    static void ApplySpritePositionBias(LTVector &cameraPos)
    {
        if (cameraPos.z <= 0.001f)
            return;

        float bias = -20.0f;
        constexpr float nearZ = 1.0f;
        if (cameraPos.z + bias < nearZ)
            bias = nearZ - cameraPos.z + 0.001f;

        const float scale = 1.0f + bias / cameraPos.z;
        cameraPos.x *= scale;
        cameraPos.y *= scale;
        cameraPos.z += bias;
    }

    static void ApplyTalonSpriteTextureRotation(const LTObjectCompat &o,
                                                std::vector<SpriteVertexGPU> &vertices)
    {
        // d3d.ren 0x1002DDE5..0x1002DEFD: secondary sprite flag 0x200
        // rotates each generated (u,v) around the texture-center using the upper
        // left 2x2 of the matrix built from LTObject::m_rRot, then temporarily
        // switches the stage address mode to CLAMP for the draw.  The game uses
        // this on the Alien Vision overlay; ignoring it leaves both overlay layers
        // perfectly aligned and visually static.
        if ((o.m_dwFlags2 & FLAG2_SPRITE_TROTATE) == 0 || vertices.empty())
            return;

        LTRotation q{
            o.m_rRot.x,
            o.m_rRot.y,
            o.m_rRot.z,
            o.m_rRot.w};
        q = q.Normalize();

        const LTVector basisU = q.Rotate({1.0f, 0.0f, 0.0f});
        const LTVector basisV = q.Rotate({0.0f, 1.0f, 0.0f});

        float minU = vertices[0].uv.x, maxU = vertices[0].uv.x;
        float minV = vertices[0].uv.y, maxV = vertices[0].uv.y;
        for (const auto &v : vertices)
        {
            minU = std::min(minU, v.uv.x);
            maxU = std::max(maxU, v.uv.x);
            minV = std::min(minV, v.uv.y);
            maxV = std::max(maxV, v.uv.y);
        }
        const float centerU = (minU + maxU) * 0.5f;
        const float centerV = (minV + maxV) * 0.5f;

        for (auto &vertex : vertices)
        {
            const float du = vertex.uv.x - centerU;
            const float dv = vertex.uv.y - centerV;
            vertex.uv.x = centerU + du * basisU.x + dv * basisV.x;
            vertex.uv.y = centerV + du * basisU.y + dv * basisV.y;
        }
    }

    static LTVector WorldToCamera(const SceneDesc *scene, LTVector world)
    {
        LTVector rel = world - LTVector{scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z};

        LTRotation cam{
            scene->m_rRotation.x,
            scene->m_rRotation.y,
            scene->m_rRotation.z,
            scene->m_rRotation.w};

        return cam.Normalize().Conjugate().Rotate(rel);
    }

    static void SetupProjection(const SceneDesc *scene, bool reallyClose)
    {
        // RCSpriteFOVOffset defaults to 0 in the reference renderer, so the
        // ReallyClose sprite projection keeps the scene FOV and only changes
        // the near/far depth range.
        const float tanHalfX = std::tan(std::max(0.01f, scene->m_fFovX * 0.5f));
        const float tanHalfY = std::tan(std::max(0.01f, scene->m_fFovY * 0.5f));
        const float nearZ = reallyClose ? 0.01f : 1.0f;

        // Talon's d3d_CalcReallyCloseMatrix uses ReallyCloseNearZ for the near
        // plane but keeps g_ViewParams.m_fFarZ. Do not clamp RC sprites to an
        // arbitrary short far plane: AVP2's menu places RC sprites at z=224,
        // z=240 and even z=1280.
        const float farZ = std::max(nearZ + 1.0f, scene->m_fFarZ);

        FrameConstants::Instance().Apply(scene, tanHalfX, tanHalfY, nearZ, farZ);
    }
}

bool SpriteRenderer::Init()
{
    auto *shader = avp2::render::ShaderManager::Instance().CreateGraphicsFromResources("sprite.main",
                                                                                       avp2::render::ShaderResourceId::SpriteVertex,
                                                                                       avp2::render::ShaderResourceId::SpriteFragment);
    if (!shader)
        return false;
    SpriteState().shader = shader;

    SpriteState().uTanHalfFovX = shader->Uniform("uTanHalfFovX");
    SpriteState().uTanHalfFovY = shader->Uniform("uTanHalfFovY");
    SpriteState().uNearZ = shader->Uniform("uNearZ");
    SpriteState().uFarZ = shader->Uniform("uFarZ");
    SpriteState().uUseColorKey = shader->Uniform("uUseColorKey");
    SpriteState().uColorKey = shader->Uniform("uColorKey");
    SpriteState().uAlphaTest = shader->Uniform("uAlphaTest");
    SpriteState().uAlphaRef = shader->Uniform("uAlphaRef");
    SpriteState().uAlphaFunc = shader->Uniform("uAlphaFunc");
    SpriteState().uMode = shader->Uniform("uMode");
    SpriteState().uModeColor = shader->Uniform("uModeColor");
    SpriteState().uFogEnabled = shader->Uniform("uFogEnabled");
    SpriteState().uFogColor = shader->Uniform("uFogColor");
    SpriteState().uFogNear = shader->Uniform("uFogNear");
    SpriteState().uFogFar = shader->Uniform("uFogFar");

    glf.CreateVertexArrays(1, &SpriteState().vao);
    glf.CreateBuffers(1, &SpriteState().vbo);
    glf.NamedBufferStorage(SpriteState().vbo, sizeof(SpriteVertexGPU) * 512, nullptr, GL_DYNAMIC_STORAGE_BIT_);

    glf.VertexArrayVertexBuffer(SpriteState().vao, 0, SpriteState().vbo, 0, sizeof(SpriteVertexGPU));

    glf.EnableVertexArrayAttrib(SpriteState().vao, 0);
    glf.VertexArrayAttribFormat(SpriteState().vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(SpriteVertexGPU, pos.x));
    glf.VertexArrayAttribBinding(SpriteState().vao, 0, 0);

    glf.EnableVertexArrayAttrib(SpriteState().vao, 1);
    glf.VertexArrayAttribFormat(SpriteState().vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(SpriteVertexGPU, uv.x));
    glf.VertexArrayAttribBinding(SpriteState().vao, 1, 0);

    glf.EnableVertexArrayAttrib(SpriteState().vao, 2);
    glf.VertexArrayAttribFormat(SpriteState().vao, 2, 4, GL_FLOAT, GL_FALSE, offsetof(SpriteVertexGPU, color.x));
    glf.VertexArrayAttribBinding(SpriteState().vao, 2, 0);

    LOG_SESSION("SpriteRenderer::Init: Talon billboard + rotatable decal/clipper + bias + linear fog ready");
    return true;
}

void SpriteRenderer::Term()
{
    if (SpriteState().vbo)
        glf.DeleteBuffers(1, &SpriteState().vbo);
    if (SpriteState().vao)
        GLStateDeleteVertexArrays(1, &SpriteState().vao);
    if (SpriteState().shader)
        avp2::render::ShaderManager::Instance().Release("sprite.main");

    SpriteState().vbo = 0;
    SpriteState().vao = 0;
    SpriteState().shader = nullptr;
}

enum SpriteModeBits : uint32
{
    SPRMODE_REALLY_CLOSE = (1u << 0),
    SPRMODE_FOG_ENABLED = (1u << 1),
    SPRMODE_NO_TEXTURE = (1u << 2),
    SPRMODE_BLEND_MULTIPLY = (1u << 5),
    SPRMODE_ADD_SIGNED = (1u << 6),
    SPRMODE_NO_LIGHT = (1u << 7),
    SPRMODE_FLAT_COLOR = (1u << 8),
    SPRMODE_CHROMAKEY = (1u << 9),
    SPRMODE_FULL_BRITE = (1u << 11),
    SPRMODE_MODULATE2X = (1u << 16),
    SPRMODE_BLEND_ADDITIVE = (1u << 17)
};

enum class SpriteBlendMode
{
    Alpha,
    Add,
    Multiply,
    Invert
};

struct SpriteRenderMode
{
    uint32 mode = 0;
    SpriteBlendMode blend = SpriteBlendMode::Alpha;
    float modeColor[3] = {0.0f, 0.0f, 0.0f};
    const char *stateName = "none";
    bool stateBlendOverride = false;
    bool stateBlendEnable = true;
    uint32 stateSrcBlend = 5;
    uint32 stateDestBlend = 6;
    bool stateZWriteOverride = false;
    bool stateZWrite = false;
    bool stateZEnableOverride = false;
    bool stateZEnable = true;
    bool stateZFuncOverride = false;
    uint32 stateZFunc = 4;
    bool alphaTest = false;
    float alphaRef = 0.0f;
    uint32 alphaFunc = 7;
};

static bool RSMatch(const StateChangeCompat *sc,
                    std::initializer_list<std::pair<uint32, uint32>> values)
{
    if (!sc || sc->m_RenderList.size() != values.size())
        return false;

    uint32 i = 0;
    for (auto v : values)
    {
        const RenderStateCompat &rs = sc->m_RenderList.m_pFirst[i++];
        if (rs.m_dwRenderStateType != v.first)
            return false;

        // Render-state 34 is FOGCOLOR and is treated as a wildcard by the
        // D3D11 renderer's StateChange hash/equality.
        if (v.first != 34 && rs.m_dwRenderState != v.second)
            return false;
    }
    return true;
}

static bool TSMatch(const StateChangeCompat *sc,
                    std::initializer_list<std::tuple<uint32, uint32, uint32>> values)
{
    if (!sc || sc->m_TextureList.size() != values.size())
        return false;

    uint32 i = 0;
    for (auto v : values)
    {
        const TextureStateCompat &ts = sc->m_TextureList.m_pFirst[i++];
        if (ts.m_dwStage != std::get<0>(v) ||
            ts.m_dwTextureStateType != std::get<1>(v) ||
            ts.m_dwTextureState != std::get<2>(v))
            return false;
    }
    return true;
}

static void ApplyTextureStateChange(SharedTexture *texture, SpriteRenderMode &out)
{
    if (!texture)
        return;

    auto *st = reinterpret_cast<SharedTextureCompat *>(texture);
    if (!st->m_pStateChange)
        return;

    auto *sc = reinterpret_cast<StateChangeCompat *>(st->m_pStateChange);

    const uint32 rsCount = sc->m_RenderList.size();
    const uint32 tsCount = sc->m_TextureList.size();

    // Sanity guard: Talon state-change vectors are tiny. Do not walk a bogus
    // pointer if our compatibility layout is ever wrong.
    if (rsCount > 32 || tsCount > 32)
    {
        static int badBudget = 8;
        if (LogIsSessionEnabled() && ((badBudget > 0 && badBudget--)))
            LOG_SESSION("Sprite3D StateChange invalid counts ptr=%p rs=%u ts=%u",
                        sc, rsCount, tsCount);
        return;
    }

    // Decode the actual D3D8 state vector, not only the handful of
    // named AVP2 RenderMode patterns. This preserves arbitrary SRC/DEST blend,
    // alpha-test/ref, fog and Z-write overrides authored through StateChange.
    const TalonRenderState d3d = TalonRenderStateSystem::Instance().Decode(sc);
    if (d3d.hasAlphaBlendEnable)
    {
        out.stateBlendOverride = true;
        out.stateBlendEnable = d3d.alphaBlendEnable;
        if (d3d.hasSrcBlend)
            out.stateSrcBlend = d3d.srcBlend;
        if (d3d.hasDestBlend)
            out.stateDestBlend = d3d.destBlend;
    }
    if (d3d.hasZEnable)
    {
        out.stateZEnableOverride = true;
        out.stateZEnable = d3d.zEnable;
    }
    if (d3d.hasZWriteEnable)
    {
        out.stateZWriteOverride = true;
        out.stateZWrite = d3d.zWriteEnable;
    }
    if (d3d.hasZFunc)
    {
        out.stateZFuncOverride = true;
        out.stateZFunc = d3d.zFunc;
    }
    if (d3d.hasFogEnable)
    {
        if (d3d.fogEnable)
            out.mode |= SPRMODE_FOG_ENABLED;
        else
            out.mode &= ~SPRMODE_FOG_ENABLED;
    }
    if (d3d.hasAlphaTestEnable)
        out.alphaTest = d3d.alphaTestEnable;
    if (out.alphaTest)
    {
        out.alphaRef = TalonRenderStateSystem::Instance().AlphaRef01(d3d, 0.5f + 0.5f / 255.0f);
        out.alphaFunc = d3d.hasAlphaFunc ? d3d.alphaFunc : 7u;
    }

    // Decode stage-0 COLOROP by state id even when the StateChange contains
    // additional render states or a different vector ordering.
    if (d3d.hasStage0ColorOp)
    {
        if (d3d.stage0ColorOp == 8u)
            out.mode |= SPRMODE_ADD_SIGNED; // ADDSIGNED
        else if (d3d.stage0ColorOp == 5u)
            out.mode |= SPRMODE_MODULATE2X; // MODULATE2X
        else if (d3d.stage0ColorOp == 2u)
            out.mode |= SPRMODE_NO_LIGHT; // SELECTARG1
    }

    // Mirrors CRenderModeMgr::Init() in the D3D11 AVP2 renderer.

    // AddSigned: TextureStageState[0] COLOROP = ADDSIGNED (8)
    if (RSMatch(sc, {}) && TSMatch(sc, {{0, 1, 8}}))
    {
        out.mode |= SPRMODE_ADD_SIGNED;
        out.stateName = "AddSigned";
    }
    // Modulate2X: COLOROP = MODULATE2X (5)
    else if (RSMatch(sc, {}) && TSMatch(sc, {{0, 1, 5}}))
    {
        out.mode |= SPRMODE_MODULATE2X;
        out.stateName = "Modulate2X";
    }
    // NoLighting: COLOROP = SELECTARG1 (2)
    else if (RSMatch(sc, {}) && TSMatch(sc, {{0, 1, 2}}))
    {
        out.mode |= SPRMODE_NO_LIGHT;
        out.stateName = "NoLighting";
    }
    // NoFullbright: SRCBLEND DESTCOLOR, DESTBLEND SRCCOLOR
    else if (RSMatch(sc, {{19, 9}, {20, 3}}) && TSMatch(sc, {}))
    {
        out.mode &= ~SPRMODE_FULL_BRITE;
        out.stateName = "NoFullbright";
    }
    // NavAliens: INVSRCCOLOR / INVSRCCOLOR, alpha blend on, fog off,
    // SELECTARG1. The D3D11 renderer maps this to BLEND_STATE_Invert.
    else if (RSMatch(sc, {{19, 4}, {20, 4}, {27, 1}, {28, 0}}) &&
             TSMatch(sc, {{0, 1, 2}}))
    {
        out.mode |= SPRMODE_NO_LIGHT;
        out.mode &= ~SPRMODE_FOG_ENABLED;
        out.blend = SpriteBlendMode::Invert;
        out.stateName = "NavAliens";
    }
    // NoFog + SELECTARG1
    else if (RSMatch(sc, {{28, 0}}) && TSMatch(sc, {{0, 1, 2}}))
    {
        out.mode |= SPRMODE_NO_LIGHT;
        out.mode &= ~SPRMODE_FOG_ENABLED;
        out.stateName = "NoFog";
    }
    // FogColored. State 34 is the packed fog color.
    else if (RSMatch(sc, {{28, 1}, {34, 0}, {35, 3}, {36, 0}, {37, 0}}) &&
             TSMatch(sc, {{0, 1, 2}}))
    {
        out.mode |= (SPRMODE_NO_LIGHT | SPRMODE_FLAT_COLOR);
        out.mode &= ~SPRMODE_FOG_ENABLED;

        const uint32 color = sc->m_RenderList.m_pFirst[1].m_dwRenderState;
        out.modeColor[0] = ((color >> 16) & 0xFF) / 255.0f;
        out.modeColor[1] = ((color >> 8) & 0xFF) / 255.0f;
        out.modeColor[2] = (color & 0xFF) / 255.0f;
        out.stateName = "FogColored";
    }
    else
    {
        out.stateName = "UNKNOWN";

        static int unknownBudget = 24;
        if (LogIsSessionEnabled() && ((unknownBudget > 0 && unknownBudget--)))
        {
            LOG_SESSION("Sprite3D UNKNOWN StateChange ptr=%p rs=%u ts=%u", sc, rsCount, tsCount);

            for (uint32 i = 0; i < rsCount; ++i)
            {
                const auto &rs = sc->m_RenderList.m_pFirst[i];
                LOG_SESSION("  RS[%u] type=%u value=%u (0x%08X)",
                            i, rs.m_dwRenderStateType, rs.m_dwRenderState, rs.m_dwRenderState);
            }

            for (uint32 i = 0; i < tsCount; ++i)
            {
                const auto &ts = sc->m_TextureList.m_pFirst[i];
                LOG_SESSION("  TS[%u] stage=%u type=%u value=%u (0x%08X)",
                            i, ts.m_dwStage, ts.m_dwTextureStateType,
                            ts.m_dwTextureState, ts.m_dwTextureState);
            }
        }
    }

    static int knownBudget = 24;
    if (LogIsSessionEnabled() && ((knownBudget > 0 && knownBudget--)))
    {
        LOG_SESSION("Sprite3D StateChange=%s ptr=%p mode=%08X blend=%d",
                    out.stateName, sc, out.mode, static_cast<int>(out.blend));
    }
}

static SpriteRenderMode BuildSpriteRenderMode(SpriteInstanceCompat *sprite,
                                              SharedTexture *texture,
                                              bool reallyClose)
{
    SpriteRenderMode result{};

    if (reallyClose)
        result.mode |= SPRMODE_REALLY_CLOSE;

    const LTObjectCompat &o = sprite->m_Base;

    if (g_fogState.enabled && !reallyClose && !(o.m_dwFlags & FLAG_FOGDISABLE))
        result.mode |= SPRMODE_FOG_ENABLED;

    if (o.m_dwFlags2 & FLAG2_ADDITIVE)
    {
        result.blend = SpriteBlendMode::Add;
        result.mode |= SPRMODE_BLEND_ADDITIVE;
    }
    else if (o.m_dwFlags2 & FLAG2_MULTIPLY)
    {
        result.blend = SpriteBlendMode::Multiply;
        result.mode |= SPRMODE_BLEND_MULTIPLY;
    }
    else
    {
        result.blend = SpriteBlendMode::Alpha;
    }

    ApplyTextureStateChange(texture, result);
    return result;
}

static void ApplySpriteBlend(const SpriteRenderMode &mode)
{
    if (mode.stateBlendOverride)
    {
        if (!mode.stateBlendEnable)
        {
            GLStateDisable(GL_BLEND);
            return;
        }
        GLStateEnable(GL_BLEND);
        GLStateBlendFunc(
            static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(mode.stateSrcBlend)),
            static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(mode.stateDestBlend)));
        return;
    }

    GLStateEnable(GL_BLEND);

    switch (mode.blend)
    {
    case SpriteBlendMode::Add:
        GLStateBlendFunc(GL_ONE, GL_ONE);
        break;

    case SpriteBlendMode::Multiply:
        GLStateBlendFunc(GL_DST_COLOR, GL_ZERO);
        break;

    case SpriteBlendMode::Invert:
        // D3D11 BLEND_STATE_Invert corresponds to
        // INVSRCCOLOR / INVSRCCOLOR.
        GLStateBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
        break;

    case SpriteBlendMode::Alpha:
    default:
        GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        break;
    }
}

static void ApplySpriteColorKey(SpriteInstanceCompat *sprite)
{
    bool keyed = (sprite->m_Base.m_dwFlags2 & FLAG2_CHROMAKEY) != 0;
    uint32 key = 0;

    if (sprite->m_SpriteTracker.m_pCurAnim)
    {
        SpriteAnimCompat *anim = sprite->m_SpriteTracker.m_pCurAnim;
        if (anim->m_bKeyed)
        {
            keyed = true;
            key = anim->m_dwColourKey;
        }
    }

    GLUniform1i(SpriteState().uUseColorKey, keyed ? 1 : 0);

    const float r = ((key >> 16) & 0xFF) / 255.0f;
    const float g = ((key >> 8) & 0xFF) / 255.0f;
    const float b = (key & 0xFF) / 255.0f;
    GLUniform3f(SpriteState().uColorKey, r, g, b);
}

bool SpriteRenderer::Render(SceneDesc *scene, SpriteInstanceCompat *sprite)
{
    if (!StockRenderOptions::Instance().DrawSprites())
        return true;
    if (!scene || !sprite)
        return false;

    SpriteEntryCompat *frame = sprite->m_SpriteTracker.m_pCurFrame;
    if (!frame || !frame->m_pTexture)
    {
        static int noFrameBudget = 16;
        if (LogIsSessionEnabled() && ((noFrameBudget > 0 && noFrameBudget--)))
            LOG_SESSION("Sprite3D DROP no current frame/texture sprite=%p frame=%p",
                        sprite, frame);
        return false;
    }

    SharedTexture *sharedTexture = frame->m_pTexture;
    Texture *tex = TextureManager::Instance().Ensure(sharedTexture, false);
    if (!tex || !tex->texture || tex->width == 0 || tex->height == 0)
    {
        static int noTexBudget = 16;
        if (LogIsSessionEnabled() && ((noTexBudget > 0 && noTexBudget--)))
            LOG_SESSION("Sprite3D DROP texture upload failed sprite=%p shared=%p",
                        sprite, sharedTexture);
        return false;
    }

    LTObjectCompat presentationBase = sprite->m_Base;
    if (scene->m_nDrawMode == DRAWMODE_NORMAL)
    {
        const float inPos[3] = {sprite->m_Base.m_vPos.x, sprite->m_Base.m_vPos.y, sprite->m_Base.m_vPos.z};
        const float inQuat[4] = {sprite->m_Base.m_rRot.x, sprite->m_Base.m_rRot.y, sprite->m_Base.m_rRot.z, sprite->m_Base.m_rRot.w};
        float outPos[3], outQuat[4];
        if (HighRefreshTimingFix::InterpolateObjectTransform(&sprite->m_Base, sprite->m_Base.m_wObjectID, sprite->m_Base.m_nObjectType, inPos, inQuat, outPos, outQuat))
        {
            presentationBase.m_vPos = {outPos[0], outPos[1], outPos[2]};
            presentationBase.m_rRot.x = outQuat[0];
            presentationBase.m_rRot.y = outQuat[1];
            presentationBase.m_rRot.z = outQuat[2];
            presentationBase.m_rRot.w = outQuat[3];
        }
    }
    const LTObjectCompat &o = presentationBase;
    const bool reallyClose = (o.m_dwFlags & FLAG_REALLYCLOSE) != 0;
    SpriteRenderMode renderMode = BuildSpriteRenderMode(sprite, sharedTexture, reallyClose);

    // Log every distinct SharedTexture the first time it is actually used by
    // a sprite. Unlike the older fixed diagnostic budget, this remains useful
    // for late menu events such as the dropship fly-in.
    static std::unordered_set<SharedTexture *> s_loggedSpriteTextures;
    if (LogIsSessionEnabled() && (s_loggedSpriteTextures.insert(sharedTexture).second))
    {
        const SpriteAnimCompat *anim = sprite->m_SpriteTracker.m_pCurAnim;
        LOG_SESSION("Sprite3D NEWTEX sprite=%p shared=%p GL=%u size=%ux%u flags=%08X flags2=%08X RC=%d pos=(%.3f,%.3f,%.3f) scale=(%.4f,%.4f,%.4f) blend=%s state=%s mode=%08X animKeyed=%d key=%08X translucent=%d objRGBA=(%u,%u,%u,%u)",
                    sprite,
                    sharedTexture,
                    tex->texture,
                    tex->width,
                    tex->height,
                    o.m_dwFlags,
                    o.m_dwFlags2,
                    reallyClose ? 1 : 0,
                    o.m_vPos.x, o.m_vPos.y, o.m_vPos.z,
                    o.m_vScale.x, o.m_vScale.y, o.m_vScale.z,
                    (renderMode.blend == SpriteBlendMode::Add) ? "ADD" : (renderMode.blend == SpriteBlendMode::Multiply) ? "MULTIPLY"
                                                                     : (renderMode.blend == SpriteBlendMode::Invert)     ? "INVERT"
                                                                                                                         : "ALPHA",
                    renderMode.stateName,
                    renderMode.mode,
                    anim ? (anim->m_bKeyed ? 1 : 0) : 0,
                    anim ? anim->m_dwColourKey : 0,
                    anim ? (anim->m_bTranslucent ? 1 : 0) : 0,
                    static_cast<unsigned>(o.m_nColorR),
                    static_cast<unsigned>(o.m_nColorG),
                    static_cast<unsigned>(o.m_nColorB),
                    static_cast<unsigned>(o.m_nColorA));
    }

    static int specialSpriteBudget = 12;
    if (LogIsSessionEnabled() && (specialSpriteBudget > 0 &&
        (o.m_dwFlags2 & (FLAG2_ADDITIVE | FLAG2_MULTIPLY))))
    {
        LOG_SESSION("Sprite3D SPECIAL sprite=%p blend=%s tex=%ux%u GL=%u flags2=%08X alpha=%u",
                    sprite,
                    (o.m_dwFlags2 & FLAG2_ADDITIVE) ? "ADD" : "MULTIPLY",
                    tex->width, tex->height, tex->texture,
                    o.m_dwFlags2, static_cast<unsigned>(o.m_nColorA));
        --specialSpriteBudget;
    }

    static int spriteFlagLogBudget = 20;
    if (LogIsSessionEnabled() && (spriteFlagLogBudget > 0))
    {
        const SpriteAnimCompat *anim = sprite->m_SpriteTracker.m_pCurAnim;
        LOG_SESSION("Sprite3D flags sprite=%p flags=%08X flags2=%08X RC=%d state=%s mode=%08X pos=(%.3f,%.3f,%.3f) tex=%ux%u scale=(%.4f,%.4f,%.4f) far=%.1f animKeyed=%d key=%08X translucent=%d",
                    sprite,
                    o.m_dwFlags,
                    o.m_dwFlags2,
                    reallyClose ? 1 : 0,
                    renderMode.stateName,
                    renderMode.mode,
                    o.m_vPos.x, o.m_vPos.y, o.m_vPos.z,
                    tex->width,
                    tex->height,
                    o.m_vScale.x,
                    o.m_vScale.y,
                    o.m_vScale.z,
                    scene->m_fFarZ,
                    anim ? (anim->m_bKeyed ? 1 : 0) : 0,
                    anim ? anim->m_dwColourKey : 0,
                    anim ? (anim->m_bTranslucent ? 1 : 0) : 0);
        --spriteFlagLogBudget;
    }

    const bool rotatable = (o.m_dwFlags & FLAG_ROTATEABLESPRITE) != 0;

    if (rotatable && (o.m_dwFlags & FLAG_NOLIGHT))
    {
        static uint32 markRenderBudget = 128;
        if (LogIsSessionEnabled() && (markRenderBudget))
        {
            --markRenderBudget;
            LOG_SESSION("Sprite3D MARK-ENTER sprite=%p flags=%08X flags2=%08X hpoly=%08X frame=%p shared=%p tex=%u pos=(%.2f %.2f %.2f) scale=(%.4f %.4f %.4f)",
                        sprite, o.m_dwFlags, o.m_dwFlags2, sprite->m_hClipperPoly, frame, sharedTexture, tex->texture,
                        o.m_vPos.x, o.m_vPos.y, o.m_vPos.z, o.m_vScale.x, o.m_vScale.y, o.m_vScale.z);
        }
    }

    LTRotation cam{
        scene->m_rRotation.x,
        scene->m_rRotation.y,
        scene->m_rRotation.z,
        scene->m_rRotation.w};
    cam = cam.Normalize();

    const float width = static_cast<float>(tex->width);
    const float height = static_cast<float>(tex->height);

    float cr = o.m_nColorR / 255.0f;
    float cg = o.m_nColorG / 255.0f;
    float cb = o.m_nColorB / 255.0f;
    const float ca = o.m_nColorA / 255.0f;

    // AVP2 uses all-zero RGB on some additive attachment sprites (the
    // dropship flares are one concrete case). Since the additive blend is
    // ONE/ONE, use the texture RGB directly when the object tint is exactly
    // black; otherwise we'd destroy the flare color before blending.
    if ((o.m_dwFlags2 & FLAG2_ADDITIVE) &&
        o.m_nColorR == 0 && o.m_nColorG == 0 && o.m_nColorB == 0)
    {
        cr = cg = cb = 1.0f;
    }

    std::vector<SpriteVertexGPU> gpuVerts;
    gpuVerts.reserve(256);

    if (rotatable)
    {
        // Talon's mark/decal path: the sprite is a real oriented quad using
        // the object's rotation rather than a camera-facing billboard.
        LTRotation q{
            o.m_rRot.x,
            o.m_rRot.y,
            o.m_rRot.z,
            o.m_rRot.w};
        q = q.Normalize();

        const LTVector center{o.m_vPos.x, o.m_vPos.y, o.m_vPos.z};
        const LTVector right = q.Rotate({1, 0, 0}) * (width * o.m_vScale.x);
        const LTVector up = q.Rotate({0, 1, 0}) * (height * o.m_vScale.y);

        // Talon uses the same two-texel UV inset for rotatable sprites as
        // for billboards.
        const float du = 1.0f / width, dv = 1.0f / height;
        const float minU = du * 2.0f, minV = dv * 2.0f;
        const float maxU = (width - 2.0f) * du, maxV = (height - 2.0f) * dv;

        std::vector<DecalClipVertex> polyVerts;
        polyVerts.reserve(48);
        polyVerts.push_back({center + up - right, LTFloatPt(minU, minV)});
        polyVerts.push_back({center + up + right, LTFloatPt(maxU, minV)});
        polyVerts.push_back({center - up + right, LTFloatPt(maxU, maxV)});
        polyVerts.push_back({center - up - right, LTFloatPt(minU, maxV)});

        const bool hasClipper = sprite->m_hClipperPoly != 0xFFFFFFFFu;
        if (hasClipper && !ClipRotatableSpriteToPoly(scene, sprite->m_hClipperPoly, polyVerts))
        {
            static int clipDropBudget = 24;
            if (LogIsSessionEnabled() && (clipDropBudget > 0))
            {
                LOG_SESSION("Sprite3D DECAL-CLIP DROP sprite=%p hpoly=%08X flags=%08X pos=(%.2f %.2f %.2f)",
                            sprite, sprite->m_hClipperPoly, o.m_dwFlags, o.m_vPos.x, o.m_vPos.y, o.m_vPos.z);
                --clipDropBudget;
            }
            return false;
        }

        std::vector<LTVector> camVerts;
        camVerts.reserve(polyVerts.size());
        for (const DecalClipVertex &v : polyVerts)
        {
            LTVector p = WorldToCamera(scene, v.world);
            if (!reallyClose && (o.m_dwFlags & FLAG_SPRITEBIAS))
                ApplySpritePositionBias(p);
            camVerts.push_back(p);
        }

        // Triangulate the clipped convex polygon as a fan.  Clip-generated
        // vertices already carry interpolated UVs.
        for (size_t i = 1; i + 1 < polyVerts.size(); ++i)
        {
            const size_t ids[3] = {0, i, i + 1};
            for (size_t id : ids)
            {
                const DecalClipVertex &decal = polyVerts[id];
                const LTVector &point = camVerts[id];
                float lr = 1.0f, lg = 1.0f, lb = 1.0f;
                if (hasClipper && scene->m_pRenderContext)
                {
                    MainWorldCompat *world = reinterpret_cast<MainWorldCompat *>(scene->m_pRenderContext->m_pMainWorld);
                    LTVector light{};
                    LTVector wp{decal.world.x, decal.world.y, decal.world.z};
                    if (WorldRenderer::Instance().Lighting().SampleDecalLighting(world, sprite->m_hClipperPoly, wp, light))
                    {
                        lr = std::clamp(light.x, 0.0f, 1.0f);
                        lg = std::clamp(light.y, 0.0f, 1.0f);
                        lb = std::clamp(light.z, 0.0f, 1.0f);
                    }
                }
                gpuVerts.push_back({point,
                                    decal.uv,
                                    PGColor(cr * lr, cg * lg, cb * lb, ca)});
            }
        }

        static int decalLightLogBudget = 32;
        if (LogIsSessionEnabled() && (hasClipper && decalLightLogBudget > 0 && scene->m_pRenderContext))
        {
            MainWorldCompat *world = reinterpret_cast<MainWorldCompat *>(scene->m_pRenderContext->m_pMainWorld);
            LTVector light{};
            LTVector wp{o.m_vPos.x, o.m_vPos.y, o.m_vPos.z};
            if (WorldRenderer::Instance().Lighting().SampleDecalLighting(world, sprite->m_hClipperPoly, wp, light))
            {
                LOG_SESSION("Sprite3D DECAL-LIGHT sprite=%p hpoly=%08X rgb=(%.3f %.3f %.3f)",
                            sprite, sprite->m_hClipperPoly, light.x, light.y, light.z);
                --decalLightLogBudget;
            }
        }

        static int decalLogBudget = 48;
        if (LogIsSessionEnabled() && (decalLogBudget > 0))
        {
            LOG_SESSION("Sprite3D DECAL sprite=%p flags=%08X flags2=%08X hpoly=%08X clipped=%d polyVerts=%u tris=%u tex=%ux%u scale=(%.4f %.4f %.4f) pos=(%.2f %.2f %.2f)",
                        sprite, o.m_dwFlags, o.m_dwFlags2, sprite->m_hClipperPoly, hasClipper ? 1 : 0,
                        static_cast<unsigned>(polyVerts.size()), static_cast<unsigned>(gpuVerts.size() / 3),
                        tex->width, tex->height, o.m_vScale.x, o.m_vScale.y, o.m_vScale.z,
                        o.m_vPos.x, o.m_vPos.y, o.m_vPos.z);
            --decalLogBudget;
        }
    }
    else
    {
        // Normal camera-facing sprite path.        
        const LTVector right = reallyClose ? LTVector{1, 0, 0} : cam.Rotate({1, 0, 0});
        const LTVector up = reallyClose ? LTVector{0, 1, 0} : cam.Rotate({0, 1, 0});

        float sizeX = width * o.m_vScale.x;
        float sizeY = height * o.m_vScale.y;

        LTVector centerCam = reallyClose
                     ? LTVector{o.m_vPos.x, o.m_vPos.y, o.m_vPos.z}
                             : WorldToCamera(scene, {o.m_vPos.x, o.m_vPos.y, o.m_vPos.z});

        if (o.m_dwFlags & FLAG_GLOWSPRITE)
        {
            float factor = (centerCam.z - 10.0f) / (500.0f - 10.0f);
            factor = std::clamp(factor, 0.0f, 1.0f);
            factor = 0.1f + (2.0f - 0.1f) * factor;
            sizeX *= factor;
            sizeY *= factor;
        }

        // PVS is deliberately conservative: an object returned by Talon's
        // visibility set is not necessarily inside the exact camera frustum.
        // Normal sprites are camera-facing quads, so every corner has the same
        // camera-space Z as the center.  Cull before building/projecting the
        // quad; otherwise a sprite behind the eye can reach the vertex shader,
        // whose near-Z clamp can turn it into a huge screen-covering polygon.
        //
        // ReallyClose sprites use camera-space coordinates supplied directly
        // by the game (menus/HUD/cutscenes), so preserve their established path.
        if (!reallyClose)
        {
            const float nearZ = 1.0f;
            const float farZ = std::max(nearZ + 1.0f, scene->m_fFarZ);
            const float tanHalfX = std::tan(std::max(0.01f, scene->m_fFovX * 0.5f));
            const float tanHalfY = std::tan(std::max(0.01f, scene->m_fFovY * 0.5f));
            const float halfX = std::fabs(sizeX);
            const float halfY = std::fabs(sizeY);
            const float dist = centerCam.length();

            const char *cullReason = nullptr;
            if (!std::isfinite(centerCam.x) || !std::isfinite(centerCam.y) ||
                !std::isfinite(centerCam.z) || !std::isfinite(halfX) ||
                !std::isfinite(halfY))
            {
                cullReason = "NONFINITE";
            }
            else if (centerCam.z <= nearZ)
            {
                cullReason = (centerCam.z <= 0.0f) ? "BEHIND_CAMERA" : "NEAR_PLANE";
            }
            else if (centerCam.z > farZ)
            {
                cullReason = "FAR_PLANE";
            }
            else
            {
                // Conservative axis-aligned test in camera space.  Because the
                // billboard is parallel to the camera plane, halfX/halfY are
                // its exact projected camera-space extents before perspective.
                const float limitX = centerCam.z * tanHalfX;
                const float limitY = centerCam.z * tanHalfY;
                if (centerCam.x - halfX > limitX)
                    cullReason = "FRUSTUM_RIGHT";
                else if (centerCam.x + halfX < -limitX)
                    cullReason = "FRUSTUM_LEFT";
                else if (centerCam.y - halfY > limitY)
                    cullReason = "FRUSTUM_TOP";
                else if (centerCam.y + halfY < -limitY)
                    cullReason = "FRUSTUM_BOTTOM";
            }

            if (cullReason)
            {
                if (LogIsSessionEnabled())
                {
                    LOG_SESSION("Sprite3D SPRITE-CULL sprite=%p reason=%s world=(%.3f %.3f %.3f) view=(%.3f %.3f %.3f) dist=%.3f half=(%.3f %.3f) tex=%ux%u scale=(%.4f %.4f %.4f) flags=%08X flags2=%08X",
                                sprite, cullReason, o.m_vPos.x, o.m_vPos.y, o.m_vPos.z,
                                centerCam.x, centerCam.y, centerCam.z, dist, halfX, halfY,
                                tex->width, tex->height, o.m_vScale.x, o.m_vScale.y, o.m_vScale.z,
                                o.m_dwFlags, o.m_dwFlags2);
                }
                return false;
            }

            if (LogIsSessionEnabled())
            {
                LOG_SESSION("Sprite3D SPRITE-SUBMIT sprite=%p world=(%.3f %.3f %.3f) view=(%.3f %.3f %.3f) dist=%.3f half=(%.3f %.3f) tex=%ux%u scale=(%.4f %.4f %.4f) depth=%s bias=%d flags=%08X flags2=%08X",
                            sprite, o.m_vPos.x, o.m_vPos.y, o.m_vPos.z,
                            centerCam.x, centerCam.y, centerCam.z, dist, halfX, halfY,
                            tex->width, tex->height, o.m_vScale.x, o.m_vScale.y, o.m_vScale.z,
                            (o.m_dwFlags & FLAG_SPRITE_NOZ) ? "OFF" : "ON",
                            (o.m_dwFlags & FLAG_SPRITEBIAS) ? 1 : 0, o.m_dwFlags, o.m_dwFlags2);
            }
        }

        LTVector camPos[4];
        if (reallyClose)
        {
            const LTVector r{sizeX, 0, 0};
            const LTVector u{0, sizeY, 0};
            camPos[0] = centerCam + u - r;
            camPos[1] = centerCam + u + r;
            camPos[2] = centerCam - u + r;
            camPos[3] = centerCam - u - r;
        }
        else
        {
            const LTVector centerWorld{o.m_vPos.x, o.m_vPos.y, o.m_vPos.z};
            const LTVector r = right * sizeX;
            const LTVector u = up * sizeY;
            const LTVector worldPts[4] = {
                centerWorld + u - r, centerWorld + u + r,
                centerWorld - u + r, centerWorld - u - r};
            for (int i = 0; i < 4; ++i)
                camPos[i] = WorldToCamera(scene, worldPts[i]);
        }

        if (!reallyClose && (o.m_dwFlags & FLAG_SPRITEBIAS))
            for (LTVector &p : camPos)
                ApplySpritePositionBias(p);

        // Match the existing verified billboard path: inset by two texels.
        const float du = 1.0f / width, dv = 1.0f / height;
        const float minU = du * 2.0f, minV = dv * 2.0f;
        const float maxU = (width - 2.0f) * du, maxV = (height - 2.0f) * dv;
        const int ids[6] = {0, 1, 2, 0, 2, 3};
        const float uv[4][2] = {{minU, minV}, {maxU, minV}, {maxU, maxV}, {minU, maxV}};
        for (int id : ids)
            gpuVerts.push_back({camPos[id],
                                LTFloatPt(uv[id][0], uv[id][1]),
                                PGColor(cr, cg, cb, ca)});
    }

    // D3D clips sprite triangles against the camera near plane.  Do the same
    // explicitly before our manual projection.  The old vertex shader pinned
    // every vertex behind the near plane to nearZ while preserving X/Y, which
    // can turn a small sprite into screen-spanning triangles as the camera
    // passes through it.
    bool nearClipped = false;
    const float spriteNearZ = reallyClose ? 0.01f : 1.0f;
    ClipSpriteTrianglesToNearPlane(gpuVerts, spriteNearZ, nearClipped);

    if (nearClipped && LogIsSessionEnabled())
    {
        static int nearClipBudget = 128;
        if (LogIsSessionEnabled() && ((nearClipBudget > 0 && nearClipBudget--)))
            LOG_SESSION("Sprite3D NEAR-CLIP sprite=%p near=%.3f outVerts=%u flags=%08X flags2=%08X",
                        sprite, spriteNearZ, static_cast<unsigned>(gpuVerts.size()),
                        o.m_dwFlags, o.m_dwFlags2);
    }

    if (gpuVerts.empty() || gpuVerts.size() > 512)
        return false;

    ApplyTalonSpriteTextureRotation(o, gpuVerts);
    const bool textureRotate = (o.m_dwFlags2 & FLAG2_SPRITE_TROTATE) != 0;
    if (textureRotate)
    {
        // d3d.ren sets D3DTSS_ADDRESS (12) to D3DTADDRESS_CLAMP (3) for
        // the rotated-UV draw and restores WRAP (1) immediately afterwards.
        glf.TextureParameteri(tex->texture, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
        glf.TextureParameteri(tex->texture, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);
    }

    GLTrackedNamedBufferSubData(SpriteState().vbo, 0,
                                static_cast<GLsizeiptr>(gpuVerts.size() * sizeof(SpriteVertexGPU)), gpuVerts.data(), GLUploadCategory::Sprites);

    SpriteState().shader->Use();
    SetupProjection(scene, reallyClose);
    GLStateBindTextureUnit(0, tex->texture);
    GLStateBindVertexArray(SpriteState().vao);

    ApplySpriteBlend(renderMode);
    ApplySpriteColorKey(sprite);
    GLUniform1i(SpriteState().uAlphaTest, renderMode.alphaTest ? 1 : 0);
    GLUniform1f(SpriteState().uAlphaRef, renderMode.alphaRef);
    GLUniform1i(SpriteState().uAlphaFunc, static_cast<GLint>(renderMode.alphaFunc));

    GLUniform1ui(SpriteState().uMode, renderMode.mode);
    GLUniform3f(SpriteState().uModeColor,
                renderMode.modeColor[0],
                renderMode.modeColor[1],
                renderMode.modeColor[2]);

    const bool fogOn = ((renderMode.mode & SPRMODE_FOG_ENABLED) != 0u) && !reallyClose;
    GLUniform1i(SpriteState().uFogEnabled, fogOn ? 1 : 0);
    GLStateDisable(GL_CULL_FACE);

    if (o.m_dwFlags & FLAG_SPRITE_NOZ)
        GLStateDisable(GL_DEPTH_TEST);
    else if (renderMode.stateZEnableOverride && !renderMode.stateZEnable)
        GLStateDisable(GL_DEPTH_TEST);
    else
    {
        GLStateEnable(GL_DEPTH_TEST);
        const uint32 zfunc = renderMode.stateZFuncOverride ? renderMode.stateZFunc : 4u;
        GLStateDepthFunc(static_cast<GLenum>(TalonRenderStateSystem::Instance().MapCompareToGL(zfunc)));
    }

    // Stock sprites are normally depth-read/no-write, but texture StateChange
    // can explicitly override D3DRS_ZWRITEENABLE.
    GLStateDepthMask((renderMode.stateZWriteOverride && renderMode.stateZWrite) ? GL_TRUE : GL_FALSE);
    glf.DrawArrays(GL_TRIANGLES_, 0, static_cast<GLsizei>(gpuVerts.size()));
    GLStateDepthMask(GL_TRUE);

    if (textureRotate)
    {
        glf.TextureParameteri(tex->texture, GL_TEXTURE_WRAP_S_, GL_REPEAT);
        glf.TextureParameteri(tex->texture, GL_TEXTURE_WRAP_T_, GL_REPEAT);
    }

    ++SpriteState().spriteCount;
    SpriteState().triCount += gpuVerts.size() / 3;
    return true;
}

void SpriteRenderer::ResetStats()
{
    SpriteState().spriteCount = 0;
    SpriteState().triCount = 0;
}

void SpriteRenderer::GetStats(uint64_t &sprites, uint64_t &tris) const
{
    sprites = SpriteState().spriteCount;
    tris = SpriteState().triCount;
}

SpriteRenderer &SpriteRenderer::Instance()
{
    static SpriteRenderer v;
    return v;
}