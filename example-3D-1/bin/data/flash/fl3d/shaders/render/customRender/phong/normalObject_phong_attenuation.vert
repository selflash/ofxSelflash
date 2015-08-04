#version 120

//--------------------------------------
//ライトID
uniform int u_light0ID;
uniform int u_light1ID;
uniform int u_light2ID;
uniform int u_light3ID;
uniform int u_light4ID;
uniform int u_light5ID;
uniform int u_light6ID;
uniform int u_light7ID;

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
uniform int u_light0Enabled;
uniform int u_light1Enabled;
uniform int u_light2Enabled;
uniform int u_light3Enabled;
uniform int u_light4Enabled;
uniform int u_light5Enabled;
uniform int u_light6Enabled;
uniform int u_light7Enabled;

//ライトの強さ
uniform float u_light0Intensity;
uniform float u_light1Intensity;
uniform float u_light2Intensity;
uniform float u_light3Intensity;
uniform float u_light4Intensity;
uniform float u_light5Intensity;
uniform float u_light6Intensity;
uniform float u_light7Intensity;
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
    v_Light0Dir = normalize(gl_LightSource[u_light0ID].position.xyz - vertInViewSpace.xyz);
    v_Light1Dir = normalize(gl_LightSource[u_light1ID].position.xyz - vertInViewSpace.xyz);
    v_Light2Dir = normalize(gl_LightSource[u_light2ID].position.xyz - vertInViewSpace.xyz);
    v_Light3Dir = normalize(gl_LightSource[u_light3ID].position.xyz - vertInViewSpace.xyz);
    v_Light4Dir = normalize(gl_LightSource[u_light4ID].position.xyz - vertInViewSpace.xyz);
    v_Light5Dir = normalize(gl_LightSource[u_light5ID].position.xyz - vertInViewSpace.xyz);
    v_Light6Dir = normalize(gl_LightSource[u_light6ID].position.xyz - vertInViewSpace.xyz);
    v_Light7Dir = normalize(gl_LightSource[u_light7ID].position.xyz - vertInViewSpace.xyz);
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
