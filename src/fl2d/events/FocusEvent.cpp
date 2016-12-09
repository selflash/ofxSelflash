#include "FocusEvent.h"

namespace fl2d {

    string FocusEvent::FOCUS_IN = "focusIn";
    string FocusEvent::FOCUS_OUT = "focusOut";
    string FocusEvent::KEY_FOCUS_CHANGE = "keyFocusChange";
    string FocusEvent::MOUSE_FOCUS_CHANGE = "mouseFocusChange";

    //--------------------------------------------------------------
    //
    FocusEvent::FocusEvent(string type):Event(type) {

    }

    //--------------------------------------------------------------
    //
    FocusEvent::~FocusEvent() {

    }

}
