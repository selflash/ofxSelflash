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
//    renderer = new Renderer();
    appModel.setup();
    appModel.x(980);
    appModel.y(40);
    ofxSelflash::stage()->addChild(&appModel);
    //--------------------------------------
    
    //--------------------------------------
    renderer = new Renderer();
    renderer->setup();
    renderer->x(550);
    renderer->y(300);
    ofxSelflash::stage()->addChildAt(renderer, 0);
    //--------------------------------------
    
    //--------------------------------------
    //Bind
    renderer->bgColor = appModel.bgColor;
    listeners.push(appModel.bgColor.newListener([&](ofColor& value) {
        renderer->bgColor = value;
    }));
    uiComponents->colorSlider001->bind(appModel.bgColor);

//    renderer->cameraPos.x = appModel.cameraPosVelXY->x;
//    renderer->cameraPos.y = appModel.cameraPosVelXY->y;
    listeners.push(appModel.cameraPosVelXY.newListener([&](vec2& value) {
//        ofLog() << "value.x = " << value.x;
//        ofLog() << "value.y = " << value.y;
        renderer->cameraPos.x += value.x * 1;
        renderer->cameraPos.y += value.y * 1;
    }));
    uiComponents->joystick2001->bind(appModel.cameraPosVelXY);
    
//    renderer->cameraPos.z = appModel.cameraPosVelZ;
    listeners.push(appModel.cameraPosVelZ.newListener([&](float& value) {
        renderer->cameraPos.z += value * 1;
    }));
    uiComponents->joystick1001->bind(appModel.cameraPosVelZ);

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

//    renderer->testVec2 = appModel.testVec2;
    listeners.push(appModel.testVec2.newListener([&](vec2& value) {
//        renderer->testVec2 = value;
    }));
    uiComponents->vec2Slider001->bind(appModel.testVec2);

//    renderer->testVec3 = appModel.testVec3;
    listeners.push(appModel.testVec3.newListener([&](vec3& value) {
//        renderer->testVec3 = value;
    }));
    uiComponents->vec3Slider001->bind(appModel.testVec3);

    renderer->left = appModel.left;
    listeners.push(appModel.left.newListener([&](float& value) {
        renderer->left = value;
    }));
    uiComponents->rangeSlider001->bindMin(appModel.left);
    
    renderer->right = appModel.right;
    listeners.push(appModel.right.newListener([&](float& value) {
        renderer->right = value;
    }));
    uiComponents->rangeSlider001->bindMax(appModel.right);
    
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
    
//    renderer->wireframeEnabled = appModel.wireframeEnabled;
    listeners.push(appModel.testFloat.newListener([&](float& value) {
//        renderer->wireframeEnabled = value;
    }));
    uiComponents->dialer001->bind(appModel.testFloat);
    
//    renderer->testVec2 = appModel.testVec2;
    listeners.push(appModel.testVec2ForPad2d.newListener([&](vec2& value) {
        //        renderer->testVec2 = value;
    }));
    uiComponents->pad002->bind(appModel.testVec2ForPad2d);
    
//    renderer->testVec2 = appModel.testVec2;
    listeners.push(appModel.testInt.newListener([&](int& value) {
        //        renderer->testVec2 = value;
    }));
    uiComponents->comboBox001->bind(appModel.testInt);
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
        
        appModel.left = ((sin(elapsedTime * 1.58) + 1.0) / 2.0) * -50.0;
        appModel.right = ((sin(elapsedTime * 1.75) + 1.0) / 2.0) * 50.0;

        appModel.cameraPosVelXY = vec2(sin(elapsedTime * 2.1), sin(elapsedTime * 1.5));
        appModel.cameraPosVelZ = sin(elapsedTime * 3.0);

        appModel.testVec2 = vec2(
                              ((sin(elapsedTime) + 1.0) / 2.0) * 200,
                              ((sin(elapsedTime) + 1.0) / 1.5) * 200
                              );

        appModel.testVec3 = vec3(
                                 ((sin(elapsedTime) + 1.0) / 2.0) * 200,
                                 ((sin(elapsedTime) + 1.0) / 1.5) * 200,
                                 ((sin(elapsedTime) + 1.0) / 2.5) * 200
                                 );

        appModel.testFloat = sin(elapsedTime * 1.5) * 100;

        appModel.testVec2ForPad2d = vec2(
                                 ((sin(elapsedTime) + 1.0) / 2.0) * 200,
                                 ((sin(elapsedTime) + 1.0) / 1.5) * 200
                                 );
        
        appModel.testInt = ((sin(elapsedTime) + 1.0) / 2.0) * 8;

        
//        appModel.cameraPosXY = { sin(elapsedTime * 1.7), sin(elapsedTime * 1.5) };
//        appModel.cameraPosXY.y = sin(elapsedTime * 1.5);
//        uiComponents->joystick2001->moveLever(sin(elapsedTime * 1.7), sin(elapsedTime * 1.5));

//        appModel.bgColor.g = ((sin(elapsedTime * 0.75) + 1.0) / 2.0) * 255.0;
//        appModel.bgColor.b = ((sin(elapsedTime * 0.45) + 1.0) / 2.0) * 255.0;
//        appModel.lineColor = ofColor(124, 30, 124, 200);

    }
    
    if(animation2Enabled) {
        float elapsedTime = ofGetElapsedTimef();
        float n = ((sin(elapsedTime) + 1.0) / 2.0);
        //        ofLog() << "n = " << n;

        uiComponents->rangeSlider001->minValue(((sin(elapsedTime * 1.58) + 1.0) / 2.0) * -50);
        uiComponents->rangeSlider001->maxValue(((sin(elapsedTime * 1.75) + 1.0) / 2.0) * 50);

        uiComponents->slider001->value(((sin(elapsedTime) + 1.0) / 2.0) * 20);
        uiComponents->slider002->value(((sin(elapsedTime * 1.7) + 1.0) / 2.0) * 10.0);
        uiComponents->colorSlider002->colorValue(ofColor(
                                                         ((sin(elapsedTime * 0.58) + 1.0) / 2.0) * 255,
                                                         ((sin(elapsedTime * 0.75) + 1.0) / 2.0) * 255,
                                                         ((sin(elapsedTime * 0.45) + 1.0) / 2.0) * 255,
                                                         255
                                                         ));
        
        uiComponents->vec2Slider001->xValue(((sin(elapsedTime) + 1.0) / 2.0) * 200);
        uiComponents->vec2Slider001->yValue(((sin(elapsedTime) + 1.0) / 1.5) * 200);

        uiComponents->vec3Slider001->xValue(((sin(elapsedTime) + 1.0) / 2.0) * 200);
        uiComponents->vec3Slider001->yValue(((sin(elapsedTime) + 1.0) / 1.5) * 200);
        uiComponents->vec3Slider001->zValue(((sin(elapsedTime) + 1.0) / 2.5) * 200);

        uiComponents->check001->selected(sin(elapsedTime * 1.4) < 0 ? false : true);
        uiComponents->check002->selected(sin(elapsedTime * 1.8) < 0 ? false : true);

        uiComponents->joystick2001->moveLever(sin(elapsedTime * 2.1), sin(elapsedTime * 1.5));
        uiComponents->joystick1001->moveLever(sin(elapsedTime * 3.0));
        
        uiComponents->dialer001->value(sin(elapsedTime * 1.5) * 100);
        
        uiComponents->pad002->xValue(((sin(elapsedTime) + 1.0) / 2.0) * 200);
        uiComponents->pad002->yValue(((sin(elapsedTime) + 1.0) / 1.5) * 200);

        uiComponents->comboBox001->selectedIndex(((sin(elapsedTime) + 1.0) / 2.0) * 8);
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
    if(key == ' ') {
        //Doesn't call update() and draw().
        ofxSelflash::pause(!ofxSelflash::pause());
        ofxSelflash::visible(!ofxSelflash::visible());
    }

    
    if(key == 'a') {
        animationEnabled = !animationEnabled;
    }
    if(key == 'A') {
        animation2Enabled = !animation2Enabled;
    }

    if(key == 's') {
        uiComponents->button003->press();
    }
    
    if(key == 'l') {
		//Lock / Unlock
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
    
    if(key == 'd') {
        listeners.unsubscribeAll();
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
