#include "deluxe_lightmap_baker.h"
#include "world_renderer.h"
#include "world_lightmap_system.h"
#include "world_static_geometry.h"
#include "world_lighting.h"
#include "../../gl_loader.h"
#include "utils/log.h"
#include <GL/gl.h>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
#include <unordered_set>
#include <vector>

namespace
{
    inline DeluxeLightmapBakerState &DeluxeState() { return DeluxeLightmapBaker::Instance().State(); }
    inline WorldLightmapSystemState &LightmapState() { return WorldLightmapSystem::Instance().State(); }
    inline WorldStaticGeometryState &StaticState() { return WorldStaticGeometryRenderer::Instance().State(); }
}

DeluxeLightmapBaker &DeluxeLightmapBaker::Instance()
{
    static DeluxeLightmapBaker v;
    return v;
}

void DeluxeLightmapBaker::SetWorldContext(MainWorldCompat *world, WorldBspCompat *targetBsp)
{
    m_state.world = world;
    m_state.targetBsp = targetBsp;
    m_state.status = (world && targetBsp)
                         ? "Ready to bake tangent-space deluxe directions for current level"
                         : "No active world/lightmap atlas to bake";
}

void DeluxeLightmapBaker::SetSunlight(const LTVector &direction, const LTVector &color)
{
    m_state.sunDir = direction;
    m_state.sunColor = color;
    const float len2 = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
    const float luminance = std::max(0.0f, 0.2126f * color.x + 0.7152f * color.y + 0.0722f * color.z);
    m_state.sunValid = len2 > 1.0e-8f && luminance > 0.001f;
}

void DeluxeLightmapBaker::Term()
{
    if (m_state.atlas)
        GLStateDeleteTextures(1, &m_state.atlas);
    m_state.atlas = 0;
    m_state.atlasPixels.clear();
    m_state.world = nullptr;
    m_state.targetBsp = nullptr;
    m_state.bakedPolys = 0;
    m_state.bakedLuxels = 0;
    m_state.sunValid = false;
    m_state.status = "No deluxe direction bake yet";
}
uint32 DeluxeLightmapBaker::Texture() const { return m_state.atlas; }
uint32 DeluxeLightmapBaker::BakedPolys() const { return m_state.bakedPolys; }
uint32 DeluxeLightmapBaker::BakedLuxels() const { return m_state.bakedLuxels; }
const char *DeluxeLightmapBaker::Status() const { return m_state.status.c_str(); }
void DeluxeLightmapBaker::SetSpecularEnabled(bool v) { m_state.specularEnabled = v; }
bool DeluxeLightmapBaker::SpecularEnabled() const { return m_state.specularEnabled; }
void DeluxeLightmapBaker::SetDebugDirectionView(bool v) { m_state.debugDirectionView = v; }
bool DeluxeLightmapBaker::DebugDirectionView() const { return m_state.debugDirectionView; }
void DeluxeLightmapBaker::SetSpecularStrength(float v) { m_state.specularStrength = std::max(0.0f, v); }
float DeluxeLightmapBaker::SpecularStrength() const { return m_state.specularStrength; }
void DeluxeLightmapBaker::SetSpecularPower(float v) { m_state.specularPower = std::clamp(v, 1.0f, 256.0f); }
float DeluxeLightmapBaker::SpecularPower() const { return m_state.specularPower; }
void DeluxeLightmapBaker::SetDirectionBlurRadius(int v) { m_state.directionBlurRadius = std::clamp(v, 0, 8); }
int DeluxeLightmapBaker::DirectionBlurRadius() const { return m_state.directionBlurRadius; }
void DeluxeLightmapBaker::SetDirectionRadiusScale(float v)
{
    const float clamped = std::clamp(v, 1.0f, 8.0f);
    if (std::fabs(clamped - m_state.directionRadiusScale) <= 0.0001f)
        return;
    m_state.directionRadiusScale = clamped;
    // A radius-scale change affects every local-light contribution.  Drop the
    // old atlas instead of allowing later live LightGroup updates to mix tiles
    // baked with different scales.  The GUI immediately shows that a rebuild
    // is required.
    if (m_state.atlas)
        ClearDirections();
    m_state.status = "Deluxe direction radius changed; rebuild direction atlas";
}
float DeluxeLightmapBaker::DirectionRadiusScale() const { return m_state.directionRadiusScale; }
void DeluxeLightmapBaker::SetSunEdgeSoftness(float v) { m_state.sunEdgeSoftnessLuxels = std::clamp(v, 0.0f, 4.0f); }
float DeluxeLightmapBaker::SunEdgeSoftness() const { return m_state.sunEdgeSoftnessLuxels; }
void DeluxeLightmapBaker::SetGeneratedNormalEnabled(bool v) { m_state.generatedNormalEnabled = v; }
bool DeluxeLightmapBaker::GeneratedNormalEnabled() const { return m_state.generatedNormalEnabled; }
void DeluxeLightmapBaker::SetNormalStrength(float v) { m_state.normalStrength = std::clamp(v, 0.0f, 12.0f); }
float DeluxeLightmapBaker::NormalStrength() const { return m_state.normalStrength; }
void DeluxeLightmapBaker::SetNormalBlack(float v) { m_state.normalBlack = std::clamp(v, 0.0f, 1.0f); }
float DeluxeLightmapBaker::NormalBlack() const { return m_state.normalBlack; }
void DeluxeLightmapBaker::SetNormalWhite(float v) { m_state.normalWhite = std::clamp(v, 0.0f, 1.0f); }
float DeluxeLightmapBaker::NormalWhite() const { return m_state.normalWhite; }
void DeluxeLightmapBaker::SetNormalInvert(bool v) { m_state.normalInvert = v; }
bool DeluxeLightmapBaker::NormalInvert() const { return m_state.normalInvert; }
void DeluxeLightmapBaker::SetNormalInvertX(bool v) { m_state.normalInvertX = v; }
bool DeluxeLightmapBaker::NormalInvertX() const { return m_state.normalInvertX; }
void DeluxeLightmapBaker::SetNormalInvertY(bool v) { m_state.normalInvertY = v; }
bool DeluxeLightmapBaker::NormalInvertY() const { return m_state.normalInvertY; }
void DeluxeLightmapBaker::SetNormalInvertZ(bool v) { m_state.normalInvertZ = v; }
bool DeluxeLightmapBaker::NormalInvertZ() const { return m_state.normalInvertZ; }
void DeluxeLightmapBaker::SetNormalBand(int v) { m_state.normalBand = std::clamp(v, 0, 2); }
int DeluxeLightmapBaker::NormalBand() const { return m_state.normalBand; }
void DeluxeLightmapBaker::SetSpecLightColorInfluence(float v) { m_state.specLightColorInfluence = std::clamp(v, 0.0f, 1.0f); }
float DeluxeLightmapBaker::SpecLightColorInfluence() const { return m_state.specLightColorInfluence; }
void DeluxeLightmapBaker::SetGeneratedSpecularEnabled(bool v) { m_state.generatedSpecularEnabled = v; }
bool DeluxeLightmapBaker::GeneratedSpecularEnabled() const { return m_state.generatedSpecularEnabled; }
void DeluxeLightmapBaker::SetSpecMapStrength(float v) { m_state.specMapStrength = std::clamp(v, 0.0f, 4.0f); }
float DeluxeLightmapBaker::SpecMapStrength() const { return m_state.specMapStrength; }
void DeluxeLightmapBaker::SetSpecBlack(float v) { m_state.specBlack = std::clamp(v, 0.0f, 1.0f); }
float DeluxeLightmapBaker::SpecBlack() const { return m_state.specBlack; }
void DeluxeLightmapBaker::SetSpecWhite(float v) { m_state.specWhite = std::clamp(v, 0.0f, 1.0f); }
float DeluxeLightmapBaker::SpecWhite() const { return m_state.specWhite; }
void DeluxeLightmapBaker::SetSpecInvert(bool v) { m_state.specInvert = v; }
bool DeluxeLightmapBaker::SpecInvert() const { return m_state.specInvert; }

// Deluxe direction lightmap baker, live LightGroup rebake, atlas upload,
// sky-gated sunlight visibility, direction filtering, and full bake algorithms.

struct DeluxeBakeLight
{
    LTVector pos{};
    LTVector color{};
    LTVector dir{};
    float radius = 0.0f;
    float fov = 0.0f;
    float blend = 1.0f; // live Talon LMAnim contribution, 1 for ordinary static lights
    uint32 animIndex = 0xFFFFFFFFu;
    bool point = true;
};

static float DeluxeLuminance(const LTVector &c)
{
    return std::max(0.0f, 0.2126f * c.x + 0.7152f * c.y + 0.0722f * c.z);
}

static float DeluxeDirectionalFalloff(float distance, float stockRadius)
{
    const float radius = stockRadius * std::clamp(DeluxeState().directionRadiusScale, 1.0f, 8.0f);
    if (!(radius > 0.0001f) || distance >= radius)
        return 0.0f;

    // Deluxe direction coverage deliberately extends beyond Talon's direct
    // light radius.  RGB lightmaps remain the energy authority; this smooth
    // tail only preserves a useful dominant-light direction for specular.
    const float x = std::clamp(1.0f - distance / radius, 0.0f, 1.0f);
    return x * x * (3.0f - 2.0f * x);
}

static bool BuildDeluxeTangentFrame(const LTVector &lmU, const LTVector &lmV, const LTVector &normal,
                                    LTVector &outT, LTVector &outB, LTVector &outN)
{
    outN = normal;
    float nl = std::sqrt(outN.x * outN.x + outN.y * outN.y + outN.z * outN.z);
    if (nl <= 0.00001f)
        return false;
    outN.x /= nl;
    outN.y /= nl;
    outN.z /= nl;

    // Tangent follows increasing Talon lightmap U. Remove any numerical normal
    // component so the encoded frame is orthonormal even if the source plane
    // normal is not perfectly unit length.
    outT = lmU;
    const float tdn = outT.x * outN.x + outT.y * outN.y + outT.z * outN.z;
    outT.x -= outN.x * tdn;
    outT.y -= outN.y * tdn;
    outT.z -= outN.z * tdn;
    float tl = std::sqrt(outT.x * outT.x + outT.y * outT.y + outT.z * outT.z);
    if (tl <= 0.00001f)
        return false;
    outT.x /= tl;
    outT.y /= tl;
    outT.z /= tl;

    // Talon's +V basis is N x T.  Store the deluxemap using the OpenGL normal
    // map convention, whose green/+Y direction is opposite the D3D-style V
    // convention used by the original content path.  Defining B as -V here
    // means the G channel is flipped exactly once at bake time.  The shader
    // reconstructs the same T,-V,N frame, so it does not apply a second flip.
    (void)lmV;
    outB = {
        -(outN.y * outT.z - outN.z * outT.y),
        -(outN.z * outT.x - outN.x * outT.z),
        -(outN.x * outT.y - outN.y * outT.x)};
    const float bl = std::sqrt(outB.x * outB.x + outB.y * outB.y + outB.z * outB.z);
    if (bl <= 0.00001f)
        return false;
    outB.x /= bl;
    outB.y /= bl;
    outB.z /= bl;
    return true;
}

static bool EncodeDeluxeWorldDirection(float wx, float wy, float wz,
                                       const LTVector &lmU, const LTVector &lmV, const LTVector &normal,
                                       uint8 &rr, uint8 &gg, uint8 &bb)
{
    LTVector T{}, B{}, N{};
    if (!BuildDeluxeTangentFrame(lmU, lmV, normal, T, B, N))
        return false;

    const float wl = std::sqrt(wx * wx + wy * wy + wz * wz);
    if (wl <= 0.00001f)
        return false;
    wx /= wl;
    wy /= wl;
    wz /= wl;

    float tx = wx * T.x + wy * T.y + wz * T.z;
    float ty = wx * B.x + wy * B.y + wz * B.z;
    float tz = wx * N.x + wy * N.y + wz * N.z;
    const float tl = std::sqrt(tx * tx + ty * ty + tz * tz);
    if (tl <= 0.00001f)
        return false;
    tx /= tl;
    ty /= tl;
    tz /= tl;

    rr = static_cast<uint8>(std::clamp(int(std::lround((tx * 0.5f + 0.5f) * 255.0f)), 0, 255));
    gg = static_cast<uint8>(std::clamp(int(std::lround((ty * 0.5f + 0.5f) * 255.0f)), 0, 255));
    bb = static_cast<uint8>(std::clamp(int(std::lround((tz * 0.5f + 0.5f) * 255.0f)), 0, 255));
    return true;
}

static void GatherDeluxeBakeLights(MainWorldCompat *world, WorldBspCompat *bsp,
                                   std::vector<DeluxeBakeLight> &out)
{
    out.clear();
    if (!world || !bsp)
        return;

    const LTVector center{
        (bsp->m_vMinBox.x + bsp->m_vMaxBox.x) * 0.5f,
        (bsp->m_vMinBox.y + bsp->m_vMaxBox.y) * 0.5f,
        (bsp->m_vMinBox.z + bsp->m_vMaxBox.z) * 0.5f};
    const float ex = std::fabs(bsp->m_vMaxBox.x - bsp->m_vMinBox.x) * 0.5f;
    const float ey = std::fabs(bsp->m_vMaxBox.y - bsp->m_vMinBox.y) * 0.5f;
    const float ez = std::fabs(bsp->m_vMaxBox.z - bsp->m_vMinBox.z) * 0.5f;
    const float worldRadius = std::sqrt(ex * ex + ey * ey + ez * ez) + 8192.0f;

    std::vector<ModelStaticLightInfo> statics(2048);
    const uint32 sc = WorldRenderer::Instance().Lighting().QueryStaticModelLights(world, center, worldRadius,
                                                                                  statics.data(), uint32(statics.size()));
    out.reserve(sc + world->m_LMAnims.m_dwElements + 1u);
    for (uint32 i = 0; i < sc; ++i)
    {
        const auto &l = statics[i];
        if (l.radius <= 0.001f || DeluxeLuminance(l.innerColor) <= 0.001f)
            continue;
        DeluxeBakeLight d{};
        d.pos = l.pos;
        d.color = l.innerColor;
        d.dir = l.dir;
        d.radius = l.radius;
        d.fov = l.fov;
        d.point = (l.fov <= -1.0f || l.fov >= 1.0f || l.fov == 0.0f);
        out.push_back(d);
    }

    // Switchable LightGroups use the exact live Talon LMAnim blend.  Unlike
    // the old binary active test, a group at 0.35 contributes 35% of its
    // directional weight, so overlapping groups rotate the dominant vector
    // continuously while the RGB lightmap fades between them.
    if (world->m_LMAnims.m_pArray)
    {
        for (uint32 i = 1; i < world->m_LMAnims.m_dwElements; ++i)
        {
            const LMAnimCompat &a = world->m_LMAnims.m_pArray[i];
            if (!WorldLightingSystem::AnimDrivesModelLight(a) || a.m_fLightRadius <= 0.001f)
                continue;
            const uint32 raw = a.m_dwBetweenFrames[0];
            const bool frameActive = (raw != 0xFFFFFFFFu && raw < static_cast<uint32>(a.m_nFrames));
            const float blend = frameActive ? WorldLightmapSystem::Instance().StockBlend(a) : 0.0f;
            DeluxeBakeLight d{};
            d.pos = a.m_vLightPos;
            d.color = a.m_vLightColor;
            d.radius = a.m_fLightRadius;
            d.blend = (blend >= WorldLightmapSystem::MinAnimBlend) ? blend : 0.0f;
            d.animIndex = i;
            d.point = true;
            out.push_back(d);
        }
    }
}

static bool DeluxeRayTriangle(const LTVector &o, const LTVector &d,
                              const LTVector &a, const LTVector &b, const LTVector &c,
                              float maxT, float &outT)
{
    const float e1x = b.x - a.x, e1y = b.y - a.y, e1z = b.z - a.z;
    const float e2x = c.x - a.x, e2y = c.y - a.y, e2z = c.z - a.z;
    const float px = d.y * e2z - d.z * e2y;
    const float py = d.z * e2x - d.x * e2z;
    const float pz = d.x * e2y - d.y * e2x;
    const float det = e1x * px + e1y * py + e1z * pz;
    if (std::fabs(det) < 1.0e-7f)
        return false;
    const float invDet = 1.0f / det;
    const float tx = o.x - a.x, ty = o.y - a.y, tz = o.z - a.z;
    const float u = (tx * px + ty * py + tz * pz) * invDet;
    if (u < 0.0f || u > 1.0f)
        return false;
    const float qx = ty * e1z - tz * e1y;
    const float qy = tz * e1x - tx * e1z;
    const float qz = tx * e1y - ty * e1x;
    const float v = (d.x * qx + d.y * qy + d.z * qz) * invDet;
    if (v < 0.0f || u + v > 1.0f)
        return false;
    const float t = (e2x * qx + e2y * qy + e2z * qz) * invDet;
    if (t <= 0.01f || t >= maxT)
        return false;
    outT = t;
    return true;
}

static bool DeluxeRayHitsPoly(const WorldPolyCompat *poly, const LTVector &o,
                              const LTVector &d, float maxT, float &outT)
{
    if (!poly || poly->m_wNumVerts < 3 || poly->m_wNumVerts > 512)
        return false;

    // Cheap ray/sphere rejection before touching the polygon fan.
    const float cx = poly->m_vCenter.x - o.x, cy = poly->m_vCenter.y - o.y, cz = poly->m_vCenter.z - o.z;
    const float along = cx * d.x + cy * d.y + cz * d.z;
    const float r = std::max(0.0f, poly->m_fRadius);
    if (along + r < 0.0f || along - r > maxT)
        return false;
    const float c2 = cx * cx + cy * cy + cz * cz;
    const float perp2 = std::max(0.0f, c2 - along * along);
    if (r > 0.0f && perp2 > r * r)
        return false;

    const SPolyVertexCompat *pv = poly->m_Vertices;
    if (!pv[0].m_pPoints)
        return false;
    const LTVector &a = pv[0].m_pPoints->m_vVec;
    bool hit = false;
    float nearest = maxT;
    for (uint32 i = 1; i + 1 < poly->m_wNumVerts; ++i)
    {
        if (!pv[i].m_pPoints || !pv[i + 1].m_pPoints)
            continue;
        float t = nearest;
        if (DeluxeRayTriangle(o, d, a, pv[i].m_pPoints->m_vVec,
                              pv[i + 1].m_pPoints->m_vVec, nearest, t))
        {
            nearest = t;
            hit = true;
        }
    }
    if (hit)
        outT = nearest;
    return hit;
}

static bool DeluxeRayReachesSkyPortal(WorldBspCompat *bsp, const WorldPolyCompat *receiver,
                                      const LTVector &o, const LTVector &towardSun)
{
    if (!bsp || !bsp->m_pPolies)
        return false;
    float skyT = std::numeric_limits<float>::max();

    // First locate the nearest actual sky portal along the ray.
    for (uint32 i = 0; i < bsp->m_dwPolies; ++i)
    {
        WorldPolyCompat *p = bsp->m_pPolies[i];
        if (!p || !p->m_pSurface || (p->m_pSurface->m_dwFlags & SURF_SKY) == 0)
            continue;
        float t = skyT;
        if (DeluxeRayHitsPoly(p, o, towardSun, skyT, t))
            skyT = t;
    }
    if (!std::isfinite(skyT) || skyT == std::numeric_limits<float>::max())
        return false;

    // Any ordinary compiled world polygon before that portal blocks sunlight.
    for (uint32 i = 0; i < bsp->m_dwPolies; ++i)
    {
        WorldPolyCompat *p = bsp->m_pPolies[i];
        if (!p || p == receiver || !p->m_pSurface)
            continue;
        const uint32 f = p->m_pSurface->m_dwFlags;
        if (f & (SURF_SKY | SURF_INVISIBLE | SURF_NONEXISTANT))
            continue;
        float t = skyT;
        if (DeluxeRayHitsPoly(p, o, towardSun, skyT - 0.02f, t))
            return false;
    }
    return true;
}

// Rebuild one deluxe tile from the current live lighting state.  This is shared
// conceptually with the full bake, but is intentionally tile-scoped so a
// LightGroup fade does not rebake/upload the entire 4096x4096 atlas every frame.
static uint32 RebuildDeluxeTileLive(MainWorldCompat *world, WorldBspCompat *mainBsp,
                                    WorldPolyCompat *poly, const WorldLightmapTile &tile,
                                    const std::vector<DeluxeBakeLight> &lights)
{
    if (!world || !mainBsp || !poly || DeluxeState().atlasPixels.empty() ||
        !(world->m_fLMGridSize > 0.0001f))
        return 0;

    WorldPolyCompat *bakePoly = tile.bakePoly ? tile.bakePoly : poly;
    if (!bakePoly || !bakePoly->m_pPlane)
        return 0;

    auto *plane = reinterpret_cast<LTPlaneCompat *>(bakePoly->m_pPlane);
    LTVector lmU{}, lmV{};
    WorldLightmapSystem::SetupPlaneVectors((bakePoly->m_wLMPlaneAndFlags >> 11) & 7u, plane->m_vNormal, lmU, lmV);
    LTVector N = plane->m_vNormal;
    const float nl = std::sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
    if (nl <= 0.0001f)
        return 0;
    N.x /= nl;
    N.y /= nl;
    N.z /= nl;

    const float grid = world->m_fLMGridSize;
    uint32 validLuxels = 0;
    for (uint32 py = 0; py < tile.h; ++py)
        for (uint32 px = 0; px < tile.w; ++px)
        {
            LTVector P{
                bakePoly->m_vLMCenter.x + (lmU.x * float(px) + lmV.x * float(py)) * grid + N.x * 0.5f,
                bakePoly->m_vLMCenter.y + (lmU.y * float(px) + lmV.y * float(py)) * grid + N.y * 0.5f,
                bakePoly->m_vLMCenter.z + (lmU.z * float(px) + lmV.z * float(py)) * grid + N.z * 0.5f};

            float ax = 0.0f, ay = 0.0f, az = 0.0f, totalWeight = 0.0f;
            float deluxeCoverage = 0.0f;
            for (const DeluxeBakeLight &l : lights)
            {
                if (l.blend <= 0.0f)
                    continue;
                float tx = l.pos.x - P.x, ty = l.pos.y - P.y, tz = l.pos.z - P.z;
                const float d2 = tx * tx + ty * ty + tz * tz;
                if (d2 <= 0.0001f)
                    continue;
                const float dist = std::sqrt(d2);
                float attenuation = DeluxeDirectionalFalloff(dist, l.radius);
                if (attenuation <= 0.0f)
                    continue;
                const float inv = 1.0f / dist;
                tx *= inv;
                ty *= inv;
                tz *= inv;

                const float ndl = N.x * tx + N.y * ty + N.z * tz;
                if (ndl <= 0.0f)
                    continue;

                const float colorWeight = DeluxeLuminance(l.color) / 255.0f;
                if (!l.point)
                {
                    const float dl = std::sqrt(l.dir.x * l.dir.x + l.dir.y * l.dir.y + l.dir.z * l.dir.z);
                    if (dl > 0.0001f)
                    {
                        const float dx = l.dir.x / dl, dy = l.dir.y / dl, dz = l.dir.z / dl;
                        const float cone = -(tx * dx + ty * dy + tz * dz);
                        if (cone < l.fov)
                            continue;
                        const float coneT = (1.0f - l.fov) > 0.0001f ? std::clamp((cone - l.fov) / (1.0f - l.fov), 0.0f, 1.0f) : 1.0f;
                        attenuation *= coneT;
                    }
                }

                const float w = colorWeight * attenuation * ndl * l.blend;
                ax += tx * w;
                ay += ty * w;
                az += tz * w;
                totalWeight += w;
                if (w > 0.00001f)
                    deluxeCoverage = std::max(deluxeCoverage, attenuation);
            }

            if (DeluxeState().sunValid && bakePoly->m_pSurface &&
                (bakePoly->m_pSurface->m_dwFlags & SURF_DIRECTIONALLIGHT) != 0)
            {
                LTVector sun{-DeluxeState().sunDir.x, -DeluxeState().sunDir.y, -DeluxeState().sunDir.z};
                const float sl = std::sqrt(sun.x * sun.x + sun.y * sun.y + sun.z * sun.z);
                if (sl > 0.00001f)
                {
                    sun.x /= sl;
                    sun.y /= sl;
                    sun.z /= sl;
                    const float ndl = N.x * sun.x + N.y * sun.y + N.z * sun.z;
                    if (ndl > 0.0f)
                    {
                        float skyCoverage = 0.0f, skyWeight = 0.0f;
                        const float softness = std::max(0.0f, DeluxeState().sunEdgeSoftnessLuxels);
                        if (softness <= 0.0001f)
                            skyCoverage = DeluxeRayReachesSkyPortal(mainBsp, bakePoly, P, sun) ? 1.0f : 0.0f;
                        else
                        {
                            static const float taps[3] = {-1.0f, 0.0f, 1.0f};
                            for (float oy : taps)
                                for (float ox : taps)
                                {
                                    const float radial = ox * ox + oy * oy;
                                    const float tapWeight = (radial < 0.5f) ? 4.0f : ((radial < 1.5f) ? 2.0f : 1.0f);
                                    LTVector sampleP{
                                        P.x + (lmU.x * ox + lmV.x * oy) * grid * softness,
                                        P.y + (lmU.y * ox + lmV.y * oy) * grid * softness,
                                        P.z + (lmU.z * ox + lmV.z * oy) * grid * softness};
                                    if (DeluxeRayReachesSkyPortal(mainBsp, bakePoly, sampleP, sun))
                                        skyCoverage += tapWeight;
                                    skyWeight += tapWeight;
                                }
                            if (skyWeight > 0.0f)
                                skyCoverage /= skyWeight;
                        }
                        if (skyCoverage > 0.00001f)
                        {
                            const float sw = (DeluxeLuminance(DeluxeState().sunColor) / 255.0f) * ndl * skyCoverage;
                            ax += sun.x * sw;
                            ay += sun.y * sw;
                            az += sun.z * sw;
                            totalWeight += sw;
                            deluxeCoverage = std::max(deluxeCoverage, skyCoverage);
                        }
                    }
                }
            }

            uint8 rr = 128, gg = 128, bb = 255, aa = 0;
            if (totalWeight > 0.00001f &&
                EncodeDeluxeWorldDirection(ax, ay, az, lmU, lmV, N, rr, gg, bb))
            {
                aa = static_cast<uint8>(std::clamp(int(std::lround(deluxeCoverage * 255.0f)), 0, 255));
                ++validLuxels;
            }
            DeluxeState().atlasPixels[(size_t(tile.y + py) * WorldLightmapSystem::AtlasDims) + (tile.x + px)] =
                (uint32(aa) << 24) | (uint32(rr) << 16) | (uint32(gg) << 8) | uint32(bb);
        }

    // Preserve the optional tile-local direction blur during live group fades.
    if (DeluxeState().directionBlurRadius > 0)
    {
        const int r = std::clamp(DeluxeState().directionBlurRadius, 0, 8);
        std::vector<uint32> src(static_cast<size_t>(tile.w) * tile.h);
        for (uint32 y = 0; y < tile.h; ++y)
            std::copy_n(&DeluxeState().atlasPixels[(size_t(tile.y + y) * WorldLightmapSystem::AtlasDims) + tile.x],
                        tile.w, &src[size_t(y) * tile.w]);
        for (uint32 py = 0; py < tile.h; ++py)
            for (uint32 px = 0; px < tile.w; ++px)
            {
                float sx = 0, sy = 0, sz = 0, sa = 0, sw = 0;
                for (int oy = -r; oy <= r; ++oy)
                    for (int ox = -r; ox <= r; ++ox)
                    {
                        const int qx = int(px) + ox, qy = int(py) + oy;
                        if (qx < 0 || qy < 0 || qx >= int(tile.w) || qy >= int(tile.h))
                            continue;
                        const uint32 c = src[size_t(qy) * tile.w + uint32(qx)];
                        const float a = float((c >> 24) & 255u) / 255.0f;
                        const float x = float((c >> 16) & 255u) / 255.0f * 2.0f - 1.0f;
                        const float y = float((c >> 8) & 255u) / 255.0f * 2.0f - 1.0f;
                        const float z = float(c & 255u) / 255.0f * 2.0f - 1.0f;
                        const float w = 1.0f / (1.0f + float(ox * ox + oy * oy));
                        sx += x * a * w;
                        sy += y * a * w;
                        sz += z * a * w;
                        sa += a * w;
                        sw += w;
                    }
                uint8 rr = 128, gg = 128, bb = 255, aa = 0;
                if (sw > 0.0f)
                {
                    const float a = std::clamp(sa / sw, 0.0f, 1.0f);
                    const float l = std::sqrt(sx * sx + sy * sy + sz * sz);
                    if (l > 0.00001f && a > 0.00001f)
                    {
                        sx /= l;
                        sy /= l;
                        sz /= l;
                        rr = static_cast<uint8>(std::clamp(int(std::lround((sx * 0.5f + 0.5f) * 255.0f)), 0, 255));
                        gg = static_cast<uint8>(std::clamp(int(std::lround((sy * 0.5f + 0.5f) * 255.0f)), 0, 255));
                        bb = static_cast<uint8>(std::clamp(int(std::lround((sz * 0.5f + 0.5f) * 255.0f)), 0, 255));
                        aa = static_cast<uint8>(std::clamp(int(std::lround(a * 255.0f)), 0, 255));
                    }
                }
                DeluxeState().atlasPixels[(size_t(tile.y + py) * WorldLightmapSystem::AtlasDims) + (tile.x + px)] =
                    (uint32(aa) << 24) | (uint32(rr) << 16) | (uint32(gg) << 8) | uint32(bb);
            }
    }
    return validLuxels;
}

void DeluxeLightmapBaker::UpdateLightGroups(MainWorldCompat *world, const std::vector<uint32> &changedAnims)
{
    if (!world || !DeluxeState().atlas || DeluxeState().atlasPixels.empty() || changedAnims.empty())
        return;
    WorldBspCompat *mainBsp = DeluxeState().targetBsp ? DeluxeState().targetBsp : StaticState().cachedBsp;
    if (!mainBsp || !world->m_LMAnims.m_pArray)
        return;

    std::unordered_set<WorldPolyCompat *> dirty;
    dirty.reserve(128);
    uint32 changedGroups = 0;
    for (uint32 ai : changedAnims)
    {
        if (ai >= world->m_LMAnims.m_dwElements)
            continue;
        LMAnimCompat &anim = world->m_LMAnims.m_pArray[ai];
        if (!WorldLightingSystem::AnimDrivesModelLight(anim) || !anim.m_pPolyRefs)
            continue;
        ++changedGroups;
        for (uint32 ri = 0; ri < anim.m_wPolyRefs; ++ri)
        {
            const LMPolyRefCompat &ref = anim.m_pPolyRefs[ri];
            if (ref.m_wModel >= world->m_WorldModels.m_dwElements)
                continue;
            WorldDataCompat *wd = world->m_WorldModels.m_pArray[ref.m_wModel];
            WorldBspCompat *b = wd ? wd->m_pOriginalBsp : nullptr;
            if (!b || ref.m_wPoly >= b->m_dwPolies || !b->m_pPolies)
                continue;
            WorldPolyCompat *p = b->m_pPolies[ref.m_wPoly];
            if (p && LightmapState().tiles.find(p) != LightmapState().tiles.end())
                dirty.insert(p);
        }
    }
    if (!changedGroups || dirty.empty())
        return;

    std::vector<DeluxeBakeLight> lights;
    GatherDeluxeBakeLights(world, mainBsp, lights);

    uint32 uploads = 0, rebuiltLuxels = 0;
    std::vector<uint32> upload;
    for (WorldPolyCompat *poly : dirty)
    {
        auto it = LightmapState().tiles.find(poly);
        if (it == LightmapState().tiles.end())
            continue;
        const WorldLightmapTile &tile = it->second;
        rebuiltLuxels += RebuildDeluxeTileLive(world, mainBsp, poly, tile, lights);

        upload.resize(static_cast<size_t>(tile.w) * tile.h);
        for (uint32 y = 0; y < tile.h; ++y)
            std::copy_n(&DeluxeState().atlasPixels[(size_t(tile.y + y) * WorldLightmapSystem::AtlasDims) + tile.x],
                        tile.w, &upload[size_t(y) * tile.w]);
        glf.TextureSubImage2D(DeluxeState().atlas, 0, GLint(tile.x), GLint(tile.y),
                              GLsizei(tile.w), GLsizei(tile.h), GL_BGRA_, GL_UNSIGNED_BYTE,
                              upload.data());
        ++uploads;
    }

    static uint32 budget = 120;
    if (LogIsSessionEnabled() && (budget))
    {
        --budget;
        LOG_SESSION("World3D DELUXE-LIGHTGROUP-UPDATE changedGroups=%u dirtyTiles=%u rebuiltLuxels=%u uploads=%u path=LIVE-LMANIM-BLEND",
                    changedGroups, static_cast<unsigned>(dirty.size()), rebuiltLuxels, uploads);
    }
}

void DeluxeLightmapBaker::ClearDirections()
{
    if (DeluxeState().atlas)
        GLStateDeleteTextures(1, &DeluxeState().atlas);
    DeluxeState().atlas = 0;
    DeluxeState().atlasPixels.clear();
    DeluxeState().bakedPolys = 0;
    DeluxeState().bakedLuxels = 0;
    DeluxeState().status = "Deluxe direction atlas cleared";
}

bool DeluxeLightmapBaker::BakeDirections()
{
    MainWorldCompat *world = DeluxeState().world ? DeluxeState().world : LightmapState().lightGridWorld;
    WorldBspCompat *bsp = DeluxeState().targetBsp ? DeluxeState().targetBsp : StaticState().cachedBsp;
    if (!world || !bsp)
    {
        DeluxeState().status = "No active world/lightmap atlas to bake";
        return false;
    }
    if (LightmapState().tiles.empty() || !(world->m_fLMGridSize > 0.0001f))
    {
        DeluxeState().status = "Current world has no usable Talon lightmap tiles";
        return false;
    }

    std::vector<DeluxeBakeLight> lights;
    GatherDeluxeBakeLights(world, bsp, lights);
    if (lights.empty() && !DeluxeState().sunValid)
    {
        DeluxeState().status = "No static/active LightGroup or sunlight sources found";
        return false;
    }

    DeluxeState().atlasPixels.assign(static_cast<size_t>(WorldLightmapSystem::AtlasDims) * WorldLightmapSystem::AtlasDims, 0x008080FFu);
    DeluxeState().bakedPolys = 0;
    DeluxeState().bakedLuxels = 0;
    uint32 bakedMainPolys = 0, bakedWorldModelPolys = 0;
    uint32 bakedMainLuxels = 0, bakedWorldModelLuxels = 0;

    const float grid = world->m_fLMGridSize;
    for (const auto &kv : LightmapState().tiles)
    {
        WorldPolyCompat *poly = kv.first;
        const WorldLightmapTile &tile = kv.second;
        WorldPolyCompat *bakePoly = tile.bakePoly ? tile.bakePoly : poly;
        if (!poly || !bakePoly || !bakePoly->m_pPlane)
            continue;
        auto *plane = reinterpret_cast<LTPlaneCompat *>(bakePoly->m_pPlane);
        LTVector lmU{}, lmV{};
        WorldLightmapSystem::SetupPlaneVectors((bakePoly->m_wLMPlaneAndFlags >> 11) & 7u, plane->m_vNormal, lmU, lmV);
        LTVector N = plane->m_vNormal;
        const float nl = std::sqrt(N.x * N.x + N.y * N.y + N.z * N.z);
        if (nl > 0.0001f)
        {
            N.x /= nl;
            N.y /= nl;
            N.z /= nl;
        }

        bool polyAny = false;
        for (uint32 py = 0; py < tile.h; ++py)
            for (uint32 px = 0; px < tile.w; ++px)
            {
                // Use the live/world-space polygon when available so brush
                // WorldModels bake from the same receiver positions they render at.
                // The lightmap UVs remain keyed by the original polygon's tile.
                LTVector P{
                    bakePoly->m_vLMCenter.x + (lmU.x * float(px) + lmV.x * float(py)) * grid + N.x * 0.5f,
                    bakePoly->m_vLMCenter.y + (lmU.y * float(px) + lmV.y * float(py)) * grid + N.y * 0.5f,
                    bakePoly->m_vLMCenter.z + (lmU.z * float(px) + lmV.z * float(py)) * grid + N.z * 0.5f};

                float ax = 0.0f, ay = 0.0f, az = 0.0f, totalWeight = 0.0f;
                float deluxeCoverage = 0.0f;
                for (const DeluxeBakeLight &l : lights)
                {
                    float tx = l.pos.x - P.x, ty = l.pos.y - P.y, tz = l.pos.z - P.z;
                    const float d2 = tx * tx + ty * ty + tz * tz;
                    if (d2 <= 0.0001f)
                        continue;
                    const float dist = std::sqrt(d2);
                    float attenuation = DeluxeDirectionalFalloff(dist, l.radius);
                    if (attenuation <= 0.0f)
                        continue;
                    const float inv = 1.0f / dist;
                    tx *= inv;
                    ty *= inv;
                    tz *= inv;

                    const float ndl = N.x * tx + N.y * ty + N.z * tz;
                    if (ndl <= 0.0f)
                        continue;

                    const float colorWeight = DeluxeLuminance(l.color) / 255.0f;
                    if (!l.point)
                    {
                        const float dl = std::sqrt(l.dir.x * l.dir.x + l.dir.y * l.dir.y + l.dir.z * l.dir.z);
                        if (dl > 0.0001f)
                        {
                            const float dx = l.dir.x / dl, dy = l.dir.y / dl, dz = l.dir.z / dl;
                            const float cone = -(tx * dx + ty * dy + tz * dz);
                            if (cone < l.fov)
                                continue;
                            const float coneT = (1.0f - l.fov) > 0.0001f ? std::clamp((cone - l.fov) / (1.0f - l.fov), 0.0f, 1.0f) : 1.0f;
                            attenuation *= coneT;
                        }
                    }

                    const float w = colorWeight * attenuation * ndl * l.blend;
                    ax += tx * w;
                    ay += ty * w;
                    az += tz * w;
                    totalWeight += w;
                    if (w > 0.00001f)
                        deluxeCoverage = std::max(deluxeCoverage, attenuation);
                }

                // Talon's global/static sunlight is directional.  Only surfaces
                // authored for directional lighting receive it, and only when a
                // ray toward the source exits through an actual SURF_SKY portal.
                if (DeluxeState().sunValid && bakePoly->m_pSurface &&
                    (bakePoly->m_pSurface->m_dwFlags & SURF_DIRECTIONALLIGHT) != 0)
                {
                    LTVector sun{-DeluxeState().sunDir.x, -DeluxeState().sunDir.y, -DeluxeState().sunDir.z};
                    const float sl = std::sqrt(sun.x * sun.x + sun.y * sun.y + sun.z * sun.z);
                    if (sl > 0.00001f)
                    {
                        sun.x /= sl;
                        sun.y /= sl;
                        sun.z /= sl;
                        const float ndl = N.x * sun.x + N.y * sun.y + N.z * sun.z;
                        if (ndl > 0.0f)
                        {
                            // Anti-alias the sky visibility test in lightmap
                            // space. A single boolean ray per luxel made the sun
                            // contribution terminate on an obvious lightmap texel
                            // boundary. Sample a 3x3 footprint around the luxel and
                            // store the fractional sky coverage in deluxe alpha.
                            // The direction itself remains the same normalized sun
                            // vector; only its visibility/coverage is softened.
                            float skyCoverage = 0.0f;
                            float skyWeight = 0.0f;
                            const float softness = std::max(0.0f, DeluxeState().sunEdgeSoftnessLuxels);
                            if (softness <= 0.0001f)
                            {
                                skyCoverage = DeluxeRayReachesSkyPortal(bsp, bakePoly, P, sun) ? 1.0f : 0.0f;
                            }
                            else
                            {
                                static const float taps[3] = {-1.0f, 0.0f, 1.0f};
                                for (float oy : taps)
                                    for (float ox : taps)
                                    {
                                        const float radial = ox * ox + oy * oy;
                                        const float tapWeight = (radial < 0.5f) ? 4.0f : ((radial < 1.5f) ? 2.0f : 1.0f);
                                        LTVector sampleP{
                                            P.x + (lmU.x * ox + lmV.x * oy) * grid * softness,
                                            P.y + (lmU.y * ox + lmV.y * oy) * grid * softness,
                                            P.z + (lmU.z * ox + lmV.z * oy) * grid * softness};
                                        if (DeluxeRayReachesSkyPortal(bsp, bakePoly, sampleP, sun))
                                            skyCoverage += tapWeight;
                                        skyWeight += tapWeight;
                                    }
                                if (skyWeight > 0.0f)
                                    skyCoverage /= skyWeight;
                            }

                            if (skyCoverage > 0.00001f)
                            {
                                const float sw = (DeluxeLuminance(DeluxeState().sunColor) / 255.0f) * ndl * skyCoverage;
                                ax += sun.x * sw;
                                ay += sun.y * sw;
                                az += sun.z * sw;
                                totalWeight += sw;
                                deluxeCoverage = std::max(deluxeCoverage, skyCoverage);
                            }
                        }
                    }
                }

                uint8 rr = 128, gg = 128, bb = 255, aa = 0;
                if (totalWeight > 0.00001f &&
                    EncodeDeluxeWorldDirection(ax, ay, az, lmU, lmV, N, rr, gg, bb))
                {
                    // RGB is the normalized dominant light direction in the
                    // surface lightmap tangent frame (T,-V,N).  The -V basis is
                    // the one intentional G-channel flip for OpenGL convention.
                    // Alpha carries visibility coverage only: local lights produce
                    // 1.0, while static sunlight can be fractional at a sky/shadow
                    // boundary.
                    aa = static_cast<uint8>(std::clamp(int(std::lround(deluxeCoverage * 255.0f)), 0, 255));
                    ++DeluxeState().bakedLuxels;
                    if (tile.modelIndex == 0)
                        ++bakedMainLuxels;
                    else
                        ++bakedWorldModelLuxels;
                    polyAny = true;
                }
                DeluxeState().atlasPixels[(size_t(tile.y + py) * WorldLightmapSystem::AtlasDims) + (tile.x + px)] =
                    (uint32(aa) << 24) | (uint32(rr) << 16) | (uint32(gg) << 8) | uint32(bb);
            }
        if (polyAny)
        {
            ++DeluxeState().bakedPolys;
            if (tile.modelIndex == 0)
                ++bakedMainPolys;
            else
                ++bakedWorldModelPolys;
        }
    }

    // Optionally smooth the direction field *inside each authored lightmap
    // tile only*.  Never blur across atlas neighbours because unrelated BSP
    // polygons are packed directly beside one another in the atlas.
    if (DeluxeState().directionBlurRadius > 0)
    {
        std::vector<uint32> src = DeluxeState().atlasPixels;
        const int r = std::clamp(DeluxeState().directionBlurRadius, 0, 8);
        for (const auto &kv : LightmapState().tiles)
        {
            WorldPolyCompat *poly = kv.first;
            if (!poly)
                continue;
            const WorldLightmapTile &tile = kv.second;
            for (uint32 py = 0; py < tile.h; ++py)
                for (uint32 px = 0; px < tile.w; ++px)
                {
                    float sx = 0.0f, sy = 0.0f, sz = 0.0f, sa = 0.0f, sw = 0.0f;
                    for (int oy = -r; oy <= r; ++oy)
                        for (int ox = -r; ox <= r; ++ox)
                        {
                            const int qx = int(px) + ox, qy = int(py) + oy;
                            if (qx < 0 || qy < 0 || qx >= int(tile.w) || qy >= int(tile.h))
                                continue;
                            const uint32 c = src[(size_t(tile.y + uint32(qy)) * WorldLightmapSystem::AtlasDims) + (tile.x + uint32(qx))];
                            const float a = ((c >> 24) & 255u) ? 1.0f : 0.0f;
                            const float x = float((c >> 16) & 255u) / 255.0f * 2.0f - 1.0f;
                            const float y = float((c >> 8) & 255u) / 255.0f * 2.0f - 1.0f;
                            const float z = float(c & 255u) / 255.0f * 2.0f - 1.0f;
                            const float d2 = float(ox * ox + oy * oy);
                            const float w = 1.0f / (1.0f + d2);
                            sx += x * a * w;
                            sy += y * a * w;
                            sz += z * a * w;
                            sa += a * w;
                            sw += w;
                        }
                    uint8 rr = 128, gg = 128, bb = 255, aa = 0;
                    if (sw > 0.0f)
                    {
                        const float a = std::clamp(sa / sw, 0.0f, 1.0f);
                        const float l = std::sqrt(sx * sx + sy * sy + sz * sz);
                        if (l > 0.00001f && a > 0.00001f)
                        {
                            sx /= l;
                            sy /= l;
                            sz /= l;
                            rr = static_cast<uint8>(std::clamp(int(std::lround((sx * 0.5f + 0.5f) * 255.0f)), 0, 255));
                            gg = static_cast<uint8>(std::clamp(int(std::lround((sy * 0.5f + 0.5f) * 255.0f)), 0, 255));
                            bb = static_cast<uint8>(std::clamp(int(std::lround((sz * 0.5f + 0.5f) * 255.0f)), 0, 255));
                            aa = static_cast<uint8>(std::clamp(int(std::lround(a * 255.0f)), 0, 255));
                        }
                    }
                    DeluxeState().atlasPixels[(size_t(tile.y + py) * WorldLightmapSystem::AtlasDims) + (tile.x + px)] =
                        (uint32(aa) << 24) | (uint32(rr) << 16) | (uint32(gg) << 8) | uint32(bb);
                }
        }
    }

    if (DeluxeState().atlas)
        GLStateDeleteTextures(1, &DeluxeState().atlas);
    DeluxeState().atlas = 0;
    glf.CreateTextures(GL_TEXTURE_2D, 1, &DeluxeState().atlas);
    if (!DeluxeState().atlas)
    {
        DeluxeState().status = "Failed to create deluxe GL texture";
        return false;
    }
    glf.TextureStorage2D(DeluxeState().atlas, 1, GL_RGBA8_, WorldLightmapSystem::AtlasDims, WorldLightmapSystem::AtlasDims);
    glf.TextureSubImage2D(DeluxeState().atlas, 0, 0, 0, WorldLightmapSystem::AtlasDims, WorldLightmapSystem::AtlasDims,
                          GL_BGRA_, GL_UNSIGNED_BYTE, DeluxeState().atlasPixels.data());
    glf.TextureParameteri(DeluxeState().atlas, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glf.TextureParameteri(DeluxeState().atlas, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glf.TextureParameteri(DeluxeState().atlas, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
    glf.TextureParameteri(DeluxeState().atlas, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);

    char status[320]{};
    std::snprintf(status, sizeof(status),
                  "Baked %u luxels on %u polys (main %u/%u, worldmodels %u/%u) from %u local/group sources + sunlight=%s",
                  DeluxeState().bakedLuxels, DeluxeState().bakedPolys,
                  bakedMainLuxels, bakedMainPolys,
                  bakedWorldModelLuxels, bakedWorldModelPolys,
                  uint32(lights.size()), DeluxeState().sunValid ? "yes" : "no");
    DeluxeState().status = status;
    LOG_SESSION("World3D DELUXE-BAKE world='%s' localLights=%u sunlight=%u directionRadiusScale=%.2f sunDir=(%.3f %.3f %.3f) sunColor=(%.2f %.2f %.2f) polys=%u luxels=%u mainPolys=%u mainLuxels=%u wmPolys=%u wmLuxels=%u atlas=%ux%u usedH=%u skyGate=SURF_SKY receiverGate=DIRECTIONALLIGHT",
                bsp->m_szWorldName, uint32(lights.size()), DeluxeState().sunValid ? 1u : 0u,
                DeluxeState().directionRadiusScale,
                DeluxeState().sunDir.x, DeluxeState().sunDir.y, DeluxeState().sunDir.z,
                DeluxeState().sunColor.x, DeluxeState().sunColor.y, DeluxeState().sunColor.z,
                DeluxeState().bakedPolys, DeluxeState().bakedLuxels,
                bakedMainPolys, bakedMainLuxels,
                bakedWorldModelPolys, bakedWorldModelLuxels,
                WorldLightmapSystem::AtlasDims, WorldLightmapSystem::AtlasDims, LightmapState().atlasUsedHeight);
    return DeluxeState().bakedLuxels > 0;
}

uint32 DeluxeLightmapBaker::AtlasUsedHeight() const { return LightmapState().atlasUsedHeight; }
