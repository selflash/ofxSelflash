/**
 ActionScript3.0 Reference
 fl.events.SliderEvent
 
 [URL] http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/fl/events/SliderEvent.html
 */

#pragma once

#include <string>
#include "flEvent.h"

namespace fl2d {
    
    class flAngler;
    class flAnglerEvent : public flEvent {
        friend class flAngler;
        
    public:
        static string CHANGE;
        
    protected:
        float __value;
        
    private:
        
    public:
        flAnglerEvent(string type);
        virtual ~flAnglerEvent();
        
        virtual inline float value() { return __value; }
        
    protected:
        
    private:
        
    };
    
}
