/**
 ActionScript3.0 Reference
 fl.events.SliderEvent
 
 [URL] http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/fl/events/SliderEvent.html
 */

#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class Angler;
    class AnglerEvent : public Event {
            friend class Angler;
            
        public:
            static string CHANGE;
        
        protected:
            float __value;
        
        private:
            
        public:
            AnglerEvent(string type);
            virtual ~AnglerEvent();
            
            virtual inline float value() { return __value; }
            
        protected:
            
        private:
            
    };
    
}
