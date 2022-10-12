#include "CustomDispatcher.h"

//--------------------------------------------------------------
CustomDispatcher::CustomDispatcher() {
    _target = this;    
}

//--------------------------------------------------------------
CustomDispatcher::~CustomDispatcher() {
    
}

//--------------------------------------------------------------
void CustomDispatcher::addListeners() {
    addEventListener(flEvent::CHANGE, this, &CustomDispatcher::eventHandler);
    addEventListener(CustomEvent::TEST1, this, &CustomDispatcher::eventHandler);
}

//--------------------------------------------------------------
void CustomDispatcher::removeListeners() {
    removeEventListener(flEvent::CHANGE, this, &CustomDispatcher::eventHandler);
    removeEventListener(CustomEvent::TEST1, this, &CustomDispatcher::eventHandler);
}

//--------------------------------------------------------------
void CustomDispatcher::dispatchTest1() {
    dispatchEvent(new flEvent(flEvent::CHANGE));
}

//--------------------------------------------------------------
void CustomDispatcher::dispatchTest2() {
    dispatchEvent(new CustomEvent(CustomEvent::TEST1));
}

//--------------------------------------------------------------
void CustomDispatcher::eventHandler(flEvent& event) {
    ofLog() << "[CustomDispatcher]eventHandler()";
    
    //---------------------------------------
    ofLog() << "[event.type] = " << event.type();
    ofLog() << "[event.target] = " << event.target();
    ofLog() << "[event.currentTarget] = " << event.currentTarget();
    //---------------------------------------
    flEventDispatcher* target = (flEventDispatcher*) event.target();
    flEventDispatcher* tarcurrentTargetget = (flEventDispatcher*) event.currentTarget();
    
    //    CustomEvent& customEvent = *(CustomEvent*) &event;
    
    if(event.type() == flEvent::CHANGE) {
        ofLog() << "A -> CHANGE";
        //        removeEventListener(Event::CHANGE, &CustomDispatcher::eventHandler);
        removeEventListeners(flEvent::CHANGE);
        //        removeAllEventListener();
    }
    
    if(event.type() == CustomEvent::TEST1) {
        ofLog() << "A -> TEST1";
        removeEventListeners(CustomEvent::TEST1);
        //        removeEventListener(CustomEvent::TEST1, &CustomDispatcher::eventHandler);
    }
}


