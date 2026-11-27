#include "material_authoring.h"
#include "../../gl_loader.h"
#include "../renderer/gl_state_cache.h"
#include "../renderer/Console.h"
#include "../textures/texture_manager.h"
#include "../cshell/cshell_build.h"
#include "../renderer/renderer_core.h"
#include "utils/log.h"

#include <windows.h>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <cstring>

namespace fs = std::filesystem;

namespace
{
    struct MaterialRecord
    {
        AuthoredMaterialBinding binding;
        fs::path normalPath;
        fs::path specularPath;
        fs::path reflectionPath;
        bool ownNormalTexture = false;
        bool ownSpecularTexture = false;
        bool ownReflectionTexture = false;
        bool materialExists = false; // loose or mounted/REZ
        bool loaded = false;
    };

    std::unordered_map<std::string, MaterialRecord> g_materials;
    // Hot-path cache: world rendering already gives us the same SharedTexture*
    // repeatedly.  Resolve the resource name once, then go straight to the
    // material record on subsequent draws.  MaterialRecord addresses remain
    // stable across unordered_map rehashes (references/pointers to elements are
    // not invalidated by rehash).
    std::unordered_map<SharedTexture *, MaterialRecord *> g_sharedTextureCache;
    MaterialAuthoringPerfStats g_perf{};

    static int64_t PerfNow()
    {
        if (!RendererCore::Instance().PerfTimingActive()) return 0;
        LARGE_INTEGER q{}; QueryPerformanceCounter(&q); return q.QuadPart;
    }
    static double PerfMs(int64_t a, int64_t b)
    {
        if (!a || !b || b <= a) return 0.0;
        static LARGE_INTEGER f = []{ LARGE_INTEGER v{}; QueryPerformanceFrequency(&v); return v; }();
        return f.QuadPart ? (1000.0 * double(b-a) / double(f.QuadPart)) : 0.0;
    }

    static std::string Lower(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return char(std::tolower(c)); });
        return s;
    }

    static std::string Trim(std::string s)
    {
        const auto notSpace=[](unsigned char c){ return !std::isspace(c); };
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
        s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
        return s;
    }

    static fs::path RootPath()
    {
        // AVP2 normally runs with the game directory as CWD. Keep the material
        // tree deliberately renderer-local and loose-file first.
        std::error_code ec;
        fs::path p = fs::current_path(ec);
        if (ec) p = fs::path(".");
        return p / "textures";
    }

    static bool ReadableRange(const void *p, size_t bytes)
    {
        if (!p || !bytes) return false;
        MEMORY_BASIC_INFORMATION mbi{};
        if (!VirtualQuery(p, &mbi, sizeof(mbi))) return false;
        if (mbi.State != MEM_COMMIT || (mbi.Protect & (PAGE_NOACCESS|PAGE_GUARD))) return false;
        const uintptr_t start = reinterpret_cast<uintptr_t>(p);
        const uintptr_t end = start + bytes;
        const uintptr_t regionEnd = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
        return end >= start && end <= regionEnd;
    }

    static std::string SharedTextureFilename(SharedTexture *shared)
    {
        if (!shared) return {};
        auto *st = reinterpret_cast<SharedTextureCompat *>(shared);
        if (!ReadableRange(st, sizeof(*st)) || !st->m_pFile) return {};
        auto *fi = reinterpret_cast<FileIdentifierCompat *>(st->m_pFile);
        if (!ReadableRange(fi, sizeof(*fi)) || !fi->m_pFilename) return {};

        // Validate the filename pointer once.  The old implementation called
        // VirtualQuery for every single character, which made Resolve() cost
        // tens of milliseconds when invoked for every material draw.
        MEMORY_BASIC_INFORMATION mbi{};
        const char *filename = fi->m_pFilename;
        if (!VirtualQuery(filename, &mbi, sizeof(mbi))) return {};
        if (mbi.State != MEM_COMMIT || (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))) return {};

        const uintptr_t start = reinterpret_cast<uintptr_t>(filename);
        const uintptr_t regionEnd = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
        if (regionEnd <= start) return {};
        const size_t maxLen = std::min<size_t>(1024, static_cast<size_t>(regionEnd - start));

        size_t len = 0;
        for (; len < maxLen; ++len)
        {
            const unsigned char c = static_cast<unsigned char>(filename[len]);
            if (!c) break;
            if (c < 0x20) return {};
        }
        if (len == 0 || len == maxLen) return {};

        std::string name(filename, len);
        std::replace(name.begin(), name.end(), '\\', '/');
        return name;
    }

    static fs::path RelativeBasePath(const std::string &source)
    {
        fs::path p(source);
        if (p.is_absolute()) p = p.filename();
        p.replace_extension();
        // Avoid ./textures/textures/... when an identifier already starts there.
        auto it=p.begin();
        if (it!=p.end() && Lower(it->string())=="textures")
        {
            fs::path q;
            ++it;
            for (;it!=p.end();++it) q /= *it;
            p=q;
        }
        return p;
    }

    static bool EndsWithI(const std::string &s, const char *suffix)
    {
        const std::string a=Lower(s), b=Lower(suffix);
        return a.size()>=b.size() && a.compare(a.size()-b.size(), b.size(), b)==0;
    }

    static void ClampSettings(AuthoredMaterialSettings &s)
    {
        s.normalStrength=std::clamp(s.normalStrength,0.0f,8.0f);
        s.specularStrength=std::clamp(s.specularStrength,0.0f,8.0f);
        s.glossMinPower=std::clamp(s.glossMinPower,1.0f,1024.0f);
        s.glossMaxPower=std::clamp(s.glossMaxPower,s.glossMinPower,2048.0f);
        s.glossBias=std::clamp(s.glossBias,-1.0f,1.0f);
        s.reflectionStrength=std::clamp(s.reflectionStrength,0.0f,1.0f);
    }

    static bool ParseSettingsText(const std::string &text, AuthoredMaterialSettings &s)
    {
        std::istringstream f(text);
        std::string line;
        bool sawSetting=false;
        while (std::getline(f,line))
        {
            const auto hash=line.find_first_of("#;");
            if (hash!=std::string::npos) line.resize(hash);
            const auto eq=line.find('=');
            if (eq==std::string::npos) continue;
            const std::string k=Lower(Trim(line.substr(0,eq)));
            const std::string v=Trim(line.substr(eq+1));
            try
            {
                if(k=="normal_strength") { s.normalStrength=std::stof(v); sawSetting=true; }
                else if(k=="specular_strength") { s.specularStrength=std::stof(v); sawSetting=true; }
                else if(k=="gloss_min_power") { s.glossMinPower=std::stof(v); sawSetting=true; }
                else if(k=="gloss_max_power") { s.glossMaxPower=std::stof(v); sawSetting=true; }
                else if(k=="gloss_bias") { s.glossBias=std::stof(v); sawSetting=true; }
                else if(k=="reflection_strength") { s.reflectionStrength=std::stof(v); sawSetting=true; }
                else if(k=="reflection_map") { s.reflectionMap=v; sawSetting=true; }
            }
            catch (...) {}
        }
        ClampSettings(s);
        return sawSetting;
    }

    static bool LoadSettings(const fs::path &path, AuthoredMaterialSettings &s)
    {
        std::ifstream f(path);
        if (!f) return false;
        std::ostringstream text;
        text << f.rdbuf();
        return ParseSettingsText(text.str(),s);
    }

    // ILTCSBase::OpenFile is virtual slot 42 in the AVP2/LithTech Talon SDK ABI.
    // It resolves through LithTech's mounted search path (REZ + loose resources).
    static bool ReadMountedResource(const std::string &resourceName, std::vector<uint8> &out)
    {
        out.clear();
        if (!CShell::CurrentProfile() && !CShell::Detect())
            return false;
        const CShell::Profile *profile=CShell::CurrentProfile();
        if(!profile || !profile->ltClientGlobalRva || !CShell::Base())
            return false;

        void *client=*reinterpret_cast<void **>(CShell::Base()+profile->ltClientGlobalRva);
        if(!client) return false;
        void **vt=*reinterpret_cast<void ***>(client);
        if(!vt) return false;

        using OpenFileFn=int (__thiscall *)(void *, char *, void **);
        auto openFile=reinterpret_cast<OpenFileFn>(vt[42]);
        if(!openFile) return false;

        std::string native=resourceName;
        std::replace(native.begin(),native.end(),'/', '\\');
        void *stream=nullptr;
        if(openFile(client,native.empty() ? nullptr : &native[0],&stream)!=0 || !stream)
            return false;

        // ILTStream has a virtual destructor at slot 0, then Release/Read/... .
        void **svt=*reinterpret_cast<void ***>(stream);
        using ReleaseFn=void (__thiscall *)(void *);
        using ReadFn=int (__thiscall *)(void *, void *, unsigned long);
        using GetLenFn=int (__thiscall *)(void *, unsigned long *);
        auto release=reinterpret_cast<ReleaseFn>(svt[1]);
        auto read=reinterpret_cast<ReadFn>(svt[2]);
        auto getLen=reinterpret_cast<GetLenFn>(svt[7]);

        unsigned long len=0;
        bool ok=false;
        if(read && getLen && getLen(stream,&len)==0 && len>0 && len <= 16u*1024u*1024u)
        {
            out.resize(len);
            ok=(read(stream,out.data(),len)==0);
            if(!ok) out.clear();
        }
        if(release) release(stream);
        return ok;
    }

    static bool LoadSettingsMounted(const std::string &resourceName, AuthoredMaterialSettings &s)
    {
        std::vector<uint8> bytes;
        if(!ReadMountedResource(resourceName,bytes)) return false;
        std::string text(reinterpret_cast<const char *>(bytes.data()),bytes.size());
        if(!ParseSettingsText(text,s)) return false;
        LOG_SESSION("Material REZ/mounted .mat loaded '%s' bytes=%u",resourceName.c_str(),static_cast<unsigned>(bytes.size()));
        return true;
    }

    static bool SaveSettings(const fs::path &path, const AuthoredMaterialSettings &s)
    {
        std::error_code ec;
        fs::create_directories(path.parent_path(),ec);
        std::ofstream f(path,std::ios::trunc);
        if(!f) return false;
        f << "# AVP2 OpenGL material v1\n";
        f << "normal_strength=" << s.normalStrength << "\n";
        f << "specular_strength=" << s.specularStrength << "\n";
        f << "gloss_min_power=" << s.glossMinPower << "\n";
        f << "gloss_max_power=" << s.glossMaxPower << "\n";
        f << "gloss_bias=" << s.glossBias << "\n";
        f << "reflection_strength=" << s.reflectionStrength << "\n";
        f << "reflection_map=" << s.reflectionMap << "\n";
        return true;
    }

    static GLenum DtxInternal(uint32 bpp)
    {
        switch(bpp)
        {
            case BPP_S3TC_DXT1: return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT_;
            case BPP_S3TC_DXT3: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT_;
            case BPP_S3TC_DXT5: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT_;
            case BPP_32: case BPP_24: return GL_RGBA8_;
            default: return 0;
        }
    }

    static size_t DtxMipBytes(uint32 bpp,uint32 w,uint32 h)
    {
        if(bpp==BPP_S3TC_DXT1 || bpp==BPP_S3TC_DXT3 || bpp==BPP_S3TC_DXT5)
        {
            const uint32 block=(bpp==BPP_S3TC_DXT1)?8u:16u;
            return size_t(std::max(1u,(w+3)/4))*std::max(1u,(h+3)/4)*block;
        }
        if(bpp==BPP_32) return size_t(w)*h*4;
        if(bpp==BPP_24) return size_t(w)*h*3;
        return 0;
    }

    static GLuint LoadLooseDtx(const fs::path &path)
    {
        std::ifstream f(path,std::ios::binary);
        if(!f) return 0;
        f.seekg(0,std::ios::end); const std::streamoff n=f.tellg(); f.seekg(0);
        if(n < std::streamoff(sizeof(DtxHeaderCompat))) return 0;
        std::vector<uint8> data(static_cast<size_t>(n));
        f.read(reinterpret_cast<char*>(data.data()),n);
        if(!f) return 0;
        DtxHeaderCompat h{}; std::memcpy(&h,data.data(),sizeof(h));
        const uint32 bpp=h.GetBPPIdent(); const GLenum internal=DtxInternal(bpp);
        const uint32 w0=h.m_wBaseWidth, h0=h.m_wBaseHeight;
        const uint32 mips=std::clamp<uint32>(h.m_wMipmaps? h.m_wMipmaps:1u,1u,16u);
        if(!internal || !w0 || !h0 || w0>16384 || h0>16384) return 0;
        GLuint tex=0; glf.CreateTextures(GL_TEXTURE_2D_,1,&tex); if(!tex) return 0;
        glf.TextureStorage2D(tex,GLsizei(mips),internal,GLsizei(w0),GLsizei(h0));
        size_t off=sizeof(DtxHeaderCompat);
        for(uint32 mip=0;mip<mips;++mip)
        {
            const uint32 w=std::max(1u,w0>>mip), hh=std::max(1u,h0>>mip);
            const size_t bytes=DtxMipBytes(bpp,w,hh);
            if(!bytes || off+bytes>data.size()){ GLStateDeleteTextures(1,&tex); return 0; }
            const void *src=data.data()+off;
            if(bpp==BPP_S3TC_DXT1 || bpp==BPP_S3TC_DXT3 || bpp==BPP_S3TC_DXT5)
                glf.CompressedTextureSubImage2D(tex,GLint(mip),0,0,GLsizei(w),GLsizei(hh),internal,GLsizei(bytes),src);
            else if(bpp==BPP_32)
            {
                glPixelStorei(GL_UNPACK_ALIGNMENT,1);
                glf.TextureSubImage2D(tex,GLint(mip),0,0,GLsizei(w),GLsizei(hh),GL_BGRA_,GL_UNSIGNED_BYTE,src);
            }
            else
            {
                // DTX 24-bit payload is BGR. Convert to RGBA to keep upload simple.
                std::vector<uint8> rgba(size_t(w)*hh*4);
                const uint8 *s=(const uint8*)src;
                for(size_t i=0;i<size_t(w)*hh;++i){ rgba[i*4+0]=s[i*3+2]; rgba[i*4+1]=s[i*3+1]; rgba[i*4+2]=s[i*3+0]; rgba[i*4+3]=255; }
                glf.TextureSubImage2D(tex,GLint(mip),0,0,GLsizei(w),GLsizei(hh),GL_RGBA,GL_UNSIGNED_BYTE,rgba.data());
            }
            off+=bytes;
        }
        glf.TextureParameteri(tex,GL_TEXTURE_WRAP_S_,GL_REPEAT);
        glf.TextureParameteri(tex,GL_TEXTURE_WRAP_T_,GL_REPEAT);
        glf.TextureParameteri(tex,GL_TEXTURE_MAG_FILTER_,GL_LINEAR_);
        glf.TextureParameteri(tex,GL_TEXTURE_MIN_FILTER_,mips>1?0x2703:GL_LINEAR_);
        LOG_SESSION("Material loose DTX loaded '%s' GL=%u %ux%u mips=%u bpp=%u",path.string().c_str(),tex,w0,h0,mips,bpp);
        return tex;
    }

    static GLuint LoadMountedDtx(const std::string &resourceName)
    {
        RenderStruct *rs=TextureManager::Instance().State().renderStruct;
        if(!rs || !rs->GetSharedTexture) return 0;
        std::string native=resourceName;
        std::replace(native.begin(),native.end(),'/', '\\');
        SharedTexture *shared=rs->GetSharedTexture(native.c_str());
        if(!shared) return 0;
        Texture *tex=TextureManager::Instance().GetOrEnsure(shared);
        if(!tex || !tex->texture) return 0;
        LOG_SESSION("Material REZ/mounted DTX loaded '%s' shared=%p GL=%u",resourceName.c_str(),shared,tex->texture);
        return tex->texture;
    }

    static GLuint LoadCompanionDtx(const fs::path &loosePath, const std::string &resourceName, bool &owned)
    {
        owned=false;
        if(fs::exists(loosePath))
        {
            GLuint id=LoadLooseDtx(loosePath);
            if(id){ owned=true; return id; }
        }

        // Support material-pack REZs authored either at resource root or beneath
        // a top-level "textures" folder. Loose ./textures always wins above.
        GLuint id=LoadMountedDtx(resourceName);
        if(id) return id;
        return LoadMountedDtx(std::string("textures/")+resourceName);
    }

    static void DestroyRecordTextures(MaterialRecord &r)
    {
        if(r.ownNormalTexture && r.binding.normalTexture) GLStateDeleteTextures(1,&r.binding.normalTexture);
        if(r.ownSpecularTexture && r.binding.specularTexture) GLStateDeleteTextures(1,&r.binding.specularTexture);
        if(r.ownReflectionTexture && r.binding.reflectionTexture) GLStateDeleteTextures(1,&r.binding.reflectionTexture);
        r.binding.albedoTexture=r.binding.normalTexture=r.binding.specularTexture=r.binding.reflectionTexture=0;
        r.binding.materialFileExists=false;
        r.ownNormalTexture=r.ownSpecularTexture=r.ownReflectionTexture=false;
        r.materialExists=false;
        r.loaded=false;
    }

    static void LoadRecord(MaterialRecord &r)
    {
        if(r.loaded) return;
        r.loaded=true;

        const fs::path rel=RelativeBasePath(r.binding.sourceTexture);
        const std::string baseResource=rel.generic_string();
        const std::string normalResource=baseResource+"_n.dtx";
        const std::string specularResource=baseResource+"_s.dtx";
        const std::string matResource=baseResource+".mat";

        AuthoredMaterialSettings s{};
        bool haveMat=LoadSettings(r.binding.matPath,s);
        if(!haveMat)
        {
            haveMat=LoadSettingsMounted(matResource,s);
            if(!haveMat) haveMat=LoadSettingsMounted(std::string("textures/")+matResource,s);
        }
        r.materialExists=haveMat;
        r.binding.materialFileExists=haveMat;
        r.binding.settings=s;

        r.binding.normalTexture=LoadCompanionDtx(r.normalPath,normalResource,r.ownNormalTexture);
        r.binding.specularTexture=LoadCompanionDtx(r.specularPath,specularResource,r.ownSpecularTexture);

        if(!s.reflectionMap.empty())
        {
            fs::path relReflection=s.reflectionMap;
            std::string reflectionResource=relReflection.generic_string();
            if(Lower(reflectionResource).rfind("textures/",0)==0)
                reflectionResource=reflectionResource.substr(9);
            fs::path p=relReflection;
            if(p.is_relative()) p=RootPath()/p;
            r.reflectionPath=p;
            r.binding.reflectionTexture=LoadCompanionDtx(p,reflectionResource,r.ownReflectionTexture);
        }
        r.binding.valid = r.binding.normalTexture || r.binding.specularTexture || r.binding.reflectionTexture || r.materialExists;
    }
}

MaterialAuthoringSystem &MaterialAuthoringSystem::Instance(){ static MaterialAuthoringSystem s; return s; }

const AuthoredMaterialBinding *MaterialAuthoringSystem::Resolve(SharedTexture *baseTexture)
{
    const bool prof = RendererCore::Instance().PerfTimingActive();
    const int64_t t0 = prof ? PerfNow() : 0;
    if (prof) ++g_perf.resolveCalls;
    if (!baseTexture)
    {
        if (prof) g_perf.resolveMs += PerfMs(t0, PerfNow());
        return nullptr;
    }

    // Normal rendering hits the same SharedTexture pointers over and over.
    // Bypass resource-name extraction, path construction, and string hashing
    // completely after the first encounter.
    const int64_t tl0 = prof ? PerfNow() : 0;
    auto cached = g_sharedTextureCache.find(baseTexture);
    if (cached != g_sharedTextureCache.end())
    {
        MaterialRecord *record = cached->second;
        if (prof)
        {
            ++g_perf.cacheHits;
            g_perf.lookupMs += PerfMs(tl0, PerfNow());
            g_perf.resolveMs += PerfMs(t0, PerfNow());
        }
        return (record && record->binding.valid) ? &record->binding : nullptr;
    }
    if (prof) g_perf.lookupMs += PerfMs(tl0, PerfNow());

    const int64_t tn0 = prof ? PerfNow() : 0;
    const std::string source = SharedTextureFilename(baseTexture);
    const int64_t tn1 = prof ? PerfNow() : 0;
    if (prof) g_perf.nameMs += PerfMs(tn0, tn1);
    if (source.empty())
    {
        if (prof) g_perf.resolveMs += PerfMs(t0, PerfNow());
        return nullptr;
    }

    const int64_t tk0 = prof ? PerfNow() : 0;
    const fs::path rel = RelativeBasePath(source);
    if (rel.empty())
    {
        if (prof)
        {
            g_perf.lookupMs += PerfMs(tk0, PerfNow());
            g_perf.resolveMs += PerfMs(t0, PerfNow());
        }
        return nullptr;
    }

    const std::string key = Lower(rel.generic_string());
    auto it = g_materials.find(key);
    if (it == g_materials.end())
    {
        MaterialRecord r{};
        r.binding.key = key;
        r.binding.sourceTexture = source;
        fs::path base = RootPath() / rel;
        r.normalPath = fs::path(base.string() + "_n.dtx");
        r.specularPath = fs::path(base.string() + "_s.dtx");
        r.binding.matPath = fs::path(base.string() + ".mat").string();
        it = g_materials.emplace(key, std::move(r)).first;
    }
    MaterialRecord *record = &it->second;
    g_sharedTextureCache.emplace(baseTexture, record);

    Texture *base = TextureManager::Instance().GetOrEnsure(baseTexture);
    record->binding.albedoTexture = (base && base->texture) ? base->texture : 0;

    if (prof) g_perf.lookupMs += PerfMs(tk0, PerfNow());

    const bool wasLoaded = record->loaded;
    const int64_t td0 = prof ? PerfNow() : 0;
    LoadRecord(*record);
    const int64_t td1 = prof ? PerfNow() : 0;
    if (prof)
    {
        g_perf.loadMs += PerfMs(td0, td1);
        if (!wasLoaded && record->loaded) ++g_perf.recordsLoaded;
        g_perf.resolveMs += PerfMs(t0, td1);
    }
    return record->binding.valid ? &record->binding : nullptr;
}

MaterialAuthoringPerfStats MaterialAuthoringSystem::ConsumePerfStats()
{
    MaterialAuthoringPerfStats out = g_perf;
    g_perf = {};
    return out;
}

void MaterialAuthoringSystem::Reset()
{
    for (auto &kv : g_materials) DestroyRecordTextures(kv.second);
    g_sharedTextureCache.clear();
    g_materials.clear();
}
void MaterialAuthoringSystem::ReloadAll(){ for(auto &kv:g_materials){ DestroyRecordTextures(kv.second); LoadRecord(kv.second); } }

int MaterialAuthoringSystem::CreateMissingMaterialFilesForActiveMap()
{
    int made = 0;
    for (auto &kv : g_materials)
    {
        MaterialRecord &r = kv.second;
        const fs::path matPath = r.binding.matPath;
        if (matPath.empty() || fs::exists(matPath) || r.materialExists)
            continue;

        if (SaveSettings(matPath, AuthoredMaterialSettings{}))
        {
            ++made;
            // The record may have been resolved before the file existed. Load it
            // again so the editor immediately reflects the newly-created .mat.
            DestroyRecordTextures(r);
            LoadRecord(r);
        }
    }

    LOG_SESSION("Material authoring active-map .mat generation materials=%u created=%d",
                static_cast<unsigned>(g_materials.size()), made);
    return made;
}

std::vector<std::string> MaterialAuthoringSystem::MaterialKeys() const
{
    std::vector<std::string> v; v.reserve(g_materials.size()); for(const auto &kv:g_materials) v.push_back(kv.first); std::sort(v.begin(),v.end()); return v;
}

bool MaterialAuthoringSystem::GetSettings(const std::string &key,AuthoredMaterialSettings &out) const
{
    auto it=g_materials.find(Lower(key)); if(it==g_materials.end()) return false; out=it->second.binding.settings; return true;
}

bool MaterialAuthoringSystem::GetBinding(const std::string &key,AuthoredMaterialBinding &out) const
{
    auto it=g_materials.find(Lower(key)); if(it==g_materials.end()) return false; out=it->second.binding; return true;
}

bool MaterialAuthoringSystem::SetSettings(const std::string &key,const AuthoredMaterialSettings &settings,bool save)
{
    auto it=g_materials.find(Lower(key)); if(it==g_materials.end()) return false; it->second.binding.settings=settings;
    if(save) return SaveSettings(it->second.binding.matPath,settings); return true;
}

std::string MaterialAuthoringSystem::RootDirectory() const { return RootPath().string(); }
