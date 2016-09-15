#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-Sprite");
    
    ofxSelflash::setup();
    ofxSelflash::autoUpdate(false);
    ofxSelflash::autoDraw(false);
    flStage* stage = ofxSelflash::stage();
    
    container = new Container();
    container->setup();
    stage->addChild(container);
}

//--------------------------------------------------------------
void ofApp::update() {
    ofxSelflash::update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofxSelflash::draw();
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
