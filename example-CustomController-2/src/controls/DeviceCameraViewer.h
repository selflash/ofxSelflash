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
#include "CameraViewer.h"

using namespace fl2d;

class DeviceCameraViewer : public flBasicController {
    
    public:
        
    protected:
        string _status;
        
    private:
        flShape* _colorCameraViewer = NULL;
        flBitmap* _colorBitmap = NULL;

        flShape* _depthCameraViewer = NULL;
        flBitmap* _depthBitmap = NULL;

        flShape* _irCameraViewer = NULL;
        flBitmap* _irBitmap = NULL;
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
