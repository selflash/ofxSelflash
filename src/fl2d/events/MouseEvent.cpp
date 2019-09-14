#include "MouseEvent.h"

namespace fl2d {
    
    string MouseEvent::MOUSE_OVER = "mouseOver";
    string MouseEvent::MOUSE_OUT = "mouseOut";
    string MouseEvent::ROLL_OVER = "rollOver";
    string MouseEvent::ROLL_OUT = "rollOut";
    string MouseEvent::MOUSE_DOWN = "mouseDown";
    string MouseEvent::MOUSE_UP = "mouseUp";
    string MouseEvent::CLICK = "click";
    //string MouseEvent::DOUBLE_CLICK = "doubleClick";
    string MouseEvent::MOUSE_MOVE = "mouseMove";
    string MouseEvent::DRAGGING = "dragging";
    string MouseEvent::MOUSE_SCROLLED = "mouseScrolled";
    
    //--------------------------------------------------------------
    //
    MouseEvent::MouseEvent(string type):Event(type) {
        
    }
    
    //--------------------------------------------------------------
    //
    MouseEvent::~MouseEvent() {
        
    }
    
}
