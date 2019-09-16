#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

using namespace fl2d;

class MainView : public flSprite {
public:
    int type = 0;

private:
    int _fontSize = 25;

public:
    MainView();
    ~MainView();
    
protected:
    virtual void _setup();
    virtual void _update();
    virtual void _draw();
    
private:
    void _eventHandler(flEvent& event);
    void _moveEventHandler(flEvent& event);
    void _mouseEventHandler(flEvent& event);
    
};
