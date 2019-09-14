#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

class DocumentRoot : public flSprite {
public:
    float counter;
    bool bSmooth;
    
private:
    float _preX = 0.0;
    float _preY = 0.0;
    float _forceX = 0.0;
    float _forceY = 0.0;
    
public:
    DocumentRoot();
    ~DocumentRoot();
    
    void init();
    void init(flEvent& event);
    
protected:
    virtual void _setup();
    virtual void _update();
    virtual void _draw();
    
private:
    void _eventHandler(flEvent& event);
    void _keyboardEventHandler(flEvent& event);
    void _moveEventHandler(flEvent& event);
    void _mouseEventHandler(flEvent& event);
    
};
