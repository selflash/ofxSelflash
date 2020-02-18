#include "AppModel.h"

//--------------------------------------------------------------
//
AppModel::AppModel() {
    status = APPSTATUS_NOT_LOADED;

    speed = 0.1;
    bgColor = ofColor(125, 124, 125, 220);
    lineWidth = 1;
    
//    isLoaded = false;
//    isProcessing = false;
//    isFinding = false;

//    viewMode = 0;
//    currentCameraPosition.set("front");
}

//--------------------------------------------------------------
//
void AppModel::setup() {
//    ofLog() << "[AppModel]setup()";

}

//--------------------------------------------------------------
void AppModel::update() {
    
}

//--------------------------------------------------------------
//string AppModel::getStatusToString() {
//    if(status == APPSTATUS_NOT_LOADED) return "Finding Next a Scanned Model.";
//    if(status == APPSTATUS_LOADED) return "Scanned Model is Loaded.";
//    if(status == APPSTATUS_PROCESSING) return "Now Processing..";
//    if(status == APPSTATUS_FINDING) return "Now Processing...";
//}
