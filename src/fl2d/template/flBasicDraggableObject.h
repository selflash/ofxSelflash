#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

namespace fl2d {
    
    class flBasicDraggableObject : public flSprite {
    public:
        
    protected:
        bool _dragEnabled = true;
        
    private:
        
    public:
        flBasicDraggableObject();
        virtual ~flBasicDraggableObject();
        
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
        //        virtual void _setup();
        //        virtual void _update();
        //        virtual void _draw();
        
    private:
        void _mouseEventHandler(flEvent& event);
        
    };
    
}
