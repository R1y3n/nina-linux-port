#include "shader_manager.h"
#include "utils/log.h"

#include <utility>

namespace avp2::render
{
    ShaderManager &ShaderManager::Instance()
    {
        static ShaderManager manager;
        return manager;
    }

    Shader *ShaderManager::Store(std::string name, std::unique_ptr<Shader> shader)
    {
        auto it = m_shaders.find(name);
        if (it != m_shaders.end())
        {
            it->second = std::move(shader);
            return it->second.get();
        }

        auto [inserted, ok] = m_shaders.emplace(std::move(name), std::move(shader));
        (void)ok;
        return inserted->second.get();
    }

    Shader *ShaderManager::CreateGraphicsFromResources(std::string name, ShaderResourceId vertexResource, ShaderResourceId fragmentResource)
    {
        std::string vertexSource;
        std::string fragmentSource;
        if (!ShaderResourceLoader::Load(vertexResource, vertexSource) ||
            !ShaderResourceLoader::Load(fragmentResource, fragmentSource))
        {
            LOG_SESSION("ShaderManager: failed to load embedded graphics shader '%s'", name.c_str());
            return nullptr;
        }

        return CreateGraphics(std::move(name), vertexSource.c_str(), fragmentSource.c_str());
    }

    Shader *ShaderManager::CreateComputeFromResource(std::string name, ShaderResourceId computeResource)
    {
        std::string computeSource;
        if (!ShaderResourceLoader::Load(computeResource, computeSource))
        {
            LOG_SESSION("ShaderManager: failed to load embedded compute shader '%s'", name.c_str());
            return nullptr;
        }

        return CreateCompute(std::move(name), computeSource.c_str());
    }

    Shader *ShaderManager::CreateGraphics(std::string name, const char *vertexSource, const char *fragmentSource)
    {
        auto shader = std::make_unique<Shader>(name);
        if (!shader->BuildGraphics(vertexSource, fragmentSource))
            return nullptr;

        Shader *result = Store(name, std::move(shader));
        LOG_SESSION("ShaderManager: graphics shader '%s' ready program=%u", name.c_str(), result ? result->Program() : 0u);
        return result;
    }

    Shader *ShaderManager::CreateCompute(std::string name, const char *computeSource)
    {
        auto shader = std::make_unique<Shader>(name);
        if (!shader->BuildCompute(computeSource))
            return nullptr;

        Shader *result = Store(name, std::move(shader));
        LOG_SESSION("ShaderManager: compute shader '%s' ready program=%u", name.c_str(), result ? result->Program() : 0u);
        return result;
    }

    Shader *ShaderManager::Find(std::string_view name)
    {
        const auto it = m_shaders.find(std::string(name));
        return it == m_shaders.end() ? nullptr : it->second.get();
    }

    const Shader *ShaderManager::Find(std::string_view name) const
    {
        const auto it = m_shaders.find(std::string(name));
        return it == m_shaders.end() ? nullptr : it->second.get();
    }

    GLuint ShaderManager::Program(std::string_view name) const
    {
        const Shader *shader = Find(name);
        return shader ? shader->Program() : 0;
    }

    GLint ShaderManager::Uniform(std::string_view shaderName, std::string_view uniformName) const
    {
        const Shader *shader = Find(shaderName);
        return shader ? shader->Uniform(uniformName) : -1;
    }

    bool ShaderManager::Use(std::string_view name) const
    {
        const Shader *shader = Find(name);
        if (!shader)
            return false;
        shader->Use();
        return true;
    }

    bool ShaderManager::Release(std::string_view name)
    {
        const auto it = m_shaders.find(std::string(name));
        if (it == m_shaders.end())
            return false;
        m_shaders.erase(it);
        return true;
    }

    void ShaderManager::Shutdown()
    {
        if (!m_shaders.empty())
            LOG_SESSION("ShaderManager: releasing %u shader program(s)", static_cast<unsigned>(m_shaders.size()));
        m_shaders.clear();
    }
}
