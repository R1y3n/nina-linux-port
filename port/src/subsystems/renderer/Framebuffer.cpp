#include "Framebuffer.h"
#include "../../gl_loader.h"
#include "utils/log.h"

#include <GL/gl.h>
#include <algorithm>

#ifndef GL_READ_FRAMEBUFFER
#define GL_READ_FRAMEBUFFER 0x8CA8
#endif
#ifndef GL_DRAW_FRAMEBUFFER
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#endif
#ifndef GL_FRAMEBUFFER
#define GL_FRAMEBUFFER 0x8D40
#endif
#ifndef GL_RENDERBUFFER
#define GL_RENDERBUFFER 0x8D41
#endif
#ifndef GL_COLOR_ATTACHMENT0
#define GL_COLOR_ATTACHMENT0 0x8CE0
#endif
#ifndef GL_COLOR
#define GL_COLOR 0x1800
#endif
#ifndef GL_DEPTH_ATTACHMENT
#define GL_DEPTH_ATTACHMENT 0x8D00
#endif
#ifndef GL_DEPTH_STENCIL_ATTACHMENT
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#endif
#ifndef GL_FRAMEBUFFER_COMPLETE
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#endif
#ifndef GL_DEPTH24_STENCIL8
#define GL_DEPTH24_STENCIL8 0x88F0
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
#ifndef GL_DEPTH_COMPONENT24
#define GL_DEPTH_COMPONENT24 0x81A6
#endif
#ifndef GL_DEPTH_COMPONENT
#define GL_DEPTH_COMPONENT 0x1902
#endif

Framebuffer &Framebuffer::Instance()
{
    static Framebuffer instance;
    return instance;
}

bool Framebuffer::Init(int width, int height)
{
    DestroyLogical();
    m_width = std::max(1, width);
    m_height = std::max(1, height);

    // LoadModernGL() is mandatory before this subsystem is initialized.  The
    // entire framebuffer implementation assumes OpenGL 4.5+ DSA entry points.
    if (!glf.CreateFramebuffers || !glf.DeleteFramebuffers || !glf.BindFramebuffer ||
        !glf.NamedFramebufferTexture || !glf.NamedFramebufferRenderbuffer ||
        !glf.NamedFramebufferDrawBuffer || !glf.NamedFramebufferDrawBuffers ||
        !glf.NamedFramebufferReadBuffer || !glf.DrawBuffers || !glf.ClearNamedFramebufferfv ||
        !glf.CheckNamedFramebufferStatus || !glf.BlitFramebuffer ||
        !glf.CreateRenderbuffers || !glf.DeleteRenderbuffers ||
        !glf.NamedRenderbufferStorage || !glf.NamedRenderbufferStorageMultisample ||
        !glf.CreateTextures || !glf.DeleteTextures || !glf.TextureStorage2D ||
        !glf.TextureParameteri)
    {
        LOG_SESSION("Framebuffer: OpenGL 4.5 DSA API is incomplete");
        m_width = m_height = 0;
        return false;
    }

    if (!CreateLogical())
    {
        m_width = m_height = 0;
        return false;
    }
    return true;
}

bool Framebuffer::CreateLogical()
{
    DestroyLogical();

    glf.CreateTextures(GL_TEXTURE_2D, 1, &m_logicalColorTexture);
    if (!m_logicalColorTexture)
        return false;
    glf.TextureStorage2D(m_logicalColorTexture, 1, GL_RGBA8, m_width, m_height);
    glf.TextureParameteri(m_logicalColorTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glf.TextureParameteri(m_logicalColorTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glf.TextureParameteri(m_logicalColorTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glf.TextureParameteri(m_logicalColorTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glf.CreateTextures(GL_TEXTURE_2D, 1, &m_logicalReflectionMaskTexture);
    if (!m_logicalReflectionMaskTexture)
    {
        DestroyLogical();
        return false;
    }
    glf.TextureStorage2D(m_logicalReflectionMaskTexture, 1, 0x822B /* GL_RG8 */, m_width, m_height);
    glf.TextureParameteri(m_logicalReflectionMaskTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glf.TextureParameteri(m_logicalReflectionMaskTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glf.TextureParameteri(m_logicalReflectionMaskTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glf.TextureParameteri(m_logicalReflectionMaskTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glf.CreateRenderbuffers(1, &m_logicalDepthStencil);
    if (!m_logicalDepthStencil)
    {
        DestroyLogical();
        return false;
    }
    glf.NamedRenderbufferStorage(m_logicalDepthStencil, GL_DEPTH24_STENCIL8, m_width, m_height);

    glf.CreateFramebuffers(1, &m_logicalFbo);
    if (!m_logicalFbo)
    {
        DestroyLogical();
        return false;
    }
    glf.NamedFramebufferTexture(m_logicalFbo, GL_COLOR_ATTACHMENT0, m_logicalColorTexture, 0);
    glf.NamedFramebufferTexture(m_logicalFbo, GL_COLOR_ATTACHMENT0 + 1, m_logicalReflectionMaskTexture, 0);
    glf.NamedFramebufferRenderbuffer(m_logicalFbo, GL_DEPTH_STENCIL_ATTACHMENT,
                                     GL_RENDERBUFFER, m_logicalDepthStencil);
    const GLenum logicalDrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT0 + 1};
    glf.NamedFramebufferDrawBuffers(m_logicalFbo, 2, logicalDrawBuffers);
    glf.NamedFramebufferReadBuffer(m_logicalFbo, GL_COLOR_ATTACHMENT0);

    const GLenum status = glf.CheckNamedFramebufferStatus(m_logicalFbo, GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_SESSION("Framebuffer logical target incomplete status=%08X", static_cast<unsigned>(status));
        DestroyLogical();
        return false;
    }

    BindLogical();
    m_ready = true;
    ClearReflectionMask(m_logicalFbo);
    LOG_SESSION("Framebuffer OpenGL 4.6 DSA target ready fbo=%u color=%u ssrMask=%u depthStencil=%u size=%dx%d",
                m_logicalFbo, m_logicalColorTexture, m_logicalReflectionMaskTexture, m_logicalDepthStencil, m_width, m_height);
    return true;
}

void Framebuffer::DestroyLogical()
{
    m_ready = false;
    if (m_logicalDepthStencil && glf.DeleteRenderbuffers)
        glf.DeleteRenderbuffers(1, &m_logicalDepthStencil);
    if (m_logicalFbo && glf.DeleteFramebuffers)
        glf.DeleteFramebuffers(1, &m_logicalFbo);
    if (m_logicalReflectionMaskTexture && glf.DeleteTextures)
        GLStateDeleteTextures(1, &m_logicalReflectionMaskTexture);
    if (m_logicalColorTexture && glf.DeleteTextures)
        GLStateDeleteTextures(1, &m_logicalColorTexture);
    m_logicalDepthStencil = 0;
    m_logicalFbo = 0;
    m_logicalColorTexture = 0;
    m_logicalReflectionMaskTexture = 0;
}

void Framebuffer::Term()
{
    DestroyLogical();
    m_width = 0;
    m_height = 0;
}

bool Framebuffer::CreateColorTarget(GLuint &texture, GLuint &fbo,
                                    int width, int height,
                                    GLenum internalFormat, GLenum,
                                    GLenum, GLenum filter) const
{
    DestroyColorTarget(texture, fbo);
    if (width <= 0 || height <= 0)
        return false;

    glf.CreateTextures(GL_TEXTURE_2D, 1, &texture);
    if (!texture)
        return false;
    glf.TextureStorage2D(texture, 1, internalFormat, width, height);
    glf.TextureParameteri(texture, GL_TEXTURE_MIN_FILTER, filter);
    glf.TextureParameteri(texture, GL_TEXTURE_MAG_FILTER, filter);
    glf.TextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glf.TextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glf.CreateFramebuffers(1, &fbo);
    if (!fbo)
    {
        GLStateDeleteTextures(1, &texture);
        texture = 0;
        return false;
    }
    glf.NamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, texture, 0);
    glf.NamedFramebufferDrawBuffer(fbo, GL_COLOR_ATTACHMENT0);
    glf.NamedFramebufferReadBuffer(fbo, GL_COLOR_ATTACHMENT0);

    const GLenum status = glf.CheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_SESSION("Framebuffer color target incomplete status=%08X size=%dx%d internal=%08X",
                    static_cast<unsigned>(status), width, height, static_cast<unsigned>(internalFormat));
        DestroyColorTarget(texture, fbo);
        return false;
    }
    return true;
}

void Framebuffer::DestroyColorTarget(GLuint &texture, GLuint &fbo) const
{
    if (fbo && glf.DeleteFramebuffers)
        glf.DeleteFramebuffers(1, &fbo);
    if (texture && glf.DeleteTextures)
        GLStateDeleteTextures(1, &texture);
    fbo = 0;
    texture = 0;
}

bool Framebuffer::CreateDepthTarget(GLuint &texture, GLuint &fbo,
                                    int width, int height,
                                    GLenum internalFormat, GLenum) const
{
    DestroyDepthTarget(texture, fbo);
    if (width <= 0 || height <= 0)
        return false;

    glf.CreateTextures(GL_TEXTURE_2D, 1, &texture);
    if (!texture)
        return false;
    glf.TextureStorage2D(texture, 1, internalFormat, width, height);
    glf.TextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glf.TextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glf.TextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glf.TextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glf.CreateFramebuffers(1, &fbo);
    if (!fbo)
    {
        GLStateDeleteTextures(1, &texture);
        texture = 0;
        return false;
    }
    glf.NamedFramebufferTexture(fbo, GL_DEPTH_ATTACHMENT, texture, 0);
    glf.NamedFramebufferDrawBuffer(fbo, GL_NONE);
    glf.NamedFramebufferReadBuffer(fbo, GL_NONE);

    const GLenum status = glf.CheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_SESSION("Framebuffer depth target incomplete status=%08X size=%dx%d",
                    static_cast<unsigned>(status), width, height);
        DestroyDepthTarget(texture, fbo);
        return false;
    }
    return true;
}

void Framebuffer::DestroyDepthTarget(GLuint &texture, GLuint &fbo) const
{
    DestroyColorTarget(texture, fbo);
}

bool Framebuffer::CreateMultisampleTarget(GLuint &fbo, GLuint &colorRenderbuffer,
                                          GLuint &reflectionMaskRenderbuffer,
                                          GLuint &depthStencilRenderbuffer,
                                          int width, int height, int samples) const
{
    DestroyMultisampleTarget(fbo, colorRenderbuffer, reflectionMaskRenderbuffer, depthStencilRenderbuffer);
    if (width <= 0 || height <= 0 || samples <= 0)
        return false;

    glf.CreateRenderbuffers(1, &colorRenderbuffer);
    glf.NamedRenderbufferStorageMultisample(colorRenderbuffer, samples, GL_RGBA8, width, height);

    glf.CreateRenderbuffers(1, &reflectionMaskRenderbuffer);
    glf.NamedRenderbufferStorageMultisample(reflectionMaskRenderbuffer, samples, 0x822B /* GL_RG8 */, width, height);

    glf.CreateRenderbuffers(1, &depthStencilRenderbuffer);
    glf.NamedRenderbufferStorageMultisample(depthStencilRenderbuffer, samples, GL_DEPTH24_STENCIL8, width, height);

    glf.CreateFramebuffers(1, &fbo);
    glf.NamedFramebufferRenderbuffer(fbo, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
    glf.NamedFramebufferRenderbuffer(fbo, GL_COLOR_ATTACHMENT0 + 1, GL_RENDERBUFFER, reflectionMaskRenderbuffer);
    glf.NamedFramebufferRenderbuffer(fbo, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRenderbuffer);
    const GLenum drawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT0 + 1};
    glf.NamedFramebufferDrawBuffers(fbo, 2, drawBuffers);
    glf.NamedFramebufferReadBuffer(fbo, GL_COLOR_ATTACHMENT0);

    const GLenum status = glf.CheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_SESSION("Framebuffer %dx MSAA target incomplete status=%08X size=%dx%d",
                    samples, static_cast<unsigned>(status), width, height);
        DestroyMultisampleTarget(fbo, colorRenderbuffer, reflectionMaskRenderbuffer, depthStencilRenderbuffer);
        return false;
    }
    ClearReflectionMask(fbo);
    return true;
}

void Framebuffer::DestroyMultisampleTarget(GLuint &fbo, GLuint &colorRenderbuffer,
                                           GLuint &reflectionMaskRenderbuffer,
                                           GLuint &depthStencilRenderbuffer) const
{
    if (depthStencilRenderbuffer && glf.DeleteRenderbuffers)
        glf.DeleteRenderbuffers(1, &depthStencilRenderbuffer);
    if (reflectionMaskRenderbuffer && glf.DeleteRenderbuffers)
        glf.DeleteRenderbuffers(1, &reflectionMaskRenderbuffer);
    if (colorRenderbuffer && glf.DeleteRenderbuffers)
        glf.DeleteRenderbuffers(1, &colorRenderbuffer);
    if (fbo && glf.DeleteFramebuffers)
        glf.DeleteFramebuffers(1, &fbo);
    depthStencilRenderbuffer = 0;
    reflectionMaskRenderbuffer = 0;
    colorRenderbuffer = 0;
    fbo = 0;
}

void Framebuffer::ClearReflectionMask(GLuint fbo) const
{
    if (!fbo || !glf.ClearNamedFramebufferfv)
        return;
    const GLfloat zero[4] = {0, 0, 0, 0};
    glf.ClearNamedFramebufferfv(fbo, GL_COLOR, 1, zero);
}

void Framebuffer::CopyColor(GLuint srcFbo, GLuint dstFbo,
                            int width, int height, GLenum filter) const
{
    if (width <= 0 || height <= 0)
        return;
    glf.BlitNamedFramebuffer(srcFbo, dstFbo,
                             0, 0, width, height, 0, 0, width, height,
                             GL_COLOR_BUFFER_BIT, filter);
}

void Framebuffer::CopyDepth(GLuint srcFbo, GLuint dstFbo,
                            int width, int height) const
{
    if (width <= 0 || height <= 0)
        return;
    glf.BlitNamedFramebuffer(srcFbo, dstFbo,
                             0, 0, width, height, 0, 0, width, height,
                             GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void Framebuffer::Bind(GLenum target, GLuint fbo) const
{
    glf.BindFramebuffer(target, fbo);
}

void Framebuffer::BindLogical() const
{
    if (!m_logicalFbo)
        return;
    glf.BindFramebuffer(GL_FRAMEBUFFER, m_logicalFbo);
    const GLenum drawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT0 + 1};
    glf.DrawBuffers(2, drawBuffers);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
}

void Framebuffer::Blit(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
                       GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
                       GLbitfield mask, GLenum filter) const
{
    glf.BlitFramebuffer(srcX0, srcY0, srcX1, srcY1,
                        dstX0, dstY0, dstX1, dstY1, mask, filter);
}
