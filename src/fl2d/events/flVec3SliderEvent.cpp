#include "flVec3SliderEvent.h"

namespace fl2d {
    
    string flVec3SliderEvent::CHANGE = "vec3SliderChange";
    string flVec3SliderEvent::THUMB_DRAG = "thumbDrag";
    string flVec3SliderEvent::THUMB_PRESS = "thumbPress";
    string flVec3SliderEvent::THUMB_RELEASE = "thumbRelease";
    
    //--------------------------------------------------------------
    //
    flVec3SliderEvent::flVec3SliderEvent(string type):flEvent(type) {
        _clickTarget = NULL;
    }
    
    //--------------------------------------------------------------
    //
    flVec3SliderEvent::~flVec3SliderEvent() {
        _clickTarget = NULL;
    }
    
}
