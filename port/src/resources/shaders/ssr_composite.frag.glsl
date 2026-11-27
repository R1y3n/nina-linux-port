#version 460 core
layout(binding=0) uniform sampler2D uColor;
layout(binding=1) uniform sampler2D uReflection;
uniform float uStrength;
in vec2 vUV; out vec4 outColor;
void main(){ vec4 c=texture(uColor,vUV); vec4 r=texture(uReflection,vUV); float w=clamp(r.a*uStrength,0.0,0.85); outColor=vec4(mix(c.rgb,r.rgb,w),c.a); }
