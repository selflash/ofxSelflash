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
    //UIコンポーネント
    uiComponents = new UIComponents();
    uiComponents->setup();
    uiComponents->slider001->addEventListener(flSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->slider002->addEventListener(flSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->rangeSlider001->addEventListener(flRangeSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->rangeSlider002->addEventListener(flRangeSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->colorSlider001->addEventListener(flColorSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->button001->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->button002->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->button002->addEventListener(flEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->button003->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->button004->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->button005->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    //uiComponents->radio001->addEventListener(flRadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->radio002->addEventListener(flRadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->radio003->addEventListener(flRadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->pad001->addEventListener(flPadEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->pad002->addEventListener(flPadEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->colorPicker001->addEventListener(flColorPickerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1001->addEventListener(flJoyStick1Event::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1002->addEventListener(flJoyStick1Event::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1003->addEventListener(flJoyStick1Event::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1004->addEventListener(flJoyStick1Event::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1005->addEventListener(flJoyStick1Event::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1101->addEventListener(flJoyStick1Event::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick2001->addEventListener(flJoyStick2Event::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->dialer001->addEventListener(flNumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //    uiComponents->dialer002->addEventListener(NumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //    uiComponents->dialer003->addEventListener(NumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->comboBox001->addEventListener(flComboBoxEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->comboBox002->addEventListener(flComboBoxEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->comboBox003->addEventListener(flComboBoxEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    ofxSelflash::stage()->addChild(uiComponents);
    //--------------------------------------
    
    //--------------------------------------
    //
    _renderer = new Renderer();
    _renderer->setup();
    _renderer->x(550);
    _renderer->y(300);
    //    frameBorder1->alpha(0.5);
    ofxSelflash::stage()->addChild(_renderer);
    //--------------------------------------
    
    //--------------------------------------
    //Bind
    _renderer->speed = _appModel.speed;
    uiComponents->slider002->bind(_appModel.speed);
    _listeners.push(_appModel.speed.newListener([&](float& value) {
        _renderer->speed = value;
    }));
    //--------------------------------------

    //--------------------------------------
    //Bind
    _renderer->bgColor = _appModel.bgColor;
    uiComponents->colorSlider001->bind(_appModel.bgColor);
    _listeners.push(_appModel.bgColor.newListener([&](ofColor& value) {
        _renderer->bgColor = value;
    }));
    //--------------------------------------

    
//    flObject* object = new flObject();
//    float x = 100.5;
    
    //    object->setProperty<float>("x", &x);
    //    cout << object->getProperty<float>("x") << endl;
    //    
    //    object->setProperty<int>("y", 150);
    //    cout << object->getProperty<int>("y") << endl;
    //
    //    ofFloatColor* color1 = new ofFloatColor();
    //    color1->r = 255;
    //    color1->g = 100;
    //    
    //    object->setProperty<ofFloatColor>("color", color1);
    //    ofFloatColor* color2 = &object->getProperty<ofFloatColor>("color");
    //    cout << "R : " << color2->r << endl;
    //    cout << "G : " << color2->g << endl;
    //    cout << "B : " << color2->b << endl;
    //    cout << "A : " << color2->a << endl;
    //    
    //    ofFloatColor* color3 = new ofFloatColor();
    //    color3->r = 155;
    //    color3->g = 130;
    //    object->setProperty<ofFloatColor>("color1", color3);
    //    ofFloatColor* color4 = &object->getProperty<ofFloatColor>("color1");
    //    cout << "R : " << color4->r << endl;
    //    cout << "G : " << color4->g << endl;
    //    cout << "B : " << color4->b << endl;
    //    cout << "A : " << color4->a << endl;
    
    //    object->setProperty<string>("label", "hoge");
    //    cout << object->getProperty<string>("label") << endl;
    
    
    //
    //    cout << object->setProperty<float>("x", &x) << endl;
    //    cout << object->setProperty<float>("x", x) << endl;
    //    object->setProperty<float>("x", 100);
    //    cout << object->getProperty<float>("x") << endl;
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
//    //--------------------------------------
//    _count += _speed;
//
//    ofPushMatrix();
//    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
//
//    ofPushMatrix();
//    ofTranslate(_position);
//
//    ofRotateX(_count);
//    ofRotateY(_count * 0.75);
//
//    ofPushStyle();
//    ofNoFill();
//    ofDrawBox(0, 0, 0, 200, 200, 200);
//    ofPopStyle();
//
//    ofPopMatrix();
//
//    ofPopMatrix();
//    //--------------------------------------
    
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

//==============================================================
// Private Event Handler
//==============================================================

//--------------------------------------------------------------
void ofApp::_uiComponentsEventHandler(flEvent& event) {
    ofLog() << "[ofApp]_uiComponentsEventHandler(" << event.type() << ")";
//    ofLog() << "[ofApp]this          = " << this << "," << ((flDisplayObject*) this)->name();
    ofLog() << "[ofApp]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
    ofLog() << "[ofApp]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
   
    //マウスダウンイベント
    if(event.type() == flEvent::CHANGE) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
    }
    
    //マウスダウンイベント
    if(event.type() == flMouseEvent::MOUSE_DOWN) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(button == uiComponents->button001);
        if(button == uiComponents->button002);
        if(button == uiComponents->button003) ofBackground(255, 255, 255, 255);
        if(button == uiComponents->button004) ofBackground(0, 0, 0, 255);
    };
    
    //マウスアップイベント
    if(event.type() == flMouseEvent::MOUSE_UP) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
    };
    
    //コンボボックス
    if(event.type() == flComboBoxEvent::CHANGE) {
        flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
        flComboBox* comboBox = (flComboBox*)(event.currentTarget());
        cout << "-------------" << endl;
        cout << comboBox->name() << " :" << endl;
        cout << "selectedIndex : " << comboBox->selectedIndex() << endl;
        
        if(comboBox == uiComponents->comboBox001) {
            cout << "selectedValue : " << comboBox->selectedValue<string>() << endl;
        }
        if(comboBox == uiComponents->comboBox002) {
            cout << "selectedValue : " << comboBox->selectedValue<float>() << endl;
        }
        if(comboBox == uiComponents->comboBox003) {
            cout << "selectedValue : " << comboBox->selectedValue<flComboBox*>()->name() << endl;
        }
    };
    
    //ラジオボタン
    if(event.type() == flRadioButtonEvent::CHANGE) {
        flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
        flRadioButton* radio = (flRadioButton*)(event.currentTarget());
        
        cout << "-------------" << endl;
        cout << radio->name() << " : " << (radio->selected() ? "true" : "false") << endl;
    }
    
    //ナンバーダイアラー
    if(event.type() == flNumberDialerEvent::CHANGE) {
        flNumberDialerEvent& numberDialerEvent = *(flNumberDialerEvent*) &event;
        flNumberDialer* dialer = (flNumberDialer*)(event.currentTarget());
        
        cout << "-------------" << endl;
        cout << dialer->name() << " : " << dialer->value() << endl;
    }
    
    //2Dパッド
    if(event.type() == flPadEvent::CHANGE) {
        flPadEvent& padEvent = *(flPadEvent*) &event;
        flPad2D* pad = (flPad2D*)(event.currentTarget());
        
        cout << "-------------" << endl;
        cout << pad->name() << " : " << "xRatio:" << pad->xRatio() << " yRatio:" << pad->yRatio() << " x:" << pad->xValue() << " y:" << pad->yValue() << endl;
    }
    
    //スライダー
    if(event.type() == flSliderEvent::CHANGE) {
        flSliderEvent& sliderEvent = *(flSliderEvent*) &event;
        flSlider* slider = (flSlider*)(event.currentTarget());
        
//        if(slider == uiComponents->slider001) {
//            slider->value();
//        };
    }
    
    //レンジスライダー
    if(event.type() == flRangeSliderEvent::CHANGE) {
        flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
        flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
        
//        if(slider == uiComponents->rangeSlider001) {
//            slider->minValue();
//            slider->maxValue();
//        };
    }
    
    //カラースライダー
    if(event.type() == flColorSliderEvent::CHANGE) {
        flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
        flColorSlider* colorSlider = (flColorSlider*)(event.currentTarget());
        
        cout << "-------------" << endl;
        
        //------------------------------------------
        cout << colorSlider->name() << " :" <<
        " R:" << colorSliderEvent.redValue<int>() <<
        " G:" << colorSliderEvent.greenValue<int>() <<
        " B:" << colorSliderEvent.blueValue<int>() << endl;
        cout << colorSlider->name() << " :" <<
        " R:" << colorSliderEvent.redValue<float>() <<
        " G:" << colorSliderEvent.greenValue<float>() <<
        " B:" << colorSliderEvent.blueValue<float>() << endl;
        //------------------------------------------
        
        //------------------------------------------
        //        cout << colorSlider->name() << " :" <<
        //        " R:" << colorSlider->redValue<int>() <<
        //        " G:" << colorSlider->greenValue<int>() <<
        //        " B:" << colorSlider->blueValue<int>() << endl;
        //        cout << colorSlider->name() << " :" <<
        //        " R:" << colorSlider->redValue<float>() <<
        //        " G:" << colorSlider->greenValue<float>() <<
        //        " B:" << colorSlider->blueValue<float>() << endl;
        //------------------------------------------
    }
    
    //カラーピッカー
    if(event.type() == flColorPickerEvent::CHANGE) {
        flColorPickerEvent& colorPickerEvent = *(flColorPickerEvent*) &event;
        flCircleColorPicker* colorPicker = (flCircleColorPicker*)(event.currentTarget());
        
        if(colorPicker == uiComponents->colorPicker001) ofBackground(colorPicker->red(), colorPicker->green(), colorPicker->blue(), 255);
    }
    
    //ジョイスティック1D
    if(event.type() == flJoyStick1Event::CHANGE) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        
        if(joystick == uiComponents->joystick1001) {
//            _position.x = _position.x + joystick->value();
            
            uiComponents->joystick1002->moveLever(joystick->value());
        }
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
void ofApp::keyPressed(int key) {
    if(key == 'c') {
//        _appModel.speed = 0.5;
        _appModel.bgColor = ofColor(255, 124, 30);
    }

    if(key == 'z') {
//        ofLog() << "_appMode.speed = " << _appModel.speed;
//        ofLog() << "_speed = " << _speed;
//        ofLog() << "uiComponents->slider002->value() = " << uiComponents->slider002->value();
    }

    
//    if(key == ('l')) {
//        _enabled = !_enabled;
//        int numChildren = uiComponents->numChildren();
//        for(int i = 0; i < numChildren; i++) {
//            flDisplayObject* displayObject = uiComponents->getChildAt(i);
//
//            ofLog() << "typeid(displayObject) = " << typeid(displayObject).name();
//            ofLog() << "typeid(flButton) = " << typeid(flButton).name();
//            if(typeid(displayObject) == typeid(flButton)) {
//                ofLog() << "displayObject.name = " << displayObject->name();
//                ((flButton*)displayObject)->enabled(_enabled);
//            }
//        }
//    }
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
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}
