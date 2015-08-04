/**
 
 @see 
 [GLSL Ver1.5　メモ]
 http://blog-imgs-35.fc2.com/b/l/u/bluvclub/20091231234604e0c.html
 
 @see
 [GLSLによるグーローとフォーンシェーディング]
 http://www.arakin.dyndns.org/glsl_phong.php
 
 @see
 [アンビエントライト(ambient light)について]
 http://mukaimame-cg.jugem.jp/?eid=490
 
 @see
 [シェーダで普通のシェーディングをする]
 http://miffysora.wikidot.com/ja:glsl:shading
 
 @see
 [GLSLによるフォンシェーディング]
 http://www.slis.tsukuba.ac.jp/~fujisawa.makoto.fu/cgi-bin/wiki/index.php?GLSL%A4%CB%A4%E8%A4%EB%A5%D5%A5%A9%A5%F3%A5%B7%A5%A7%A1%BC%A5%C7%A5%A3%A5%F3%A5%B0
 
 @see
 [WebGL フォンシェーディング]
 http://wgld.org/d/webgl/w024.html
 
 @see
 [Wiki  フィンシェーディング]
 http://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A9%E3%83%B3%E3%82%B7%E3%82%A7%E3%83%BC%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0
 
 */

#version 120

//--------------------------------------
//フォグ
uniform int u_fogEnabled;
//--------------------------------------

//--------------------------------------
//カラーマップ
uniform sampler2DRect u_colorMap;
//--------------------------------------

//--------------------------------------
//テクスチャカラーマップ
uniform sampler2DRect u_textureColorMap;
//--------------------------------------

//--------------------------------------
//シャドウマッピング
uniform int u_shadowEnabled;
uniform sampler2DRect u_shadowTexture;
//--------------------------------------

//--------------------------------------
//被写界深度
uniform int u_dofEnabled;
uniform sampler2DRect u_depthTexture;
uniform float u_focalDistance;
uniform float u_focalRange;
uniform float u_blurRadius;
float sourceTextureWidth = 1024.0;
float sourceTextureHeight = 768.0;
//--------------------------------------

//--------------------------------------------------------------
// 被写界深度
//--------------------------------------------------------------

//--------------------------------------------------------------
//
float linearizeDepth(float zoverw){
    float near = 1.0;
    float far = 100000.0;
    return (2.0 * near) / (far + near - zoverw * (far - near));
}
//--------------------------------------------------------------
//
vec4 getColor(vec2 offset) {
    vec4 shadowColor = texture2DRect(u_shadowTexture, gl_FragCoord.st + offset);
    vec4 color = texture2DRect(u_colorMap, gl_FragCoord.st + offset);
    return color * (1.0 - shadowColor.r);
}
//--------------------------------------------------------------
//
float getDepth(vec2 offset) {
    return texture2DRect(u_depthTexture, gl_FragCoord.st + offset).r;
}
//--------------------------------------------------------------
//
float getBlur(float depth) {
    return min(abs(linearizeDepth(depth) * 100000.0 - u_focalDistance) / u_focalRange, 1.0);
}
//--------------------------------------------------------------
//
vec4 blurSample(float depth, vec2 blur, vec2 offset, inout float influence) {
    offset *= blur * u_blurRadius;
    
    vec4 color = getColor(offset);
    //if (col.rgb == vec3(0,0,0)) {
    //    return vec4(0,0,0,0);
    //}
    
    float contrib;
    float idepth = getDepth(offset);
    if (idepth < depth){
        contrib = getBlur(idepth);
    } else {
        contrib = 1.0;
    }
    
    influence += contrib;
    
    return color * contrib;
}






//--------------------------------------------------------------
// MAIN
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    //カラー
    vec4 color = texture2DRect(u_colorMap, gl_FragCoord.st);
    compositeColor += color;
    
    //テクスチャカラー
    //vec4 textureColor = texture2DRect(u_textureColorMap, gl_FragCoord.st);
    //compositeColor *= textureColor;

    
//    //--------------------------------------
//    //フォグ
//    if(u_fogEnabled == 1) {
//        //カメラから対象のピクセルまでの距離zを求める
//        float z = gl_FragCoord.z / gl_FragCoord.w;
//        
//        //Liner Fog
//        float fogFactor = (gl_Fog.end - z) / (gl_Fog.end - gl_Fog.start);
//        
//        //float LOG2 = 1.442695;
//        //Exp Fog
//        //float fogFactor = exp2(-gl_Fog.density * z * LOG2);
//        //Exp2 Fog
//        //float fogFactor = exp2(-gl_Fog.density * gl_Fog.density * z * z * LOG2);
//        
//        //0.0~1の間に巻く
//        fogFactor = clamp(fogFactor, 0.0, 1.0);
//        
//        compositeColor = mix(gl_Fog.color, compositeColor, fogFactor);
//    }
//    //--------------------------------------
//    
//    
//    vec4 color;
//    
//    //--------------------------------------------------------------
//    //被写界深度
//    if(u_dofEnabled == 1) {
//        color = vec4(0.0, 0.0, 0.0, 0.0);
//        
//        float depth = getDepth(vec2(0.0, 0.0));
//        float aspect = sourceTextureWidth / sourceTextureHeight;
//        vec2 blur = vec2(getBlur(depth)) * vec2(1.0, aspect);
//        float influence = 0.000001;
//        
//        // Bokeh: Pentagon_Outline (30 samples)
//        color += blurSample(depth, blur, vec2(0.158509, -0.884836), influence);
//        color += blurSample(depth, blur, vec2(0.475528, -0.654508), influence);
//        color += blurSample(depth, blur, vec2(0.792547, -0.424181), influence);
//        color += blurSample(depth, blur, vec2(0.890511, -0.122678), influence);
//        color += blurSample(depth, blur, vec2(0.769421, 0.250000), influence);
//        color += blurSample(depth, blur, vec2(0.648330, 0.622678), influence);
//        color += blurSample(depth, blur, vec2(0.391857, 0.809017), influence);
//        color += blurSample(depth, blur, vec2(-0.000000, 0.809017), influence);
//        color += blurSample(depth, blur, vec2(-0.391857, 0.809017), influence);
//        color += blurSample(depth, blur, vec2(-0.648331, 0.622678), influence);
//        color += blurSample(depth, blur, vec2(-0.769421, 0.250000), influence);
//        color += blurSample(depth, blur, vec2(-0.890511, -0.122678), influence);
//        color += blurSample(depth, blur, vec2(-0.158509, -0.884836), influence);
//        color += blurSample(depth, blur, vec2(-0.475528, -0.654509), influence);
//        color += blurSample(depth, blur, vec2(-0.792547, -0.424181), influence);
//        color += blurSample(depth, blur, vec2(0.000000, -1.000000), influence);
//        color += blurSample(depth, blur, vec2(0.951056, -0.309017), influence);
//        color += blurSample(depth, blur, vec2(0.587785, 0.809017), influence);
//        color += blurSample(depth, blur, vec2(-0.587785, 0.809017), influence);
//        color += blurSample(depth, blur, vec2(-0.951057, -0.309017), influence);
//        color += blurSample(depth, blur, vec2(0.317019, -0.769672), influence);
//        color += blurSample(depth, blur, vec2(0.634038, -0.539345), influence);
//        color += blurSample(depth, blur, vec2(0.829966, 0.063661), influence);
//        color += blurSample(depth, blur, vec2(0.708876, 0.436339), influence);
//        color += blurSample(depth, blur, vec2(0.195928, 0.809017), influence);
//        color += blurSample(depth, blur, vec2(-0.195929, 0.809017), influence);
//        color += blurSample(depth, blur, vec2(-0.708876, 0.436339), influence);
//        color += blurSample(depth, blur, vec2(-0.829966, 0.063661), influence);
//        color += blurSample(depth, blur, vec2(-0.317019, -0.769672), influence);
//        color += blurSample(depth, blur, vec2(-0.634038, -0.539345), influence);
//        
//        compositeColor = color / influence;
//    } else {
//
//        //vec4 shadowColor = texture2DRect(u_shadowTexture, gl_FragCoord.st);
//        //compositeColor = color * (1.0 - shadowColor.r);
//    }
    //--------------------------------------------------------------
    
    //--------------------------------------------------------------
    //フォグ
    //if(u_fogEnabled == 1) {
//        //カメラから対象のピクセルまでの距離zを求める
//        float z = gl_FragCoord.z / gl_FragCoord.w;
//    
//        //Liner Fog
//        float fogFactor = (gl_Fog.end - z) / (gl_Fog.end - gl_Fog.start);
//        
//        float LOG2 = 1.442695;
//        //Exp Fog
//        //float fogFactor = exp2(-gl_Fog.density * z * LOG2);
//        //Exp2 Fog
//        //float fogFactor = exp2(-gl_Fog.density * gl_Fog.density * z * z * LOG2);
//        
//        //0.0~1の間に巻く
//        fogFactor = clamp(fogFactor, 0.0, 1.0);
//        
//        compositeColor = mix(gl_Fog.color, compositeColor, fogFactor);
    //}
    //--------------------------------------------------------------
    
	gl_FragColor = vec4(compositeColor.rgb, 1.0);
}