#include "gl_loader.h"
#include "utils/log.h"

GLFns glf;

namespace
{
    bool g_renderDocCaptureCompat = false;
}

bool GLRenderDocCaptureCompatEnabled()
{
    return g_renderDocCaptureCompat;
}

namespace
{
    bool IsInvalidWGLProc(void *p)
    {
        return p == nullptr || p == reinterpret_cast<void *>(0x1) ||
               p == reinterpret_cast<void *>(0x2) || p == reinterpret_cast<void *>(0x3) ||
               p == reinterpret_cast<void *>(-1);
    }
}

#ifdef AVP2_LINUX
/* Native build: wgl* entry points are the host's stdcall functions; every gl* entry point comes straight from the
 * SDL/GLX driver (cdecl), never through a thunk. */
extern "C" void *WINAPI lt_GetGLProcNative(LPCSTR) __asm__("W_lt_GetGLProcNative");
void *GetModernGLProc(const char *name)
{
    if (strncmp(name, "wgl", 3) == 0)
    {
        void *p = reinterpret_cast<void *>(wglGetProcAddress(name));
        return IsInvalidWGLProc(p) ? nullptr : p;
    }
    return lt_GetGLProcNative(name);
}
#else
void *GetModernGLProc(const char *name)
{
    void *p = reinterpret_cast<void *>(wglGetProcAddress(name));
    if (!IsInvalidWGLProc(p))
        return p;

    HMODULE ogl = GetModuleHandleA("opengl32.dll");
    if (!ogl)
        ogl = LoadLibraryA("opengl32.dll");
    if (!ogl)
        return nullptr;

    return reinterpret_cast<void *>(GetProcAddress(ogl, name));
}

#endif

#define LOAD_GL(member, name)                                                       \
    do                                                                              \
    {                                                                               \
        glf.member = reinterpret_cast<decltype(glf.member)>(GetModernGLProc(name)); \
        if (!glf.member)                                                            \
        {                                                                           \
            LOG_SESSION("Missing GL entry point: %s", name);                        \
            return false;                                                           \
        }                                                                           \
    } while (0)

bool LoadWGLExtensions()
{
    glf.wglCreateContextAttribsARB =
        reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(GetModernGLProc("wglCreateContextAttribsARB"));
    glf.wglSwapIntervalEXT =
        reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(GetModernGLProc("wglSwapIntervalEXT"));

    if (!glf.wglCreateContextAttribsARB)
    {
        LOG_SESSION("WGL_ARB_create_context is unavailable.");
        return false;
    }
    return true;
}

bool LoadModernGL()
{
    LOAD_GL(CreateShader, "glCreateShader");
    LOAD_GL(ShaderSource, "glShaderSource");
    LOAD_GL(CompileShader, "glCompileShader");
    LOAD_GL(GetShaderiv, "glGetShaderiv");
    LOAD_GL(GetShaderInfoLog, "glGetShaderInfoLog");
    LOAD_GL(DeleteShader, "glDeleteShader");

    LOAD_GL(CreateProgram, "glCreateProgram");
    LOAD_GL(AttachShader, "glAttachShader");
    LOAD_GL(LinkProgram, "glLinkProgram");
    LOAD_GL(GetProgramiv, "glGetProgramiv");
    LOAD_GL(GetProgramInfoLog, "glGetProgramInfoLog");
    LOAD_GL(DeleteProgram, "glDeleteProgram");
    LOAD_GL(UseProgram, "glUseProgram");

    LOAD_GL(GetUniformLocation, "glGetUniformLocation");
    LOAD_GL(Uniform1i, "glUniform1i");
    LOAD_GL(Uniform1ui, "glUniform1ui");
    LOAD_GL(Uniform1f, "glUniform1f");
    LOAD_GL(Uniform3f, "glUniform3f");
    LOAD_GL(Uniform4f, "glUniform4f");
    LOAD_GL(UniformMatrix4fv, "glUniformMatrix4fv");

    LOAD_GL(CreateVertexArrays, "glCreateVertexArrays");
    LOAD_GL(DeleteVertexArrays, "glDeleteVertexArrays");
    LOAD_GL(BindVertexArray, "glBindVertexArray");
    LOAD_GL(CreateBuffers, "glCreateBuffers");
    LOAD_GL(DeleteBuffers, "glDeleteBuffers");
    LOAD_GL(NamedBufferStorage, "glNamedBufferStorage");
    LOAD_GL(NamedBufferSubData, "glNamedBufferSubData");
    LOAD_GL(MapNamedBufferRange, "glMapNamedBufferRange");
    LOAD_GL(FenceSync, "glFenceSync");
    LOAD_GL(ClientWaitSync, "glClientWaitSync");
    LOAD_GL(DeleteSync, "glDeleteSync");
    LOAD_GL(VertexArrayVertexBuffer, "glVertexArrayVertexBuffer");
    LOAD_GL(EnableVertexArrayAttrib, "glEnableVertexArrayAttrib");
    LOAD_GL(VertexArrayAttribFormat, "glVertexArrayAttribFormat");
    LOAD_GL(VertexArrayAttribBinding, "glVertexArrayAttribBinding");
    LOAD_GL(VertexArrayElementBuffer, "glVertexArrayElementBuffer");

    LOAD_GL(CreateTextures, "glCreateTextures");
    LOAD_GL(DeleteTextures, "glDeleteTextures");
    LOAD_GL(TextureStorage2D, "glTextureStorage2D");
    LOAD_GL(TextureSubImage2D, "glTextureSubImage2D");
    LOAD_GL(CompressedTextureSubImage2D, "glCompressedTextureSubImage2D");
    LOAD_GL(TextureParameteri, "glTextureParameteri");
    LOAD_GL(TextureParameterf, "glTextureParameterf");
    LOAD_GL(GetTextureLevelParameteriv, "glGetTextureLevelParameteriv");
    LOAD_GL(BindTextureUnit, "glBindTextureUnit");

    // OpenGL 4.5+ direct-state-access framebuffer/renderbuffer API.  There is
    // intentionally no EXT/ARB or bind-to-edit fallback path.
    LOAD_GL(CreateFramebuffers, "glCreateFramebuffers");
    LOAD_GL(DeleteFramebuffers, "glDeleteFramebuffers");
    LOAD_GL(BindFramebuffer, "glBindFramebuffer");
    LOAD_GL(NamedFramebufferTexture, "glNamedFramebufferTexture");
    LOAD_GL(NamedFramebufferRenderbuffer, "glNamedFramebufferRenderbuffer");
    LOAD_GL(NamedFramebufferDrawBuffer, "glNamedFramebufferDrawBuffer");
    LOAD_GL(NamedFramebufferDrawBuffers, "glNamedFramebufferDrawBuffers");
    LOAD_GL(NamedFramebufferReadBuffer, "glNamedFramebufferReadBuffer");
    LOAD_GL(DrawBuffers, "glDrawBuffers");
    LOAD_GL(ClearNamedFramebufferfv, "glClearNamedFramebufferfv");
    LOAD_GL(CheckNamedFramebufferStatus, "glCheckNamedFramebufferStatus");
    LOAD_GL(BlitNamedFramebuffer, "glBlitNamedFramebuffer");
    LOAD_GL(BlitFramebuffer, "glBlitFramebuffer");
    LOAD_GL(CreateRenderbuffers, "glCreateRenderbuffers");
    LOAD_GL(DeleteRenderbuffers, "glDeleteRenderbuffers");
    LOAD_GL(NamedRenderbufferStorage, "glNamedRenderbufferStorage");
    LOAD_GL(NamedRenderbufferStorageMultisample, "glNamedRenderbufferStorageMultisample");
    LOAD_GL(GetNamedRenderbufferParameteriv, "glGetNamedRenderbufferParameteriv");
    LOAD_GL(GetStringi, "glGetStringi");

    LOAD_GL(BlendEquation, "glBlendEquation");
    LOAD_GL(DrawArrays, "glDrawArrays");
    LOAD_GL(DrawElements, "glDrawElements");
    LOAD_GL(DrawArraysInstancedBaseInstance, "glDrawArraysInstancedBaseInstance");
    LOAD_GL(DrawElementsInstancedBaseVertexBaseInstance, "glDrawElementsInstancedBaseVertexBaseInstance");
    LOAD_GL(MultiDrawArrays, "glMultiDrawArrays");
    LOAD_GL(MultiDrawArraysIndirect, "glMultiDrawArraysIndirect");
    LOAD_GL(BindBuffer, "glBindBuffer");
    LOAD_GL(DispatchCompute, "glDispatchCompute");
    LOAD_GL(BindImageTexture, "glBindImageTexture");
    LOAD_GL(MemoryBarrier, "glMemoryBarrier");
    LOAD_GL(BindBufferBase, "glBindBufferBase");
    LOAD_GL(BindBufferRange, "glBindBufferRange");

    // RenderDoc 1.x still hooks this 32-bit legacy WGL application through its
    // OpenGL layer.  Keep the normal renderer untouched, but when RenderDoc is
    // injected deliberately disable the three paths most likely to stress that
    // hook layer.  All affected subsystems already have SubData/direct-draw
    // fallbacks and select them when these entry points are unavailable.
    g_renderDocCaptureCompat = (GetModuleHandleA("renderdoc.dll") != nullptr);
    if (g_renderDocCaptureCompat)
    {
        glf.MapNamedBufferRange = nullptr;
        glf.FenceSync = nullptr;
        glf.ClientWaitSync = nullptr;
        glf.DeleteSync = nullptr;
        glf.MultiDrawArraysIndirect = nullptr;
        OutputDebugStringA("AVP2 OpenGL: RenderDoc capture compatibility enabled (persistent map/sync/MDI disabled).\n");
        LOG_SESSION("RenderDoc capture compatibility enabled: persistent map/sync/MDI disabled; using fallback upload/draw paths");
    }
    return true;
}
