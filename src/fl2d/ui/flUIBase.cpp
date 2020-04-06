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
    }
    
    //--------------------------------------------------------------
    flUIBase::~flUIBase() {
//        ofLog() << "[flUIBase]~flUIBase()";
        
        _label = NULL;
            
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
    // Protected / Private Event Handler
    //==============================================================

    
}
