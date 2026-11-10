#include "memory_utils.h"

#include <algorithm>
#include <limits>

bool MemoryUtils::WriteBytes(void *destination, const void *source, size_t size)
{
    if (!destination || !source || size == 0)
        return false;

    DWORD oldProtect = 0;
    if (!VirtualProtect(destination, size, PAGE_EXECUTE_READWRITE, &oldProtect))
        return false;

    std::memcpy(destination, source, size);

    DWORD ignored = 0;
    VirtualProtect(destination, size, oldProtect, &ignored);
    FlushInstructionCache(GetCurrentProcess(), destination, size);
    return true;
}

bool MemoryUtils::ReadBytes(const void *source, void *destination, size_t size)
{
    if (!source || !destination || size == 0)
        return false;
    if (!IsReadable(reinterpret_cast<uintptr_t>(source)))
        return false;
    std::memcpy(destination, source, size);
    return true;
}

bool MemoryUtils::Nop(uintptr_t address, size_t size)
{
    if (!address || size == 0)
        return false;
    std::vector<uint8_t> bytes(size, 0x90u);
    return WriteBytes(reinterpret_cast<void *>(address), bytes.data(), bytes.size());
}

bool MemoryUtils::IsReadable(uintptr_t address)
{
    if (!address)
        return false;
    MEMORY_BASIC_INFORMATION mbi{};
    if (!VirtualQuery(reinterpret_cast<const void *>(address), &mbi, sizeof(mbi)))
        return false;
    return mbi.State == MEM_COMMIT && !(mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS));
}

bool MemoryUtils::IsExecutable(uintptr_t address)
{
    if (!address)
        return false;
    MEMORY_BASIC_INFORMATION mbi{};
    if (!VirtualQuery(reinterpret_cast<const void *>(address), &mbi, sizeof(mbi)))
        return false;
    if (mbi.State != MEM_COMMIT || (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)))
        return false;
    const DWORD protection = mbi.Protect & 0xFFu;
    return protection == PAGE_EXECUTE || protection == PAGE_EXECUTE_READ ||
           protection == PAGE_EXECUTE_READWRITE || protection == PAGE_EXECUTE_WRITECOPY;
}

uintptr_t MemoryUtils::ReadRelativeTarget(uintptr_t instruction, uint8_t expectedOpcode)
{
    if (!instruction || Read<uint8_t>(instruction) != expectedOpcode)
        return 0;
    const int32_t displacement = Read<int32_t>(instruction + 1u);
    return instruction + 5u + static_cast<intptr_t>(displacement);
}

bool MemoryUtils::WriteRelativeBranch(uintptr_t instruction, uintptr_t target, uint8_t opcode)
{
    if (!instruction || !target || (opcode != 0xE8u && opcode != 0xE9u))
        return false;

    const intptr_t displacement = static_cast<intptr_t>(target) - static_cast<intptr_t>(instruction + 5u);
    if (displacement < std::numeric_limits<int32_t>::min() || displacement > std::numeric_limits<int32_t>::max())
        return false;

    uint8_t bytes[5]{};
    bytes[0] = opcode;
    const int32_t rel32 = static_cast<int32_t>(displacement);
    std::memcpy(bytes + 1, &rel32, sizeof(rel32));
    return WriteBytes(reinterpret_cast<void *>(instruction), bytes, sizeof(bytes));
}

uintptr_t MemoryUtils::CreateTrampoline(uintptr_t source, size_t stolenBytes)
{
    if (!source || stolenBytes < 5u)
        return 0;

    const size_t allocationSize = stolenBytes + 5u;
    auto *trampoline = static_cast<uint8_t *>(VirtualAlloc(nullptr, allocationSize,
                                                           MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
    if (!trampoline)
        return 0;

    std::memcpy(trampoline, reinterpret_cast<const void *>(source), stolenBytes);
    const uintptr_t jumpSite = reinterpret_cast<uintptr_t>(trampoline + stolenBytes);
    if (!WriteRelativeBranch(jumpSite, source + stolenBytes, 0xE9u))
    {
        VirtualFree(trampoline, 0, MEM_RELEASE);
        return 0;
    }

    FlushInstructionCache(GetCurrentProcess(), trampoline, allocationSize);
    return reinterpret_cast<uintptr_t>(trampoline);
}

void MemoryUtils::FreeTrampoline(uintptr_t trampoline)
{
    if (trampoline)
        VirtualFree(reinterpret_cast<void *>(trampoline), 0, MEM_RELEASE);
}
