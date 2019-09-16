#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
#ifdef _DEBUG_MEASURE_PROCESS_TIME
	TIME_SAMPLE_SET_FRAMERATE(60.0f);
#endif

	ofSetFrameRate(60);
	ofSetVerticalSync(true);

	//----------------------------------
	Config::load();

	AppEngine::setup();

    ofxSelflash::setup();
    flStage* stage = ofxSelflash::stage();
    stage->addEventListener(flFocusEvent::FOCUS_IN, this, &ofApp::_eventHandler);
    stage->addEventListener(flFocusEvent::FOCUS_OUT, this, &ofApp::_eventHandler);

	//--------------------------------------
	networkManager = AppEngine::networkManager();
    networkManager->addEventListener(NetworkEvent::RECEIVED, this, &ofApp::_networkEventHandler);
    networkManager->addEventListener("udp0Received", this, &ofApp::_networkEventHandler);
	//networkManager->bindWithUDP(0, Config::udp_local_port0);
	//--------------------------------------
    
	//--------------------------------------
	mainController = new MainController();
	mainController->setup();
	mainController->x(1);
	mainController->y(ofGetHeight() - mainController->height() - 1);
	stage->addChild(mainController);
	((NetworkController*)mainController->controller0())->networkManager(AppEngine::networkManager());
    AppEngine::controller((flBasicController*)mainController);
	//--------------------------------------
}

//--------------------------------------------------------------
void ofApp::exit()
{
    
}

//--------------------------------------------------------------
void ofApp::update()
{		

}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(128);

	ofxSelflash::draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

//--------------------------------------------------------------
// Event Handler
//--------------------------------------------------------------

//--------------------------------------------------------------
//
void ofApp::_eventHandler(flEvent& event) {
	cout << "[ofApp]_eventHandler(" << event.type() << ")" << endl;
	//    cout << "[ofApp]this          = " << this << "," << ((flDisplayObject*) this)->name() << endl;
	cout << "[ofApp]currentTarget = " << event.currentTarget() << ", " << ((flDisplayObject*)event.currentTarget())->name() << endl;
	cout << "[ofApp]target        = " << event.target() << ", " << ((flDisplayObject*)event.target())->name() << endl;

	if (event.type() == flEvent::ADDED_TO_STAGE) {

	}

	if (event.type() == flFocusEvent::FOCUS_IN) {
		if (event.currentTarget() == ofxSelflash::stage()) {
            
		}
	}
	else if (event.type() == flFocusEvent::FOCUS_OUT) {
		if (event.currentTarget() == ofxSelflash::stage()) {
            
		}
	}
}


void ofApp::_networkEventHandler(flEvent& event) {
    cout << "[ofApp]_networkEventHandler(" << ofToString(event.type()) << ")" << endl;
    
    NetworkEvent& networkEvent = *(NetworkEvent*) &event;
    vector<string> messages = ofSplitString(networkEvent.data(), "@");
    string eventName = messages[0];
    if(eventName == " ") goto break0;
    
    if(event.type() == "udp0Received") {
        //----------------------------------
        if(eventName == "connected") {
            
        }
        if(
           eventName == "disconnected" ||
           eventName == "close"
           ) {
            
        }
        if(eventName == "startConversion") {
            
        }
        if(eventName == "endConversion") {
            //            copyTo();
        }
        //----------------------------------
    }
    
break0:;
}
