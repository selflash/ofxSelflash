#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flAbstractController.h"

using namespace fl2d;

class UIComponents : public flAbstractController {
    public:
        flRadioButtonGroup* radioButtonGroup;

//        //--------------------------------------
//        flScrollKit* scrollKit001;
//        flSprite* body001;
//        //--------------------------------------
    
    private:
    
    public:
        UIComponents();
        virtual ~UIComponents();
    
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();

        virtual void _uiEventHandler(flEvent& event);

    private:
};
