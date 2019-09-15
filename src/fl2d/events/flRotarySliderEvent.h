/**
 ActionScript3.0 Reference
 fl.events.SliderEvent
 
 [URL] http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/fl/events/SliderEvent.html
 */

#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flRotarySlider;
    class flRotarySliderEvent : public flEvent {
        friend class flRotarySlider;
        
    public:
        static string CHANGE;
        static string UP;
        static string DOWN;
        static string LEFT;
        static string RIGHT;
        
    protected:
        float __xValue;
        float __yValue;
        
    private:
        
    public:
        flRotarySliderEvent(string type);
        virtual ~flRotarySliderEvent();
        
        virtual inline float xValue() { return __xValue; }
        virtual inline float yValue() { return __yValue; }
        
    protected:
        
    private:
        
    };
    
}
