#version 460 core
layout(std140,binding=12) uniform FramePassConstants {
    vec4 frameProjection;      // tanHalfX, tanHalfY, nearZ, farZ
    vec4 frameCameraPos;       // xyz
    vec4 frameCameraQuat;      // xyzw
    vec4 frameFogColorEnabled; // rgb, enabled
    vec4 frameFogParams;       // near, far, frameTime, unused
};
#define uTanHalfFovX frameProjection.x
#define uTanHalfFovY frameProjection.y
#define uNearZ frameProjection.z
#define uFarZ frameProjection.w
layout(location=0) in vec3 aCameraPos;
layout(location=1) in vec2 aUV;
layout(location=2) in vec4 aColor;


out vec2 vUV;
out vec4 vColor;
out float vFogZ;

void main()
{
    float z = aCameraPos.z;
    float A = (uFarZ + uNearZ) / (uFarZ - uNearZ);
    float B = (-2.0 * uFarZ * uNearZ) / (uFarZ - uNearZ);

    gl_Position = vec4(
        aCameraPos.x / uTanHalfFovX,
        aCameraPos.y / uTanHalfFovY,
        A * z + B,
        z);

    vUV = aUV;
    vColor = aColor;
    vFogZ = max(aCameraPos.z, 0.0);
}
