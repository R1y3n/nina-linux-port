#include "world_lightmap_system.h"
#include "world_renderer.h"
#include "world_model_renderer.h"
#include "deluxe_lightmap_baker.h"
#include "../../gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "utils/log.h"
#include "../../shaders/shader_manager.h"
#include "../../shaders/shader_resources.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <limits>

namespace
{
    inline WorldLightmapSystemState &LightmapState() { return WorldLightmapSystem::Instance().State(); }
}

WorldLightmapSystem &WorldLightmapSystem::Instance()
{
    static WorldLightmapSystem instance;
    return instance;
}

bool WorldLightmapSystem::DecompressLightmap(const uint8 *compressed, uint32 len, uint32 *out, uint32 maxPixels) const
{
    if (!compressed || !len || !out || !maxPixels)
        return false;

    const uint8 *p = compressed;
    const uint8 *end = compressed + len;
    uint32 written = 0;

    while (p < end)
    {
        if (end - p < 4)
            return false;
        uint32 tag = 0;
        std::memcpy(&tag, p, 4);
        p += 4;

        uint32 count = 1;
        if (tag & 0x80000000u)
        {
            tag &= 0x7FFFFFFFu;
            if (p >= end)
                return false;
            count = *p++;
        }

        if (written + count > maxPixels)
            return false;
        while (count--)
            out[written++] = tag;
    }

    return written > 0;
}

bool WorldLightmapSystem::DecompressShadowMap(const uint8 *compressed, uint32 len, uint32 *out, uint32 maxPixels) const
{
    if (!compressed || !len || !out || !maxPixels)
        return false;

    uint32 written = 0;
    bool white = false;
    for (uint32 i = 0; i < len; ++i)
    {
        const uint32 count = compressed[i];
        if (written + count > maxPixels)
            return false;
        const uint32 value = white ? 0xFFFFFFFFu : 0x00000000u;
        for (uint32 j = 0; j < count; ++j)
            out[written++] = value;
        white = !white;
    }
    return written > 0;
}

float WorldLightmapSystem::StockBlend(const LMAnimCompat &anim) const
{
    // Talon/D3D treats LMAnim::m_fBlendPercent as a real 0..1 light-group
    // contribution.  In d3d.ren the lightmap path compares +0x40 against
    // 0.02f and skips the animation when it is below that threshold.  Zero
    // therefore means OFF; it must never be repaired to 1.0f.
    const float raw = anim.m_fBlendPercent;
    if (!std::isfinite(raw))
        return 1.0f;
    return std::clamp(raw, 0.0f, 1.0f);
}

// Stock d3d.ren does NOT use the loop index from LMAnim::m_pPolyRefs to
// address LMFrame::m_pPolyDataList. Each WorldPoly owns a compact
// PolyAnimRef { animIndex, frameDataIndex } pair, and the second WORD is the
// authoritative per-animation frame-data index (d3d.ren 0x100338F5 and
// 0x10033C18). Using the LMAnim poly-ref loop index mixes light-group data
// between unrelated polygons and can make switched groups appear permanently on.
bool WorldLightmapSystem::FindPolyAnimDataIndex(const WorldPolyCompat *poly, uint32 animIndex, uint32 &outDataIndex) const
{
    if (!poly || !poly->m_pPolyAnimRefs || poly->m_dwPolyAnimRefs == 0 ||
        poly->m_dwPolyAnimRefs > 256)
        return false;

    for (uint32 i = 0; i < poly->m_dwPolyAnimRefs; ++i)
    {
        const PolyAnimRefCompat &ref = poly->m_pPolyAnimRefs[i];
        if (static_cast<uint32>(ref.m_wRefs[0]) == animIndex)
        {
            outDataIndex = static_cast<uint32>(ref.m_wRefs[1]);
            return true;
        }
    }
    return false;
}

void WorldLightmapSystem::AddLightPixel(uint32 &dst, uint32 src, float mod) const
{
    const uint32 sr = (src >> 16) & 255u;
    const uint32 sg = (src >> 8) & 255u;
    const uint32 sb = src & 255u;

    uint32 dr = (dst >> 16) & 255u;
    uint32 dg = (dst >> 8) & 255u;
    uint32 db = dst & 255u;

    dr = std::min(255u, dr + static_cast<uint32>(sr * mod));
    dg = std::min(255u, dg + static_cast<uint32>(sg * mod));
    db = std::min(255u, db + static_cast<uint32>(sb * mod));
    dst = 0xFF000000u | (dr << 16) | (dg << 8) | db;
}

void WorldLightmapSystem::DestroyGpuResources()
{
    GLuint ids[6] = {LightmapState().tileSsbo, LightmapState().refSsbo, LightmapState().frameOffsetSsbo,
                     LightmapState().sourcePixelSsbo, LightmapState().animStateSsbo, LightmapState().dirtyTileSsbo};
    for (GLuint &id : ids)
    {
        if (id)
            glf.DeleteBuffers(1, &id);
    }
    LightmapState().tileSsbo = LightmapState().refSsbo = LightmapState().frameOffsetSsbo = 0;
    LightmapState().sourcePixelSsbo = LightmapState().animStateSsbo = LightmapState().dirtyTileSsbo = 0;
    LightmapState().gpuReady = false;
    LightmapState().gpuTileIndex.clear();
    LightmapState().gpuAnimTiles.clear();
    LightmapState().gpuAnimPolys.clear();
    LightmapState().gpuTileDirtyStamp.clear();
    LightmapState().gpuDirtyStamp = 1;
    LightmapState().gpuSourceBytes = 0;
}

bool WorldLightmapSystem::EnsureGpuProgram()
{
    if (LightmapState().computeShader)
        return true;

    auto *shader = avp2::render::ShaderManager::Instance().CreateComputeFromResource("world.lightmap_compute",
                                                                                     avp2::render::ShaderResourceId::LightmapCompute);
    if (!shader)
        return false;
    LightmapState().computeShader = shader;
    return true;
}

float WorldLightmapSystem::StockPercentBetween(const LMAnimCompat &anim) const
{
    // d3d.ren 0x100185B9/0x100185DA reads LMAnim+0x3C as a BYTE,
    // not as a float.  Talon stores 0..255 interpolation here; the
    // remaining three bytes are padding/opaque state.
    const uint8 raw = *reinterpret_cast<const uint8 *>(reinterpret_cast<const uint8 *>(&anim) + 0x3C);
    return float(raw) * (1.0f / 255.0f);
}

uint8 WorldLightmapSystem::StockMulByte(uint8 a, uint8 b) const
{
    // 0x10082168 lookup built at 0x10035D13: round/truncate a*b/255.
    return static_cast<uint8>((uint32(a) * uint32(b)) / 255u);
}

uint8 WorldLightmapSystem::StockSatAddByte(uint8 a, uint8 b) const
{
    // 0x10092168 lookup built at 0x10035CE7: min(a+b,255).
    const uint32 v = uint32(a) + uint32(b);
    return static_cast<uint8>(v > 255u ? 255u : v);
}

GpuLmAnimState WorldLightmapSystem::MakeGpuAnimState(const LMAnimCompat &anim) const
{
    GpuLmAnimState out{};
    const uint32 raw0 = anim.m_dwBetweenFrames[0];
    const uint32 raw1 = anim.m_dwBetweenFrames[1];
    const bool active = (anim.m_pFrames && anim.m_nFrames &&
                         raw0 != 0xFFFFFFFFu && raw0 < static_cast<uint32>(anim.m_nFrames));
    out.frame0 = active ? raw0 : 0u;
    out.frame1 = (active && raw1 < static_cast<uint32>(anim.m_nFrames)) ? raw1 : out.frame0;
    out.enabledFlag = active ? 1u : 0u;
    out.shadowFlag = anim.m_bShadowMap ? 1u : 0u;
    out.between = (out.frame0 == out.frame1) ? 0.0f : StockPercentBetween(anim);
    out.blend = StockBlend(anim);
    return out;
}

bool WorldLightmapSystem::CreateGpuBuffer(GLuint &out, const void *data, size_t bytes, GLbitfield flags) const
{
    if (!bytes)
        return false;
    glf.CreateBuffers(1, &out);
    if (!out)
        return false;
    glf.NamedBufferStorage(out, static_cast<GLsizeiptr>(bytes), data, flags);
    return true;
}

bool WorldLightmapSystem::BuildGpuResources(MainWorldCompat *world)
{
    DestroyGpuResources();
    if (!world || !LightmapState().atlas || LightmapState().tiles.empty() || !world->m_LMAnims.m_pArray ||
        !world->m_LMAnims.m_dwElements || !EnsureGpuProgram())
        return false;

    const uint32 animCount = world->m_LMAnims.m_dwElements;
    std::vector<GpuLmTileDesc> tiles;
    std::vector<GpuLmRefDesc> refs;
    std::vector<uint32> frameOffsets;
    std::vector<uint32> sourcePixels;
    std::vector<GpuLmAnimState> states(animCount);

    tiles.reserve(LightmapState().tiles.size());
    refs.reserve(LightmapState().tiles.size() * 2u);
    frameOffsets.reserve(LightmapState().tiles.size() * 2u);
    LightmapState().gpuAnimTiles.assign(animCount, {});
    LightmapState().gpuAnimPolys.assign(animCount, {});
    LightmapState().gpuTileIndex.reserve(LightmapState().tiles.size() * 2u);

    // Pre-resolve every animation's polygon list once.  Runtime state changes
    // no longer chase WorldData/BSP/poly pointers thousands of times just to
    // discover which cached Gouraud vertices could be dirty.
    for (uint32 ai = 0; ai < animCount; ++ai)
    {
        LMAnimCompat &anim = world->m_LMAnims.m_pArray[ai];
        states[ai] = MakeGpuAnimState(anim);
        if (!anim.m_pPolyRefs)
            continue;
        auto &out = LightmapState().gpuAnimPolys[ai];
        out.reserve(anim.m_wPolyRefs);
        for (uint32 ri = 0; ri < anim.m_wPolyRefs; ++ri)
        {
            const LMPolyRefCompat &r = anim.m_pPolyRefs[ri];
            if (r.m_wModel >= world->m_WorldModels.m_dwElements)
                continue;
            WorldDataCompat *wd = world->m_WorldModels.m_pArray[r.m_wModel];
            WorldBspCompat *bsp = wd ? wd->m_pOriginalBsp : nullptr;
            if (!bsp || r.m_wPoly >= bsp->m_dwPolies)
                continue;
            WorldPolyCompat *poly = bsp->m_pPolies[r.m_wPoly];
            if (poly)
                out.push_back(poly);
        }
    }

    constexpr size_t GPU_SOURCE_CAP_BYTES = 256u * 1024u * 1024u;
    std::array<uint32, 1024> temp{};

    for (const auto &kv : LightmapState().tiles)
    {
        WorldPolyCompat *poly = kv.first;
        const WorldLightmapTile &lt = kv.second;
        const uint32 tileIndex = static_cast<uint32>(tiles.size());
        LightmapState().gpuTileIndex.emplace(poly, tileIndex);

        GpuLmTileDesc td{};
        td.x = lt.x;
        td.y = lt.y;
        td.w = lt.w;
        td.h = lt.h;
        td.refStart = static_cast<uint32>(refs.size());
        const uint32 pixels = lt.w * lt.h;

        // Preserve the existing renderer's validated lightmap payload limit.
        if (poly && pixels && pixels <= temp.size() && poly->m_pPolyAnimRefs &&
            poly->m_dwPolyAnimRefs > 0 && poly->m_dwPolyAnimRefs <= 256)
        {
            for (uint32 pr = 0; pr < poly->m_dwPolyAnimRefs; ++pr)
            {
                const PolyAnimRefCompat &pref = poly->m_pPolyAnimRefs[pr];
                const uint32 ai = static_cast<uint32>(pref.m_wRefs[0]);
                const uint32 dataIndex = static_cast<uint32>(pref.m_wRefs[1]);
                if (ai >= animCount)
                    continue;

                LMAnimCompat &anim = world->m_LMAnims.m_pArray[ai];
                if (anim.m_bShadowMap || !anim.m_pFrames || !anim.m_nFrames || dataIndex >= anim.m_wPolyRefs)
                    continue;

                GpuLmRefDesc rd{};
                rd.animIndex = ai;
                rd.frameOffsetStart = static_cast<uint32>(frameOffsets.size());
                rd.pixelCount = pixels;
                bool anyFrame = false;

                for (uint32 fi = 0; fi < static_cast<uint32>(anim.m_nFrames); ++fi)
                {
                    uint32 sourceOffset = 0xFFFFFFFFu;
                    LMFramePolyDataCompat *list = anim.m_pFrames[fi].m_pPolyDataList;
                    if (list)
                    {
                        LMFramePolyDataCompat &d = list[dataIndex];
                        temp.fill(0);
                        if (DecompressLightmap(d.m_pData, d.m_wSize, temp.data(), pixels))
                        {
                            const size_t nextBytes = (sourcePixels.size() + pixels) * sizeof(uint32);
                            if (nextBytes > GPU_SOURCE_CAP_BYTES)
                            {
                                LOG_SESSION("World3D LM GPU source cap exceeded bytes=%llu cap=%llu; retaining CPU delta fallback",
                                            static_cast<unsigned long long>(nextBytes),
                                            static_cast<unsigned long long>(GPU_SOURCE_CAP_BYTES));
                                DestroyGpuResources();
                                return false;
                            }
                            sourceOffset = static_cast<uint32>(sourcePixels.size());
                            sourcePixels.insert(sourcePixels.end(), temp.begin(), temp.begin() + pixels);
                            anyFrame = true;
                        }
                    }
                    frameOffsets.push_back(sourceOffset);
                }

                if (anyFrame)
                {
                    refs.push_back(rd);
                    LightmapState().gpuAnimTiles[ai].push_back(tileIndex);
                }
            }
        }

        td.refCount = static_cast<uint32>(refs.size()) - td.refStart;
        tiles.push_back(td);
    }

    for (auto &v : LightmapState().gpuAnimTiles)
    {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }

    if (tiles.empty() || refs.empty() || frameOffsets.empty() || sourcePixels.empty())
    {
        DestroyGpuResources();
        return false;
    }

    bool ok = true;
    ok &= CreateGpuBuffer(LightmapState().tileSsbo, tiles.data(), tiles.size() * sizeof(tiles[0]), 0);
    ok &= CreateGpuBuffer(LightmapState().refSsbo, refs.data(), refs.size() * sizeof(refs[0]), 0);
    ok &= CreateGpuBuffer(LightmapState().frameOffsetSsbo, frameOffsets.data(), frameOffsets.size() * sizeof(uint32), 0);
    ok &= CreateGpuBuffer(LightmapState().sourcePixelSsbo, sourcePixels.data(), sourcePixels.size() * sizeof(uint32), 0);
    ok &= CreateGpuBuffer(LightmapState().animStateSsbo, states.data(), states.size() * sizeof(states[0]), GL_DYNAMIC_STORAGE_BIT_);
    ok &= CreateGpuBuffer(LightmapState().dirtyTileSsbo, nullptr, std::max<size_t>(1, tiles.size()) * sizeof(uint32), GL_DYNAMIC_STORAGE_BIT_);
    if (!ok)
    {
        DestroyGpuResources();
        return false;
    }

    LightmapState().gpuTileDirtyStamp.assign(tiles.size(), 0u);
    LightmapState().gpuSourceBytes = sourcePixels.size() * sizeof(uint32);
    LightmapState().gpuReady = true;

    LOG_SESSION("World3D LM GPU-COMPUTE ready tiles=%u refs=%u frameOffsets=%u sourcePixels=%u sourceMB=%.2f anims=%u path=SSBO-DECOMPRESS-ONCE/COMPUTE-COMPOSE",
                static_cast<unsigned>(tiles.size()), static_cast<unsigned>(refs.size()),
                static_cast<unsigned>(frameOffsets.size()), static_cast<unsigned>(sourcePixels.size()),
                double(LightmapState().gpuSourceBytes) / (1024.0 * 1024.0), animCount);
    return true;
}

bool WorldLightmapSystem::DispatchGpuUpdate(MainWorldCompat *world,
                                            const std::vector<uint32> &changedAnims,
                                            uint32 liveAnims)
{
    if (!LightmapState().gpuReady || !world || changedAnims.empty() ||
        LightmapState().gpuAnimTiles.size() != world->m_LMAnims.m_dwElements ||
        LightmapState().gpuAnimPolys.size() != world->m_LMAnims.m_dwElements)
        return false;

    if (++LightmapState().gpuDirtyStamp == 0)
    {
        std::fill(LightmapState().gpuTileDirtyStamp.begin(), LightmapState().gpuTileDirtyStamp.end(), 0u);
        LightmapState().gpuDirtyStamp = 1;
    }

    std::vector<uint32> dirtyTiles;
    dirtyTiles.reserve(256);
    const bool cpuVertexFallback = WorldRenderer::Instance().WorldModels().NeedsCpuVertexLightFallback();

    for (uint32 ai : changedAnims)
    {
        if (ai >= LightmapState().gpuAnimTiles.size())
            continue;

        // GPU vertex-light SSBOs consume the same animation-state buffer
        // directly in the vertex shader.  Only build the changed-poly pointer
        // set when some legacy/fallback cache still needs CPU VBO colors.
        if (cpuVertexFallback)
        {
            for (WorldPolyCompat *poly : LightmapState().gpuAnimPolys[ai])
                if (poly)
                    LightmapState().changedLightAnimPolys.insert(poly);
        }

        for (uint32 ti : LightmapState().gpuAnimTiles[ai])
        {
            if (ti >= LightmapState().gpuTileDirtyStamp.size())
                continue;
            if (LightmapState().gpuTileDirtyStamp[ti] == LightmapState().gpuDirtyStamp)
                continue;
            LightmapState().gpuTileDirtyStamp[ti] = LightmapState().gpuDirtyStamp;
            dirtyTiles.push_back(ti);
        }
    }

    // The animation-state SSBO is shared by both the lightmap compute shader
    // and GPU Gouraud vertex lighting.  Update it even when the changed
    // animation has no texture-lightmap tiles.
    std::vector<GpuLmAnimState> states(world->m_LMAnims.m_dwElements);
    for (uint32 ai = 0; ai < world->m_LMAnims.m_dwElements; ++ai)
        states[ai] = MakeGpuAnimState(world->m_LMAnims.m_pArray[ai]);

    GLTrackedWorldNamedBufferSubData(LightmapState().animStateSsbo, 0,
                                     static_cast<GLsizeiptr>(states.size() * sizeof(states[0])), states.data(), GLWorldUploadKind::LightmapState);

    // A LightAnim can be vertex-colour-only.  Its Gouraud result is now read
    // directly from the updated state SSBO by the vertex shader, so no atlas
    // dispatch or VBO upload is necessary.
    if (dirtyTiles.empty())
    {
        static uint32 stateBudget = 48;
        if (LogIsSessionEnabled() && (stateBudget > 0 && stateBudget--))
            LOG_SESSION("World3D LM GPU-STATE liveAnims=%u changedAnims=%u dirtyTiles=0 textureUploads=0 vertexVboUploads=0",
                        liveAnims, static_cast<unsigned>(changedAnims.size()));
        return true;
    }

    GLTrackedWorldNamedBufferSubData(LightmapState().dirtyTileSsbo, 0,
                                     static_cast<GLsizeiptr>(dirtyTiles.size() * sizeof(uint32)), dirtyTiles.data(), GLWorldUploadKind::LightmapDirty);

    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 0, LightmapState().tileSsbo);
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 1, LightmapState().refSsbo);
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 2, LightmapState().frameOffsetSsbo);
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 3, LightmapState().sourcePixelSsbo);
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 4, LightmapState().animStateSsbo);
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 5, LightmapState().dirtyTileSsbo);
    glf.BindImageTexture(0, LightmapState().atlas, 0, GL_FALSE, 0, GL_WRITE_ONLY_, GL_RGBA8_);
    LightmapState().computeShader->Use();
    glf.DispatchCompute(static_cast<GLuint>(dirtyTiles.size()), 1, 1);
    glf.MemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT_ | GL_TEXTURE_FETCH_BARRIER_BIT_);
    // Restore the world graphics program because lightmap state changes happen
    // inside the render path immediately before normal BSP submission.
    WorldRenderer::Instance().State().worldShader->Use();

    static uint32 budget = 96;
    if (LogIsSessionEnabled() && (budget && (--budget, true)))
        LOG_SESSION("World3D LM GPU-UPDATE liveAnims=%u changedAnims=%u dirtyTiles=%u dispatchGroups=%u textureUploads=0 sourceMB=%.2f",
                    liveAnims, static_cast<unsigned>(changedAnims.size()),
                    static_cast<unsigned>(dirtyTiles.size()), static_cast<unsigned>(dirtyTiles.size()),
                    double(LightmapState().gpuSourceBytes) / (1024.0 * 1024.0));
    return true;
}

bool WorldLightmapSystem::BuildAtlas(MainWorldCompat *world, WorldBspCompat *targetBsp)
{
    DestroyGpuResources();
    // Direction atlases are level-specific because they share the lightmap
    // tile layout. Never let a previous map's bake leak into a new level.
    DeluxeLightmapBaker::Instance().ClearDirections();
    DeluxeLightmapBaker::Instance().SetWorldContext(world, targetBsp);
    LightmapState().tiles.clear();
    LightmapState().atlasPixels.assign(static_cast<size_t>(WorldLightmapSystem::AtlasDims) * WorldLightmapSystem::AtlasDims, 0xFF000000u);
    LightmapState().lightmapPolys = 0;
    LightmapState().lightmapAnims = 0;

    if (!world || !targetBsp || !world->m_LMAnims.m_pArray ||
        world->m_LMAnims.m_dwElements == 0 || world->m_LMAnims.m_dwElements > 256)
    {
        LOG_SESSION("World3D LM: no usable LM animations");
        return false;
    }

    uint32 nextX = 0, nextY = 0, rowH = 0;
    std::unordered_map<WorldPolyCompat *, WorldLightmapTile> tiles;
    uint32 lmRefMapped = 0;
    uint32 lmRefMissingPolyAnim = 0;
    uint32 lmRefIndexMismatch = 0;

    // Allocate one tile per referenced world polygon, including movable
    // WorldModelInstance BSPs.
    for (uint32 ai = 0; ai < world->m_LMAnims.m_dwElements; ++ai)
    {
        LMAnimCompat &anim = world->m_LMAnims.m_pArray[ai];
        if (!anim.m_pPolyRefs)
            continue;

        for (uint32 ri = 0; ri < anim.m_wPolyRefs; ++ri)
        {
            const LMPolyRefCompat &ref = anim.m_pPolyRefs[ri];
            if (ref.m_wModel >= world->m_WorldModels.m_dwElements)
                continue;

            WorldDataCompat *wd = world->m_WorldModels.m_pArray[ref.m_wModel];
            WorldBspCompat *refBsp = wd ? wd->m_pOriginalBsp : nullptr;
            if (!refBsp || ref.m_wPoly >= refBsp->m_dwPolies)
                continue;

            WorldPolyCompat *poly = refBsp->m_pPolies[ref.m_wPoly];
            if (!poly || !poly->m_pSurface || !(poly->m_pSurface->m_dwFlags & SURF_LIGHTMAP))
                continue;

            uint32 frameDataIndex = 0;
            if (!FindPolyAnimDataIndex(poly, ai, frameDataIndex) ||
                frameDataIndex >= static_cast<uint32>(anim.m_wPolyRefs))
            {
                ++lmRefMissingPolyAnim;
                continue;
            }
            ++lmRefMapped;
            if (frameDataIndex != ri)
                ++lmRefIndexMismatch;

            // A SURF_LIGHTMAP polygon is not guaranteed to have a texture
            // lightmap. Talon also stores a per-vertex RGB fallback in every
            // LMFramePolyData record, and some custom maps use that form for
            // every polygon while leaving m_wSize at zero. Stock d3d.ren only
            // allocates a lightmap page when the compressed payload is nonzero;
            // otherwise its lightmap draw consumes the vertex RGB arrays.
            // Do not allocate a black atlas tile for a vertex-only record.
            bool hasTexturePayload = false;
            if (anim.m_pFrames && anim.m_nFrames)
            {
                for (uint32 fi = 0; fi < static_cast<uint32>(anim.m_nFrames); ++fi)
                {
                    LMFramePolyDataCompat *frameData = anim.m_pFrames[fi].m_pPolyDataList;
                    if (frameData && frameData[frameDataIndex].m_pData &&
                        frameData[frameDataIndex].m_wSize != 0)
                    {
                        hasTexturePayload = true;
                        break;
                    }
                }
            }
            if (!hasTexturePayload)
                continue;

            if (tiles.find(poly) != tiles.end())
                continue;

            const uint32 w = std::max(1u, static_cast<uint32>(poly->m_nLightmapWidth));
            const uint32 h = std::max(1u, static_cast<uint32>(poly->m_nLightmapHeight));
            if (w > 64 || h > 64)
                continue;

            if (nextX + w > WorldLightmapSystem::AtlasDims)
            {
                nextX = 0;
                nextY += rowH;
                rowH = 0;
            }
            if (nextY + h > WorldLightmapSystem::AtlasDims)
            {
                LOG_SESSION("World3D LM atlas overflow at %u tiles", static_cast<unsigned>(tiles.size()));
                break;
            }

            WorldPolyCompat *bakePoly = poly;
            if (wd)
            {
                WorldBspCompat *bakeBsp = refBsp;
                // Keep the proven static BSP path unchanged.  For movable brush
                // WorldModels, prefer the live/world-space BSP copy when the
                // engine exposes one so deluxe receiver positions match the
                // placed instance rather than the authored local-space source.
                if (wd->m_pWorldBsp && wd->m_pWorldBsp != refBsp &&
                    (refBsp->m_dwWorldInfoFlags & (WIF_MAINWORLD | WIF_PHYSICSBSP)) == 0)
                    bakeBsp = wd->m_pWorldBsp;
                if (bakeBsp && bakeBsp->m_pPolies && ref.m_wPoly < bakeBsp->m_dwPolies &&
                    bakeBsp->m_pPolies[ref.m_wPoly])
                    bakePoly = bakeBsp->m_pPolies[ref.m_wPoly];
            }

            tiles.emplace(poly, WorldLightmapTile{nextX, nextY, w, h, ref.m_wModel, ref.m_wPoly, bakePoly});
            nextX += w;
            rowH = std::max(rowH, h);
        }
    }

    LightmapState().atlasUsedHeight = std::min<uint32>(WorldLightmapSystem::AtlasDims, nextY + rowH);

    std::array<uint32, 1024> temp{};
    std::array<uint32, 1024> temp2{};

    // Compose the current frame of every light animation into the tile.
    // This mirrors the reference's additive LM composition on the CPU.
    for (uint32 ai = 0; ai < world->m_LMAnims.m_dwElements; ++ai)
    {
        LMAnimCompat &anim = world->m_LMAnims.m_pArray[ai];
        if (!anim.m_pFrames || !anim.m_pPolyRefs || anim.m_nFrames == 0)
            continue;

        ++LightmapState().lightmapAnims;

        const uint32 rawF0 = anim.m_dwBetweenFrames[0];
        const uint32 rawF1 = anim.m_dwBetweenFrames[1];
        const bool frameActive = (rawF0 != 0xFFFFFFFFu && rawF0 < static_cast<uint32>(anim.m_nFrames));
        uint32 f0 = frameActive ? rawF0 : 0u;
        uint32 f1 = (rawF1 < static_cast<uint32>(anim.m_nFrames)) ? rawF1 : f0;

        float between = StockPercentBetween(anim);
        const float blend = StockBlend(anim);

        static uint32 s_lmAnimBuildLogBudget = 256;
        if (LogIsSessionEnabled() && (s_lmAnimBuildLogBudget))
        {
            --s_lmAnimBuildLogBudget;
            LOG_SESSION("World3D LM ANIM index=%u name='%s' shadow=%d frames=%u refs=%u blend=%.4f active=%d frameActive=%d rawBetween=(%08X,%08X) resolved=(%u,%u) pct=%.4f",
                        ai, anim.m_szName, anim.m_bShadowMap ? 1 : 0, static_cast<unsigned>(anim.m_nFrames),
                        static_cast<unsigned>(anim.m_wPolyRefs), blend,
                        (frameActive && blend >= WorldLightmapSystem::MinAnimBlend) ? 1 : 0, frameActive ? 1 : 0,
                        rawF0, rawF1, f0, f1, between);
        }

        // Stock d3d.ren checks LMAnim+0x34 for 0xFFFFFFFF before it even
        // examines m_fBlendPercent (0x100332E3).  That sentinel means this
        // animation/light group has no active frame.  Our old code converted
        // it to frame 0, which literally turned disabled groups back on.
        if (!frameActive)
            continue;

        // Stock also skips an LMAnim below 0.02 blend.
        if (blend < WorldLightmapSystem::MinAnimBlend && !anim.m_bShadowMap)
            continue;

        for (uint32 ri = 0; ri < anim.m_wPolyRefs; ++ri)
        {
            const LMPolyRefCompat &ref = anim.m_pPolyRefs[ri];
            if (ref.m_wModel >= world->m_WorldModels.m_dwElements)
                continue;
            WorldDataCompat *wd = world->m_WorldModels.m_pArray[ref.m_wModel];
            WorldBspCompat *refBsp = wd ? wd->m_pOriginalBsp : nullptr;
            if (!refBsp || ref.m_wPoly >= refBsp->m_dwPolies)
                continue;

            WorldPolyCompat *poly = refBsp->m_pPolies[ref.m_wPoly];
            auto it = tiles.find(poly);
            if (it == tiles.end())
                continue;

            uint32 frameDataIndex = 0;
            if (!FindPolyAnimDataIndex(poly, ai, frameDataIndex) ||
                frameDataIndex >= static_cast<uint32>(anim.m_wPolyRefs))
                continue;

            if (!anim.m_pFrames[f0].m_pPolyDataList)
                continue;

            const WorldLightmapTile &tile = it->second;
            const uint32 pixels = tile.w * tile.h;
            if (pixels == 0 || pixels > temp.size())
                continue;

            LMFramePolyDataCompat &d0 = anim.m_pFrames[f0].m_pPolyDataList[frameDataIndex];
            LMFramePolyDataCompat &d1 = anim.m_pFrames[f1].m_pPolyDataList ? anim.m_pFrames[f1].m_pPolyDataList[frameDataIndex] : d0;

            temp.fill(0);
            temp2.fill(0);

            bool ok0 = anim.m_bShadowMap ? DecompressShadowMap(d0.m_pData, d0.m_wSize, temp.data(), pixels) : DecompressLightmap(d0.m_pData, d0.m_wSize, temp.data(), pixels);
            bool ok1 = anim.m_bShadowMap ? DecompressShadowMap(d1.m_pData, d1.m_wSize, temp2.data(), pixels) : DecompressLightmap(d1.m_pData, d1.m_wSize, temp2.data(), pixels);

            if (!ok0)
                continue;
            if (!ok1)
                temp2 = temp;

            // Shadow animations require the light's world-space color/radius
            // operation in the reference shader. Leave them for the next
            // dynamic-light pass rather than darkening the atlas incorrectly.
            if (anim.m_bShadowMap)
                continue;

            for (uint32 py = 0; py < tile.h; ++py)
            {
                for (uint32 px = 0; px < tile.w; ++px)
                {
                    const uint32 si = py * tile.w + px;
                    const uint32 a = temp[si];
                    const uint32 b = temp2[si];
                    auto lerp8 = [&](uint32 shift) -> uint32
                    {
                        float av = float((a >> shift) & 255u);
                        float bv = float((b >> shift) & 255u);
                        return static_cast<uint32>(std::clamp(av + (bv - av) * between, 0.0f, 255.0f));
                    };
                    const uint32 mixed = 0xFF000000u | (lerp8(16) << 16) | (lerp8(8) << 8) | lerp8(0);
                    uint32 &dst = LightmapState().atlasPixels[(tile.y + py) * WorldLightmapSystem::AtlasDims + (tile.x + px)];
                    AddLightPixel(dst, mixed, blend);
                }
            }
        }
    }

    LightmapState().tiles = std::move(tiles);
    LightmapState().lightmapPolys = static_cast<uint32>(LightmapState().tiles.size());

    if (!LightmapState().atlas)
        glf.CreateTextures(GL_TEXTURE_2D, 1, &LightmapState().atlas);

    // Recreate immutable storage when changing level.
    if (LightmapState().atlas)
    {
        GLStateDeleteTextures(1, &LightmapState().atlas);
        LightmapState().atlas = 0;
    }
    glf.CreateTextures(GL_TEXTURE_2D, 1, &LightmapState().atlas);
    glf.TextureStorage2D(LightmapState().atlas, 1, GL_RGBA8_, WorldLightmapSystem::AtlasDims, WorldLightmapSystem::AtlasDims);
    glf.TextureSubImage2D(LightmapState().atlas, 0, 0, 0, WorldLightmapSystem::AtlasDims, WorldLightmapSystem::AtlasDims,
                          GL_BGRA_, GL_UNSIGNED_BYTE, LightmapState().atlasPixels.data());
    glf.TextureParameteri(LightmapState().atlas, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glf.TextureParameteri(LightmapState().atlas, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glf.TextureParameteri(LightmapState().atlas, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
    glf.TextureParameteri(LightmapState().atlas, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);

    if (!BuildGpuResources(world))
        LOG_SESSION("World3D LM GPU-COMPUTE unavailable; CPU delta compositor retained as compatibility fallback");

    LOG_SESSION("World3D LM REF-MAP mapped=%u missingPolyAnim=%u loopIndexMismatch=%u (frame data indexed by WorldPoly::PolyAnimRef[1], stock d3d.ren semantics)",
                lmRefMapped, lmRefMissingPolyAnim, lmRefIndexMismatch);
    LOG_SESSION("World3D LM atlas: anims=%u polys=%u dims=%ux%u grid=%.3f",
                LightmapState().lightmapAnims, LightmapState().lightmapPolys, WorldLightmapSystem::AtlasDims, WorldLightmapSystem::AtlasDims, world->m_fLMGridSize);
    return !LightmapState().tiles.empty();
}

uint32 WorldLightmapSystem::UpdateAnimated(MainWorldCompat *world)
{
    LightmapState().changedLightAnimPolys.clear();

    if (!world || !world->m_LMAnims.m_pArray)
        return 0;

    // The original implementation rebuilt every lightmap tile, decompressed every
    // active LightAnim reference, and uploaded the whole used atlas on *every*
    // RenderScene call.  Large AVP2 maps can have tens of thousands of LightGroup
    // refs, so that turned a tiny state change into O(all-lightmaps) CPU work plus
    // a multi-megabyte texture upload every frame.
    //
    // Track the stock-visible LightAnim state first.  If nothing changed, the GPU
    // atlas is already correct and there is literally no work to do.
    static MainWorldCompat *prevWorld = nullptr;
    static std::vector<uint64_t> prev;
    static std::vector<uint32> prevBlendBits;
    static std::vector<uint32> prevRawF0;
    static std::vector<uint32> prevRawF1;

    const uint32 animCount = world->m_LMAnims.m_dwElements;
    const bool resetStateHistory =
        prevWorld != world ||
        prev.size() != animCount ||
        prevBlendBits.size() != animCount ||
        prevRawF0.size() != animCount ||
        prevRawF1.size() != animCount;

    if (resetStateHistory)
    {
        prevWorld = world;
        prev.assign(animCount, 0ull);
        prevBlendBits.assign(animCount, 0u);
        prevRawF0.assign(animCount, 0xFFFFFFFFu);
        prevRawF1.assign(animCount, 0xFFFFFFFFu);
    }

    std::vector<uint32> changedAnims;
    changedAnims.reserve(16);
    uint32 live = 0;

    for (uint32 ai = 0; ai < animCount; ++ai)
    {
        LMAnimCompat &anim = world->m_LMAnims.m_pArray[ai];
        if (!anim.m_pFrames || !anim.m_pPolyRefs || !anim.m_nFrames)
            continue;

        ++live;
        const uint32 rawF0 = anim.m_dwBetweenFrames[0];
        const uint32 rawF1 = anim.m_dwBetweenFrames[1];
        const bool frameActive = (rawF0 != 0xFFFFFFFFu && rawF0 < static_cast<uint32>(anim.m_nFrames));
        const uint32 f0 = frameActive ? rawF0 : 0u;
        const uint32 f1 = (rawF1 < static_cast<uint32>(anim.m_nFrames)) ? rawF1 : f0;
        const float t = StockPercentBetween(anim);
        const float blend = StockBlend(anim);

        uint32 tb = 0, bb = 0;
        memcpy(&tb, &t, 4);
        memcpy(&bb, &blend, 4);

        // If both frame endpoints are identical, interpolation percent cannot
        // change the resulting pixels.  Canonicalize it out of the state key.
        const uint32 effectiveTB = (f0 == f1) ? 0u : tb;
        const uint64_t st =
            uint64_t(rawF0) ^
            (uint64_t(rawF1) << 17) ^
            (uint64_t(effectiveTB) << 1) ^
            (uint64_t(bb) << 32);

        if (resetStateHistory)
        {
            prev[ai] = st;
            prevBlendBits[ai] = bb;
            prevRawF0[ai] = rawF0;
            prevRawF1[ai] = rawF1;
            continue;
        }

        if (prev[ai] != st)
        {
            changedAnims.push_back(ai);

            const bool frameStateChanged =
                prevRawF0[ai] != rawF0 || prevRawF1[ai] != rawF1;
            const bool blendChanged = prevBlendBits[ai] != bb;
            if (blendChanged || frameStateChanged)
            {
                // Diagnostic only.  Some maps toggle many LightGroups every
                // frame; unbounded per-group file logging can itself become a
                // measurable render-thread stall.
                static uint32 s_groupStateLogBudget = 96;
                if (LogIsSessionEnabled() && (s_groupStateLogBudget))
                {
                    --s_groupStateLogBudget;
                    float oldBlend = 0.0f;
                    const uint32 oldBlendBits = prevBlendBits[ai];
                    memcpy(&oldBlend, &oldBlendBits, 4);
                    LOG_SESSION("World3D LM GROUP STATE index=%u name='%s' blend=%.4f->%.4f active=%d frameActive=%d rawBetween=(%08X,%08X)->(%08X,%08X) frames=(%u,%u) pct=%.4f",
                                ai, anim.m_szName, oldBlend, blend,
                                (frameActive && blend >= WorldLightmapSystem::MinAnimBlend) ? 1 : 0, frameActive ? 1 : 0,
                                prevRawF0[ai], prevRawF1[ai], rawF0, rawF1, f0, f1, t);
                }
            }
        }

        prev[ai] = st;
        prevBlendBits[ai] = bb;
        prevRawF0[ai] = rawF0;
        prevRawF1[ai] = rawF1;
    }

    // BuildLightmapAtlas already composed and uploaded the current state when a
    // level was adopted.  The first call here only seeds our change history.
    if (resetStateHistory || changedAnims.empty())
        return 0;

    // Keep the deluxe direction atlas in the same live LightGroup state as the
    // RGB lightmap. Only changed group-referenced tiles are rebuilt/uploaded.
    if (!LightmapState().tiles.empty())
        DeluxeLightmapBaker::Instance().UpdateLightGroups(world, changedAnims);

    // Core 4.6 path: source LM data was decompressed once at level adoption.
    // Recompose only dirty tiles in a compute shader; no runtime decompression,
    // CPU pixel loops or texture uploads.  If resource creation was rejected
    // (for example because the 32-bit process would need an excessive source
    // buffer), fall through to the validated CPU delta compositor below.
    if (LightmapState().gpuReady && DispatchGpuUpdate(world, changedAnims, live))
        return static_cast<uint32>(changedAnims.size());

    // Resolve only the polygons touched by changed animations.  Include non-LM
    // polygons too so compiled Gouraud/flat vertex colours can be refreshed by
    // UpdateWorldModelVertexLighting without scanning every polygon in every
    // LightGroup.
    std::unordered_set<WorldPolyCompat *> dirtyLMPolys;
    dirtyLMPolys.reserve(256);

    for (uint32 ai : changedAnims)
    {
        LMAnimCompat &anim = world->m_LMAnims.m_pArray[ai];
        for (uint32 ri = 0; ri < anim.m_wPolyRefs; ++ri)
        {
            const LMPolyRefCompat &ref = anim.m_pPolyRefs[ri];
            if (ref.m_wModel >= world->m_WorldModels.m_dwElements)
                continue;

            WorldDataCompat *wd = world->m_WorldModels.m_pArray[ref.m_wModel];
            WorldBspCompat *bsp = wd ? wd->m_pOriginalBsp : nullptr;
            if (!bsp || ref.m_wPoly >= bsp->m_dwPolies)
                continue;

            WorldPolyCompat *poly = bsp->m_pPolies[ref.m_wPoly];
            if (!poly)
                continue;

            LightmapState().changedLightAnimPolys.insert(poly);
            if (LightmapState().tiles.find(poly) != LightmapState().tiles.end())
                dirtyLMPolys.insert(poly);
        }
    }

    // A changed animation may contain only vertex-colour data.  In that case
    // there is no texture atlas work, but return a change count so the vertex
    // lighting path still runs.
    if (dirtyLMPolys.empty())
        return static_cast<uint32>(changedAnims.size());

    std::array<uint32, 1024> a{}, b{};

    // Recompose each dirty tile from all of that polygon's currently active
    // LightAnims.  This preserves additive Talon semantics when one group turns
    // off or changes frame: clear the tile, then re-add BASE + the other active
    // groups for this polygon only.
    for (WorldPolyCompat *poly : dirtyLMPolys)
    {
        auto tileIt = LightmapState().tiles.find(poly);
        if (tileIt == LightmapState().tiles.end())
            continue;

        const WorldLightmapTile &tile = tileIt->second;
        const uint32 n = tile.w * tile.h;
        if (!n || n > a.size())
            continue;

        for (uint32 y = 0; y < tile.h; ++y)
        {
            uint32 *row = &LightmapState().atlasPixels[(tile.y + y) * WorldLightmapSystem::AtlasDims + tile.x];
            std::fill(row, row + tile.w, 0xFF000000u);
        }

        if (!poly->m_pPolyAnimRefs || poly->m_dwPolyAnimRefs == 0 || poly->m_dwPolyAnimRefs > 256)
            continue;

        for (uint32 pr = 0; pr < poly->m_dwPolyAnimRefs; ++pr)
        {
            const PolyAnimRefCompat &pref = poly->m_pPolyAnimRefs[pr];
            const uint32 ai = static_cast<uint32>(pref.m_wRefs[0]);
            const uint32 dataIndex = static_cast<uint32>(pref.m_wRefs[1]);
            if (ai >= animCount)
                continue;

            LMAnimCompat &anim = world->m_LMAnims.m_pArray[ai];
            if (!anim.m_pFrames || !anim.m_nFrames || dataIndex >= anim.m_wPolyRefs)
                continue;

            const uint32 rawF0 = anim.m_dwBetweenFrames[0];
            const uint32 rawF1 = anim.m_dwBetweenFrames[1];
            const bool frameActive = (rawF0 != 0xFFFFFFFFu && rawF0 < static_cast<uint32>(anim.m_nFrames));
            if (!frameActive || anim.m_bShadowMap)
                continue;

            const float blend = StockBlend(anim);
            if (blend < WorldLightmapSystem::MinAnimBlend)
                continue;

            const uint32 f0 = rawF0;
            const uint32 f1 = (rawF1 < static_cast<uint32>(anim.m_nFrames)) ? rawF1 : f0;
            const float t = (f0 == f1) ? 0.0f : StockPercentBetween(anim);

            LMFramePolyDataCompat *list0 = anim.m_pFrames[f0].m_pPolyDataList;
            LMFramePolyDataCompat *list1 = anim.m_pFrames[f1].m_pPolyDataList;
            if (!list0)
                continue;

            LMFramePolyDataCompat &d0 = list0[dataIndex];
            LMFramePolyDataCompat &d1 = list1 ? list1[dataIndex] : d0;

            a.fill(0);
            b.fill(0);
            const bool ok0 = DecompressLightmap(d0.m_pData, d0.m_wSize, a.data(), n);
            bool ok1 = DecompressLightmap(d1.m_pData, d1.m_wSize, b.data(), n);
            if (!ok0)
                continue;
            if (!ok1)
                b = a;

            for (uint32 y = 0; y < tile.h; ++y)
            {
                for (uint32 x = 0; x < tile.w; ++x)
                {
                    const uint32 i = y * tile.w + x;
                    const uint32 srcA = a[i], srcB = b[i];
                    auto lerp8 = [&](uint32 sh) -> uint32
                    {
                        const float av = float((srcA >> sh) & 255u);
                        const float bv = float((srcB >> sh) & 255u);
                        return static_cast<uint32>(std::clamp(av + (bv - av) * t, 0.0f, 255.0f));
                    };
                    const uint32 mixed = 0xFF000000u | (lerp8(16) << 16) | (lerp8(8) << 8) | lerp8(0);
                    AddLightPixel(LightmapState().atlasPixels[(tile.y + y) * WorldLightmapSystem::AtlasDims + tile.x + x], mixed, blend);
                }
            }
        }
    }

    // Upload only atlas rows which contain changed tiles.  GL_UNPACK_ROW_LENGTH
    // lets DSA upload directly from the 4096-wide CPU backing store without
    // allocating/copying a scratch image per dirty rectangle.
    struct DirtyBand
    {
        uint32 y = 0, minX = 0, maxX = 0, maxY = 0;
    };

    std::vector<DirtyBand> bands;
    bands.reserve(dirtyLMPolys.size());
    std::unordered_map<uint32, size_t> bandByY;
    bandByY.reserve(dirtyLMPolys.size());

    uint32 globalMinX = WorldLightmapSystem::AtlasDims, globalMinY = WorldLightmapSystem::AtlasDims;
    uint32 globalMaxX = 0, globalMaxY = 0;
    uint64_t dirtyPixels = 0;

    for (WorldPolyCompat *poly : dirtyLMPolys)
    {
        auto it = LightmapState().tiles.find(poly);
        if (it == LightmapState().tiles.end())
            continue;
        const WorldLightmapTile &tile = it->second;
        dirtyPixels += uint64_t(tile.w) * uint64_t(tile.h);
        globalMinX = std::min(globalMinX, tile.x);
        globalMinY = std::min(globalMinY, tile.y);
        globalMaxX = std::max(globalMaxX, tile.x + tile.w);
        globalMaxY = std::max(globalMaxY, tile.y + tile.h);

        auto bi = bandByY.find(tile.y);
        if (bi == bandByY.end())
        {
            const size_t index = bands.size();
            bandByY.emplace(tile.y, index);
            bands.push_back(DirtyBand{tile.y, tile.x, tile.x + tile.w, tile.y + tile.h});
        }
        else
        {
            DirtyBand &band = bands[bi->second];
            band.minX = std::min(band.minX, tile.x);
            band.maxX = std::max(band.maxX, tile.x + tile.w);
            band.maxY = std::max(band.maxY, tile.y + tile.h);
        }
    }

    uint64_t uploadedPixels = 0;
    uint32 uploadCalls = 0;
    if (globalMaxX > globalMinX && globalMaxY > globalMinY)
    {
        constexpr GLenum GL_UNPACK_ROW_LENGTH_COMPAT = 0x0CF2;
        glPixelStorei(GL_UNPACK_ROW_LENGTH_COMPAT, (GLint)WorldLightmapSystem::AtlasDims);

        // A few dirty packing rows are cheapest as separate uploads.  Once the
        // change is widespread, one bounding upload avoids hundreds of driver
        // calls while still avoiding the old unconditional full-atlas transfer.
        if (bands.size() <= 48)
        {
            std::sort(bands.begin(), bands.end(), [](const DirtyBand &lhs, const DirtyBand &rhs)
                      { return lhs.y < rhs.y; });
            for (const DirtyBand &band : bands)
            {
                const uint32 w = band.maxX - band.minX;
                const uint32 h = band.maxY - band.y;
                if (!w || !h)
                    continue;
                const uint32 *src = &LightmapState().atlasPixels[band.y * WorldLightmapSystem::AtlasDims + band.minX];
                glf.TextureSubImage2D(LightmapState().atlas, 0, (GLint)band.minX, (GLint)band.y,
                                      (GLsizei)w, (GLsizei)h, GL_BGRA_, GL_UNSIGNED_BYTE, src);
                uploadedPixels += uint64_t(w) * uint64_t(h);
                ++uploadCalls;
            }
        }
        else
        {
            const uint32 w = globalMaxX - globalMinX;
            const uint32 h = globalMaxY - globalMinY;
            const uint32 *src = &LightmapState().atlasPixels[globalMinY * WorldLightmapSystem::AtlasDims + globalMinX];
            glf.TextureSubImage2D(LightmapState().atlas, 0, (GLint)globalMinX, (GLint)globalMinY,
                                  (GLsizei)w, (GLsizei)h, GL_BGRA_, GL_UNSIGNED_BYTE, src);
            uploadedPixels = uint64_t(w) * uint64_t(h);
            uploadCalls = 1;
        }

        glPixelStorei(GL_UNPACK_ROW_LENGTH_COMPAT, 0);
    }

    static uint32 budget = 60;
    if (LogIsSessionEnabled() && (budget && (--budget, true)))
    {
        LOG_SESSION("World3D LM UPDATE-DELTA liveAnims=%u changedAnims=%u affectedPolys=%u dirtyLMTiles=%u dirtyPixels=%llu uploadCalls=%u uploadPixels=%llu usedRows=%u",
                    live, static_cast<unsigned>(changedAnims.size()),
                    static_cast<unsigned>(LightmapState().changedLightAnimPolys.size()),
                    static_cast<unsigned>(dirtyLMPolys.size()),
                    static_cast<unsigned long long>(dirtyPixels), uploadCalls,
                    static_cast<unsigned long long>(uploadedPixels), LightmapState().atlasUsedHeight);
    }

    return static_cast<uint32>(changedAnims.size());
}

void WorldLightmapSystem::SetupPlaneVectors(uint32 index, const LTVector &normal, LTVector &outU, LTVector &outV)
{
    static const LTVector axes[18] =
        {
            {1, 0, 0}, {0, 0, -1}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1}, {0, -1, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 0, 0}, {0, -1, 0}, {0, 0, -1}, {0, 0, 1}, {0, -1, 0}, {1, 0, 0}, {0, 0, -1}, {0, -1, 0}, {-1, 0, 0}};
    index = std::min(index, 5u) * 3u + 1u;
    const LTVector &t = axes[index];
    outU = {
        t.y * normal.z - t.z * normal.y,
        t.z * normal.x - t.x * normal.z,
        t.x * normal.y - t.y * normal.x};
    outV = {
        normal.y * outU.z - normal.z * outU.y,
        normal.z * outU.x - normal.x * outU.z,
        normal.x * outU.y - normal.y * outU.x};
}

bool WorldLightmapSystem::GetUVAtPoint(MainWorldCompat *world, WorldPolyCompat *poly, const LTVector &point, float &outU, float &outV) const
{
    auto it = LightmapState().tiles.find(poly);
    if (it == LightmapState().tiles.end() || !world || !(world->m_fLMGridSize > 0.0001f) || !poly->m_pPlane)
        return false;

    const WorldLightmapTile &tile = it->second;
    auto *plane = reinterpret_cast<LTPlaneCompat *>(poly->m_pPlane);
    LTVector lmU{}, lmV{};
    SetupPlaneVectors((poly->m_wLMPlaneAndFlags >> 11) & 7u, plane->m_vNormal, lmU, lmV);

    const float dx = point.x - poly->m_vLMCenter.x;
    const float dy = point.y - poly->m_vLMCenter.y;
    const float dz = point.z - poly->m_vLMCenter.z;

    const float localU = (dz * lmU.z + dx * lmU.x + dy * lmU.y) / world->m_fLMGridSize + 0.5f;
    const float localV = (dz * lmV.z + dx * lmV.x + dy * lmV.y) / world->m_fLMGridSize + 0.5f;

    outU = (static_cast<float>(tile.x) + localU) / static_cast<float>(WorldLightmapSystem::AtlasDims);
    outV = (static_cast<float>(tile.y) + localV) / static_cast<float>(WorldLightmapSystem::AtlasDims);
    return true;
}

bool WorldLightmapSystem::GetUV(MainWorldCompat *world, WorldPolyCompat *poly, uint32 vert, float &outU, float &outV) const
{
    if (!poly || vert >= poly->m_wNumVerts || !poly->m_Vertices[vert].m_pPoints)
        return false;
    return GetUVAtPoint(world, poly, poly->m_Vertices[vert].m_pPoints->m_vVec, outU, outV);
}
