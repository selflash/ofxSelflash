#include "PadEvent.h"

namespace fl2d {

    string PadEvent::CHANGE = "pad2DChange";

    //--------------------------------------------------------------
    //
    PadEvent::PadEvent(string type):Event(type) {
        __xRatio = 0.0;
        __yRatio = 0.0;
        __xValue = 0.0;
        __yValue = 0.0;
        __zValue = 0.0;
    }

    //--------------------------------------------------------------
    //
    PadEvent::~PadEvent() {
        __xRatio = 0.0;
        __yRatio = 0.0;
        __xValue = 0.0;
        __yValue = 0.0;
        __zValue = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    float PadEvent::xRatio() { return __xRatio; }
    
    //--------------------------------------------------------------
    //
    float PadEvent::yRatio() { return __yRatio; }

    //--------------------------------------------------------------
    //
    float PadEvent::xValue() { return __xValue; }

    //--------------------------------------------------------------
    //
    float PadEvent::yValue() { return __yValue; }
    
    //--------------------------------------------------------------
    //
    float PadEvent::zValue() { return __zValue; }

}