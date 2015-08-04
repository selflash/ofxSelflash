#include "JoystickEvent.h"

namespace fl2d {

    string JoystickEvent::CHANGE = "joystickChange";
    string JoystickEvent::UP = "joystickUp";
    string JoystickEvent::DOWN = "joystickDown";
    string JoystickEvent::LEFT = "joystickLeft";
    string JoystickEvent::RIGHT = "joystickRight";

    //--------------------------------------------------------------
    //
    JoystickEvent::JoystickEvent(string type):Event(type) {
        __xValue = 0.0;
        __yValue = 0.0;
    }

    //--------------------------------------------------------------
    //
    JoystickEvent::~JoystickEvent() {
        __xValue = 0.0;
        __yValue = 0.0;
    }

    //--------------------------------------------------------------
    //
    float JoystickEvent::xValue() { return __xValue; }
    //--------------------------------------------------------------
    //
    float JoystickEvent::yValue() { return __yValue; }

}