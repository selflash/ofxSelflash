#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicDraggableObject.h"

using namespace fl2d;

class FrameBorder4 : public flBasicDraggableObject {
public:
    
protected:
    
private:
    ofVideoGrabber _vidGrabber;
    ofTexture _videoTexture;
//    flBitmap* bitmap;
public:
    
protected:
    virtual void _setup();
    virtual void _update();
    virtual void _draw();
    
private:
    
};
