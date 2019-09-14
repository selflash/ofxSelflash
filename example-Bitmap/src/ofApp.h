#pragma once

#include "ofMain.h"

#include "ofxSelflash.h"

class ofApp : public ofBaseApp {
public:
    flBitmap* bitmap1;
    
    ofImage image1;
    flBitmap* bitmap2;
    
    flBitmap* bitmap3;
    
    ofTexture texture1;
    flBitmap* bitmap4;
    
    flBitmap* bitmap5;
    
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
