#version 120

//uniform sampler2D u_source0;
uniform sampler2D u_source1;
uniform sampler2D u_source2;
uniform sampler2D u_source3;
uniform sampler2D u_source4;
uniform sampler2D u_source5;

varying vec2 v_texCoord;

//--------------------------------------------------------------
//
void main(void) {
//    vec4 source0Color = texture2D(u_source0, v_texCoord.xy);
    vec4 source1Color = texture2D(u_source1, v_texCoord.xy);
    vec4 source2Color = texture2D(u_source2, v_texCoord.xy);
    vec4 source3Color = texture2D(u_source3, v_texCoord.xy);
    vec4 source4Color = texture2D(u_source4, v_texCoord.xy);
    vec4 source5Color = texture2D(u_source5, v_texCoord.xy);
    
    vec4 finalColor = vec4(0.0);
    
    float intensity = 0.35;
//    finalColor += source0Color;
    finalColor += source1Color * intensity;
    finalColor += source2Color * intensity;
    finalColor += source3Color * intensity;
    finalColor += source4Color * intensity;
    finalColor += source5Color * intensity;
    
    gl_FragColor = vec4(finalColor.rgb, 1.0);
}
