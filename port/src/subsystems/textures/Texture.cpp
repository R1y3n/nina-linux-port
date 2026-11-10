#include "subsystems/renderer/Console.h"
#include "Texture.h"

#include "subsystems/textures/Texture.h"
#include "gl_loader.h"
#include "subsystems/renderer/fog_state.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cstdint>
#include <vector>
#include "utils/log.h"

#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif

namespace
{

    static GLenum InternalFormatFor(uint32 bpp)
    {
        switch (bpp)
        {
        case BPP_S3TC_DXT1:
            return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT_;
        case BPP_S3TC_DXT3:
            return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT_;
        case BPP_S3TC_DXT5:
            return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT_;
        case BPP_32:
            return GL_RGBA8_;
        // Talon chromakey WorldModels may use 24-bit DTX data.  D3D's
        // color-key path supplies transparency even though the source texture has
        // no alpha channel, so keep an alpha plane available in GL.
        case BPP_24:
            return GL_RGBA8_;
        default:
            return 0;
        }
    }

    static bool IsCompressed(uint32 bpp)
    {
        return bpp == BPP_S3TC_DXT1 ||
               bpp == BPP_S3TC_DXT3 ||
               bpp == BPP_S3TC_DXT5;
    }

    static uint32 CompressedSize(uint32 bpp, uint32 width, uint32 height)
    {
        const uint32 blockBytes = (bpp == BPP_S3TC_DXT1) ? 8u : 16u;
        const uint32 bw = std::max(1u, (width + 3u) / 4u);
        const uint32 bh = std::max(1u, (height + 3u) / 4u);
        return bw * bh * blockBytes;
    }

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

    static uint32 ComputeMipOffset(const SharedTextureCompat *st, const TextureDataCompat *td)
    {
        uint32 offset = 0;

        if (td)
            offset = td->m_DtxHeader.m_Extra.m_nMipMapOffsetED;

        if (st && st->m_dwMipMapOffsetED > offset)
            offset = st->m_dwMipMapOffsetED;

        return std::min<uint32>(offset, 15u);
    }

    static uint32 ChooseMipCount(const TextureDataCompat *td)
    {
        uint32 count = std::clamp<uint32>(td->m_DtxHeader.m_wMipmaps, 1u, 8u);
        const uint8 inUse = td->m_DtxHeader.m_Extra.m_nMipMapsInUse;
        if (inUse > 0 && inUse <= count)
            count = inUse;
        return count;
    }

    static float ParseAlphaRef(const char *commandString)
    {
        if (!commandString || !*commandString)
            return 0.0f;

        const char *p = commandString;
        while (*p)
        {
            if (_strnicmp(p, "AlphaRef", 8) == 0)
            {
                p += 8;
                while (*p && (std::isspace(static_cast<unsigned char>(*p)) || *p == '=' || *p == '('))
                    ++p;

                char *end = nullptr;
                const long v = std::strtol(p, &end, 10);
                if (end != p)
                {
                    const long clamped = std::max(0L, std::min(255L, v));
                    return static_cast<float>(clamped) / 255.0f + (0.5f / 255.0f);
                }
            }
            ++p;
        }

        return 0.0f;
    }

    static inline uint8 Expand5To8(uint32 v) { return uint8((v << 3) | (v >> 2)); }
    static inline uint8 Expand6To8(uint32 v) { return uint8((v << 2) | (v >> 4)); }

    static void Decode565(uint16 c, uint8 &r, uint8 &g, uint8 &b)
    {
        r = Expand5To8((c >> 11) & 31u);
        g = Expand6To8((c >> 5) & 63u);
        b = Expand5To8(c & 31u);
    }

    static void DecodeDXTColorBlock(const uint8 *block, bool dxt1, uint8 rgba[16][4])
    {
        const uint16 c0 = uint16(block[0]) | (uint16(block[1]) << 8);
        const uint16 c1 = uint16(block[2]) | (uint16(block[3]) << 8);
        uint8 pal[4][4]{};
        Decode565(c0, pal[0][0], pal[0][1], pal[0][2]);
        pal[0][3] = 255;
        Decode565(c1, pal[1][0], pal[1][1], pal[1][2]);
        pal[1][3] = 255;
        if (!dxt1 || c0 > c1)
        {
            for (int k = 0; k < 3; ++k)
            {
                pal[2][k] = uint8((2u * pal[0][k] + pal[1][k] + 1u) / 3u);
                pal[3][k] = uint8((pal[0][k] + 2u * pal[1][k] + 1u) / 3u);
            }
            pal[2][3] = pal[3][3] = 255;
        }
        else
        {
            for (int k = 0; k < 3; ++k)
                pal[2][k] = uint8((uint32(pal[0][k]) + pal[1][k]) / 2u);
            pal[2][3] = 255;
            pal[3][0] = pal[3][1] = pal[3][2] = 0;
            pal[3][3] = 0;
        }
        const uint32 bits = uint32(block[4]) | (uint32(block[5]) << 8) | (uint32(block[6]) << 16) | (uint32(block[7]) << 24);
        for (uint32 i = 0; i < 16; ++i)
        {
            const uint32 idx = (bits >> (2u * i)) & 3u;
            std::memcpy(rgba[i], pal[idx], 4);
        }
    }

    static bool DecodeMip0RGBA8(TextureDataCompat *td, std::vector<uint8> &rgba, uint32 &w, uint32 &h)
    {
        if (!td)
            return false;
        w = td->m_Mips[0].m_dwWidth ? td->m_Mips[0].m_dwWidth : td->m_DtxHeader.m_wBaseWidth;
        h = td->m_Mips[0].m_dwHeight ? td->m_Mips[0].m_dwHeight : td->m_DtxHeader.m_wBaseHeight;
        const uint8 *src = reinterpret_cast<const uint8 *>(td->m_Mips[0].m_pData);
        if (!src || !w || !h)
            return false;
        rgba.assign(size_t(w) * h * 4u, 255);
        const uint32 bpp = td->m_DtxHeader.GetBPPIdent();
        if (bpp == BPP_32)
        {
            for (uint32 y = 0; y < h; ++y)
                for (uint32 x = 0; x < w; ++x)
                {
                    const uint8 *p = src + (size_t(y) * w + x) * 4u;
                    uint8 *d = &rgba[(size_t(y) * w + x) * 4u];
                    d[0] = p[2];
                    d[1] = p[1];
                    d[2] = p[0];
                    d[3] = p[3];
                }
            return true;
        }
        if (bpp == BPP_24)
        {
            for (uint32 y = 0; y < h; ++y)
                for (uint32 x = 0; x < w; ++x)
                {
                    const uint8 *p = src + (size_t(y) * w + x) * 3u;
                    uint8 *d = &rgba[(size_t(y) * w + x) * 4u];
                    d[0] = p[2];
                    d[1] = p[1];
                    d[2] = p[0];
                    d[3] = 255;
                }
            return true;
        }
        if (bpp != BPP_S3TC_DXT1 && bpp != BPP_S3TC_DXT3 && bpp != BPP_S3TC_DXT5)
            return false;

        const uint32 bw = std::max(1u, (w + 3u) / 4u), bh = std::max(1u, (h + 3u) / 4u);
        const uint32 blockBytes = (bpp == BPP_S3TC_DXT1) ? 8u : 16u;
        for (uint32 by = 0; by < bh; ++by)
            for (uint32 bx = 0; bx < bw; ++bx)
            {
                const uint8 *block = src + (size_t(by) * bw + bx) * blockBytes;
                uint8 colors[16][4]{};
                if (bpp == BPP_S3TC_DXT1)
                    DecodeDXTColorBlock(block, true, colors);
                else
                    DecodeDXTColorBlock(block + 8, false, colors);
                if (bpp == BPP_S3TC_DXT5)
                {
                    uint8 a[16];
                    DecodeDXT5AlphaBlock(block, a);
                    for (int i = 0; i < 16; ++i)
                        colors[i][3] = a[i];
                }
                else if (bpp == BPP_S3TC_DXT3)
                {
                    uint64_t abits = 0;
                    for (int i = 0; i < 8; ++i)
                        abits |= (uint64_t(block[i]) << (8 * i));
                    for (int i = 0; i < 16; ++i)
                        colors[i][3] = uint8(((abits >> (4 * i)) & 15u) * 17u);
                }
                for (uint32 py = 0; py < 4; ++py)
                    for (uint32 px = 0; px < 4; ++px)
                    {
                        const uint32 x = bx * 4u + px, y = by * 4u + py;
                        if (x >= w || y >= h)
                            continue;
                        std::memcpy(&rgba[(size_t(y) * w + x) * 4u], colors[py * 4u + px], 4);
                    }
            }
        return true;
    }

    static bool BuildDerivedMaterialMapImpl(Texture *out, TextureDataCompat *td)
    {
        if (!out || !td)
            return false;
        std::vector<uint8> src;
        uint32 w = 0, h = 0;
        if (!DecodeMip0RGBA8(td, src, w, h))
            return false;
        std::vector<uint8> mat(size_t(w) * h * 4u, 0);
        auto lumAt = [&](int x, int y) -> float
        {
            x = (x % int(w) + int(w)) % int(w);
            y = (y % int(h) + int(h)) % int(h);
            const uint8 *p = &src[(size_t(y) * w + uint32(x)) * 4u];
            return (0.2126f * p[0] + 0.7152f * p[1] + 0.0722f * p[2]) / 255.0f;
        };
        // Medium-radius central difference. Runtime strength/invert controls remain live;
        // only the expensive neighborhood sampling is cached here once per DTX upload.
        const int r = 2;
        for (uint32 y = 0; y < h; ++y)
            for (uint32 x = 0; x < w; ++x)
            {
                const float gx = 0.5f * (lumAt(int(x) + r, int(y)) - lumAt(int(x) - r, int(y)));
                const float gy = 0.5f * (lumAt(int(x), int(y) + r) - lumAt(int(x), int(y) - r));
                const float l = lumAt(int(x), int(y));
                uint8 *d = &mat[(size_t(y) * w + x) * 4u];
                d[0] = uint8(std::clamp(int(std::lround((gx * 0.5f + 0.5f) * 255.0f)), 0, 255));
                d[1] = uint8(std::clamp(int(std::lround((gy * 0.5f + 0.5f) * 255.0f)), 0, 255));
                d[2] = uint8(std::clamp(int(std::lround(l * 255.0f)), 0, 255));
                d[3] = 255;
            }
        if (out->materialTexture)
            GLStateDeleteTextures(1, &out->materialTexture);
        glf.CreateTextures(GL_TEXTURE_2D_, 1, &out->materialTexture);
        if (!out->materialTexture)
            return false;
        glf.TextureStorage2D(out->materialTexture, 1, GL_RGBA8_, GLsizei(w), GLsizei(h));
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glf.TextureSubImage2D(out->materialTexture, 0, 0, 0, GLsizei(w), GLsizei(h), GL_RGBA, GL_UNSIGNED_BYTE, mat.data());
        glf.TextureParameteri(out->materialTexture, GL_TEXTURE_MIN_FILTER_, GL_LINEAR_);
        glf.TextureParameteri(out->materialTexture, GL_TEXTURE_MAG_FILTER_, GL_LINEAR_);
        glf.TextureParameteri(out->materialTexture, GL_TEXTURE_WRAP_S_, GL_REPEAT);
        glf.TextureParameteri(out->materialTexture, GL_TEXTURE_WRAP_T_, GL_REPEAT);
        return true;
    }

    static bool UploadImpl(Texture *out, TextureDataCompat *td, SharedTextureCompat *st)
    {
        if (!out || !td)
            return false;

        const uint32 bpp = td->m_DtxHeader.GetBPPIdent();

        // Exact Talon d3d.ren format-selection branch at 0x1002006A..0x100200B0.
        // Internal flags: 0x0002 = Prefer16Bit gate, 0x0080 = 4444-in-16-bit,
        // 0x0001 = FULLBRITE, 0x0100 = special/fullbrite-class format.
        const uint32 iFlags = static_cast<uint32>(td->m_DtxHeader.m_nIFlags);
        const bool use32BitTextures = Console::Instance().GetFloat("32BitTextures", 1.0f) != 0.0f;
        uint8 stockFormatClass = 3; // FORMAT_NORMAL / normal 16-bit fallback
        if ((iFlags & 0x0002u) == 0u && use32BitTextures)
            stockFormatClass = 0;
        else if ((iFlags & 0x0100u) != 0u)
            stockFormatClass = 1;
        else if ((iFlags & 0x0080u) != 0u)
            stockFormatClass = 2; // FORMAT_4444
        else if ((iFlags & 0x0001u) != 0u)
            stockFormatClass = 1; // FORMAT_FULLBRITE
        else
            stockFormatClass = 3; // FORMAT_NORMAL

        GLenum internal = InternalFormatFor(bpp);
        // Stock FORMAT_4444 really stores RGBA at 4 bits/channel.  Preserve that
        // quantization in GL for uncompressed source DTXs instead of silently
        // promoting the texture to RGBA8.
        if (stockFormatClass == 2 && !IsCompressed(bpp))
            internal = 0x8056; // GL_RGBA4

        if (!internal)
        {
            LOG_SESSION("Texture3D: unsupported BPPIdent=%u", bpp);
            return false;
        }

        const uint32 mipCount = ChooseMipCount(td);
        const uint32 width = td->m_Mips[0].m_dwWidth ? td->m_Mips[0].m_dwWidth : td->m_DtxHeader.m_wBaseWidth;
        const uint32 height = td->m_Mips[0].m_dwHeight ? td->m_Mips[0].m_dwHeight : td->m_DtxHeader.m_wBaseHeight;

        if (!width || !height || !td->m_Mips[0].m_pData)
            return false;

        if (out->texture)
            GLStateDeleteTextures(1, &out->texture);
        if (out->materialTexture)
        {
            GLStateDeleteTextures(1, &out->materialTexture);
            out->materialTexture = 0;
        }

        glf.CreateTextures(GL_TEXTURE_2D_, 1, &out->texture);
        glf.TextureStorage2D(out->texture, static_cast<GLsizei>(mipCount),
                             internal, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

        for (uint32 mip = 0; mip < mipCount; ++mip)
        {
            const TextureMipDataCompat &m = td->m_Mips[mip];
            if (!m.m_pData || !m.m_dwWidth || !m.m_dwHeight)
                break;

            if (IsCompressed(bpp))
            {
                const uint32 bytes = CompressedSize(bpp, m.m_dwWidth, m.m_dwHeight);
                glf.CompressedTextureSubImage2D(
                    out->texture, static_cast<GLint>(mip),
                    0, 0,
                    static_cast<GLsizei>(m.m_dwWidth),
                    static_cast<GLsizei>(m.m_dwHeight),
                    internal,
                    static_cast<GLsizei>(bytes),
                    m.m_pData);
            }
            else if (bpp == BPP_32)
            {
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glf.TextureSubImage2D(
                    out->texture, static_cast<GLint>(mip),
                    0, 0,
                    static_cast<GLsizei>(m.m_dwWidth),
                    static_cast<GLsizei>(m.m_dwHeight),
                    GL_BGRA_, GL_UNSIGNED_BYTE, m.m_pData);
            }
            else if (bpp == BPP_24)
            {
                // FLAG2_CHROMAKEY in stock Talon is a color-key operation, not an
                // "sample whatever alpha happens to be in the DTX" operation.
                // 24-bit DTX files have no alpha plane, so uploading them as RGB8
                // made every sample alpha=1 and allowed the keyed black texels to
                // survive our fragment alpha-test.  That showed up as black
                // flicker/shimmer on only the chromakey WorldModels whose source
                // texture happened to be BPP_24.
                //
                // Preserve the authored RGB byte-for-byte and synthesize the stock
                // black color key into alpha for every authored mip.  Opaque users
                // of the same texture are unchanged because they never consume the
                // alpha channel.
                const uint32 w = m.m_dwWidth;
                const uint32 h = m.m_dwHeight;
                const uint32 tightPitch = w * 3u;
                const uint32 srcPitch = (m.m_nPitch >= static_cast<int32>(tightPitch))
                                            ? static_cast<uint32>(m.m_nPitch)
                                            : tightPitch;

                std::vector<uint8> rgba;
                rgba.resize(static_cast<size_t>(w) * static_cast<size_t>(h) * 4u);
                for (uint32 y = 0; y < h; ++y)
                {
                    const uint8 *src = m.m_pData + static_cast<size_t>(y) * srcPitch;
                    uint8 *dst = rgba.data() + static_cast<size_t>(y) * w * 4u;
                    for (uint32 x = 0; x < w; ++x)
                    {
                        const uint8 b = src[x * 3u + 0u];
                        const uint8 g = src[x * 3u + 1u];
                        const uint8 r = src[x * 3u + 2u];
                        dst[x * 4u + 0u] = r;
                        dst[x * 4u + 1u] = g;
                        dst[x * 4u + 2u] = b;
                        dst[x * 4u + 3u] = (r == 0u && g == 0u && b == 0u) ? 0u : 255u;
                    }
                }

                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glf.TextureSubImage2D(
                    out->texture, static_cast<GLint>(mip),
                    0, 0,
                    static_cast<GLsizei>(w),
                    static_cast<GLsizei>(h),
                    GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());
            }
        }

        glf.TextureParameteri(out->texture, GL_TEXTURE_WRAP_S_, GL_REPEAT);
        glf.TextureParameteri(out->texture, GL_TEXTURE_WRAP_T_, GL_REPEAT);

        // Exact d3d.ren filter policy, recovered from 0x1001A733..0x1001A80F.
        // D3D sets stage MIN/MAG from the Bilinear cvar and MIPFILTER from
        // Trilinear independently.  The old GL path forced trilinear filtering
        // (GL_LINEAR_MIPMAP_LINEAR) for every mipmapped texture, which badly
        // over-filters narrow repeated sky strips such as HorizonCloud2 (16px
        // wide with ~8-14 U repeats per visible quad).
        const bool bilinear = Console::Instance().GetFloat("Bilinear", 1.0f) != 0.0f;
        const bool trilinear = Console::Instance().GetFloat("Trilinear", 0.0f) != 0.0f;
        const GLenum magFilter = bilinear ? GL_LINEAR_ : 0x2600 /* GL_NEAREST */;
        GLenum minFilter = magFilter;
        if (mipCount > 1)
        {
            if (bilinear)
                minFilter = trilinear ? 0x2703 /* GL_LINEAR_MIPMAP_LINEAR */
                                      : 0x2701 /* GL_LINEAR_MIPMAP_NEAREST */;
            else
                minFilter = trilinear ? 0x2702 /* GL_NEAREST_MIPMAP_LINEAR */
                                      : 0x2700 /* GL_NEAREST_MIPMAP_NEAREST */;
        }
        glf.TextureParameteri(out->texture, GL_TEXTURE_MIN_FILTER_, minFilter);
        glf.TextureParameteri(out->texture, GL_TEXTURE_MAG_FILTER_, magFilter);
        out->stockBilinear = bilinear ? 1u : 0u;
        out->stockTrilinear = trilinear ? 1u : 0u;
        out->glMinFilter = static_cast<uint32>(minFilter);
        out->glMagFilter = static_cast<uint32>(magFilter);

        const uint32 mipOffset = ComputeMipOffset(st, td);
        out->width = width;
        out->height = height;
        out->scaledWidth = std::max(1u, width >> mipOffset);
        out->scaledHeight = std::max(1u, height >> mipOffset);
        out->mipOffset = mipOffset;
        out->bppIdent = bpp;
        out->mipLevels = mipCount;
        out->dtxIFlags = iFlags;
        out->dtxUserFlags = static_cast<uint32>(td->m_DtxHeader.m_nUserFlags);
        out->stockFormatClass = stockFormatClass;
        out->alphaRef = ParseAlphaRef(td->m_DtxHeader.m_szCommandString);
        out->fullBright = (td->m_DtxHeader.m_nIFlags & 1) != 0; // DTX_FULLBRITE
        out->syntheticChromaAlpha = (bpp == BPP_24);

        // AVP2/Talon d3d.ren 0x1002020c..0x10020246.  Do not substitute
        // Jupiter RenderStyle semantics here: the stock renderer stores the base
        // DTX detail metadata directly on its RTexture at creation time.
        out->detailScale = 1.0f + td->m_DtxHeader.m_Extra.m_fDetTexScale;
        out->detailAngle = td->m_DtxHeader.m_Extra.m_nDetTexAngle;
        const float detailRadians = static_cast<float>(out->detailAngle) *
                                    0.01745329238474369f; // exact pi/180 constant used by d3d.ren
        out->detailCos = std::cos(detailRadians);
        out->detailSin = std::sin(detailRadians);

        return true;
    }

}

bool Texture::Upload(TextureDataCompat *data, SharedTextureCompat *shared)
{
    return UploadImpl(this, data, shared);
}

bool Texture::BuildDerivedMaterial(TextureDataCompat *data)
{
    return BuildDerivedMaterialMapImpl(this, data);
}

void Texture::ApplyAnisotropy(float level)
{
    const GLfloat anisotropy = std::clamp(level, 1.0f, 16.0f);
    if (texture)
        glf.TextureParameterf(texture, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
    if (materialTexture)
        glf.TextureParameterf(materialTexture, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
}

void Texture::Destroy()
{
    if (texture)
    {
        GLStateDeleteTextures(1, &texture);
        texture = 0;
    }
    if (materialTexture)
    {
        GLStateDeleteTextures(1, &materialTexture);
        materialTexture = 0;
    }
}
