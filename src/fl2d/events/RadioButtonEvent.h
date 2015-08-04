#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class RadioButton;
    class RadioButtonEvent : public Event {
        friend class RadioButton;
            
        public:
            static string CHANGE;
            
        protected:
            
        private:
            
        public:
            RadioButtonEvent(string type);
            ~RadioButtonEvent();
            
        protected:
            
        private:
        
    };
    
}