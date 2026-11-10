#include "world_renderer.h"

WorldRenderer &WorldRenderer::Instance()
{
    static WorldRenderer v;
    return v;
}
