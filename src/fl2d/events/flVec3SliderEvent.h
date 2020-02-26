#pragma once

#include "ofMain.h"
#include "flEvent.h"

using namespace glm;

namespace fl2d {
    
    class flVec3Slider;
    class flVec3SliderEvent : public flEvent {
        friend class flVec3Slider;
        
    public:
        static string CHANGE;
        static string THUMB_DRAG;
        static string THUMB_PRESS;
        static string THUMB_RELEASE;
        
    protected:
        //スライダサムまたはスライダトラックが押されたかどうかを示すストリングを取得します。
        void* _clickTarget;
        
        vec3 __value;
        
    private:
        
    public:
        flVec3SliderEvent(string type);
        virtual ~flVec3SliderEvent();
        
        //----------------------------------
        virtual inline vec3 value() { return __value; }
        virtual inline float xValue() { return __value.x; }
        virtual inline float yValue() { return __value.y; }
        virtual inline float zValue() { return __value.z; }
        //----------------------------------
        
    protected:
        
    private:
        
    };
    
}
