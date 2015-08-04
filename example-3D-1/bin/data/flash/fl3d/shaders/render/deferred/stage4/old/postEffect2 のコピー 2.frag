#version 120

#define PI  3.14159265

//--------------------------------------
//アルベドテクスチャ
uniform sampler2D u_albedoTexture;
//レンダリング済テクスチャ
uniform sampler2D u_renderedTexture;
//マテリアルタイプテクスチャ
uniform sampler2D u_materialType;
//デプステクスチャ
uniform sampler2D u_normalAndDepth;
//ブルームテクスチャ
uniform sampler2D u_bloomTexture;
//--------------------------------------

//--------------------------------------
uniform float u_textureWidth;
uniform float u_textureHeight;
float width = u_textureWidth;
float height = u_textureHeight;
//経過時間
uniform float u_time = 0;
//--------------------------------------

//--------------------------------------
//カメラ
//位置
uniform vec3 u_cameraPosition;
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
//------------------------------------------

//------------------------------------------
//デプスオブフィールド(被写界深度)
//samples on the first ring
uniform int u_samples = 3;
//ring count
uniform int u_ringCount = 3;
//テクセル
vec2 texel = vec2(1.0 / width, 1.0 / height);
//ブラーサイズ
uniform float u_depthBlurSize = 1.25;
//clamp value of max blur (0.0 = no blur,1.0 default)
uniform float u_maxBlur = 1.0;

//highlight threshold;
uniform float u_highlightThreshold = 0.3;
//highlight gain;
uniform float u_higilightGain = 8.0;

//bokeh edge bias
uniform float u_edgeBias = 0.5;
//pentagon shape feather
uniform float u_feather = 0.4;
//ディザ-処理
uniform float u_ditherAmount = 0.0001;

//マニュアル
//manual dof calculation
bool manualdof = false;
//near dof blur start
uniform float ndofstart = 1.0;
//near dof blur falloff distance
uniform float ndofdist = 2.0;
//far dof blur start
uniform float fdofstart = 1.0;
//far dof blur falloff distance
uniform float fdofdist = 3.0;
//------------------------------------------

//------------------------------------------
//クロマティックアベレーション(色収差)
//bokeh chromatic aberration/fringing
uniform float u_fringe = 0.7;
//------------------------------------------

//------------------------------------------
//HDR(ハイダイナミックレンジ)
//露出
uniform float u_exposure = 0.5;
//------------------------------------------

//------------------------------------------
//ノイズ
uniform float u_noiseStrength = 0.1;
//------------------------------------------

//------------------------------------------
//ビネット(周辺減光)
//circle of confusion size in mm (35mm film = 0.03mm)
float CoC = 0.03;
//vignetting outer border
float vignout = 1.0;
//vignetting inner border
float vignin = 0.0;
//f-stops till vignete fades
float vignfade = 22.0;
//------------------------------------------

//------------------------------------------
varying vec2 v_texCoord;
//------------------------------------------

//------------------------------------------
//pentagonal shape
float getPentagonalShape(vec2 coords) {
	float scale = float(u_ringCount) - 1.3;
	vec4  HS0 = vec4( 1.0,         0.0,         0.0,  1.0);
	vec4  HS1 = vec4( 0.309016994, 0.951056516, 0.0,  1.0);
	vec4  HS2 = vec4(-0.809016994, 0.587785252, 0.0,  1.0);
	vec4  HS3 = vec4(-0.809016994,-0.587785252, 0.0,  1.0);
	vec4  HS4 = vec4( 0.309016994,-0.951056516, 0.0,  1.0);
	vec4  HS5 = vec4( 0.0        ,0.0         , 1.0,  1.0);
	
	vec4  one = vec4(1.0);
	
	vec4 P = vec4((coords),vec2(scale, scale)); 
	
	vec4 dist = vec4(0.0);
	float inorout = -4.0;
	
	dist.x = dot(P, HS0);
	dist.y = dot(P, HS1);
	dist.z = dot(P, HS2);
	dist.w = dot(P, HS3);
	
	dist = smoothstep(-u_feather, u_feather, dist);
	
	inorout += dot(dist, one);
	
	dist.x = dot(P, HS4);
	dist.y = HS5.w - abs(P.z);
	
	dist = smoothstep(-u_feather, u_feather, dist);
	inorout += dist.x;
	
	return clamp(inorout, 0.0, 1.0);
}

//------------------------------------------
//blurring depth
float getBlurringDepth(vec2 coords) {
	float d = 0.0;
	float kernel[9];
	vec2 offset[9];
	
	vec2 wh = vec2(texel.x, texel.y) * u_depthBlurSize;
	
	offset[0] = vec2(-wh.x,-wh.y);
	offset[1] = vec2( 0.0, -wh.y);
	offset[2] = vec2( wh.x -wh.y);
	
	offset[3] = vec2(-wh.x,  0.0);
	offset[4] = vec2( 0.0,   0.0);
	offset[5] = vec2( wh.x,  0.0);
	
	offset[6] = vec2(-wh.x, wh.y);
	offset[7] = vec2( 0.0,  wh.y);
	offset[8] = vec2( wh.x, wh.y);
	
	kernel[0] = 1.0 / 16.0; kernel[1] = 2.0 / 16.0; kernel[2] = 1.0 / 16.0;
	kernel[3] = 2.0 / 16.0; kernel[4] = 4.0 / 16.0; kernel[5] = 2.0 / 16.0;
	kernel[6] = 1.0 / 16.0; kernel[7] = 2.0 / 16.0; kernel[8] = 1.0 / 16.0;
	
	for(int i = 0; i < 9; i++) {
		float tmp = texture2D(u_normalAndDepth, coords + offset[i]).a * 1000.0;
        
        //TODO
//        float n = texture2D(u_normalAndDepth, coords + offset[i]).a;
//        //実際のデプス値に戻す
//        n = n * u_farClip;
//        n = (n - u_cameraPosition.z) / u_farClip;
        
        
//		float tmp = n;
		d += tmp * kernel[i];
	}
	
	return d;
}

//------------------------------------------
//processing the sample
vec4 color(vec2 coords, float blur) {
	vec4 col = vec4(0.0, 0.0, 0.0, 1.0);
	
	col.r = texture2D(u_renderedTexture, coords + vec2(0.0, 1.0) * texel * u_fringe * blur).r;
	col.g = texture2D(u_renderedTexture, coords + vec2(-0.866, -0.5) * texel * u_fringe * blur).g;
	col.b = texture2D(u_renderedTexture, coords + vec2(0.866, -0.5) * texel * u_fringe * blur).b;
	
	vec3 lumcoeff = vec3(0.299, 0.587, 0.114);
	float lum = dot(col.rgb, lumcoeff);
	float thresh = max((lum - u_highlightThreshold) * u_higilightGain, 0.0);
	return col + mix(vec4(0.0), col, thresh * blur);
}

//------------------------------------------
//generating noise/pattern texture for dithering
vec2 getNoise(vec2 coord) {
	float noiseX = ((fract(1.0 - coord.s * (width / 2.0)) * 0.25) + (fract(coord.t * (height / 2.0)) * 0.75)) * 2.0 - 1.0;
	float noiseY = ((fract(1.0 - coord.s * (width / 2.0)) * 0.75) + (fract(coord.t * (height / 2.0)) * 0.25)) * 2.0 - 1.0;
	
//	if (noise) {
    if (true) {
		noiseX = clamp(fract(sin(dot(coord, vec2(12.9898, 78.233))) * 43758.5453), 0.0, 1.0) * 2.0 - 1.0;
		noiseY = clamp(fract(sin(dot(coord, vec2(12.9898, 78.233) * 2.0)) * 43758.5453), 0.0, 1.0) * 2.0 - 1.0;
	}
	return vec2(noiseX, noiseY);
}

//------------------------------------------
//
float linearize(float depth) {
    float length = u_farClip - u_nearClip;
    
	return -u_farClip * u_nearClip / (depth * (u_farClip - u_nearClip) - u_farClip);
}

//------------------------------------------
//ビネット(周辺減光)
float getVignette() {
	float dist = distance(v_texCoord.xy, vec2(0.5, 0.5));
	dist = smoothstep(vignout + (u_fstop / vignfade), vignin + (u_fstop / vignfade), dist);
	return clamp(dist, 0.0, 1.0);
}

//------------------------------------------
//
vec3 getDebugFocus(vec3 col, float blur, float depth) {
    //distance based edge smoothing
	float edge = 0.002 * depth;
	float m = clamp(smoothstep(0.0, edge, blur), 0.0, 1.0);
	float e = clamp(smoothstep(1.0 - edge, 1.0, blur), 0.0, 1.0);
	
	col = mix(col, vec3(1.0, 0.5, 0.0), (1.0 - m) * 0.6);
	col = mix(col, vec3(0.0, 0.5, 1.0), ((1.0 - e) - (1.0 - m)) * 0.2);
    
	return col;
}

//------------------------------------------
//
void main(void) {
    vec4 compositeColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    //--------------------------------------
    //アルベド
    vec4 albedo = texture2D(u_albedoTexture, v_texCoord.st);
    //マテリアルズ
    vec4 materials = texture2D(u_materialType, v_texCoord.st);
    //--------------------------------------

    //--------------------------------------
	//scene depth calculation
    float viewSpaceDepth;
    viewSpaceDepth = texture2D(u_normalAndDepth, v_texCoord.xy).a;
    //実際のデプス値に戻す
    viewSpaceDepth *= u_farClip;
    viewSpaceDepth = (viewSpaceDepth - u_cameraPosition.z) / u_farClip;
    //--------------------------------------
    
    
    float depth;
    float focalPlane;
    
    //--------------------------------------
    //A
    depth = linearize(viewSpaceDepth);
    
    //B depthblur
    depth = linearize(getBlurringDepth(v_texCoord.xy));
    //--------------------------------------
    
    //--------------------------------------
	//A focal plane calculation
	focalPlane = u_focalDistance;
    
    //B オートフォーカス
    viewSpaceDepth = texture2D(u_normalAndDepth, u_focus).a;
    //実際のデプス値に戻す
//    viewSpaceDepth *= u_farClip;
//    viewSpaceDepth = (viewSpaceDepth - u_cameraPosition.z) / u_farClip;
    
	//focal plane calculation
//    focalPlane = linearize(viewSpaceDepth);
    //------------------------------------------
	
	//dof blur factor calculation
	float blur = 0.0;
	
//	if (manualdof) {
//        //focal plane
//		float a = depth - fDepth;
//        //far DoF
//		float b = (a - fdofstart) / fdofdist;
//        //near Dof
//		float c = (-a - ndofstart) / ndofdist;
//		blur = (a > 0.0) ? b : c;
//	} else {
        //focal length in mm
		float focalLength = u_focalLength;
        //focal plane in mm
		focalPlane = focalPlane * 1000.0;
        //depth in mm
		depth = depth * 1000.0;
		
		float a = (depth * focalLength) / (depth - focalLength);
		float b = (focalPlane * focalLength) / (focalPlane - focalLength);
    
		float c = (focalPlane - focalLength) / (focalPlane * u_fstop * CoC);
		
		blur = abs(a - b) * c;
//	}
	
	blur = clamp(blur, 0.0, 1.0);
	
	// calculation of pattern for ditering
	vec2 noise = getNoise(v_texCoord.xy) * u_ditherAmount * blur;
	
	// getting blur x and y step factor
	float w = (1.0 / width) * blur * u_maxBlur + noise.x;
	float h = (1.0 / height) * blur * u_maxBlur + noise.y;
	
    
	if(blur < 0.05) {
        compositeColor = texture2D(u_renderedTexture, v_texCoord.xy);
	} else {
		compositeColor = texture2D(u_renderedTexture, v_texCoord.xy);
		float s = 1.0;
		int ringsamples;

		for (int i = 1; i <= u_ringCount; i += 1) {
			ringsamples = i * u_samples;

			for (int j = 0 ; j < ringsamples ; j += 1) {
				float step = PI*2.0 / float(ringsamples);
				float pw = (cos(float(j) * step) * float(i));
				float ph = (sin(float(j) * step) * float(i));
				float p = 1.0;

//				if (pentagon) {
//					p = getBlurringDepth(vec2(pw, ph));
//				}

				compositeColor += color(v_texCoord.xy + vec2(pw * w, ph * h), blur) * mix(1.0, (float(i)) / (float(u_ringCount)), u_edgeBias) * p;
				s += 1.0 * mix(1.0, (float(i)) / (float(u_ringCount)), u_edgeBias) * p;
			}
		}
        
        //divide by sample count
		compositeColor /= s;
	}
    
    //------------------------------------------
//    if(materials.a <= 0.3) compositeColor.rgb = albedo.rgb;
    //------------------------------------------
    
    //--------------------------------------
    //HDR
    //露出
	compositeColor.rgb = 1.0 - pow(vec3(2.71), -(compositeColor.rgb * u_exposure));
    //ガンマ補正
    compositeColor.rgb = pow(compositeColor.rgb, vec3(1.0 / 2.2));
    //--------------------------------------
    
    //------------------------------------------
    //ビネット(周辺減光)
    compositeColor *= getVignette();
    //------------------------------------------
	
    vec4 finalColor = vec4(compositeColor.rgb, 1.0);
	gl_FragColor = finalColor;
    
    
//    //被写界深度
//    float depthInViewSpace;
//    //------------------------------------------
//    //奥から1.0〜0.0 (1.0/1000.0)
//    //視点座標系でのデプス値
//    depthInViewSpace = texture2D(u_normalAndDepth, v_texCoord.xy).a;
//    //実際の視点座標系でのデプス値
//    float realDepthInViewSpace = depthInViewSpace * u_farClip;
//    float linearizeDepthInViewSpace = linearize(realDepthInViewSpace);
////    depthInViewSpace = (depthInViewSpace - u_cameraPosition.z) / u_farClip;
//    
//    
//
//    
//
////    float depth = linearize(depthInViewSpace);
//    
//
//    //depthblur
////    float depth = linearize(getBlurringDepth(v_texCoord.xy));
////    depth = depth * 0.01;
//    
////    float fDepth = u_focalDistance;
//    //focal plane
//    float a = linearizeDepthInViewSpace - u_focalDistance;
////    //far DoF
////    float b = (a - fdofstart) / fdofdist;
////    //near Dof
////    float c = (-a - ndofstart) / ndofdist;
////    float blur = (a > 0.0) ? b : c;
//    
//    
////    vec3 col = texture2D(u_renderedTexture, v_texCoord.xy).rgb;
//    compositeColor.rgb = vec3(a, a, a);
//    vec4 finalColor = vec4(compositeColor.rgb, 1.0);
//    gl_FragColor = finalColor;
////    //------------------------------------------
////    
////    
////    
////    //------------------------------------------
//////    //オートフォーカス
//////    depthInViewSpace = texture2D(u_normalAndDepth, u_focus).a;
//////    //実際のデプス値に戻す
//////    depthInViewSpace *= u_farClip;
//////    depthInViewSpace = (depthInViewSpace - u_cameraPosition.z) / u_farClip;
////    
////	//focal plane calculation
////    float fDepth = linearize(depthInViewSpace);
////    //------------------------------------------
////	
////    //------------------------------------------
////	//dof blur factor calculation
////	float blur = 0.0;
//////	if (manualdof) {
////        //focal plane
////		float a = depth - fDepth;
////        //far DoF
////		float b = (a - fdofstart) / fdofdist;
////        //near Dof
////		float c = (-a - ndofstart) / ndofdist;
////		blur = (a > 0.0) ? b : c;
//////	} else {
//////        //focal length in mm
//////		float f = u_focalLength;
//////        //focal plane in mm
//////		float d = fDepth * 1000.0;
//////        //depth in mm
//////		float o = depth * 1000.0;
//////		
//////		float a = (o * f) / (o - f);
//////		float b = (d * f) / (d - f);
//////		float c = (d - f) / (d * u_fstop * CoC);
//////		
//////		blur = abs(a - b) * c;
//////	}
////	
////	blur = clamp(blur, 0.0, 1.0);
////	
////	// calculation of pattern for ditering
////	vec2 noise = getNoise(v_texCoord.xy) * u_ditherAmount * blur;
////	
////	// getting blur x and y step factor
////	float w = (1.0 / width) * blur * u_maxBlur + noise.x;
////	float h = (1.0 / height) * blur * u_maxBlur + noise.y;
////    //------------------------------------------
////	
////    //------------------------------------------
////	// calculation of final color
//////	vec3 compositeColor = vec3(0.0, 0.0, 0.0);
////	
////    //some optimization thingy
////	if(blur < 0.05) {
////		compositeColor += texture2D(u_renderedTexture, v_texCoord.xy);
////	} else {
////		compositeColor += texture2D(u_renderedTexture, v_texCoord.xy);
////		float s = 1.0;
////		int ringsamples;
////
////		for (int i = 1; i <= u_ringCount; i += 1) {
////			ringsamples = i * u_samples;
////			
////			for (int j = 0; j < ringsamples; j += 1) {
////				float step = PI * 2.0 / float(ringsamples);
////				float pw = (cos(float(j) * step) * float(i));
////				float ph = (sin(float(j) * step) * float(i));
////				float p = 1.0;
////                
////                //ペンタゴン
////				p = getPentagonalShape(vec2(pw, ph));
////            
////				compositeColor += color(v_texCoord.xy + vec2(pw * w, ph * h), blur) * mix(1.0, (float(i)) / (float(u_ringCount)), u_edgeBias) * p;
////				s += 1.0 * mix(1.0, (float(i)) / (float(u_ringCount)), u_edgeBias) * p;
////			}
////		}
////        
////        //divide by sample count
////		compositeColor /= s;
////	}
////    //------------------------------------------
////	
////    //------------------------------------------
//////		col = getDebugFocus(col, blur, depth);
////    //------------------------------------------
////	
////    //------------------------------------------
////    //ビネット(周辺減光)
////    compositeColor *= getVignette();
////    //------------------------------------------
////    
////    //--------------------------------------
////    //HDR
////    //露出
////	compositeColor.rgb = 1.0 - pow(vec3(2.71), -(compositeColor.rgb * u_exposure));
////    //ガンマ補正
////    compositeColor.rgb = pow(compositeColor.rgb, vec3(1.0 / 2.2));
////    //--------------------------------------
////    
////    
//	
////    vec4 finalColor = vec4(compositeColor.rgb, 1.0);
////	gl_FragColor = finalColor;
}