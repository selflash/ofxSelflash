#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "UIComponents.h"
#include "AppModel.h"
#include "Renderer.h"

using namespace fl2d;

class ofApp : public ofBaseApp {
    public:
        AppModel appModel;
        UIComponents* uiComponents;
        Renderer* renderer;
        ofEventListeners listeners;
        bool enabled = true;
    
        bool animationEnabled = false;

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
        void _uiComponentsEventHandler(flEvent& event);
    
};
