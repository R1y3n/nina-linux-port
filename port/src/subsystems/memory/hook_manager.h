#pragma once

#include <windows.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>
#include "memory_utils.h"

class HookManager final
{
public:
    HookManager() = delete;

    static bool InstallBytes(const char *name, uintptr_t address, const void *bytes, size_t size);

    static bool InstallNop(const char *name, uintptr_t address, size_t size);

    template <typename T>
    static bool InstallPointer(const char *name, T *slot, T replacement, T *original = nullptr)
    {
        static_assert(std::is_trivially_copyable_v<T>, "HookManager::InstallPointer requires a trivially-copyable pointer-sized type");
        static_assert(sizeof(T) == sizeof(void *), "HookManager::InstallPointer requires a pointer-sized type");
        if (!slot)
            return false;
        const T oldValue = MemoryUtils::Read<T>(slot);
        if (!InstallBytes(name, reinterpret_cast<uintptr_t>(slot), &replacement, sizeof(T)))
            return false;
        if (original)
            *original = oldValue;
        return true;
    }

    static bool InstallCall(const char *name, uintptr_t site, uintptr_t expectedTarget, uintptr_t hook);

    static bool InstallJump(const char *name, uintptr_t site, uintptr_t expectedTarget,
                            uintptr_t hook, size_t overwriteLength = 5u,
                            uintptr_t *trampolineOut = nullptr);

    static bool InstallIAT(const char *name, HMODULE module, const char *importedDll,
                           const char *functionName, void *hook,
                           void **originalOut = nullptr, void ***slotOut = nullptr);

    static bool InstallVTable(const char *name, void *instance, size_t index,
                              void *hook, void **originalOut = nullptr,
                              void ***slotOut = nullptr);

    static bool InstallPointerRaw(const char *name, void **slot, void *replacement,
                                  void **originalOut = nullptr);

    static bool Uninstall(const char *name);

    static void UninstallAll();

    static bool IsInstalled(const char *name);

    static size_t InstalledCount();
};
