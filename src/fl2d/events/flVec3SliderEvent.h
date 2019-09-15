#pragma once

#include "ofMain.h"
#include "flEvent.h"

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
        
        ofVec3f __vec3f;
        
    private:
        
    public:
        flVec3SliderEvent(string type);
        virtual ~flVec3SliderEvent();
        
        //----------------------------------
        virtual inline float xValue() { return __vec3f.x; }
        virtual inline float yValue() { return __vec3f.y; }
        virtual inline float zValue() { return __vec3f.z; }
        //----------------------------------
        
    protected:
        
    private:
        
    };
    
}
