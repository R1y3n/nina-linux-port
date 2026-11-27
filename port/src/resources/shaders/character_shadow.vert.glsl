#version 460 core
layout(location=0) in vec3 aCameraPos;
layout(location=1) in vec2 aUV;
uniform float uTanHalfFovX;
uniform float uTanHalfFovY;
uniform float uNearZ;
uniform float uFarZ;
out vec2 vUV;
out float vFogZ;
void main()
{
    float z=aCameraPos.z;
    float A=(uFarZ+uNearZ)/(uFarZ-uNearZ);
    float B=(-2.0*uFarZ*uNearZ)/(uFarZ-uNearZ);
    gl_Position=vec4(aCameraPos.x/uTanHalfFovX,aCameraPos.y/uTanHalfFovY,A*z+B,z);
    vUV=aUV;
    vFogZ=max(z,0.0);
}
