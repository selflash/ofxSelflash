#pragma once

#include "ofMain.h"
#include "Event.h"

namespace fl2d {
    
    class ColorSlider;
    class ColorSliderEvent : public Event {
        friend class ColorSlider;
            
        public:
            static string CHANGE;
            static string THUMB_DRAG;
            static string THUMB_PRESS;
            static string THUMB_RELEASE;
            
        protected:
            //スライダサムまたはスライダトラックが押されたかどうかを示すストリングを取得します。
            void* _clickTarget;
        
            ofFloatColor __color;
        
        private:
        
        public:
            ColorSliderEvent(string type);
            ~ColorSliderEvent();

            virtual int hexValue();
        
            //----------------------------------
            //型を渡さなかったらintで処理される
            virtual int redValue();
            template <class T>
            const T redValue() {
                if (typeid(T) == typeid(float)) {
                    return __color.r;
                } else {
                    return __color.r * 255.0;
                }
            }
            //----------------------------------
            
            //----------------------------------
            //型を渡さなかったらintで処理される
            virtual int greenValue();
            template <class T>
            const T greenValue() {
                if (typeid(T) == typeid(float)) {
                    return __color.g;
                } else {
                    return __color.g * 255.0;
                }
            }
            //----------------------------------
            
            //----------------------------------
            //型を渡さなかったらintで処理される
            virtual int blueValue();
            template <class T>
            const T blueValue() {
                if (typeid(T) == typeid(float)) {
                    return __color.b;
                } else {
                    return __color.b * 255.0;
                }
            }
            //----------------------------------
            
            //----------------------------------
            //型を渡さなかったらintで処理される
            virtual int alphaValue();
            template <class T>
            const T alphaValue() {
                if (typeid(T) == typeid(float)) {
                    return __color.a;
                } else {
                    return __color.a * 255.0;
                }
            }
            //----------------------------------
            
        protected:
            
        private:
        
    };
    
}