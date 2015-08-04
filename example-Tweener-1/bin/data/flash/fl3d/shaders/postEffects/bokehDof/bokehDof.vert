#version 120

//--------------------------------------
varying vec2 v_texCoord;
//--------------------------------------

//--------------------------------------------------------------
//
void main() {
    //テクスチャ座標にテクスチャ変換行列をかける
    gl_TexCoord[0] = gl_MultiTexCoord0 * gl_TextureMatrix[0];
//    v_texCoord = vec4(gl_MultiTexCoord0 * gl_TextureMatrix[0]).st;
    v_texCoord = gl_MultiTexCoord0.st;
    
    gl_FrontColor = gl_Color;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
