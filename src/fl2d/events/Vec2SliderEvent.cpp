#include "Vec2SliderEvent.h"

namespace fl2d {

    string Vec2SliderEvent::CHANGE = "Vec2SliderChange";
    string Vec2SliderEvent::THUMB_DRAG = "thumbDrag";
    string Vec2SliderEvent::THUMB_PRESS = "thumbPress";
    string Vec2SliderEvent::THUMB_RELEASE = "thumbRelease";

    //--------------------------------------------------------------
    //
    Vec2SliderEvent::Vec2SliderEvent(string type):Event(type) {
        _clickTarget = NULL;
    }

    //--------------------------------------------------------------
    //
    Vec2SliderEvent::~Vec2SliderEvent() {
        _clickTarget = NULL;
    }
    
}
