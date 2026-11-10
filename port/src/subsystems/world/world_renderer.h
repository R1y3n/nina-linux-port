#pragma once
#include "../../lt_renderer_abi.h"
#include "world_visibility.h"
#include "world_pvs.h"
#include "world_lightmap_system.h"
#include "world_lighting.h"
#include "world_model_renderer.h"
#include "sky_renderer.h"
#include "world_material_system.h"
#include "world_dynamic_lights.h"
#include "world_static_geometry.h"
#include "world_surface_fx.h"
#include <GL/gl.h>

namespace avp2::render
{
    class Shader;
}

struct WorldRendererState
{
    avp2::render::Shader *worldShader = nullptr;
    GLuint vao = 0;
    GLuint vbo = 0;
};

// High-level world orchestrator.  Detailed responsibilities are exposed as
// focused child objects instead of accumulating more APIs on WorldRenderer.
class WorldRenderer final
{
public:
    static WorldRenderer &Instance();

    void SetRenderStruct(RenderStruct *rs) { m_renderStruct = rs; }
    RenderStruct *GetRenderStruct() const { return m_renderStruct; }

    bool Init();
    void Term();
    int RenderScene(SceneDesc *scene);
    void SetupScene(SceneDesc *scene);

    WorldPVS &PVS() { return WorldPVS::Instance(); }
    const WorldPVS &PVS() const { return WorldPVS::Instance(); }

    WorldLightmapSystem &Lightmaps() { return WorldLightmapSystem::Instance(); }
    const WorldLightmapSystem &Lightmaps() const { return WorldLightmapSystem::Instance(); }

    WorldVisibilitySystem &Visibility() { return m_visibility; }
    const WorldVisibilitySystem &Visibility() const { return m_visibility; }
    WorldLightingSystem &Lighting() { return m_lighting; }
    const WorldLightingSystem &Lighting() const { return m_lighting; }
    WorldModelRenderer &WorldModels() { return m_worldModels; }
    SkyRenderer &Sky() { return SkyRenderer::Instance(); }
    WorldMaterialSystem &Materials() { return WorldMaterialSystem::Instance(); }
    WorldDynamicLightSystem &DynamicLights() { return WorldDynamicLightSystem::Instance(); }
    WorldStaticGeometryRenderer &StaticGeometry() { return WorldStaticGeometryRenderer::Instance(); }
    WorldSurfaceFxSystem &SurfaceFx() { return WorldSurfaceFxSystem::Instance(); }
    const WorldModelRenderer &WorldModels() const { return m_worldModels; }
    const SkyRenderer &Sky() const { return SkyRenderer::Instance(); }
    const WorldMaterialSystem &Materials() const { return WorldMaterialSystem::Instance(); }
    const WorldDynamicLightSystem &DynamicLights() const { return WorldDynamicLightSystem::Instance(); }
    const WorldStaticGeometryRenderer &StaticGeometry() const { return WorldStaticGeometryRenderer::Instance(); }
    const WorldSurfaceFxSystem &SurfaceFx() const { return WorldSurfaceFxSystem::Instance(); }

    WorldRendererState &State() { return m_state; }
    const WorldRendererState &State() const { return m_state; }

private:
    WorldRenderer() = default;
    RenderStruct *m_renderStruct = nullptr;
    WorldRendererState m_state{};
    WorldVisibilitySystem m_visibility{};
    WorldLightingSystem m_lighting{};
    WorldModelRenderer m_worldModels{};
};
