#pragma once

#include "ofMain.h"

#include "ofxSelflash.h"
#include "Container.h"

class ofApp : public ofBaseApp {
    public:
        Container* container;
    
        //--------------------------------------
        flTextField* textField000;
        flTextField* textField001;
        flTextField* textField002;
        flTextField* textField003;
        flTextField* textField004;
        //--------------------------------------
    
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
