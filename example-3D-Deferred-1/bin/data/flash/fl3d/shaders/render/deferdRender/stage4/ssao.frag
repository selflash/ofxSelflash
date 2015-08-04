#version 120

uniform sampler2D u_normalAndDepthMap;
uniform sampler2D u_randomJitterMap;

uniform vec2 u_texelSize;

//--------------------------------------
//カメラ
//視点逆行列
uniform mat4 u_inverseProjectionMatrix;
//ニアークリップ
uniform float u_nearClip = 0.1;
//ファークリップ
uniform float u_farClip = 10000000.0;
//焦点距離
uniform float u_focalDistance;
//focal length in mm
uniform float u_focalLength;
//f-stop value
uniform float u_fstop;
// autofocus point on screen (0.0,0.0 - left lower corner, 1.0,1.0 - upper right)
uniform vec2 u_focus = vec2(0.5, 0.5);
//--------------------------------------

//--------------------------------------
uniform float u_occluderBias;
uniform float u_samplingRadius;
// .x constant, .y linear, .z quadratic (unused)
uniform vec2 u_attenuation;
//--------------------------------------

//--------------------------------------
varying vec3 v_vertex;
varying vec2 v_texCoord;
//--------------------------------------

//--------------------------------------------------------------
///
float samplePixels(vec3 position, vec3 normal, vec2 texCoord) {
    //--------------------------------------
    //深度値から位置を復元
    float realDepth = texture2D(u_normalAndDepthMap, texCoord).a * u_farClip;
    vec4 pos = vec4((texCoord.x - 0.5) * 2.0, (texCoord.y - 0.5) * 2.0, 1.0, 1.0);
    //視線(レイ)
    vec4 viewRay = u_inverseProjectionMatrix * pos;
    vec3 dstPosition = viewRay.xyz * realDepth;
    //--------------------------------------
    
    vec3 positionVector = dstPosition - position;
    float intensity = max(dot(normalize(positionVector), normal) - u_occluderBias, 0.0);
    
    float dist = length(positionVector);
    float attenuation = 1.0 / (u_attenuation.x + (u_attenuation.y * dist));
    
    return intensity * attenuation;
}

//--------------------------------------------------------------
//
void main(void) {
    vec2 randomVector = normalize(texture2D(u_randomJitterMap, v_texCoord).xy * 2.0 - 1.0);

    //--------------------------------------
    vec3 normalInViewSpace = texture2D(u_normalAndDepthMap, v_texCoord).xyz;
    //--------------------------------------
    
    //--------------------------------------
    float depthInViewSpace = texture2D(u_normalAndDepthMap, v_texCoord).a;
    //--------------------------------------
    
    //--------------------------------------
    //深度値から位置を復元
    float realDepth = depthInViewSpace * u_farClip;
    vec4 pos = vec4((v_texCoord.x - 0.5) * 2.0, (v_texCoord.y - 0.5) * 2.0, 1.0, 1.0);
    //視線(レイ)
    vec4 viewRay = u_inverseProjectionMatrix * pos;
    vec3 positionInViewSpace = viewRay.xyz * realDepth;
    //--------------------------------------

    //--------------------------------------
    float kernelRadius = u_samplingRadius * (1.0 - depthInViewSpace);

    vec2 kernel[4];
    kernel[0] = vec2(0.0, 1.0);  // top
    kernel[1] = vec2(1.0, 0.0);  // right
    kernel[2] = vec2(0.0, -1.0); // bottom
    kernel[3] = vec2(-1.0, 0.0); // left

    // 45 degrees = sin(PI / 4)
    const float Sin45 = 0.707107;

    float occlusion = 0.0;

    for (int i = 0; i < 4; ++i) {
        vec2 k1 = reflect(kernel[i], randomVector);

        vec2 k2 = vec2(k1.x * Sin45 - k1.y * Sin45, k1.x * Sin45 + k1.y * Sin45);

        k1 *= u_texelSize;
        k2 *= u_texelSize;

        occlusion += samplePixels(positionInViewSpace, normalInViewSpace, v_texCoord + k1 * kernelRadius);
        occlusion += samplePixels(positionInViewSpace, normalInViewSpace, v_texCoord + k2 * kernelRadius * 0.75);
        occlusion += samplePixels(positionInViewSpace, normalInViewSpace, v_texCoord + k1 * kernelRadius * 0.5);
        occlusion += samplePixels(positionInViewSpace, normalInViewSpace, v_texCoord + k2 * kernelRadius * 0.25);
    }

    occlusion /= 16;
    occlusion = 1.0 - clamp(occlusion, 0.0, 1.0);
    //--------------------------------------

    gl_FragColor = vec4(occlusion, occlusion, occlusion, 1.0);
}
