/**
 ActionScript3.0 Reference
 fl.events.SliderEvent
 
 [URL] http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/fl/events/SliderEvent.html
 */

#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class Joystick2;
    class Joystick2Event : public Event {
            friend class Joystick2;
            
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
            Joystick2Event(string type);
            virtual ~Joystick2Event();
            
            virtual inline float xValue() { return __xValue; }
            virtual inline float yValue() { return __yValue; }
            
        protected:
            
        private:
            
    };
    
}
