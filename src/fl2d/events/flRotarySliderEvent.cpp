#include "flRotarySliderEvent.h"

namespace fl2d {
    
    string flRotarySliderEvent::CHANGE = "rotarySliderChange";
    string flRotarySliderEvent::UP = "rotarySliderUp";
    string flRotarySliderEvent::DOWN = "rotarySliderDown";
    string flRotarySliderEvent::LEFT = "rotarySliderLeft";
    string flRotarySliderEvent::RIGHT = "rotarySliderRight";
    
    //--------------------------------------------------------------
    //
    flRotarySliderEvent::flRotarySliderEvent(string type):flEvent(type) {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    flRotarySliderEvent::~flRotarySliderEvent() {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
}
