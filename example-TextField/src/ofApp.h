#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"

class ofApp : public ofBaseApp {
    
    public:
        flTextField* textField001;
    
        flTextField* textField101;
        flTextField* textField102;
        flTextField* textField103;
    
        flTextField* textField201;
        flTextField* textField202;
        flTextField* textField203;
    
        bool isShowRect;
        bool isTween;
    
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
        
};