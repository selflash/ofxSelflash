#version 120

//--------------------------------------
//ライトID
uniform int u_Light0ID;
uniform int u_Light1ID;
uniform int u_Light2ID;
uniform int u_Light3ID;
uniform int u_Light4ID;
uniform int u_Light5ID;
uniform int u_Light6ID;
uniform int u_Light7ID;

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
uniform int u_Light0Enabled;
uniform int u_Light1Enabled;
uniform int u_Light2Enabled;
uniform int u_Light3Enabled;
uniform int u_Light4Enabled;
uniform int u_Light5Enabled;
uniform int u_Light6Enabled;
uniform int u_Light7Enabled;

//ライトの強さ
uniform float u_Light0Intensity;
uniform float u_Light1Intensity;
uniform float u_Light2Intensity;
uniform float u_Light3Intensity;
uniform float u_Light4Intensity;
uniform float u_Light5Intensity;
uniform float u_Light6Intensity;
uniform float u_Light7Intensity;

//減衰効果の有効・無効
uniform int u_Light0AttenuationEnabled;
uniform int u_Light1AttenuationEnabled;
uniform int u_Light2AttenuationEnabled;
uniform int u_Light3AttenuationEnabled;
uniform int u_Light4AttenuationEnabled;
uniform int u_Light5AttenuationEnabled;
uniform int u_Light6AttenuationEnabled;
uniform int u_Light7AttenuationEnabled;
//--------------------------------------

//--------------------------------------
//フォグ
uniform int u_fogEnabled;
//--------------------------------------

//--------------------------------------
uniform sampler2D tex;
varying float rotAngle;
//--------------------------------------

//--------------------------------------
//頂点
varying vec3 v_Vertex;
//法線
varying vec3 v_Normal;
//--------------------------------------

vec4 textureColor;

//--------------------------------------------------------------
//
vec4 shading(int id, vec3 rowDirection, float intensity, int attenuationEnabled){
    //光線ベクトル(正規化)
    vec3 lightDir = normalize(v_Vertex.xyz - gl_LightSource[id].position.xyz);
    //法線(正規化)
    vec3 normal = normalize(v_Normal);
    //ランバート反射
    float lambert = max(dot(normal, rowDirection), 0.0);
    
    vec4 color;
    
    //--------------------------------------
    //環境反射成分(全体の色。暗いところ)
    vec4 ambient = gl_FrontMaterial.emission * gl_LightSource[id].ambient;
    //拡散反射成分(中間のところ　石膏やチョークで発生する。ぼやっとした光。)
    intensity = intensity - 1.0;
    vec4 diffuse = vec4(intensity, intensity, intensity, 1.0);
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
    //if(true) {
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
//    if(u_Light0Enabled == 1) compositeColor += shading(u_Light0ID, v_Light0Dir, 2.0, false);
    if(u_Light0Enabled == 1) compositeColor += shading(u_Light0ID, v_Light0Dir, u_Light0Intensity, u_Light0AttenuationEnabled);
    if(u_Light1Enabled == 1) compositeColor += shading(u_Light1ID, v_Light1Dir, u_Light1Intensity, u_Light1AttenuationEnabled);
    if(u_Light2Enabled == 1) compositeColor += shading(u_Light2ID, v_Light2Dir, u_Light2Intensity, u_Light2AttenuationEnabled);
    if(u_Light3Enabled == 1) compositeColor += shading(u_Light3ID, v_Light3Dir, u_Light3Intensity, u_Light3AttenuationEnabled);
    if(u_Light4Enabled == 1) compositeColor += shading(u_Light4ID, v_Light4Dir, u_Light4Intensity, u_Light4AttenuationEnabled);
    if(u_Light5Enabled == 1) compositeColor += shading(u_Light5ID, v_Light5Dir, u_Light5Intensity, u_Light5AttenuationEnabled);
    if(u_Light6Enabled == 1) compositeColor += shading(u_Light6ID, v_Light6Dir, u_Light6Intensity, u_Light6AttenuationEnabled);
//    if(u_Light7Enabled == 1) compositeColor += shading(u_Light7ID, v_Light7Dir, u_Light7Intensity, true);
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
    
    //--------------------------------------
    //テクスチャの回転なし
    //    textureColor = texture2D(tex, gl_TexCoord[0].st);
    
    //テクスチャの回転
    float angle = rotAngle;
    vec2 offset = vec2(0.5, 0.5);
    vec2 v2 = gl_TexCoord[0].st;
    
    //回転マトリックスの生成
    float sinX = sin(angle);
    float cosX = cos(angle);
    float sinY = sin(angle);
    float cosY = cos(angle);
    mat2 rotationMatrix = mat2(cosX, -sinX, sinY, cosX);
    
    //中心から半分ズラして回転マトリックスを加味して中心に戻す
    vec2 newcoords = ((v2-offset) * (rotationMatrix));
    newcoords += offset;
    
    textureColor = texture2D(tex, newcoords) * gl_Color;
    compositeColor *= textureColor;
    //--------------------------------------
    
    gl_FragColor = compositeColor;
}