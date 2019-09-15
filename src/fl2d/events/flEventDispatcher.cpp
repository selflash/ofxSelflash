#include "flEventDispatcher.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flEventDispatcher::flEventDispatcher() {
        _typeID = FL_TYPE_EVENT_DISPATCHER;
        _target = this;
        
        _debugEnabled = false;
    }
    
    //--------------------------------------------------------------
    //
    flEventDispatcher::~flEventDispatcher() {
        _target = NULL;
        
        _debugEnabled = false;
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flEventDispatcher::dispatchEvent(flEvent* event) {
        event->currentTarget(_target);
        if(!event->target()) event->target(_target);
        
        ofNotifyEvent(_handlers[event->type()], *event);
        
        delete event;
    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
}
