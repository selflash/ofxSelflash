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
    void flEventDispatcher::dispatchEvent(flEvent* event, bool destry) {
        //�C�x���g���X�i���֘A�t����ꂽ�I�u�W�F�N�g
        event->__currentTarget = _target;
        //����XXXX���ꂽ�I�u�W�F�N�g
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
