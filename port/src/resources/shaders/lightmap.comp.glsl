#version 460 core
layout(local_size_x=8,local_size_y=8,local_size_z=1) in;

struct TileDesc {
    uint x; uint y; uint w; uint h;
    uint refStart; uint refCount; uint pad0; uint pad1;
};
struct RefDesc {
    uint animIndex; uint frameOffsetStart; uint pixelCount; uint pad;
};
struct AnimState {
    // Keep this layout exactly 32 bytes/std430-compatible with GpuLmAnimState.
    // Avoid GLSL reserved identifiers (notably `active`) by using packed vectors.
    uvec4 frameFlags; // x=frame0, y=frame1, z=enabled, w=shadow
    vec4 params;      // x=between, y=blend, z/w=unused
};

layout(std430,binding=0) readonly buffer TileBuffer { TileDesc gTiles[]; };
layout(std430,binding=1) readonly buffer RefBuffer { RefDesc gRefs[]; };
layout(std430,binding=2) readonly buffer FrameOffsetBuffer { uint gFrameOffsets[]; };
layout(std430,binding=3) readonly buffer SourcePixelBuffer { uint gSourcePixels[]; };
layout(std430,binding=4) readonly buffer AnimStateBuffer { AnimState gAnimStates[]; };
layout(std430,binding=5) readonly buffer DirtyTileBuffer { uint gDirtyTiles[]; };
layout(rgba8,binding=0) uniform writeonly image2D uLightAtlas;

uvec3 unpackRGB(uint p)
{
    return uvec3((p>>16u)&255u,(p>>8u)&255u,p&255u);
}

void main()
{
    uint dirtyIndex=gl_WorkGroupID.x;
    TileDesc tile=gTiles[gDirtyTiles[dirtyIndex]];

    for(uint py=gl_LocalInvocationID.y;py<tile.h;py+=gl_WorkGroupSize.y)
    {
        for(uint px=gl_LocalInvocationID.x;px<tile.w;px+=gl_WorkGroupSize.x)
        {
            uint pixel=py*tile.w+px;
            uvec3 accum=uvec3(0u);

            for(uint ri=0u;ri<tile.refCount;++ri)
            {
                RefDesc ref=gRefs[tile.refStart+ri];
                AnimState st=gAnimStates[ref.animIndex];
                if(st.frameFlags.z==0u || st.frameFlags.w!=0u || st.params.y<0.02)
                    continue;

                uint off0=gFrameOffsets[ref.frameOffsetStart+st.frameFlags.x];
                if(off0==0xFFFFFFFFu)
                    continue;
                uint off1=gFrameOffsets[ref.frameOffsetStart+st.frameFlags.y];
                if(off1==0xFFFFFFFFu)
                    off1=off0;

                uvec3 a=unpackRGB(gSourcePixels[off0+pixel]);
                uvec3 b=unpackRGB(gSourcePixels[off1+pixel]);
                // CPU compatibility path truncates both interpolation and the
                // blend multiply to integer channels.  Keep those semantics so
                // moving composition to compute does not alter authored light.
                uvec3 mixed=uvec3(mix(vec3(a),vec3(b),clamp(st.params.x,0.0,1.0)));
                uvec3 add=uvec3(vec3(mixed)*clamp(st.params.y,0.0,1.0));
                accum=min(uvec3(255u),accum+add);
            }

            imageStore(uLightAtlas,ivec2(int(tile.x+px),int(tile.y+py)),
                       vec4(vec3(accum)/255.0,1.0));
        }
    }
}
