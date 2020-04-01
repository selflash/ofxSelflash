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
        
        _toolTip = new flToolTip();
        
        addEventListener(flMouseEvent::ROLL_OVER, this, &flUIBase::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flUIBase::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    flUIBase::~flUIBase() {
//        ofLog() << "[flUIBase]~flUIBase()";
        
        _label = NULL;
        
        delete _toolTip;
        _toolTip = NULL;
    
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flUIBase::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flUIBase::_mouseEventHandler);
        
        _bChangedByMyself.clear();
        _bChangedByOfParm.clear();

    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flUIBase::_update() {
//        if(
//           _mouseWhenRollOver.x != ((flStage*)stage())->mouseX() ||
//           _mouseWhenRollOver.y != ((flStage*)stage())->mouseY()
//           ) {
//            _showToolTip = false;
//        }
        
        if(_toolTipEnabled && _toolTip->visible()) {
            _toolTip->x(((flStage*)stage())->mouseX() + 30);
            _toolTip->y(((flStage*)stage())->mouseY() + 10);
        }
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    bool flUIBase::toolTipEnabled() { return _toolTipEnabled; }
    void flUIBase::toolTipEnabled(bool value) {
        _toolTipEnabled = value;
    }

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
    
    //--------------------------------------------------------------
    void flUIBase::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flUIBase]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flUIBase]this          = " << this << "," << ((flDisplayObject*) this)->name();
//        ofLog() << "[flUIBase]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flUIBase]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) {
                if(_toolTipEnabled) {
//                    _showToolTip = true;
                    _toolTip->visible(true);
                    _mouseWhenRollOver.x = ((flStage*)stage())->mouseX();
                    _mouseWhenRollOver.y = ((flStage*)stage())->mouseY();

                    _toolTip->x(((flStage*)stage())->mouseX() + 20);
                    _toolTip->y(((flStage*)stage())->mouseY() + 10);
                    ((flStage*)stage())->addChild(_toolTip);
                }
            }
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) {
                if(_toolTipEnabled) {
//                    _showToolTip = false;
                    _toolTip->visible(false);

                    if(_toolTip->parent() != NULL) {
                        ((flStage*)stage())->removeChild(_toolTip);
                    }
                }
            }
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            
        }
    }
    
}
