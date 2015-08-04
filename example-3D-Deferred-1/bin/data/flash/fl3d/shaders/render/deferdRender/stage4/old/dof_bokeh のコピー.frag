#version 120

//--------------------------------------
//カメラ
//位置
uniform vec3 u_cameraPosition;
//ニアークリップ
uniform float u_nearClip;
//ファークリップ
uniform float u_farClip;
//--------------------------------------


uniform sampler2D bgl_RenderedTexture;
uniform sampler2D bgl_DepthTexture;
uniform float bgl_RenderedTextureWidth;
uniform float bgl_RenderedTextureHeight;


varying vec2 v_texCoord;

#define PI  3.14159265

//texture width
float width = bgl_RenderedTextureWidth;
//texture height
float height = bgl_RenderedTextureHeight;

vec2 texel = vec2(1.0 / width, 1.0 / height);

//uniform variables from external script

//focal distance value in meters, but you may use autofocus option below
uniform float u_focalDistance;
//focal length in mm
uniform float focalLength;
//f-stop value
uniform float fstop;
//show debug focus point and focal range (red = focal point, green = focal range)
uniform bool showFocus;

/* 
make sure that these two values are the same for your camera, otherwise distances will be wrong.
*/

//camera clipping start
float znear = 0.1;
//camera clipping end
float zfar = 10000000.0;

//------------------------------------------
//user variables

//samples on the first ring
int samples = 3;
//ring count
int rings = 3;

//manual dof calculation
bool manualdof = false;
//near dof blur start
float ndofstart = 1.0;
//near dof blur falloff distance
float ndofdist = 2.0;
//far dof blur start
float fdofstart = 1.0;
//far dof blur falloff distance
float fdofdist = 3.0;

//circle of confusion size in mm (35mm film = 0.03mm)
float CoC = 0.03;
//use optical lens vignetting?
bool vignetting = true;
//vignetting outer border
float vignout = 1.3;
//vignetting inner border
float vignin = 0.0;
//f-stops till vignete fades
float vignfade = 22.0;

//use autofocus in shader? disable if you use external u_focalDistance value
bool autofocus = false;
// autofocus point on screen (0.0,0.0 - left lower corner, 1.0,1.0 - upper right)
vec2 focus = vec2(0.5, 0.5);
//clamp value of max blur (0.0 = no blur,1.0 default)
float maxblur = 1.0;

//highlight threshold;
float threshold = 0.5;
//highlight gain;
float gain = 0.0;

//bokeh edge bias
float bias = 0.5;
//bokeh chromatic aberration/fringing
float fringe = 0.7;

//use noise instead of pattern for sample dithering
bool noise = true;
//dither amount
float namount = 0.0001;

//blur the depth buffer?
bool depthblur = false;
//depthblursize
float dbsize = 1.25;

/*
next part is experimental
not looking good with small sample and ring count
looks okay starting from samples = 4, rings = 4
*/

//use pentagon as bokeh shape?
bool pentagon = false;
//pentagon shape feather
float feather = 0.4;

//------------------------------------------
//pentagonal shape
float penta(vec2 coords) {
	float scale = float(rings) - 1.3;
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
	
	dist = smoothstep(-feather, feather, dist);
	
	inorout += dot(dist, one);
	
	dist.x = dot(P, HS4);
	dist.y = HS5.w - abs(P.z);
	
	dist = smoothstep(-feather, feather, dist);
	inorout += dist.x;
	
	return clamp(inorout, 0.0, 1.0);
}

//------------------------------------------
//blurring depth
float bdepth(vec2 coords) {
	float d = 0.0;
	float kernel[9];
	vec2 offset[9];
	
	vec2 wh = vec2(texel.x, texel.y) * dbsize;
	
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
		float tmp = texture2D(bgl_DepthTexture, coords + offset[i]).a * 1000.0;
		d += tmp * kernel[i];
	}
	
	return d;
}

//------------------------------------------
//processing the sample
vec3 color(vec2 coords, float blur) {
	vec3 col = vec3(0.0);
	
	col.r = texture2D(bgl_RenderedTexture, coords + vec2(0.0, 1.0) * texel * fringe * blur).r;
	col.g = texture2D(bgl_RenderedTexture, coords + vec2(-0.866, -0.5) * texel * fringe * blur).g;
	col.b = texture2D(bgl_RenderedTexture, coords + vec2(0.866, -0.5) * texel * fringe * blur).b;
	
	vec3 lumcoeff = vec3(0.299, 0.587, 0.114);
	float lum = dot(col.rgb, lumcoeff);
	float thresh = max((lum - threshold) * gain, 0.0);
	return col + mix(vec3(0.0), col, thresh * blur);
}

//------------------------------------------
//generating noise/pattern texture for dithering
vec2 rand(vec2 coord) {
	float noiseX = ((fract(1.0 - coord.s * (width / 2.0)) * 0.25) + (fract(coord.t * (height / 2.0)) * 0.75)) * 2.0 - 1.0;
	float noiseY = ((fract(1.0 - coord.s * (width / 2.0)) * 0.75) + (fract(coord.t * (height / 2.0)) * 0.25)) * 2.0 - 1.0;
	
	if (noise) {
		noiseX = clamp(fract(sin(dot(coord, vec2(12.9898, 78.233))) * 43758.5453), 0.0, 1.0) * 2.0 - 1.0;
		noiseY = clamp(fract(sin(dot(coord, vec2(12.9898, 78.233) * 2.0)) * 43758.5453), 0.0, 1.0) * 2.0 - 1.0;
	}
	return vec2(noiseX,noiseY);
}

//------------------------------------------
//
vec3 debugFocus(vec3 col, float blur, float depth) {
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
float linearize(float depth) {
	return -zfar * znear / (depth * (zfar - znear) - zfar);
}

//------------------------------------------
//
float vignette() {
	float dist = distance(gl_TexCoord[3].xy, vec2(0.5,0.5));
	dist = smoothstep(vignout + (fstop / vignfade), vignin + (fstop / vignfade), dist);
	return clamp(dist, 0.0, 1.0);
}

//------------------------------------------
//
void main(void) {
	//scene depth calculation
    float n;
    
    n = texture2D(bgl_DepthTexture, gl_TexCoord[0].xy).a;
    //実際のデプス値に戻す
    n = n * u_farClip;
    n = abs(n - u_cameraPosition.z) / u_farClip;


    float depth = linearize(n);
//	float depth = linearize(texture2D(bgl_DepthTexture, gl_TexCoord[0].xy).a);
	
//	if (depthblur) {
		depth = linearize(bdepth(gl_TexCoord[0].xy));
//	}
//    gl_FragColor = vec4(depth, depth, depth, 1.0);
    
	//focal plane calculation
	float fDepth = u_focalDistance;
	
	if (autofocus) {
    n = texture2D(bgl_DepthTexture, focus).a;
    //実際のデプス値に戻す
    n = n * u_farClip;
    n = abs(n - u_cameraPosition.z) / u_farClip;
    fDepth = linearize(n);
//		fDepth = linearize(texture2D(bgl_DepthTexture, focus).a * 1000.0);
	}
	
	
	//dof blur factor calculation
	float blur = 0.0;
	
	if (manualdof) {
        //focal plane
		float a = depth - fDepth;
        //far DoF
		float b = (a - fdofstart) / fdofdist;
        //near Dof
		float c = (-a - ndofstart) / ndofdist;
		blur = (a > 0.0) ? b : c;
	} else {
        //focal length in mm
		float f = focalLength;
        //focal plane in mm
		float d = fDepth * 1000.0;
        //depth in mm
		float o = depth * 1000.0;
		
		float a = (o * f) / (o - f);
		float b = (d * f) / (d - f);
		float c = (d - f) / (d * fstop * CoC);
		
		blur = abs(a - b) * c;
	}
	
	blur = clamp(blur, 0.0, 1.0);
	
	// calculation of pattern for ditering
	vec2 noise = rand(gl_TexCoord[0].xy) * namount * blur;
	
	// getting blur x and y step factor
	float w = (1.0 / width) * blur * maxblur + noise.x;
	float h = (1.0 / height) * blur * maxblur + noise.y;
	
	// calculation of final color
	vec3 col = vec3(0.0);
	
    //some optimization thingy
//	if(blur < 0.05) {
		col = texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy).rgb;
//	} else {
//		col = texture2D(bgl_RenderedTexture, gl_TexCoord[0].xy).rgb;
//		float s = 1.0;
//		int ringsamples;
//
//		for (int i = 1; i <= rings; i += 1) {
//			ringsamples = i * samples;
//			
//			for (int j = 0 ; j < ringsamples ; j += 1) {
//				float step = PI*2.0 / float(ringsamples);
//				float pw = (cos(float(j) * step) * float(i));
//				float ph = (sin(float(j) * step) * float(i));
//				float p = 1.0;
//                
//				if (pentagon) {
//					p = penta(vec2(pw, ph));
//				}
//                
//				col += color(gl_TexCoord[0].xy + vec2(pw * w, ph * h), blur) * mix(1.0, (float(i)) / (float(rings)), bias) * p;
//				s += 1.0 * mix(1.0, (float(i)) / (float(rings)), bias) * p;
//			}
//		}
//        
//        //divide by sample count
//		col /= s;
//	}
    
	
//	if (showFocus) {
//		col = debugFocus(col, blur, depth);
//	}
    
//    gl_FragColor = vec4(col.rgb, 1.0);
	
    //ビネット
//	if (vignetting) {
//		col *= vignette();
//	}
	
	gl_FragColor.rgb = col;
	gl_FragColor.a = 1.0;
    
//    depth = texture2D(bgl_DepthTexture, gl_TexCoord[0].xy).a * 1000.0;
//    gl_FragColor = vec4(depth, depth, depth, 1.0);

//    gl_FragColor = texture2D(bgl_RenderedTexture, v_texCoord.xy);
//    gl_FragColor = texture2D(bgl_DepthTexture, v_texCoord.xy);
}