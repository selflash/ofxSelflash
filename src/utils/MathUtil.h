#pragma once

#include <math.h>

class MathUtil {
    public:
        static inline double round(double value, int n = 3) {
            double dst;
            //処理を行う桁を10-1 の位にする
            dst = value * pow((double)10, (double)(-n - 1));
            dst = (double)(int)(dst + 0.5);

            //処理を行った桁を元に戻す
            return dst * pow((double)10, (double)(n + 1));
        }
    
        //??
        static inline double roundd(const double& value) {
            double result;
            if (value > 0.0) {
                result = floor(value + 0.5);
            } else {
                result = -1.0 * floor(fabs(value) + 0.5);
            }
            
            if(result == -0) result = 0;
            return result;
        }
};