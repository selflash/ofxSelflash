#pragma once

#include "ofMain.h"

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

class AppModel {
    public:
        ofParameter<AppStatus> status;
    
//        bool isLoaded;
//        bool isProcessing;
//        bool isFinding;
    
        ofParameter<ofColor> bgColor = ofColor(125, 124, 125, 220);
        ofParameter<ofColor> lineColor = ofColor(255, 124, 255, 255);
        ofParameter<int> lineWidth = 5;
        ofParameter<float> speed = 0.1;
        ofParameter<bool> fillEnabled = false;
        ofParameter<bool> wireframeEnabled = false;

    protected:
        
    private:

    
    public:
        AppModel();

//        string getStatusToString();

        void setup();
        void update();
    
    protected:
        
    private:
};
