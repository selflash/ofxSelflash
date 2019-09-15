#include "flColorSliderEvent.h"

namespace fl2d {
    
    string flColorSliderEvent::CHANGE = "colorSliderChange";
    string flColorSliderEvent::THUMB_DRAG = "thumbDrag";
    string flColorSliderEvent::THUMB_PRESS = "thumbPress";
    string flColorSliderEvent::THUMB_RELEASE = "thumbRelease";
    
    //--------------------------------------------------------------
    //
    flColorSliderEvent::flColorSliderEvent(string type):flEvent(type) {
        _clickTarget = NULL;
    }
    
    //--------------------------------------------------------------
    //
    flColorSliderEvent::~flColorSliderEvent() {
        _clickTarget = NULL;
    }
    
}
