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
uniform int uFogEnabled;
uniform int uUseColorKey;
uniform vec3 uColorKey;
uniform int uAlphaTest;
uniform float uAlphaRef;
uniform int uAlphaFunc;
uniform uint uMode;
uniform vec3 uModeColor;

const uint MODE_ADD_SIGNED  = (1u << 6);
const uint MODE_NO_LIGHT    = (1u << 7);
const uint MODE_FLAT_COLOR  = (1u << 8);
const uint MODE_MODULATE2X  = (1u << 16);

in vec2 vUV;
in vec4 vColor;
in float vFogZ;
layout(location=0) out vec4 outColor;
layout(location=1) out vec4 outSSRReceiver;

vec3 ColorOp(uint mode, vec3 c1, vec3 c2)
{
    if ((mode & MODE_ADD_SIGNED) != 0u)
        return c1 + c2 - vec3(0.5);
    else if ((mode & MODE_MODULATE2X) != 0u)
        return c1 * c2 * 2.0;
    else
        return c1 * c2;
}

void main()
{
    outSSRReceiver=vec4(1.0,0.0,0.0,1.0);
    vec4 texel = texture(uTexture, vUV);

    if (uUseColorKey != 0)
    {
        vec3 d = abs(texel.rgb - uColorKey);
        if (all(lessThanEqual(d, vec3(0.5 / 255.0))))
            discard;
    }

    // D3D8 StateChange can independently enable ALPHATEST and ALPHAREF.
    // The normal Talon sprite path still performs no implicit alpha discard.
    if (uAlphaTest != 0)
    {
        bool passAlpha = true;
        if      (uAlphaFunc == 1) passAlpha = false;
        else if (uAlphaFunc == 2) passAlpha = texel.a <  uAlphaRef;
        else if (uAlphaFunc == 3) passAlpha = texel.a == uAlphaRef;
        else if (uAlphaFunc == 4) passAlpha = texel.a <= uAlphaRef;
        else if (uAlphaFunc == 5) passAlpha = texel.a >  uAlphaRef;
        else if (uAlphaFunc == 6) passAlpha = texel.a != uAlphaRef;
        else if (uAlphaFunc == 7) passAlpha = texel.a >= uAlphaRef;
        else if (uAlphaFunc == 8) passAlpha = true;
        if (!passAlpha) discard;
    }

    // Do NOT alpha-discard here.
    //
    // The AVP2 D3D11 reference sprite shader does not discard based on alpha.
    // This matters for additive/multiply sprites: their blend states consume
    // RGB independently of source alpha, and some Talon sprite textures carry
    // useful RGB with zero/irrelevant alpha.
    //
    // Chromakey above remains the only explicit discard path.

    // Mirrors sprite_PS.hlsl:
    // alpha is texture alpha * object alpha,
    // RGB goes through ColorOp(texture, diffuse).
    vec4 result;
    result.a = texel.a * vColor.a;
    result.rgb = ColorOp(uMode, texel.rgb, vColor.rgb);

    // The D3D11 renderer applies global vertex tint unless MODE_NO_LIGHT.
    // Object-list menu scenes supply no world lighting/tint, so white is the
    // correct neutral equivalent here.

    if ((uMode & MODE_FLAT_COLOR) != 0u)
        result.rgb = uModeColor;

    if (uFogEnabled != 0 && uFogFar != uFogNear)
    {
        float fog = clamp((uFogNear - vFogZ) / (uFogNear - uFogFar), 0.0, 1.0);
        const uint MODE_BLEND_ADDITIVE = (1u << 17);
        if ((uMode & MODE_BLEND_ADDITIVE) != 0u)
            result.rgb *= (1.0 - fog);
        else
            result.rgb = mix(result.rgb, uFogColor, fog);
    }

    outColor = result;
}
