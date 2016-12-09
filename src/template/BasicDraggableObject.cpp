#include "BasicDraggableObject.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
BasicDraggableObject::BasicDraggableObject() {
//    cout << "[BasicDraggableObject]BasicDraggableObject()" << endl;
    _target = this;
    name("BasicDraggableObject");
    
    useHandCursor(true);
    
    addEventListener(flMouseEvent::MOUSE_DOWN, this, &BasicDraggableObject::_mouseEventHandler);
}

//--------------------------------------------------------------
//
BasicDraggableObject::~BasicDraggableObject() {
//    cout << "[BasicDraggableObject]~BasicDraggableObject()" << endl;
    
    removeEventListener(flMouseEvent::MOUSE_DOWN, this, &BasicDraggableObject::_mouseEventHandler);
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
//void BasicDraggableObject::_setup() {
//    cout << "[BasicDraggableObject]_setup()" << endl;
//
//}

//--------------------------------------------------------------
//
//void BasicDraggableObject::_update() {
////    cout << width() << ", " << height() << endl;
//    
//}

//--------------------------------------------------------------
//
//void BasicDraggableObject::_draw() {
//    
//}

//==============================================================
// PROTECTED / PRIVATE METHOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================


//--------------------------------------------------------------
//
void BasicDraggableObject::_mouseEventHandler(flEvent& event) {
//    cout << "[BasicDraggableObject]_mouseEventHandler(" << event.type() << ")" << endl;
//    cout << "[PrentBox]this          = " << this << endl;
//    cout << "[ParetBox]currentTarget = " << event.currentTarget() << endl;
//    cout << "[ParetBox]target        = " << event.target() << endl;
    
    if(event.type() == flMouseEvent::MOUSE_DOWN) {
        if(event.target() == this) {
            if(_dragEnabled) {
                ((DisplayObjectContainer*)parent())->addChild(this);
                startDrag();
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &BasicDraggableObject::_mouseEventHandler);
            }
        }
    }
    if(event.type() == flMouseEvent::MOUSE_UP) {
        if(event.currentTarget() == stage()) {
            stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &BasicDraggableObject::_mouseEventHandler);            
            stopDrag();
        }
    }
}
