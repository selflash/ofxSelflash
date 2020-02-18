#include "flUIBase.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flUIBase::flUIBase() {
//        ofLog() << "[flUIBase]flUIBase()";
        
        _target = this;
        name("flUIBase");

        _label = NULL;
        _enabled = true;
    }
    
    //--------------------------------------------------------------
    flUIBase::~flUIBase() {
//        ofLog() << "[flUIBase]~flUIBase()";
        
        _label = NULL;
        _enabled = false;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flUIBase::label() { return _label; }
    void flUIBase::label(flTextField* value) { _label = value; }

    //--------------------------------------------------------------
    bool flUIBase::enabled() { return _enabled; }
    void flUIBase::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================

    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flUIBase::_mouseEventHandler(flEvent& event) {
        if(!_enabled) return;
//ofLog() << "[flUIBase]_mouseEventHandler(" << event.type() << ")";
//ofLog() << "[flUIBase]this          = " << this << "," << ((flDisplayObject*) this)->name();
//ofLog() << "[flUIBase]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//ofLog() << "[flUIBase]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            
        }
    }
    
}
