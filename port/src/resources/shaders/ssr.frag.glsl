#version 460 core
layout(binding=0) uniform sampler2D uColor;
layout(binding=1) uniform sampler2D uDepth;
layout(binding=2) uniform sampler2D uMaterialReceiver;
uniform vec4 uParams0; // tanX,tanY,near,far
uniform vec4 uParams1; // invW,invH,unused,maxDistance
uniform vec4 uParams2; // thicknessBase,thicknessScale,normalBias,steps
uniform vec4 uFilter0; // enabled,invert,hueCenter,hueWidth
uniform vec4 uFilter1; // satMin,satMax,valueMin,valueMax
uniform vec4 uFilter2; // alphaMin,softness,unused,unused
in vec2 vUV; out vec4 outColor;
float ViewZ(float d){ float n=uParams0.z,f=uParams0.w; float A=(f+n)/(f-n); float B=(-2.0*f*n)/(f-n); float ndc=d*2.0-1.0; return B/(ndc-A); }
vec3 Pos(vec2 uv){ float z=ViewZ(texture(uDepth,uv).r); vec2 ndc=uv*2.0-1.0; return vec3(ndc.x*uParams0.x*z,ndc.y*uParams0.y*z,z); }
vec3 NormalAt(vec2 uv){ vec2 px=uParams1.xy; vec3 p=Pos(uv); vec3 x=Pos(clamp(uv+vec2(px.x,0),0.0,1.0)); vec3 y=Pos(clamp(uv+vec2(0,px.y),0.0,1.0)); vec3 n=normalize(cross(x-p,y-p)); if(n.z>0.0)n=-n; return n; }
vec2 Project(vec3 p){ return vec2(p.x/(uParams0.x*p.z),p.y/(uParams0.y*p.z))*0.5+0.5; }
vec3 RGB2HSV(vec3 c){ vec4 K=vec4(0.,-1./3.,2./3.,-1.); vec4 p=mix(vec4(c.bg,K.wz),vec4(c.gb,K.xy),step(c.b,c.g)); vec4 q=mix(vec4(p.xyw,c.r),vec4(c.r,p.yzx),step(p.x,c.r)); float d=q.x-min(q.w,q.y),e=1e-10; return vec3(abs(q.z+(q.w-q.y)/(6.*d+e)),d/(q.x+e),q.x); }
float Band(float x,float lo,float hi,float soft){ float a=smoothstep(lo-soft,lo+soft,x); float b=1.0-smoothstep(hi-soft,hi+soft,x); return clamp(a*b,0.0,1.0); }
float ReceiverMask(vec4 base){ if(uFilter0.x<0.5)return 1.0; vec3 h=RGB2HSV(base.rgb); float hd=abs(h.x-uFilter0.z); hd=min(hd,1.0-hd); float hm=1.0-smoothstep(max(0.0,uFilter0.w-uFilter2.y),uFilter0.w+uFilter2.y,hd); float m=hm*Band(h.y,uFilter1.x,uFilter1.y,uFilter2.y)*Band(h.z,uFilter1.z,uFilter1.w,uFilter2.y)*smoothstep(uFilter2.x-uFilter2.y,uFilter2.x+uFilter2.y,base.a); return (uFilter0.y>0.5)?1.0-m:m; }
void main(){ vec4 base=texture(uColor,vUV); float d=texture(uDepth,vUV).r; if(d>=0.999999){outColor=vec4(0);return;} vec2 materialReceiver=texture(uMaterialReceiver,vUV).rg;
 float receiver=(materialReceiver.g>0.5)?materialReceiver.r:(ReceiverMask(base)*materialReceiver.r); if(receiver<=0.0001){outColor=vec4(0);return;} vec3 p=Pos(vUV); vec3 n=NormalAt(vUV); vec3 incident=normalize(p); vec3 r=normalize(reflect(incident,n)); if(r.z<=0.02){outColor=vec4(0);return;} float maxD=min(uParams1.w,max(50.0,p.z*0.8)); float steps=max(4.0,uParams2.w); float stepD=max(1.0,maxD/steps); vec3 q=p+n*uParams2.z; float found=0.0; vec2 huv=vUV;
 for(int i=0;i<64;i++){ if(float(i)>=steps) break; q+=r*stepD; if(q.z<=uParams0.z||length(q-p)>maxD)break; vec2 uv=Project(q); if(any(lessThanEqual(uv,vec2(.002)))||any(greaterThanEqual(uv,vec2(.998))))break; float sd=texture(uDepth,uv).r; if(sd>=0.999999)continue; float sz=ViewZ(sd); float thickness=max(uParams2.x,q.z*uParams2.y); if(q.z>=sz-thickness && q.z<=sz+thickness*2.0){ huv=uv; found=1.0; break; } }
 if(found>0.0){ vec3 refl=texture(uColor,huv).rgb; float fres=pow(1.0-clamp(abs(dot(normalize(-p),n)),0.0,1.0),3.0); float edge=clamp(min(min(huv.x,1.0-huv.x),min(huv.y,1.0-huv.y))*12.0,0.0,1.0); float facing=clamp(1.0-abs(n.z)*0.45,0.25,1.0); float w=(0.18+0.82*fres)*edge*facing*receiver; outColor=vec4(refl,clamp(w,0.0,1.0)); return; }
 outColor=vec4(0); }
