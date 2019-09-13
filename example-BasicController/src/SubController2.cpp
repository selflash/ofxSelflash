//
//  SubController2.cpp
//  ofApp
//
//  Created by 横田達也 on 2016/12/15.
//
//

#include "SubController2.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
SubController2::SubController2(string title) {
    cout << "[SubController2]SubController2()" << endl;
    _target = this;
    
    name(title);
    useHandCursor(true);
    
    titleTf->text("[" + title + "]");
}

//--------------------------------------------------------------
//
SubController2::~SubController2() {
    cout << "[SubController2]~SubController2()" << endl;
    _target = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void SubController2::_setup() {
    cout << "[SubController2]_setup()" << endl;
    
    BasicController::_setup();
    
    _normalBackWidth = 400;
    _normalBackHeight = 105;
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
    marginLeft = 5;
    marginTop = 20;
    spacing = 205;
    lineSpacing = 22.5;
    
    textField = new flTextField();
    textField->text("Box Color");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 0);
    textField->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    textField->mouseEnabled(false);
    addChild(textField);
    colorSlider001 = new flColorSlider(185, false);
    colorSlider001->label(textField);
//    colorSlider001->label()->width(200);
//    colorSlider001->label()->autoSize(flTextFieldAutoSize::CENTER);
    colorSlider001->x(marginLeft + spacing * 0);
    colorSlider001->y(marginTop + lineSpacing * 1);
    colorSlider001->redValue<float>(1.0);
    colorSlider001->greenValue<float>(1.0);
    colorSlider001->blueValue<float>(1.0);
//    colorSlider001->addEventListener(flColorSliderEvent::CHANGE, this, &SubController2::_uiEventHandler);
    addChild(colorSlider001);
    
    //スライダー
    textField = new flTextField();
    textField->text("Line Width");
    textField->x(marginLeft + spacing * 1);
    textField->y(marginTop + lineSpacing * 0);
    textField->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    textField->mouseEnabled(false);
    addChild(textField);
    slider001 = new flSlider(185, 1, 20, 1);
    slider001->x(marginLeft + spacing * 1);
    slider001->y(marginTop + lineSpacing * 1);
//    slider001->addEventListener(flSliderEvent::CHANGE, this, &SubController2::_uiEventHandler);
    addChild(slider001);
    
    check001 = new flCheckBox();
    check001->labelText("Fill Enabled");
    check001->x(marginLeft + spacing * 1);
    check001->y(marginTop + lineSpacing * 2 + 10);
//    check001->selected(true);
//    check001->enabled(false);
//    check001->addEventListener(flRadioButtonEvent::CHANGE, this, &SubController2::_uiEventHandler);
    addChild(check001);
    //--------------------------------------
}

//--------------------------------------------------------------
//
void SubController2::_update() {
    //cout << "[SubController2]update()" << endl;
}

//--------------------------------------------------------------
//
void SubController2::_draw() {
    //cout << "[SubController2]draw()" << endl;
    
    if(_isMinimize) return;
    
    //Draw Anything
//    ofDrawBitmapString(_status, 10, 170);
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void SubController2::_uiEventHandler(flEvent& event) {
//    cout << "[SubController2]_uiEventHandler(" << event.type() << endl;
    
    //ボタン(マウスダウン)
    if(event.type() == flButtonEvent::MOUSE_DOWN) {
        flButtonEvent& mouseEvent = *(flButtonEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
    }
    //ボタン(チェンジ)
    if(event.type() == flButtonEvent::CHANGE) {
        flButtonEvent& mouseEvent = *(flButtonEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
    }
    
    //コンボボックス
    if(event.type() == flComboBoxEvent::CHANGE) {
        flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
        flComboBox* comboBox = (flComboBox*)(event.currentTarget());
    };
    
    //チェックボックス
    if(event.type() == flCheckBoxEvent::CHANGE) {
        flCheckBoxEvent& checkBoxEvent = *(flCheckBoxEvent*) &event;
        flCheckBox* checkBox = (flCheckBox*)(event.currentTarget());
    }

    //ラジオボタン
    if(event.type() == flRadioButtonEvent::CHANGE) {
        flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
        flRadioButton* radio = (flRadioButton*)(event.currentTarget());
    }
    
    //ナンバーダイアラー
    if(event.type() == flNumberDialerEvent::CHANGE) {
        flNumberDialerEvent& numberDialerEvent = *(flNumberDialerEvent*) &event;
        flNumberDialer* dialer = (flNumberDialer*)(event.currentTarget());
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
    
    //Vec2スライダー
    if(event.type() == flVec2SliderEvent::CHANGE) {
        flVec2SliderEvent& sliderEvent = *(flVec2SliderEvent*) &event;
        flVec2Slider* slider = (flVec2Slider*)(event.currentTarget());
    }
    
    //Vec3スライダー
    if(event.type() == flVec3SliderEvent::CHANGE) {
        flVec3SliderEvent& sliderEvent = *(flVec3SliderEvent*) &event;
        flVec3Slider* slider = (flVec3Slider*)(event.currentTarget());
    }
    
    //レンジスライダー
    if(event.type() == flRangeSliderEvent::CHANGE) {
        flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
        flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
    }
    
    //カラースライダー
    if(event.type() == flColorSliderEvent::CHANGE) {
        flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
        flColorSlider* slider = (flColorSlider*)(event.currentTarget());
    }
    
    //ジョイスティック1D
    if(event.type() == flJoystick1Event::CHANGE) {
        flJoystick1Event& joystickEvent = *(flJoystick1Event*) &event;
        flJoystick1* joystick = (flJoystick1*)(event.currentTarget());
        
        flEvent* newEvent = new flEvent("uiEvent");
        newEvent->target(joystick);
        dispatchEvent(newEvent);
    }
    if(event.type() == flJoystick1Event::UP) {
        flJoystick1Event& joystickEvent = *(flJoystick1Event*) &event;
        flJoystick1* joystick = (flJoystick1*)(event.currentTarget());
    }
    if(event.type() == flJoystick1Event::DOWN) {
        flJoystick1Event& joystickEvent = *(flJoystick1Event*) &event;
        flJoystick1* joystick = (flJoystick1*)(event.currentTarget());
    }
    if(event.type() == flJoystick1Event::LEFT) {
        flJoystick1Event& joystickEvent = *(flJoystick1Event*) &event;
        flJoystick1* joystick = (flJoystick1*)(event.currentTarget());
    }
    if(event.type() == flJoystick1Event::RIGHT) {
        flJoystick1Event& joystickEvent = *(flJoystick1Event*) &event;
        flJoystick1* joystick = (flJoystick1*)(event.currentTarget());
    }
    
    //ジョイスティック2D
    if(event.type() == flJoystick2Event::CHANGE) {
        flJoystick2Event& joystickEvent = *(flJoystick2Event*) &event;
        flJoystick2* joystick = (flJoystick2*)(event.currentTarget());
    }
    if(event.type() == flJoystick2Event::UP) {
        flJoystick2Event& joystickEvent = *(flJoystick2Event*) &event;
        flJoystick2* joystick = (flJoystick2*)(event.currentTarget());
    }
    if(event.type() == flJoystick2Event::DOWN) {
        flJoystick2Event& joystickEvent = *(flJoystick2Event*) &event;
        flJoystick2* joystick = (flJoystick2*)(event.currentTarget());
    }
    if(event.type() == flJoystick2Event::LEFT) {
        flJoystick2Event& joystickEvent = *(flJoystick2Event*) &event;
        flJoystick2* joystick = (flJoystick2*)(event.currentTarget());
    }
    if(event.type() == flJoystick2Event::RIGHT) {
        flJoystick2Event& joystickEvent = *(flJoystick2Event*) &event;
        flJoystick2* joystick = (flJoystick2*)(event.currentTarget());
    }
}
