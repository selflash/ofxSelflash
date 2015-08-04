#version 120

//--------------------------------------
attribute float pointSize;
attribute float	angle;

varying float rotAngle;
//--------------------------------------

//--------------------------------------
//頂点
varying vec3 v_Vertex;
//法線
varying vec3 v_Normal;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    //--------------------------------------------------------------
    //視点座標で光源計算
    vec4 vertexInViewSpace = gl_ModelViewMatrix * gl_Vertex;
    v_Vertex = vertexInViewSpace.xyz;
    //--------------------------------------------------------------
    
    //--------------------------------------------------------------
    rotAngle = angle;

    gl_TexCoord[0] = gl_MultiTexCoord0 * gl_TextureMatrix[0];


    //視点座標系
    vec4 eyeCoord = gl_ModelViewMatrix * gl_Vertex;

    //サイズ
    float pSize = length(eyeCoord);
    //適当に重み付け
    pSize *= 0.001;
    float size = gl_Normal.x;
    gl_PointSize = size/pSize;
    //--------------------------------------------------------------
    
    //法線
    //gl_NormalMatrixをかけ算しないと、光の位置がオブジェクトについてくるように見える
    v_Normal = gl_NormalMatrix * gl_Normal;
    
    //投影変換 (モデルビュー * プロジェクション) * 頂点座標
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //gl_Position = ftransform();
    //頂点色
    gl_FrontColor = gl_Color;
}