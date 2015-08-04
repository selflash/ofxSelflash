#include "EventDispatcher.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    EventDispatcher::EventDispatcher(){
        _typeID = TYPE_EVENT_DISPATCHER;
        _target = this;
        
        _isDispatchEvent = "";
        _removeEventType = "";

        _debugEnabled = false;
    }

    //--------------------------------------------------------------
    //
    EventDispatcher::~EventDispatcher(){
        _target = NULL;
        
        _isDispatchEvent = "";
        _removeEventType = "";
        
        handler = NULL;
        _eventHandlerList.clear();
        
        _debugEnabled = false;
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //==============================================================
    // PRIVATE METHOD
    //==============================================================

}