#version 120

uniform sampler2DRect u_sourceTexture;
uniform sampler2DRect u_depthTexture;
float u_sourceTextureWidth = 1024.0;
float u_sourceTextureHeight = 768.0;

uniform float u_focalDistance;
uniform float u_focalRange;
uniform float u_blurRadius;

//--------------------------------------------------------------
//
float linearizeDepth(float zoverw){
    // camera z near
    float n = 1.0;
    // camera z far
    float f = 100000.0;
    return (2.0 * n) / (f + n - zoverw * (f - n));
}

//--------------------------------------------------------------
//
vec4 get_color(vec2 offset) {
    return texture2DRect(u_sourceTexture, gl_TexCoord[0].st + offset);
}

//--------------------------------------------------------------
//
float get_depth(vec2 offset) {
    return texture2DRect(u_depthTexture, gl_TexCoord[0].st + offset).r;
}

//--------------------------------------------------------------
//
float get_blur(float depth) {
    return min(abs(linearizeDepth(depth) * 100000.0 - u_focalDistance) / u_focalRange, 1.0);
}

//--------------------------------------------------------------
//
vec4 blur_sample(float depth, vec2 blur, vec2 offset, inout float influence) {
    float idepth;
    float contrib;
    vec4 col;

    offset *= blur * u_blurRadius;

    col = get_color(offset);
    //if (col.rgb == vec3(0,0,0)) {
    //    return vec4(0,0,0,0);
    //}
    
    idepth = get_depth(offset);
    if (idepth < depth){
        contrib = get_blur(idepth);
    } else {
        contrib = 1.0;
    }

    influence += contrib;
    
    return col * contrib;
}

//--------------------------------------------------------------
//
void main(void) {
    float depth = get_depth(vec2(0.0));
    float aspect = u_sourceTextureWidth / u_sourceTextureHeight;
    vec2 blur = vec2(get_blur(depth)) * vec2(1.0, aspect);
    vec4 col = vec4(0.0);
    float influence = 0.000001;

    // Bokeh: Pentagon_Outline (30 samples)
    col += blur_sample(depth, blur, vec2(0.158509, -0.884836), influence);
    col += blur_sample(depth, blur, vec2(0.475528, -0.654508), influence);
    col += blur_sample(depth, blur, vec2(0.792547, -0.424181), influence);
    col += blur_sample(depth, blur, vec2(0.890511, -0.122678), influence);
    col += blur_sample(depth, blur, vec2(0.769421, 0.250000), influence);
    col += blur_sample(depth, blur, vec2(0.648330, 0.622678), influence);
    col += blur_sample(depth, blur, vec2(0.391857, 0.809017), influence);
    col += blur_sample(depth, blur, vec2(-0.000000, 0.809017), influence);
    col += blur_sample(depth, blur, vec2(-0.391857, 0.809017), influence);
    col += blur_sample(depth, blur, vec2(-0.648331, 0.622678), influence);
    col += blur_sample(depth, blur, vec2(-0.769421, 0.250000), influence);
    col += blur_sample(depth, blur, vec2(-0.890511, -0.122678), influence);
    col += blur_sample(depth, blur, vec2(-0.158509, -0.884836), influence);
    col += blur_sample(depth, blur, vec2(-0.475528, -0.654509), influence);
    col += blur_sample(depth, blur, vec2(-0.792547, -0.424181), influence);
    col += blur_sample(depth, blur, vec2(0.000000, -1.000000), influence);
    col += blur_sample(depth, blur, vec2(0.951056, -0.309017), influence);
    col += blur_sample(depth, blur, vec2(0.587785, 0.809017), influence);
    col += blur_sample(depth, blur, vec2(-0.587785, 0.809017), influence);
    col += blur_sample(depth, blur, vec2(-0.951057, -0.309017), influence);
    col += blur_sample(depth, blur, vec2(0.317019, -0.769672), influence);
    col += blur_sample(depth, blur, vec2(0.634038, -0.539345), influence);
    col += blur_sample(depth, blur, vec2(0.829966, 0.063661), influence);
    col += blur_sample(depth, blur, vec2(0.708876, 0.436339), influence);
    col += blur_sample(depth, blur, vec2(0.195928, 0.809017), influence);
    col += blur_sample(depth, blur, vec2(-0.195929, 0.809017), influence);
    col += blur_sample(depth, blur, vec2(-0.708876, 0.436339), influence);
    col += blur_sample(depth, blur, vec2(-0.829966, 0.063661), influence);
    col += blur_sample(depth, blur, vec2(-0.317019, -0.769672), influence);
    col += blur_sample(depth, blur, vec2(-0.634038, -0.539345), influence);

    gl_FragColor = col / influence;

    // For debugging the blur factor
    //gl_FragColor = vec4(get_blur(depth));
    //gl_FragColor = vec4(depth);
}