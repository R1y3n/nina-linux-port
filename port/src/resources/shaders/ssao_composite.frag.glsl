#version 460 core
layout(binding=0) uniform sampler2D uColor;
layout(binding=1) uniform sampler2D uAO;
in vec2 vUV; out vec4 outColor;
void main(){ vec4 c=texture(uColor,vUV); float ao=texture(uAO,vUV).r; outColor=vec4(c.rgb*ao,c.a); }
