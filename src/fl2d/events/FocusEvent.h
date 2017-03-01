/**
 
 ActionScript3.0 Reference
 flash.events.FocusEvent
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/events/FocusEvent.html
 
 */

#pragma once

#include <string>
#include "Event.h"
#include "../display/InteractiveObject.h"

namespace fl2d {
    
    class InteractiveObject;
    class Stage;
    class FocusEvent : public Event {
        friend InteractiveObject;
        friend Stage;
            
        public:
            static string FOCUS_IN;
            static string FOCUS_OUT;
            static string KEY_FOCUS_CHANGE;
            static string MOUSE_FOCUS_CHANGE;
            
        private:
            
        public:
            FocusEvent(string type);
            virtual ~FocusEvent();
            
        private:
        
    };
    
}
