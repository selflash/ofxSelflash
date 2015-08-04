#version 120
#extension GL_ARB_texture_rectangle : enable

//--------------------------------------
varying vec2 v_texCoord;
//--------------------------------------

void main(void) {
    gl_FrontColor = gl_Color;
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
    v_texCoord = gl_MultiTexCoord0.st;
}
