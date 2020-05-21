#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-BasicDraggableObject");
    ofSetVerticalSync(true);
    //ofDisableAntiAliasing();
//    ofSetFrameRate(60);
    
    //--------------------------------------
    ofxSelflash::setup();
    //--------------------------------------
    
    flStage* stage = ofxSelflash::stage();
    
    //load image
    ofImage image;
    image.load("selflash.jpeg");
    
    //--------------------------------------
    //make a simple draggable object.
    noFrameBorder = new flBasicDraggableObject();
    noFrameBorder->x(20);
    noFrameBorder->y(30);
    //    noFrameBorder->alpha(0.5);
    noFrameBorder->toolTipEnabled(true);
    noFrameBorder->toolTipText("No Frame Border");
    stage->addChild(noFrameBorder);
    
    flBitmap* bitmap1 = new flBitmap(image);
    noFrameBorder->addChild(bitmap1);
    ofLog() << "noFrameBorder = " << noFrameBorder->width() << " " << noFrameBorder->height();
    //--------------------------------------
    
    //--------------------------------------
    //Frame Border1
    frameBorder1 = new FrameBorder1();
    frameBorder1->x(20 + 276 + 20);
    frameBorder1->y(30);
    //    frameBorder1->alpha(0.5);
    frameBorder1->toolTipEnabled(true);
    frameBorder1->toolTipText("Frame Border 1");
    stage->addChild(frameBorder1);
    
    flBitmap* bitmap2 = new flBitmap(image);
//    bitmap2->alpha(0.5);
    frameBorder1->addChild(bitmap2);
    ofLog() << "frameBorder1 = " << frameBorder1->width() << " " << frameBorder1->height();
    //--------------------------------------
    
    //--------------------------------------
    //Frame Border2
    frameBorder2 = new FrameBorder2();
    frameBorder2->setup();
    frameBorder2->x(20);
    frameBorder2->y(30 + 276);
    frameBorder2->toolTipEnabled(true);
    frameBorder2->toolTipText("Frame Border 2");

    frameBorder1->update(); //must update for property fo width/height
    
    frameBorder2->y(noFrameBorder->y() + noFrameBorder->height() + 20 + 10);
    stage->addChild(frameBorder2);
    ofLog() << "frameBorder2 = " << frameBorder2->width() << " " << frameBorder2->height();
    //--------------------------------------
    
    //--------------------------------------
    //Frame Border3
    frameBorder3 = new FrameBorder3();
    frameBorder3->setup();
    frameBorder3->x(20 + 276 + 20);
    frameBorder3->y(30 + 276 + 10);
    frameBorder3->toolTipEnabled(true);
    frameBorder3->toolTipText("Frame Border 3");
    stage->addChild(frameBorder3);
    ofLog() << "frameBorder3 = " << frameBorder3->width() << " " << frameBorder3->height();
    //--------------------------------------
    
    //--------------------------------------
    //Frame Border4
    frameBorder4 = new FrameBorder4();
    frameBorder4->setup();
    frameBorder4->x(20 + 276 + 20 + 276 + 20);
    frameBorder4->y(40);
//    frameBorder1->alpha(0.5);
    frameBorder4->toolTipEnabled(true);
    frameBorder4->toolTipText("Frame Border 4");
    stage->addChild(frameBorder4);
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
//    ofBackground(100, 100, 100);
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofxSelflash::draw();
    
    ofPushStyle();
    ofSetColor(0, 0, 0, 255);
    flFont::drawString("Drag to move any object.\nPress [ 1 ]  to change dragEnabled.", 5, 20);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == 'f') ofToggleFullscreen();
    if(key == '1') {
        noFrameBorder->dragEnabled(!noFrameBorder->dragEnabled());
        frameBorder1->dragEnabled(!frameBorder1->dragEnabled());
        frameBorder2->dragEnabled(!frameBorder2->dragEnabled());
        frameBorder3->dragEnabled(!frameBorder3->dragEnabled());
        frameBorder4->dragEnabled(!frameBorder4->dragEnabled());
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
