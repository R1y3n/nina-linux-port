#pragma once

#include "../../lt_renderer_abi.h"
#include <GL/gl.h>

struct TextureDataCompat;
struct SharedTextureCompat;

class Texture final
{
public:
    Texture() = default;
    ~Texture() = default;
    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    bool Upload(TextureDataCompat *data, SharedTextureCompat *shared);
    bool BuildDerivedMaterial(TextureDataCompat *data);
    void ApplyAnisotropy(float level);
    void Destroy();

    SharedTexture *sharedTexture = nullptr;
    void *engineDataSnapshot = nullptr;
    void *fileSnapshot = nullptr;
    void *textureDataSnapshot = nullptr;
    void *mip0DataSnapshot = nullptr;
    GLuint texture = 0;
    GLuint materialTexture = 0;
    uint32 width = 0;
    uint32 height = 0;
    uint32 scaledWidth = 0;
    uint32 scaledHeight = 0;
    uint32 mipOffset = 0;
    uint32 bppIdent = 0;
    uint32 mipLevels = 0;
    uint32 dtxIFlags = 0;
    uint32 dtxUserFlags = 0;
    uint8 stockFormatClass = 0;
    uint8 stockBilinear = 1;
    uint8 stockTrilinear = 0;
    uint32 glMinFilter = 0;
    uint32 glMagFilter = 0;
    float alphaRef = 0.0f;
    bool fullBright = false;
    bool syntheticChromaAlpha = false;
    float detailScale = 1.0f;
    float detailCos = 1.0f;
    float detailSin = 0.0f;
    int16 detailAngle = 0;
};
