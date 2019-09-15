#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicController.h"

using namespace fl2d;

class SubController2 : public flBasicController {
    
public:
    
protected:
    
private:
    
public:
    SubController2(string title = "Sub Controller");
    virtual ~SubController2();
    
    //virtual void setup();
    //virtual void update();
    //virtual void draw();
    
protected:
    virtual void _setup();
    virtual void _update();
    virtual void _draw();
    
private:
    virtual void _uiEventHandler(flEvent& event);
    
};
