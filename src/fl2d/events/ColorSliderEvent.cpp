#include "ColorSliderEvent.h"

namespace fl2d {

    string ColorSliderEvent::CHANGE = "ColorSliderChange";
    string ColorSliderEvent::THUMB_DRAG = "thumbDrag";
    string ColorSliderEvent::THUMB_PRESS = "thumbPress";
    string ColorSliderEvent::THUMB_RELEASE = "thumbRelease";

    //--------------------------------------------------------------
    //
    ColorSliderEvent::ColorSliderEvent(string type):Event(type) {
        _clickTarget = NULL;
    }

    //--------------------------------------------------------------
    //
    ColorSliderEvent::~ColorSliderEvent() {
        _clickTarget = NULL;
    }
        
}
