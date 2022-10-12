#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofLogToConsole();

    flObject* object = new flObject();
    float x = 100.5;

    object->setProperty<float>("x", &x);
    ofLog() << object->getProperty<float>("x");

    object->setProperty<int>("y", 150);
    ofLog() << object->getProperty<int>("y");

    ofFloatColor* color1 = new ofFloatColor();
    color1->r = 255;
    color1->g = 100;

    object->setProperty<ofFloatColor>("color", color1);
    ofFloatColor* color2 = &object->getProperty<ofFloatColor>("color");
    ofLog() << "R : " << color2->r;
    ofLog() << "G : " << color2->g;
    ofLog() << "B : " << color2->b;
    ofLog() << "A : " << color2->a;

    ofFloatColor* color3 = new ofFloatColor();
    color3->r = 155;
    color3->g = 130;
    object->setProperty<ofFloatColor>("color1", color3);
    ofFloatColor* color4 = &object->getProperty<ofFloatColor>("color1");
    ofLog() << "R : " << color4->r;
    ofLog() << "G : " << color4->g;
    ofLog() << "B : " << color4->b;
    ofLog() << "A : " << color4->a;

    object->setProperty<string>("label", "hoge");
    ofLog() << object->getProperty<string>("label");

//    object->setProperty<float>("x", &x);
//    object->setProperty<float>("x", x);
    object->setProperty<float>("x", 100);
    ofLog() << object->getProperty<float>("x");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
