#include "subsystems/renderer/Console.h"
#include "../renderer/frame_constants.h"
#include "../textures/texture_manager.h"
#include "../world/world_renderer.h"
#include "../renderer/renderer_core.h"

#include <cfloat>
#include "lt_renderer_abi.h"
#include "gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "shaders/shader_manager.h"
#include "gl_renderer.h"
#include "utils/log.h"
#include "subsystems/textures/Texture.h"
#include "subsystems/models/abc_model_renderer.h"
#include "subsystems/renderer/stock_render_options.h"
#include "subsystems/renderer/talon_render_state.h"
#include "subsystems/renderer/fog_state.h"
#include "subsystems/timing/high_refresh_timing.h"

#include "shaders/shader_resources.h"

#include <GL/gl.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <initializer_list>

namespace
{
    static ABCModelRendererState &ModelState() { return ABCModelRenderer::Instance().State(); }

    struct ModelVertexGPU
    {
        LTVector pos;
        LTVector normal;
        LTFloatPt uv;
        PGColor color;
    };

    // GPU-skinned Talon model path.  ModelVert::NewVertexWeight already contains
    // the four vectors consumed by Talon's matrix palette, so preserve those raw
    // values and perform the exact matrix*vector accumulation in the vertex
    // shader.  Node indices are kept as floats because the existing DSA loader
    // only needs floating-point vertex attribute formats; Talon node indices are
    // small integers and are represented exactly by IEEE-754 float.
    struct ModelBatchVertexGPU
    {
        LTVector pos;
        LTVector normal;
        LTFloatPt uv;
        float weightVec[4][4];
        float nodeIndex[4];
        float weightCount;
        float skinIndex;
    };

    struct ModelBatchLightGPU
    {
        float posRadius[4];  // camera xyz, radius
        float innerType[4];  // inner rgb, 0=point / 1=spot
        float dirFov[4];     // camera direction xyz, spot cosine
        float outerClose[4]; // outer rgb, close-hack enable
    };

    struct ModelBatchSkinStateGPU
    {
        float data0[4]; // mode bits, alphaRef, detailEnabled, detailScale
        float data1[4]; // detailAdd, modeColor rgb
    };
    static_assert(sizeof(ModelBatchVertexGPU) == 120, "Model batch vertex layout changed");
    static_assert(sizeof(ModelBatchLightGPU) == 64, "Model batch light std430 layout changed");
    static_assert(sizeof(ModelBatchSkinStateGPU) == 32, "Model batch skin std430 layout changed");

    GLuint g_vao3D = 0;
    GLuint g_vbo3D = 0;
    constexpr size_t MAX_MODEL_VERTICES = 1024 * 1024;

    struct CharacterShadowVertexGPU
    {
        float x, y, z;
        float u, v;
    };

    GLuint g_characterShadowVao = 0;
    GLuint g_characterShadowVbo = 0;
    GLuint g_characterShadowTexture = 0;
    avp2::render::Shader *g_characterShadowShader = nullptr;
    GLint g_uShadowTanHalfFovX = -1;
    GLint g_uShadowTanHalfFovY = -1;
    GLint g_uShadowNearZ = -1;
    GLint g_uShadowFarZ = -1;
    GLint g_uShadowAlpha = -1;
    GLint g_uShadowFogNear = -1;
    GLint g_uShadowFogFar = -1;
    GLint g_uShadowFogEnabled = -1;

    GLuint g_vaoModelBatch = 0;
    GLuint g_vboModelBatch = 0;
    GLuint g_modelNodeSsbo = 0;
    GLuint g_modelLightSsbo = 0;
    GLuint g_modelSkinStateSsbo = 0;
    GLuint g_modelFrameSsbo = 0;
    void *g_modelFrameMapped = nullptr;
    constexpr size_t MODEL_STREAM_FRAMES = 3;
    constexpr size_t MODEL_STREAM_SEGMENT_BYTES = 4u * 1024u * 1024u;
    GLSyncHandle g_modelFrameFences[MODEL_STREAM_FRAMES]{};
    uint32 g_modelFrameSlot = 0;
    size_t g_modelFrameCursorBytes = 0;
    size_t g_modelSsboAlignment = 256;
    bool g_modelFrameUsed = false;
    size_t g_modelBatchVertexCapacity = 0;

    struct ModelGpuGeometryCache
    {
        GLuint vbo = 0;
        GLsizei vertexCount = 0;
        uint32 visiblePieces = 0;
        uint32 maxReferencedNode = 0;
        bool hasWeightedVertices = false;
        std::vector<GLint> pieceFirst;
        std::vector<GLsizei> pieceCount;
    };
    static std::unordered_map<uint64_t, ModelGpuGeometryCache> g_modelGpuGeometryCache;

    constexpr size_t MAX_MODEL_BATCH_VERTICES = 1024 * 1024;
    constexpr uint32 MAX_MODEL_BATCH_NODES = 1024;
    constexpr uint32 MAX_MODEL_BATCH_LIGHTS = 256;
    constexpr uint32 MODEL_BATCH_SKIN_SLOTS = MAX_MODEL_TEXTURES;

    static size_t AlignModelStream(size_t value)
    {
        const size_t a = std::max<size_t>(16u, g_modelSsboAlignment);
        return ((value + a - 1u) / a) * a;
    }

    struct ModelFrameStreamRanges
    {
        GLintptr nodeOffset = 0;
        GLsizeiptr nodeBytes = 0;
        GLintptr lightOffset = 0;
        GLsizeiptr lightBytes = 0;
        GLintptr skinOffset = 0;
        GLsizeiptr skinBytes = 0;
    };

    static bool UploadModelFrameState(const LTMatrix *transforms, uint32 nodeCount,
                                      const ModelBatchLightGPU *lights, size_t lightCount,
                                      const ModelBatchSkinStateGPU *skin, size_t skinCount,
                                      ModelFrameStreamRanges &out)
    {
        if (!g_modelFrameSsbo || !g_modelFrameMapped || !glf.BindBufferRange)
            return false;

        const size_t nodeBytes = size_t(nodeCount) * sizeof(LTMatrix);
        const size_t lightBytes = lightCount * sizeof(ModelBatchLightGPU);
        const size_t skinBytes = skinCount * sizeof(ModelBatchSkinStateGPU);
        size_t cursor = AlignModelStream(g_modelFrameCursorBytes);
        const size_t segmentBase = size_t(g_modelFrameSlot) * MODEL_STREAM_SEGMENT_BYTES;
        const size_t segmentEnd = segmentBase + MODEL_STREAM_SEGMENT_BYTES;

        const size_t nodeOffset = cursor;
        cursor = AlignModelStream(cursor + nodeBytes);
        const size_t lightOffset = cursor;
        cursor = AlignModelStream(cursor + lightBytes);
        const size_t skinOffset = cursor;
        cursor = AlignModelStream(cursor + skinBytes);
        if (cursor > segmentEnd)
            return false;

        auto *base = static_cast<unsigned char *>(g_modelFrameMapped);
        if (nodeBytes && transforms)
        {
            std::memcpy(base + nodeOffset, transforms, nodeBytes);
            GLUploadStats::Instance().RecordModelStreamWrite(GLModelUploadKind::Nodes, nodeBytes);
        }
        if (lightBytes && lights)
        {
            std::memcpy(base + lightOffset, lights, lightBytes);
            GLUploadStats::Instance().RecordModelStreamWrite(GLModelUploadKind::Lights, lightBytes);
        }
        if (skinBytes && skin)
        {
            std::memcpy(base + skinOffset, skin, skinBytes);
            GLUploadStats::Instance().RecordModelStreamWrite(GLModelUploadKind::SkinState, skinBytes);
        }

        out.nodeOffset = static_cast<GLintptr>(nodeOffset);
        out.nodeBytes = static_cast<GLsizeiptr>(nodeBytes);
        out.lightOffset = static_cast<GLintptr>(lightOffset);
        out.lightBytes = static_cast<GLsizeiptr>(lightBytes);
        out.skinOffset = static_cast<GLintptr>(skinOffset);
        out.skinBytes = static_cast<GLsizeiptr>(skinBytes);
        g_modelFrameCursorBytes = cursor;
        g_modelFrameUsed = true;
        return true;
    }

    GLint g_uBatchTanHalfFovX = -1;
    GLint g_uBatchTanHalfFovY = -1;
    GLint g_uBatchNearZ = -1;
    GLint g_uBatchFarZ = -1;
    GLint g_uBatchObjPos = -1;
    GLint g_uBatchObjScale = -1;
    GLint g_uBatchObjQuat = -1;
    GLint g_uBatchCamPos = -1;
    GLint g_uBatchCamQuat = -1;
    GLint g_uBatchReallyClose = -1;
    GLint g_uBatchNodeCount = -1;
    GLint g_uBatchAmbient = -1;
    GLint g_uBatchHookColor = -1;
    GLint g_uBatchSceneTint = -1;
    GLint g_uBatchLightAdd = -1;
    GLint g_uBatchDirColor = -1;
    GLint g_uBatchDirCamera = -1;
    GLint g_uBatchAlpha = -1;
    GLint g_uBatchLightCount = -1;
    GLint g_uBatchFogEnabled = -1;
    GLint g_uBatchFogColor = -1;
    GLint g_uBatchFogNear = -1;
    GLint g_uBatchFogFar = -1;
    GLint g_uBatchFogAdditive = -1;
    GLint g_uBatchVFogEnabled = -1, g_uBatchVFogMinY = -1, g_uBatchVFogMaxY = -1;
    GLint g_uBatchVFogMinYVal = -1, g_uBatchVFogMaxYVal = -1, g_uBatchVFogDensity = -1, g_uBatchVFogMax = -1;
    GLint g_uBatchEnvPass = -1;
    GLint g_uBatchEnvParams = -1;
    GLint g_uBatchBlendMode = -1;

    GLint g_uTanHalfFovX = -1;
    GLint g_uTanHalfFovY = -1;
    GLint g_uNearZ = -1;
    GLint g_uFarZ = -1;
    GLint g_uTextured = -1;
    GLint g_uModelMode = -1;
    GLint g_uModelModeColor = -1;
    GLint g_uModelAlphaRef = -1;
    GLint g_uModelAlphaFunc = -1;
    GLint g_uModelFogEnabled = -1;
    GLint g_uModelFogColor = -1;
    GLint g_uModelFogNear = -1;
    GLint g_uModelFogFar = -1;
    GLint g_uModelFogAdditive = -1;
    GLint g_uModelVFogEnabled = -1, g_uModelVFogMinY = -1, g_uModelVFogMaxY = -1;
    GLint g_uModelVFogMinYVal = -1, g_uModelVFogMaxYVal = -1, g_uModelVFogDensity = -1, g_uModelVFogMax = -1;
    GLint g_uModelHookColor = -1;
    GLint g_uModelSceneTint = -1;
    GLint g_uModelLightAdd = -1;
    GLint g_uModelLinkedMode = -1; // 0=none, 1=Talon model detail texture
    GLint g_uModelDetailScale = -1;
    GLint g_uModelDetailAdd = -1;
    GLint g_uModelEnvPass = -1;   // 0=none, 1=Talon model environment contribution enabled
    GLint g_uModelEnvParams = -1; // x=scale, y=panU, z=panV
    GLint g_uModelBlendMode = -1;
    static void ApplyModelVFogUniforms(GLint enabled, GLint minY, GLint maxY, GLint minYVal, GLint maxYVal, GLint density, GLint maxAmount)
    {
        GLUniform1i(enabled, g_fogState.vFog ? 1 : 0);
        GLUniform1f(minY, g_fogState.vFogMinY);
        GLUniform1f(maxY, g_fogState.vFogMaxY);
        GLUniform1f(minYVal, g_fogState.vFogMinYVal);
        GLUniform1f(maxYVal, g_fogState.vFogMaxYVal);
        GLUniform1f(density, g_fogState.vFogDensity);
        GLUniform1f(maxAmount, g_fogState.vFogMax);
    }
 // shader collapse of Talon env pre-pass + skin/detail pass

    uint64_t g_modelCount = 0;
    uint64_t g_triCount = 0;

    static LTVector MatrixTransformPoint(const LTMatrix &m, const float v[4], float &outW)
    {
        // Matches the Talon model shader's matrix * weight-vector convention.
        const float x = m.m[0][0] * v[0] + m.m[0][1] * v[1] + m.m[0][2] * v[2] + m.m[0][3] * v[3];
        const float y = m.m[1][0] * v[0] + m.m[1][1] * v[1] + m.m[1][2] * v[2] + m.m[1][3] * v[3];
        const float z = m.m[2][0] * v[0] + m.m[2][1] * v[1] + m.m[2][2] * v[2] + m.m[2][3] * v[3];
        outW = m.m[3][0] * v[0] + m.m[3][1] * v[1] + m.m[3][2] * v[2] + m.m[3][3] * v[3];
        return {x, y, z}; // Assuming LTVector has a constructor that takes three floats
    }

    static LTVector SkinVertex(const ModelVert &vert, LTMatrix *transforms)
    {
        if (!vert.m_pWeights || vert.m_wWeights == 0 || !transforms)
            return {vert.m_vVec.x, vert.m_vVec.y, vert.m_vVec.z};

        LTVector sum{0, 0, 0};
        float sumW = 0.0f;
        const uint16 count = std::min<uint16>(vert.m_wWeights, 4);

        for (uint16 i = 0; i < count; ++i)
        {
            float w = 0.0f;
            LTVector p = MatrixTransformPoint(transforms[vert.m_pWeights[i].m_dwNode],
                                          vert.m_pWeights[i].m_afVec, w);
            sum = sum + p;
            sumW += w;
        }

        if (std::fabs(sumW) > 1e-7f)
            sum = sum * (1.0f / sumW);

        return sum;
    }

    static LTVector MatrixTransformVector(const LTMatrix &m, LTVector v)
    {
        return {
            m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z,
            m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z,
            m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z};
    }

    static LTVector SkinNormal(const ModelVert &vert, LTMatrix *transforms)
    {
        const LTVector bindN{vert.m_vNormal.x, vert.m_vNormal.y, vert.m_vNormal.z};
        if (!vert.m_pWeights || vert.m_wWeights == 0 || !transforms)
            return bindN.normalize();

        LTVector sum{0, 0, 0};
        float sumWeight = 0.0f;
        const uint16 count = std::min<uint16>(vert.m_wWeights, 4);
        for (uint16 i = 0; i < count; ++i)
        {
            // NewVertexWeight::m_afVec[3] is the homogeneous skin weight used by
            // Talon's matrix-palette position path.  Apply that same scalar to
            // the bind normal, but transform it with only the 3x3 rotational
            // portion of the node matrix (no translation).
            const float w = vert.m_pWeights[i].m_afVec[3];
            if (std::fabs(w) <= 1e-8f)
                continue;
            sum = sum + (MatrixTransformVector(transforms[vert.m_pWeights[i].m_dwNode], bindN) * w);
            sumWeight += w;
        }
        if (std::fabs(sumWeight) > 1e-8f)
            sum = sum * (1.0f / sumWeight);
        const float len2 = sum.x * sum.x + sum.y * sum.y + sum.z * sum.z;
        return len2 > 1e-12f ? sum.normalize() : bindN.normalize();
    }

    static void GetPresentationObjectPose(const SceneDesc *scene, const LTObjectCompat &obj, LTVector &pos, LTRotation &rot)
    {
        pos = obj.m_vPos;
        rot = obj.m_rRot;
        if (!scene || scene->m_nDrawMode != DRAWMODE_NORMAL)
            return;
        const float inPos[3] = {obj.m_vPos.x, obj.m_vPos.y, obj.m_vPos.z};
        const float inQuat[4] = {obj.m_rRot.x, obj.m_rRot.y, obj.m_rRot.z, obj.m_rRot.w};
        float outPos[3], outQuat[4];
        if (HighRefreshTimingFix::InterpolateObjectTransform(&obj, obj.m_wObjectID, obj.m_nObjectType, inPos, inQuat, outPos, outQuat))
        {
            pos = {outPos[0], outPos[1], outPos[2]};
            rot.x = outQuat[0];
            rot.y = outQuat[1];
            rot.z = outQuat[2];
            rot.w = outQuat[3];
        }
    }

    static LTVector ToCamera(const SceneDesc *scene, const LTObjectCompat &obj, LTVector modelPos)
    {
        LTVector scaled{
            modelPos.x * obj.m_vScale.x,
            modelPos.y * obj.m_vScale.y,
            modelPos.z * obj.m_vScale.z};

        LTVector ppos;
        LTRotation prot;
        GetPresentationObjectPose(scene, obj, ppos, prot);
        LTRotation oq{prot.x, prot.y, prot.z, prot.w};
        LTVector transformed = oq.Rotate(scaled) + LTVector{ppos.x, ppos.y, ppos.z};

        // Talon ReallyClose models are already expressed in view-relative space.
        // Original d3d_GetFinalModelTransform omits the normal view transform and
        // uses the special ReallyClose projection directly.
        if (obj.m_dwFlags & FLAG_REALLYCLOSE)
            return transformed;

        LTVector rel = transformed - LTVector{scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z};
        LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                scene->m_rRotation.z, scene->m_rRotation.w};

        return cq.Conjugate().Rotate(rel);
    }

    static LTVector ToCameraNormal(const SceneDesc *scene, const LTObjectCompat &obj, LTVector n)
    {
        LTVector ppos;
        LTRotation prot;
        GetPresentationObjectPose(scene, obj, ppos, prot);
        LTRotation oq{prot.x, prot.y, prot.z, prot.w};
        LTVector modelN = oq.Rotate(n);

        if (obj.m_dwFlags & FLAG_REALLYCLOSE)
            return modelN.normalize();

        LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                scene->m_rRotation.z, scene->m_rRotation.w};
        return cq.Conjugate().Rotate(modelN);
    }

    // Environment coordinates are generated in view orientation even for
    // ReallyClose geometry. Stock d3d.ren keeps the special RC position/projection
    // separate from the model/view normal matrix used by its env-UV callback.
    static LTVector ToEnvironmentNormal(const SceneDesc *scene, const LTObjectCompat &obj, LTVector n)
    {
        LTVector ppos;
        LTRotation prot;
        GetPresentationObjectPose(scene, obj, ppos, prot);
        LTRotation oq{prot.x, prot.y, prot.z, prot.w};
        LTVector modelN = oq.Rotate(n);
        LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                scene->m_rRotation.z, scene->m_rRotation.w};
        return cq.Conjugate().Rotate(modelN);
    }

    struct ModelRenderSetup
    {
        uint32 effectiveFlags = 0;
        uint32 hookFlags = 1; // MHF_USETEXTURE
        LTVector lightAdd{};
        LTVector objectColor{};
        LTVector sceneTint{1.0f, 1.0f, 1.0f};
        // True when the game-side ModelHookFn explicitly changed m_pObjectColor.
        // Talon vision modes use this as a per-model classification/override
        // (for example a thermal-hot human) and it must take precedence over
        // the scene-wide model tint instead of being multiplied by it.
        bool hookColorOverride = false;
    };

    struct ModelPointLight
    {
        LTVector cameraPos;
        LTVector color;
        float radius = 0.0f;
        bool closeHack = true;
    };

    struct ModelStaticLight
    {
        LTVector cameraPos;
        LTVector innerColor;
        LTVector outerColor;
        LTVector cameraDir;
        float radius = 0.0f;
        float fov = 0.0f;
        bool point = true;
        bool closeHack = true;
    };

    struct ModelLighting
    {
        LTVector ambient;  // scene-tinted base/grid lighting
        LTVector lightAdd; // ModelHookData add; stock keeps this UNTINTED
        LTVector dirColor;
        LTVector dirCamera;
        std::array<ModelPointLight, 16> dynamicLights{};
        std::array<ModelStaticLight, 16> staticLights{};
        uint32 dynamicLightCount = 0;
        uint32 staticLightCount = 0;
        float alpha;
        bool noLight;
    };

    enum ModelModeBits : uint32
    {
        MMD_NO_TEXTURE = (1u << 2),
        MMD_ADD_SIGNED = (1u << 6),
        MMD_NO_LIGHT = (1u << 7),
        MMD_FLAT_COLOR = (1u << 8),
        MMD_CHROMAKEY = (1u << 9),
        MMD_FULL_BRITE = (1u << 11),
        MMD_MODULATE2X = (1u << 16)
    };

    enum class ModelBlendMode
    {
        Opaque,
        Alpha,
        Add,
        Multiply,
        Invert
    };

    struct ModelMaterialMode
    {
        uint32 mode = 0;
        ModelBlendMode blend = ModelBlendMode::Opaque;
        float modeColor[3] = {0.0f, 0.0f, 0.0f};
        float alphaRef = 0.0f;
        const char *stateName = "none";
        bool stateBlendOverride = false;
        bool stateBlendEnable = false;
        uint32 stateSrcBlend = 2;
        uint32 stateDestBlend = 1;
        bool stateZWriteOverride = false;
        bool stateZWrite = true;
        bool stateZEnableOverride = false;
        bool stateZEnable = true;
        bool stateZFuncOverride = false;
        uint32 stateZFunc = 4;
        uint32 alphaFunc = 7;
        bool stateCullOverride = false;
        uint32 stateCullMode = 0;
    };

    static bool ModelRSMatch(const StateChangeCompat *sc,
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
            if (v.first != 34 && rs.m_dwRenderState != v.second)
                return false;
        }
        return true;
    }

    static bool ModelTSMatch(const StateChangeCompat *sc,
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

    static void ApplyModelStateChange(SharedTexture *texture, ModelMaterialMode &out)
    {
        if (!texture)
            return;

        auto *st = reinterpret_cast<SharedTextureCompat *>(texture);
        if (!st->m_pStateChange)
            return;

        auto *sc = reinterpret_cast<StateChangeCompat *>(st->m_pStateChange);
        if (sc->m_RenderList.size() > 32 || sc->m_TextureList.size() > 32)
            return;

        // Preserve arbitrary D3D8 StateChange render-state overrides in
        // addition to the named Talon render modes below.
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
        if (d3d.hasCullMode)
        {
            out.stateCullOverride = true;
            out.stateCullMode = d3d.cullMode;
        }
        if (d3d.hasAlphaTestEnable && d3d.alphaTestEnable)
        {
            // The model shader's cutout bit is the stock alpha-test path: it only
            // discards by sampled alpha and does not imply GL blending.
            out.mode |= MMD_CHROMAKEY;
            out.alphaRef = TalonRenderStateSystem::Instance().AlphaRef01(
                d3d, 0.5f + 0.5f / 255.0f);
            out.alphaFunc = d3d.hasAlphaFunc ? d3d.alphaFunc : 7u;
        }

        // Decode stage-0 COLOROP by state id even when the StateChange contains
        // additional render states or a different vector ordering.
        if (d3d.hasStage0ColorOp)
        {
            if (d3d.stage0ColorOp == 8u)
                out.mode |= MMD_ADD_SIGNED; // ADDSIGNED
            else if (d3d.stage0ColorOp == 5u)
                out.mode |= MMD_MODULATE2X; // MODULATE2X
            else if (d3d.stage0ColorOp == 2u)
                out.mode |= MMD_NO_LIGHT; // SELECTARG1
        }

        if (ModelRSMatch(sc, {}) && ModelTSMatch(sc, {{0, 1, 8}}))
        {
            out.mode |= MMD_ADD_SIGNED;
            out.stateName = "AddSigned";
        }
        else if (ModelRSMatch(sc, {}) && ModelTSMatch(sc, {{0, 1, 5}}))
        {
            out.mode |= MMD_MODULATE2X;
            out.stateName = "Modulate2X";
        }
        else if (ModelRSMatch(sc, {}) && ModelTSMatch(sc, {{0, 1, 2}}))
        {
            out.mode |= MMD_NO_LIGHT;
            out.stateName = "NoLighting";
        }
        else if (ModelRSMatch(sc, {{19, 9}, {20, 3}}) && ModelTSMatch(sc, {}))
        {
            out.mode &= ~MMD_FULL_BRITE;
            out.stateName = "NoFullbright";
        }
        else if (ModelRSMatch(sc, {{19, 4}, {20, 4}, {27, 1}, {28, 0}}) &&
                 ModelTSMatch(sc, {{0, 1, 2}}))
        {
            out.mode |= MMD_NO_LIGHT;
            out.blend = ModelBlendMode::Invert;
            out.stateName = "NavAliens";
        }
        else if (ModelRSMatch(sc, {{28, 0}}) && ModelTSMatch(sc, {{0, 1, 2}}))
        {
            out.mode |= MMD_NO_LIGHT;
            out.stateName = "NoFog";
        }
        else if (ModelRSMatch(sc, {{28, 1}, {34, 0}, {35, 3}, {36, 0}, {37, 0}}) &&
                 ModelTSMatch(sc, {{0, 1, 2}}))
        {
            out.mode |= (MMD_NO_LIGHT | MMD_FLAT_COLOR);
            const uint32 color = sc->m_RenderList.m_pFirst[1].m_dwRenderState;
            out.modeColor[0] = ((color >> 16) & 0xFF) / 255.0f;
            out.modeColor[1] = ((color >> 8) & 0xFF) / 255.0f;
            out.modeColor[2] = (color & 0xFF) / 255.0f;
            out.stateName = "FogColored";
        }
        else
        {
            out.stateName = "UNKNOWN";
            static int budget = 16;
            if (LogIsSessionEnabled() && ((budget > 0 && budget--)))
                LOG_SESSION("Model3D UNKNOWN StateChange ptr=%p rs=%u ts=%u",
                            sc, sc->m_RenderList.size(), sc->m_TextureList.size());
        }
    }

    struct ModelTextureConsoleState
    {
        float detailTextures = 1.0f;
        float detailTextureAdd = 1.0f;
        float modelDetailTextureScale = 3.0f;
        float envMapAll = 0.0f;
        float envMapEnable = 0.0f;
        // Stock AVP2 d3d.ren initializes EnvPanSpeed to 0.0.  Keep the
        // parameter live so an explicit game/config override still works, but do
        // not inject renderer-side motion when Talon did not request any.
        float envPanSpeed = 0.0f;
        float envScale = 1.0f;
        std::uint64_t lastReadMs = ~std::uint64_t(0);
    };

    static const ModelTextureConsoleState &GetModelTextureConsoleState()
    {
        static ModelTextureConsoleState s{};
        const std::uint64_t now = static_cast<std::uint64_t>(GetTickCount64());
        if (s.lastReadMs == ~std::uint64_t(0) || now - s.lastReadMs >= 100u)
        {
            // Defaults recovered from AVP2 d3d.ren:
            //   DetailTextures          0x100098D5 -> 1
            //   DetailTextureAdd        0x100098F4 -> 1
            //   ModelDetailTextureScale 0x10001150 -> 3.0
            s.detailTextures = Console::Instance().GetFloat("DetailTextures", 1.0f);
            s.detailTextureAdd = Console::Instance().GetFloat("DetailTextureAdd", 1.0f);
            s.modelDetailTextureScale = Console::Instance().GetFloat("ModelDetailTextureScale", 3.0f);
            // Talon model environment controls. EnvMapEnable's renderer-side
            // descriptor starts at zero; the game can enable it through the
            // console parameter exactly as it does with d3d.ren.
            s.envMapAll = Console::Instance().GetFloat("EnvMapAll", 0.0f);
            s.envMapEnable = Console::Instance().GetFloat("EnvMapEnable", 0.0f);
            // d3d.ren 0x10011841..0x1001184D stores FLDZ into the
            // EnvPanSpeed console variable; its stock default is exactly 0.0.
            // EnvScale is initialized with FLD1 at 0x1001189A..0x100118A6.
            s.envPanSpeed = Console::Instance().GetFloat("EnvPanSpeed", 0.0f);
            s.envScale = Console::Instance().GetFloat("EnvScale", 1.0f);
            s.lastReadMs = now;
        }
        return s;
    }

    static ModelMaterialMode BuildModelMaterial(const ModelInstanceCompat *inst,
                                                const ModelRenderSetup &setup,
                                                SharedTexture *texture,
                                                const Texture *glTexture)
    {
        ModelMaterialMode out{};

        const uint32 flags = setup.effectiveFlags;
        const uint32 flags2 = inst->m_Base.m_dwFlags2;

        if (!texture || !(setup.hookFlags & 1u))
            out.mode |= MMD_NO_TEXTURE;

        if (flags & FLAG_NOLIGHT)
            out.mode |= MMD_NO_LIGHT;

        if (flags2 & FLAG2_CHROMAKEY)
        {
            // Talon chromakey models are a dedicated cutout phase, not ordinary
            // translucent models.  Keep blending disabled and Z writes enabled;
            // the fragment shader alpha-test/discard provides the holes.  This is
            // critical for multi-piece foliage models: transparent leaf texels
            // must not reserve depth and hide an opaque trunk drawn afterwards.
            out.mode |= MMD_CHROMAKEY;
            out.blend = ModelBlendMode::Opaque;
        }

        // Talon d3d.ren model classification (process handler 0x10024CEB):
        // object alpha decides whether a model enters the translucent-model path.
        // FLAG2_ADDITIVE / FLAG2_MULTIPLY are only interpreted by the translucent
        // model callback; they do NOT make an alpha-255 solid model blended.
        //
        // Our old code applied ONE/ONE to every no-light FLAG2_ADDITIVE model,
        // including opaque interface meshes.  That is not stock AVP2 behavior and
        // can massively over-brighten a multi-piece loading-screen model.
        if (inst->m_Base.m_nColorA < 255)
        {
            if (flags2 & FLAG2_ADDITIVE)
                out.blend = ModelBlendMode::Add;
            else if (flags2 & FLAG2_MULTIPLY)
                out.blend = ModelBlendMode::Multiply;
            else
                out.blend = ModelBlendMode::Alpha;
        }

        if (glTexture)
            out.alphaRef = glTexture->alphaRef;

        if ((out.mode & MMD_CHROMAKEY) && out.alphaRef == 0.0f)
            out.alphaRef = 0.5f + (0.5f / 255.0f);

        ApplyModelStateChange(texture, out);
        return out;
    }

    static const char *ModelCullModeName(uint32 mode)
    {
        switch (mode)
        {
        case 1u:
            return "NONE";
        case 2u:
            return "CW";
        case 3u:
            return "CCW";
        default:
            return "UNKNOWN";
        }
    }

    static void ApplyModelCull(const ModelMaterialMode &mat, bool stockChromakeyFallback)
    {
        // D3D8 D3DCULL values: NONE=1, CW=2, CCW=3.  The value names the
        // winding to discard.  OpenGL names the winding considered FRONT, so
        // express the same contract as BACK-face culling with the opposite front
        // winding.  Talon's +Z-forward projection does not introduce a viewport Y
        // flip in our GL path, therefore the screen-space winding maps directly.
        if (mat.stateCullOverride)
        {
            switch (mat.stateCullMode)
            {
            case 1u: // D3DCULL_NONE
                GLStateDisable(GL_CULL_FACE);
                return;
            case 2u: // D3DCULL_CW: keep CCW faces
                GLStateFrontFace(GL_CCW);
                GLStateCullFace(GL_BACK);
                GLStateEnable(GL_CULL_FACE);
                return;
            case 3u: // D3DCULL_CCW: keep CW faces (D3D8 default)
                GLStateFrontFace(GL_CW);
                GLStateCullFace(GL_BACK);
                GLStateEnable(GL_CULL_FACE);
                return;
            default:
                // Unknown/custom state: do not invent a winding policy.
                GLStateDisable(GL_CULL_FACE);
                return;
            }
        }

        // Retail D3D8's default raster state is D3DCULL_CCW.  Earlier OpenGL
        // revisions intentionally disabled model culling globally because that
        // also affected menus/ReallyClose content.  Reintroduce the stock default
        // only where we have strong evidence it is required: normal world-space
        // chromakey/cutout ABCs such as the AvP2 canopy cards.  Other model paths
        // remain unchanged unless their material carries an explicit CullMode.
        if (stockChromakeyFallback)
        {
            GLStateFrontFace(GL_CW);
            GLStateCullFace(GL_BACK);
            GLStateEnable(GL_CULL_FACE);
        }
        else
            GLStateDisable(GL_CULL_FACE);
    }

    static void ApplyModelBlend(const ModelMaterialMode &mat)
    {
        // Reset the stock model depth state for every material so a StateChange on
        // one piece cannot leak ZENABLE/ZFUNC into the next piece.
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);
        if (mat.stateZEnableOverride && !mat.stateZEnable)
            GLStateDisable(GL_DEPTH_TEST);
        else if (mat.stateZFuncOverride)
            GLStateDepthFunc(static_cast<GLenum>(TalonRenderStateSystem::Instance().MapCompareToGL(mat.stateZFunc)));

        if (mat.stateBlendOverride)
        {
            if (mat.stateBlendEnable)
            {
                GLStateEnable(GL_BLEND);
                GLStateBlendFunc(
                    static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(mat.stateSrcBlend)),
                    static_cast<GLenum>(TalonRenderStateSystem::Instance().MapBlendToGL(mat.stateDestBlend)));
            }
            else
                GLStateDisable(GL_BLEND);

            GLStateDepthMask(mat.stateZWriteOverride ? (mat.stateZWrite ? GL_TRUE : GL_FALSE)
                                                     : (mat.blend == ModelBlendMode::Opaque ? GL_TRUE : GL_FALSE));
            return;
        }

        switch (mat.blend)
        {
        case ModelBlendMode::Opaque:
            GLStateDisable(GL_BLEND);
            GLStateDepthMask(GL_TRUE);
            break;
        case ModelBlendMode::Alpha:
            GLStateEnable(GL_BLEND);
            GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            GLStateDepthMask(GL_TRUE);
            break;
        case ModelBlendMode::Add:
            GLStateEnable(GL_BLEND);
            GLStateBlendFunc(GL_ONE, GL_ONE);
            GLStateDepthMask(GL_FALSE);
            break;
        case ModelBlendMode::Multiply:
            GLStateEnable(GL_BLEND);
            // Talon d3d.ren: D3DBLEND_ZERO / D3DBLEND_SRCCOLOR.
            GLStateBlendFunc(GL_ZERO, GL_SRC_COLOR);
            GLStateDepthMask(GL_FALSE);
            break;
        case ModelBlendMode::Invert:
            GLStateEnable(GL_BLEND);
            GLStateBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
            GLStateDepthMask(GL_FALSE);
            break;
        default:
            GLStateDisable(GL_BLEND);
            GLStateDepthMask(GL_TRUE);
            break;
        }

        if (mat.stateZWriteOverride)
            GLStateDepthMask(mat.stateZWrite ? GL_TRUE : GL_FALSE);
    }

    static LTVector SampleModelLightTable(const LightTableCompat *table, const LTVector &pos)
    {
        if (!table || !table->m_pLookup ||
            table->m_adwLookupSize[0] < 2 ||
            table->m_adwLookupSize[1] < 2 ||
            table->m_adwLookupSize[2] < 2)
            return {0.0f, 0.0f, 0.0f};

        float sx = (pos.x - table->m_vLookupStart.x) * table->m_vReciBlockSize.x;
        float sy = (pos.y - table->m_vLookupStart.y) * table->m_vReciBlockSize.y;
        float sz = (pos.z - table->m_vLookupStart.z) * table->m_vReciBlockSize.z;

        int gx = std::clamp((int)sx, 0, table->m_anLookupSizeMinusOne[0]);
        int gy = std::clamp((int)sy, 0, table->m_anLookupSizeMinusOne[1]);
        int gz = std::clamp((int)sz, 0, table->m_anLookupSizeMinusOne[2]);

        float fx, fy, fz;
        if (gx == table->m_anLookupSizeMinusOne[0])
        {
            fx = 0.0f;
            --gx;
        }
        else
            fx = sx - floorf(sx);
        if (gy == table->m_anLookupSizeMinusOne[1])
        {
            fy = 0.0f;
            --gy;
        }
        else
            fy = sy - floorf(sy);
        if (gz == table->m_anLookupSizeMinusOne[2])
        {
            fz = 0.0f;
            --gz;
        }
        else
            fz = sz - floorf(sz);

        gx = std::max(gx, 0);
        gy = std::max(gy, 0);
        gz = std::max(gz, 0);
        const uint32 nx = table->m_adwLookupSize[0];
        const uint32 nxy = table->m_dwXSizeTimesYSize;

        auto sample = [&](int x, int y, int z) -> LTVector
        {
            const LTRGBCompat &c = table->m_pLookup[static_cast<uint32>(x) +
                                                    static_cast<uint32>(y) * nx +
                                                    static_cast<uint32>(z) * nxy];
            return {c.r / 255.0f, c.g / 255.0f, c.b / 255.0f};
        };

        const LTVector c000 = sample(gx, gy, gz);
        const LTVector c100 = sample(gx + 1, gy, gz);
        const LTVector c010 = sample(gx, gy + 1, gz);
        const LTVector c110 = sample(gx + 1, gy + 1, gz);
        const LTVector c001 = sample(gx, gy, gz + 1);
        const LTVector c101 = sample(gx + 1, gy, gz + 1);
        const LTVector c011 = sample(gx, gy + 1, gz + 1);
        const LTVector c111 = sample(gx + 1, gy + 1, gz + 1);

        const LTVector x00 = c000.Lerp(c100, fx);
        const LTVector x10 = c010.Lerp(c110, fx);
        const LTVector x01 = c001.Lerp(c101, fx);
        const LTVector x11 = c011.Lerp(c111, fx);
        return x00.Lerp(x10, fy).Lerp(x01.Lerp(x11, fy), fz);
    }

    static ModelRenderSetup BuildModelRenderSetup(SceneDesc *scene, ModelInstanceCompat *inst)
    {
        ModelRenderSetup out{};
        out.effectiveFlags = inst->m_Base.m_dwFlags;
        out.hookFlags = 1; // MHF_USETEXTURE
        out.lightAdd = scene->m_vModelLightAdd;
        out.sceneTint = scene->m_vGlobalVertexTint;
        out.objectColor = {
            static_cast<float>(inst->m_Base.m_nColorR),
            static_cast<float>(inst->m_Base.m_nColorG),
            static_cast<float>(inst->m_Base.m_nColorB)};

        if (scene->m_ModelHookFn)
        {
            const LTVector preHookColor = out.objectColor;

            ModelHookData hook{};
            hook.m_pObject = reinterpret_cast<LTObject *>(inst);
            hook.m_dwHookFlags = out.hookFlags;
            hook.m_dwObjectFlags = out.effectiveFlags;
            hook.m_pLightAdd = &out.lightAdd;
            hook.m_pObjectColor = &out.objectColor;
            scene->m_ModelHookFn(&hook, scene->m_pModelHookUser);

            out.hookFlags = hook.m_dwHookFlags;
            out.effectiveFlags = hook.m_dwObjectFlags;
            constexpr float kHookColorEpsilon = 0.01f;
            out.hookColorOverride =
                std::fabs(out.objectColor.x - preHookColor.x) > kHookColorEpsilon ||
                std::fabs(out.objectColor.y - preHookColor.y) > kHookColorEpsilon ||
                std::fabs(out.objectColor.z - preHookColor.z) > kHookColorEpsilon;
        }

        return out;
    }

    static LTVector ObjectPointToWorld(const LTObjectCompat &obj, LTVector local)
    {
        LTVector scaled = local * LTVector{obj.m_vScale.x, obj.m_vScale.y, obj.m_vScale.z};
        LTRotation oq{obj.m_rRot.x, obj.m_rRot.y,
                obj.m_rRot.z, obj.m_rRot.w};
        return oq.Rotate(scaled) + LTVector{obj.m_vPos.x, obj.m_vPos.y, obj.m_vPos.z};
    }

    static LTVector GetModelLightingPoint(SceneDesc *scene, ModelInstanceCompat *inst,
                                          Model *model, LTMatrix *transforms, bool reallyClose)
    {
        LTVector p{inst->m_Base.m_vPos.x, inst->m_Base.m_vPos.y, inst->m_Base.m_vPos.z};

        // Original SetupModelLight samples at the root's first child node when
        // one exists, not blindly at LTObject::m_vPos.
        if (model && model->m_pRootNode &&
            model->m_pRootNode->m_Children.m_pArray &&
            model->m_pRootNode->m_Children.m_dwElements > 0 &&
            transforms)
        {
            ModelNodeCompat *child = model->m_pRootNode->m_Children.m_pArray[0];
            if (child && child->m_wNodeIndex < 96)
            {
                const LTMatrix &m = transforms[child->m_wNodeIndex];
                LTVector nodeLocal{m.m[0][3], m.m[1][3], m.m[2][3]};
                p = ObjectPointToWorld(inst->m_Base, nodeLocal);
            }
        }

        if (reallyClose)
        {
            LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                    scene->m_rRotation.z, scene->m_rRotation.w};
            LTVector rotated = cq.Rotate(p);
            p = rotated + LTVector{scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z};
        }

        return p;
    }

    static LTVector WorldPointToCamera(const SceneDesc *scene, const LTVector &p)
    {
        LTVector rel{p.x - scene->m_vPos.x, p.y - scene->m_vPos.y, p.z - scene->m_vPos.z};
        LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                scene->m_rRotation.z, scene->m_rRotation.w};
        return cq.Conjugate().Rotate(rel);
    }

    static LTVector WorldDirToCamera(const SceneDesc *scene, const LTVector &p)
    {
        LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                scene->m_rRotation.z, scene->m_rRotation.w};
        return cq.Conjugate().Rotate(p).normalize();
    }

    static ModelLighting BuildModelLighting(SceneDesc *scene, ModelInstanceCompat *inst,
                                            Model *model, LTMatrix *transforms,
                                            const ModelRenderSetup &setup)
    {
        ModelLighting out{};
        const LTVector &lightAdd = setup.lightAdd;
        const uint32 effectiveFlags = setup.effectiveFlags;
        const bool reallyClose = (effectiveFlags & FLAG_REALLYCLOSE) != 0;

        out.alpha = inst->m_Base.m_nColorA / 255.0f;
        out.noLight = (effectiveFlags & FLAG_NOLIGHT) != 0;

        if (out.noLight)
        {
            out.ambient = {1.0f, 1.0f, 1.0f};
            return out;
        }

        if (scene->m_nDrawMode == DRAWMODE_OBJECTLIST)
        {
            // Keep lighting and ModelHookData::m_pObjectColor as separate terms.
            // The hook color is applied to the completed model result below/in
            // the fragment shader, so vision-mode tints also modulate direct
            // lighting instead of being washed out by it.
            out.ambient = {1.0f, 1.0f, 1.0f};
            return out;
        }

        const LTVector lightPoint = GetModelLightingPoint(scene, inst, model, transforms, reallyClose);
        LTVector gridAmbient{0.0f, 0.0f, 0.0f};

        MainWorldCompat *mainWorld = nullptr;
        if (scene->m_pRenderContext)
            mainWorld = reinterpret_cast<MainWorldCompat *>(scene->m_pRenderContext->m_pMainWorld);

        if (mainWorld)
            gridAmbient = SampleModelLightTable(&mainWorld->m_LightTable, lightPoint);

        // Stock d3d.ren SetupModelLight keeps SceneDesc::m_vModelLightAdd
        // separate from ordinary model lighting.  0x1000C55A applies the
        // SceneDesc global vertex tint to sampled light-table RGB, while the
        // ModelHookData light-add vector at context+0x850 is added later in the
        // vertex diffuse path (0x100046A9..0x10004718).  Do NOT scene-tint the
        // light-add term and do NOT add it after texturing.
        const LTVector sceneTint = {
            std::clamp(setup.sceneTint.x, 0.0f, 1.0f),
            std::clamp(setup.sceneTint.y, 0.0f, 1.0f),
            std::clamp(setup.sceneTint.z, 0.0f, 1.0f)};
        // Retail keeps the sampled light-table channels in 0..255 space and
        // multiplies them by SceneDesc::m_vGlobalVertexTint. Our sampler is
        // already normalized to 0..1, so there is no additional *2 gain here.
        out.ambient = LTVector(gridAmbient.x * sceneTint.x,
                               gridAmbient.y * sceneTint.y,
                               gridAmbient.z * sceneTint.z).Clamp();
        out.lightAdd = {
            lightAdd.x / 255.0f,
            lightAdd.y / 255.0f,
            lightAdd.z / 255.0f};

        // Original uses RenderStruct global sun values. Occlusion is a separate
        // ray-to-sky stage; until that ray test is wired, preserve the global
        // directional term rather than folding it into ambient.
        if (ModelState().renderStruct)
        {
            // d3d.ren 0x1000C4B5..0x1000C4F3 multiplies the renderer
            // global model-light color by SceneDesc::m_vGlobalVertexTint.
            out.dirColor = LTVector((ModelState().renderStruct->m_vGlobalLightColor.x / 255.0f) * sceneTint.x,
                                    (ModelState().renderStruct->m_vGlobalLightColor.y / 255.0f) * sceneTint.y,
                                    (ModelState().renderStruct->m_vGlobalLightColor.z / 255.0f) * sceneTint.z).Clamp();
            out.dirCamera = WorldDirToCamera(scene, ModelState().renderStruct->m_vGlobalLightDir);
        }

        const float maxScale = std::max(inst->m_Base.m_vScale.x,
                                        std::max(inst->m_Base.m_vScale.y, inst->m_Base.m_vScale.z));
        const float modelRadius = (model ? model->m_fVisRadius : inst->m_Base.m_fRadius) *
                                  std::max(maxScale, 0.001f);

        // Visible dynamic lights: original selects when
        // distance < modelVisRadius + lightRadius, max 16.
        const uint32 dynCount = WorldRenderer::Instance().PVS().GetDynamicLightCount();
        for (uint32 i = 0; i < dynCount && out.dynamicLightCount < out.dynamicLights.size(); ++i)
        {
            DynamicLightCompat *l = WorldRenderer::Instance().PVS().GetDynamicLight(i);
            if (!l || l->m_fLightRadius <= 0.0f)
                continue;

            // LightGroup/LightAnim can leave the source OT_LIGHT in the WorldTree
            // while its baked contribution is switched off. Stock model lighting
            // gates that source with the same LMAnim state.
            if (mainWorld && !WorldRenderer::Instance().Lighting().ModelLightAllowedByLightAnim(
                                 mainWorld, l->m_Base.m_vPos, l->m_fLightRadius))
                continue;

            // Stock d3d.ren excludes OT_LIGHT objects marked ONLYLIGHTWORLD
            // from model/object lighting.  Talon reuses bit 5 by object type.
            if (l->m_Base.m_dwFlags & FLAG_ONLYLIGHTWORLD)
                continue;

            const float dx = lightPoint.x - l->m_Base.m_vPos.x;
            const float dy = lightPoint.y - l->m_Base.m_vPos.y;
            const float dz = lightPoint.z - l->m_Base.m_vPos.z;
            const float sumR = modelRadius + l->m_fLightRadius;
            if (dx * dx + dy * dy + dz * dz >= sumR * sumR)
                continue;

            ModelPointLight ml{};
            ml.cameraPos = WorldPointToCamera(scene, l->m_Base.m_vPos);
            // d3d.ren 0x100100B2..0x1001011A decodes dynamic-light object
            // color around the 127/128 midpoint: (2*channel-255).  Normalizing
            // the bytes directly made every colored OT_LIGHT appear mostly white.
            constexpr float kInv255 = 1.0f / 255.0f;
            ml.color = {
                ((2.0f * float(l->m_Base.m_nColorR) - 255.0f) * kInv255) * sceneTint.x,
                ((2.0f * float(l->m_Base.m_nColorG) - 255.0f) * kInv255) * sceneTint.y,
                ((2.0f * float(l->m_Base.m_nColorB) - 255.0f) * kInv255) * sceneTint.z};
            ml.radius = l->m_fLightRadius;
            ml.closeHack = !reallyClose;
            out.dynamicLights[out.dynamicLightCount++] = ml;
        }

        // Static lights come from the WorldTree NOA_Lights array exactly as the
        // original SetupModelLight box query does.  Switchable LightGroup sources
        // are removed from that unconditional list in World3D and reintroduced
        // here from the live LMAnim state, which is the only representation that
        // actually knows whether the group is ON or OFF.
        if (mainWorld)
        {
            ModelLightAnimInfo animated[16]{};
            const uint32 animatedCount = WorldRenderer::Instance().Lighting().QueryActiveModelLightAnims(
                mainWorld, lightPoint, modelRadius, animated, 16);

            for (uint32 i = 0; i < animatedCount && out.staticLightCount < out.staticLights.size(); ++i)
            {
                const auto &l = animated[i];
                if (l.radius <= 0.0f)
                    continue;

                ModelStaticLight sl{};
                sl.cameraPos = WorldPointToCamera(scene, l.pos);
                sl.innerColor = {(l.color.x / 255.0f) * sceneTint.x,
                                 (l.color.y / 255.0f) * sceneTint.y,
                                 (l.color.z / 255.0f) * sceneTint.z};
                sl.outerColor = sl.innerColor;
                sl.cameraDir = {0.0f, 0.0f, 1.0f};
                sl.radius = l.radius;
                sl.fov = 0.0f;
                sl.point = true;
                sl.closeHack = !reallyClose;
                out.staticLights[out.staticLightCount++] = sl;
            }

            ModelStaticLightInfo raw[16]{};
            const uint32 staticCount = WorldRenderer::Instance().Lighting().QueryStaticModelLights(
                mainWorld, lightPoint, modelRadius, raw, 16);

            for (uint32 i = 0; i < staticCount && out.staticLightCount < out.staticLights.size(); ++i)
            {
                const auto &l = raw[i];
                if (l.radius <= 0.0f)
                    continue;

                ModelStaticLight sl{};
                sl.cameraPos = WorldPointToCamera(scene, l.pos);
                sl.innerColor = {(l.innerColor.x / 255.0f) * sceneTint.x,
                                 (l.innerColor.y / 255.0f) * sceneTint.y,
                                 (l.innerColor.z / 255.0f) * sceneTint.z};
                sl.outerColor = {(l.outerColor.x / 255.0f) * sceneTint.x,
                                 (l.outerColor.y / 255.0f) * sceneTint.y,
                                 (l.outerColor.z / 255.0f) * sceneTint.z};
                sl.cameraDir = WorldDirToCamera(scene, l.dir);
                sl.radius = l.radius;
                sl.fov = l.fov;
                sl.point = (l.fov <= -1.0f || l.fov >= 1.0f || l.fov == 0.0f);
                sl.closeHack = !reallyClose;
                out.staticLights[out.staticLightCount++] = sl;
            }
        }

        static int logBudget = 64;
        if (LogIsSessionEnabled() && ((logBudget > 0 && logBudget--)))
        {
            LOG_SESSION("MODEL ORIGINAL-LIGHT inst=%p rc=%d point=(%.2f %.2f %.2f) grid=(%.3f %.3f %.3f) diffuse=(%.3f %.3f %.3f) dyn=%u static=%u internal=%08X",
                        inst, reallyClose ? 1 : 0,
                        lightPoint.x, lightPoint.y, lightPoint.z,
                        gridAmbient.x, gridAmbient.y, gridAmbient.z,
                        out.ambient.x, out.ambient.y, out.ambient.z,
                        static_cast<unsigned>(out.dynamicLightCount),
                        static_cast<unsigned>(out.staticLightCount),
                        inst->m_Base.m_dwInternalFlags);
        }

        return out;
    }

    static uint32 SelectModelPieceLOD(const Model *model, const ModelPiece *piece, float dist)
    {
        if (!model || !piece || !piece->m_LODs.m_dwElements)
            return 0;

        int nLOD = 0;
        const int nNumLODS = static_cast<int>(piece->m_LODs.m_dwElements);

        if (dist > 0.0f)
        {
            nLOD = nNumLODS;

            for (int i = 1; i < nNumLODS; i++)
            {
                if (model->m_LODInfos.m_pArray &&
                    static_cast<uint32>(nLOD - 1) < model->m_LODInfos.m_dwElements &&
                    dist < model->m_LODInfos.m_pArray[nLOD - 1].m_fDist)
                {
                    nLOD = i - 1;
                    break;
                }
            }
        }

        return static_cast<uint32>(std::clamp(nLOD, 0, nNumLODS));
    }

    struct ModelPieceSource
    {
        ModelVert *verts = nullptr;
        uint32 vertCount = 0;
        ModelTri *tris = nullptr;
        uint32 triCount = 0;
    };

    static ModelPieceSource GetModelPieceSource(ModelPiece *piece, uint32 lodIndex)
    {
        ModelPieceSource src{};
        if (!piece)
            return src;

        if (lodIndex == 0)
        {
            src.verts = piece->m_Verts.m_pArray;
            src.vertCount = piece->m_Verts.m_dwElements;
            src.tris = piece->m_Tris.m_pArray;
            src.triCount = piece->m_Tris.m_dwElements;
            return src;
        }

        const uint32 li = lodIndex - 1;
        if (!piece->m_LODs.m_pArray || li >= piece->m_LODs.m_dwElements)
            return src;

        PieceLOD &lod = piece->m_LODs.m_pArray[li];
        src.verts = lod.m_Verts.m_pArray;
        src.vertCount = lod.m_Verts.m_dwElements;
        src.tris = lod.m_Tris.m_pArray;
        src.triCount = lod.m_Tris.m_dwElements;
        return src;
    }

    static void LogModelBatchFallback(const Model *model, const char *reason)
    {
        if (!LogIsSessionEnabled())
            return;
        static int budget = 48;
        if (budget-- <= 0)
            return;
        LOG_SESSION("MODEL-GPU-BATCH fallback model='%s' reason=%s",
                    model && model->m_szFilename ? model->m_szFilename : "", reason ? reason : "unknown");
    }

    struct ModelBatchSkinSlot
    {
        SharedTexture *shared = nullptr;
        Texture *skin = nullptr;
        SharedTexture *detailShared = nullptr;
        Texture *detail = nullptr;
        ModelMaterialMode material{};
        bool detailEnabled = false;
    };

    static bool TryRenderModelGpuBatch(SceneDesc *scene, ModelInstanceCompat *inst,
                                       Model *model, LTMatrix *transforms,
                                       const ModelLighting &lighting,
                                       const ModelRenderSetup &renderSetup,
                                       bool reallyClose, bool forceTranslucentDepthOff,
                                       float modelDistance)
    {
        if (!ModelState().batchShader || !g_vaoModelBatch || !g_modelNodeSsbo ||
            !g_modelLightSsbo || !g_modelSkinStateSsbo)
            return false;

        // OBJECTLIST menu models are commonly FLAG_REALLYCLOSE, but unlike
        // first-person ReallyClose geometry they still use normal model RenderStyle
        // piece state.  The full-GPU batch path currently has one rasterizer state
        // for the whole model and therefore bypasses per-piece D3DRS_CULLMODE.
        // Keep these very small menu scenes on the legacy piece path until batch
        // commands carry/split CullMode as well.  This is correctness-first and
        // has negligible performance impact outside menus.
        if (reallyClose && scene->m_nDrawMode == DRAWMODE_OBJECTLIST)
            return false;

        const uint32 nodeCount = model->m_Nodes.m_dwElements;

        // Leaving alpha<255 multi-piece models on the legacy path was expensive:
        // each piece was CPU expanded/skinned and uploaded every frame.  Outdoor
        // scenes can contain dozens of these objects.  Let them use cached GPU
        // geometry + node-palette skinning exactly like opaque/chromakey models.
        // Actual incompatible per-material Talon StateChange cases are still
        // rejected below and retain the proven legacy renderer.

        if (nodeCount > MAX_MODEL_BATCH_NODES)
        {
            LogModelBatchFallback(model, "node palette exceeds GPU batch limit");
            return false;
        }
        // The GPU light buffer is deliberately bounded. Extremely light-heavy
        // scenes are clamped to the first MAX_MODEL_BATCH_LIGHTS entries rather
        // than forcing the entire animated model back through CPU skinning.

        const ModelTextureConsoleState &modelTexCV = GetModelTextureConsoleState();
        std::array<ModelBatchSkinSlot, MODEL_BATCH_SKIN_SLOTS> slots{};
        std::array<ModelBatchSkinStateGPU, MODEL_BATCH_SKIN_SLOTS> skinGpu{};

        for (uint32 si = 0; si < MODEL_BATCH_SKIN_SLOTS; ++si)
        {
            ModelBatchSkinSlot &slot = slots[si];
            if ((renderSetup.hookFlags & 1u) && inst->m_pSkins[si])
            {
                slot.shared = reinterpret_cast<SharedTexture *>(inst->m_pSkins[si]);
                slot.skin = TextureManager::Instance().GetOrEnsure(slot.shared);
            }
            slot.material = BuildModelMaterial(inst, renderSetup, slot.shared, slot.skin);
            if (!slot.skin || !slot.skin->texture)
                slot.material.mode |= MMD_NO_TEXTURE;

            // Talon material StateChange can carry fixed-function raster/depth/blend
            // state (ZENABLE/ZWRITEENABLE/ZFUNC/CULLMODE and exact SRC/DEST blend).
            // The one-draw GPU model path currently has only model-wide raster state
            // and therefore cannot reproduce those per-material overrides exactly.
            // Special-effect shells/aura models depend on this state for visibility
            // through/around the base actor.  Route only these uncommon materials to
            // the legacy per-piece renderer, which applies the decoded D3D state
            // verbatim.  Normal opaque animated models remain GPU-batched.
            if (slot.material.stateBlendOverride ||
                slot.material.stateZEnableOverride ||
                slot.material.stateZWriteOverride ||
                slot.material.stateZFuncOverride ||
                slot.material.stateCullOverride)
            {
                LogModelBatchFallback(model, "material carries Talon raster/depth/blend StateChange");
                return false;
            }

            // Stock Talon d3d.ren model path (0x10024630..0x10024661) does NOT
            // classify the linked skin texture by SharedTexture::m_eTexType.  For
            // models, a linked texture is the model detail stage.  Reusing the
            // world-texture DETAIL/ENVMAP classification here darkens ordinary
            // model lighting because it incorrectly multiplies the lit result by
            // an environment sample.
            if (slot.shared && modelTexCV.detailTextures != 0.0f)
            {
                auto *st = reinterpret_cast<SharedTextureCompat *>(slot.shared);
                if (st->m_pLinkedTexture)
                {
                    slot.detailShared = reinterpret_cast<SharedTexture *>(st->m_pLinkedTexture);
                    slot.detail = TextureManager::Instance().GetOrEnsure(slot.detailShared);
                    slot.detailEnabled = slot.detail && slot.detail->texture;
                }
            }

            ModelBatchSkinStateGPU &gpu = skinGpu[si];
            gpu.data0[0] = static_cast<float>(slot.material.mode);
            gpu.data0[1] = slot.material.alphaRef;
            gpu.data0[2] = slot.detailEnabled ? 1.0f : 0.0f;
            gpu.data0[3] = modelTexCV.modelDetailTextureScale;
            gpu.data1[0] = modelTexCV.detailTextureAdd != 0.0f ? 1.0f : 0.0f;
            gpu.data1[1] = slot.material.modeColor[0];
            gpu.data1[2] = slot.material.modeColor[1];
            gpu.data1[3] = slot.material.modeColor[2];
        }

        bool haveBlend = false;
        bool mixedBlend = false;
        ModelBlendMode commonBlend = ModelBlendMode::Opaque;
        // Reuse piece-selection scratch storage across models.  Outdoor scenes can
        // submit 100+ ABC instances, so allocating this vector for every model was
        // measurable CPU allocator churn on the hot path.
        thread_local std::vector<ModelPieceSource> selectedGeom;
        selectedGeom.clear();
        selectedGeom.resize(model->m_Pieces.m_dwElements);
        uint32 visiblePieces = 0;

        // First pass is metadata only: select LODs and validate material compatibility.
        // The heavy triangle/weight expansion is cached below and no longer happens
        // every animated frame.
        uint64_t geometryKey = 1469598103934665603ull;
        auto hash64 = [&](uint64_t v)
        {
            geometryKey ^= v;
            geometryKey *= 1099511628211ull;
        };
        hash64(static_cast<uint64_t>(reinterpret_cast<uintptr_t>(model)));
        hash64(static_cast<uint64_t>(inst->m_adwHiddenPiece[0]));

        for (uint32 pi = 0; pi < model->m_Pieces.m_dwElements; ++pi)
        {
            if (pi < 32 && (inst->m_adwHiddenPiece[0] & (1u << pi)))
            {
                hash64(0x80000000ull | pi);
                continue;
            }
            ModelPiece *piece = model->m_Pieces.m_pArray[pi];
            if (!piece)
            {
                hash64(0x40000000ull | pi);
                continue;
            }
            if (piece->m_wTextureIndex >= MODEL_BATCH_SKIN_SLOTS)
            {
                LogModelBatchFallback(model, "piece references skin slot outside Talon 0..3 range");
                return false;
            }

            const uint32 lodIndex = SelectModelPieceLOD(model, piece, modelDistance);
            ModelPieceSource geom = GetModelPieceSource(piece, lodIndex);
            selectedGeom[pi] = geom;
            hash64((static_cast<uint64_t>(pi) << 32) | lodIndex);
            hash64(static_cast<uint64_t>(reinterpret_cast<uintptr_t>(geom.verts)));
            hash64(static_cast<uint64_t>(reinterpret_cast<uintptr_t>(geom.tris)));
            hash64((static_cast<uint64_t>(geom.vertCount) << 32) | geom.triCount);
            if (!geom.verts || !geom.tris || !geom.vertCount || !geom.triCount)
                continue;

            const ModelBlendMode pieceBlend = slots[piece->m_wTextureIndex].material.blend;
            if (!haveBlend)
            {
                commonBlend = pieceBlend;
                haveBlend = true;
            }
            else if (pieceBlend != commonBlend)
            {
                // Fixed-function blend/depth state cannot change inside one GL
                // draw. Keep the complete model GPU-resident and split only at
                // material-state boundaries later; animation/skinning stays GPU.
                mixedBlend = true;
            }
            ++visiblePieces;
        }

        if (!haveBlend || visiblePieces == 0)
            return false;

        ModelGpuGeometryCache *cached = nullptr;
        auto cacheIt = g_modelGpuGeometryCache.find(geometryKey);
        if (cacheIt != g_modelGpuGeometryCache.end())
        {
            cached = &cacheIt->second;
        }
        else
        {
            std::vector<ModelBatchVertexGPU> vertices;
            vertices.reserve(std::min<size_t>(model->m_nTotalTris * 3u, MAX_MODEL_BATCH_VERTICES));
            std::vector<GLint> pieceFirst(model->m_Pieces.m_dwElements, -1);
            std::vector<GLsizei> pieceCount(model->m_Pieces.m_dwElements, 0);
            uint32 maxReferencedNode = 0;
            bool hasWeightedVertices = false;

            for (uint32 pi = 0; pi < model->m_Pieces.m_dwElements; ++pi)
            {
                ModelPiece *piece = model->m_Pieces.m_pArray[pi];
                const ModelPieceSource &geom = selectedGeom[pi];
                if (!piece || !geom.verts || !geom.tris || !geom.vertCount || !geom.triCount)
                    continue;

                const size_t worstNeeded = vertices.size() + static_cast<size_t>(geom.triCount) * 3u;
                if (worstNeeded > MAX_MODEL_BATCH_VERTICES)
                {
                    LogModelBatchFallback(model, "cached triangle stream exceeds GPU vertex limit");
                    return false;
                }

                const float skinIndex = static_cast<float>(piece->m_wTextureIndex);
                pieceFirst[pi] = static_cast<GLint>(vertices.size());
                for (uint32 ti = 0; ti < geom.triCount; ++ti)
                {
                    const ModelTri &tri = geom.tris[ti];
                    for (int c = 0; c < 3; ++c)
                    {
                        const uint16 vi = tri.m_awIndices[c];
                        if (vi >= geom.vertCount)
                            continue;
                        const ModelVert &mv = geom.verts[vi];
                        ModelBatchVertexGPU out{};
                        out.pos.x = mv.m_vVec.x;
                        out.pos.y = mv.m_vVec.y;
                        out.pos.z = mv.m_vVec.z;
                        out.normal.x = mv.m_vNormal.x;
                        out.normal.y = mv.m_vNormal.y;
                        out.normal.z = mv.m_vNormal.z;
                        out.uv.x = tri.m_UVs[c].m_fU;
                        out.uv.y = tri.m_UVs[c].m_fV;
                        out.skinIndex = skinIndex;

                        uint16 wc = 0;
                        if (transforms && mv.m_pWeights && mv.m_wWeights)
                            wc = std::min<uint16>(mv.m_wWeights, 4);
                        for (uint16 wi = 0; wi < wc; ++wi)
                        {
                            const uint32 node = mv.m_pWeights[wi].m_dwNode;
                            if (node >= nodeCount)
                            {
                                LogModelBatchFallback(model, "vertex weight references invalid node");
                                return false;
                            }
                            for (int k = 0; k < 4; ++k)
                                out.weightVec[wi][k] = mv.m_pWeights[wi].m_afVec[k];
                            out.nodeIndex[wi] = static_cast<float>(node);
                            maxReferencedNode = std::max(maxReferencedNode, node);
                        }
                        out.weightCount = static_cast<float>(wc);
                        hasWeightedVertices |= (wc != 0);
                        vertices.push_back(out);
                    }
                }
                pieceCount[pi] = static_cast<GLsizei>(vertices.size() - static_cast<size_t>(pieceFirst[pi]));
            }

            if (vertices.empty())
                return false;
            if (hasWeightedVertices && (!transforms || nodeCount == 0))
            {
                LogModelBatchFallback(model, "weighted model has no node transform palette");
                return false;
            }

            ModelGpuGeometryCache entry{};
            glf.CreateBuffers(1, &entry.vbo);
            if (!entry.vbo)
                return false;
            glf.NamedBufferStorage(entry.vbo,
                                   static_cast<GLsizeiptr>(vertices.size() * sizeof(ModelBatchVertexGPU)),
                                   vertices.data(), 0);
            entry.vertexCount = static_cast<GLsizei>(vertices.size());
            entry.visiblePieces = visiblePieces;
            entry.maxReferencedNode = maxReferencedNode;
            entry.hasWeightedVertices = hasWeightedVertices;
            entry.pieceFirst = std::move(pieceFirst);
            entry.pieceCount = std::move(pieceCount);
            auto ins = g_modelGpuGeometryCache.emplace(geometryKey, entry);
            cached = &ins.first->second;

            static int cacheLogBudget = 64;
            if (LogIsSessionEnabled() && ((cacheLogBudget > 0 && cacheLogBudget--)))
                LOG_SESSION("MODEL-GPU-CACHE build model='%s' key=%016llX pieces=%u verts=%d tris=%d lodVariants=%zu",
                            model->m_szFilename ? model->m_szFilename : "",
                            static_cast<unsigned long long>(geometryKey), visiblePieces,
                            cached->vertexCount, cached->vertexCount / 3, g_modelGpuGeometryCache.size());
        }

        if (!cached || !cached->vbo || cached->vertexCount <= 0)
            return false;
        if (cached->hasWeightedVertices && (!transforms || nodeCount == 0))
            return false;

        // Convert Talon's CPU light lists to one std430 array.  The shader uses
        // the same attenuation/cone equations as the previous CPU vertex loop.
        std::array<ModelBatchLightGPU, 32> gpuLights{};
        size_t gpuLightCount = 0;
        for (uint32 li = 0; li < lighting.dynamicLightCount && gpuLightCount < gpuLights.size(); ++li)
        {
            const ModelPointLight &l = lighting.dynamicLights[li];
            ModelBatchLightGPU &g = gpuLights[gpuLightCount++];
            g.posRadius[0] = l.cameraPos.x;
            g.posRadius[1] = l.cameraPos.y;
            g.posRadius[2] = l.cameraPos.z;
            g.posRadius[3] = l.radius;
            g.innerType[0] = l.color.x;
            g.innerType[1] = l.color.y;
            g.innerType[2] = l.color.z;
            g.innerType[3] = 0.0f;
            g.outerClose[3] = l.closeHack ? 1.0f : 0.0f;
        }
        for (uint32 li = 0; li < lighting.staticLightCount && gpuLightCount < gpuLights.size(); ++li)
        {
            const ModelStaticLight &l = lighting.staticLights[li];
            ModelBatchLightGPU &g = gpuLights[gpuLightCount++];
            g.posRadius[0] = l.cameraPos.x;
            g.posRadius[1] = l.cameraPos.y;
            g.posRadius[2] = l.cameraPos.z;
            g.posRadius[3] = l.radius;
            g.innerType[0] = l.innerColor.x;
            g.innerType[1] = l.innerColor.y;
            g.innerType[2] = l.innerColor.z;
            g.innerType[3] = l.point ? 0.0f : 1.0f;
            g.dirFov[0] = l.cameraDir.x;
            g.dirFov[1] = l.cameraDir.y;
            g.dirFov[2] = l.cameraDir.z;
            g.dirFov[3] = l.fov;
            g.outerClose[0] = l.outerColor.x;
            g.outerClose[1] = l.outerColor.y;
            g.outerClose[2] = l.outerColor.z;
            g.outerClose[3] = l.closeHack ? 1.0f : 0.0f;
        }

        SharedTexture *envShared = nullptr;
        Texture *envTex = nullptr;
        const bool envAll = (modelTexCV.envMapAll != 0.0f);
        const bool envObject = ((renderSetup.effectiveFlags & FLAG_ENVIRONMENTMAP) != 0u);
        const bool modelEnvRequested = envAll || (envObject && modelTexCV.envMapEnable != 0.0f);
        if (modelEnvRequested && ModelState().renderStruct && ModelState().renderStruct->m_pEnvMapTexture)
        {
            envShared = ModelState().renderStruct->m_pEnvMapTexture;
            envTex = TextureManager::Instance().GetOrEnsure(envShared);
            if (!envTex || !envTex->texture)
            {
                static std::unordered_set<uintptr_t> s_failedBatchEnv;
                const uintptr_t key = reinterpret_cast<uintptr_t>(envShared);
                if (LogIsSessionEnabled() && (s_failedBatchEnv.size() < 32 && s_failedBatchEnv.insert(key).second))
                    LOG_SESSION("TALON-MODEL-ENVMAP unresolved batch env=%p flags=%08X envAll=%d envEnable=%d",
                                envShared, renderSetup.effectiveFlags, envAll ? 1 : 0, modelTexCV.envMapEnable != 0.0f ? 1 : 0);
                envTex = nullptr;
            }
        }

        // All validation is complete.  From here on the function commits to the
        // batch path and leaves later object renderers to bind their own pipeline.
        ModelState().batchShader->Use();
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);
        GLStateDisable(GL_CULL_FACE);
        ModelMaterialMode batchMaterial{};
        batchMaterial.blend = commonBlend;
        if (!mixedBlend)
            ApplyModelBlend(batchMaterial);
        if (forceTranslucentDepthOff)
            GLStateDepthMask(GL_FALSE);

        const bool usePvReallyCloseProjection = reallyClose && scene->m_nDrawMode != DRAWMODE_OBJECTLIST;
        float tanHalfX = 0.0f, tanHalfY = 0.0f, nearZ = 1.0f, farZ = scene->m_fFarZ;
        if (usePvReallyCloseProjection)
        {
            const int vpW = std::max(1, scene->m_rcViewport.m_nRight - scene->m_rcViewport.m_nLeft);
            const int vpH = std::max(1, scene->m_rcViewport.m_nBottom - scene->m_rcViewport.m_nTop);
            const float aspect = static_cast<float>(vpW) / static_cast<float>(vpH);
            constexpr float kPvFovY = 75.0f * 3.14159265358979323846f / 180.0f;
            tanHalfY = std::tan(kPvFovY * 0.5f);
            tanHalfX = tanHalfY * aspect;
            nearZ = 0.1f;
            farZ = 7.0f;
        }
        else
        {
            tanHalfX = std::tan(std::max(0.01f, scene->m_fFovX * 0.5f));
            tanHalfY = std::tan(std::max(0.01f, scene->m_fFovY * 0.5f));
            nearZ = reallyClose ? 0.01f : 1.0f;
            farZ = std::max(nearZ + 1.0f, scene->m_fFarZ);
        }
        FrameConstants::Instance().Apply(scene, tanHalfX, tanHalfY, nearZ, farZ);

        LTVector presentationPos;
        LTRotation presentationRot;
        GetPresentationObjectPose(scene, inst->m_Base, presentationPos, presentationRot);
        GLUniform3f(g_uBatchObjPos, presentationPos.x, presentationPos.y, presentationPos.z);
        GLUniform3f(g_uBatchObjScale, inst->m_Base.m_vScale.x, inst->m_Base.m_vScale.y, inst->m_Base.m_vScale.z);
        GLUniform4f(g_uBatchObjQuat, presentationRot.x, presentationRot.y, presentationRot.z, presentationRot.w);
        GLUniform1i(g_uBatchReallyClose, (inst->m_Base.m_dwFlags & FLAG_REALLYCLOSE) ? 1 : 0);
        GLUniform1i(g_uBatchNodeCount, static_cast<int>(nodeCount));

        GLUniform3f(g_uBatchAmbient, lighting.ambient.x, lighting.ambient.y, lighting.ambient.z);
        GLUniform3f(g_uBatchHookColor,
                    std::clamp(renderSetup.objectColor.x / 255.0f, 0.0f, 1.0f),
                    std::clamp(renderSetup.objectColor.y / 255.0f, 0.0f, 1.0f),
                    std::clamp(renderSetup.objectColor.z / 255.0f, 0.0f, 1.0f));

        const bool applySceneTint = !renderSetup.hookColorOverride;
        GLUniform3f(g_uBatchSceneTint,
                    applySceneTint ? std::clamp(renderSetup.sceneTint.x, 0.0f, 1.0f) : 1.0f,
                    applySceneTint ? std::clamp(renderSetup.sceneTint.y, 0.0f, 1.0f) : 1.0f,
                    applySceneTint ? std::clamp(renderSetup.sceneTint.z, 0.0f, 1.0f) : 1.0f);
        GLUniform3f(g_uBatchLightAdd, lighting.lightAdd.x, lighting.lightAdd.y, lighting.lightAdd.z);
        GLUniform3f(g_uBatchDirColor, lighting.dirColor.x, lighting.dirColor.y, lighting.dirColor.z);
        GLUniform3f(g_uBatchDirCamera, lighting.dirCamera.x, lighting.dirCamera.y, lighting.dirCamera.z);
        GLUniform1f(g_uBatchAlpha, lighting.alpha);
        GLUniform1i(g_uBatchLightCount, static_cast<int>(gpuLightCount));

        // Gameplay world-space ABCs follow the active scene fog.  ReallyClose models
        // participate during normal gameplay (for underwater/scene fog), while
        // menu/object-list ReallyClose models remain unfogged.
        const bool allowReallyCloseFog = !reallyClose || scene->m_nDrawMode == DRAWMODE_NORMAL;
        const bool worldSpaceGameplayModel = !reallyClose && scene->m_nDrawMode == DRAWMODE_NORMAL;
        const bool modelFog = g_fogState.enabled && allowReallyCloseFog &&
                              (worldSpaceGameplayModel || ((inst->m_Base.m_dwFlags & FLAG_FOGDISABLE) == 0));
        GLUniform1i(g_uBatchFogEnabled, modelFog ? 1 : 0);
        ApplyModelVFogUniforms(g_uBatchVFogEnabled, g_uBatchVFogMinY, g_uBatchVFogMaxY, g_uBatchVFogMinYVal, g_uBatchVFogMaxYVal, g_uBatchVFogDensity, g_uBatchVFogMax);
        GLUniform1i(g_uBatchFogAdditive, commonBlend == ModelBlendMode::Add ? 1 : 0);

        // Model environment mapping is reflection-coordinate driven only.
        // Do not feed Talon's global EnvPanSpeed into ABC/model envmaps: that
        // makes the reflection texture crawl across a stationary player model.
        // World envmap/panning behavior remains handled by the world renderer.
        GLUniform1i(g_uBatchEnvPass, envTex ? 1 : 0);
        GLUniform4f(g_uBatchEnvParams, modelTexCV.envScale, 0.0f, 0.0f, 0.0f);
        GLUniform1i(g_uBatchBlendMode, static_cast<int>(commonBlend));

        ModelFrameStreamRanges streamRanges{};
        const bool streamed = UploadModelFrameState(
            transforms, nodeCount,
            gpuLightCount ? gpuLights.data() : nullptr, gpuLightCount,
            skinGpu.data(), skinGpu.size(), streamRanges);

        if (streamed)
        {
            if (streamRanges.nodeBytes > 0)
                glf.BindBufferRange(GL_SHADER_STORAGE_BUFFER_, 0, g_modelFrameSsbo, streamRanges.nodeOffset, streamRanges.nodeBytes);
            else
                glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 0, g_modelNodeSsbo);
            if (streamRanges.lightBytes > 0)
                glf.BindBufferRange(GL_SHADER_STORAGE_BUFFER_, 1, g_modelFrameSsbo, streamRanges.lightOffset, streamRanges.lightBytes);
            else
                glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 1, g_modelLightSsbo);
            glf.BindBufferRange(GL_SHADER_STORAGE_BUFFER_, 2, g_modelFrameSsbo, streamRanges.skinOffset, streamRanges.skinBytes);
        }
        else
        {
            if (transforms && nodeCount)
                GLTrackedModelNamedBufferSubData(g_modelNodeSsbo, 0,
                                                 static_cast<GLsizeiptr>(nodeCount * sizeof(LTMatrix)), transforms, GLModelUploadKind::Nodes);
            if (gpuLightCount)
                GLTrackedModelNamedBufferSubData(g_modelLightSsbo, 0,
                                                 static_cast<GLsizeiptr>(gpuLightCount * sizeof(ModelBatchLightGPU)), gpuLights.data(), GLModelUploadKind::Lights);
            GLTrackedModelNamedBufferSubData(g_modelSkinStateSsbo, 0,
                                             static_cast<GLsizeiptr>(skinGpu.size() * sizeof(ModelBatchSkinStateGPU)), skinGpu.data(), GLModelUploadKind::SkinState);
            glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 0, g_modelNodeSsbo);
            glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 1, g_modelLightSsbo);
            glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 2, g_modelSkinStateSsbo);
        }
        for (uint32 si = 0; si < MODEL_BATCH_SKIN_SLOTS; ++si)
        {
            GLStateBindTextureUnit(si, slots[si].skin ? slots[si].skin->texture : 0);
            GLStateBindTextureUnit(4u + si, slots[si].detailEnabled ? slots[si].detail->texture : 0);
        }
        GLStateBindTextureUnit(8, envTex ? envTex->texture : 0);

        // Geometry/weights live in immutable GPU storage; per-frame animation is
        // only the node palette + lighting/material state update. Most models are
        // one draw. Mixed fixed-function blend states are emitted as contiguous
        // GPU ranges without ever CPU-skinning the model.
        glf.VertexArrayVertexBuffer(g_vaoModelBatch, 0, cached->vbo, 0, sizeof(ModelBatchVertexGPU));
        GLStateBindVertexArray(g_vaoModelBatch);

        uint32 gpuDrawCalls = 0;
        if (!mixedBlend)
        {
            batchMaterial.blend = commonBlend;
            ApplyModelBlend(batchMaterial);
            if (forceTranslucentDepthOff)
                GLStateDepthMask(GL_FALSE);
            GLUniform1i(g_uBatchBlendMode, static_cast<int>(commonBlend));
            GLUniform1i(g_uBatchFogAdditive, commonBlend == ModelBlendMode::Add ? 1 : 0);
            glf.DrawArrays(GL_TRIANGLES_, 0, cached->vertexCount);
            gpuDrawCalls = 1;
        }
        else
        {
            GLint runFirst = -1;
            GLsizei runCount = 0;
            ModelBlendMode runBlend = ModelBlendMode::Opaque;
            auto flushRun = [&]()
            {
                if (runFirst < 0 || runCount <= 0)
                    return;
                batchMaterial.blend = runBlend;
                ApplyModelBlend(batchMaterial);
                if (forceTranslucentDepthOff)
                    GLStateDepthMask(GL_FALSE);
                GLUniform1i(g_uBatchBlendMode, static_cast<int>(runBlend));
                GLUniform1i(g_uBatchFogAdditive, runBlend == ModelBlendMode::Add ? 1 : 0);
                glf.DrawArrays(GL_TRIANGLES_, runFirst, runCount);
                ++gpuDrawCalls;
                runFirst = -1;
                runCount = 0;
            };

            for (uint32 pi = 0; pi < model->m_Pieces.m_dwElements; ++pi)
            {
                if (pi >= cached->pieceFirst.size() || pi >= cached->pieceCount.size())
                    break;
                const GLint first = cached->pieceFirst[pi];
                const GLsizei count = cached->pieceCount[pi];
                ModelPiece *piece = model->m_Pieces.m_pArray[pi];
                if (!piece || first < 0 || count <= 0)
                    continue;
                const ModelBlendMode b = slots[piece->m_wTextureIndex].material.blend;
                if (runFirst < 0)
                {
                    runFirst = first;
                    runCount = count;
                    runBlend = b;
                }
                else if (b == runBlend && first == runFirst + runCount)
                    runCount += count;
                else
                {
                    flushRun();
                    runFirst = first;
                    runCount = count;
                    runBlend = b;
                }
            }
            flushRun();
        }

        g_triCount += static_cast<uint64_t>(cached->vertexCount / 3);
        ++g_modelCount;

        static int successBudget = 96;
        if (LogIsSessionEnabled() && ((successBudget > 0 && successBudget--)))
            LOG_SESSION("MODEL-GPU-FULL model='%s' pieces=%u verts=%u tris=%u nodes=%u maxNode=%u lights=%u cache=1 drawCalls=%u mixedState=%d",
                        model->m_szFilename ? model->m_szFilename : "", visiblePieces,
                        static_cast<unsigned>(cached->vertexCount), static_cast<unsigned>(cached->vertexCount / 3),
                        nodeCount, cached->maxReferencedNode, static_cast<unsigned>(gpuLightCount), gpuDrawCalls, mixedBlend ? 1 : 0);

        GLStateDepthMask(GL_TRUE);
        return true;
    }

    static bool IsSuspiciousModelForGeometryDiag(const Model *model)
    {
        if (!model || !model->m_szFilename)
            return false;

        const char *n = model->m_szFilename;
        return strstr(n, "characters\\") || strstr(n, "Characters\\") ||
               strstr(n, "loader.abc") || strstr(n, "Loader.abc") ||
               strstr(n, "dropshipanim.abc") || strstr(n, "DropshipAnim.abc");
    }

    static bool RenderModel(SceneDesc *scene, ModelInstanceCompat *inst, bool forceTranslucentDepthOff, bool loadingObjectList)
    {
        if (!StockRenderOptions::Instance().DrawModels())
            return true;
        // AVP2 reuses interface ModelInstance objects and swaps the underlying
        // model pointer. Track both so diagnostics follow the actual ABC being
        // rendered instead of only the first model ever assigned to an instance.
        static std::unordered_map<ModelInstanceCompat *, Model *> s_lastLoggedModel;

        // Object-list rendering interleaves models and sprites. SpriteRenderer::Instance().Render()
        // binds its own shader and blend/depth state, so the model path must
        // explicitly restore its pipeline for every model draw.
        ModelState().modelShader->Use();

        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);
        // Normal-space ABCs must share the exact same depth mapping as the world.
        // Several other Talon callbacks (ReallyClose/canvas/effect paths) can use
        // a compressed depth range.  If that state leaks into a later translucent
        // model, its fragments are pulled toward the camera and incorrectly draw
        // over BSP/WorldModel geometry that is actually in front.
        if ((inst->m_Base.m_dwFlags & FLAG_REALLYCLOSE) == 0u)
            GLStateDepthRange(0.0, 1.0);
        GLStateDepthMask(forceTranslucentDepthOff ? GL_FALSE : GL_TRUE);
        GLStateDisable(GL_BLEND);
        GLStateDisable(GL_CULL_FACE);

        Model *model = GetModelFromInstance(inst);
        if (!model || !model->m_Pieces.m_pArray || model->m_Pieces.m_dwElements == 0)
            return false;

        bool logInstanceIdentity = false;
        if (LogIsSessionEnabled())
        {
            auto prevModelIt = s_lastLoggedModel.find(inst);
            logInstanceIdentity = prevModelIt == s_lastLoggedModel.end() || prevModelIt->second != model;
            if (logInstanceIdentity)
                s_lastLoggedModel[inst] = model;
        }

        if (logInstanceIdentity)
        {
            LOG_SESSION("Model3D NEWINST inst=%p model=%p flags=%08X flags2=%08X type=%u pos=(%.3f,%.3f,%.3f) scale=(%.3f,%.3f,%.3f) objRGBA=(%u,%u,%u,%u) pieces=%u tris=%u",
                        inst, model, inst->m_Base.m_dwFlags, inst->m_Base.m_dwFlags2,
                        static_cast<unsigned>(inst->m_Base.m_nObjectType),
                        inst->m_Base.m_vPos.x, inst->m_Base.m_vPos.y, inst->m_Base.m_vPos.z,
                        inst->m_Base.m_vScale.x, inst->m_Base.m_vScale.y, inst->m_Base.m_vScale.z,
                        static_cast<unsigned>(inst->m_Base.m_nColorR),
                        static_cast<unsigned>(inst->m_Base.m_nColorG),
                        static_cast<unsigned>(inst->m_Base.m_nColorB),
                        static_cast<unsigned>(inst->m_Base.m_nColorA),
                        model->m_Pieces.m_dwElements, model->m_nTotalTris);
            LOG_SESSION("Model3D INSTANCEFLAGS inst=%p model='%s' rawReallyClose=%d hiddenPieces=%08X internal=%08X wtFrame=%08X rigid=%d lodInfos=%u",
                        inst, model->m_szFilename ? model->m_szFilename : "",
                        (inst->m_Base.m_dwFlags & FLAG_REALLYCLOSE) ? 1 : 0,
                        inst->m_adwHiddenPiece[0], inst->m_Base.m_dwInternalFlags,
                        inst->m_Base.m_dwWTFrameCode, model->m_bRigid ? 1 : 0,
                        model->m_LODInfos.m_dwElements);

            if (model->m_LODInfos.m_pArray && model->m_LODInfos.m_dwElements)
            {
                char lodBuf[256]{};
                size_t used = 0;
                for (uint32 li = 0; li < model->m_LODInfos.m_dwElements && used < sizeof(lodBuf) - 24; ++li)
                {
                    int n = snprintf(lodBuf + used, sizeof(lodBuf) - used,
                                     "%s%.2f", li ? "," : "", model->m_LODInfos.m_pArray[li].m_fDist);
                    if (n <= 0)
                        break;
                    used += static_cast<size_t>(n);
                }
                LOG_SESSION("Model3D LODTHRESH model='%s' values=[%s]",
                            model->m_szFilename ? model->m_szFilename : "", lodBuf);
            }
        }

        ModelRenderSetup renderSetup = BuildModelRenderSetup(scene, inst);

        bool usedVisionCarry = false;
        renderSetup.sceneTint = scene->m_vGlobalVertexTint;

        bool visionStateChanged = false;
        bool periodicRC = false;
        if (LogIsSessionEnabled())
        {
            struct VisionDiagState
            {
                uint32 effectiveFlags = 0, hookFlags = 0;
                uint32 rawFlags = 0, rawFlags2 = 0;
                uint8 r = 0, g = 0, b = 0, a = 0;
                int drawMode = 0;
                int hookOverride = 0;
                int forceTrans = 0;
                int fogEnabled = 0;
                float hookR = 0, hookG = 0, hookB = 0;
                float addR = 0, addG = 0, addB = 0;
                float addDirX = 0, addDirY = 0, addDirZ = 0;
                float tintR = 0, tintG = 0, tintB = 0;
                float scaleR = 0, scaleG = 0, scaleB = 0;
            };
            static std::unordered_map<ModelInstanceCompat *, VisionDiagState> s_visionDiag;
            static std::unordered_map<ModelInstanceCompat *, uint64_t> s_visionDiagLastMs;
            VisionDiagState vd{};
            vd.effectiveFlags = renderSetup.effectiveFlags;
            vd.hookFlags = renderSetup.hookFlags;
            vd.rawFlags = inst->m_Base.m_dwFlags;
            vd.rawFlags2 = inst->m_Base.m_dwFlags2;
            vd.r = inst->m_Base.m_nColorR;
            vd.g = inst->m_Base.m_nColorG;
            vd.b = inst->m_Base.m_nColorB;
            vd.a = inst->m_Base.m_nColorA;
            vd.drawMode = scene->m_nDrawMode;
            vd.hookOverride = renderSetup.hookColorOverride ? 1 : 0;
            vd.forceTrans = forceTranslucentDepthOff ? 1 : 0;
            vd.fogEnabled = (g_fogState.enabled && ((renderSetup.effectiveFlags & FLAG_FOGDISABLE) == 0) &&
                             ((renderSetup.effectiveFlags & FLAG_REALLYCLOSE) == 0))
                                ? 1
                                : 0;
            vd.hookR = renderSetup.objectColor.x;
            vd.hookG = renderSetup.objectColor.y;
            vd.hookB = renderSetup.objectColor.z;
            vd.addR = renderSetup.lightAdd.x;
            vd.addG = renderSetup.lightAdd.y;
            vd.addB = renderSetup.lightAdd.z;
            vd.addDirX = scene->m_vModelLightAddDir.x;
            vd.addDirY = scene->m_vModelLightAddDir.y;
            vd.addDirZ = scene->m_vModelLightAddDir.z;
            vd.tintR = renderSetup.sceneTint.x;
            vd.tintG = renderSetup.sceneTint.y;
            vd.tintB = renderSetup.sceneTint.z;
            vd.scaleR = scene->m_vGlobalLightScale.x;
            vd.scaleG = scene->m_vGlobalLightScale.y;
            vd.scaleB = scene->m_vGlobalLightScale.z;
            auto changed = [&](const VisionDiagState &a, const VisionDiagState &b) -> bool
            {
                return memcmp(&a, &b, sizeof(VisionDiagState)) != 0;
            };
            const uint64_t diagNow = GetTickCount64();
            auto prevVD = s_visionDiag.find(inst);
            visionStateChanged = (prevVD == s_visionDiag.end()) || changed(prevVD->second, vd);
            periodicRC = ((renderSetup.effectiveFlags & FLAG_REALLYCLOSE) != 0) &&
                                    (diagNow - s_visionDiagLastMs[inst] >= 1000);
            if (logInstanceIdentity || visionStateChanged || periodicRC)
            {
                s_visionDiag[inst] = vd;
                s_visionDiagLastMs[inst] = diagNow;
                LOG_SESSION("Model3D VISION inst=%p model='%s' drawMode=%d forceTrans=%d rawFlags=%08X flags2=%08X effective=%08X hookFlags=%08X rawRGBA=(%u,%u,%u,%u) hookColor=(%.1f %.1f %.1f) hookColorOverride=%d lightAdd=(%.1f %.1f %.1f) sceneTint=(%.3f %.3f %.3f) effectiveTint=(%.3f %.3f %.3f) carry=%d lightScale=(%.3f %.3f %.3f) modelLightAdd=(%.3f %.3f %.3f) modelLightAddDir=(%.3f %.3f %.3f) reallyClose=%d fog=%d fogDisable=%d noLight=%d hookFn=%p hookUser=%p",
                            inst, model->m_szFilename ? model->m_szFilename : "", scene->m_nDrawMode, forceTranslucentDepthOff ? 1 : 0,
                            inst->m_Base.m_dwFlags, inst->m_Base.m_dwFlags2, renderSetup.effectiveFlags, renderSetup.hookFlags,
                            unsigned(inst->m_Base.m_nColorR), unsigned(inst->m_Base.m_nColorG), unsigned(inst->m_Base.m_nColorB), unsigned(inst->m_Base.m_nColorA),
                            renderSetup.objectColor.x, renderSetup.objectColor.y, renderSetup.objectColor.z, renderSetup.hookColorOverride ? 1 : 0,
                            renderSetup.lightAdd.x, renderSetup.lightAdd.y, renderSetup.lightAdd.z,
                            scene->m_vGlobalVertexTint.x, scene->m_vGlobalVertexTint.y, scene->m_vGlobalVertexTint.z,
                            renderSetup.sceneTint.x, renderSetup.sceneTint.y, renderSetup.sceneTint.z, usedVisionCarry ? 1 : 0,
                            scene->m_vGlobalLightScale.x, scene->m_vGlobalLightScale.y, scene->m_vGlobalLightScale.z,
                            scene->m_vModelLightAdd.x, scene->m_vModelLightAdd.y, scene->m_vModelLightAdd.z,
                            scene->m_vModelLightAddDir.x, scene->m_vModelLightAddDir.y, scene->m_vModelLightAddDir.z,
                            (renderSetup.effectiveFlags & FLAG_REALLYCLOSE) ? 1 : 0, vd.fogEnabled,
                            (renderSetup.effectiveFlags & FLAG_FOGDISABLE) ? 1 : 0, (renderSetup.effectiveFlags & FLAG_NOLIGHT) ? 1 : 0,
                            reinterpret_cast<void *>(scene->m_ModelHookFn), scene->m_pModelHookUser);
            }
        }

        // Respect the effective flags returned by AVP2's model hook.  We were
        // previously using the hook only for light values, then ignoring its
        // flag changes for projection/material behavior.
        if (!(renderSetup.effectiveFlags & FLAG_VISIBLE))
            return false;

        auto *vt = reinterpret_cast<ModelInstanceVTable *>(inst->m_Base.m_pVTable);
        LTMatrix *transforms = nullptr;
        if (vt && vt->GetNodeTransforms)
            transforms = vt->GetNodeTransforms(inst);

        const ModelLighting lighting = BuildModelLighting(scene, inst, model, transforms, renderSetup);
        const bool reallyClose = (renderSetup.effectiveFlags & FLAG_REALLYCLOSE) != 0;

        // The rifle/ammo loading scene changes FarZ while remaining the same
        // OBJECTLIST. Emit enough identity/state information to correlate its model
        // draws directly with RenderDoc's 72/60/60-vertex calls.
        const bool talonLoadingModelDiag = LogIsSessionEnabled() && loadingObjectList;
        if (talonLoadingModelDiag)
        {
            static int loadModelDiagBudget = 96;
            if (LogIsSessionEnabled() && ((loadModelDiagBudget > 0 && loadModelDiagBudget--)))
                LOG_SESSION("TALON-LOADMODEL inst=%p model=%p name='%s' alpha=%u flags=%08X flags2=%08X effective=%08X pieces=%u tris=%u reallyClose=%d",
                            inst, model, model->m_szFilename ? model->m_szFilename : "",
                            static_cast<unsigned>(inst->m_Base.m_nColorA),
                            inst->m_Base.m_dwFlags, inst->m_Base.m_dwFlags2,
                            renderSetup.effectiveFlags, model->m_Pieces.m_dwElements,
                            model->m_nTotalTris, reallyClose ? 1 : 0);
        }

        // Suppress only the local third-person character body. The previous
        // visibility-radius test was wrong: entering ANY prop/character radius
        // made that model disappear. The local body tracks the camera in X/Z,
        // while its origin remains below the eye position.
        if (!reallyClose && scene->m_nDrawMode != DRAWMODE_OBJECTLIST &&
            model->m_szFilename &&
            (strstr(model->m_szFilename, "characters\\") ||
             strstr(model->m_szFilename, "Characters\\")))
        {
            const float dx = inst->m_Base.m_vPos.x - scene->m_vPos.x;
            const float dz = inst->m_Base.m_vPos.z - scene->m_vPos.z;
            const float horiz2 = dx * dx + dz * dz;
            const float dy = fabsf(inst->m_Base.m_vPos.y - scene->m_vPos.y);

            if (horiz2 < 144.0f && dy < 128.0f)
            {
                static int selfCullBudget = 16;
                if (LogIsSessionEnabled() && ((selfCullBudget > 0 && selfCullBudget--)))
                    LOG_SESSION("Model3D LOCAL-PLAYER-BODY CULL inst=%p model='%s' dx=%.2f dy=%.2f dz=%.2f",
                                inst, model->m_szFilename, dx, dy, dz);
                return false;
            }
        }

        // d3d.ren truth for the WORLD/PV path: d3d_SetReallyClose() uses a
        // dedicated 75 degree PV projection with reallyclose_near=0.1 and
        // reallyclose_far=7.0.  Do not apply that tiny PV frustum to explicit
        // OBJECTLIST scenes, though.  AVP2's menus also mark their 3D interface
        // ABCs ReallyClose, but place them at view-relative Z values such as
        // 96/112/160.  The sprite path already keeps scene FarZ for this exact
        // reason.  Using far=7 here submitted every menu model correctly and then
        // clipped it completely before rasterization.
        const bool usePvReallyCloseProjection = reallyClose &&
                                                scene->m_nDrawMode != DRAWMODE_OBJECTLIST;

        if (usePvReallyCloseProjection)
        {
            const int vpW = std::max(1, scene->m_rcViewport.m_nRight - scene->m_rcViewport.m_nLeft);
            const int vpH = std::max(1, scene->m_rcViewport.m_nBottom - scene->m_rcViewport.m_nTop);
            const float aspect = static_cast<float>(vpW) / static_cast<float>(vpH);
            constexpr float kPvFovY = 75.0f * 3.14159265358979323846f / 180.0f;
            const float tanHalfY = std::tan(kPvFovY * 0.5f);
            const float tanHalfX = tanHalfY * aspect;
            FrameConstants::Instance().Apply(scene, tanHalfX, tanHalfY, 0.1f, 7.0f);
        }
        else
        {
            const float nearZ = reallyClose ? 0.01f : 1.0f;
            FrameConstants::Instance().Apply(scene, nearZ, std::max(nearZ + 1.0f, scene->m_fFarZ));

            if (reallyClose && logInstanceIdentity && scene->m_nDrawMode == DRAWMODE_OBJECTLIST)
                LOG_SESSION("Model3D RC-PROJECTION inst=%p path=OBJECTLIST sceneFov=(%.4f,%.4f) near=%.3f far=%.2f",
                            inst, scene->m_fFovX, scene->m_fFovY, nearZ,
                            std::max(nearZ + 1.0f, scene->m_fFarZ));
        }

        bool drewAnything = false;
        std::vector<ModelVertexGPU> vertices;

        float modelDistance = 0.0f;
        float modelRawDistance = 0.0f;
        float modelLodFovScale = 1.0f;
        if (!reallyClose)
        {
            const float dx = inst->m_Base.m_vPos.x - scene->m_vPos.x;
            const float dy = inst->m_Base.m_vPos.y - scene->m_vPos.y;
            const float dz = inst->m_Base.m_vPos.z - scene->m_vPos.z;
            modelRawDistance = std::sqrt(dx * dx + dy * dy + dz * dz);

            // Talon d3d.ren exposes ModelZoomScale alongside ModelLODOffset and
            // the model LOD controls.  Stock LOD therefore is not a pure world-
            // distance test: narrowing the camera FOV for a scope must promote
            // distant models because their projected screen size increases.
            // The authored thresholds are neutral at a 90-degree horizontal FOV
            // (tan(45)=1).  A narrower FOV reduces the effective LOD distance.
            const float halfFovX = std::clamp(scene->m_fFovX * 0.5f, 0.01f, 1.55334306f);
            modelLodFovScale = std::tan(halfFovX);
            modelDistance = modelRawDistance * modelLodFovScale;

            if (LogIsSessionEnabled())
            {
                static int lodFovBudget = 256;
                if (LogIsSessionEnabled() && ((lodFovBudget > 0 && lodFovBudget--)))
                    LOG_SESSION("Model3D LOD-FOV model='%s' rawDist=%.2f fovX=%.5f fovScale=%.5f effectiveDist=%.2f",
                                model->m_szFilename ? model->m_szFilename : "",
                                modelRawDistance, scene->m_fFovX, modelLodFovScale, modelDistance);
            }
        }

        // Common Talon models use one object-level blend state and up to four skin
        // slots.  In that case stream all visible pieces once, upload the current
        // node palette once, and let the vertex shader perform animation/skinning.
        // This collapses N per-piece DrawArrays calls to one model draw.  Mixed
        // blend/state edge cases deliberately fall through to the proven legacy
        // piece path below.
        if (TryRenderModelGpuBatch(scene, inst, model, transforms, lighting, renderSetup,
                                   reallyClose, forceTranslucentDepthOff, modelDistance))
        {
            if (visionStateChanged || periodicRC || logInstanceIdentity)
                LOG_SESSION("Model3D VISION-PATH inst=%p model='%s' path=GPU-FULL reallyClose=%d hookOverride=%d sceneTintApplied=%d",
                            inst, model->m_szFilename ? model->m_szFilename : "", reallyClose ? 1 : 0,
                            renderSetup.hookColorOverride ? 1 : 0, renderSetup.hookColorOverride ? 0 : 1);
            return true;
        }

        if (visionStateChanged || periodicRC || logInstanceIdentity)
            LOG_SESSION("Model3D VISION-PATH inst=%p model='%s' path=LEGACY-PIECE reallyClose=%d hookOverride=%d sceneTintApplied=%d",
                        inst, model->m_szFilename ? model->m_szFilename : "", reallyClose ? 1 : 0,
                        renderSetup.hookColorOverride ? 1 : 0, renderSetup.hookColorOverride ? 0 : 1);

        // A failed batch attempt never commits GL state, so the legacy path can
        // continue with the already-bound CPU-skinned model program unchanged.
        ModelState().modelShader->Use();

        // Talon ABC foliage commonly consists of several overlapping
        // alpha-tested planes/pieces.  File-order submission lets a farther plane
        // win on equal/near-equal depth and is especially visible on the AvP2
        // tree canopies.  Sort only order-sensitive multi-piece models using the
        // CURRENT skinned geometry, far-to-near.  Opaque ABCs retain their
        // original piece order and still use the GPU full-model fast path above.
        std::vector<uint32> pieceOrder(model->m_Pieces.m_dwElements);
        for (uint32 i = 0; i < model->m_Pieces.m_dwElements; ++i)
            pieceOrder[i] = i;

        // Keep ABC piece submission in model/file order.
        // Cross-object translucency is already handled by the stock translucent
        // scene queue.  Within one ABC, preserve author/model piece order so
        // changing view orientation cannot reshuffle the model's material layers.
        if (logInstanceIdentity && model->m_Pieces.m_dwElements > 1 &&
            (((inst->m_Base.m_dwFlags2 & FLAG2_CHROMAKEY) != 0u) || inst->m_Base.m_nColorA < 255))
        {
            LOG_SESSION("Model3D PIECE-ORDER inst=%p model='%s' mode=FILE-STABLE chroma=%d alpha=%u pieces=%u",
                        inst, model->m_szFilename ? model->m_szFilename : "",
                        (inst->m_Base.m_dwFlags2 & FLAG2_CHROMAKEY) ? 1 : 0,
                        static_cast<unsigned>(inst->m_Base.m_nColorA),
                        static_cast<unsigned>(model->m_Pieces.m_dwElements));
        }

        for (uint32 orderIndex = 0; orderIndex < pieceOrder.size(); ++orderIndex)
        {
            const uint32 pi = pieceOrder[orderIndex];
            // AVP2 actively hides ABC pieces (including first/third-person body
            // parts) through ModelInstance::m_adwHiddenPiece.
            if (pi < 32 && (inst->m_adwHiddenPiece[0] & (1u << pi)))
                continue;

            ModelPiece *piece = model->m_Pieces.m_pArray[pi];
            if (!piece)
                continue;

            const uint32 lodIndex = SelectModelPieceLOD(model, piece, modelDistance);
            ModelPieceSource geom = GetModelPieceSource(piece, lodIndex);

            // Stock Talon skips an explicitly empty selected LOD.
            if (!geom.verts || !geom.tris || !geom.vertCount || !geom.triCount)
            {
                if (logInstanceIdentity)
                    LOG_SESSION("Model3D PIECE-SKIP inst=%p model='%s' piece=%u name='%s' selectedLOD=%u verts=%u tris=%u",
                                inst, model->m_szFilename ? model->m_szFilename : "",
                                pi, piece->m_szName, lodIndex, geom.vertCount, geom.triCount);
                continue;
            }

            if (logInstanceIdentity)
                LOG_SESSION("Model3D LODSELECT inst=%p model='%s' piece=%u name='%s' dist=%.2f baseTris=%u lodCount=%u selected=%u selectedVerts=%u selectedTris=%u rigid=%d",
                            inst, model->m_szFilename ? model->m_szFilename : "",
                            pi, piece->m_szName, modelDistance, piece->m_Tris.m_dwElements,
                            piece->m_LODs.m_dwElements, lodIndex, geom.vertCount, geom.triCount,
                            model->m_bRigid ? 1 : 0);

            // Geometry diagnostics are deliberately done after skinning too.
            // This will tell us whether a head/helmet/Powerloader part is being
            // transformed to an unexpected location instead of being skipped.
            LTVector localMin{FLT_MAX, FLT_MAX, FLT_MAX};
            LTVector localMax{-FLT_MAX, -FLT_MAX, -FLT_MAX};
            LTVector skinMin{FLT_MAX, FLT_MAX, FLT_MAX};
            LTVector skinMax{-FLT_MAX, -FLT_MAX, -FLT_MAX};
            LTVector camMin{FLT_MAX, FLT_MAX, FLT_MAX};
            LTVector camMax{-FLT_MAX, -FLT_MAX, -FLT_MAX};
            uint32 zeroWeightVerts = 0;
            uint32 weightedVerts = 0;
            uint32 minNode = 0xFFFFFFFFu;
            uint32 maxNode = 0;
            uint32 inFrontVerts = 0;
            uint32 behindVerts = 0;
            uint32 inFrustumVerts = 0;
            bool badFinite = false;

            if (logInstanceIdentity && IsSuspiciousModelForGeometryDiag(model))
            {
                for (uint32 vi = 0; vi < geom.vertCount; ++vi)
                {
                    const ModelVert &mv = geom.verts[vi];
                    LTVector local{mv.m_vVec.x, mv.m_vVec.y, mv.m_vVec.z};
                    LTVector skinned = SkinVertex(mv, transforms);
                    LTVector cam = ToCamera(scene, inst->m_Base, skinned);

                    localMin = {std::min(localMin.x, local.x), std::min(localMin.y, local.y), std::min(localMin.z, local.z)};
                    localMax = {std::max(localMax.x, local.x), std::max(localMax.y, local.y), std::max(localMax.z, local.z)};
                    skinMin = {std::min(skinMin.x, skinned.x), std::min(skinMin.y, skinned.y), std::min(skinMin.z, skinned.z)};
                    skinMax = {std::max(skinMax.x, skinned.x), std::max(skinMax.y, skinned.y), std::max(skinMax.z, skinned.z)};
                    camMin = {std::min(camMin.x, cam.x), std::min(camMin.y, cam.y), std::min(camMin.z, cam.z)};
                    camMax = {std::max(camMax.x, cam.x), std::max(camMax.y, cam.y), std::max(camMax.z, cam.z)};

                    if (cam.z > 0.0f)
                    {
                        ++inFrontVerts;
                        const float tx = std::tan(std::max(0.01f, scene->m_fFovX * 0.5f));
                        const float ty = std::tan(std::max(0.01f, scene->m_fFovY * 0.5f));
                        const float maxX = cam.z * tx;
                        const float maxY = cam.z * ty;
                        if (std::fabs(cam.x) <= maxX && std::fabs(cam.y) <= maxY &&
                            cam.z >= 1.0f && cam.z <= std::max(2.0f, scene->m_fFarZ))
                            ++inFrustumVerts;
                    }
                    else
                        ++behindVerts;

                    if (!std::isfinite(skinned.x) || !std::isfinite(skinned.y) || !std::isfinite(skinned.z) ||
                        !std::isfinite(cam.x) || !std::isfinite(cam.y) || !std::isfinite(cam.z))
                        badFinite = true;

                    if (!mv.m_pWeights || !mv.m_wWeights)
                    {
                        ++zeroWeightVerts;
                    }
                    else
                    {
                        ++weightedVerts;
                        const uint16 wc = std::min<uint16>(mv.m_wWeights, 4);
                        for (uint16 wi = 0; wi < wc; ++wi)
                        {
                            minNode = std::min(minNode, mv.m_pWeights[wi].m_dwNode);
                            maxNode = std::max(maxNode, mv.m_pWeights[wi].m_dwNode);
                        }
                    }
                }

                if (minNode == 0xFFFFFFFFu)
                    minNode = 0;

                LOG_SESSION("Model3D GEOMDIAG inst=%p model='%s' piece=%u name='%s' lod=%u rigid=%d verts=%u tris=%u weighted=%u zeroWeight=%u nodes=%u..%u front=%u behind=%u inFrustum=%u local=[%.2f %.2f %.2f]-[%.2f %.2f %.2f] skin=[%.2f %.2f %.2f]-[%.2f %.2f %.2f] cam=[%.2f %.2f %.2f]-[%.2f %.2f %.2f] bad=%d",
                            inst, model->m_szFilename ? model->m_szFilename : "",
                            pi, piece->m_szName, lodIndex, model->m_bRigid ? 1 : 0,
                            geom.vertCount, geom.triCount, weightedVerts, zeroWeightVerts,
                            minNode, maxNode, inFrontVerts, behindVerts, inFrustumVerts,
                            localMin.x, localMin.y, localMin.z, localMax.x, localMax.y, localMax.z,
                            skinMin.x, skinMin.y, skinMin.z, skinMax.x, skinMax.y, skinMax.z,
                            camMin.x, camMin.y, camMin.z, camMax.x, camMax.y, camMax.z,
                            badFinite ? 1 : 0);
            }

            vertices.clear();
            vertices.reserve(static_cast<size_t>(geom.triCount) * 3);

            for (uint32 ti = 0; ti < geom.triCount; ++ti)
            {
                const ModelTri &tri = geom.tris[ti];

                for (int c = 0; c < 3; ++c)
                {
                    const uint16 vi = tri.m_awIndices[c];
                    if (vi >= geom.vertCount)
                        continue;

                    const ModelVert &mv = geom.verts[vi];
                    LTVector local = SkinVertex(mv, transforms);
                    LTVector cam = ToCamera(scene, inst->m_Base, local);

                    // Ordinary world ABCs retain the established authored-normal
                    // lighting path. ReallyClose first-person models use the
                    // node-skinned normal, matching stock's animated vertex path so
                    // the diffuse response follows weapon/hand animation.
                    LTVector sourceNormal = reallyClose
                                            ? SkinNormal(mv, transforms)
                                            : LTVector{mv.m_vNormal.x, mv.m_vNormal.y, mv.m_vNormal.z};
                    LTVector normal = ToCameraNormal(scene, inst->m_Base, sourceNormal);

                    // Match the D3D11 model shader:
                    // MODE_NO_LIGHT skips RGB lighting/diffuse modulation entirely.
                    // Object/model alpha is still applied separately.
                    //
                    // Previously we used object RGB here even for FLAG_NOLIGHT,
                    // which turns valid skins black when the object RGB is dark/zero.
                    LTVector litColor = lighting.noLight ? LTVector{1.0f, 1.0f, 1.0f}
                                                     : lighting.ambient;

                    if (!lighting.noLight)
                    {
                        LTVector direct{0.0f, 0.0f, 0.0f};

                        // Directional contribution. Original later doubles the
                        // entire directional/dynamic/static light accumulation.
                        const float sunNdl = std::max(0.0f,
                                                      -(normal.x * lighting.dirCamera.x +
                                                        normal.y * lighting.dirCamera.y +
                                                        normal.z * lighting.dirCamera.z));
                        direct.x += lighting.dirColor.x * sunNdl;
                        direct.y += lighting.dirColor.y * sunNdl;
                        direct.z += lighting.dirColor.z * sunNdl;

                        for (uint32 li = 0; li < lighting.dynamicLightCount; ++li)
                        {
                            const ModelPointLight &l = lighting.dynamicLights[li];
                            LTVector to{l.cameraPos.x - cam.x, l.cameraPos.y - cam.y, l.cameraPos.z - cam.z};
                            const float dist = std::sqrt(to.x * to.x + to.y * to.y + to.z * to.z);
                            if (dist <= 0.0001f || dist >= l.radius)
                                continue;
                            const float inv = 1.0f / dist;
                            to = {to.x * inv, to.y * inv, to.z * inv};
                            const float dn = 1.0f - std::min(1.0f, dist / l.radius);
                            float intensity = std::max(0.0f, to.x * normal.x + to.y * normal.y + to.z * normal.z);
                            if (l.closeHack)
                                intensity += std::pow(dn, 5.0f);
                            intensity *= dn;
                            direct.x += l.color.x * intensity;
                            direct.y += l.color.y * intensity;
                            direct.z += l.color.z * intensity;
                        }

                        for (uint32 li = 0; li < lighting.staticLightCount; ++li)
                        {
                            const ModelStaticLight &l = lighting.staticLights[li];
                            LTVector to{l.cameraPos.x - cam.x, l.cameraPos.y - cam.y, l.cameraPos.z - cam.z};
                            const float dist = std::sqrt(to.x * to.x + to.y * to.y + to.z * to.z);
                            if (dist <= 0.0001f || dist >= l.radius)
                                continue;
                            const float inv = 1.0f / dist;
                            to = {to.x * inv, to.y * inv, to.z * inv};
                            const float dn = 1.0f - std::min(1.0f, dist / l.radius);
                            float intensity = std::max(0.0f, to.x * normal.x + to.y * normal.y + to.z * normal.z);
                            if (l.closeHack)
                                intensity += std::pow(dn, 5.0f);

                            LTVector color = l.innerColor;
                            if (!l.point)
                            {
                                // Spotlight: direction is from light outward.
                                const float cone = -(to.x * l.cameraDir.x + to.y * l.cameraDir.y + to.z * l.cameraDir.z);
                                if (cone < l.fov)
                                    continue;
                                const float t = (1.0f - l.fov) > 0.0001f ? std::clamp((cone - l.fov) / (1.0f - l.fov), 0.0f, 1.0f) : 1.0f;
                                color = {
                                    l.outerColor.x + (l.innerColor.x - l.outerColor.x) * t,
                                    l.outerColor.y + (l.innerColor.y - l.outerColor.y) * t,
                                    l.outerColor.z + (l.innerColor.z - l.outerColor.z) * t};
                            }

                            intensity *= dn;
                            direct.x += color.x * intensity;
                            direct.y += color.y * intensity;
                            direct.z += color.z * intensity;
                        }

                        // Retail accumulates in 0..255 diffuse space and clamps
                        // to 255. These terms are already normalized to 0..1.
                        direct = direct.Clamp();

                        // model_PS: texture * completed vertex diffuse.
                        litColor = {
                            std::min(1.0f, lighting.ambient.x + direct.x + lighting.lightAdd.x),
                            std::min(1.0f, lighting.ambient.y + direct.y + lighting.lightAdd.y),
                            std::min(1.0f, lighting.ambient.z + direct.z + lighting.lightAdd.z)};
                    }

                    // IMPORTANT: engine-supplied TextureData is already in the
                    // orientation expected by Talon's model UVs. M2.1 inverted V
                    // here and produced visibly upside-down character skins.
                    const float u = tri.m_UVs[c].m_fU;
                    const float v = tri.m_UVs[c].m_fV;

                    // The legacy shader receives a pre-lit color, so its normal
                    // attribute is dedicated to stock-style environment UV
                    // generation. Use the animated normal and always include the
                    // view orientation for ReallyClose chrome.
                    LTVector envNormal = ToEnvironmentNormal(scene, inst->m_Base,
                                                         reallyClose ? SkinNormal(mv, transforms)
                                                                     : LTVector{mv.m_vNormal.x, mv.m_vNormal.y, mv.m_vNormal.z});

                    vertices.push_back({LTVector(cam.x, cam.y, cam.z),
                                        LTVector(envNormal.x, envNormal.y, envNormal.z),
                                        LTFloatPt(u, v),
                                        PGColor(litColor.x, litColor.y, litColor.z, lighting.alpha)});
                }
            }

            if (vertices.empty())
                continue;

            if (vertices.size() > MAX_MODEL_VERTICES)
                vertices.resize(MAX_MODEL_VERTICES - (MAX_MODEL_VERTICES % 3));

            Texture *skin = nullptr;
            SharedTexture *sharedSkin = nullptr;
            if ((renderSetup.hookFlags & 1u) && piece->m_wTextureIndex < MAX_MODEL_TEXTURES)
            {
                sharedSkin = reinterpret_cast<SharedTexture *>(inst->m_pSkins[piece->m_wTextureIndex]);
                skin = TextureManager::Instance().GetOrEnsure(sharedSkin);
            }

            static int modelSkinLogBudget = 32;
            if (LogIsSessionEnabled() && ((logInstanceIdentity || modelSkinLogBudget > 0) && sharedSkin))
            {
                LOG_SESSION("Model3D SKIN%s inst=%p model=%p piece=%u texIndex=%u shared=%p GL=%u size=%ux%u noLight=%d flags=%08X flags2=%08X objRGBA=(%u,%u,%u,%u)",
                            logInstanceIdentity ? "[NEW/MODEL]" : "",
                            inst, model, pi,
                            static_cast<unsigned>(piece->m_wTextureIndex),
                            sharedSkin,
                            skin ? skin->texture : 0,
                            skin ? skin->width : 0,
                            skin ? skin->height : 0,
                            lighting.noLight ? 1 : 0,
                            inst->m_Base.m_dwFlags, inst->m_Base.m_dwFlags2,
                            static_cast<unsigned>(inst->m_Base.m_nColorR),
                            static_cast<unsigned>(inst->m_Base.m_nColorG),
                            static_cast<unsigned>(inst->m_Base.m_nColorB),
                            static_cast<unsigned>(inst->m_Base.m_nColorA));
                if (LogIsSessionEnabled() && (!logInstanceIdentity && modelSkinLogBudget > 0))
                    --modelSkinLogBudget;
            }

            if (!sharedSkin)
            {
                static int noSkinBudget = 64;
                if (LogIsSessionEnabled() && ((noSkinBudget > 0 && noSkinBudget--)))
                    LOG_SESSION("Model3D NOSKIN inst=%p model='%s' piece=%u texIndex=%u hookFlags=%08X",
                                inst, model->m_szFilename ? model->m_szFilename : "",
                                pi, static_cast<unsigned>(piece->m_wTextureIndex),
                                renderSetup.hookFlags);
            }

            ModelMaterialMode material = BuildModelMaterial(inst, renderSetup, sharedSkin, skin);

            // Talon model detail textures are a distinct path from world detail.
            // d3d.ren 0x10024630 checks the skin RTexture's linked detail pointer;
            // 0x10001390 generates UV1 as (baseUV + model pan) *
            // ModelDetailTextureScale (stock default 3.0).  Unlike world detail,
            // model detail does not consume the linked DTX's detail angle/scale.
            Texture *modelDetail = nullptr;
            SharedTexture *modelDetailShared = nullptr;
            int modelLinkedMode = 0;
            const ModelTextureConsoleState &modelTexCV = GetModelTextureConsoleState();
            if (sharedSkin && modelTexCV.detailTextures != 0.0f)
            {
                auto *st = reinterpret_cast<SharedTextureCompat *>(sharedSkin);
                // d3d.ren 0x10024630 checks only the linked texture pointer for
                // model skins.  m_eTexType classification belongs to world
                // textures and must not be imported into this model path.
                if (st->m_pLinkedTexture)
                {
                    modelDetailShared = reinterpret_cast<SharedTexture *>(st->m_pLinkedTexture);
                    modelDetail = TextureManager::Instance().GetOrEnsure(modelDetailShared);
                    if (modelDetail && modelDetail->texture)
                        modelLinkedMode = 1;
                }
            }

            if (talonLoadingModelDiag)
            {
                static int loadPieceDiagBudget = 256;
                if (LogIsSessionEnabled() && ((loadPieceDiagBudget > 0 && loadPieceDiagBudget--)))
                    LOG_SESSION("TALON-LOADPIECE inst=%p model='%s' piece=%u name='%s' alpha=%u flags2=%08X texIndex=%u GL=%u srcVerts=%u srcTris=%u drawVerts=%u state=%s mode=%08X blend=%d alphaRef=%.4f",
                                inst, model->m_szFilename ? model->m_szFilename : "",
                                pi, piece->m_szName,
                                static_cast<unsigned>(inst->m_Base.m_nColorA),
                                inst->m_Base.m_dwFlags2,
                                static_cast<unsigned>(piece->m_wTextureIndex),
                                skin ? skin->texture : 0, geom.vertCount, geom.triCount,
                                static_cast<unsigned>(vertices.size()),
                                material.stateName, material.mode,
                                static_cast<int>(material.blend), material.alphaRef);
            }

            ApplyModelBlend(material);

            const bool stockChromakeyCullFallback =
                scene->m_nDrawMode != DRAWMODE_OBJECTLIST &&
                !reallyClose &&
                (material.mode & MMD_CHROMAKEY) != 0u;

            // Diagnostic/parity test: retail D3D8 starts from D3DCULL_CCW and
            // model RenderStyle passes override that state when needed.  Menu ABCs
            // are FLAG_REALLYCLOSE for projection/visibility purposes, not because
            // they are implicitly two-sided.  For opaque OBJECTLIST ReallyClose
            // pieces with no explicit CullMode, restore the D3D8 default.  Explicit
            // D3DCULL_NONE/CW/CCW always wins through ApplyModelCull.
            const bool stockMenuReallyCloseCullFallback =
                scene->m_nDrawMode == DRAWMODE_OBJECTLIST &&
                reallyClose &&
                material.blend == ModelBlendMode::Opaque;

            const bool stockCullFallback =
                stockChromakeyCullFallback || stockMenuReallyCloseCullFallback;
            ApplyModelCull(material, stockCullFallback);

            if (logInstanceIdentity && (material.stateCullOverride || stockCullFallback))
                LOG_SESSION("Model3D CULL inst=%p model='%s' piece=%u state=%s mode=%u source=%s glFront=%s",
                            inst, model->m_szFilename ? model->m_szFilename : "", pi,
                            material.stateCullOverride ? ModelCullModeName(material.stateCullMode) : "CCW",
                            static_cast<unsigned>(material.stateCullOverride ? material.stateCullMode : 3u),
                            material.stateCullOverride ? "STATECHANGE" : (stockMenuReallyCloseCullFallback ? "D3D8-DEFAULT-MENU-RC" : "D3D8-DEFAULT-CHROMAKEY"),
                            (material.stateCullOverride && material.stateCullMode == 2u) ? "CCW" : "CW");

            // d3d.ren's translucent model callback is invoked while the outer
            // sorted-translucent pass has ZWRITE disabled. It changes blend/fog
            // state, but does not turn ZWRITE back on.
            if (forceTranslucentDepthOff)
                GLStateDepthMask(GL_FALSE);
            // Gameplay world-space ABCs follow the active scene fog.  ReallyClose
            // models participate during normal gameplay, but menu/object-list
            // ReallyClose models remain unfogged.
            const bool allowReallyCloseFog = !reallyClose || scene->m_nDrawMode == DRAWMODE_NORMAL;
            const bool worldSpaceGameplayModel = !reallyClose && scene->m_nDrawMode == DRAWMODE_NORMAL;
            const bool modelFog = g_fogState.enabled && allowReallyCloseFog &&
                                  (worldSpaceGameplayModel || ((inst->m_Base.m_dwFlags & FLAG_FOGDISABLE) == 0));
            GLUniform1i(g_uModelFogEnabled, modelFog ? 1 : 0);
            ApplyModelVFogUniforms(g_uModelVFogEnabled, g_uModelVFogMinY, g_uModelVFogMaxY, g_uModelVFogMinYVal, g_uModelVFogMaxYVal, g_uModelVFogDensity, g_uModelVFogMax);
            GLUniform1i(g_uModelFogAdditive, material.blend == ModelBlendMode::Add ? 1 : 0);
            GLUniform3f(g_uModelHookColor,
                        std::clamp(renderSetup.objectColor.x / 255.0f, 0.0f, 1.0f),
                        std::clamp(renderSetup.objectColor.y / 255.0f, 0.0f, 1.0f),
                        std::clamp(renderSetup.objectColor.z / 255.0f, 0.0f, 1.0f));
            const bool applySceneTint = !renderSetup.hookColorOverride;
            GLUniform3f(g_uModelSceneTint,
                        applySceneTint ? std::clamp(renderSetup.sceneTint.x, 0.0f, 1.0f) : 1.0f,
                        applySceneTint ? std::clamp(renderSetup.sceneTint.y, 0.0f, 1.0f) : 1.0f,
                        applySceneTint ? std::clamp(renderSetup.sceneTint.z, 0.0f, 1.0f) : 1.0f);
            GLUniform3f(g_uModelLightAdd, lighting.lightAdd.x, lighting.lightAdd.y, lighting.lightAdd.z);

            GLUniform1ui(g_uModelMode, material.mode);
            GLUniform3f(g_uModelModeColor,
                        material.modeColor[0],
                        material.modeColor[1],
                        material.modeColor[2]);
            GLUniform1f(g_uModelAlphaRef, material.alphaRef);
            GLUniform1i(g_uModelAlphaFunc, static_cast<GLint>(material.alphaFunc));

            static int modelMaterialLogBudget = 64;
            const bool forceMaterialDiag = logInstanceIdentity && IsSuspiciousModelForGeometryDiag(model);
            if (LogIsSessionEnabled() && (forceMaterialDiag || (modelMaterialLogBudget > 0 &&
                                      (material.stateName[0] != 'n' ||
                                       material.mode != (lighting.noLight ? MMD_NO_LIGHT : 0u) ||
                                       material.blend != ModelBlendMode::Opaque))))
            {
                LOG_SESSION("Model3D MATERIAL inst=%p model='%s' piece=%u name='%s' texIndex=%u state=%s mode=%08X blend=%d alphaRef=%.4f objA=%u",
                            inst, model->m_szFilename ? model->m_szFilename : "",
                            pi, piece->m_szName, static_cast<unsigned>(piece->m_wTextureIndex),
                            material.stateName, material.mode,
                            static_cast<int>(material.blend), material.alphaRef,
                            static_cast<unsigned>(inst->m_Base.m_nColorA));
                if (!forceMaterialDiag)
                    --modelMaterialLogBudget;
            }

            GLTrackedModelNamedBufferSubData(g_vbo3D, 0,
                                             static_cast<GLsizeiptr>(vertices.size() * sizeof(ModelVertexGPU)),
                                             vertices.data(), GLModelUploadKind::LegacyVertices);

            GLUniform1i(g_uTextured, skin && skin->texture ? 1 : 0);
            GLStateBindTextureUnit(0, skin ? skin->texture : 0);

            GLUniform1i(g_uModelLinkedMode, modelLinkedMode);
            GLUniform1f(g_uModelDetailScale, modelTexCV.modelDetailTextureScale);
            GLUniform1i(g_uModelDetailAdd, modelTexCV.detailTextureAdd != 0.0f ? 1 : 0);
            GLStateBindTextureUnit(1, (modelLinkedMode == 1 && modelDetail) ? modelDetail->texture : 0);

            // AVP2 d3d.ren 0x100247BF..0x10024830 implements model
            // environment mapping as an env texture pass followed by the normal
            // skin/detail pass.  OpenGL does not need to reproduce that hardware-
            // era submission split: the fragment shader algebraically collapses
            // both Talon passes into one material evaluation, while preserving the
            // stock blend result for OPAQUE / ALPHA / ADD / MULTIPLY modes.
            // Exact Talon enable logic from d3d.ren 0x1000D5B0..0x1000D5E0:
            // EnvMapAll bypasses the per-object EnvMapEnable gate; otherwise an
            // object's FLAG_ENVIRONMENTMAP requires EnvMapEnable and a global env
            // texture.  The resulting cached flag is consumed by 0x100247BF.
            const bool envAll = (modelTexCV.envMapAll != 0.0f);
            const bool envObject = ((renderSetup.effectiveFlags & FLAG_ENVIRONMENTMAP) != 0u);
            const bool modelEnvRequested = envAll ||
                                           (envObject && modelTexCV.envMapEnable != 0.0f);
            SharedTexture *envShared = nullptr;
            Texture *envTex = nullptr;
            if (modelEnvRequested && ModelState().renderStruct && ModelState().renderStruct->m_pEnvMapTexture)
            {
                envShared = ModelState().renderStruct->m_pEnvMapTexture;
                envTex = TextureManager::Instance().GetOrEnsure(envShared);
                if (!envTex || !envTex->texture)
                {
                    static std::unordered_set<uintptr_t> s_failedLegacyEnv;
                    const uintptr_t key = reinterpret_cast<uintptr_t>(envShared);
                    if (LogIsSessionEnabled() && (s_failedLegacyEnv.size() < 32 && s_failedLegacyEnv.insert(key).second))
                        LOG_SESSION("TALON-MODEL-ENVMAP unresolved legacy env=%p flags=%08X envAll=%d envEnable=%d",
                                    envShared, renderSetup.effectiveFlags, envAll ? 1 : 0, modelTexCV.envMapEnable != 0.0f ? 1 : 0);
                    envTex = nullptr;
                }
            }

            if (LogIsSessionEnabled() && modelLinkedMode == 1)
            {
                static std::unordered_set<uint64_t> s_loggedModelDetails;
                const uint64_t key = uint64_t(reinterpret_cast<uintptr_t>(sharedSkin)) ^
                                     (uint64_t(reinterpret_cast<uintptr_t>(modelDetailShared)) << 1);
                if (LogIsSessionEnabled() && (s_loggedModelDetails.size() < 128 && s_loggedModelDetails.insert(key).second))
                    LOG_SESSION("TALON-MODEL-DETAIL base=%p GL=%u detail=%p GL=%u scale=%.3f add=%d model='%s' piece='%s'",
                                sharedSkin, skin ? skin->texture : 0, modelDetailShared,
                                modelDetail ? modelDetail->texture : 0, modelTexCV.modelDetailTextureScale,
                                modelTexCV.detailTextureAdd != 0.0f ? 1 : 0,
                                model->m_szFilename ? model->m_szFilename : "", piece->m_szName);
            }

            // Keep model envmaps locked to their reflection coordinates.  The
            // previous time-based EnvPanSpeed offset made stationary ABC/player
            // models look as if their chrome texture was scrolling by itself.
            GLUniform1i(g_uModelEnvPass, envTex ? 1 : 0);
            GLUniform4f(g_uModelEnvParams, modelTexCV.envScale, 0.0f, 0.0f, 0.0f);
            GLUniform1i(g_uModelBlendMode, static_cast<int>(material.blend));
            GLStateBindTextureUnit(2, envTex ? envTex->texture : 0);

            if (LogIsSessionEnabled() && envTex)
            {
                static std::unordered_set<uint64_t> s_loggedModelEnv;
                const uint64_t envKey = uint64_t(reinterpret_cast<uintptr_t>(model)) ^
                                        (uint64_t(reinterpret_cast<uintptr_t>(envShared)) << 1);
                if (LogIsSessionEnabled() && (s_loggedModelEnv.size() < 128 && s_loggedModelEnv.insert(envKey).second))
                    LOG_SESSION("TALON-MODEL-ENVMAP model='%s' env=%p GL=%u objectFlags=%08X envAll=%d envEnable=%d panSpeed=%.6f envScale=%.3f shaderCombined=1 detail=%d blend=%d",
                                model->m_szFilename ? model->m_szFilename : "", envShared, envTex->texture,
                                renderSetup.effectiveFlags, modelTexCV.envMapAll != 0.0f ? 1 : 0,
                                modelTexCV.envMapEnable != 0.0f ? 1 : 0, modelTexCV.envPanSpeed,
                                modelTexCV.envScale, modelLinkedMode == 1 ? 1 : 0,
                                static_cast<int>(material.blend));
            }

            // Single Talon material draw: base + optional detail + optional env.
            // The current GL blend mode is still the object's final Talon blend
            // mode; the shader converts the old two-pass env result into the
            // equivalent single source color/alpha before it reaches blending.
            GLStateBindVertexArray(g_vao3D);
            glf.DrawArrays(GL_TRIANGLES_, 0, static_cast<GLsizei>(vertices.size()));

            g_triCount += vertices.size() / 3;
            drewAnything = true;
        }

        if (drewAnything)
        {
            ++g_modelCount;

            static int modelDrawLogBudget = 12;
            if (LogIsSessionEnabled() && (modelDrawLogBudget > 0))
            {
                LOG_SESSION("Model3D: drew model=%p pieces=%u trisTotal=%u",
                            model,
                            model->m_Pieces.m_dwElements,
                            model->m_nTotalTris);
                --modelDrawLogBudget;
            }
        }

        GLStateDepthMask(GL_TRUE);
        GLStateDisable(GL_CULL_FACE);
        // Keep the renderer-wide convention deterministic for later world draws.
        GLStateFrontFace(GL_CW);

        return drewAnything;
    }


}

static bool IsCharacterBodyModel(const Model *model)
{
    if (!model || !model->m_szFilename)
        return false;
    std::string n = model->m_szFilename;
    std::transform(n.begin(), n.end(), n.begin(), [](unsigned char c)
                   { return char(std::tolower(c)); });
    return n.find("models\\characters\\") != std::string::npos ||
           n.find("models/characters/") != std::string::npos;
}

static bool IsLocalCharacterBody(const SceneDesc *scene, const ModelInstanceCompat *inst)
{
    if (!scene || !inst)
        return false;
    const float dx = inst->m_Base.m_vPos.x - scene->m_vPos.x;
    const float dz = inst->m_Base.m_vPos.z - scene->m_vPos.z;
    const float dy = std::fabs(inst->m_Base.m_vPos.y - scene->m_vPos.y);
    return (dx * dx + dz * dz) < 144.0f && dy < 128.0f;
}

static bool InitCharacterDropShadowPipeline()
{
    g_characterShadowShader = avp2::render::ShaderManager::Instance().CreateGraphicsFromResources(
        "model.character_shadow",
        avp2::render::ShaderResourceId::CharacterShadowVertex,
        avp2::render::ShaderResourceId::CharacterShadowFragment);
    if (!g_characterShadowShader)
        return false;
    g_uShadowTanHalfFovX = g_characterShadowShader->Uniform("uTanHalfFovX");
    g_uShadowTanHalfFovY = g_characterShadowShader->Uniform("uTanHalfFovY");
    g_uShadowNearZ = g_characterShadowShader->Uniform("uNearZ");
    g_uShadowFarZ = g_characterShadowShader->Uniform("uFarZ");
    g_uShadowAlpha = g_characterShadowShader->Uniform("uShadowAlpha");
    g_uShadowFogNear = g_characterShadowShader->Uniform("uFogNear");
    g_uShadowFogFar = g_characterShadowShader->Uniform("uFogFar");
    g_uShadowFogEnabled = g_characterShadowShader->Uniform("uFogEnabled");

    glf.CreateVertexArrays(1, &g_characterShadowVao);
    glf.CreateBuffers(1, &g_characterShadowVbo);
    if (!g_characterShadowVao || !g_characterShadowVbo)
        return false;
    glf.NamedBufferStorage(g_characterShadowVbo, 6 * sizeof(CharacterShadowVertexGPU), nullptr, GL_DYNAMIC_STORAGE_BIT_);
    glf.VertexArrayVertexBuffer(g_characterShadowVao, 0, g_characterShadowVbo, 0, sizeof(CharacterShadowVertexGPU));
    glf.EnableVertexArrayAttrib(g_characterShadowVao, 0);
    glf.VertexArrayAttribFormat(g_characterShadowVao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(CharacterShadowVertexGPU, x));
    glf.VertexArrayAttribBinding(g_characterShadowVao, 0, 0);
    glf.EnableVertexArrayAttrib(g_characterShadowVao, 1);
    glf.VertexArrayAttribFormat(g_characterShadowVao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(CharacterShadowVertexGPU, u));
    glf.VertexArrayAttribBinding(g_characterShadowVao, 1, 0);

    constexpr int N = 64;
    std::array<uint8_t, N * N * 4> tex{};
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < N; ++x)
        {
            const float fx = ((float(x) + 0.5f) / float(N)) * 2.0f - 1.0f;
            const float fy = ((float(y) + 0.5f) / float(N)) * 2.0f - 1.0f;
            const float r2 = fx * fx + fy * fy;
            const float edge = std::clamp(1.0f - r2, 0.0f, 1.0f);
            const float a = edge * edge;
            const size_t i = (size_t(y) * N + x) * 4u;
            tex[i + 0] = tex[i + 1] = tex[i + 2] = 0;
            tex[i + 3] = uint8_t(std::lround(a * 255.0f));
        }
    glf.CreateTextures(GL_TEXTURE_2D_, 1, &g_characterShadowTexture);
    if (!g_characterShadowTexture)
        return false;
    glf.TextureStorage2D(g_characterShadowTexture, 1, GL_RGBA8_, N, N);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glf.TextureSubImage2D(g_characterShadowTexture, 0, 0, 0, N, N, GL_RGBA, GL_UNSIGNED_BYTE, tex.data());
    glf.TextureParameteri(g_characterShadowTexture, GL_TEXTURE_MIN_FILTER_, GL_LINEAR_);
    glf.TextureParameteri(g_characterShadowTexture, GL_TEXTURE_MAG_FILTER_, GL_LINEAR_);
    glf.TextureParameteri(g_characterShadowTexture, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
    glf.TextureParameteri(g_characterShadowTexture, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);
    return true;
}

static void TermCharacterDropShadowPipeline()
{
    if (g_characterShadowTexture)
        GLStateDeleteTextures(1, &g_characterShadowTexture);
    if (g_characterShadowVbo)
        glf.DeleteBuffers(1, &g_characterShadowVbo);
    if (g_characterShadowVao)
        GLStateDeleteVertexArrays(1, &g_characterShadowVao);
    avp2::render::ShaderManager::Instance().Release("model.character_shadow");
    g_characterShadowTexture = g_characterShadowVbo = g_characterShadowVao = 0;
    g_characterShadowShader = nullptr;
}

static void RenderCharacterDropShadows(SceneDesc *scene,
                                       const std::vector<ModelInstanceCompat *> &models,
                                       const std::unordered_set<ModelInstanceCompat *> &attachments)
{
    if (!scene || scene->m_nDrawMode == DRAWMODE_OBJECTLIST || !g_characterShadowShader ||
        !g_characterShadowVao || !g_characterShadowTexture)
        return;

    // SceneDesc has no near-plane member. Normal world-space ABC rendering
    // uses Talon's fixed 1.0-unit near plane, so keep the shadow projection
    // on the identical depth mapping.
    const float nearZ = 1.0f;
    const float farZ = std::max(scene->m_fFarZ, nearZ + 1.0f);
    const float tanHalfFovY = std::tan(std::max(scene->m_fFovY, 0.01f) * 0.5f);
    const float tanHalfFovX = std::tan(std::max(scene->m_fFovX, 0.01f) * 0.5f);

    g_characterShadowShader->Use();
    if (g_uShadowTanHalfFovX >= 0)
        GLUniform1f(g_uShadowTanHalfFovX, tanHalfFovX);
    if (g_uShadowTanHalfFovY >= 0)
        GLUniform1f(g_uShadowTanHalfFovY, tanHalfFovY);
    if (g_uShadowNearZ >= 0)
        GLUniform1f(g_uShadowNearZ, nearZ);
    if (g_uShadowFarZ >= 0)
        GLUniform1f(g_uShadowFarZ, farZ);
    if (g_uShadowAlpha >= 0)
        GLUniform1f(g_uShadowAlpha, 0.55f);
    if (g_uShadowFogEnabled >= 0)
        GLUniform1i(g_uShadowFogEnabled, g_fogState.enabled ? 1 : 0);
    if (g_uShadowFogNear >= 0)
        GLUniform1f(g_uShadowFogNear, g_fogState.nearZ);
    if (g_uShadowFogFar >= 0)
        GLUniform1f(g_uShadowFogFar, g_fogState.farZ);
    GLStateBindTextureUnit(0, g_characterShadowTexture);
    GLStateBindVertexArray(g_characterShadowVao);

    GLStateEnable(GL_DEPTH_TEST);
    GLStateDepthFunc(GL_LEQUAL);
    GLStateDepthMask(GL_FALSE);
    GLStateEnable(GL_BLEND);
    GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLStateDisable(GL_CULL_FACE);
    GLStateEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);

    for (ModelInstanceCompat *inst : models)
    {
        if (!inst || attachments.find(inst) != attachments.end())
            continue;
        LTObjectCompat &o = inst->m_Base;
        if (!(o.m_dwFlags & FLAG_VISIBLE) || (o.m_dwFlags & FLAG_REALLYCLOSE) || o.m_nColorA == 0)
            continue;
        Model *model = GetModelFromInstance(inst);
        if (!IsCharacterBodyModel(model) || IsLocalCharacterBody(scene, inst))
            continue;

        const float dx = std::fabs(o.m_vDims.x);
        const float dy = std::fabs(o.m_vDims.y);
        const float dz = std::fabs(o.m_vDims.z);
        float hx = std::max(10.0f, dx * 1.35f);
        float hz = std::max(10.0f, dz * 1.35f);
        if (dx < 0.01f || dz < 0.01f)
        {
            const float r = std::max(8.0f, (model ? model->m_fGlobalRadius : o.m_fRadius) * 0.22f);
            hx = hz = r;
        }
        const float y = o.m_vPos.y - dy + 0.35f;
        const LTVector world[4] = {
            {o.m_vPos.x - hx, y, o.m_vPos.z - hz},
            {o.m_vPos.x + hx, y, o.m_vPos.z - hz},
            {o.m_vPos.x + hx, y, o.m_vPos.z + hz},
            {o.m_vPos.x - hx, y, o.m_vPos.z + hz}};
        LTVector c[4];
        for (int i = 0; i < 4; ++i)
            c[i] = WorldPointToCamera(scene, world[i]);
        CharacterShadowVertexGPU v[6] = {
            {c[0].x, c[0].y, c[0].z, 0, 0}, {c[1].x, c[1].y, c[1].z, 1, 0}, {c[2].x, c[2].y, c[2].z, 1, 1}, {c[0].x, c[0].y, c[0].z, 0, 0}, {c[2].x, c[2].y, c[2].z, 1, 1}, {c[3].x, c[3].y, c[3].z, 0, 1}};
        GLTrackedModelNamedBufferSubData(g_characterShadowVbo, 0, sizeof(v), v, GLModelUploadKind::Shadow);
        glf.DrawArrays(GL_TRIANGLES_, 0, 6);
        g_triCount += 2;
    }

    GLStateDisable(GL_POLYGON_OFFSET_FILL);
    GLStateDepthMask(GL_TRUE);
    GLStateDisable(GL_BLEND);
    ModelState().modelShader->Use();
}

static bool InitModelGpuBatchPipeline()
{
    auto *shader = avp2::render::ShaderManager::Instance().CreateGraphicsFromResources("model.batch",
                                                                                       avp2::render::ShaderResourceId::ModelBatchVertex,
                                                                                       avp2::render::ShaderResourceId::ModelBatchFragment);
    if (!shader)
        return false;
    ModelState().batchShader = shader;

    g_uBatchTanHalfFovX = shader->Uniform("uTanHalfFovX");
    g_uBatchTanHalfFovY = shader->Uniform("uTanHalfFovY");
    g_uBatchNearZ = shader->Uniform("uNearZ");
    g_uBatchFarZ = shader->Uniform("uFarZ");
    g_uBatchObjPos = shader->Uniform("uObjPos");
    g_uBatchObjScale = shader->Uniform("uObjScale");
    g_uBatchObjQuat = shader->Uniform("uObjQuat");
    g_uBatchCamPos = shader->Uniform("uCamPos");
    g_uBatchCamQuat = shader->Uniform("uCamQuat");
    g_uBatchReallyClose = shader->Uniform("uReallyClose");
    g_uBatchNodeCount = shader->Uniform("uNodeCount");
    g_uBatchAmbient = shader->Uniform("uAmbient");
    g_uBatchHookColor = shader->Uniform("uHookColor");
    g_uBatchSceneTint = shader->Uniform("uSceneTint");
    g_uBatchLightAdd = shader->Uniform("uLightAdd");
    g_uBatchDirColor = shader->Uniform("uDirColor");
    g_uBatchDirCamera = shader->Uniform("uDirCamera");
    g_uBatchAlpha = shader->Uniform("uModelAlpha");
    g_uBatchLightCount = shader->Uniform("uLightCount");
    g_uBatchFogEnabled = shader->Uniform("uModelFogEnabled");
    g_uBatchFogColor = shader->Uniform("uModelFogColor");
    g_uBatchFogNear = shader->Uniform("uModelFogNear");
    g_uBatchFogFar = shader->Uniform("uModelFogFar");
    g_uBatchFogAdditive = shader->Uniform("uModelFogAdditive");
    g_uBatchVFogEnabled = shader->Uniform("uVFogEnabled");
    g_uBatchVFogMinY = shader->Uniform("uVFogMinY");
    g_uBatchVFogMaxY = shader->Uniform("uVFogMaxY");
    g_uBatchVFogMinYVal = shader->Uniform("uVFogMinYVal");
    g_uBatchVFogMaxYVal = shader->Uniform("uVFogMaxYVal");
    g_uBatchVFogDensity = shader->Uniform("uVFogDensity");
    g_uBatchVFogMax = shader->Uniform("uVFogMax");
    g_uBatchEnvPass = shader->Uniform("uModelEnvPass");
    g_uBatchEnvParams = shader->Uniform("uModelEnvParams");
    g_uBatchBlendMode = shader->Uniform("uModelBlendMode");

    glf.CreateVertexArrays(1, &g_vaoModelBatch);
    if (!g_vaoModelBatch)
        return false;

    glf.EnableVertexArrayAttrib(g_vaoModelBatch, 0);
    glf.VertexArrayAttribFormat(g_vaoModelBatch, 0, 3, GL_FLOAT, GL_FALSE, offsetof(ModelBatchVertexGPU, pos.x));
    glf.VertexArrayAttribBinding(g_vaoModelBatch, 0, 0);
    glf.EnableVertexArrayAttrib(g_vaoModelBatch, 1);
    glf.VertexArrayAttribFormat(g_vaoModelBatch, 1, 3, GL_FLOAT, GL_FALSE, offsetof(ModelBatchVertexGPU, normal.x));
    glf.VertexArrayAttribBinding(g_vaoModelBatch, 1, 0);
    glf.EnableVertexArrayAttrib(g_vaoModelBatch, 2);
    glf.VertexArrayAttribFormat(g_vaoModelBatch, 2, 2, GL_FLOAT, GL_FALSE, offsetof(ModelBatchVertexGPU, uv.x));
    glf.VertexArrayAttribBinding(g_vaoModelBatch, 2, 0);
    for (GLuint i = 0; i < 4; ++i)
    {
        glf.EnableVertexArrayAttrib(g_vaoModelBatch, 3 + i);
        glf.VertexArrayAttribFormat(g_vaoModelBatch, 3 + i, 4, GL_FLOAT, GL_FALSE,
                                    offsetof(ModelBatchVertexGPU, weightVec) + i * sizeof(float) * 4);
        glf.VertexArrayAttribBinding(g_vaoModelBatch, 3 + i, 0);
    }
    glf.EnableVertexArrayAttrib(g_vaoModelBatch, 7);
    glf.VertexArrayAttribFormat(g_vaoModelBatch, 7, 4, GL_FLOAT, GL_FALSE, offsetof(ModelBatchVertexGPU, nodeIndex));
    glf.VertexArrayAttribBinding(g_vaoModelBatch, 7, 0);
    glf.EnableVertexArrayAttrib(g_vaoModelBatch, 8);
    glf.VertexArrayAttribFormat(g_vaoModelBatch, 8, 2, GL_FLOAT, GL_FALSE, offsetof(ModelBatchVertexGPU, weightCount));
    glf.VertexArrayAttribBinding(g_vaoModelBatch, 8, 0);

    glf.CreateBuffers(1, &g_modelNodeSsbo);
    glf.CreateBuffers(1, &g_modelLightSsbo);
    glf.CreateBuffers(1, &g_modelSkinStateSsbo);
    if (!g_modelNodeSsbo || !g_modelLightSsbo || !g_modelSkinStateSsbo)
        return false;
    glf.NamedBufferStorage(g_modelNodeSsbo,
                           static_cast<GLsizeiptr>(MAX_MODEL_BATCH_NODES * sizeof(LTMatrix)), nullptr, GL_DYNAMIC_STORAGE_BIT_);
    glf.NamedBufferStorage(g_modelLightSsbo,
                           static_cast<GLsizeiptr>(MAX_MODEL_BATCH_LIGHTS * sizeof(ModelBatchLightGPU)), nullptr, GL_DYNAMIC_STORAGE_BIT_);
    glf.NamedBufferStorage(g_modelSkinStateSsbo,
                           static_cast<GLsizeiptr>(MODEL_BATCH_SKIN_SLOTS * sizeof(ModelBatchSkinStateGPU)), nullptr, GL_DYNAMIC_STORAGE_BIT_);

    // Animated model frame data is tiny but was previously submitted as
    // three glNamedBufferSubData calls per GPU-batched model. Keep the old
    // buffers above as a correctness fallback, but prefer one persistently
    // mapped frame arena and bind aligned SSBO ranges for nodes/lights/skins.
    if (glf.MapNamedBufferRange && glf.BindBufferRange && glf.FenceSync && glf.ClientWaitSync && glf.DeleteSync)
    {
        GLint align = 256;
        glGetIntegerv(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT_, &align);
        if (align > 0)
            g_modelSsboAlignment = static_cast<size_t>(align);
        glf.CreateBuffers(1, &g_modelFrameSsbo);
        if (g_modelFrameSsbo)
        {
            const GLsizeiptr total = static_cast<GLsizeiptr>(MODEL_STREAM_SEGMENT_BYTES * MODEL_STREAM_FRAMES);
            const GLbitfield flags = GL_MAP_WRITE_BIT_ | GL_MAP_PERSISTENT_BIT_ | GL_MAP_COHERENT_BIT_ | GL_DYNAMIC_STORAGE_BIT_;
            glf.NamedBufferStorage(g_modelFrameSsbo, total, nullptr, flags);
            g_modelFrameMapped = glf.MapNamedBufferRange(g_modelFrameSsbo, 0, total,
                                                         GL_MAP_WRITE_BIT_ | GL_MAP_PERSISTENT_BIT_ | GL_MAP_COHERENT_BIT_);
            if (!g_modelFrameMapped)
            {
                glf.DeleteBuffers(1, &g_modelFrameSsbo);
                g_modelFrameSsbo = 0;
            }
        }
    }
    g_modelFrameSlot = 0;
    g_modelFrameCursorBytes = 0;
    g_modelFrameUsed = false;

    LOG_SESSION("Model3D GPU model pipeline: immutable geometry cache + vertex-shader Talon animation + persistent frame-state arena=%d align=%llu",
                g_modelFrameMapped ? 1 : 0, static_cast<unsigned long long>(g_modelSsboAlignment));
    return true;
}


static void TermModelGpuBatchPipeline()
{
    for (auto &kv : g_modelGpuGeometryCache)
        if (kv.second.vbo)
            glf.DeleteBuffers(1, &kv.second.vbo);
    g_modelGpuGeometryCache.clear();
    for (size_t i = 0; i < MODEL_STREAM_FRAMES; ++i)
    {
        if (g_modelFrameFences[i] && glf.DeleteSync)
            glf.DeleteSync(g_modelFrameFences[i]);
        g_modelFrameFences[i] = nullptr;
    }
    if (g_modelFrameSsbo)
        glf.DeleteBuffers(1, &g_modelFrameSsbo);
    g_modelFrameSsbo = 0;
    g_modelFrameMapped = nullptr;
    g_modelFrameSlot = 0;
    g_modelFrameCursorBytes = 0;
    g_modelFrameUsed = false;
    if (g_modelSkinStateSsbo)
        glf.DeleteBuffers(1, &g_modelSkinStateSsbo);
    if (g_modelLightSsbo)
        glf.DeleteBuffers(1, &g_modelLightSsbo);
    if (g_modelNodeSsbo)
        glf.DeleteBuffers(1, &g_modelNodeSsbo);
    if (g_vboModelBatch)
        glf.DeleteBuffers(1, &g_vboModelBatch);
    if (g_vaoModelBatch)
        GLStateDeleteVertexArrays(1, &g_vaoModelBatch);
    avp2::render::ShaderManager::Instance().Release("model.batch");
    g_modelSkinStateSsbo = g_modelLightSsbo = g_modelNodeSsbo = 0;
    g_vboModelBatch = g_vaoModelBatch = 0;
    ModelState().batchShader = nullptr;
    g_modelBatchVertexCapacity = 0;
}

void ABCModelRenderer::SetRenderStruct(RenderStruct *rs)
{
    ModelState().renderStruct = rs;
}

bool ABCModelRenderer::Init()
{
    auto *shader = avp2::render::ShaderManager::Instance().CreateGraphicsFromResources("model.main",
                                                                                       avp2::render::ShaderResourceId::ModelLegacyVertex,
                                                                                       avp2::render::ShaderResourceId::ModelLegacyFragment);
    if (!shader)
        return false;
    ModelState().modelShader = shader;

    g_uTanHalfFovX = shader->Uniform("uTanHalfFovX");
    g_uTanHalfFovY = shader->Uniform("uTanHalfFovY");
    g_uNearZ = shader->Uniform("uNearZ");
    g_uFarZ = shader->Uniform("uFarZ");
    g_uTextured = shader->Uniform("uTextured");
    g_uModelMode = shader->Uniform("uModelMode");
    g_uModelModeColor = shader->Uniform("uModelModeColor");
    g_uModelAlphaRef = shader->Uniform("uModelAlphaRef");
    g_uModelAlphaFunc = shader->Uniform("uModelAlphaFunc");
    g_uModelFogEnabled = shader->Uniform("uModelFogEnabled");
    g_uModelFogColor = shader->Uniform("uModelFogColor");
    g_uModelFogNear = shader->Uniform("uModelFogNear");
    g_uModelFogFar = shader->Uniform("uModelFogFar");
    g_uModelFogAdditive = shader->Uniform("uModelFogAdditive");
    g_uModelVFogEnabled = shader->Uniform("uVFogEnabled");
    g_uModelVFogMinY = shader->Uniform("uVFogMinY");
    g_uModelVFogMaxY = shader->Uniform("uVFogMaxY");
    g_uModelVFogMinYVal = shader->Uniform("uVFogMinYVal");
    g_uModelVFogMaxYVal = shader->Uniform("uVFogMaxYVal");
    g_uModelVFogDensity = shader->Uniform("uVFogDensity");
    g_uModelVFogMax = shader->Uniform("uVFogMax");
    g_uModelHookColor = shader->Uniform("uModelHookColor");
    g_uModelSceneTint = shader->Uniform("uModelSceneTint");
    g_uModelLightAdd = shader->Uniform("uModelLightAdd");
    g_uModelLinkedMode = shader->Uniform("uModelLinkedMode");
    g_uModelDetailScale = shader->Uniform("uModelDetailScale");
    g_uModelDetailAdd = shader->Uniform("uModelDetailAdd");
    g_uModelEnvPass = shader->Uniform("uModelEnvPass");
    g_uModelEnvParams = shader->Uniform("uModelEnvParams");
    g_uModelBlendMode = shader->Uniform("uModelBlendMode");

    glf.CreateVertexArrays(1, &g_vao3D);
    glf.CreateBuffers(1, &g_vbo3D);
    glf.NamedBufferStorage(g_vbo3D,
                           static_cast<GLsizeiptr>(MAX_MODEL_VERTICES * sizeof(ModelVertexGPU)),
                           nullptr, GL_DYNAMIC_STORAGE_BIT_);

    glf.VertexArrayVertexBuffer(g_vao3D, 0, g_vbo3D, 0, sizeof(ModelVertexGPU));

    glf.EnableVertexArrayAttrib(g_vao3D, 0);
    glf.VertexArrayAttribFormat(g_vao3D, 0, 3, GL_FLOAT, GL_FALSE, offsetof(ModelVertexGPU, pos.x));
    glf.VertexArrayAttribBinding(g_vao3D, 0, 0);

    glf.EnableVertexArrayAttrib(g_vao3D, 1);
    glf.VertexArrayAttribFormat(g_vao3D, 1, 3, GL_FLOAT, GL_FALSE, offsetof(ModelVertexGPU, normal.x));
    glf.VertexArrayAttribBinding(g_vao3D, 1, 0);

    glf.EnableVertexArrayAttrib(g_vao3D, 2);
    glf.VertexArrayAttribFormat(g_vao3D, 2, 2, GL_FLOAT, GL_FALSE, offsetof(ModelVertexGPU, uv.x));
    glf.VertexArrayAttribBinding(g_vao3D, 2, 0);

    glf.EnableVertexArrayAttrib(g_vao3D, 3);
    glf.VertexArrayAttribFormat(g_vao3D, 3, 4, GL_FLOAT, GL_FALSE, offsetof(ModelVertexGPU, color.x));
    glf.VertexArrayAttribBinding(g_vao3D, 3, 0);

    if (!InitCharacterDropShadowPipeline())
        return false;
    if (!InitModelGpuBatchPipeline())
        return false;

    LOG_SESSION("ABCModelRenderer::Init: M3.18 world-vs-RC depth + OBJECTLIST ReallyClose projection split ready");
    return true;
}

void ABCModelRenderer::Term()
{
    TermModelGpuBatchPipeline();
    TermCharacterDropShadowPipeline();

    if (g_vbo3D)
        glf.DeleteBuffers(1, &g_vbo3D);
    if (g_vao3D)
        GLStateDeleteVertexArrays(1, &g_vao3D);
    avp2::render::ShaderManager::Instance().Release("model.main");
    g_vbo3D = g_vao3D = 0;
    ModelState().modelShader = nullptr;
}

void ABCModelRenderer::AdvanceStreamFrame()
{
    if (!g_modelFrameMapped || !g_modelFrameSsbo || !glf.FenceSync || !glf.ClientWaitSync || !glf.DeleteSync)
    {
        g_modelFrameCursorBytes = size_t(g_modelFrameSlot) * MODEL_STREAM_SEGMENT_BYTES;
        g_modelFrameUsed = false;
        return;
    }

    if (g_modelFrameUsed)
    {
        if (g_modelFrameFences[g_modelFrameSlot])
            glf.DeleteSync(g_modelFrameFences[g_modelFrameSlot]);
        g_modelFrameFences[g_modelFrameSlot] = glf.FenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE_, 0);
    }

    const uint32 next = (g_modelFrameSlot + 1u) % static_cast<uint32>(MODEL_STREAM_FRAMES);
    if (g_modelFrameFences[next])
    {
        const GLenum wait = glf.ClientWaitSync(g_modelFrameFences[next], GL_SYNC_FLUSH_COMMANDS_BIT_, GL_TIMEOUT_IGNORED_);
        if (wait == GL_WAIT_FAILED_)
            LOG_SESSION("Model3D frame-state stream: glClientWaitSync failed on slot %u", next);
        glf.DeleteSync(g_modelFrameFences[next]);
        g_modelFrameFences[next] = nullptr;
    }

    g_modelFrameSlot = next;
    g_modelFrameCursorBytes = size_t(next) * MODEL_STREAM_SEGMENT_BYTES;
    g_modelFrameUsed = false;
}


ABCModelRenderer &ABCModelRenderer::Instance()
{
    static ABCModelRenderer v;
    return v;
}
bool ABCModelRenderer::Render(SceneDesc *scene, ModelInstanceCompat *model,
                              bool forceTranslucentDepthOff, bool loadingObjectList)
{
    return RenderModel(scene, model, forceTranslucentDepthOff, loadingObjectList);
}

uint32 ABCModelRenderer::EffectiveFlags(SceneDesc *scene, ModelInstanceCompat *model) const
{
    return BuildModelRenderSetup(scene, model).effectiveFlags;
}

void ABCModelRenderer::BindPipeline()
{
    ModelState().modelShader->Use();
}

void ABCModelRenderer::RenderShadows(SceneDesc *scene,
    const std::vector<ModelInstanceCompat *> &models,
    const std::unordered_set<ModelInstanceCompat *> &attachments)
{
    RenderCharacterDropShadows(scene, models, attachments);
}

uint64_t ABCModelRenderer::TrianglesDrawn() const { return g_triCount; }
uint64_t ABCModelRenderer::ModelsDrawn() const { return g_modelCount; }
void ABCModelRenderer::ResetStats() { g_triCount = g_modelCount = 0; }
