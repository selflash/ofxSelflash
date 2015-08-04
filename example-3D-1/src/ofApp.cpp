#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(200, 200, 200);
    ofSetWindowTitle("example-Primitive3D");
    
    //Flashフレームワークの準備
    ofxSelflash::setup(true);
    Stage* stage = ofxSelflash::stage();
    
    _world = new World3D();
    _world->name("World");
    stage->addChild(_world);
    _world->setup();
    
//    ofEnableAlphaBlending();
    
    _controller01 = new Camera3DController();
    _controller01->setup();
    _controller01->x();
    _controller01->y();
    ((Camera3DController*) _controller01)->camera(_world->camera());
    stage->addChild(_controller01);
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == OF_KEY_UP) {
        cameraZ -= 100;
    }
    if(key == OF_KEY_DOWN) {
        cameraZ += 100;
    }
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
