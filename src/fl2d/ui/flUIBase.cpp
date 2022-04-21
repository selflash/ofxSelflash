#include "flUIBase.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flUIBase::flUIBase() {
		//ofLog() << "[flUIBase]flUIBase()";
        
        _typeID = FL_TYPE_UIBASE;
        _target = this;
        name("flUIBase");        
    }
    
    //--------------------------------------------------------------
    flUIBase::~flUIBase() {
//        ofLog() << "[flUIBase]~flUIBase()";
        
		if (_label != NULL) {
			//if (contains(_label)) removeChild(_label);
            _label->removeEventListener(flEvent::REMOVED, this, &flUIBase::_childEventHandler);
            if (_label->parent()) ((flDisplayObjectContainer*)_label->parent())->removeChild(_label);
            delete _label;
			_label = NULL;
		}
            
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
    void flUIBase::label(flTextField* value) { 
        if (value != NULL) {
            _label = value;
            _label->addEventListener(flEvent::REMOVED, this, &flUIBase::_childEventHandler);
        }
        else {
            _label->removeEventListener(flEvent::REMOVED, this, &flUIBase::_childEventHandler);
            _label = NULL;
        }
    }

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

    //--------------------------------------------------------------
    void flUIBase::_childEventHandler(flEvent& event) {
        //ofLog() << "[flUIBase]_childEventHandler(" << event.type() << ")";
        //ofLog() << "[flUIBase]this          = " << this << "," << ((flDisplayObject*)this)->name();
        //ofLog() << "[flUIBase]currentTarget = " << event.currentTarget() << "," << ((event.currentTarget() == NULL) ? "NULL" : ((flDisplayObject*)event.currentTarget())->name());
        //ofLog() << "[flUIBase]target        = " << event.target() << "," << ((event.target() == NULL) ? "NULL" : ((flDisplayObject*)event.target())->name());

        flSprite::_childEventHandler(event);

        if (event.type() == flEvent::ADDED) {

        }
        else if (event.type() == flEvent::ADDED_TO_STAGE) {

        }
        else if (event.type() == flEvent::REMOVED) {
            if (event.target() == _label) {
                _label->removeEventListener(flEvent::REMOVED, this, &flUIBase::_childEventHandler);
                _label = NULL;
            }
        }
        else if (event.type() == flEvent::REMOVED_FROM_STAGE) {

        }
        else if (event.type() == flEvent::REMOVED) {

        }
    }
    
}
