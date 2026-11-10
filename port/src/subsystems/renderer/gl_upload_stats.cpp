#include "gl_upload_stats.h"
#include "../../gl_loader.h"

extern GLFns glf;

GLUploadStats &GLUploadStats::Instance()
{
    static GLUploadStats s;
    return s;
}

void GLUploadStats::RecordSubData(GLUploadCategory category, size_t bytes)
{
    ++m_stats.subDataCalls;
    m_stats.subDataBytes += bytes;
    const size_t i = static_cast<size_t>(category);
    ++m_stats.categoryCalls[i];
    m_stats.categoryBytes[i] += bytes;
}

void GLUploadStats::RecordStreamWrite(GLUploadCategory category, size_t bytes)
{
    ++m_stats.streamWrites;
    m_stats.streamBytes += bytes;
    const size_t i = static_cast<size_t>(category);
    ++m_stats.categoryCalls[i];
    m_stats.categoryBytes[i] += bytes;
}

void GLUploadStats::RecordModelSubData(GLModelUploadKind kind, size_t bytes)
{
    RecordSubData(GLUploadCategory::Models, bytes);
    const size_t i = static_cast<size_t>(kind);
    ++m_stats.modelKindCalls[i];
    m_stats.modelKindBytes[i] += bytes;
    ++m_stats.modelKindSubDataCalls[i];
    m_stats.modelKindSubDataBytes[i] += bytes;
}

void GLUploadStats::RecordModelStreamWrite(GLModelUploadKind kind, size_t bytes)
{
    RecordStreamWrite(GLUploadCategory::Models, bytes);
    const size_t i = static_cast<size_t>(kind);
    ++m_stats.modelKindCalls[i];
    m_stats.modelKindBytes[i] += bytes;
    ++m_stats.modelKindStreamWrites[i];
    m_stats.modelKindStreamBytes[i] += bytes;
}

void GLUploadStats::RecordWorldSubData(GLWorldUploadKind kind, size_t bytes)
{
    RecordSubData(GLUploadCategory::World, bytes);
    const size_t i = static_cast<size_t>(kind);
    ++m_stats.worldKindCalls[i];
    m_stats.worldKindBytes[i] += bytes;
    ++m_stats.worldKindSubDataCalls[i];
    m_stats.worldKindSubDataBytes[i] += bytes;
}

void GLUploadStats::RecordWorldStreamWrite(GLWorldUploadKind kind, size_t bytes)
{
    RecordStreamWrite(GLUploadCategory::World, bytes);
    const size_t i = static_cast<size_t>(kind);
    ++m_stats.worldKindCalls[i];
    m_stats.worldKindBytes[i] += bytes;
    ++m_stats.worldKindStreamWrites[i];
    m_stats.worldKindStreamBytes[i] += bytes;
}

void GLTrackedNamedBufferSubData(unsigned int buffer, std::ptrdiff_t offset, std::ptrdiff_t size,
                                 const void *data, GLUploadCategory category)
{
    if (size > 0)
        GLUploadStats::Instance().RecordSubData(category, static_cast<size_t>(size));
    glf.NamedBufferSubData(buffer, offset, size, data);
}

void GLTrackedWorldNamedBufferSubData(unsigned int buffer, std::ptrdiff_t offset, std::ptrdiff_t size,
                                      const void *data, GLWorldUploadKind kind)
{
    if (size > 0)
        GLUploadStats::Instance().RecordWorldSubData(kind, static_cast<size_t>(size));
    glf.NamedBufferSubData(buffer, offset, size, data);
}

void GLTrackedModelNamedBufferSubData(unsigned int buffer, std::ptrdiff_t offset, std::ptrdiff_t size,
                                      const void *data, GLModelUploadKind kind)
{
    if (size > 0)
        GLUploadStats::Instance().RecordModelSubData(kind, static_cast<size_t>(size));
    glf.NamedBufferSubData(buffer, offset, size, data);
}
