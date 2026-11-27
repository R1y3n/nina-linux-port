#include "subsystems/renderer/Console.h"
#include "../renderer/frame_constants.h"
#include "../renderer/talon_render_state.h"
#include "../textures/texture_manager.h"
#include "../renderer/renderer_core.h"
#include "deluxe_lightmap_baker.h"
#include "../renderer/renderer_2d.h"

#include <cstdlib>
#include <cctype>
#include <string>
#include "subsystems/world/deluxe_lightmap_baker.h"
#include "gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "shaders/shader_manager.h"
#include "gl_renderer.h"
#include "subsystems/textures/Texture.h"
#include "subsystems/textures/texture_manager.h"
#include "utils/log.h"
#include "subsystems/renderer/fog_state.h"
#include "lt_renderer_abi.h"
#include "subsystems/sprites/sprite_renderer.h"
#include "subsystems/fx/fx_renderer.h"
#include "subsystems/world/world_renderer.h"
#include "subsystems/renderer/stock_render_options.h"

#include "shaders/shader_resources.h"

#include <GL/gl.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <array>
#include <cstring>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "world_pvs.h"
#include "world_lightmap_system.h"
#include "world_tree_abi.h"

#include "world_render_types.h"
#include "world_material_system.h"
#include "material_authoring.h"
#include "world_dynamic_lights.h"
#include "world_static_geometry.h"
#include "world_surface_fx.h"

namespace
{

    static WorldPVSState &PVSState() { return WorldPVS::Instance().State(); }
    static WorldLightmapSystemState &LightmapState() { return WorldLightmapSystem::Instance().State(); }

    static WorldRendererState &WorldState() { return WorldRenderer::Instance().State(); }
    static WorldStaticGeometryState &StaticState() { return WorldStaticGeometryRenderer::Instance().State(); }
    static void EnableWorldBackfaceCulling();
    static void DisableWorldBackfaceCulling();

    // Talon/D3D7 has a useful (and map-authored) coplanar layering behavior:
    // when multiple static world polygons occupy exactly the same geometry,
    // the first layer writes normally and subsequent layers modulate the
    // framebuffer at the same depth.  Match duplicates by the exact compiled
    // vertex set only.  Do NOT include the plane normal/distance: Talon BSP
    // compilation can emit the same coincident polygon with opposite winding
    // (and therefore an inverted plane) on different BSP splits.
    static uint32 FloatBitsCanonical(float v)
    {
        if (v == 0.0f)
            v = 0.0f; // collapse -0 to +0
        uint32 bits = 0;
        std::memcpy(&bits, &v, sizeof(bits));
        return bits;
    }

    static uint64_t CoplanarPolySignature(const SPolyVertexCompat *pv, uint32 n, const LTPlaneCompat *plane)
    {
        struct PBits { uint32 x, y, z; };
        std::vector<PBits> pts;
        pts.reserve(n);
        for (uint32 i = 0; i < n; ++i)
        {
            if (!pv[i].m_pPoints)
                return 0;
            const LTVector &v = pv[i].m_pPoints->m_vVec;
            pts.push_back({FloatBitsCanonical(v.x), FloatBitsCanonical(v.y), FloatBitsCanonical(v.z)});
        }
        std::sort(pts.begin(), pts.end(), [](const PBits &a, const PBits &b)
        {
            if (a.x != b.x) return a.x < b.x;
            if (a.y != b.y) return a.y < b.y;
            return a.z < b.z;
        });

        uint64_t h = 1469598103934665603ull;
        auto mix = [&](uint32 v)
        {
            h ^= static_cast<uint64_t>(v);
            h *= 1099511628211ull;
        };
        (void)plane;
        mix(n);
        for (const PBits &v : pts)
        {
            mix(v.x); mix(v.y); mix(v.z);
        }
        return h ? h : 1ull;
    }

    // Reverse lookup for Talon SurfaceFX.  The old compatibility path walked every
    // static/worldmodel polygon and then linearly searched MainWorld::m_pSurfaceEffects
    // for each one, every frame.  Large Talon levels can have tens of thousands of
    // polygon spans, so even a level with zero active matching SurfaceFX spent many
    // milliseconds in O(polys * effects) pointer chasing.
    //
    // Keep the exact Talon semantics, but index geometry once by Surface*.  Each
    // frame we now walk only the live SurfaceEffect list and touch the spans that
    // can actually be affected.

    // Lightmap atlas/LightAnim state is owned by WorldLightmapSystem.

    // Deluxe-lighting uniforms belong to the world shader; the deluxe baker owns
    // bake state/textures while WorldRenderer owns these shader bindings.
    GLint g_uDeluxeEnabled = -1;
    GLint g_uDeluxeDebugView = -1;
    GLint g_uDeluxeSpecularStrength = -1;
    GLint g_uDeluxeSpecularPower = -1;
    GLint g_uDeluxeGeneratedNormalEnabled = -1;
    GLint g_uDeluxeNormalStrength = -1;
    GLint g_uDeluxeNormalBlack = -1;
    GLint g_uDeluxeNormalWhite = -1;
    GLint g_uDeluxeNormalInvert = -1;
    GLint g_uDeluxeNormalInvertX = -1;
    GLint g_uDeluxeNormalInvertY = -1;
    GLint g_uDeluxeNormalInvertZ = -1;
    GLint g_uDeluxeNormalBand = -1;
    GLint g_uDeluxeSpecLightColorInfluence = -1;
    GLint g_uDeluxeGeneratedSpecularEnabled = -1;
    GLint g_uDeluxeSpecMapStrength = -1;
    GLint g_uDeluxeSpecBlack = -1;
    GLint g_uDeluxeSpecWhite = -1;
    GLint g_uDeluxeSpecInvert = -1;

    // Terrain BSP polygons are referenced by the same Leaf::m_pPolies PVS stream
    // as the PhysicsBSP, but live in separate WIF_TERRAIN BSPs.  Keep a second
    // compact PVS index stream so those immutable meshes participate in the exact
    // stock visibility set without reverting to the old full-terrain draw.
    // Static PhysicsBSP polygons can be vertex-lit through the same LightAnim
    // vertex-colour payload used by WorldModels.  Keep a source reference for
    // every cached GPU vertex so animated LightGroups can update those colours.
    GLint g_uCameraPos = -1;
    GLint g_uCameraQuat = -1;
    GLint g_uTanHalfFovX = -1;
    GLint g_uTanHalfFovY = -1;
    GLint g_uNearZ = -1;
    GLint g_uFarZ = -1;
    GLint g_uTextured = -1;
    GLint g_uLightmapped = -1;
    GLint g_uNoLight = -1;
    GLint g_uAlphaTest = -1;
    GLint g_uAlphaRef = -1;
    GLint g_uAlphaFunc = -1;
    GLint g_uFullBrightTexture = -1;
    GLint g_uUseWorld = -1;
    GLint g_uWorld = -1;
    GLint g_uObjectColor = -1;
    GLint g_uLegacyDrawFlags = -1;
    GLint g_uSkyDxt5AlphaOnly = -1;
    GLint g_uSkyHorizonFogGradient = -1;
    GLint g_uSkyClipCameraSpace = -1;
    GLint g_uUseWmDrawState = -1;
    GLint g_uUseGridLight = -1;
    GLint g_uLightGridDims = -1;
    GLint g_uLightGridLookupStart = -1;
    GLint g_uLightGridReciBlock = -1;
    GLint g_uHighQualityLightGrid = -1;
    GLint g_uGlobalVertexTint = -1;
    GLint g_uAlienInvertHack = -1;
    GLint g_uGlobalWMAmbient = -1;
    GLint g_uGpuVertexLight = -1;
    GLint g_uVertexLightVertexBase = -1;
    GLint g_uVertexLightDataBase = -1;

    GLint g_uStaticMaterialIndexFromBaseInstance = -1;
    GLint g_uWorldModelLightmapGouraud = -1;
    GLint g_uWorldModelBakedOnly = -1;
    GLint g_uLightmapSaturate = -1;
    GLint g_uFogEnabled = -1;
    GLint g_uFogColor = -1;
    GLint g_uFogNear = -1;
    GLint g_uFogFar = -1;
    GLint g_uFogAdditive = -1;
    GLint g_uVFogEnabled = -1;
    GLint g_uVFogMinY = -1;
    GLint g_uVFogMaxY = -1;
    GLint g_uVFogMinYVal = -1;
    GLint g_uVFogMaxYVal = -1;
    GLint g_uVFogDensity = -1;
    GLint g_uVFogMax = -1;

    static WorldBspCompat *FindVisBsp(MainWorldCompat *world)
    {
        if (!world || !world->m_WorldModels.m_pArray || world->m_WorldModels.m_dwElements > 4096)
            return nullptr;

        for (uint32 i = 0; i < world->m_WorldModels.m_dwElements; ++i)
        {
            WorldDataCompat *wd = world->m_WorldModels.m_pArray[i];
            if (wd && wd->m_pOriginalBsp &&
                (wd->m_pOriginalBsp->m_dwWorldInfoFlags & WIF_VISBSP))
                return wd->m_pOriginalBsp;
        }
        return nullptr;
    }

    static WorldBspCompat *FindMainBsp(SceneDesc *scene)
    {
        if (!scene || !scene->m_pRenderContext || !scene->m_pRenderContext->m_pMainWorld)
            return nullptr;

        auto *world = reinterpret_cast<MainWorldCompat *>(scene->m_pRenderContext->m_pMainWorld);
        const auto &arr = world->m_WorldModels;

        if (!arr.m_pArray || arr.m_dwElements == 0 || arr.m_dwElements > 4096)
            return nullptr;

        WorldBspCompat *physics = nullptr;
        WorldBspCompat *mainWorld = nullptr;
        WorldBspCompat *fallback = nullptr;

        static MainWorldCompat *s_loggedWorld = nullptr;
        const bool logModels = LogIsSessionEnabled() && (s_loggedWorld != world);
        if (logModels)
            s_loggedWorld = world;

        for (uint32 i = 0; i < arr.m_dwElements; ++i)
        {
            WorldDataCompat *wd = arr.m_pArray[i];
            if (!wd)
                continue;

            WorldBspCompat *original = wd->m_pOriginalBsp;
            if (!original)
                continue;

            if (logModels)
            {
                LOG_SESSION("World3D BSP[%u] name='%s' flags=%08X orig=%p world=%p valid=%p polies=%u surfaces=%u",
                            i, original->m_szWorldName, original->m_dwWorldInfoFlags,
                            wd->m_pOriginalBsp, wd->m_pWorldBsp, wd->m_pValidBsp,
                            original->m_dwPolies, original->m_dwSurfaces);
            }

            if (!fallback)
                fallback = original;

            // AVP2/Talon's PhysicsBSP is the actual static rendered map geometry
            // in the levels we've validated.  VisBSP is a much smaller structure
            // used for visibility/partitioning and is not the drawable world.
            if ((original->m_dwWorldInfoFlags & WIF_PHYSICSBSP) && !physics)
                physics = original;

            if ((original->m_dwWorldInfoFlags & WIF_MAINWORLD) && !mainWorld)
                mainWorld = original;
        }

        if (physics)
            return physics;
        if (mainWorld)
            return mainWorld;
        return fallback;
    }

    static bool IsTerrainBsp(const WorldBspCompat *bsp)
    {
        return bsp && (bsp->m_dwWorldInfoFlags & WIF_TERRAIN) != 0;
    }

    static void SetIdentityWorldTransform()
    {
        static const float I[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        GLUniform1i(g_uUseWmDrawState, 0);
        GLUniform1ui(g_uLegacyDrawFlags, 0u);
        GLUniform1i(g_uSkyDxt5AlphaOnly, 0);
        GLUniform1i(g_uSkyHorizonFogGradient, 0);
        GLUniform1i(g_uSkyClipCameraSpace, 0);
        GLUniform1i(g_uUseWorld, 0);
        GLUniformMatrix4fv(g_uWorld, 1, GL_FALSE, I);
        GLUniform4f(g_uObjectColor, 1, 1, 1, 1);
    }

    // SurfaceFX live UV updates are owned by WorldSurfaceFxSystem.

    // World material binding/blending is owned by WorldMaterialSystem.

    static void BindGpuVertexLight(GLuint ssbo, uint32 vertexBase = 0, uint32 dataBase = 0)
    {
        const bool enabled = LightmapState().gpuReady && LightmapState().animStateSsbo && ssbo;
        GLUniform1i(g_uGpuVertexLight, enabled ? 1 : 0);
        GLUniform1ui(g_uVertexLightVertexBase, enabled ? vertexBase : 0u);
        GLUniform1ui(g_uVertexLightDataBase, enabled ? dataBase : 0u);
        glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 4, enabled ? LightmapState().animStateSsbo : 0);
        glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 6, enabled ? ssbo : 0);
    }

    static void RebuildTerrainVisibleBatchCache(MainWorldCompat *world)
    {
        if (!world || !world->m_WorldModels.m_pArray)
        {
            StaticState().terrainVisibleBspCache.clear();
            StaticState().terrainDrawCacheGeneration = 0;
            StaticState().terrainDrawCacheWorld = nullptr;
            StaticState().terrainDrawCacheHadPvs = false;
            return;
        }

        if (StaticState().terrainDrawCacheGeneration == PVSState().staticPvsGeneration &&
            StaticState().terrainDrawCacheWorld == world &&
            StaticState().terrainDrawCacheHadPvs == PVSState().haveStaticPVS)
            return;

        StaticState().terrainVisibleBspCache.clear();
        std::vector<uint32> indices;
        std::unordered_set<WorldBspCompat *> seen;

        uint32 terrainBsps = 0;
        uint32 visibleBsps = 0;
        uint32 visibleMaterials = 0;
        uint32 visiblePolys = 0;
        uint32 sourceRuns = 0;
        uint64_t visibleTris = 0;

        // d3d.ren resolves packed polygon references through MainWorld's WorldData
        // array (0x1002EBB0: high 16 bits select WorldData, then BSP vfunc +0x0c
        // resolves the polygon).  Leaf::m_pPolies is therefore a cross-BSP render
        // visibility stream, not a list confined to PhysicsBSP.  Compile the
        // WIF_TERRAIN members of that exact pointer set here.
        for (uint32 wi = 0; wi < world->m_WorldModels.m_dwElements; ++wi)
        {
            WorldDataCompat *wd = world->m_WorldModels.m_pArray[wi];
            WorldBspCompat *bsp = wd ? wd->m_pOriginalBsp : nullptr;
            if (!bsp || !IsTerrainBsp(bsp) || !seen.insert(bsp).second)
                continue;

            ++terrainBsps;
            WorldModelCache *c = WorldRenderer::Instance().WorldModels().GetOrCreateCache(world, bsp);
            if (!c)
                continue;

            TerrainVisibleBspCache tc{};
            tc.bsp = bsp;
            tc.batches.resize(c->batches.size());
            bool any = false;

            for (size_t bi = 0; bi < c->batches.size(); ++bi)
            {
                const WorldBatch &b = c->batches[bi];
                StaticVisibleBatchCache &out = tc.batches[bi];
                out.firstIndex = static_cast<uint32>(indices.size());

                uint32 prevEnd = 0;
                bool haveRun = false;
                for (const PolySpan &span : b.spans)
                {
                    if (PVSState().haveStaticPVS && !WorldStaticGeometryRenderer::Instance().IsPolyVisible(span.poly))
                        continue;

                    if (!haveRun || prevEnd != span.firstVertex)
                        ++out.sourceRuns;
                    haveRun = true;
                    prevEnd = span.firstVertex + span.vertexCount;

                    ++out.visiblePolys;
                    ++tc.visiblePolys;
                    out.tris += span.vertexCount / 3;
                    tc.tris += span.vertexCount / 3;

                    // WorldModel caches may live either in the shared arena or in
                    // a dedicated fallback VBO.  Element indices are relative to
                    // whichever buffer WorldRenderer::Instance().WorldModels().BindGeometry() selects.
                    const uint32 base = c->arenaResident ? c->arenaFirstVertex : 0u;
                    const uint32 end = span.firstVertex + span.vertexCount;
                    for (uint32 vi = span.firstVertex; vi < end; ++vi)
                        indices.push_back(base + vi);
                }

                out.indexCount = static_cast<uint32>(indices.size()) - out.firstIndex;
                sourceRuns += out.sourceRuns;
                if (out.indexCount)
                {
                    ++visibleMaterials;
                    any = true;
                }
            }

            if (any)
                ++visibleBsps;
            visiblePolys += tc.visiblePolys;
            visibleTris += tc.tris;
            StaticState().terrainVisibleBspCache.push_back(std::move(tc));
        }

        const size_t bytes = indices.size() * sizeof(uint32);
        size_t wantedCapacity = std::max<size_t>(sizeof(uint32), bytes);
        // Avoid reallocating on every nearby PVS change while keeping this stream
        // tiny compared with the immutable terrain vertex arena.
        if (wantedCapacity < 64u * 1024u)
            wantedCapacity = 64u * 1024u;
        if (StaticState().terrainPvsEboCapacity)
            wantedCapacity = std::max(wantedCapacity, StaticState().terrainPvsEboCapacity);

        if (!StaticState().terrainPvsEbo || StaticState().terrainPvsEboCapacity < wantedCapacity)
        {
            if (StaticState().terrainPvsEbo)
                glf.DeleteBuffers(1, &StaticState().terrainPvsEbo);
            StaticState().terrainPvsEbo = 0;
            glf.CreateBuffers(1, &StaticState().terrainPvsEbo);
            if (StaticState().terrainPvsEbo)
            {
                glf.NamedBufferStorage(StaticState().terrainPvsEbo,
                                       static_cast<GLsizeiptr>(wantedCapacity), nullptr, GL_DYNAMIC_STORAGE_BIT_);
                StaticState().terrainPvsEboCapacity = wantedCapacity;
            }
        }

        if (StaticState().terrainPvsEbo && bytes)
            GLTrackedWorldNamedBufferSubData(StaticState().terrainPvsEbo, 0,
                                             static_cast<GLsizeiptr>(bytes), indices.data(), GLWorldUploadKind::PvsTerrain);

        StaticState().terrainDrawCacheGeneration = PVSState().staticPvsGeneration;
        StaticState().terrainDrawCacheWorld = world;
        StaticState().terrainDrawCacheHadPvs = PVSState().haveStaticPVS;
        ++StaticState().terrainDrawCacheRebuilds;

        static uint32 budget = 96;
        if (LogIsSessionEnabled() && (budget && (--budget, true)))
            LOG_SESSION("World3D TERRAIN-PVS generation=%llu rebuild=%u terrainBsps=%u visibleBsps=%u visibleMaterials=%u sourceRuns=%u indices=%u visiblePolys=%u tris=%llu leafRefs=%u uniqueLeafPolys=%u path=Leaf::m_pPolies/CROSS-BSP/IMMUTABLE-MESH/INDEX-CACHE",
                        static_cast<unsigned long long>(PVSState().staticPvsGeneration), StaticState().terrainDrawCacheRebuilds,
                        terrainBsps, visibleBsps, visibleMaterials, sourceRuns,
                        static_cast<unsigned>(indices.size()), visiblePolys,
                        static_cast<unsigned long long>(visibleTris), PVSState().visibleLeafPolyRefs,
                        static_cast<unsigned>(PVSState().visibleStaticPolys.size()));
    }

    static void DrawTerrainPvsPhase(MainWorldCompat *world, WorldBlendMode phase,
                                    uint32 &draws, uint64_t &tris,
                                    uint32 &visiblePolys, uint32 &materialCalls)
    {
        if (!world || !StaticState().terrainPvsEbo || StaticState().terrainVisibleBspCache.empty())
            return;

        SetIdentityWorldTransform();
        GLUniform1ui(g_uLegacyDrawFlags, 1u);
        GLUniform1i(g_uUseGridLight, 0);
        glf.VertexArrayElementBuffer(WorldState().vao, StaticState().terrainPvsEbo);

        for (const TerrainVisibleBspCache &tc : StaticState().terrainVisibleBspCache)
        {
            if (!tc.bsp)
                continue;
            WorldModelCache *c = WorldRenderer::Instance().WorldModels().GetOrCreateCache(world, tc.bsp);
            if (!c || !WorldRenderer::Instance().WorldModels().BindGeometry(c))
                continue;
            WorldRenderer::Instance().WorldModels().BindGpuVertexLight(c);

            const size_t n = std::min(c->batches.size(), tc.batches.size());
            for (size_t bi = 0; bi < n; ++bi)
            {
                const WorldBatch &bt = c->batches[bi];
                const StaticVisibleBatchCache &vis = tc.batches[bi];
                if (bt.blend != phase || !vis.indexCount)
                    continue;

                WorldMaterialSystem::Instance().ApplyTexFx(bt);
                Texture *tx = WorldMaterialSystem::Instance().Apply(bt);
                GLStateBindTextureUnit(1, LightmapState().atlas);
                GLUniform1i(g_uTextured, tx && tx->texture ? 1 : 0);
                GLUniform1i(g_uLightmapped, LightmapState().atlas ? 1 : 0);

                // Terrain's compiled vertex/lightmap payload is real lighting.
                // IsTerrainBsp() marks cache batches noLight only to keep them out
                // of ordinary brush assumptions; the stock terrain submission
                // consumes the authored lighting, so explicitly enable it here.
                GLUniform1i(g_uNoLight, 0);
                GLUniform1i(g_uAlphaTest, 0);
                GLUniform1f(g_uAlphaRef, 0.0f);
                GLUniform1i(g_uAlphaFunc, 7);
                WorldMaterialSystem::Instance().ApplyBlend(bt.blend);

                const uintptr_t byteOffset =
                    static_cast<uintptr_t>(vis.firstIndex) * sizeof(uint32);
                glf.DrawElements(GL_TRIANGLES_, static_cast<GLsizei>(vis.indexCount),
                                 GL_UNSIGNED_INT, reinterpret_cast<const void *>(byteOffset));
                ++draws;
                ++materialCalls;
                visiblePolys += vis.visiblePolys;
                tris += vis.tris;
            }
        }

        // Restore the immutable PhysicsBSP stream for the next static phase.
        glf.VertexArrayVertexBuffer(WorldState().vao, 0, WorldState().vbo, 0, sizeof(WorldVertexGPU));
        WorldSurfaceFxSystem::Instance().BindUvOverride(WorldState().vbo);
        if (StaticState().staticPvsEbo)
            glf.VertexArrayElementBuffer(WorldState().vao, StaticState().staticPvsEbo);
        BindGpuVertexLight(StaticState().vertexLightSsbo);
        GLUniform1ui(g_uLegacyDrawFlags, 0u);
        GLUniform1i(g_uWorldModelLightmapGouraud, 0);
        GLUniform1i(g_uWorldModelBakedOnly, 0);
        GLUniform1i(g_uUseGridLight, 0);
        SetIdentityWorldTransform();
    }

    // WorldModel phase classification is owned by WorldModelRenderer.

    static void LogStockWorldModelClasses()
    {
        if (!LogIsSessionEnabled())
            return;
        uint32 opaque = 0, chroma = 0, trans = 0;
        for (WorldModelInstanceCompat *wm : PVSState().visibleWorldModels)
        {
            if (!wm || !(wm->m_Base.m_dwFlags & FLAG_VISIBLE) || !wm->m_pOriginalBsp)
                continue;
            switch (WorldRenderer::Instance().WorldModels().Classify(wm))
            {
            case WorldModelPhase::Opaque:
                ++opaque;
                break;
            case WorldModelPhase::ChromaKey:
                ++chroma;
                break;
            case WorldModelPhase::Translucent:
                ++trans;
                break;
            }
        }

        static uint32 po = 0xFFFFFFFFu, pc = 0xFFFFFFFFu, pt = 0xFFFFFFFFu;
        if (po != opaque || pc != chroma || pt != trans)
        {
            po = opaque;
            pc = chroma;
            pt = trans;
            LOG_SESSION("World3D WM-CLASS stock firstSurface opaque=%u chromakey=%u translucent=%u total=%u",
                        opaque, chroma, trans, opaque + chroma + trans);
        }
    }

    static void ExcludeSceneSkyObjectsFromNormalVisibleSets(SceneDesc *scene)
    {
        if (!scene || !scene->m_pSkyObjects || scene->m_nSkyObjects <= 0)
            return;

        // SceneDesc::m_pSkyObjects is an explicit renderer-owned list.  Stock
        // d3d.ren renders these objects only from the sky pass, through the
        // SURF_SKY portal mask.  They must not also survive in the ordinary
        // WorldTree/PVS visible sets.  A number of AVP2 levels keep their cloud
        // worldmodels spatially near the playable BSP; the WorldTree can therefore
        // return them even while the camera is inside a sealed tunnel.  Rendering
        // them again as normal WorldModels makes chromakey holes look like windows
        // into the exterior sky even though the sky portal pass was correctly
        // skipped.
        std::unordered_set<const LTObjectCompat *> skyObjects;
        skyObjects.reserve(static_cast<size_t>(scene->m_nSkyObjects) * 2u);
        for (int i = 0; i < scene->m_nSkyObjects; ++i)
        {
            auto *obj = reinterpret_cast<const LTObjectCompat *>(scene->m_pSkyObjects[i]);
            if (obj)
                skyObjects.insert(obj);
        }
        if (skyObjects.empty())
            return;

        auto isSky = [&](const void *p) -> bool
        {
            return p && skyObjects.find(reinterpret_cast<const LTObjectCompat *>(p)) != skyObjects.end();
        };

        const size_t oldWM = PVSState().visibleWorldModels.size();
        const size_t oldModels = PVSState().visibleModels.size();
        const size_t oldSprites = PVSState().visibleSprites.size();
        const size_t oldPS = PVSState().visibleParticleSystems.size();
        const size_t oldPG = PVSState().visiblePolyGrids.size();
        const size_t oldLS = PVSState().visibleLineSystems.size();
        const size_t oldCanvas = PVSState().visibleCanvases.size();

        PVSState().visibleWorldModels.erase(
            std::remove_if(PVSState().visibleWorldModels.begin(), PVSState().visibleWorldModels.end(), isSky),
            PVSState().visibleWorldModels.end());
        PVSState().visibleModels.erase(
            std::remove_if(PVSState().visibleModels.begin(), PVSState().visibleModels.end(), isSky),
            PVSState().visibleModels.end());
        PVSState().visibleSprites.erase(
            std::remove_if(PVSState().visibleSprites.begin(), PVSState().visibleSprites.end(), isSky),
            PVSState().visibleSprites.end());
        PVSState().visibleParticleSystems.erase(
            std::remove_if(PVSState().visibleParticleSystems.begin(), PVSState().visibleParticleSystems.end(), isSky),
            PVSState().visibleParticleSystems.end());
        PVSState().visiblePolyGrids.erase(
            std::remove_if(PVSState().visiblePolyGrids.begin(), PVSState().visiblePolyGrids.end(), isSky),
            PVSState().visiblePolyGrids.end());
        PVSState().visibleLineSystems.erase(
            std::remove_if(PVSState().visibleLineSystems.begin(), PVSState().visibleLineSystems.end(), isSky),
            PVSState().visibleLineSystems.end());
        PVSState().visibleCanvases.erase(
            std::remove_if(PVSState().visibleCanvases.begin(), PVSState().visibleCanvases.end(), isSky),
            PVSState().visibleCanvases.end());

        PVSState().visibleWorldModelCount = static_cast<uint32>(PVSState().visibleWorldModels.size());

        const size_t removed = (oldWM - PVSState().visibleWorldModels.size()) +
                               (oldModels - PVSState().visibleModels.size()) +
                               (oldSprites - PVSState().visibleSprites.size()) +
                               (oldPS - PVSState().visibleParticleSystems.size()) +
                               (oldPG - PVSState().visiblePolyGrids.size()) +
                               (oldLS - PVSState().visibleLineSystems.size()) +
                               (oldCanvas - PVSState().visibleCanvases.size());
        if (removed)
        {
            static uint32 budget = 96;
            if (LogIsSessionEnabled() && (budget && (--budget, true)))
                LOG_SESSION("World3D SKY-EXCLUDE normalPVS total=%u wm=%u model=%u sprite=%u particle=%u polygrid=%u lines=%u canvases=%u skyList=%d",
                            static_cast<unsigned>(removed),
                            static_cast<unsigned>(oldWM - PVSState().visibleWorldModels.size()),
                            static_cast<unsigned>(oldModels - PVSState().visibleModels.size()),
                            static_cast<unsigned>(oldSprites - PVSState().visibleSprites.size()),
                            static_cast<unsigned>(oldPS - PVSState().visibleParticleSystems.size()),
                            static_cast<unsigned>(oldPG - PVSState().visiblePolyGrids.size()),
                            static_cast<unsigned>(oldLS - PVSState().visibleLineSystems.size()),
                            static_cast<unsigned>(oldCanvas - PVSState().visibleCanvases.size()),
                            scene->m_nSkyObjects);
        }
    }

    // Deferred WorldModel implementation lives on WorldModelRenderer.
    static bool BuildWorldCache(MainWorldCompat *world, WorldBspCompat *bsp)
    {
        // A new main BSP means a new material-editor scope. Clear materials
        // from the previous map before walking this map's surfaces.
        MaterialAuthoringSystem::Instance().Reset();

        StaticState().cachedBsp = nullptr;
        StaticState().batches.clear();
        for (auto &indices : StaticState().batchIndicesByBlend)
            indices.clear();
        StaticState().cpuVertices.clear();
        StaticState().vertexLightRefs.clear();
        if (StaticState().vertexLightSsbo)
            glf.DeleteBuffers(1, &StaticState().vertexLightSsbo);
        StaticState().vertexLightSsbo = 0;
        if (StaticState().staticPvsEbo)
            glf.DeleteBuffers(1, &StaticState().staticPvsEbo);
        StaticState().staticPvsEbo = 0;
        StaticState().staticPvsEboCapacity = 0;
        if (StaticState().terrainPvsEbo)
            glf.DeleteBuffers(1, &StaticState().terrainPvsEbo);
        StaticState().terrainPvsEbo = 0;
        StaticState().terrainPvsEboCapacity = 0;
        StaticState().terrainVisibleBspCache.clear();
        StaticState().terrainDrawCacheGeneration = 0;
        StaticState().terrainDrawCacheWorld = nullptr;
        StaticState().terrainDrawCacheHadPvs = false;
        StaticState().totalVerts = 0;
        StaticState().totalPolys = 0;
        StaticState().badPolys = 0;
        StaticState().missingTextures = 0;
        StaticState().skippedInvisible = 0;
        StaticState().skippedSky = 0;
        StaticState().solidPolys = 0;
        StaticState().alphaPolys = 0;
        StaticState().addPolys = 0;
        SkyRenderer::Instance().State().portalVertices.clear();
        SkyRenderer::Instance().State().portalSpans.clear();
        StaticState().staticVisibleBatchCache.clear();
        StaticState().staticDrawCacheGeneration = 0;
        StaticState().staticDrawCacheBsp = nullptr;
        StaticState().staticMaskGeneration = 0;
        StaticState().staticMaskGenerationBsp = nullptr;
        PVSState().staticPvsWorld = nullptr;
        PVSState().staticPvsHash = ~0ull;
        ++PVSState().staticPvsGeneration;
        PVSState().haveStaticPVS = false;
        PVSState().visibleLeafCount = 0;
        PVSState().visibleLeafPolyRefs = 0;
        WorldRenderer::Instance().WorldModels().Term();

        if (!bsp || !bsp->m_pPolies || bsp->m_dwPolies == 0 || bsp->m_dwPolies > 2000000)
            return false;

        WorldLightmapSystem::Instance().BuildAtlas(world, bsp);

        std::vector<BatchBuild> builds;
        std::unordered_map<BatchKey, size_t, BatchKeyHash> batchMap;
        builds.reserve(256);

        // Signature -> number of already-seen static polygons at this exact
        // compiled location.  Layer 0 is ordinary opaque geometry; layers 1+
        // are Talon's coplanar multiplicative overlay special case.
        std::unordered_map<uint64_t, uint32> coplanarLayers;
        coplanarLayers.reserve(static_cast<size_t>(bsp->m_dwPolies));
        uint32 coplanarMultiplyPolys = 0;

        uint32 vertexShadeNoLMPolys = 0;
        uint32 gouraudNoLMPolys = 0;
        uint32 flatNoLMPolys = 0;
        uint32 gouraudWithLMPolys = 0;
        uint32 flatWithLMPolys = 0;
        uint32 vertexShadeLMColorVerts = 0;
        uint32 vertexShadeRawFallbackVerts = 0;
        uint32 vertexShadeBlackFallbackVerts = 0;

        for (uint32 pi = 0; pi < bsp->m_dwPolies; ++pi)
        {
            WorldPolyCompat *poly = bsp->m_pPolies[pi];
            if (!poly)
            {
                ++StaticState().badPolys;
                continue;
            }

            const uint32 n = poly->m_wNumVerts;

            static int vertexSourceLogBudget = 16;
            if (LogIsSessionEnabled() && ((vertexSourceLogBudget > 0 && vertexSourceLogBudget--)))
            {
                LOG_SESSION("World3D POLYVERT poly=%p index=%u verts=%u ptr80=%p inline88=%p same=%d",
                            poly,
                            static_cast<unsigned>(poly->m_wIndex),
                            static_cast<unsigned>(n),
                            poly->m_pTJunctionVertices,
                            poly->m_Vertices,
                            poly->m_pTJunctionVertices == poly->m_Vertices ? 1 : 0);
            }

            // This path uses the normal inline span at byte 88. Stock Talon
            // can instead select m_pTJunctionVertices / m_wNumTJunctionVerts when
            // FixTJunc is enabled; see docs/world_poly_layout_trace.md.
            SPolyVertexCompat *pv = poly->m_Vertices;

            if (n < 3 || n > 512 || !poly->m_pSurface)
            {
                ++StaticState().badPolys;
                continue;
            }

            SurfaceCompat *surface = poly->m_pSurface;
            const uint32 surfFlags = surface->m_dwFlags;
            const LTPlaneCompat *polyPlane = poly->m_pPlane
                                                 ? reinterpret_cast<const LTPlaneCompat *>(poly->m_pPlane)
                                                 : nullptr;
            const LTVector polyNormal = polyPlane ? polyPlane->m_vNormal : LTVector{0.0f, 0.0f, 0.0f};
            const bool authoredVertexShade = (surfFlags & (SURF_GOURAUDSHADE | SURF_FLATSHADE)) != 0;

            if (surfFlags & SURF_INVISIBLE)
            {
                ++StaticState().skippedInvisible;
                continue;
            }

            // Sky polygons are portals/masks for the separate sky rendering pass.
            // Drawing their base texture as ordinary geometry produces the large
            // bright/white surfaces seen in the M3.0 screenshot.
            if (surfFlags & SURF_SKY)
            {
                // Sky surfaces are portal masks, not textured world geometry.
                // Preserve their exact triangulated world-space geometry, but keep
                // a per-poly span. Stock Talon only opens sky through sky polygons
                // that survived the current world visibility traversal; drawing
                // every SURF_SKY polygon in the entire PhysicsBSP leaks sky through
                // tunnels/windows and chromakey WorldModels outside the current PVS.
                const uint32 firstSkyVertex = static_cast<uint32>(SkyRenderer::Instance().State().portalVertices.size());
                const SPolyVertexCompat baseSky = pv[0];
                for (uint32 j = 1; j + 1 < n; ++j)
                {
                    const SPolyVertexCompat tri[3] = {baseSky, pv[j], pv[j + 1]};
                    if (!tri[0].m_pPoints || !tri[1].m_pPoints || !tri[2].m_pPoints)
                        continue;
                    for (int k = 0; k < 3; ++k)
                    {
                        const LTVector &p = tri[k].m_pPoints->m_vVec;
                        SkyRenderer::Instance().State().portalVertices.push_back({p.x, p.y, p.z, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
                                                                                  poly->m_vCenter.x, poly->m_vCenter.y, poly->m_vCenter.z,
                                                                                  polyNormal.x, polyNormal.y, polyNormal.z,
                                                                                  0.0f, 0.0f, 0.0f,
                                                                                  0.0f, 0.0f, 0.0f});
                    }
                }
                const uint32 skyVertexCount = static_cast<uint32>(SkyRenderer::Instance().State().portalVertices.size()) - firstSkyVertex;
                if (skyVertexCount)
                    SkyRenderer::Instance().State().portalSpans.push_back({poly, firstSkyVertex, skyVertexCount});
                ++StaticState().skippedSky;
                continue;
            }

            SharedTexture *texture = surface->m_pTexture;
            if (!texture)
                ++StaticState().missingTextures;
            else
                // Register every static-world material while the BSP is built,
                // not merely when it happens to become visible.
                MaterialAuthoringSystem::Instance().Resolve(texture);
            Texture *glTex = TextureManager::Instance().Ensure(texture, false);

            // Static PhysicsBSP transparency authority:
            // Static BSP geometry is not bound to a TranslucentWorldModel object,
            // therefore SURF_TRANSPARENT is never allowed to promote it to alpha
            // blending or alpha-cutout semantics.  Keep authored additive surfaces
            // separate, but treat ordinary transparent-flagged static polygons as
            // fully opaque geometry.
            WorldBlendMode blend = WorldBlendMode::Solid;
            if (surfFlags & SURF_ADDITIVE)
            {
                blend = WorldBlendMode::Additive;
                ++StaticState().addPolys;
            }
            else
            {
                // Special Talon static-BSP behavior: exact duplicate/coplanar
                // geometry is not treated as z-fighting opaque surfaces.  The
                // first polygon is the base; later coincident polygons modulate
                // the already-rendered color, like an extra lightmap/detail layer.
                const uint64_t sig = CoplanarPolySignature(pv, n, polyPlane);
                uint32 &layer = coplanarLayers[sig];
                if (sig != 0 && layer > 0)
                {
                    blend = WorldBlendMode::Multiply;
                    ++coplanarMultiplyPolys;
                }
                ++layer;

                if (surfFlags & SURF_TRANSPARENT)
                    ++StaticState().alphaPolys; // diagnostic only: ignored for coverage
                else
                    ++StaticState().solidPolys;
            }

            SurfaceCompat *animatedSurface = (surfFlags & SURF_SPRITEANIMATE) ? surface : nullptr;
            WorldTexFx texFx = WorldMaterialSystem::Instance().BuildTexFx(surface);
            BatchKey key{texture, animatedSurface, blend, texFx.hash};
            size_t bi;
            auto it = batchMap.find(key);
            if (it == batchMap.end())
            {
                bi = builds.size();
                batchMap.emplace(key, bi);
                builds.push_back({});
                builds.back().texture = texture;
                builds.back().animatedSurface = animatedSurface;
                builds.back().uvNormWidth = (glTex && glTex->scaledWidth) ? float(glTex->scaledWidth) : ((glTex && glTex->width) ? float(glTex->width) : 1.0f);
                builds.back().uvNormHeight = (glTex && glTex->scaledHeight) ? float(glTex->scaledHeight) : ((glTex && glTex->height) ? float(glTex->height) : 1.0f);
                builds.back().blend = blend;
                builds.back().noLight = IsTerrainBsp(bsp) || ((surfFlags & SURF_BRIGHT) != 0);
                builds.back().texFx = texFx;
                builds.back().alphaRef = glTex ? glTex->alphaRef : 0.0f;
            }
            else
            {
                bi = it->second;
            }

            // Talon's "ScaledU/ScaledV" are in texture pixel space.  The D3D11
            // renderer divides by RTexture::m_dwScaledWidth/Height before sampling.
            const float invTexW = (glTex && glTex->scaledWidth) ? (1.0f / static_cast<float>(glTex->scaledWidth)) : ((glTex && glTex->width) ? (1.0f / static_cast<float>(glTex->width)) : 1.0f);
            const float invTexH = (glTex && glTex->scaledHeight) ? (1.0f / static_cast<float>(glTex->scaledHeight)) : ((glTex && glTex->height) ? (1.0f / static_cast<float>(glTex->height)) : 1.0f);

            auto &out = builds[bi].vertices;
            const uint32 polyFirstVertex = static_cast<uint32>(out.size());
            const SPolyVertexCompat base = pv[0];
            bool countedVertexShadeNoLM = false;

            // Deluxe lightmap tangent is a polygon constant.  Bake it into the
            // vertex stream once instead of solving it from dFdx/dFdy(vLMUV) for
            // every covered screen pixel.
            LTVector deluxeLmT{0.0f, 0.0f, 0.0f}, deluxeLmV{0.0f, 0.0f, 0.0f};
            if (poly->m_pPlane)
            {
                auto *deluxePlane = reinterpret_cast<LTPlaneCompat *>(poly->m_pPlane);
                WorldLightmapSystem::SetupPlaneVectors((poly->m_wLMPlaneAndFlags >> 11) & 7u,
                                                       deluxePlane->m_vNormal, deluxeLmT, deluxeLmV);
                const float tl = std::sqrt(deluxeLmT.x * deluxeLmT.x + deluxeLmT.y * deluxeLmT.y + deluxeLmT.z * deluxeLmT.z);
                if (tl > 0.00001f)
                {
                    deluxeLmT.x /= tl;
                    deluxeLmT.y /= tl;
                    deluxeLmT.z /= tl;
                }
            }

            for (uint32 j = 1; j + 1 < n; ++j)
            {
                const SPolyVertexCompat tri[3] = {base, pv[j], pv[j + 1]};

                bool valid = true;
                for (int k = 0; k < 3; ++k)
                    if (!tri[k].m_pPoints)
                        valid = false;
                if (!valid)
                {
                    ++StaticState().badPolys;
                    break;
                }

                LTVector baseTexT{0.0f, 0.0f, 0.0f};
                {
                    const LTVector &p0 = tri[0].m_pPoints->m_vVec;
                    const LTVector &p1 = tri[1].m_pPoints->m_vVec;
                    const LTVector &p2 = tri[2].m_pPoints->m_vVec;
                    const float u0 = tri[0].m_fScaledU * invTexW, v0 = tri[0].m_fScaledV * invTexH, u1 = tri[1].m_fScaledU * invTexW, v1 = tri[1].m_fScaledV * invTexH, u2 = tri[2].m_fScaledU * invTexW, v2 = tri[2].m_fScaledV * invTexH;
                    const float e1x = p1.x - p0.x, e1y = p1.y - p0.y, e1z = p1.z - p0.z, e2x = p2.x - p0.x, e2y = p2.y - p0.y, e2z = p2.z - p0.z;
                    const float du1 = u1 - u0, dv1 = v1 - v0, du2 = u2 - u0, dv2 = v2 - v0, det = du1 * dv2 - du2 * dv1;
                    if (std::fabs(det) > 1e-20f)
                    {
                        const float inv = 1.0f / det;
                        baseTexT.x = (e1x * dv2 - e2x * dv1) * inv;
                        baseTexT.y = (e1y * dv2 - e2y * dv1) * inv;
                        baseTexT.z = (e1z * dv2 - e2z * dv1) * inv;
                        const float tl = std::sqrt(baseTexT.x * baseTexT.x + baseTexT.y * baseTexT.y + baseTexT.z * baseTexT.z);
                        if (tl > 1e-10f)
                        {
                            baseTexT.x /= tl;
                            baseTexT.y /= tl;
                            baseTexT.z /= tl;
                        }
                    }
                }

                for (int k = 0; k < 3; ++k)
                {
                    const LTVector &p = tri[k].m_pPoints->m_vVec;
                    float lmU = 0.0f, lmV = 0.0f;
                    const uint32 sourceVert = (k == 0) ? 0u : ((k == 1) ? j : (j + 1));
                    const bool hasLM = WorldLightmapSystem::Instance().GetUV(world, poly, sourceVert, lmU, lmV);
                    if (hasLM)
                        builds[bi].hasLightmap = true;

                    // LightMap takes precedence over Gouraud/Flat shading in the
                    // stock static-world path.  d3d.ren's lightmap pass builds its
                    // vertices with the renderer's global diffuse colour, not the
                    // SPolyVertex RGB, so a Gouraud flag on a lightmapped polygon
                    // must not become a permanent additive illumination floor.
                    // The per-polygon counters are updated after triangulation.

                    // Talon does not store Gouraud lighting in the texture
                    // lightmap for LightMap=false polygons.  Processor writes the
                    // per-vertex RGB into the LightAnim frame's VertexColours
                    // table (including LightAnim_BASE), and d3d.ren consumes that
                    // as the diffuse vertex colour.  The old OpenGL path ignored
                    // this payload for the main PhysicsBSP and therefore fed the
                    // usually-zero inline SPolyVertex RGB to MODULATE2X.
                    float vr = tri[k].m_nColorR / 255.0f;
                    float vg = tri[k].m_nColorG / 255.0f;
                    float vb = tri[k].m_nColorB / 255.0f;
                    bool vertexLM = false;
                    const bool lightmapColorFallback =
                        !hasLM && ((surfFlags & SURF_LIGHTMAP) != 0);
                    if (!hasLM && (authoredVertexShade || lightmapColorFallback))
                    {
                        vertexLM = WorldRenderer::Instance().Lighting().SampleAnimatedVertexColor(world, poly, sourceVert, vr, vg, vb);
                        if (vertexLM)
                        {
                            ++vertexShadeLMColorVerts;
                            countedVertexShadeNoLM = true;
                        }
                        else
                        {
                            ++vertexShadeRawFallbackVerts;
                            if (vr <= 0.001f && vg <= 0.001f && vb <= 0.001f)
                                ++vertexShadeBlackFallbackVerts;
                        }
                    }

                    out.push_back({p.x, p.y, p.z,
                                   tri[k].m_fScaledU * invTexW,
                                   tri[k].m_fScaledV * invTexH,
                                   lmU, lmV,
                                   vr, vg, vb,
                                   tri[k].m_nColorA / 255.0f,
                                   hasLM ? 1.0f : 0.0f,
                                   vertexLM ? 1.0f : 0.0f,
                                   poly->m_vCenter.x, poly->m_vCenter.y, poly->m_vCenter.z,
                                   polyNormal.x, polyNormal.y, polyNormal.z,
                                   deluxeLmT.x, deluxeLmT.y, deluxeLmT.z,
                                   baseTexT.x, baseTexT.y, baseTexT.z});

                    builds[bi].lightRefs.push_back(
                        vertexLM ? WorldModelVertexLightRef{poly, static_cast<uint16>(sourceVert), 0}
                                 : WorldModelVertexLightRef{});

                    BatchBuild &bb = builds[bi];
                    if (!bb.haveBounds)
                    {
                        bb.minX = bb.maxX = p.x;
                        bb.minY = bb.maxY = p.y;
                        bb.minZ = bb.maxZ = p.z;
                        bb.haveBounds = true;
                    }
                    else
                    {
                        bb.minX = std::min(bb.minX, p.x);
                        bb.maxX = std::max(bb.maxX, p.x);
                        bb.minY = std::min(bb.minY, p.y);
                        bb.maxY = std::max(bb.maxY, p.y);
                        bb.minZ = std::min(bb.minZ, p.z);
                        bb.maxZ = std::max(bb.maxZ, p.z);
                    }
                }
            }

            const uint32 polyVertexCount =
                static_cast<uint32>(out.size()) - polyFirstVertex;
            if (polyVertexCount)
            {
                builds[bi].spans.push_back({poly, polyFirstVertex, polyVertexCount});
                // A compiled lightmap is authoritative when both flags are set.
                // Keep this diagnostic at polygon granularity rather than once per
                // triangulated vertex.
                if ((surfFlags & SURF_LIGHTMAP) && (surfFlags & SURF_GOURAUDSHADE))
                    ++gouraudWithLMPolys;
                if ((surfFlags & SURF_LIGHTMAP) && (surfFlags & SURF_FLATSHADE))
                    ++flatWithLMPolys;
            }

            if (countedVertexShadeNoLM)
            {
                ++vertexShadeNoLMPolys;
                if (surfFlags & SURF_GOURAUDSHADE)
                    ++gouraudNoLMPolys;
                if (surfFlags & SURF_FLATSHADE)
                    ++flatNoLMPolys;
            }

            ++StaticState().totalPolys;
        }

        std::vector<WorldVertexGPU> all;
        size_t total = 0;
        for (const auto &b : builds)
            total += b.vertices.size();

        if (total > 15000000)
        {
            LOG_SESSION("World3D cache rejected: vertices=%u polys=%u bad=%u reason=vertex-limit",
                        static_cast<unsigned>(total), StaticState().totalPolys, StaticState().badPolys);
            return false;
        }

        // Some Talon worlds (notably AVP2 p5s1) carry a PhysicsBSP that
        // is valid for collision/world ownership but has no drawable static
        // surfaces.  The visible level geometry is supplied by WorldModels and
        // discovered through the VisBSP/object phases.  Treating zero generated
        // vertices as a failed cache causes BuildWorldCache to run every frame,
        // rebuilding the 4096x4096 lightmap/compute resources and returning before
        // PVS/WorldModel submission -- yielding both a black screen and ~5 FPS.
        //
        // An empty cache is valid as long as the BSP itself parsed cleanly.  Keep
        // the lightmap atlas built above (WorldModels use it), detach any previous
        // level's static VBO, upload any sky portal geometry we may have collected,
        // and mark this BSP cached so normal scene traversal can continue.
        if (total == 0)
        {
            if (WorldState().vbo)
            {
                glf.DeleteBuffers(1, &WorldState().vbo);
                WorldState().vbo = 0;
            }
            glf.VertexArrayVertexBuffer(WorldState().vao, 0, 0, 0, sizeof(WorldVertexGPU));

            SkyRenderer::Instance().UploadPortalGeometry();

            StaticState().totalVerts = 0;
            StaticState().cachedBsp = bsp;
            WorldSurfaceFxSystem::Instance().RegisterTargets(bsp, StaticState().batches, true);

            LOG_SESSION("World3D CACHE-EMPTY world='%s' flags=%08X bsp=%p polies=%u accepted=%u bad=%u skipInvisible=%u skipSky=%u reason=no-drawable-static-geometry continuation=PVS/WORLDMODELS",
                        bsp->m_szWorldName, bsp->m_dwWorldInfoFlags, bsp, bsp->m_dwPolies,
                        StaticState().totalPolys, StaticState().badPolys,
                        StaticState().skippedInvisible, StaticState().skippedSky);
            LOG_SESSION("World3D MATERIAL/LIGHT: lmPolys=%u lmAnims=%u atlas=%u (retained for WorldModels)",
                        LightmapState().lightmapPolys, LightmapState().lightmapAnims, LightmapState().atlas);
            return true;
        }

        all.reserve(total);
        StaticState().vertexLightRefs.reserve(total);
        StaticState().batches.reserve(builds.size());

        for (auto &b : builds)
        {
            if (b.vertices.empty())
                continue;
            WorldBatch wb{};
            wb.texture = b.texture;
            wb.animatedSurface = b.animatedSurface;
            wb.uvNormWidth = b.uvNormWidth;
            wb.uvNormHeight = b.uvNormHeight;
            wb.firstVertex = static_cast<uint32>(all.size());
            wb.vertexCount = static_cast<uint32>(b.vertices.size());
            wb.blend = b.blend;
            wb.alphaRef = b.alphaRef;
            wb.noLight = b.noLight;
            wb.hasLightmap = b.hasLightmap;
            wb.extraShade = false;
            wb.texFx = b.texFx;
            wb.minX = b.minX;
            wb.minY = b.minY;
            wb.minZ = b.minZ;
            wb.maxX = b.maxX;
            wb.maxY = b.maxY;
            wb.maxZ = b.maxZ;
            wb.spans.reserve(b.spans.size());
            for (const PolySpan &span : b.spans)
                wb.spans.push_back({span.poly, wb.firstVertex + span.firstVertex, span.vertexCount});
            all.insert(all.end(), b.vertices.begin(), b.vertices.end());
            if (b.lightRefs.size() == b.vertices.size())
                StaticState().vertexLightRefs.insert(StaticState().vertexLightRefs.end(), b.lightRefs.begin(), b.lightRefs.end());
            else
                StaticState().vertexLightRefs.insert(StaticState().vertexLightRefs.end(), b.vertices.size(), WorldModelVertexLightRef{});
            const uint32 batchIndex = static_cast<uint32>(StaticState().batches.size());
            StaticState().batchIndicesByBlend[static_cast<size_t>(wb.blend)].push_back(batchIndex);
            StaticState().batches.push_back(std::move(wb));
        }

        const GLsizeiptr bytes = static_cast<GLsizeiptr>(all.size() * sizeof(WorldVertexGPU));

        if (WorldState().vbo)
            glf.DeleteBuffers(1, &WorldState().vbo);
        glf.CreateBuffers(1, &WorldState().vbo);
        glf.NamedBufferStorage(WorldState().vbo, bytes, all.data(), GL_DYNAMIC_STORAGE_BIT_);
        StaticState().cpuVertices = all;

        WorldRenderer::Instance().WorldModels().BuildGpuVertexLightBuffer(world, StaticState().vertexLightRefs, StaticState().vertexLightSsbo, bsp->m_szWorldName);

        glf.VertexArrayVertexBuffer(WorldState().vao, 0, WorldState().vbo, 0, sizeof(WorldVertexGPU));

        SkyRenderer::Instance().UploadPortalGeometry();

        StaticState().totalVerts = static_cast<uint32>(all.size());
        StaticState().cachedBsp = bsp;
        WorldSurfaceFxSystem::Instance().RegisterTargets(bsp, StaticState().batches, true);

        LOG_SESSION("World3D CACHE world='%s' flags=%08X bsp=%p polies=%u accepted=%u bad=%u surfaces=%u points=%u batches=%u vertices=%u missingTex=%u skipInvisible=%u skipSky=%u solid=%u alpha=%u add=%u coplanarMul=%u",
                    bsp->m_szWorldName, bsp->m_dwWorldInfoFlags, bsp, bsp->m_dwPolies,
                    StaticState().totalPolys, StaticState().badPolys, bsp->m_dwSurfaces, bsp->m_dwPoints,
                    static_cast<unsigned>(StaticState().batches.size()), StaticState().totalVerts, StaticState().missingTextures,
                    StaticState().skippedInvisible, StaticState().skippedSky, StaticState().solidPolys, StaticState().alphaPolys, StaticState().addPolys, coplanarMultiplyPolys);
        LOG_SESSION("World3D SKY PORTALS polys=%u verts=%u skyObjectsPending=SceneDesc",
                    StaticState().skippedSky, unsigned(SkyRenderer::Instance().State().portalVertices.size()));
        LOG_SESSION("World3D MATERIAL/LIGHT: lmPolys=%u lmAnims=%u atlas=%u", LightmapState().lightmapPolys, LightmapState().lightmapAnims, LightmapState().atlas);
        LOG_SESSION("World3D STATIC VERTEX-LIGHT shadedNoLMPolys=%u gouraud=%u flat=%u lightAnimVerts=%u rawFallbackVerts=%u blackFallbackVerts=%u source=LightAnim::VertexColours",
                    vertexShadeNoLMPolys, gouraudNoLMPolys, flatNoLMPolys,
                    vertexShadeLMColorVerts, vertexShadeRawFallbackVerts, vertexShadeBlackFallbackVerts);
        LOG_SESSION("World3D STATIC LIGHTMODE gouraud+lightmap=%u flat+lightmap=%u precedence=LIGHTMAP d3d=global-diffuse/no-SPolyRGB",
                    gouraudWithLMPolys, flatWithLMPolys);

        return true;
    }

    // Dynamic world-light GPU submission is owned by WorldDynamicLightSystem.

    // World/BSP geometry in Talon uses the normal rasterizer back-face test.
    // Keep culling scoped to world geometry only; models, sprites, sky and UI all
    // retain their independently validated state.  AVP2's cached triangles are
    // front-facing with clockwise winding after the renderer's mirrored world transform.
    static void EnableWorldBackfaceCulling()
    {
        GLStateFrontFace(GL_CW);
        GLStateCullFace(GL_BACK);
        GLStateEnable(GL_CULL_FACE);
    }

    static void DisableWorldBackfaceCulling()
    {
        GLStateDisable(GL_CULL_FACE);
    }

}

void WorldRenderer::SetupScene(SceneDesc *scene)
{
    const int vx = scene->m_rcViewport.m_nLeft;
    const int vyTop = scene->m_rcViewport.m_nTop;
    const int vw = std::max(1, scene->m_rcViewport.m_nRight - scene->m_rcViewport.m_nLeft);
    const int vh = std::max(1, scene->m_rcViewport.m_nBottom - scene->m_rcViewport.m_nTop);
    const int vy = RendererCore::Instance().Height() - (vyTop + vh);
    glViewport(vx, vy, vw, vh);

    GLStateEnable(GL_DEPTH_TEST);
    GLStateDepthFunc(GL_LEQUAL);
    GLStateDepthMask(GL_TRUE);
    GLStateDisable(GL_BLEND);
    GLStateDisable(GL_CULL_FACE);

    WorldState().worldShader->Use();
    GLStateBindVertexArray(WorldState().vao);
    BindGpuVertexLight(StaticState().vertexLightSsbo);
    WorldSurfaceFxSystem::Instance().BindUvOverride(WorldState().vbo);
    WorldDynamicLightSystem::Instance().Disable();

    FrameConstants::Instance().Apply(scene, 1.0f, std::max(2.0f, scene->m_fFarZ));
    GLUniform1i(g_uFogEnabled, g_fogState.enabled ? 1 : 0);
    GLUniform1i(g_uFogAdditive, 0);
    GLUniform1i(g_uVFogEnabled, g_fogState.vFog ? 1 : 0);
    GLUniform1f(g_uVFogMinY, g_fogState.vFogMinY);
    GLUniform1f(g_uVFogMaxY, g_fogState.vFogMaxY);
    GLUniform1f(g_uVFogMinYVal, g_fogState.vFogMinYVal);
    GLUniform1f(g_uVFogMaxYVal, g_fogState.vFogMaxYVal);
    GLUniform1f(g_uVFogDensity, g_fogState.vFogDensity);
    GLUniform1f(g_uVFogMax, g_fogState.vFogMax);
    if (DeluxeLightmapBaker::Instance().Texture())
        GLStateBindTextureUnit(5, DeluxeLightmapBaker::Instance().Texture());
    if (g_uDeluxeEnabled >= 0)
        GLUniform1i(g_uDeluxeEnabled, (DeluxeLightmapBaker::Instance().SpecularEnabled() && DeluxeLightmapBaker::Instance().Texture()) ? 1 : 0);
    if (g_uDeluxeDebugView >= 0)
        GLUniform1i(g_uDeluxeDebugView, (DeluxeLightmapBaker::Instance().DebugDirectionView() && DeluxeLightmapBaker::Instance().Texture()) ? 1 : 0);
    if (g_uDeluxeSpecularStrength >= 0)
        GLUniform1f(g_uDeluxeSpecularStrength, DeluxeLightmapBaker::Instance().SpecularStrength());
    if (g_uDeluxeSpecularPower >= 0)
        GLUniform1f(g_uDeluxeSpecularPower, DeluxeLightmapBaker::Instance().SpecularPower());
    if (g_uDeluxeGeneratedNormalEnabled >= 0)
        GLUniform1i(g_uDeluxeGeneratedNormalEnabled, DeluxeLightmapBaker::Instance().GeneratedNormalEnabled() ? 1 : 0);
    if (g_uDeluxeNormalStrength >= 0)
        GLUniform1f(g_uDeluxeNormalStrength, DeluxeLightmapBaker::Instance().NormalStrength());
    if (g_uDeluxeNormalBlack >= 0)
        GLUniform1f(g_uDeluxeNormalBlack, DeluxeLightmapBaker::Instance().NormalBlack());
    if (g_uDeluxeNormalWhite >= 0)
        GLUniform1f(g_uDeluxeNormalWhite, DeluxeLightmapBaker::Instance().NormalWhite());
    if (g_uDeluxeNormalInvert >= 0)
        GLUniform1i(g_uDeluxeNormalInvert, DeluxeLightmapBaker::Instance().NormalInvert() ? 1 : 0);
    if (g_uDeluxeNormalInvertX >= 0)
        GLUniform1i(g_uDeluxeNormalInvertX, DeluxeLightmapBaker::Instance().NormalInvertX() ? 1 : 0);
    if (g_uDeluxeNormalInvertY >= 0)
        GLUniform1i(g_uDeluxeNormalInvertY, DeluxeLightmapBaker::Instance().NormalInvertY() ? 1 : 0);
    if (g_uDeluxeNormalInvertZ >= 0)
        GLUniform1i(g_uDeluxeNormalInvertZ, DeluxeLightmapBaker::Instance().NormalInvertZ() ? 1 : 0);
    if (g_uDeluxeNormalBand >= 0)
        GLUniform1i(g_uDeluxeNormalBand, DeluxeLightmapBaker::Instance().NormalBand());
    if (g_uDeluxeSpecLightColorInfluence >= 0)
        GLUniform1f(g_uDeluxeSpecLightColorInfluence, DeluxeLightmapBaker::Instance().SpecLightColorInfluence());
    if (g_uDeluxeGeneratedSpecularEnabled >= 0)
        GLUniform1i(g_uDeluxeGeneratedSpecularEnabled, DeluxeLightmapBaker::Instance().GeneratedSpecularEnabled() ? 1 : 0);
    if (g_uDeluxeSpecMapStrength >= 0)
        GLUniform1f(g_uDeluxeSpecMapStrength, DeluxeLightmapBaker::Instance().SpecMapStrength());
    if (g_uDeluxeSpecBlack >= 0)
        GLUniform1f(g_uDeluxeSpecBlack, DeluxeLightmapBaker::Instance().SpecBlack());
    if (g_uDeluxeSpecWhite >= 0)
        GLUniform1f(g_uDeluxeSpecWhite, DeluxeLightmapBaker::Instance().SpecWhite());
    if (g_uDeluxeSpecInvert >= 0)
        GLUniform1i(g_uDeluxeSpecInvert, DeluxeLightmapBaker::Instance().SpecInvert() ? 1 : 0);

    auto *mw = (scene->m_pRenderContext) ? reinterpret_cast<MainWorldCompat *>(scene->m_pRenderContext->m_pMainWorld) : nullptr;
    if (mw)
    {
        const LightTableCompat &lt = mw->m_LightTable;
        GLUniform3f(g_uLightGridDims,
                    static_cast<float>(lt.m_adwLookupSize[0]),
                    static_cast<float>(lt.m_adwLookupSize[1]),
                    static_cast<float>(lt.m_adwLookupSize[2]));
        GLUniform3f(g_uLightGridLookupStart,
                    lt.m_vLookupStart.x, lt.m_vLookupStart.y, lt.m_vLookupStart.z);
        GLUniform3f(g_uLightGridReciBlock,
                    lt.m_vReciBlockSize.x, lt.m_vReciBlockSize.y, lt.m_vReciBlockSize.z);
        GLUniform1i(g_uHighQualityLightGrid,
                    WorldRenderer::Instance().Lighting().IsHighQualityLightGridEnabled() ? 1 : 0);
    }

    // Original d3d.ren uses SceneDesc::m_vGlobalVertexTint as the RGB
    // multiplicative scale, and m_vGlobalWMAmbient (0..255 domain) as an
    // additive term on top of the sampled LightTable color.
    GLUniform3f(g_uGlobalVertexTint,
                scene->m_vGlobalVertexTint.x,
                scene->m_vGlobalVertexTint.y,
                scene->m_vGlobalVertexTint.z);
    GLUniform1i(g_uAlienInvertHack,
                Console::Instance().GetFloat("InvertHack", 0.0f) != 0.0f ? 1 : 0);
    GLUniform3f(g_uGlobalWMAmbient,
                scene->m_vGlobalWMAmbient.x,
                scene->m_vGlobalWMAmbient.y,
                scene->m_vGlobalWMAmbient.z);
    GLUniform1i(g_uUseGridLight, 0);
    GLUniform1ui(g_uLegacyDrawFlags, 0u);
    GLUniform1i(g_uWorldModelLightmapGouraud, 0);
    GLUniform1i(g_uWorldModelBakedOnly, 0);
    GLUniform1i(g_uLightmapSaturate, Console::Instance().GetFloat("Saturate", 0.0f) != 0.0f ? 1 : 0);

    if (LogIsSessionEnabled())
    {
        static float lastTint[3] = {-9999, -9999, -9999};
        static float lastAmb[3] = {-9999, -9999, -9999};
        const bool changed =
            fabsf(lastTint[0] - scene->m_vGlobalVertexTint.x) > 0.001f ||
            fabsf(lastTint[1] - scene->m_vGlobalVertexTint.y) > 0.001f ||
            fabsf(lastTint[2] - scene->m_vGlobalVertexTint.z) > 0.001f ||
            fabsf(lastAmb[0] - scene->m_vGlobalWMAmbient.x) > 0.001f ||
            fabsf(lastAmb[1] - scene->m_vGlobalWMAmbient.y) > 0.001f ||
            fabsf(lastAmb[2] - scene->m_vGlobalWMAmbient.z) > 0.001f;
        if (changed)
        {
            lastTint[0] = scene->m_vGlobalVertexTint.x;
            lastTint[1] = scene->m_vGlobalVertexTint.y;
            lastTint[2] = scene->m_vGlobalVertexTint.z;
            lastAmb[0] = scene->m_vGlobalWMAmbient.x;
            lastAmb[1] = scene->m_vGlobalWMAmbient.y;
            lastAmb[2] = scene->m_vGlobalWMAmbient.z;
            LOG_SESSION("World3D LIGHTGLOBALS vertexTint=(%.3f %.3f %.3f) wmAmbient=(%.3f %.3f %.3f)",
                        lastTint[0], lastTint[1], lastTint[2], lastAmb[0], lastAmb[1], lastAmb[2]);
        }
    }

    SetIdentityWorldTransform();
}

bool WorldRenderer::Init()
{
    WorldPVS::Instance().Reset();
    auto *shader = avp2::render::ShaderManager::Instance().CreateGraphicsFromResources("world.main",
                                                                                       avp2::render::ShaderResourceId::WorldVertex,
                                                                                       avp2::render::ShaderResourceId::WorldFragment);
    if (!shader)
        return false;
    WorldState().worldShader = shader;
    WorldMaterialSystem::Instance().Init(shader);

    g_uCameraPos = shader->Uniform("uCameraPos");
    g_uCameraQuat = shader->Uniform("uCameraQuat");
    g_uTanHalfFovX = shader->Uniform("uTanHalfFovX");
    g_uTanHalfFovY = shader->Uniform("uTanHalfFovY");
    g_uNearZ = shader->Uniform("uNearZ");
    g_uFarZ = shader->Uniform("uFarZ");
    g_uTextured = shader->Uniform("uTextured");
    g_uLightmapped = shader->Uniform("uLightmapped");
    g_uDeluxeEnabled = shader->Uniform("uDeluxeEnabled");
    g_uDeluxeDebugView = shader->Uniform("uDeluxeDebugView");
    g_uDeluxeSpecularStrength = shader->Uniform("uDeluxeSpecularStrength");
    g_uDeluxeSpecularPower = shader->Uniform("uDeluxeSpecularPower");
    g_uDeluxeGeneratedNormalEnabled = shader->Uniform("uDeluxeGeneratedNormalEnabled");
    g_uDeluxeNormalStrength = shader->Uniform("uDeluxeNormalStrength");
    g_uDeluxeNormalBlack = shader->Uniform("uDeluxeNormalBlack");
    g_uDeluxeNormalWhite = shader->Uniform("uDeluxeNormalWhite");
    g_uDeluxeNormalInvert = shader->Uniform("uDeluxeNormalInvert");
    g_uDeluxeNormalInvertX = shader->Uniform("uDeluxeNormalInvertX");
    g_uDeluxeNormalInvertY = shader->Uniform("uDeluxeNormalInvertY");
    g_uDeluxeNormalInvertZ = shader->Uniform("uDeluxeNormalInvertZ");
    g_uDeluxeNormalBand = shader->Uniform("uDeluxeNormalBand");
    g_uDeluxeSpecLightColorInfluence = shader->Uniform("uDeluxeSpecLightColorInfluence");
    g_uDeluxeGeneratedSpecularEnabled = shader->Uniform("uDeluxeGeneratedSpecularEnabled");
    g_uDeluxeSpecMapStrength = shader->Uniform("uDeluxeSpecMapStrength");
    g_uDeluxeSpecBlack = shader->Uniform("uDeluxeSpecBlack");
    g_uDeluxeSpecWhite = shader->Uniform("uDeluxeSpecWhite");
    g_uDeluxeSpecInvert = shader->Uniform("uDeluxeSpecInvert");
    g_uNoLight = shader->Uniform("uNoLight");
    g_uAlphaTest = shader->Uniform("uAlphaTest");
    g_uAlphaRef = shader->Uniform("uAlphaRef");
    g_uAlphaFunc = shader->Uniform("uAlphaFunc");
    g_uFullBrightTexture = shader->Uniform("uFullBrightTexture");
    g_uUseWorld = shader->Uniform("uUseWorld");
    g_uWorld = shader->Uniform("uWorld");
    g_uObjectColor = shader->Uniform("uObjectColor");
    g_uLegacyDrawFlags = shader->Uniform("uLegacyDrawFlags");
    g_uSkyDxt5AlphaOnly = shader->Uniform("uSkyDxt5AlphaOnly");
    g_uSkyHorizonFogGradient = shader->Uniform("uSkyHorizonFogGradient");
    g_uSkyClipCameraSpace = shader->Uniform("uSkyClipCameraSpace");
    g_uUseWmDrawState = shader->Uniform("uUseWmDrawState");
    g_uUseGridLight = shader->Uniform("uUseGridLight");
    g_uLightGridDims = shader->Uniform("uLightGridDims");
    g_uLightGridLookupStart = shader->Uniform("uLightGridLookupStart");
    g_uLightGridReciBlock = shader->Uniform("uLightGridReciBlock");
    g_uHighQualityLightGrid = shader->Uniform("uHighQualityLightGrid");
    g_uGlobalVertexTint = shader->Uniform("uGlobalVertexTint");
    g_uAlienInvertHack = shader->Uniform("uAlienInvertHack");
    g_uGlobalWMAmbient = shader->Uniform("uGlobalWMAmbient");
    g_uGpuVertexLight = shader->Uniform("uGpuVertexLight");
    g_uVertexLightVertexBase = shader->Uniform("uVertexLightVertexBase");
    g_uVertexLightDataBase = shader->Uniform("uVertexLightDataBase");

    g_uStaticMaterialIndexFromBaseInstance = shader->Uniform("uStaticMaterialIndexFromBaseInstance");
    g_uWorldModelLightmapGouraud = shader->Uniform("uWorldModelLightmapGouraud");
    g_uWorldModelBakedOnly = shader->Uniform("uWorldModelBakedOnly");
    g_uLightmapSaturate = shader->Uniform("uLightmapSaturate");
    g_uFogEnabled = shader->Uniform("uFogEnabled");
    g_uFogColor = shader->Uniform("uFogColor");
    g_uFogNear = shader->Uniform("uFogNear");
    g_uFogFar = shader->Uniform("uFogFar");
    g_uFogAdditive = shader->Uniform("uFogAdditive");
    g_uVFogEnabled = shader->Uniform("uVFogEnabled");
    g_uVFogMinY = shader->Uniform("uVFogMinY");
    g_uVFogMaxY = shader->Uniform("uVFogMaxY");
    g_uVFogMinYVal = shader->Uniform("uVFogMinYVal");
    g_uVFogMaxYVal = shader->Uniform("uVFogMaxYVal");
    g_uVFogDensity = shader->Uniform("uVFogDensity");
    g_uVFogMax = shader->Uniform("uVFogMax");

    glf.CreateVertexArrays(1, &WorldState().vao);

    glf.EnableVertexArrayAttrib(WorldState().vao, 0);
    glf.VertexArrayAttribFormat(WorldState().vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, x));
    glf.VertexArrayAttribBinding(WorldState().vao, 0, 0);

    glf.EnableVertexArrayAttrib(WorldState().vao, 1);
    glf.VertexArrayAttribFormat(WorldState().vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, u));
    glf.VertexArrayAttribBinding(WorldState().vao, 1, 0);

    glf.EnableVertexArrayAttrib(WorldState().vao, 2);
    glf.VertexArrayAttribFormat(WorldState().vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, lmU));
    glf.VertexArrayAttribBinding(WorldState().vao, 2, 0);

    glf.EnableVertexArrayAttrib(WorldState().vao, 3);
    glf.VertexArrayAttribFormat(WorldState().vao, 3, 4, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, r));
    glf.VertexArrayAttribBinding(WorldState().vao, 3, 0);

    glf.EnableVertexArrayAttrib(WorldState().vao, 4);
    glf.VertexArrayAttribFormat(WorldState().vao, 4, 1, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, hasLightmap));
    glf.VertexArrayAttribBinding(WorldState().vao, 4, 0);

    glf.EnableVertexArrayAttrib(WorldState().vao, 5);
    glf.VertexArrayAttribFormat(WorldState().vao, 5, 1, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, hasVertexLight));
    glf.VertexArrayAttribBinding(WorldState().vao, 5, 0);

    glf.EnableVertexArrayAttrib(WorldState().vao, 6);
    glf.VertexArrayAttribFormat(WorldState().vao, 6, 3, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, polyCenterX));
    glf.VertexArrayAttribBinding(WorldState().vao, 6, 0);

    glf.EnableVertexArrayAttrib(WorldState().vao, 7);
    glf.VertexArrayAttribFormat(WorldState().vao, 7, 3, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, normalX));
    glf.VertexArrayAttribBinding(WorldState().vao, 7, 0);

    glf.EnableVertexArrayAttrib(WorldState().vao, 8);
    glf.VertexArrayAttribFormat(WorldState().vao, 8, 3, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, lmTangentX));
    glf.VertexArrayAttribBinding(WorldState().vao, 8, 0);

    glf.EnableVertexArrayAttrib(WorldState().vao, 9);
    glf.VertexArrayAttribFormat(WorldState().vao, 9, 3, GL_FLOAT, GL_FALSE, offsetof(WorldVertexGPU, baseTangentX));
    glf.VertexArrayAttribBinding(WorldState().vao, 9, 0);
    if (!WorldDynamicLightSystem::Instance().Init(shader))
        LOG_SESSION("WorldRenderer::Init: dynamic world light SSBO unavailable; world dynamic lighting disabled");

    LOG_SESSION("WorldRenderer::Init: M3.18 core46 + D3D sky clip v81 + baked Gouraud no-LM BSP lighting v85 ready");
    return true;
}

void WorldRenderer::Term()
{
    WorldMaterialSystem::Instance().Reset();
    WorldPVS::Instance().Reset();
    WorldDynamicLightSystem::Instance().Term();
    WorldRenderer::Instance().WorldModels().Term();
    WorldLightmapSystem::Instance().DestroyGpuResources();
    avp2::render::ShaderManager::Instance().Release("world.lightmap_compute");
    LightmapState().computeShader = nullptr;
    if (LightmapState().lightGridTexture)
        GLStateDeleteTextures(1, &LightmapState().lightGridTexture);
    LightmapState().lightGridTexture = 0;
    LightmapState().lightGridWorld = nullptr;
    LightmapState().lightGridX = LightmapState().lightGridY = LightmapState().lightGridZ = 0;
    if (LightmapState().atlas)
        GLStateDeleteTextures(1, &LightmapState().atlas);
    DeluxeLightmapBaker::Instance().Term();
    if (WorldState().vbo)
        glf.DeleteBuffers(1, &WorldState().vbo);
    if (StaticState().vertexLightSsbo)
        glf.DeleteBuffers(1, &StaticState().vertexLightSsbo);
    StaticState().vertexLightSsbo = 0;
    if (StaticState().staticPvsEbo)
        glf.DeleteBuffers(1, &StaticState().staticPvsEbo);
    StaticState().staticPvsEbo = 0;
    StaticState().staticPvsEboCapacity = 0;
    if (StaticState().terrainPvsEbo)
        glf.DeleteBuffers(1, &StaticState().terrainPvsEbo);
    StaticState().terrainPvsEbo = 0;
    StaticState().terrainPvsEboCapacity = 0;
    SkyRenderer::Instance().Term();
    if (WorldState().vao)
        GLStateDeleteVertexArrays(1, &WorldState().vao);
    avp2::render::ShaderManager::Instance().Release("world.main");
    WorldState().vbo = WorldState().vao = 0;
    WorldState().worldShader = nullptr;
    LightmapState().atlas = 0;
    LightmapState().tiles.clear();
    PVSState().visibleStaticPolys.clear();
    PVSState().visibleStaticMaskBsp = nullptr;
    PVSState().visibleStaticMask.clear();
    StaticState().staticVisibleBatchCache.clear();
    StaticState().staticDrawCacheGeneration = 0;
    StaticState().staticDrawCacheBsp = nullptr;
    StaticState().terrainVisibleBspCache.clear();
    StaticState().terrainDrawCacheGeneration = 0;
    StaticState().terrainDrawCacheWorld = nullptr;
    StaticState().terrainDrawCacheHadPvs = false;
    StaticState().staticMaskGeneration = 0;
    StaticState().staticMaskGenerationBsp = nullptr;
    StaticState().cachedBsp = nullptr;
    StaticState().batches.clear();
    for (auto &indices : StaticState().batchIndicesByBlend)
        indices.clear();
    StaticState().cpuVertices.clear();
    StaticState().vertexLightRefs.clear();
}

int WorldRenderer::RenderScene(SceneDesc *scene)
{
    if (!scene || scene->m_nDrawMode == DRAWMODE_OBJECTLIST)
        return RENDER_OK;

    Renderer2D::Instance().Flush();

    WorldBspCompat *bsp = FindMainBsp(scene);
    if (!bsp)
    {
        static int noWorldBudget = 16;
        if (LogIsSessionEnabled() && ((noWorldBudget > 0 && noWorldBudget--)))
            LOG_SESSION("World3D: drawMode=%d has no usable main BSP context=%p mainWorld=%p",
                        scene->m_nDrawMode, scene->m_pRenderContext,
                        scene->m_pRenderContext ? scene->m_pRenderContext->m_pMainWorld : nullptr);
        return RENDER_OK;
    }

    auto *mainWorld = reinterpret_cast<MainWorldCompat *>(scene->m_pRenderContext->m_pMainWorld);

    // Cache Talon's current global/static sunlight for the manual deluxe bake.
    // Model lighting treats -m_vGlobalLightDir as the incoming direction.
    DeluxeLightmapBaker::Instance().SetSunlight(scene->m_vGlobalLightDir, scene->m_vGlobalLightColor);

    if (bsp != StaticState().cachedBsp && !BuildWorldCache(mainWorld, bsp))
        return RENDER_OK;

    // Original Talon d3d.ren behavior:
    // WorldTree::DoVisQuery calls a Leaf callback which walks Leaf::m_pPolies.
    // Those polygon pointers are the static BSP visibility set for this frame.
    if (WorldBspCompat *vis = FindVisBsp(mainWorld))
    {
        WorldPVS::Instance().Query(mainWorld, vis, scene);
        WorldPVS::Instance().AuditObjectManager(mainWorld, scene->m_vPos);

        // Exact stock selector at d3d.ren 0x10039510:
        // MainWorld::m_dwFlags is +0x180. If bit 0x2 is clear, stock calls
        // 0x10039540(1), which walks the complete engine object manager via
        // 0x10039100 instead of relying only on WorldTree PVS. Merge that
        // source here while retaining the visible-leaf static polygon set.
        if ((mainWorld->m_dwFlags & 0x2u) == 0)
            WorldPVS::Instance().MergeObjectManager(mainWorld);

        static MainWorldCompat *s_pathWorld = nullptr;
        static uint32 s_pathFlags = 0xFFFFFFFFu;
        if (LogIsSessionEnabled() && (s_pathWorld != mainWorld || s_pathFlags != mainWorld->m_dwFlags))
        {
            s_pathWorld = mainWorld;
            s_pathFlags = mainWorld->m_dwFlags;
            LOG_SESSION("World3D STOCK-OBJECT-SOURCE world=%p flags=%08X path=%s",
                        mainWorld, mainWorld->m_dwFlags,
                        (mainWorld->m_dwFlags & 0x2u) ? "WORLDTREE-PVS" : "FULL-OBJECT-MANAGER");
        }
    }
    else
    {
        PVSState().haveStaticPVS = false;
        PVSState().visibleStaticPolys.clear();
        PVSState().visibleWorldModels.clear();
        PVSState().visibleWorldModelCount = 0;
        PVSState().visibleModels.clear();
        PVSState().visibleDynamicLights.clear();
        PVSState().visibleSprites.clear();
        PVSState().visibleParticleSystems.clear();
        PVSState().visiblePolyGrids.clear();
        PVSState().visibleLineSystems.clear();
        PVSState().visibleCanvases.clear();
    }

    // Convert Talon's exact visible polygon pointer set into a dense mask once
    // per scene.  The render hot path then avoids one unordered_set lookup for
    // every cached BSP polygon span.
    WorldStaticGeometryRenderer::Instance().RebuildVisibilityMask(bsp);
    WorldStaticGeometryRenderer::Instance().RebuildVisibleBatchCache(bsp);
    RebuildTerrainVisibleBatchCache(mainWorld);

    // In d3d.ren InvertHack is consulted only by the final
    // fullscreen pass at 0x10015240; it never disables or substitutes the
    // static lightmap renderer.  Keep a transition/periodic audit here so an
    // Alien-vision regression can be distinguished from the post effect
    // without perturbing the actual lightmap path.
    if (LogIsSessionEnabled())
    {
        const bool alienInvertAudit = Console::Instance().GetFloat("InvertHack", 0.0f) != 0.0f;
        if (alienInvertAudit)
        {
            static uint32 s_alienAuditFrame = 0;
            ++s_alienAuditFrame;
            if (s_alienAuditFrame == 1 || (s_alienAuditFrame % 120u) == 0u)
            {
                uint32 cachedLmBatches = 0;
                uint32 cachedLmSpans = 0;
                uint32 visibleLmPolys = 0;
                for (size_t bi = 0; bi < StaticState().batches.size(); ++bi)
                {
                    const WorldBatch &b = StaticState().batches[bi];
                    if (!b.hasLightmap)
                        continue;
                    ++cachedLmBatches;
                    cachedLmSpans += static_cast<uint32>(b.spans.size());
                    if (!PVSState().haveStaticPVS)
                        visibleLmPolys += static_cast<uint32>(b.spans.size());
                    else if (bi < StaticState().staticVisibleBatchCache.size())
                        visibleLmPolys += StaticState().staticVisibleBatchCache[bi].visiblePolys;
                }

                LOG_SESSION("ALIEN-LIGHTMAP audit atlas=%u lmPolys=%u cachedLmBatches=%u cachedLmSpans=%u visibleLmPolys=%u pvs=%u tint=(%.3f %.3f %.3f) scale=(%.3f %.3f %.3f)",
                            LightmapState().atlas, LightmapState().lightmapPolys, cachedLmBatches, cachedLmSpans, visibleLmPolys,
                            PVSState().haveStaticPVS ? 1u : 0u,
                            scene->m_vGlobalVertexTint.x, scene->m_vGlobalVertexTint.y, scene->m_vGlobalVertexTint.z,
                            scene->m_vGlobalLightScale.x, scene->m_vGlobalLightScale.y, scene->m_vGlobalLightScale.z);
            }
        }
        else
        {
            static bool s_loggedAlienOff = false;
            if (LogIsSessionEnabled() && (!s_loggedAlienOff))
            {
                s_loggedAlienOff = true;
                LOG_SESSION("ALIEN-LIGHTMAP audit InvertHack=0 stock path=no lightmap override");
            }
        }
    }

    // Sky objects have their own SceneDesc list/pass and are not ordinary PVS
    // objects.  Strip any WorldTree overlap before the normal object phases.
    ExcludeSceneSkyObjectsFromNormalVisibleSets(scene);
    LogStockWorldModelClasses();

    WorldRenderer::Instance().SetupScene(scene);
    WorldSurfaceFxSystem::Instance().Update(mainWorld, bsp);
    const uint32 lmStateChanges = WorldLightmapSystem::Instance().UpdateAnimated(mainWorld);
    if (lmStateChanges)
        WorldRenderer::Instance().WorldModels().UpdateVertexLighting(mainWorld);

    static MainWorldCompat *s_visLoggedWorld = nullptr;
    if (LogIsSessionEnabled() && s_visLoggedWorld != mainWorld)
    {
        s_visLoggedWorld = mainWorld;
        WorldBspCompat *vis = nullptr;
        for (uint32 i = 0; i < mainWorld->m_WorldModels.m_dwElements; ++i)
        {
            WorldDataCompat *wd = mainWorld->m_WorldModels.m_pArray[i];
            if (wd && wd->m_pOriginalBsp &&
                (wd->m_pOriginalBsp->m_dwWorldInfoFlags & WIF_VISBSP))
            {
                vis = wd->m_pOriginalBsp;
                break;
            }
        }
        LOG_SESSION("World3D VISSET static='%s' staticPolys=%u visBsp=%p visPolys=%u (original d3d.ren uses visible Leaf::m_pPolies for static BSP submission)",
                    bsp->m_szWorldName, bsp->m_dwPolies, vis, vis ? vis->m_dwPolies : 0);
    }

    uint32 draws = 0;
    uint64_t tris = 0;

    SkyRenderer::Instance().Render(scene, mainWorld, draws, tris);

    // Sky uses the same world shader but stock dynamic lights are a world
    // overlay, not sky illumination.  RenderSkyPortalPass ends by restoring
    // WorldRenderer::Instance().SetupScene(scene), which leaves the light count at zero; enable the
    // visible OT_LIGHT set only now for static BSP and WorldModels.
    WorldDynamicLightSystem::Instance().UploadVisible();

    // Do not use the old CPU camera/plane rejection path.  Let the GPU
    // rasterizer cull back faces for BSP/WorldModel geometry instead.
    EnableWorldBackfaceCulling();

    uint32 visibleCachedPolys = 0;
    uint32 staticLogicalRuns = 0;
    uint32 staticMultiCalls = 0;
    const bool staticBaseInstance = glf.DrawArraysInstancedBaseInstance && glf.DrawElementsInstancedBaseVertexBaseInstance;
    GLUniform1i(g_uStaticMaterialIndexFromBaseInstance, staticBaseInstance ? 1 : 0);
    auto drawBatch = [&](size_t batchIndex)
    {
        const WorldBatch &b = StaticState().batches[batchIndex];
        WorldMaterialSystem::Instance().ApplyTexFx(b);
        GLUniform1i(g_uFogAdditive, b.blend == WorldBlendMode::Additive ? 1 : 0);
        uint32 materialParamIndex = 0;
        Texture *tex = WorldMaterialSystem::Instance().Apply(b, staticBaseInstance, &materialParamIndex);
        SharedTexture *stateTexture = WorldMaterialSystem::Instance().ResolveBatchTexture(b);
        const TalonRenderState d3dState = TalonRenderStateSystem::Instance().Decode(stateTexture);

        // Static PhysicsBSP transparency authority.  Static BSP geometry cannot
        // be bound to a TranslucentWorldModel object, so material/StateChange
        // alpha state is not permitted to alter coverage.  Additive remains an
        // explicitly authored non-alpha blend mode; every other static batch is
        // depth-writing opaque regardless of SURF_TRANSPARENT, texture alpha,
        // AlphaRef, ColorKey, or decoded D3D alpha state.
        if (b.blend == WorldBlendMode::Additive || b.blend == WorldBlendMode::Multiply)
            WorldMaterialSystem::Instance().ApplyBlend(b.blend);
        else
            GLStateDisable(GL_BLEND);
        GLStateEnable(GL_DEPTH_TEST);

        if (b.blend == WorldBlendMode::Multiply)
        {
            // Coincident Talon overlay: only touch pixels written by the base
            // geometry at precisely the same raster depth, and never disturb Z.
            // Talon treats this like lightmap-style MODULATE2X rather than a
            // plain multiply.  DST_COLOR/SRC_COLOR yields 2 * src * dst.
            GLStateBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
            GLStateDepthFunc(GL_EQUAL);
            GLStateDepthMask(GL_FALSE);
        }
        else
        {
            GLStateDepthFunc(GL_LEQUAL);
            GLStateDepthMask(b.blend == WorldBlendMode::Additive ? GL_FALSE : GL_TRUE);

            // Non-alpha depth state may still be authored for static geometry.
            if (d3dState.hasZEnable && !d3dState.zEnable)
                GLStateDisable(GL_DEPTH_TEST);
            else if (d3dState.hasZFunc)
                GLStateDepthFunc(static_cast<GLenum>(TalonRenderStateSystem::Instance().MapCompareToGL(d3dState.zFunc)));
        }

        GLStateBindTextureUnit(1, LightmapState().atlas);
        GLUniform1i(g_uTextured, tex && tex->texture ? 1 : 0);
        GLUniform1i(g_uLightmapped, LightmapState().atlas ? 1 : 0);
        GLUniform1i(g_uNoLight, b.noLight ? 1 : 0);

        // Static PhysicsBSP is fully opaque for coverage.  Texture alpha,
        // DTX AlphaRef/ColorKey and StateChange alpha-test are ignored here.
        GLUniform1i(g_uAlphaTest, 0);
        GLUniform1f(g_uAlphaRef, 0.0f);
        GLUniform1i(g_uAlphaFunc, 7);
        if (d3dState.hasFogEnable)
            GLUniform1i(g_uFogEnabled, (d3dState.fogEnable && g_fogState.enabled) ? 1 : 0);
        else
            GLUniform1i(g_uFogEnabled, g_fogState.enabled ? 1 : 0);

        if (!PVSState().haveStaticPVS)
        {
            if (staticBaseInstance)
                glf.DrawArraysInstancedBaseInstance(GL_TRIANGLES_,
                                                    static_cast<GLint>(b.firstVertex),
                                                    static_cast<GLsizei>(b.vertexCount), 1, materialParamIndex);
            else
                glf.DrawArrays(GL_TRIANGLES_,
                               static_cast<GLint>(b.firstVertex),
                               static_cast<GLsizei>(b.vertexCount));
            ++draws;
            tris += b.vertexCount / 3;
            visibleCachedPolys += static_cast<uint32>(b.spans.size());
            return;
        }

        // The exact Talon visible set was compiled into one compact index
        // stream grouped by material when the PVS generation changed.  Static
        // vertex geometry stays immutable; one DrawElements submits each
        // visible material with no sub-draw fan-out.
        if (batchIndex >= StaticState().staticVisibleBatchCache.size())
            return;
        const StaticVisibleBatchCache &vis = StaticState().staticVisibleBatchCache[batchIndex];
        if (!vis.indexCount || !StaticState().staticPvsEbo)
            return;

        visibleCachedPolys += vis.visiblePolys;
        staticLogicalRuns += vis.sourceRuns;
        tris += vis.tris;

        glf.VertexArrayElementBuffer(WorldState().vao, StaticState().staticPvsEbo);
        const uintptr_t byteOffset =
            static_cast<uintptr_t>(vis.firstIndex) * sizeof(uint32);
        if (staticBaseInstance)
            glf.DrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES_, static_cast<GLsizei>(vis.indexCount),
                                                            GL_UNSIGNED_INT, reinterpret_cast<const void *>(byteOffset), 1, 0, materialParamIndex);
        else
            glf.DrawElements(GL_TRIANGLES_, static_cast<GLsizei>(vis.indexCount),
                             GL_UNSIGNED_INT, reinterpret_cast<const void *>(byteOffset));
        ++staticMultiCalls;
        ++draws;
    };

    uint32 terrainVisiblePolys = 0;
    uint32 terrainMaterialCalls = 0;
    const bool drawStockWorld = StockRenderOptions::Instance().DrawWorld();
    const bool drawTerrain = drawStockWorld && StockRenderOptions::Instance().DrawTerrainSections();
    auto drawStaticBlend = [&](WorldBlendMode blend)
    {
        if (!drawStockWorld)
            return;
        const auto &indices = StaticState().batchIndicesByBlend[static_cast<size_t>(blend)];
        for (uint32 batchIndex : indices)
            drawBatch(batchIndex);
    };

    // Opaque PhysicsBSP and WIF_TERRAIN geometry share the same Talon leaf
    // visibility set.  Submit both before translucent phases so terrain writes
    // depth and occludes sky/objects exactly like ordinary static world geo.
    GLStateDisable(GL_BLEND);
    GLStateDepthMask(GL_TRUE);
    drawStaticBlend(WorldBlendMode::Solid);
    GLUniform1i(g_uStaticMaterialIndexFromBaseInstance, 0);
    if (drawTerrain)
        DrawTerrainPvsPhase(mainWorld, WorldBlendMode::Solid, draws, tris,
                            terrainVisiblePolys, terrainMaterialCalls);

    // Talon coplanar layering pass.  Exact duplicate static polygons are
    // modulated over the opaque base at equal depth using Talon-style MODULATE2X
    // (DST_COLOR, SRC_COLOR => 2 * source * destination).
    // Duplicate detection is winding-independent (vertex-set signature), so the
    // normal BSP backface-culling rules can remain intact here.
    // This is intentionally before ordinary translucent/additive geometry.
    EnableWorldBackfaceCulling();
    GLStateEnable(GL_BLEND);
    GLStateBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
    GLStateDepthMask(GL_FALSE);
    GLUniform1i(g_uStaticMaterialIndexFromBaseInstance, staticBaseInstance ? 1 : 0);
    drawStaticBlend(WorldBlendMode::Multiply);
    GLUniform1i(g_uStaticMaterialIndexFromBaseInstance, 0);


    // Then transparent static surfaces, still filtered by the exact leaf PVS.
    GLStateEnable(GL_BLEND);
    GLStateDepthMask(GL_FALSE);

    GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLUniform1i(g_uStaticMaterialIndexFromBaseInstance, staticBaseInstance ? 1 : 0);
    drawStaticBlend(WorldBlendMode::Alpha);
    GLUniform1i(g_uStaticMaterialIndexFromBaseInstance, 0);
    if (drawTerrain)
        DrawTerrainPvsPhase(mainWorld, WorldBlendMode::Alpha, draws, tris,
                            terrainVisiblePolys, terrainMaterialCalls);

    GLStateBlendFunc(GL_ONE, GL_ONE);
    GLUniform1i(g_uStaticMaterialIndexFromBaseInstance, staticBaseInstance ? 1 : 0);
    drawStaticBlend(WorldBlendMode::Additive);
    GLUniform1i(g_uStaticMaterialIndexFromBaseInstance, 0);
    if (drawTerrain)
        DrawTerrainPvsPhase(mainWorld, WorldBlendMode::Additive, draws, tris,
                            terrainVisiblePolys, terrainMaterialCalls);

    WorldRenderer::Instance().WorldModels().RenderVisiblePhase(mainWorld, WorldModelPhase::Opaque, draws, tris);

    DisableWorldBackfaceCulling();
    GLStateDepthMask(GL_TRUE);
    GLStateDisable(GL_BLEND);

    PVSState().perfStats.pvsActive = PVSState().haveStaticPVS;
    PVSState().perfStats.visibleLeaves = PVSState().visibleLeafCount;
    PVSState().perfStats.totalLeaves = PVSState().totalLeafCount;
    PVSState().perfStats.leafPolyRefs = PVSState().visibleLeafPolyRefs;
    PVSState().perfStats.uniqueVisiblePolys = static_cast<uint32>(PVSState().visibleStaticPolys.size());
    PVSState().perfStats.renderedPolys = visibleCachedPolys + terrainVisiblePolys;
    PVSState().perfStats.visibleTriangles = tris;
    PVSState().perfStats.apiDrawCalls = draws;
    PVSState().perfStats.worldModels = PVSState().visibleWorldModelCount;
    PVSState().perfStats.models = static_cast<uint32>(PVSState().visibleModels.size());
    PVSState().perfStats.sprites = static_cast<uint32>(PVSState().visibleSprites.size());
    PVSState().perfStats.dynamicLights = WorldDynamicLightSystem::Instance().UploadedCount();

    static int frameBudget = 20;
    if (LogIsSessionEnabled() && ((frameBudget > 0 && frameBudget--)))
        LOG_SESSION("World3D DRAW drawMode=%d bsp=%p batches=%u apiDrawCalls=%u staticSourceRuns=%u staticMaterialIndexCalls=%u terrainPolys=%u terrainMaterialCalls=%u terrainPvsRebuilds=%u tris=%llu pvs=%d pvsGen=%llu pvsCacheRebuilds=%u visibleLeaves=%u leafPolyRefs=%u uniqueLeafPolys=%u renderedPolys=%u worldmodels=%u dynWorldLights=%u cull=GL_BACK_CW cam=(%.2f,%.2f,%.2f) fov=(%.4f,%.4f) quat=(%.5f,%.5f,%.5f,%.5f)",
                    scene->m_nDrawMode, bsp,
                    static_cast<unsigned>(StaticState().batches.size()), draws, staticLogicalRuns, staticMultiCalls,
                    terrainVisiblePolys, terrainMaterialCalls, StaticState().terrainDrawCacheRebuilds,
                    static_cast<unsigned long long>(tris),
                    PVSState().haveStaticPVS ? 1 : 0, static_cast<unsigned long long>(PVSState().staticPvsGeneration), StaticState().staticDrawCacheRebuilds,
                    PVSState().visibleLeafCount, PVSState().visibleLeafPolyRefs,
                    static_cast<unsigned>(PVSState().visibleStaticPolys.size()), visibleCachedPolys + terrainVisiblePolys,
                    PVSState().visibleWorldModelCount, WorldDynamicLightSystem::Instance().UploadedCount(),
                    scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z,
                    scene->m_fFovX, scene->m_fFovY,
                    scene->m_rRotation.x,
                    scene->m_rRotation.y,
                    scene->m_rRotation.z,
                    scene->m_rRotation.w);

    return RENDER_OK;
}
