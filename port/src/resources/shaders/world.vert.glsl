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
#define uCameraPos frameCameraPos.xyz
#define uCameraQuat frameCameraQuat
#define uFogNear frameFogParams.x
#define uFogFar frameFogParams.y
layout(location=0) in vec3 aWorldPos;
layout(location=1) in vec2 aUV;
layout(location=2) in vec2 aLMUV;
layout(location=3) in vec4 aColor;
layout(location=4) in float aHasLightmap;
layout(location=5) in float aHasVertexLight;
layout(location=6) in vec3 aPolyCenter;
layout(location=7) in vec3 aPolyNormal;
layout(location=8) in vec3 aLMTangent;
layout(location=9) in vec3 aBaseTangent;

uniform int uUseWorld;
uniform mat4 uWorld;
uniform vec4 uObjectColor;
uniform uint uLegacyDrawFlags; // bit0=WorldModel, bit1=Sky
uniform int uSkyClipCameraSpace;
uniform int uUseWmDrawState;
uniform int uFogEnabled;
layout(binding=2) uniform sampler2D uLightGrid;
uniform int uUseGridLight;
uniform vec3 uLightGridDims;
uniform vec3 uLightGridLookupStart;
uniform vec3 uLightGridReciBlock;
uniform int uHighQualityLightGrid;
uniform vec3 uGlobalVertexTint;
uniform vec3 uGlobalWMAmbient;
uniform int uGpuVertexLight;
uniform uint uVertexLightVertexBase;
uniform uint uVertexLightDataBase;
uniform int uCpuWorldModelColor;
uniform uint uCpuWorldModelColorBase;
uniform int uStaticMaterialIndexFromBaseInstance;
uniform int uWorldModelGouraud;
uniform int uWorldModelBakedOnly;

struct AnimState {
    uvec4 frameFlags; // x=frame0, y=frame1, z=enabled, w=shadow
    vec4 params;      // x=between, y=blend
};
layout(std430,binding=4) readonly buffer AnimStateBuffer { AnimState gAnimStates[]; };
layout(std430,binding=6) readonly buffer VertexLightBuffer { uint gVertexLightData[]; };

struct WmDrawState {
    mat4 world;
    vec4 objectColor;
    uvec4 info;
};
layout(std430,binding=7) readonly buffer WmDrawStateBuffer { WmDrawState gWmDrawStates[]; };
layout(std430,binding=9) readonly buffer CpuWorldModelColorBuffer { float gCpuWorldModelColor[]; };
layout(std430,binding=10) readonly buffer SurfaceFxUvBuffer { vec4 gSurfaceFxUv[]; };
uniform uint uSurfaceFxUvBase;

uniform uint uTexFxMask;
uniform vec4 uTexFxParams0;
uniform vec4 uTexFxParams1;
uniform vec4 uTexFxParams2;
uniform float uTexFxTime;
uniform int uLinkedTexMode;
uniform vec4 uLinkedParams0; // legacy fallback: xy base UV scale, zw base scaled size
uniform vec4 uLinkedParams1; // legacy fallback: x detailScale, y cos, z sin, w linkedInvW
uniform vec4 uLinkedParams2; // legacy fallback: x linkedInvH, y DetailTextureAdd
struct WorldMaterialParams { vec4 linkedParams0; vec4 linkedParams1; vec4 linkedParams2; uvec4 info; };
layout(std430,binding=11) readonly buffer WorldMaterialParamBuffer { WorldMaterialParams gWorldMaterialParams[]; };
uniform int uUseWorldMaterialParams;
uniform uint uWorldMaterialParamIndex;
#define LINKED_PARAMS0 ((uUseWorldMaterialParams!=0)?gWorldMaterialParams[materialParamIndex].linkedParams0:uLinkedParams0)
#define LINKED_PARAMS1 ((uUseWorldMaterialParams!=0)?gWorldMaterialParams[materialParamIndex].linkedParams1:uLinkedParams1)
#define LINKED_PARAMS2 ((uUseWorldMaterialParams!=0)?gWorldMaterialParams[materialParamIndex].linkedParams2:uLinkedParams2)

out vec2 vUV;
out vec2 vLinkedUV;
out vec2 vLMUV;
out vec2 vPanSkyUV;
out vec4 vColor;
out float vHasLightmap;
out float vHasVertexLight;
out vec3 vLMTangentWorld;
out vec3 vBaseTangentWorld;
out float vFogZ;
noperspective out float vSkyFogFactor;
out vec3 vWorldPos;
out vec3 vWorldNormal;
flat out uint vMaterialParamIndex;
flat out int vWorldModelPass;
flat out uint vWorldDrawFlags;

vec3 qrotate(vec4 q,vec3 v)
{
    return v + 2.0*cross(q.xyz,cross(q.xyz,v)+q.w*v);
}

vec3 gridFetch(ivec3 p)
{
    int sy=int(uLightGridDims.y);
    int row=p.y + p.z*sy;
    return texelFetch(uLightGrid,ivec2(p.x,row),0).rgb*255.0;
}

vec3 cubicCR(vec3 p0,vec3 p1,vec3 p2,vec3 p3,float t)
{
    float t2=t*t, t3=t2*t;
    return 0.5*((2.0*p1)+(-p0+p2)*t+
        (2.0*p0-5.0*p1+4.0*p2-p3)*t2+
        (-p0+3.0*p1-3.0*p2+p3)*t3);
}

vec3 sampleLightGrid(vec3 worldPos)
{
    ivec3 dims=max(ivec3(uLightGridDims),ivec3(1));
    vec3 maxCoord=vec3(dims-1);
    vec3 c=clamp((worldPos-uLightGridLookupStart)*uLightGridReciBlock,
                 vec3(0.0),maxCoord);

    ivec3 i0=ivec3(floor(c));
    vec3 f=fract(c);

    // d3d.ren backs up one cell at the positive edge and uses forward weight
    // zero, selecting the penultimate lookup sample.
    for(int a=0;a<3;++a)
    {
        if(dims[a]<=1)
        {
            i0[a]=0;
            f[a]=0.0;
        }
        else if(i0[a]>=dims[a]-1)
        {
            i0[a]=dims[a]-2;
            f[a]=0.0;
        }
    }

    if(uHighQualityLightGrid!=0)
    {
        // 4x4x4 Catmull-Rom reconstruction.  This is intentionally optional:
        // it costs 64 LightTable fetches versus the baseline trilinear 8.
        vec3 yz[4][4];
        for(int zz=0;zz<4;++zz)
            for(int yy=0;yy<4;++yy)
            {
                int z=clamp(i0.z+zz-1,0,dims.z-1);
                int y=clamp(i0.y+yy-1,0,dims.y-1);
                vec3 px[4];
                for(int xx=0;xx<4;++xx)
                {
                    int x=clamp(i0.x+xx-1,0,dims.x-1);
                    px[xx]=gridFetch(ivec3(x,y,z));
                }
                yz[zz][yy]=cubicCR(px[0],px[1],px[2],px[3],f.x);
            }
        vec3 zv[4];
        for(int zz=0;zz<4;++zz)
            zv[zz]=cubicCR(yz[zz][0],yz[zz][1],yz[zz][2],yz[zz][3],f.y);
        return clamp(cubicCR(zv[0],zv[1],zv[2],zv[3],f.z),vec3(0.0),vec3(255.0));
    }

    ivec3 i1=min(i0+ivec3(1),dims-1);
    vec3 c000=gridFetch(ivec3(i0.x,i0.y,i0.z));
    vec3 c100=gridFetch(ivec3(i1.x,i0.y,i0.z));
    vec3 c010=gridFetch(ivec3(i0.x,i1.y,i0.z));
    vec3 c110=gridFetch(ivec3(i1.x,i1.y,i0.z));
    vec3 c001=gridFetch(ivec3(i0.x,i0.y,i1.z));
    vec3 c101=gridFetch(ivec3(i1.x,i0.y,i1.z));
    vec3 c011=gridFetch(ivec3(i0.x,i1.y,i1.z));
    vec3 c111=gridFetch(ivec3(i1.x,i1.y,i1.z));
    vec3 z0=mix(mix(c000,c100,f.x),mix(c010,c110,f.x),f.y);
    vec3 z1=mix(mix(c001,c101,f.x),mix(c011,c111,f.x),f.y);
    return mix(z0,z1,f.z);
}

vec3 unpackVertexRGB(uint p)
{
    return vec3(float((p>>16u)&255u),
                float((p>>8u)&255u),
                float(p&255u));
}

vec3 sampleGpuVertexLight(uint vertexIndex,vec3 fallbackColor,uint dataBase)
{
    if(uGpuVertexLight==0)
        return fallbackColor;

    uint descBase=dataBase+gVertexLightData[dataBase+0u];
    uint refBase=dataBase+gVertexLightData[dataBase+1u];
    uint colorBase=dataBase+gVertexLightData[dataBase+2u];
    uint vertexCount=gVertexLightData[dataBase+3u];
    if(vertexIndex>=vertexCount)
        return fallbackColor;

    uint di=descBase+vertexIndex*2u;
    uint refStart=gVertexLightData[di+0u];
    uint refCount=gVertexLightData[di+1u];
    if(refCount==0u)
        return fallbackColor;

    vec3 accum=vec3(0.0);
    bool found=false;
    for(uint ri=0u;ri<refCount;++ri)
    {
        uint rbase=refBase+(refStart+ri)*4u;
        uint animIndex=gVertexLightData[rbase+0u];
        uint colorStart=gVertexLightData[rbase+1u];
        uint frameCount=gVertexLightData[rbase+2u];
        if(frameCount==0u)
            continue;

        AnimState st=gAnimStates[animIndex];
        if(st.frameFlags.z==0u || st.params.y<0.02)
            continue;

        uint f0=min(st.frameFlags.x,frameCount-1u);
        uint f1=min(st.frameFlags.y,frameCount-1u);
        uint p0=gVertexLightData[colorBase+colorStart+f0];
        if(p0==0xFFFFFFFFu)
            continue;
        uint p1=gVertexLightData[colorBase+colorStart+f1];
        if(p1==0xFFFFFFFFu)
            p1=p0;

        vec3 a=unpackVertexRGB(p0);
        vec3 b=unpackVertexRGB(p1);
        float tf=clamp(st.params.x,0.0,1.0);
        uint t=uint(clamp(floor(tf*255.0+0.5),0.0,255.0));
        uint it=255u-t;
        uvec3 ai=uvec3(a+0.5);
        uvec3 bi=uvec3(b+0.5);
        uvec3 mixed=(t==0u)?ai:((t==255u)?bi:
            min(uvec3(255u),(ai*it)/255u+(bi*t)/255u));
        // 0x10092168 is a saturating-add table.
        accum=min(vec3(255.0),accum+vec3(mixed));
        found=true;
    }

    return found ? (accum/255.0) : fallbackColor;
}

void main()
{
    vec4 q=normalize(uCameraQuat);
    vec4 qi=vec4(-q.xyz,q.w);

    mat4 objectWorld=uWorld;
    vec4 objectColor=uObjectColor;
    int useWorld=uUseWorld;
    uint vertexLightVertexBase=uVertexLightVertexBase;
    uint vertexLightDataBase=uVertexLightDataBase;
    bool drawHasVertexLight=true;
    uint materialParamIndex=(uStaticMaterialIndexFromBaseInstance!=0)?uint(gl_BaseInstance):uWorldMaterialParamIndex;
    uint worldDrawFlags=uLegacyDrawFlags;
    int worldModelPass=((worldDrawFlags & 1u)!=0u)?1:0;
    if(uUseWmDrawState!=0)
    {
        WmDrawState ds=gWmDrawStates[uint(gl_BaseInstance)];
        objectWorld=ds.world;
        objectColor=ds.objectColor;
        useWorld=1;
        vertexLightVertexBase=ds.info.x;
        vertexLightDataBase=ds.info.y;
        drawHasVertexLight=(ds.info.z!=0u);
        materialParamIndex=ds.info.w;
        worldModelPass=1;
        worldDrawFlags|=1u;
    }

    vec3 worldPos=(useWorld!=0)?(objectWorld*vec4(aWorldPos,1.0)).xyz:aWorldPos;
    vec3 worldNormal=(useWorld!=0)?(mat3(objectWorld)*aPolyNormal):aPolyNormal;
    float worldNormalLen=length(worldNormal);
    vec3 p;
    if(uSkyClipCameraSpace!=0)
    {
        // CPU-clipped sky vertices are already in camera space.  Keeping the
        // generated near-plane intersections near the origin avoids losing
        // most of their precision by storing them back at Talon's ~116k-unit
        // authored sky coordinates and subtracting the sky camera again.
        p=aWorldPos;
        worldPos=uCameraPos+qrotate(q,p);
    }
    else
        p=qrotate(qi,worldPos-uCameraPos);
    vWorldPos=worldPos;
    vWorldNormal=(worldNormalLen>0.00001)?(worldNormal/worldNormalLen):vec3(0.0);
    // Polygon-constant +lightmap-U tangent.  WorldModels carry it in local
    // space, so apply the same object transform as their normal.
    vec3 lmTangentWorld=aLMTangent;
    if(uUseWorld!=0)
        lmTangentWorld=mat3(uWorld)*lmTangentWorld;
    vLMTangentWorld=lmTangentWorld;
    vec3 baseTangentWorld=aBaseTangent;
    if(uUseWorld!=0) baseTangentWorld=mat3(uWorld)*baseTangentWorld;
    vBaseTangentWorld=baseTangentWorld;

    // Do NOT clamp camera-space Z to the near plane.  M3.0 currently
    // submits the entire BSP, including geometry behind the camera.
    // Homogeneous clipping must reject those vertices/polygons naturally.
    //
    // Clamping p.z here projected every behind-camera vertex onto NearZ,
    // producing giant perspective wedges across the screen.
    float z=p.z;
    float clipZ;
    if(uSkyClipCameraSpace!=0)
    {
        // Infinite-far perspective for the dedicated sky-object painter pass.
        // With z>=NearZ this gives clipZ<=w for every finite camera-space z,
        // so OpenGL's homogeneous far plane cannot cut the authored sky shell.
        // The near plane remains exactly the same and sky fog is independent.
        clipZ=z-2.0*uNearZ;
    }
    else
    {
        float A=(uFarZ+uNearZ)/(uFarZ-uNearZ);
        float B=(-2.0*uFarZ*uNearZ)/(uFarZ-uNearZ);
        clipZ=A*z+B;
    }

    gl_Position=vec4(p.x/uTanHalfFovX,
                     p.y/uTanHalfFovY,
                     clipZ,z);
    // Cached Talon SPolyVertex UVs are normalized by the texture frame that
    // was active when the BSP cache was built. SURF_SPRITEANIMATE can replace
    // Surface::m_pTexture live, so correct the normalization before all base
    // texture effects.
    vec2 authoredUV=aUV;
    {
        vec4 fxuv=gSurfaceFxUv[uSurfaceFxUvBase+uint(gl_VertexID)];
        if(fxuv.z>0.5) authoredUV=fxuv.xy;
    }
    vec2 sourceUV=authoredUV*LINKED_PARAMS0.xy;
    vec2 uv=sourceUV;
    if((uTexFxMask&1u)!=0u)
        uv+=uTexFxParams0.xy*uTexFxTime;
    if((uTexFxMask&2u)!=0u)
    {
        float a=radians(uTexFxParams0.z)*uTexFxTime;
        float c=cos(a),sn=sin(a);
        vec2 d=uv-vec2(0.5);
        uv=vec2(d.x*c-d.y*sn,d.x*sn+d.y*c)+vec2(0.5);
    }
    if((uTexFxMask&4u)!=0u)
    {
        float t=uTexFxTime*uTexFxParams1.x*0.1;
        vec2 baseUV=uv;
        uv.x+=sin(baseUV.y*6.2831853+t)*uTexFxParams0.w;
        uv.y+=cos(baseUV.x*6.2831853+t)*uTexFxParams0.w;
    }
    // PanningSky is a separate projected cloud-shadow overlay.  Do not
    // replace the base texture coordinates with the projected coordinates.
    vPanSkyUV=((uTexFxMask&8u)!=0u)
        ? vec2((worldPos.x+uTexFxParams1.y)*uTexFxParams2.x,
               (worldPos.z+uTexFxParams1.z)*uTexFxParams2.y)
        : vec2(0.0);

    vUV=uv;

    // AVP2/Talon linked texture coordinates. Detail texture coordinates are
    // generated from the authored ScaledU/ScaledV pixel coordinates, while
    // environment coordinates are a per-vertex reflection mapping from the
    // camera, vertex position and polygon normal (d3d.ren 0x1001085E).
    vLinkedUV=vec2(0.0);
    int linkedTexMode=(uUseWorldMaterialParams!=0)?int(gWorldMaterialParams[materialParamIndex].info.x):uLinkedTexMode;
    if(linkedTexMode==1)
    {
        vec2 pixelUV=sourceUV*LINKED_PARAMS0.zw;
        float detailScale=LINKED_PARAMS1.x;
        float c=LINKED_PARAMS1.y;
        float sn=LINKED_PARAMS1.z;
        vLinkedUV=vec2(
            (pixelUV.x*c-pixelUV.y*sn)*detailScale*LINKED_PARAMS1.w,
            (pixelUV.x*sn+pixelUV.y*c)*detailScale*LINKED_PARAMS2.x);
    }
    else if(linkedTexMode==2 || linkedTexMode==3)
    {
        vec3 nrm=(worldNormalLen>0.00001)?(worldNormal/worldNormalLen):vec3(0.0);
        vec3 incident=worldPos-uCameraPos;
        float ilen=length(incident);
        vec3 reflected=(ilen>0.00001 && dot(nrm,nrm)>0.25)
            ? reflect(incident/ilen,nrm) : vec3(0.0,0.0,1.0);
        float chosen=((nrm.y*nrm.y)>0.5443900227546692 ||
                      (nrm.x*nrm.x)>(nrm.z*nrm.z))
            ? reflected.x : reflected.z;
        vLinkedUV=vec2(0.5-0.5*chosen,0.5-0.5*reflected.y);
    }

    vLMUV=aLMUV;
    vec3 authoredColor=aColor.rgb;
    if(aHasVertexLight>0.5 && uCpuWorldModelColor!=0)
    {
        uint ci=uCpuWorldModelColorBase+uint(gl_VertexID)*3u;
        authoredColor=vec3(gCpuWorldModelColor[ci+0u],
                           gCpuWorldModelColor[ci+1u],
                           gCpuWorldModelColor[ci+2u]);
    }
    else if(aHasVertexLight>0.5 && uGpuVertexLight!=0 && drawHasVertexLight)
    {
        uint vertexIndex=uint(gl_VertexID);
        if(vertexIndex>=vertexLightVertexBase)
            vertexIndex-=vertexLightVertexBase;
        authoredColor=sampleGpuVertexLight(vertexIndex,authoredColor,vertexLightDataBase);
    }

    if((vWorldDrawFlags & 2u)!=0u)
    {
        // d3d.ren 0x1001056E copies SceneDesc::m_vGlobalVertexTint (+0x5C)
        // into the renderer RGB multipliers.  The dedicated sky builder at
        // 0x10019583..0x100195CD then multiplies LTObject RGB by those three
        // values before 0x100193BC..0x1001942C multiplies the authored
        // SPolyVertex RGB.  This is what makes AVP2 vision-mode sky colours
        // follow Heat/Electro/Night vision instead of remaining stock green.
        vec3 skyScale=clamp(objectColor.rgb*uGlobalVertexTint,vec3(0.0),vec3(1.0));
        vColor=vec4(clamp(aColor.rgb*skyScale,vec3(0.0),vec3(1.0)),
                    objectColor.a);
    }
    else if(uWorldModelBakedOnly!=0)
    {
        // Gouraud-only WorldModels already contain compiled static lighting in
        // their authored/LightAnim vertex colors. Stock WorldModel ambient is
        // still added with byte-range saturation.
        vec3 lit255=min(vec3(255.0),authoredColor*255.0+uGlobalWMAmbient);
        vec3 scale=clamp(objectColor.rgb*uGlobalVertexTint,vec3(0.0),vec3(1.0));
        vColor=vec4((lit255/255.0)*scale,aColor.a*objectColor.a);
    }
    else if(uUseGridLight!=0)
    {
        // Original d3d.ren samples MainWorld::m_LightTable at the polygon
        // center, adds that and GlobalWMAmbient to the baked SPolyVertex RGB
        // with saturation, then multiplies by object RGB * GlobalVertexTint.
        // d3d.ren 0x10030447..0x1003045D passes WorldPoly::m_vCenter
        // directly to MainWorld::m_LightTable.  Do NOT transform the center
        // through the WorldModel object matrix here; that samples a different
        // light-grid cell for translated/rotated brush WorldModels.
        // Stock D3D samples one value at WorldPoly::m_vCenter in the BSP's
        // authored coordinate space; it does NOT run that point through the
        // WorldModel instance transform before querying MainWorld::m_LightTable.
        vec3 grid255=sampleLightGrid(aPolyCenter);
        vec3 lit255=min(vec3(255.0),authoredColor*255.0+grid255+uGlobalWMAmbient);
        // 0x100305C2..0x100305E7 applies object RGB/global vertex tint after
        // the saturating light add.
        vec3 scale=clamp(objectColor.rgb*uGlobalVertexTint,vec3(0.0),vec3(1.0));
        vColor=vec4((lit255/255.0)*scale,aColor.a*objectColor.a);
    }
    else
    {
        vColor=vec4(authoredColor*clamp(uGlobalVertexTint,vec3(0.0),vec3(1.0)),
                    aColor.a*objectColor.a);
    }
    vHasLightmap=aHasLightmap;
    vHasVertexLight=aHasVertexLight;
    vFogZ=max(p.z,0.0);


    // Stock d3d.ren sky fog parity.  The dedicated sky polygon path
    // transforms/clips the polygon first, then 0x10019351 calls the active
    // fog helper (0x10058C40).  In normal AVP2 sky fog that helper is
    // 0x10013560, which converts camera-space Z into an 8-bit visibility
    // factor and stores it in transformed-vertex specular alpha.  D3D then
    // interpolates that vertex fog factor across the polygon.  Do not
    // recompute sky fog per-fragment from interpolated Z.
    vSkyFogFactor=1.0;
    if((worldDrawFlags & 2u)!=0u && uFogEnabled!=0 && uFogFar!=uFogNear)
    {
        float vis;
        if(p.z<uFogNear) vis=1.0;
        else if(p.z>=uFogFar) vis=0.0;
        else vis=clamp((uFogFar-p.z)/(uFogFar-uFogNear),0.0,1.0);
        // d3d.ren stores the factor in an 8-bit alpha channel before draw.
        vSkyFogFactor=floor(vis*255.0+0.5)/255.0;
    }
    vMaterialParamIndex=materialParamIndex;
    vWorldModelPass=worldModelPass;
    vWorldDrawFlags=worldDrawFlags;
}
