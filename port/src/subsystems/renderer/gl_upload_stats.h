#pragma once
#include <cstddef>
#include <cstdint>

enum class GLUploadCategory : uint8_t
{
    Renderer,
    FX,
    Models,
    Sprites,
    World,
    Count
};

enum class GLModelUploadKind : uint8_t
{
    Nodes,
    Lights,
    SkinState,
    LegacyVertices,
    Shadow,
    Other,
    Count
};

enum class GLWorldUploadKind : uint8_t
{
    MdiState,
    MdiCommands,
    PvsStatic,
    PvsTerrain,
    LightmapState,
    LightmapDirty,
    DynamicLights,
    VertexUpdates,
    VertexStatic,
    VertexFallback,
    SurfaceFx,
    CacheBuild,
    SkyClip,
    Other,
    Count
};

struct GLUploadStatsSnapshot
{
    uint64_t subDataCalls = 0;
    uint64_t subDataBytes = 0;
    uint64_t streamWrites = 0;
    uint64_t streamBytes = 0;
    uint64_t categoryCalls[static_cast<size_t>(GLUploadCategory::Count)]{};
    uint64_t categoryBytes[static_cast<size_t>(GLUploadCategory::Count)]{};
    uint64_t modelKindCalls[static_cast<size_t>(GLModelUploadKind::Count)]{};
    uint64_t modelKindBytes[static_cast<size_t>(GLModelUploadKind::Count)]{};
    uint64_t modelKindSubDataCalls[static_cast<size_t>(GLModelUploadKind::Count)]{};
    uint64_t modelKindSubDataBytes[static_cast<size_t>(GLModelUploadKind::Count)]{};
    uint64_t modelKindStreamWrites[static_cast<size_t>(GLModelUploadKind::Count)]{};
    uint64_t modelKindStreamBytes[static_cast<size_t>(GLModelUploadKind::Count)]{};
    uint64_t worldKindCalls[static_cast<size_t>(GLWorldUploadKind::Count)]{};
    uint64_t worldKindBytes[static_cast<size_t>(GLWorldUploadKind::Count)]{};
    uint64_t worldKindSubDataCalls[static_cast<size_t>(GLWorldUploadKind::Count)]{};
    uint64_t worldKindSubDataBytes[static_cast<size_t>(GLWorldUploadKind::Count)]{};
    uint64_t worldKindStreamWrites[static_cast<size_t>(GLWorldUploadKind::Count)]{};
    uint64_t worldKindStreamBytes[static_cast<size_t>(GLWorldUploadKind::Count)]{};
};

class GLUploadStats final
{
public:
    static GLUploadStats &Instance();
    void RecordSubData(GLUploadCategory category, size_t bytes);
    void RecordStreamWrite(GLUploadCategory category, size_t bytes);
    void RecordModelSubData(GLModelUploadKind kind, size_t bytes);
    void RecordModelStreamWrite(GLModelUploadKind kind, size_t bytes);
    void RecordWorldSubData(GLWorldUploadKind kind, size_t bytes);
    void RecordWorldStreamWrite(GLWorldUploadKind kind, size_t bytes);
    GLUploadStatsSnapshot Stats() const { return m_stats; }
    void Reset() { m_stats = {}; }

private:
    GLUploadStatsSnapshot m_stats{};
};

void GLTrackedNamedBufferSubData(unsigned int buffer, std::ptrdiff_t offset, std::ptrdiff_t size,
                                 const void *data, GLUploadCategory category);

void GLTrackedWorldNamedBufferSubData(unsigned int buffer, std::ptrdiff_t offset, std::ptrdiff_t size,
                                      const void *data, GLWorldUploadKind kind);

void GLTrackedModelNamedBufferSubData(unsigned int buffer, std::ptrdiff_t offset, std::ptrdiff_t size,
                                      const void *data, GLModelUploadKind kind);
