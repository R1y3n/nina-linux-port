#include "world_lighting.h"
#include "world_lightmap_system.h"
#include "world_pvs.h"
#include "world_tree_abi.h"
#include "../renderer/renderer_settings.h"
#include "utils/log.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>

namespace
{
    static WorldPVSState &PVSState() { return WorldPVS::Instance().State(); }
    static WorldLightmapSystemState &LightmapState() { return WorldLightmapSystem::Instance().State(); }
}

void WorldLightingSystem::SetHighQualityLightGridEnabled(bool enabled)
{
    if (m_highQualityLightGridEnabled == enabled)
        return;
    m_highQualityLightGridEnabled = enabled;
    RendererSettings::Instance().SaveCurrent();
    LOG_SESSION("Renderer high quality light-grid interpolation -> %d (%s)",
                enabled ? 1 : 0, enabled ? "tricubic 4x4x4" : "trilinear 2x2x2");
}

LTVector WorldLightingSystem::SampleLightTable(const LightTableCompat &lt, const LTVector &pos) const
{
    if (!lt.m_pLookup || !lt.m_dwFullLookupSize ||
        !lt.m_adwLookupSize[0] || !lt.m_adwLookupSize[1] || !lt.m_adwLookupSize[2])
        return {0.0f, 0.0f, 0.0f};

    float c[3] = {
        (pos.x - lt.m_vLookupStart.x) * lt.m_vReciBlockSize.x,
        (pos.y - lt.m_vLookupStart.y) * lt.m_vReciBlockSize.y,
        (pos.z - lt.m_vLookupStart.z) * lt.m_vReciBlockSize.z};
    int i0[3];
    float f[3];
    for (int a = 0; a < 3; ++a)
    {
        const int maxI = std::max(0, lt.m_anLookupSizeMinusOne[a]);
        int base = (int)std::floor(c[a]);
        if (base < 0)
            base = 0;
        if (base > maxI)
            base = maxI;
        if (maxI <= 0)
        {
            i0[a] = 0;
            f[a] = 0.0f;
            continue;
        }
        if (base >= maxI)
        {
            i0[a] = maxI - 1;
            // d3d.ren 0x1000C916..0x1000C985 backs up one cell at the
            // positive boundary and sets the forward interpolation weight to
            // zero. This deliberately selects the penultimate lookup sample.
            f[a] = 0.0f;
        }
        else
        {
            i0[a] = base;
            f[a] = std::clamp(c[a] - std::floor(c[a]), 0.0f, 1.0f);
        }
    }
    auto fetch = [&](int x, int y, int z) -> LTVector
    {
        const uint32 idx = (uint32)x + (uint32)y * lt.m_adwLookupSize[0] +
                           (uint32)z * lt.m_dwXSizeTimesYSize;
        if (idx >= lt.m_dwFullLookupSize)
            return {0.0f, 0.0f, 0.0f};
        const LTRGBCompat &q = lt.m_pLookup[idx];
        return {(float)q.r, (float)q.g, (float)q.b};
    };
    auto mixv = [](const LTVector &a, const LTVector &b, float t) -> LTVector
    { return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t}; };

    if (m_highQualityLightGridEnabled)
    {
        auto cubic = [](float p0, float p1, float p2, float p3, float t) -> float
        {
            // Catmull-Rom cubic interpolation.  Clamp after the separable
            // filter because authored 8-bit LightTable values must not
            // overshoot the valid Talon lighting range.
            const float t2 = t * t, t3 = t2 * t;
            return 0.5f * ((2.0f * p1) + (-p0 + p2) * t +
                           (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2 +
                           (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t3);
        };
        auto cubicv = [&](const LTVector &p0, const LTVector &p1, const LTVector &p2, const LTVector &p3, float t) -> LTVector
        {
            return {cubic(p0.x, p1.x, p2.x, p3.x, t),
                    cubic(p0.y, p1.y, p2.y, p3.y, t),
                    cubic(p0.z, p1.z, p2.z, p3.z, t)};
        };
        auto ci = [](int i, int n) -> int
        { return std::clamp(i, 0, std::max(0, n - 1)); };
        const int nx = (int)lt.m_adwLookupSize[0], ny = (int)lt.m_adwLookupSize[1], nz = (int)lt.m_adwLookupSize[2];
        LTVector yz[4][4];
        for (int zz = 0; zz < 4; ++zz)
            for (int yy = 0; yy < 4; ++yy)
            {
                const int z = ci(i0[2] + zz - 1, nz), y = ci(i0[1] + yy - 1, ny);
                LTVector px[4];
                for (int xx = 0; xx < 4; ++xx)
                    px[xx] = fetch(ci(i0[0] + xx - 1, nx), y, z);
                yz[zz][yy] = cubicv(px[0], px[1], px[2], px[3], f[0]);
            }
        LTVector zv[4];
        for (int zz = 0; zz < 4; ++zz)
            zv[zz] = cubicv(yz[zz][0], yz[zz][1], yz[zz][2], yz[zz][3], f[1]);
        LTVector out = cubicv(zv[0], zv[1], zv[2], zv[3], f[2]);
        out.x = std::clamp(out.x, 0.0f, 255.0f);
        out.y = std::clamp(out.y, 0.0f, 255.0f);
        out.z = std::clamp(out.z, 0.0f, 255.0f);
        return out;
    }

    const int x1 = std::min(i0[0] + 1, (int)lt.m_adwLookupSize[0] - 1);
    const int y1 = std::min(i0[1] + 1, (int)lt.m_adwLookupSize[1] - 1);
    const int z1 = std::min(i0[2] + 1, (int)lt.m_adwLookupSize[2] - 1);
    LTVector c00 = mixv(fetch(i0[0], i0[1], i0[2]), fetch(x1, i0[1], i0[2]), f[0]);
    LTVector c10 = mixv(fetch(i0[0], y1, i0[2]), fetch(x1, y1, i0[2]), f[0]);
    LTVector c01 = mixv(fetch(i0[0], i0[1], z1), fetch(x1, i0[1], z1), f[0]);
    LTVector c11 = mixv(fetch(i0[0], y1, z1), fetch(x1, y1, z1), f[0]);
    LTVector z0 = mixv(c00, c10, f[1]);
    LTVector z1v = mixv(c01, c11, f[1]);
    return mixv(z0, z1v, f[2]);
}

bool WorldLightingSystem::SampleDecalLighting(MainWorldCompat *world, uint32 hPoly, const LTVector &worldPos, LTVector &outColor) const
{
    outColor = {1.0f, 1.0f, 1.0f};
    if (!world)
        return false;

    WorldPolyCompat *poly = nullptr;
    if (hPoly != 0xFFFFFFFFu && world->m_WorldModels.m_pArray)
    {
        const uint32 worldIndex = (hPoly >> 16) & 0xFFFFu;
        const uint32 polyIndex = hPoly & 0xFFFFu;
        if (worldIndex < world->m_WorldModels.m_dwElements)
        {
            WorldDataCompat *wd = world->m_WorldModels.m_pArray[worldIndex];
            WorldBspCompat *bsp = wd ? wd->m_pOriginalBsp : nullptr;
            if (bsp && bsp->m_pPolies && polyIndex < bsp->m_dwPolies)
                poly = bsp->m_pPolies[polyIndex];
        }
    }

    bool haveBase = false;

    // Sample the exact current CPU lightmap atlas used by the world pass.
    // LightAnim/LightGroup edits are reflected here every frame.
    if (poly)
    {
        float u = 0.0f, v = 0.0f;
        auto tileIt = LightmapState().tiles.find(poly);
        if (tileIt != LightmapState().tiles.end() && WorldLightmapSystem::Instance().GetUVAtPoint(world, poly, worldPos, u, v) && !LightmapState().atlasPixels.empty())
        {
            const WorldLightmapTile &tile = tileIt->second;
            const float atlasX = u * float(WorldLightmapSystem::AtlasDims) - 0.5f;
            const float atlasY = v * float(WorldLightmapSystem::AtlasDims) - 0.5f;
            const float minX = float(tile.x), maxX = float(tile.x + tile.w - 1u);
            const float minY = float(tile.y), maxY = float(tile.y + tile.h - 1u);
            const float sx = std::clamp(atlasX, minX, maxX);
            const float sy = std::clamp(atlasY, minY, maxY);
            const int x0 = (int)std::floor(sx), y0 = (int)std::floor(sy);
            const int x1 = std::min(x0 + 1, (int)(tile.x + tile.w - 1u));
            const int y1 = std::min(y0 + 1, (int)(tile.y + tile.h - 1u));
            const float fx = sx - float(x0), fy = sy - float(y0);
            auto sample = [&](int x, int y) -> LTVector
            {
                const uint32 px = LightmapState().atlasPixels[(size_t)y * WorldLightmapSystem::AtlasDims + (size_t)x];
                return {float((px >> 16) & 255u) / 255.0f, float((px >> 8) & 255u) / 255.0f, float(px & 255u) / 255.0f};
            };
            auto lerp = [](const LTVector &a, const LTVector &b, float t) -> LTVector
            {
                return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t};
            };
            const LTVector a = lerp(sample(x0, y0), sample(x1, y0), fx);
            const LTVector b = lerp(sample(x0, y1), sample(x1, y1), fx);
            outColor = lerp(a, b, fy);
            haveBase = true;
        }
    }

    if (!haveBase)
    {
        const LTVector grid = SampleLightTable(world->m_LightTable, worldPos);
        outColor = {std::clamp(grid.x / 255.0f, 0.0f, 1.0f),
                    std::clamp(grid.y / 255.0f, 0.0f, 1.0f),
                    std::clamp(grid.z / 255.0f, 0.0f, 1.0f)};
        haveBase = world->m_LightTable.m_pLookup != nullptr;
    }

    // Dynamic lights are NOT baked into either source above.  The world
    // shader evaluates them live, so reproduce the same spherical 1.50x
    // smooth attenuation here or an impact mark stays constant while a
    // flashlight/flicker/muzzle flash changes the wall beneath it.
    LTVector dynamicAdd{0.0f, 0.0f, 0.0f};
    for (DynamicLightCompat *light : PVSState().visibleDynamicLights)
    {
        if (!light || !(light->m_Base.m_dwFlags & FLAG_VISIBLE) ||
            (light->m_Base.m_dwFlags & FLAG_ONLYLIGHTOBJECTS) ||
            light->m_fLightRadius <= 0.001f || !std::isfinite(light->m_fLightRadius))
            continue;

        const float radius = light->m_fLightRadius * 1.50f;
        const float dx = light->m_Base.m_vPos.x - worldPos.x;
        const float dy = light->m_Base.m_vPos.y - worldPos.y;
        const float dz = light->m_Base.m_vPos.z - worldPos.z;
        const float dist2 = dx * dx + dy * dy + dz * dz;
        const float radius2 = radius * radius;
        if (dist2 >= radius2)
            continue;

        float a = std::max(0.0f, 1.0f - dist2 / radius2);
        a = a * a * (3.0f - 2.0f * a);
        constexpr float kInv255 = 1.0f / 255.0f;
        dynamicAdd.x += ((2.0f * float(light->m_Base.m_nColorR) - 255.0f) * kInv255) * a;
        dynamicAdd.y += ((2.0f * float(light->m_Base.m_nColorG) - 255.0f) * kInv255) * a;
        dynamicAdd.z += ((2.0f * float(light->m_Base.m_nColorB) - 255.0f) * kInv255) * a;
    }

    // Decals need an illumination/tint factor rather than raw additive RGB.
    // Consume remaining headroom just like the world dynamic-light path so a
    // flickering light brightens the mark without blowing it to white.
    auto ApplySignedLight = [](float base, float lightDelta)
    {
        const float contribution = (lightDelta >= 0.0f)
                                       ? lightDelta * (1.0f - base)
                                       : lightDelta * base;
        return std::clamp(base + contribution, 0.0f, 1.0f);
    };
    outColor.x = ApplySignedLight(outColor.x, dynamicAdd.x);
    outColor.y = ApplySignedLight(outColor.y, dynamicAdd.y);
    outColor.z = ApplySignedLight(outColor.z, dynamicAdd.z);
    return haveBase || std::fabs(dynamicAdd.x) > 0.0001f ||
           std::fabs(dynamicAdd.y) > 0.0001f ||
           std::fabs(dynamicAdd.z) > 0.0001f;
}

static bool LMAnimModelLightActive(const LMAnimCompat &anim);
static const LMAnimCompat *FindModelLightAnim(MainWorldCompat *world,
                                              const LTVector &pos, float radius,
                                              uint32 *outIndex);

bool WorldLightingSystem::ModelLightAllowedByLightAnim(MainWorldCompat *world, const LTVector &pos, float radius) const
{
    uint32 groupIndex = 0;
    const LMAnimCompat *group = FindModelLightAnim(world, pos, radius, &groupIndex);
    if (!group)
        return true;

    // The corresponding contribution is emitted from the LMAnim record by
    // WorldLightingSystem::QueryActiveModelLightAnims.  Never also submit the raw OT_LIGHT
    // or active groups are doubled and inactive groups can leak through an
    // engine light object whose runtime state is not reflected in its color.
    static uint32 replacementBudget = 96;
    if (LogIsSessionEnabled() && (replacementBudget > 0 && replacementBudget--))
        LOG_SESSION("World3D MODEL-LIGHTGROUP replace dynamic anim=%u name='%s' active=%u pos=(%.2f %.2f %.2f) radius=%.2f raw=%08X blend=%.4f",
                    groupIndex, group->m_szName, LMAnimModelLightActive(*group) ? 1u : 0u,
                    pos.x, pos.y, pos.z, radius, group->m_dwBetweenFrames[0], group->m_fBlendPercent);
    return false;
}

bool WorldLightingSystem::AnimDrivesModelLight(const LMAnimCompat &anim)
{
    if (anim.m_nFrames == 0 || anim.m_fLightRadius <= 0.0f)
        return false;
    // BASE is the baked world contribution, not a switchable source light.
    if (std::strncmp(anim.m_szName, "LightAnim_BASE", 14) == 0)
        return false;
    // Talon-generated switchable/flicker animations use these suffixes.
    return std::strstr(anim.m_szName, "__LG") != nullptr ||
           std::strstr(anim.m_szName, "__LA") != nullptr;
}

static bool LMAnimModelLightActive(const LMAnimCompat &anim)
{
    const uint32 raw = anim.m_dwBetweenFrames[0];
    if (raw == 0xFFFFFFFFu || raw >= static_cast<uint32>(anim.m_nFrames))
        return false;
    return WorldLightmapSystem::Instance().StockBlend(anim) >= WorldLightmapSystem::MinAnimBlend;
}

static const LMAnimCompat *FindModelLightAnim(MainWorldCompat *world,
                                              const LTVector &pos, float radius,
                                              uint32 *outIndex)
{
    if (!world || !world->m_LMAnims.m_pArray || world->m_LMAnims.m_dwElements <= 1 || radius <= 0.0f)
        return nullptr;

    const LMAnimCompat *best = nullptr;
    uint32 bestIndex = 0;
    float bestScore = std::numeric_limits<float>::max();

    for (uint32 i = 1; i < world->m_LMAnims.m_dwElements; ++i)
    {
        const LMAnimCompat &anim = world->m_LMAnims.m_pArray[i];
        if (!WorldLightingSystem::AnimDrivesModelLight(anim))
            continue;

        // LMAnim carries the authoritative source-light position/color/radius
        // used by Talon's animated model-light path.  The runtime StaticLight
        // radius is not guaranteed to be byte-for-byte identical to the
        // compiled LMAnim radius (spot/falloff preprocessing can change it),
        // so radius is a ranking hint rather than a hard rejection.  Position
        // is the stable identity.  The previous 1%/2.5% tolerances were too
        // strict and failed to associate AVP2's switchable lights at all.
        const float posTol = std::max(32.0f, std::max(anim.m_fLightRadius, radius) * 0.08f);
        const float dx = anim.m_vLightPos.x - pos.x;
        const float dy = anim.m_vLightPos.y - pos.y;
        const float dz = anim.m_vLightPos.z - pos.z;
        const float d2 = dx * dx + dy * dy + dz * dz;
        if (d2 > posTol * posTol)
            continue;

        const float maxR = std::max(1.0f, std::max(anim.m_fLightRadius, radius));
        const float radiusFrac = std::fabs(anim.m_fLightRadius - radius) / maxR;
        const float score = d2 + (radiusFrac * posTol) * (radiusFrac * posTol);
        if (score < bestScore)
        {
            bestScore = score;
            best = &anim;
            bestIndex = i;
        }
    }

    if (best && outIndex)
        *outIndex = bestIndex;
    return best;
}

struct StaticLightQueryContext
{
    MainWorldCompat *world = nullptr;
    ModelStaticLightInfo *outLights = nullptr;
    uint32 maxLights = 0;
    uint32 count = 0;
};

static void __cdecl StaticModelLightCB(void *pObj, void *pUser)
{
    auto *ctx = reinterpret_cast<StaticLightQueryContext *>(pUser);
    auto *light = reinterpret_cast<StaticLightCompat *>(pObj);
    if (!ctx || !light || !ctx->outLights || ctx->count >= ctx->maxLights)
        return;

    uint32 groupIndex = 0;
    const LMAnimCompat *group = FindModelLightAnim(ctx->world, light->m_vPos, light->m_fRadius, &groupIndex);
    if (group)
    {
        // A switchable/animated source is represented twice in the world data:
        // the ordinary StaticLight object and the LMAnim's model-light record.
        // Stock uses the LMAnim state for the animated contribution.  Do not
        // also feed the unconditional StaticLight into the model shader or an
        // OFF LightGroup remains visibly ON (and an ON group is doubled).
        static uint32 replacementBudget = 128;
        if (LogIsSessionEnabled() && (replacementBudget > 0 && replacementBudget--))
            LOG_SESSION("World3D MODEL-LIGHTGROUP replace static anim=%u name='%s' active=%u staticPos=(%.2f %.2f %.2f) staticR=%.2f animPos=(%.2f %.2f %.2f) animR=%.2f raw=%08X blend=%.4f",
                        groupIndex, group->m_szName, LMAnimModelLightActive(*group) ? 1u : 0u,
                        light->m_vPos.x, light->m_vPos.y, light->m_vPos.z,
                        light->m_fRadius,
                        group->m_vLightPos.x, group->m_vLightPos.y, group->m_vLightPos.z,
                        group->m_fLightRadius, group->m_dwBetweenFrames[0], group->m_fBlendPercent);
        return;
    }

    ModelStaticLightInfo &out = ctx->outLights[ctx->count++];
    out.pos = light->m_vPos;
    out.radius = light->m_fRadius;
    out.innerColor = light->m_vInnerColor;
    out.dir = light->m_vDir;
    out.fov = light->m_fFOV;
    out.outerColor = light->m_vOuterColor;
}

uint32 WorldLightingSystem::QueryStaticModelLights(MainWorldCompat *world, const LTVector &pos, float modelRadius,
                                                   ModelStaticLightInfo *outLights, uint32 maxLights) const
{
    if (!world || !outLights || !maxLights)
        return 0;

    auto *tree = reinterpret_cast<WorldTreeCompat *>(reinterpret_cast<uint8 *>(world) + 108);
    if (!tree || !tree->m_pVTable || !tree->m_pVTable->FindObjectsInBox2)
        return 0;

    FindObjInfoCompat info{};
    info.m_pTree = tree;
    info.m_eObjArray = NOA_Lights_Compat;
    info.m_vMin = {pos.x - modelRadius, pos.y - modelRadius, pos.z - modelRadius};
    info.m_vMax = {pos.x + modelRadius, pos.y + modelRadius, pos.z + modelRadius};
    info.m_vViewpoint = pos;
    info.m_CB = &StaticModelLightCB;

    StaticLightQueryContext ctx{};
    ctx.world = world;
    ctx.outLights = outLights;
    ctx.maxLights = maxLights;
    info.m_pCBUser = &ctx;

    tree->m_pVTable->FindObjectsInBox2(tree, nullptr, &info);
    return ctx.count;
}

uint32 WorldLightingSystem::QueryActiveModelLightAnims(MainWorldCompat *world, const LTVector &pos, float modelRadius,
                                                       ModelLightAnimInfo *outLights, uint32 maxLights) const
{
    if (!world || !world->m_LMAnims.m_pArray || !outLights || !maxLights)
        return 0;

    uint32 count = 0;
    for (uint32 i = 1; i < world->m_LMAnims.m_dwElements && count < maxLights; ++i)
    {
        const LMAnimCompat &anim = world->m_LMAnims.m_pArray[i];
        if (!AnimDrivesModelLight(anim) || !LMAnimModelLightActive(anim))
            continue;

        const float sumR = std::max(0.0f, modelRadius) + anim.m_fLightRadius;
        const float dx = pos.x - anim.m_vLightPos.x;
        const float dy = pos.y - anim.m_vLightPos.y;
        const float dz = pos.z - anim.m_vLightPos.z;
        if (dx * dx + dy * dy + dz * dz >= sumR * sumR)
            continue;

        ModelLightAnimInfo &out = outLights[count++];
        out.pos = anim.m_vLightPos;
        out.color = anim.m_vLightColor;
        out.radius = anim.m_fLightRadius;
        out.animIndex = i;
    }
    return count;
}

// Animated per-vertex LightAnim sampling shared by static BSP and brush WorldModels.
bool WorldLightingSystem::SampleAnimatedVertexColor(MainWorldCompat *world, WorldPolyCompat *poly,
                                                    uint32 vert, float &outR, float &outG, float &outB) const
{
    outR = outG = outB = 0.0f;
    if (!world || !poly || !poly->m_pPolyAnimRefs || poly->m_dwPolyAnimRefs == 0 ||
        poly->m_dwPolyAnimRefs > 256 || !world->m_LMAnims.m_pArray)
        return false;

    bool found = false;
    for (uint32 pr = 0; pr < poly->m_dwPolyAnimRefs; ++pr)
    {
        const PolyAnimRefCompat &pref = poly->m_pPolyAnimRefs[pr];
        const uint32 animIndex = pref.m_wRefs[0];
        const uint32 dataIndex = pref.m_wRefs[1];
        if (animIndex >= world->m_LMAnims.m_dwElements)
            continue;

        LMAnimCompat &anim = world->m_LMAnims.m_pArray[animIndex];
        if (!anim.m_pFrames || anim.m_nFrames == 0 || dataIndex >= anim.m_wPolyRefs)
            continue;

        const uint32 rawF0 = anim.m_dwBetweenFrames[0];
        const uint32 rawF1 = anim.m_dwBetweenFrames[1];
        if (rawF0 == 0xFFFFFFFFu || rawF0 >= static_cast<uint32>(anim.m_nFrames))
            continue;
        uint32 f0 = rawF0;
        uint32 f1 = (rawF1 < static_cast<uint32>(anim.m_nFrames)) ? rawF1 : f0;

        LMFramePolyDataCompat *list0 = anim.m_pFrames[f0].m_pPolyDataList;
        LMFramePolyDataCompat *list1 = anim.m_pFrames[f1].m_pPolyDataList;
        if (!list0)
            continue;

        LMFramePolyDataCompat &d0 = list0[dataIndex];
        LMFramePolyDataCompat &d1 = list1 ? list1[dataIndex] : d0;
        if (!d0.m_pReds || !d0.m_pGreens || !d0.m_pBlues || vert >= d0.m_nVertices)
            continue;

        const float between = WorldLightmapSystem::Instance().StockPercentBetween(anim);
        // d3d.ren 0x10030419..0x10030431 uses m_fBlendPercent only as
        // an activation threshold. Once active, 0x100185A0 contributes the
        // interpolated vertex RGB at full strength.
        if (WorldLightmapSystem::Instance().StockBlend(anim) < WorldLightmapSystem::MinAnimBlend)
            continue;

        const uint8 t = static_cast<uint8>(std::clamp(int(between * 255.0f + 0.5f), 0, 255));
        const uint8 it = static_cast<uint8>(255u - t);
        auto channel = [&](uint8 *a, uint8 *b) -> uint8
        {
            const uint8 v0 = a[vert];
            const uint8 v1 = (b && vert < d1.m_nVertices) ? b[vert] : v0;
            if (t == 0u)
                return v0;
            if (t == 255u)
                return v1;
            return WorldLightmapSystem::Instance().StockSatAddByte(WorldLightmapSystem::Instance().StockMulByte(v0, it), WorldLightmapSystem::Instance().StockMulByte(v1, t));
        };

        const uint8 rr = channel(d0.m_pReds, d1.m_pReds);
        const uint8 gg = channel(d0.m_pGreens, d1.m_pGreens);
        const uint8 bb = channel(d0.m_pBlues, d1.m_pBlues);
        outR = float(std::min(255u, uint32(outR) + uint32(rr)));
        outG = float(std::min(255u, uint32(outG) + uint32(gg)));
        outB = float(std::min(255u, uint32(outB) + uint32(bb)));
        found = true;
    }

    outR /= 255.0f;
    outG /= 255.0f;
    outB /= 255.0f;
    return found;
}
