/**
 ActionScript3.0 Reference
 fl.events.SliderEvent
 
 [URL] http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/fl/events/SliderEvent.html
 */

#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flJoyStick2;
    class flJoyStick2Event : public flEvent {
        friend class flJoyStick2;
        
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
        flJoyStick2Event(string type);
        virtual ~flJoyStick2Event();
        
        virtual inline float xValue() { return __xValue; }
        virtual inline float yValue() { return __yValue; }
        
    protected:
        
    private:
        
    };
    
}
