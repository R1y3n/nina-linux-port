#pragma once
#include "Texture.h"
#include <unordered_set>

struct TextureManagerState
{
    RenderStruct *renderStruct = nullptr;
    std::unordered_set<Texture *> textures;
    bool anisotropic16xEnabled = false;
    bool anisotropyCapsChecked = false;
    bool anisotropySupported = false;
    float maxAnisotropy = 1.0f;
};

class TextureManager final
{
public:
    static TextureManager &Instance();
    void SetRenderStruct(RenderStruct *rs);
    Texture *Ensure(SharedTexture *texture, bool changed = false);
    Texture *GetCached(SharedTexture *texture) const;
    Texture *GetOrEnsure(SharedTexture *texture);
    GLuint GetOrCreateDerivedMaterial(SharedTexture *texture);
    void Unbind(SharedTexture *texture);
    void Term();
    void LogRawDiagnostic(SharedTexture *texture, const char *label);
    void LogDXT5AlphaDiagnostic(SharedTexture *texture, const char *label);
    bool SampleDXT5Alpha(SharedTexture *texture, float u, float v, uint8 &alpha);
    bool DXT5AlphaOnlyEnabled() const;
    void SetAnisotropic16xEnabled(bool enabled);
    bool IsAnisotropic16xEnabled() const { return m_state.anisotropic16xEnabled; }

    TextureManagerState &State() { return m_state; }
    const TextureManagerState &State() const { return m_state; }

private:
    TextureManager() = default;
    void EnsureAnisotropyCaps();
    void ApplyAnisotropyToCachedTextures();
    TextureManagerState m_state{};
};
