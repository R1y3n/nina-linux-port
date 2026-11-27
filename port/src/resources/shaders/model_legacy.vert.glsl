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
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aUV;
layout(location=3) in vec4 aColor;

uniform vec4 uModelEnvParams; // x=EnvScale, y=panU, z=panV

out vec2 vUV;
out vec3 vCamPos;
out vec3 vEnvNormal;
out vec2 vEnvUV;
out vec4 vColor;
out float vFogZ;

void main()
{
    // Talon camera space is +Z forward. Preserve signed Z and let
    // homogeneous clipping reject vertices/triangles behind the camera.
    float z = aCameraPos.z;
    float A = (uFarZ + uNearZ) / (uFarZ - uNearZ);
    float B = (-2.0 * uFarZ * uNearZ) / (uFarZ - uNearZ);

    gl_Position = vec4(
        aCameraPos.x / uTanHalfFovX,
        aCameraPos.y / uTanHalfFovY,
        A * z + B,
        z);

    vUV = aUV;
    vCamPos = aCameraPos;
    vEnvNormal = normalize(aNormal);
    float envHalf=0.5*uModelEnvParams.x;
    vEnvUV=vec2(0.5+vEnvNormal.x*envHalf+uModelEnvParams.y,
                0.5-vEnvNormal.y*envHalf+uModelEnvParams.z);

    vColor = aColor;
    // Same D3DFOG_LINEAR table-fog coordinate as the GPU model path.
    vFogZ = max(aCameraPos.z, 0.0);
}
