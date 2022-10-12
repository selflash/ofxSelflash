#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofLogToConsole();
    ofSetWindowTitle("example-Eventdispatcher-2");
    
    //---------------------------------------
    dispatcherA = new flEventDispatcher();
    dispatcherA->debug(true);
    dispatcherA->addEventListener(flEvent::CHANGE, this, &ofApp::eventHandler);
    dispatcherA->addEventListener(CustomEvent::TEST1, this, &ofApp::eventHandler);
    
    dispatcherB = new CustomDispatcher();
    dispatcherB->debug(true);
    dispatcherB->addListeners();
    
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
    std::string text = "";
    text += "Press [ 1 ] : A.dispatchEvent(Event::CHANGE)\n";
    text += "Press [ 2 ] : A.dispatchEvent(CustomEvent::TEST1)\n";
    text += "Press [ 3 ] : B.dispatchTest1()\n";
    text += "Press [ 4 ] : B.dispatchTest2()\n";
    text += "Press [ 5 ] : removeEventListeners()\n";
    ofDrawBitmapString(text, 10, 15);
    
    ofPopStyle();
    //---------------------------------------
}

//--------------------------------------------------------------
void ofApp::test1() {
    //---------------------------------------
    //removeEventListenerテスト
    ofLog() << "TEST 5 ---------------------";
    ofLog() << &ofApp::eventHandler;
    ofLog() << (dispatcherA->hasEventListener(flEvent::CHANGE) ? "true" : "false");
    
    dispatcherA->removeEventListeners(flEvent::CHANGE);
    
    ofLog() << dispatcherA->hasEventListener(flEvent::CHANGE);
    ofLog() << "----------------------------";
    //---------------------------------------
}

//--------------------------------------------------------------
// Private Event Handler
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::eventHandler(flEvent& event) {
    ofLog() << "[ofApp]eventHandler()";
    
    //---------------------------------------
    ofLog() << "[event.type] = " << event.type();
    ofLog() << "[event.target] = " << event.target();
    ofLog() << "[event.currentTarget] = " << event.currentTarget();
    //---------------------------------------
    
    flEventDispatcher* target = (flEventDispatcher*) event.target();
    flEventDispatcher* tarcurrentTargetget = (flEventDispatcher*) event.currentTarget();
    
    //Cast
    //    CustomEvent& customEvent = *(CustomEvent*)& event;
    
    if(event.target() == dispatcherA) {
        if(event.type() == flEvent::CHANGE) ofLog() << "A -> CHANGE";
        if(event.type() == CustomEvent::TEST1) ofLog() << "A -> TEST1";
        
        //removeEventListenerテスト
        //        target->removeEventListeners(flEvent::CHANGE);
        //        target->removeEventListeners(CustomEvent::TEST1);
        
        //        target->removeEventListener(flEvent::CHANGE, this, &ofApp::eventHandler);
        //        target->removeEventListener(CustomEvent::TEST1, this, &ofApp::eventHandler);
        
        target->removeAllEventListeners();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == '1') {
        dispatcherA->dispatchEvent(new CustomEvent(CustomEvent::TEST1));
    }
    
    if(key == '2') {
        dispatcherA->dispatchEvent(new flEvent(flEvent::CHANGE));
    }
    
    if(key == '3') {
        dispatcherB->dispatchTest1();
    }
    
    if(key == '4') {
        dispatcherB->dispatchTest2();
    }
    
    if(key == '5') {
        test1();
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
