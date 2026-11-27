#version 460 core
layout(binding=0) uniform sampler2D uShadowTex;
uniform float uShadowAlpha;
uniform int uFogEnabled;
uniform float uFogNear;
uniform float uFogFar;
in vec2 vUV;
in float vFogZ;
layout(location=0) out vec4 FragColor;
layout(location=1) out vec4 outSSRReceiver;
void main()
{
    outSSRReceiver=vec4(1.0,0.0,0.0,1.0);
    float a=texture(uShadowTex,vUV).a*uShadowAlpha;
    if(uFogEnabled!=0)
    {
        float fog=clamp((vFogZ-uFogNear)/max(uFogFar-uFogNear,0.0001),0.0,1.0);
        a*=1.0-fog;
    }
    if(a<0.003) discard;
    FragColor=vec4(0.0,0.0,0.0,a);
}
