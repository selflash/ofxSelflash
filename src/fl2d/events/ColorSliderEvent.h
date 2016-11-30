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

            virtual int hexValue() { return __color.getHex(); }
        
            //----------------------------------
            //型を渡さなかったらintで処理される
            virtual inline int redValue() { return __color.r * 255.0; }
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
            virtual inline int greenValue() { return __color.g * 255.0; }
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
            virtual inline int blueValue() { return __color.b * 255.0; }
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
            virtual inline int alphaValue() { return __color.a * 255.0; }
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
