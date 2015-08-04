#version 120
#define HORIZONTAL_BLUR_5

uniform sampler2D u_blurSampler;
uniform float u_sigma;
uniform float u_blurSize;

const float PI = 3.14159265;

#if defined(VERTICAL_BLUR_9)
const float numBlurPixelsPerSide = 4.0;
const vec2  blurMultiplyVec      = vec2(1.0, 0.0);
#elif defined(HORIZONTAL_BLUR_9)
const float numBlurPixelsPerSide = 4.0;
const vec2  blurMultiplyVec      = vec2(0.0, 1.0);
#elif defined(VERTICAL_BLUR_7)
const float numBlurPixelsPerSide = 3.0;
const vec2  blurMultiplyVec      = vec2(1.0, 0.0);
#elif defined(HORIZONTAL_BLUR_7)
const float numBlurPixelsPerSide = 3.0;
const vec2  blurMultiplyVec      = vec2(0.0, 1.0);
#elif defined(VERTICAL_BLUR_5)
const float numBlurPixelsPerSide = 2.0;
const vec2  blurMultiplyVec      = vec2(1.0, 0.0);
#elif defined(HORIZONTAL_BLUR_5)
const float numBlurPixelsPerSide = 2.0;
const vec2  blurMultiplyVec      = vec2(0.0, 1.0);
#else
const float numBlurPixelsPerSide = 0.0;
const vec2  blurMultiplyVec      = vec2(0.0, 0.0);
#endif

varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
    vec3 incrementalGaussian;
    incrementalGaussian.x = 1.0 / (sqrt(2.0 * PI) * u_sigma);
    incrementalGaussian.y = exp(-0.5 / (u_sigma * u_sigma));
    incrementalGaussian.z = incrementalGaussian.y * incrementalGaussian.y;
    
    vec4 avgValue = vec4(0.0, 0.0, 0.0, 0.0);
    float coefficientSum = 0.0;
    
    avgValue += texture2D(u_blurSampler, v_texCoord.xy) * incrementalGaussian.x;
    coefficientSum += incrementalGaussian.x;
    incrementalGaussian.xy *= incrementalGaussian.yz;
    
    for (float i = 1.0; i <= numBlurPixelsPerSide; i++) {
        avgValue += texture2D(u_blurSampler, v_texCoord.xy - i * u_blurSize * blurMultiplyVec) * incrementalGaussian.x;
        avgValue += texture2D(u_blurSampler, v_texCoord.xy + i * u_blurSize * blurMultiplyVec) * incrementalGaussian.x;
        coefficientSum += 2.0 * incrementalGaussian.x;
        incrementalGaussian.xy *= incrementalGaussian.yz;
    }
    
    gl_FragColor = avgValue / coefficientSum;
    
//    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
