#include "shader_resources.h"
#include "utils/log.h"

#include <windows.h>

extern HMODULE g_hModule;

namespace avp2::render
{
    bool ShaderResourceLoader::Load(ShaderResourceId id, std::string &source)
    {
        source.clear();
        if (!g_hModule)
        {
            LOG_SESSION("ShaderResourceLoader: renderer module handle is unavailable");
            return false;
        }

        const int resourceId = static_cast<int>(id);
        HRSRC resource = FindResourceW(g_hModule, MAKEINTRESOURCEW(resourceId), MAKEINTRESOURCEW(10));
        if (!resource)
        {
            LOG_SESSION("ShaderResourceLoader: FindResource failed id=%d error=%lu", resourceId, GetLastError());
            return false;
        }

        const DWORD size = SizeofResource(g_hModule, resource);
        if (size == 0)
        {
            LOG_SESSION("ShaderResourceLoader: resource id=%d is empty", resourceId);
            return false;
        }

        HGLOBAL loaded = LoadResource(g_hModule, resource);
        if (!loaded)
        {
            LOG_SESSION("ShaderResourceLoader: LoadResource failed id=%d error=%lu", resourceId, GetLastError());
            return false;
        }

        const void *data = LockResource(loaded);
        if (!data)
        {
            LOG_SESSION("ShaderResourceLoader: LockResource failed id=%d", resourceId);
            return false;
        }

        source.assign(static_cast<const char *>(data), static_cast<size_t>(size));
        return true;
    }
}
