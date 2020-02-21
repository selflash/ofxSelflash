#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    ofSetWindowTitle("example-UIComponents-1");
    //ofDisableAntiAliasing();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    //--------------------------------------
    ofxSelflash::setup();
    //--------------------------------------
    
    //--------------------------------------
    uiComponents = new UIComponents();
    uiComponents->setup();
    ofxSelflash::stage()->addChild(uiComponents);
    //--------------------------------------
    
    //--------------------------------------
    renderer = new Renderer();
    renderer->setup();
    renderer->x(550);
    renderer->y(300);
    ofxSelflash::stage()->addChild(renderer);
    //--------------------------------------
    
    //--------------------------------------
    //Bind
    renderer->bgColor = appModel.bgColor;
    listeners.push(appModel.bgColor.newListener([&](ofColor& value) {
        renderer->bgColor = value;
    }));
    uiComponents->colorSlider001->bind(appModel.bgColor);

    renderer->cameraPos.x = appModel.cameraPosXY->x;
    renderer->cameraPos.y = appModel.cameraPosXY->y;
    listeners.push(appModel.cameraPosXY.newListener([&](vec2& value) {
        renderer->cameraPos.x += value.x * 1;
        renderer->cameraPos.y += value.y * 1;
    }));
    uiComponents->joystick2001->bind(appModel.cameraPosXY);
    
    renderer->lineColor = appModel.lineColor;
    listeners.push(appModel.lineColor.newListener([&](ofColor& value) {
        renderer->lineColor = value;
    }));
    uiComponents->colorSlider002->bind(appModel.lineColor);

    renderer->lineWidth = appModel.lineWidth;
    listeners.push(appModel.lineWidth.newListener([&](int& value) {
        renderer->lineWidth = value;
    }));
    uiComponents->slider001->bind(appModel.lineWidth);

    renderer->speed = appModel.speed;
    listeners.push(appModel.speed.newListener([&](float& value) {
        renderer->speed = value;
    }));
    uiComponents->slider002->bind(appModel.speed);

    renderer->fillEnabled = appModel.fillEnabled;
    listeners.push(appModel.fillEnabled.newListener([&](bool& value) {
        renderer->fillEnabled = value;
    }));
    uiComponents->check001->bind(appModel.fillEnabled);
    
    renderer->wireframeEnabled = appModel.wireframeEnabled;
    listeners.push(appModel.wireframeEnabled.newListener([&](bool& value) {
        renderer->wireframeEnabled = value;
    }));
    uiComponents->check002->bind(appModel.wireframeEnabled);
    //--------------------------------------
    
    
    //--------------------------------------
    {
        _guideLinePath.clear();
        _guideLinePath.setStrokeColor(ofColor(255, 255, 255, 50));
        _guideLinePath.setFilled(false);
        _guideLinePath.setStrokeWidth(1.0);
        
        int w = ofGetWidth();
        int h = ofGetHeight();
        for(int i = 0; i < w; i += 10) {
            _guideLinePath.moveTo(i, 0);
            _guideLinePath.lineTo(i, h);
        }
        for(int i = 0; i < h; i += 10) {
            _guideLinePath.moveTo(0, i);
            _guideLinePath.lineTo(w, i);
        }
    }
    //--------------------------------------
    
    //--------------------------------------
    {
        _guideLinePath2.clear();
        _guideLinePath2.setStrokeColor(ofColor(255, 255, 255, 100));
        _guideLinePath2.setFilled(false);
        _guideLinePath2.setStrokeWidth(1.0);
        
        int w = ofGetWidth();
        int h = ofGetHeight();
        for(int i = 0; i < w; i += 170) {
            _guideLinePath2.moveTo(i, 0);
            _guideLinePath2.lineTo(i, h);
        }
        for(int i = 0; i < h; i += 170) {
            _guideLinePath2.moveTo(0, i);
            _guideLinePath2.lineTo(w, i);
        }
    }
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::update() {
    if(animationEnabled) {
        float elapsedTime = ofGetElapsedTimef();
        float n = ((sin(elapsedTime) + 1.0) / 2.0);
//        ofLog() << "n = " << n;
        appModel.lineWidth = ((sin(elapsedTime) + 1.0) / 2.0) * 20;
        appModel.speed = ((sin(elapsedTime * 1.7) + 1.0) / 2.0) * 10.0;
        appModel.lineColor = ofColor(
            ((sin(elapsedTime * 0.58) + 1.0) / 2.0) * 255,
            ((sin(elapsedTime * 0.75) + 1.0) / 2.0) * 255,
            ((sin(elapsedTime * 0.45) + 1.0) / 2.0) * 255,
            255
        );
        appModel.fillEnabled = sin(elapsedTime * 1.4) < 0 ? false : true;
        appModel.wireframeEnabled = sin(elapsedTime * 1.8) < 0 ? false : true;
        
        uiComponents->joystick2001->moveLever(sin(elapsedTime * 1.7), sin(elapsedTime * 1.5));
        
//        appModel.bgColor.g = ((sin(elapsedTime * 0.75) + 1.0) / 2.0) * 255.0;
//        appModel.bgColor.b = ((sin(elapsedTime * 0.45) + 1.0) / 2.0) * 255.0;
//        appModel.lineColor = ofColor(124, 30, 124, 200);

    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    drawGrid();
    
    //----------------------------------
    ofxSelflash::draw();
    //----------------------------------
    
    //--------------------------------------
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 255, 255, 200);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 5);
    ofPopStyle();
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::drawGrid() {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    ofEnableAlphaBlending();
//    ofEnableSmoothing();
//    ofDisableAntiAliasing();
    
    _guideLinePath.draw();
    _guideLinePath2.draw();

    glPopAttrib();
}

//==============================================================
// Private Event Handler
//==============================================================

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == 'a') {
        animationEnabled = !animationEnabled;
//        appModel.lineWidth = 15;
//        appModel.speed = 0.5;
//        appModel.bgColor = ofColor(255, 124, 30, 200);
//        appModel.lineColor = ofColor(124, 30, 124, 200);
    }
    
    if(key == 's') {
        uiComponents->button003->press();
    }
    
    if(key == ('l')) {
        enabled = !enabled;
        int numChildren = uiComponents->numChildren();
        for(int i = 0; i < numChildren; i++) {
            flDisplayObject* displayObject = (flDisplayObject*)uiComponents->getChildAt(i);
//            ofLog() << "displayObject->name() = " << displayObject->name();

            if(displayObject->typeID() == FL_TYPE_UIBASE) {
                ofLog() << "displayObject.name = " << displayObject->name();
                ((flUIBase*)displayObject)->enabled(enabled);
            }
        }
    }
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
void ofApp::windowResized(int w, int h) {
    //--------------------------------------
    {
        _guideLinePath.clear();
        _guideLinePath.setStrokeColor(ofColor(255, 255, 255, 50));
        _guideLinePath.setFilled(false);
        _guideLinePath.setStrokeWidth(1.0);
        
        for(int i = 0; i < w; i += 10) {
            _guideLinePath.moveTo(i, 0);
            _guideLinePath.lineTo(i, h);
        }
        for(int i = 0; i < h; i += 10) {
            _guideLinePath.moveTo(0, i);
            _guideLinePath.lineTo(w, i);
        }
    }
    //--------------------------------------
    
    //--------------------------------------
    {
        _guideLinePath2.clear();
        _guideLinePath2.setStrokeColor(ofColor(255, 255, 255, 50));
        _guideLinePath2.setFilled(false);
        _guideLinePath2.setStrokeWidth(1.0);
        
        for(int i = 0; i < w; i += 170) {
            _guideLinePath2.moveTo(i, 0);
            _guideLinePath2.lineTo(i, h);
        }
        for(int i = 0; i < h; i += 170) {
            _guideLinePath2.moveTo(0, i);
            _guideLinePath2.lineTo(w, i);
        }
    }
    //--------------------------------------
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}
