#include "flAnglerEvent.h"

namespace fl2d {
    
    string flAnglerEvent::CHANGE = "anglerChange";
    
    //--------------------------------------------------------------
    //
    flAnglerEvent::flAnglerEvent(string type):flEvent(type) {
        __value = 0.0;
    }
    
    //--------------------------------------------------------------
    //
    flAnglerEvent::~flAnglerEvent() {
        __value = 0.0;
    }
    
}
