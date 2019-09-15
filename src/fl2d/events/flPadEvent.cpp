#include "flPadEvent.h"

namespace fl2d {
    
    string flPadEvent::CHANGE = "pad2DChange";
    
    //--------------------------------------------------------------
    //
    flPadEvent::flPadEvent(string type):flEvent(type) {
        __xRatio = 0.0;
        __yRatio = 0.0;
        __xValue = 0.0;
        __yValue = 0.0;
        __zValue = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    flPadEvent::~flPadEvent() {
        __xRatio = 0.0;
        __yRatio = 0.0;
        __xValue = 0.0;
        __yValue = 0.0;
        __zValue = 0.0;
    }
    
}
