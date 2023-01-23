#include "flNumericDialerEvent.h"

namespace fl2d {
    
    string flNumericDialerEvent::CHANGE = "numericDialerChange";
    
    //--------------------------------------------------------------
    flNumericDialerEvent::flNumericDialerEvent(string type):flEvent(type) {
        
    }
    
    //--------------------------------------------------------------
    flNumericDialerEvent::~flNumericDialerEvent() {
        
    }
    
}
