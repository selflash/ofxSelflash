#version 120

#define PI  3.14159265

//--------------------------------------
//法線 + 深度マップ
uniform sampler2D u_normalAndDepth;
//スペキュラーマップ
uniform sampler2D u_specular;
//--------------------------------------

//--------------------------------------
uniform vec2 u_inverseScreenSize;
//--------------------------------------

//--------------------------------------
//カメラ
//位置
uniform vec3 u_cameraPosition;
//ニアークリップ
uniform float u_nearClip;
//ファークリップ
uniform float u_farClip;

uniform mat4x4 u_inverseCameraMatrix;
//--------------------------------------

//--------------------------------------
//ライト
//位置
uniform vec3 u_lightPositionInViewSpace;
//環境反射光
uniform vec4 u_lightAmbient;
//拡散反射光
uniform vec4 u_lightDiffuse;
//鏡面反射光
uniform vec4 u_lightSpecular;
//強さ
uniform float u_lightIntensity;
//リム
uniform float u_rimEnabled = 1.0;
uniform float u_rimIntensity = 2.0;
//スクリーン座標
uniform vec3 u_lightCoord;
//距離減衰
uniform float u_lightAttenuationEnabled;
uniform float u_lightConstantAttenuation;
uniform float u_lightLinearAttenuation;
uniform float u_lightQuadraticAttenuation;
//半径
uniform float u_lightRadius;
//--------------------------------------

//--------------------------------------
//視点座標系での頂点位置
varying vec4 v_vertexInViewSpace;
//--------------------------------------

//--------------------------------------------------------------
//
void main(void) {
    //--------------------------------------
    //処理中のピクセル座標(0.0〜1.0)
    vec2 texCoord = gl_FragCoord.xy * u_inverseScreenSize.xy;
    vec4 aData = texture2D(u_normalAndDepth, texCoord.st);
    vec4 bData = texture2D(u_specular, texCoord.st);
    
    //法線
    vec3 normal = aData.rgb;
    // 法線ベクトル
    vec3 normalVector = normalize(normal);
    
    //深度
    float linearDepth = aData.a;
    //視線(レイ)
    vec3 viewRay = vec3(v_vertexInViewSpace.xy * (-u_farClip / v_vertexInViewSpace.z), -u_farClip);
    //視線上にある頂点座標を深度値から求める(zは負)
    vec3 position = viewRay * linearDepth;
    //光線
    vec3 lightDirection = u_lightPositionInViewSpace - position;
    //光線ベクトル
    vec3 lightVector = normalize(lightDirection);
    
    //スペキュラ/シャインネス
    vec4 materialSpecular = vec4(bData.rgb, 1.0);
    float materialShininess = bData.a;
    //--------------------------------------
    
    //--------------------------------------
    //環境反射成分(アンビエント)
//    vec4 ambient = AMBIENT_GLOBAL + u_lightAmbient;
    vec4 ambient = vec4(0.0, 0.0, 0.0, 1.0);
    //拡散反射成分(ディフューズ)
    vec4 diffuse = vec4(0.0, 0.0, 0.0, 1.0);
    //鏡面反射成分(スペキュラ)
    vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);
    //--------------------------------------
    
    //--------------------------------------
    //ライティング
    vec4 diffuseContribution = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 specularContribution = vec4(0.0, 0.0, 0.0, 1.0);
    //ランバート反射
    float lambert = max(dot(normal, lightVector), 0.0);
    
    // @see http://shikihuiku.wordpress.com/2012/07/03/%E7%89%A9%E7%90%86%E3%83%99%E3%83%BC%E3%82%B9%E3%83%AC%E3%83%B3%E3%83%80%E3%83%AA%E3%83%B3%E3%82%B01/
    lambert = lambert * (1.0 / PI);
    //もし光の方向ベクトル・法線の内積が0以下だったら鏡面反射は発生しない。
    if (lambert > 0.0) {
        diffuseContribution = u_lightDiffuse * lambert;

        //反射ベクトルによるスペキュラー計算
        // @see http://www.arakin.dyndns.org/glsl_phong.php
        vec3 R = normalize(reflect(lightDirection, normal));
        vec3 V = normalize(position);
        //127 = shininess
        specularContribution = materialSpecular * u_lightSpecular * pow(max(dot(R, V), 0.0), materialShininess * 127.0);
        
        //--------------------------------------
        //減衰係数を乗じる
        if(u_lightAttenuationEnabled == 1) {
            //光源との距離
            float distance = length(lightDirection);
            
            //減衰係数
            float attenuation = 1.0 / (u_lightConstantAttenuation +
                                       u_lightLinearAttenuation * distance +
                                       u_lightQuadraticAttenuation * distance * distance);
            
            //ambientContribution *= attenuation;
            diffuseContribution *= attenuation;
            specularContribution *= attenuation;
        }
        //--------------------------------------
    }
    
//    ambient *= u_lightIntensity;
    diffuse += diffuseContribution * u_lightIntensity;
    specular += specularContribution * u_lightIntensity;
    vec4 compositeColor = ambient + diffuse + specular;
    //--------------------------------------

    //--------------------------------------
    // 視線ベクトル
//    vec3 eyeVector = (u_cameraPosition - position.xyz);
    
//    (mat3x3)worldMatrix4x4 ではなく mat3x3(worldMatrix4x4)
//    vec3 worldVertex = mat3x3(u_inverseCameraMatrix) * position;
//    vec3 worldNormal = mat3x3(u_inverseCameraMatrix) * normalVector;
//    vec3 worldCamera = mat3x3(u_inverseCameraMatrix) * u_cameraPosition;
    // ライトベクトル
//    vec3 lightVector = normalize(lightDirection);
    // 法線
//    vec3 normalVector = normalize(normal);
    // リムライトの強さ
//    float rimPower = 5.0;

    // 内積の値を反転しモデルの縁部分が1.0、視線と平行部分を0.0にする。
//    float rim = 1.0 - dot(normalVector, eyeVector);
    
    
    // リムライトの強さを補正
//    rim = pow(abs(rim), 11.0 - u_rimIntensity);

    // 太陽との逆光を計算（頂点シェーダでOK）
//    float lightRim = max(dot(-lightVector, eyeVector), 0.0);

    // モデルの縁計算と、太陽の逆光計算を乗算
//    float color = rim * lightRim;
    // Rimlight Shader
    const float rimStart = 0.1;
    const float rimEnd = 0.9;
    const float rimMultiplier = 0.4;
//    float rimMultiplier = u_rimIntensity;
    vec3 rimColor = u_lightDiffuse.rgb;
//    float NormalToCam = normalize(worldCamera - worldVertex);
//    float rim = smoothstep(rimStart, rimEnd, NormalToCam) * rimMultiplier;
//    compositeColor.rgb = (rimColor * rim);
//    if(u_rimEnabled == 1.0) compositeColor = vec4(color);
//    compositeColor.rgb = vec3(NormalToCam, NormalToCam, NormalToCam);
//    compositeColor.rgb = vec3(length(worldCamera - worldVertex) * 0.001);
    
//    float NormalToCam = 1.0 - clamp(dot(normalVector, vec3(0.0, 0.0, -1.0)), 0.0, 1.0);
    float NormalToCam = dot(normalVector, vec3(-0.4, 0.0, -1.0));
    float rim = smoothstep(rimStart, rimEnd, NormalToCam) * rimMultiplier;
    rim = pow(NormalToCam, u_rimIntensity * 2.0);
    rim = 1.0 - rim;
    compositeColor.rgb = rimColor * pow(rim, 5.0);
    //--------------------------------------
    
    //逆ガンマをかける
    compositeColor.rgb = pow(compositeColor.rgb, vec3(2.2));
    vec4 finalColor = vec4(compositeColor.rgb, 1.0);
    gl_FragData[0] = finalColor;
}
