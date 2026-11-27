#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <cstdint>
#include <unordered_map>
#include <array>
#include <string>
#include <string_view>
#include <vector>

enum class GLUniformDomain : std::uint8_t
{
    World = 0,
    Model,
    FX,
    Sprite,
    Renderer,
    Quality,
    Other,
    Count
};

struct GLUniformDomainStats
{
    std::uint64_t requests = 0;
    std::uint64_t calls = 0;
    std::uint64_t skipped = 0;
};

struct GLUniformHotEntry
{
    std::string program;
    std::string uniform;
    std::uint64_t requests = 0;
    std::uint64_t calls = 0;
    std::uint64_t skipped = 0;
};

struct GLUniformPerfStats
{
    std::uint64_t requests = 0;
    std::uint64_t calls = 0;
    std::uint64_t skipped = 0;

    std::uint64_t scalarRequests = 0;
    std::uint64_t scalarCalls = 0;
    std::uint64_t scalarSkipped = 0;
    std::uint64_t vectorRequests = 0;
    std::uint64_t vectorCalls = 0;
    std::uint64_t vectorSkipped = 0;
    std::uint64_t matrixRequests = 0;
    std::uint64_t matrixCalls = 0;
    std::uint64_t matrixSkipped = 0;
    std::array<GLUniformDomainStats, static_cast<std::size_t>(GLUniformDomain::Count)> domains{};
};

// Per-program/per-location uniform value cache.  OpenGL stores ordinary
// uniform values in the program object, so a value can be skipped whenever
// the same program/location already contains the exact same bits.
class GLUniformStats final
{
public:
    static GLUniformStats &Instance();

    void Submit1i(GLint location, GLint v0);
    void Submit1ui(GLint location, GLuint v0);
    void Submit1f(GLint location, GLfloat v0);
    void Submit3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
    void Submit4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    void SubmitMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

    void RegisterProgram(GLuint program, const std::string &name);
    void RegisterUniform(GLuint program, GLint location, std::string_view name);
    void InvalidateProgram(GLuint program);
    void InvalidateAll();

    GLUniformPerfStats Stats() const noexcept { return m_stats; }
    std::vector<GLUniformHotEntry> TopActual(std::size_t count) const;
    void Reset() noexcept
    {
        m_stats = {};
        m_frameHot.clear();
    }

private:
    enum class ValueType : std::uint8_t
    {
        I1,
        UI1,
        F1,
        F3,
        F4,
        M4
    };
    struct CachedValue
    {
        ValueType type = ValueType::I1;
        GLsizei count = 1;
        GLboolean transpose = GL_FALSE;
        std::array<std::uint8_t, 64> bytes{};
        std::uint8_t byteCount = 0;
    };

    GLUniformStats() = default;
    static std::uint64_t MakeKey(GLuint program, GLint location) noexcept;
    bool ShouldSubmit(GLuint program, GLint location, ValueType type,
                      const void *data, std::uint8_t byteCount,
                      GLsizei count = 1, GLboolean transpose = GL_FALSE);
    void Record(GLuint program, GLint location, bool actual, int category) noexcept;
    GLUniformDomain DomainForProgram(GLuint program) const noexcept;

    struct HotCounter
    {
        std::uint64_t requests = 0, calls = 0, skipped = 0;
    };
    std::unordered_map<std::uint64_t, CachedValue> m_cache;
    std::unordered_map<std::uint64_t, HotCounter> m_frameHot;
    std::unordered_map<GLuint, std::string> m_programNames;
    std::unordered_map<std::uint64_t, std::string> m_uniformNames;
    GLUniformPerfStats m_stats{};
};
