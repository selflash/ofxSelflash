#pragma once

#include "ofMain.h"
#include "Event.h"

namespace fl2d {
    
    class Vec2Slider;
    class Vec2SliderEvent : public Event {
        friend class Vec2Slider;
            
        public:
            static string CHANGE;
            static string THUMB_DRAG;
            static string THUMB_PRESS;
            static string THUMB_RELEASE;
            
        protected:
            //スライダサムまたはスライダトラックが押されたかどうかを示すストリングを取得します。
            void* _clickTarget;
        
            ofVec2f __vec2f;
        
        private:
        
        public:
            Vec2SliderEvent(string type);
            virtual ~Vec2SliderEvent();

            //----------------------------------
            inline virtual float xValue() { return __vec2f.x; }
            inline virtual float yValue() { return __vec2f.y; }
            //----------------------------------
        
        protected:
            
        private:
        
    };
    
}
