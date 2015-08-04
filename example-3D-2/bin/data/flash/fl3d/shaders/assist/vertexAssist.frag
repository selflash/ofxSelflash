#version 120

//--------------------------------------
//ローカル座標系での頂点位置
varying vec4 v_vertexInModelSpace;
//グローバル座標系での頂点位置
//varying vec4 v_vertexInGlobalSpace;
//視点座標系での頂点位置
varying vec4 v_vertexInViewSpace;
//投影変換後のxy座標
varying vec4 v_vertexInProjectionSpace;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 1.0);
    
    //--------------------------------------
    //ローカル座標系での頂点位置
//    //生の値
//    compositeColor = v_vertexInModelSpace;
//    //丸めたやつ
//    compositeColor = normalize(v_vertexInModelSpace);
    //--------------------------------------
    
    //--------------------------------------
    //グローバル座標系での頂点位置
//    //生の値
//    compositeColor = v_vertexInModelSpace;
//    //丸めたやつ
//    compositeColor = normalize(v_vertexInGlobalSpace);
    //--------------------------------------
    
    //--------------------------------------
    //視点座標系での頂点位置
//    //生の値
//    compositeColor = v_vertexInViewSpace;
//    //丸めたやつ
    compositeColor = normalize(v_vertexInViewSpace);
    //--------------------------------------
    
    //--------------------------------------
    //投影変換後のxy座標
//    //生の値
//    compositeColor = v_vertexInProjectionSpace;
//    //丸めたやつ
//    compositeColor = normalize(v_pov_vertexInProjectionSpacesition);
    //--------------------------------------

    gl_FragColor = compositeColor;
    gl_FragColor.a = 1.0;
}