#include "frame_constants.h"
#include "../../gl_loader.h"
#include "subsystems/renderer/fog_state.h"
#include "gl_upload_stats.h"
#include <algorithm>
#include <cmath>
#include <cstring>

namespace
{
    constexpr GLenum GL_UNIFORM_BUFFER_AVP2 = 0x8A11;
    constexpr GLbitfield GL_DYNAMIC_STORAGE_BIT_AVP2 = 0x0100;
    constexpr GLuint FRAME_CONSTANT_BINDING = 12;
}

FrameConstants &FrameConstants::Instance()
{
    static FrameConstants s;
    return s;
}

bool FrameConstants::Ensure()
{
    if (m_ubo)
        return true;
    if (!glf.CreateBuffers || !glf.NamedBufferStorage || !glf.BindBufferBase || !glf.NamedBufferSubData)
        return false;
    glf.CreateBuffers(1, &m_ubo);
    if (!m_ubo)
        return false;
    glf.NamedBufferStorage(m_ubo, sizeof(GpuData), nullptr, GL_DYNAMIC_STORAGE_BIT_AVP2);
    glf.BindBufferBase(GL_UNIFORM_BUFFER_AVP2, FRAME_CONSTANT_BINDING, m_ubo);
    m_haveLast = false;
    return true;
}

bool FrameConstants::Apply(const SceneDesc *scene, float nearZ, float farZ)
{
    if (!scene)
        return false;
    const float tx = std::tan(std::max(0.01f, scene->m_fFovX * 0.5f));
    const float ty = std::tan(std::max(0.01f, scene->m_fFovY * 0.5f));
    return Apply(scene, tx, ty, nearZ, farZ);
}

bool FrameConstants::Apply(const SceneDesc *scene, float tanHalfFovX, float tanHalfFovY, float nearZ, float farZ)
{
    ++m_stats.applyRequests;
    if (!scene || !Ensure())
        return false;
    GpuData d{};
    d.projection[0] = tanHalfFovX;
    d.projection[1] = tanHalfFovY;
    d.projection[2] = nearZ;
    d.projection[3] = farZ;
    d.cameraPos[0] = scene->m_vPos.x;
    d.cameraPos[1] = scene->m_vPos.y;
    d.cameraPos[2] = scene->m_vPos.z;
    d.cameraQuat[0] = scene->m_rRotation.x;
    d.cameraQuat[1] = scene->m_rRotation.y;
    d.cameraQuat[2] = scene->m_rRotation.z;
    d.cameraQuat[3] = scene->m_rRotation.w;
    d.fogColorEnabled[0] = g_fogState.r;
    d.fogColorEnabled[1] = g_fogState.g;
    d.fogColorEnabled[2] = g_fogState.b;
    d.fogColorEnabled[3] = g_fogState.enabled ? 1.0f : 0.0f;
    d.fogParams[0] = g_fogState.nearZ;
    d.fogParams[1] = g_fogState.farZ;
    d.fogParams[2] = scene->m_fFrameTime;

    if (m_haveLast && std::memcmp(&d, &m_last, sizeof(d)) == 0)
    {
        ++m_stats.skippedUploads;
        return true;
    }
    glf.NamedBufferSubData(m_ubo, 0, sizeof(d), &d);
    GLUploadStats::Instance().RecordSubData(GLUploadCategory::Renderer, sizeof(d));
    m_last = d;
    m_haveLast = true;
    ++m_stats.uploads;
    return true;
}

void FrameConstants::Term()
{
    if (m_ubo && glf.DeleteBuffers)
        glf.DeleteBuffers(1, &m_ubo);
    m_ubo = 0;
    m_haveLast = false;
    m_last = {};
    m_stats = {};
}
