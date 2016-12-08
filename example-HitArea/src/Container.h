#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

#include "InteractiveBox.h"

class Container : public flSprite {
    
    public:
        //--------------------------------------
        InteractiveBox* box100;
        InteractiveBox* box101;
        //--------------------------------------
        
    private:
        float _preX;
        float _preY;
        float _forceX;
        float _forceY;
        
    public:
        Container();
        virtual ~Container();
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        void _moveEventHandler(flEvent& event);
        void _mouseEventHandler(flEvent& event);
    
};
