#include "flBasicDraggableObject.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flBasicDraggableObject::flBasicDraggableObject() {
        //    cout << "[flBasicDraggableObject]flBasicDraggableObject()" << endl;
        _target = this;
        name("flBasicDraggableObject");
        
        useHandCursor(true);
        
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicDraggableObject::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    //
    flBasicDraggableObject::~flBasicDraggableObject() {
        //    cout << "[flBasicDraggableObject]~flBasicDraggableObject()" << endl;
        
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicDraggableObject::_mouseEventHandler);
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    //void flBasicDraggableObject::_setup() {
    //    cout << "[flBasicDraggableObject]_setup()" << endl;
    //
    //}
    
    //--------------------------------------------------------------
    //
    //void flBasicDraggableObject::_update() {
    ////    cout << width() << ", " << height() << endl;
    //    
    //}
    
    //--------------------------------------------------------------
    //
    //void flBasicDraggableObject::_draw() {
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
    void flBasicDraggableObject::_mouseEventHandler(flEvent& event) {
        //    cout << "[flBasicDraggableObject]_mouseEventHandler(" << event.type() << ")" << endl;
        //    cout << "[PrentBox]this          = " << this << endl;
        //    cout << "[ParetBox]currentTarget = " << event.currentTarget() << endl;
        //    cout << "[ParetBox]target        = " << event.target() << endl;
        
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) {
                if(_dragEnabled) {
                    ((flDisplayObjectContainer*)parent())->addChild(this);
                    startDrag();
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicDraggableObject::_mouseEventHandler);
                }
            }
        }
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(event.currentTarget() == stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicDraggableObject::_mouseEventHandler);
                stopDrag();
            }
        }
    }
    
}
