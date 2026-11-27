#include "renderer_2d.h"
#include "renderer_core.h"
#include "renderer_presenter.h"
#include "renderer_settings.h"
#include "../../gl_loader.h"
#include "utils/log.h"
#include "../../shaders/shader_manager.h"
#include "../../shaders/shader_resources.h"
#include <algorithm>
#include <cstring>

static RendererPresenterState &PresenterState() { return RendererPresenter::Instance().State(); }

Renderer2D &Renderer2D::Instance()
{
    static Renderer2D v;
    return v;
}

bool Renderer2D::Init()
{
    auto &shaderManager = avp2::render::ShaderManager::Instance();
    auto *shader = shaderManager.CreateGraphicsFromResources("renderer.2d", avp2::render::ShaderResourceId::RendererQuadVertex, avp2::render::ShaderResourceId::RendererQuadFragment);
    if (!shader)
        return false;
    m_state.blitShader = shader;
    m_state.uTex = shader->Uniform("uTex");
    m_state.uColor = shader->Uniform("uColor");
    m_state.uAlpha = shader->Uniform("uAlpha");
    m_state.uUseKey = shader->Uniform("uUseKey");
    m_state.uKey = shader->Uniform("uKey");
    m_state.uUseTexAlpha = shader->Uniform("uUseTexAlpha");
    return true;
}

void Renderer2D::Term()
{
    avp2::render::ShaderManager::Instance().Release("renderer.2d");
    m_state.blitShader = nullptr;
    m_state.uTex = m_state.uColor = m_state.uAlpha = m_state.uUseKey = m_state.uKey = m_state.uUseTexAlpha = -1;
    m_state.optimized = false;
    m_state.blend = LTSURFACEBLEND_ALPHA;
    m_state.color = 0xFFFFFFFFu;
    m_state.optimizedUploadScratch.clear();
}

bool Renderer2D::StartOptimized()
{
    // Stock d3d_StartOptimized2D only succeeds while inside Start3D, then
    // disables Z test/write and enables conventional alpha blending.
    if (!RendererCore::Instance().IsIn3D())
        return false;
    if (m_state.optimized)
        return true;

    Flush();
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);
    GLStateEnable(GL_BLEND);
    avp2::render::GLStateCache::Instance().SetBlendEquation(GL_FUNC_ADD_);
    GLStateBlendFunc(GL_SRC_ALPHA_, GL_ONE_MINUS_SRC_ALPHA_);
    m_state.optimized = true;
    return true;
}

void Renderer2D::EndOptimized()
{
    if (!RendererCore::Instance().IsIn3D() || !m_state.optimized)
        return;

    Flush();
    GLStateEnable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_TRUE);
    GLStateDisable(GL_BLEND);
    m_state.optimized = false;
}

bool Renderer2D::IsOptimized() const { return m_state.optimized; }

bool Renderer2D::SetBlend(LTSurfaceBlend blend)
{
    if (blend != m_state.blend)
        Flush();
    m_state.blend = blend;
    return true;
}

bool Renderer2D::GetBlend(LTSurfaceBlend &blend) const
{
    blend = m_state.blend;
    return true;
}

bool Renderer2D::SetColor(HLTCOLOR color)
{
    const HLTCOLOR next = color | 0xFF000000u;
    if (next != m_state.color)
        Flush();

    m_state.color = next;
    return true;
}

bool Renderer2D::GetColor(HLTCOLOR &color) const
{
    color = m_state.color;
    return true;
}

GLSurface *Renderer2D::CreateSurface(int width, int height)
{
    if (width <= 0 || height <= 0)
        return nullptr;

    auto *s = new GLSurface();
    s->width = width;
    s->height = height;
    s->pitch = width * 4;
    s->pixels.resize(static_cast<size_t>(s->pitch) * height);
    s->dirty = true;
    LOG_SESSION("CreateSurface %p %dx%d pitch=%d", s, width, height, s->pitch);
    return s;
}

void Renderer2D::DeleteSurface(GLSurface *s)
{
    if (!s)
        return;
    LOG_SESSION("DeleteSurface %p", s);
    if (s->texture)
        GLStateDeleteTextures(1, &s->texture);
    delete s;
}

void Renderer2D::EnsureTexture(GLSurface *s)
{
    if (!s)
        return;

    if (!s->textureAllocated)
    {
        glf.CreateTextures(GL_TEXTURE_2D_, 1, &s->texture);
        glf.TextureStorage2D(s->texture, 1, GL_RGBA8_, s->width, s->height);
        glf.TextureParameteri(s->texture, GL_TEXTURE_MIN_FILTER_, GL_LINEAR_);
        glf.TextureParameteri(s->texture, GL_TEXTURE_MAG_FILTER_, GL_LINEAR_);
        glf.TextureParameteri(s->texture, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
        glf.TextureParameteri(s->texture, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);
        s->textureAllocated = true;
        s->dirty = true;
    }

    if (s->dirty)
    {
        const void *uploadPixels = s->pixels.data();
        auto &s_optimizedUploadScratch = m_state.optimizedUploadScratch;

        if (s->optimized)
        {
            // Stock d3d_FillSurfaceTiles does not preserve the source alpha.
            // It explicitly writes opaque alpha for every non-keyed pixel and
            // zero alpha for pixels equal to the optimized transparent color.
            // This happens BEFORE bilinear filtering, which is materially
            // different from doing an exact RGB discard in the fragment shader.
            const size_t bytes = static_cast<size_t>(s->pitch) * s->height;
            s_optimizedUploadScratch.resize(bytes);
            std::memcpy(s_optimizedUploadScratch.data(), s->pixels.data(), bytes);

            const bool keyed = (s->transparentColor != 0xFFFFFFFFu);
            const uint32_t keyRGB = s->transparentColor & 0x00FFFFFFu;
            for (int y = 0; y < s->height; ++y)
            {
                uint8_t *row = s_optimizedUploadScratch.data() + static_cast<size_t>(y) * s->pitch;
                for (int x = 0; x < s->width; ++x)
                {
                    uint8_t *px = row + static_cast<size_t>(x) * 4;
                    const uint32_t rgb = (static_cast<uint32_t>(px[2]) << 16) |
                                         (static_cast<uint32_t>(px[1]) << 8) |
                                         static_cast<uint32_t>(px[0]);
                    px[3] = (keyed && rgb == keyRGB) ? 0u : 255u;
                }
            }
            uploadPixels = s_optimizedUploadScratch.data();
        }

        glf.TextureSubImage2D(s->texture, 0, 0, 0, s->width, s->height,
                              GL_BGRA_, GL_UNSIGNED_BYTE, uploadPixels);
        s->dirty = false;
        ++PresenterState().frameTextureUploads;
    }
}

void Renderer2D::Flush()
{
    RendererPresenter::Instance().FlushBatch();
}
