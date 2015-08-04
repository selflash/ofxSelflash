#version 120

varying vec4 v_position;

//--------------------------------------------------------------
//
void main(void){
    v_position = gl_ModelViewMatrix * gl_Vertex;
    gl_Position = ftransform();
}