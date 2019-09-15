#include "flJoyStick1Event.h"

namespace fl2d {
    
    string flJoyStick1Event::CHANGE = "joystick1Change";
    string flJoyStick1Event::UP = "joystick1Up";
    string flJoyStick1Event::DOWN = "joystick1Down";
    string flJoyStick1Event::LEFT = "joystick1Left";
    string flJoyStick1Event::RIGHT = "joystick1Right";
    
    //--------------------------------------------------------------
    //
    flJoyStick1Event::flJoyStick1Event(string type):flEvent(type) {
        __value = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    flJoyStick1Event::~flJoyStick1Event() {
        __value = 0.0;
    }
    
}
