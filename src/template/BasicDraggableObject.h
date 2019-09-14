#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

namespace fltemplate {
    
    class BasicDraggableObject : public flSprite {
    public:
        
    protected:
        bool _dragEnabled = true;
        
    private:
        
    public:
        BasicDraggableObject();
        virtual ~BasicDraggableObject();
        
        virtual inline bool dragEnabled() { return _dragEnabled; }
        virtual inline void dragEnabled(bool value) {
            _dragEnabled = value;
            useHandCursor(_dragEnabled);
            
            if(!_dragEnabled) {
                if(stage() != NULL) stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &BasicDraggableObject::_mouseEventHandler);
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
