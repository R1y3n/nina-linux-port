#pragma once
#include "lt_renderer_abi.h"
#include <windows.h>
#include <vector>
#include <cstdint>

struct GLSurface
{
    int width = 0;
    int height = 0;
    int pitch = 0;
    std::vector<uint8_t> pixels;

    unsigned int texture = 0;
    bool textureAllocated = false;
    bool dirty = true;
    bool locked = false;
    bool optimized = false;
    uint32 transparentColor = 0xFFFFFFFFu;
};
