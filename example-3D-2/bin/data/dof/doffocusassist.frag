#version 110
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect u_depthMap;
uniform float focalDistance;
uniform float focalRange;

float nearClip = 1.0;
float farClip = 20000.0;

float LinearizeDepth(float rawDepth){
//    return (2.0 * nearClip) / (farClip + nearClip - zoverw * (farClip - nearClip)) * farClip;
    
    float diff = farClip - nearClip;
    return nearClip / (farClip + nearClip - rawDepth * diff) * farClip;
}

void main() {
    float depth = LinearizeDepth(texture2DRect(u_depthMap, gl_TexCoord[0].st).r) / focalRange;
//    float depth = (texture2DRect(u_depthMap, gl_TexCoord[0].st).r + 700.0) / 1000.0;
    gl_FragColor = vec4(depth);
    gl_FragColor.a = 1.0;
}