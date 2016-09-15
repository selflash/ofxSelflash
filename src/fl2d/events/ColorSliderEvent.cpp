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

    //--------------------------------------------------------------
    //
    int ColorSliderEvent::hexValue() { return __color.getHex(); }

    //--------------------------------------------------------------
    //
    int ColorSliderEvent::redValue() { return __color.r * 255.0; }

    //--------------------------------------------------------------
    //
    int ColorSliderEvent::greenValue() { return __color.g * 255.0; }

    //--------------------------------------------------------------
    //
    int ColorSliderEvent::blueValue() { return __color.b * 255.0; }

    //--------------------------------------------------------------
    //
    int ColorSliderEvent::alphaValue() { return __color.a * 255.0; }
        
}
