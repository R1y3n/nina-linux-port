// Talon SharedTexture cache/lifetime manager. Low-level DTX upload lives in Texture.cpp.
#include "subsystems/renderer/Console.h"
#include "subsystems/textures/Texture.h"
#include "gl_loader.h"
#include "utils/log.h"
#include "subsystems/renderer/fog_state.h"
#include "subsystems/textures/texture_manager.h"
#include "subsystems/renderer/renderer_settings.h"

#include <windows.h>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <unordered_set>

#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif
#ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif

namespace
{
    static TextureManagerState &TextureState() { return TextureManager::Instance().State(); }

    static void DecodeDXT5AlphaBlock(const uint8 *block, uint8 outAlpha[16])
    {
        const uint8 a0 = block[0], a1 = block[1];
        uint8 palette[8]{};
        palette[0] = a0;
        palette[1] = a1;
        if (a0 > a1)
        {
            palette[2] = uint8((6u * a0 + 1u * a1 + 3u) / 7u);
            palette[3] = uint8((5u * a0 + 2u * a1 + 3u) / 7u);
            palette[4] = uint8((4u * a0 + 3u * a1 + 3u) / 7u);
            palette[5] = uint8((3u * a0 + 4u * a1 + 3u) / 7u);
            palette[6] = uint8((2u * a0 + 5u * a1 + 3u) / 7u);
            palette[7] = uint8((1u * a0 + 6u * a1 + 3u) / 7u);
        }
        else
        {
            palette[2] = uint8((4u * a0 + 1u * a1 + 2u) / 5u);
            palette[3] = uint8((3u * a0 + 2u * a1 + 2u) / 5u);
            palette[4] = uint8((2u * a0 + 3u * a1 + 2u) / 5u);
            palette[5] = uint8((1u * a0 + 4u * a1 + 2u) / 5u);
            palette[6] = 0;
            palette[7] = 255;
        }
        uint64_t bits = 0;
        for (unsigned i = 0; i < 6; ++i)
            bits |= (uint64_t(block[2 + i]) << (8u * i));
        for (unsigned i = 0; i < 16; ++i)
            outAlpha[i] = palette[(bits >> (3u * i)) & 7u];
    }

    static bool GetDXT5Mip0(SharedTexture *sharedTexture, TextureDataCompat *&td, const uint8 *&data, uint32 &w, uint32 &h)
    {
        td = nullptr;
        data = nullptr;
        w = h = 0;
        if (!sharedTexture || !TextureState().renderStruct || !TextureState().renderStruct->GetTexture)
            return false;
        TextureData *raw = TextureState().renderStruct->GetTexture(sharedTexture);
        td = reinterpret_cast<TextureDataCompat *>(raw);
        if (!td || td->m_DtxHeader.GetBPPIdent() != BPP_S3TC_DXT5)
            return false;
        w = td->m_Mips[0].m_dwWidth ? td->m_Mips[0].m_dwWidth : td->m_DtxHeader.m_wBaseWidth;
        h = td->m_Mips[0].m_dwHeight ? td->m_Mips[0].m_dwHeight : td->m_DtxHeader.m_wBaseHeight;
        data = reinterpret_cast<const uint8 *>(td->m_Mips[0].m_pData);
        return data && w && h;
    }
}

// ===== anisotropic texture filtering =====
void TextureManager::EnsureAnisotropyCaps()
{
    if (m_state.anisotropyCapsChecked)
        return;

    m_state.anisotropyCapsChecked = true;
    m_state.anisotropySupported = false;
    m_state.maxAnisotropy = 1.0f;

    // EXT_texture_filter_anisotropic is not part of the OpenGL 4.6 core spec,
    // so query the extension limit and treat GL_INVALID_ENUM as unsupported.
    while (glGetError() != GL_NO_ERROR)
    {
    }
    GLfloat maxLevel = 1.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxLevel);
    const GLenum err = glGetError();
    if (err == GL_NO_ERROR && maxLevel > 1.0f)
    {
        m_state.anisotropySupported = true;
        m_state.maxAnisotropy = std::max(1.0f, maxLevel);
    }

    LOG_SESSION("Texture filtering: anisotropy supported=%d max=%.1fx",
                m_state.anisotropySupported ? 1 : 0, m_state.maxAnisotropy);
}

void TextureManager::ApplyAnisotropyToCachedTextures()
{
    EnsureAnisotropyCaps();
    const float level = (m_state.anisotropic16xEnabled && m_state.anisotropySupported)
                            ? std::min(16.0f, m_state.maxAnisotropy)
                            : 1.0f;
    for (Texture *texture : m_state.textures)
        if (texture)
            texture->ApplyAnisotropy(level);
}

void TextureManager::SetAnisotropic16xEnabled(bool enabled)
{
    EnsureAnisotropyCaps();
    const bool actual = enabled && m_state.anisotropySupported;
    if (m_state.anisotropic16xEnabled == actual)
        return;

    m_state.anisotropic16xEnabled = actual;
    ApplyAnisotropyToCachedTextures();
    RendererSettings::Instance().SaveCurrent();
    LOG_SESSION("Renderer 16x anisotropic filtering -> %d (applied=%.1fx, hardwareMax=%.1fx)%s",
                actual ? 1 : 0,
                actual ? std::min(16.0f, m_state.maxAnisotropy) : 1.0f,
                m_state.maxAnisotropy,
                (enabled && !m_state.anisotropySupported) ? " (unsupported)" : "");
}

void TextureManager::SetRenderStruct(RenderStruct *renderStruct)
{
    TextureState().renderStruct = renderStruct;
}

Texture *TextureManager::Ensure(SharedTexture *sharedTexture, bool textureChanged)
{
    if (!sharedTexture || !TextureState().renderStruct || !TextureState().renderStruct->GetTexture)
        return nullptr;

    auto *st = reinterpret_cast<SharedTextureCompat *>(sharedTexture);
    auto *rt = reinterpret_cast<Texture *>(st->m_pRenderData);

    // Authoritative validation: Talon can recycle SharedTexture, engine-data, and
    // file storage addresses.  Ask the engine for the current TextureData before
    // trusting renderer-owned metadata.  This is especially important for sky
    // WorldModels, whose authored ScaledU/V are in source-texel units.
    TextureData *raw = TextureState().renderStruct->GetTexture(sharedTexture);
    if (!raw)
        return rt;

    auto *td = reinterpret_cast<TextureDataCompat *>(raw);
    const uint32 currentWidth = td->m_Mips[0].m_dwWidth ? td->m_Mips[0].m_dwWidth : td->m_DtxHeader.m_wBaseWidth;
    const uint32 currentHeight = td->m_Mips[0].m_dwHeight ? td->m_Mips[0].m_dwHeight : td->m_DtxHeader.m_wBaseHeight;
    const uint32 currentBpp = td->m_DtxHeader.GetBPPIdent();
    const uint32 currentIFlags = static_cast<uint32>(td->m_DtxHeader.m_nIFlags);
    const uint32 currentUserFlags = static_cast<uint32>(td->m_DtxHeader.m_nUserFlags);
    void *currentMip0Data = td->m_Mips[0].m_pData;

    const bool cachedIdentityValid = rt &&
                                     rt->sharedTexture == sharedTexture &&
                                     rt->engineDataSnapshot == st->m_pEngineData &&
                                     rt->fileSnapshot == st->m_pFile &&
                                     rt->textureDataSnapshot == raw &&
                                     rt->mip0DataSnapshot == currentMip0Data &&
                                     rt->width == currentWidth && rt->height == currentHeight &&
                                     rt->bppIdent == currentBpp &&
                                     rt->dtxIFlags == currentIFlags && rt->dtxUserFlags == currentUserFlags;

    if (rt && !textureChanged && cachedIdentityValid)
        return rt;

    if (rt && !cachedIdentityValid)
    {
        LOG_SESSION("Texture3D: authoritative cache mismatch shared=%p GL=%u cached=%ux%u bpp=%u if=%08X td=%p mip0=%p current=%ux%u bpp=%u if=%08X td=%p mip0=%p -> reupload",
                    sharedTexture, rt->texture, rt->width, rt->height, rt->bppIdent, rt->dtxIFlags,
                    rt->textureDataSnapshot, rt->mip0DataSnapshot,
                    currentWidth, currentHeight, currentBpp, currentIFlags, raw, currentMip0Data);
    }

    if (!rt)
    {
        rt = new Texture();
        rt->sharedTexture = sharedTexture;
        st->m_pRenderData = rt;
        TextureState().textures.insert(rt);
    }

    if (!rt->Upload(td, st))
    {
        LOG_SESSION("Texture3D: upload failed shared=%p bpp=%u size=%ux%u",
                    sharedTexture,
                    td->m_DtxHeader.GetBPPIdent(),
                    td->m_DtxHeader.m_wBaseWidth,
                    td->m_DtxHeader.m_wBaseHeight);
        return nullptr;
    }

    // Capture engine-owned identity only after a successful upload.  This is
    // deliberately separate from the SharedTexture address because Talon reuses
    // those addresses when resources/worlds are replaced.
    rt->sharedTexture = sharedTexture;
    rt->engineDataSnapshot = st->m_pEngineData;
    rt->fileSnapshot = st->m_pFile;
    rt->textureDataSnapshot = raw;
    rt->mip0DataSnapshot = td->m_Mips[0].m_pData;

    EnsureAnisotropyCaps();
    rt->ApplyAnisotropy((m_state.anisotropic16xEnabled && m_state.anisotropySupported)
                            ? std::min(16.0f, m_state.maxAnisotropy)
                            : 1.0f);

    static uint32 logBudget = 32;
    if (LogIsSessionEnabled() && (logBudget))
    {
        LOG_SESSION("Texture3D: uploaded shared=%p GL=%u %ux%u scaled=%ux%u mipOffset=%u bpp=%u mips=%u iFlags=%08X userFlags=%08X stockFmt=%u prefer16=%u force4444=%u bilinear=%u trilinear=%u minFilter=%04X magFilter=%04X synthChromaAlpha=%u linked=%p texType=%u detScale=%.4f detAngle=%d",
                    sharedTexture, rt->texture, rt->width, rt->height,
                    rt->scaledWidth, rt->scaledHeight, rt->mipOffset,
                    rt->bppIdent, rt->mipLevels, rt->dtxIFlags, rt->dtxUserFlags,
                    static_cast<unsigned>(rt->stockFormatClass),
                    (rt->dtxIFlags & 0x0002u) ? 1u : 0u,
                    (rt->dtxIFlags & 0x0080u) ? 1u : 0u,
                    unsigned(rt->stockBilinear), unsigned(rt->stockTrilinear),
                    unsigned(rt->glMinFilter), unsigned(rt->glMagFilter),
                    rt->syntheticChromaAlpha ? 1u : 0u,
                    st->m_pLinkedTexture, static_cast<unsigned>(st->m_eTexType),
                    rt->detailScale, static_cast<int>(rt->detailAngle));
        --logBudget;
    }

    // IMPORTANT:
    // Do NOT call RenderStruct::FreeTexture here.
    //
    // The reference renderer only releases the engine's system texture copy
    // when its CacheTextures policy explicitly allows it. We have not yet
    // reconstructed that console-variable policy, so freeing it unconditionally
    // can invalidate engine-owned TextureData while AVP2 still expects it.
    //
    // Keep the system copy alive for correctness. We can reintroduce the
    // conditional release later once the exact cache policy is implemented.
    return rt;
}

GLuint TextureManager::GetOrCreateDerivedMaterial(SharedTexture *sharedTexture)
{
    Texture *rt = Ensure(sharedTexture, false);
    if (!rt)
        return 0;
    if (rt->materialTexture)
        return rt->materialTexture;
    if (!TextureState().renderStruct || !TextureState().renderStruct->GetTexture)
        return 0;
    TextureData *raw = TextureState().renderStruct->GetTexture(sharedTexture);
    auto *td = reinterpret_cast<TextureDataCompat *>(raw);
    if (!td)
        return 0;
    if (!rt->BuildDerivedMaterial(td))
        return 0;
    EnsureAnisotropyCaps();
    rt->ApplyAnisotropy((m_state.anisotropic16xEnabled && m_state.anisotropySupported)
                            ? std::min(16.0f, m_state.maxAnisotropy)
                            : 1.0f);
    static uint32 logBudget = 24;
    if (LogIsSessionEnabled() && (logBudget))
    {
        LOG_SESSION("Texture3D DERIVED-MATERIAL shared=%p GL=%u source=%ux%u bpp=%u path=LAZY-WORLD-ONLY",
                    sharedTexture, rt->materialTexture, rt->width, rt->height, rt->bppIdent);
        --logBudget;
    }
    return rt->materialTexture;
}

bool TextureManager::DXT5AlphaOnlyEnabled() const
{
    if (Console::Instance().GetFloat("SkyDXT5AlphaOnly", 0.0f) != 0.0f)
        return true;
    char value[32] = {};
    const DWORD len = GetEnvironmentVariableA("AVP2_SKY_DXT5_ALPHA_ONLY", value,
                                              static_cast<DWORD>(sizeof(value)));
    return len > 0 && len < sizeof(value) && std::strcmp(value, "0") != 0;
}

bool TextureManager::SampleDXT5Alpha(SharedTexture *sharedTexture, float rawU, float rawV, uint8 &outAlpha)
{
    TextureDataCompat *td = nullptr;
    const uint8 *data = nullptr;
    uint32 w = 0, h = 0;
    if (!GetDXT5Mip0(sharedTexture, td, data, w, h))
        return false;
    const float fu = rawU - std::floor(rawU / float(w)) * float(w);
    const float fv = rawV - std::floor(rawV / float(h)) * float(h);
    const uint32 x = std::min(w - 1u, uint32(std::floor(fu)));
    const uint32 y = std::min(h - 1u, uint32(std::floor(fv)));
    const uint32 bw = std::max(1u, (w + 3u) / 4u);
    const uint32 bx = x / 4u, by = y / 4u;
    const uint8 *block = data + (by * bw + bx) * 16u;
    uint8 alpha[16];
    DecodeDXT5AlphaBlock(block, alpha);
    outAlpha = alpha[(y & 3u) * 4u + (x & 3u)];
    return true;
}

void TextureManager::LogDXT5AlphaDiagnostic(SharedTexture *sharedTexture, const char *label)
{
    if (!LogIsSessionEnabled())
        return;
    TextureDataCompat *td = nullptr;
    const uint8 *data = nullptr;
    uint32 w = 0, h = 0;
    if (!GetDXT5Mip0(sharedTexture, td, data, w, h))
        return;
    static std::unordered_set<uintptr_t> logged;
    const uintptr_t key = reinterpret_cast<uintptr_t>(sharedTexture);
    if (!logged.insert(key).second)
        return;

    uint64_t hist[16]{};
    uint64_t zero = 0, full = 0, total = 0;
    uint8 amin = 255, amax = 0;
    const uint32 bw = std::max(1u, (w + 3u) / 4u), bh = std::max(1u, (h + 3u) / 4u);
    for (uint32 by = 0; by < bh; ++by)
        for (uint32 bx = 0; bx < bw; ++bx)
        {
            const uint8 *block = data + (by * bw + bx) * 16u;
            uint8 alpha[16];
            DecodeDXT5AlphaBlock(block, alpha);
            for (uint32 py = 0; py < 4; ++py)
                for (uint32 px = 0; px < 4; ++px)
                {
                    const uint32 x = bx * 4u + px, y = by * 4u + py;
                    if (x >= w || y >= h)
                        continue;
                    const uint8 a = alpha[py * 4u + px];
                    amin = std::min(amin, a);
                    amax = std::max(amax, a);
                    ++hist[a >> 4];
                    zero += (a == 0);
                    full += (a == 255);
                    ++total;
                }
        }
    LOG_SESSION("Texture3D DXT5-ALPHA label='%s' shared=%p dim=%ux%u blocks=%ux%u bytes=%u min=%u max=%u zero=%llu full=%llu total=%llu hist16=[%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu]",
                label ? label : "?", sharedTexture, w, h, bw, bh, bw * bh * 16u, unsigned(amin), unsigned(amax),
                (unsigned long long)zero, (unsigned long long)full, (unsigned long long)total,
                (unsigned long long)hist[0], (unsigned long long)hist[1], (unsigned long long)hist[2], (unsigned long long)hist[3],
                (unsigned long long)hist[4], (unsigned long long)hist[5], (unsigned long long)hist[6], (unsigned long long)hist[7],
                (unsigned long long)hist[8], (unsigned long long)hist[9], (unsigned long long)hist[10], (unsigned long long)hist[11],
                (unsigned long long)hist[12], (unsigned long long)hist[13], (unsigned long long)hist[14], (unsigned long long)hist[15]);
    for (uint32 i = 0; i < std::min<uint32>(8u, bw * bh); ++i)
    {
        const uint8 *b = data + i * 16u;
        LOG_SESSION("Texture3D DXT5-BLOCK label='%s' i=%u bytes=%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
                    label ? label : "?", i, b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9], b[10], b[11], b[12], b[13], b[14], b[15]);
    }

    Texture *rt = GetCached(sharedTexture);
    GLint internalFmt = 0, compressed = 0, glw = 0, glh = 0;
    if (rt && rt->texture && glf.GetTextureLevelParameteriv)
    {
        glf.GetTextureLevelParameteriv(rt->texture, 0, GL_TEXTURE_INTERNAL_FORMAT_, &internalFmt);
        glf.GetTextureLevelParameteriv(rt->texture, 0, GL_TEXTURE_COMPRESSED_, &compressed);
        glf.GetTextureLevelParameteriv(rt->texture, 0, GL_TEXTURE_WIDTH_, &glw);
        glf.GetTextureLevelParameteriv(rt->texture, 0, GL_TEXTURE_HEIGHT_, &glh);
    }
    LOG_SESSION("Texture3D DXT5-GL label='%s' shared=%p GL=%u queried=%dx%d internal=%04X compressed=%d expectedDXT5=%04X alphaOnly=%d",
                label ? label : "?", sharedTexture, rt ? rt->texture : 0, glw, glh, unsigned(internalFmt), compressed,
                unsigned(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT_), DXT5AlphaOnlyEnabled() ? 1 : 0);
}

void TextureManager::LogRawDiagnostic(SharedTexture *sharedTexture, const char *label)
{
    if (!LogIsSessionEnabled())
        return;
    if (!sharedTexture || !TextureState().renderStruct || !TextureState().renderStruct->GetTexture)
        return;

    static std::unordered_set<uintptr_t> s_logged;
    const uintptr_t key = reinterpret_cast<uintptr_t>(sharedTexture);
    if (!s_logged.insert(key).second)
        return;

    auto *st = reinterpret_cast<SharedTextureCompat *>(sharedTexture);
    TextureData *raw = TextureState().renderStruct->GetTexture(sharedTexture);
    auto *td = reinterpret_cast<TextureDataCompat *>(raw);
    if (!td)
    {
        LOG_SESSION("Texture3D DTX-RAW label='%s' shared=%p GetTexture=NULL engineData=%p renderData=%p file=%p linked=%p texType=%u stFlags=%04X stMipOffset=%u",
                    label ? label : "?", sharedTexture, st->m_pEngineData, st->m_pRenderData,
                    st->m_pFile, st->m_pLinkedTexture, unsigned(st->m_eTexType),
                    unsigned(st->m_wFlags), unsigned(st->m_dwMipMapOffsetED));
        return;
    }

    const DtxHeaderCompat &dh = td->m_DtxHeader;
    LOG_SESSION("Texture3D DTX-RAW label='%s' shared=%p td=%p tdShared=%p assocMatch=%u vtbl=%08X resType=%08X tdFlags=%08X alloc=%u dataBuf=%p sections=%p",
                label ? label : "?", sharedTexture, td, td->m_pSharedTexture,
                td->m_pSharedTexture == st ? 1u : 0u, unsigned(td->m_dwVTable),
                unsigned(td->m_dwResType), unsigned(td->m_dwFlags), unsigned(td->m_dwAllocSize),
                td->m_pDataBuffer, td->m_pDtxSections);
    LOG_SESSION("Texture3D DTX-HEADER label='%s' hdrRes=%08X version=%d base=%ux%u mipmaps=%u sections=%u iFlags=%08X userFlags=%08X group=%u mipsInUse=%u bpp=%u mipNC=%u mipED=%u priority=%u detScale=%.6f detAngle=%d stMipED=%u",
                label ? label : "?", unsigned(dh.m_dwResType), int(dh.m_nVersion),
                unsigned(dh.m_wBaseWidth), unsigned(dh.m_wBaseHeight), unsigned(dh.m_wMipmaps),
                unsigned(dh.m_wSections), unsigned(dh.m_nIFlags), unsigned(dh.m_nUserFlags),
                unsigned(dh.m_Extra.m_nTexGroup), unsigned(dh.m_Extra.m_nMipMapsInUse),
                unsigned(dh.GetBPPIdent()), unsigned(dh.m_Extra.m_nMipMapOffsetNC),
                unsigned(dh.m_Extra.m_nMipMapOffsetED), unsigned(dh.m_Extra.m_nTexPriority),
                dh.m_Extra.m_fDetTexScale, int(dh.m_Extra.m_nDetTexAngle),
                unsigned(st->m_dwMipMapOffsetED));

    for (uint32 i = 0; i < 8; ++i)
    {
        const TextureMipDataCompat &m = td->m_Mips[i];
        LOG_SESSION("Texture3D DTX-MIP label='%s' i=%u dim=%ux%u data=%p pitch=%d data16=%08X data20=%08X",
                    label ? label : "?", unsigned(i), unsigned(m.m_dwWidth), unsigned(m.m_dwHeight),
                    m.m_pData, int(m.m_nPitch), unsigned(m.m_dwData16), unsigned(m.m_dwData20));
    }

    // Raw bytes make this probe useful even if TextureDataCompat itself is the bug.
    // Dump the full 164-byte DTX header and enough of the mip-array prefix to
    // independently recover widths/heights/pointers from the log.
    const uint8 *bytes = reinterpret_cast<const uint8 *>(td);
    auto dumpRange = [&](uint32 begin, uint32 end, const char *tag)
    {
        char hex[16 * 3 + 1];
        for (uint32 off = begin; off < end; off += 16)
        {
            const uint32 n = std::min<uint32>(16u, end - off);
            char *p = hex;
            for (uint32 j = 0; j < n; ++j)
            {
                static const char *k = "0123456789ABCDEF";
                const uint8 v = bytes[off + j];
                *p++ = k[v >> 4];
                *p++ = k[v & 15];
                if (j + 1 < n)
                    *p++ = ' ';
            }
            *p = 0;
            LOG_SESSION("Texture3D DTX-BYTES label='%s' %s off=%03X bytes=%s",
                        label ? label : "?", tag, unsigned(off), hex);
        }
    };
    dumpRange(0u, 172u, "HEADER");
    dumpRange(184u, 204u + 8u * sizeof(TextureMipDataCompat), "MIPS");
}

void TextureManager::Unbind(SharedTexture *sharedTexture)
{
    if (!sharedTexture)
        return;

    auto *st = reinterpret_cast<SharedTextureCompat *>(sharedTexture);
    auto *rt = reinterpret_cast<Texture *>(st->m_pRenderData);
    if (!rt)
        return;

    rt->Destroy();

    TextureState().textures.erase(rt);
    st->m_pRenderData = nullptr;
    rt->sharedTexture = nullptr;
    delete rt;
}

void TextureManager::Term()
{
    for (Texture *rt : TextureState().textures)
    {
        if (!rt)
            continue;

        if (rt->sharedTexture)
        {
            auto *st = reinterpret_cast<SharedTextureCompat *>(rt->sharedTexture);
            if (st->m_pRenderData == rt)
                st->m_pRenderData = nullptr;
        }

        rt->Destroy();

        rt->sharedTexture = nullptr;
        delete rt;
    }
    TextureState().textures.clear();
    // The next renderer context may expose a different extension limit. Keep
    // the user's enabled state, but force a capability re-query.
    TextureState().anisotropyCapsChecked = false;
    TextureState().anisotropySupported = false;
    TextureState().maxAnisotropy = 1.0f;
}

TextureManager &TextureManager::Instance()
{
    static TextureManager v;
    return v;
}

Texture *TextureManager::GetCached(SharedTexture *sharedTexture) const
{
    if (!sharedTexture)
        return nullptr;
    auto *st = reinterpret_cast<SharedTextureCompat *>(sharedTexture);
    return reinterpret_cast<Texture *>(st->m_pRenderData);
}

Texture *TextureManager::GetOrEnsure(SharedTexture *sharedTexture)
{
    // Never trust SharedTexture::m_pRenderData by itself. Talon reuses and
    // repopulates SharedTexture records across renderer/world reloads, and the
    // pointer can therefore be non-null while referring to stale renderer data.
    //
    // Base world textures already pass through Ensure(), which validates the
    // engine TextureData/mip identity before returning a cached GL texture.
    // Linked detail/environment textures and the global model environment map
    // use GetOrEnsure(), so bypassing that validation here made those secondary
    // texture stages uniquely vulnerable to stale cache state after the recent
    // renderer ownership/lifetime refactors.
    //
    // Ensure() has a fast cached path once identity is confirmed, so keeping a
    // separate unchecked return path here is both unsafe and unnecessary.
    return Ensure(sharedTexture, false);
}

// Legacy Talon-facing compatibility API. Implementation ownership is the class.
