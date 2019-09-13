#include "Vec3SliderEvent.h"

namespace fl2d {

    string Vec3SliderEvent::CHANGE = "vec3SliderChange";
    string Vec3SliderEvent::THUMB_DRAG = "thumbDrag";
    string Vec3SliderEvent::THUMB_PRESS = "thumbPress";
    string Vec3SliderEvent::THUMB_RELEASE = "thumbRelease";

    //--------------------------------------------------------------
    //
    Vec3SliderEvent::Vec3SliderEvent(string type):Event(type) {
        _clickTarget = NULL;
    }

    //--------------------------------------------------------------
    //
    Vec3SliderEvent::~Vec3SliderEvent() {
        _clickTarget = NULL;
    }
    
}
