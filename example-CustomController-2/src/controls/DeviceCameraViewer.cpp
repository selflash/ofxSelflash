#include "DeviceCameraViewer.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
DeviceCameraViewer::DeviceCameraViewer(string title) {
    cout << "[DeviceCameraViewer]DeviceCameraViewer()" << endl;
    _target = this;
    
    name("DeviceCameraViewer");
    useHandCursor(true);
    
    titleTf->text("[" + title + "]");
    
    _status = "[Status]";
}

//--------------------------------------------------------------
//
DeviceCameraViewer::~DeviceCameraViewer() {
    cout << "[DeviceCameraViewer]~DeviceCameraViewer()" << endl;
    _target = NULL;
    
    _status = "";
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void DeviceCameraViewer::_setup() {
    cout << "[DeviceCameraViewer]_setup()" << endl;
    
    flBasicController::_setup();
    
    _normalBackWidth = 800;
    _normalBackHeight = 195;
    _minBackWidth = _normalBackWidth;
    _backWidth = _normalBackWidth;
    _backHeight = _normalBackHeight;
    
    flGraphics* g;
    g = graphics();
    g->clear();
    g->lineStyle(1, 0xffffff);
    g->beginFill(0x000000, 0.7);
    g->drawRect(0, 0, _backWidth, _backHeight);
    g->endFill();
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    flTextField* textField = NULL;
    //--------------------------------------

    
    //--------------------------------------
    {
        int camWidth = 1280 * 0.2;
        int camHeight = 720 * 0.2;
        flGraphics* g;
        
        int borderWidth = 2;

        //Color Image
        _colorCameraViewer = new flShape();
        _colorCameraViewer->setup();
//    _videoTexture.allocate(camWidth, camHeight, GL_RGBA);
        
        g = _colorCameraViewer->graphics();
        g->clear();
        g->beginFill(0xffffff, 0.8);
        g->drawRect(0, 0, camWidth + borderWidth * 2, camHeight + borderWidth * 2);
        g->beginFill(0x008888, 1.0);
        g->drawRect(borderWidth, borderWidth, camWidth, camHeight);
        g->endFill();
        
        _colorCameraViewer->x(5);
        _colorCameraViewer->y(40);
        addChild(_colorCameraViewer);
        
        //Depth Image
        _depthCameraViewer = new flShape();
        _depthCameraViewer->setup();
        
        g = _depthCameraViewer->graphics();
        g->clear();
        g->beginFill(0xffffff, 0.8);
        g->drawRect(0, 0, camWidth + borderWidth * 2, camHeight + borderWidth * 2);
        g->beginFill(0x008888, 1.0);
        g->drawRect(borderWidth, borderWidth, camWidth, camHeight);
        g->endFill();
        
        _depthCameraViewer->x(5 + borderWidth + camWidth + borderWidth + 5);
        _depthCameraViewer->y(40);
        addChild(_depthCameraViewer);
        
        
        //Ir Image
        _irCameraViewer = new flShape();
        _irCameraViewer->setup();
        
        g = _irCameraViewer->graphics();
        g->clear();
        g->beginFill(0xffffff, 0.8);
        g->drawRect(0, 0, camWidth + borderWidth * 2, camHeight + borderWidth * 2);
        g->beginFill(0x008888, 1.0);
        g->drawRect(borderWidth, borderWidth, camWidth, camHeight);
        g->endFill();
        
        _irCameraViewer->x(5 + borderWidth + camWidth + borderWidth + 5 + borderWidth + camWidth + borderWidth + 5);
        _irCameraViewer->y(40);
        addChild(_irCameraViewer);
        
//        ofLog() << "hoge = " << 5 + borderWidth + camWidth + borderWidth + 5 + borderWidth + camWidth + borderWidth + 5;
        
//        ofLog() << "_irCameraViewer = " << _irCameraViewer->y() + _irCameraViewer->height();
//        ofLog() << "_irCameraViewer.height = " << _irCameraViewer->height();
        ofLog() << "_irCameraViewer = " << _irCameraViewer->y() + (camHeight * 0.2);
    }
}

//--------------------------------------------------------------
//
void DeviceCameraViewer::_update() {
    //cout << "[DeviceCameraViewer]update()" << endl;
}

//--------------------------------------------------------------
//
void DeviceCameraViewer::_draw() {
    //cout << "[DeviceCameraViewer]draw()" << endl;
    
    if(_isMinimize) return;
    
    ofPushStyle();
    ofSetColor(255, 255, 255, 255);
    flFont::drawString("Color", 5, 35);
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(255, 255, 255, 255);
    flFont::drawString("Depth", 174, 35);
    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(255, 255, 255, 255);
    flFont::drawString("Ir", 343, 35);
    ofPopStyle();
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void DeviceCameraViewer::_uiEventHandler(flEvent& event) {
    //    cout << "[DeviceCameraViewer]_uiEventHandler(" << event.type() << endl;
    
    //ボタン(マウスダウン)
    if(event.type() == flButtonEvent::MOUSE_DOWN) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
    }
    
    //コンボボックス
    else if(event.type() == flComboBoxEvent::CHANGE) {
        flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
        flComboBox* comboBox = (flComboBox*)(event.currentTarget());
        cout << "-------------" << endl;
        cout << comboBox->name() << " :" << endl;
        cout << "selectedIndex : " << comboBox->selectedIndex() << endl;
    }
    
    //チェックボックス
	else if(event.type() == flCheckBoxEvent::CHANGE) {
        flCheckBoxEvent& checkBoxEvent = *(flCheckBoxEvent*) &event;
        flCheckBox* checkBox = (flCheckBox*)(event.currentTarget());
    }

    //ラジオボタン
	else if(event.type() == flRadioButtonEvent::CHANGE) {
        flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
        flRadioButton* radio = (flRadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
	else if(event.type() == flNumberDialerEvent::CHANGE) {
        flNumberDialerEvent& numberDialerEvent = *(flNumberDialerEvent*) &event;
        flNumberDialer* dialer = (flNumberDialer*)(event.currentTarget());
    }
    
    //2Dパッド
	else if(event.type() == flPadEvent::CHANGE) {
        flPadEvent& padEvent = *(flPadEvent*) &event;
        flPad2D* pad = (flPad2D*)(event.currentTarget());
    }
    
    //スライダー
	else if(event.type() == flSliderEvent::CHANGE) {
        flSliderEvent& sliderEvent = *(flSliderEvent*) &event;
        flSlider* slider = (flSlider*)(event.currentTarget());
    }
    
    //Vec2スライダー
	else if(event.type() == flVec2SliderEvent::CHANGE) {
        flVec2SliderEvent& sliderEvent = *(flVec2SliderEvent*) &event;
        flVec2Slider* slider = (flVec2Slider*)(event.currentTarget());
    }
    
    //Vec3スライダー
	else if(event.type() == flVec3SliderEvent::CHANGE) {
        flVec3SliderEvent& sliderEvent = *(flVec3SliderEvent*) &event;
        flVec3Slider* slider = (flVec3Slider*)(event.currentTarget());
    }
    
    //レンジスライダー
	else if(event.type() == flRangeSliderEvent::CHANGE) {
        flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
        flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
    }
    
    //カラースライダー
	else if(event.type() == flColorSliderEvent::CHANGE) {
        flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
        flColorSlider* slider = (flColorSlider*)(event.currentTarget());
    }
    
    //ジョイスティック1D
	else if(event.type() == flJoyStick1Event::CHANGE) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    if(event.type() == flJoyStick1Event::UP) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick1Event::DOWN) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick1Event::LEFT) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick1Event::RIGHT) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
    }
    
    //ジョイスティック2D
	else if(event.type() == flJoyStick2Event::CHANGE) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick2Event::UP) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick2Event::DOWN) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick2Event::LEFT) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
	else if(event.type() == flJoyStick2Event::RIGHT) {
        flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
        flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
    }
}
