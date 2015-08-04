#version 120

/*
 マテリアルIDの内訳
 <= 0.1 [背景]
 <= 0.2 [透明]
 <= 0.3 [自己発光]
 <= 0.4 [未定]
 <= 0.5 [未定]
 <= 0.6 [未定]
 <= 0.7 [未定]
 <= 0.8 [未定]
 <= 0.9 [未定]
 <= 1.0 [未定]
 */

//--------------------------------------
//各サンプラー
uniform sampler2D u_colorTexture;
uniform sampler2D u_normalTexture;
uniform sampler2D u_materialTypeTexture;
uniform sampler2D u_specularTexture;
uniform sampler2D u_illuminationTexture;
uniform sampler2D u_reflectionTexture;
uniform sampler2D u_displacementTexture;
//--------------------------------------

//--------------------------------------
//カメラ
//位置
uniform vec3 u_cameraPosition;
//ニアークリップ
uniform float u_nearClip;
//ファークリップ
uniform float u_farClip;
//--------------------------------------

//--------------------------------------
//視点座標系での頂点位置
varying vec4 v_vertInViewSpace;
//深度
varying float v_depth;
//視点座標系での法線
varying vec3 v_normal;
//UV値
varying vec2 v_texCoord;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    //----------------------------------
    //1枚目 RGBA(Albedo)
    vec4 diffuse = gl_FrontMaterial.diffuse * gl_Color;
    diffuse.r *= diffuse.a;
    diffuse.g *= diffuse.a;
    diffuse.b *= diffuse.a;
    
    vec4 diffuseData = texture2D(u_colorTexture, v_texCoord.st);
    vec4 albedo = diffuse * diffuseData;
    
    //逆ガンマをかける
    albedo.rgb = pow(albedo.rgb, vec3(2.2));
    gl_FragData[0] = vec4(albedo.rgb, diffuse.a * diffuseData.a);
    //----------------------------------
    
    //----------------------------------
    //3枚目 R(Specular) + G(Illumination) + B(Reflection) + A(MaterialType)
    //マテリアルの種類
    vec4 specularData = texture2D(u_specularTexture, v_texCoord.st);
    vec4 illuminationData = texture2D(u_illuminationTexture, v_texCoord.st);
    vec4 reflectionData = texture2D(u_reflectionTexture, v_texCoord.st);
    vec4 materialTypeData = texture2D(u_materialTypeTexture, v_texCoord.st);
//    vec4 materialType = gl_FrontMaterial.emission;
//    materialType *= materialTypeData;
//    gl_FragData[1] = vec4(materialType.rgb, 0.0);
    vec4 materials = vec4(specularData.r, illuminationData.r, reflectionData.r, materialTypeData.r);
    gl_FragData[2] = materials;
    //----------------------------------
    
    //----------------------------------
    //2枚目 RGB(Normals) + A(Depth 0.001) ※視点座標系
    vec4 normalsData = texture2D(u_normalTexture, v_texCoord.st);
    vec4 displacementData = texture2D(u_displacementTexture, v_texCoord.st);
    vec4 normals = vec4(normalize(v_normal), v_depth);
//    normals.r += (normalsData.r / 255.0);
//    normals.g += (normalsData.g / 255.0);
//    normals.b += (normalsData.b / 255.0);
    normals.r += normalsData.r;
    normals.g += normalsData.g;
    normals.b += normalsData.b;
    
    if(materialTypeData.r <= 0.1) {
//        gl_FragData[1] = vec4(0.0, 0.0, 0.0, v_depth);
        gl_FragData[1] = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        gl_FragData[1] = normals;
    }
    //----------------------------------
    
    //----------------------------------
    //4枚目 RGB(SpecularColor) + A(Shininess)
    vec4 specularColorData = vec4(gl_FrontMaterial.specular.rgb, 1.0);
    float shininess = gl_FrontMaterial.shininess / 128.0;
    if(materialTypeData.r <= 0.3) {
        gl_FragData[3] = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        gl_FragData[3] = vec4(specularColorData.rgb, shininess);
    }
    //----------------------------------

}