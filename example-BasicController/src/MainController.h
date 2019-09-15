//
//  MainController.h
//  ofApp
//
//  Created by 横田達也 on 2016/12/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicController.h"

#include "SubController1.h"
#include "SubController2.h"
#include "NativeWindow.h"

using namespace fl2d;

class MainController : public flBasicController {
    
public:
    
protected:
    
private:
    //サブコントローラー
    flBasicController* _controller1 = NULL;
    flBasicController* _controller2 = NULL;
    
public:
    MainController();
    virtual ~MainController();
    
    //virtual void setup();
    //virtual void update();
    //virtual void draw();
    
    virtual void normalize();
    
    void toggleShowAll();
    
    //サブコントローラー
    inline flBasicController* controller1() { return _controller1; }
    inline flBasicController* controller2() { return _controller2; }
    
protected:
    virtual void _setup();
    virtual void _update();
    virtual void _draw();
    
private:
    virtual void _uiEventHandler(flEvent& event);
    
};
