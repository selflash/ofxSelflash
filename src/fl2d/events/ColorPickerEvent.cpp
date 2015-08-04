#include "ColorPickerEvent.h"

namespace fl2d {
    
    string ColorPickerEvent::CHANGE = "radioButtonChange";
    
    //--------------------------------------------------------------
    //
    ColorPickerEvent::ColorPickerEvent(string type):Event(type) {
        
    }
    
    //--------------------------------------------------------------
    //
    ColorPickerEvent::~ColorPickerEvent() {
        
    }
    
}