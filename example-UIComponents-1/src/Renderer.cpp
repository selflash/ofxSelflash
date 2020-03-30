#include "Renderer.h"

//--------------------------------------------------------------
Renderer::Renderer() {
    _target = this;
    name("Renderer");

}

//--------------------------------------------------------------
Renderer::~Renderer() {
    
}

//==============================================================
// Setup / Update / Draw
//==============================================================

//--------------------------------------------------------------
void Renderer::_setup() {
    camera.setAutoDistance(false);
    camera.disableMouseInput();
    camera.setPosition(cameraPos);

    viewPort.set(0, 0, camWidth, camHeight);

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
    g->moveTo(-1, 0);
    g->lineTo(camWidth + 1, 0);
    g->lineTo(camWidth + 1, camHeight + 1);
    g->lineTo(-1, camHeight + 1);
    g->lineTo(-1, 0);
    g->endFill();

//    flBitmap* bitmap = new flBitmap(_videoTexture);
//    //    bitmap->alpha(0.5);
//    addChild(bitmap);
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
    
    camera.setPosition(cameraPos);
    
    _width = right - left;
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
    
    //--------------------------------------
    ofPushStyle();
    ofSetColor(lineColor);
    if(fillEnabled) {
        ofFill();
    } else {
        ofNoFill();
    }
    ofSetLineWidth(2);
    ofDrawBox(left + _width * 0.5, 0, 0, _width, 100, 100);
    ofPopStyle();
    //--------------------------------------

    //--------------------------------------
    if(wireframeEnabled) {
        //--------------------------------------
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        ofEnableAlphaBlending();
        glEnable(GL_DEPTH_TEST);
        
        ofPushStyle();
        ofSetColor(0);
        ofNoFill();
        
        ofSetLineWidth(lineWidth);
        ofDrawBox(left + _width * 0.5, 0, 0, _width, 100, 100);
        ofPopStyle();
        
        glPopAttrib();
        //--------------------------------------
    }
    //--------------------------------------

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
