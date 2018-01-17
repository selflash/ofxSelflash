#include "RotarySliderEvent.h"

namespace fl2d {
    
    string RotarySliderEvent::CHANGE = "rotarySliderChange";
    string RotarySliderEvent::UP = "rotarySliderUp";
    string RotarySliderEvent::DOWN = "rotarySliderDown";
    string RotarySliderEvent::LEFT = "rotarySliderLeft";
    string RotarySliderEvent::RIGHT = "rotarySliderRight";
    
    //--------------------------------------------------------------
    //
    RotarySliderEvent::RotarySliderEvent(string type):Event(type) {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    RotarySliderEvent::~RotarySliderEvent() {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
}
