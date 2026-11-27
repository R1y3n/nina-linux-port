#pragma once

#include "../gl_loader.h"

#include <string>
#include <string_view>
#include <unordered_map>

namespace avp2::render
{
    class Shader final
    {
    public:
        Shader() = default;
        explicit Shader(std::string name);
        ~Shader();

        Shader(const Shader &) = delete;
        Shader &operator=(const Shader &) = delete;
        Shader(Shader &&other) noexcept;
        Shader &operator=(Shader &&other) noexcept;

        bool BuildGraphics(const char *vertexSource, const char *fragmentSource);
        bool BuildCompute(const char *computeSource);
        void Reset();

        GLuint Program() const noexcept { return m_program; }
        bool IsValid() const noexcept { return m_program != 0; }
        const std::string &Name() const noexcept { return m_name; }

        void Use() const;
        GLint Uniform(std::string_view name) const;

    private:
        GLuint CompileStage(GLenum type, const char *source, const char *stageName) const;
        bool Link(GLuint vertex, GLuint fragment, GLuint compute);
        std::string ProgramLog() const;

        std::string m_name;
        GLuint m_program = 0;
        mutable std::unordered_map<std::string, GLint> m_uniformCache;
    };
}
