#pragma once
#include "../../lt_renderer_abi.h"
#include <GL/gl.h>

namespace avp2::render
{
    class Shader;
}

struct SpriteRendererState
{
    avp2::render::Shader *shader = nullptr;
    GLuint vao = 0;
    GLuint vbo = 0;

    GLint uTanHalfFovX = -1;
    GLint uTanHalfFovY = -1;
    GLint uNearZ = -1;
    GLint uFarZ = -1;
    GLint uUseColorKey = -1;
    GLint uColorKey = -1;
    GLint uAlphaTest = -1;
    GLint uAlphaRef = -1;
    GLint uAlphaFunc = -1;
    GLint uMode = -1;
    GLint uModeColor = -1;
    GLint uFogEnabled = -1;
    GLint uFogColor = -1;
    GLint uFogNear = -1;
    GLint uFogFar = -1;

    uint64_t spriteCount = 0;
    uint64_t triCount = 0;
};

class SpriteRenderer final
{
public:
    static SpriteRenderer &Instance();
    bool Init();
    void Term();
    bool Render(SceneDesc *scene, SpriteInstanceCompat *sprite);
    void ResetStats();
    void GetStats(uint64_t &sprites, uint64_t &tris) const;

    // Internal subsystem bridge used by the split sprite implementation files.
    // State ownership stays here; callers outside the sprite subsystem should
    // use the public renderer methods above.
    SpriteRendererState &State() { return m_state; }
    const SpriteRendererState &State() const { return m_state; }

private:
    SpriteRenderer() = default;
    SpriteRendererState m_state{};
};
