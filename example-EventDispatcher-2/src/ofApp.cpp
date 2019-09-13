#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetWindowTitle("example-Eventdispatcher-2");
    
    //---------------------------------------
    dispatcherA = new flEventDispatcher();
    dispatcherA->debug(true);
    dispatcherA->addEventListener(flEvent::INIT, this, &ofApp::eventHandler);
    dispatcherA->addEventListener(CustomEvent::TEST1, this, &ofApp::eventHandler);
    
    dispatcherB = new CustomDispatcher();
    dispatcherB->debug(true);
    dispatcherB->addListeners();
    
    //アドレスを表示
    cout << "----------------------------" << endl;
    cout << "[dispathcerA] = " << dispatcherA << endl;
    cout << "[dispathcerB] = " << dispatcherB << endl;
    cout << "----------------------------";
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
    text += "Press [ 1 ] : A.dispatchEvent(Event::INIT)\n";
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
    cout << "TEST 5 ---------------------" << endl;
    cout << &ofApp::eventHandler << endl;
    cout << (dispatcherA->hasEventListener(flEvent::INIT) ? "true" : "false") << endl;
    
    dispatcherA->removeEventListeners(flEvent::INIT);
    
    cout << dispatcherA->hasEventListener(flEvent::INIT) << endl;
    cout << "----------------------------" << endl;
    //---------------------------------------
}

//--------------------------------------------------------------
// EVENT HANDLER
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::eventHandler(flEvent& event) {
    cout << "[ofApp]eventHandler()" << endl;
    
    //---------------------------------------
    cout << "[event.type] = " << event.type() << endl;
    cout << "[event.target] = " << event.target() << endl;
    cout << "[event.currentTarget] = " << event.currentTarget() << endl;
    //---------------------------------------
    
    flEventDispatcher* target = (flEventDispatcher*) event.target();
    flEventDispatcher* tarcurrentTargetget = (flEventDispatcher*) event.currentTarget();
    
    //Cast
//    CustomEvent& customEvent = *(CustomEvent*)& event;

    if(event.target() == dispatcherA) {
        if(event.type() == flEvent::INIT) cout << "A -> INIT" << endl;
        if(event.type() == CustomEvent::TEST1) cout << "A -> TEST1" << endl;
        
        //removeEventListenerテスト
//        target->removeEventListeners(flEvent::INIT);
//        target->removeEventListeners(CustomEvent::TEST1);
        
//        target->removeEventListener(flEvent::INIT, this, &ofApp::eventHandler);
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
        dispatcherA->dispatchEvent(new flEvent(flEvent::INIT));
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
