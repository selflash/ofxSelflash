#include "ColorPickerEvent.h"

namespace fl2d {
    
    string ColorPickerEvent::CHANGE = "colorPickerChange";
    
    //--------------------------------------------------------------
    //
    ColorPickerEvent::ColorPickerEvent(string type):Event(type) {
        
    }
    
    //--------------------------------------------------------------
    //
    ColorPickerEvent::~ColorPickerEvent() {
        
    }
    
}
