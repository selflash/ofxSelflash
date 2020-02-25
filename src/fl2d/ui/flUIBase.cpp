#include "flUIBase.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flUIBase::flUIBase() {
//        ofLog() << "[flUIBase]flUIBase()";
        
        _typeID = FL_TYPE_UIBASE;
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
        
//        _listeners.unsubscribeAll();
        
        _bChangedByMyself.clear();
        _bChangedByOfParm.clear();
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
    
    //--------------------------------------------------------------
//    void flUIBase::bind(ofParameter<float>& param) { }
//    void flUIBase::bind(ofParameter<int>& param) { }
//    void flUIBase::bind(ofParameter<bool>& param) { }
//
//    template <class T>
//    void flUIBase::bind(ofParameter<T>& param) { }
//
//    inline void flUIBase::unbind() { }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================

    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flUIBase::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flUIBase]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flUIBase]this          = " << this << "," << ((flDisplayObject*) this)->name();
//        ofLog() << "[flUIBase]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flUIBase]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
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
