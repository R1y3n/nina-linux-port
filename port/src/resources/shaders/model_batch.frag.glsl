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
layout(binding=0) uniform sampler2D uTexture0;
layout(binding=1) uniform sampler2D uTexture1;
layout(binding=2) uniform sampler2D uTexture2;
layout(binding=3) uniform sampler2D uTexture3;
layout(binding=4) uniform sampler2D uDetail0;
layout(binding=5) uniform sampler2D uDetail1;
layout(binding=6) uniform sampler2D uDetail2;
layout(binding=7) uniform sampler2D uDetail3;
layout(binding=8) uniform sampler2D uEnvTexture;
layout(std430,binding=2) readonly buffer SkinStates { vec4 skinData[]; };

uniform int uModelFogEnabled;
uniform int uModelEnvPass;
uniform int uModelBlendMode;
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

uniform vec3 uHookColor;
uniform vec3 uSceneTint;
uniform vec3 uLightAdd;
uniform vec4 uModelEnvParams;

const uint MODE_NO_TEXTURE=(1u<<2);
const uint MODE_ADD_SIGNED=(1u<<6);
const uint MODE_NO_LIGHT=(1u<<7);
const uint MODE_FLAT_COLOR=(1u<<8);
const uint MODE_CHROMAKEY=(1u<<9);
const uint MODE_MODULATE2X=(1u<<16);

in vec2 vUV;
in vec3 vCamPos;
in vec3 vEnvNormal;
in vec2 vEnvUV;
in vec4 vColor;
in float vFogZ;
flat in int vSkinIndex;
layout(location=0) out vec4 outColor;
layout(location=1) out vec4 outSSRReceiver;

vec4 SampleBase(int s,vec2 uv)
{
    if(s==0) return texture(uTexture0,uv);
    if(s==1) return texture(uTexture1,uv);
    if(s==2) return texture(uTexture2,uv);
    return texture(uTexture3,uv);
}

vec3 SampleDetail(int s,vec2 uv)
{
    if(s==0) return texture(uDetail0,uv).rgb;
    if(s==1) return texture(uDetail1,uv).rgb;
    if(s==2) return texture(uDetail2,uv).rgb;
    return texture(uDetail3,uv).rgb;
}

vec3 ColorOp(uint mode,vec3 a,vec3 b)
{
    if((mode&MODE_ADD_SIGNED)!=0u)
        return a+b-vec3(0.5);
    if((mode&MODE_MODULATE2X)!=0u)
        return a*b*2.0;
    return a*b;
}

void main()
{
    outSSRReceiver=vec4(1.0,0.0,0.0,1.0);
    int skin=clamp(vSkinIndex,0,3);
    vec4 s0=skinData[skin*2+0];
    vec4 s1=skinData[skin*2+1];
    uint mode=uint(s0.x+0.5);
    float alphaRef=s0.y;
    bool detailEnabled=s0.z>0.5;
    float detailScale=s0.w;
    bool detailAdd=s1.x>0.5;
    vec3 modeColor=s1.yzw;

    vec4 texel=((mode&MODE_NO_TEXTURE)==0u)?SampleBase(skin,vUV):vec4(1.0);
    vec4 result=texel;
    if((mode&MODE_NO_LIGHT)==0u)
    {
        // Ordinary scene tint has already been incorporated into the vertex
        // lighting terms. Keep object/hook color separate from that operation.
        vec3 lit=clamp(ColorOp(mode,texel.rgb,vColor.rgb),0.0,1.0);
        // Scene tint is already applied inside the stock-equivalent lighting
        // terms. Applying it again here incorrectly tints ModelLightAdd and
        // crushes Predator thermal contrast.
        result.rgb=clamp(lit*uHookColor,0.0,1.0);
    }
    else
    {
        // NO_LIGHT still honors the game/model-hook object color, but must not
        // multiply SceneDesc global tint here. Predator thermal/vision uses
        // this path for classified targets and the hook color is authoritative.
        result.rgb=clamp(ColorOp(mode,texel.rgb,uHookColor),0.0,1.0);
    }

    if(detailEnabled)
    {
        vec3 detail=SampleDetail(skin,vUV*detailScale);
        if(detailAdd) result.rgb=clamp(result.rgb+detail-vec3(0.5),0.0,1.0);
        else result.rgb*=detail;
    }

    if((mode&MODE_FLAT_COLOR)!=0u)
        result.rgb=modeColor;

    result.a*=vColor.a;
    bool chromaReject=((mode&MODE_CHROMAKEY)!=0u && result.a<alphaRef);

    if(uModelEnvPass!=0)
    {
        // Stock model chrome uses per-vertex environment coordinates produced
        // by the animated normal transform (d3d.ren 0x10001420), then lets D3D
        // interpolate them across the triangle.  Do not reconstruct a face
        // normal here; that makes the reflection insensitive to the exact
        // bone/view normal transform and visually glues the mask to the mesh.
        vec4 env=texture(uEnvTexture,vEnvUV);
        // d3d.ren submits the environment pass through the normal model
        // vertex builder, so chrome is not an unlit full-bright texture.
        // Modulate it by the same completed vertex diffuse/object color that
        // reaches the base skin pass.  This keeps bright Chrome.dtx texels
        // from blowing a dark first-person model out to pure white.
        env.rgb*=clamp(vColor.rgb*uHookColor,0.0,1.0);
        float baseA=chromaReject?0.0:clamp(result.a,0.0,1.0);
        if(uModelBlendMode==0)
        {
            result.rgb=mix(env.rgb,result.rgb,baseA);
            result.a=1.0;
        }
        else if(uModelBlendMode==1)
        {
            float envA=clamp(env.a,0.0,1.0);
            float combinedA=baseA+envA*(1.0-baseA);
            vec3 premul=result.rgb*baseA+env.rgb*envA*(1.0-baseA);
            result.rgb=(combinedA>0.000001)?premul/combinedA:vec3(0.0);
            result.a=combinedA;
        }
        else if(uModelBlendMode==2)
            result.rgb=env.rgb+result.rgb;
        else if(uModelBlendMode==3)
            result.rgb=env.rgb*result.rgb;
    }
    else if(chromaReject)
        discard;

    if(uModelFogEnabled != 0)
    {
        float fog = ComputeSceneFogAmount(vCamPos);
        if(uModelFogAdditive != 0) result.rgb *= 1.0 - fog;
        else result.rgb = mix(result.rgb, uModelFogColor, fog);
    }
    outColor=result;
}
