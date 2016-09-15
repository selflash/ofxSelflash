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
void CustomDispatcher::dispatchTest1() {
    dispatchEvent(new flEvent(flEvent::INIT));
}

//--------------------------------------------------------------
//
void CustomDispatcher::dispatchTest2() {
    dispatchEvent(new CustomEvent(CustomEvent::TEST1));
}