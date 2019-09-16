#pragma once

#include "ofMain.h"

#include "ofxSelflash.h"

using namespace fl2d;

class ofApp : public ofBaseApp {
public:
    ofImage image1;
    flBitmap* bitmap1;
    
    flBitmap* bitmap2;
    
    ofTexture texture3;
    flBitmap* bitmap3;
    
    flBitmap* bitmap4;
    
    flBitmap* bitmap5;

    ofVideoGrabber vidGrabber;
    ofTexture videoTexture;
    flBitmap* bitmap6;

private:
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    
};
