#version 120

//#version 110
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect u_depthTexture;

uniform float u_focalDistance;
uniform float u_focalRange;

//uniform float u_focalNear = 1.0;
//uniform float u_focalLength = 10000.0;

//UV値
varying vec2 v_texCoord;

//--------------------------------------------------------------
//
float linearizeDepth(float zoverw) {
    // camera z near
    float n = 0.1;
    // camera z far
//    float f = 10000000.0;
//    float f = u_cameraFarClip;
    float f = 100000.0;
    return (2.0 * n) / (f + n - zoverw * (f - n));
}

//--------------------------------------------------------------
//
void main(void) {
////    float depth = 1.0 - linearizeDepth(texture2D(u_depth, v_texCoord).r) * 10000000.0;
//    float depth = 1.0 - linearizeDepth(texture2D(u_depth, v_texCoord).r) * u_cameraFarClip;
//    gl_FragColor = vec4(min(abs(depth - u_focalNear) / u_focalLength, 1.0));
//    
////    vec4 depthMap = texture2D(u_depthMap, v_texCoord);
////    
////    gl_FragColor *= depthMap;
////    gl_FragColor.a = 1.0;
    
    float depth = linearizeDepth(texture2DRect(u_depthTexture, v_texCoord.st).r) * 100000.0;
    gl_FragColor = vec4(min(abs(depth - u_focalDistance) / u_focalRange, 1.0));
    gl_FragColor.a = 1.0;
    
}