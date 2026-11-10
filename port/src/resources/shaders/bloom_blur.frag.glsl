#version 460 core
layout(binding=0) uniform sampler2D uBloom;
uniform vec4 uBlur; // invW, invH, dirX, dirY
uniform float uRadius;
in vec2 vUV; out vec4 outColor;
void main(){
    vec2 stepUV=uBlur.xy*uBlur.zw*max(0.5,uRadius);
    vec3 c=texture(uBloom,vUV).rgb*0.227027;
    c+=texture(uBloom,vUV+stepUV*1.384615).rgb*0.316216;
    c+=texture(uBloom,vUV-stepUV*1.384615).rgb*0.316216;
    c+=texture(uBloom,vUV+stepUV*3.230769).rgb*0.070270;
    c+=texture(uBloom,vUV-stepUV*3.230769).rgb*0.070270;
    outColor=vec4(c,1.0);
}
