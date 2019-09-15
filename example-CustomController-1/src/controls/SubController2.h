//
//  SubController.hpp
//  ofApp
//
//  Created by 横田達也 on 2016/06/07.
//
//

#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicController.h"

using namespace fl2d;

class SubController2 : public flBasicController {
    
    public:
        
    protected:
        string _status;
        
    private:
        map<string, map<string, ofVec3f> > _params;
        string _targetJointName;
    
    public:
        SubController2(string title = "Sub Controller");
        virtual ~SubController2();
        
        //virtual void setup();
        //virtual void update();
        //virtual void draw();
    
        string targetJointName();
        void targetJointName(string value);
    
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        virtual void _uiEventHandler(flEvent& event);
        
};
