#include "gl_state_cache.h"

namespace avp2::render
{
    namespace
    {
        enum : uint32_t
        {
            V_DEPTH = 1u << 0,
            V_BLEND = 1u << 1,
            V_CULL = 1u << 2,
            V_SCISSOR = 1u << 3,
            V_DWRITE = 1u << 4,
            V_DFUNC = 1u << 5,
            V_DRANGE = 1u << 6,
            V_BFUNC = 1u << 7,
            V_BEQ = 1u << 8,
            V_CFACE = 1u << 9,
            V_FFACE = 1u << 10,
            V_PROGRAM = 1u << 11,
            V_VAO = 1u << 12
        };
    }
    GLStateCache &GLStateCache::Instance()
    {
        static GLStateCache s;
        return s;
    }
    void GLStateCache::Invalidate()
    {
        m_validMask = 0;
        m_textureValid.fill(false);
    }
    void GLStateCache::ResetStats() { m_stats = {}; }
    void GLStateCache::Hit(bool changed)
    {
        ++m_stats.requests;
        if (changed)
            ++m_stats.changes;
        else
            ++m_stats.skipped;
    }

    void GLStateCache::SetEnabled(GLenum cap, bool enabled)
    {
        bool *p = nullptr;
        uint32_t bit = 0;
        switch (cap)
        {
        case GL_DEPTH_TEST:
            p = &m_state.depthTest;
            bit = V_DEPTH;
            break;
        case GL_BLEND:
            p = &m_state.blend;
            bit = V_BLEND;
            break;
        case GL_CULL_FACE:
            p = &m_state.cull;
            bit = V_CULL;
            break;
        case GL_SCISSOR_TEST:
            p = &m_state.scissor;
            bit = V_SCISSOR;
            break;
        default:
            if (enabled)
                glEnable(cap);
            else
                glDisable(cap);
            ++m_stats.requests;
            ++m_stats.changes;
            return;
        }
        const bool change = !(m_validMask & bit) || *p != enabled;
        Hit(change);
        if (!change)
            return;
        if (enabled)
            glEnable(cap);
        else
            glDisable(cap);
        *p = enabled;
        m_validMask |= bit;
    }
    void GLStateCache::SetDepthWrite(bool v)
    {
        const bool c = !(m_validMask & V_DWRITE) || m_state.depthWrite != v;
        Hit(c);
        if (!c)
            return;
        glDepthMask(v ? GL_TRUE : GL_FALSE);
        m_state.depthWrite = v;
        m_validMask |= V_DWRITE;
    }
    void GLStateCache::SetDepthFunc(GLenum v)
    {
        const bool c = !(m_validMask & V_DFUNC) || m_state.depthFunc != v;
        Hit(c);
        if (!c)
            return;
        glDepthFunc(v);
        m_state.depthFunc = v;
        m_validMask |= V_DFUNC;
    }
    void GLStateCache::SetDepthRange(double n, double f)
    {
        const bool c = !(m_validMask & V_DRANGE) || m_state.depthNear != n || m_state.depthFar != f;
        Hit(c);
        if (!c)
            return;
        glDepthRange(n, f);
        m_state.depthNear = n;
        m_state.depthFar = f;
        m_validMask |= V_DRANGE;
    }
    void GLStateCache::SetBlendFunc(GLenum s, GLenum d)
    {
        const bool c = !(m_validMask & V_BFUNC) || m_state.blendSrc != s || m_state.blendDst != d;
        Hit(c);
        if (!c)
            return;
        glBlendFunc(s, d);
        m_state.blendSrc = s;
        m_state.blendDst = d;
        m_validMask |= V_BFUNC;
    }
    void GLStateCache::SetBlendEquation(GLenum e)
    {
        const bool c = !(m_validMask & V_BEQ) || m_state.blendEquation != e;
        Hit(c);
        if (!c)
            return;
        glf.BlendEquation(e);
        m_state.blendEquation = e;
        m_validMask |= V_BEQ;
    }
    void GLStateCache::SetCullFace(GLenum v)
    {
        const bool c = !(m_validMask & V_CFACE) || m_state.cullFace != v;
        Hit(c);
        if (!c)
            return;
        glCullFace(v);
        m_state.cullFace = v;
        m_validMask |= V_CFACE;
    }
    void GLStateCache::SetFrontFace(GLenum v)
    {
        const bool c = !(m_validMask & V_FFACE) || m_state.frontFace != v;
        Hit(c);
        if (!c)
            return;
        glFrontFace(v);
        m_state.frontFace = v;
        m_validMask |= V_FFACE;
    }
    void GLStateCache::UseProgram(GLuint p)
    {
        const bool c = !(m_validMask & V_PROGRAM) || m_program != p;
        Hit(c);
        if (!c)
            return;
        glf.UseProgram(p);
        m_program = p;
        m_validMask |= V_PROGRAM;
        ++m_stats.programBinds;
    }
    void GLStateCache::BindVertexArray(GLuint v)
    {
        const bool c = !(m_validMask & V_VAO) || m_vao != v;
        Hit(c);
        if (!c)
            return;
        glf.BindVertexArray(v);
        m_vao = v;
        m_validMask |= V_VAO;
        ++m_stats.vaoBinds;
    }
    void GLStateCache::BindTextureUnit(GLuint u, GLuint t)
    {
        if (u >= m_textures.size())
        {
            glf.BindTextureUnit(u, t);
            ++m_stats.requests;
            ++m_stats.changes;
            ++m_stats.textureBinds;
            return;
        }
        const bool c = !m_textureValid[u] || m_textures[u] != t;
        Hit(c);
        if (!c)
            return;
        glf.BindTextureUnit(u, t);
        m_textures[u] = t;
        m_textureValid[u] = true;
        ++m_stats.textureBinds;
    }
    GLStateSnapshot GLStateCache::Capture() const { return m_state; }
    void GLStateCache::Restore(const GLStateSnapshot &s)
    {
        SetDepthRange(s.depthNear, s.depthFar);
        SetDepthWrite(s.depthWrite);
        SetDepthFunc(s.depthFunc);
        SetBlendFunc(s.blendSrc, s.blendDst);
        SetBlendEquation(s.blendEquation);
        SetEnabled(GL_DEPTH_TEST, s.depthTest);
        SetEnabled(GL_BLEND, s.blend);
        SetEnabled(GL_CULL_FACE, s.cull);
        SetEnabled(GL_SCISSOR_TEST, s.scissor);
        SetCullFace(s.cullFace);
        SetFrontFace(s.frontFace);
    }
}
