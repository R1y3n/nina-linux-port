#pragma once
#include "../../lt_renderer_abi.h"

// Owns scene dispatch and ordering across the specialized object renderers.
class SceneRenderer final
{
public:
    static SceneRenderer &Instance();
    bool Init();
    void Term();
    int RenderScene(SceneDesc *scene);
    bool IsTalonLoadingObjectList(const SceneDesc *scene) const;
    void SetRenderStruct(RenderStruct *rs);
    RenderStruct *GetRenderStruct() const { return m_renderStruct; }
    uint64_t LastFrameModelTriangles() const;
    uint32 LastFrameModelsDrawn() const;

private:
    SceneRenderer() = default;
    RenderStruct *m_renderStruct = nullptr;
};
