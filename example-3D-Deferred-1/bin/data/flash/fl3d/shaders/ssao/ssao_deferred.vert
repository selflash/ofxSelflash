#version 120

varying vec3 norm;
void main()
{
    norm = normalize(gl_NormalMatrix * gl_Normal);
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
    gl_Position = ftransform();
}