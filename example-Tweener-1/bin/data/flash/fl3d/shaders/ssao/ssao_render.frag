#version 120

uniform sampler2DRect colortex;
uniform sampler2DRect normaltex;
uniform sampler2DRect depthtex;

uniform float minThreshold;
uniform float maxThreshold;
uniform float radius;
uniform vec2 randSeed;
uniform float nearClip;
uniform float farClip;

uniform vec3 samples[23];

float getDepth( in float d ) {
    return (2.0 * nearClip) / (farClip + nearClip - d * (farClip - nearClip));
}

float map(float value, float inputMin, float inputMax, float outputMin, float outputMax) {;
	return ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);
}

float rand(vec2 n){
    return 0.6 + 0.5 *fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}

void main(void)
{
    vec4 basecolor = texture2DRect( colortex, gl_TexCoord[0].st );
    //vec4 xyzd = texture2DRect( depthtex, gl_TexCoord[0].st );
    //float depth = xyzd.a;
    float depth = getDepth( texture2DRect( depthtex, gl_TexCoord[0].st ).r );
    if( depth == 0. ){
        gl_FragColor = basecolor;
        return;
    }
    vec3 norm = texture2DRect( normaltex, gl_TexCoord[0].st ).xyz;
    float delta, mx, mn;
    float ao = 0.;
    float dscl = (1.-depth);
    dscl *= dscl;
    mx = maxThreshold * dscl;
    mn = minThreshold * dscl;
    float rad = radius * dscl;
    float rnd = 0.;
    vec3 ray;

    for(int i=0; i<16; i++){
        rnd = rand( gl_FragCoord.xy+randSeed+vec2(i*i));
        //ray = samples[i].zxy * rad * rnd;
        //ray = reflect( -samples[i], xyzd.xyz) * rad * rnd;
        ray = reflect( -samples[i], norm) * rad * rnd;
        delta = ( depth - mn - getDepth( texture2DRect( depthtex, gl_TexCoord[0].st + ray.xy).r ));
        ao += min( 1., ( delta > 0. ) ? delta/max( delta, mx) : (mx - delta)/mx );
    }

    gl_FragColor = basecolor*vec4( ao/16. );
    //for debugging the different textures
    //gl_FragColor = vec4( ao/16. );
    //gl_FragColor = vec4(norm, 1.0);
    //gl_FragColor = vec4(depth, 1.0);


}
