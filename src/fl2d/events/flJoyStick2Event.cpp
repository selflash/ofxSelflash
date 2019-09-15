#include "flJoyStick2Event.h"

namespace fl2d {
    
    string flJoyStick2Event::CHANGE = "joystick2Change";
    string flJoyStick2Event::UP = "joystick2Up";
    string flJoyStick2Event::DOWN = "joystick2Down";
    string flJoyStick2Event::LEFT = "joystick2Left";
    string flJoyStick2Event::RIGHT = "joystick2Right";
    
    //--------------------------------------------------------------
    //
    flJoyStick2Event::flJoyStick2Event(string type):flEvent(type) {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    flJoyStick2Event::~flJoyStick2Event() {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
}
