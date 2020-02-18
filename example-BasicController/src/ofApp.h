#pragma once

#include "ofMain.h"

#include "ofxSelflash.h"
#include "MainController.h"
#include "TransformableNode.h"

using namespace fl2d;

class ofApp : public ofBaseApp {
    public:
        MainController* mainController = NULL;
        
        ofCamera camera;
        TransformableNode transformableNode;
        
        float _rotation = 0.0;
        
        bool _isMouseDown = false;
        ofVec2f _mouseDownPosition;
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
        void _uiEventHandler(flEvent& event);
        void _eventHandler(flEvent& event);
        
};
