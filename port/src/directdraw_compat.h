#pragma once
#include "gl_renderer.h"
#include <ddraw.h>

class DirectDrawCompat final
{
public:
    static DirectDrawCompat &Instance();
    void *GetInterface(const char *query);

private:
    DirectDrawCompat() = default;
};
