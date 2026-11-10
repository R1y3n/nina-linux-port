#version 460 core
layout(binding=0) uniform sampler2D uEffect;
layout(binding=1) uniform sampler2D uDepth;
uniform vec4 uParams0; // invW,invH,radius,depthToleranceWorld
uniform vec4 uParams1; // dirX,dirY,near,far
in vec2 vUV; out vec4 outColor;
float ViewZ(float d){ float n=uParams1.z,f=uParams1.w; float A=(f+n)/(f-n); float B=(-2.0*f*n)/(f-n); float ndc=d*2.0-1.0; return B/(ndc-A); }
void main(){ float radius=clamp(uParams0.z,0.0,8.0); if(radius<0.5){outColor=texture(uEffect,vUV);return;} float cd=texture(uDepth,vUV).r; float cz=ViewZ(cd); vec4 sum=vec4(0); float ws=0.0; float sigma=max(0.75,radius*0.55); for(int i=-8;i<=8;i++){ float fi=float(i); if(abs(fi)>radius+0.01)continue; vec2 uv=clamp(vUV+vec2(uParams1.xy)*uParams0.xy*fi,0.001,0.999); float sd=texture(uDepth,uv).r; float sz=ViewZ(sd); float spatial=exp(-(fi*fi)/(2.0*sigma*sigma)); float dw=exp(-abs(sz-cz)/max(0.01,uParams0.w)); float w=spatial*dw; sum+=texture(uEffect,uv)*w; ws+=w; } outColor=sum/max(ws,1e-5); }
