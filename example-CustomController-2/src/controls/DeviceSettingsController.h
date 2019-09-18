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

class DeviceSettingsController : public flBasicController {
    
    public:
        
    protected:
        string _status;
        
    private:
        flShape* _colorViewer = NULL;
        flBitmap* _colorBitmap = NULL;

        flShape* _depthViewer = NULL;
        flBitmap* _depthBitmap = NULL;

        flShape* _irViewer = NULL;
        flBitmap* _irBitmap = NULL;

        flShape* _depthInColorViewer = NULL;
        flBitmap* _depthInColorBitmap = NULL;
    
        flShape* _colorInDepthViewer = NULL;
        flBitmap* _colorInDepthBitmap = NULL;

    
    public:
        DeviceSettingsController(string title = "Sub Controller");
        virtual ~DeviceSettingsController();
        
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
