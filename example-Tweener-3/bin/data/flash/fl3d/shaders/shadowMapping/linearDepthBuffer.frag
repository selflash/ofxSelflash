#version 120

uniform float u_linearDepthConstant;
varying vec4 v_position;

//--------------------------------------------------------------
//
void main(){
    //    float linearDepth = length(v_position) * 0.0001;
    float linearDepth = length(v_position) * u_linearDepthConstant;
//    float linearDepth = length(v_position);
    gl_FragColor.r = linearDepth;
}
