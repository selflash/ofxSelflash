#version 120

/*
 マテリアルIDの内訳
 <= 0.1 [背景]
 <= 0.2 [透明]
 <= 0.3 [自己発光]
 <= 0.4 [未定]
 <= 0.5 [未定]
 <= 0.6 [未定]
 <= 0.7 [未定]
 <= 0.8 [未定]
 <= 0.9 [未定]
 <= 1.0 [未定]
 */

//--------------------------------------
//各サンプラー
//アルベドマップ
uniform sampler2D u_albedoMap;
//マテリアルタイプマップ
uniform sampler2D u_materialTypeMap;
//ノーマル&デプスマップ
uniform sampler2D u_normalAndDepthMap;
//ライティングマップ
uniform sampler2D u_lightingMap;
//--------------------------------------

//--------------------------------------
//グローバルアンビエントカラー
uniform vec4 u_globalAmbientColor = vec4(1.0, 1.0, 1.0, 1.0);
//--------------------------------------

//--------------------------------------
varying vec2 v_texCoord;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    //--------------------------------------
    //アルベド
    vec4 albedo = texture2D(u_albedoMap, v_texCoord.st);
    //マテリアルズ
    vec4 materialType = texture2D(u_materialTypeMap, v_texCoord.st);
    //法線+深度
    vec4 normalAndDepth = texture2D(u_normalAndDepthMap, v_texCoord.st);
    //ライティング
    vec4 lighting = texture2D(u_lightingMap, v_texCoord.st);
    //--------------------------------------
    
    //--------------------------------------
    //通常
    compositeColor += u_globalAmbientColor;
    compositeColor += lighting;
    compositeColor *= albedo;
    if(materialType.a <= 0.3) compositeColor = albedo; //ライティングに影響されない(ブルームの為)
//    if(materialType.a <= 0.1) compositeColor = albedo; //ライティングに影響されない
    
    gl_FragData[0] = vec4(compositeColor.rgb, 1.0);
    //--------------------------------------
    
    //--------------------------------------
    //ブルーム
    vec4 bloomColor = vec4(0.0);
    if(materialType.g >= 0.1) {
        float luminance = 0.0;
        float r = compositeColor.r;
        float g = compositeColor.g;
        float b = compositeColor.b;
        luminance = r + g + b;
//        luminance = luminance / 255.0;
        if(luminance < 1.5) {
//
        } else {
            bloomColor = compositeColor;
            bloomColor *= materialType.g * 1.0;
        }
    }
//    if(materialType.a <= 0.2) bloomColor = vec4(0.0);
    vec4 bloom = vec4(bloomColor.rgb, 1.0);
    gl_FragData[1] = bloom;
    //--------------------------------------
}
