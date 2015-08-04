#version 120

uniform sampler2D u_textuer0;
uniform sampler2D u_textuer1;
uniform sampler2D u_textuer2;
uniform sampler2D u_textuer3;
uniform sampler2D u_textuer4;
uniform sampler2D u_textuer5;
uniform sampler2D u_textuer6;

varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
    //テクスチャ0
    vec4 texture0 = texture2D(u_textuer0, v_texCoord.st);
    //テクスチャ1
    vec4 texture1 = texture2D(u_textuer1, v_texCoord.st);
    //テクスチャ2
    vec4 texture2 = texture2D(u_textuer2, v_texCoord.st);
    //テクスチャ3
    vec4 texture3 = texture2D(u_textuer3, v_texCoord.st);
    //テクスチャ4
    vec4 texture4 = texture2D(u_textuer4, v_texCoord.st);
    //テクスチャ5
    vec4 texture5 = texture2D(u_textuer5, v_texCoord.st);
    //テクスチャ6
    vec4 texture6 = texture2D(u_textuer6, v_texCoord.st);

    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 0.0);
//    compositeColor += texture0;
    compositeColor += texture1;
//    compositeColor += texture2;
//    compositeColor += texture3;
//    compositeColor += texture4;
//    compositeColor += texture5;
//    compositeColor += texture6;
    
    vec4 finalColor = vec4(compositeColor.rgb, 1.0);
    gl_FragColor = finalColor;
}
