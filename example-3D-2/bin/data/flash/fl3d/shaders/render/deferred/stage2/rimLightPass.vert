#version 120

//--------------------------------------
//カメラ
//位置
uniform vec3 u_cameraPosition;
//ニアークリップ
uniform float u_nearClip;
//ファークリップ
uniform float u_farClip;
//--------------------------------------

//--------------------------------------
//視点座標系での頂点位置
varying vec4 v_vertexInViewSpace;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    //視点座標系での頂点位置　※丸め込まれていない生の値
    v_vertexInViewSpace = gl_ModelViewMatrix * gl_Vertex;
    
    //スクリーン上での位置(-1.0〜1.0)
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
