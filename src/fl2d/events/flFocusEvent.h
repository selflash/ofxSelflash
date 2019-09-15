/**
 
 ActionScript3.0 Reference
 flash.events.FocusEvent
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/events/FocusEvent.html
 
 */

#pragma once

#include <string>
#include "flEvent.h"
#include "flInteractiveObject.h"

namespace fl2d {
    
    class flInteractiveObject;
    class flStage;
    class flFocusEvent : public flEvent {
        friend flInteractiveObject;
        friend flStage;
        
    public:
        static string FOCUS_IN;
        static string FOCUS_OUT;
        static string KEY_FOCUS_CHANGE;
        static string MOUSE_FOCUS_CHANGE;
        
    private:
        
    public:
        flFocusEvent(string type);
        virtual ~flFocusEvent();
        
    private:
        
    };
    
}
