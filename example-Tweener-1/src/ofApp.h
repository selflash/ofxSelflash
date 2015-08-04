#pragma once

#include "ofMain.h"

#define FLASH_3D
//#define FLASH_3D_ASSIMP
#include "ofxSelflash.h"
using namespace fl2d;
using namespace fl3d;

#include "STweener.h"
#include "BasicWorld3D.h"
#include "UIComponents.h"

class ofApp : public ofBaseApp {
    public:
        UIComponents* uiComponents;
    
    protected:
    
    private:
        float _value1;
        float _value2;
        float _value3;
        float _value4;
    
        float _count;
        float _speed;
        ofFloatColor _color;
    
        Sprite* _testObject2d;
    
        BasicWorld3D* _world;
        Cube3D* _testObject3d;
    
        STweenCore* _tween1;
        STweenCore* _tween2;
    
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
        void _playAnimation2d();
        void _playAnimation3d();
        void _reset2D();
        void _reset3D();
    
        void _uiComponentsEventHandler(Event& event);

};
