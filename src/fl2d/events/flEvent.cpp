#include "flEvent.h"

namespace fl2d {
    
    string flEvent::ADDED = "added";
    string flEvent::ADDED_TO_STAGE = "addedToStage";
    
    string flEvent::REMOVED = "removed";
    string flEvent::REMOVED_FROM_STAGE = "removedFromStage";
    
    //string flEvent::ACTIVATE = "activate";
    //string flEvent::DEACTIVATE = "deactivate";
    
    //string flEvent::OPEN = "open";
    string flEvent::CLOSE = "close";
    //string flEvent::CANCEL = "cancel";
    string flEvent::CHANGE = "change";
    string flEvent::COMPLETE = "complete";
    //string flEvent::CONNECT = "connect";
    string flEvent::ENTER_FRAME = "enterFrame";
    string flEvent::EXIT_FRAME = "exitFrame";
    //string flflEvent::FULLSCREEN = "fullScreen";
    //string flflEvent::ID3 = "id3";
    string flEvent::INIT = "init";
    //string flEvent::MOUSE_LEAVE = "mouseLeave";
    //string flEvent::RENDER = "render";
    //string flEvent::RESIZE = "resize";
    //string flEvent::SCROLL = "scroll";
    //string flEvent::SELECT = "select";
    //string flEvent::SOUND_COMPLETE = "soundComplete";
    //string flEvent::TAB_CHILDREN_CHANEG = "tabChildrenChange";
    //string flEvent::TAB_ENABLED_CHANGE = "tabEnabledChange";
    //string flEvent::TAB_INDEX_CHANGE = "tabIndexChange";
    //string flEvent::UNLOAD = "unload";
    
    //--------------------------------------------------------------
    //
    flEvent::flEvent(string type) {
        //        cout << "[flEvent]flEvent1()" << endl;
        
        _type = type;
        
        _currentTarget = NULL;
        _target = NULL;
    }
    
    //--------------------------------------------------------------
    //
    flEvent::~flEvent() {
        _type = "";
        
        _currentTarget = NULL;
        _target = NULL;
    }
    
}
