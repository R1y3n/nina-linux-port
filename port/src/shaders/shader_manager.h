#pragma once

#include "shader.h"
#include "shader_resources.h"

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace avp2::render
{
    class ShaderManager final
    {
    public:
        static ShaderManager &Instance();

        ShaderManager(const ShaderManager &) = delete;
        ShaderManager &operator=(const ShaderManager &) = delete;

        Shader *CreateGraphicsFromResources(std::string name, ShaderResourceId vertexResource, ShaderResourceId fragmentResource);
        Shader *CreateComputeFromResource(std::string name, ShaderResourceId computeResource);

        Shader *Find(std::string_view name);
        const Shader *Find(std::string_view name) const;
        GLuint Program(std::string_view name) const;
        GLint Uniform(std::string_view shaderName, std::string_view uniformName) const;
        bool Use(std::string_view name) const;

        bool Release(std::string_view name);
        void Shutdown();
        size_t Count() const noexcept { return m_shaders.size(); }

    private:
        ShaderManager() = default;
        ~ShaderManager() = default;

        Shader *Store(std::string name, std::unique_ptr<Shader> shader);
        Shader *CreateGraphics(std::string name, const char *vertexSource, const char *fragmentSource);
        Shader *CreateCompute(std::string name, const char *computeSource);

        std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;
    };
}
