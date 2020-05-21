#include "ofApp.h"

//--------------------------------------------------------------
//
void ofApp::setup() {
    ofSetWindowTitle("example-BasicController");
    ofDisableAntiAliasing();
    
    //--------------------------------------
    //Camera
    camera.setPosition(0, 0, 100.0);
    camera.setNearClip(0.01);
    
    transformableNode.enabled(true);
    //--------------------------------------
    
    //--------------------------------------
    ofxSelflash::setup();
    ofxSelflash::stage()->addEventListener(flFocusEvent::FOCUS_IN, this, &ofApp::_eventHandler);
    ofxSelflash::stage()->addEventListener(flFocusEvent::FOCUS_OUT, this, &ofApp::_eventHandler);
    //--------------------------------------
    
    //--------------------------------------
    //Main Controller
    mainController = new MainController();
    mainController->setup();
    mainController->controller1()->text001->text("X : " + ofToString(transformableNode.rotationY()));
    mainController->controller1()->text002->text("Y : " + ofToString(transformableNode.rotationX()));
    mainController->controller1()->text003->text("Z : " + ofToString(transformableNode.rotationZ()));
    mainController->controller1()->text101->text("X : " + ofToString(transformableNode.x()));
    mainController->controller1()->text102->text("Y : " + ofToString(transformableNode.y()));
    mainController->controller1()->text103->text("Z : " + ofToString(transformableNode.z()));
    mainController->addEventListener("uiEvent1", this, &ofApp::_uiEventHandler);
    //    mainController->alpha(0.5);
    ofxSelflash::stage()->addChild(mainController);
    //--------------------------------------
}

//--------------------------------------------------------------
//
void ofApp::update() {
    //----------------------------------
//    ofxSelflash::update();
    //----------------------------------
}

//--------------------------------------------------------------
//
void ofApp::draw() {
    //--------------------------------------
    camera.begin();
    
    ofEnableDepthTest();
    
    transformableNode.begin();
    
    //--------------------------------------
    _rotation += 0.2;
    
    ofPushMatrix();
    ofRotateX(_rotation);
    ofRotateY(_rotation * 0.75);
    
    ofPushStyle();
    //Fill or No Fill
    if(mainController->controller2()->check001->selected()) {
        ofFill();
    } else {
        ofNoFill();
        //Line Width
        ofSetLineWidth(mainController->controller2()->slider001->value());
    }
    //Color
    ofSetColor(
               mainController->controller2()->colorSlider001->redValue(),
               mainController->controller2()->colorSlider001->greenValue(),
               mainController->controller2()->colorSlider001->blueValue()
               );
    ofDrawBox(0, 0, 0, 30, 30, 30);
    ofPopStyle();
    
    ofPopMatrix();
    //--------------------------------------
    
    transformableNode.end();
    transformableNode.draw();
    
    ofDisableDepthTest();
    
    camera.end();
    //--------------------------------------
    
    //----------------------------------
    ofxSelflash::draw();
    //----------------------------------
    
    //----------------------------------
    //Draw Mouse Guide
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(2);
    ofEnableAlphaBlending();
    if(_isMouseDown) {
        ofSetColor(80, 180, 255, 150);
        ofDrawCircle(_mouseDownPosition, 10);
        ofDrawLine(_mouseDownPosition.x, _mouseDownPosition.y, ofGetMouseX(), ofGetMouseY());
    }
    ofSetColor(80, 180, 255, 255);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 10);
    ofPopStyle();
    //----------------------------------
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void ofApp::_eventHandler(flEvent& event) {
    cout << "[ofApp]_eventHandler(" << event.type() << ")" << endl;
    //    cout << "[ofApp]this          = " << this << "," << ((flDisplayObject*) this)->name() << endl;
    cout << "[ofApp]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name() << endl;
    cout << "[ofApp]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name() << endl;
    
    if(event.type() == flEvent::ADDED_TO_STAGE) {
        
    }
    
    if(event.type() == flFocusEvent::FOCUS_IN) {
        if(event.currentTarget() == ofxSelflash::stage()) {
            transformableNode.enabled(true);
        }
    }
    if(event.type() == flFocusEvent::FOCUS_OUT) {
        if(event.currentTarget() == ofxSelflash::stage()) {
            transformableNode.enabled(false);
        }
    }
}

//--------------------------------------------------------------
//
void ofApp::_uiEventHandler(flEvent& event) {
    cout << "[ofApp]_uiEventHandler(" << event.type() << ")" << endl;
    
    //    //------------------------------------------
    //    //イベントタイプ
    //    cout << "event.type          = " << event.type() << endl;
    //    //カレントターゲット
    //    cout << "event.currentTarget = " << event.currentTarget() << ", " << ((DisplayObject*) event.currentTarget())->name() << endl;
    //    //イベントターゲット
    //    cout << "event.target        = " << event.target() << ", " << ((DisplayObject*) event.target())->name() << endl;
    //    //------------------------------------------
    
    if(event.type() == "uiEvent1") {
        if(event.target() == mainController->controller1()->joystick1001) {
            float velY = mainController->controller1()->joystick1001->value() * 2;
            transformableNode.rotationY(transformableNode.rotationY() + velY);
            mainController->controller1()->text001->text("X : " + ofToString(transformableNode.rotationY()));
        }
        if(event.target() == mainController->controller1()->joystick1002) {
            float velX = mainController->controller1()->joystick1002->value() * 2;
            transformableNode.rotationX(transformableNode.rotationX() + velX);
            mainController->controller1()->text002->text("Y : " + ofToString(transformableNode.rotationX()));
        }
        if(event.target() == mainController->controller1()->joystick1003) {
            float velZ = mainController->controller1()->joystick1003->value() * 2;
            transformableNode.rotationZ(transformableNode.rotationZ() + velZ);
            mainController->controller1()->text003->text("Z : " + ofToString(transformableNode.rotationZ()));
        }
        
        if(event.target() == mainController->controller1()->joystick1101) {
            float velX = mainController->controller1()->joystick1101->value();
            transformableNode.x(transformableNode.x() + velX);
            mainController->controller1()->text101->text("X : " + ofToString(transformableNode.x()));
        }
        if(event.target() == mainController->controller1()->joystick1102) {
            float velY = mainController->controller1()->joystick1102->value();
            transformableNode.y(transformableNode.y() + velY);
            mainController->controller1()->text102->text("Y : " + ofToString(transformableNode.y()));
        }
        if(event.target() == mainController->controller1()->joystick1103) {
            float velZ = mainController->controller1()->joystick1103->value();
            transformableNode.z(transformableNode.z() + velZ);
            mainController->controller1()->text103->text("Z : " + ofToString(transformableNode.z()));
        }
    }
    
    //ボタン(ダウン)
    if(event.type() == flButtonEvent::MOUSE_DOWN) {
        flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
    }
    //ボタン(チェンジ)
    if(event.type() == flButtonEvent::CHANGE) {
        flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
    }
    
    //コンボボックス
    if(event.type() == flComboBoxEvent::CHANGE) {
        flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
        flComboBox* comboBox = (flComboBox*)(event.currentTarget());
    };
    
    //ラジオボタン
    if(event.type() == flRadioButtonEvent::CHANGE) {
        flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
        flRadioButton* radio = (flRadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
    if(event.type() == flNumericDialerEvent::CHANGE) {
        flNumericDialerEvent& numericDialerEvent = *(flNumericDialerEvent*) &event;
        flNumericDialer* dialer = (flNumericDialer*)(event.currentTarget());
    }
    
    //2Dパッド
    if(event.type() == flPadEvent::CHANGE) {
        flPadEvent& padEvent = *(flPadEvent*) &event;
        flPad2D* pad = (flPad2D*)(event.currentTarget());
    }
    
    //スライダー
    if(event.type() == flSliderEvent::CHANGE) {
        flSliderEvent& sliderEvent = *(flSliderEvent*) &event;
        flSlider* slider = (flSlider*)(event.currentTarget());
    }
    
    //レンジスライダー
    if(event.type() == flRangeSliderEvent::CHANGE) {
        flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
        flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
    }
    
    //カラースライダー
    if(event.type() == flColorSliderEvent::CHANGE) {
        flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
        flColorSlider* colorSlider = (flColorSlider*)(event.currentTarget());
    }
    
    //カラーピッカー
    if(event.type() == flColorPickerEvent::CHANGE) {
        flColorPickerEvent& colorPickerEvent = *(flColorPickerEvent*) &event;
        flCircleColorPicker* colorPicker = (flCircleColorPicker*)(event.currentTarget());
    }
    
    //ジョイスティック1D
    if(event.type() == flJoyStick1Event::CHANGE) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::UP) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::DOWN) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::LEFT) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::RIGHT) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    
    //ジョイスティック2D
    if(event.type() == flJoyStick2Event::CHANGE) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
    if(event.type() == flJoyStick2Event::UP) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
    if(event.type() == flJoyStick2Event::DOWN) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
    if(event.type() == flJoyStick2Event::LEFT) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
    if(event.type() == flJoyStick2Event::RIGHT) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
}

//--------------------------------------------------------------
//
void ofApp::keyPressed(int key) {
    
}

//--------------------------------------------------------------
//
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
//
void ofApp::mouseMoved(int x, int y ) {
    
}

//--------------------------------------------------------------
//
void ofApp::mouseDragged(int x, int y, int button) {
    
}

//--------------------------------------------------------------
//
void ofApp::mousePressed(int x, int y, int button) {
    _isMouseDown = true;
    _mouseDownPosition.x = x;
    _mouseDownPosition.y = y;
}

//--------------------------------------------------------------
//
void ofApp::mouseReleased(int x, int y, int button) {
    _isMouseDown = false;
}

//--------------------------------------------------------------
//
void ofApp::windowResized(int w, int h) {
    
}

//--------------------------------------------------------------
//
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
//
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}
