#version 120

uniform sampler2D u_source;
uniform sampler2D u_glareSampler;

varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
    vec3 incrementalGaussian;
    
    vec4 sourceColor = texture2D(u_source, v_texCoord.xy);
    vec4 glareColor = texture2D(u_glareSampler, v_texCoord.xy);
    
    vec4 finalColor = sourceColor;
    finalColor += glareColor;
    
    gl_FragColor = vec4(finalColor.rgb, 1.0);
}
