#pragma once

#include "ofMain.h"

#include "flShape.h"
#include "flSprite.h"
#include "flTextField.h"

namespace fl2d {
    
    class flScrollKit : public flSprite {
        
    public:
        flShape* base;
        
        ofRectangle viewport;
        
    protected:
        
    private:
        flDisplayObject* _body;
        
        float _disy;
        
    public:
        flScrollKit();
        virtual ~flScrollKit();
        
        flDisplayObject* body();
        void body(flDisplayObject* value);
        
        void drawViewportOutline(const ofRectangle & viewport);
        
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:        
        void _mouseEventHandler(flEvent& event);
        void _moveEventHandler(flEvent& event);
    };
    
}
