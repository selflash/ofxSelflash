#include "flRangeSliderEvent.h"

namespace fl2d {
    
    string flRangeSliderEvent::CHANGE = "rangeSliderChange";
    string flRangeSliderEvent::THUMB_DRAG = "thumbDrag";
    string flRangeSliderEvent::THUMB_PRESS = "thumbPress";
    string flRangeSliderEvent::THUMB_RELEASE = "thumbRelease";
    
    //--------------------------------------------------------------
    //
    flRangeSliderEvent::flRangeSliderEvent(string type):flEvent(type) {
        _clickTarget = NULL;
        
        __minValue = 0.0f;
        __maxValue = 0.0f;
        __range = 0.0f;
    }
    
    //--------------------------------------------------------------
    //
    flRangeSliderEvent::~flRangeSliderEvent() {
        _clickTarget = NULL;
        
        __minValue = 0.0f;
        __maxValue = 0.0f;
        __range = 0.0f;
    }
    
}
