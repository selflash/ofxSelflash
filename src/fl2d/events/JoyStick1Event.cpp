#include "Joystick1Event.h"

namespace fl2d {
    
    string Joystick1Event::CHANGE = "joystick1Change";
    string Joystick1Event::UP = "joystick1Up";
    string Joystick1Event::DOWN = "joystick1Down";
    string Joystick1Event::LEFT = "joystick1Left";
    string Joystick1Event::RIGHT = "joystick1Right";
    
    //--------------------------------------------------------------
    //
    Joystick1Event::Joystick1Event(string type):Event(type) {
        __value = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    Joystick1Event::~Joystick1Event() {
        __value = 0.0;
    }
    
}
