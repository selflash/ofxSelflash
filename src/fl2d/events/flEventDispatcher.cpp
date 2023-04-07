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
        _target = nullptr;
        
        _debugEnabled = false;
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flEventDispatcher::dispatchEvent(flEvent* event, bool destry) {
        //イベントリスナが関連付けられたオブジェクト
        if (event->__currentTarget == nullptr) event->__currentTarget = _target;
        //直接XXXXされたオブジェクト
        if(event->__target == nullptr) event->__target = _target;
        
         ofNotifyEvent(_listeners[event->type()], *event);
        
         try {
             if (destry) delete event;
         }
         catch (...)
         {

         }
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================

}
