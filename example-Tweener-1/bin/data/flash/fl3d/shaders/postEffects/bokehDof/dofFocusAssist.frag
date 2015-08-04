#version 120
#extension GL_ARB_texture_rectangle : enable

//Shader for visualizing a depth texture as a focal distance map
//paired with dofblur for debugging purposes

uniform sampler2DRect depthTex;
uniform float u_focalLength;
uniform float u_focalDepth;

//ニアークリップ
uniform float u_nearClip = 1.0;
//ファークリップ
uniform float u_farClip = 20000.0;


float linearize(float depth) {
    float diff = u_farClip - u_nearClip;
    return -u_farClip * u_nearClip / (depth * diff - u_farClip);
    
//    float near = u_nearClip; // camera z near
//    float far = u_farClip; // camera z far
    //    return (2.0 * n) / (f + n - zoverw * (f - n));
    
//    float diff = u_farClip - u_nearClip;
//    return (2.0 * near) / (far + near - depth * diff);
    
//    float n = 1.0; // camera z near
//    float f = 20000.0; // camera z far
//    return (2.0 * n) / (f + n - depth * (f - n));
}

void main() {
    float depth = linearize(texture2DRect(depthTex, gl_TexCoord[0].st).r) * 20000.;
    gl_FragColor = vec4(min( abs(depth  - u_focalLength) / u_focalDepth, 1.0) );
    gl_FragColor.a = 1.0;
}