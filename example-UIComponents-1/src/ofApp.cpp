#include "ofApp.h"

//--------------------------------------------------------------
//
void ofApp::setup() {
    ofBackground(0);
    ofSetWindowTitle("example-UIComponents-1");
    ofDisableAntiAliasing();
    
    //--------------------------------------
    //Ready ofxSelflash
    ofxSelflash::autoUpdate(false);
    ofxSelflash::autoDraw(false);
    ofxSelflash::setup(false);
    //--------------------------------------
    
    //--------------------------------------
    //UIコンポーネント
    uiComponents = new UIComponents();
    uiComponents->setup();
    ofxSelflash::stage()->addChild(uiComponents);
    //--------------------------------------
    
    //--------------------------------------
    //スライダー
    uiComponents->slider001->addEventListener(flSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->slider002->addEventListener(flSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //レンジスライダー
    uiComponents->rangeSlider001->addEventListener(flRangeSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->rangeSlider002->addEventListener(flRangeSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //カラースラーダー
    uiComponents->colorSlider001->addEventListener(flColorSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //ボタン
    uiComponents->btn001->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn002->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn002->addEventListener(flEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn003->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn004->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn005->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    //ラジオボタン
    uiComponents->radio001->addEventListener(flRadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->radio002->addEventListener(flRadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->radio003->addEventListener(flRadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //2Dパッド
    uiComponents->pad001->addEventListener(flPadEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->pad002->addEventListener(flPadEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //カラーピッカー
    uiComponents->colorPicker001->addEventListener(flColorPickerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    
    //ジョイスティック1D
    uiComponents->joystick1D001->addEventListener(flJoystick1DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1D002->addEventListener(flJoystick1DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1D003->addEventListener(flJoystick1DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1D004->addEventListener(flJoystick1DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1D005->addEventListener(flJoystick1DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1D006->addEventListener(flJoystick1DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1D007->addEventListener(flJoystick1DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1D101->addEventListener(flJoystick1DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->joystick1D102->addEventListener(flJoystick1DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //ジョイスティック2D
    uiComponents->joystick2D001->addEventListener(flJoystick2DEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //ナンバーダイアラー
    uiComponents->dialer001->addEventListener(flNumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->dialer002->addEventListener(NumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->dialer003->addEventListener(NumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //コンボボックス
    uiComponents->comboBox001->addEventListener(flComboBoxEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->comboBox002->addEventListener(flComboBoxEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->comboBox003->addEventListener(flComboBoxEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //--------------------------------------
    
    
    _count = 0.0;
    _speed = 0.1;
    
    
    Object* object = new Object();
    float x = 100.5;
    
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
//
void ofApp::update() {
    //----------------------------------
    ofxSelflash::update();
    //----------------------------------
}

//--------------------------------------------------------------
//
void ofApp::draw() {
    //--------------------------------------
    _count += _speed;
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    
    ofPushMatrix();
    ofTranslate(_position);

    ofRotateX(_count);
    ofRotateY(_count * 0.75);
    
    ofPushStyle();
    ofNoFill();
    ofDrawBox(0, 0, 0, 200, 200, 200);
    ofPopStyle();

    ofPopMatrix();

    ofPopMatrix();
    //--------------------------------------
    
    //----------------------------------
    ofxSelflash::draw();
    //----------------------------------

    //--------------------------------------
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 255, 255, 200);
    ofCircle(ofGetMouseX(), ofGetMouseY(), 5);
    ofPopStyle();
    //--------------------------------------
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void ofApp::_uiComponentsEventHandler(flEvent& event) {
    cout << "[ofApp]_uiComponentsEventHandler(" << event.type() << ")" << endl;
    
//    //------------------------------------------
//    //イベントタイプ
//    cout << "event.type          = " << event.type() << endl;
//    //カレントターゲット
//    cout << "event.currentTarget = " << event.currentTarget() << ", " << ((DisplayObject*) event.currentTarget())->name() << endl;
//    //イベントターゲット
//    cout << "event.target        = " << event.target() << ", " << ((DisplayObject*) event.target())->name() << endl;
//    //------------------------------------------
    
    //マウスダウンイベント
    if(event.type() == flEvent::CHANGE) {
        flButton* button = (flButton*)(event.currentTarget());

    }
    
    //マウスダウンイベント
    if(event.type() == flMouseEvent::MOUSE_DOWN) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(button == uiComponents->btn001);
        if(button == uiComponents->btn002);
        if(button == uiComponents->btn003) ofBackground(255, 255, 255, 255);
        if(button == uiComponents->btn004) ofBackground(120, 120, 120, 255);
        if(button == uiComponents->btn005) ofBackground(0, 0, 0, 255);
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
        
        if(slider == uiComponents->slider001);
        if(slider == uiComponents->slider002) _speed = slider->value();
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
    if(event.type() == flJoystick1DEvent::CHANGE) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
        
        if(joystick == uiComponents->joystick1D001) {
            _position.x = _position.x + joystick->value();
            
            uiComponents->joystick1D002->moveLever(joystick->value());
        }
    }
    if(event.type() == flJoystick1DEvent::UP) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::DOWN) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::LEFT) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::RIGHT) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    
    //ジョイスティック2D
    if(event.type() == flJoystick2DEvent::CHANGE) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::UP) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::DOWN) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::LEFT) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::RIGHT) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
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

}

//--------------------------------------------------------------
//
void ofApp::mouseReleased(int x, int y, int button) {

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