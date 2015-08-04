#include "Camera3DController.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
Camera3DController::Camera3DController(){
    cout << "[Camera3DController]Camera3DController()" << endl;
    _target = this;
    
    useHandCursor(true);
    
    _status = "[STATUS]";
    _camera = NULL;
    
    _focalNear = 0.0;
    _focalFar = 0.0;
}

//--------------------------------------------------------------
//
Camera3DController::~Camera3DController(){
    cout << "[Camera3DController]~Camera3DController()" << endl;
    _target = NULL;
    
    _status = "";
    _camera = NULL;
    
    _focalNear = 0.0;
    _focalFar = 0.0;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void Camera3DController::_setup() {
    cout << "[Camera3DController]_setup()" << endl;
    
    BasicController::_setup();
    
    _normalBackWidth = 600;
    _normalBackHeight = 400;
    _minBackWidth = _normalBackWidth;
    _backWidth = _normalBackWidth;
    _backHeight = _normalBackHeight;
    
    Graphics* g;
    g = graphics();
    g->clear();
    g->lineStyle(1, 0xffffff);
    g->beginFill(0x000000, 0.7);
    g->drawRect(0, 0, _backWidth, _backHeight);
    g->endFill();
    
    titleTf->text("[CAMERA CONTROLLER]");
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    //--------------------------------------
    //コンボボックス
    marginLeft = 10;
    marginTop = 40;
    spacing = 100;
    lineSpacing = 40;
    
    comboBox001 = new ComboBox();
    comboBox001->label("CAMERA LIST", 0xffffff);
    comboBox001->x(marginLeft + spacing * 0);
    comboBox001->y(marginTop + lineSpacing * 0);
    comboBox001->addItem<int>("MAIN CAMERA", 0);
    comboBox001->addItem("FRONT CAMERA", 1);
    comboBox001->addItem("BACK CAMERA", 2);
    comboBox001->addItem("LEFT CAMERA", 3);
    comboBox001->addItem("RIGHT CAMERA", 4);
    comboBox001->addItem("TOP CAMERA", 5);
    comboBox001->addItem("BOTTOM CAMERA", 6);
    comboBox001->addItem("SUB CAMERA 1", 7);
    comboBox001->addItem("SUB CAMERA 2", 8);
    comboBox001->selectedIndex(1);
    addChild(comboBox001);
    //--------------------------------------
    //--------------------------------------
    //ジョイスティック
    marginLeft = 190;
    marginTop = 40;
    spacing = 100;
    lineSpacing = 100;
    
    joystick001 = new Joystick();
    joystick001->label("MOVE", 0xffffff);
    joystick001->x(marginLeft + spacing * 0);
    joystick001->y(marginTop + lineSpacing * 0);
    joystick001->addEventListener(JoystickEvent::UP, this, &Camera3DController::_uiEventHandler);
    joystick001->addEventListener(JoystickEvent::DOWN, this, &Camera3DController::_uiEventHandler);
    joystick001->addEventListener(JoystickEvent::LEFT, this, &Camera3DController::_uiEventHandler);
    joystick001->addEventListener(JoystickEvent::RIGHT, this, &Camera3DController::_uiEventHandler);
    addChild(joystick001);
    joystick002 = new Joystick();
    joystick002->label("ROTATE", 0xffffff);
    joystick002->x(marginLeft + spacing * 1);
    joystick002->y(marginTop + lineSpacing * 0);
    joystick002->addEventListener(JoystickEvent::UP, this, &Camera3DController::_uiEventHandler);
    joystick002->addEventListener(JoystickEvent::DOWN, this, &Camera3DController::_uiEventHandler);
    joystick002->addEventListener(JoystickEvent::LEFT, this, &Camera3DController::_uiEventHandler);
    joystick002->addEventListener(JoystickEvent::RIGHT, this, &Camera3DController::_uiEventHandler);
    addChild(joystick002);
    joystick003 = new Joystick();
    joystick003->label("X, Y", 0xffffff);
    joystick003->x(marginLeft + spacing * 2);
    joystick003->y(marginTop + lineSpacing * 0);
    joystick003->addEventListener(JoystickEvent::UP, this, &Camera3DController::_uiEventHandler);
    joystick003->addEventListener(JoystickEvent::DOWN, this, &Camera3DController::_uiEventHandler);
    joystick003->addEventListener(JoystickEvent::LEFT, this, &Camera3DController::_uiEventHandler);
    joystick003->addEventListener(JoystickEvent::RIGHT, this, &Camera3DController::_uiEventHandler);
    addChild(joystick003);
    joystick004 = new Joystick();
    joystick004->label("Z", 0xffffff);
    joystick004->x(marginLeft + spacing * 3);
    joystick004->y(marginTop + lineSpacing * 0);
    joystick004->addEventListener(JoystickEvent::UP, this, &Camera3DController::_uiEventHandler);
    joystick004->addEventListener(JoystickEvent::DOWN, this, &Camera3DController::_uiEventHandler);
    joystick004->addEventListener(JoystickEvent::LEFT, this, &Camera3DController::_uiEventHandler);
    joystick004->addEventListener(JoystickEvent::RIGHT, this, &Camera3DController::_uiEventHandler);
    addChild(joystick004);
    //--------------------------------------
    //--------------------------------------
    //スライダー
    marginLeft = 190;
    marginTop = 120;
    spacing = 100;
    lineSpacing = 40;
    
    slider001 = new Slider(200);
    slider001->label("FOV", 0xffffff);
    slider001->min(0, false);
    slider001->max(200, false);
    slider001->value(60, false);
    slider001->x(marginLeft + spacing * 0);
    slider001->y(marginTop + lineSpacing * 0);
    slider001->addEventListener(SliderEvent::CHANGE, this, &Camera3DController::_uiEventHandler);
    addChild(slider001);
    
    rangeSlider002 = new RangeSlider(200);
    rangeSlider002->label("CLIPING", 0xffffff);
    rangeSlider002->min(0.1, false);
    rangeSlider002->max(100000.0, false);
    rangeSlider002->minValue(0.1, false);
    rangeSlider002->maxValue(100000.0, false);
    rangeSlider002->x(marginLeft + spacing * 0);
    rangeSlider002->y(marginTop + lineSpacing * 1);
    rangeSlider002->addEventListener(RangeSliderEvent::CHANGE, this, &Camera3DController::_uiEventHandler);
    addChild(rangeSlider002);
    
    rangeSlider003 = new RangeSlider(200);
    rangeSlider003->label("FOCUL", 0xffffff);
    rangeSlider003->min(0.0, false);
    rangeSlider003->max(1.0, false);
    rangeSlider003->minValue(0.1, false);
    rangeSlider003->maxValue(1.0, false);
    rangeSlider003->x(marginLeft + spacing * 0);
    rangeSlider003->y(marginTop + lineSpacing * 2);
    rangeSlider003->addEventListener(RangeSliderEvent::CHANGE, this, &Camera3DController::_uiEventHandler);
    addChild(rangeSlider003);
    
    slider004 = new Slider(200);
    slider004->label("F-STOP", 0xffffff);
    slider004->min(0.0, false);
//    slider004->max(3.0, false);
    slider004->max(1000.0, false);
    slider004->value(1.0, false);
    slider004->x(marginLeft + spacing * 0);
    slider004->y(marginTop + lineSpacing * 3);
//    slider004->roundEnabled(true);
    slider004->addEventListener(SliderEvent::CHANGE, this, &Camera3DController::_uiEventHandler);
    addChild(slider004);
    //--------------------------------------

    //--------------------------------------
    //ラジオボタン
    marginLeft = 190;
    marginTop = 200;
    spacing = 100;
    lineSpacing = 20;
    
    radio002 = new RadioButton(150);
    radio002->label("AUTO FOCUS");
    radio002->textColor(0xffffff);
    radio002->x(marginLeft + spacing * 0);
    radio002->y(marginTop + lineSpacing * 0);
    radio002->addEventListener(RadioButtonEvent::CHANGE, this, &Camera3DController::_uiEventHandler);
    //addChild(radio002);
    //--------------------------------------
    
    addChild(comboBox001);
}

//--------------------------------------------------------------
//
void Camera3DController::_update() {
    //cout << "[Camera3DController]_update()" << endl;
    
    if(_camera) {
        _status = "NAME----------\n";
        _status += ofToString(_camera->name()) + "\n";
        _status += "LOCAL--------\n";
        _status += "X          : " + ofToString(_camera->x()) + "\n";
        _status += "Y          : " + ofToString(_camera->y()) + "\n";
        _status += "Z          : " + ofToString(_camera->z()) + "\n";
        _status += "ROTATION X : " + ofToString(_camera->rotationX()) + "\n";
        _status += "ROTATION Y : " + ofToString(_camera->rotationY()) + "\n";
        _status += "ROTATION Z : " + ofToString(_camera->rotationZ()) + "\n";
//        _status += "GLOBAL X : " + ofToString(_camera->globalX()) + "\n";
//        _status += "GLOBAL Y : " + ofToString(_camera->globalY()) + "\n";
//        _status += "GLOBAL Z : " + ofToString(_camera->globalZ()) + "\n";
        _status += "FOV  --------\n";
        _status += "FOV        : " + ofToString(_camera->fov()) + "\n";
        _status += "FOCUS      : " + ofToString(_camera->focus()) + "\n";
        _status += "FOCUS--------\n";
        _status += "DISTANCE   : " + ofToString(_camera->focalDistance()) + "\n";
        _status += "LENGTH     : " + ofToString(_camera->focalLength()) + "\n";
        _status += "NEAR       : " + ofToString(_camera->focalNear()) + "\n";
        _status += "FAR        : " + ofToString(_camera->focalFar()) + "\n";
        _status += "CLIP---------\n";
        _status += "NEAR       : " + ofToString(_camera->nearClip()) + "\n";
        _status += "FAR        : " + ofToString(_camera->farClip()) + "\n";
    }
}

//--------------------------------------------------------------
//
void Camera3DController::_draw() {
    //cout << "[Camera3DController]_draw()" << endl;
    
    if(_isMinimize) return;
    
    ofDrawBitmapString(_status, 10, 100);
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//--------------------------------------------------------------
//
CameraObject3D* Camera3DController::camera() { return _camera; }
void Camera3DController::camera(CameraObject3D* value) {
    _camera = value;
    
    fov(_camera->fov());
    nearClip(_camera->nearClip());
    farClip(_camera->farClip());
    focalNear(_camera->focalNear());
    focalFar(_camera->focalFar());
}

//--------------------------------------------------------------
//
const float Camera3DController::fov() { return _fov; }
void Camera3DController::fov(const float& value) {
    _fov = value;
    _camera->fov(_fov);
    slider001->value(_fov, false);
}

//--------------------------------------------------------------
//
const float Camera3DController::nearClip() { return _nearClip; }
void Camera3DController::nearClip(const float& value) {
    _nearClip = value;
    _camera->nearClip(_nearClip);
    rangeSlider002->minValue(_nearClip, false);
}

//--------------------------------------------------------------
//
const float Camera3DController::farClip() { return _farClip; }
void Camera3DController::farClip(const float& value) {
    _farClip = value;
    _camera->farClip(_farClip);
    rangeSlider002->maxValue(_farClip, false);
}

//--------------------------------------------------------------
//
const float Camera3DController::focalNear() { return _focalNear; }
void Camera3DController::focalNear(const float& value) {
    _focalNear = value;
    _camera->focalNear(_focalNear);
    rangeSlider003->minValue(_focalNear, false);
}

//--------------------------------------------------------------
//
const float Camera3DController::focalFar() { return _focalFar; }
void Camera3DController::focalFar(const float& value) {
    _focalFar = value;
    _camera->focalFar(_focalFar);
    rangeSlider003->maxValue(_focalFar, false);
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void Camera3DController::_uiEventHandler(Event& event) {
    //cout << "[Camera3DController]_uiEventHandler(" << event.type() << endl;
    
    //ボタン(マウスアップ)
    if(event.type() == MouseEvent::MOUSE_UP) {
        Button* button = (Button*)(event.currentTarget());
    };
    
    //ラジオボタン
    if(event.type() == RadioButtonEvent::CHANGE) {
        RadioButton* radio = (RadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
    
    //スライダー
    if(event.type() == SliderEvent::CHANGE) {
        Slider* slider = (Slider*)(event.currentTarget());
        if(slider == slider001) fov(slider->value());
        if(slider == slider004) _camera->fstop(slider->value());
    }
    
    //レンジスライダー
    if(event.type() == RangeSliderEvent::CHANGE) {
        RangeSlider* slider = (RangeSlider*)(event.currentTarget());
        if(slider == rangeSlider002) {
            nearClip(slider->minValue());
            farClip(slider->maxValue());
        }
        if(slider == rangeSlider003) {
            focalNear(slider->minValue());
            focalFar(slider->maxValue());
        }
    }
    
    //カラースライダー
    if(event.type() == ColorSliderEvent::CHANGE){
        ColorSlider* slider = (ColorSlider*)(event.currentTarget());
    }
    
    //カラーピッカー
    
    //2Dパッド
    if(event.type() == PadEvent::CHANGE) {
        Pad2D* pad = (Pad2D*)(event.currentTarget());
    }
    
    //ジョイスティック
    if(event.type() == JoystickEvent::UP) {
        Joystick* joystick = (Joystick*)(event.currentTarget());
        if(joystick == joystick001) _camera->dolly(joystick->yValue() * -0.5);
        if(joystick == joystick002) _camera->rotationY(_camera->rotationY() - joystick->yValue());
        if(joystick == joystick003) _camera->y(_camera->y() + joystick->yValue() * 0.5);
        if(joystick == joystick004) _camera->z(_camera->z() + joystick->yValue() * -0.5);
    }
    if(event.type() == JoystickEvent::DOWN) {
        Joystick* joystick = (Joystick*)(event.currentTarget());
        if(joystick == joystick001) _camera->dolly(joystick->yValue() * -1);
        if(joystick == joystick002) _camera->rotationY(_camera->rotationY() - joystick->yValue());
        if(joystick == joystick003) _camera->y(_camera->y() + joystick->yValue() * 0.5);
        if(joystick == joystick004) _camera->z(_camera->z() + joystick->yValue() * -0.5);
    }
    if(event.type() == JoystickEvent::LEFT) {
        Joystick* joystick = (Joystick*)(event.currentTarget());
        //if(joystick == joystick001) _camera->rotationX(_camera->rotationX() + joystick->xValue());
        if(joystick == joystick002) _camera->rotationX(_camera->rotationX() + joystick->xValue());
        if(joystick == joystick003) _camera->x(_camera->x() + joystick->xValue() * 0.5);
    }
    if(event.type() == JoystickEvent::RIGHT) {
        Joystick* joystick = (Joystick*)(event.currentTarget());
        //if(joystick == joystick001) _camera->rotationX(_camera->rotationX() + joystick->xValue());
        if(joystick == joystick002) _camera->rotationX(_camera->rotationX() + joystick->xValue());
        if(joystick == joystick003) _camera->x(_camera->x() + joystick->xValue() * 0.5);
    }
    
    //コンボボックス
    if(event.type() == ComboBoxEvent::CHANGE) {
        ComboBox* comboBox = (ComboBox*)(event.currentTarget());
    };
}
