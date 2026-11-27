#pragma once
#include "world_render_types.h"

// Model/decal-facing lighting queries are kept separate from geometry drawing.
class WorldLightingSystem final
{
public:
    void SetHighQualityLightGridEnabled(bool enabled);
    bool IsHighQualityLightGridEnabled() const { return m_highQualityLightGridEnabled; }
    uint32 QueryStaticModelLights(MainWorldCompat *world, const LTVector &pos, float modelRadius,
                                  ModelStaticLightInfo *outLights, uint32 maxLights) const;
    uint32 QueryActiveModelLightAnims(MainWorldCompat *world, const LTVector &pos, float modelRadius,
                                      ModelLightAnimInfo *outLights, uint32 maxLights) const;
    bool ModelLightAllowedByLightAnim(MainWorldCompat *world, const LTVector &pos, float radius) const;
    bool SampleDecalLighting(MainWorldCompat *world, uint32 hPoly, const LTVector &worldPos, LTVector &outColor) const;
    LTVector SampleLightTable(const LightTableCompat &table, const LTVector &worldPos) const;
    static bool AnimDrivesModelLight(const LMAnimCompat &anim);
    bool SampleAnimatedVertexColor(MainWorldCompat *world, WorldPolyCompat *poly, uint32 vert,
                                   float &outR, float &outG, float &outB) const;

private:
    bool m_highQualityLightGridEnabled = false;
};
