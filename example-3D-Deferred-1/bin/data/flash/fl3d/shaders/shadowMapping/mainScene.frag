#version 120

//シャドウマップ
uniform sampler2D u_shadowMap;

uniform float u_linearDepthConstant;

//--------------------------------------
//ライト
uniform vec3 u_lightPosition;
//影の濃さ
//uniform float u_shadowDarkness;
uniform mat4 u_shadowMatrix;
//--------------------------------------

varying vec3 v_vertex;
varying vec4 v_vertInLightSpace;

//--------------------------------------------------------------
//
void main(void) {
    //光源座標
    vec3 shadowCoord = v_vertInLightSpace.xyz / v_vertInLightSpace.w;
    
    float shadowCoefficient = 1.0;
    if (shadowCoord.z > 0.0) {
        //光源からの深度値(カメラ視点)
        float lightDepth_camera = length(v_vertex.xyz - u_lightPosition) * u_linearDepthConstant;
        
        // shadow coeffecient - change this to to affect shadow darkness / fade
        float shadowDarkness = 10.0;
        //光源からの深度値(光源視点)
        float lightDepth_light = texture2D(u_shadowMap, shadowCoord.xy).r;
        
        //影と日向の判定(1マッハバンド帽子の為に-0.005する)
        if(lightDepth_light < lightDepth_camera - 0.005) shadowCoefficient = 0.5;
//        shadowCoefficient = clamp(exp(-shadowDarkness * (lightDepth_camera - lightDepth_light)), 0.0, 1.0);
    }
    
    vec4 finalColor = vec4(1.0) * shadowCoefficient;
    finalColor.a = 1.0;
	gl_FragColor = finalColor;
}
