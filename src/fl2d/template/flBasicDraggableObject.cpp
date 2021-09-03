#include "flBasicDraggableObject.h"

namespace fl2d {
    
    //==============================================================
	// Constructor / Destructor
	//==============================================================
    
    //--------------------------------------------------------------
    flBasicDraggableObject::flBasicDraggableObject() {
        //    ofLog(OF_LOG_NOTICE) << "[flBasicDraggableObject]flBasicDraggableObject()";
        _target = this;
        name("flBasicDraggableObject");
        
        useHandCursor(true);
        
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicDraggableObject::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    flBasicDraggableObject::~flBasicDraggableObject() {
        //    ofLog(OF_LOG_NOTICE) << "[flBasicDraggableObject]~flBasicDraggableObject()";
        
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
		//ofLog(OF_LOG_NOTICE) << "[flBasicDraggableObject]_mouseEventHandler(" << event.type() << ")";
		//ofLog(OF_LOG_NOTICE) << "[flBasicDraggableObject]this          = " << this;
		//ofLog(OF_LOG_NOTICE) << "[flBasicDraggableObject]currentTarget = " << event.currentTarget();
		//ofLog(OF_LOG_NOTICE) << "[flBasicDraggableObject]target        = " << event.target();

		//Roll Over
		if (event.type() == flMouseEvent::ROLL_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			if (event.target() == this) {

			}
		}

		//Roll Out
		if (event.type() == flMouseEvent::ROLL_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			if (event.target() == this) {

			}
		}

		//Mouse Over
		if (event.type() == flMouseEvent::MOUSE_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			if (event.target() == this) {

			}
		}

		//Mouse Out
		if (event.type() == flMouseEvent::MOUSE_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			if (event.target() == this) {

			}
		}

        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) {
                if(_dragEnabled) {
                    if(_moveFrontOnSelect) ((flDisplayObjectContainer*)parent())->addChild(this);
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
