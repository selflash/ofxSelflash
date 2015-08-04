#version 120

//--------------------------------------
//アルベドマップ
uniform sampler2D u_albedoMap;
//マテリアルタイプマップ
uniform sampler2D u_materialTypeMap;
//ノーマル&デプスマップ
uniform sampler2D u_normalAndDepthMap;
//レンダリング済マップ
uniform sampler2D u_renderedMap;
//ブルームマップ
uniform sampler2D u_bloomMap;
//--------------------------------------

//--------------------------------------
//経過時間
uniform float u_time = 0;
//--------------------------------------

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
//------------------------------------------

//--------------------------------------
//クロマティックアベレーション(色収差)
uniform vec2 u_chromCenter = vec2(0.5, 0.5);
uniform vec2 u_chromRadius = vec2(0.15, 0.95);
uniform float u_chromIntensity = 0.01;
//--------------------------------------

//--------------------------------------
//HDR
//露出
uniform float u_exposure = 0.5;
//--------------------------------------

//--------------------------------------
//ノイズ
uniform float u_noiseStrength = 0.1;
//--------------------------------------

//--------------------------------------
//ビネット(周辺減光)
uniform vec2 u_vignetteCenter = vec2(0.5, 0.5);
uniform vec2 u_vignetteRadius = vec2(0.15, 0.95);
//--------------------------------------

//--------------------------------------
varying vec2 v_texCoord;
//--------------------------------------

//--------------------------------------------------------------
//
float rand(vec2 co) {
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

//--------------------------------------------------------------
//
void main(void) {
    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    //--------------------------------------
    //クロマティックアベレーション(色収差)
    float dist = distance(v_texCoord.st, u_chromCenter);
    float val = u_chromIntensity * smoothstep(u_chromRadius.x, u_chromRadius.y, dist);
    
    //Rチャンネル用のテクスチャ座標
    vec2 toR = vec2(v_texCoord.x + val, v_texCoord.y + val);
    vec4 red = vec4(0.0, 0.0, 0.0, 0.0);
    red += texture2D(u_renderedMap, toR).r;
    red += texture2D(u_bloomMap, toR).r;
    
    //Gチャンネル用のテクスチャ座標
    vec2 toG = vec2(v_texCoord.x, v_texCoord.y);
    vec4 green = vec4(0.0, 0.0, 0.0, 0.0);
    green += texture2D(u_renderedMap, toG).g;
    green += texture2D(u_bloomMap, toG).g;
    
    //Bチャンネル用のテクスチャ座標
    vec2 toB = vec2(v_texCoord.x - val, v_texCoord.y - val);
    vec4 blue = vec4(0.0, 0.0, 0.0, 0.0);
    blue += texture2D(u_renderedMap, toB).b;
    blue += texture2D(u_bloomMap, toB).b;
    
    //３つのカラーのRGBをそれぞれ一色ずつ入れる
    compositeColor += vec4(red.r , green.g, blue.b, 1.0);
    //--------------------------------------
    
    //--------------------------------------
    //HDR
    //露出
	compositeColor.rgb = 1.0 - pow(vec3(2.71), -(compositeColor.rgb * u_exposure));
    //ガンマ補正
    compositeColor.rgb = pow(compositeColor.rgb, vec3(1.0 / 2.2));
    //--------------------------------------

    //--------------------------------------
    //ノイズ
    compositeColor.rgb *= 1.0 + (rand(gl_FragCoord.xy + u_time) - 0.5) * u_noiseStrength;
    //--------------------------------------
    
    //--------------------------------------
    //ビネット(周辺減光)
    compositeColor.rgb *= smoothstep(u_vignetteRadius.y, u_vignetteRadius.x, distance(v_texCoord.st, u_vignetteCenter));
//    compositeColor.rgb += 1.0 - smoothstep(u_vignetteRadius.y, u_vignetteRadius.x, distance(v_texCoord.st, u_vignetteCenter));
    //--------------------------------------
    
    //--------------------------------------
//    if(gl_FragCoord.y & 1.0) compositeColor.rgb *= 1.0 + (rand(gl_FragCoord.xy + u_time) - 0.5) * u_noiseStrength;
    //--------------------------------------

    vec4 finalColor = vec4(compositeColor.rgb, 1.0);
    gl_FragData[0] = finalColor;
}
