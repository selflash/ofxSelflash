#include "InteractiveObject.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    InteractiveObject::InteractiveObject() {
        _typeID = FL_TYPE_INTERACTIVE_OBJECT;
        _target = this;
        
        name("InteractiveObject");
        
        _mouseEnabled = true;
        _buttonMode = false;
        _doubleClickEnabled	= false;
        _mouseUpOutside = true;
        
        _tabEnabled = false;
        _tabIndex = 0;
        
        __isMouseOver = false;
        __isRollOver = false;
        __isMouseDown = false;
        __isMousePressed = false;
        __isMouseReleased = false;
        __isFocus = false;
    }

    //--------------------------------------------------------------
    //
    InteractiveObject::~InteractiveObject() {
        _target = NULL;
        
        _mouseEnabled = false;
        _buttonMode = false;
        _doubleClickEnabled	= false;
        _mouseUpOutside = false;
        
        _tabEnabled = false;
        _tabIndex = 0;
        
        __isMouseOver = false;
        __isRollOver = false;
        __isMouseDown = false;
        __isMousePressed = false;
        __isMouseReleased = false;
        __isFocus = false;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void InteractiveObject::drop(ofDragInfo& info) {
        
    }

    //--------------------------------------------------------------
    //
    bool InteractiveObject::buttonMode() { return _buttonMode; }
    void InteractiveObject::buttonMode(bool value) { _buttonMode = value; }

    //--------------------------------------------------------------
    //
    bool InteractiveObject::mouseEnabled() { return _mouseEnabled; }
    void InteractiveObject::mouseEnabled(bool value) { _mouseEnabled = value; }

    //--------------------------------------------------------------
    //
    bool InteractiveObject::doubleClickEnabled() { return _doubleClickEnabled; }
    void InteractiveObject::doubleClickEnabled(bool value) { _doubleClickEnabled = value; }

    //--------------------------------------------------------------
    //
    bool InteractiveObject::mouseUpOutside() { return _mouseUpOutside; }
    void InteractiveObject::mouseUpOutside(bool value) { _mouseUpOutside = value; }

    //--------------------------------------------------------------
    //
    bool InteractiveObject::isMouseOver() { return __isMouseOver; }
    //--------------------------------------------------------------
    //
    bool InteractiveObject::isRollOver() { return __isRollOver; }
    //--------------------------------------------------------------
    //
    bool InteractiveObject::isMouseDown() { return __isMouseDown; }
//    const bool& InteractiveObject::isMouseDown() { return __isMousePressed; }
    //--------------------------------------------------------------
    //
    bool InteractiveObject::isFocus() { return __isFocus; }
    
    //--------------------------------------------------------------
    //
//    void InteractiveObject::focusOut() {
//        __isFocus = false;
//        FocusEvent* focusEvent = new FocusEvent(FocusEvent::FOCUS_OUT);
//        focusEvent->_target = this;
//        dispatchEvent(focusEvent);
//    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================


}
