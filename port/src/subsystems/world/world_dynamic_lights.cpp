#include "world_dynamic_lights.h"
#include "world_renderer.h"
#include "world_pvs.h"
#include "../../gl_loader.h"
#include "subsystems/renderer/gl_upload_stats.h"
#include "utils/log.h"
#include "../../shaders/shader.h"
#include "../renderer/stock_render_options.h"
#include <algorithm>
#include <array>
#include <cmath>

WorldDynamicLightSystem &WorldDynamicLightSystem::Instance()
{
    static WorldDynamicLightSystem v;
    return v;
}

bool WorldDynamicLightSystem::Init(avp2::render::Shader *shader)
{
    Term();
    if (!shader)
        return false;
    m_state.uDynamicLightCount = shader->Uniform("uDynamicLightCount");
    glf.CreateBuffers(1, &m_state.ssbo);
    if (!m_state.ssbo)
        return false;
    glf.NamedBufferStorage(m_state.ssbo,
                           static_cast<GLsizeiptr>(MAX_WORLD_DYNAMIC_LIGHTS * sizeof(DynamicWorldLightGPU)),
                           nullptr, GL_DYNAMIC_STORAGE_BIT_);
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 8, m_state.ssbo);
    Disable();
    return true;
}

void WorldDynamicLightSystem::Term()
{
    m_state.uploadedCount = 0;
    if (m_state.ssbo)
        glf.DeleteBuffers(1, &m_state.ssbo);
    m_state.ssbo = 0;
    m_state.uDynamicLightCount = -1;
}

uint32 WorldDynamicLightSystem::UploadVisible()
{
    m_state.uploadedCount = 0;
    if (!WorldRenderer::Instance().State().worldShader || !m_state.ssbo || m_state.uDynamicLightCount < 0)
        return 0;

    // d3d.ren exposes DynamicLight as the master switch for the
    // world dynamic-light pass.  Keep PVS collection alive, but submit no
    // light volumes when the stock cvar is disabled.
    if (!StockRenderOptions::Instance().DynamicLight())
    {
        Disable();
        return 0;
    }

    std::array<DynamicWorldLightGPU, MAX_WORLD_DYNAMIC_LIGHTS> gpu{};
    uint32 skippedOnlyObjects = 0;
    uint32 skippedHidden = 0;
    uint32 skippedInvalid = 0;

    for (DynamicLightCompat *light : WorldPVS::Instance().State().visibleDynamicLights)
    {
        if (m_state.uploadedCount >= MAX_WORLD_DYNAMIC_LIGHTS)
            break;
        if (!light || !(light->m_Base.m_dwFlags & FLAG_VISIBLE))
        {
            ++skippedHidden;
            continue;
        }
        if (light->m_fLightRadius <= 0.001f || !std::isfinite(light->m_fLightRadius))
        {
            ++skippedInvalid;
            continue;
        }

        // FLAG_ONLYLIGHTOBJECTS means exactly that: stock Talon keeps the
        // light in the object-light list but excludes it from world lighting.
        // FLAG_ONLYLIGHTWORLD is allowed here (and excluded in model3d.cpp).
        if (light->m_Base.m_dwFlags & FLAG_ONLYLIGHTOBJECTS)
        {
            ++skippedOnlyObjects;
            continue;
        }

        DynamicWorldLightGPU &dst = gpu[m_state.uploadedCount++];
        dst.posRadius[0] = light->m_Base.m_vPos.x;
        dst.posRadius[1] = light->m_Base.m_vPos.y;
        dst.posRadius[2] = light->m_Base.m_vPos.z;
        dst.posRadius[3] = light->m_fLightRadius;
        // Retail d3d.ren does NOT treat OT_LIGHT object color as ordinary
        // 0..255 RGB.  Both the world-light and model-light paths decode each
        // channel as a signed delta around the midpoint:
        //
        //     signedChannel = (2 * byte - 255) / 255
        //
        // See d3d.ren 0x10008414..0x10008477 and
        // 0x100100B2..0x1001011A.  Treating the bytes as plain RGB makes
        // authored colored lights wash toward white.
        constexpr float kInv255 = 1.0f / 255.0f;
        dst.colorFlags[0] = (2.0f * float(light->m_Base.m_nColorR) - 255.0f) * kInv255;
        dst.colorFlags[1] = (2.0f * float(light->m_Base.m_nColorG) - 255.0f) * kInv255;
        dst.colorFlags[2] = (2.0f * float(light->m_Base.m_nColorB) - 255.0f) * kInv255;
        dst.colorFlags[3] = 0.0f;
    }

    if (m_state.uploadedCount)
    {
        GLTrackedWorldNamedBufferSubData(m_state.ssbo, 0,
                                         static_cast<GLsizeiptr>(m_state.uploadedCount * sizeof(DynamicWorldLightGPU)),
                                         gpu.data(), GLWorldUploadKind::DynamicLights);
    }
    glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 8, m_state.ssbo);
    GLUniform1i(m_state.uDynamicLightCount, static_cast<GLint>(m_state.uploadedCount));

    // Dynamic lights can move every frame (especially the flashlight), so do
    // not turn diagnostics into a render-thread I/O bottleneck.  Report when
    // the population changes and periodically while lights are active.
    static uint32 lastCount = 0xFFFFFFFFu;
    static uint32 activeFrame = 0;
    ++activeFrame;
    if (m_state.uploadedCount != lastCount ||
        (m_state.uploadedCount && (activeFrame % 60u) == 1u))
    {
        lastCount = m_state.uploadedCount;
        LOG_SESSION("World3D DYNAMIC-LIGHTS visible=%u world=%u skipOnlyObjects=%u skipHidden=%u skipInvalid=%u max=%u path=DYNAMICLIGHT-CVAR/QUALITY-SMOOTH-ALBEDO-R1.50",
                    static_cast<unsigned>(WorldPVS::Instance().State().visibleDynamicLights.size()),
                    m_state.uploadedCount, skippedOnlyObjects, skippedHidden, skippedInvalid,
                    MAX_WORLD_DYNAMIC_LIGHTS);
        const uint32 details = std::min<uint32>(m_state.uploadedCount, 4u);
        for (uint32 i = 0; i < details; ++i)
        {
            DynamicLightCompat *src = nullptr;
            // Find the i-th world-eligible source again only for diagnostics.
            uint32 eligible = 0;
            for (DynamicLightCompat *l : WorldPVS::Instance().State().visibleDynamicLights)
            {
                if (!l || !(l->m_Base.m_dwFlags & FLAG_VISIBLE) ||
                    l->m_fLightRadius <= 0.001f || !std::isfinite(l->m_fLightRadius) ||
                    (l->m_Base.m_dwFlags & FLAG_ONLYLIGHTOBJECTS))
                    continue;
                if (eligible++ == i)
                {
                    src = l;
                    break;
                }
            }
            if (src)
                LOG_SESSION("  DYNAMIC-LIGHT[%u] obj=%p pos=(%.2f %.2f %.2f) radius=%.2f rawRGB=(%u,%u,%u) signedRGB=(%.3f,%.3f,%.3f) flags=%08X flags2=%08X forcedWorld=%d onlyWorld=%d",
                            i, src, src->m_Base.m_vPos.x, src->m_Base.m_vPos.y, src->m_Base.m_vPos.z,
                            src->m_fLightRadius, unsigned(src->m_Base.m_nColorR),
                            unsigned(src->m_Base.m_nColorG), unsigned(src->m_Base.m_nColorB),
                            (2.0f * float(src->m_Base.m_nColorR) - 255.0f) / 255.0f,
                            (2.0f * float(src->m_Base.m_nColorG) - 255.0f) / 255.0f,
                            (2.0f * float(src->m_Base.m_nColorB) - 255.0f) / 255.0f,
                            src->m_Base.m_dwFlags, src->m_Base.m_dwFlags2,
                            (src->m_Base.m_dwFlags2 & FLAG2_FORCEDYNAMICLIGHTWORLD) ? 1 : 0,
                            (src->m_Base.m_dwFlags & FLAG_ONLYLIGHTWORLD) ? 1 : 0);
        }
    }

    return m_state.uploadedCount;
}

void WorldDynamicLightSystem::Disable()
{
    m_state.uploadedCount = 0;
    if (m_state.uDynamicLightCount >= 0)
        GLUniform1i(m_state.uDynamicLightCount, 0);
    if (m_state.ssbo)
        glf.BindBufferBase(GL_SHADER_STORAGE_BUFFER_, 8, m_state.ssbo);
}
