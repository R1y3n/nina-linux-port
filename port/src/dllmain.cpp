#include <windows.h>
#include "utils/log.h"

HMODULE g_hModule = nullptr;
static LPTOP_LEVEL_EXCEPTION_FILTER g_prevFilter = nullptr;

static LONG WINAPI RendererUnhandledExceptionFilter(EXCEPTION_POINTERS *ep)
{
    if (LogIsSessionEnabled() && ep && ep->ExceptionRecord)
    {
        LOG_SESSION("UNHANDLED EXCEPTION code=0x%08X address=%p",
                    ep->ExceptionRecord->ExceptionCode,
                    ep->ExceptionRecord->ExceptionAddress);

#if defined(_M_IX86)
        if (ep->ContextRecord)
        {
            CONTEXT *c = ep->ContextRecord;
            LOG_SESSION("CRASH REGISTERS EIP=%08X ESP=%08X EBP=%08X EAX=%08X EBX=%08X ECX=%08X EDX=%08X ESI=%08X EDI=%08X",
                        c->Eip, c->Esp, c->Ebp, c->Eax, c->Ebx, c->Ecx, c->Edx, c->Esi, c->Edi);
        }
#endif

        MEMORY_BASIC_INFORMATION mbi{};
        if (VirtualQuery(ep->ExceptionRecord->ExceptionAddress, &mbi, sizeof(mbi)) == sizeof(mbi))
        {
            char modulePath[MAX_PATH] = {};
            HMODULE faultModule = reinterpret_cast<HMODULE>(mbi.AllocationBase);
            if (GetModuleFileNameA(faultModule, modulePath, MAX_PATH))
            {
                const uintptr_t moduleBase = reinterpret_cast<uintptr_t>(faultModule);
                const uintptr_t faultIP = reinterpret_cast<uintptr_t>(ep->ExceptionRecord->ExceptionAddress);
                LOG_SESSION("FAULT MODULE base=%p offset=0x%08X path=%s",
                            faultModule,
                            static_cast<unsigned int>(faultIP - moduleBase),
                            modulePath);
            }
        }

        if (ep->ExceptionRecord->NumberParameters >= 2 &&
            ep->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
        {
            const ULONG_PTR accessType = ep->ExceptionRecord->ExceptionInformation[0];
            const ULONG_PTR faultAddr = ep->ExceptionRecord->ExceptionInformation[1];
            LOG_SESSION("ACCESS VIOLATION type=%s target=%p",
                        accessType == 0 ? "READ" : (accessType == 1 ? "WRITE" : "EXECUTE"),
                        reinterpret_cast<void *>(faultAddr));
        }
    }
    LogFlushMarker("renderer crash marker");

    if (g_prevFilter)
        return g_prevFilter(ep);

    return EXCEPTION_CONTINUE_SEARCH;
}

#ifdef AVP2_LINUX
static BOOL RendererModuleMain(HINSTANCE instance, DWORD reason, LPVOID);
__attribute__((constructor)) static void RendererSoLoad() { RendererModuleMain(reinterpret_cast<HINSTANCE>(static_cast<uintptr_t>(0x6d300000)), DLL_PROCESS_ATTACH, nullptr); if (getenv("AVP2_OGL_LOG")) LogSetSessionEnabled(true); }
__attribute__((destructor)) static void RendererSoUnload() { RendererModuleMain(nullptr, DLL_PROCESS_DETACH, nullptr); }
static BOOL RendererModuleMain(HINSTANCE instance, DWORD reason, LPVOID)
#else
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID)
#endif
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        g_hModule = instance;
        DisableThreadLibraryCalls(instance);
        LogSetModule(instance);
        g_prevFilter = SetUnhandledExceptionFilter(RendererUnhandledExceptionFilter);
        LogFlushMarker("opengl.ren loaded");
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        LogFlushMarker("opengl.ren unloading");
    }
    return TRUE;
}
