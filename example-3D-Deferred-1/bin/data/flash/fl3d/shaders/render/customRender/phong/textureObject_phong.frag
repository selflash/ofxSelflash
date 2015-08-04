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
//--------------------------------------

//--------------------------------------
//フォグ
uniform int u_fogEnabled;
//--------------------------------------

//--------------------------------------
//
uniform sampler2D tex0;
//--------------------------------------

//--------------------------------------
//頂点
varying vec3 v_Vertex;
//法線
varying vec3 v_Normal;
//--------------------------------------

//--------------------------------------------------------------
//
vec4 shading(int id, vec3 rowDirection, float intensity, bool enabled){
    //光線ベクトル(正規化)
    vec3 lightDir = normalize(v_Vertex.xyz - gl_LightSource[id].position.xyz);
    //法線(正規化)
    vec3 normal = normalize(v_Normal);
    //ランバート反射
    float lambert = max(dot(normal, rowDirection), 0.0);
    
    vec4 color;

    //--------------------------------------
    //環境反射成分(全体の色。暗いところ)
    //vec4 ambient = ((texture2D(tex0, gl_TexCoord[0].st) * gl_Color) + gl_FrontMaterial.emission) * gl_LightSource[id].ambient;
    vec4 ambient = ((texture2D(tex0, gl_TexCoord[0].st) * gl_Color) * gl_FrontMaterial.emission) * gl_LightSource[id].ambient;
    //拡散反射成分(中間のところ　石膏やチョークで発生する。ぼやっとした光。)
    intensity = intensity - 1.0;
    vec4 diffuse = vec4(intensity, intensity, intensity, 1.0);
    //鏡面反射成分(金属が光った時みたいなキラッとした光。ハイライト。)
    vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);
    //--------------------------------------
    
    //--------------------------------------
    //もし光の方向ベクトル・法線の内積が0以下だったら鏡面反射は発生しない。
    if(lambert > 0.0 && enabled){
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
    if(enabled) {
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
    
    return color;
}

//--------------------------------------------------------------
// MAIN
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    //--------------------------------------
    if(u_light0Enabled == 1) compositeColor += shading(u_light0ID, v_Light0Dir, u_light0Intensity, true);
    if(u_light1Enabled == 1) compositeColor += shading(u_light1ID, v_Light1Dir, u_light1Intensity, true);
    if(u_light2Enabled == 1) compositeColor += shading(u_light2ID, v_Light2Dir, u_light2Intensity, true);
    if(u_light3Enabled == 1) compositeColor += shading(u_light3ID, v_Light3Dir, u_light3Intensity, true);
    if(u_light4Enabled == 1) compositeColor += shading(u_light4ID, v_Light4Dir, u_light4Intensity, true);
    if(u_light5Enabled == 1) compositeColor += shading(u_light5ID, v_Light5Dir, u_light5Intensity, true);
    if(u_light6Enabled == 1) compositeColor += shading(u_light6ID, v_Light6Dir, u_light6Intensity, true);
    if(u_light7Enabled == 1) compositeColor += shading(u_light7ID, v_Light7Dir, u_light7Intensity, true);
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