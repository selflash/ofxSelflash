#include "ButtonEvent.h"

namespace fl2d {

    string ButtonEvent::CHANGE = "buttonChange";
    string ButtonEvent::MOUSE_OVER = "buttonMouseOver";
    string ButtonEvent::MOUSE_OUT = "buttonMouseOut";
    string ButtonEvent::ROLL_OVER = "buttonRollOver";
    string ButtonEvent::ROLL_OUT = "buttonRollOut";
    string ButtonEvent::MOUSE_DOWN = "buttonMouseDown";
    string ButtonEvent::MOUSE_UP = "buttonMouseUp";

    //--------------------------------------------------------------
    //
    ButtonEvent::ButtonEvent(string type):Event(type) {
//        cout << "[ButtonEvent]ButtonEvent()" << endl;
        
    }

    //--------------------------------------------------------------
    //
    ButtonEvent::~ButtonEvent() {
        
    }
    
    //--------------------------------------------------------------
    //
//    ButtonEvent* ButtonEvent::clone() { return new ButtonEvent(_type); }

}
