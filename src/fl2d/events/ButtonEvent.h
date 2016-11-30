#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class Button;
    class ButtonEvent : public Event {
        public:
            static string CHANGE;
            static string MOUSE_OVER;
            static string MOUSE_OUT;
            static string ROLL_OVER;
            static string ROLL_OUT;
            static string MOUSE_DOWN;
            static string MOUSE_UP;
        
        protected:
        
        private:
        
        public:
            ButtonEvent(string type);
            ~ButtonEvent();
        
//            ButtonEvent* clone();

        protected:
            
        private:
        
    };
    
}
