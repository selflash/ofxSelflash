#include "flFocusEvent.h"

namespace fl2d {
    
    string flFocusEvent::FOCUS_IN = "focusIn";
    string flFocusEvent::FOCUS_OUT = "focusOut";
    string flFocusEvent::KEY_FOCUS_CHANGE = "keyFocusChange";
    string flFocusEvent::MOUSE_FOCUS_CHANGE = "mouseFocusChange";
    
    //--------------------------------------------------------------
    //
    flFocusEvent::flFocusEvent(string type):flEvent(type) {
        
    }
    
    //--------------------------------------------------------------
    //
    flFocusEvent::~flFocusEvent() {
        
    }
    
}
