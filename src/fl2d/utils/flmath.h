#pragma once

#include <math.h>
#include "ofMain.h"

namespace flinternal {
    
    class flmath {
    public:
        
        //--------------------------------------------------------------
        //
        inline static double round(double value, int n = 3) {
            double dst;
            //処理を行う桁を10-1 の位にする
            dst = value * pow((double)10, (double)(-n - 1));
            dst = (double)(int)(dst + 0.5);
            
            //処理を行った桁を元に戻す
            return dst * pow((double)10, (double)(n + 1));
        }
        
        //--------------------------------------------------------------
        //??
        inline static double roundd(const double& value) {
            double result;
            if (value > 0.0) {
                result = floor(value + 0.5);
            } else {
                result = -1.0 * floor(fabs(value) + 0.5);
            }
            
            if(result == -0) result = 0;
            return result;
        }
        
        //--------------------------------------------------------------
        //
        inline static float getAngle(float x, float y) {
            auto getAtan = [](float x, float y)->float {
                if(x > 0.0) {
                    return atan(y / x);
                } else {
                    return atan(y / x) + PI;
                }
            };
            
            float rot = getAtan(x, y) * 180.0 / PI;
            if(rot > 180.0) { rot -= 360.0; }
            if(rot < -180.0) { rot += 360.0; }
            return rot;
        }
        
        //--------------------------------------------------------------
        //
        inline static float getAngle(ofVec2f point) {
            return getAngle(point.x, point.y);
        }
        
        
    private:
        flmath() { };
        ~flmath() { };
        
    };
    
}
