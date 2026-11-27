#pragma once

#include <windows.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <type_traits>
#include <vector>

class MemoryUtils final
{
public:
    MemoryUtils() = delete;

    template <typename T>
    static T Read(uintptr_t address)
    {
        static_assert(std::is_trivially_copyable_v<T>, "MemoryUtils::Read requires a trivially-copyable type");
        T value{};
        if (address)
            std::memcpy(&value, reinterpret_cast<const void *>(address), sizeof(T));
        return value;
    }

    template <typename T>
    static T Read(const void *address)
    {
        return Read<T>(reinterpret_cast<uintptr_t>(address));
    }

    template <typename T>
    static bool Write(uintptr_t address, const T &value)
    {
        static_assert(std::is_trivially_copyable_v<T>, "MemoryUtils::Write requires a trivially-copyable type");
        return WriteBytes(reinterpret_cast<void *>(address), &value, sizeof(T));
    }

    template <typename T>
    static bool Write(void *address, const T &value)
    {
        return Write<T>(reinterpret_cast<uintptr_t>(address), value);
    }

    static uintptr_t ResolvePointer(uintptr_t base, std::initializer_list<uintptr_t> offsets)
    {
        if (!base)
            return 0;
        uintptr_t current = base;
        size_t index = 0;
        for (const uintptr_t offset : offsets)
        {
            current += offset;
            ++index;
            if (index < offsets.size())
            {
                current = Read<uintptr_t>(current);
                if (!current)
                    return 0;
            }
        }
        return current;
    }

    template <typename Container>
    static uintptr_t ResolvePointer(uintptr_t base, const Container &offsets)
    {
        if (!base)
            return 0;
        uintptr_t current = base;
        auto it = offsets.begin();
        const auto end = offsets.end();
        while (it != end)
        {
            current += static_cast<uintptr_t>(*it);
            ++it;
            if (it != end)
            {
                current = Read<uintptr_t>(current);
                if (!current)
                    return 0;
            }
        }
        return current;
    }

    template <typename T>
    static T ReadDeep(uintptr_t base, std::initializer_list<uintptr_t> offsets)
    {
        const uintptr_t address = ResolvePointer(base, offsets);
        return address ? Read<T>(address) : T{};
    }

    template <typename T>
    static bool WriteDeep(uintptr_t base, std::initializer_list<uintptr_t> offsets, const T &value)
    {
        const uintptr_t address = ResolvePointer(base, offsets);
        return address && Write<T>(address, value);
    }

    template <typename T, typename Container>
    static T ReadDeep(uintptr_t base, const Container &offsets)
    {
        const uintptr_t address = ResolvePointer(base, offsets);
        return address ? Read<T>(address) : T{};
    }

    template <typename T, typename Container>
    static bool WriteDeep(uintptr_t base, const Container &offsets, const T &value)
    {
        const uintptr_t address = ResolvePointer(base, offsets);
        return address && Write<T>(address, value);
    }

    static uintptr_t ModuleAddress(HMODULE module, uintptr_t rva)
    {
        return module ? reinterpret_cast<uintptr_t>(module) + rva : 0;
    }

    static bool WriteBytes(void *destination, const void *source, size_t size);

    static bool ReadBytes(const void *source, void *destination, size_t size);

    static bool Nop(uintptr_t address, size_t size);

    static bool IsReadable(uintptr_t address);

    static bool IsExecutable(uintptr_t address);

    static uintptr_t ReadRelativeTarget(uintptr_t instruction, uint8_t expectedOpcode);

    static uintptr_t ReadRelativeTarget(const void *instruction, uint8_t expectedOpcode)
    {
        return ReadRelativeTarget(reinterpret_cast<uintptr_t>(instruction), expectedOpcode);
    }

    static bool WriteRelativeBranch(uintptr_t instruction, uintptr_t target, uint8_t opcode);

    static bool WriteRelativeBranch(void *instruction, uintptr_t target, uint8_t opcode)
    {
        return WriteRelativeBranch(reinterpret_cast<uintptr_t>(instruction), target, opcode);
    }

    static uintptr_t CreateTrampoline(uintptr_t source, size_t stolenBytes);

    static void FreeTrampoline(uintptr_t trampoline);
};
