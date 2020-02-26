#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicDraggableObject.h"

using namespace fl2d;
using namespace glm;

enum AppStatus {
    APPSTATUS_NONE = 0,
    APPSTATUS_NOT_FOUND_CONFIGXML,
    APPSTATUS_INVALID_PATH,
    APPSTATUS_FOUND_DIRECTORIES,
    APPSTATUS_NOT_LOADED,
    APPSTATUS_LOADED,
    APPSTATUS_PROCESSING,
    APPSTATUS_FINDING
};

class AppModel : public flBasicDraggableObject {
    public:
        ofParameter<AppStatus> status;
    
//        bool isLoaded;
//        bool isProcessing;
//        bool isFinding;
    
        ofParameter<ofColor> bgColor = ofColor(125, 124, 125, 220);
    
//        ofParameter<vec2> cameraPosXY = vec2(0, 0);
//        ofParameter<float> cameraPosZ = 100;

        ofParameter<vec2> cameraPosVelXY = vec2(0, 0);
        ofParameter<float> cameraPosVelZ = 0;

        ofParameter<ofColor> lineColor = ofColor(255, 124, 255, 255);
        ofParameter<int> lineWidth = 5;
        ofParameter<float> speed = 0.1;
        ofParameter<bool> fillEnabled = false;
        ofParameter<bool> wireframeEnabled = false;

        ofParameter<float> left = -50.0;
        ofParameter<float> right = 50.0;

    protected:
        
    private:

    
    public:
        AppModel();
    
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
    
    private:
};
