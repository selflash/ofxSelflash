#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

#include "CustomSpriteA.h"

class Container : public flSprite {
    
    public:
        CustomSpriteA* spriteA;
        CustomSpriteA* spriteB;
    
    private:
    
    public:
        Container();
        ~Container();
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
    
    private:
};