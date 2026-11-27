#version 460 core
layout(binding=0) uniform sampler2D uScene;
layout(binding=1) uniform sampler2D uPreviousExposure;
uniform vec4 uExposureParams0; // baseline, darkMax, darkThreshold, adaptationAlpha
out vec4 outColor;
float luminance(vec3 c){ return max(dot(c,vec3(0.2126,0.7152,0.0722)),1e-4); }
void main(){
    float logSum=0.0;
    const int N=8;
    for(int y=0;y<N;y++) for(int x=0;x<N;x++){
        vec2 uv=(vec2(x,y)+vec2(0.5))/float(N);
        float lum=luminance(texture(uScene,uv).rgb);
        logSum+=log(lum);
    }
    float avgLum=exp(logSum/float(N*N));
    float baseline=max(uExposureParams0.x,0.0);
    float darkMax=max(uExposureParams0.y,baseline);
    float threshold=max(uExposureParams0.z,1e-4);
    float darkness=clamp((threshold-avgLum)/threshold,0.0,1.0);
    float target=mix(baseline,darkMax,darkness);
    float prev=max(texture(uPreviousExposure,vec2(0.5)).r,1e-4);
    float exposure=mix(prev,target,clamp(uExposureParams0.w,0.0,1.0));
    outColor=vec4(exposure,avgLum,target,1.0);
}
