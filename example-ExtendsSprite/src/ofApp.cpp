#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-ExtendsSprite");
    ofDisableAntiAliasing();
    
    //--------------------------------------
    //Ready ofxSelflash
    ofxSelflash::autoUpdate(false);
    ofxSelflash::autoDraw(false);
    ofxSelflash::setup(false);
    //--------------------------------------
    
    flStage* stage = ofxSelflash::stage();
    
    documentRoot = new DocumentRoot();
    documentRoot->setup();
    //    documentRoot->alpha(0.5);
    stage->addChild(documentRoot);
}

//--------------------------------------------------------------
void ofApp::update() {
    ofxSelflash::update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofxSelflash::draw();
    
    ofPushStyle();
    ofSetColor(0, 0, 0, 255);
    flFont::drawString("Drag to move sprite.", 5, 20);
    ofPopStyle();
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
