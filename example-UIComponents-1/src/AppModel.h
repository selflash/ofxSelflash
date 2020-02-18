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

        ofParameter<float> speed;
        ofParameter<ofColor> bgColor;

//        ofParameter<int> viewMode;
//        ofParameter<string> currentCameraPosition;

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
