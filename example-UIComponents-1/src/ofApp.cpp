#include "ofApp.h"

//--------------------------------------------------------------
//
void ofApp::setup() {
    ofSetWindowTitle("example-UIComponents-1");
    
    ofxSelflash::setup();
    
    //--------------------------------------
    //UI„Ç≥„É≥„Éù„Éº„Éç„É≥„Éà„ÅÆÁîüÊàê„Å®„Çπ„ÉÜ„Éº„Ç∏„Å´ÈÖçÁΩÆ
    uiComponents = new UIComponents();
    uiComponents->setup();
    ofxSelflash::stage()->addChild(uiComponents);
    //--------------------------------------
    
    //--------------------------------------
    //ÂêÑUI„ÇíÁõ£Ë¶ñ„Åô„Çã
    //„Çπ„É©„Ç§„ÉÄ„Éº„ÇíÁõ£Ë¶ñ
    uiComponents->slider001->addEventListener(flSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->slider002->addEventListener(flSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //„É¨„É≥„Ç∏„Çπ„É©„Ç§„ÉÄ„Éº„ÇíÁõ£Ë¶ñ
    uiComponents->rangeSlider001->addEventListener(flRangeSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->rangeSlider002->addEventListener(flRangeSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //„Ç´„É©„Éº„Çπ„É©„Ç§„ÉÄ„Éº„ÇíÁõ£Ë¶ñ
    uiComponents->colorSlider001->addEventListener(flColorSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //„Éú„Çø„É≥„ÇíÁõ£Ë¶ñ
    uiComponents->btn001->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn002->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn003->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn004->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn005->addEventListener(flMouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    //„É©„Ç∏„Ç™„Éú„Çø„É≥„ÇíÁõ£Ë¶ñ
    uiComponents->radio001->addEventListener(flRadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->radio002->addEventListener(flRadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->radio003->addEventListener(flRadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //2D„Éë„ÉÉ„Éâ„ÇíÁõ£Ë¶ñ
    uiComponents->pad001->addEventListener(flPadEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->pad002->addEventListener(flPadEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //„Ç´„É©„Éº„Éî„ÉÉ„Ç´„Éº„ÇíÁõ£Ë¶ñ
    uiComponents->colorPicker001->addEventListener(flColorPickerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //„Ç∏„Éß„Ç§„Çπ„ÉÜ„Ç£„ÉÉ„ÇØ„ÇíÁõ£Ë¶ñ
    uiComponents->joystick001->addEventListener(flJoystickEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //„Éä„É≥„Éê„Éº„ÉÄ„Ç§„Ç¢„É©„Éº„ÇíÁõ£Ë¶ñ
    uiComponents->dialer001->addEventListener(flNumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->dialer002->addEventListener(NumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->dialer003->addEventListener(NumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
    //„Ç≥„É≥„Éú„Éú„ÉÉ„ÇØ„Çπ„ÇíÁõ£Ë¶ñ
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
    
}

//--------------------------------------------------------------
//
void ofApp::draw() {
    //--------------------------------------
    //„ÉÜ„Çπ„Éà
    _count += _speed;
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    ofRotateX(_count);
    ofRotateY(_count * 0.75);
    
    ofPushStyle();
    ofNoFill();
    ofDrawBox(0, 0, 0, 200, 200, 200);
    ofPopStyle();
    
    ofPopMatrix();
    //--------------------------------------
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void ofApp::_uiComponentsEventHandler(flEvent& event) {
//    cout << "[ofApp]_uiComponentsEventHandler(" << event.type() << ")" << endl;
    
//    //------------------------------------------
//    //„Ç§„Éô„É≥„Éà„Çø„Ç§„Éó„ÇíÂá∫Âäõ
//    cout << "event.type          = " << event.type() << endl;
//    //„Ç´„É¨„É≥„Éà„Çø„Éº„Ç≤„ÉÉ„Éà„ÅÆ„Ç¢„Éâ„É¨„Çπ„Å®name„Éó„É≠„Éë„ÉÜ„Ç£„ÇíÂá∫Âäõ
//    cout << "event.currentTarget = " << event.currentTarget() << ", " << ((DisplayObject*) event.currentTarget())->name() << endl;
//    //„Çø„Éº„Ç≤„ÉÉ„Éà„ÅÆ„Ç¢„Éâ„É¨„Çπ„Å®name„Éó„É≠„Éë„ÉÜ„Ç£„ÇíÂá∫Âäõ
//    cout << "event.target        = " << event.target() << ", " << ((DisplayObject*) event.target())->name() << endl;
//    //------------------------------------------
    
    //„Éû„Ç¶„Çπ„ÉÄ„Ç¶„É≥
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
        //„Ç§„Éô„É≥„Éà„Åã„ÇâÂÄ§„ÇíÂèñÂæó(intÂûã)
        cout << colorSlider->name() << " :" <<
        " R:" << colorSliderEvent.redValue<int>() <<
        " G:" << colorSliderEvent.greenValue<int>() <<
        " B:" << colorSliderEvent.blueValue<int>() << endl;
        //„Ç§„Éô„É≥„Éà„Åã„ÇâÂÄ§„ÇíÂèñÂæó(floatÂûã)
        cout << colorSlider->name() << " :" <<
        " R:" << colorSliderEvent.redValue<float>() <<
        " G:" << colorSliderEvent.greenValue<float>() <<
        " B:" << colorSliderEvent.blueValue<float>() << endl;
        //------------------------------------------
        
        //------------------------------------------
//        //„Ç´„É¨„É≥„Éà„Çø„Éº„Ç≤„ÉÉ„Éà„Åã„ÇâÂÄ§„ÇíÂèñÂæó(intÂûã)
//        cout << colorSlider->name() << " :" <<
//        " R:" << colorSlider->redValue<int>() <<
//        " G:" << colorSlider->greenValue<int>() <<
//        " B:" << colorSlider->blueValue<int>() << endl;
//        //„Ç´„É¨„É≥„Éà„Çø„Éº„Ç≤„ÉÉ„Éà„Åã„ÇâÂÄ§„ÇíÂèñÂæó(floatÂûã)
//        cout << colorSlider->name() << " :" <<
//        " R:" << colorSlider->redValue<float>() <<
//        " G:" << colorSlider->greenValue<float>() <<
//        " B:" << colorSlider->blueValue<float>() << endl;
        //------------------------------------------
    }
    
    //„Ç´„É©„Éº„Éî„ÉÉ„Ç´„Éº
    if(event.type() == flColorPickerEvent::CHANGE) {
        flColorPickerEvent& colorPickerEvent = *(flColorPickerEvent*) &event;
        flCircleColorPicker* colorPicker = (flCircleColorPicker*)(event.currentTarget());
        
        if(colorPicker == uiComponents->colorPicker001) ofBackground(colorPicker->red(), colorPicker->green(), colorPicker->blue(), 255);
    }
    
    //„Ç∏„Éß„Ç§„Çπ„ÉÜ„Ç£„ÉÉ„ÇØ„Éë„ÉÉ„Éâ
    if(event.type() == flJoystickEvent::UP) {
        flJoystickEvent& joystickEvent = *(flJoystickEvent*) &event;
        flJoystick* joystick = (flJoystick*)(event.currentTarget());
    }
    if(event.type() == flJoystickEvent::DOWN) {
        flJoystickEvent& joystickEvent = *(flJoystickEvent*) &event;
        flJoystick* joystick = (flJoystick*)(event.currentTarget());
    }
    if(event.type() == flJoystickEvent::LEFT) {
        flJoystickEvent& joystickEvent = *(flJoystickEvent*) &event;
        flJoystick* joystick = (flJoystick*)(event.currentTarget());
    }
    if(event.type() == flJoystickEvent::RIGHT) {
        flJoystickEvent& joystickEvent = *(flJoystickEvent*) &event;
        flJoystick* joystick = (flJoystick*)(event.currentTarget());
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
