#include "cshell_build.h"
#include "utils/log.h"

#include <wincrypt.h>
#include <array>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>

namespace
{
    // Known AVP2 MSP layout/RVAs from the renderer's existing integration.
    // The exact SHA-256 below is the canonical MSP CSHELL fingerprint.
    constexpr CShell::Profile kMSPProfile = {
        CShell::Build::AVP2MSP, "AVP2 MSP", "9ca8f929bcb5a07d296202e7de0cceb673fb2aa5696dd4390f9eda0ea354b7b2",
        0x184828u, 0x0D750u, 0x0D9F0u,
        0x03FC0u, 0x02610u, 0x04480u, 0x03D60u, 0x06BE0u,
        0x03950u, 0x03430u, 0x03DF0u, 0x1842C4u,
        0x4BF90u, 0x4BFC0u, 0x4BF60u,
        0x13EFE0u, 0x13F140u,
        0x03C50u, 0x02AE0u, 0x02AF0u, 0x02AC0u,
        0x026A0u, 0x04FA0u, 0x02160u, 0x055E0u,
        0x36530u, 0x364B0u, 0x246B0u, 0x166485u, 0x18530Cu,
        0x1C7EE8u, 0x1C5388u,
        0xB7Cu, 0xDCu, 0xE0u, 0xECu
    };

    // A profile is selected by exact SHA-256, never by filename/timestamp.
    // Original AVP2 RVAs below were mapped from the canonical base-game DLL using
    // MSVC RTTI/vtables plus direct call/field analysis. Coop remains unmapped.
    constexpr CShell::Profile kOriginalProfile = {
        CShell::Build::AVP2Original, "AVP2 Original", "e4f8fa8e1d0e8f8ba49c3433fbccbb32077255b77b8f5182702de493227c2146",
        0x1957D8u, 0x0D720u, 0x0D940u,
        0x03F80u, 0x025A0u, 0x04440u, 0x03D20u, 0x06C50u,
        0x03910u, 0x033F0u, 0x03DB0u, 0x195274u,
        0x4B360u, 0x4B3B0u, 0x4B320u,
        0x129420u, 0x129580u,
        0x03C10u, 0x02A60u, 0x02A70u, 0x02A40u,
        0x02630u, 0x04F60u, 0x020F0u, 0x05680u,
        0x35A90u, 0x35A10u, 0x23AF0u, 0x173675u, 0x1962B0u,
        0x1E0300u, 0x1DD970u,
        0xB18u, 0xDCu, 0xE0u, 0xECu
    };
    constexpr CShell::Profile kCoopProfile = { CShell::Build::AVP2Coop, "AVP2 Coop", "" };

    constexpr const CShell::Profile *kProfiles[] = { &kOriginalProfile, &kMSPProfile, &kCoopProfile };

    HMODULE g_module = nullptr;
    const CShell::Profile *g_profile = nullptr;
    bool g_hashVerified = false;
    std::string g_sha256;

    void DetectLog(const char *fmt, ...)
    {
        char message[2048]{};
        va_list args;
        va_start(args, fmt);
        _vsnprintf_s(message, sizeof(message), _TRUNCATE, fmt, args);
        va_end(args);

        char debugLine[2140]{};
        _snprintf_s(debugLine, sizeof(debugLine), _TRUNCATE, "AVP2 OpenGL: %s\n", message);
        OutputDebugStringA(debugLine);

        if (LogIsSessionEnabled())
            Log("%s", message);
    }

    bool HashFileSHA256(const char *path, std::string &out)
    {
        out.clear();
        HANDLE file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                  nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
        if (file == INVALID_HANDLE_VALUE)
            return false;

        HCRYPTPROV prov = 0;
        HCRYPTHASH hash = 0;
        bool ok = false;
        if (CryptAcquireContextA(&prov, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT) &&
            CryptCreateHash(prov, CALG_SHA_256, 0, 0, &hash))
        {
            std::array<unsigned char, 64 * 1024> buffer{};
            DWORD got = 0;
            bool readOk = true;
            while (ReadFile(file, buffer.data(), static_cast<DWORD>(buffer.size()), &got, nullptr) && got)
            {
                if (!CryptHashData(hash, buffer.data(), got, 0))
                {
                    readOk = false;
                    break;
                }
            }
            if (readOk)
            {
                BYTE digest[32]{};
                DWORD len = sizeof(digest);
                if (CryptGetHashParam(hash, HP_HASHVAL, digest, &len, 0) && len == sizeof(digest))
                {
                    char text[65]{};
                    for (DWORD i = 0; i < len; ++i)
                        std::sprintf(text + i * 2, "%02x", digest[i]);
                    out.assign(text, 64);
                    ok = true;
                }
            }
        }
        if (hash) CryptDestroyHash(hash);
        if (prov) CryptReleaseContext(prov, 0);
        CloseHandle(file);
        return ok;
    }

    bool HasUsableHash(const CShell::Profile &p)
    {
        return p.sha256 && std::strlen(p.sha256) == 64;
    }

    const CShell::Profile *FindByHash(const std::string &sha)
    {
        for (const auto *p : kProfiles)
            if (HasUsableHash(*p) && _stricmp(p->sha256, sha.c_str()) == 0)
                return p;
        return nullptr;
    }

    bool ValidateMSPBootstrap(HMODULE module)
    {
        if (!module)
            return false;
        auto *base = reinterpret_cast<unsigned char *>(module);
        const auto *dos = reinterpret_cast<const IMAGE_DOS_HEADER *>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew <= 0)
            return false;
        const auto *nt = reinterpret_cast<const IMAGE_NT_HEADERS *>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return false;
        const std::size_t imageSize = nt->OptionalHeader.SizeOfImage;
        const std::size_t need = kMSPProfile.folderDisplayVtableRva + 5u * sizeof(void *);
        if (need > imageSize || kMSPProfile.folderDisplayBuildRva >= imageSize ||
            kMSPProfile.folderDisplayOnCommandRva >= imageSize)
            return false;
        auto **vt = reinterpret_cast<void **>(base + kMSPProfile.folderDisplayVtableRva);
        return vt[4] == base + kMSPProfile.folderDisplayBuildRva &&
               vt[1] == base + kMSPProfile.folderDisplayOnCommandRva;
    }
}

namespace CShell
{
    bool Detect()
    {
        HMODULE module = GetModuleHandleA("CSHELL.DLL");
        if (!module)
            module = GetModuleHandleA("cshell.dll");
        if (!module)
            return false;

        if (g_module == module && g_profile)
            return true;

        Reset();
        g_module = module;

        char path[MAX_PATH]{};
        const DWORD n = GetModuleFileNameA(module, path, MAX_PATH);
        if (!n || n >= MAX_PATH || !HashFileSHA256(path, g_sha256))
        {
            DetectLog("CSHELL detect: failed to SHA-256 loaded module path");
            return false;
        }

        g_profile = FindByHash(g_sha256);
        g_hashVerified = (g_profile != nullptr);

        if (!g_profile && ValidateMSPBootstrap(module))
        {
            g_profile = &kMSPProfile;
            g_hashVerified = false;
            DetectLog("CSHELL detect: bootstrap matched AVP2 MSP layout; SHA256=%s", g_sha256.c_str());
            DetectLog("CSHELL detect: WARNING: MSP matched structural bootstrap but not the canonical MSP SHA-256");
        }
        else if (g_profile)
        {
            DetectLog("CSHELL detect: %s SHA256=%s", g_profile->name, g_sha256.c_str());
        }
        else
        {
            DetectLog("CSHELL detect: unsupported DLL SHA256=%s path='%s'", g_sha256.c_str(), path);
        }
        return g_profile != nullptr;
    }

    void Reset()
    {
        g_module = nullptr;
        g_profile = nullptr;
        g_hashVerified = false;
        g_sha256.clear();
    }

    bool IsSupported() { return g_profile != nullptr && g_profile->folderDisplayVtableRva != 0; }
    bool IsHashVerified() { return g_hashVerified; }
    HMODULE Module() { return g_module; }
    uintptr_t Base() { return reinterpret_cast<uintptr_t>(g_module); }
    Build CurrentBuild() { return g_profile ? g_profile->build : Build::Unknown; }
    const Profile *CurrentProfile() { return g_profile; }
    const char *BuildName() { return g_profile ? g_profile->name : "Unsupported CSHELL"; }
    const char *SHA256() { return g_sha256.c_str(); }
}
