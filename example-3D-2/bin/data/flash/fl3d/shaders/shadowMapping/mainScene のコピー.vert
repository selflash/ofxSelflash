#version 120

//ライトの強さ
uniform float u_intensity;
//影の濃さ
uniform float u_shadowDarkness;
uniform mat4 u_shadowMatrix;
varying vec4 v_vertInLightSpace;

varying vec3 v_vertex;
varying vec3 v_normal;
varying vec2 v_texCoord;
//!< シャドウデプスマップの参照用座標
varying vec4 v_shadowCoord;

//--------------------------------------------------------------
//
void main(void){
    //フラグメントシェーダでの計算用(モデルビュー変換のみ)
    //頂点位置
    v_vertex = gl_ModelViewMatrix * gl_Vertex;
    //頂点法線
    v_normal = normalize(gl_NormalMatrix * gl_Normal);
    //影用座標値(光源中心座標)
    v_shadowCoord = gl_TextureMatrix[10] * gl_ModelViewMatrix * gl_Vertex;
    
    //描画用
    //頂点位置
    gl_Position = gl_ProjectionMatrix * v_vertex;
    //頂点色
    gl_FrontColor = gl_Color;
    //頂点テクスチャ座標
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    
//    vec4 vertInViewSpace = gl_ModelViewMatrix * gl_Vertex;
//
//    v_vertex = vertInViewSpace.xyz;
//    v_normal = gl_NormalMatrix * gl_Normal;
//    
//    v_texCoord = gl_MultiTexCoord0.st;
//
//    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//
//    v_vertInLightSpace = u_shadowMatrix * vertInViewSpace;
}
