#include "shader.h"
#include "utils/log.h"

#include <algorithm>
#include <utility>
#include <vector>

namespace avp2::render
{
    Shader::Shader(std::string name)
        : m_name(std::move(name))
    {
    }

    Shader::~Shader()
    {
        Reset();
    }

    Shader::Shader(Shader &&other) noexcept
        : m_name(std::move(other.m_name)),
          m_program(other.m_program),
          m_uniformCache(std::move(other.m_uniformCache))
    {
        other.m_program = 0;
    }

    Shader &Shader::operator=(Shader &&other) noexcept
    {
        if (this == &other)
            return *this;

        Reset();
        m_name = std::move(other.m_name);
        m_program = other.m_program;
        m_uniformCache = std::move(other.m_uniformCache);
        other.m_program = 0;
        return *this;
    }

    GLuint Shader::CompileStage(GLenum type, const char *source, const char *stageName) const
    {
        if (!source || !*source)
        {
            LOG_SESSION("Shader '%s': empty %s source", m_name.c_str(), stageName);
            return 0;
        }

        const GLuint shader = glf.CreateShader(type);
        if (!shader)
        {
            LOG_SESSION("Shader '%s': glCreateShader failed for %s stage", m_name.c_str(), stageName);
            return 0;
        }

        glf.ShaderSource(shader, 1, &source, nullptr);
        glf.CompileShader(shader);

        GLint ok = 0;
        glf.GetShaderiv(shader, GL_COMPILE_STATUS_, &ok);
        if (ok)
            return shader;

        if (LogIsSessionEnabled())
        {
            GLint len = 0;
            glf.GetShaderiv(shader, GL_INFO_LOG_LENGTH_, &len);
            std::vector<char> text(static_cast<size_t>(std::max(1, len)), '\0');
            glf.GetShaderInfoLog(shader, len, nullptr, text.data());
            LOG_SESSION("Shader '%s' %s compile failed: %s", m_name.c_str(), stageName, text.data());
        }

        glf.DeleteShader(shader);
        return 0;
    }

    std::string Shader::ProgramLog() const
    {
        if (!m_program)
            return {};

        GLint len = 0;
        glf.GetProgramiv(m_program, GL_INFO_LOG_LENGTH_, &len);
        if (len <= 1)
            return {};

        std::vector<char> text(static_cast<size_t>(len), '\0');
        glf.GetProgramInfoLog(m_program, len, nullptr, text.data());
        return std::string(text.data());
    }

    bool Shader::Link(GLuint vertex, GLuint fragment, GLuint compute)
    {
        Reset();
        m_program = glf.CreateProgram();
        if (!m_program)
        {
            LOG_SESSION("Shader '%s': glCreateProgram failed", m_name.c_str());
            return false;
        }

        if (vertex)
            glf.AttachShader(m_program, vertex);
        if (fragment)
            glf.AttachShader(m_program, fragment);
        if (compute)
            glf.AttachShader(m_program, compute);
        glf.LinkProgram(m_program);

        GLint ok = 0;
        glf.GetProgramiv(m_program, GL_LINK_STATUS_, &ok);
        if (!ok)
        {
            if (LogIsSessionEnabled())
            {
                const std::string text = ProgramLog();
                LOG_SESSION("Shader '%s' link failed: %s", m_name.c_str(), text.empty() ? "<no driver log>" : text.c_str());
            }

            Reset();
            return false;
        }

        m_uniformCache.clear();
        GLUniformStats::Instance().RegisterProgram(m_program, m_name);
        return true;
    }

    bool Shader::BuildGraphics(const char *vertexSource, const char *fragmentSource)
    {
        const GLuint vertex = CompileStage(GL_VERTEX_SHADER_, vertexSource, "vertex");
        if (!vertex)
            return false;

        const GLuint fragment = CompileStage(GL_FRAGMENT_SHADER_, fragmentSource, "fragment");
        if (!fragment)
        {
            glf.DeleteShader(vertex);
            return false;
        }

        const bool ok = Link(vertex, fragment, 0);
        glf.DeleteShader(vertex);
        glf.DeleteShader(fragment);
        return ok;
    }

    bool Shader::BuildCompute(const char *computeSource)
    {
        const GLuint compute = CompileStage(GL_COMPUTE_SHADER_, computeSource, "compute");
        if (!compute)
            return false;

        const bool ok = Link(0, 0, compute);
        glf.DeleteShader(compute);
        return ok;
    }

    void Shader::Reset()
    {
        m_uniformCache.clear();
        if (m_program && glf.DeleteProgram)
            GLStateDeleteProgram(m_program);
        m_program = 0;
    }

    void Shader::Use() const
    {
        GLStateCache::Instance().UseProgram(m_program);
    }

    GLint Shader::Uniform(std::string_view name) const
    {
        if (!m_program || name.empty())
            return -1;

        const std::string key(name);
        const auto found = m_uniformCache.find(key);
        if (found != m_uniformCache.end())
            return found->second;

        const GLint location = glf.GetUniformLocation(m_program, key.c_str());
        GLUniformStats::Instance().RegisterUniform(m_program, location, key);
        m_uniformCache.emplace(key, location);
        return location;
    }
}
