#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flRangeSlider;
    class flRangeSliderEvent : public flEvent {
        friend class flRangeSlider;
        
    public:
        static string CHANGE;
        static string THUMB_DRAG;
        static string THUMB_PRESS;
        static string THUMB_RELEASE;
        
    protected:        
        float __minValue;
        float __maxValue;
//        float __range;
        
    private:
        //スライダサムまたはスライダトラックが押されたかどうかを示すストリングを取得します。
//        void* _clickTarget;
        
    public:
        flRangeSliderEvent(string type);
        virtual ~flRangeSliderEvent();
        
        virtual inline float minValue() { return __minValue; }
        virtual inline float maxValue() { return __maxValue; }
//        virtual inline float range() { return __range; }
        
    protected:
        
    private:
        
    };
    
}
