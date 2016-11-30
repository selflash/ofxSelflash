#include "Joystick1DEvent.h"

namespace fl2d {
    
    string Joystick1DEvent::CHANGE = "Joystick1DChange";
    string Joystick1DEvent::UP = "Joystick1DUp";
    string Joystick1DEvent::DOWN = "Joystick1DDown";
    string Joystick1DEvent::LEFT = "Joystick1DLeft";
    string Joystick1DEvent::RIGHT = "Joystick1DRight";
    
    //--------------------------------------------------------------
    //
    Joystick1DEvent::Joystick1DEvent(string type):Event(type) {
        __value = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    Joystick1DEvent::~Joystick1DEvent() {
        __value = 0.0;
    }
    
}
