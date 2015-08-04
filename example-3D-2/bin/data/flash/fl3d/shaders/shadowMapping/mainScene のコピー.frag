#version 120

//テクスチャ
uniform sampler2D u_colorTexture;
//シャドウマップ
uniform sampler2D u_shadowMap;

//--------------------------------------
//ライト
uniform vec3 u_lightPosition;
//ライトの強さ
uniform float u_intensity;

//影の濃さ
uniform float u_shadowDarkness;

uniform mat4 u_shadowMatrix;

varying vec4 v_vertInLightSpace;

uniform float u_linearDepthConstant;
//--------------------------------------

//--------------------------------------
varying vec3 v_vertex;
varying vec3 v_normal;
varying vec2 v_texCoord;
//!< シャドウデプスマップの参照用座標
varying vec4 v_shadowCoord;
//--------------------------------------

//varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
    vec4 textureColor = texture2D(u_colorTexture, v_texCoord.st);
    vec4 shadowMapColor = texture2D(u_shadowMap, v_texCoord.st);
    
    vec4 compositeColor = vec4(1.0, 1.0, 1.0, 1.0);
//    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 0.0);
//    compositeColor = textureColor;
    
    //--------------------------------------
    //環境反射成分
    vec4 ambient = gl_FrontMaterial.ambient;
    //拡散反射成分
    vec4 diffuse = gl_FrontMaterial.diffuse;
    //鏡面反射成分
    vec4 specular = gl_FrontMaterial.specular;
    //--------------------------------------
    compositeColor = diffuse;

    //--------------------------------------
    //▼深度の計算
    
    //光源座標
    vec3 depth = v_vertInLightSpace.xyz / v_vertInLightSpace.w;
    
    // 光源からのデプス値(視点)
    float view_d = depth.z;
    
    vec4 shadowColor = vec4(0.0);
    
    float shadow = 1.0;
//    if (depth.z > 0.0) {
        //リアルZ値抽出
        float lightDepth = length(v_vertex.xyz - u_lightPosition) * u_linearDepthConstant;
        //格納された光源からの最小デプス値を取得
        //ライト目線によるZ値
        float light_d = texture2D(u_shadowMap, depth.xy).z;
        if(light_d > lightDepth + 0.005f) {
            compositeColor *= 0.5;
//            if(lightDepth < texel) {
//                shadow = 0.0;
//            }
//            shadow = clamp(exp(-10.0 * (lightDepth - texel)), 0.0, 1.0);
//            shadowColor = vec4((diffuse * (1 - shadow)));
            //shadowColor = vec4(0.0, 0.0, 1.0, 0.0);
//            shadowColor = vec4(0.5, 0.5, 0.5, 1.0);
        }
//    }
    //--------------------------------------
//    compositeColor = textureColor;
//    compositeColor = shadowMapColor;
    
//    compositeColor *= shadow;
//    compositeColor -= shadowColor;
	gl_FragColor = vec4(compositeColor.rgb, 1.0);
}
