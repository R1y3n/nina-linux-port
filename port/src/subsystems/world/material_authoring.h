#pragma once

#include "../../lt_renderer_abi.h"
#include <GL/gl.h>
#include <string>
#include <vector>
#include <cstdint>

struct AuthoredMaterialSettings
{
    float normalStrength = 1.0f;
    float specularStrength = 1.0f;
    float glossMinPower = 8.0f;
    float glossMaxPower = 256.0f;
    float glossBias = 0.0f;
    float reflectionStrength = 0.0f;
    std::string reflectionMap;
};

struct MaterialAuthoringPerfStats
{
    double resolveMs = 0.0;
    double nameMs = 0.0;
    double lookupMs = 0.0;
    double loadMs = 0.0;
    uint32_t resolveCalls = 0;
    uint32_t cacheHits = 0;
    uint32_t recordsLoaded = 0;
};

struct AuthoredMaterialBinding
{
    bool valid = false;
    bool materialFileExists = false;
    std::string key;
    std::string sourceTexture;
    std::string matPath;
    GLuint albedoTexture = 0;
    GLuint normalTexture = 0;
    GLuint specularTexture = 0;
    GLuint reflectionTexture = 0;
    AuthoredMaterialSettings settings{};
};

class MaterialAuthoringSystem final
{
public:
    static MaterialAuthoringSystem &Instance();

    const AuthoredMaterialBinding *Resolve(SharedTexture *baseTexture);
    void Reset();
    void ReloadAll();

    // Creates default .mat files only for materials referenced by the currently
    // loaded map. This works even when the base .dtx comes from a REZ; the path
    // is derived from the map's SharedTexture identifier and written below
    // ./textures.
    int CreateMissingMaterialFilesForActiveMap();

    std::vector<std::string> MaterialKeys() const;
    bool GetSettings(const std::string &key, AuthoredMaterialSettings &out) const;
    bool GetBinding(const std::string &key, AuthoredMaterialBinding &out) const;
    bool SetSettings(const std::string &key, const AuthoredMaterialSettings &settings, bool saveToDisk);
    std::string RootDirectory() const;
    MaterialAuthoringPerfStats ConsumePerfStats();

private:
    MaterialAuthoringSystem() = default;
};
