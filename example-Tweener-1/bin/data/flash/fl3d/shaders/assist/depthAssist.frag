#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect u_renderdMap;
uniform sampler2DRect u_depthMap;

//ニアークリップ
uniform float u_nearClip = 1.0;
//ファークリップ
uniform float u_farClip = 1000.0;

//UV値
varying vec2 v_texCoord;

//--------------------------------------------------------------
//
float linearize(float rawDepth) {
    
    float diff = u_farClip - u_nearClip;
//    return nearClip / (farClip + nearClip - rawDepth * diff) * farClip;
    return (2.0 * u_nearClip) / (u_farClip + u_nearClip - rawDepth * diff);
}

//--------------------------------------------------------------
//
void main() {
    float depth = linearize(texture2DRect(u_depthMap, v_texCoord.st).r);
    gl_FragColor = vec4(depth);
    gl_FragColor.a = 1.0;
}