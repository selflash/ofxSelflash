#pragma once

#include "ofMain.h"
#include "flEvent.h"

using namespace glm;

namespace fl2d {
    
    class flVec2Slider;
    class flVec2SliderEvent : public flEvent {
        friend class flVec2Slider;
        
    public:
        static string CHANGE;
        static string THUMB_DRAG;
        static string THUMB_PRESS;
        static string THUMB_RELEASE;
        
    protected:
        //スライダサムまたはスライダトラックが押されたかどうかを示すストリングを取得します。
        void* _clickTarget;
        
        vec2 __value;
        
    private:
        
    public:
        flVec2SliderEvent(string type);
        virtual ~flVec2SliderEvent();
        
        //----------------------------------
        inline virtual vec2 value() { return __value; }
        inline virtual float xValue() { return __value.x; }
        inline virtual float yValue() { return __value.y; }
        //----------------------------------
        
    protected:
        
    private:
        
    };
    
}
