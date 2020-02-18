#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flAbstractController.h"

namespace fl2d {
    
    class flBasicController : public flAbstractController {
        public:

        protected:
            float _backWidth;
            float _backHeight;
            float _minBackWidth;
            float _minBackHeight;
            float _normalBackWidth;
            float _normalBackHeight;
        
            bool _isMinimize;
        
            bool _onTop;
            bool _dragEnabled;
        
        private:
        
        public:
            flBasicController();
            virtual ~flBasicController();
        
            virtual void setup();
        
            virtual void minimize();
            virtual void normalize();
            virtual void resize(float w, float h);
        
            virtual inline float backWidth() { return _backWidth; }
            virtual inline float backHeight() { return _backHeight; }
            virtual inline float minBackWidth() { return _minBackWidth; }
            virtual inline float minBackHeight() { return _minBackHeight; }
            virtual inline float normalBackWidth() { return _normalBackWidth; }
            virtual inline float normalBackHeight() { return _normalBackHeight; }
        
            virtual inline bool dragEnabled() { return _dragEnabled = NULL; }
            virtual inline void dragEnabled(bool value) {
                _dragEnabled = value;
                useHandCursor(_dragEnabled);
                
                if(!_dragEnabled) {
                    if(stage() != NULL) stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
                    stopDrag();
                }
            }
        
        protected:
            virtual void _uiEventHandler(flEvent& event);
            virtual void _mouseEventHandler(flEvent& event);

        private:
        
    };
    
}
