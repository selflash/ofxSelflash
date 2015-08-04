#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(200, 200, 200);
    ofSetWindowTitle("example-Primitive3D");
    
    //Flashフレームワークの準備
    ofxSelflash::setup(true);
    Stage* stage = ofxSelflash::stage();
    
    _world = new World3D();
    _world->name("World");
    stage->addChild(_world);
    _world->setup();
    
//    ofEnableAlphaBlending();
    
    //----------------------------------
    _glslAssister = new GLSLAssister();
    _glslAssister->setup(ofGetWidth(), ofGetHeight());
    _glslAssister->camera = _world->camera()->camera();
    //----------------------------------
    
    //----------------------------------
    _bokehDof = new BokehDOF();
    _bokehDof->setup();
    //----------------------------------
    
    _controller01 = new Camera3DController();
    _controller01->setup();
    _controller01->x();
    _controller01->y();
    ((Camera3DController*) _controller01)->camera(_world->camera());
    stage->addChild(_controller01);
    
//    _controller02 = new DepthOfFieldController();
//    _controller02->setup();
//    _controller02->x(600);
//    _controller02->y();
//    ((DepthOfFieldController*) _controller02)->bokehDOF(_world->bokehDOF());
//    stage->addChild(_controller02);

    //----------------------------------
//    ofBackground(1.0, 1.0, 1.0);
//	for(int i = 0; i < 1000; i++){
//		boxPositions.push_back(ofVec3f(ofRandom(-1300, 1300),
//									   ofRandom(-1300, 1300),
//									   ofRandom(-1300, 1300)));
//		boxSizes.push_back(ofRandom(30, 100));
//		boxColors.push_back(ofColor::fromHsb(ofRandomuf() > 0.8 ? ofRandom(120, 130) : 128 - ofRandom(110, 128),
//											 ofRandom(255),
//											 ofRandom(255)
//                                             )
//                            );
//	}
//
//    cameraZ = 700;
//    camera.setPosition(0, 0, cameraZ);
    //----------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
    
//    camera.setPosition(0, 0, cameraZ);
}

//--------------------------------------------------------------
void ofApp::draw() {
    return;
    
//	_glslAssister->begin();
	_bokehDof->begin();
	
    //----------------------------------
	camera.begin();
    
	ofPushStyle();
	for(int i = 0; i < boxPositions.size(); i ++){
        sphere.setPosition(boxPositions[i]);
        ofFill();
		ofSetColor(boxColors[i]);
		ofDrawBox(boxPositions[i], boxSizes[i]);
	}
	ofPopStyle();
    //----------------------------------
    
	camera.end();
	
    _bokehDof->end();
    _bokehDof->draw(0, 0);
    
//    _glslAssister->end();
//    _glslAssister->draw(0, 0);
	
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 10, 10);
//    if(false) {
//        glEnable(GL_DEPTH_TEST);
//
//        ofPushMatrix();
//        
//        ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
//        ofRotateX(sin(ofGetElapsedTimef()) * 330);
//        ofRotateY(sin(ofGetElapsedTimef() * 0.6) * 360);
//        
//        ofPushStyle();
//        ofSetColor(255, 255, 255);
//        _diffuseTexture->bind();
//        _primitive->draw();
//        _diffuseTexture->unbind();
//        ofPopStyle();
//        
//        ofPopMatrix();
//    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == OF_KEY_UP) {
        cameraZ -= 100;
    }
    if(key == OF_KEY_DOWN) {
        cameraZ += 100;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

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
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
