#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-HitArea");
    
    ofxSelflash::setup();
    flStage* stage = ofxSelflash::stage();
    
    container = new Container();
    container->setup();
    stage->addChild(container);
    
    //--------------------------------------
    //タイトル
    textField000 = new flTextField();
    textField000->textColor(0x000000);
    textField000->text("Stage info");
    textField000->x(10);
    textField000->y(20);
//    textField000->width(100);
//    textField000->autoSize = TEXT_FIELD_AUTOSIZE_LEFT;
    textField000->mouseEnabled(false);
    stage->addChild(textField000);
    
    //
    textField001 = new flTextField();
    textField001->textColor(0x000000);
    textField001->text("");
    textField001->x(10);
    textField001->y(40);
    textField001->mouseEnabled(false);
    stage->addChild(textField001);
    
    //
    textField002 = new flTextField();
    textField002->textColor(0x000000);
    textField002->text("");
    textField002->x(10);
    textField002->y(60);
    textField002->mouseEnabled(false);
    stage->addChild(textField002);
    
    //
    textField003 = new flTextField();
    textField003->textColor(0x000000);
    textField003->text("");
    textField003->x(10);
    textField003->y(80);
    textField003->mouseEnabled(false);
    stage->addChild(textField003);
    
    //
    textField004 = new flTextField();
    textField004->textColor(0x000000);
    textField004->text("");
    textField004->x(10);
    textField004->y(100);
    textField004->mouseEnabled(false);
    stage->addChild(textField004);
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    flStage* stage = ofxSelflash::stage();
    flDisplayObject* disp = stage->topMostHitDisplayObject();
    
    if(disp) {
        textField001->text("topMostHitDisplayObject = " + disp->name());
    } else {
        textField001->text("topMostHitDisplayObject = NONE");
    }
    
    flDisplayObject* dispPrev = stage->topMostHitDisplayObjectPrev();
    if(dispPrev != disp) {
        if(dispPrev) {
            textField002->text("topMostHitDisplayObjectPrev = " + dispPrev->name());
        } else {
            textField002->text("topMostHitDisplayObjectPrev = NONE");
        }
    }
    
    flInteractiveObject* intDisp = stage->topMostHitInteractiveObject();
    if(intDisp) {
        textField003->text("topMostHitInteractiveObject = " + intDisp->name());
    } else {
        textField003->text("topMostHitInteractiveObject = NONE");
    }
    
    flInteractiveObject* intDispPrev = stage->topMostHitInteractiveObjectPrev();
    if(intDispPrev != intDisp) {
        if(intDispPrev) {
            textField004->text("topMostHitInteractiveObjectPrev = " + intDispPrev->name());
        } else {
            textField004->text("topMostHitInteractiveObjectPrev = NONE");
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == 'f') ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
