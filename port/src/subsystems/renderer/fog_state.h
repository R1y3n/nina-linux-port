#pragma once

struct FogState
{
    bool enabled = false;
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float nearZ = 0.0f;
    float farZ = 2000.0f;
    // Talon has a separate linear fog range for the sky render phase.
    // d3d.ren defaults: SkyFogNearZ=0, SkyFogFarZ=2000.
    float skyNearZ = 0.0f;
    float skyFarZ = 2000.0f;
    bool vFog = false;
    // Talon vertical fog parameters.  When VFog is active, stock renderers
    // use these instead of the normal FogNearZ/FogFarZ distance ramp.
    float vFogMinY = 0.0f;
    float vFogMaxY = 1300.0f;
    float vFogMinYVal = 0.5f;
    float vFogMaxYVal = 0.0f;
    float vFogDensity = 1800.0f;
    float vFogMax = 120.0f / 255.0f;
};

extern FogState g_fogState;

void RefreshFogStateFromConsole();
