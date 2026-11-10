#version 460 core
layout(binding=0) uniform sampler2D uScene;
uniform vec4 uBloomParams; // threshold, softKnee, intensity(unused here), unused
in vec2 vUV; out vec4 outColor;
void main(){
    vec3 c=texture(uScene,vUV).rgb;
    float l=max(max(c.r,c.g),c.b);
    float threshold=uBloomParams.x;
    float knee=max(1e-4,uBloomParams.y);
    float soft=clamp((l-threshold+knee)/(2.0*knee),0.0,1.0);
    soft=soft*soft*(3.0-2.0*soft);
    float hard=max(l-threshold,0.0);
    float contribution=max(hard,soft*knee)/max(l,1e-4);
    outColor=vec4(c*contribution,1.0);
}
