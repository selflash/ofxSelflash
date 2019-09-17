#include "CameraViewer.h"

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void CameraViewer::_setup() {
    int camWidth = 320;
    int camHeight = 240;
//    _vidGrabber.setDeviceID(0);
////    _vidGrabber.setDesiredFrameRate(60);
//    _vidGrabber.initGrabber(camWidth, camHeight);
//    _videoTexture.allocate(camWidth, camHeight, GL_RGBA);
    
    flGraphics* g;
    g = graphics();
    g->clear();
    g->beginFill(0x888888, 0.8);
    g->drawRect(0, 0, camWidth + 20, camHeight + 20);
    g->beginFill(0x008888, 1.0);
    g->drawRect(10, 10, camWidth, camHeight);
    g->endFill();
    
//    flBitmap* bitmap = new flBitmap(_videoTexture);
//    //    bitmap->alpha(0.5);
//    addChild(bitmap);
}

//--------------------------------------------------------------
//
void CameraViewer::_update() {
//    _vidGrabber.update();
//    if(_vidGrabber.isFrameNew()){
//        ofPixels& pixels = _vidGrabber.getPixels();
//        _videoTexture.loadData(pixels);
//    }
}

//--------------------------------------------------------------
//
void CameraViewer::_draw() {
    
}
