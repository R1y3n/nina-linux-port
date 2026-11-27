#pragma once
#include "../../lt_renderer_abi.h"

class WorldVisibilitySystem final
{
public:
    uint32 GetTranslucentWorldModelCount() const;
    WorldModelInstanceCompat *GetTranslucentWorldModel(uint32 index) const;
};
