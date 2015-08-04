#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect u_renderedMap;
uniform sampler2DRect u_depthMap;

//ニアークリップ
uniform float u_nearClip = 1.0;
//ファークリップ
uniform float u_farClip = 20000.0;

uniform float u_focalLength;
uniform float u_focalDepth;


//this value comes from ReadDepth script.
uniform float u_focus = 500.0;

//max blur amount
uniform float u_maxBlurAmount = 32.0;

//aperture - bigger values for shallower depth of field
uniform float u_bias = 0.6;



//--------------------------------------
varying vec2 v_texCoord;
//--------------------------------------



//--------------------------------------------------------------
//
float linearize(float depth) {
//    float diff = u_farClip - u_nearClip;
//    float rawDepth = depth * diff;
//    return -u_farClip * u_nearClip / (rawDepth - u_farClip);
    
    float diff = u_farClip - u_nearClip;
    float rawDepth = depth * diff;
    return -u_nearClip / (rawDepth - u_farClip + u_nearClip);
    
    //    float n = 1.0; // camera z near
    //    float f = 20000.0; // camera z far
    //    return (2.0 * n) / (f + n - depth * (f - n));
}


void main() {
	float aspectratio = 800.0 / 600.0;
	vec2 aspectcorrect = vec2(1.0, aspectratio);
	
	vec4 depth1 = texture2DRect(u_depthMap, gl_TexCoord[0].xy);
//    depth1 = linearize(texture2DRect(u_depthMap, gl_TexCoord[0].st).r) * u_farClip;
    
//	float factor = (depth1.x - u_focus);
	float factor = depth1.x;
    
    float depth = linearize(texture2DRect(u_depthMap, v_texCoord.st).r) * u_farClip;
    float focalPlane = min(abs(depth  - u_focalLength) / u_focalDepth, 1.0);

    
	vec2 dofblur = vec2(clamp(factor * u_bias, -u_maxBlurAmount, u_maxBlurAmount));
	vec4 col = vec4(0.0);
	
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.0,0.4 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.15,0.37 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.29,0.29 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.37,0.15 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.4,0.0 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.37,-0.15 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.29,-0.29 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.15,-0.37 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.0,-0.4 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.15,0.37 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.29,0.29 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.37,0.15 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.4,0.0 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.37,-0.15 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.29,-0.29 )*aspectcorrect) * dofblur);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.15,-0.37 )*aspectcorrect) * dofblur);
	
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.15,0.37 )*aspectcorrect) * dofblur*0.9);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.37,0.15 )*aspectcorrect) * dofblur*0.9);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.37,-0.15 )*aspectcorrect) * dofblur*0.9);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.15,-0.37 )*aspectcorrect) * dofblur*0.9);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.15,0.37 )*aspectcorrect) * dofblur*0.9);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.37,0.15 )*aspectcorrect) * dofblur*0.9);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.37,-0.15 )*aspectcorrect) * dofblur*0.9);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.15,-0.37 )*aspectcorrect) * dofblur*0.9);
	
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.29,0.29 )*aspectcorrect) * dofblur*0.7);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.4,0.0 )*aspectcorrect) * dofblur*0.7);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.29,-0.29 )*aspectcorrect) * dofblur*0.7);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.0,-0.4 )*aspectcorrect) * dofblur*0.7);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.29,0.29 )*aspectcorrect) * dofblur*0.7);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.4,0.0 )*aspectcorrect) * dofblur*0.7);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.29,-0.29 )*aspectcorrect) * dofblur*0.7);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.0,0.4 )*aspectcorrect) * dofblur*0.7);
    
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.29,0.29 )*aspectcorrect) * dofblur*0.4);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.4,0.0 )*aspectcorrect) * dofblur*0.4);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.29,-0.29 )*aspectcorrect) * dofblur*0.4);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.0,-0.4 )*aspectcorrect) * dofblur*0.4);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.29,0.29 )*aspectcorrect) * dofblur*0.4);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.4,0.0 )*aspectcorrect) * dofblur*0.4);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( -0.29,-0.29 )*aspectcorrect) * dofblur*0.4);
	col += texture2DRect(u_renderedMap, gl_TexCoord[0].xy + (vec2( 0.0,0.4 )*aspectcorrect) * dofblur*0.4);
    
	gl_FragColor = col / 41.0;
    
//    gl_FragColor = vec4(depth1.x);
    gl_FragColor = vec4(focalPlane);
//    gl_FragColor = vec4(depth1.x);
	gl_FragColor.a = 1.0;
}
