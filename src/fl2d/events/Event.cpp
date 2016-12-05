#include "Event.h"

namespace fl2d {

    string Event::ADDED = "added";
    string Event::ADDED_TO_STAGE = "addedToStage";

    string Event::REMOVED = "removed";
    string Event::REMOVED_FROM_STAGE = "removedFromStage";

    //string Event::ACTIVATE = "activate";
    //string Event::DEACTIVATE = "deactivate";

    //string Event::OPEN = "open";
    string Event::CLOSE = "close";
    //string Event::CANCEL = "cancel";
    string Event::CHANGE = "change";
    string Event::COMPLETE = "complete";
    //string Event::CONNECT = "connect";
    string Event::ENTER_FRAME = "enterFrame";
    string Event::EXIT_FRAME = "exitFrame";
    //string Event::FULLSCREEN = "fullScreen";
    //string Event::ID3 = "id3";
    string Event::INIT = "init";
    //string Event::MOUSE_LEAVE = "mouseLeave";
    //string Event::RENDER = "render";
    //string Event::RESIZE = "resize";
    //string Event::SCROLL = "scroll";
    //string Event::SELECT = "select";
    //string Event::SOUND_COMPLETE = "soundComplete";
    //string Event::TAB_CHILDREN_CHANEG = "tabChildrenChange";
    //string Event::TAB_ENABLED_CHANGE = "tabEnabledChange";
    //string Event::TAB_INDEX_CHANGE = "tabIndexChange";
    //string Event::UNLOAD = "unload";

    //--------------------------------------------------------------
    //
    Event::Event(string type) {
//        cout << "[Event]Event1()" << endl;
        
        _type = type;
        
        _currentTarget = NULL;
        _target = NULL;
    }

    //--------------------------------------------------------------
    //
    Event::~Event() {
        _type = "";
        
        _currentTarget = NULL;
        _target = NULL;
    }
    
}
