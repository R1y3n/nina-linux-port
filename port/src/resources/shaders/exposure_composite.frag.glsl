#version 460 core
layout(binding=0) uniform sampler2D uScene;
layout(binding=1) uniform sampler2D uBloom;
layout(binding=2) uniform sampler2D uExposure;
uniform vec4 uCompositeParams; // bloomIntensity, dynamicExposureEnabled, unused, unused
in vec2 vUV; out vec4 outColor;
void main(){
    vec4 src=texture(uScene,vUV);
    float exposure=1.0;
    if(uCompositeParams.y>0.5)
        exposure=max(texture(uExposure,vec2(0.5)).r,0.0);
    vec3 c=src.rgb*exposure;
    c+=texture(uBloom,vUV).rgb*uCompositeParams.x;
    outColor=vec4(clamp(c,0.0,1.0),src.a);
}
