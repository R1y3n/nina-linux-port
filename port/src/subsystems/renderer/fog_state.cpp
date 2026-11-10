#include "fog_state.h"
#include "Console.h"
#include "utils/log.h"
#include <algorithm>

FogState g_fogState{};

void RefreshFogStateFromConsole()
{
    const FogState old = g_fogState;

    // Keep the raw console values around for F10 diagnostics.  This makes it
    // obvious whether a bad fog range originates in Talon/CShell state or in
    // our shader math.
    const float rawEnable = Console::Instance().GetFloat("FogEnable", old.enabled ? 1.0f : 0.0f);
    const float rawR = Console::Instance().GetFloat("FogR", old.r * 255.0f);
    const float rawG = Console::Instance().GetFloat("FogG", old.g * 255.0f);
    const float rawB = Console::Instance().GetFloat("FogB", old.b * 255.0f);
    const float rawNear = Console::Instance().GetFloat("FogNearZ", old.nearZ);
    const float rawFar = Console::Instance().GetFloat("FogFarZ", old.farZ);
    const float rawSkyNear = Console::Instance().GetFloat("SkyFogNearZ", old.skyNearZ);
    const float rawSkyFar = Console::Instance().GetFloat("SkyFogFarZ", old.skyFarZ);
    const float rawVFog = Console::Instance().GetFloat("VFog", old.vFog ? 1.0f : 0.0f);
    const float rawVFogMinY = Console::Instance().GetFloat("VFogMinY", old.vFogMinY);
    const float rawVFogMaxY = Console::Instance().GetFloat("VFogMaxY", old.vFogMaxY);
    const float rawVFogMinYVal = Console::Instance().GetFloat("VFogMinYVal", old.vFogMinYVal);
    const float rawVFogMaxYVal = Console::Instance().GetFloat("VFogMaxYVal", old.vFogMaxYVal);
    const float rawVFogDensity = Console::Instance().GetFloat("VFogDensity", old.vFogDensity);
    const float rawVFogMax = Console::Instance().GetFloat("VFogMax", 120.0f);

    g_fogState.enabled = rawEnable != 0.0f;
    g_fogState.r = std::clamp(rawR / 255.0f, 0.0f, 1.0f);
    g_fogState.g = std::clamp(rawG / 255.0f, 0.0f, 1.0f);
    g_fogState.b = std::clamp(rawB / 255.0f, 0.0f, 1.0f);
    g_fogState.nearZ = rawNear;
    g_fogState.farZ = rawFar;
    g_fogState.skyNearZ = rawSkyNear;
    g_fogState.skyFarZ = rawSkyFar;
    g_fogState.vFog = rawVFog != 0.0f;
    g_fogState.vFogMinY = rawVFogMinY;
    g_fogState.vFogMaxY = rawVFogMaxY;
    // The D3D11 AVP2 renderer mirrors stock Talon here: height values are
    // clamped to normalized factors and VFogMax is an 8-bit fog amount.
    // Passing the raw 0..255 VFogMax directly into the shader is what turns
    // a gentle haze into a fully saturated fog wall.
    g_fogState.vFogMinYVal = std::clamp(rawVFogMinYVal, 0.0f, 1.0f);
    g_fogState.vFogMaxYVal = std::clamp(rawVFogMaxYVal, 0.0f, 1.0f);
    g_fogState.vFogDensity = rawVFogDensity;
    g_fogState.vFogMax = std::clamp(rawVFogMax / 255.0f, 0.0f, 1.0f);

    if (LogIsSessionEnabled())
    {
        static int budget = 20;
        const bool changed = old.enabled != g_fogState.enabled || old.r != g_fogState.r ||
                             old.g != g_fogState.g || old.b != g_fogState.b ||
                             old.nearZ != g_fogState.nearZ || old.farZ != g_fogState.farZ ||
                             old.skyNearZ != g_fogState.skyNearZ || old.skyFarZ != g_fogState.skyFarZ ||
                             old.vFog != g_fogState.vFog ||
                             old.vFogMinY != g_fogState.vFogMinY || old.vFogMaxY != g_fogState.vFogMaxY ||
                             old.vFogMinYVal != g_fogState.vFogMinYVal || old.vFogMaxYVal != g_fogState.vFogMaxYVal ||
                             old.vFogDensity != g_fogState.vFogDensity || old.vFogMax != g_fogState.vFogMax;

        if (LogIsSessionEnabled() && ((changed || budget > 0) && (budget > 0 && budget--)))
        {
            LOG_SESSION("FOG state enabled=%d color=(%.3f %.3f %.3f) near=%.2f far=%.2f skyNear=%.2f skyFar=%.2f vFog=%d vMinY=%.2f vMaxY=%.2f vMinVal=%.4f vMaxVal=%.4f vDensity=%.2f vMax=%.4f",
                        g_fogState.enabled ? 1 : 0, g_fogState.r, g_fogState.g, g_fogState.b,
                        g_fogState.nearZ, g_fogState.farZ, g_fogState.skyNearZ, g_fogState.skyFarZ,
                        g_fogState.vFog ? 1 : 0, g_fogState.vFogMinY, g_fogState.vFogMaxY,
                        g_fogState.vFogMinYVal, g_fogState.vFogMaxYVal, g_fogState.vFogDensity, g_fogState.vFogMax);
        }
    }

    // While F10 logging is active, emit a steady live sample once per second.
    // The existing change/budget logging above is intentionally short-lived;
    // this diagnostic stays useful when the player walks into a problematic
    // fog volume much later in the session.
    if (LogIsSessionEnabled())
    {
        static ULONGLONG s_lastFogLiveLog = 0;
        const ULONGLONG now = GetTickCount64();
        if (!s_lastFogLiveLog || now - s_lastFogLiveLog >= 1000)
        {
            s_lastFogLiveLog = now;
            const float range = g_fogState.farZ - g_fogState.nearZ;
            const float slope = (std::fabs(range) > 0.0001f) ? (1.0f / range) : 0.0f;
            LOG_SESSION("FOG LIVE raw enable=%.3f rgb=(%.2f %.2f %.2f) near=%.3f far=%.3f skyNear=%.3f skyFar=%.3f vFog=%.3f vMinY=%.3f vMaxY=%.3f vMinVal=%.6f vMaxVal=%.6f vDensity=%.3f vMax=%.6f | resolved enabled=%d rgb=(%.4f %.4f %.4f) near=%.3f far=%.3f range=%.3f slope=%.8f skyNear=%.3f skyFar=%.3f vFog=%d vMinY=%.3f vMaxY=%.3f vMinVal=%.6f vMaxVal=%.6f vDensity=%.3f vMax=%.6f",
                        rawEnable, rawR, rawG, rawB, rawNear, rawFar, rawSkyNear, rawSkyFar, rawVFog,
                        rawVFogMinY, rawVFogMaxY, rawVFogMinYVal, rawVFogMaxYVal, rawVFogDensity, rawVFogMax,
                        g_fogState.enabled ? 1 : 0, g_fogState.r, g_fogState.g, g_fogState.b,
                        g_fogState.nearZ, g_fogState.farZ, range, slope,
                        g_fogState.skyNearZ, g_fogState.skyFarZ, g_fogState.vFog ? 1 : 0,
                        g_fogState.vFogMinY, g_fogState.vFogMaxY, g_fogState.vFogMinYVal, g_fogState.vFogMaxYVal,
                        g_fogState.vFogDensity, g_fogState.vFogMax);
        }
    }
}
