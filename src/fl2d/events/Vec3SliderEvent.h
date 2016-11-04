#pragma once

#include "ofMain.h"
#include "Event.h"

namespace fl2d {
    
    class Vec3Slider;
    class Vec3SliderEvent : public Event {
        friend class Vec3Slider;
            
        public:
            static string CHANGE;
            static string THUMB_DRAG;
            static string THUMB_PRESS;
            static string THUMB_RELEASE;
            
        protected:
            //スライダサムまたはスライダトラックが押されたかどうかを示すストリングを取得します。
            void* _clickTarget;
        
            ofVec3f __vec3f;
        
        private:
        
        public:
            Vec3SliderEvent(string type);
            ~Vec3SliderEvent();

            //----------------------------------
            inline virtual float xValue() { return __vec3f.x; }
            inline virtual float yValue() { return __vec3f.y; }
            inline virtual float zValue() { return __vec3f.z; }
            //----------------------------------
        
        protected:
            
        private:
        
    };
    
}