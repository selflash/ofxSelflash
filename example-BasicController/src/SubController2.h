//
//  SubController2.h
//  ofApp
//
//  Created by 横田達也 on 2016/12/15.
//
//

#pragma once

#include "ofMain.h"
#include "../../addons/ofxSelflash/src/ofxSelflash.h"
#include "../../addons/ofxSelflash/src/template/BasicController.h"

class SubController2 : public BasicController {
    
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
