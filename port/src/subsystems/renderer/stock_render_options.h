#pragma once

class StockRenderOptions
{
public:
    static StockRenderOptions &Instance();

    void Refresh();

    bool DrawAll() const { return m_drawAll; }
    // DrawAll is a stock debug/visibility cvar, not a master renderer enable.
    // Multiplayer commonly leaves DrawAll=0 while the individual draw-class
    // cvars remain enabled.  Gate each renderer path by its own stock cvar.
    bool DrawWorld() const { return m_drawWorld; }
    bool DrawSky() const { return m_drawSky && m_enableSky; }
    bool DrawTerrainSections() const { return m_drawTerrainSections; }
    bool DrawModels() const { return m_drawModels; }
    bool DrawSprites() const { return m_drawSprites; }
    bool DrawWorldModels() const { return m_drawWorldModels; }
    bool DrawPolyGrids() const { return m_drawPolyGrids; }
    bool DrawParticles() const { return m_drawParticles; }
    bool DrawLineSystems() const { return m_drawLineSystems; }
    bool DrawCanvases() const { return m_drawCanvases; }
    bool DynamicLight() const { return m_dynamicLight; }

private:
    bool m_drawAll = true;
    bool m_drawWorld = true;
    bool m_drawSky = true;
    bool m_enableSky = true;
    bool m_drawTerrainSections = true;
    bool m_drawModels = true;
    bool m_drawSprites = true;
    bool m_drawWorldModels = true;
    bool m_drawPolyGrids = true;
    bool m_drawParticles = true;
    bool m_drawLineSystems = true;
    bool m_drawCanvases = true;
    bool m_dynamicLight = true;
};
