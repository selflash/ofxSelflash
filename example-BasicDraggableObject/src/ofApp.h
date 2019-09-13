#pragma once

#include "ofMain.h"

#include "ofxSelflash.h"
#include "BasicDraggableObject.h"
#include "FrameBorder1.h"
#include "FrameBorder2.h"
#include "FrameBorder3.h"

class ofApp : public ofBaseApp {
    public:
        BasicDraggableObject* noFrameBorder;
        FrameBorder1* frameBorder1;
        FrameBorder2* frameBorder2;
        FrameBorder3* frameBorder3;
    
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
