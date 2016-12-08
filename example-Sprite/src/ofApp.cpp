#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-Sprite");
    ofDisableAntiAliasing();
    
    //--------------------------------------
    //Ready ofxSelflash
    ofxSelflash::setup();
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
    
}

//--------------------------------------------------------------
void ofApp::_enterFrameEventHandler(flEvent& event) {
    cout << "[ofApp]_enterFrameEventHandler("<< event.type() << ")" << endl;
    
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
