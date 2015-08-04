#version 120

//--------------------------------------
uniform sampler2D tex;
varying float rotAngle;
//--------------------------------------

//--------------------------------------
//頂点
varying vec3 v_Vertex;
//法線
varying vec3 v_Normal;
//--------------------------------------

vec4 textureColor;

//--------------------------------------------------------------
// MAIN
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    //--------------------------------------
    //テクスチャの回転なし
//    textureColor = texture2D(tex, gl_TexCoord[0].st);
    
    //テクスチャの回転
    float angle = rotAngle;
    vec2 offset = vec2(0.5, 0.5);
    vec2 v2 = gl_TexCoord[0].st;
    
    //回転マトリックスの生成
    float sinX = sin(angle);
    float cosX = cos(angle);
    float sinY = sin(angle);
    float cosY = cos(angle);
    mat2 rotationMatrix = mat2(cosX, -sinX, sinY, cosX);
    
    //中心から半分ズラして回転マトリックスを加味して中心に戻す
    vec2 newcoords = ((v2-offset) * (rotationMatrix));
    newcoords += offset;
    
    textureColor = texture2D(tex, newcoords) * gl_Color;
//    textureColor = texture2D(tex, newcoords);
//    compositeColor *= textureColor;
    compositeColor = textureColor;
    //--------------------------------------
    
//    gl_FragColor = vec4(v_Vertex.xyz * textureColor.a, textureColor.a);
//    gl_FragColor = textureColor;
    gl_FragColor = compositeColor;
}