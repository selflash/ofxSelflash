#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-Eventdispatcher-1");
    
    //---------------------------------------
    dispatcherA = new flEventDispatcher();
    dispatcherA->debug(true);
    
    dispatcherA->addEventListener(flEvent::INIT, this, &ofApp::eventHandler);
    dispatcherA->addEventListener(CustomEvent::TEST1, this, &ofApp::eventHandler);
    
//    dispatcherA->removeEventListener(flEvent::INIT, this, &ofApp::eventHandler);
//    dispatcherA->removeEventListener(CustomEvent::TEST1, this, &ofApp::eventHandler);
    
    dispatcherB = new CustomDispatcher();
    dispatcherB->debug(true);
    dispatcherB->addEventListener(flEvent::INIT, this, &ofApp::eventHandler);
    dispatcherB->addEventListener(CustomEvent::TEST1, this, &ofApp::eventHandler);
    
//    dispatcherB->removeEventListener(CustomEvent::TEST1, this, &ofApp::eventHandler);
    
    //アドレスを表示
    ofLog() << "----------------------------";
    ofLog() << "[dispathcerA] = " << dispatcherA;
    ofLog() << "[dispathcerB] = " << dispatcherB;
    ofLog() << "----------------------------";
    //---------------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    //---------------------------------------
    ofPushStyle();
    
    ofSetColor(255, 255, 255);
    string text = "";
    text += "Press [ 1 ] : A.dispatchEvent(Event::INIT)\n";
    text += "Press [ 2 ] : A.dispatchEvent(CustomEvent::TEST1)\n";
    text += "Press [ 3 ] : B.dispatchEvent(Event::INIT)\n";
    text += "Press [ 4 ] : B.dispatchEvent(CustomEvent::TEST1)\n";
    text += "Press [ 5 ] : B.dispatchTest1()\n";
    text += "Press [ 6 ] : B.dispatchTest2()\n";
    ofDrawBitmapString(text, 10, 15);
    
    ofPopStyle();
    //---------------------------------------
}

//--------------------------------------------------------------
void ofApp::eventHandler(flEvent& event) {
    ofLog() << "[ofApp]eventHandler(" << event.type() << ")";
    
    //---------------------------------------
    ofLog() << "[event.type] = " << event.type();
    ofLog() << "[event.target] = " << event.target();
    ofLog() << "[event.currentTarget] = " << event.currentTarget();
    //---------------------------------------
    flEventDispatcher* target = (flEventDispatcher*) event.target();
    flEventDispatcher* tarcurrentTargetget = (flEventDispatcher*) event.currentTarget();
    
    //    CustomEvent& customEvent = *(CustomEvent*) &event;
    
    if(event.target() == dispatcherA) {
        if(event.type() == flEvent::INIT) ofLog() << "A -> INIT";
        if(event.type() == CustomEvent::TEST1) ofLog() << "A -> TEST1";
    }
    
    if(event.target() == dispatcherB) {
        if(event.type() == flEvent::INIT) ofLog() << "B -> INIT";
        if(event.type() == CustomEvent::TEST1) ofLog() << "B -> TEST1";
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == '1') {
        ofLog() << "TEST 1 ---------------------";
        dispatcherA->dispatchEvent(new flEvent(flEvent::INIT));
        ofLog() << "----------------------------";
    }
    
    if(key == '2') {
        ofLog() << "TEST 2 ---------------------";
        dispatcherA->dispatchEvent(new CustomEvent(CustomEvent::TEST1));
        ofLog() << "----------------------------";
    }
    
    if(key == '3') {
        ofLog() << "TEST 3 ---------------------";
        dispatcherB->dispatchEvent(new flEvent(flEvent::INIT));
        ofLog() << "----------------------------";
    }
    
    if(key == '4') {
        ofLog() << "TEST 4 ---------------------";
        dispatcherB->dispatchEvent(new CustomEvent(CustomEvent::TEST1));
        ofLog() << "----------------------------";
    }
    
    if(key == '5') {
        ofLog() << "TEST 5 ---------------------";
        dispatcherB->dispatchTest1();
        ofLog() << "----------------------------";
    }
    
    if(key == '6') {
        ofLog() << "TEST 6 ---------------------";
        dispatcherB->dispatchTest2();
        ofLog() << "----------------------------";
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
