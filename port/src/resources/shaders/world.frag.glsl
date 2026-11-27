#version 460 core
layout(std140,binding=12) uniform FramePassConstants {
    vec4 frameProjection;      // tanHalfX, tanHalfY, nearZ, farZ
    vec4 frameCameraPos;       // xyz
    vec4 frameCameraQuat;      // xyzw
    vec4 frameFogColorEnabled; // rgb, enabled
    vec4 frameFogParams;       // near, far, frameTime, unused
};
#define uCameraPos frameCameraPos.xyz
#define uCameraQuat frameCameraQuat
#define uFogColor frameFogColorEnabled.xyz
#define uFogNear frameFogParams.x
#define uFogFar frameFogParams.y
layout(binding=0) uniform sampler2D uTexture;
layout(binding=1) uniform sampler2D uLightAtlas;
layout(binding=5) uniform sampler2D uDeluxeAtlas;
layout(binding=6) uniform sampler2D uDerivedMaterial;
layout(binding=12) uniform sampler2D uAuthoredNormal;
layout(binding=13) uniform sampler2D uAuthoredSpecular;
layout(binding=14) uniform sampler2D uAuthoredReflection;
layout(binding=3) uniform sampler2D uPanSkyTexture;
layout(binding=4) uniform sampler2D uLinkedTexture;
uniform int uTextured;
uniform int uLinkedTexMode;
uniform vec4 uLinkedParams2; // legacy fallback
struct WorldMaterialParams { vec4 linkedParams0; vec4 linkedParams1; vec4 linkedParams2; uvec4 info; };
layout(std430,binding=11) readonly buffer WorldMaterialParamBuffer { WorldMaterialParams gWorldMaterialParams[]; };
uniform int uUseWorldMaterialParams;
uniform uint uWorldMaterialParamIndex;
#define LINKED_PARAMS2 ((uUseWorldMaterialParams!=0)?gWorldMaterialParams[vMaterialParamIndex].linkedParams2:uLinkedParams2)
uniform int uLightmapped;
uniform int uDeluxeEnabled;
uniform int uDeluxeDebugView;
uniform float uDeluxeSpecularStrength;
uniform float uDeluxeSpecularPower;
uniform int uDeluxeGeneratedNormalEnabled;
uniform float uDeluxeNormalStrength;
uniform float uDeluxeNormalBlack;
uniform float uDeluxeNormalWhite;
uniform int uDeluxeNormalInvert;
uniform int uDeluxeNormalInvertX;
uniform int uDeluxeNormalInvertY;
uniform int uDeluxeNormalInvertZ;
uniform int uDeluxeNormalBand;
uniform float uDeluxeSpecLightColorInfluence;
uniform int uDeluxeGeneratedSpecularEnabled;
uniform int uAuthoredNormalEnabled;
uniform int uAuthoredSpecularEnabled;
uniform float uAuthoredNormalStrength;
uniform float uAuthoredSpecularStrength;
uniform float uAuthoredGlossMinPower;
uniform float uAuthoredGlossMaxPower;
uniform float uAuthoredGlossBias;
uniform int uAuthoredReflectionMode;
uniform int uAuthoredReflectionMapEnabled;
uniform float uAuthoredReflectionStrength;
uniform float uDeluxeSpecMapStrength;
uniform float uDeluxeSpecBlack;
uniform float uDeluxeSpecWhite;
uniform int uDeluxeSpecInvert;
uniform int uNoLight;
uniform uint uLegacyDrawFlags; // shared legacy classification fallback
uniform int uSkyDxt5AlphaOnly;
uniform int uSkyHorizonFogGradient;
uniform int uAlphaTest;
uniform float uAlphaRef;
uniform int uAlphaFunc;
uniform int uFullBrightTexture;
uniform int uWorldModelLightmapGouraud;
uniform int uWorldModelGouraud;
uniform int uLightmapSaturate;
uniform int uUseGridLight;
uniform vec3 uGlobalVertexTint;
uniform vec3 uGlobalWMAmbient;
uniform int uAlienInvertHack;
uniform int uFogEnabled;
uniform int uFogAdditive;
uniform int uVFogEnabled;
uniform float uVFogMinY;
uniform float uVFogMaxY;
uniform float uVFogMinYVal;
uniform float uVFogMaxYVal;
uniform float uVFogDensity;
uniform float uVFogMax;
uniform int uPanSkyEnabled;
uniform int uDynamicLightCount;

struct DynamicWorldLight {
    vec4 posRadius;
    vec4 colorFlags;
};
layout(std430,binding=8) readonly buffer DynamicWorldLightBuffer {
    DynamicWorldLight gDynamicWorldLights[];
};

in vec2 vUV;
in vec2 vLinkedUV;
in vec2 vLMUV;
in vec2 vPanSkyUV;
in vec4 vColor;
in float vHasLightmap;
in float vHasVertexLight;
in vec3 vLMTangentWorld;
in vec3 vBaseTangentWorld;
in float vFogZ;
noperspective in float vSkyFogFactor;
in vec3 vWorldPos;
in vec3 vWorldNormal;
flat in uint vMaterialParamIndex;
flat in int vWorldModelPass;
flat in uint vWorldDrawFlags;
layout(location=0) out vec4 outColor;
layout(location=1) out vec4 outSSRReceiver;

// Original d3d.ren one-pass lightmapping configures the lightmap texture
// stage as D3DTOP_MODULATE or D3DTOP_MODULATE2X.  AVP2's saturated
// lightmap path uses MODULATE2X, so the combined result must be
// saturate(base * light * 2), not just base * light.
vec3 TalonLightModulate(vec3 baseColor,vec3 lightColor)
{
    return clamp(baseColor*lightColor*2.0,0.0,1.0);
}


float ComputeTalonVFogAmount(float cameraY,float eyeZ,float worldY)
{
    // Same vertical-fog equation used by the AVP2 D3D11 reference renderer.
    // VFog is an alternate fog mode: FogNearZ/FogFarZ are not part of this
    // calculation.  The Y term selects the denser of camera height and
    // fragment height, then distance along camera Z scales it by density.
    float fogDiff=uVFogMaxY-uVFogMinY;
    if(abs(fogDiff)<0.0001 || abs(uVFogDensity)<0.0001)
        return 0.0;
    float fogValDiff=uVFogMaxYVal-uVFogMinYVal;
    float camY=clamp((cameraY-uVFogMinY)/fogDiff,0.0,1.0);
    float fragY=clamp((worldY-uVFogMinY)/fogDiff,0.0,1.0);
    float camYMod=camY*fogValDiff+uVFogMinYVal;
    float fragYMod=fragY*fogValDiff+uVFogMinYVal;
    float zFactor=clamp(eyeZ/uVFogDensity,0.0,1.0);
    return max(camYMod,fragYMod)*zFactor*uVFogMax;
}

vec3 TalonDynamicLightAdd()
{
    vec3 add=vec3(0.0);

    // Stock d3d_rendershader_dynamiclight uses two attenuation textures whose
    // combined alpha is exactly 1 - (dx^2+dy^2+dz^2)/radius^2, then blends
    // SRC_ALPHA,ONE.  There is deliberately no Lambert/angular attenuation.
    //
    // IMPORTANT: do not perform a per-polygon normal/facing rejection here.
    // BSP and WorldModel normals are authored flat per polygon, so a hard
    // dot(normal,toLight) test creates visible polygon-shaped/faceted light
    // boundaries.  vWorldPos is interpolated continuously by the rasterizer;
    // using only the spherical distance falloff therefore produces a smooth
    // light pool across triangle/polygon boundaries.
    for(int i=0;i<uDynamicLightCount;++i)
    {
        DynamicWorldLight dl=gDynamicWorldLights[i];
        float radius=dl.posRadius.w;
        if(radius<=0.0)
            continue;

        // Preserve the authored peak intensity while broadening the visible
        // pool slightly.  The stock-equivalent hard edge is visibly harsh in
        // the modern one-pass path, so keep the quality-tuned radius/falloff
        // that was already validated in-game.
        const float falloffRadiusScale=1.50;
        float effectiveRadius=radius*falloffRadiusScale;

        vec3 toLight=dl.posRadius.xyz-vWorldPos;
        float dist2=dot(toLight,toLight);
        float radius2=effectiveRadius*effectiveRadius;
        if(dist2>=radius2)
            continue;

        float attenuation=max(0.0,1.0-dist2/radius2);
        attenuation=attenuation*attenuation*(3.0-2.0*attenuation);
        // colorFlags.rgb is Talon's signed light delta, not conventional RGB.
        add+=dl.colorFlags.rgb*attenuation;
    }
    return add;
}


vec3 fogQRotate(vec4 q, vec3 v)
{
    return v + 2.0 * cross(q.xyz, cross(q.xyz, v) + q.w * v);
}

void main()
{
    // Materials without a .mat retain the old global SSR receiver heuristic.
    // A .mat opts the surface into explicit reflection authoring.
    outSSRReceiver=vec4((uAuthoredReflectionMode==0)?1.0:0.0,(uAuthoredReflectionMode!=0)?1.0:0.0,0.0,1.0);
    vec4 base=(uTextured!=0)?texture(uTexture,vUV):vec4(1.0);
    float textureAlpha=base.a;
    base.a*=vColor.a;

    if(uSkyDxt5AlphaOnly!=0)
    {
        outColor=vec4(vec3(textureAlpha),1.0);
        return;
    }

    if(uAlphaTest!=0)
    {
        bool passAlpha=true;
        if      (uAlphaFunc == 1) passAlpha=false;
        else if (uAlphaFunc == 2) passAlpha=base.a <  uAlphaRef;
        else if (uAlphaFunc == 3) passAlpha=base.a == uAlphaRef;
        else if (uAlphaFunc == 4) passAlpha=base.a <= uAlphaRef;
        else if (uAlphaFunc == 5) passAlpha=base.a >  uAlphaRef;
        else if (uAlphaFunc == 6) passAlpha=base.a != uAlphaRef;
        else if (uAlphaFunc == 7) passAlpha=base.a >= uAlphaRef;
        else if (uAlphaFunc == 8) passAlpha=true;
        if(!passAlpha) discard;
    }

    // Deluxe direction-atlas debug view.  This is deliberately an early
    // return so static lightmaps, Gouraud/LightTable lighting, dynamic lights,
    // material modulation, deluxe specular and fog cannot contaminate the
    // visualization.  Static BSP and lightmapped WorldModels share this shader
    // and the same atlas UVs, so both paths are inspected identically.
    if(uDeluxeDebugView!=0)
    {
        if(uLightmapped!=0 && vHasLightmap>0.5)
        {
            vec4 deluxeDebug=texture(uDeluxeAtlas,vLMUV);
            outColor=vec4(deluxeDebug.rgb,1.0);
        }
        else
        {
            // Non-lightmapped geometry has no valid deluxe atlas location.
            outColor=vec4(0.0,0.0,0.0,1.0);
        }
        return;
    }

    vec3 rgb=base.rgb;
    // Cache the large RGB lightmap sample. Deluxe energy/chroma uses this same
    // texel, so normal lightmapped surfaces no longer fetch uLightAtlas twice.
    vec3 cachedLightSample=vec3(0.0);
    bool cachedLightValid=false;

    // AVP2 p1s1 Horizon uses blackgradient2.dtx as a transparent
    // fog-coloured horizon belt.  Its texture command string is the stock
    // "ViewModes ... Fog*" table and the texture alpha is the authored
    // vertical fade.  d3d.ren therefore shows the current vision/fog colour
    // through this layer instead of a literal black strip.  Keep the texture
    // alpha untouched for blending; only source the layer RGB from the live
    // Talon fog colour.
    if(uSkyHorizonFogGradient!=0)
        rgb=clamp(uFogColor,vec3(0.0),vec3(1.0));

    int linkedTexMode=(uUseWorldMaterialParams!=0)?int(gWorldMaterialParams[vMaterialParamIndex].info.x):uLinkedTexMode;
    if(linkedTexMode!=0)
    {
        vec4 linked=texture(uLinkedTexture,vLinkedUV);
        if(linkedTexMode==1)
        {
            // Detail textures alone obey DetailTextureAdd.
            if(LINKED_PARAMS2.y>0.5)
                rgb=clamp(base.rgb+linked.rgb-vec3(0.5),0.0,1.0);
            else
                rgb=base.rgb*linked.rgb;
        }
        else if(linkedTexMode==2)
        {
            // Talon ordinary world environment maps use ADDSIGNED.  Do not
            // inherit the DetailTextureAdd switch here; doing so can turn the
            // environment stage into a dark multiply.
            rgb=clamp(base.rgb+linked.rgb-vec3(0.5),0.0,1.0);
        }
        else if(linkedTexMode==3)
        {
            // d3d.ren 0x1000A584 binds the linked environment map to
            // stage 0 and the BASE texture to stage 1.  For m_eTexType==2,
            // 0x1000A1CC selects D3DTOP_MODULATEALPHA_ADDCOLOR (18).
            // With stage-1 ARG1=base texture and ARG2=current env,
            // D3DTOP_MODULATEALPHA_ADDCOLOR is:
            //     base.rgb + base.a * env.rgb
            // Use authored texture alpha, before object/vertex alpha.
            rgb=clamp(base.rgb+textureAlpha*linked.rgb,0.0,1.0);
        }
    }

    // d3d.ren 0x100193BC..0x1001942C emits a prelit sky diffuse color
    // (source SPolyVertex RGB * LTObject RGB) and the fixed-function texture
    // stage modulates the bound base texture by that diffuse.  Sky is otherwise
    // unlit, so this dedicated multiply must happen outside uNoLight lighting.
    if((vWorldDrawFlags & 2u)!=0u)
        rgb*=clamp(vColor.rgb,vec3(0.0),vec3(1.0));

    // DTX_FULLBRITE: texture alpha is the per-pixel full-bright mask.
    // This is distinct from SURF_BRIGHT/MODE_NO_LIGHT.
    bool materialFullBright=(uUseWorldMaterialParams!=0)
        ? (gWorldMaterialParams[vMaterialParamIndex].info.y!=0u)
        : (uFullBrightTexture!=0);
    float fullBriteAlpha=materialFullBright?clamp(base.a,0.0,1.0):0.0;

    // Talon Alien vision parity: stock d3d.ren exposes LMFullBright and,
    // while InvertHack is active, the world is rendered without the normal
    // static LightMap/Gouraud contribution before the final fullscreen
    // inversion.  Keep material texturing and the later dynamic-light path
    // alive; only bypass the baked/static world-lighting stage here.
    if(uNoLight==0 && uAlienInvertHack==0)
    {
        if(vWorldModelPass!=0)
        {
            // d3d.ren 0x10030370..0x100305E7: WorldModels do not use
            // the static BSP lightmap texture stage.  The vertex builder
            // starts with the authored/LightAnim SPolyVertex RGB, adds the
            // LightTable sample taken at WorldPoly::m_vCenter plus
            // GlobalWMAmbient with byte saturation, applies object/global
            // tint, then the base texture modulates that diffuse once.
            vec3 wmDiffuse=clamp(vColor.rgb,0.0,1.0);

            // 0x1002F55C loads Surface::m_dwFlags (+0x30) and tests bit 0x80
            // (SURF_LIGHTMAP).  If set, 0x1002F56B..0x1002F571 calls the
            // installed lightmap renderer callback and SKIPS the Gouraud/LightAnim
            // path at 0x1002F579..0x1002F72A entirely.  Therefore a brush authored
            // with BOTH LightMap and GouraudShade is lightmap-authoritative: the
            // Gouraud vertex diffuse must not participate in the final color.
            //
            // The stock lightmap blend at 0x10009CE3 is:
            //   Saturate=0: SRCBLEND=ZERO, DESTBLEND=SRCCOLOR => base * lightmap
            //   Saturate=1: SRCBLEND=DESTCOLOR, DESTBLEND=SRCCOLOR
            //               => 2 * base * lightmap
            if(uWorldModelLightmapGouraud!=0 && uLightmapped!=0 && vHasLightmap>0.5)
            {
                cachedLightSample=clamp(texture(uLightAtlas,vLMUV).rgb,0.0,1.0);
                cachedLightValid=true;
                vec3 lm=cachedLightSample;
                if(uLightmapSaturate!=0)
                    rgb=clamp(2.0*rgb*lm,0.0,1.0);
                else
                    rgb=clamp(rgb*lm,0.0,1.0);
            }
            else
            {
                rgb*=wmDiffuse;
            }

            // Stock d3d.ren folds GlobalWMAmbient into the per-vertex diffuse
            // before the texture stage (0x100304D0..0x100305E7).  Do not add
            // it again here or WorldModels receive ambient twice.
        }
        else
        {
            if(uLightmapped!=0 && vHasLightmap>0.5)
            {
                // Static PhysicsBSP/Terrain lightmap precedence, matching
                // d3d.ren 0x100099B9 / 0x10009F0B.  The stock lightmap
                // pass writes a global diffuse colour into the lightmap
                // vertices; it does NOT add the polygon's SPolyVertex RGB to
                // the lightmap.  Therefore a brush authored with both
                // GouraudShade and LightMap is still controlled by the
                // animated lightmap.  When a flicker LightAnim goes black,
                // the surface is allowed to go black instead of retaining a
                // baked Gouraud illumination floor.
                cachedLightSample=texture(uLightAtlas,vLMUV).rgb;
                cachedLightValid=true;
                vec3 light=cachedLightSample;
                rgb=TalonLightModulate(rgb,clamp(light,0.0,1.0));
                rgb*=clamp(uGlobalVertexTint,0.0,1.0);
            }
            else
            {
                // Gouraud/flat surfaces and SURF_LIGHTMAP records without a
                // compressed texture payload use the compiled LightAnim
                // vertex-colour data.
                rgb=TalonLightModulate(rgb,clamp(vColor.rgb,0.0,1.0));
            }
        }
    }

    if(uNoLight==0 && fullBriteAlpha>0.0)
        rgb=mix(rgb,base.rgb,fullBriteAlpha);

    // Keep dynamic lighting detail-preserving in the one-pass shader.  Raw
    // additive RGB reproduces the old fixed-function blend mathematically, but
    // in this LDR combined path it clips bright surfaces to white and destroys
    // texture detail.  Modulate by albedo and consume remaining headroom.
    if(uNoLight==0 && uDynamicLightCount>0)
    {
        vec3 dynamicAdd=TalonDynamicLightAdd();
        vec3 albedo=clamp(base.rgb,0.0,1.0);

        // Talon light color is signed around the 127/128 midpoint. Positive
        // channels brighten toward white; negative channels darken toward
        // black.
        vec3 positive=max(dynamicAdd,vec3(0.0));
        vec3 negative=min(dynamicAdd,vec3(0.0));
        vec3 signedContribution=
            positive*(vec3(1.0)-rgb) +
            negative*rgb;
        rgb=clamp(rgb + albedo*signedContribution,0.0,1.0);
    }

    // Deluxe-direction material test.  Talon's RGB lightmap remains the diffuse
    // authority.  For testing modern material response without authoring new
    // assets, derive a tangent-space normal and a specular mask directly from
    // the base albedo.  Both are independently level/strength controlled.
    if(uDeluxeEnabled!=0 && uLightmapped!=0 && vHasLightmap>0.5 && uNoLight==0)
    {
        vec4 deluxe=texture(uDeluxeAtlas,vLMUV);
        vec3 Lt=deluxe.rgb*2.0-1.0;
        // RGB stores tangent-space direction in the lightmap basis T,-V,N.
        // The -V axis is the single OpenGL-vs-D3D green-channel convention
        // flip; reconstruct the same basis here rather than flipping G again.
        // Alpha is directional visibility coverage: ordinary/local
        // contributions are 1.0 while static sunlight can be fractional near
        // a sky/occluder boundary. Diffuse lightmap RGB still carries energy.
        float deluxeInfluence=clamp(deluxe.a,0.0,1.0);
        float ll=dot(Lt,Lt);

        // Runtime cost gate.  The atlas can intentionally carry a neutral
        // tangent-space direction in unlit/directionless luxels, but alpha=0
        // means it contributes no specular response.  Sample baked energy up
        // front and skip the expensive TBN/normal/specular work when either
        // directional coverage or actual Talon lightmap energy is tiny.
        vec3 bakedLight=max(cachedLightValid?cachedLightSample:texture(uLightAtlas,vLMUV).rgb,vec3(0.0));
        float baked=max(max(bakedLight.r,bakedLight.g),bakedLight.b);
        float deluxeSpecGate=baked*deluxeInfluence*uDeluxeSpecularStrength;

        // Albedo neighborhood work is cached once per DTX in uDerivedMaterial.
        // RG is a signed height gradient and B is luminance. No fragment derivatives
        // or extra albedo samples are required for generated normals/specular masks.
        bool haveAuthoredNormal=(uAuthoredNormalEnabled!=0 && uTextured!=0);
        bool haveAuthoredSpecular=(uAuthoredSpecularEnabled!=0 && uTextured!=0);
        bool needGeneratedNormal=(!haveAuthoredNormal && uDeluxeGeneratedNormalEnabled!=0 && uTextured!=0);
        bool needDerivedMaterial=needGeneratedNormal || (!haveAuthoredSpecular && uDeluxeGeneratedSpecularEnabled!=0 && uTextured!=0);
        vec4 derived=needDerivedMaterial?texture(uDerivedMaterial,vUV):vec4(0.5,0.5,1.0,1.0);

        if(ll>0.01 && deluxeSpecGate>1e-5)
        {
            Lt*=inversesqrt(ll);
            vec3 N=normalize(vWorldNormal);

            // +lightmap-U is constant for the polygon and was precomputed by
            // the world cache builder.  Avoid the old per-fragment derivative
            // solve (four derivatives + determinant/divide) on every deluxe
            // covered pixel. OpenGL deluxe green remains the -V axis.
            vec3 Tlm=vLMTangentWorld;
            Tlm-=N*dot(Tlm,N);
            float t2=dot(Tlm,Tlm);
            vec3 L=N;
            if(t2>1e-20)
            {
                Tlm*=inversesqrt(t2);
                vec3 Blm=-normalize(cross(N,Tlm));
                L=normalize(Tlm*Lt.x+Blm*Lt.y+N*Lt.z);
            }

            // Authored tangent-space normal overrides the generated albedo normal.
            // DTX RGB follows the conventional 0..1 -> -1..1 encoding.
            if(haveAuthoredNormal || needGeneratedNormal)
            {
                vec3 Tb=vBaseTangentWorld;
                Tb-=N*dot(Tb,N);
                float bt2=dot(Tb,Tb);
                if(bt2>1e-20)
                {
                    Tb*=inversesqrt(bt2);
                    vec3 Bb=normalize(cross(N,Tb));
                    vec3 Nt=vec3(0.0,0.0,1.0);
                    if(haveAuthoredNormal)
                    {
                        Nt=texture(uAuthoredNormal,vUV).rgb*2.0-1.0;
                        Nt.xy*=uAuthoredNormalStrength;
                        Nt=normalize(Nt);
                    }
                    else
                    {
                        float nDen=max(0.001,uDeluxeNormalWhite-uDeluxeNormalBlack);
                        float bandScale=(uDeluxeNormalBand==0)?2.0:((uDeluxeNormalBand==1)?1.0:0.5);
                        vec2 grad=(derived.rg*2.0-1.0)*(uDeluxeNormalStrength*bandScale/nDen);
                        if(derived.b<=uDeluxeNormalBlack || derived.b>=uDeluxeNormalWhite) grad=vec2(0.0);
                        if(uDeluxeNormalInvert!=0) grad=-grad;
                        Nt=normalize(vec3(-grad.x,-grad.y,1.0));
                        if(uDeluxeNormalInvertX!=0) Nt.x=-Nt.x;
                        if(uDeluxeNormalInvertY!=0) Nt.y=-Nt.y;
                        if(uDeluxeNormalInvertZ!=0) Nt.z=-Nt.z;
                    }
                    N=normalize(Tb*Nt.x+Bb*Nt.y+N*Nt.z);
                }
            }

            vec3 authoredSpecColor=vec3(1.0);
            float specMask=1.0;
            float specPower=max(1.0,uDeluxeSpecularPower);
            if(haveAuthoredSpecular)
            {
                vec4 sm=texture(uAuthoredSpecular,vUV);
                // RGB is authored highlight colour/intensity contribution.
                authoredSpecColor=max(sm.rgb,vec3(0.0))*uAuthoredSpecularStrength;
                // Alpha is gloss: 0 = broad/rough, 1 = tight/glossy.
                float gloss=clamp(sm.a+uAuthoredGlossBias,0.0,1.0);
                specPower=mix(max(1.0,uAuthoredGlossMinPower),max(uAuthoredGlossMinPower,uAuthoredGlossMaxPower),gloss);
            }
            else if(uDeluxeGeneratedSpecularEnabled!=0)
            {
                float lum=derived.b;
                float sDen=max(0.001,uDeluxeSpecWhite-uDeluxeSpecBlack);
                specMask=clamp((lum-uDeluxeSpecBlack)/sDen,0.0,1.0);
                specMask=specMask*specMask*(3.0-2.0*specMask);
                if(uDeluxeSpecInvert!=0) specMask=1.0-specMask;
                specMask=clamp(specMask*uDeluxeSpecMapStrength,0.0,1.0);
            }

            vec3 V=normalize(uCameraPos-vWorldPos);
            vec3 H=normalize(L+V);
            float spec=pow(max(dot(N,H),0.0),specPower);
            vec3 lightChroma=(baked>1e-5)?(bakedLight/baked):vec3(1.0);
            vec3 specColor=mix(vec3(1.0),lightChroma,clamp(uDeluxeSpecLightColorInfluence,0.0,1.0));
            specColor*=authoredSpecColor;
            rgb=clamp(rgb+specColor*(spec*specMask*deluxeSpecGate),0.0,1.0);
        }
    }

    // Stock SURF_PANNINGSKY is a projected texture pass over the already
    // textured/lit polygon.  It is used for moving cloud-cover shadows, so
    // reproduce that pass as a color modulation instead of replacing the
    // polygon's base UVs.
    if(uPanSkyEnabled!=0)
        rgb*=texture(uPanSkyTexture,vPanSkyUV).rgb;

    if(uFogEnabled!=0)
    {
        if((vWorldDrawFlags & 2u)!=0u)
        {
            // d3d.ren 0x10013560 writes visibility (255=clear, 0=fogged)
            // into specular alpha per transformed/clipped sky vertex.
            // noperspective interpolation reproduces fixed-function vertex
            // fog much more closely than deriving fog from fragment Z.
            float vis=clamp(vSkyFogFactor,0.0,1.0);
            if(uFogAdditive!=0) rgb*=vis;
            else rgb=mix(uFogColor,rgb,vis);
        }
        else
        {
            vec4 fogCameraQuat=normalize(uCameraQuat);
            vec4 invCameraQuat=vec4(-fogCameraQuat.xyz,fogCameraQuat.w);
            vec3 fogCameraPos=fogQRotate(invCameraQuat,vWorldPos-uCameraPos);
            float eyeZ=max(fogCameraPos.z,0.0);
            float radialDistance=length(fogCameraPos);

            float fogAmount=0.0;
            if(uVFogEnabled!=0)
            {
                // Talon VFog replaces the ordinary FogNearZ/FogFarZ ramp.
                // This is the important distinction for levels that leave a
                // very short normal fog range (for example 1..500) while
                // VFog is active.
                fogAmount=ComputeTalonVFogAmount(uCameraPos.y,eyeZ,vWorldPos.y);
            }
            else if(uFogFar!=uFogNear)
            {
                // AVP2's D3D11 reference uses range fog for the ordinary
                // distance mode.  Keep the calculation per-fragment, but use
                // true camera-space range here; VFog above intentionally uses
                // forward camera Z as its density distance.
                if(radialDistance<=uFogNear) fogAmount=0.0;
                else if(radialDistance>=uFogFar) fogAmount=1.0;
                else fogAmount=clamp((radialDistance-uFogNear)/(uFogFar-uFogNear),0.0,1.0);
            }

            // D3D's fog factor is normally in [0,1].  Clamp here so malformed
            // map/console VFog values cannot extrapolate mix() into a hard
            // over-fogged wall.
            fogAmount=clamp(fogAmount,0.0,1.0);
            if(uFogAdditive!=0) rgb*=1.0-fogAmount;
            else rgb=mix(rgb,uFogColor,fogAmount);
        }
    }

    float ssrReceiver=1.0;
    if(uAuthoredReflectionMode!=0)
    {
        ssrReceiver=clamp(uAuthoredReflectionStrength,0.0,1.0);
        if(uAuthoredReflectionMapEnabled!=0)
        {
            vec4 rm=texture(uAuthoredReflection,vUV);
            float mask=dot(rm.rgb,vec3(0.2126,0.7152,0.0722))*rm.a;
            ssrReceiver*=clamp(mask,0.0,1.0);
        }
    }
    outSSRReceiver=vec4(ssrReceiver,(uAuthoredReflectionMode!=0)?1.0:0.0,0.0,1.0);
    outColor=vec4(rgb,base.a);
}
