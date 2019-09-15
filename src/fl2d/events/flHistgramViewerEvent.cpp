#include "flHistgramViewerEvent.h"

namespace fl2d {
    
    string flHistgramViewerEvent::CHANGE = "histgramViewerEventChange";
    
    //--------------------------------------------------------------
    //
    flHistgramViewerEvent::flHistgramViewerEvent(string type):flEvent(type) {
        //        cout << "[HistgramViewerEvent]ButtonEvent()" << endl;
        
    }
    
    //--------------------------------------------------------------
    //
    flHistgramViewerEvent::~flHistgramViewerEvent() {
        
    }
    
}
