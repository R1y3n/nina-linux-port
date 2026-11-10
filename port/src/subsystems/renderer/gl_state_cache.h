#pragma once
#include "../../gl_loader.h"
#include <array>
#include <cstdint>

namespace avp2::render
{
    struct GLStateSnapshot
    {
        bool depthTest = false, blend = false, cull = false, scissor = false;
        bool depthWrite = true;
        GLenum depthFunc = GL_LESS;
        GLenum blendSrc = GL_ONE, blendDst = GL_ZERO;
        GLenum blendEquation = GL_FUNC_ADD_;
        GLenum cullFace = GL_BACK, frontFace = GL_CCW;
        double depthNear = 0.0, depthFar = 1.0;
    };

    struct GLStateStats
    {
        uint64_t requests = 0, changes = 0, skipped = 0;
        uint64_t programBinds = 0, vaoBinds = 0, textureBinds = 0;
    };

    class GLStateCache final
    {
    public:
        static GLStateCache &Instance();
        void Invalidate();
        void ResetStats();
        const GLStateStats &Stats() const { return m_stats; }
        GLuint CurrentProgram() const { return (m_validMask & (1u << 11)) ? m_program : 0; }

        void SetEnabled(GLenum cap, bool enabled);
        void SetDepthWrite(bool enabled);
        void SetDepthFunc(GLenum func);
        void SetDepthRange(double n, double f);
        void SetBlendFunc(GLenum src, GLenum dst);
        void SetBlendEquation(GLenum eq);
        void SetCullFace(GLenum face);
        void SetFrontFace(GLenum face);
        void UseProgram(GLuint program);
        void BindVertexArray(GLuint vao);
        void BindTextureUnit(GLuint unit, GLuint texture);

        GLStateSnapshot Capture() const;
        void Restore(const GLStateSnapshot &s);

    private:
        GLStateCache() = default;
        void Hit(bool changed);
        uint32_t m_validMask = 0;
        GLStateSnapshot m_state{};
        GLuint m_program = 0, m_vao = 0;
        std::array<GLuint, 32> m_textures{};
        std::array<bool, 32> m_textureValid{};
        GLStateStats m_stats{};
    };
}

inline void GLStateEnable(GLenum cap) { avp2::render::GLStateCache::Instance().SetEnabled(cap, true); }
inline void GLStateDisable(GLenum cap) { avp2::render::GLStateCache::Instance().SetEnabled(cap, false); }
inline void GLStateDepthMask(GLboolean v) { avp2::render::GLStateCache::Instance().SetDepthWrite(v != GL_FALSE); }
inline void GLStateDepthFunc(GLenum v) { avp2::render::GLStateCache::Instance().SetDepthFunc(v); }
inline void GLStateDepthRange(GLdouble n, GLdouble f) { avp2::render::GLStateCache::Instance().SetDepthRange(n, f); }
inline void GLStateBlendFunc(GLenum s, GLenum d) { avp2::render::GLStateCache::Instance().SetBlendFunc(s, d); }
inline void GLStateFrontFace(GLenum v) { avp2::render::GLStateCache::Instance().SetFrontFace(v); }
inline void GLStateCullFace(GLenum v) { avp2::render::GLStateCache::Instance().SetCullFace(v); }
inline void GLStateBindTextureUnit(GLuint u, GLuint t) { avp2::render::GLStateCache::Instance().BindTextureUnit(u, t); }
inline void GLStateBindVertexArray(GLuint v) { avp2::render::GLStateCache::Instance().BindVertexArray(v); }
inline void GLStateDeleteTextures(GLsizei n, const GLuint *p)
{
    if (glf.DeleteTextures)
        glf.DeleteTextures(n, p);
    avp2::render::GLStateCache::Instance().Invalidate();
}
inline void GLStateDeleteVertexArrays(GLsizei n, const GLuint *p)
{
    if (glf.DeleteVertexArrays)
        glf.DeleteVertexArrays(n, p);
    avp2::render::GLStateCache::Instance().Invalidate();
}
inline void GLStateDeleteProgram(GLuint p)
{
    GLUniformStats::Instance().InvalidateProgram(p);
    if (glf.DeleteProgram)
        glf.DeleteProgram(p);
    avp2::render::GLStateCache::Instance().Invalidate();
}
