#include "flInteractiveObject.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flInteractiveObject::flInteractiveObject() {
        _typeID = FL_TYPE_INTERACTIVE_OBJECT;
        _target = this;
        
        name("flInteractiveObject");
        
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
    flInteractiveObject::~flInteractiveObject() {
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
    void flInteractiveObject::drop(ofDragInfo& info) {
        
    }
    
    //--------------------------------------------------------------
    //
    bool flInteractiveObject::buttonMode() { return _buttonMode; }
    void flInteractiveObject::buttonMode(bool value) { _buttonMode = value; }
    
    //--------------------------------------------------------------
    //
    bool flInteractiveObject::mouseEnabled() { return _mouseEnabled; }
    void flInteractiveObject::mouseEnabled(bool value) { _mouseEnabled = value; }
    
    //--------------------------------------------------------------
    //
    bool flInteractiveObject::doubleClickEnabled() { return _doubleClickEnabled; }
    void flInteractiveObject::doubleClickEnabled(bool value) { _doubleClickEnabled = value; }
    
    //--------------------------------------------------------------
    //
    bool flInteractiveObject::mouseUpOutside() { return _mouseUpOutside; }
    void flInteractiveObject::mouseUpOutside(bool value) { _mouseUpOutside = value; }
    
    //--------------------------------------------------------------
    //
    bool flInteractiveObject::isMouseOver() { return __isMouseOver; }
    //--------------------------------------------------------------
    //
    bool flInteractiveObject::isRollOver() { return __isRollOver; }
    //--------------------------------------------------------------
    //
    bool flInteractiveObject::isMouseDown() { return __isMouseDown; }
    //    const bool& flInteractiveObject::isMouseDown() { return __isMousePressed; }
    //--------------------------------------------------------------
    //
    bool flInteractiveObject::isFocus() { return __isFocus; }
    
    //--------------------------------------------------------------
    //
    //    void flInteractiveObject::focusOut() {
    //        __isFocus = false;
    //        FocusEvent* focusEvent = new FocusEvent(FocusEvent::FOCUS_OUT);
    //        focusEvent->_target = this;
    //        dispatchEvent(focusEvent);
    //    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    
}
