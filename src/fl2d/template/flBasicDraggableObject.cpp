#include "flBasicDraggableObject.h"

namespace fl2d {
    
    //==============================================================
	// Constructor / Destructor
	//==============================================================
    
    //--------------------------------------------------------------
    flBasicDraggableObject::flBasicDraggableObject() {
        //    cout << "[flBasicDraggableObject]flBasicDraggableObject()" << endl;
        _target = this;
        name("flBasicDraggableObject");
        
        useHandCursor(true);
        
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicDraggableObject::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    flBasicDraggableObject::~flBasicDraggableObject() {
        //    cout << "[flBasicDraggableObject]~flBasicDraggableObject()" << endl;
        
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicDraggableObject::_mouseEventHandler);
    }
    
    //==============================================================
	// Setup / Update / Draw
	//==============================================================
    
    //--------------------------------------------------------------
    //void flBasicDraggableObject::_setup() {
    //    cout << "[flBasicDraggableObject]_setup()" << endl;
    //
    //}
    
    //--------------------------------------------------------------
    //void flBasicDraggableObject::_update() {
    ////    cout << width() << ", " << height() << endl;
    //    
    //}
    
    //--------------------------------------------------------------
    //void flBasicDraggableObject::_draw() {
    //    
    //}
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //==============================================================
    // Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flBasicDraggableObject::_mouseEventHandler(flEvent& event) {
		//ofLog() << "[flBasicDraggableObject]_mouseEventHandler(" << event.type() << ")";
		//ofLog() << "[flBasicDraggableObject]this          = " << this;
		//ofLog() << "[flBasicDraggableObject]currentTarget = " << event.currentTarget();
		//ofLog() << "[flBasicDraggableObject]target        = " << event.target();

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
