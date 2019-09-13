//
//  MainController.h
//  ofApp
//
//  Created by 横田達也 on 2016/12/15.
//
//

#pragma once

#include "ofMain.h"
#include "../../addons/ofxSelflash/src/ofxSelflash.h"
#include "../../addons/ofxSelflash/src/template/BasicController.h"

#include "./SubController1.h"
#include "./SubController2.h"
#include "./NativeWindow.h"

class MainController : public BasicController {
    
    public:
        
    protected:
        
    private:
        //サブコントローラー
        BasicController* _controller1 = NULL;
        BasicController* _controller2 = NULL;
        
    public:
        MainController();
        virtual ~MainController();
        
        //virtual void setup();
        //virtual void update();
        //virtual void draw();
        
        virtual void normalize();
        
        void toggleShowAll();
        
        //サブコントローラー
        inline BasicController* controller1() { return _controller1; }
        inline BasicController* controller2() { return _controller2; }
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        virtual void _uiEventHandler(flEvent& event);
        
};
