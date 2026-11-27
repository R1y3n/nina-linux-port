#pragma once
#include "../../lt_renderer_abi.h"
#include <cstdint>

struct FrameConstantsPerfStats
{
    std::uint64_t applyRequests = 0;
    std::uint64_t uploads = 0;
    std::uint64_t skippedUploads = 0;
};

class FrameConstants final
{
public:
    static FrameConstants &Instance();
    bool Apply(const SceneDesc *scene, float tanHalfFovX, float tanHalfFovY, float nearZ, float farZ);
    bool Apply(const SceneDesc *scene, float nearZ, float farZ);
    void Term();
    void ResetStats() noexcept { m_stats = {}; }
    FrameConstantsPerfStats Stats() const noexcept { return m_stats; }

private:
    struct alignas(16) GpuData
    {
        float projection[4];      // tanHalfX, tanHalfY, nearZ, farZ
        float cameraPos[4];       // xyz, unused
        float cameraQuat[4];      // xyzw
        float fogColorEnabled[4]; // rgb, enabled
        float fogParams[4];       // near, far, frameTime, unused
    };

    bool Ensure();
    unsigned int m_ubo = 0;
    bool m_haveLast = false;
    GpuData m_last{};
    FrameConstantsPerfStats m_stats{};
};
