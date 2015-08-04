#version 120

//--------------------------------------
//ローカル座標系での頂点位置
varying vec4 v_vertexInModelSpace;
//グローバル座標系での頂点位置
//varying vec4 v_vertexInGlobalSpace;
//視点座標系での頂点位置
varying vec4 v_vertexInViewSpace;
//投影変換後のxy座標
varying vec4 v_vertexInProjectionSpace;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    //--------------------------------------
    //ローカル座標系での頂点位置
    v_vertexInModelSpace = gl_Vertex;
    //グローバル座標系での頂点位置
//    v_vertexInGlobalSpace = gl_ModelMatrix * gl_Vertex;
    //視点座標系での頂点位置　※丸め込まれていない生の値
    v_vertexInViewSpace = gl_ModelViewMatrix * gl_Vertex;
    
    //投影変換後のxy座標 (モデルビュー * プロジェクション) * 頂点座標
    v_vertexInProjectionSpace = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //--------------------------------------
}