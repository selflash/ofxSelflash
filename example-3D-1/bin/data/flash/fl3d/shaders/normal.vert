
//--------------------------------------------------------------
//
void main() {
    gl_FrontColor = gl_Color;

    //テクスチャ座標にテクスチャ変換行列をかける
    gl_TexCoord[0] = gl_MultiTexCoord0 * gl_TextureMatrix[0];

    //固定機能の変換結果をそのまま使う
    gl_Position = ftransform();
}
