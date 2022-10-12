#include "CustomDispatcher.h"

//--------------------------------------------------------------
CustomDispatcher::CustomDispatcher() {
    _target = this;    
}

//--------------------------------------------------------------
CustomDispatcher::~CustomDispatcher() {
    
}

//--------------------------------------------------------------
void CustomDispatcher::dispatchTest1() {
    dispatchEvent(new flEvent(flEvent::CHANGE));
}

//--------------------------------------------------------------
void CustomDispatcher::dispatchTest2() {
    dispatchEvent(new CustomEvent(CustomEvent::TEST1));
}
