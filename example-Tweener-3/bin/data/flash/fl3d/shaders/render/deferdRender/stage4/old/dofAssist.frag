#version 120

//#version 110
#extension GL_ARB_texture_rectangle : enable


//Shader for visualizing a depth texture as a focal distance map
//paired with dofblur for debugging purposes

uniform sampler2D u_depthTexture;

//--------------------------------------
//カメラ
//位置
uniform vec3 u_cameraPosition;
//ニアークリップ
uniform float u_nearClip;
//ファークリップ
uniform float u_farClip;
//--------------------------------------

uniform float u_focalDistance;
uniform float u_focalRange;

varying vec2 v_texCoord;

float linearizeDepth(float zoverw){
    // camera z near
    float n = 1.0;
    // camera z far
    float f = 100000.0;
    return (2.0 * n) / (f + n - zoverw * (f - n));
}

void main(void){
    //-1.0〜1.0
    float depth = texture2D(u_depthTexture, v_texCoord.st).a;
    //実際のデプス値に戻す
    depth = depth * u_farClip;
//    depth = (depth - u_cameraPosition.z) / u_farClip;
//    depth *= 1000.0;
    
//    float depth = linearizeDepth(texture2D(u_depthTexture, gl_TexCoord[0].st).a * 1.0) * 100000.0;
//    float depth = texture2D(u_depthTexture, gl_TexCoord[0].st).a * 10000000.0;
    gl_FragColor = vec4(min(abs(depth - u_focalDistance) / u_focalRange, 1.0));
    gl_FragColor.a = 1.0;
    
//    depth = texture2D(u_depthTexture, gl_TexCoord[0].st).a * 1000.0;
//    gl_FragColor = vec4(depth, depth, depth, 1.0);
//    gl_FragColor = vec4(texture2D(u_depthTexture, gl_TexCoord[0].st).rgb, 1.0);
}