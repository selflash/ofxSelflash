#pragma once

#include "ofMain.h"

#include "ofxSelflash.h"
#include "UIComponents.h"

using namespace fl2d;

class ofApp : public ofBaseApp {
    public:
        UIComponents* uiComponents;
    
    private:
        float _count;
        float _speed;
        ofFloatColor _color;
    
        ofVec3f _position;
        bool _enabled = true;
    
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
        void _uiComponentsEventHandler(flEvent& event);
    
};
