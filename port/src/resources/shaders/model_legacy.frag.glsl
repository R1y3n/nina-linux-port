#version 460 core
layout(std140,binding=12) uniform FramePassConstants {
    vec4 frameProjection;      // tanHalfX, tanHalfY, nearZ, farZ
    vec4 frameCameraPos;       // xyz
    vec4 frameCameraQuat;      // xyzw
    vec4 frameFogColorEnabled; // rgb, enabled
    vec4 frameFogParams;       // near, far, frameTime, unused
};
#define uModelFogColor frameFogColorEnabled.xyz
#define uModelFogNear frameFogParams.x
#define uModelFogFar frameFogParams.y
layout(binding=0) uniform sampler2D uTexture;
layout(binding=1) uniform sampler2D uModelLinkedTexture;
layout(binding=2) uniform sampler2D uModelEnvTexture;
uniform int uModelFogEnabled;
uniform int uTextured;
uniform int uModelLinkedMode;
uniform int uModelEnvPass;
uniform int uModelBlendMode;
uniform vec4 uModelEnvParams;
uniform float uModelDetailScale;
uniform int uModelDetailAdd;
uniform uint uModelMode;
uniform vec3 uModelModeColor;
uniform float uModelAlphaRef;
uniform int uModelAlphaFunc;
uniform int uModelFogAdditive;

uniform int uVFogEnabled;
uniform float uVFogMinY;
uniform float uVFogMaxY;
uniform float uVFogMinYVal;
uniform float uVFogMaxYVal;
uniform float uVFogDensity;
uniform float uVFogMax;

vec3 FogQRotate(vec4 q, vec3 v)
{
    return v + 2.0 * cross(q.xyz, cross(q.xyz, v) + q.w * v);
}

float ComputeTalonVFogAmount(float cameraY, float eyeZ, float worldY)
{
    float fogDiff = uVFogMaxY - uVFogMinY;
    if (abs(fogDiff) < 0.0001 || abs(uVFogDensity) < 0.0001)
        return 0.0;
    float fogValDiff = uVFogMaxYVal - uVFogMinYVal;
    float camY = clamp((cameraY - uVFogMinY) / fogDiff, 0.0, 1.0);
    float fragY = clamp((worldY - uVFogMinY) / fogDiff, 0.0, 1.0);
    float camYMod = camY * fogValDiff + uVFogMinYVal;
    float fragYMod = fragY * fogValDiff + uVFogMinYVal;
    float zFactor = clamp(eyeZ / uVFogDensity, 0.0, 1.0);
    return max(camYMod, fragYMod) * zFactor * uVFogMax;
}

float ComputeSceneFogAmount(vec3 cameraPos)
{
    vec4 cameraQuat = normalize(frameCameraQuat);
    vec3 worldPos = frameCameraPos.xyz + FogQRotate(cameraQuat, cameraPos);
    float eyeZ = max(cameraPos.z, 0.0);

    if (uVFogEnabled != 0)
        return clamp(ComputeTalonVFogAmount(frameCameraPos.y, eyeZ, worldPos.y), 0.0, 1.0);

    if (uModelFogFar == uModelFogNear)
        return 0.0;

    float radialDistance = length(cameraPos);
    if (radialDistance <= uModelFogNear) return 0.0;
    if (radialDistance >= uModelFogFar) return 1.0;
    return clamp((radialDistance - uModelFogNear) / (uModelFogFar - uModelFogNear), 0.0, 1.0);
}

uniform vec3 uModelHookColor;
uniform vec3 uModelSceneTint;
uniform vec3 uModelLightAdd;

const uint MODE_ADD_SIGNED = (1u << 6);
const uint MODE_NO_LIGHT   = (1u << 7);
const uint MODE_FLAT_COLOR = (1u << 8);
const uint MODE_CHROMAKEY  = (1u << 9);
const uint MODE_MODULATE2X = (1u << 16);

in vec2 vUV;
in vec3 vCamPos;
in vec3 vEnvNormal;
in vec2 vEnvUV;
in vec4 vColor;
in float vFogZ;
layout(location=0) out vec4 outColor;
layout(location=1) out vec4 outSSRReceiver;

vec3 ColorOp(uint mode, vec3 a, vec3 b)
{
    if ((mode & MODE_ADD_SIGNED) != 0u)
        return a + b - vec3(0.5);
    if ((mode & MODE_MODULATE2X) != 0u)
        return a * b * 2.0;
    return a * b;
}

void main()
{
    outSSRReceiver=vec4(1.0,0.0,0.0,1.0);
    vec4 texel = (uTextured != 0) ? texture(uTexture, vUV) : vec4(1.0);
    vec4 result = texel;

    // Talon stage 0: skin * lighting.  NO_LIGHT disables scene lighting,
    // but it does not discard ModelHookData::m_pObjectColor.  Predator vision
    // depends on that hook color to recolor otherwise-unlit ABC models.
    if ((uModelMode & MODE_NO_LIGHT) == 0u)
    {
        vec3 lit = clamp(ColorOp(uModelMode, texel.rgb, vColor.rgb), 0.0, 1.0);
        result.rgb = clamp(lit * uModelHookColor, 0.0, 1.0);
    }
    else
    {
        // Keep the post-hook object color authoritative for NO_LIGHT models.
        // Multiplying global scene tint here crushes Predator thermal targets.
        result.rgb = clamp(ColorOp(uModelMode, texel.rgb, uModelHookColor),
                           0.0, 1.0);
    }

    // Talon model detail stage.  This is deliberately evaluated before the
    // environment composition because stock draws the normal skin/detail pass
    // after the environment pass.
    if(uModelLinkedMode==1)
    {
        vec3 detail=texture(uModelLinkedTexture,vUV*uModelDetailScale).rgb;
        if(uModelDetailAdd!=0)
            result.rgb=clamp(result.rgb+detail-vec3(0.5),0.0,1.0);
        else
            result.rgb*=detail;
    }

    if ((uModelMode & MODE_FLAT_COLOR) != 0u)
        result.rgb = uModelModeColor;

    result.a *= vColor.a;

    bool chromaReject=false;
    if((uModelMode & MODE_CHROMAKEY) != 0u)
    {
        bool passAlpha=true;
        if      (uModelAlphaFunc == 1) passAlpha=false;
        else if (uModelAlphaFunc == 2) passAlpha=result.a <  uModelAlphaRef;
        else if (uModelAlphaFunc == 3) passAlpha=result.a == uModelAlphaRef;
        else if (uModelAlphaFunc == 4) passAlpha=result.a <= uModelAlphaRef;
        else if (uModelAlphaFunc == 5) passAlpha=result.a >  uModelAlphaRef;
        else if (uModelAlphaFunc == 6) passAlpha=result.a != uModelAlphaRef;
        else if (uModelAlphaFunc == 7) passAlpha=result.a >= uModelAlphaRef;
        else if (uModelAlphaFunc == 8) passAlpha=true;
        chromaReject=!passAlpha;
    }

    if(uModelEnvPass!=0)
    {
        // Same per-vertex environment-coordinate path as the GPU model shader.
        vec4 env=texture(uModelEnvTexture,vEnvUV);
        // Same stock env-pass diffuse modulation as the GPU-batched path.
        env.rgb*=clamp(vColor.rgb*uModelHookColor,0.0,1.0);
        float baseA=chromaReject?0.0:clamp(result.a,0.0,1.0);

        // Collapse d3d.ren's environment pre-pass + skin/detail pass into one
        // source value.  ModelBlendMode values are:
        //   0 Opaque, 1 Alpha, 2 Add, 3 Multiply, 4 Invert.
        if(uModelBlendMode==0)
        {
            // Env pre-pass replaces the framebuffer, then the skin is alpha
            // blended over it.  With GL blending disabled the exact composite
            // can be emitted directly.
            result.rgb=mix(env.rgb,result.rgb,baseA);
            result.a=1.0;
        }
        else if(uModelBlendMode==1)
        {
            // Two SRC_ALPHA/INVSRC_ALPHA passes can be collapsed into one
            // straight-alpha source using the Porter-Duff over algebra.
            float envA=clamp(env.a,0.0,1.0);
            float combinedA=baseA+envA*(1.0-baseA);
            vec3 premul=result.rgb*baseA + env.rgb*envA*(1.0-baseA);
            result.rgb=(combinedA>0.000001)?(premul/combinedA):vec3(0.0);
            result.a=combinedA;
        }
        else if(uModelBlendMode==2)
        {
            // ONE/ONE is additive and associative.
            result.rgb=env.rgb+result.rgb;
        }
        else if(uModelBlendMode==3)
        {
            // ZERO/SRCCOLOR sequential passes multiply together.
            result.rgb=env.rgb*result.rgb;
        }
        else
        {
            // The NavAliens invert state is not used by Talon's model env-map
            // path in AVP2 content.  Keep the skin result rather than invent a
            // non-associative framebuffer-fetch approximation.
        }
    }
    else if(chromaReject)
    {
        discard;
    }

    if(uModelFogEnabled != 0)
    {
        float fog = ComputeSceneFogAmount(vCamPos);
        if(uModelFogAdditive != 0) result.rgb *= 1.0 - fog;
        else result.rgb = mix(result.rgb, uModelFogColor, fog);
    }

    outColor = result;
}
