#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-Sprite");
    ofDisableAntiAliasing();
    
    //--------------------------------------
    flSettings settings;
//    settings.manualDraw = false;
    ofxSelflash::setup(settings);
    //--------------------------------------
    
    flStage* stage = ofxSelflash::stage();
    
    container = new Container();
    container->setup();
    container->addEventListener(flEvent::ENTER_FRAME, this, &ofApp::_enterFrameEventHandler);
    stage->addChild(container);
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofxSelflash::draw();
}

//--------------------------------------------------------------
void ofApp::_enterFrameEventHandler(flEvent& event) {
    ofLog() << "[ofApp]_enterFrameEventHandler("<< event.type() << ")";
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
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
