#version 120

//--------------------------------------
//ローカル座標系での法線
varying vec3 v_normalInModelSpace;
//グローバル座標系での法線
//varying vec3 v_normalInGlobalSpace;
//視点座標系での法線
varying vec3 v_normalInViewSpace;
//投影変換後のxy座標
//varying vec4 v_normalInProjectionSpace;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    //--------------------------------------
    //ローカル座標系での法線
    v_normalInModelSpace = gl_Normal;
    //グローバル座標系での法線
//    v_normalInGlobalSpace = gl_ViewMatrix * gl_Vertex;
    //視点座標系での法線　※丸め込まれていない生の値
    v_normalInViewSpace = gl_NormalMatrix * gl_Normal;
    
    //投影変換後のxy座標 (モデルビュー * プロジェクション) * 頂点座標
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //--------------------------------------
}