#include "SliderEvent.h"

namespace fl2d {
    
    string SliderEvent::CHANGE = "sliderChange";
    string SliderEvent::THUMB_DRAG = "thumbDrag";
    string SliderEvent::THUMB_PRESS = "thumbPress";
    string SliderEvent::THUMB_RELEASE = "thumbRelease";
    
    //--------------------------------------------------------------
    //
    SliderEvent::SliderEvent(string type):Event(type) {
        _clickTarget = NULL;
    }
    
    //--------------------------------------------------------------
    //
    SliderEvent::~SliderEvent() {
        _clickTarget = NULL;
    }
    
}
