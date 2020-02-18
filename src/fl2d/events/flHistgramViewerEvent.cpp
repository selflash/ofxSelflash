#include "flHistgramViewerEvent.h"

namespace fl2d {
    
    string flHistgramViewerEvent::CHANGE = "histgramViewerEventChange";
    
    //--------------------------------------------------------------
    flHistgramViewerEvent::flHistgramViewerEvent(string type):flEvent(type) {
        __value = 0.0;
    }
    
    //--------------------------------------------------------------
    flHistgramViewerEvent::~flHistgramViewerEvent() {
        __value = 0.0;
    }
    
}
