#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofSetWindowTitle("example-EventdispatcherA-2");
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //---------------------------------------
    dispatcherA = new flEventDispatcher();
    dispatcherA->debug(true);
    dispatcherA->addEventListener(flEvent::INIT, this, &ofApp::eventHandler);
    dispatcherA->addEventListener(CustomEvent::TEST1, this, &ofApp::eventHandler);
    
    dispatcherB = new CustomDispatcher();
    dispatcherB->debug(true);
    dispatcherB->addListeners();
    
    //アドレスを表示
    ofLog(OF_LOG_VERBOSE) << "----------------------------";
    ofLog(OF_LOG_VERBOSE) << "[dispathcerA] = " << dispatcherA;
    ofLog(OF_LOG_VERBOSE) << "[dispathcerB] = " << dispatcherB;
    ofLog(OF_LOG_VERBOSE) << "----------------------------";
    //---------------------------------------
}

void ofApp::test1() {
    
    //---------------------------------------
    //removeEventListenerテスト
    cout << "TEST 5 ---------------------" << endl;
    cout << &ofApp::eventHandler << endl;
    cout << dispatcherA->hasEventListener(flEvent::INIT) << endl;
    dispatcherA->removeEventListener(flEvent::INIT);
    cout << dispatcherA->hasEventListener(flEvent::INIT) << endl;
    cout << "----------------------------" << endl;
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
    text += "1 : A.dispatchEvent(Event::INIT)\n";
    text += "2 : A.dispatchEvent(CustomEvent::TEST1)\n";
    text += "3 : B.dispatchTest1()\n";
    text += "4 : B.dispatchTest2()\n";
    ofDrawBitmapString(text, 10, 15);
    
    ofPopStyle();
    //---------------------------------------
}

//--------------------------------------------------------------
void ofApp::eventHandler(flEvent& event) {
    cout << "[testApp]eventHandler()" << endl;
    
    //---------------------------------------
    cout << "[event.type] = " << event.type() << endl;
    cout << "[event.target] = " << event.target() << endl;
    cout << "[event.currentTarget] = " << event.currentTarget() << endl;
    //---------------------------------------
    flEventDispatcher* target = (flEventDispatcher*) event.target();
    flEventDispatcher* tarcurrentTargetget = (flEventDispatcher*) event.currentTarget();
    
//    CustomEvent& customEvent = *(CustomEvent*) &event;

    if(event.target() == dispatcherA) {
        if(event.type() == flEvent::INIT) cout << "A -> INIT" << endl;
        if(event.type() == CustomEvent::TEST1) cout << "A -> TEST1" << endl;
        
        //removeEventListenerテスト
        target->removeEventListener(flEvent::INIT, this);
        target->removeEventListener(CustomEvent::TEST1, this);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == '1') {
        dispatcherA->dispatchEvent(new CustomEvent(CustomEvent::TEST1));
    }
    
    if(key == '2') {
        dispatcherA->dispatchEvent(new flEvent(flEvent::INIT));
    }
    
    if(key == '3') {
        dispatcherB->dispatchTest1();
    }
    
    if(key == '4') {
        dispatcherB->dispatchTest2();
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
