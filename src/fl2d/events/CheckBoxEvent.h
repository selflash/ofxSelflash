#pragma once

#include <string>
#include "Event.h"

namespace fl2d {
    
    class CheckBox;
    class CheckBoxEvent : public Event {
        friend class CheckBox;
            
        public:
            static string CHANGE;
            
        protected:
            
        private:
            
        public:
            CheckBoxEvent(string type);
            virtual ~CheckBoxEvent();
            
        protected:
            
        private:
        
    };
    
}
