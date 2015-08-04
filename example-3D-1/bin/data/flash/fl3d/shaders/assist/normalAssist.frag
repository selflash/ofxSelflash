#version 120

//--------------------------------------
//ローカル座標系での法線
varying vec3 v_normalInModelSpace;
//グローバル座標系での法線
//varying vec3 v_normalInGlobalSpace;
//視点座標系での法線
varying vec3 v_normalInViewSpace;
//投影変換後のxy座標
//varying vec3 v_normalInProjectionSpace;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    //--------------------------------------
    //ローカル座標系での法線
    compositeColor = vec4(v_normalInModelSpace, 1.0);
    //--------------------------------------
    
    //--------------------------------------
    //グローバル座標系での頂点位置
    
    //--------------------------------------
    
    //--------------------------------------
    //視点座標系での法線
//    compositeColor = vec4(v_normalInViewSpace, 1.0);
    //--------------------------------------
    
    gl_FragColor = compositeColor;
    gl_FragColor.a = 1.0;
}