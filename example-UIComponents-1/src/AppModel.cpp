#include "AppModel.h"

//--------------------------------------------------------------
//
AppModel::AppModel() {
    status = APPSTATUS_NOT_LOADED;

    
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