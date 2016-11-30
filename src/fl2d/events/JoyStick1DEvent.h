/**
 ActionScript3.0 Reference
 fl.events.SliderEvent
 
 [URL] http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/fl/events/SliderEvent.html
 */

#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class Joystick1D;
    class Joystick1DEvent : public Event {
            friend class Joystick1D;
            
        public:
            static string CHANGE;
            static string UP;
            static string DOWN;
            static string LEFT;
            static string RIGHT;
            
        protected:
            float __value;
            
        private:
            
        public:
            Joystick1DEvent(string type);
            ~Joystick1DEvent();
            
            virtual inline float value() { return __value; }
            
        protected:
            
        private:
        
    };
    
}
