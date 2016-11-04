#include "KeyboardEvent.h"

namespace fl2d {

    string KeyboardEvent::KEY_DOWN = "keyDown";
    string KeyboardEvent::KEY_UP = "keyUp";
    string KeyboardEvent::KEY_PRESS = "keyPress";
    string KeyboardEvent::KEY_RELEASE = "keyRelease";


    //--------------------------------------------------------------
    //
    KeyboardEvent::KeyboardEvent(string type):Event(type) {
        __keyCode = 0;
    }

    //--------------------------------------------------------------
    //
    KeyboardEvent::~KeyboardEvent() {
        __keyCode = 0;
    }

    //--------------------------------------------------------------
    //
    int KeyboardEvent::keyCode() { return __keyCode; }

}