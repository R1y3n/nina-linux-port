#include "renderer_core.h"
#include "frame_constants.h"
#include "gl_uniform_stats.h"
#include "renderer_2d.h"
#include "renderer_presenter.h"
#include "Framebuffer.h"
#include "gui_quality.h"
#include "renderer_settings.h"
#include "../textures/texture_manager.h"
#include "../scene/scene_renderer.h"
#include "../world/world_renderer.h"
#include "../world/world_material_system.h"
#include "../world/material_authoring.h"
#include "../../gl_loader.h"
#include "gl_upload_stats.h"
#include "utils/log.h"
#include "../../shaders/shader_manager.h"
#include "../../shaders/shader_resources.h"
#include <GL/gl.h>
#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

#ifndef GL_READ_FRAMEBUFFER
#define GL_READ_FRAMEBUFFER 0x8CA8
#endif
#ifndef GL_DRAW_FRAMEBUFFER
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#endif
#ifndef GL_FRAMEBUFFER
#define GL_FRAMEBUFFER 0x8D40
#endif
#ifndef GL_RENDERBUFFER
#define GL_RENDERBUFFER 0x8D41
#endif
#ifndef GL_COLOR_ATTACHMENT0
#define GL_COLOR_ATTACHMENT0 0x8CE0
#endif
#ifndef GL_DEPTH_STENCIL_ATTACHMENT
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#endif
#ifndef GL_FRAMEBUFFER_COMPLETE
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#endif
#ifndef GL_DEPTH24_STENCIL8
#define GL_DEPTH24_STENCIL8 0x88F0
#endif

struct Vertex2D
{
    float x, y, u, v;
};

namespace
{
    RendererCoreState &CoreState() { return RendererCore::Instance().State(); }
    Framebuffer &FB() { return Framebuffer::Instance(); }
    RendererPresenterState &PresenterState() { return RendererPresenter::Instance().State(); }
    static SRWLOCK g_glCallLock = SRWLOCK_INIT;
    static thread_local uint32_t g_glCallDepth = 0;
    static float ToNdcX(float x) { return (x / static_cast<float>(std::max(1, CoreState().width))) * 2.0f - 1.0f; }
    static float ToNdcY(float y) { return 1.0f - (y / static_cast<float>(std::max(1, CoreState().height))) * 2.0f; }
    static bool CreateScreenQuadResources()
    {
        glf.CreateVertexArrays(1, &CoreState().screenQuadVao);
        glf.CreateBuffers(1, &CoreState().screenQuadVbo);
        glf.NamedBufferStorage(CoreState().screenQuadVbo, sizeof(Vertex2D) * RendererPresenterState::kMaxBatchVerts, nullptr, GL_DYNAMIC_STORAGE_BIT_);
        glf.VertexArrayVertexBuffer(CoreState().screenQuadVao, 0, CoreState().screenQuadVbo, 0, sizeof(Vertex2D));
        glf.EnableVertexArrayAttrib(CoreState().screenQuadVao, 0);
        glf.VertexArrayAttribFormat(CoreState().screenQuadVao, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, x));
        glf.VertexArrayAttribBinding(CoreState().screenQuadVao, 0, 0);
        glf.EnableVertexArrayAttrib(CoreState().screenQuadVao, 1);
        glf.VertexArrayAttribFormat(CoreState().screenQuadVao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex2D, u));
        glf.VertexArrayAttribBinding(CoreState().screenQuadVao, 1, 0);
        return CoreState().screenQuadVao != 0 && CoreState().screenQuadVbo != 0;
    }
}

RendererCore &RendererCore::Instance()
{
    static RendererCore v;
    return v;
}

static void GetPresentClientSize(int &width, int &height)
{
    width = CoreState().width;
    height = CoreState().height;
    if (!CoreState().hwnd)
        return;

    RECT rc{};
    if (GetClientRect(CoreState().hwnd, &rc))
    {
        const int w = rc.right - rc.left;
        const int h = rc.bottom - rc.top;
        if (w > 0 && h > 0)
        {
            width = w;
            height = h;
        }
    }
}

static bool CreateModernContext(HWND hwnd)
{
    CoreState().hdc = GetDC(hwnd);
    if (!CoreState().hdc)
        return false;

    PIXELFORMATDESCRIPTOR pfd{};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SWAP_COPY;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    // Talon tears the renderer down and reloads it when the user changes
    // resolution.  The game normally keeps the same HWND across that cycle.
    // A Win32 window's pixel format is immutable once SetPixelFormat succeeds,
    // so calling SetPixelFormat again on the same HWND/DC during the second
    // renderer init fails even though the previous HGLRC was deleted.
    int pf = GetPixelFormat(CoreState().hdc);
    if (pf == 0)
    {
        pf = ChoosePixelFormat(CoreState().hdc, &pfd);
        if (!pf || !SetPixelFormat(CoreState().hdc, pf, &pfd))
        {
            LOG_SESSION("SetPixelFormat initial assignment failed pf=%d err=%lu",
                        pf, static_cast<unsigned long>(GetLastError()));
            ReleaseDC(hwnd, CoreState().hdc);
            CoreState().hdc = nullptr;
            return false;
        }
        LOG_SESSION("WGL pixel format assigned first-init pf=%d hwnd=%p", pf, hwnd);
    }
    else
    {
        // Re-init/reload path.  Reuse the immutable pixel format already owned
        // by the Talon host window instead of attempting SetPixelFormat again.
        LOG_SESSION("WGL pixel format reuse re-init pf=%d hwnd=%p", pf, hwnd);
    }

    PIXELFORMATDESCRIPTOR actualPfd{};
    if (!DescribePixelFormat(CoreState().hdc, pf, sizeof(actualPfd), &actualPfd))
    {
        LOG_SESSION("DescribePixelFormat failed pf=%d err=%lu",
                    pf, static_cast<unsigned long>(GetLastError()));
        ReleaseDC(hwnd, CoreState().hdc);
        CoreState().hdc = nullptr;
        return false;
    }
    CoreState().pixelFormatSwapCopy = (actualPfd.dwFlags & PFD_SWAP_COPY) != 0;
    LOG_SESSION("WGL pixel format=%d flags=%08lX swapCopy=%d", pf, (unsigned long)actualPfd.dwFlags, CoreState().pixelFormatSwapCopy ? 1 : 0);

    HGLRC bootstrap = wglCreateContext(CoreState().hdc);
    if (!bootstrap || !wglMakeCurrent(CoreState().hdc, bootstrap))
    {
        LOG_SESSION("Bootstrap WGL context creation failed err=%lu",
                    static_cast<unsigned long>(GetLastError()));
        if (bootstrap)
            wglDeleteContext(bootstrap);
        ReleaseDC(hwnd, CoreState().hdc);
        CoreState().hdc = nullptr;
        return false;
    }

    if (!LoadWGLExtensions())
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(bootstrap);
        ReleaseDC(hwnd, CoreState().hdc);
        CoreState().hdc = nullptr;
        return false;
    }

    int attribs[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB_, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB_, 6,
            WGL_CONTEXT_FLAGS_ARB_, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB_,
            WGL_CONTEXT_PROFILE_MASK_ARB_, WGL_CONTEXT_CORE_PROFILE_BIT_ARB_,
            0};

    HGLRC modern = glf.wglCreateContextAttribsARB(CoreState().hdc, nullptr, attribs);
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(bootstrap);

    if (!modern)
    {
        LOG_SESSION("OpenGL 4.6 core context creation failed err=%lu",
                    static_cast<unsigned long>(GetLastError()));
        ReleaseDC(hwnd, CoreState().hdc);
        CoreState().hdc = nullptr;
        return false;
    }

    if (!wglMakeCurrent(CoreState().hdc, modern))
    {
        LOG_SESSION("OpenGL 4.6 core make-current failed err=%lu",
                    static_cast<unsigned long>(GetLastError()));
        wglDeleteContext(modern);
        ReleaseDC(hwnd, CoreState().hdc);
        CoreState().hdc = nullptr;
        return false;
    }

    CoreState().glrc = modern;

    if (!LoadModernGL())
    {
        LOG_SESSION("OpenGL 4.6 entry-point loading failed; tearing down rejected context");
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(CoreState().glrc);
        CoreState().glrc = nullptr;
        ReleaseDC(hwnd, CoreState().hdc);
        CoreState().hdc = nullptr;
        return false;
    }

    if (LogIsSessionEnabled())
    {
        const char *version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
        const char *vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
        const char *renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
        LOG_SESSION("OpenGL context: version=%s vendor=%s renderer=%s",
                    version ? version : "?", vendor ? vendor : "?", renderer ? renderer : "?");
    }

    if (glf.wglSwapIntervalEXT)
    {
        const BOOL ok = glf.wglSwapIntervalEXT(CoreState().vsyncEnabled ? 1 : 0);
        LOG_SESSION("WGL VSync init -> %s (interval=%d)", ok ? "accepted" : "rejected", CoreState().vsyncEnabled ? 1 : 0);
    }
    else
    {
        LOG_SESSION("WGL VSync init -> unavailable (WGL_EXT_swap_control missing)");
    }

    return true;
}

static bool CreateScenePostPipeline()
{
    // d3d.ren 0x10015240 draws one screen-filling D3D triangle fan.  A
    // vertex-ID full-screen triangle is the OpenGL-core equivalent and keeps
    // this pass independent of any model/2D vertex layout.
    auto &shaders = avp2::render::ShaderManager::Instance();
    auto *shader = shaders.CreateGraphicsFromResources("renderer.scene_post",
                                                       avp2::render::ShaderResourceId::ScenePostVertex,
                                                       avp2::render::ShaderResourceId::ScenePostFragment);
    if (!shader)
        return false;

    CoreState().scenePostShader = shader;
    CoreState().scenePostColorUniform = shader->Uniform("uColor");
    return CoreState().scenePostColorUniform >= 0;
}

static const uint8_t *PerfGlyphRows(char c);

static bool CreatePerfOverlayTextures()
{
    constexpr int atlasW = 128, atlasH = 64, cell = 8;
    std::vector<uint8_t> pixels(atlasW * atlasH * 4, 0);
    for (int ch = 0; ch < 128; ++ch)
    {
        const uint8_t *rows = PerfGlyphRows(static_cast<char>(ch));
        const int ox = (ch & 15) * cell, oy = (ch >> 4) * cell;
        for (int y = 0; y < 7; ++y)
            for (int x = 0; x < 5; ++x)
            {
                const bool on = (rows[y] & (0x10 >> x)) != 0;
                const size_t i = static_cast<size_t>(((oy + y) * atlasW + (ox + x)) * 4);
                pixels[i + 0] = 255;
                pixels[i + 1] = 255;
                pixels[i + 2] = 255;
                pixels[i + 3] = on ? 255 : 0;
            }
    }
    glf.CreateTextures(GL_TEXTURE_2D_, 1, &CoreState().perfFontTexture);
    glf.TextureStorage2D(CoreState().perfFontTexture, 1, GL_RGBA8_, atlasW, atlasH);
    glf.TextureParameteri(CoreState().perfFontTexture, GL_TEXTURE_MIN_FILTER_, GL_NEAREST);
    glf.TextureParameteri(CoreState().perfFontTexture, GL_TEXTURE_MAG_FILTER_, GL_NEAREST);
    glf.TextureParameteri(CoreState().perfFontTexture, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
    glf.TextureParameteri(CoreState().perfFontTexture, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);
    glf.TextureSubImage2D(CoreState().perfFontTexture, 0, 0, 0, atlasW, atlasH, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    const uint32_t white = 0xFFFFFFFFu;
    glf.CreateTextures(GL_TEXTURE_2D_, 1, &CoreState().perfWhiteTexture);
    glf.TextureStorage2D(CoreState().perfWhiteTexture, 1, GL_RGBA8_, 1, 1);
    glf.TextureParameteri(CoreState().perfWhiteTexture, GL_TEXTURE_MIN_FILTER_, GL_NEAREST);
    glf.TextureParameteri(CoreState().perfWhiteTexture, GL_TEXTURE_MAG_FILTER_, GL_NEAREST);
    glf.TextureParameteri(CoreState().perfWhiteTexture, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
    glf.TextureParameteri(CoreState().perfWhiteTexture, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);
    glf.TextureSubImage2D(CoreState().perfWhiteTexture, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &white);
    QueryPerformanceFrequency(&CoreState().perfQpcFreq);
    QueryPerformanceCounter(&CoreState().perfLastQpc);
    return CoreState().perfFontTexture != 0 && CoreState().perfWhiteTexture != 0;
}

static const uint8_t *PerfGlyphRows(char c)
{
    // 5x7 uppercase bitmap font. Row bits use 0x10..0x01 left-to-right.
    static const uint8_t blank[7] = {0, 0, 0, 0, 0, 0, 0};
#define G(name, a, b, c, d, e, f, g) static const uint8_t name[7] = {a, b, c, d, e, f, g}
    G(A, 14, 17, 17, 31, 17, 17, 17);
    G(B, 30, 17, 17, 30, 17, 17, 30);
    G(C, 14, 17, 16, 16, 16, 17, 14);
    G(D, 30, 17, 17, 17, 17, 17, 30);
    G(E, 31, 16, 16, 30, 16, 16, 31);
    G(F, 31, 16, 16, 30, 16, 16, 16);
    G(G, 14, 17, 16, 23, 17, 17, 15);
    G(H, 17, 17, 17, 31, 17, 17, 17);
    G(I, 14, 4, 4, 4, 4, 4, 14);
    G(J, 7, 2, 2, 2, 18, 18, 12);
    G(K, 17, 18, 20, 24, 20, 18, 17);
    G(L, 16, 16, 16, 16, 16, 16, 31);
    G(M, 17, 27, 21, 21, 17, 17, 17);
    G(N, 17, 25, 21, 19, 17, 17, 17);
    G(O, 14, 17, 17, 17, 17, 17, 14);
    G(P, 30, 17, 17, 30, 16, 16, 16);
    G(Q, 14, 17, 17, 17, 21, 18, 13);
    G(R, 30, 17, 17, 30, 20, 18, 17);
    G(S, 15, 16, 16, 14, 1, 1, 30);
    G(T, 31, 4, 4, 4, 4, 4, 4);
    G(U, 17, 17, 17, 17, 17, 17, 14);
    G(V, 17, 17, 17, 17, 17, 10, 4);
    G(W, 17, 17, 17, 17, 21, 21, 10);
    G(X, 17, 17, 10, 4, 10, 17, 17);
    G(Y, 17, 17, 10, 4, 4, 4, 4);
    G(Z, 31, 1, 2, 4, 8, 16, 31);
    G(N0, 14, 17, 19, 21, 25, 17, 14);
    G(N1, 4, 12, 4, 4, 4, 4, 14);
    G(N2, 14, 17, 1, 2, 4, 8, 31);
    G(N3, 30, 1, 1, 14, 1, 1, 30);
    G(N4, 2, 6, 10, 18, 31, 2, 2);
    G(N5, 31, 16, 16, 30, 1, 1, 30);
    G(N6, 14, 16, 16, 30, 17, 17, 14);
    G(N7, 31, 1, 2, 4, 8, 8, 8);
    G(N8, 14, 17, 17, 14, 17, 17, 14);
    G(N9, 14, 17, 17, 15, 1, 1, 14);
    G(COL, 0, 4, 4, 0, 4, 4, 0);
    G(DOT, 0, 0, 0, 0, 0, 6, 6);
    G(SLASH, 1, 2, 2, 4, 8, 8, 16);
    G(PCT, 17, 2, 4, 8, 16, 0, 17);
    G(DASH, 0, 0, 0, 31, 0, 0, 0);
    G(PLUS, 0, 4, 4, 31, 4, 4, 0);
#undef G
    if (c >= 'a' && c <= 'z')
        c = char(c - 'a' + 'A');
    switch (c)
    {
#define C(ch, n) \
    case ch:     \
        return n
        C('A', A);
        C('B', B);
        C('C', C);
        C('D', D);
        C('E', E);
        C('F', F);
        C('G', G);
        C('H', H);
        C('I', I);
        C('J', J);
        C('K', K);
        C('L', L);
        C('M', M);
        C('N', N);
        C('O', O);
        C('P', P);
        C('Q', Q);
        C('R', R);
        C('S', S);
        C('T', T);
        C('U', U);
        C('V', V);
        C('W', W);
        C('X', X);
        C('Y', Y);
        C('Z', Z);
        C('0', N0);
        C('1', N1);
        C('2', N2);
        C('3', N3);
        C('4', N4);
        C('5', N5);
        C('6', N6);
        C('7', N7);
        C('8', N8);
        C('9', N9);
        C(':', COL);
        C('.', DOT);
        C('/', SLASH);
        C('%', PCT);
        C('-', DASH);
        C('+', PLUS);
#undef C
    default:
        return blank;
    }
}

static void PerfPushQuad(std::vector<Vertex2D> &out, float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1)
{
    const Vertex2D q[6] = {{ToNdcX(x0), ToNdcY(y0), u0, v0}, {ToNdcX(x1), ToNdcY(y0), u1, v0}, {ToNdcX(x1), ToNdcY(y1), u1, v1}, {ToNdcX(x0), ToNdcY(y0), u0, v0}, {ToNdcX(x1), ToNdcY(y1), u1, v1}, {ToNdcX(x0), ToNdcY(y1), u0, v1}};
    out.insert(out.end(), q, q + 6);
}

static void PerfDrawBatch(const std::vector<Vertex2D> &verts, GLuint tex, float r, float g, float b, float a, bool texAlpha)
{
    if (verts.empty())
        return;
    GLTrackedNamedBufferSubData(CoreState().screenQuadVbo, 0, static_cast<GLsizeiptr>(verts.size() * sizeof(Vertex2D)), verts.data(), GLUploadCategory::Renderer);
    Renderer2D::Instance().BlitShader()->Use();
    GLUniform1i(Renderer2D::Instance().BlitTexUniform(), 0);
    GLUniform4f(Renderer2D::Instance().BlitColorUniform(), r, g, b, a);
    GLUniform1f(Renderer2D::Instance().BlitAlphaUniform(), 1.0f);
    GLUniform1i(Renderer2D::Instance().BlitUseKeyUniform(), 0);
    GLUniform3f(Renderer2D::Instance().BlitKeyUniform(), 0, 0, 0);
    GLUniform1i(Renderer2D::Instance().BlitUseTexAlphaUniform(), texAlpha ? 1 : 0);
    GLStateBindTextureUnit(0, tex);
    GLStateBindVertexArray(CoreState().screenQuadVao);
    glf.DrawArrays(GL_TRIANGLES_, 0, static_cast<GLsizei>(verts.size()));
}

static const char *PerfSystemName(size_t i)
{
    static const char *kNames[kPerfTimingSystemCount] = {
        "WORLD", "MODEL PREP", "SOLID FX", "SHADOWS", "MODELS", "WORLDMODELS",
        "TRANSLUCENT", "NOZ", "REALLYCLOSE", "OBJECTLIST", "QUALITY", "STREAM", "PRESENT"};
    return i < kPerfTimingSystemCount ? kNames[i] : "OTHER";
}

int64_t RendererCore::PerfTimingBegin() const
{
    if (!m_state.perfOverlayEnabled)
        return 0;
    LARGE_INTEGER q{};
    QueryPerformanceCounter(&q);
    return q.QuadPart;
}

void RendererCore::PerfTimingEnd(PerfTimingSystem system, int64_t startTicks)
{
    if (!m_state.perfOverlayEnabled || startTicks == 0)
        return;
    LARGE_INTEGER now{};
    QueryPerformanceCounter(&now);
    LARGE_INTEGER freq = m_state.perfQpcFreq;
    if (freq.QuadPart == 0)
        QueryPerformanceFrequency(&freq);
    if (freq.QuadPart == 0 || now.QuadPart <= startTicks)
        return;
    const size_t i = static_cast<size_t>(system);
    if (i >= kPerfTimingSystemCount)
        return;
    m_state.perfSystemMs[i] += 1000.0 * double(now.QuadPart - startTicks) / double(freq.QuadPart);
}

void RendererCore::PerfSetSceneObjectCounts(uint32_t modelPvs, uint32_t opaque, uint32_t chroma, uint32_t translucent, uint32_t reallyClose,
                                            uint32_t translucentWorldModels, uint32_t sprites, uint32_t particles, uint32_t polyGrids,
                                            uint32_t lineSystems, uint32_t canvases)
{
    if (!m_state.perfOverlayEnabled)
        return;
    m_state.perfModelPvs = modelPvs;
    m_state.perfModelOpaque = opaque;
    m_state.perfModelChroma = chroma;
    m_state.perfModelTranslucent = translucent;
    m_state.perfModelReallyClose = reallyClose;
    m_state.perfWorldModelTranslucent = translucentWorldModels;
    m_state.perfSprites = sprites;
    m_state.perfParticles = particles;
    m_state.perfPolyGrids = polyGrids;
    m_state.perfLineSystems = lineSystems;
    m_state.perfCanvases = canvases;
}
void RendererCore::PerfMarkFrameStart()
{
    if (!m_state.perfOverlayEnabled || m_state.perfFrameStartSeen)
        return;
    LARGE_INTEGER now{};
    QueryPerformanceCounter(&now);
    m_state.perfFrameStartQpc = now;
    m_state.perfFrameStartSeen = true;
}

void RendererCore::PerfFrameComplete()
{
    if (!m_state.perfOverlayEnabled)
    {
        m_state.perfSystemMs.fill(0.0);
        m_state.perfLastQpc = {};
        return;
    }

    LARGE_INTEGER now{};
    QueryPerformanceCounter(&now);
    if (m_state.perfQpcFreq.QuadPart == 0)
        QueryPerformanceFrequency(&m_state.perfQpcFreq);

    const LARGE_INTEGER previousFrameQpc = m_state.perfLastQpc;
    double frameMs = 0.0;
    if (previousFrameQpc.QuadPart && m_state.perfQpcFreq.QuadPart)
        frameMs = 1000.0 * double(now.QuadPart - previousFrameQpc.QuadPart) / double(m_state.perfQpcFreq.QuadPart);
    m_state.perfLastQpc = now;

    if (frameMs <= 0.01 || frameMs >= 1000.0)
    {
        m_state.perfSystemMs.fill(0.0);
        return;
    }

    const double fps = 1000.0 / frameMs;
    const double previousAverage = m_state.perfFrameMs;
    if (m_state.perfFrameMs <= 0.0)
    {
        m_state.perfFrameMs = frameMs;
        m_state.perfFps = fps;
    }
    else
    {
        m_state.perfFrameMs = m_state.perfFrameMs * 0.92 + frameMs * 0.08;
        m_state.perfFps = m_state.perfFps * 0.92 + fps * 0.08;
    }

    m_state.perfFrameHistory[m_state.perfHistoryWrite] = frameMs;
    m_state.perfFpsHistory[m_state.perfHistoryWrite] = fps;
    m_state.perfHistoryWrite = (m_state.perfHistoryWrite + 1) % kPerfHistorySamples;
    m_state.perfHistoryCount = std::min(m_state.perfHistoryCount + 1, kPerfHistorySamples);

    m_state.perfLastSystemMs = m_state.perfSystemMs;
    m_state.perfSystemMs.fill(0.0);

    const WorldMaterialPerfStats matPerf = WorldMaterialSystem::Instance().ConsumePerfStats();
    const MaterialAuthoringPerfStats authPerf = MaterialAuthoringSystem::Instance().ConsumePerfStats();
    m_state.perfMaterialApplyMs = matPerf.applyMs;
    m_state.perfMaterialResolveMs = matPerf.authoredResolveMs;
    m_state.perfMaterialStateMs = matPerf.authoredStateMs;
    m_state.perfMaterialDerivedMs = matPerf.derivedMs;
    m_state.perfMaterialNameMs = authPerf.nameMs;
    m_state.perfMaterialLookupMs = authPerf.lookupMs;
    m_state.perfMaterialLoadMs = authPerf.loadMs;
    m_state.perfMaterialApplyCalls = matPerf.applyCalls;
    m_state.perfMaterialResolveCalls = authPerf.resolveCalls;
    m_state.perfMaterialBindings = matPerf.authoredBindings;
    m_state.perfMaterialRecordsLoaded = authPerf.recordsLoaded;

    double hostMs = 0.0;
    if (m_state.perfFrameStartSeen && previousFrameQpc.QuadPart && m_state.perfQpcFreq.QuadPart &&
        m_state.perfFrameStartQpc.QuadPart > previousFrameQpc.QuadPart)
    {
        hostMs = 1000.0 * double(m_state.perfFrameStartQpc.QuadPart - previousFrameQpc.QuadPart) / double(m_state.perfQpcFreq.QuadPart);
        hostMs = std::clamp(hostMs, 0.0, frameMs);
    }
    m_state.perfFrameStartSeen = false;
    m_state.perfFrameStartQpc = {};

    double accounted = 0.0;
    size_t slowestIndex = kPerfTimingSystemCount;
    double slowestMs = 0.0;
    for (size_t i = 0; i < kPerfTimingSystemCount; ++i)
    {
        accounted += m_state.perfLastSystemMs[i];
        if (m_state.perfLastSystemMs[i] > slowestMs)
        {
            slowestMs = m_state.perfLastSystemMs[i];
            slowestIndex = i;
        }
    }
    m_state.perfLastHostMs = hostMs;
    m_state.perfLastUntypedMs = std::max(0.0, frameMs - accounted - hostMs);

    // Hold the worst HOST/UNTYPED sample for five seconds.  At several hundred
    // FPS these spikes are otherwise visible for only a few milliseconds and
    // are effectively impossible to capture in a screenshot.  Keep the named
    // subsystem snapshot from the same frame so F10 can tell us what else was
    // happening when the host-side spike occurred.
    const ULONGLONG peakNow = GetTickCount64();
    bool establishedNewHostPeak = false;
    if (!m_state.perfPeakWindowTick || peakNow - m_state.perfPeakWindowTick >= 5000)
    {
        establishedNewHostPeak = true;
        m_state.perfPeakWindowTick = peakNow;
        m_state.perfPeakHostMs = m_state.perfLastHostMs;
        m_state.perfPeakUntypedMs = m_state.perfLastUntypedMs;
        m_state.perfPeakFrameMs = frameMs;
        m_state.perfPeakSystemMs = m_state.perfLastSystemMs;
    }
    else if (m_state.perfLastHostMs > m_state.perfPeakHostMs || m_state.perfLastUntypedMs > m_state.perfPeakUntypedMs)
    {
        // Preserve maxima independently for display, but keep the subsystem
        // snapshot for whichever category just established the more useful
        // new peak.
        const bool newHostPeak = m_state.perfLastHostMs > m_state.perfPeakHostMs;
        establishedNewHostPeak = newHostPeak;
        m_state.perfPeakHostMs = std::max(m_state.perfPeakHostMs, m_state.perfLastHostMs);
        m_state.perfPeakUntypedMs = std::max(m_state.perfPeakUntypedMs, m_state.perfLastUntypedMs);
        if (newHostPeak)
        {
            m_state.perfPeakFrameMs = frameMs;
            m_state.perfPeakSystemMs = m_state.perfLastSystemMs;
        }
    }
    if (m_state.perfLastHostMs > slowestMs)
    {
        slowestMs = m_state.perfLastHostMs;
        slowestIndex = kPerfTimingSystemCount;
    }
    if (m_state.perfLastUntypedMs > slowestMs)
    {
        slowestMs = m_state.perfLastUntypedMs;
        slowestIndex = kPerfTimingSystemCount + 1;
    }

    // HOST spikes matter even when the whole frame is still extremely fast.
    // Log them separately at >=1 ms so F10 captures transient client/game
    // work, but never at the old 100 ms cadence: the formatted file write can
    // itself appear in the following frame's HOST interval and create a
    // profiler/logging feedback loop.  New 5-second peaks are captured
    // immediately; otherwise emit at most one sample per second.
    if (LogIsSessionEnabled() && m_state.perfLastHostMs >= 1.0 &&
        (establishedNewHostPeak || peakNow - m_state.perfLastHostSpikeLogTick >= 1000))
    {
        m_state.perfLastHostSpikeLogTick = peakNow;
        LOG_SESSION("PERF HOST SPIKE host=%.3f ms frame=%.3f ms (%.1f FPS) untyped=%.3f | WORLD %.3f PREP %.3f SFX %.3f SH %.3f M %.3f WM %.3f TR %.3f NOZ %.3f RC %.3f Q %.3f STR %.3f PR %.3f | counts M=%u O=%u C=%u T=%u RC=%u WM-T=%u SP=%u PS=%u PG=%u LN=%u CV=%u",
                    m_state.perfLastHostMs, frameMs, fps, m_state.perfLastUntypedMs,
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::World)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::ModelPrep)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::SolidFx)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Shadows)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Models)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::WorldModels)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Translucent)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::NoZ)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::ReallyClose)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Quality)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Streaming)],
                    m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Present)],
                    m_state.perfModelPvs, m_state.perfModelOpaque, m_state.perfModelChroma, m_state.perfModelTranslucent, m_state.perfModelReallyClose,
                    m_state.perfWorldModelTranslucent, m_state.perfSprites, m_state.perfParticles, m_state.perfPolyGrids, m_state.perfLineSystems, m_state.perfCanvases);
    }

    // Log only meaningful spikes/new worst frames.  This keeps F10 logs useful
    // instead of turning the profiler into another source of frame-time noise.
    if (LogIsSessionEnabled())
    {
        const double dynamicThreshold = previousAverage > 0.0 ? std::max(25.0, previousAverage * 1.50) : 25.0;
        const bool newWorst = frameMs >= 20.0 && frameMs > m_state.perfWorstFrameMs + 0.25;
        if (newWorst)
            m_state.perfWorstFrameMs = frameMs;
        const ULONGLONG tick = GetTickCount64();
        const bool spike = frameMs >= dynamicThreshold;
        if ((newWorst || spike) && (newWorst || tick - m_state.perfLastSlowLogTick >= 250))
        {
            m_state.perfLastSlowLogTick = tick;
            const char *slowName = slowestIndex < kPerfTimingSystemCount ? PerfSystemName(slowestIndex) : (slowestIndex == kPerfTimingSystemCount ? "HOST" : "UNTYPED");
            LOG_SESSION("PERF SLOW FRAME %.3f ms (%.1f FPS) slowest=%s %.3f ms | WORLD %.3f PREP %.3f SOLIDFX %.3f SHADOW %.3f MODELS %.3f WM %.3f TRANS %.3f NOZ %.3f RC %.3f OBJECTLIST %.3f QUALITY %.3f STREAM %.3f PRESENT %.3f HOST %.3f UNTYPED %.3f | counts pvsM=%u opaque=%u chroma=%u transM=%u rcM=%u transWM=%u spr=%u part=%u pg=%u line=%u canvas=%u",
                        frameMs, fps, slowName, slowestMs,
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::World)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::ModelPrep)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::SolidFx)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Shadows)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Models)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::WorldModels)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Translucent)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::NoZ)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::ReallyClose)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::ObjectList)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Quality)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Streaming)],
                        m_state.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Present)],
                        m_state.perfLastHostMs, m_state.perfLastUntypedMs,
                        m_state.perfModelPvs, m_state.perfModelOpaque, m_state.perfModelChroma, m_state.perfModelTranslucent, m_state.perfModelReallyClose,
                        m_state.perfWorldModelTranslucent, m_state.perfSprites, m_state.perfParticles, m_state.perfPolyGrids, m_state.perfLineSystems, m_state.perfCanvases);
        }
    }

}

void RendererCore::DrawPerfOverlay()
{
    if (!CoreState().perfOverlayEnabled || !CoreState().perfFontTexture || !CoreState().perfWhiteTexture || !Renderer2D::Instance().BlitShader())
        return;

    const auto &st = CoreState();
    constexpr float x = 12.0f, y = 12.0f;
    const float panelW = std::min(600.0f, std::max(360.0f, float(st.width) - 24.0f));
    const float panelH = 333.0f;
    const float pad = 10.0f;
    const float textScale = 1.5f;
    const float charW = 6.0f * textScale;
    const float graphX = x + pad;
    const float graphW = panelW - pad * 2.0f;
    const float frameGraphY = y + 142.0f;
    const float frameGraphH = 92.0f;
    const float fpsGraphY = y + 258.0f;
    const float fpsGraphH = 52.0f;

    size_t slowestIndex = kPerfTimingSystemCount;
    double slowestMs = st.perfLastHostMs;
    if (st.perfLastUntypedMs > slowestMs)
    {
        slowestMs = st.perfLastUntypedMs;
        slowestIndex = kPerfTimingSystemCount + 1;
    }
    for (size_t i = 0; i < kPerfTimingSystemCount; ++i)
    {
        if (st.perfLastSystemMs[i] > slowestMs)
        {
            slowestMs = st.perfLastSystemMs[i];
            slowestIndex = i;
        }
    }

    char line0[128]{}, line1[160]{}, line2[96]{}, detail0[192]{}, detail1[192]{}, detail2[192]{}, detail3[224]{};
    std::snprintf(line0, sizeof(line0), "OPENGL FRAME PROFILER");
    const char *slowName = slowestIndex < kPerfTimingSystemCount ? PerfSystemName(slowestIndex) : (slowestIndex == kPerfTimingSystemCount ? "HOST" : "UNTYPED");
    std::snprintf(line1, sizeof(line1), "FPS %.1F   %.2F MS   SLOWEST %s %.2F MS   HOSTPK %.2F/%.2F", st.perfFps, st.perfFrameMs, slowName, slowestMs, st.perfPeakHostMs, st.perfPeakFrameMs);
    std::snprintf(detail0, sizeof(detail0), "MS W %.2F PREP %.2F SFX %.2F SH %.2F M %.2F WM %.2F TR %.2F",
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::World)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::ModelPrep)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::SolidFx)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Shadows)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Models)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::WorldModels)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Translucent)]);
    std::snprintf(detail1, sizeof(detail1), "MS NOZ %.2F RC %.2F Q %.2F STR %.2F PR %.2F HOST %.2F PK %.2F U %.2F PK %.2F",
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::NoZ)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::ReallyClose)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Quality)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Streaming)],
                  st.perfLastSystemMs[static_cast<size_t>(PerfTimingSystem::Present)], st.perfLastHostMs, st.perfPeakHostMs, st.perfLastUntypedMs, st.perfPeakUntypedMs);
    std::snprintf(detail2, sizeof(detail2), "CNT M %u O %u C %u T %u RC %u WM-T %u SP %u PS %u PG %u LN %u CV %u",
                  st.perfModelPvs, st.perfModelOpaque, st.perfModelChroma, st.perfModelTranslucent, st.perfModelReallyClose,
                  st.perfWorldModelTranslucent, st.perfSprites, st.perfParticles, st.perfPolyGrids, st.perfLineSystems, st.perfCanvases);
    std::snprintf(detail3, sizeof(detail3),
                  "MAT %.2F RES %.2F NAME %.2F LOOK %.2F LOAD %.2F STATE %.2F DER %.2F | A %u R %u HIT %u NEW %u",
                  st.perfMaterialApplyMs, st.perfMaterialResolveMs, st.perfMaterialNameMs, st.perfMaterialLookupMs,
                  st.perfMaterialLoadMs, st.perfMaterialStateMs, st.perfMaterialDerivedMs,
                  st.perfMaterialApplyCalls, st.perfMaterialResolveCalls, st.perfMaterialBindings, st.perfMaterialRecordsLoaded);
    std::snprintf(line2, sizeof(line2), "FRAME TIME MS");

    const auto savedGL = avp2::render::GLStateCache::Instance().Capture();
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);
    GLStateDisable(GL_CULL_FACE);
    GLStateDisable(GL_SCISSOR_TEST);
    GLStateEnable(GL_BLEND);
    GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::vector<Vertex2D> bg;
    bg.reserve(64);
    PerfPushQuad(bg, x, y, x + panelW, y + panelH, 0, 0, 1, 1);
    PerfDrawBatch(bg, CoreState().perfWhiteTexture, 0.02f, 0.02f, 0.02f, 0.82f, false);

    // Graph backgrounds and reference lines. Frame-time graph is autoscaled but
    // never below 33.3 ms so 16.7/33.3 ms reference lines remain meaningful.
    double maxFrame = 33.333;
    double maxFps = 60.0;
    for (size_t n = 0; n < st.perfHistoryCount; ++n)
    {
        const size_t idx = (st.perfHistoryWrite + kPerfHistorySamples - st.perfHistoryCount + n) % kPerfHistorySamples;
        maxFrame = std::max(maxFrame, st.perfFrameHistory[idx]);
        maxFps = std::max(maxFps, st.perfFpsHistory[idx]);
    }
    maxFrame = std::min(100.0, std::ceil(maxFrame / 5.0) * 5.0);
    maxFps = std::min(500.0, std::ceil(maxFps / 30.0) * 30.0);

    std::vector<Vertex2D> graph;
    graph.reserve(kPerfHistorySamples * 12 + 48);
    PerfPushQuad(graph, graphX, frameGraphY, graphX + graphW, frameGraphY + frameGraphH, 0, 0, 1, 1);
    PerfPushQuad(graph, graphX, fpsGraphY, graphX + graphW, fpsGraphY + fpsGraphH, 0, 0, 1, 1);
    PerfDrawBatch(graph, CoreState().perfWhiteTexture, 0.10f, 0.10f, 0.10f, 0.82f, false);

    std::vector<Vertex2D> refs;
    refs.reserve(24);
    auto refLine = [&](double ms)
    {
        if (ms > maxFrame)
            return;
        const float yy = frameGraphY + frameGraphH - float(ms / maxFrame) * frameGraphH;
        PerfPushQuad(refs, graphX, yy, graphX + graphW, yy + 1.0f, 0, 0, 1, 1);
    };
    refLine(16.6667);
    refLine(33.3333);
    PerfDrawBatch(refs, CoreState().perfWhiteTexture, 0.45f, 0.45f, 0.45f, 0.55f, false);

    if (st.perfHistoryCount > 1)
    {
        std::vector<Vertex2D> frameBars;
        frameBars.reserve(st.perfHistoryCount * 6);
        std::vector<Vertex2D> fpsBars;
        fpsBars.reserve(st.perfHistoryCount * 6);
        const float step = graphW / float(kPerfHistorySamples);
        const float barW = std::max(1.0f, step);
        for (size_t n = 0; n < st.perfHistoryCount; ++n)
        {
            const size_t idx = (st.perfHistoryWrite + kPerfHistorySamples - st.perfHistoryCount + n) % kPerfHistorySamples;
            const float xx = graphX + float(kPerfHistorySamples - st.perfHistoryCount + n) * step;
            const float fh = std::min(frameGraphH, float(st.perfFrameHistory[idx] / maxFrame) * frameGraphH);
            const float ph = std::min(fpsGraphH, float(st.perfFpsHistory[idx] / maxFps) * fpsGraphH);
            PerfPushQuad(frameBars, xx, frameGraphY + frameGraphH - fh, xx + barW, frameGraphY + frameGraphH, 0, 0, 1, 1);
            PerfPushQuad(fpsBars, xx, fpsGraphY + fpsGraphH - ph, xx + barW, fpsGraphY + fpsGraphH, 0, 0, 1, 1);
        }
        PerfDrawBatch(frameBars, CoreState().perfWhiteTexture, 1.0f, 0.56f, 0.12f, 0.95f, false);
        PerfDrawBatch(fpsBars, CoreState().perfWhiteTexture, 0.28f, 0.80f, 1.0f, 0.90f, false);
    }

    auto drawText = [&](const char *str, float tx, float ty, float r, float g, float b)
    {
        std::vector<Vertex2D> text;
        text.reserve(std::strlen(str) * 6);
        float cx = tx;
        for (const unsigned char *pch = reinterpret_cast<const unsigned char *>(str); *pch; ++pch, cx += charW)
        {
            const int ch = *pch;
            const float u0 = float((ch & 15) * 8) / 128.0f, v0 = float((ch >> 4) * 8) / 64.0f;
            const float u1 = u0 + 8.0f / 128.0f, v1 = v0 + 8.0f / 64.0f;
            PerfPushQuad(text, cx, ty, cx + 5.0f * textScale, ty + 7.0f * textScale, u0, v0, u1, v1);
        }
        PerfDrawBatch(text, CoreState().perfFontTexture, r, g, b, 1.0f, true);
    };

    drawText(line0, x + pad, y + 8.0f, 1.0f, 0.72f, 0.18f);
    drawText(line1, x + pad, y + 29.0f, 1.0f, 1.0f, 1.0f);
    drawText(detail0, x + pad, y + 50.0f, 0.80f, 0.90f, 1.0f);
    drawText(detail1, x + pad, y + 71.0f, 0.80f, 0.90f, 1.0f);
    drawText(detail2, x + pad, y + 92.0f, 0.80f, 0.90f, 1.0f);
    drawText(detail3, x + pad, y + 113.0f, 1.0f, 0.78f, 0.35f);
    drawText(line2, graphX, frameGraphY - 18.0f, 0.90f, 0.90f, 0.90f);
    char frameScale[48]{};
    std::snprintf(frameScale, sizeof(frameScale), "MAX %.0F   16.7 / 33.3", maxFrame);
    drawText(frameScale, graphX + graphW - std::strlen(frameScale) * charW, frameGraphY - 18.0f, 0.65f, 0.65f, 0.65f);
    drawText("FPS", graphX, fpsGraphY - 18.0f, 0.90f, 0.90f, 0.90f);
    char fpsScale[32]{};
    std::snprintf(fpsScale, sizeof(fpsScale), "MAX %.0F", maxFps);
    drawText(fpsScale, graphX + graphW - std::strlen(fpsScale) * charW, fpsGraphY - 18.0f, 0.65f, 0.65f, 0.65f);

    avp2::render::GLStateCache::Instance().Restore(savedGL);
    PresenterState().screenShadowValid = false;
    RendererPresenter::Instance().InvalidateScreenRect(nullptr);
    PresenterState().frameHasPresentableContent = true;
}

void RendererCore::SetVSyncEnabled(bool enabled)
{
    const bool changed = CoreState().vsyncEnabled != enabled;
    CoreState().vsyncEnabled = enabled;
    if (!glf.wglSwapIntervalEXT)
    {
        LOG_SESSION("Renderer VSync -> %d (WGL_EXT_swap_control unavailable)", enabled ? 1 : 0);
        if (changed)
            RendererSettings::Instance().SaveCurrent();
        return;
    }

    if (CoreState().hdc && CoreState().glrc && wglGetCurrentContext() != CoreState().glrc)
        wglMakeCurrent(CoreState().hdc, CoreState().glrc);

    const BOOL ok = glf.wglSwapIntervalEXT(enabled ? 1 : 0);
    LOG_SESSION("Renderer VSync -> %d interval=%d result=%s", enabled ? 1 : 0, enabled ? 1 : 0, ok ? "accepted" : "rejected");
    if (changed)
        RendererSettings::Instance().SaveCurrent();
}

bool RendererCore::IsVSyncEnabled() const
{
    return CoreState().vsyncEnabled;
}

void RendererCore::SetPerfOverlayEnabled(bool enabled)
{
    if (CoreState().perfOverlayEnabled == enabled)
        return;
    CoreState().perfOverlayEnabled = enabled;
    CoreState().perfSystemMs.fill(0.0);
    CoreState().perfLastSystemMs.fill(0.0);
    CoreState().perfLastHostMs = 0.0;
    CoreState().perfLastUntypedMs = 0.0;
    CoreState().perfFrameStartQpc = {};
    CoreState().perfFrameStartSeen = false;
    if (enabled)
    {
        CoreState().perfFrameHistory.fill(0.0);
        CoreState().perfFpsHistory.fill(0.0);
        CoreState().perfHistoryWrite = 0;
        CoreState().perfHistoryCount = 0;
        CoreState().perfFps = 0.0;
        CoreState().perfFrameMs = 0.0;
        CoreState().perfWorstFrameMs = 0.0;
        CoreState().perfLastSlowLogTick = 0;
        QueryPerformanceCounter(&CoreState().perfLastQpc);
    }
    else
    {
        CoreState().perfLastQpc = {};
    }
    RendererSettings::Instance().SaveCurrent();
}

bool RendererCore::IsPerfOverlayEnabled() const { return CoreState().perfOverlayEnabled; }

void RendererCore::AcquireLifecycleExclusive()
{
    // Renderer_Init/Renderer_Term are top-level lifecycle entrypoints, never
    // nested GL calls.  Sharing g_glCallLock with AcquireThreadContext means a
    // mode change waits for the last in-flight map/render call and prevents any
    // new one from observing half-destroyed or half-created renderer state.
    AcquireSRWLockExclusive(&g_glCallLock);
}

void RendererCore::ReleaseLifecycleExclusive()
{
    ReleaseSRWLockExclusive(&g_glCallLock);
}

bool RendererCore::AcquireThreadContext()
{
    if (g_glCallDepth > 0)
    {
        ++g_glCallDepth;
        return true;
    }

    AcquireSRWLockExclusive(&g_glCallLock);

    if (!CoreState().glrc || !CoreState().hdc)
    {
        ReleaseSRWLockExclusive(&g_glCallLock);
        return false;
    }

    if (wglGetCurrentContext() != CoreState().glrc || wglGetCurrentDC() != CoreState().hdc)
    {
        if (!wglMakeCurrent(CoreState().hdc, CoreState().glrc))
        {
            const DWORD err = GetLastError();
            LOG_SESSION("GL CONTEXT acquire FAILED tid=%lu err=%lu currentCtx=%p rendererCtx=%p",
                        static_cast<unsigned long>(GetCurrentThreadId()),
                        static_cast<unsigned long>(err),
                        wglGetCurrentContext(), CoreState().glrc);
            ReleaseSRWLockExclusive(&g_glCallLock);
            return false;
        }
        ++CoreState().contextBindCount;
    }

    const DWORD tid = GetCurrentThreadId();
    if (CoreState().lastContextThread != 0 && CoreState().lastContextThread != tid)
    {
        ++CoreState().contextThreadChangeCount;
        static uint32_t s_threadChangeBudget = 64;
        if (LogIsSessionEnabled() && (s_threadChangeBudget))
        {
            --s_threadChangeBudget;
            LOG_SESSION("GL CONTEXT caller-switch tid=%lu previousTid=%lu total=%llu",
                        static_cast<unsigned long>(tid),
                        static_cast<unsigned long>(CoreState().lastContextThread),
                        static_cast<unsigned long long>(CoreState().contextThreadChangeCount));
        }
    }
    CoreState().lastContextThread = tid;
    g_glCallDepth = 1;
    return true;
}

void RendererCore::ReleaseThreadContext()
{
    if (g_glCallDepth == 0)
        return;

    --g_glCallDepth;
    if (g_glCallDepth != 0)
        return;

    // Release the WGL context before another engine caller can enter.
    // The renderer itself owns no thread; this only satisfies WGL thread affinity.
    if (CoreState().glrc && wglGetCurrentContext() == CoreState().glrc)
    {
        if (!wglMakeCurrent(nullptr, nullptr))
        {
            LOG_SESSION("GL CONTEXT release FAILED tid=%lu err=%lu",
                        static_cast<unsigned long>(GetCurrentThreadId()),
                        static_cast<unsigned long>(GetLastError()));
        }
    }

    ReleaseSRWLockExclusive(&g_glCallLock);
}

bool RendererCore::Init(HWND hwnd, int width, int height, bool windowed)
{
    CoreState().hwnd = hwnd;
    CoreState().width = std::max(1, width);
    CoreState().height = std::max(1, height);
    CoreState().initThread = GetCurrentThreadId();
    RendererPresenter::Instance().Init(windowed, CoreState().width, CoreState().height);

    LOG_SESSION("RendererCore::Init hwnd=%p size=%dx%d swapModel=%s", hwnd, CoreState().width, CoreState().height,
                PresenterState().emulateDiscardSwap ? "D3D_DISCARD" : "D3D_COPY");

    if (!CreateModernContext(hwnd))
        return false;

    avp2::render::GLStateCache::Instance().Invalidate();
    GLUniformStats::Instance().InvalidateAll();

    if (!FB().Init(CoreState().width, CoreState().height))
        return false;

    glViewport(0, 0, CoreState().width, CoreState().height);
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDisable(GL_CULL_FACE);

    if (!Renderer2D::Instance().Init())
        return false;
    if (!CreateScreenQuadResources())
        return false;

    if (!CreateScenePostPipeline())
        return false;

    GUIQuality::Instance().Init();
    RendererSettings::Instance().LoadAndApply();

    if (!CreatePerfOverlayTextures())
        LOG_SESSION("Perf overlay texture init failed; F12 overlay unavailable");

    if (!SceneRenderer::Instance().Init())
        return false;

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Present the initial logical target once.
    FB().Bind(GL_READ_FRAMEBUFFER, FB().Logical());
    FB().Bind(GL_DRAW_FRAMEBUFFER, 0);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glDrawBuffer(GL_BACK);
    int presentW = CoreState().width, presentH = CoreState().height;
    GetPresentClientSize(presentW, presentH);
    FB().Blit(0, 0, CoreState().width, CoreState().height, 0, 0, presentW, presentH,
              GL_COLOR_BUFFER_BIT, GL_NEAREST);
    ::SwapBuffers(CoreState().hdc);
    FB().BindLogical();
    RendererPresenter::Instance().ClearInvalidScreenRects();
    PresenterState().frameHasPresentableContent = false;

    // Do not pin the context to Init. Stock d3d.ren can be called synchronously
    // by the engine loading worker, so leave WGL unbound between serialized calls.
    if (!wglMakeCurrent(nullptr, nullptr))
    {
        LOG_SESSION("RendererCore::Init failed to release initial context err=%lu",
                    static_cast<unsigned long>(GetLastError()));
        return false;
    }
    CoreState().lastContextThread = GetCurrentThreadId();
    LOG_SESSION("RendererCore::Init context released; synchronous direct-call mode enabled (no renderer thread)");
    return true;
}

void RendererCore::Term()
{
    LOG_SESSION("RendererCore::Term");

    if (CoreState().glrc)
    {
        wglMakeCurrent(CoreState().hdc, CoreState().glrc);

        GUIQuality::Instance().Term();
        SceneRenderer::Instance().Term();
        FrameConstants::Instance().Term();
        TextureManager::Instance().Term();

        auto &shaderManager = avp2::render::ShaderManager::Instance();
        FB().Term();

        if (CoreState().perfFontTexture && glf.DeleteTextures)
            GLStateDeleteTextures(1, &CoreState().perfFontTexture);
        if (CoreState().perfWhiteTexture && glf.DeleteTextures)
            GLStateDeleteTextures(1, &CoreState().perfWhiteTexture);
        CoreState().perfFontTexture = 0;
        CoreState().perfWhiteTexture = 0;

        if (CoreState().screenQuadVbo)
            glf.DeleteBuffers(1, &CoreState().screenQuadVbo);
        if (CoreState().screenQuadVao)
            GLStateDeleteVertexArrays(1, &CoreState().screenQuadVao);
        Renderer2D::Instance().Term();
        shaderManager.Release("renderer.scene_post");

        // Return all context-owned 2D/post state to a true cold-start state.
        // This matters both for in-DLL re-init and for failed-init recovery.
        CoreState().screenQuadVbo = 0;
        CoreState().screenQuadVao = 0;
        CoreState().scenePostShader = nullptr;
        CoreState().scenePostColorUniform = -1;
        shaderManager.Shutdown();
        PresenterState().batchVertCount = 0;
        PresenterState().batchTexture = 0;
        PresenterState().batchBlend = LTSURFACEBLEND_ALPHA;
        PresenterState().batchColor = 0xFFFFFFFFu;
        PresenterState().batchAlpha = 1.0f;
        PresenterState().batchUseKey = false;
        PresenterState().batchKey = 0;
        PresenterState().batchUseTexAlpha = false;
        CoreState().in3D = false;
        Renderer2D::Instance().State().optimized = false;

        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(CoreState().glrc);
        CoreState().glrc = nullptr;
    }

    RendererPresenter::Instance().Term();

    if (CoreState().hdc && CoreState().hwnd)
        ReleaseDC(CoreState().hwnd, CoreState().hdc);

    CoreState().hdc = nullptr;
    CoreState().hwnd = nullptr;
    CoreState().width = CoreState().height = 0;
}

void RendererCore::Clear(const LTRect *rect, uint32 flags, const LTVector *color)
{
    // Stock d3d_Clear takes the load/render critical section, temporarily uses
    // a full-screen viewport, performs a target/depth/stencil clear, calls
    // InvalidateRect(pRect), and restores render state.  The GL compatibility
    // boundary mirrors the important observable parts of that contract.
    FB().BindLogical();
    Renderer2D::Instance().Flush();

    if (!CoreState().glrc)
        return;

    const bool fullScreenRect = RendererPresenter::Instance().IsFullScreenRect(rect);

    if ((flags & CLEARSCREEN_SCREEN) && (flags & CLEARSCREEN_RENDER))
        ++PresenterState().clearScreenRenderCount;
    else if (flags & CLEARSCREEN_SCREEN)
        ++PresenterState().clearScreenCount;
    else if (flags & CLEARSCREEN_RENDER)
        ++PresenterState().clearRenderOnlyCount;

    // D3D Clear is independent of COLORWRITEENABLE, ZWRITEENABLE and the
    // stencil write mask.  Save/restore the GL equivalents so Clear itself
    // never mutates the following draw state.
    GLboolean oldColorMask[4] = {GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE};
    const auto savedGL = avp2::render::GLStateCache::Instance().Capture();
    GLint oldStencilMask = 0xFF;
    GLint oldScissorBox[4] = {0, 0, CoreState().width, CoreState().height};

    glGetBooleanv(GL_COLOR_WRITEMASK, oldColorMask);
    glGetIntegerv(GL_STENCIL_WRITEMASK, &oldStencilMask);
    glGetIntegerv(GL_SCISSOR_BOX, oldScissorBox);

    if (fullScreenRect)
    {
        GLStateDisable(GL_SCISSOR_TEST);
    }
    else
    {
        GLStateEnable(GL_SCISSOR_TEST);
        const int y = CoreState().height - rect->m_nBottom;
        glScissor(rect->m_nLeft, y,
                  std::max(0, rect->m_nRight - rect->m_nLeft),
                  std::max(0, rect->m_nBottom - rect->m_nTop));
    }

    GLbitfield mask = 0;

    if (flags & CLEARSCREEN_SCREEN)
    {
        PresenterState().screenShadowValid = false;

        // A full target clear begins a new logical frame.  Clear-only engine
        // transition frames are still held at presentation time, but any draw
        // after this clear earns presentation normally.
        if (fullScreenRect)
            PresenterState().frameHasPresentableContent = false;

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

        const float r = color ? color->x / 255.0f : 0.0f;
        const float g = color ? color->y / 255.0f : 0.0f;
        const float b = color ? color->z / 255.0f : 0.0f;
        glClearColor(r, g, b, 1.0f);
        mask |= GL_COLOR_BUFFER_BIT;
    }

    if (flags & CLEARSCREEN_RENDER)
    {
        GLStateDepthMask(GL_TRUE);
        glClearDepth(1.0);

        // The renderer creates a D24S8 logical target.  D3D clears
        // stencil together with Z whenever a stencil buffer is available.
        glStencilMask(0xFFu);
        glClearStencil(0);
        mask |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
    }

    if (mask)
        glClear(mask);

    // This is the piece the earlier dirty-flip experiment missed: stock D3D
    // invalidates even a full clear.  Therefore FlipScreen(0x04) after a
    // normal/loading frame sees the whole screen as dirty, not just the last
    // HUD rectangle that happened to blit.
    RendererPresenter::Instance().InvalidateScreenRect(rect);

    // Restore exactly the state Clear temporarily overrode.
    glColorMask(oldColorMask[0], oldColorMask[1], oldColorMask[2], oldColorMask[3]);
    GLStateDepthMask(savedGL.depthWrite);
    glStencilMask(static_cast<GLuint>(oldStencilMask));
    glScissor(oldScissorBox[0], oldScissorBox[1], oldScissorBox[2], oldScissorBox[3]);
    avp2::render::GLStateCache::Instance().SetEnabled(GL_SCISSOR_TEST, savedGL.scissor);

    static uint32_t s_clearDetailBudget = 96;
    if (LogIsSessionEnabled() && (s_clearDetailBudget))
    {
        --s_clearDetailBudget;
        if (fullScreenRect)
        {
            LOG_SESSION("CLEAR tid=%lu flags=%08X rect=FULL%s target=logicalFBO dirty=FULL",
                        static_cast<unsigned long>(GetCurrentThreadId()), flags,
                        rect ? "(explicit)" : "");
        }
        else
        {
            LOG_SESSION("CLEAR tid=%lu flags=%08X rect=(%d,%d)-(%d,%d) target=logicalFBO dirtyCount=%u",
                        static_cast<unsigned long>(GetCurrentThreadId()), flags,
                        rect->m_nLeft, rect->m_nTop, rect->m_nRight, rect->m_nBottom,
                        PresenterState().dirtyRectCount);
        }
    }
}

bool RendererCore::Start3D()
{
    Renderer2D::Instance().Flush();

    // 3D rendering may modify the framebuffer without going through the 2D
    // surface path, so a later LockScreen must recapture once.
    PresenterState().screenShadowValid = false;

    CoreState().in3D = true;
    return true;
}

bool RendererCore::End3D()
{
    CoreState().in3D = false;
    GLStateDisable(GL_DEPTH_TEST);
    return true;
}

bool RendererCore::IsIn3D() const { return CoreState().in3D; }

void RendererCore::GetScreenFormat(PFormat *f) const
{
    if (!f)
        return;

    // Do not disturb m_dwVTable supplied by the engine.
    f->m_eType = BPP_32;

    // Stock d3d renderer reports its back buffer as X8R8G8B8 pixel format.
    // LT engine's 2D CPU draws convert colors and keys through this.
    f->m_adwMasks[CP_ALPHA] = 0;
    f->m_adwMasks[CP_RED] = 0x00FF0000u;
    f->m_adwMasks[CP_GREEN] = 0x0000FF00u;
    f->m_adwMasks[CP_BLUE] = 0x000000FFu;

    for (int i = 0; i < NUM_COLORPLANES; ++i)
        f->m_adwBits[i] = 8;
    f->m_adwBits[CP_ALPHA] = 0;

    f->m_adwFirstBits[CP_ALPHA] = 24;
    f->m_adwFirstBits[CP_RED] = 16;
    f->m_adwFirstBits[CP_GREEN] = 8;
    f->m_adwFirstBits[CP_BLUE] = 0;
}

HDC RendererCore::DeviceContext() const { return CoreState().hdc; }

DWORD RendererCore::InitThread() const { return CoreState().initThread; }

uint64_t RendererCore::GLContextBindCount() const { return CoreState().contextBindCount; }

uint64_t RendererCore::GLContextThreadChangeCount() const { return CoreState().contextThreadChangeCount; }

int RendererCore::Width() const { return CoreState().width; }
int RendererCore::Height() const { return CoreState().height; }
HWND RendererCore::Window() const { return CoreState().hwnd; }
GLuint RendererCore::ScreenQuadVao() const { return CoreState().screenQuadVao; }
GLuint RendererCore::ScreenQuadVbo() const { return CoreState().screenQuadVbo; }
