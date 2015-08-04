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
//視点逆行列
uniform mat4x4 u_cameraModelViewMatrix;
//視点逆行列
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
//    vec3 lightDirection = u_lightPositionInViewSpace - vec3(0.0, 0.0, 0.0);
    vec3 lightDirection = vec3(1.0, 0.0, 0.0);
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
        
//        (mat3x3)worldMatrix4x4 ではなく mat3x3(worldMatrix4x4)
//        lightDirection = lightDirection * mat3x3(u_cameraModelViewMatrix);
        
        //反射ベクトルによるスペキュラー計算
        // @see http://www.arakin.dyndns.org/glsl_phong.php
        vec3 R = normalize(reflect(lightDirection, normal));
        vec3 V = normalize(position);
        //127 = shininess
        specularContribution = materialSpecular * u_lightSpecular * pow(max(dot(R, V), 0.0), materialShininess * 127.0);
    }
    
//    ambient *= u_lightIntensity;
    diffuse += diffuseContribution * u_lightIntensity;
//    specular += specularContribution * u_lightIntensity;
    vec4 compositeColor = ambient + diffuse + specular;
    //--------------------------------------
    
    //逆ガンマをかける
    compositeColor.rgb = pow(compositeColor.rgb, vec3(2.2));
    vec4 finalColor = vec4(compositeColor.rgb, 1.0);
    gl_FragData[0] = finalColor;
}
