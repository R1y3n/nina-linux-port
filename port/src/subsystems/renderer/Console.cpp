#include "Console.h"

#include <cstdarg>
#include <cstdio>

Console &Console::Instance()
{
    static Console value;
    return value;
}

HLTPARAM Console::GetParameter(const char *name) const
{
    if (!m_renderStruct || !m_renderStruct->GetParameter || !name || !*name)
        return nullptr;
    return m_renderStruct->GetParameter(const_cast<char *>(name));
}

float Console::GetFloat(const char *name, float fallback) const
{
    if (!m_renderStruct || !m_renderStruct->GetParameterValueFloat)
        return fallback;
    HLTPARAM p = GetParameter(name);
    return p ? m_renderStruct->GetParameterValueFloat(p) : fallback;
}

bool Console::GetBool(const char *name, bool fallback) const
{
    return GetFloat(name, fallback ? 1.0f : 0.0f) != 0.0f;
}

void Console::SetFloat(const char *name, float value) const
{
    if (!name || !*name)
        return;
    char command[256];
    std::snprintf(command, sizeof(command), "%s %.9g", name, static_cast<double>(value));
    Run(command);
}

void Console::SetBool(const char *name, bool value) const
{
    SetFloat(name, value ? 1.0f : 0.0f);
}

void Console::Run(const char *command) const
{
    if (!m_renderStruct || !m_renderStruct->RunConsoleString || !command || !*command)
        return;
    m_renderStruct->RunConsoleString(const_cast<char *>(command));
}

void Console::Print(const char *fmt, ...) const
{
    if (!m_renderStruct || !m_renderStruct->ConsolePrint || !fmt)
        return;

    char text[512];
    va_list args;
    va_start(args, fmt);
    std::vsnprintf(text, sizeof(text), fmt, args);
    va_end(args);
    text[sizeof(text) - 1] = '\0';

    // LT's ConsolePrint is printf-style.  Pass the formatted
    // result as an arg and NOT as a format string so that a '%'
    // produced by our own formatting is not reinterpreted by LT.
    char passthrough[] = "%s";
    m_renderStruct->ConsolePrint(passthrough, text);
}
