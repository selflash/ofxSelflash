#include "flKeyboardEvent.h"

namespace fl2d {
    
    string flKeyboardEvent::KEY_DOWN = "keyDown";
    string flKeyboardEvent::KEY_UP = "keyUp";
    string flKeyboardEvent::KEY_PRESS = "keyPress";
    string flKeyboardEvent::KEY_RELEASE = "keyRelease";
    
    
    //--------------------------------------------------------------
    //
    flKeyboardEvent::flKeyboardEvent(string type):flEvent(type) {
        __keyCode = 0;
    }
    
    //--------------------------------------------------------------
    //
    flKeyboardEvent::~flKeyboardEvent() {
        __keyCode = 0;
    }
    
}
