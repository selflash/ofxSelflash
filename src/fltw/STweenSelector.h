#pragma once

#include "ofMain.h"

#define EASE_LINEAR				 0

#define EASE_IN_QUAD			 1
#define EASE_OUT_QUAD			 2
#define EASE_IN_OUT_QUAD		 3

#define EASE_IN_CUBIC			 4
#define EASE_OUT_CUBIC			 5
#define EASE_IN_OUT_CUBIC		 6

#define EASE_IN_QUART			 7
#define EASE_OUT_QUART			 8
#define EASE_IN_OUT_QUART		 9

#define EASE_IN_QUINT			 10
#define EASE_OUT_QUINT			 11
#define EASE_IN_OUT_QUINT		 12

#define EASE_IN_SINE			 13
#define EASE_OUT_SINE			 14
#define EASE_IN_OUT_SINE		 15

#define EASE_IN_EXPO			 16
#define EASE_OUT_EXPO			 17
#define EASE_IN_OUT_EXPO		 18

#define EASE_IN_CIRC			 19
#define EASE_OUT_CIRC			 20
#define EASE_IN_OUT_CIRC		 21

#define EASE_IN_ELASTIC			 22
#define EASE_OUT_ELASTIC		 23
#define EASE_IN_OUT_ELASTIC		 24
#define EASE_OUT_IN_ELASTIC		 25

#define EASE_IN_BACK			 26
#define EASE_OUT_BACK			 27
#define	EASE_IN_OUT_BACK		 28
#define EASE_OUT_IN_BACK		 29

#define EASE_IN_BOUNCE			 30
#define EASE_OUT_BOUNCE			 31
#define EASE_IN_OUT_BOUNCE		 32
#define EASE_OUT_IN_BOUNCE		 33

namespace fltw {
    
    class STweenSelector {
        public:
            static float getValueEase(float $t, float $b, float $c, float $d, int $easeType = 0, float $p = 0, float $a = 0) {
                switch ($easeType) {
                    case EASE_LINEAR: return easeLinear($t, $b, $c, $d);
                        
                    case EASE_IN_QUAD: return easeInQuad($t, $b, $c, $d);
                    case EASE_OUT_QUAD: return easeOutQuad($t, $b, $c, $d);
                    case EASE_IN_OUT_QUAD: return easeInOutQuad($t, $b, $c, $d);
                        
                    case EASE_IN_CUBIC: return easeInCubic($t, $b, $c, $d);
                    case EASE_OUT_CUBIC: return easeOutCubic($t, $b, $c, $d);
                    case EASE_IN_OUT_CUBIC: return easeInOutCubic($t, $b, $c, $d);
                        
                    case EASE_IN_QUART: return easeInQuart($t, $b, $c, $d);
                    case EASE_OUT_QUART: return easeOutQuart($t, $b, $c, $d);
                    case EASE_IN_OUT_QUART: return easeInOutQuart($t, $b, $c, $d);
                        
                    case EASE_IN_QUINT: return easeInQuint($t, $b, $c, $d);
                    case EASE_OUT_QUINT: return easeOutQuint($t, $b, $c, $d);
                    case EASE_IN_OUT_QUINT: return easeInOutQuint($t, $b, $c, $d);
                        
                    case EASE_IN_SINE: return easeInSine($t, $b, $c, $d);
                    case EASE_OUT_SINE: return easeOutSine($t, $b, $c, $d);
                    case EASE_IN_OUT_SINE: return easeInOutSine($t, $b, $c, $d);
                        
                    case EASE_IN_EXPO: return easeInExpo($t, $b, $c, $d);
                    case EASE_OUT_EXPO: return easeOutExpo($t, $b, $c, $d);
                    case EASE_IN_OUT_EXPO: return easeInOutExpo($t, $b, $c, $d);
                        
                    case EASE_IN_CIRC: return easeInCirc($t, $b, $c, $d);
                    case EASE_OUT_CIRC: return easeOutCirc($t, $b, $c, $d);
                    case EASE_IN_OUT_CIRC: return easeInOutCirc($t, $b, $c, $d);
                        
                    case EASE_IN_ELASTIC: return easeInElastic($t, $b, $c, $d, $p, $a);
                    case EASE_OUT_ELASTIC: return easeOutElastic($t, $b, $c, $d, $p, $a);
                    case EASE_IN_OUT_ELASTIC: return easeInOutElastic($t, $b, $c, $d, $p, $a);
                    case EASE_OUT_IN_ELASTIC: return easeOutInElastic($t, $b, $c, $d, $p, $a);
                        
                    case EASE_IN_BACK: return easeInBack($t, $b, $c, $d, $p);
                    case EASE_OUT_BACK: return easeOutBack($t, $b, $c, $d, $p);
                    case EASE_IN_OUT_BACK: return easeInOutBack($t, $b, $c, $d, $p);
                    case EASE_OUT_IN_BACK: return easeOutInBack($t, $b, $c, $d, $p);
                        
                    case EASE_IN_BOUNCE: return easeInBounce($t, $b, $c, $d);
                    case EASE_OUT_BOUNCE: return easeOutBounce($t, $b, $c, $d);
                    case EASE_IN_OUT_BOUNCE: return easeInOutBounce($t, $b, $c, $d);
                    case EASE_OUT_IN_BOUNCE: return easeOutInBounce($t, $b, $c, $d);
                        
                    default: return easeLinear($t, $b, $c, $d); break;
                }
            }
            
        public:
            
            //--------------------------------------------------------------
            //
            inline static float easeLinear(float t, float b, float c, float d) {
                return c * t / d + b;
            }
            
            //==============================================================
            // QUAD
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInQuad(float $t, float $b, float $c, float $d) {
                return $c * ($t /= $d) * $t + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutQuad(float $t, float $b, float $c, float $d) {
                return - $c * ($t /= $d) * ($t-2.f) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutQuad(float $t, float $b, float $c, float $d) {
                if (($t /= $d / 2.f) < 1.f) return $c / 2.f * $t * $t + $b;
                return -$c / 2 * ((--$t) * ($t - 2.f) - 1.f) + $b;
            }
            
            //==============================================================
            // CUBIC
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInCubic(float $t, float $b, float $c, float $d) {
                return $c * pow(($t / $d), 3) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutCubic(float $t, float $b, float $c, float $d) {
                return $c * (pow($t / $d - 1.f, 3) + 1.f) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutCubic(float $t, float $b, float $c, float $d) {
                if ( ($t /= $d / 2) < 1.f) return $c / 2.f * pow($t, 3) + $b;
                return $c / 2.f * (pow($t - 2.f, 3) + 2.f) + $b;
            }
            
            //==============================================================
            // QUART
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInQuart(float $t, float $b, float $c, float $d) {
                return $c * pow($t / $d, 4) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutQuart(float $t, float $b, float $c, float $d) {
                return -$c * (pow($t / $d-1, 4) - 1.f) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutQuart(float $t, float $b, float $c, float $d) {
                if ( ($t /= $d / 2.f) < 1.f) return $c / 2.f * pow($t, 4) + $b;
                return -$c / 2.f * (pow($t - 2, 4) -2.f) + $b;
            }
            
            //==============================================================
            // QUINT
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInQuint(float $t, float $b, float $c, float $d) {
                return $c * pow($t / $d, 5) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutQuint(float $t, float $b, float $c, float $d) {
                return $c * (pow($t / $d - 1, 5) + 1.f) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutQuint(float $t, float $b, float $c, float $d) {
                if ( ($t /= $d / 2.f) < 1.f) return $c / 2 * pow($t, 5) + $b;
                return $c / 2 * (pow($t - 2.f, 5) + 2.f) + $b;
            }
            
            //==============================================================
            // SINE
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInSine(float $t, float $b, float $c, float $d) {
                return $c * (1.f - cos($t / $d * HALF_PI)) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutSine(float $t, float $b, float $c, float $d) {
                return $c * sin($t / $d * HALF_PI) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutSine(float $t, float $b, float $c, float $d) {
                return $c / 2 * (1.f - cos(PI * $t / $d)) + $b;
            }
            
            //==============================================================
            // EXPO
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInExpo(float $t, float $b, float $c, float $d) {
                return $c * pow(2.f, 10.f * ($t / $d - 1.f)) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutExpo(float $t, float $b, float $c, float $d) {
                return $c * (-pow(2.f, -10.f * $t / $d) + 1.f) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutExpo(float $t, float $b, float $c, float $d) {
                if ( ($t /= $d / 2.f) < 1.f) return $c / 2 * pow(2.f, 10.f * ($t - 1.f)) + $b;
                return $c / 2 * (-pow(2.f, -10.f * --$t) + 2.f) + $b;
            }
            
            //==============================================================
            // CIRC
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInCirc(float $t, float $b, float $c, float $d) {
                return $c * (1.f - sqrt(1.f - ($t /= $d) * $t)) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutCirc(float $t, float $b, float $c, float $d) {
                return $c * sqrt(1.f - ($t = $t / $d - 1.f) * $t) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutCirc(float $t, float $b, float $c, float $d) {
                if ( ($t /= $d / 2.f) < 1.f) return $c / 2.f * (1.f - sqrt(1.f - $t * $t)) + $b;
                return $c / 2.f * (sqrt(1.f - ($t -= 2.f) * $t) + 1.f) + $b;
            }
            
            /**
             * Equations
             * Main equations for the ofxSTweener class
             *
             * @author		Zeh Fernando, Nate Chatellier, Arthur Debert
             * @version		1.0.2
             * http://code.google.com/p/ofxSTweener/
             */
            
            //==============================================================
            // ELASTIC
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInElastic(float $t, float $b, float $c, float $d, float $p = 0, float $a = 0) {
                if ($t == 0) return $b;
                if (($t /= $d) == 1) return $b + $c;
                $p = $p == 0 ? $d * .3 : $p;
                float $s;
                //float a = !Boolean(p_params) || isNaN(p_params.amplitude) ? 0 : p_params.amplitude;
                float $a_c = $c < 0 ? $c * - 1 : $c;
                if (!($a) || $a < $a_c) {
                    $a = $c;
                    $s = $p / 4;
                } else {
                    $s = $p / (2 * PI) * asin ($c / $a);
                }
                return -($a * pow(2, 10 * ($t -= 1)) * sin(($t * $d - $s) * (2 * PI) / $p)) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutElastic(float $t, float $b, float $c, float $d, float $p = 0, float $a = 0) {
                if ($t == 0) return $b;
                if (($t /= $d) == 1) return $b + $c;
                //float p = !Boolean(p_params) || isNaN(p_params.period) ? d*.3 : p_params.period;
                $p = $p == 0 ? $d * .3 : $p;
                float $s;
                //float a = !Boolean(p_params) || isNaN(p_params.amplitude) ? 0 : p_params.amplitude;
                float $a_c = $c < 0 ? $c * - 1 : $c;
                if (!($a) || $a < $a_c) {
                    $a = $c;
                    $s = $p / 4;
                } else {
                    $s = $p / (2 * PI) * asin ($c / $a);
                }
                return ($a * pow(2, -10 * $t) * sin(($t * $d - $s) * (2 * PI) / $p) + $c + $b);
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutElastic(float $t, float $b, float $c, float $d, float $p = 0, float $a = 0) {
                if ($t == 0) return $b;
                if (($t /= $d / 2) == 2) return $b + $c;
                //var p:Number = !Boolean(p_params) || isNaN(p_params.period) ? d*(.3*1.5) : p_params.period;
                $p = $p == 0 ? $d * (.3 * 1.5) : $p;
                float $s;
                //var a:Number = !Boolean(p_params) || isNaN(p_params.amplitude) ? 0 : p_params.amplitude;
                float $a_c = $c < 0 ? $c * - 1 : $c;
                if (!($a) || $a < $a_c) {
                    $a = $c;
                    $s = $p / 4;
                } else {
                    $s = $p / (2 * PI) * asin ($c / $a);
                }
                if ($t < 1) return -.5 * ($a * pow(2, 10 * ($t -= 1)) * sin(($t * $d - $s) * (2 * PI) / $p)) + $b;
                return $a*pow(2, -10 * ($t -= 1)) * sin(($t * $d - $s) * (2 * PI) / $p) *.5 + $c + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutInElastic(float $t, float $b, float $c, float $d, float $p = 0, float $a = 0) {
                if ($t < $d / 2) return easeOutElastic ($t * 2, $b, $c / 2, $d, $p, $a);
                return easeInElastic(($t * 2) - $d, $b + $c / 2, $c / 2, $d, $p, $a);
            }
            
            //==============================================================
            // BACK
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInBack(float $t, float $b, float $c, float $d, float $p = 0) {
                // var s:Number = !Boolean(p_params) || isNaN(p_params.overshoot) ? 1.70158 : p_params.overshoot;
                $p = $p == 0 ? 1.70158 : $p;
                return $c * ($t /= $d) * $t *(($p + 1) * $t - $p) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutBack(float $t, float $b, float $c, float $d, float $p = 0) {
                //var s:Number = !Boolean(p_params) || isNaN(p_params.overshoot) ? 1.70158 : p_params.overshoot;
                $p = $p == 0 ? 1.70158 : $p;
                return $c * (($t = $t / $d - 1) * $t * (($p + 1) * $t + $p) + 1) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutBack(float $t, float $b, float $c, float $d, float $p = 0) {
                //var s:Number = !Boolean(p_params) || isNaN(p_params.overshoot) ? 1.70158 : p_params.overshoot;
                $p = $p == 0 ? 1.70158 : $p;
                if (($t /= $d / 2) < 1) return $c / 2 * ($t * $t * ((($p *= (1.525)) + 1) * $t - $p)) + $b;
                return $c / 2 * (($t -= 2) * $t * ((($p *= (1.525)) + 1) * $t + $p) + 2) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutInBack(float $t, float $b, float $c, float $d, float $p = 0) {
                if ($t < $d / 2) return easeOutBack($t * 2, $b, $c /2 , $d, $p);
                return easeInBack(($t * 2) - $d, $b + $c / 2, $c / 2, $d, $p);
            }
            
            //==============================================================
            // BOUNCE
            //==============================================================
            
            //--------------------------------------------------------------
            //
            inline static float easeInBounce(float $t, float $b, float $c, float $d) {
                return $c - easeOutBounce ($d - $t, 0, $c, $d) + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutBounce(float $t, float $b, float $c, float $d) {
                if (($t /= $d) < (1 / 2.75)) {
                    return $c * (7.5625 * $t * $t) + $b;
                } else if ($t < (2 / 2.75)) {
                    return $c * (7.5625 * ($t -=(1.5 / 2.75)) * $t + .75) + $b;
                } else if ($t < (2.5 / 2.75)) {
                    return $c * (7.5625 * ($t -= (2.25 / 2.75)) * $t + .9375) + $b;
                } else {
                    return $c*(7.5625 * ($t -= (2.625 / 2.75)) * $t + .984375) + $b;
                }
            }
            //--------------------------------------------------------------
            //
            inline static float easeInOutBounce(float $t, float $b, float $c, float $d) {
                if ($t < $d / 2) return easeInBounce ($t * 2, 0, $c, $d) * .5 + $b;
                else return easeOutBounce ($t * 2 - $d, 0, $c, $d) * .5 + $c * .5 + $b;
            }
            //--------------------------------------------------------------
            //
            inline static float easeOutInBounce(float $t, float $b, float $c, float $d) {
                if ($t < $d / 2) return easeOutBounce ($t * 2, $b, $c / 2, $d);
                return easeInBounce(($t * 2) - $d, $b + $c / 2, $c / 2, $d);
            }
        };

}