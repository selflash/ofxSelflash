#include "BlendMode.h"

namespace fl2d {
    
    string BlendMode::ADD = "add";
    string BlendMode::ALPHA = "alpha";
    string BlendMode::ALPHA_TEST = "alphaTest";
    string BlendMode::DARKEN = "darken";
    string BlendMode::DIFFERENCE_ = "difference";
    string BlendMode::ERASE = "erase";
    string BlendMode::HARDLIGHT = "hardlight";
    string BlendMode::INVERT = "invert";
    string BlendMode::LAYER = "layer";
    string BlendMode::LIGHTEN = "lighten";
    string BlendMode::MULTIPLY = "multiply";
    string BlendMode::NORMAL = "normal";
    string BlendMode::OVERLAY = "overlay";
    string BlendMode::SCREEN = "screen";
    string BlendMode::SHADER = "shader";
    string BlendMode::SUBTRACT = "subtract";
    
    ofFbo* BlendMode::_base = NULL;
    ofShader* BlendMode::_blendShader = NULL;
    int BlendMode::_width = 0;
    int BlendMode::_height = 0;
    
    //--------------------------------------------------------------
    //
    void BlendMode::enable(string value) {
        glPushAttrib(GL_ALL_ATTRIB_BITS);

        if(value == BlendMode::NORMAL) {
//            glEnable(GL_BLEND);
//            glBlendFunc(GL_ONE, GL_ZERO);
        }
        
        if(value == BlendMode::ADD) {
            glEnable(GL_BLEND);
//        glBlendFuncSeparate(GL_ZERO, GL_SRC_COLOR, GL_SRC_ALPHA, GL_ONE);
            glBlendFuncSeparate(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE);
        }
        if(value == BlendMode::ALPHA) {
            glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE);
            glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        if(value == BlendMode::ALPHA_TEST) {
//            glAlphaFunc(GL_GEQUAL, 0.1);
            glAlphaFunc(GL_GEQUAL, 1.0);
            glEnable(GL_ALPHA_TEST);
        }
        if(value == BlendMode::DARKEN) {
            
        }
        if(value == BlendMode::DIFFERENCE_) {
            
        }
        if(value == BlendMode::ERASE) {
            
        }
        if(value == BlendMode::HARDLIGHT) {
            
        }
        if(value == BlendMode::INVERT) {
            
        }
        if(value == BlendMode::LAYER) {
            
        }
        if(value == BlendMode::LIGHTEN) {
            
        }
        if(value == BlendMode::MULTIPLY) {
            
        }
        if(value == BlendMode::OVERLAY) {
            
        }
        if(value == BlendMode::SCREEN) {
            
        }
        if(value == BlendMode::SHADER) {
            
        }
        if(value == BlendMode::SUBTRACT) {
            
        }
    }
    
    //--------------------------------------------------------------
    //ブレンドモード無効
    void BlendMode::disable() {
        glDisable(GL_ALPHA_TEST);
        
        glBlendFunc(GL_ONE, GL_ZERO);
        glDisable(GL_BLEND);
        
        glPopAttrib();
    }
    
    
    
    
    //--------------------------------------------------------------
    //
    void BlendMode::setup(int width, int height) {
        _base = new ofFbo();
        _base->allocate(width, height, GL_RGBA, ofFbo::maxSamples());
        
        _loadShader();
    }
    
    //--------------------------------------------------------------
    //
	void BlendMode::draw(ofTexture& blendTgt, int blendMode, int x, int y) {
        _blendShader->begin();
        _blendShader->setUniformTexture("base", _base->getTexture(), 1);
        _blendShader->setUniform1i("blendTgt", 0);
        _blendShader->setUniform1i("mode", blendMode);
        
        ofEnableAlphaBlending();
        blendTgt.draw(x, y);
        
        _blendShader->end();
	}
    
    //--------------------------------------------------------------
    //
	void BlendMode::draw(ofTexture& blendTgt, int blendMode, int x, int y, int width, int height) {
        _blendShader->begin();
        _blendShader->setUniformTexture("base", _base->getTexture(), 1);
        _blendShader->setUniform1i("blendTgt", 0);
        _blendShader->setUniform1i("mode", blendMode);
        
        ofEnableAlphaBlending();
        blendTgt.draw(x, y, width, height);
        
        _blendShader->end();
	}
    
    //--------------------------------------------------------------
    //
    void BlendMode::resize(int width, int height) {
        _base->allocate(width, height, GL_RGBA, ofFbo::maxSamples());
    }
    
    //--------------------------------------------------------------
    //
    void BlendMode::begin() {
        ofPushStyle();
        ofPushMatrix();
        
        _base->begin();
        ofClear(0);
    }
    
    //--------------------------------------------------------------
    //
    void BlendMode::end() {
        _base->end();
        
        ofPopStyle();
        ofPopMatrix();
    }
    
    //--------------------------------------------------------------
    //
    string BlendMode::blendMode(int blendMode) {
        string blendName = "no such blend hiii";
        
        switch(blendMode) {
            case  0: blendName = "BlendAlpha"; break;
            case  1: blendName = "BlendMultiply"; break;
            case  2: blendName = "BlendAverage"; break;
            case  3: blendName = "BlendAdd"; break;
            case  4: blendName = "BlendSubstract"; break;
            case  5: blendName = "BlendDifference"; break;
            case  6: blendName = "BlendNegation"; break;
            case  7: blendName = "BlendExclusion"; break;
            case  8: blendName = "BlendScreen"; break;
            case  9: blendName = "BlendOverlay"; break;
            case 10: blendName = "BlendSoftLight"; break;
            case 11: blendName = "BlendHardLight"; break;
            case 12: blendName = "BlendColorDodge"; break;
            case 13: blendName = "BlendColorBurn"; break;
            case 14: blendName = "BlendLinearLight"; break;
            case 15: blendName = "BlendVividLight"; break;
            case 16: blendName = "BlendPinLight"; break;
            case 17: blendName = "BlendHardMix"; break;
            case 18: blendName = "BlendReflect"; break;
            case 19: blendName = "BlendGlow"; break;
            case 20: blendName = "BlendPhoenix"; break;
            case 21: blendName = "BlendHue"; break;
            case 22: blendName = "BlendSaturation"; break;
            case 23: blendName = "BlendColor"; break;
            case 24: blendName = "BlendLuminosity"; break;
            default: blendName = "BlendNormal"; break;
        }
        
        return blendName;
    }
    
    //--------------------------------------------------------------
    //
//    string BlendMode::_getFragmentProgramGL3() {
//        string fragmentProgram = "#version 150\n \
//        \n \
//        out vec4 outputColor;\n \
//        #define BlendLinearDodgef BlendAddf\n \
//        #define BlendLinearBurnf BlendSubstractf\n \
//        #define BlendAddf(base, blend) min(base + blend, 1.0)\n \
//        #define BlendSubstractf(base, blend) max(base + blend - 1.0, 0.0)\n \
//        #define BlendLightenf(base, blend) max(blend, base)\n \
//        #define BlendDarkenf(base, blend) min(blend, base)\n \
//        #define BlendLinearLightf(base, blend) (blend < 0.5 ? BlendLinearBurnf(base, (2.0 * blend)) : BlendLinearDodgef(base, (2.0 * (blend - 0.5))))\n \
//        #define BlendScreenf(base, blend) (1.0 - ((1.0 - base) * (1.0 - blend)))\n \
//        #define BlendOverlayf(base, blend) (base < 0.5 ? (2.0 * base * blend) : (1.0 - 2.0 * (1.0 - base) * (1.0 - blend)))\n \
//        #define BlendSoftLightf(base, blend) ((blend < 0.5) ? (2.0 * base * blend + base * base * (1.0 - 2.0 * blend)) : (sqrt(base) * (2.0 * blend - 1.0) + 2.0 * base * (1.0 - blend)))\n \
//        #define BlendColorDodgef(base, blend) ((blend == 1.0) ? blend : min(base / (1.0 - blend), 1.0))\n \
//        #define BlendColorBurnf(base, blend) ((blend == 0.0) ? blend : max((1.0 - ((1.0 - base) / blend)), 0.0))\n \
//        #define BlendVividLightf(base, blend) ((blend < 0.5) ? BlendColorBurnf(base, (2.0 * blend)) : BlendColorDodgef(base, (2.0 * (blend - 0.5))))\n \
//        #define BlendPinLightf(base, blend) ((blend < 0.5) ? BlendDarkenf(base, (2.0 * blend)) : BlendLightenf(base, (2.0 *(blend - 0.5))))\n \
//        #define BlendHardMixf(base, blend) ((BlendVividLightf(base, blend) < 0.5) ? 0.0 : 1.0)\n \
//        #define BlendReflectf(base, blend) ((blend == 1.0) ? blend : min(base * base / (1.0 - blend), 1.0))\n \
//        #define Blend(base, blend, funcf) vec3(funcf(base.r, blend.r), funcf(base.g, blend.g), funcf(base.b, blend.b))\n \
//        #define BlendLightenBlendLightenf\n \
//        #define BlendDarkenBlendDarkenf\n \
//        #define BlendNormal(base, blend) (blend)\n \
//        #define BlendMultiply(base, blend) (base * blend)\n \
//        #define BlendAverage(base, blend) ((base + blend) / 2.0)\n \
//        #define BlendAdd(base, blend) min(base + blend, vec3(1.0))\n \
//        #define BlendSubstract(base, blend) max(base + blend - vec3(1.0), vec3(0.0))\n \
//        #define BlendDifference(base, blend) abs(base - blend)\n \
//        #define BlendNegation(base, blend) (vec3(1.0) - abs(vec3(1.0) - base - blend))\n \
//        #define BlendExclusion(base, blend) (base + blend - 2.0 * base * blend)\n \
//        #define BlendScreen(base, blend) Blend(base, blend, BlendScreenf)\n \
//        #define BlendOverlay(base, blend) Blend(base, blend, BlendOverlayf)\n \
//        #define BlendSoftLight(base, blend) Blend(base, blend, BlendSoftLightf)\n \
//        #define BlendHardLight(base, blend) BlendOverlay(blend, base)\n \
//        #define BlendColorDodge(base, blend) Blend(base, blend, BlendColorDodgef)\n \
//        #define BlendColorBurn(base, blend) Blend(base, blend, BlendColorBurnf)\n \
//        #define BlendLinearDodgeBlendAdd\n \
//        #define BlendLinearBurnBlendSubstract\n \
//        #define BlendLinearLight(base, blend) Blend(base, blend, BlendLinearLightf)\n \
//        #define BlendVividLight(base, blend) Blend(base, blend, BlendVividLightf)\n \
//        #define BlendPinLight(base, blend) Blend(base, blend, BlendPinLightf)\n \
//        #define BlendHardMix(base, blend) Blend(base, blend, BlendHardMixf)\n \
//        #define BlendReflect(base, blend) Blend(base, blend, BlendReflectf)\n \
//        #define BlendGlow(base, blend) BlendReflect(blend, base)\n \
//        #define BlendPhoenix(base, blend) (min(base, blend) - max(base, blend) + vec3(1.0))\n \
//        #define BlendOpacity(base, blend, F, O) (F(base, blend) * O + blend * (1.0 - O))\n \
//        #define BlendAlpha(base, blend, O) ((base * (1.0 - O)) + blend * O)\n \
//        #define GammaCorrection(color, gamma)pow(color, 1.0 / gamma)\n \
//        #define LevelsControlInputRange(color, minInput, maxInput)min(max(color - vec3(minInput), vec3(0.0)) / (vec3(maxInput) - vec3(minInput)), vec3(1.0))\n \
//        #define LevelsControlInput(color, minInput, gamma, maxInput)GammaCorrection(LevelsControlInputRange(color, minInput, maxInput), gamma)\n \
//        #define LevelsControlOutputRange(color, minOutput, maxOutput) mix(vec3(minOutput), vec3(maxOutput), color)\n \
//        #define LevelsControl(color, minInput, gamma, maxInput, minOutput, maxOutput) LevelsControlOutputRange(LevelsControlInput(color, minInput, gamma, maxInput), minOutput, maxOutput)\n \
//        \n \
//        vec4 Desaturate(vec3 color, float Desaturation) {\n \
//            vec3 grayXfer = vec3(0.3, 0.59, 0.11);\n \
//            vec3 gray = vec3(dot(grayXfer, color));\n \
//            return vec4(mix(color, gray, Desaturation), 1.0);\n \
//        }\n \
//        \n \
//        vec3 RGBToHSL(vec3 color) {\n \
//            vec3 hsl;\n \
//            float fmin = min(min(color.r, color.g), color.b);\n \
//            float fmax = max(max(color.r, color.g), color.b);\n \
//            float delta = fmax - fmin;\n \
//            hsl.z = (fmax + fmin) / 2.0;\n \
//            if (delta == 0.0) {\n \
//                hsl.x = 0.0;\n \
//                hsl.y = 0.0;\n \
//            } else {\n \
//                if (hsl.z < 0.5) {\n \
//                    hsl.y = delta / (fmax + fmin);\n \
//                } else {\n \
//                    hsl.y = delta / (2.0 - fmax - fmin);\n \
//                    float deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;\n \
//                    float deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;\n \
//                    float deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;\n \
//                    if (color.r == fmax) {\n \
//                        hsl.x = deltaB - deltaG;\n \
//                    } else if (color.g == fmax) {\n \
//                        hsl.x = (1.0 / 3.0) + deltaR - deltaB;\n \
//                    } else if (color.b == fmax) {\n \
//                        hsl.x = (2.0 / 3.0) + deltaG - deltaR;\n \
//                    }\n \
//                if (hsl.x < 0.0) {\n \
//                    hsl.x += 1.0;\n \
//                } else if (hsl.x > 1.0) {\n \
//                    hsl.x -= 1.0;\n \
//                }\n \
//            }\n \
//            return hsl;\n \
//        }\n \
//        \n \
//        float HueToRGB(float f1, float f2, float hue) {\n \
//            if (hue < 0.0) {\n \
//                hue += 1.0;\n \
//            } else if (hue > 1.0) {\n \
//                hue -= 1.0;\n \
//                float res;\n \
//            }\n \
//            if ((6.0 * hue) < 1.0) {\n \
//                res = f1 + (f2 - f1) * 6.0 * hue;\n \
//            } else if ((2.0 * hue) < 1.0) {\n \
//                res = f2;\n \
//            } else if ((3.0 * hue) < 2.0) {\n \
//                res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;\n \
//            } else {\n \
//                res = f1;\n \
//            }\n \
//            return res;\n \
//        }\n \
//        \n \
//        vec3 HSLToRGB(vec3 hsl)\n \
//        {\n \
//        vec3 rgb;\n \
//        if (hsl.y == 0.0)\n \
//        rgb = vec3(hsl.z);\n \
//        else\n \
//        {\n \
//        float f2;\n \
//        if (hsl.z < 0.5)\n \
//        f2 = hsl.z * (1.0 + hsl.y);\n \
//        else\n \
//        f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);\n \
//        float f1 = 2.0 * hsl.z - f2;\n \
//        rgb.r = HueToRGB(f1, f2, hsl.x + (1.0/3.0));\n \
//        rgb.g = HueToRGB(f1, f2, hsl.x);\n \
//        rgb.b= HueToRGB(f1, f2, hsl.x - (1.0/3.0));\n \
//        }\n \
//        return rgb;\n \
//        }\n \
//        \n \
//        vec3 ContrastSaturationBrightness(vec3 color, float brt, float sat, float con)\n \
//        {\n \
//        const float AvgLumR = 0.5;\n \
//        const float AvgLumG = 0.5;\n \
//        const float AvgLumB = 0.5;\n \
//        const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);\n \
//        vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);\n \
//        vec3 brtColor = color * brt;\n \
//        vec3 intensity = vec3(dot(brtColor, LumCoeff));\n \
//        vec3 satColor = mix(intensity, brtColor, sat);\n \
//        vec3 conColor = mix(AvgLumin, satColor, con);\n \
//        return conColor;\n \
//        }\n \
//        \n \
//        vec3 BlendHue(vec3 base, vec3 blend)\n \
//        {\n \
//        vec3 baseHSL = RGBToHSL(base);\n \
//        return HSLToRGB(vec3(RGBToHSL(blend).r, baseHSL.g, baseHSL.b));\n \
//        }\n \
//        \n \
//        vec3 BlendSaturation(vec3 base, vec3 blend)\n \
//        {\n \
//        vec3 baseHSL = RGBToHSL(base);\n \
//        return HSLToRGB(vec3(baseHSL.r, RGBToHSL(blend).g, baseHSL.b));\n \
//        }\n \
//        \n \
//        vec3 BlendColor(vec3 base, vec3 blend)\n \
//        {\n \
//        vec3 blendHSL = RGBToHSL(blend);\n \
//        return HSLToRGB(vec3(blendHSL.r, blendHSL.g, RGBToHSL(base).b));\n \
//        }\n \
//        \n \
//        vec3 BlendLuminosity(vec3 base, vec3 blend)\n \
//        {\n \
//        vec3 baseHSL = RGBToHSL(base);\n \
//        return HSLToRGB(vec3(baseHSL.r, baseHSL.g, RGBToHSL(blend).b));\n \
//        }\n \
//        \n \
//        uniform sampler2D base;\n \
//        uniform sampler2D blendTgt;\n \
//        uniform int mode;\n \
//        \n \
//        void main()\n \
//        {\n \
//        vec4 baseCol = texture(base, gl_TexCoord[0].st);\n \
//        vec4 blendCol = texture(blendTgt, gl_TexCoord[0].st);\n \
//        \n \
//        vec3 result;\n \
//        if (mode == 0)\n \
//        {\n \
//        result = BlendAlpha(baseCol.rgb, blendCol.rgb, blendCol.a);\n \
//        }\n \
//        else if (mode == 1)\n \
//        {\n \
//        result = BlendMultiply(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 2)\
//        {\
//        result = BlendAverage(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 3)\
//        {\
//        result = BlendAdd(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 4)\
//        {\
//        result = BlendSubstract(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 5)\
//        {\
//        result = BlendDifference(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 6)\
//        {\
//        result = BlendNegation(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 7)\
//        {\
//        result = BlendExclusion(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 8)\
//        {\
//        result = BlendScreen(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 9)\
//        {\
//        result = BlendOverlay(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 10)\
//        {\
//        result = BlendSoftLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 11)\
//        {\
//        result = BlendHardLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 12)\
//        {\
//        result = BlendColorDodge(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 13)\
//        {\
//        result = BlendColorBurn(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 14)\
//        {\
//        result = BlendLinearLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 15)\
//        {\
//        result = BlendVividLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 16)\
//        {\
//        result = BlendPinLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 17)\
//        {\
//        result = BlendHardMix(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 18)\
//        {\
//        result = BlendReflect(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 19)\
//        {\
//        result = BlendGlow(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 20)\
//        {\
//        result = BlendPhoenix(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 21)\
//        {\
//        result = BlendHue(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 22)\
//        {\
//        result = BlendSaturation(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 23)\
//        {\
//        result = BlendColor(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 24)\
//        {\
//        result = BlendLuminosity(baseCol.rgb, blendCol.rgb);\
//        }\
//        else\
//        {\
//        result = BlendNormal(baseCol.rgb, blendCol.rgb);\
//        }\
//        \
//        outputColor = vec4(result, baseCol.a + blendCol.a);\
//        }\
//        ";
//        
//        return fragmentProgram;
//    }
    
    //--------------------------------------------------------------
    //
//    string BlendMode::_getFragmentProgramGL2() {
//        string fragmentProgram = "#version 120\n \
//        #extension GL_ARB_texture_rectangle : enable\n \
//        \
//        #define BlendLinearDodgef BlendAddf\n \
//        #define BlendLinearBurnf BlendSubstractf\n \
//        #define BlendAddf(base, blend) min(base + blend, 1.0)\n \
//        #define BlendSubstractf(base, blend) max(base + blend - 1.0, 0.0)\n \
//        #define BlendLightenf(base, blend) max(blend, base)\n \
//        #define BlendDarkenf(base, blend) min(blend, base)\n \
//        #define BlendLinearLightf(base, blend) (blend < 0.5 ? BlendLinearBurnf(base, (2.0 * blend)) : BlendLinearDodgef(base, (2.0 * (blend - 0.5))))\n \
//        #define BlendScreenf(base, blend) (1.0 - ((1.0 - base) * (1.0 - blend)))\n \
//        #define BlendOverlayf(base, blend) (base < 0.5 ? (2.0 * base * blend) : (1.0 - 2.0 * (1.0 - base) * (1.0 - blend)))\n \
//        #define BlendSoftLightf(base, blend) ((blend < 0.5) ? (2.0 * base * blend + base * base * (1.0 - 2.0 * blend)) : (sqrt(base) * (2.0 * blend - 1.0) + 2.0 * base * (1.0 - blend)))\n \
//        #define BlendColorDodgef(base, blend) ((blend == 1.0) ? blend : min(base / (1.0 - blend), 1.0))\n \
//        #define BlendColorBurnf(base, blend) ((blend == 0.0) ? blend : max((1.0 - ((1.0 - base) / blend)), 0.0))\n \
//        #define BlendVividLightf(base, blend) ((blend < 0.5) ? BlendColorBurnf(base, (2.0 * blend)) : BlendColorDodgef(base, (2.0 * (blend - 0.5))))\n \
//        #define BlendPinLightf(base, blend) ((blend < 0.5) ? BlendDarkenf(base, (2.0 * blend)) : BlendLightenf(base, (2.0 *(blend - 0.5))))\n \
//        #define BlendHardMixf(base, blend) ((BlendVividLightf(base, blend) < 0.5) ? 0.0 : 1.0)\n \
//        #define BlendReflectf(base, blend) ((blend == 1.0) ? blend : min(base * base / (1.0 - blend), 1.0))\n \
//        #define Blend(base, blend, funcf) vec3(funcf(base.r, blend.r), funcf(base.g, blend.g), funcf(base.b, blend.b))\n \
//        #define BlendLightenBlendLightenf\n \
//        #define BlendDarkenBlendDarkenf\n \
//        #define BlendNormal(base, blend) (blend)\n \
//        #define BlendMultiply(base, blend) (base * blend)\n \
//        #define BlendAverage(base, blend) ((base + blend) / 2.0)\n \
//        #define BlendAdd(base, blend) min(base + blend, vec3(1.0))\n \
//        #define BlendSubstract(base, blend) max(base + blend - vec3(1.0), vec3(0.0))\n \
//        #define BlendDifference(base, blend) abs(base - blend)\n \
//        #define BlendNegation(base, blend) (vec3(1.0) - abs(vec3(1.0) - base - blend))\n \
//        #define BlendExclusion(base, blend) (base + blend - 2.0 * base * blend)\n \
//        #define BlendScreen(base, blend) Blend(base, blend, BlendScreenf)\n \
//        #define BlendOverlay(base, blend) Blend(base, blend, BlendOverlayf)\n \
//        #define BlendSoftLight(base, blend) Blend(base, blend, BlendSoftLightf)\n \
//        #define BlendHardLight(base, blend) BlendOverlay(blend, base)\n \
//        #define BlendColorDodge(base, blend) Blend(base, blend, BlendColorDodgef)\n \
//        #define BlendColorBurn(base, blend) Blend(base, blend, BlendColorBurnf)\n \
//        #define BlendLinearDodgeBlendAdd\n \
//        #define BlendLinearBurnBlendSubstract\n \
//        #define BlendLinearLight(base, blend) Blend(base, blend, BlendLinearLightf)\n \
//        #define BlendVividLight(base, blend) Blend(base, blend, BlendVividLightf)\n \
//        #define BlendPinLight(base, blend) Blend(base, blend, BlendPinLightf)\n \
//        #define BlendHardMix(base, blend) Blend(base, blend, BlendHardMixf)\n \
//        #define BlendReflect(base, blend) Blend(base, blend, BlendReflectf)\n \
//        #define BlendGlow(base, blend) BlendReflect(blend, base)\n \
//        #define BlendPhoenix(base, blend) (min(base, blend) - max(base, blend) + vec3(1.0))\n \
//        #define BlendOpacity(base, blend, F, O) (F(base, blend) * O + blend * (1.0 - O))\n \
//        #define BlendAlpha(base, blend, O) ((base * (1.0 - O)) + blend * O)\n \
//        #define GammaCorrection(color, gamma)pow(color, 1.0 / gamma)\n \
//        #define LevelsControlInputRange(color, minInput, maxInput)min(max(color - vec3(minInput), vec3(0.0)) / (vec3(maxInput) - vec3(minInput)), vec3(1.0))\n \
//        #define LevelsControlInput(color, minInput, gamma, maxInput)GammaCorrection(LevelsControlInputRange(color, minInput, maxInput), gamma)\n \
//        #define LevelsControlOutputRange(color, minOutput, maxOutput) mix(vec3(minOutput), vec3(maxOutput), color)\n \
//        #define LevelsControl(color, minInput, gamma, maxInput, minOutput, maxOutput) LevelsControlOutputRange(LevelsControlInput(color, minInput, gamma, maxInput), minOutput, maxOutput)\n \
//        \
//        vec4 Desaturate(vec3 color, float Desaturation)\
//        {\
//        vec3 grayXfer = vec3(0.3, 0.59, 0.11);\
//        vec3 gray = vec3(dot(grayXfer, color));\
//        return vec4(mix(color, gray, Desaturation), 1.0);\
//        }\
//        \
//        vec3 RGBToHSL(vec3 color)\
//        {\
//        vec3 hsl;\
//        float fmin = min(min(color.r, color.g), color.b);\
//        float fmax = max(max(color.r, color.g), color.b);\
//        float delta = fmax - fmin;\
//        hsl.z = (fmax + fmin) / 2.0;\
//        if (delta == 0.0)\
//        {\
//        hsl.x = 0.0;\
//        hsl.y = 0.0;\
//        }\
//        else\
//        {\
//        if (hsl.z < 0.5)\
//        hsl.y = delta / (fmax + fmin);\
//        else\
//        hsl.y = delta / (2.0 - fmax - fmin);\
//        float deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;\
//        float deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;\
//        float deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;\
//        if (color.r == fmax )\
//        hsl.x = deltaB - deltaG;\
//        else if (color.g == fmax)\
//        hsl.x = (1.0 / 3.0) + deltaR - deltaB;\
//        else if (color.b == fmax)\
//        hsl.x = (2.0 / 3.0) + deltaG - deltaR;\
//        if (hsl.x < 0.0)\
//        hsl.x += 1.0;\
//        else if (hsl.x > 1.0)\
//        hsl.x -= 1.0;\
//        }\
//        return hsl;\
//        }\
//        \
//        float HueToRGB(float f1, float f2, float hue)\
//        {\
//        if (hue < 0.0)\
//        hue += 1.0;\
//        else if (hue > 1.0)\
//        hue -= 1.0;\
//        float res;\
//        if ((6.0 * hue) < 1.0)\
//        res = f1 + (f2 - f1) * 6.0 * hue;\
//        else if ((2.0 * hue) < 1.0)\
//        res = f2;\
//        else if ((3.0 * hue) < 2.0)\
//        res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;\
//        else\
//        res = f1;\
//        return res;\
//        }\
//        \
//        vec3 HSLToRGB(vec3 hsl)\
//        {\
//        vec3 rgb;\
//        if (hsl.y == 0.0)\
//        rgb = vec3(hsl.z);\
//        else\
//        {\
//        float f2;\
//        if (hsl.z < 0.5)\
//        f2 = hsl.z * (1.0 + hsl.y);\
//        else\
//        f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);\
//        float f1 = 2.0 * hsl.z - f2;\
//        rgb.r = HueToRGB(f1, f2, hsl.x + (1.0/3.0));\
//        rgb.g = HueToRGB(f1, f2, hsl.x);\
//        rgb.b= HueToRGB(f1, f2, hsl.x - (1.0/3.0));\
//        }\
//        return rgb;\
//        }\
//        \
//        vec3 ContrastSaturationBrightness(vec3 color, float brt, float sat, float con)\
//        {\
//        const float AvgLumR = 0.5;\
//        const float AvgLumG = 0.5;\
//        const float AvgLumB = 0.5;\
//        const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);\
//        vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);\
//        vec3 brtColor = color * brt;\
//        vec3 intensity = vec3(dot(brtColor, LumCoeff));\
//        vec3 satColor = mix(intensity, brtColor, sat);\
//        vec3 conColor = mix(AvgLumin, satColor, con);\
//        return conColor;\
//        }\
//        \
//        vec3 BlendHue(vec3 base, vec3 blend)\
//        {\
//        vec3 baseHSL = RGBToHSL(base);\
//        return HSLToRGB(vec3(RGBToHSL(blend).r, baseHSL.g, baseHSL.b));\
//        }\
//        \
//        vec3 BlendSaturation(vec3 base, vec3 blend)\
//        {\
//        vec3 baseHSL = RGBToHSL(base);\
//        return HSLToRGB(vec3(baseHSL.r, RGBToHSL(blend).g, baseHSL.b));\
//        }\
//        \
//        vec3 BlendColor(vec3 base, vec3 blend)\
//        {\
//        vec3 blendHSL = RGBToHSL(blend);\
//        return HSLToRGB(vec3(blendHSL.r, blendHSL.g, RGBToHSL(base).b));\
//        }\
//        \
//        vec3 BlendLuminosity(vec3 base, vec3 blend)\
//        {\
//        vec3 baseHSL = RGBToHSL(base);\
//        return HSLToRGB(vec3(baseHSL.r, baseHSL.g, RGBToHSL(blend).b));\
//        }\
//        \
//        uniform sampler2DRect base;\
//        uniform sampler2DRect blendTgt;\
//        uniform int mode;\
//        \
//        void main()\
//        {\
//        vec4 baseCol = texture2DRect(base, gl_TexCoord[0].st);\
//        vec4 blendCol = texture2DRect(blendTgt, gl_TexCoord[0].st);\
//        \
//        vec3 result;\
//        if (mode == 0)\
//        {\
//        result = BlendAlpha(baseCol.rgb, blendCol.rgb, blendCol.a);\
//        }\
//        else if (mode == 1)\
//        {\
//        result = BlendMultiply(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 2)\
//        {\
//        result = BlendAverage(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 3)\
//        {\
//        result = BlendAdd(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 4)\
//        {\
//        result = BlendSubstract(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 5)\
//        {\
//        result = BlendDifference(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 6)\
//        {\
//        result = BlendNegation(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 7)\
//        {\
//        result = BlendExclusion(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 8)\
//        {\
//        result = BlendScreen(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 9)\
//        {\
//        result = BlendOverlay(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 10)\
//        {\
//        result = BlendSoftLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 11)\
//        {\
//        result = BlendHardLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 12)\
//        {\
//        result = BlendColorDodge(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 13)\
//        {\
//        result = BlendColorBurn(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 14)\
//        {\
//        result = BlendLinearLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 15)\
//        {\
//        result = BlendVividLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 16)\
//        {\
//        result = BlendPinLight(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 17)\
//        {\
//        result = BlendHardMix(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 18)\
//        {\
//        result = BlendReflect(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 19)\
//        {\
//        result = BlendGlow(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 20)\
//        {\
//        result = BlendPhoenix(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 21)\
//        {\
//        result = BlendHue(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 22)\
//        {\
//        result = BlendSaturation(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 23)\
//        {\
//        result = BlendColor(baseCol.rgb, blendCol.rgb);\
//        }\
//        else if (mode == 24)\
//        {\
//        result = BlendLuminosity(baseCol.rgb, blendCol.rgb);\
//        }\
//        else\
//        {\
//        result = BlendNormal(baseCol.rgb, blendCol.rgb);\
//        }\
//        \
//        gl_FragColor = vec4(result, baseCol.a + blendCol.a);\
//        }\
//        ";
//
//        return fragmentProgram;
//    }

    //--------------------------------------------------------------
    //
    void BlendMode::_loadShader() {
        _blendShader = new ofShader();
        
//        string fragmentProgram;
//#ifdef TARGET_OPENGLES
//        
//#else
//        if(ofIsGLProgrammableRenderer()){
//            fragmentProgram = _getFragmentProgramGL3();
//        } else {
//            fragmentProgram = _getFragmentProgramGL2();
//        }
//#endif
//        
//        _blendShader->setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentProgram);
//        _blendShader->linkProgram();
    }
    
    //--------------------------------------------------------------
    //
    void BlendMode::destroy() {
        delete _base;
        _base = NULL;
        
        delete _blendShader;
        _blendShader = NULL;
    }
    
}
