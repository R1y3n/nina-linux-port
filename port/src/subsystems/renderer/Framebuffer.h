#pragma once

#include "../../gl_renderer.h"
#include <GL/gl.h>

#ifndef GL_RGBA8
#define GL_RGBA8 0x8058
#endif

// OpenGL 4.6 core framebuffer owner.  Allocation is DSA-only: there are no
// EXT/ARB framebuffer fallbacks and no bind-to-edit construction paths.
class Framebuffer final
{
public:
    static Framebuffer &Instance();

    bool Init(int width, int height);
    void Term();

    bool Ready() const { return m_ready; }
    GLuint Logical() const { return m_logicalFbo; }
    GLuint ColorTexture() const { return m_logicalColorTexture; }
    GLuint ReflectionMaskTexture() const { return m_logicalReflectionMaskTexture; }
    GLuint DepthStencil() const { return m_logicalDepthStencil; }
    void ClearReflectionMask(GLuint fbo) const;
    int Width() const { return m_width; }
    int Height() const { return m_height; }

    // Binding is still required to select a draw/read framebuffer; creation and
    // mutation never rely on binding.
    void Bind(GLenum target, GLuint fbo) const;
    void BindLogical() const;
    void Blit(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
              GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
              GLbitfield mask, GLenum filter) const;

    bool CreateColorTarget(GLuint &texture, GLuint &fbo,
                           int width, int height,
                           GLenum internalFormat = GL_RGBA8,
                           GLenum format = GL_RGBA,
                           GLenum type = GL_UNSIGNED_BYTE,
                           GLenum filter = GL_LINEAR) const;
    void DestroyColorTarget(GLuint &texture, GLuint &fbo) const;

    bool CreateDepthTarget(GLuint &texture, GLuint &fbo,
                           int width, int height,
                           GLenum internalFormat = 0x81A6,
                           GLenum type = GL_UNSIGNED_INT) const;
    void DestroyDepthTarget(GLuint &texture, GLuint &fbo) const;

    bool CreateMultisampleTarget(GLuint &fbo, GLuint &colorRenderbuffer,
                                 GLuint &reflectionMaskRenderbuffer,
                                 GLuint &depthStencilRenderbuffer,
                                 int width, int height, int samples) const;
    void DestroyMultisampleTarget(GLuint &fbo, GLuint &colorRenderbuffer,
                                  GLuint &reflectionMaskRenderbuffer,
                                  GLuint &depthStencilRenderbuffer) const;

    void CopyColor(GLuint srcFbo, GLuint dstFbo,
                   int width, int height, GLenum filter = GL_NEAREST) const;
    void CopyDepth(GLuint srcFbo, GLuint dstFbo,
                   int width, int height) const;

private:
    Framebuffer() = default;
    Framebuffer(const Framebuffer &) = delete;
    Framebuffer &operator=(const Framebuffer &) = delete;

    bool CreateLogical();
    void DestroyLogical();

    int m_width = 0;
    int m_height = 0;
    GLuint m_logicalFbo = 0;
    GLuint m_logicalColorTexture = 0;
    GLuint m_logicalReflectionMaskTexture = 0;
    GLuint m_logicalDepthStencil = 0;
    bool m_ready = false;
};
