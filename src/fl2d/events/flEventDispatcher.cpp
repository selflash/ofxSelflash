#include "flEventDispatcher.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flEventDispatcher::flEventDispatcher() {
        _typeID = FL_TYPE_EVENT_DISPATCHER;
        _target = this;
        
        _debugEnabled = false;
    }
    
    //--------------------------------------------------------------
    flEventDispatcher::~flEventDispatcher() {
        _target = NULL;
        
        _debugEnabled = false;
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flEventDispatcher::dispatchEvent(flEvent* event) {
        event->__currentTarget = _target;
        if(event->__target == NULL) event->__target = _target;
        
        ofNotifyEvent(_handlers[event->type()], *event);
        
        delete event;
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
}
