#pragma once
#include <vector>
#include <unordered_set>
#include "../../lt_renderer_abi.h"
namespace avp2::render
{
    class Shader;
}

struct ABCModelRendererState
{
    RenderStruct *renderStruct = nullptr;
    avp2::render::Shader *modelShader = nullptr;
    avp2::render::Shader *batchShader = nullptr;
};

class ABCModelRenderer final
{
public:
    static ABCModelRenderer &Instance();
    bool Init();
    void SetRenderStruct(RenderStruct *rs);
    void Term();
    bool Render(SceneDesc *scene, ModelInstanceCompat *model,
                bool forceTranslucentDepthOff = false, bool loadingObjectList = false);
    uint32 EffectiveFlags(SceneDesc *scene, ModelInstanceCompat *model) const;
    void BindPipeline();
    void RenderShadows(SceneDesc *scene, const std::vector<ModelInstanceCompat *> &models,
                       const std::unordered_set<ModelInstanceCompat *> &attachments);
    uint64_t TrianglesDrawn() const;
    uint64_t ModelsDrawn() const;
    void ResetStats();
    void AdvanceStreamFrame();
    ABCModelRendererState &State() { return m_state; }
    const ABCModelRendererState &State() const { return m_state; }

private:
    ABCModelRenderer() = default;
    ABCModelRendererState m_state{};
};
