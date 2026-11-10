#include "subsystems/renderer/Console.h"
#include "stock_render_options.h"
#include "subsystems/renderer/fog_state.h"
#include "utils/log.h"

namespace
{
    static bool ReadEnabled(const char *name)
    {
        return Console::Instance().GetFloat(name, 1.0f) != 0.0f;
    }
}

StockRenderOptions &StockRenderOptions::Instance()
{
    static StockRenderOptions value;
    return value;
}

void StockRenderOptions::Refresh()
{
    const bool oldAll = m_drawAll;
    const bool oldWorld = m_drawWorld;
    const bool oldSky = m_drawSky;
    const bool oldEnableSky = m_enableSky;
    const bool oldTerrain = m_drawTerrainSections;
    const bool oldModels = m_drawModels;
    const bool oldSprites = m_drawSprites;
    const bool oldWorldModels = m_drawWorldModels;
    const bool oldPolyGrids = m_drawPolyGrids;
    const bool oldParticles = m_drawParticles;
    const bool oldLineSystems = m_drawLineSystems;
    const bool oldCanvases = m_drawCanvases;
    const bool oldDynamicLight = m_dynamicLight;

    m_drawAll = ReadEnabled("DrawAll");
    m_drawWorld = ReadEnabled("DrawWorld");
    m_drawSky = ReadEnabled("DrawSky");
    m_enableSky = ReadEnabled("EnableSky");
    m_drawTerrainSections = ReadEnabled("DrawTerrainSections");
    m_drawModels = ReadEnabled("DrawModels");
    m_drawSprites = ReadEnabled("DrawSprites");
    m_drawWorldModels = ReadEnabled("DrawWorldModels");
    m_drawPolyGrids = ReadEnabled("DrawPolyGrids");
    m_drawParticles = ReadEnabled("DrawParticles");
    m_drawLineSystems = ReadEnabled("DrawLineSystems");
    m_drawCanvases = ReadEnabled("DrawCanvases");
    m_dynamicLight = ReadEnabled("DynamicLight");

    if (LogIsSessionEnabled() && (oldAll != m_drawAll || oldWorld != m_drawWorld || oldSky != m_drawSky ||
        oldEnableSky != m_enableSky || oldTerrain != m_drawTerrainSections ||
        oldModels != m_drawModels || oldSprites != m_drawSprites ||
        oldWorldModels != m_drawWorldModels || oldPolyGrids != m_drawPolyGrids ||
        oldParticles != m_drawParticles || oldLineSystems != m_drawLineSystems ||
        oldCanvases != m_drawCanvases || oldDynamicLight != m_dynamicLight))
    {
        LOG_SESSION("D3D-PARITY DRAW-CVARS all=%d world=%d sky=%d enableSky=%d terrain=%d models=%d sprites=%d worldmodels=%d polygrids=%d particles=%d lines=%d canvases=%d dynamicLight=%d",
                    m_drawAll ? 1 : 0, m_drawWorld ? 1 : 0, m_drawSky ? 1 : 0, m_enableSky ? 1 : 0,
                    m_drawTerrainSections ? 1 : 0, m_drawModels ? 1 : 0, m_drawSprites ? 1 : 0,
                    m_drawWorldModels ? 1 : 0, m_drawPolyGrids ? 1 : 0, m_drawParticles ? 1 : 0,
                    m_drawLineSystems ? 1 : 0, m_drawCanvases ? 1 : 0, m_dynamicLight ? 1 : 0);
    }
}
