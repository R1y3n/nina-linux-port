#pragma once

#include "../../lt_renderer_abi.h"

class Console final
{
public:
    static Console &Instance();

    void SetRenderStruct(RenderStruct *rs) { m_renderStruct = rs; }
    RenderStruct *GetRenderStruct() const { return m_renderStruct; }

    HLTPARAM GetParameter(const char *name) const;
    float GetFloat(const char *name, float fallback = 0.0f) const;
    bool GetBool(const char *name, bool fallback = false) const;
    void SetFloat(const char *name, float value) const;
    void SetBool(const char *name, bool value) const;
    void Run(const char *command) const;
    void Print(const char *fmt, ...) const;

private:
    Console() = default;
    RenderStruct *m_renderStruct = nullptr;
};
