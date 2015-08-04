/**
 ActionScript3.0 Reference
 fl.events.SliderEvent
 
 [URL] http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/fl/events/SliderEvent.html
 */

#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class Joystick;
    class JoystickEvent : public Event {
        friend class Joystick;
            
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
            JoystickEvent(string type);
            ~JoystickEvent();
            
            virtual float xValue();
            virtual float yValue();
            
        protected:
            
        private:
            
    };
    
}