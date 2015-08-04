#version 120

//--------------------------------------
//ライトID
uniform int u_Light0ID;
uniform int u_Light1ID;
uniform int u_Light2ID;
uniform int u_Light3ID;
uniform int u_Light4ID;
uniform int u_Light5ID;
uniform int u_Light6ID;
uniform int u_Light7ID;

//光源ベクトル
varying vec3 v_Light0Dir;
varying vec3 v_Light1Dir;
varying vec3 v_Light2Dir;
varying vec3 v_Light3Dir;
varying vec3 v_Light4Dir;
varying vec3 v_Light5Dir;
varying vec3 v_Light6Dir;
varying vec3 v_Light7Dir;

//ライトの有効・無効
uniform int u_Light0Enabled;
uniform int u_Light1Enabled;
uniform int u_Light2Enabled;
uniform int u_Light3Enabled;
uniform int u_Light4Enabled;
uniform int u_Light5Enabled;
uniform int u_Light6Enabled;
uniform int u_Light7Enabled;

//ライトの強さ
uniform float u_Light0Intensity;
uniform float u_Light1Intensity;
uniform float u_Light2Intensity;
uniform float u_Light3Intensity;
uniform float u_Light4Intensity;
uniform float u_Light5Intensity;
uniform float u_Light6Intensity;
uniform float u_Light7Intensity;
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
    vec4 vertInViewSpace = gl_ModelViewMatrix * gl_Vertex;    
    v_Vertex = vertInViewSpace.xyz;
    
    //光線ベクトル
    v_Light0Dir = normalize(gl_LightSource[u_Light0ID].position.xyz - vertInViewSpace.xyz);
    v_Light1Dir = normalize(gl_LightSource[u_Light1ID].position.xyz - vertInViewSpace.xyz);
    v_Light2Dir = normalize(gl_LightSource[u_Light2ID].position.xyz - vertInViewSpace.xyz);
    v_Light3Dir = normalize(gl_LightSource[u_Light3ID].position.xyz - vertInViewSpace.xyz);
    v_Light4Dir = normalize(gl_LightSource[u_Light4ID].position.xyz - vertInViewSpace.xyz);
    v_Light5Dir = normalize(gl_LightSource[u_Light5ID].position.xyz - vertInViewSpace.xyz);
    v_Light6Dir = normalize(gl_LightSource[u_Light6ID].position.xyz - vertInViewSpace.xyz);
    v_Light7Dir = normalize(gl_LightSource[u_Light7ID].position.xyz - vertInViewSpace.xyz);
    //--------------------------------------------------------------
    
    gl_TexCoord[0] = gl_MultiTexCoord0 * gl_TextureMatrix[0];
    
    //法線
    //gl_NormalMatrixをかけ算しないと、光の位置がオブジェクトについてくるように見える
    v_Normal = gl_NormalMatrix * gl_Normal;
    
    //頂点
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //gl_Position = gl_ProjectionMatrix * vertInViewSpace;
    //gl_Position = ftransform();
    
    //頂点色
    gl_FrontColor = gl_Color;
}
