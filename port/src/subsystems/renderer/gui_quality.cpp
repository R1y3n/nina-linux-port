#include "gui_quality.h"
#include "opengl_options_menu.h"
#include "renderer_settings.h"

#include "renderer_2d.h"
#include "renderer_core.h"
#include "Framebuffer.h"
#include "renderer_presenter.h"
#include "../world/deluxe_lightmap_baker.h"
#include "../world/material_authoring.h"
#include "../timing/high_refresh_timing.h"
#include "../../gl_loader.h"
#include "utils/log.h"
#include "../../shaders/shader_manager.h"
#include "../../shaders/shader.h"
#include "../../shaders/shader_resources.h"

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"

#include <GL/gl.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

#ifndef GL_READ_FRAMEBUFFER
#define GL_READ_FRAMEBUFFER 0x8CA8
#endif
#ifndef GL_DRAW_FRAMEBUFFER
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#endif
#ifndef GL_FRAMEBUFFER
#define GL_FRAMEBUFFER 0x8D40
#endif
#ifndef GL_DRAW_FRAMEBUFFER_BINDING
#define GL_DRAW_FRAMEBUFFER_BINDING 0x8CA6
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
#ifndef GL_DEPTH24_STENCIL8
#define GL_DEPTH24_STENCIL8 0x88F0
#endif
#ifndef GL_FRAMEBUFFER_COMPLETE
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#endif

static GUIQualityState &QualityState() { return GUIQuality::Instance().State(); }
static RendererPresenterState &PresenterState() { return RendererPresenter::Instance().State(); }
static Framebuffer &FB() { return Framebuffer::Instance(); }


namespace
{
    struct MaterialPreviewVertex
    {
        float px, py, pz;
        float nx, ny, nz;
        float tx, ty, tz;
        float u, v;
    };


    struct MaterialOpaquePreviewCache
    {
        avp2::render::Shader shader{"gui.material_opaque_preview"};
        GLuint vao = 0;
        GLuint fbo = 0;
        std::unordered_map<GLuint, GLuint> copies;
        bool failed = false;

        static MaterialOpaquePreviewCache &Instance()
        {
            static MaterialOpaquePreviewCache v;
            return v;
        }

        ~MaterialOpaquePreviewCache() { Clear(); }

        void Clear()
        {
            for (auto &kv : copies)
                if (kv.second) GLStateDeleteTextures(1, &kv.second);
            copies.clear();
            if (fbo && glf.DeleteFramebuffers) glf.DeleteFramebuffers(1, &fbo);
            if (vao) GLStateDeleteVertexArrays(1, &vao);
            fbo = vao = 0;
            shader.Reset();
            failed = false;
        }

        bool Ensure()
        {
            if (failed) return false;
            if (!shader.IsValid())
            {
                const char *vs =
                    "#version 330 core\n"
                    "out vec2 vUV;\n"
                    "void main(){\n"
                    " vec2 p = vec2((gl_VertexID << 1) & 2, gl_VertexID & 2);\n"
                    " vUV = p;\n"
                    " gl_Position = vec4(p * 2.0 - 1.0, 0.0, 1.0);\n"
                    "}\n";
                const char *fs =
                    "#version 330 core\n"
                    "uniform sampler2D uTex;\n"
                    "in vec2 vUV;\n"
                    "out vec4 FragColor;\n"
                    "void main(){ vec3 rgb = texture(uTex, vUV).rgb; FragColor = vec4(rgb, 1.0); }\n";
                if (!shader.BuildGraphics(vs, fs)) { failed = true; return false; }
            }
            if (!vao)
            {
                if (!glf.CreateVertexArrays) { failed = true; return false; }
                glf.CreateVertexArrays(1, &vao);
            }
            if (!fbo)
            {
                if (!glf.CreateFramebuffers) { failed = true; return false; }
                glf.CreateFramebuffers(1, &fbo);
            }
            return true;
        }

        GLuint Get(GLuint source)
        {
            if (!source) return 0;
            auto it = copies.find(source);
            if (it != copies.end()) return it->second;
            if (!Ensure()) return source;

            constexpr int kSize = 128;
            GLuint out = 0;
            glf.CreateTextures(GL_TEXTURE_2D_, 1, &out);
            if (!out) return source;
            glf.TextureStorage2D(out, 1, GL_RGBA8_, kSize, kSize);
            glf.TextureParameteri(out, GL_TEXTURE_MIN_FILTER_, GL_LINEAR_);
            glf.TextureParameteri(out, GL_TEXTURE_MAG_FILTER_, GL_LINEAR_);
            glf.TextureParameteri(out, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
            glf.TextureParameteri(out, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);

            glf.NamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, out, 0);
            glf.NamedFramebufferDrawBuffer(fbo, GL_COLOR_ATTACHMENT0);
            glf.NamedFramebufferReadBuffer(fbo, GL_COLOR_ATTACHMENT0);
            if (glf.CheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                GLStateDeleteTextures(1, &out);
                return source;
            }

            GLint prevViewport[4]{};
            GLint prevDrawFbo = 0;
            glGetIntegerv(GL_VIEWPORT, prevViewport);
            glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevDrawFbo);
            auto saved = avp2::render::GLStateCache::Instance().Capture();

            glf.BindFramebuffer(GL_FRAMEBUFFER, fbo);
            glViewport(0, 0, kSize, kSize);
            GLStateDisable(GL_DEPTH_TEST);
            GLStateDisable(GL_BLEND);
            GLStateDisable(GL_CULL_FACE);
            shader.Use();
            GLStateBindVertexArray(vao);
            GLUniform1i(shader.Uniform("uTex"), 0);
            GLStateBindTextureUnit(0, source);
            glf.DrawArrays(GL_TRIANGLES_, 0, 3);

            avp2::render::GLStateCache::Instance().Restore(saved);
            glf.BindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(prevDrawFbo));
            glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);

            copies.emplace(source, out);
            return out;
        }
    };

    struct MaterialPreviewRenderer
    {
        avp2::render::Shader shader{"gui.material_preview"};
        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint ibo = 0;
        GLuint fbo = 0;
        GLuint colorTex = 0;
        GLuint depthRb = 0;
        int targetSize = 0;
        GLsizei indexCount = 0;
        float orbitYaw = 0.55f;
        float orbitPitch = 0.18f;
        float orbitRadius = 2.4f;
        bool autoRotate = false;
        float autoRotateSpeed = 0.55f;
        bool failed = false;
        bool ready = false;

        static MaterialPreviewRenderer &Instance()
        {
            static MaterialPreviewRenderer v;
            return v;
        }

        ~MaterialPreviewRenderer() { Destroy(); }

        void Destroy()
        {
            if (ibo) glf.DeleteBuffers(1, &ibo);
            if (vbo) glf.DeleteBuffers(1, &vbo);
            if (vao) GLStateDeleteVertexArrays(1, &vao);
            if (fbo && glf.DeleteFramebuffers) glf.DeleteFramebuffers(1, &fbo);
            if (colorTex) GLStateDeleteTextures(1, &colorTex);
            if (depthRb && glf.DeleteRenderbuffers) glf.DeleteRenderbuffers(1, &depthRb);
            vao = vbo = ibo = fbo = colorTex = depthRb = 0;
            targetSize = 0;
            indexCount = 0;
            shader.Reset();
            failed = false;
            ready = false;
        }

        void ResetView()
        {
            orbitYaw = 0.55f;
            orbitPitch = 0.18f;
            orbitRadius = 2.4f;
        }

        void DragOrbit(float dx, float dy)
        {
            orbitYaw += dx * 0.01f;
            orbitPitch += dy * 0.01f;
            orbitPitch = std::clamp(orbitPitch, -1.35f, 1.35f);
        }

        void SetAutoRotate(bool enabled) { autoRotate = enabled; }
        bool AutoRotateEnabled() const { return autoRotate; }
        void SetAutoRotateSpeed(float speed) { autoRotateSpeed = std::clamp(speed, -4.0f, 4.0f); }
        float AutoRotateSpeed() const { return autoRotateSpeed; }

        static void Identity(float *m)
        {
            for (int i = 0; i < 16; ++i) m[i] = 0.0f;
            m[0] = m[5] = m[10] = m[15] = 1.0f;
        }

        static void Multiply(float *out, const float *a, const float *b)
        {
            float r[16]{};
            for (int c = 0; c < 4; ++c)
                for (int r0 = 0; r0 < 4; ++r0)
                    r[c * 4 + r0] = a[0 * 4 + r0] * b[c * 4 + 0] + a[1 * 4 + r0] * b[c * 4 + 1] + a[2 * 4 + r0] * b[c * 4 + 2] + a[3 * 4 + r0] * b[c * 4 + 3];
            std::memcpy(out, r, sizeof(r));
        }

        static void Perspective(float *m, float fovyRad, float aspect, float zNear, float zFar)
        {
            for (int i = 0; i < 16; ++i) m[i] = 0.0f;
            const float f = 1.0f / std::tan(fovyRad * 0.5f);
            m[0] = f / std::max(0.0001f, aspect);
            m[5] = f;
            m[10] = (zFar + zNear) / (zNear - zFar);
            m[11] = -1.0f;
            m[14] = (2.0f * zFar * zNear) / (zNear - zFar);
        }

        static void LookAt(float *m, float eyeX, float eyeY, float eyeZ,
                           float centerX, float centerY, float centerZ,
                           float upX, float upY, float upZ)
        {
            const float fx0 = centerX - eyeX;
            const float fy0 = centerY - eyeY;
            const float fz0 = centerZ - eyeZ;
            const float fl = std::sqrt(fx0 * fx0 + fy0 * fy0 + fz0 * fz0);
            const float fx = fl > 0.0f ? fx0 / fl : 0.0f;
            const float fy = fl > 0.0f ? fy0 / fl : 0.0f;
            const float fz = fl > 0.0f ? fz0 / fl : -1.0f;

            float sx = fy * upZ - fz * upY;
            float sy = fz * upX - fx * upZ;
            float sz = fx * upY - fy * upX;
            const float sl = std::sqrt(sx * sx + sy * sy + sz * sz);
            if (sl > 0.0f) { sx /= sl; sy /= sl; sz /= sl; }

            const float ux = sy * fz - sz * fy;
            const float uy = sz * fx - sx * fz;
            const float uz = sx * fy - sy * fx;

            Identity(m);
            m[0] = sx; m[4] = sy; m[8] = sz;
            m[1] = ux; m[5] = uy; m[9] = uz;
            m[2] = -fx; m[6] = -fy; m[10] = -fz;
            m[12] = -(sx * eyeX + sy * eyeY + sz * eyeZ);
            m[13] = -(ux * eyeX + uy * eyeY + uz * eyeZ);
            m[14] = fx * eyeX + fy * eyeY + fz * eyeZ;
        }

        bool EnsureMesh()
        {
            if (vao && vbo && ibo && indexCount > 0)
                return true;
            if (!glf.CreateVertexArrays || !glf.CreateBuffers || !glf.NamedBufferStorage ||
                !glf.VertexArrayVertexBuffer || !glf.EnableVertexArrayAttrib ||
                !glf.VertexArrayAttribFormat || !glf.VertexArrayAttribBinding ||
                !glf.VertexArrayElementBuffer)
                return false;

            std::vector<MaterialPreviewVertex> verts;
            std::vector<uint32_t> indices;
            const int slices = 40;
            const int stacks = 24;
            verts.reserve((slices + 1) * (stacks + 1));
            for (int y = 0; y <= stacks; ++y)
            {
                const float v = static_cast<float>(y) / static_cast<float>(stacks);
                const float theta = v * 3.1415926535f;
                const float st = std::sin(theta), ct = std::cos(theta);
                for (int x = 0; x <= slices; ++x)
                {
                    const float u = static_cast<float>(x) / static_cast<float>(slices);
                    const float phi = u * 6.283185307f;
                    const float sp = std::sin(phi), cp = std::cos(phi);
                    MaterialPreviewVertex vv{};
                    vv.px = st * cp; vv.py = ct; vv.pz = st * sp;
                    vv.nx = vv.px; vv.ny = vv.py; vv.nz = vv.pz;
                    vv.tx = -sp; vv.ty = 0.0f; vv.tz = cp;
                    if (std::fabs(vv.py) > 0.999f) { vv.tx = 1.0f; vv.ty = 0.0f; vv.tz = 0.0f; }
                    vv.u = u; vv.v = 1.0f - v;
                    verts.push_back(vv);
                }
            }
            for (int y = 0; y < stacks; ++y)
            {
                for (int x = 0; x < slices; ++x)
                {
                    const uint32_t i0 = static_cast<uint32_t>(y * (slices + 1) + x);
                    const uint32_t i1 = i0 + 1;
                    const uint32_t i2 = i0 + static_cast<uint32_t>(slices + 1);
                    const uint32_t i3 = i2 + 1;
                    indices.push_back(i0); indices.push_back(i1); indices.push_back(i2);
                    indices.push_back(i1); indices.push_back(i3); indices.push_back(i2);
                }
            }

            glf.CreateVertexArrays(1, &vao);
            glf.CreateBuffers(1, &vbo);
            glf.CreateBuffers(1, &ibo);
            glf.NamedBufferStorage(vbo, static_cast<GLsizeiptr>(verts.size() * sizeof(MaterialPreviewVertex)), verts.data(), 0);
            glf.NamedBufferStorage(ibo, static_cast<GLsizeiptr>(indices.size() * sizeof(uint32_t)), indices.data(), 0);
            glf.VertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(MaterialPreviewVertex));
            glf.EnableVertexArrayAttrib(vao, 0);
            glf.EnableVertexArrayAttrib(vao, 1);
            glf.EnableVertexArrayAttrib(vao, 2);
            glf.EnableVertexArrayAttrib(vao, 3);
            glf.VertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(MaterialPreviewVertex, px)));
            glf.VertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(MaterialPreviewVertex, nx)));
            glf.VertexArrayAttribFormat(vao, 2, 3, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(MaterialPreviewVertex, tx)));
            glf.VertexArrayAttribFormat(vao, 3, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(offsetof(MaterialPreviewVertex, u)));
            glf.VertexArrayAttribBinding(vao, 0, 0);
            glf.VertexArrayAttribBinding(vao, 1, 0);
            glf.VertexArrayAttribBinding(vao, 2, 0);
            glf.VertexArrayAttribBinding(vao, 3, 0);
            glf.VertexArrayElementBuffer(vao, ibo);
            indexCount = static_cast<GLsizei>(indices.size());
            return true;
        }

        bool EnsureShader()
        {
            if (shader.IsValid())
                return true;
            const char *vs =
                "#version 330 core\n"
                "layout(location=0) in vec3 aPos;\n"
                "layout(location=1) in vec3 aNormal;\n"
                "layout(location=2) in vec3 aTangent;\n"
                "layout(location=3) in vec2 aUV;\n"
                "uniform mat4 uMVP;\n"
                "uniform mat4 uModel;\n"
                "out vec3 vWorldPos;\n"
                "out vec3 vNormal;\n"
                "out vec3 vTangent;\n"
                "out vec2 vUV;\n"
                "void main(){ vec4 wp=uModel*vec4(aPos,1.0); vWorldPos=wp.xyz; vNormal=mat3(uModel)*aNormal; vTangent=mat3(uModel)*aTangent; vUV=aUV; gl_Position=uMVP*vec4(aPos,1.0); }\n";
            const char *fs =
                "#version 330 core\n"
                "uniform sampler2D uAlbedo;\n"
                "uniform sampler2D uNormalMap;\n"
                "uniform sampler2D uSpecMap;\n"
                "uniform int uUseAlbedo;\n"
                "uniform int uUseNormal;\n"
                "uniform int uUseSpec;\n"
                "uniform float uNormalStrength;\n"
                "uniform float uSpecularStrength;\n"
                "uniform float uGlossMin;\n"
                "uniform float uGlossMax;\n"
                "uniform float uGlossBias;\n"
                "uniform vec3 uCameraPos;\n"
                "uniform vec3 uLightDir;\n"
                "in vec3 vWorldPos;\n"
                "in vec3 vNormal;\n"
                "in vec3 vTangent;\n"
                "in vec2 vUV;\n"
                "out vec4 FragColor;\n"
                "void main(){\n"
                " vec3 albedo = (uUseAlbedo!=0) ? texture(uAlbedo,vUV).rgb : vec3(0.7,0.72,0.75);\n"
                " vec3 N = normalize(vNormal);\n"
                " vec3 T = normalize(vTangent);\n"
                " vec3 B = normalize(cross(N,T));\n"
                " if(uUseNormal!=0){ vec3 tn = texture(uNormalMap,vUV).xyz * 2.0 - 1.0; tn.xy *= max(0.0,uNormalStrength); tn.z = mix(1.0, tn.z, clamp(uNormalStrength * 0.5, 0.0, 1.0)); tn = normalize(tn); N = normalize(mat3(T,B,N) * tn); }\n"
                " vec3 L = normalize(-uLightDir);\n"
                " vec3 V = normalize(uCameraPos - vWorldPos);\n"
                " vec3 H = normalize(L + V);\n"
                " float ndl = max(dot(N,L),0.0);\n"
                " vec3 diffuse = albedo * (0.18 + ndl * 0.82);\n"
                " vec4 specTex = (uUseSpec!=0) ? texture(uSpecMap,vUV) : vec4(0.04,0.04,0.04,0.35);\n"
                " float gloss = clamp(specTex.a + uGlossBias, 0.0, 1.0);\n"
                " float power = mix(uGlossMin, uGlossMax, gloss);\n"
                " float spec = pow(max(dot(N,H),0.0), max(1.0,power)) * ndl * uSpecularStrength;\n"
                " vec3 specColor = mix(vec3(0.04), specTex.rgb, float(uUseSpec!=0));\n"
                " vec3 color = diffuse + specColor * spec;\n"
                " color += albedo * 0.02 * pow(1.0 - max(dot(N,V),0.0), 2.0);\n"
                " FragColor = vec4(color,1.0);\n"
                "}\n";
            return shader.BuildGraphics(vs, fs);
        }

        bool EnsureTarget(int size)
        {
            size = std::clamp(size, 128, 1024);
            if (fbo && targetSize == size && colorTex && depthRb)
                return true;
            if (!glf.CreateFramebuffers || !glf.CreateRenderbuffers || !glf.NamedRenderbufferStorage ||
                !glf.NamedFramebufferTexture || !glf.NamedFramebufferRenderbuffer || !glf.CheckNamedFramebufferStatus)
                return false;
            if (fbo && glf.DeleteFramebuffers) glf.DeleteFramebuffers(1, &fbo);
            if (colorTex) GLStateDeleteTextures(1, &colorTex);
            if (depthRb && glf.DeleteRenderbuffers) glf.DeleteRenderbuffers(1, &depthRb);
            fbo = 0; colorTex = 0; depthRb = 0;

            glf.CreateTextures(GL_TEXTURE_2D_, 1, &colorTex);
            glf.TextureStorage2D(colorTex, 1, GL_RGBA8_, size, size);
            glf.TextureParameteri(colorTex, GL_TEXTURE_MIN_FILTER_, GL_LINEAR_);
            glf.TextureParameteri(colorTex, GL_TEXTURE_MAG_FILTER_, GL_LINEAR_);
            glf.TextureParameteri(colorTex, GL_TEXTURE_WRAP_S_, GL_CLAMP_TO_EDGE_);
            glf.TextureParameteri(colorTex, GL_TEXTURE_WRAP_T_, GL_CLAMP_TO_EDGE_);
            glf.CreateRenderbuffers(1, &depthRb);
            glf.NamedRenderbufferStorage(depthRb, GL_DEPTH24_STENCIL8, size, size);
            glf.CreateFramebuffers(1, &fbo);
            glf.NamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0, colorTex, 0);
            glf.NamedFramebufferRenderbuffer(fbo, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRb);
            glf.NamedFramebufferDrawBuffer(fbo, GL_COLOR_ATTACHMENT0);
            glf.NamedFramebufferReadBuffer(fbo, GL_COLOR_ATTACHMENT0);
            if (glf.CheckNamedFramebufferStatus(fbo, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                return false;
            targetSize = size;
            return true;
        }

        GLuint Render(const AuthoredMaterialBinding &binding, const AuthoredMaterialSettings &settings, int size, bool useNormal, bool useSpec)
        {
            if (failed)
                return 0;
            if (!EnsureMesh() || !EnsureShader() || !EnsureTarget(size))
            {
                failed = true;
                return 0;
            }
            ready = true;

            GLint prevViewport[4]{};
            glGetIntegerv(GL_VIEWPORT, prevViewport);
            GLint prevDrawFbo = 0;
            glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prevDrawFbo);
            auto saved = avp2::render::GLStateCache::Instance().Capture();

            glf.BindFramebuffer(GL_FRAMEBUFFER, fbo);
            glViewport(0, 0, targetSize, targetSize);
            glClearColor(0.12f, 0.13f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            GLStateDisable(GL_BLEND);
            GLStateEnable(GL_DEPTH_TEST);
            GLStateDepthMask(GL_TRUE);
            GLStateDepthFunc(GL_LESS);
            GLStateEnable(GL_CULL_FACE);
            GLStateCullFace(GL_BACK);
            GLStateFrontFace(GL_CCW);
            shader.Use();
            GLStateBindVertexArray(vao);

            if (autoRotate)
                orbitYaw += ImGui::GetIO().DeltaTime * autoRotateSpeed;
            const float cosPitch = std::cos(orbitPitch);
            const float eyeX = std::sin(orbitYaw) * cosPitch * orbitRadius;
            const float eyeY = std::sin(orbitPitch) * orbitRadius;
            const float eyeZ = std::cos(orbitYaw) * cosPitch * orbitRadius;
            float model[16], view[16], proj[16], vp[16], mvp[16];
            Identity(model);
            LookAt(view, eyeX, eyeY, eyeZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
            Perspective(proj, 50.0f * 3.1415926535f / 180.0f, 1.0f, 0.1f, 16.0f);
            Multiply(vp, proj, view);
            Multiply(mvp, vp, model);

            GLUniformMatrix4fv(shader.Uniform("uMVP"), 1, GL_FALSE, mvp);
            GLUniformMatrix4fv(shader.Uniform("uModel"), 1, GL_FALSE, model);
            GLUniform3f(shader.Uniform("uCameraPos"), eyeX, eyeY, eyeZ);
            GLUniform3f(shader.Uniform("uLightDir"), -0.55f, -0.75f, -0.35f);
            GLUniform1f(shader.Uniform("uNormalStrength"), settings.normalStrength);
            GLUniform1f(shader.Uniform("uSpecularStrength"), settings.specularStrength);
            GLUniform1f(shader.Uniform("uGlossMin"), settings.glossMinPower);
            GLUniform1f(shader.Uniform("uGlossMax"), settings.glossMaxPower);
            GLUniform1f(shader.Uniform("uGlossBias"), settings.glossBias);
            GLUniform1i(shader.Uniform("uUseAlbedo"), binding.albedoTexture ? 1 : 0);
            GLUniform1i(shader.Uniform("uUseNormal"), (useNormal && binding.normalTexture) ? 1 : 0);
            GLUniform1i(shader.Uniform("uUseSpec"), (useSpec && binding.specularTexture) ? 1 : 0);
            GLUniform1i(shader.Uniform("uAlbedo"), 0);
            GLUniform1i(shader.Uniform("uNormalMap"), 1);
            GLUniform1i(shader.Uniform("uSpecMap"), 2);
            GLStateBindTextureUnit(0, binding.albedoTexture ? binding.albedoTexture : 0);
            GLStateBindTextureUnit(1, binding.normalTexture ? binding.normalTexture : 0);
            GLStateBindTextureUnit(2, binding.specularTexture ? binding.specularTexture : 0);
            glf.DrawElements(GL_TRIANGLES_, indexCount, GL_UNSIGNED_INT, nullptr);

            avp2::render::GLStateCache::Instance().Restore(saved);
            glf.BindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(prevDrawFbo));
            glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);
            return colorTex;
        }
    };

    static const char *MaterialLeafName(const std::string &key)
    {
        const size_t slash = key.find_last_of('/');
        return (slash == std::string::npos) ? key.c_str() : key.c_str() + slash + 1;
    }
}

GUIQuality &GUIQuality::Instance()
{
    static GUIQuality v;
    return v;
}

static bool LinkFullscreenProgram(const char *key, const char *label, avp2::render::ShaderResourceId fragmentResource, avp2::render::Shader *&program)
{
    auto *shader = avp2::render::ShaderManager::Instance().CreateGraphicsFromResources(
        key,
        avp2::render::ShaderResourceId::FullscreenVertex,
        fragmentResource);
    if (!shader)
    {
        LOG_SESSION("%s shader pipeline failed", label);
        program = nullptr;
        return false;
    }
    program = shader;
    return true;
}

static bool CreateQualityPostPipelines()
{
    // Splits SSAO/SSR into raw-effect -> depth-aware blur -> composite.
    // Besides looking better this keeps inspectable effect FBOs for Insert.
    if (!LinkFullscreenProgram("quality.ssao", "SSAO raw", avp2::render::ShaderResourceId::SsaoFragment, QualityState().ssaoShader))
        return false;
    if (!LinkFullscreenProgram("quality.ssr", "SSR raw", avp2::render::ShaderResourceId::SsrFragment, QualityState().ssrShader))
        return false;
    if (!LinkFullscreenProgram("quality.blur", "Quality blur", avp2::render::ShaderResourceId::BlurFragment, QualityState().blurShader))
        return false;
    if (!LinkFullscreenProgram("quality.ssao_composite", "SSAO composite", avp2::render::ShaderResourceId::SsaoCompositeFragment, QualityState().ssaoCompositeShader))
        return false;
    if (!LinkFullscreenProgram("quality.ssr_composite", "SSR composite", avp2::render::ShaderResourceId::SsrCompositeFragment, QualityState().ssrCompositeShader))
        return false;
    if (!LinkFullscreenProgram("quality.debug", "Quality debug", avp2::render::ShaderResourceId::QualityDebugFragment, QualityState().debugShader))
        return false;
    if (!LinkFullscreenProgram("quality.bloom_extract", "Bloom extract", avp2::render::ShaderResourceId::BloomExtractFragment, QualityState().bloomExtractShader))
        return false;
    if (!LinkFullscreenProgram("quality.bloom_blur", "Bloom blur", avp2::render::ShaderResourceId::BloomBlurFragment, QualityState().bloomBlurShader))
        return false;
    if (!LinkFullscreenProgram("quality.exposure", "Dynamic exposure", avp2::render::ShaderResourceId::ExposureFragment, QualityState().exposureShader))
        return false;
    if (!LinkFullscreenProgram("quality.exposure_composite", "Exposure composite", avp2::render::ShaderResourceId::ExposureCompositeFragment, QualityState().exposureCompositeShader))
        return false;
    QualityState().uSSAOParams0 = avp2::render::ShaderManager::Instance().Uniform("quality.ssao", "uParams0");
    QualityState().uSSAOParams1 = avp2::render::ShaderManager::Instance().Uniform("quality.ssao", "uParams1");
    QualityState().uSSAOParams2 = avp2::render::ShaderManager::Instance().Uniform("quality.ssao", "uParams2");
    QualityState().uSSRParams0 = avp2::render::ShaderManager::Instance().Uniform("quality.ssr", "uParams0");
    QualityState().uSSRParams1 = avp2::render::ShaderManager::Instance().Uniform("quality.ssr", "uParams1");
    QualityState().uSSRParams2 = avp2::render::ShaderManager::Instance().Uniform("quality.ssr", "uParams2");
    QualityState().uSSRFilter0 = avp2::render::ShaderManager::Instance().Uniform("quality.ssr", "uFilter0");
    QualityState().uSSRFilter1 = avp2::render::ShaderManager::Instance().Uniform("quality.ssr", "uFilter1");
    QualityState().uSSRFilter2 = avp2::render::ShaderManager::Instance().Uniform("quality.ssr", "uFilter2");
    QualityState().uBlurParams0 = avp2::render::ShaderManager::Instance().Uniform("quality.blur", "uParams0");
    QualityState().uBlurParams1 = avp2::render::ShaderManager::Instance().Uniform("quality.blur", "uParams1");
    QualityState().uSSRCompositeStrength = avp2::render::ShaderManager::Instance().Uniform("quality.ssr_composite", "uStrength");
    QualityState().uDebugParams = avp2::render::ShaderManager::Instance().Uniform("quality.debug", "uParams");
    QualityState().uDebugMode = avp2::render::ShaderManager::Instance().Uniform("quality.debug", "uMode");
    QualityState().uBloomParams = avp2::render::ShaderManager::Instance().Uniform("quality.bloom_extract", "uBloomParams");
    QualityState().uBloomBlur = avp2::render::ShaderManager::Instance().Uniform("quality.bloom_blur", "uBlur");
    QualityState().uBloomRadius = avp2::render::ShaderManager::Instance().Uniform("quality.bloom_blur", "uRadius");
    QualityState().uExposureParams0 = avp2::render::ShaderManager::Instance().Uniform("quality.exposure", "uExposureParams0");
    QualityState().uCompositeParams = avp2::render::ShaderManager::Instance().Uniform("quality.exposure_composite", "uCompositeParams");
    return true;
}

static bool CreateQualityTargets()
{
    const int width = RendererCore::Instance().Width();
    const int height = RendererCore::Instance().Height();

    {
        QualityState().msaaReady = FB().CreateMultisampleTarget(
            QualityState().msaaFBO,
            QualityState().msaaColorRB,
            QualityState().msaaReflectionMaskRB,
            QualityState().msaaDepthStencilRB,
            width, height, 4);
        LOG_SESSION("4x MSAA target %s fbo=%u size=%dx%d",
                    QualityState().msaaReady ? "ready" : "FAILED",
                    QualityState().msaaFBO, width, height);
    }

    bool ok = true;
    ok &= FB().CreateColorTarget(QualityState().postColorTex, QualityState().postFBO, width, height); // shared blur scratch
    ok &= FB().CreateColorTarget(QualityState().ssaoTex, QualityState().ssaoFBO, width, height);
    ok &= FB().CreateColorTarget(QualityState().ssaoBlurTex, QualityState().ssaoBlurFBO, width, height);
    ok &= FB().CreateColorTarget(QualityState().ssrTex, QualityState().ssrFBO, width, height);
    ok &= FB().CreateColorTarget(QualityState().ssrBlurTex, QualityState().ssrBlurFBO, width, height);
    ok &= FB().CreateColorTarget(QualityState().ssrInputTex, QualityState().ssrInputFBO, width, height);
    ok &= FB().CreateColorTarget(QualityState().debugTex, QualityState().debugFBO, width, height);

    const int bloomW = std::max(1, width / 2);
    const int bloomH = std::max(1, height / 2);
    bool postFxOk = true;
    postFxOk &= FB().CreateColorTarget(QualityState().bloomExtractTex, QualityState().bloomExtractFBO, bloomW, bloomH);
    postFxOk &= FB().CreateColorTarget(QualityState().bloomScratchTex, QualityState().bloomScratchFBO, bloomW, bloomH);
    postFxOk &= FB().CreateColorTarget(QualityState().bloomBlurTex, QualityState().bloomBlurFBO, bloomW, bloomH);
    postFxOk &= FB().CreateColorTarget(QualityState().exposureTex[0], QualityState().exposureFBO[0], 1, 1, 0x881A, GL_RGBA, GL_FLOAT, GL_LINEAR);
    postFxOk &= FB().CreateColorTarget(QualityState().exposureTex[1], QualityState().exposureFBO[1], 1, 1, 0x881A, GL_RGBA, GL_FLOAT, GL_LINEAR);
    QualityState().postFxReady = postFxOk;

    if (postFxOk)
    {
        GLfloat oldClear[4] = {0, 0, 0, 0};
        glGetFloatv(GL_COLOR_CLEAR_VALUE, oldClear);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        for (int i = 0; i < 2; i++)
        {
            FB().Bind(GL_FRAMEBUFFER, QualityState().exposureFBO[i]);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        glClearColor(oldClear[0], oldClear[1], oldClear[2], oldClear[3]);
    }

    ok &= FB().CreateDepthTarget(QualityState().postDepthTex, QualityState().postDepthFBO, width, height);

    QualityState().postReady = ok;
    LOG_SESSION("Scene post targets %s (SSAO/SSR=%s bloom/exposure=%s)",
                QualityState().postReady ? "ready" : "FAILED",
                QualityState().postReady ? "ready" : "FAILED",
                QualityState().postFxReady ? "ready" : "FAILED");
    FB().BindLogical();
    return QualityState().postReady;
}

static void CopySceneDepthToPostTexture()
{
    if (!QualityState().postReady)
        return;

    FB().CopyDepth(FB().Logical(), QualityState().postDepthFBO,
                   RendererCore::Instance().Width(), RendererCore::Instance().Height());
    FB().BindLogical();
}

static void CopyLogicalColorTo(GLuint dstFBO)
{
    FB().CopyColor(FB().Logical(), dstFBO,
                   RendererCore::Instance().Width(), RendererCore::Instance().Height(), GL_NEAREST);
    FB().BindLogical();
}

static void BeginFullscreenPost(GLuint fbo, avp2::render::Shader *program)
{
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);
    GLStateDisable(GL_BLEND);
    GLStateDisable(GL_CULL_FACE);
    FB().Bind(GL_FRAMEBUFFER, fbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glViewport(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height());
    program->Use();
    GLStateBindVertexArray(RendererCore::Instance().ScreenQuadVao());
}

static void BeginFullscreenPostSized(GLuint fbo, avp2::render::Shader *program, int width, int height)
{
    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);
    GLStateDisable(GL_BLEND);
    GLStateDisable(GL_CULL_FACE);
    FB().Bind(GL_FRAMEBUFFER, fbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glViewport(0, 0, width, height);
    program->Use();
    GLStateBindVertexArray(RendererCore::Instance().ScreenQuadVao());
}

static void DrawFullscreen()
{
    glf.DrawArrays(GL_TRIANGLES_, 0, 3);
    ++PresenterState().frameDrawCalls;
}

static void RunDepthAwareBlur(GLuint srcTex, GLuint dstFBO, float radius, float depthTolerance, const SceneDesc *scene)
{
    if (radius < 0.5f)
    {
        FB().Bind(GL_READ_FRAMEBUFFER, srcTex == QualityState().ssaoTex ? QualityState().ssaoFBO : QualityState().ssrFBO);
        FB().Bind(GL_DRAW_FRAMEBUFFER, dstFBO);
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        FB().Blit(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), 0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
        FB().BindLogical();
        return;
    }
    float n = 1.0f, f = std::max(2.0f, scene->m_fFarZ);
    BeginFullscreenPost(QualityState().postFBO, QualityState().blurShader);
    GLStateBindTextureUnit(0, srcTex);
    GLStateBindTextureUnit(1, QualityState().postDepthTex);
    GLUniform4f(QualityState().uBlurParams0, 1.0f / RendererCore::Instance().Width(), 1.0f / RendererCore::Instance().Height(), radius, depthTolerance);
    GLUniform4f(QualityState().uBlurParams1, 1, 0, n, f);
    DrawFullscreen();
    BeginFullscreenPost(dstFBO, QualityState().blurShader);
    GLStateBindTextureUnit(0, QualityState().postColorTex);
    GLStateBindTextureUnit(1, QualityState().postDepthTex);
    GLUniform4f(QualityState().uBlurParams0, 1.0f / RendererCore::Instance().Width(), 1.0f / RendererCore::Instance().Height(), radius, depthTolerance);
    GLUniform4f(QualityState().uBlurParams1, 0, 1, n, f);
    DrawFullscreen();
    FB().BindLogical();
}

static void RunSSAOPass(const SceneDesc *scene)
{
    float tx = std::tan(std::max(0.01f, scene->m_fFovX * 0.5f)), ty = std::tan(std::max(0.01f, scene->m_fFovY * 0.5f));
    float n = 1.0f, f = std::max(2.0f, scene->m_fFarZ);
    BeginFullscreenPost(QualityState().ssaoFBO, QualityState().ssaoShader);
    GLStateBindTextureUnit(0, FB().ColorTexture());
    GLStateBindTextureUnit(1, QualityState().postDepthTex);
    GLUniform4f(QualityState().uSSAOParams0, tx, ty, n, f);
    GLUniform4f(QualityState().uSSAOParams1, 1.0f / RendererCore::Instance().Width(), 1.0f / RendererCore::Instance().Height(), QualityState().ssaoStrength, QualityState().ssaoRadiusPixels);
    GLUniform4f(QualityState().uSSAOParams2, QualityState().ssaoBias, QualityState().ssaoMinAO, 0, 0);
    DrawFullscreen();
    RunDepthAwareBlur(QualityState().ssaoTex, QualityState().ssaoBlurFBO, QualityState().ssaoBlurRadius, QualityState().ssaoBlurDepth, scene);
    BeginFullscreenPost(QualityState().postFBO, QualityState().ssaoCompositeShader);
    GLStateBindTextureUnit(0, FB().ColorTexture());
    GLStateBindTextureUnit(1, QualityState().ssaoBlurTex);
    DrawFullscreen();
    FB().Bind(GL_READ_FRAMEBUFFER, QualityState().postFBO);
    FB().Bind(GL_DRAW_FRAMEBUFFER, FB().Logical());
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    FB().Blit(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), 0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
    FB().BindLogical();
}

static void RunSSRPass(const SceneDesc *scene)
{
    // Snapshot exactly what SSR reacts against so Insert can inspect it.
    CopyLogicalColorTo(QualityState().ssrInputFBO);
    float tx = std::tan(std::max(0.01f, scene->m_fFovX * 0.5f)), ty = std::tan(std::max(0.01f, scene->m_fFovY * 0.5f));
    float n = 1.0f, f = std::max(2.0f, scene->m_fFarZ);
    BeginFullscreenPost(QualityState().ssrFBO, QualityState().ssrShader);
    GLStateBindTextureUnit(0, QualityState().ssrInputTex);
    GLStateBindTextureUnit(1, QualityState().postDepthTex);
    GLStateBindTextureUnit(2, FB().ReflectionMaskTexture());
    GLUniform4f(QualityState().uSSRParams0, tx, ty, n, f);
    GLUniform4f(QualityState().uSSRParams1, 1.0f / RendererCore::Instance().Width(), 1.0f / RendererCore::Instance().Height(), 0.0f, std::min(QualityState().ssrMaxDistance, f * 0.35f));
    GLUniform4f(QualityState().uSSRParams2, QualityState().ssrThicknessBase, QualityState().ssrThicknessScale, QualityState().ssrNormalBias, static_cast<float>(QualityState().ssrSteps));
    GLUniform4f(QualityState().uSSRFilter0, QualityState().ssrFilterEnabled ? 1.0f : 0.0f, QualityState().ssrFilterInvert ? 1.0f : 0.0f, QualityState().ssrHueCenter, QualityState().ssrHueWidth);
    GLUniform4f(QualityState().uSSRFilter1, QualityState().ssrSatMin, QualityState().ssrSatMax, QualityState().ssrValueMin, QualityState().ssrValueMax);
    GLUniform4f(QualityState().uSSRFilter2, QualityState().ssrAlphaMin, QualityState().ssrFilterSoftness, 0, 0);
    DrawFullscreen();
    RunDepthAwareBlur(QualityState().ssrTex, QualityState().ssrBlurFBO, QualityState().ssrBlurRadius, QualityState().ssrBlurDepth, scene);
    BeginFullscreenPost(QualityState().postFBO, QualityState().ssrCompositeShader);
    GLStateBindTextureUnit(0, QualityState().ssrInputTex);
    GLStateBindTextureUnit(1, QualityState().ssrBlurTex);
    if (QualityState().uSSRCompositeStrength >= 0)
        GLUniform1f(QualityState().uSSRCompositeStrength, QualityState().ssrStrength);
    DrawFullscreen();
    FB().Bind(GL_READ_FRAMEBUFFER, QualityState().postFBO);
    FB().Bind(GL_DRAW_FRAMEBUFFER, FB().Logical());
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    FB().Blit(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), 0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
    FB().BindLogical();
}

static float ComputeFrameDeltaSeconds()
{
    static LARGE_INTEGER freq{};
    static LARGE_INTEGER prev{};
    if (freq.QuadPart == 0)
        QueryPerformanceFrequency(&freq);
    LARGE_INTEGER now{};
    QueryPerformanceCounter(&now);
    float dt = 1.0f / 60.0f;
    if (prev.QuadPart != 0 && freq.QuadPart > 0)
        dt = static_cast<float>(double(now.QuadPart - prev.QuadPart) / double(freq.QuadPart));
    prev = now;
    return std::clamp(dt, 0.001f, 0.10f);
}

static void RunBloomAndExposureComposite()
{
    if (!QualityState().postFxReady || !QualityState().exposureCompositeShader || (!QualityState().bloomEnabled && !QualityState().dynamicExposureEnabled))
        return;

    Renderer2D::Instance().Flush();
    CopyLogicalColorTo(QualityState().postFBO);
    const int bw = std::max(1, RendererCore::Instance().Width() / 2);
    const int bh = std::max(1, RendererCore::Instance().Height() / 2);

    if (QualityState().bloomEnabled)
    {
        BeginFullscreenPostSized(QualityState().bloomExtractFBO, QualityState().bloomExtractShader, bw, bh);
        GLStateBindTextureUnit(0, QualityState().postColorTex);
        GLUniform4f(QualityState().uBloomParams, QualityState().bloomThreshold, QualityState().bloomSoftKnee, QualityState().bloomIntensity, 0.0f);
        DrawFullscreen();

        BeginFullscreenPostSized(QualityState().bloomScratchFBO, QualityState().bloomBlurShader, bw, bh);
        GLStateBindTextureUnit(0, QualityState().bloomExtractTex);
        GLUniform4f(QualityState().uBloomBlur, 1.0f / float(bw), 1.0f / float(bh), 1.0f, 0.0f);
        GLUniform1f(QualityState().uBloomRadius, QualityState().bloomRadius);
        DrawFullscreen();

        BeginFullscreenPostSized(QualityState().bloomBlurFBO, QualityState().bloomBlurShader, bw, bh);
        GLStateBindTextureUnit(0, QualityState().bloomScratchTex);
        GLUniform4f(QualityState().uBloomBlur, 1.0f / float(bw), 1.0f / float(bh), 0.0f, 1.0f);
        GLUniform1f(QualityState().uBloomRadius, QualityState().bloomRadius);
        DrawFullscreen();
    }

    if (QualityState().dynamicExposureEnabled)
    {
        const int srcIdx = QualityState().exposureIndex;
        const int dstIdx = 1 - srcIdx;
        const float dt = ComputeFrameDeltaSeconds();
        const float alpha = 1.0f - std::exp(-std::max(0.01f, QualityState().exposureAdaptSpeed) * dt);
        BeginFullscreenPostSized(QualityState().exposureFBO[dstIdx], QualityState().exposureShader, 1, 1);
        GLStateBindTextureUnit(0, QualityState().postColorTex);
        GLStateBindTextureUnit(1, QualityState().exposureTex[srcIdx]);
        GLUniform4f(QualityState().uExposureParams0,
                    QualityState().exposureBaseline,
                    QualityState().exposureDarkMax,
                    QualityState().exposureDarkThreshold,
                    alpha);
        DrawFullscreen();
        QualityState().exposureIndex = dstIdx;
    }

    BeginFullscreenPost(FB().Logical(), QualityState().exposureCompositeShader);
    GLStateBindTextureUnit(0, QualityState().postColorTex);
    GLStateBindTextureUnit(1, QualityState().bloomEnabled ? QualityState().bloomBlurTex : QualityState().postColorTex);
    GLStateBindTextureUnit(2, QualityState().exposureTex[QualityState().exposureIndex]);
    GLUniform4f(QualityState().uCompositeParams, QualityState().bloomEnabled ? QualityState().bloomIntensity : 0.0f, QualityState().dynamicExposureEnabled ? 1.0f : 0.0f, 0.0f, 0.0f);
    DrawFullscreen();
    FB().BindLogical();

    PresenterState().screenShadowValid = false;
    RendererPresenter::Instance().InvalidateScreenRect(nullptr);
    PresenterState().frameHasPresentableContent = true;
}

static void UpdateQualityDebugPreview()
{
    if (!QualityState().postReady || !QualityState().debugShader || QualityState().qualityDebugView <= 0)
        return;
    GLuint src = 0;
    int mode = 0;
    switch (QualityState().qualityDebugView)
    {
    case 1:
        src = FB().ColorTexture();
        break;
    case 2:
        src = QualityState().ssrInputTex;
        break;
    case 3:
        src = QualityState().postDepthTex;
        mode = 1;
        break;
    case 4:
        src = QualityState().ssaoTex;
        break;
    case 5:
        src = QualityState().ssaoBlurTex;
        break;
    case 6:
        src = QualityState().ssrTex;
        break;
    case 7:
        src = QualityState().ssrBlurTex;
        break;
    case 8:
        src = FB().ReflectionMaskTexture();
        mode = 3;
        break;
    case 9:
        src = QualityState().bloomExtractTex;
        break;
    case 10:
        src = QualityState().bloomBlurTex;
        break;
    default:
        return;
    }
    BeginFullscreenPost(QualityState().debugFBO, QualityState().debugShader);
    GLStateBindTextureUnit(0, src);
    GLUniform4f(QualityState().uDebugParams, QualityState().lastQualityNear, QualityState().lastQualityFar, 0, 0);
    if (QualityState().uDebugMode >= 0)
        GLUniform1i(QualityState().uDebugMode, mode);
    DrawFullscreen();
    FB().BindLogical();
}

static bool InitTuningMenu()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.IniFilename = nullptr; // renderer debug UI: do not create imgui.ini beside AVP2.exe
    ImGui::StyleColorsDark();
    if (!ImGui_ImplWin32_Init(RendererCore::Instance().Window()))
    {
        LOG_SESSION("ImGui Win32 init FAILED");
        ImGui::DestroyContext();
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 460 core"))
    {
        LOG_SESSION("ImGui OpenGL3 init FAILED");
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        return false;
    }
    QualityState().imguiReady = true;
    LOG_SESSION("ImGui tuning UI ready (Insert)");
    return true;
}

static void ShutdownTuningMenu()
{
    if (!QualityState().imguiReady)
        return;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    QualityState().imguiReady = false;
    QualityState().tuningMenuOpen = false;
}

static void ResetSSAOSettings()
{
    QualityState().ssaoStrength = 2.15f;
    QualityState().ssaoRadiusPixels = 8.0f;
    QualityState().ssaoBias = 0.08f;
    QualityState().ssaoMinAO = 0.35f;
    QualityState().ssaoBlurRadius = 7.2f;
    QualityState().ssaoBlurDepth = 93.2f;
}

static void ResetSSRSettings()
{
    QualityState().ssrStrength = 0.30f;
    QualityState().ssrMaxDistance = 341.0f;
    QualityState().ssrThicknessBase = 0.10f;
    QualityState().ssrThicknessScale = 0.0088f;
    QualityState().ssrNormalBias = 0.28f;
    QualityState().ssrSteps = 34;
    QualityState().ssrBlurRadius = 4.9f;
    QualityState().ssrBlurDepth = 44.8f;
    QualityState().ssrFilterEnabled = true;
    QualityState().ssrFilterInvert = true;
    QualityState().ssrHueCenter = 0.166f;
    QualityState().ssrHueWidth = 0.376f;
    QualityState().ssrSatMin = 0.02f;
    QualityState().ssrSatMax = 0.30f;
    QualityState().ssrValueMin = 0.0f;
    QualityState().ssrValueMax = 0.60f;
    QualityState().ssrAlphaMin = 0.09f;
    QualityState().ssrFilterSoftness = 0.060f;
}

static void ResetBloomSettings()
{
    QualityState().bloomThreshold = 0.72f;
    QualityState().bloomSoftKnee = 0.18f;
    QualityState().bloomIntensity = 0.55f;
    QualityState().bloomRadius = 1.25f;
}

static void ResetDynamicExposureSettings()
{
    QualityState().exposureBaseline = 1.00f;
    QualityState().exposureDarkMax = 1.35f;
    QualityState().exposureDarkThreshold = 0.20f;
    QualityState().exposureAdaptSpeed = 2.0f;
}

static void FeedTuningMenuMouseState()
{
    if (!QualityState().imguiReady || !QualityState().tuningMenuOpen || !RendererCore::Instance().Window())
        return;

    ImGuiIO &io = ImGui::GetIO();
    POINT pt{};
    if (GetCursorPos(&pt) && ScreenToClient(RendererCore::Instance().Window(), &pt))
        io.AddMousePosEvent(static_cast<float>(pt.x), static_cast<float>(pt.y));

    static bool oldButtons[5] = {};
    const int vks[5] = {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2};
    for (int i = 0; i < 5; ++i)
    {
        const bool down = (GetAsyncKeyState(vks[i]) & 0x8000) != 0;
        if (down != oldButtons[i])
        {
            io.AddMouseButtonEvent(i, down);
            oldButtons[i] = down;
        }
    }
}

bool GUIQuality::Init()
{
    if (!CreateQualityPostPipelines())
        LOG_SESSION("Quality post shaders unavailable; SSAO/SSR disabled");
    if (!CreateQualityTargets())
        LOG_SESSION("Quality targets incomplete; optional effects may be unavailable");
    if (!InitTuningMenu())
        LOG_SESSION("ImGui tuning UI unavailable; Insert disabled");
    return true;
}

void GUIQuality::Term()
{
    ShutdownTuningMenu();
    auto &shaderManager = avp2::render::ShaderManager::Instance();
    shaderManager.Release("quality.ssao");
    shaderManager.Release("quality.ssr");
    shaderManager.Release("quality.blur");
    shaderManager.Release("quality.ssao_composite");
    shaderManager.Release("quality.ssr_composite");
    shaderManager.Release("quality.debug");
    shaderManager.Release("quality.bloom_extract");
    shaderManager.Release("quality.bloom_blur");
    shaderManager.Release("quality.exposure");
    shaderManager.Release("quality.exposure_composite");
    QualityState().ssaoShader = QualityState().ssrShader = QualityState().blurShader = QualityState().ssaoCompositeShader = QualityState().ssrCompositeShader = QualityState().debugShader = nullptr;
    QualityState().bloomExtractShader = QualityState().bloomBlurShader = QualityState().exposureShader = QualityState().exposureCompositeShader = nullptr;
    FB().DestroyDepthTarget(QualityState().postDepthTex, QualityState().postDepthFBO);
    FB().DestroyColorTarget(QualityState().postColorTex, QualityState().postFBO);
    FB().DestroyColorTarget(QualityState().ssaoTex, QualityState().ssaoFBO);
    FB().DestroyColorTarget(QualityState().ssaoBlurTex, QualityState().ssaoBlurFBO);
    FB().DestroyColorTarget(QualityState().ssrTex, QualityState().ssrFBO);
    FB().DestroyColorTarget(QualityState().ssrBlurTex, QualityState().ssrBlurFBO);
    FB().DestroyColorTarget(QualityState().ssrInputTex, QualityState().ssrInputFBO);
    FB().DestroyColorTarget(QualityState().debugTex, QualityState().debugFBO);
    FB().DestroyColorTarget(QualityState().bloomExtractTex, QualityState().bloomExtractFBO);
    FB().DestroyColorTarget(QualityState().bloomScratchTex, QualityState().bloomScratchFBO);
    FB().DestroyColorTarget(QualityState().bloomBlurTex, QualityState().bloomBlurFBO);
    FB().DestroyColorTarget(QualityState().exposureTex[0], QualityState().exposureFBO[0]);
    FB().DestroyColorTarget(QualityState().exposureTex[1], QualityState().exposureFBO[1]);
    FB().DestroyMultisampleTarget(QualityState().msaaFBO, QualityState().msaaColorRB, QualityState().msaaReflectionMaskRB, QualityState().msaaDepthStencilRB);
    QualityState().exposureIndex = 0;
    QualityState().currentExposure = 1.0f;
    QualityState().msaaDepthStencilRB = QualityState().msaaReflectionMaskRB = QualityState().msaaColorRB = QualityState().msaaFBO = 0;
    QualityState().msaaReady = false;
    QualityState().postReady = false;
    QualityState().postFxReady = false;
    QualityState().sceneRenderingToMSAA = false;
    QualityState().sceneOpaqueQualityApplied = false;
}

void GUIQuality::DrawTuningMenu()
{
    if (!QualityState().imguiReady || !QualityState().tuningMenuOpen)
        return;

    UpdateQualityDebugPreview();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    FeedTuningMenuMouseState();
    ImGui::NewFrame();
    ImGui::GetIO().MouseDrawCursor = QualityState().tuningMenuOpen;

    ImGui::SetNextWindowSize(ImVec2(780.0f, 800.0f), ImGuiCond_FirstUseEver);
    bool open = QualityState().tuningMenuOpen;
    if (ImGui::Begin("AVP2 OpenGL Renderer - Tools", &open))
    {
        ImGui::TextUnformatted("Renderer tools (Insert) - game input captured while open");
        ImGui::Separator();

        if (ImGui::BeginTabBar("##RendererToolTabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Quality"))
            {
                bool msaa = QualityState().msaa4xEnabled;
                if (ImGui::Checkbox("4x MSAA", &msaa))
                    GUIQuality::Instance().SetMSAA4xEnabled(msaa);

                if (ImGui::CollapsingHeader("SSAO", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    bool ssao = QualityState().ssaoEnabled;
                    if (ImGui::Checkbox("Enabled##SSAO", &ssao))
                        GUIQuality::Instance().SetSSAOEnabled(ssao);
                    ImGui::BeginDisabled(!QualityState().ssaoEnabled);
                    ImGui::SliderFloat("AO strength", &QualityState().ssaoStrength, 0.0f, 5.0f, "%.2f");
                    ImGui::SliderFloat("AO radius (pixels)", &QualityState().ssaoRadiusPixels, 1.0f, 32.0f, "%.1f");
                    ImGui::SliderFloat("AO bias", &QualityState().ssaoBias, 0.0f, 0.30f, "%.3f");
                    ImGui::SliderFloat("Minimum AO", &QualityState().ssaoMinAO, 0.0f, 1.0f, "%.2f");
                    ImGui::SeparatorText("Depth-aware blur");
                    ImGui::SliderFloat("AO blur radius", &QualityState().ssaoBlurRadius, 0.0f, 8.0f, "%.1f px");
                    ImGui::SliderFloat("AO edge depth tolerance", &QualityState().ssaoBlurDepth, 1.0f, 200.0f, "%.1f");
                    ImGui::EndDisabled();
                    if (ImGui::Button("Reset SSAO"))
                        ResetSSAOSettings();
                }

                if (ImGui::CollapsingHeader("SSR", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    bool ssr = QualityState().ssrEnabled;
                    if (ImGui::Checkbox("Enabled##SSR", &ssr))
                        GUIQuality::Instance().SetSSREnabled(ssr);
                    ImGui::BeginDisabled(!QualityState().ssrEnabled);
                    ImGui::SliderFloat("Reflection strength", &QualityState().ssrStrength, 0.0f, 1.5f, "%.2f");
                    ImGui::SliderFloat("Max distance", &QualityState().ssrMaxDistance, 50.0f, 5000.0f, "%.0f");
                    ImGui::SliderInt("Ray steps", &QualityState().ssrSteps, 8, 64);
                    ImGui::SliderFloat("Thickness base", &QualityState().ssrThicknessBase, 0.1f, 20.0f, "%.2f");
                    ImGui::SliderFloat("Thickness scale", &QualityState().ssrThicknessScale, 0.0005f, 0.03f, "%.4f");
                    ImGui::SliderFloat("Normal offset", &QualityState().ssrNormalBias, 0.0f, 5.0f, "%.2f");
                    ImGui::SeparatorText("Depth-aware reflection blur");
                    ImGui::SliderFloat("SSR blur radius", &QualityState().ssrBlurRadius, 0.0f, 8.0f, "%.1f px");
                    ImGui::SliderFloat("SSR edge depth tolerance", &QualityState().ssrBlurDepth, 1.0f, 250.0f, "%.1f");

                    ImGui::SeparatorText("Receiver color / alpha filter");
                    ImGui::Checkbox("Enable receiver filter", &QualityState().ssrFilterEnabled);
                    ImGui::BeginDisabled(!QualityState().ssrFilterEnabled);
                    ImGui::Checkbox("Invert filter", &QualityState().ssrFilterInvert);
                    ImGui::SliderFloat("Hue center", &QualityState().ssrHueCenter, 0.0f, 1.0f, "%.3f");
                    ImGui::SliderFloat("Hue half-width", &QualityState().ssrHueWidth, 0.0f, 0.5f, "%.3f");
                    ImGui::SliderFloat("Saturation min", &QualityState().ssrSatMin, 0.0f, 1.0f, "%.2f");
                    ImGui::SliderFloat("Saturation max", &QualityState().ssrSatMax, 0.0f, 1.0f, "%.2f");
                    if (QualityState().ssrSatMin > QualityState().ssrSatMax)
                        std::swap(QualityState().ssrSatMin, QualityState().ssrSatMax);
                    ImGui::SliderFloat("Value/luminance min", &QualityState().ssrValueMin, 0.0f, 1.0f, "%.2f");
                    ImGui::SliderFloat("Value/luminance max", &QualityState().ssrValueMax, 0.0f, 1.0f, "%.2f");
                    if (QualityState().ssrValueMin > QualityState().ssrValueMax)
                        std::swap(QualityState().ssrValueMin, QualityState().ssrValueMax);
                    ImGui::SliderFloat("Resolved alpha min", &QualityState().ssrAlphaMin, 0.0f, 1.0f, "%.2f");
                    ImGui::SliderFloat("Filter softness", &QualityState().ssrFilterSoftness, 0.001f, 0.20f, "%.3f");
                    ImGui::EndDisabled();
                    ImGui::EndDisabled();
                    if (ImGui::Button("Reset SSR"))
                        ResetSSRSettings();
                }

                if (ImGui::CollapsingHeader("Bloom", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    bool bloom = QualityState().bloomEnabled;
                    if (ImGui::Checkbox("Enabled##Bloom", &bloom))
                        GUIQuality::Instance().SetBloomEnabled(bloom);
                    ImGui::BeginDisabled(!QualityState().bloomEnabled);
                    ImGui::SliderFloat("Threshold", &QualityState().bloomThreshold, 0.0f, 1.0f, "%.2f");
                    ImGui::SliderFloat("Soft knee", &QualityState().bloomSoftKnee, 0.001f, 0.50f, "%.3f");
                    ImGui::SliderFloat("Intensity", &QualityState().bloomIntensity, 0.0f, 3.0f, "%.2f");
                    ImGui::SliderFloat("Blur radius", &QualityState().bloomRadius, 0.25f, 4.0f, "%.2f");
                    ImGui::EndDisabled();
                    if (ImGui::Button("Reset Bloom"))
                        ResetBloomSettings();
                }

                if (ImGui::CollapsingHeader("Dynamic Exposure", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    bool exposure = QualityState().dynamicExposureEnabled;
                    if (ImGui::Checkbox("Enabled##DynamicExposure", &exposure))
                        GUIQuality::Instance().SetDynamicExposureEnabled(exposure);
                    ImGui::BeginDisabled(!QualityState().dynamicExposureEnabled);
                    ImGui::SliderFloat("Baseline exposure", &QualityState().exposureBaseline, 0.50f, 1.50f, "%.2f");
                    ImGui::SliderFloat("Dark-area max exposure", &QualityState().exposureDarkMax, 1.00f, 2.00f, "%.2f");
                    if (QualityState().exposureDarkMax < QualityState().exposureBaseline)
                        QualityState().exposureDarkMax = QualityState().exposureBaseline;
                    ImGui::SliderFloat("Dark threshold", &QualityState().exposureDarkThreshold, 0.02f, 0.60f, "%.2f");
                    ImGui::SliderFloat("Adaptation speed", &QualityState().exposureAdaptSpeed, 0.05f, 10.0f, "%.2f");
                    ImGui::TextDisabled("Color-neutral exposure only: one scalar multiplies RGB equally. No tone curve, gamma, saturation, or contrast changes.");
                    ImGui::EndDisabled();
                    if (ImGui::Button("Reset Dynamic Exposure"))
                        ResetDynamicExposureSettings();
                }
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Timing"))
            {
                ImGui::TextWrapped("Global fixed gameplay/server quantization is disabled. Input, camera, PlayerMovement and the server shell run at the real frame cadence.");
                ImGui::Spacing();
                ImGui::TextDisabled("High refresh keeps Talon server scheduling stock; client game dt and Door movement integration use the real outer-frame delta.");
                ImGui::TextDisabled("Door displacement remains speed * real server frame delta; no source-level ObjectDLL rebuild is required.");
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Deluxe Lightmapper"))
            {
                ImGui::TextWrapped("Bakes a classic deluxemap: normalized dominant incoming-light direction using Talon's static lights, live/blended LightGroups, spot/directional sources, and static sunlight. Existing RGB lightmaps remain the lighting/intensity authority.");
                ImGui::Spacing();

                if (ImGui::Button("Bake / Rebuild Direction Atlas", ImVec2(250, 0)))
                {
                    if (DeluxeLightmapBaker::Instance().BakeDirections())
                        DeluxeLightmapBaker::Instance().SetSpecularEnabled(true);
                }
                ImGui::SameLine();
                if (ImGui::Button("Clear Atlas"))
                    DeluxeLightmapBaker::Instance().ClearDirections();

                ImGui::Text("Status: %s", DeluxeLightmapBaker::Instance().Status());
                ImGui::Text("Baked polygons: %u", DeluxeLightmapBaker::Instance().BakedPolys());
                ImGui::Text("Baked luxels: %u", DeluxeLightmapBaker::Instance().BakedLuxels());
                ImGui::TextDisabled("Static sunlight is accepted only through compiled SkyPortal/SURF_SKY polygons and only on DirectionalLight-enabled surfaces.");
                ImGui::TextDisabled("LightGroups update live: deluxe direction is rebuilt only for affected tiles and weighted by the same LMAnim blend used by Talon's RGB lightmap.");

                ImGui::SeparatorText("Debug visualization");
                bool debugDirection = DeluxeLightmapBaker::Instance().DebugDirectionView();
                if (ImGui::Checkbox("View directional lightmap on world", &debugDirection))
                    DeluxeLightmapBaker::Instance().SetDebugDirectionView(debugDirection);
                ImGui::TextDisabled("Shows raw tangent-space deluxemap RGB on lightmapped PhysicsBSP/Terrain and WorldModels. T=R, -V=G (OpenGL green convention), N=B; lit surfaces should vary like a normal map and unlit/directionless luxels now fall back to neutral blue-purple. All diffuse/static/dynamic lighting, specular and fog are bypassed while enabled; black = no lightmap UV.");

                ImGui::SeparatorText("Deluxe material response");
                bool deluxeSpec = DeluxeLightmapBaker::Instance().SpecularEnabled();
                if (ImGui::Checkbox("Enable deluxe specular", &deluxeSpec))
                    DeluxeLightmapBaker::Instance().SetSpecularEnabled(deluxeSpec);
                float specStrength = DeluxeLightmapBaker::Instance().SpecularStrength();
                if (ImGui::SliderFloat("Blinn-Phong strength", &specStrength, 0.0f, 6.0f, "%.2f"))
                    DeluxeLightmapBaker::Instance().SetSpecularStrength(specStrength);
                float specPower = DeluxeLightmapBaker::Instance().SpecularPower();
                if (ImGui::SliderFloat("Blinn-Phong power", &specPower, 1.0f, 256.0f, "%.0f"))
                    DeluxeLightmapBaker::Instance().SetSpecularPower(specPower);
                float specLightColor = DeluxeLightmapBaker::Instance().SpecLightColorInfluence();
                if (ImGui::SliderFloat("Specular light color influence", &specLightColor, 0.0f, 1.0f, "%.2f"))
                    DeluxeLightmapBaker::Instance().SetSpecLightColorInfluence(specLightColor);
                ImGui::TextDisabled("0 = white highlight, 1 = fully tinted by baked lightmap color.");

                ImGui::SeparatorText("Generated normal from albedo");
                bool genNormal = DeluxeLightmapBaker::Instance().GeneratedNormalEnabled();
                if (ImGui::Checkbox("Generate normal map from albedo", &genNormal))
                    DeluxeLightmapBaker::Instance().SetGeneratedNormalEnabled(genNormal);
                ImGui::BeginDisabled(!genNormal);
                float normalStrength = DeluxeLightmapBaker::Instance().NormalStrength();
                if (ImGui::SliderFloat("Normal strength", &normalStrength, 0.0f, 12.0f, "%.2f"))
                    DeluxeLightmapBaker::Instance().SetNormalStrength(normalStrength);
                float normalBlack = DeluxeLightmapBaker::Instance().NormalBlack();
                float normalWhite = DeluxeLightmapBaker::Instance().NormalWhite();
                if (ImGui::SliderFloat("Normal levels black", &normalBlack, 0.0f, 0.99f, "%.3f"))
                {
                    normalBlack = std::min(normalBlack, normalWhite - 0.001f);
                    DeluxeLightmapBaker::Instance().SetNormalBlack(normalBlack);
                }
                if (ImGui::SliderFloat("Normal levels white", &normalWhite, 0.01f, 1.0f, "%.3f"))
                {
                    normalWhite = std::max(normalWhite, normalBlack + 0.001f);
                    DeluxeLightmapBaker::Instance().SetNormalWhite(normalWhite);
                }
                bool normalInvert = DeluxeLightmapBaker::Instance().NormalInvert();
                if (ImGui::Checkbox("Invert generated height", &normalInvert))
                    DeluxeLightmapBaker::Instance().SetNormalInvert(normalInvert);
                bool normalInvertX = DeluxeLightmapBaker::Instance().NormalInvertX();
                bool normalInvertY = DeluxeLightmapBaker::Instance().NormalInvertY();
                bool normalInvertZ = DeluxeLightmapBaker::Instance().NormalInvertZ();
                if (ImGui::Checkbox("Invert normal X", &normalInvertX))
                    DeluxeLightmapBaker::Instance().SetNormalInvertX(normalInvertX);
                ImGui::SameLine();
                if (ImGui::Checkbox("Invert normal Y", &normalInvertY))
                    DeluxeLightmapBaker::Instance().SetNormalInvertY(normalInvertY);
                ImGui::SameLine();
                if (ImGui::Checkbox("Invert normal Z", &normalInvertZ))
                    DeluxeLightmapBaker::Instance().SetNormalInvertZ(normalInvertZ);
                int normalBand = DeluxeLightmapBaker::Instance().NormalBand();
                const char *normalBands[] = {"Low frequency (broad)", "Mid frequency", "High frequency (fine)"};
                if (ImGui::Combo("Normal source band", &normalBand, normalBands, 3))
                    DeluxeLightmapBaker::Instance().SetNormalBand(normalBand);
                ImGui::EndDisabled();

                ImGui::SeparatorText("Generated specular from albedo");
                bool genSpec = DeluxeLightmapBaker::Instance().GeneratedSpecularEnabled();
                if (ImGui::Checkbox("Generate specular map from albedo", &genSpec))
                    DeluxeLightmapBaker::Instance().SetGeneratedSpecularEnabled(genSpec);
                ImGui::BeginDisabled(!genSpec);
                float specMapStrength = DeluxeLightmapBaker::Instance().SpecMapStrength();
                if (ImGui::SliderFloat("Specular map strength", &specMapStrength, 0.0f, 4.0f, "%.2f"))
                    DeluxeLightmapBaker::Instance().SetSpecMapStrength(specMapStrength);
                float specBlack = DeluxeLightmapBaker::Instance().SpecBlack();
                float specWhite = DeluxeLightmapBaker::Instance().SpecWhite();
                if (ImGui::SliderFloat("Specular levels black", &specBlack, 0.0f, 0.99f, "%.3f"))
                {
                    specBlack = std::min(specBlack, specWhite - 0.001f);
                    DeluxeLightmapBaker::Instance().SetSpecBlack(specBlack);
                }
                if (ImGui::SliderFloat("Specular levels white", &specWhite, 0.01f, 1.0f, "%.3f"))
                {
                    specWhite = std::max(specWhite, specBlack + 0.001f);
                    DeluxeLightmapBaker::Instance().SetSpecWhite(specWhite);
                }
                bool specInvert = DeluxeLightmapBaker::Instance().SpecInvert();
                if (ImGui::Checkbox("Invert generated specular", &specInvert))
                    DeluxeLightmapBaker::Instance().SetSpecInvert(specInvert);
                ImGui::EndDisabled();

                float directionRadiusScale = DeluxeLightmapBaker::Instance().DirectionRadiusScale();
                if (ImGui::SliderFloat("Direction radius scale", &directionRadiusScale, 1.0f, 8.0f, "%.2fx"))
                    DeluxeLightmapBaker::Instance().SetDirectionRadiusScale(directionRadiusScale);
                ImGui::TextDisabled("Extends only the deluxe direction field; Talon's RGB lightmap radius/intensity is unchanged. Changing this clears the old atlas; rebuild required. 3x is the default test value.");

                float sunSoftness = DeluxeLightmapBaker::Instance().SunEdgeSoftness();
                if (ImGui::SliderFloat("Sun edge softness", &sunSoftness, 0.0f, 4.0f, "%.2f luxels"))
                    DeluxeLightmapBaker::Instance().SetSunEdgeSoftness(sunSoftness);
                ImGui::TextDisabled("0 = hard sky visibility. Higher values supersample a wider lightmap-space footprint; rebuild required.");
                int dirBlur = DeluxeLightmapBaker::Instance().DirectionBlurRadius();
                if (ImGui::SliderInt("Direction blur radius", &dirBlur, 0, 8, "%d luxels"))
                    DeluxeLightmapBaker::Instance().SetDirectionBlurRadius(dirBlur);
                ImGui::TextDisabled("Direction blur is tile-local and requires a rebuild. Albedo normal/spec controls are live.");
                ImGui::TextDisabled("Diffuse remains Talon's existing RGB lightmap; generated channels affect only the deluxe specular test.");

                ImGui::SeparatorText("Direction atlas");
                const GLuint deluxeTex = static_cast<GLuint>(DeluxeLightmapBaker::Instance().Texture());
                if (deluxeTex)
                {
                    const float usedV = std::clamp(float(DeluxeLightmapBaker::Instance().AtlasUsedHeight()) / 4096.0f, 1.0f / 4096.0f, 1.0f);
                    const float avail = std::max(200.0f, ImGui::GetContentRegionAvail().x);
                    const float w = std::min(avail, 730.0f);
                    const float h = std::max(80.0f, w * usedV);
                    ImGui::Image(static_cast<ImTextureID>(static_cast<uintptr_t>(deluxeTex)),
                                 ImVec2(w, h), ImVec2(0, 0), ImVec2(1, usedV));
                    ImGui::TextDisabled("RGB = normalized tangent-space incoming-light direction (T,-V,N). Alpha = smooth directional support/visibility; Talon's RGB lightmap remains the light-energy authority. Neutral blue-purple = no dominant direction.");
                }
                else
                {
                    ImGui::TextDisabled("No direction atlas baked for the current level.");
                }
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Materials"))
            {
                auto &materials = MaterialAuthoringSystem::Instance();
                ImGui::TextWrapped("This editor is scoped to materials referenced by the currently loaded map. Loose authored world materials are read from ./textures first. For a base foo.dtx use foo_n.dtx for tangent-space normal and foo_s.dtx for RGB specular + alpha gloss. Generated deluxe material channels remain the fallback when authored maps are absent.");
                ImGui::TextDisabled("Material root: %s", materials.RootDirectory().c_str());

                static int createCount = -1;
                if (ImGui::Button("Create missing .mat files for this map"))
                    createCount = materials.CreateMissingMaterialFilesForActiveMap();
                ImGui::SameLine();
                if (ImGui::Button("Reload authored materials"))
                {
                    materials.ReloadAll();
                    MaterialOpaquePreviewCache::Instance().Clear();
                }
                if (createCount >= 0)
                    ImGui::Text("Created %d material file(s).", createCount);

                const std::vector<std::string> keys = materials.MaterialKeys();
                ImGui::Text("Map materials: %u", static_cast<unsigned>(keys.size()));
                static int selected = 0;
                if (selected >= static_cast<int>(keys.size())) selected = std::max(0, static_cast<int>(keys.size()) - 1);
                if (keys.empty())
                {
                    ImGui::TextDisabled("No materials have been registered for the current map yet.");
                }
                else
                {
                    ImGui::Separator();
                    const float totalWidth = ImGui::GetContentRegionAvail().x;
                    const float paletteWidth = std::clamp(totalWidth * 0.38f, 220.0f, 420.0f);
                    ImGui::BeginChild("MaterialPalette", ImVec2(paletteWidth, 0.0f), true);
                    ImGui::TextUnformatted("Palette");
                    ImGui::Separator();
                    const float thumbSize = 72.0f;
                    const float tileWidth = thumbSize + 16.0f;
                    const float avail = std::max(thumbSize, ImGui::GetContentRegionAvail().x);
                    const int columns = std::max(1, static_cast<int>(avail / tileWidth));
                    for (int i = 0; i < static_cast<int>(keys.size()); ++i)
                    {
                        if (i > 0 && (i % columns) != 0)
                            ImGui::SameLine();
                        AuthoredMaterialBinding thumbBinding{};
                        materials.GetBinding(keys[i], thumbBinding);
                        const GLuint thumbTex = thumbBinding.albedoTexture ? thumbBinding.albedoTexture : (thumbBinding.normalTexture ? thumbBinding.normalTexture : thumbBinding.specularTexture);
                        ImGui::PushID(i);
                        ImGui::BeginGroup();
                        const ImVec2 p0 = ImGui::GetCursorScreenPos();
                        if (thumbTex)
                        {
                            const GLuint opaqueThumb = MaterialOpaquePreviewCache::Instance().Get(thumbTex);
                            ImGui::Image(static_cast<ImTextureID>(static_cast<uintptr_t>(opaqueThumb)), ImVec2(thumbSize, thumbSize), ImVec2(0, 1), ImVec2(1, 0));
                        }
                        else
                            ImGui::Dummy(ImVec2(thumbSize, thumbSize));
                        if (ImGui::IsItemClicked()) selected = i;
                        const ImVec2 p1(p0.x + thumbSize, p0.y + thumbSize);
                        ImU32 border = (selected == i) ? IM_COL32(255, 200, 64, 255) : IM_COL32(96, 96, 96, 255);
                        ImGui::GetWindowDrawList()->AddRect(p0, p1, border, 0.0f, 0, (selected == i) ? 3.0f : 1.0f);
                        ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + thumbSize + 4.0f);
                        ImGui::TextWrapped("%s", MaterialLeafName(keys[i]));
                        ImGui::PopTextWrapPos();
                        ImGui::EndGroup();
                        ImGui::PopID();
                    }
                    ImGui::EndChild();

                    ImGui::SameLine();
                    ImGui::BeginChild("MaterialInspector", ImVec2(0.0f, 0.0f), false);

                    AuthoredMaterialSettings ms{};
                    AuthoredMaterialBinding binding{};
                    materials.GetBinding(keys[selected], binding);
                    if (materials.GetSettings(keys[selected], ms))
                    {
                        ImGui::Text("Selected: %s", keys[selected].c_str());
                        ImGui::TextDisabled("Source: %s", binding.sourceTexture.empty() ? "<unknown>" : binding.sourceTexture.c_str());
                        ImGui::TextDisabled(".mat: %s", binding.matPath.empty() ? "<none>" : binding.matPath.c_str());
                        ImGui::TextDisabled("Authoring assets: albedo=%s normal=%s spec=%s refl=%s", binding.albedoTexture ? "yes" : "no", binding.normalTexture ? "yes" : "no", binding.specularTexture ? "yes" : "no", binding.reflectionTexture ? "yes" : "no");

                        static bool previewUseNormal = true;
                        static bool previewUseSpec = true;
                        auto &preview = MaterialPreviewRenderer::Instance();
                        ImGui::Checkbox("Preview normal map", &previewUseNormal); ImGui::SameLine();
                        ImGui::Checkbox("Preview specular map", &previewUseSpec);
                        if (ImGui::Button("Reset view")) preview.ResetView();
                        ImGui::SameLine();
                        if (ImGui::Button(preview.AutoRotateEnabled() ? "Stop auto rotate" : "Start auto rotate"))
                            preview.SetAutoRotate(!preview.AutoRotateEnabled());
                        float rotateSpeed = preview.AutoRotateSpeed();
                        if (ImGui::SliderFloat("Rotate speed", &rotateSpeed, -4.0f, 4.0f, "%.2f"))
                            preview.SetAutoRotateSpeed(rotateSpeed);
                        const float previewAvail = std::max(220.0f, ImGui::GetContentRegionAvail().x);
                        const float previewW = std::min(previewAvail, 460.0f);
                        const GLuint previewTex = preview.Render(binding, ms, 512, previewUseNormal, previewUseSpec);
                        if (previewTex)
                        {
                            ImGui::Image(static_cast<ImTextureID>(static_cast<uintptr_t>(previewTex)), ImVec2(previewW, previewW), ImVec2(0, 1), ImVec2(1, 0));
                            if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
                                preview.DragOrbit(ImGui::GetIO().MouseDelta.x, ImGui::GetIO().MouseDelta.y);
                            if (ImGui::IsItemHovered())
                                ImGui::SetTooltip("Drag with left mouse to orbit the preview sphere.");
                        }
                        else
                            ImGui::TextDisabled("Material preview unavailable.");

                        ImGui::SeparatorText("Maps");
                        auto drawMapThumb = [&](const char *label, GLuint tex)
                        {
                            ImGui::BeginGroup();
                            ImGui::TextUnformatted(label);
                            if (tex)
                            {
                                const GLuint opaqueTex = MaterialOpaquePreviewCache::Instance().Get(tex);
                                ImGui::Image(static_cast<ImTextureID>(static_cast<uintptr_t>(opaqueTex)), ImVec2(96, 96), ImVec2(0, 1), ImVec2(1, 0));
                            }
                            else
                                ImGui::Dummy(ImVec2(96, 96));
                            ImGui::EndGroup();
                        };
                        drawMapThumb("Albedo", binding.albedoTexture); ImGui::SameLine();
                        drawMapThumb("Normal", binding.normalTexture); ImGui::SameLine();
                        drawMapThumb("Spec", binding.specularTexture); ImGui::SameLine();
                        drawMapThumb("Refl", binding.reflectionTexture);

                        bool changed=false;
                        changed |= ImGui::SliderFloat("Normal strength", &ms.normalStrength, 0.0f, 4.0f, "%.2f");
                        changed |= ImGui::SliderFloat("Specular strength", &ms.specularStrength, 0.0f, 4.0f, "%.2f");
                        changed |= ImGui::SliderFloat("Gloss min power", &ms.glossMinPower, 1.0f, 128.0f, "%.0f");
                        changed |= ImGui::SliderFloat("Gloss max power", &ms.glossMaxPower, std::max(2.0f,ms.glossMinPower), 512.0f, "%.0f");
                        changed |= ImGui::SliderFloat("Gloss alpha bias", &ms.glossBias, -1.0f, 1.0f, "%.2f");
                        changed |= ImGui::SliderFloat("Reflection strength (SSR)", &ms.reflectionStrength, 0.0f, 1.0f, "%.2f");

                        static char reflectionBuf[260]{};
                        static std::string reflectionKey;
                        if(reflectionKey!=keys[selected])
                        {
                            reflectionKey=keys[selected];
                            std::strncpy(reflectionBuf,ms.reflectionMap.c_str(),sizeof(reflectionBuf)-1);
                            reflectionBuf[sizeof(reflectionBuf)-1]=0;
                        }
                        if(ImGui::InputText("Reflection map",reflectionBuf,sizeof(reflectionBuf)))
                        {
                            ms.reflectionMap=reflectionBuf; changed=true;
                        }
                        ImGui::TextDisabled("Reflection: no .mat = legacy SSR heuristic; .mat uses strength and optional map as the SSR receiver mask.");

                        if(changed) materials.SetSettings(keys[selected],ms,false);
                        if(ImGui::Button("Save .mat")) materials.SetSettings(keys[selected],ms,true);
                        ImGui::SameLine();
                        if(ImGui::Button("Save + Reload maps"))
                        {
                            materials.SetSettings(keys[selected],ms,true);
                            materials.ReloadAll();
                            MaterialOpaquePreviewCache::Instance().Clear();
                        }
                    }
                    ImGui::EndChild();
                }
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Buffers"))
            {
                ImGui::TextUnformatted("Post-process / FBO inspection");
                static const char *views[] = {"Off", "Final logical color", "SSR input color", "Linear depth", "SSAO raw", "SSAO blurred", "SSR raw reflection", "SSR blurred reflection", "SSR material receiver mask", "Bloom extract", "Bloom blurred"};
                ImGui::Combo("Buffer", &QualityState().qualityDebugView, views, static_cast<int>(sizeof(views) / sizeof(views[0])));
                if (QualityState().qualityDebugView > 0 && QualityState().debugTex)
                {
                    const float avail = std::max(200.0f, ImGui::GetContentRegionAvail().x);
                    const float w = std::min(avail, 720.0f);
                    const float h = w * (static_cast<float>(RendererCore::Instance().Height()) / std::max(1, RendererCore::Instance().Width()));
                    ImGui::Image(static_cast<ImTextureID>(static_cast<uintptr_t>(QualityState().debugTex)), ImVec2(w, h), ImVec2(0, 1), ImVec2(1, 0));
                }
                ImGui::TextDisabled("SSR input is captured immediately before the SSR ray pass.");
                ImGui::Text("Post target: %s", QualityState().postReady ? "ready" : "unavailable");
                ImGui::Text("MSAA target: %s", QualityState().msaaReady ? "ready" : "unavailable");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        ImGui::Separator();
        ImGui::TextDisabled("Ctrl+2/3/4 toggles remain available. Insert returns all input to AVP2.");
    }
    ImGui::End();
    if (!open)
        GUIQuality::Instance().SetTuningMenuOpen(false);

    ImGui::Render();
    FB().BindLogical();
    glViewport(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height());
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // Dear ImGui owns raw GL state internally (including glUseProgram), so our
    // renderer-side state cache must forget its bindings before normal draws resume.
    avp2::render::GLStateCache::Instance().Invalidate();
    PresenterState().screenShadowValid = false;
    RendererPresenter::Instance().InvalidateScreenRect(nullptr);
    PresenterState().frameHasPresentableContent = true;
}

void GUIQuality::SetTuningMenuOpen(bool open)
{
    if (open && !QualityState().imguiReady)
        return;
    QualityState().tuningMenuOpen = open;
    if (QualityState().imguiReady)
        ImGui::GetIO().MouseDrawCursor = open;

    if (open)
    {
        // Talon normally confines and recenters the cursor for relative-look.
        // The SetCursorPos call is suppressed by the renderer_exports IAT hook
        // while this flag is true; also release any active ClipCursor region.
        ClipCursor(nullptr);
    }
    else if (RendererCore::Instance().Window() && GetForegroundWindow() == RendererCore::Instance().Window())
    {
        // Put confinement back immediately. Talon's own SetCursorPos resumes on
        // the next host frame because QualityState().tuningMenuOpen is now false.
        RECT rc{};
        if (GetClientRect(RendererCore::Instance().Window(), &rc))
        {
            POINT tl{rc.left, rc.top}, br{rc.right, rc.bottom};
            if (ClientToScreen(RendererCore::Instance().Window(), &tl) && ClientToScreen(RendererCore::Instance().Window(), &br))
            {
                RECT screenRc{tl.x, tl.y, br.x, br.y};
                ClipCursor(&screenRc);
            }
        }
    }
    LOG_SESSION("Renderer Insert tuning menu -> %d cursor=%s", open ? 1 : 0, open ? "released" : "game-controlled");
}

bool GUIQuality::IsTuningMenuOpen() const { return QualityState().tuningMenuOpen; }

bool GUIQuality::HandleImGuiWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, LRESULT *outResult)
{
    if (!QualityState().imguiReady || !QualityState().tuningMenuOpen)
        return false;
    const LRESULT r = ImGui_ImplWin32_WndProcHandler(hwnd, msg, wp, lp);
    if (outResult)
        *outResult = r;
    switch (msg)
    {
    case WM_INPUT:
        // MSP handles raw mouse input in its own window procedure, independently
        // of Talon's DirectInput/axis callbacks. Do not forward this message to
        // that procedure while the panel owns input. ImGui uses WM_MOUSEMOVE.
        // Foreground raw input still requires DefWindowProc for OS cleanup.
        if (GET_RAWINPUT_CODE_WPARAM(wp) == RIM_INPUT)
            DefWindowProc(hwnd, msg, wp, lp);
        if (outResult)
            *outResult = 0;
        return true;
    case WM_MOUSEMOVE:
    case WM_MOUSEWHEEL:
    case WM_MOUSEHWHEEL:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDBLCLK:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_XBUTTONDBLCLK:
        // While the renderer menu is open the mouse belongs to ImGui, not
        // AVP2/DirectInput.  Always consume client mouse messages after
        // forwarding them to the backend so clicks cannot leak to the game.
        return true;
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_CHAR:
        return true;
    default:
        return false;
    }
}

void GUIQuality::BeginScene(const SceneDesc *scene)
{
    QualityState().sceneRenderingToMSAA = false;
    QualityState().sceneOpaqueQualityApplied = false;
    if (!scene || scene->m_nDrawMode != DRAWMODE_NORMAL)
        return;
    // Receiver coverage is rebuilt by scene geometry every frame.
    FB().ClearReflectionMask(FB().Logical());
    if (!QualityState().msaa4xEnabled || !QualityState().msaaReady)
        return;
    Renderer2D::Instance().Flush();
    FB().Bind(GL_READ_FRAMEBUFFER, FB().Logical());
    FB().Bind(GL_DRAW_FRAMEBUFFER, QualityState().msaaFBO);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    FB().Blit(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), 0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(),
              GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, GL_NEAREST);
    FB().Bind(GL_FRAMEBUFFER, QualityState().msaaFBO);
    const GLenum sceneDrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT0 + 1};
    glf.DrawBuffers(2, sceneDrawBuffers);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    FB().ClearReflectionMask(QualityState().msaaFBO);
    glViewport(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height());
    QualityState().sceneRenderingToMSAA = true;
}

void GUIQuality::ApplyOpaqueScene(const SceneDesc *scene)
{
    if (QualityState().sceneOpaqueQualityApplied || !scene || scene->m_nDrawMode != DRAWMODE_NORMAL)
        return;
    QualityState().sceneOpaqueQualityApplied = true;

    if (!(QualityState().ssaoEnabled || QualityState().ssrEnabled) || !QualityState().postReady)
        return;

    Renderer2D::Instance().Flush();
    const bool resumeMSAA = QualityState().sceneRenderingToMSAA;

    // Resolve the opaque/chromakey scene so SSAO/SSR see only depth-writing
    // geometry.  Translucent models/brushes, particles, sprites, ReallyClose
    // weapons and later Talon overlays are intentionally submitted afterwards.
    if (resumeMSAA)
    {
        FB().Bind(GL_READ_FRAMEBUFFER, QualityState().msaaFBO);
        FB().Bind(GL_DRAW_FRAMEBUFFER, FB().Logical());
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        FB().Blit(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), 0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(),
                  GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, GL_NEAREST);
        // Resolve the authored/legacy SSR receiver attachment independently.
        glReadBuffer(GL_COLOR_ATTACHMENT0 + 1);
        glDrawBuffer(GL_COLOR_ATTACHMENT0 + 1);
        FB().Blit(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), 0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(),
                  GL_COLOR_BUFFER_BIT, GL_NEAREST);
        FB().BindLogical();
    }

    QualityState().lastQualityNear = 1.0f;
    QualityState().lastQualityFar = std::max(2.0f, scene->m_fFarZ);
    CopySceneDepthToPostTexture();

    const auto savedGL = avp2::render::GLStateCache::Instance().Capture();
    if (QualityState().ssaoEnabled)
        RunSSAOPass(scene);
    if (QualityState().ssrEnabled)
        RunSSRPass(scene);
    avp2::render::GLStateCache::Instance().Restore(savedGL);

    // Continue the remaining Talon 3D phases in the multisample target when
    // 4x AA is active.  This copies the processed opaque color plus the same
    // opaque depth/stencil back before transparent/effect submission.
    if (resumeMSAA)
    {
        FB().Bind(GL_READ_FRAMEBUFFER, FB().Logical());
        FB().Bind(GL_DRAW_FRAMEBUFFER, QualityState().msaaFBO);
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        FB().Blit(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), 0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(),
                  GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, GL_NEAREST);
        FB().Bind(GL_FRAMEBUFFER, QualityState().msaaFBO);
        const GLenum resumeDrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT0 + 1};
        glf.DrawBuffers(2, resumeDrawBuffers);
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glViewport(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height());
    }
    else
        FB().BindLogical();

    PresenterState().screenShadowValid = false;
    RendererPresenter::Instance().InvalidateScreenRect(nullptr);
    PresenterState().frameHasPresentableContent = true;

    static int budget = 64;
    if (LogIsSessionEnabled() && ((budget > 0 && budget--)))
        LOG_SESSION("QUALITY OPAQUE-COMPOSITE ssao=%d ssr=%d msaaResume=%d phase=BEFORE-TRANSLUCENT",
                    QualityState().ssaoEnabled ? 1 : 0, QualityState().ssrEnabled ? 1 : 0, resumeMSAA ? 1 : 0);
}

void GUIQuality::EndScene(const SceneDesc *scene)
{
    if (!scene || scene->m_nDrawMode != DRAWMODE_NORMAL)
    {
        if (QualityState().sceneRenderingToMSAA)
            FB().BindLogical();
        QualityState().sceneRenderingToMSAA = false;
        QualityState().sceneOpaqueQualityApplied = false;
        return;
    }

    // SSAO/SSR have already been composited at the opaque/chromakey
    // checkpoint.  EndSceneQuality now only performs the final MSAA resolve,
    // leaving every later translucent/effect/ReallyClose layer untouched.
    if (QualityState().sceneRenderingToMSAA)
    {
        FB().Bind(GL_READ_FRAMEBUFFER, QualityState().msaaFBO);
        FB().Bind(GL_DRAW_FRAMEBUFFER, FB().Logical());
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        FB().Blit(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), 0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(),
                  GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, GL_NEAREST);
        // Resolve the authored/legacy SSR receiver attachment independently.
        glReadBuffer(GL_COLOR_ATTACHMENT0 + 1);
        glDrawBuffer(GL_COLOR_ATTACHMENT0 + 1);
        FB().Blit(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(), 0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height(),
                  GL_COLOR_BUFFER_BIT, GL_NEAREST);
        FB().BindLogical();
        QualityState().sceneRenderingToMSAA = false;
    }
    RunBloomAndExposureComposite();
    QualityState().sceneOpaqueQualityApplied = false;
}

void GUIQuality::SetMSAA4xEnabled(bool e)
{
    const bool v = e && QualityState().msaaReady;
    if (QualityState().msaa4xEnabled == v)
        return;
    QualityState().msaa4xEnabled = v;
    RendererSettings::Instance().SaveCurrent();
    LOG_SESSION("Renderer Ctrl+2 4x MSAA -> %d%s", QualityState().msaa4xEnabled ? 1 : 0, (!QualityState().msaaReady && e) ? " (target unavailable)" : "");
}
bool GUIQuality::IsMSAA4xEnabled() const { return QualityState().msaa4xEnabled; }
void GUIQuality::SetSSAOEnabled(bool e)
{
    const bool v = e && QualityState().postReady;
    if (QualityState().ssaoEnabled == v)
        return;
    QualityState().ssaoEnabled = v;
    RendererSettings::Instance().SaveCurrent();
    LOG_SESSION("Renderer Ctrl+3 SSAO -> %d%s", QualityState().ssaoEnabled ? 1 : 0, (!QualityState().postReady && e) ? " (post target unavailable)" : "");
}
bool GUIQuality::IsSSAOEnabled() const { return QualityState().ssaoEnabled; }
void GUIQuality::SetSSREnabled(bool e)
{
    const bool v = e && QualityState().postReady;
    if (QualityState().ssrEnabled == v)
        return;
    QualityState().ssrEnabled = v;
    RendererSettings::Instance().SaveCurrent();
    LOG_SESSION("Renderer Ctrl+4 SSR -> %d%s", QualityState().ssrEnabled ? 1 : 0, (!QualityState().postReady && e) ? " (post target unavailable)" : "");
}
bool GUIQuality::IsSSREnabled() const { return QualityState().ssrEnabled; }
void GUIQuality::SetBloomEnabled(bool e)
{
    const bool v = e && QualityState().postFxReady;
    if (QualityState().bloomEnabled == v)
        return;
    QualityState().bloomEnabled = v;
    RendererSettings::Instance().SaveCurrent();
    LOG_SESSION("Renderer Bloom -> %d%s", v ? 1 : 0, (!QualityState().postFxReady && e) ? " (post target unavailable)" : "");
}
bool GUIQuality::IsBloomEnabled() const { return QualityState().bloomEnabled; }
void GUIQuality::SetDynamicExposureEnabled(bool e)
{
    const bool v = e && QualityState().postFxReady;
    if (QualityState().dynamicExposureEnabled == v)
        return;
    QualityState().dynamicExposureEnabled = v;
    RendererSettings::Instance().SaveCurrent();
    LOG_SESSION("Renderer Dynamic Exposure -> %d%s", v ? 1 : 0, (!QualityState().postFxReady && e) ? " (post target unavailable)" : "");
}
bool GUIQuality::IsDynamicExposureEnabled() const { return QualityState().dynamicExposureEnabled; }

void GUIQuality::ApplyGlobalLightScale(const LTVector &scale, bool invertHack)
{
    if (!RendererCore::Instance().ScenePostShader())
        return;

    // Exact early-out window in d3d.ren 0x10015269..0x100152CE:
    // only values strictly inside (0.99,1.01) count as identity, and
    // InvertHack overrides that early-out.
    const bool identity =
        scale.x > 0.99f && scale.x < 1.01f &&
        scale.y > 0.99f && scale.y < 1.01f &&
        scale.z > 0.99f && scale.z < 1.01f;
    if (identity && !invertHack)
        return;

    Renderer2D::Instance().Flush();

    // d3d.ren chooses 255.0 when InvertHack is set and 127.5 otherwise,
    // truncates each product toward zero, then stores the low byte as D3DCOLOR.
    const float factor = invertHack ? 255.0f : 127.5f;
    const auto stockByte = [&](float v) -> uint8_t
    {
        return static_cast<uint8_t>(static_cast<int32_t>(v * factor));
    };
    const uint8_t r = stockByte(scale.x);
    const uint8_t g = stockByte(scale.y);
    const uint8_t b = stockByte(scale.z);

    const auto savedGL = avp2::render::GLStateCache::Instance().Capture();

    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);
    GLStateDisable(GL_CULL_FACE);
    GLStateEnable(GL_BLEND);
    avp2::render::GLStateCache::Instance().SetBlendEquation(GL_FUNC_ADD_);

    if (invertHack)
    {
        // d3d.ren: D3DBLEND_INVDESTCOLOR / D3DBLEND_ZERO.
        // With the normally-white source this is exactly 1 - framebuffer.
        GLStateBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
    }
    else
    {
        // d3d.ren: D3DBLEND_DESTCOLOR / D3DBLEND_SRCCOLOR.  The 127.5
        // source coefficient makes the two blend terms sum to scale*dest.
        GLStateBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
    }

    RendererCore::Instance().ScenePostShader()->Use();
    GLUniform4f(RendererCore::Instance().ScenePostColorUniform(), r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    GLStateBindVertexArray(RendererCore::Instance().ScreenQuadVao());
    glf.DrawArrays(GL_TRIANGLES_, 0, 3);

    ++PresenterState().frameDrawCalls;
    PresenterState().frameHasPresentableContent = true;
    PresenterState().screenShadowValid = false;
    RendererPresenter::Instance().InvalidateScreenRect(nullptr);

    avp2::render::GLStateCache::Instance().Restore(savedGL);

    static int lastInvert = -1;
    const int nowInvert = invertHack ? 1 : 0;
    if (LogIsSessionEnabled() && lastInvert != nowInvert)
    {
        lastInvert = nowInvert;
        LOG_SESSION("D3D-SCENE-POST InvertHack=%d scale=(%.3f %.3f %.3f) color=(%u %u %u) blend=%s path=D3D-0x10015240",
                    nowInvert, scale.x, scale.y, scale.z, unsigned(r), unsigned(g), unsigned(b),
                    invertHack ? "INVDEST/ZERO" : "DESTCOLOR/SRCCOLOR");
    }
}

void GUIQuality::ApplyGlobalLightAdd(const LTVector &add)
{
    if (!RendererCore::Instance().ScenePostShader())
        return;

    // d3d.ren 0x10014F63..0x10014F90: skip only when all three components
    // are below 0.001.  The stock path then truncates component*255 to the
    // D3DCOLOR byte and draws the same untextured screen quad with ONE/ONE.
    if (add.x < 0.001f && add.y < 0.001f && add.z < 0.001f)
        return;

    Renderer2D::Instance().Flush();

    const auto stockByte = [](float v) -> uint8_t
    {
        return static_cast<uint8_t>(static_cast<int32_t>(v * 255.0f));
    };
    const uint8_t r = stockByte(add.x);
    const uint8_t g = stockByte(add.y);
    const uint8_t b = stockByte(add.z);

    const auto savedGL = avp2::render::GLStateCache::Instance().Capture();

    GLStateDisable(GL_DEPTH_TEST);
    GLStateDepthMask(GL_FALSE);
    GLStateDisable(GL_CULL_FACE);
    GLStateEnable(GL_BLEND);
    avp2::render::GLStateCache::Instance().SetBlendEquation(GL_FUNC_ADD_);
    // d3d.ren 0x10015158/0x10015181: SRCBLEND=ONE, DESTBLEND=ONE.
    GLStateBlendFunc(GL_ONE, GL_ONE);

    RendererCore::Instance().ScenePostShader()->Use();
    GLUniform4f(RendererCore::Instance().ScenePostColorUniform(), r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    GLStateBindVertexArray(RendererCore::Instance().ScreenQuadVao());
    glf.DrawArrays(GL_TRIANGLES_, 0, 3);

    ++PresenterState().frameDrawCalls;
    PresenterState().frameHasPresentableContent = true;
    PresenterState().screenShadowValid = false;
    RendererPresenter::Instance().InvalidateScreenRect(nullptr);

    avp2::render::GLStateCache::Instance().Restore(savedGL);

    static int budget = 24;
    if (LogIsSessionEnabled() && ((budget > 0 && budget--)))
        LOG_SESSION("D3D-SCENE-POST GlobalLightAdd=(%.3f %.3f %.3f) color=(%u %u %u) blend=ONE/ONE path=D3D-0x10014F20",
                    add.x, add.y, add.z, unsigned(r), unsigned(g), unsigned(b));
}
