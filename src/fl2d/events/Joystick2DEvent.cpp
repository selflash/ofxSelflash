#include "Joystick2DEvent.h"

namespace fl2d {
    
    string Joystick2DEvent::CHANGE = "joystick2DChange";
    string Joystick2DEvent::UP = "joystick2DUp";
    string Joystick2DEvent::DOWN = "joystick2DDown";
    string Joystick2DEvent::LEFT = "joystick2DLeft";
    string Joystick2DEvent::RIGHT = "joystick2DRight";
    
    //--------------------------------------------------------------
    //
    Joystick2DEvent::Joystick2DEvent(string type):Event(type) {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    Joystick2DEvent::~Joystick2DEvent() {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    float Joystick2DEvent::xValue() { return __xValue; }
    //--------------------------------------------------------------
    //
    float Joystick2DEvent::yValue() { return __yValue; }
    
}