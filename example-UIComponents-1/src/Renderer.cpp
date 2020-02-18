#include "Renderer.h"

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
void Renderer::_setup() {
    camWidth = 320 * 2;
    camHeight = 240 * 2;

    camera.setAutoDistance(false);
    camera.disableMouseInput();
    camera.setPosition(ofVec3f(0, 0, 100));

    viewPort.set(0, 0, camWidth, camHeight);

    _count = 0;
    speed = 0.5;
    
    objPos.set(0, 0, -100);

//    _vidGrabber.setDeviceID(0);
//    _vidGrabber.setDesiredFrameRate(60);
//    _vidGrabber.initGrabber(camWidth, camHeight);
//    _videoTexture.allocate(camWidth, camHeight, GL_RGBA);
//
    
    //Frame line.
    flGraphics* g;
    g = graphics();
    g->clear();
//    g->beginFill(0xffffff, 1);
//    g->drawRect(-1, -1, camWidth + 2, camHeight + 2);
    g->lineStyle(1, 0xffffff);
    g->moveTo(-1, -1);
    g->lineTo(camWidth + 2, -1);
    g->lineTo(camWidth + 2, camHeight + 2);
    g->lineTo(-1, camHeight + 2);
    g->lineTo(-1, -1);
    g->endFill();

//    flBitmap* bitmap = new flBitmap(_videoTexture);
//    //    bitmap->alpha(0.5);
//    addChild(bitmap);
    
    bgColor = ofColor(0, 0, 0, 255);
    lineWidth = 1;
}

//--------------------------------------------------------------
void Renderer::_update() {
//    _vidGrabber.update();
//    if(_vidGrabber.isFrameNew()){
//        ofPixels& pixels = _vidGrabber.getPixels();
//        _videoTexture.loadData(pixels);
//    }
    
    viewPort.x = x();
    viewPort.y = y();
}

//--------------------------------------------------------------
void Renderer::_draw() {
    //--------------------------------------
    ofPushStyle();
    ofSetColor(bgColor);
    
    ofDrawRectangle(0, 0, camWidth, camHeight);
    
    ofPopStyle();
    //--------------------------------------

    
    camera.begin(viewPort);
    
    //--------------------------------------
    _count += speed;
    
    ofPushMatrix();
//    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    
    ofPushMatrix();
    ofTranslate(objPos);
    
    ofRotateX(_count);
    ofRotateY(_count * 0.75);
    
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(lineWidth);
    ofDrawBox(0, 0, 0, 100, 100, 100);
    ofPopStyle();
    
    ofPopMatrix();
    
    ofPopMatrix();
    
    camera.end();
    //--------------------------------------
    
    //--------------------------------------
    string text = "";
    text += name() + "\n";
    text += "X = " + ofToString(x()) + "\n";
    text += "Y = " + ofToString(y()) + "\n";
//    text += "width = " + ofToString(width()) + "\n";
//    text += "height = " + ofToString(height()) + "\n";
//    text += "scaleX = " + ofToString(scaleX()) + "\n";
//    text += "scaleY = " + ofToString(scaleY()) + "\n";
    
    ofPushStyle();
    ofSetColor(255, 255, 255);
    flFont::drawString(text, 9, 10, 20);
    ofPopStyle();
    //--------------------------------------
}
