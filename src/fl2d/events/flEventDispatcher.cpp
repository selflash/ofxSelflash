﻿#include "flEventDispatcher.h"

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
    void flEventDispatcher::dispatchEvent(flEvent* event, bool destry) {
        //イベントリスナが関連付けられたオブジェクト
        event->__currentTarget = _target;
        //直接XXXXされたオブジェクト
        if(event->__target == NULL) event->__target = _target;
        
         ofNotifyEvent(_listeners[event->type()], *event);
        
        if(destry) delete event;
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================

}
