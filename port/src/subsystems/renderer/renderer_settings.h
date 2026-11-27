#pragma once

#include <cstdint>

class RendererSettings final
{
public:
    static RendererSettings &Instance();

    // Loads the 4-byte bitmask from %APPDATA% and applies it to the renderer.
    // If no valid file exists yet, applies defaults (MSAA 4x on; all others off, including 16x anisotropic filtering and high quality light-grid interpolation) and writes them once.
    void LoadAndApply();

    // Called by option setters after their state changes.
    void SaveCurrent();

    bool IsApplying() const { return m_applying; }
    bool IsInitialized() const { return m_initialized; }

private:
    RendererSettings() = default;

    bool BuildSettingsPath(char *outPath, unsigned int outPathBytes) const;
    std::uint32_t CaptureMask() const;
    void ApplyMask(std::uint32_t mask);

    bool m_initialized = false;
    bool m_applying = false;
};
