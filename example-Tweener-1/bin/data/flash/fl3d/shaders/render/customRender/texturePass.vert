#version 120

varying vec3 v_normal;
varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main (void) {
    vec4 viewSpaceVertex = gl_ModelViewMatrix * gl_Vertex;
    v_normal = gl_NormalMatrix * gl_Normal;
    
    v_texCoord = gl_MultiTexCoord0.st;
    
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    //頂点色
    gl_FrontColor = gl_Color;
}