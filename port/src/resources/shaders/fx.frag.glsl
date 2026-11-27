#version 460 core
layout(std140,binding=12) uniform FramePassConstants {
    vec4 frameProjection;      // tanHalfX, tanHalfY, nearZ, farZ
    vec4 frameCameraPos;       // xyz
    vec4 frameCameraQuat;      // xyzw
    vec4 frameFogColorEnabled; // rgb, enabled
    vec4 frameFogParams;       // near, far, frameTime, unused
};
#define uFogColor frameFogColorEnabled.xyz
#define uFogNear frameFogParams.x
#define uFogFar frameFogParams.y
layout(binding=0) uniform sampler2D uTexture;
layout(binding=1) uniform sampler2D uEnvMap;
uniform int uFogEnabled;
uniform int uTextured;
uniform int uEnvMapEnabled;
uniform int uFogAdditive;

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

    if (uFogFar == uFogNear)
        return 0.0;

    float radialDistance = length(cameraPos);
    if (radialDistance <= uFogNear) return 0.0;
    if (radialDistance >= uFogFar) return 1.0;
    return clamp((radialDistance - uFogNear) / (uFogFar - uFogNear), 0.0, 1.0);
}

uniform int uCanvasOps;
uniform int uCanvasColorOp;
uniform int uCanvasAlphaOp;
in vec2 vUV;
in vec4 vColor;
in float vFogZ;
in vec3 vCameraPos;
layout(location=0) out vec4 outColor;
layout(location=1) out vec4 outSSRReceiver;
void main()
{
    outSSRReceiver=vec4(1.0,0.0,0.0,1.0);
    vec4 t=(uTextured!=0)?texture(uTexture,vUV):vec4(1.0);
    vec4 c;
    if(uCanvasOps!=0)
    {
        vec3 rgb;
        if(uCanvasColorOp==1) rgb=t.rgb;                         // SELECTARG1
        else if(uCanvasColorOp==2) rgb=vColor.rgb;              // SELECTARG2
        else if(uCanvasColorOp==4) rgb=t.rgb+vColor.rgb;        // ADD
        else if(uCanvasColorOp==5) rgb=t.rgb+vColor.rgb-vec3(0.5); // ADDSIGNED
        else rgb=t.rgb*vColor.rgb;                              // MODULATE/default

        float alpha;
        if(uCanvasAlphaOp==1) alpha=t.a;
        else if(uCanvasAlphaOp==2) alpha=vColor.a;
        else if(uCanvasAlphaOp==4) alpha=t.a+vColor.a;
        else if(uCanvasAlphaOp==5) alpha=t.a+vColor.a-0.5;
        else alpha=t.a*vColor.a;
        c=clamp(vec4(rgb,alpha),0.0,1.0);
    }
    else
    {
        c=t*vColor;
    }
    if(uEnvMapEnabled!=0)
    {
        // Retail d3d.ren exposes EnvMapPolyGrids and consumes a dedicated
        // PolyGrid environment texture.  D3D generated camera-space
        // reflection coordinates for this stage; reconstruct the same
        // camera-space normal from the rasterized grid surface.
        vec3 dx=dFdx(vCameraPos);
        vec3 dy=dFdy(vCameraPos);
        vec3 n=normalize(cross(dx,dy));
        vec3 eyeDir=normalize(vCameraPos);
        if(dot(n,eyeDir)>0.0) n=-n;
        vec3 r=reflect(eyeDir,n);
        float m=2.0*sqrt(max(1.0e-8,r.x*r.x+r.y*r.y+(r.z+1.0)*(r.z+1.0)));
        vec2 euv=r.xy/m+vec2(0.5);
        vec3 env=texture(uEnvMap,euv).rgb;
        // Stock LithTech d3d_SetEnvMapTextureStates(): stage 1 computes
        // DIFFUSE * ENVMAP.  It does NOT multiply the already-combined base
        // texture into the final RGB.  Keeping the base texture in this product
        // makes water dramatically too dark.
        // Talon PolyGrid environment stage is visually MODULATE2X-strength.
        // Plain diffuse*env is substantially too dark compared with d3d.ren.
        c.rgb=clamp(2.0*vColor.rgb*env,0.0,1.0);
    }
    if(uFogEnabled!=0)
    {
        float fog=ComputeSceneFogAmount(vCameraPos);
        if(uFogAdditive!=0) c.rgb*=1.0-fog;
        else c.rgb=mix(c.rgb,uFogColor,fog);
    }
    outColor=c;
}
