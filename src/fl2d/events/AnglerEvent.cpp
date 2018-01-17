#include "AnglerEvent.h"

namespace fl2d {
    
    string AnglerEvent::CHANGE = "anglerChange";
    
    //--------------------------------------------------------------
    //
    AnglerEvent::AnglerEvent(string type):Event(type) {
        __value = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    AnglerEvent::~AnglerEvent() {
        __value = 0.0;
    }
    
}
