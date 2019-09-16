#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

#include "CustomSpriteA.h"

using namespace fl2d;

class Container : public flSprite {
    
public:
    CustomSpriteA* spriteA;
    CustomSpriteA* spriteB;
    
private:
    
public:
    Container();
    virtual ~Container();
    
protected:
    virtual void _setup();
    virtual void _update();
    virtual void _draw();
    
private:
};
