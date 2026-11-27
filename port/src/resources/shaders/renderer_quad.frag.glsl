#version 460 core
layout(binding=0) uniform sampler2D uTex;
uniform vec4 uColor;
uniform float uAlpha;
uniform int uUseKey;
uniform vec3 uKey;
uniform int uUseTexAlpha;
in vec2 vUV;
out vec4 outColor;

void main()
{
    vec4 s = texture(uTex, vUV);

    if (uUseKey != 0)
    {
        ivec3 px = ivec3(round(s.rgb * 255.0));
        ivec3 key = ivec3(round(uKey * 255.0));
        if (all(equal(px, key)))
            discard;
    }

    // Stock d3d_OptimizeSurface converts the color key into texture alpha
    // before filtering. Direct/nonoptimized copies remain XRGB-style.
    float texAlpha = (uUseTexAlpha != 0) ? s.a : 1.0;
    outColor = vec4(s.rgb * uColor.rgb, texAlpha * uAlpha * uColor.a);
}
