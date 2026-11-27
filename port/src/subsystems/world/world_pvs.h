#pragma once

#include "world_render_types.h"
#include <cstdint>
#include <unordered_set>
#include <vector>

struct WorldPVSState
{
    std::unordered_set<WorldPolyCompat *> visibleStaticPolys;
    WorldBspCompat *visibleStaticMaskBsp = nullptr;
    std::vector<uint8_t> visibleStaticMask;
    bool haveStaticPVS = false;
    uint32 visibleLeafCount = 0;
    uint32 visibleLeafPolyRefs = 0;
    uint32 totalLeafCount = 0;

    std::vector<WorldModelInstanceCompat *> visibleWorldModels;
    std::vector<ModelInstanceCompat *> visibleModels;
    std::vector<DynamicLightCompat *> visibleDynamicLights;
    std::vector<SpriteInstanceCompat *> visibleSprites;
    std::vector<ParticleSystemCompat *> visibleParticleSystems;
    std::vector<PolyGridCompat *> visiblePolyGrids;
    std::vector<LineSystemCompat *> visibleLineSystems;
    std::vector<CanvasCompat *> visibleCanvases;
    uint32 visibleWorldModelCount = 0;

    MainWorldCompat *staticPvsWorld = nullptr;
    uint64_t staticPvsHash = ~uint64_t(0);
    uint64_t staticPvsGeneration = 1;

    World3DPerfStats perfStats{};
};

class WorldPVS final
{
public:
    static WorldPVS &Instance();

    void Reset();
    bool Query(MainWorldCompat *world, WorldBspCompat *vis, SceneDesc *scene);
    bool MergeObjectManager(MainWorldCompat *world);
    void AuditObjectManager(MainWorldCompat *world, const LTVector &camera);

    const WorldPVSState &State() const { return m_state; }
    WorldPVSState &State() { return m_state; }

    uint32 GetModelCount() const;
    ModelInstanceCompat *GetModel(uint32 index) const;
    uint32 GetSpriteCount() const;
    SpriteInstanceCompat *GetSprite(uint32 index) const;
    uint32 GetParticleSystemCount() const;
    ParticleSystemCompat *GetParticleSystem(uint32 index) const;
    uint32 GetPolyGridCount() const;
    PolyGridCompat *GetPolyGrid(uint32 index) const;
    uint32 GetLineSystemCount() const;
    LineSystemCompat *GetLineSystem(uint32 index) const;
    uint32 GetCanvasCount() const;
    CanvasCompat *GetCanvas(uint32 index) const;
    uint32 GetDynamicLightCount() const;
    DynamicLightCompat *GetDynamicLight(uint32 index) const;
    World3DPerfStats GetPerfStats() const { return m_state.perfStats; }

private:
    WorldPVS() = default;
    WorldPVSState m_state{};
};
