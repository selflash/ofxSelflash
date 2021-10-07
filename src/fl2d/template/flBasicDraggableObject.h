#pragma once

#include "ofMain.h"
#include "flSprite.h"

namespace fl2d {
    
    class flBasicDraggableObject : public flSprite {
		public:
        
		protected:
			bool _dragEnabled = true;
			bool _moveFrontOnSelect = true;        

		private:
        
		public:
			flBasicDraggableObject();
			virtual ~flBasicDraggableObject();

			virtual void setup();

			virtual inline bool moveFrontOnSelect() { return _moveFrontOnSelect; }
			virtual inline void moveFrontOnSelect(bool value) { _moveFrontOnSelect = value; }        

			virtual inline bool dragEnabled() { return _dragEnabled; }
			virtual inline void dragEnabled(bool value) {
				_dragEnabled = value;
				useHandCursor(_dragEnabled);
            
				if(!_dragEnabled) {
					if(stage() != NULL) stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicDraggableObject::_mouseEventHandler);
					stopDrag();
				}
			}
        
		protected:
			//virtual void _setup();			    
			//virtual void _update();
			//virtual void _draw();

			virtual void _mouseEventHandler(flEvent& event);

		private:
        
    };
    
}
