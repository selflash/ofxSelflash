/**
 ActionScript3.0 Reference
 fl.events.SliderEvent
 
 [URL] http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/fl/events/SliderEvent.html
 */

#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class Joystick2D;
    class Joystick2DEvent : public Event {
            friend class Joystick2D;
            
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
            Joystick2DEvent(string type);
            ~Joystick2DEvent();
            
            virtual inline float xValue() { return __xValue; }
            virtual inline float yValue() { return __yValue; }
            
        protected:
            
        private:
            
    };
    
}
