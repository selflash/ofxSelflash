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
    flBitmap* _colorBitmap = NULL;

    protected:
        string _status;

    private:
        flSprite* _colorViewer = NULL;

        flSprite* _depthViewer = NULL;
        flBitmap* _depthBitmap = NULL;

        flSprite* _irViewer = NULL;
        flBitmap* _irBitmap = NULL;

        flSprite* _depthInColorViewer = NULL;
        flBitmap* _depthInColorBitmap = NULL;
    
        flSprite* _colorInDepthViewer = NULL;
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
