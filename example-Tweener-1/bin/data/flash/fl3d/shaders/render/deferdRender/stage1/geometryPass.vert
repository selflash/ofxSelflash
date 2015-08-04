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
varying vec4 v_vertInViewSpace;
//深度
varying float v_depth;
//視点座標系での法線
varying vec3 v_normal;
//UV値
varying vec2 v_texCoord;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    //--------------------------------------
    //視点座標系での頂点位置　※丸め込まれていない生の値
    v_vertInViewSpace = gl_ModelViewMatrix * gl_Vertex;
    //デプス値を-1.0〜1.0に丸める
    v_depth = -v_vertInViewSpace.z / u_farClip;
    //視点座標系での法線
    v_normal = gl_NormalMatrix * gl_Normal;
    //UV値
    v_texCoord = gl_MultiTexCoord0.st;
//    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    //投影変換後のxy座標 (モデルビュー * プロジェクション) * 頂点座標
//    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position = gl_ProjectionMatrix * v_vertInViewSpace;
    //頂点色
    gl_FrontColor = gl_Color;
    //--------------------------------------
    
    //--------------------------------------
    //視点座標系の頂点位置
	vec4 eyeCoord = v_vertInViewSpace;
	float dist = sqrt(eyeCoord.x * eyeCoord.x + eyeCoord.y * eyeCoord.y + eyeCoord.z * eyeCoord.z);
	float att = 600.0 / dist;
	
	gl_PointSize = gl_Normal.x * att;
    //--------------------------------------
}