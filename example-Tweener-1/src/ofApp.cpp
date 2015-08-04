#include "ofApp.h"

//--------------------------------------------------------------
//
void ofApp::setup() {
    ofSetWindowTitle("example-Tweener");
    
    _value1 = 0.0;
    _value2 = 0.0;
    _value3 = 0.0;
    _value4 = 0.0;
    
    //----------------------------------
    //Flashフレームワークの準備
    ofxSelflash::setup(true);
    Stage* stage = ofxSelflash::stage();
    //----------------------------------
    
    //----------------------------------
    //3D空間の用意
    _world = new BasicWorld3D();
    _world->name("World");
    stage->addChild(_world);
    _world->setup();
    //----------------------------------
    
    //----------------------------------
    //3D
    _testObject3d = new Cube3D(100, 100, 100);
    _testObject3d->name("TEST OBJECT 3D");
    _testObject3d->x(120);
    _testObject3d->y(-110);
    _testObject3d->z(0);
    _testObject3d->frontFaceEnabled(true);
    _testObject3d->backFaceEnabled(true);
    _testObject3d->wireframeEnabled(true);
    _testObject3d->lightEnabled(false);
    _testObject3d->vertexColor(ofRandom(0.2, 1.0), ofRandom(0.2, 1.0), ofRandom(0.2, 1.0));
    _world->rootNode()->addChild(_testObject3d);
    //----------------------------------
    
    //----------------------------------
    //2D
    _testObject2d = new Sprite();
    _testObject2d->name("TEST OBJECT 2D");
    _testObject2d->x(600);
    _testObject2d->y(100);
    Graphics* g = _testObject2d->graphics();
    g->clear();
    g->beginFill(0xff0000);
    g->drawRect(0, 0, 150, 150);
    g->endFill();
    _testObject2d->mouseEnabled(false);
    stage->addChild(_testObject2d);
    //----------------------------------

    //--------------------------------------
    //Initialize UI
    uiComponents = new UIComponents();
    uiComponents->setup();
    uiComponents->x(20);
    uiComponents->y(20);
    uiComponents->btn101->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn102->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn103->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn201->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn202->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    uiComponents->btn203->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
    ofxSelflash::stage()->addChild(uiComponents);
    //--------------------------------------
//
//    //--------------------------------------
//    //ÂêÑUI„ÇíÁõ£Ë¶ñ„Åô„Çã
//    //„Çπ„É©„Ç§„ÉÄ„Éº„ÇíÁõ£Ë¶ñ
//    uiComponents->slider001->addEventListener(SliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->slider002->addEventListener(SliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    //„É¨„É≥„Ç∏„Çπ„É©„Ç§„ÉÄ„Éº„ÇíÁõ£Ë¶ñ
//    uiComponents->rangeSlider001->addEventListener(RangeSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->rangeSlider002->addEventListener(RangeSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    //„Ç´„É©„Éº„Çπ„É©„Ç§„ÉÄ„Éº„ÇíÁõ£Ë¶ñ
//    uiComponents->colorSlider001->addEventListener(ColorSliderEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    //„Éú„Çø„É≥„ÇíÁõ£Ë¶ñ
//    uiComponents->btn001->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->btn002->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->btn003->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->btn004->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->btn005->addEventListener(MouseEvent::MOUSE_DOWN, this, &ofApp::_uiComponentsEventHandler);
//    //„É©„Ç∏„Ç™„Éú„Çø„É≥„ÇíÁõ£Ë¶ñ
//    uiComponents->radio001->addEventListener(RadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->radio002->addEventListener(RadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->radio003->addEventListener(RadioButtonEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    //2D„Éë„ÉÉ„Éâ„ÇíÁõ£Ë¶ñ
//    uiComponents->pad001->addEventListener(PadEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->pad002->addEventListener(PadEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    //„Ç´„É©„Éº„Éî„ÉÉ„Ç´„Éº„ÇíÁõ£Ë¶ñ
//    uiComponents->colorPicker001->addEventListener(ColorPickerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    //„Ç∏„Éß„Ç§„Çπ„ÉÜ„Ç£„ÉÉ„ÇØ„ÇíÁõ£Ë¶ñ
//    uiComponents->joystick001->addEventListener(JoystickEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    //„Éä„É≥„Éê„Éº„ÉÄ„Ç§„Ç¢„É©„Éº„ÇíÁõ£Ë¶ñ
//    uiComponents->dialer001->addEventListener(NumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
////    uiComponents->dialer002->addEventListener(NumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
////    uiComponents->dialer003->addEventListener(NumberDialerEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    //„Ç≥„É≥„Éú„Éú„ÉÉ„ÇØ„Çπ„ÇíÁõ£Ë¶ñ
//    uiComponents->comboBox001->addEventListener(ComboBoxEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->comboBox002->addEventListener(ComboBoxEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    uiComponents->comboBox003->addEventListener(ComboBoxEvent::CHANGE, this, &ofApp::_uiComponentsEventHandler);
//    //--------------------------------------
//    
//    
//    _count = 0.0;
//    _speed = 0.1;
//    
//    
//    Object* object = new Object();
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
    
//    object->setProperty<std::string>("label", "hoge");
//    cout << object->getProperty<std::string>("label") << endl;

    
//
//    cout << object->setProperty<float>("x", &x) << endl;
//    cout << object->setProperty<float>("x", x) << endl;
//    object->setProperty<float>("x", 100);
//    cout << object->getProperty<float>("x") << endl;
}

//--------------------------------------------------------------
//
void ofApp::update() {
//    _testObject3d->rotationX(_testObject3d->rotationX() + 0.1);
//    _testObject3d->rotationY(_testObject3d->rotationY() + 0.2);
//    _testObject3d->rotationZ(_testObject3d->rotationZ() + 0.3);
    
}

//--------------------------------------------------------------
//
void ofApp::draw() {
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);

    ofDrawBitmapString(ofToString(_value1), 10, 40);
    ofDrawBitmapString(ofToString(_value2), 10, 60);
    ofDrawBitmapString(ofToString(_value3), 10, 80);
    ofDrawBitmapString(ofToString(_value4), 10, 100);
    
//    //--------------------------------------
//    //„ÉÜ„Çπ„Éà
//    _count += _speed;
//    
//    ofPushMatrix();
//    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
//    ofRotateX(_count);
//    ofRotateY(_count * 0.75);
//    
//    ofPushStyle();
//    ofNoFill();
//    ofDrawBox(0, 0, 0, 200, 200, 200);
//    ofPopStyle();
//    
//    ofPopMatrix();
//    //--------------------------------------
}

//==============================================================
// PROTECTED / PRIVATE
//==============================================================

//--------------------------------------------------------------
//
void ofApp::_playAnimation2d() {
    cout << "[ofApp]_playAnimation2d()" << endl;
    
    _tween1 = STweener::to(
                 _testObject2d,
                 ofToFloat(uiComponents->text101->text()),
                 "delay", ofToFloat(uiComponents->text102->text()),
                 "x", ofToFloat(uiComponents->text103->text()),
                 "y", ofToFloat(uiComponents->text104->text()),
                 "z", ofToFloat(uiComponents->text105->text()),
                 "alpha", ofToFloat(uiComponents->text106->text()),
//                 "width", ofToFloat(uiComponents->text107->text()),
//                 "height", ofToFloat(uiComponents->text108->text()),
//                 "scaleX", ofToFloat(uiComponents->text109->text()),
//                 "scaleY", ofToFloat(uiComponents->text110->text()),
                 "rotation", ofToFloat(uiComponents->text111->text()),
//                 "rotationX", ofToFloat(uiComponents->text112->text()),
//                 "rotationY", ofToFloat(uiComponents->text113->text()),
                 uiComponents->comboBox101->selectedValue<int>()
                 );
    
}
//--------------------------------------------------------------
//
void ofApp::_playAnimation3d() {
    cout << "[ofApp]_playAnimation3d()" << endl;
    
    _tween2 = STweener::to(
                 _testObject3d,
                 ofToFloat(uiComponents->text201->text()),
                 "delay", ofToFloat(uiComponents->text202->text()),
                 "x", ofToFloat(uiComponents->text203->text()),
                 "y", ofToFloat(uiComponents->text204->text()),
                 "z", ofToFloat(uiComponents->text205->text()),
//                 "alpha", ofToFloat(uiComponents->text206->text()),
//                 "width", ofToFloat(uiComponents->text107->text()),
//                 "height", ofToFloat(uiComponents->text108->text()),
//                 "scaleX", ofToFloat(uiComponents->text109->text()),
//                 "scaleY", ofToFloat(uiComponents->text110->text()),
//                 "rotation", ofToFloat(uiComponents->text211->text()),
                 "rotationX", ofToFloat(uiComponents->text211->text()),
                 "rotationY", ofToFloat(uiComponents->text212->text()),
                 "rotationZ", ofToFloat(uiComponents->text213->text()),
                 uiComponents->comboBox201->selectedValue<int>()
                 );
}

//--------------------------------------------------------------
//
void ofApp::_reset2D() {
    cout << "[ofApp]_reset2D()" << endl;
    _testObject2d->x(500);
    _testObject2d->y(100);
    _testObject2d->alpha(1.0);
    _testObject2d->rotation(0.0);
//    _testObject2d->scaleX(1.0);
//    _testObject2d->scaleY(1.0);
//    _testObject2d->width(100);
//    _testObject2d->height(100);
}

//--------------------------------------------------------------
//
void ofApp::_reset3D() {
    cout << "[ofApp]_reset2D()" << endl;
    
    _testObject3d->x(120);
    _testObject3d->y(-110);
    _testObject3d->z(0);
    _testObject3d->rotationX(0);
    _testObject3d->rotationY(0);
    _testObject3d->rotationZ(0);
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void ofApp::_uiComponentsEventHandler(Event& event) {
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
    if(event.type() == MouseEvent::MOUSE_DOWN) {
        MouseEvent& mouseEvent = *(MouseEvent*) &event;
        Button* button = (Button*)(event.currentTarget());
        
        if(button == uiComponents->btn101) _playAnimation2d();
        if(button == uiComponents->btn102) _reset2D();
        if(button == uiComponents->btn103) {
            if(!_tween1) return;
            if(button->selected()) {
                _tween1->pause();
            } else {
                _tween1->resume();
            }
        }
        if(button == uiComponents->btn201) _playAnimation3d();
        if(button == uiComponents->btn202) _reset3D();
        if(button == uiComponents->btn203) {
            if(!_tween2) return;
            if(button->selected()) {
                _tween2->pause();
            } else {
                _tween2->resume();
            }
        }
        
//        if(button == uiComponents->btn003) ofBackground(255, 255, 255, 255);
//        if(button == uiComponents->btn004) ofBackground(120, 120, 120, 255);
//        if(button == uiComponents->btn005) ofBackground(0, 0, 0, 255);
    };
    
    //„Éû„Ç¶„Çπ„Ç¢„ÉÉ„Éó
    if(event.type() == MouseEvent::MOUSE_UP) {
        MouseEvent& mouseEvent = *(MouseEvent*) &event;
        Button* button = (Button*)(event.currentTarget());
    };
    
    //„Ç≥„É≥„Éú„Éú„ÉÉ„ÇØ„Çπ
    if(event.type() == ComboBoxEvent::CHANGE) {
        ComboBoxEvent& comboBoxEvent = *(ComboBoxEvent*) &event;
        ComboBox* comboBox = (ComboBox*)(event.currentTarget());
        cout << "-------------" << endl;
        cout << comboBox->name() << " :" << endl;
        cout << "selectedIndex : " << comboBox->selectedIndex() << endl;
        
//        if(comboBox == uiComponents->comboBox001) {
//            cout << "selectedValue : " << comboBox->selectedValue<std::string>() << endl;
//        }
//        if(comboBox == uiComponents->comboBox002) {
//            cout << "selectedValue : " << comboBox->selectedValue<float>() << endl;
//        }
//        if(comboBox == uiComponents->comboBox003) {
//            cout << "selectedValue : " << comboBox->selectedValue<ComboBox*>()->name() << endl;
//        }
    };
    
    //„É©„Ç∏„Ç™„Éú„Çø„É≥
    if(event.type() == RadioButtonEvent::CHANGE) {
        RadioButtonEvent& radioButtonEvent = *(RadioButtonEvent*) &event;
        RadioButton* radio = (RadioButton*)(event.currentTarget());
        
        cout << "-------------" << endl;
        cout << radio->name() << " : " << (radio->selected() ? "true" : "false") << endl;
    }
    
    //„Éä„É≥„Éê„Éº„ÉÄ„Ç§„Ç¢„É©„Éº
    if(event.type() == NumberDialerEvent::CHANGE) {
        NumberDialerEvent& numberDialerEvent = *(NumberDialerEvent*) &event;
        NumberDialer* dialer = (NumberDialer*)(event.currentTarget());
        
        cout << "-------------" << endl;
        cout << dialer->name() << " : " << dialer->value() << endl;
    }
    
    //2D„Éë„ÉÉ„Éâ
    if(event.type() == PadEvent::CHANGE) {
        PadEvent& padEvent = *(PadEvent*) &event;
        Pad2D* pad = (Pad2D*)(event.currentTarget());
        
        cout << "-------------" << endl;
        cout << pad->name() << " : " << "xRatio:" << pad->xRatio() << " yRatio:" << pad->yRatio() << " x:" << pad->xValue() << " y:" << pad->yValue() << endl;
    }
    
    //„Çπ„É©„Ç§„ÉÄ„Éº
    if(event.type() == SliderEvent::CHANGE) {
        SliderEvent& sliderEvent = *(SliderEvent*) &event;
        Slider* slider = (Slider*)(event.currentTarget());
        
//        if(slider == uiComponents->slider001);
//        if(slider == uiComponents->slider002) _speed = slider->value();
    }
    
    //„É¨„É≥„Ç∏„Çπ„É©„Ç§„ÉÄ„Éº
    if(event.type() == RangeSliderEvent::CHANGE) {
        RangeSliderEvent& rangeSliderEvent = *(RangeSliderEvent*) &event;
        RangeSlider* slider = (RangeSlider*)(event.currentTarget());
    }
    
    //„Ç´„É©„Éº„Çπ„É©„Ç§„ÉÄ„Éº
    if(event.type() == ColorSliderEvent::CHANGE) {
        ColorSliderEvent& colorSliderEvent = *(ColorSliderEvent*) &event;
        ColorSlider* colorSlider = (ColorSlider*)(event.currentTarget());
        
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
    if(event.type() == ColorPickerEvent::CHANGE) {
        ColorPickerEvent& colorPickerEvent = *(ColorPickerEvent*) &event;
        CircleColorPicker* colorPicker = (CircleColorPicker*)(event.currentTarget());
        
//        if(colorPicker == uiComponents->colorPicker001) ofBackground(colorPicker->red(), colorPicker->green(), colorPicker->blue(), 255);
    }
    
    //„Ç∏„Éß„Ç§„Çπ„ÉÜ„Ç£„ÉÉ„ÇØ„Éë„ÉÉ„Éâ
    if(event.type() == JoystickEvent::UP) {
        JoystickEvent& joystickEvent = *(JoystickEvent*) &event;
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    if(event.type() == JoystickEvent::DOWN) {
        JoystickEvent& joystickEvent = *(JoystickEvent*) &event;
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    if(event.type() == JoystickEvent::LEFT) {
        JoystickEvent& joystickEvent = *(JoystickEvent*) &event;
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
    if(event.type() == JoystickEvent::RIGHT) {
        JoystickEvent& joystickEvent = *(JoystickEvent*) &event;
        Joystick* joystick = (Joystick*)(event.currentTarget());
    }
}

//--------------------------------------------------------------
//
void ofApp::keyPressed(int key) {

    if(key == '1') {
        _value1 = 0.0;
        STweener::to(&_value1, 1.0, 3.0, 100.0, EASE_LINEAR);
//        STweener::fromTo(&_value1, 0.0, 1.0, 100.0, EASE_LINEAR);
    }
    
//    if(key == '1') {
//        STweener::delayedCall(1.0f, this, &ofApp::_playAnimation2d);
//
//    }
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
