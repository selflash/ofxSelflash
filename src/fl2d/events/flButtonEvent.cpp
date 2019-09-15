#include "flButtonEvent.h"

namespace fl2d {
    
    string flButtonEvent::CHANGE = "buttonChange";
    string flButtonEvent::MOUSE_OVER = "buttonMouseOver";
    string flButtonEvent::MOUSE_OUT = "buttonMouseOut";
    string flButtonEvent::ROLL_OVER = "buttonRollOver";
    string flButtonEvent::ROLL_OUT = "buttonRollOut";
    string flButtonEvent::MOUSE_DOWN = "buttonMouseDown";
    string flButtonEvent::MOUSE_UP = "buttonMouseUp";
    string flButtonEvent::CLICK = "buttonClick";
    
    //--------------------------------------------------------------
    //
    flButtonEvent::flButtonEvent(string type):flEvent(type) {
        //        cout << "[ButtonEvent]ButtonEvent()" << endl;
        
    }
    
    //--------------------------------------------------------------
    //
    flButtonEvent::~flButtonEvent() {
        
    }
    
}
