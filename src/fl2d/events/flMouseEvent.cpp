#include "flMouseEvent.h"

namespace fl2d {
    
    string flMouseEvent::MOUSE_OVER = "mouseOver";
    string flMouseEvent::MOUSE_OUT = "mouseOut";
    string flMouseEvent::ROLL_OVER = "rollOver";
    string flMouseEvent::ROLL_OUT = "rollOut";
    string flMouseEvent::MOUSE_DOWN = "mouseDown";
    string flMouseEvent::MOUSE_UP = "mouseUp";
    string flMouseEvent::CLICK = "click";
    //string flMouseEvent::DOUBLE_CLICK = "doubleClick";
    string flMouseEvent::MOUSE_MOVE = "mouseMove";
    string flMouseEvent::DRAGGING = "dragging";
    string flMouseEvent::MOUSE_SCROLLED = "mouseScrolled";
    
    //--------------------------------------------------------------
    //
    flMouseEvent::flMouseEvent(string type):flEvent(type) {
        
    }
    
    //--------------------------------------------------------------
    //
    flMouseEvent::~flMouseEvent() {
        
    }
    
}
