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
            inline static float getDeg(float x, float y) {
                auto f = [](float x, float y)->float {
                    if(x >= 0.0) {
                        return atan(y / x);
                    } else {
                        return atan(y / x) + PI;
                    }
                };
                
                float deg = f(x, y) * 180.0 / PI;
                if(deg > 180.0) { deg -= 360.0; }
                if(deg < -180.0) { deg += 360.0; }
                return deg;
            }
            
            //--------------------------------------------------------------
            //
            inline static float getAngle(ofVec2f point) {
                return getDeg(point.x, point.y);
            }

			inline static void mapImageSizeToFrameSize(
				const float srcWidth, const float srcHeight,
				const float frameWidth, const float frameHeight,
				float& dstWidth, float& dstHeight
			) {
				//ウインドウの横幅と縦幅どちらが大きいか？
				if (frameWidth < frameHeight) {
					//横幅に縦幅を合わせる
					dstWidth = frameWidth;
					dstHeight = (srcHeight / srcWidth) * dstWidth;

					//縦幅がウインドウの縦幅より大きくなったら
					if (frameWidth < dstWidth) {
						//縦幅に横幅を合わせる
						dstHeight = frameHeight;
						dstWidth = (srcWidth / srcHeight) * dstHeight;
					}
				}
				else {
					//縦幅に横幅を合わせる
					dstHeight = frameHeight;
					dstWidth = (srcWidth / srcHeight) * dstHeight;

					//横幅がウインドウの横幅より大きくなったら
					if (frameWidth < dstWidth) {
						//横幅に縦幅を合わせる
						dstWidth = frameWidth;
						dstHeight = (srcHeight / srcWidth) * dstWidth;
					}
				}
			}
            
        private:
            flmath() { };
            ~flmath() { };
        
    };
    
}
