#include "flBasicDraggableObject.h"

namespace fl2d {
    
    //==============================================================
	// Constructor / Destructor
	//==============================================================
    
    //--------------------------------------------------------------
    flBasicDraggableObject::flBasicDraggableObject() {
        //ofLog() << "[flBasicDraggableObject]flBasicDraggableObject()";
        _target = this;
        name("flBasicDraggableObject");
        
        useHandCursor(true);

		addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicDraggableObject::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    flBasicDraggableObject::~flBasicDraggableObject() {
        //ofLog() << "[flBasicDraggableObject]~flBasicDraggableObject()";
        
		if (stage()) {
			if (stage()->hasEventListener(flMouseEvent::MOUSE_UP)) {
				stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicDraggableObject::_mouseEventHandler);
			}
		}

        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicDraggableObject::_mouseEventHandler);
    }
    
    //==============================================================
	// Setup / Update / Draw
	//==============================================================
    
    //--------------------------------------------------------------
    void flBasicDraggableObject::_setup() {
		//ofLog() << "[flBasicDraggableObject]_setup()";

		flSprite::_setup();

		//addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicDraggableObject::_mouseEventHandler);
    }
 
	//==============================================================
	// Public Method
	//==============================================================

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

		//flSprite::_mouseEventHandler(event);

		//Roll Over
		if (event.type() == flMouseEvent::ROLL_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Roll Out
		if (event.type() == flMouseEvent::ROLL_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Over
		if (event.type() == flMouseEvent::MOUSE_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Out
		if (event.type() == flMouseEvent::MOUSE_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

			if (target == (hitArea() != NULL ? hitArea() : this)) {
                if(_dragEnabled) {
                    if(_moveFrontOnSelect) ((flDisplayObjectContainer*)parent())->addChild(this);
                    startDrag();
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicDraggableObject::_mouseEventHandler);
                }
            }
        }

		//Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

            //if(currentTarget == stage()) {
			if (target == stage()) {
				if (_dragEnabled) {
					stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicDraggableObject::_mouseEventHandler);
					stopDrag();
				}
			}
        }
    }
    
}
