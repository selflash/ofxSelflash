#include "RangeSliderEvent.h"

namespace fl2d {

    string RangeSliderEvent::CHANGE = "rangeSliderChange";
    string RangeSliderEvent::THUMB_DRAG = "thumbDrag";
    string RangeSliderEvent::THUMB_PRESS = "thumbPress";
    string RangeSliderEvent::THUMB_RELEASE = "thumbRelease";

    //--------------------------------------------------------------
    //
    RangeSliderEvent::RangeSliderEvent(string type):Event(type) {
        _clickTarget = NULL;
        
        __minValue = 0.0f;
        __maxValue = 0.0f;
        __range = 0.0f;
    }

    //--------------------------------------------------------------
    //
    RangeSliderEvent::~RangeSliderEvent() {
        _clickTarget = NULL;
        
        __minValue = 0.0f;
        __maxValue = 0.0f;
        __range = 0.0f;
    }

    //--------------------------------------------------------------
    //
    float RangeSliderEvent::minValue() { return __minValue; }

    //--------------------------------------------------------------
    //
    float RangeSliderEvent::maxValue() { return __maxValue; }

    //--------------------------------------------------------------
    //
    float RangeSliderEvent::range() { return __range; }

}