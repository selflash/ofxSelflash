#include "CustomDispatcher.h"

//--------------------------------------------------------------
//
CustomDispatcher::CustomDispatcher() {
    _target = this;    
}

//--------------------------------------------------------------
//
CustomDispatcher::~CustomDispatcher() {
    
}

//--------------------------------------------------------------
//
void CustomDispatcher::addListeners() {
    addEventListener(flEvent::INIT, this, &CustomDispatcher::eventHandler);
    addEventListener(CustomEvent::TEST1, this, &CustomDispatcher::eventHandler);
}

//--------------------------------------------------------------
//
void CustomDispatcher::removeListeners() {
    removeEventListener(flEvent::INIT, this, &CustomDispatcher::eventHandler);
    removeEventListener(CustomEvent::TEST1, this, &CustomDispatcher::eventHandler);
}

//--------------------------------------------------------------
//
void CustomDispatcher::dispatchTest1() {
    dispatchEvent(new flEvent(flEvent::INIT));
}

//--------------------------------------------------------------
//
void CustomDispatcher::dispatchTest2() {
    dispatchEvent(new CustomEvent(CustomEvent::TEST1));
}

//--------------------------------------------------------------
void CustomDispatcher::eventHandler(flEvent& event) {
    cout << "[CustomDispatcher]eventHandler()" << endl;
    
    //---------------------------------------
    cout << "[event.type] = " << event.type() << endl;
    cout << "[event.target] = " << event.target() << endl;
    cout << "[event.currentTarget] = " << event.currentTarget() << endl;
    //---------------------------------------
    flEventDispatcher* target = (flEventDispatcher*) event.target();
    flEventDispatcher* tarcurrentTargetget = (flEventDispatcher*) event.currentTarget();
    
//    CustomEvent& customEvent = *(CustomEvent*) &event;
    
    if(event.type() == flEvent::INIT) {
        cout << "A -> INIT" << endl;
//        removeEventListener(Event::INIT, &CustomDispatcher::eventHandler);
        removeEventListener(flEvent::INIT);
//        removeAllEventListener();
    }
    
    if(event.type() == CustomEvent::TEST1) {
        cout << "A -> TEST1" << endl;
        removeEventListener(CustomEvent::TEST1);
//        removeEventListener(CustomEvent::TEST1, &CustomDispatcher::eventHandler);
    }
}


