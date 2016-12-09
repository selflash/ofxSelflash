#include "EventDispatcher.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    EventDispatcher::EventDispatcher() {
        _typeID = FL_TYPE_EVENT_DISPATCHER;
        _target = this;

        _debugEnabled = false;
    }

    //--------------------------------------------------------------
    //
    EventDispatcher::~EventDispatcher() {
        _target = NULL;
        
        _debugEnabled = false;
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void EventDispatcher::dispatchEvent(Event* event) {
        event->currentTarget(_target);
        if(!event->target()) event->target(_target);
        
        ofNotifyEvent(_handlers[event->type()], *event);
        
        delete event;
    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================

}
