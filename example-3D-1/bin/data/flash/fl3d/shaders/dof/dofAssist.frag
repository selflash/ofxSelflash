#version 120

//#version 110
#extension GL_ARB_texture_rectangle : enable


//Shader for visualizing a depth texture as a focal distance map
//paired with dofblur for debugging purposes

uniform sampler2DRect u_depthTexture;

uniform float u_focalDistance;
uniform float u_focalRange;

float linearizeDepth(float zoverw){
    // camera z near
    float n = 1.0;
    // camera z far
    float f = 100000.0;
    return (2.0 * n) / (f + n - zoverw * (f - n));
}

void main(void){
    float depth = linearizeDepth(texture2DRect(u_depthTexture, gl_TexCoord[0].st).r) * 100000.0;
    gl_FragColor = vec4(min(abs(depth - u_focalDistance) / u_focalRange, 1.0));
    gl_FragColor.a = 1.0;
}