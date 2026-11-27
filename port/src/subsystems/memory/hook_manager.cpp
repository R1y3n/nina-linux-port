#include "hook_manager.h"
#include "memory_utils.h"

#include <algorithm>
#include <cstring>
#include <mutex>
#include <vector>

namespace
{
    enum class PatchKind
    {
        Bytes,
        Pointer,
        Jump
    };

    struct PatchRecord
    {
        std::string name;
        PatchKind kind = PatchKind::Bytes;
        uintptr_t address = 0;
        std::vector<uint8_t> originalBytes;
        std::vector<uint8_t> patchedBytes;
        uintptr_t trampoline = 0;
    };

    std::vector<PatchRecord> g_patches;
    std::mutex g_patchMutex;

    PatchRecord *FindRecord(const char *name)
    {
        if (!name)
            return nullptr;
        auto it = std::find_if(g_patches.begin(), g_patches.end(),
                               [name](const PatchRecord &record)
                               { return record.name == name; });
        return it == g_patches.end() ? nullptr : &*it;
    }

    bool SaveAndWrite(const char *name, uintptr_t address, const void *bytes, size_t size,
                      PatchKind kind, uintptr_t trampoline = 0)
    {
        if (!name || !*name || !address || !bytes || size == 0 || FindRecord(name))
            return false;

        PatchRecord record{};
        record.name = name;
        record.kind = kind;
        record.address = address;
        record.trampoline = trampoline;
        record.originalBytes.resize(size);
        record.patchedBytes.resize(size);
        if (!MemoryUtils::ReadBytes(reinterpret_cast<const void *>(address), record.originalBytes.data(), size))
            return false;
        std::memcpy(record.patchedBytes.data(), bytes, size);
        if (!MemoryUtils::WriteBytes(reinterpret_cast<void *>(address), bytes, size))
            return false;
        g_patches.push_back(std::move(record));
        return true;
    }
}

bool HookManager::InstallBytes(const char *name, uintptr_t address, const void *bytes, size_t size)
{
    std::lock_guard<std::mutex> lock(g_patchMutex);
    return SaveAndWrite(name, address, bytes, size, PatchKind::Bytes);
}

bool HookManager::InstallNop(const char *name, uintptr_t address, size_t size)
{
    if (size == 0)
        return false;
    std::vector<uint8_t> bytes(size, 0x90u);
    return InstallBytes(name, address, bytes.data(), bytes.size());
}

bool HookManager::InstallPointerRaw(const char *name, void **slot, void *replacement, void **originalOut)
{
    if (!slot)
        return false;
    std::lock_guard<std::mutex> lock(g_patchMutex);
    if (FindRecord(name))
        return false;
    void *original = *slot;
    if (!SaveAndWrite(name, reinterpret_cast<uintptr_t>(slot), &replacement, sizeof(replacement), PatchKind::Pointer))
        return false;
    if (originalOut)
        *originalOut = original;
    return true;
}

bool HookManager::InstallCall(const char *name, uintptr_t site, uintptr_t expectedTarget, uintptr_t hook)
{
    if (!site || !hook || MemoryUtils::ReadRelativeTarget(site, 0xE8u) != expectedTarget)
        return false;

    const intptr_t displacement = static_cast<intptr_t>(hook) - static_cast<intptr_t>(site + 5u);
    const int32_t rel32 = static_cast<int32_t>(displacement);
    if (static_cast<intptr_t>(rel32) != displacement)
        return false;

    uint8_t bytes[5]{0xE8u, 0, 0, 0, 0};
    std::memcpy(bytes + 1, &rel32, sizeof(rel32));
    std::lock_guard<std::mutex> lock(g_patchMutex);
    return SaveAndWrite(name, site, bytes, sizeof(bytes), PatchKind::Bytes);
}

bool HookManager::InstallJump(const char *name, uintptr_t site, uintptr_t expectedTarget,
                              uintptr_t hook, size_t overwriteLength, uintptr_t *trampolineOut)
{
    if (!site || !hook || overwriteLength < 5u)
        return false;
    if (expectedTarget && MemoryUtils::ReadRelativeTarget(site, 0xE9u) != expectedTarget)
        return false;

    uintptr_t trampoline = 0;
    if (trampolineOut)
    {
        trampoline = MemoryUtils::CreateTrampoline(site, overwriteLength);
        if (!trampoline)
            return false;
    }

    const intptr_t displacement = static_cast<intptr_t>(hook) - static_cast<intptr_t>(site + 5u);
    const int32_t rel32 = static_cast<int32_t>(displacement);
    if (static_cast<intptr_t>(rel32) != displacement)
    {
        MemoryUtils::FreeTrampoline(trampoline);
        return false;
    }

    std::vector<uint8_t> bytes(overwriteLength, 0x90u);
    bytes[0] = 0xE9u;
    std::memcpy(bytes.data() + 1, &rel32, sizeof(rel32));

    std::lock_guard<std::mutex> lock(g_patchMutex);
    if (!SaveAndWrite(name, site, bytes.data(), bytes.size(), PatchKind::Jump, trampoline))
    {
        MemoryUtils::FreeTrampoline(trampoline);
        return false;
    }
    if (trampolineOut)
        *trampolineOut = trampoline;
    return true;
}

bool HookManager::InstallIAT(const char *name, HMODULE module, const char *importedDll,
                             const char *functionName, void *hook,
                             void **originalOut, void ***slotOut)
{
    if (!module || !importedDll || !functionName || !hook)
        return false;

    auto *base = reinterpret_cast<uint8_t *>(module);
    auto *dos = reinterpret_cast<IMAGE_DOS_HEADER *>(base);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        return false;
    auto *nt = reinterpret_cast<IMAGE_NT_HEADERS *>(base + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE)
        return false;

    const auto &directory = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!directory.VirtualAddress)
        return false;

    auto *descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR *>(base + directory.VirtualAddress);
    for (; descriptor->Name; ++descriptor)
    {
        const char *dllName = reinterpret_cast<const char *>(base + descriptor->Name);
        if (_stricmp(dllName, importedDll) != 0)
            continue;

        auto *thunk = reinterpret_cast<IMAGE_THUNK_DATA *>(base + descriptor->FirstThunk);
        auto *originalThunk = descriptor->OriginalFirstThunk
                                  ? reinterpret_cast<IMAGE_THUNK_DATA *>(base + descriptor->OriginalFirstThunk)
                                  : nullptr;
        for (size_t i = 0; thunk[i].u1.Function; ++i)
        {
            if (!originalThunk || IMAGE_SNAP_BY_ORDINAL(originalThunk[i].u1.Ordinal))
                continue;
            auto *import = reinterpret_cast<IMAGE_IMPORT_BY_NAME *>(base + originalThunk[i].u1.AddressOfData);
            if (std::strcmp(reinterpret_cast<const char *>(import->Name), functionName) != 0)
                continue;

            void **slot = reinterpret_cast<void **>(&thunk[i].u1.Function);
            void *original = nullptr;
            if (!InstallPointerRaw(name, slot, hook, &original))
                return false;
            if (originalOut)
                *originalOut = original;
            if (slotOut)
                *slotOut = slot;
            return true;
        }
    }
    return false;
}

bool HookManager::InstallVTable(const char *name, void *instance, size_t index,
                                void *hook, void **originalOut, void ***slotOut)
{
    if (!instance)
        return false;
    void **vtable = *reinterpret_cast<void ***>(instance);
    if (!vtable)
        return false;
    void **slot = &vtable[index];
    if (!InstallPointerRaw(name, slot, hook, originalOut))
        return false;
    if (slotOut)
        *slotOut = slot;
    return true;
}

bool HookManager::Uninstall(const char *name)
{
    if (!name)
        return false;
    std::lock_guard<std::mutex> lock(g_patchMutex);
    auto it = std::find_if(g_patches.begin(), g_patches.end(),
                           [name](const PatchRecord &record)
                           { return record.name == name; });
    if (it == g_patches.end())
        return false;

    std::vector<uint8_t> current(it->patchedBytes.size());
    const bool stillOwned = MemoryUtils::ReadBytes(reinterpret_cast<const void *>(it->address),
                                                   current.data(), current.size()) &&
                            current == it->patchedBytes;
    const bool restored = stillOwned && MemoryUtils::WriteBytes(reinterpret_cast<void *>(it->address),
                                                                it->originalBytes.data(), it->originalBytes.size());
    MemoryUtils::FreeTrampoline(it->trampoline);
    g_patches.erase(it);
    return restored;
}

void HookManager::UninstallAll()
{
    std::lock_guard<std::mutex> lock(g_patchMutex);
    for (auto it = g_patches.rbegin(); it != g_patches.rend(); ++it)
    {
        std::vector<uint8_t> current(it->patchedBytes.size());
        if (MemoryUtils::ReadBytes(reinterpret_cast<const void *>(it->address), current.data(), current.size()) &&
            current == it->patchedBytes)
        {
            MemoryUtils::WriteBytes(reinterpret_cast<void *>(it->address),
                                    it->originalBytes.data(), it->originalBytes.size());
        }
        MemoryUtils::FreeTrampoline(it->trampoline);
    }
    g_patches.clear();
}

bool HookManager::IsInstalled(const char *name)
{
    std::lock_guard<std::mutex> lock(g_patchMutex);
    return FindRecord(name) != nullptr;
}

size_t HookManager::InstalledCount()
{
    std::lock_guard<std::mutex> lock(g_patchMutex);
    return g_patches.size();
}
