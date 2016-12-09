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
    flStage* stage = ofxSelflash::stage();
    
    //load image
    ofImage image;
    image.load("selflash.jpeg");
    
    //--------------------------------------
    //make simple draggable object.
    draggableObject = new BasicDraggableObject();
    draggableObject->x(10);
    draggableObject->y(10);
    stage->addChild(draggableObject);
    
    flBitmap* bitmap1 = new flBitmap(image);
    draggableObject->addChild(bitmap1);
    cout << "draggableObject = " << draggableObject->width() << " " << draggableObject->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //Image Frame1
    imageFrame1 = new ImageFrame1();
    imageFrame1->x(draggableObject->x() + draggableObject->width() + 20 + 10);
    imageFrame1->y(10);
    stage->addChild(imageFrame1);
    
    flBitmap* bitmap2 = new flBitmap(image);
    imageFrame1->addChild(bitmap2);
    cout << "imageFrame1 = " << imageFrame1->width() << " " << imageFrame1->height() << endl;
    //--------------------------------------

    //--------------------------------------
    //Image Frame2
    imageFrame2 = new ImageFrame2();
    imageFrame2->setup();
    imageFrame2->x(10);
    
    imageFrame1->update(); //must update for property fo width/height

    imageFrame2->y(draggableObject->y() + draggableObject->height() + 20 + 10);
    stage->addChild(imageFrame2);
    cout << "imageFrame2 = " << imageFrame2->width() << " " << imageFrame2->height() << endl;
    //--------------------------------------
    
    //--------------------------------------
    //Image Frame3
    imageFrame3 = new ImageFrame3();
    imageFrame3->setup();
    imageFrame3->x(imageFrame2->x() + imageFrame2->width() + 10);
    imageFrame3->y(imageFrame1->y() + imageFrame1->height() + 10);
    stage->addChild(imageFrame3);
    cout << "imageFrame3 = " << imageFrame3->width() << " " << imageFrame3->height() << endl;
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
        draggableObject->dragEnabled(!draggableObject->dragEnabled());
        imageFrame1->dragEnabled(!imageFrame1->dragEnabled());
        imageFrame2->dragEnabled(!imageFrame2->dragEnabled());
        imageFrame3->dragEnabled(!imageFrame3->dragEnabled());
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
