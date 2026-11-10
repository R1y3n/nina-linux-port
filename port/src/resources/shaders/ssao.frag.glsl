#version 460 core
layout(binding=0) uniform sampler2D uColor;
layout(binding=1) uniform sampler2D uDepth;
uniform vec4 uParams0; // tanHalfFovX,tanHalfFovY,near,far
uniform vec4 uParams1; // invW,invH,strength,radiusPixels
uniform vec4 uParams2; // bias,minAO,unused,unused
in vec2 vUV; out vec4 outColor;
float ViewZ(float d){ float n=uParams0.z,f=uParams0.w; float A=(f+n)/(f-n); float B=(-2.0*f*n)/(f-n); float ndc=d*2.0-1.0; return B/(ndc-A); }
vec3 Pos(vec2 uv){ float d=texture(uDepth,uv).r; float z=ViewZ(d); vec2 ndc=uv*2.0-1.0; return vec3(ndc.x*uParams0.x*z,ndc.y*uParams0.y*z,z); }
vec3 NormalAt(vec2 uv){ vec2 px=uParams1.xy; vec3 p=Pos(uv); vec3 px1=Pos(clamp(uv+vec2(px.x,0),0.0,1.0)); vec3 py1=Pos(clamp(uv+vec2(0,px.y),0.0,1.0)); vec3 n=normalize(cross(px1-p,py1-p)); if(n.z>0.0)n=-n; return n; }
void main(){ float d=texture(uDepth,vUV).r; if(d>=0.999999){outColor=vec4(1.0);return;} vec3 p=Pos(vUV); vec3 n=NormalAt(vUV); float occ=0.0; const vec2 dirs[12]=vec2[12](vec2(1,0),vec2(-1,0),vec2(0,1),vec2(0,-1),vec2(.707,.707),vec2(-.707,.707),vec2(.707,-.707),vec2(-.707,-.707),vec2(.383,.924),vec2(-.383,.924),vec2(.924,.383),vec2(-.924,.383));
 float rp=uParams1.w; for(int i=0;i<12;i++){ float ring=1.0+float(i%3)*0.65; vec2 suv=clamp(vUV+dirs[i]*uParams1.xy*rp*ring,0.001,0.999); float sd=texture(uDepth,suv).r; if(sd>=0.999999)continue; vec3 q=Pos(suv); vec3 v=q-p; float dist=length(v); float hemi=max(dot(n,v/max(dist,1e-4))-uParams2.x,0.0); float atten=1.0-smoothstep(0.0,max(20.0,abs(p.z)*0.12),dist); occ+=hemi*atten; }
 float ao=clamp(1.0-occ/12.0*uParams1.z,uParams2.y,1.0); outColor=vec4(ao,ao,ao,1.0); }
