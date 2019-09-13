#include "Joystick2Event.h"

namespace fl2d {
    
    string Joystick2Event::CHANGE = "joystick2Change";
    string Joystick2Event::UP = "joystick2Up";
    string Joystick2Event::DOWN = "joystick2Down";
    string Joystick2Event::LEFT = "joystick2Left";
    string Joystick2Event::RIGHT = "joystick2Right";
    
    //--------------------------------------------------------------
    //
    Joystick2Event::Joystick2Event(string type):Event(type) {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    Joystick2Event::~Joystick2Event() {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
}
