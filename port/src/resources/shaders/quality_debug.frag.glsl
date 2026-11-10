#version 460 core
layout(binding=0) uniform sampler2D uTex;
uniform vec4 uParams; // near,far,unused,unused
uniform int uMode; // 0 rgb, 1 depth, 2 alpha
in vec2 vUV; out vec4 outColor;
float ViewZ(float d){ float n=uParams.x,f=uParams.y; float A=(f+n)/(f-n); float B=(-2.0*f*n)/(f-n); float ndc=d*2.0-1.0; return abs(B/(ndc-A)); }
void main(){ vec4 s=texture(uTex,vUV); if(uMode==1){ float z=ViewZ(s.r); float q=clamp(log2(1.0+z)/log2(1.0+max(2.0,uParams.y)),0.0,1.0); outColor=vec4(vec3(q),1); } else if(uMode==2){ outColor=vec4(vec3(s.a),1); } else if(uMode==3){ outColor=vec4(vec3(s.r),1); } else outColor=vec4(s.rgb,1); }
