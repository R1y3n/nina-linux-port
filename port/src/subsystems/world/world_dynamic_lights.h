#pragma once
#include "world_render_types.h"
#include <GL/gl.h>

namespace avp2::render
{
    class Shader;
}

struct WorldDynamicLightState
{
    GLuint ssbo = 0;
    GLint uDynamicLightCount = -1;
    uint32 uploadedCount = 0;
};

class WorldDynamicLightSystem final
{
public:
    static WorldDynamicLightSystem &Instance();
    bool Init(avp2::render::Shader *shader);
    void Term();
    uint32 UploadVisible();
    void Disable();
    uint32 UploadedCount() const { return m_state.uploadedCount; }

private:
    WorldDynamicLightSystem() = default;
    WorldDynamicLightState m_state{};
};
