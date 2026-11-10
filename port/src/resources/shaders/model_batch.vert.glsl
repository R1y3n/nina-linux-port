#version 460 core
layout(std140,binding=12) uniform FramePassConstants {
    vec4 frameProjection;      // tanHalfX, tanHalfY, nearZ, farZ
    vec4 frameCameraPos;       // xyz
    vec4 frameCameraQuat;      // xyzw
    vec4 frameFogColorEnabled; // rgb, enabled
    vec4 frameFogParams;       // near, far, frameTime, unused
};
#define uTanHalfFovX frameProjection.x
#define uTanHalfFovY frameProjection.y
#define uNearZ frameProjection.z
#define uFarZ frameProjection.w
#define uCamPos frameCameraPos.xyz
#define uCamQuat frameCameraQuat
layout(location=0) in vec3 aLocalPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aUV;
layout(location=3) in vec4 aWeight0;
layout(location=4) in vec4 aWeight1;
layout(location=5) in vec4 aWeight2;
layout(location=6) in vec4 aWeight3;
layout(location=7) in vec4 aNodeIndex;
layout(location=8) in vec2 aMeta; // x=weightCount, y=skinIndex

layout(std430,binding=0) readonly buffer NodeRows { vec4 nodeRows[]; };
struct ModelLight
{
    vec4 posRadius;
    vec4 innerType;
    vec4 dirFov;
    vec4 outerClose;
};
layout(std430,binding=1) readonly buffer ModelLights { ModelLight modelLights[]; };
layout(std430,binding=2) readonly buffer SkinStates { vec4 skinData[]; };

uniform vec3 uObjPos;
uniform vec3 uObjScale;
uniform vec4 uObjQuat;
uniform int uReallyClose;
uniform int uNodeCount;
uniform vec3 uAmbient;
uniform vec3 uLightAdd;
uniform vec3 uHookColor;
uniform vec3 uDirColor;
uniform vec3 uDirCamera;
uniform float uModelAlpha;
uniform int uLightCount;
uniform vec4 uModelEnvParams;

const uint MODE_NO_LIGHT=(1u<<7);

out vec2 vUV;
out vec3 vCamPos;
out vec3 vEnvNormal;
out vec2 vEnvUV;
out vec4 vColor;
out float vFogZ;
flat out int vSkinIndex;

vec4 QNormalize(vec4 q)
{
    float d=length(q);
    return d>1e-8?q/d:vec4(0.0,0.0,0.0,1.0);
}

vec3 QRotate(vec4 q,vec3 v)
{
    q=QNormalize(q);
    vec3 u=q.xyz;
    float s=q.w;
    return 2.0*u*dot(u,v)+v*(s*s-dot(u,u))+2.0*s*cross(u,v);
}

vec4 TransformWeight(uint node,vec4 v)
{
    uint b=node*4u;
    return vec4(dot(nodeRows[b+0u],v),
                dot(nodeRows[b+1u],v),
                dot(nodeRows[b+2u],v),
                dot(nodeRows[b+3u],v));
}

vec3 SkinPosition()
{
    int wc=clamp(int(aMeta.x+0.5),0,4);
    if(wc==0 || uNodeCount<=0)
        return aLocalPos;

    vec4 sum=vec4(0.0);
    vec4 weights[4]=vec4[4](aWeight0,aWeight1,aWeight2,aWeight3);
    for(int i=0;i<wc;++i)
    {
        uint node=min(uint(aNodeIndex[i]+0.5),uint(uNodeCount-1));
        sum+=TransformWeight(node,weights[i]);
    }
    return abs(sum.w)>1e-7?sum.xyz/sum.w:sum.xyz;
}

vec3 SkinNormal(vec3 bindNormal)
{
    int wc=clamp(int(aMeta.x+0.5),0,4);
    if(wc==0 || uNodeCount<=0)
        return normalize(bindNormal);

    vec4 weights[4]=vec4[4](aWeight0,aWeight1,aWeight2,aWeight3);
    vec3 sum=vec3(0.0);
    float sumWeight=0.0;
    for(int i=0;i<wc;++i)
    {
        uint node=min(uint(aNodeIndex[i]+0.5),uint(uNodeCount-1));
        float w=weights[i].w;
        if(abs(w)<=1e-8)
            continue;
        uint b=node*4u;
        vec3 n=vec3(dot(nodeRows[b+0u].xyz,bindNormal),
                    dot(nodeRows[b+1u].xyz,bindNormal),
                    dot(nodeRows[b+2u].xyz,bindNormal));
        sum+=n*w;
        sumWeight+=w;
    }
    if(abs(sumWeight)>1e-8)
        sum/=sumWeight;
    return dot(sum,sum)>1e-12?normalize(sum):normalize(bindNormal);
}

vec3 ToCameraPosition(vec3 modelPos)
{
    vec3 world=QRotate(uObjQuat,modelPos*uObjScale)+uObjPos;
    if(uReallyClose!=0)
        return world;
    vec4 cq=QNormalize(uCamQuat);
    return QRotate(vec4(-cq.xyz,cq.w),world-uCamPos);
}

vec3 ToCameraNormal(vec3 n)
{
    vec3 modelN=QRotate(uObjQuat,n);
    if(uReallyClose!=0)
        return normalize(modelN);
    vec4 cq=QNormalize(uCamQuat);
    return normalize(QRotate(vec4(-cq.xyz,cq.w),modelN));
}

// Stock d3d.ren's model environment callback (0x10001420) transforms the
// animated vertex normal through the model/view orientation even when the
// model position itself uses the special ReallyClose projection.  Keep that
// distinction explicit: RC positions are camera-relative, env normals are
// still view-oriented so chrome responds to camera yaw/pitch.
vec3 ToEnvironmentNormal(vec3 n)
{
    vec3 modelN=QRotate(uObjQuat,n);
    vec4 cq=QNormalize(uCamQuat);
    return normalize(QRotate(vec4(-cq.xyz,cq.w),modelN));
}

vec3 ComputeLighting(vec3 cam,vec3 normal,uint mode)
{
    if((mode&MODE_NO_LIGHT)!=0u)
        return vec3(1.0);

    vec3 direct=vec3(0.0);
    float sunNdl=max(0.0,-dot(normal,uDirCamera));
    direct+=uDirColor*sunNdl;

    for(int i=0;i<uLightCount;++i)
    {
        ModelLight l=modelLights[i];
        vec3 to=l.posRadius.xyz-cam;
        float dist=length(to);
        float radius=l.posRadius.w;
        if(dist<=0.0001 || dist>=radius)
            continue;
        to/=dist;
        float dn=1.0-min(1.0,dist/radius);
        float intensity=max(0.0,dot(to,normal));
        if(l.outerClose.w>0.5)
            intensity+=pow(dn,5.0);

        vec3 color=l.innerType.rgb;
        if(l.innerType.w>0.5)
        {
            float cone=-dot(to,l.dirFov.xyz);
            if(cone<l.dirFov.w)
                continue;
            float denom=1.0-l.dirFov.w;
            float t=denom>0.0001?clamp((cone-l.dirFov.w)/denom,0.0,1.0):1.0;
            color=mix(l.outerClose.rgb,l.innerType.rgb,t);
        }
        intensity*=dn;
        direct+=color*intensity;
    }

    // Stock d3d.ren accumulates model-light values in 0..255 diffuse space
    // and saturates the completed vertex diffuse to 255. All values in this
    // shader are already normalized to 0..1, so no *2 gain or 1.2 ceiling
    // belongs here.
    direct=clamp(direct,vec3(0.0),vec3(1.0));
    // ModelHookData::m_pLightAdd remains an untinted pre-texture diffuse term.
    return min(vec3(1.0),uAmbient+direct+uLightAdd);
}

void main()
{
    int skin=clamp(int(aMeta.y+0.5),0,3);
    vec4 s0=skinData[skin*2+0];
    uint mode=uint(s0.x+0.5);

    vec3 modelPos=SkinPosition();
    vec3 cam=ToCameraPosition(modelPos);

    // Keep diffuse lighting on Talon's authored model-normal path.  The
    // environment callback is a separate operation in d3d.ren and does use
    // the animated/view-transformed normal; using our reconstructed skinned
    // normal for N.L made ReallyClose weapon lighting appear inverted.
    vec3 skinnedNormal=SkinNormal(aNormal);
    vec3 lightNormal=ToCameraNormal(aNormal);
    vec3 envNormal=ToEnvironmentNormal(skinnedNormal);
    vec3 lit=ComputeLighting(cam,lightNormal,mode);

    float z=cam.z;
    float A=(uFarZ+uNearZ)/(uFarZ-uNearZ);
    float B=(-2.0*uFarZ*uNearZ)/(uFarZ-uNearZ);
    gl_Position=vec4(cam.x/uTanHalfFovX,
                     cam.y/uTanHalfFovY,
                     A*z+B,
                     z);

    vUV=aUV;
    // Pass the actual GPU-skinned camera-space surface into the fragment
    // stage.  Environment reflection is derived there from screen-space
    // derivatives of this deformed surface, rather than trusting Talon's
    // bind-pose normal stream to describe animated deformation.
    vCamPos=cam;
    vEnvNormal=envNormal;
    // d3d.ren 0x10001420 generates model environment coordinates per vertex
    // from the transformed normal.  EnvScale=1 maps [-1,+1] to [0,1].
    float envHalf=0.5*uModelEnvParams.x;
    vEnvUV=vec2(0.5+envNormal.x*envHalf+uModelEnvParams.y,
                0.5-envNormal.y*envHalf+uModelEnvParams.z);
    vColor=vec4(lit,uModelAlpha);
    // Retail d3d.ren installs D3DFOG_LINEAR as FOGTABLEMODE and supplies
    // FOGSTART/FOGEND globally.  This is depth/table fog, not range fog.
    // Talon camera space is +Z forward, so emulate the fixed-function depth
    // coordinate with camera-space Z.
    vFogZ=max(cam.z,0.0);
    vSkinIndex=skin;
}
