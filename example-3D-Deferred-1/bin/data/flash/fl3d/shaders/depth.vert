#version 120
//#extension GL_ARB_texture_rectangle : enable

//UV値
varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
    //UV値
    v_texCoord = gl_MultiTexCoord0.st;
    //固定機能の変換結果をそのまま使う
	gl_Position = ftransform();
}
