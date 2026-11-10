#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <cstddef>
#include <cstdint>

#ifndef APIENTRY
#define APIENTRY __stdcall
#endif

using GLsizeiptr = ptrdiff_t;
using GLintptr = ptrdiff_t;
using GLchar = char;

constexpr GLenum GL_VERTEX_SHADER_ = 0x8B31;
constexpr GLenum GL_FRAGMENT_SHADER_ = 0x8B30;
constexpr GLenum GL_COMPUTE_SHADER_ = 0x91B9;
constexpr GLenum GL_COMPILE_STATUS_ = 0x8B81;
constexpr GLenum GL_LINK_STATUS_ = 0x8B82;
constexpr GLenum GL_INFO_LOG_LENGTH_ = 0x8B84;
constexpr GLenum GL_RGBA8_ = 0x8058;
constexpr GLenum GL_RGB8_ = 0x8051;
constexpr GLenum GL_COMPRESSED_RGBA_S3TC_DXT1_EXT_ = 0x83F1;
constexpr GLenum GL_COMPRESSED_RGBA_S3TC_DXT3_EXT_ = 0x83F2;
constexpr GLenum GL_COMPRESSED_RGBA_S3TC_DXT5_EXT_ = 0x83F3;
constexpr GLenum GL_BGRA_ = 0x80E1;
constexpr GLenum GL_TEXTURE_2D_ = 0x0DE1;
constexpr GLenum GL_TEXTURE_MIN_FILTER_ = 0x2801;
constexpr GLenum GL_TEXTURE_MAG_FILTER_ = 0x2800;
constexpr GLenum GL_TEXTURE_WRAP_S_ = 0x2802;
constexpr GLenum GL_TEXTURE_INTERNAL_FORMAT_ = 0x1003;
constexpr GLenum GL_TEXTURE_WIDTH_ = 0x1000;
constexpr GLenum GL_TEXTURE_HEIGHT_ = 0x1001;
constexpr GLenum GL_TEXTURE_COMPRESSED_ = 0x86A1;
constexpr GLenum GL_TEXTURE_WRAP_T_ = 0x2803;
constexpr GLenum GL_LINEAR_ = 0x2601;
constexpr GLenum GL_CLAMP_TO_EDGE_ = 0x812F;
constexpr GLenum GL_DYNAMIC_STORAGE_BIT_ = 0x0100;
constexpr GLenum GL_MAP_WRITE_BIT_ = 0x0002;
constexpr GLenum GL_MAP_PERSISTENT_BIT_ = 0x0040;
constexpr GLenum GL_MAP_COHERENT_BIT_ = 0x0080;
constexpr GLenum GL_ARRAY_BUFFER_ = 0x8892;
constexpr GLenum GL_DRAW_INDIRECT_BUFFER_ = 0x8F3F;
constexpr GLenum GL_TRIANGLES_ = 0x0004;
constexpr GLenum GL_FUNC_ADD_ = 0x8006;
constexpr GLenum GL_SRC_ALPHA_ = 0x0302;
constexpr GLenum GL_ONE_MINUS_SRC_ALPHA_ = 0x0303;
constexpr GLenum GL_ONE_ = 1;
constexpr GLenum GL_ZERO_ = 0;
constexpr GLenum GL_DST_COLOR_ = 0x0306;
constexpr GLenum GL_SRC_COLOR_ = 0x0300;
constexpr GLenum GL_ONE_MINUS_SRC_COLOR_ = 0x0301;
constexpr GLenum GL_COLOR_BUFFER_BIT_ = 0x00004000;
constexpr GLenum GL_SHADER_STORAGE_BUFFER_ = 0x90D2;
constexpr GLenum GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT_ = 0x90DF;
constexpr GLenum GL_WRITE_ONLY_ = 0x88B9;
constexpr GLbitfield GL_SHADER_IMAGE_ACCESS_BARRIER_BIT_ = 0x00000020;
constexpr GLbitfield GL_TEXTURE_FETCH_BARRIER_BIT_ = 0x00000008;
constexpr GLenum GL_SYNC_GPU_COMMANDS_COMPLETE_ = 0x9117;
constexpr GLenum GL_ALREADY_SIGNALED_ = 0x911A;
constexpr GLenum GL_TIMEOUT_EXPIRED_ = 0x911B;
constexpr GLenum GL_CONDITION_SATISFIED_ = 0x911C;
constexpr GLenum GL_WAIT_FAILED_ = 0x911D;
constexpr GLbitfield GL_SYNC_FLUSH_COMMANDS_BIT_ = 0x00000001;
constexpr unsigned long long GL_TIMEOUT_IGNORED_ = 0xFFFFFFFFFFFFFFFFull;

constexpr int WGL_CONTEXT_MAJOR_VERSION_ARB_ = 0x2091;
constexpr int WGL_CONTEXT_MINOR_VERSION_ARB_ = 0x2092;
constexpr int WGL_CONTEXT_FLAGS_ARB_ = 0x2094;
constexpr int WGL_CONTEXT_PROFILE_MASK_ARB_ = 0x9126;
constexpr int WGL_CONTEXT_CORE_PROFILE_BIT_ARB_ = 0x00000001;
constexpr int WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB_ = 0x0002;
constexpr int WGL_CONTEXT_DEBUG_BIT_ARB_ = 0x0001;

using PFNWGLCREATECONTEXTATTRIBSARBPROC = HGLRC(WINAPI *)(HDC, HGLRC, const int *);
using PFNWGLSWAPINTERVALEXTPROC = BOOL(WINAPI *)(int);

using PFNGLCREATESHADERPROC = GLuint(APIENTRY *)(GLenum);
using PFNGLSHADERSOURCEPROC = void(APIENTRY *)(GLuint, GLsizei, const GLchar *const *, const GLint *);
using PFNGLCOMPILESHADERPROC = void(APIENTRY *)(GLuint);
using PFNGLGETSHADERIVPROC = void(APIENTRY *)(GLuint, GLenum, GLint *);
using PFNGLGETSHADERINFOLOGPROC = void(APIENTRY *)(GLuint, GLsizei, GLsizei *, GLchar *);
using PFNGLDELETESHADERPROC = void(APIENTRY *)(GLuint);

using PFNGLCREATEPROGRAMPROC = GLuint(APIENTRY *)();
using PFNGLATTACHSHADERPROC = void(APIENTRY *)(GLuint, GLuint);
using PFNGLLINKPROGRAMPROC = void(APIENTRY *)(GLuint);
using PFNGLGETPROGRAMIVPROC = void(APIENTRY *)(GLuint, GLenum, GLint *);
using PFNGLGETPROGRAMINFOLOGPROC = void(APIENTRY *)(GLuint, GLsizei, GLsizei *, GLchar *);
using PFNGLDELETEPROGRAMPROC = void(APIENTRY *)(GLuint);
using PFNGLUSEPROGRAMPROC = void(APIENTRY *)(GLuint);

using PFNGLGETUNIFORMLOCATIONPROC = GLint(APIENTRY *)(GLuint, const GLchar *);
using PFNGLUNIFORM1IPROC = void(APIENTRY *)(GLint, GLint);
using PFNGLUNIFORM1UIPROC = void(APIENTRY *)(GLint, GLuint);
using PFNGLUNIFORM1FPROC = void(APIENTRY *)(GLint, GLfloat);
using PFNGLUNIFORM3FPROC = void(APIENTRY *)(GLint, GLfloat, GLfloat, GLfloat);
using PFNGLUNIFORM4FPROC = void(APIENTRY *)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
using PFNGLUNIFORMMATRIX4FVPROC = void(APIENTRY *)(GLint, GLsizei, GLboolean, const GLfloat *);

using PFNGLCREATEVERTEXARRAYSPROC = void(APIENTRY *)(GLsizei, GLuint *);
using PFNGLDELETEVERTEXARRAYSPROC = void(APIENTRY *)(GLsizei, const GLuint *);
using PFNGLBINDVERTEXARRAYPROC = void(APIENTRY *)(GLuint);
using PFNGLCREATEBUFFERSPROC = void(APIENTRY *)(GLsizei, GLuint *);
using PFNGLDELETEBUFFERSPROC = void(APIENTRY *)(GLsizei, const GLuint *);
using PFNGLNAMEDBUFFERSTORAGEPROC = void(APIENTRY *)(GLuint, GLsizeiptr, const void *, GLbitfield);
using PFNGLNAMEDBUFFERSUBDATAPROC = void(APIENTRY *)(GLuint, GLintptr, GLsizeiptr, const void *);
using PFNGLMAPNAMEDBUFFERRANGEPROC = void *(APIENTRY *)(GLuint, GLintptr, GLsizeiptr, GLbitfield);
using GLSyncHandle = void *;
using PFNGLFENCESYNCPROC_ = GLSyncHandle(APIENTRY *)(GLenum, GLbitfield);
using PFNGLCLIENTWAITSYNCPROC_ = GLenum(APIENTRY *)(GLSyncHandle, GLbitfield, unsigned long long);
using PFNGLDELETESYNCPROC_ = void(APIENTRY *)(GLSyncHandle);
using PFNGLVERTEXARRAYVERTEXBUFFERPROC = void(APIENTRY *)(GLuint, GLuint, GLuint, GLintptr, GLsizei);
using PFNGLENABLEVERTEXARRAYATTRIBPROC = void(APIENTRY *)(GLuint, GLuint);
using PFNGLVERTEXARRAYATTRIBFORMATPROC = void(APIENTRY *)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint);
using PFNGLVERTEXARRAYATTRIBBINDINGPROC = void(APIENTRY *)(GLuint, GLuint, GLuint);

using PFNGLCREATETEXTURESPROC = void(APIENTRY *)(GLenum, GLsizei, GLuint *);
using PFNGLDELETETEXTURESPROC = void(APIENTRY *)(GLsizei, const GLuint *);
using PFNGLTEXTURESTORAGE2DPROC = void(APIENTRY *)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
using PFNGLTEXTURESUBIMAGE2DPROC = void(APIENTRY *)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
using PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC = void(APIENTRY *)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
using PFNGLTEXTUREPARAMETERIPROC = void(APIENTRY *)(GLuint, GLenum, GLint);
using PFNGLTEXTUREPARAMETERFPROC = void(APIENTRY *)(GLuint, GLenum, GLfloat);
using PFNGLGETTEXTURELEVELPARAMETERIVPROC = void(APIENTRY *)(GLuint, GLint, GLenum, GLint *);
using PFNGLBINDTEXTUREUNITPROC = void(APIENTRY *)(GLuint, GLuint);
using PFNGLCREATEFRAMEBUFFERSPROC = void(APIENTRY *)(GLsizei, GLuint *);
using PFNGLDELETEFRAMEBUFFERSPROC = void(APIENTRY *)(GLsizei, const GLuint *);
using PFNGLBINDFRAMEBUFFERPROC = void(APIENTRY *)(GLenum, GLuint);
using PFNGLNAMEDFRAMEBUFFERTEXTUREPROC = void(APIENTRY *)(GLuint, GLenum, GLuint, GLint);
using PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC = void(APIENTRY *)(GLuint, GLenum, GLenum, GLuint);
using PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC = void(APIENTRY *)(GLuint, GLenum);
using PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC = void(APIENTRY *)(GLuint, GLsizei, const GLenum *);
using PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC = void(APIENTRY *)(GLuint, GLenum);
using PFNGLDRAWBUFFERSPROC_ = void(APIENTRY *)(GLsizei, const GLenum *);
using PFNGLCLEARNAMEDFRAMEBUFFERFVPROC_ = void(APIENTRY *)(GLuint, GLenum, GLint, const GLfloat *);
using PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC = GLenum(APIENTRY *)(GLuint, GLenum);
using PFNGLBLITNAMEDFRAMEBUFFERPROC = void(APIENTRY *)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
using PFNGLBLITFRAMEBUFFERPROC = void(APIENTRY *)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
using PFNGLCREATE_RENDERBUFFERSPROC = void(APIENTRY *)(GLsizei, GLuint *);
using PFNGLDELETE_RENDERBUFFERSPROC = void(APIENTRY *)(GLsizei, const GLuint *);
using PFNGLNAMEDRENDERBUFFERSTORAGEPROC = void(APIENTRY *)(GLuint, GLenum, GLsizei, GLsizei);
using PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC = void(APIENTRY *)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
using PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC = void(APIENTRY *)(GLuint, GLenum, GLint *);
using PFNGLGETSTRINGIPROC = const GLubyte *(APIENTRY *)(GLenum, GLuint);

using PFNGLBLENDEQUATIONPROC = void(APIENTRY *)(GLenum);
using PFNGLDRAWARRAYSPROC = void(APIENTRY *)(GLenum, GLint, GLsizei);
using PFNGLDRAWELEMENTSPROC = void(APIENTRY *)(GLenum, GLsizei, GLenum, const void *);
using PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC_ = void(APIENTRY *)(GLenum, GLint, GLsizei, GLsizei, GLuint);
using PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC_ = void(APIENTRY *)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint);
using PFNGLMULTIDRAWARRAYSPROC = void(APIENTRY *)(GLenum, const GLint *, const GLsizei *, GLsizei);
using PFNGLMULTIDRAWARRAYSINDIRECTPROC = void(APIENTRY *)(GLenum, const void *, GLsizei, GLsizei);
using PFNGLBINDBUFFERPROC = void(APIENTRY *)(GLenum, GLuint);
using PFNGLVERTEXARRAYELEMENTBUFFERPROC = void(APIENTRY *)(GLuint, GLuint);
using PFNGLDISPATCHCOMPUTEPROC = void(APIENTRY *)(GLuint, GLuint, GLuint);
using PFNGLBINDIMAGETEXTUREPROC = void(APIENTRY *)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
using PFNGLMEMORYBARRIERPROC = void(APIENTRY *)(GLbitfield);
using PFNGLBINDBUFFERBASEPROC = void(APIENTRY *)(GLenum, GLuint, GLuint);
using PFNGLBINDBUFFERRANGEPROC = void(APIENTRY *)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);

struct GLFns
{
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = nullptr;

    PFNGLCREATESHADERPROC CreateShader = nullptr;
    PFNGLSHADERSOURCEPROC ShaderSource = nullptr;
    PFNGLCOMPILESHADERPROC CompileShader = nullptr;
    PFNGLGETSHADERIVPROC GetShaderiv = nullptr;
    PFNGLGETSHADERINFOLOGPROC GetShaderInfoLog = nullptr;
    PFNGLDELETESHADERPROC DeleteShader = nullptr;

    PFNGLCREATEPROGRAMPROC CreateProgram = nullptr;
    PFNGLATTACHSHADERPROC AttachShader = nullptr;
    PFNGLLINKPROGRAMPROC LinkProgram = nullptr;
    PFNGLGETPROGRAMIVPROC GetProgramiv = nullptr;
    PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog = nullptr;
    PFNGLDELETEPROGRAMPROC DeleteProgram = nullptr;
    PFNGLUSEPROGRAMPROC UseProgram = nullptr;

    PFNGLGETUNIFORMLOCATIONPROC GetUniformLocation = nullptr;
    PFNGLUNIFORM1IPROC Uniform1i = nullptr;
    PFNGLUNIFORM1UIPROC Uniform1ui = nullptr;
    PFNGLUNIFORM1FPROC Uniform1f = nullptr;
    PFNGLUNIFORM3FPROC Uniform3f = nullptr;
    PFNGLUNIFORM4FPROC Uniform4f = nullptr;
    PFNGLUNIFORMMATRIX4FVPROC UniformMatrix4fv = nullptr;

    PFNGLCREATEVERTEXARRAYSPROC CreateVertexArrays = nullptr;
    PFNGLDELETEVERTEXARRAYSPROC DeleteVertexArrays = nullptr;
    PFNGLBINDVERTEXARRAYPROC BindVertexArray = nullptr;
    PFNGLCREATEBUFFERSPROC CreateBuffers = nullptr;
    PFNGLDELETEBUFFERSPROC DeleteBuffers = nullptr;
    PFNGLNAMEDBUFFERSTORAGEPROC NamedBufferStorage = nullptr;
    PFNGLNAMEDBUFFERSUBDATAPROC NamedBufferSubData = nullptr;
    PFNGLMAPNAMEDBUFFERRANGEPROC MapNamedBufferRange = nullptr;
    PFNGLFENCESYNCPROC_ FenceSync = nullptr;
    PFNGLCLIENTWAITSYNCPROC_ ClientWaitSync = nullptr;
    PFNGLDELETESYNCPROC_ DeleteSync = nullptr;
    PFNGLVERTEXARRAYVERTEXBUFFERPROC VertexArrayVertexBuffer = nullptr;
    PFNGLENABLEVERTEXARRAYATTRIBPROC EnableVertexArrayAttrib = nullptr;
    PFNGLVERTEXARRAYATTRIBFORMATPROC VertexArrayAttribFormat = nullptr;
    PFNGLVERTEXARRAYATTRIBBINDINGPROC VertexArrayAttribBinding = nullptr;
    PFNGLVERTEXARRAYELEMENTBUFFERPROC VertexArrayElementBuffer = nullptr;

    PFNGLCREATETEXTURESPROC CreateTextures = nullptr;
    PFNGLDELETETEXTURESPROC DeleteTextures = nullptr;
    PFNGLTEXTURESTORAGE2DPROC TextureStorage2D = nullptr;
    PFNGLTEXTURESUBIMAGE2DPROC TextureSubImage2D = nullptr;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC CompressedTextureSubImage2D = nullptr;
    PFNGLTEXTUREPARAMETERIPROC TextureParameteri = nullptr;
    PFNGLTEXTUREPARAMETERFPROC TextureParameterf = nullptr;
    PFNGLGETTEXTURELEVELPARAMETERIVPROC GetTextureLevelParameteriv = nullptr;
    PFNGLBINDTEXTUREUNITPROC BindTextureUnit = nullptr;

    PFNGLCREATEFRAMEBUFFERSPROC CreateFramebuffers = nullptr;
    PFNGLDELETEFRAMEBUFFERSPROC DeleteFramebuffers = nullptr;
    PFNGLBINDFRAMEBUFFERPROC BindFramebuffer = nullptr;
    PFNGLNAMEDFRAMEBUFFERTEXTUREPROC NamedFramebufferTexture = nullptr;
    PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC NamedFramebufferRenderbuffer = nullptr;
    PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC NamedFramebufferDrawBuffer = nullptr;
    PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC NamedFramebufferDrawBuffers = nullptr;
    PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC NamedFramebufferReadBuffer = nullptr;
    PFNGLDRAWBUFFERSPROC_ DrawBuffers = nullptr;
    PFNGLCLEARNAMEDFRAMEBUFFERFVPROC_ ClearNamedFramebufferfv = nullptr;
    PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC CheckNamedFramebufferStatus = nullptr;
    PFNGLBLITNAMEDFRAMEBUFFERPROC BlitNamedFramebuffer = nullptr;
    PFNGLBLITFRAMEBUFFERPROC BlitFramebuffer = nullptr;
    PFNGLCREATE_RENDERBUFFERSPROC CreateRenderbuffers = nullptr;
    PFNGLDELETE_RENDERBUFFERSPROC DeleteRenderbuffers = nullptr;
    PFNGLNAMEDRENDERBUFFERSTORAGEPROC NamedRenderbufferStorage = nullptr;
    PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC NamedRenderbufferStorageMultisample = nullptr;
    PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC GetNamedRenderbufferParameteriv = nullptr;
    PFNGLGETSTRINGIPROC GetStringi = nullptr;

    PFNGLBLENDEQUATIONPROC BlendEquation = nullptr;
    PFNGLDRAWARRAYSPROC DrawArrays = nullptr;
    PFNGLDRAWELEMENTSPROC DrawElements = nullptr;
    PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC_ DrawArraysInstancedBaseInstance = nullptr;
    PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC_ DrawElementsInstancedBaseVertexBaseInstance = nullptr;
    PFNGLMULTIDRAWARRAYSPROC MultiDrawArrays = nullptr;
    PFNGLMULTIDRAWARRAYSINDIRECTPROC MultiDrawArraysIndirect = nullptr;
    PFNGLBINDBUFFERPROC BindBuffer = nullptr;
    PFNGLDISPATCHCOMPUTEPROC DispatchCompute = nullptr;
    PFNGLBINDIMAGETEXTUREPROC BindImageTexture = nullptr;
    PFNGLMEMORYBARRIERPROC MemoryBarrier = nullptr;
    PFNGLBINDBUFFERBASEPROC BindBufferBase = nullptr;
    PFNGLBINDBUFFERRANGEPROC BindBufferRange = nullptr;
};

// Capture-tool compatibility. RenderDoc's 32-bit OpenGL hook path can be
// unstable around persistent/coherent mappings, sync-ring management and MDI.
// Normal renderer behavior is unchanged unless renderdoc.dll is injected.
bool GLRenderDocCaptureCompatEnabled();
extern GLFns glf;

#include "subsystems/renderer/gl_uniform_stats.h"

inline void GLUniform1i(GLint location, GLint v0) { GLUniformStats::Instance().Submit1i(location, v0); }
inline void GLUniform1ui(GLint location, GLuint v0) { GLUniformStats::Instance().Submit1ui(location, v0); }
inline void GLUniform1f(GLint location, GLfloat v0) { GLUniformStats::Instance().Submit1f(location, v0); }
inline void GLUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { GLUniformStats::Instance().Submit3f(location, v0, v1, v2); }
inline void GLUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { GLUniformStats::Instance().Submit4f(location, v0, v1, v2, v3); }
inline void GLUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) { GLUniformStats::Instance().SubmitMatrix4fv(location, count, transpose, value); }

bool LoadWGLExtensions();
bool LoadModernGL();
void *GetModernGLProc(const char *name);

// Central renderer-owned GL state cache. Included here so legacy renderer
// translation units that already depend on gl_loader can migrate incrementally.
#include "subsystems/renderer/gl_state_cache.h"
