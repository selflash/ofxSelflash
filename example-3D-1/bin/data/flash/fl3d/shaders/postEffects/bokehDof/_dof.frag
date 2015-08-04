#version 120

uniform sampler2D u_renderedMap;
uniform sampler2D u_normalAndDepthMap;

//--------------------------------------
//カメラ
//位置
uniform vec3 u_cameraPosition;
//ニアークリップ
uniform float u_nearClip = 0.1;
//ファークリップ
uniform float u_farClip = 10000000.0;
//焦点距離
uniform float u_focalDistance;
//focal length in mm
uniform float u_focalLength;
//f-stop value
uniform float u_fstop;
// autofocus point on screen (0.0,0.0 - left lower corner, 1.0,1.0 - upper right)
uniform vec2 u_focus = vec2(0.5, 0.5);
//--------------------------------------

uniform float u_maxBlur = 1.0;
uniform float u_aperture = 1.0;

//uniform float u_textureWidth;
//uniform float u_textureHeight;
uniform float u_aspect = 1920.0 / 1080.0;

//--------------------------------------
varying vec2 v_texCoord;
//--------------------------------------

//--------------------------------------------------------------
//
void main() {
    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    vec2 aspectcorrect = vec2(1.0, u_aspect);
    
    float depthInViewSpace = texture2D(u_normalAndDepthMap, v_texCoord).a;
    depthInViewSpace *= u_farClip;
    
    float factor = depthInViewSpace - u_focalDistance;
    factor /= u_farClip;
    
    vec2 dofblur = vec2 (clamp(factor * u_aperture, -u_maxBlur, u_maxBlur));
    
    vec2 dofblur9 = dofblur * 0.9;
    vec2 dofblur7 = dofblur * 0.7;
    vec2 dofblur4 = dofblur * 0.4;
    
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.0,   0.4 ) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.15,  0.37) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.29,  0.29) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.37,  0.15) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.40,  0.0 ) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.37, -0.15) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.29, -0.29) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.15, -0.37) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.0,  -0.4 ) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.15,  0.37) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.29,  0.29) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.37,  0.15) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.4,   0.0 ) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.37, -0.15) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.29, -0.29) * aspectcorrect) * dofblur);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.15, -0.37) * aspectcorrect) * dofblur);
    
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.15,  0.37) * aspectcorrect) * dofblur9);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.37,  0.15) * aspectcorrect) * dofblur9);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.37, -0.15) * aspectcorrect) * dofblur9);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.15, -0.37) * aspectcorrect) * dofblur9);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.15,  0.37) * aspectcorrect) * dofblur9);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.37,  0.15) * aspectcorrect) * dofblur9);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.37, -0.15) * aspectcorrect) * dofblur9);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.15, -0.37) * aspectcorrect) * dofblur9);
    
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.29,  0.29) * aspectcorrect) * dofblur7);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.40,  0.0 ) * aspectcorrect) * dofblur7);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.29, -0.29) * aspectcorrect) * dofblur7);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.0,  -0.4 ) * aspectcorrect) * dofblur7);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.29,  0.29) * aspectcorrect) * dofblur7);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.4,   0.0 ) * aspectcorrect) * dofblur7);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.29, -0.29) * aspectcorrect) * dofblur7);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.0,   0.4 ) * aspectcorrect) * dofblur7);
    
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.29,  0.29) * aspectcorrect) * dofblur4);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.4,   0.0 ) * aspectcorrect) * dofblur4);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.29, -0.29) * aspectcorrect) * dofblur4);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.0,  -0.4 ) * aspectcorrect) * dofblur4);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.29,  0.29) * aspectcorrect) * dofblur4);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.4,   0.0 ) * aspectcorrect) * dofblur4);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2(-0.29, -0.29) * aspectcorrect) * dofblur4);
    compositeColor += texture2D(u_renderedMap, v_texCoord.xy + (vec2( 0.0,   0.4 ) * aspectcorrect) * dofblur4);
    
    gl_FragColor = compositeColor / 41.0;
    gl_FragColor.a = 1.0;
}