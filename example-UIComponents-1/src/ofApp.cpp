#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    ofSetWindowTitle("example-UIComponents-1");
    //ofDisableAntiAliasing();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    //--------------------------------------
    ofxSelflash::setup();
    //--------------------------------------
    
    //--------------------------------------
    uiComponents = new UIComponents();
    uiComponents->setup();
    ofxSelflash::stage()->addChild(uiComponents);
    //--------------------------------------
    
    //--------------------------------------
    renderer = new Renderer();
    renderer->setup();
    renderer->x(550);
    renderer->y(300);
    ofxSelflash::stage()->addChild(renderer);
    //--------------------------------------
    
    //--------------------------------------
    //Bind
    renderer->lineWidth = appModel.lineWidth;
    uiComponents->slider001->bind(appModel.lineWidth);
    listeners.push(appModel.lineWidth.newListener([&](int& value) {
        renderer->lineWidth = value;
    }));

    renderer->speed = appModel.speed;
    uiComponents->slider002->bind(appModel.speed);
    listeners.push(appModel.speed.newListener([&](float& value) {
        renderer->speed = value;
    }));
    
    renderer->bgColor = appModel.bgColor;
    uiComponents->colorSlider001->bind(appModel.bgColor);
    listeners.push(appModel.bgColor.newListener([&](ofColor& value) {
        renderer->bgColor = value;
    }));
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    //----------------------------------
    ofxSelflash::draw();
    //----------------------------------
    
    //--------------------------------------
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 255, 255, 200);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 5);
    ofPopStyle();
    //--------------------------------------
}

//==============================================================
// Private Event Handler
//==============================================================

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == 'c') {
        appModel.lineWidth = 15;
        appModel.speed = 0.5;
        appModel.bgColor = ofColor(255, 124, 30, 200);
    }
    
    if(key == ('l')) {
        enabled = !enabled;
        int numChildren = uiComponents->numChildren();
        for(int i = 0; i < numChildren; i++) {
            flDisplayObject* displayObject = (flDisplayObject*)uiComponents->getChildAt(i);
//            ofLog() << "displayObject->name() = " << displayObject->name();

            if(displayObject->typeID() == FL_TYPE_UIBASE) {
                ofLog() << "displayObject.name = " << displayObject->name();
                ((flUIBase*)displayObject)->enabled(enabled);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    
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
