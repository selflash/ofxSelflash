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
    //string Event::ENTER_FRAME = "enterFrame";
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
        _listener = NULL;
    }

    //--------------------------------------------------------------
    //
    Event::~Event() {
        _type = "";
        
        _currentTarget = NULL;
        _target = NULL;
        _listener = NULL;
    }

    //--------------------------------------------------------------
    //
    Event* Event::clone() { return new Event(_type); }

    //--------------------------------------------------------------
    //
    const string& Event::type() { return _type; }

    //--------------------------------------------------------------
    //
    void* Event::currentTarget() { return _currentTarget; }
    void Event::currentTarget(void* value) { _currentTarget = value; }

    //--------------------------------------------------------------
    //
    void* Event::target() { return _target; }
    void Event::target(void* value) { _target = value; }

    //--------------------------------------------------------------
    //
    void* Event::listener() { return _listener; }
}
