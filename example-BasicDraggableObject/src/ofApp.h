#pragma once

#include "ofMain.h"

#include "ofxSelflash.h"
#include "BasicDraggableObject.h"
#include "ImageFrame1.h"
#include "ImageFrame2.h"
#include "ImageFrame3.h"

class ofApp : public ofBaseApp {
    public:
        BasicDraggableObject* draggableObject;
        ImageFrame1* imageFrame1;
        ImageFrame2* imageFrame2;
        ImageFrame3* imageFrame3;
    
    protected:
    
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
		
    protected:
    
    private:

};
