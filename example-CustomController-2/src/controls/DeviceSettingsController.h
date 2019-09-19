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
        flBitmap* _depthBitmap = NULL;
        flBitmap* _irBitmap = NULL;
        flBitmap* _depthInColorBitmap = NULL;
        flBitmap* _colorInDepthBitmap = NULL;

    protected:
        string _status;

    private:
        flSprite* _colorViewer = NULL;

        flSprite* _depthViewer = NULL;

        flSprite* _irViewer = NULL;

        flSprite* _depthInColorViewer = NULL;
    
        flSprite* _colorInDepthViewer = NULL;

    
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
