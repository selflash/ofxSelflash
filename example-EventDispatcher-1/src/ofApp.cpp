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
    cout << "----------------------------" << endl;
    cout << "[dispathcerA] = " << dispatcherA << endl;
    cout << "[dispathcerB] = " << dispatcherB << endl;
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
    cout << "[ofApp]eventHandler(" << event.type() << ")" << endl;
    
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
    }
    
    if(event.target() == dispatcherB) {
        if(event.type() == flEvent::INIT) cout << "B -> INIT" << endl;
        if(event.type() == CustomEvent::TEST1) cout << "B -> TEST1" << endl;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == '1') {
        cout << "TEST 1 ---------------------" << endl;
        dispatcherA->dispatchEvent(new flEvent(flEvent::INIT));
        cout << "----------------------------" << endl;
    }
    
    if(key == '2') {
        cout << "TEST 2 ---------------------" << endl;
        dispatcherA->dispatchEvent(new CustomEvent(CustomEvent::TEST1));
        cout << "----------------------------" << endl;
    }
    
    if(key == '3') {
        cout << "TEST 3 ---------------------" << endl;
        dispatcherB->dispatchEvent(new flEvent(flEvent::INIT));
        cout << "----------------------------" << endl;
    }
    
    if(key == '4') {
        cout << "TEST 4 ---------------------" << endl;
        dispatcherB->dispatchEvent(new CustomEvent(CustomEvent::TEST1));
        cout << "----------------------------" << endl;
    }
    
    if(key == '5') {
        cout << "TEST 5 ---------------------" << endl;
        dispatcherB->dispatchTest1();
        cout << "----------------------------" << endl;
    }
    
    if(key == '6') {
        cout << "TEST 6 ---------------------" << endl;
        dispatcherB->dispatchTest2();
        cout << "----------------------------" << endl;
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
