#pragma once

namespace HighRefreshTimingFix
{
    // Installs the high-refresh timing hooks into the stock AVP2 LithTech
    // runtime. Patch sites are validated before writes.
    bool Install();

    // Restores every LithTech/cshell byte/vtable entry patched by this module.
    void Remove();

    // CSHELL and the live ILTServer interface can become available after renderer initialization.
    // Call once per rendered frame; setup checks become cheap after hooks are installed.
    void TickRuntimePatches();

    float GetClientInterpolationAlpha();
    unsigned long long GetClientSimulationSerial();

    // Presentation-only dynamic-object interpolation. The renderer supplies the
    // authoritative transform currently stored on LTObject; this returns a
    // previous/current fixed-tick blend without mutating engine state.
    bool InterpolateObjectTransform(const void *objectKey, unsigned objectId, unsigned objectType,
                                    const float inPos[3], const float inQuat[4],
                                    float outPos[3], float outQuat[4]);

    bool IsInstalled();
}
