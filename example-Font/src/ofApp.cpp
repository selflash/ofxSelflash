#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("example-Font");
    
    ofxSelflash::setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    auto drawText = [](string text, int fontSize, float ix, float iy, bool centering = false)->void {
        ofPushMatrix();
        ofTranslate(ix, iy);
        
        float x = 0;
        float y = 0;
        if(centering) {
            x = -flFont::getStringWidth(text, fontSize) * 0.5;
            y = -flFont::getStringHeight(text, fontSize) * 0.5;
        }
        
        ofPushStyle();
        ofSetColor(0, 0, 0, 255);
        flFont::drawString(text, fontSize, x, y);
        ofPopStyle();
        
        ofPopMatrix();
    };
    
    float w = ofGetWidth();
    float h = ofGetHeight();
    drawText("ようこそ世界。\r\nHello World.", 60, w * 0.5, h * 0.5, true);
    drawText("僕の名前はSelflash。\r\nI'm Selflash.", 15, 100, 50);
    drawText("沖縄生まれ沖縄育ち。\r\nBorn Okinawa and grew up there.", 18, 10, 600);
    drawText("僕の名前はSelflash。\r\nI'm Selflash.", 23, 600, 700);
    drawText("沖縄生まれ沖縄育ち。\r\nBorn Okinawa and grew up there.", 30, 200, 150);
    
//    ofPushStyle();
//    ofSetColor(0, 0, 0, 255);
//    ofDrawBitmapString("FPS : " + ofToString(ofGetFrameRate(), 1), 10, 20);
//    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
