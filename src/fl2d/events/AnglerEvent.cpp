#include "AnglerEvent.h"

namespace fl2d {
    
    string AnglerEvent::CHANGE = "AnglerChange";
    string AnglerEvent::UP = "AnglerUp";
    string AnglerEvent::DOWN = "AnglerDown";
    string AnglerEvent::LEFT = "AnglerLeft";
    string AnglerEvent::RIGHT = "AnglerRight";
    
    //--------------------------------------------------------------
    //
    AnglerEvent::AnglerEvent(string type):Event(type) {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    AnglerEvent::~AnglerEvent() {
        __xValue = 0.0;
        __yValue = 0.0;
    }
    
}
