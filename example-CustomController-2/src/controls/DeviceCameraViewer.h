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
#include "FrameBorder4.h"

using namespace fl2d;

class DeviceCameraViewer : public flBasicController {
    
    public:
        
    protected:
        string _status;
        
    private:
        FrameBorder4* _frameBorder1;
//        FrameBorder4* frameBorder2;

    public:
        DeviceCameraViewer(string title = "Sub Controller");
        virtual ~DeviceCameraViewer();
        
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
