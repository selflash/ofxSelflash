#pragma once

#include "ofMain.h"
#include "flBasicUIWindow.h"

namespace fl2d {
    
    class flBasicController : public flBasicUIWindow {
        public:

        protected:
        
        private:
        
        public:
            flBasicController();
            virtual ~flBasicController();

			//virtual inline bool moveFrontOnSelect() { return _moveFrontOnSelect; }
			//virtual inline void moveFrontOnSelect(bool value) { _moveFrontOnSelect = value; }

            //virtual inline bool dragEnabled() { return _dragEnabled; }
            //virtual inline void dragEnabled(bool value) {
            //    _dragEnabled = value;
            //    useHandCursor(_dragEnabled);

            //    if(!_dragEnabled) {
            //        if(stage() != NULL) stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_flBasicControllerMouseEventHandler);
            //        stopDrag();
            //    }
            //}
        
        protected:
			virtual void _mouseEventHandler(flEvent& event);
			virtual void _uiEventHandler(flEvent& event);

        private:
        
    };
    
}
