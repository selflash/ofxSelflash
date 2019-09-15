#include "flSliderEvent.h"

namespace fl2d {
    
    string flSliderEvent::CHANGE = "sliderChange";
    string flSliderEvent::THUMB_DRAG = "thumbDrag";
    string flSliderEvent::THUMB_PRESS = "thumbPress";
    string flSliderEvent::THUMB_RELEASE = "thumbRelease";
    
    //--------------------------------------------------------------
    //
    flSliderEvent::flSliderEvent(string type):flEvent(type) {
        _clickTarget = NULL;
    }
    
    //--------------------------------------------------------------
    //
    flSliderEvent::~flSliderEvent() {
        _clickTarget = NULL;
    }
    
}
