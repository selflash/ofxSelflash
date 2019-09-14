#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-BasicDraggableObject");
    ofDisableAntiAliasing();
    
    //--------------------------------------
    //Ready ofxSelflash
    ofxSelflash::drawPriority(OF_EVENT_ORDER_BEFORE_APP);
    //    ofxSelflash::drawPriority(OF_EVENT_ORDER_AFTER_APP);
    ofxSelflash::setup();
    //--------------------------------------
    
    flStage* stage = ofxSelflash::stage();
    
    //load image
    ofImage image;
    image.load("selflash.jpeg");
    
    //--------------------------------------
    //make a simple draggable object.
    noFrameBorder = new BasicDraggableObject();
    noFrameBorder->x(10);
    noFrameBorder->y(10);
    //    noFrameBorder->alpha(0.5);
    stage->addChild(noFrameBorder);
    
    flBitmap* bitmap1 = new flBitmap(image);
    noFrameBorder->addChild(bitmap1);
    cout << "noFrameBorder = " << noFrameBorder->width() << " " << noFrameBorder->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //Frame Border1
    frameBorder1 = new FrameBorder1();
    frameBorder1->x(noFrameBorder->x() + noFrameBorder->width() + 20 + 10);
    frameBorder1->y(10);
    //    frameBorder1->alpha(0.5);
    stage->addChild(frameBorder1);
    
    flBitmap* bitmap2 = new flBitmap(image);
    //    bitmap2->alpha(0.5);
    frameBorder1->addChild(bitmap2);
    cout << "frameBorder1 = " << frameBorder1->width() << " " << frameBorder1->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //Frame Border2
    frameBorder2 = new FrameBorder2();
    frameBorder2->setup();
    frameBorder2->x(10);
    
    frameBorder1->update(); //must update for property fo width/height
    
    frameBorder2->y(noFrameBorder->y() + noFrameBorder->height() + 20 + 10);
    stage->addChild(frameBorder2);
    cout << "frameBorder2 = " << frameBorder2->width() << " " << frameBorder2->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //Frame Border3
    frameBorder3 = new FrameBorder3();
    frameBorder3->setup();
    frameBorder3->x(frameBorder2->x() + frameBorder2->width() + 10);
    frameBorder3->y(frameBorder1->y() + frameBorder1->height() + 10);
    stage->addChild(frameBorder3);
    cout << "frameBorder3 = " << frameBorder3->width() << " " << frameBorder3->height() << endl;
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
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
