#pragma once
#include "../../lt_renderer_abi.h"
#include <string>
#include <vector>

// Deluxe-lightmap lifetime, configuration, GPU atlas, and all bake/rebake
// algorithms are owned by this subsystem. No deluxe implementation lives in
// world_runtime.cpp and there are no loose g_deluxe* globals.
struct DeluxeLightmapBakerState
{
    uint32 atlas = 0;
    std::vector<uint32> atlasPixels;
    MainWorldCompat *world = nullptr;
    WorldBspCompat *targetBsp = nullptr;
    uint32 bakedPolys = 0;
    uint32 bakedLuxels = 0;
    std::string status = "No deluxe direction bake yet";

    bool specularEnabled = false;
    bool debugDirectionView = false;
    float specularStrength = 0.65f;
    float specularPower = 48.0f;
    int directionBlurRadius = 0;
    float directionRadiusScale = 3.0f;
    float sunEdgeSoftnessLuxels = 1.5f;

    LTVector sunDir{};
    LTVector sunColor{};
    bool sunValid = false;

    bool generatedNormalEnabled = true;
    float normalStrength = 2.0f;
    float normalBlack = 0.05f;
    float normalWhite = 0.95f;
    bool normalInvert = false;
    bool normalInvertX = false;
    bool normalInvertY = false;
    bool normalInvertZ = false;
    int normalBand = 2;

    float specLightColorInfluence = 1.0f;
    bool generatedSpecularEnabled = true;
    float specMapStrength = 1.35f;
    float specBlack = 0.10f;
    float specWhite = 0.85f;
    bool specInvert = false;
};

class DeluxeLightmapBaker final
{
public:
    static DeluxeLightmapBaker &Instance();

    bool BakeDirections();
    void Term();
    void SetWorldContext(MainWorldCompat *world, WorldBspCompat *targetBsp);
    void SetSunlight(const LTVector &direction, const LTVector &color);
    void UpdateLightGroups(MainWorldCompat *world, const std::vector<uint32> &changedAnims);
    void ClearDirections();
    uint32 Texture() const;
    uint32 AtlasUsedHeight() const;
    uint32 BakedPolys() const;
    uint32 BakedLuxels() const;
    const char *Status() const;

    void SetSpecularEnabled(bool v);
    bool SpecularEnabled() const;
    void SetDebugDirectionView(bool v);
    bool DebugDirectionView() const;
    void SetSpecularStrength(float v);
    float SpecularStrength() const;
    void SetSpecularPower(float v);
    float SpecularPower() const;
    void SetDirectionBlurRadius(int v);
    int DirectionBlurRadius() const;
    void SetDirectionRadiusScale(float v);
    float DirectionRadiusScale() const;
    void SetSunEdgeSoftness(float v);
    float SunEdgeSoftness() const;
    void SetGeneratedNormalEnabled(bool v);
    bool GeneratedNormalEnabled() const;
    void SetNormalStrength(float v);
    float NormalStrength() const;
    void SetNormalBlack(float v);
    float NormalBlack() const;
    void SetNormalWhite(float v);
    float NormalWhite() const;
    void SetNormalInvert(bool v);
    bool NormalInvert() const;
    void SetNormalInvertX(bool v);
    bool NormalInvertX() const;
    void SetNormalInvertY(bool v);
    bool NormalInvertY() const;
    void SetNormalInvertZ(bool v);
    bool NormalInvertZ() const;
    void SetNormalBand(int v);
    int NormalBand() const;
    void SetSpecLightColorInfluence(float v);
    float SpecLightColorInfluence() const;
    void SetGeneratedSpecularEnabled(bool v);
    bool GeneratedSpecularEnabled() const;
    void SetSpecMapStrength(float v);
    float SpecMapStrength() const;
    void SetSpecBlack(float v);
    float SpecBlack() const;
    void SetSpecWhite(float v);
    float SpecWhite() const;
    void SetSpecInvert(bool v);
    bool SpecInvert() const;

    DeluxeLightmapBakerState &State() { return m_state; }
    const DeluxeLightmapBakerState &State() const { return m_state; }

private:
    DeluxeLightmapBaker() = default;
    DeluxeLightmapBakerState m_state{};
};
