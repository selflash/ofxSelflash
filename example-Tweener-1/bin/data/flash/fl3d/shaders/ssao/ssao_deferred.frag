#version 120

uniform sampler2DRect tex;

varying vec3 norm;
void main(void)
{
    gl_FragData[0] = texture2DRect( tex, gl_TexCoord[0].st) * gl_Color;
    gl_FragData[1] = vec4( norm, 1.0 ) ;
}