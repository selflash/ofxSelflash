#include "HistgramViewerEvent.h"

namespace fl2d {
    
    string HistgramViewerEvent::CHANGE = "histgramViewerEventChange";
    
    //--------------------------------------------------------------
    //
    HistgramViewerEvent::HistgramViewerEvent(string type):Event(type) {
        //        cout << "[HistgramViewerEvent]ButtonEvent()" << endl;
        
    }
    
    //--------------------------------------------------------------
    //
    HistgramViewerEvent::~HistgramViewerEvent() {
        
    }
    
}
