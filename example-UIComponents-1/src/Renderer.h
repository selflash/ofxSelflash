#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "flBasicDraggableObject.h"

using namespace fl2d;

class Renderer : public flBasicDraggableObject {
    public:
        int camWidth;
        int camHeight;

        ofEasyCam camera;
        ofRectangle viewPort;
        ofVec3f cameraPos;

        ofVec3f objPos;
        float speed;

        ofColor bgColor;
        int lineWidth;
    
    protected:
        
    private:
        float _count;

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
