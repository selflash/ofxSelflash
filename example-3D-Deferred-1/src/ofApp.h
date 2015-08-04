#pragma once

#include "ofMain.h"

#define FLASH_3D
#include "ofxSelflash.h"

#include "World3D.h"

#include "Camera3DController.h"
#include "DepthOfFieldController.h"
#include "GLSLAssister.h"

using namespace fl2d;
using namespace fl3d;

class ofApp : public ofBaseApp {
    public:
        ofSpherePrimitive sphere;
        ofIcoSpherePrimitive icoSphere;
        ofPlanePrimitive plane;
        ofCylinderPrimitive cylinder;
        ofConePrimitive cone;
        ofBoxPrimitive box;
        
        vector<ofVec3f> boxPositions;
        vector<float> boxSizes;
        vector<ofColor> boxColors;
        
        GLSLAssister* _glslAssister;
        BokehDOF* _bokehDof;
        ofEasyCam camera;
        float cameraZ;

    protected:
    
    private:
        World3D* _world;
    
        ofBoxPrimitive* _primitive;
        ofTexture* _diffuseTexture;
    
        Camera3DController* _controller01;
        DepthOfFieldController* _controller02;
    
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
