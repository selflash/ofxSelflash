#pragma once

#include "ofMain.h"

#include "ofxSelflash.h"
//#include "ofxSTweener.h"
#include "ofxSTweener2D.h"

class ofApp : public ofBaseApp {
    public:
        flSprite* box0;
        flSprite* box1;
        flSprite* box2;
        flSprite* box3;
        flSprite* box4;
        flSprite* box5;
        
        flSTweenCore* tween001; flSTweenCore* tween002; flSTweenCore* tween003;
        flSTweenCore* tween101; flSTweenCore* tween102; flSTweenCore* tween103;
        flSTweenCore* tween201; flSTweenCore* tween202; flSTweenCore* tween203;
        flSTweenCore* tween301; flSTweenCore* tween302; flSTweenCore* tween303;
        flSTweenCore* tween401; flSTweenCore* tween402; flSTweenCore* tween403;
        flSTweenCore* tween501; flSTweenCore* tween502; flSTweenCore* tween503;
    
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
        void _tweenStart(flSTweenCore* currentTarget);
        void _tweenUpdate(flSTweenCore* currentTarget);
        void _tweenComplete(flSTweenCore* currentTarget);

        void _playAnimation0();
        void _playAnimation1();
        void _playAnimation2();
        void _playAnimation3();
        void _playAnimation4();
        void _playAnimation5();
};
