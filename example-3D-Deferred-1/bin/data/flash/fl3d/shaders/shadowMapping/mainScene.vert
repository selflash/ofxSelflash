#version 120

//ライト
uniform vec3 u_lightPosition;
//影の濃さ
//uniform float u_shadowDarkness;
uniform mat4 u_shadowMatrix;

varying vec3 v_vertex;
varying vec4 v_vertInLightSpace;

//--------------------------------------------------------------
//
void main(void){
    vec4 vertInViewSpace = gl_ModelViewMatrix * gl_Vertex;
    
    //頂点位置
    v_vertex = vertInViewSpace.xyz;

    v_vertInLightSpace = u_shadowMatrix * vertInViewSpace;
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
