#pragma once

#include "ofMain.h"
#include "ofxSelflash.h"
#include "AppEngine.h"
#include "MainController.h"
#include "NetworkManager.h"

#include "ViewController.h"
#include "Model.h"
#include "Controller.h"
#include "boost/shared_ptr.hpp"

using namespace boost;

using namespace fl2d;

class ofApp : public ofBaseApp
{
	public:
        Model model;
        Controller controller;
        ViewController viewController;
    
		MainController* mainController;
		NetworkManager* networkManager;
    
        ofTexture sampleTex;

	private:

	public:
		void setup();
		void exit();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		void _eventHandler(flEvent& event);
        void _networkEventHandler(flEvent& event);
};
