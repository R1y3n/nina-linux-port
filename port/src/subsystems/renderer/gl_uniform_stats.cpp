#include "../../gl_loader.h"
#include "gl_state_cache.h"
#include <algorithm>
#include <cstring>

GLUniformStats &GLUniformStats::Instance()
{
    static GLUniformStats s;
    return s;
}

std::uint64_t GLUniformStats::MakeKey(GLuint program, GLint location) noexcept
{
    return (std::uint64_t(program) << 32) | std::uint32_t(location);
}

GLUniformDomain GLUniformStats::DomainForProgram(GLuint program) const noexcept
{
    const auto it = m_programNames.find(program);
    if (it == m_programNames.end())
        return GLUniformDomain::Other;
    const std::string &n = it->second;
    if (n.rfind("world.", 0) == 0)
        return GLUniformDomain::World;
    if (n.rfind("model.", 0) == 0)
        return GLUniformDomain::Model;
    if (n.rfind("fx.", 0) == 0)
        return GLUniformDomain::FX;
    if (n.rfind("sprite.", 0) == 0)
        return GLUniformDomain::Sprite;
    if (n.rfind("renderer.", 0) == 0)
        return GLUniformDomain::Renderer;
    if (n.rfind("quality.", 0) == 0)
        return GLUniformDomain::Quality;
    return GLUniformDomain::Other;
}

void GLUniformStats::Record(GLuint program, GLint location, bool actual, int category) noexcept
{
    ++m_stats.requests;
    if (actual)
        ++m_stats.calls;
    else
        ++m_stats.skipped;
    if (category == 0)
    {
        ++m_stats.scalarRequests;
        if (actual)
            ++m_stats.scalarCalls;
        else
            ++m_stats.scalarSkipped;
    }
    else if (category == 1)
    {
        ++m_stats.vectorRequests;
        if (actual)
            ++m_stats.vectorCalls;
        else
            ++m_stats.vectorSkipped;
    }
    else
    {
        ++m_stats.matrixRequests;
        if (actual)
            ++m_stats.matrixCalls;
        else
            ++m_stats.matrixSkipped;
    }
    const auto d = static_cast<std::size_t>(DomainForProgram(program));
    auto &ds = m_stats.domains[d];
    ++ds.requests;
    if (actual)
        ++ds.calls;
    else
        ++ds.skipped;
    if (location >= 0 && program)
    {
        auto &h = m_frameHot[MakeKey(program, location)];
        ++h.requests;
        if (actual)
            ++h.calls;
        else
            ++h.skipped;
    }
}

bool GLUniformStats::ShouldSubmit(GLuint program, GLint location, ValueType type,
                                  const void *data, std::uint8_t byteCount,
                                  GLsizei count, GLboolean transpose)
{
    if (location < 0)
        return false;
    if (program == 0)
        return true;
    const std::uint64_t key = MakeKey(program, location);
    auto it = m_cache.find(key);
    if (it != m_cache.end())
    {
        const CachedValue &old = it->second;
        if (old.type == type && old.byteCount == byteCount && old.count == count &&
            old.transpose == transpose && std::memcmp(old.bytes.data(), data, byteCount) == 0)
            return false;
    }
    CachedValue next{};
    next.type = type;
    next.byteCount = byteCount;
    next.count = count;
    next.transpose = transpose;
    std::memcpy(next.bytes.data(), data, byteCount);
    m_cache[key] = next;
    return true;
}

void GLUniformStats::Submit1i(GLint location, GLint v0)
{
    const GLuint p = avp2::render::GLStateCache::Instance().CurrentProgram();
    const bool actual = ShouldSubmit(p, location, ValueType::I1, &v0, sizeof(v0));
    Record(p, location, actual, 0);
    if (actual)
        glf.Uniform1i(location, v0);
}
void GLUniformStats::Submit1ui(GLint location, GLuint v0)
{
    const GLuint p = avp2::render::GLStateCache::Instance().CurrentProgram();
    const bool actual = ShouldSubmit(p, location, ValueType::UI1, &v0, sizeof(v0));
    Record(p, location, actual, 0);
    if (actual)
        glf.Uniform1ui(location, v0);
}
void GLUniformStats::Submit1f(GLint location, GLfloat v0)
{
    const GLuint p = avp2::render::GLStateCache::Instance().CurrentProgram();
    const bool actual = ShouldSubmit(p, location, ValueType::F1, &v0, sizeof(v0));
    Record(p, location, actual, 0);
    if (actual)
        glf.Uniform1f(location, v0);
}
void GLUniformStats::Submit3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    const GLfloat v[3] = {v0, v1, v2};
    const GLuint p = avp2::render::GLStateCache::Instance().CurrentProgram();
    const bool actual = ShouldSubmit(p, location, ValueType::F3, v, sizeof(v));
    Record(p, location, actual, 1);
    if (actual)
        glf.Uniform3f(location, v0, v1, v2);
}
void GLUniformStats::Submit4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    const GLfloat v[4] = {v0, v1, v2, v3};
    const GLuint p = avp2::render::GLStateCache::Instance().CurrentProgram();
    const bool actual = ShouldSubmit(p, location, ValueType::F4, v, sizeof(v));
    Record(p, location, actual, 1);
    if (actual)
        glf.Uniform4f(location, v0, v1, v2, v3);
}
void GLUniformStats::SubmitMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    const GLuint p = avp2::render::GLStateCache::Instance().CurrentProgram();
    bool actual = true;
    if (count == 1 && value)
        actual = ShouldSubmit(p, location, ValueType::M4, value, 64, count, transpose);
    else if (location < 0)
        actual = false;
    Record(p, location, actual, 2);
    if (actual)
        glf.UniformMatrix4fv(location, count, transpose, value);
}

void GLUniformStats::RegisterProgram(GLuint program, const std::string &name)
{
    if (program)
        m_programNames[program] = name;
}
void GLUniformStats::RegisterUniform(GLuint program, GLint location, std::string_view name)
{
    if (program && location >= 0 && !name.empty())
        m_uniformNames[MakeKey(program, location)] = std::string(name);
}

std::vector<GLUniformHotEntry> GLUniformStats::TopActual(std::size_t count) const
{
    struct Item
    {
        std::uint64_t key;
        HotCounter h;
    };
    std::vector<Item> items;
    items.reserve(m_frameHot.size());
    for (const auto &kv : m_frameHot)
        if (kv.second.calls)
            items.push_back({kv.first, kv.second});
    std::sort(items.begin(), items.end(), [](const Item &a, const Item &b)
              { if(a.h.calls!=b.h.calls)return a.h.calls>b.h.calls; return a.h.requests>b.h.requests; });
    if (items.size() > count)
        items.resize(count);
    std::vector<GLUniformHotEntry> out;
    out.reserve(items.size());
    for (const auto &i : items)
    {
        const GLuint p = GLuint(i.key >> 32);
        GLUniformHotEntry e{};
        auto pn = m_programNames.find(p);
        e.program = (pn == m_programNames.end()) ? "?" : pn->second;
        auto un = m_uniformNames.find(i.key);
        e.uniform = (un == m_uniformNames.end()) ? ("loc" + std::to_string(std::uint32_t(i.key))) : un->second;
        e.requests = i.h.requests;
        e.calls = i.h.calls;
        e.skipped = i.h.skipped;
        out.push_back(std::move(e));
    }
    return out;
}

void GLUniformStats::InvalidateProgram(GLuint program)
{
    if (!program)
        return;
    for (auto it = m_cache.begin(); it != m_cache.end();)
    {
        if (GLuint(it->first >> 32) == program)
            it = m_cache.erase(it);
        else
            ++it;
    }
    for (auto it = m_frameHot.begin(); it != m_frameHot.end();)
    {
        if (GLuint(it->first >> 32) == program)
            it = m_frameHot.erase(it);
        else
            ++it;
    }
    for (auto it = m_uniformNames.begin(); it != m_uniformNames.end();)
    {
        if (GLuint(it->first >> 32) == program)
            it = m_uniformNames.erase(it);
        else
            ++it;
    }
    m_programNames.erase(program);
}
void GLUniformStats::InvalidateAll()
{
    m_cache.clear();
    m_frameHot.clear();
    m_programNames.clear();
    m_uniformNames.clear();
}
