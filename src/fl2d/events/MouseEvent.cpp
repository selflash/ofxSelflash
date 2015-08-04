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

    //--------------------------------------------------------------
    //
    MouseEvent::MouseEvent(string type):Event(type) {
        __localX = 0.0;
        __localY = 0.0;
        
        __stageX = 0.0;
        __stageY = 0.0;
    }

    //--------------------------------------------------------------
    //
    MouseEvent::~MouseEvent() {
        __localX = 0.0;
        __localY = 0.0;
        
        __stageX = 0.0;
        __stageY = 0.0;
    }

}