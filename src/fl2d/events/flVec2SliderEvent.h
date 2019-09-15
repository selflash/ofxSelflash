#pragma once

#include "ofMain.h"
#include "flEvent.h"

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
        
        ofVec2f __vec2f;
        
    private:
        
    public:
        flVec2SliderEvent(string type);
        virtual ~flVec2SliderEvent();
        
        //----------------------------------
        inline virtual float xValue() { return __vec2f.x; }
        inline virtual float yValue() { return __vec2f.y; }
        //----------------------------------
        
    protected:
        
    private:
        
    };
    
}
