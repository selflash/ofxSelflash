#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicController.h"

using namespace fl2d;

class SubController1 : public flBasicController {
    
public:
    
protected:
    
private:
    
public:
    SubController1(string title = "Sub Controller");
    virtual ~SubController1();
    
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
