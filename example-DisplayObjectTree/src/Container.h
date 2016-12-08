#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

#include "InteractiveBox.h"

class Container : public flSprite {
    
    public:
        //--------------------------------------
        InteractiveBox* box1;
        InteractiveBox* box1_1;
        InteractiveBox* box1_2;
        
        InteractiveBox* box2;
        InteractiveBox* box2_1;
        InteractiveBox* box2_2;
        
        InteractiveBox* box3;
        InteractiveBox* box3_1;
        InteractiveBox* box3_2;

        InteractiveBox* box4;
        InteractiveBox* box4_1;
        InteractiveBox* box4_1_1;
        
        InteractiveBox* box5;
        InteractiveBox* box5_1;
        InteractiveBox* box5_1_1;
        
        InteractiveBox* box6;
        InteractiveBox* box6_1;
        InteractiveBox* box6_1_1;
        
        InteractiveBox* box7;
        InteractiveBox* box7_1;
        InteractiveBox* box7_1_1;
        
        InteractiveBox* box8;
        InteractiveBox* box8_1;
        InteractiveBox* box8_1_1;
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
        
        void _setupBoxes();
    
    private:
        void _moveEventHandler(flEvent& event);
        void _mouseEventHandler(flEvent& event);
    
};
