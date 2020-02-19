#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicDraggableObject.h"

using namespace fl2d;

class Renderer : public flBasicDraggableObject {
    public:
        int camWidth = 320 * 2;
        int camHeight = 240 * 2;

        ofEasyCam camera;
        ofRectangle viewPort;
        ofVec3f cameraPos = ofVec3f(0, 0, 100);

        ofVec3f objPos = ofVec3f(0, 0, -100);
        float speed = 0.5;

        ofColor bgColor = ofColor(0, 0, 0, 255);
        ofColor lineColor = ofColor(255, 255, 255, 255);
        int lineWidth = 1;
        bool fillEnabled = false;
        bool wireframeEnabled = false;
    
    protected:
        
    private:
        float _count = 0;

//        ofVideoGrabber _vidGrabber;
//        ofTexture _videoTexture;
    //    flBitmap* bitmap;
    

    public:
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        
};
