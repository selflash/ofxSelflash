#version 120

//--------------------------------------
//ライトID
uniform int u_light0ID;
uniform int u_light1ID;
uniform int u_light2ID;
uniform int u_light3ID;
uniform int u_light4ID;
uniform int u_light5ID;
uniform int u_light6ID;
uniform int u_light7ID;

//ライトの種類
uniform int u_light0Type;
uniform int u_light1Type;
uniform int u_light2Type;
uniform int u_light3Type;
uniform int u_light4Type;
uniform int u_light5Type;
uniform int u_light6Type;
uniform int u_light7Type;

//光源ベクトル
varying vec3 v_Light0Dir;
varying vec3 v_Light1Dir;
varying vec3 v_Light2Dir;
varying vec3 v_Light3Dir;
varying vec3 v_Light4Dir;
varying vec3 v_Light5Dir;
varying vec3 v_Light6Dir;
varying vec3 v_Light7Dir;

//ライトの有効・無効
uniform int u_light0Enabled;
uniform int u_light1Enabled;
uniform int u_light2Enabled;
uniform int u_light3Enabled;
uniform int u_light4Enabled;
uniform int u_light5Enabled;
uniform int u_light6Enabled;
uniform int u_light7Enabled;

//ライトの強さ
uniform float u_light0Intensity;
uniform float u_light1Intensity;
uniform float u_light2Intensity;
uniform float u_light3Intensity;
uniform float u_light4Intensity;
uniform float u_light5Intensity;
uniform float u_light6Intensity;
uniform float u_light7Intensity;

//減衰効果の有効・無効
uniform int u_light0AttenuationEnabled;
uniform int u_light1AttenuationEnabled;
uniform int u_light2AttenuationEnabled;
uniform int u_light3AttenuationEnabled;
uniform int u_light4AttenuationEnabled;
uniform int u_light5AttenuationEnabled;
uniform int u_light6AttenuationEnabled;
uniform int u_light7AttenuationEnabled;
//--------------------------------------

//--------------------------------------
//フォグ
uniform int u_fogEnabled;
//--------------------------------------

//--------------------------------------
//頂点
varying vec3 v_Vertex;
//法線
varying vec3 v_Normal;
//--------------------------------------

vec4 globalAmbient = vec4(0.1, 0.1, 0.1, 1.0);
vec4 textureColor = vec4(1.0, 1.0, 1.0, 1.0);

//--------------------------------------------------------------
//
vec4 shading(int id, int type, vec3 direction, float intensity, int attenuationEnabled){
    //光線ベクトル(正規化)
    vec3 lightDir = normalize(v_Vertex.xyz - gl_LightSource[id].position.xyz);
    //法線(正規化)
    vec3 normal = normalize(v_Normal);
    //ランバート反射
    float lambert = max(dot(normal, direction), 0.0);
    
    vec4 color;

    //--------------------------------------
    //環境反射成分(全体の色。暗いところ)
    vec4 ambient = gl_Color * gl_FrontMaterial.ambient * gl_LightSource[id].ambient;
    //if(textureColor.r + textureColor.g + textureColor.b > 0.0) {
    //    ambient *= textureColor;
    //}
    //拡散反射成分(中間のところ　石膏やチョークで発生する。ぼやっとした光。)
    intensity = intensity - 1.0;
    vec4 diffuse = vec4(intensity, intensity, intensity, 1.0) * gl_FrontMaterial.diffuse;
    //鏡面反射成分(金属が光った時みたいなキラッとした光。ハイライト。)
    vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);
    //--------------------------------------
    
    //--------------------------------------
    //もし光の方向ベクトル・法線の内積が0以下だったら鏡面反射は発生しない。
    if(lambert > 0.0){
        diffuse += vec4(1.0, 1.0, 1.0, 1.0) * gl_LightSource[id].diffuse * lambert;
        
        //反射ベクトルによるスペキュラー計算
        // @see http://www.arakin.dyndns.org/glsl_phong.php
        vec3 R = -normalize(reflect(lightDir, normal));
        vec3 V = normalize(v_Vertex);
        specular += gl_FrontMaterial.specular * pow(max(dot(R, V), 0.0), gl_FrontMaterial.shininess);
    }

    color = ambient + diffuse + specular;
    //--------------------------------------
    
    //--------------------------------------
    //減衰係数を乗じる
    if(attenuationEnabled == 1) {
        //法線やライティング情報を受け取る
        vec3 L = v_Vertex.xyz - gl_LightSource[id].position.xyz;
        //ライトまでの距離
        float d = length(L);
        //減衰係数
        float attenuation = 1.0 / (gl_LightSource[id].constantAttenuation +
                                   gl_LightSource[id].linearAttenuation * d +
                                   gl_LightSource[id].quadraticAttenuation * d * d);
                                   
        color *= attenuation;
    }
    //--------------------------------------
    
    
    //--------------------------------------
    //際だけがくっりきスポットライト
//    float angle;
//    angle = dot(normalize(gl_LightSource[id].spotDirection), -normalize(direction));
//    angle = max(angle, 0.0);
//    //if(acos(angle) < radians(gl_LightSource[id].spotCosCutoff))
//    if(acos(angle) > radians(10.0)) {
//        color = vec4(0.0, 0.0, 0.0, 1.0);
//    }
    //--------------------------------------
    //--------------------------------------
    //際だけがぼけたスポットライト
//    float angle;
//    angle = dot(normalize(gl_LightSource[id].spotDirection), -normalize(direction));
//    angle = max(angle, 0.0);
//    //if(acos(angle) < radians(gl_LightSource[id].spotCosCutoff))
//    if(acos(angle) > radians(10.0)) {
//        float n = (acos(angle) - radians(10.0)) / radians(1.0);
//        color *= (1.0 - n);
//    }
    //--------------------------------------
    //--------------------------------------
    //放射状にぼけたスポットライト
    if(type == 2) {
        float angle;
        angle = dot(normalize(gl_LightSource[id].spotDirection), -normalize(direction));
        angle = max(angle, 0.0);
        //if(acos(angle) < radians(gl_LightSource[id].spotCosCutoff))
        float n = (acos(angle) - radians((1.0 - gl_LightSource[id].spotCosCutoff)) * 10.0) / radians(1.0);
        color *= max((1.0 - n), 0.0);
        color.a = 1.0;
    }
    //--------------------------------------
    
    return color;
}

//--------------------------------------------------------------
// MAIN
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    vec4 compositeColor = globalAmbient;
    
    //--------------------------------------
    if(u_light0Enabled == 1) compositeColor += shading(u_light0ID, u_light0Type, v_Light0Dir, u_light0Intensity, u_light0AttenuationEnabled);
    if(u_light1Enabled == 1) compositeColor += shading(u_light1ID, u_light1Type, v_Light1Dir, u_light1Intensity, u_light1AttenuationEnabled);
    if(u_light2Enabled == 1) compositeColor += shading(u_light2ID, u_light2Type, v_Light2Dir, u_light2Intensity, u_light2AttenuationEnabled);
    if(u_light3Enabled == 1) compositeColor += shading(u_light3ID, u_light3Type, v_Light3Dir, u_light3Intensity, u_light3AttenuationEnabled);
    if(u_light4Enabled == 1) compositeColor += shading(u_light4ID, u_light4Type, v_Light4Dir, u_light4Intensity, u_light4AttenuationEnabled);
    if(u_light5Enabled == 1) compositeColor += shading(u_light5ID, u_light5Type, v_Light5Dir, u_light5Intensity, u_light5AttenuationEnabled);
    if(u_light6Enabled == 1) compositeColor += shading(u_light6ID, u_light6Type, v_Light6Dir, u_light6Intensity, u_light6AttenuationEnabled);
    if(u_light7Enabled == 1) compositeColor += shading(u_light7ID, u_light7Type, v_Light7Dir, u_light7Intensity, u_light7AttenuationEnabled);
    //--------------------------------------
    
    //--------------------------------------
    //フォグ
    if(u_fogEnabled == 1) {
        //カメラから対象のピクセルまでの距離zを求める
        float z = gl_FragCoord.z / gl_FragCoord.w;
        
        //Liner Fog
        float fogFactor = (gl_Fog.end - z) / (gl_Fog.end - gl_Fog.start);
        
        //float LOG2 = 1.442695;
        //Exp Fog
        //float fogFactor = exp2(-gl_Fog.density * z * LOG2);
        //Exp2 Fog
        //float fogFactor = exp2(-gl_Fog.density * gl_Fog.density * z * z * LOG2);
        
        //0.0~1の間に巻く
        fogFactor = clamp(fogFactor, 0.0, 1.0);
        
        compositeColor = mix(gl_Fog.color, compositeColor, fogFactor);
    }
    //--------------------------------------
    
    gl_FragColor = vec4(compositeColor.rgb, 1.0);
}