#version 120
#extension GL_ARB_texture_rectangle : enable

//--------------------------------------
varying vec2 v_texCoord;
//--------------------------------------

//--------------------------------------------------------------
//
void main() {
    gl_FrontColor = gl_Color;

    //テクスチャ座標にテクスチャ変換行列をかける
    gl_TexCoord[0] = gl_MultiTexCoord0 * gl_TextureMatrix[0];

    v_texCoord = vec4(gl_MultiTexCoord0 * gl_TextureMatrix[0]).st;
//    v_texCoord = gl_MultiTexCoord0.st;
    
    //固定機能の変換結果をそのまま使う
    gl_Position = ftransform();
}
