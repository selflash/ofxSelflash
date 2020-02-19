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
    renderer->bgColor = appModel.bgColor;
    listeners.push(appModel.bgColor.newListener([&](ofColor& value) {
        renderer->bgColor = value;
    }));
    uiComponents->colorSlider001->bind(appModel.bgColor);

    renderer->lineColor = appModel.lineColor;
    listeners.push(appModel.lineColor.newListener([&](ofColor& value) {
        renderer->lineColor = value;
    }));
    uiComponents->colorSlider002->bind(appModel.lineColor);

    renderer->lineWidth = appModel.lineWidth;
    listeners.push(appModel.lineWidth.newListener([&](int& value) {
        renderer->lineWidth = value;
    }));
    uiComponents->slider001->bind(appModel.lineWidth);

    renderer->speed = appModel.speed;
    listeners.push(appModel.speed.newListener([&](float& value) {
        renderer->speed = value;
    }));
    uiComponents->slider002->bind(appModel.speed);
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
    if(animationEnabled) {
        float elapsedTime = ofGetElapsedTimef();
        float n = ((sin(elapsedTime) + 1.0) / 2.0);
//        ofLog() << "n = " << n;
        appModel.lineWidth = ((sin(elapsedTime) + 1.0) / 2.0) * 20;
        appModel.speed = ((sin(elapsedTime * 1.7) + 1.0) / 2.0) * 10.0;
        appModel.lineColor = ofColor(
            ((sin(elapsedTime * 0.58) + 1.0) / 2.0) * 255,
            ((sin(elapsedTime * 0.75) + 1.0) / 2.0) * 255,
            ((sin(elapsedTime * 0.45) + 1.0) / 2.0) * 255,
            255
        );
//        appModel.bgColor.g = ((sin(elapsedTime * 0.75) + 1.0) / 2.0) * 255.0;
//        appModel.bgColor.b = ((sin(elapsedTime * 0.45) + 1.0) / 2.0) * 255.0;
//        appModel.lineColor = ofColor(124, 30, 124, 200);

    }
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
    if(key == 'a') {
        animationEnabled = !animationEnabled;
//        appModel.lineWidth = 15;
//        appModel.speed = 0.5;
//        appModel.bgColor = ofColor(255, 124, 30, 200);
//        appModel.lineColor = ofColor(124, 30, 124, 200);
    }
    
    if(key == 's') {
        uiComponents->button003->press();
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
