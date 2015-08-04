#version 120

uniform sampler2D texture;
//uniform sampler2D bumpTexture;

varying vec3 v_normal;
varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
    //albedo
    vec4 textureColor = texture2D(texture, v_texCoord.st);
    //vec4 diffuse = gl_FrontMaterial.diffuse;
    //gl_FragData[0] = diffuse * textureColor;
    //gl_FragData[0] = vec4(textureColor.rgb, 0.1);
    gl_FragData[0] = vec4(0.0);
    if(textureColor.a > 0) gl_FragData[0] = textureColor.rgba;
    
//    //normals + depth
//    gl_FragData[1] = vec4(normalize(v_normal), v_depth);
//    
//    //specular
//    vec4 specular = gl_FrontMaterial.specular;
//    //shininess
//    float shininess = gl_FrontMaterial.shininess / 128.0;
//    gl_FragData[2] = vec4(specular.rgb, shininess);
}