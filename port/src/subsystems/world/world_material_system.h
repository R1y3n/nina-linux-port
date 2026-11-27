#pragma once
#include "world_render_types.h"
#include <GL/gl.h>

class Texture;
namespace avp2::render
{
    class Shader;
}

struct WorldMaterialPerfStats
{
    double applyMs = 0.0;
    double authoredResolveMs = 0.0;
    double authoredStateMs = 0.0;
    double derivedMs = 0.0;
    uint32 applyCalls = 0;
    uint32 authoredBindings = 0;
};

struct WorldMaterialSystemState
{
    GLint uTexFxMask = -1;
    GLint uTexFxParams0 = -1;
    GLint uTexFxParams1 = -1;
    GLint uTexFxParams2 = -1;
    GLint uTexFxTime = -1;
    GLint uPanSkyEnabled = -1;
    GLint uLinkedTexMode = -1;
    GLint uLinkedParams0 = -1;
    GLint uLinkedParams1 = -1;
    GLint uLinkedParams2 = -1;
    GLint uUseWorldMaterialParams = -1;
    GLint uWorldMaterialParamIndex = -1;
    GLint uFogAdditive = -1;
    GLint uFullBrightTexture = -1;
    GLint uAuthoredNormalEnabled = -1;
    GLint uAuthoredSpecularEnabled = -1;
    GLint uAuthoredNormalStrength = -1;
    GLint uAuthoredSpecularStrength = -1;
    GLint uAuthoredGlossMinPower = -1;
    GLint uAuthoredGlossMaxPower = -1;
    GLint uAuthoredGlossBias = -1;
    GLint uAuthoredReflectionMode = -1;
    GLint uAuthoredReflectionMapEnabled = -1;
    GLint uAuthoredReflectionStrength = -1;
};

class WorldMaterialSystem final
{
public:
    static WorldMaterialSystem &Instance();
    void Init(avp2::render::Shader *shader);
    void Reset();

    WorldTexFx BuildTexFx(const SurfaceCompat *surface) const;
    WorldBlendMode ClassifyBlend(uint32 flags) const;
    void ApplyTexFx(const WorldBatch &batch);
    SharedTexture *ResolveBatchTexture(const WorldBatch &batch) const;
    Texture *Apply(const WorldBatch &batch, bool materialIndexFromDrawState = false, uint32 *outMaterialParamIndex = nullptr);
    bool PrepareMaterialParamIndex(const WorldBatch &batch, uint32 &outIndex);
    void ApplyBlend(WorldBlendMode blend);
    void AdvanceStreamFrame();
    WorldMaterialPerfStats ConsumePerfStats();

private:
    WorldMaterialSystem() = default;
    uint32 HashTexFx(const WorldTexFx &fx) const;
    WorldMaterialSystemState m_state{};
};
