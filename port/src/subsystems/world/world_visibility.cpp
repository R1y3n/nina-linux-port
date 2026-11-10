#include "world_visibility.h"
#include "world_renderer.h"
#include "world_pvs.h"
#include "world_model_renderer.h"

uint32 WorldVisibilitySystem::GetTranslucentWorldModelCount() const
{
    uint32 count = 0;
    for (WorldModelInstanceCompat *wm : WorldPVS::Instance().State().visibleWorldModels)
        if (wm && (wm->m_Base.m_dwFlags & FLAG_VISIBLE) &&
            WorldRenderer::Instance().WorldModels().HasPhase(wm, WorldModelPhase::Translucent))
            ++count;
    return count;
}

WorldModelInstanceCompat *WorldVisibilitySystem::GetTranslucentWorldModel(uint32 index) const
{
    for (WorldModelInstanceCompat *wm : WorldPVS::Instance().State().visibleWorldModels)
    {
        if (!wm || !(wm->m_Base.m_dwFlags & FLAG_VISIBLE) ||
            !WorldRenderer::Instance().WorldModels().HasPhase(wm, WorldModelPhase::Translucent))
            continue;
        if (index == 0)
            return wm;
        --index;
    }
    return nullptr;
}
