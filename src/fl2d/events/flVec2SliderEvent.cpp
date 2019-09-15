#include "flVec2SliderEvent.h"

namespace fl2d {
    
    string flVec2SliderEvent::CHANGE = "vec2SliderChange";
    string flVec2SliderEvent::THUMB_DRAG = "thumbDrag";
    string flVec2SliderEvent::THUMB_PRESS = "thumbPress";
    string flVec2SliderEvent::THUMB_RELEASE = "thumbRelease";
    
    //--------------------------------------------------------------
    //
    flVec2SliderEvent::flVec2SliderEvent(string type):flEvent(type) {
        _clickTarget = NULL;
    }
    
    //--------------------------------------------------------------
    //
    flVec2SliderEvent::~flVec2SliderEvent() {
        _clickTarget = NULL;
    }
    
}
