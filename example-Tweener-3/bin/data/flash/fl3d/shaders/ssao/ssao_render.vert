#version 120

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
    gl_Position.y *= -1.;
}