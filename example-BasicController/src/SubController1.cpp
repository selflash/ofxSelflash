//
//  SubController1.cpp
//  ofApp
//
//  Created by 横田達也 on 2016/12/15.
//
//

#include "SubController1.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
SubController1::SubController1(string title) {
    cout << "[SubController1]SubController1()" << endl;
    _target = this;
    
    name(title);
    useHandCursor(true);
    
    titleTf->text("[" + title + "]");
}

//--------------------------------------------------------------
//
SubController1::~SubController1() {
    cout << "[SubController1]~SubController1()" << endl;
    _target = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void SubController1::_setup() {
    cout << "[SubController1]_setup()" << endl;
    
    BasicController::_setup();
    
    _normalBackWidth = 540;
    _normalBackHeight = 243;
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
    spacing = 155;
    lineSpacing = 22.5;
    
    textField = new flTextField();
    textField->text("Rotation");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 0);
    textField->autoSize(flTextFieldAutoSize::CENTER);
    textField->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    textField->mouseEnabled(false);
    addChild(textField);
    
    textField = new flTextField();
    textField->text("Y");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 1);
    textField->width(150);
    textField->autoSize(flTextFieldAutoSize::CENTER);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1001 = new flJoystick1(150);
    joystick1001->label(textField);
    joystick1001->x(marginLeft + spacing * 0);
    joystick1001->y(marginTop + lineSpacing * 2);
    joystick1001->type(flJoystick1::VERTICALLY);
//    joystick1001->enabled(false);
    joystick1001->addEventListener(flJoystick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    addChild(joystick1001);
    
    textField = new flTextField();
    textField->text("X");
    textField->x(marginLeft + spacing * 0 + (150 / 3) * 1 - 7 - 5 - 22.5);
    textField->y(marginTop + lineSpacing * 3 + 150 * 0.5 - 22.5 * 0.5);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1002 = new flJoystick1(150);
    joystick1002->label(textField);
    joystick1002->x(marginLeft + spacing * 0 + (150 / 3) * 1 - 7 - 5);
    joystick1002->y(marginTop + lineSpacing * 3);
    joystick1002->type(flJoystick1::HORIZONTALLY);
//    joystick1002->enabled(false);
    joystick1002->addEventListener(flJoystick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    addChild(joystick1002);
    
    textField = new flTextField();
    textField->text("Z");
    textField->x(marginLeft + spacing * 0 + (150 / 3) * 2 - 7 + 5 - 22.5);
    textField->y(marginTop + lineSpacing * 3 + 150 * 0.5 - 22.5 * 0.5);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1003 = new flJoystick1(150);
    joystick1003->label(textField);
    joystick1003->x(marginLeft + spacing * 0 + (150 / 3) * 2 - 7 + 5);
    joystick1003->y(marginTop + lineSpacing * 3);
    joystick1003->type(flJoystick1::HORIZONTALLY);
//    joystick1003->enabled(false);
    joystick1003->addEventListener(flJoystick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    addChild(joystick1003);
    
    text001 = new flTextField();
    text001->text("X : ");
    text001->x(marginLeft + spacing * 1);
    text001->y(marginTop + lineSpacing * 4);
    text001->autoSize(flTextFieldAutoSize::LEFT);
    text001->mouseEnabled(false);
    addChild(text001);
    text002 = new flTextField();
    text002->text("Y : ");
    text002->x(marginLeft + spacing * 1);
    text002->y(marginTop + lineSpacing * 5);
    text002->autoSize(flTextFieldAutoSize::LEFT);
    text002->mouseEnabled(false);
    addChild(text002);
    text003 = new flTextField();
    text003->text("Z : ");
    text003->x(marginLeft + spacing * 1);
    text003->y(marginTop + lineSpacing * 6);
    text003->autoSize(flTextFieldAutoSize::LEFT);
    text003->mouseEnabled(false);
    addChild(text003);
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 5 + 150 + 5 + 100 + 5;
    marginTop = 20;
    spacing = 155;
    lineSpacing = 22.5;

    textField = new flTextField();
    textField->text("Position");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 0);
    textField->autoSize(flTextFieldAutoSize::CENTER);
    textField->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    textField->mouseEnabled(false);
    addChild(textField);
    
    textField = new flTextField();
    textField->text("X");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 1);
    textField->width(150);
    textField->autoSize(flTextFieldAutoSize::CENTER);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1101 = new flJoystick1(150);
    joystick1101->label(textField);
    joystick1101->x(marginLeft + spacing * 0);
    joystick1101->y(marginTop + lineSpacing * 2);
    joystick1101->type(flJoystick1::VERTICALLY);
//    joystick1101->enabled(false);
    joystick1101->addEventListener(flJoystick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    addChild(joystick1101);
    
    textField = new flTextField();
    textField->text("Y");
    textField->x(marginLeft + spacing * 0 + (150 / 3) * 1 - 7 - 5 - 22.5);
    textField->y(marginTop + lineSpacing * 3 + 150 * 0.5 - 22.5 * 0.5);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1102 = new flJoystick1(150);
    joystick1102->label(textField);
    joystick1102->x(marginLeft + spacing * 0 + (150 / 3) * 1 - 7 - 5);
    joystick1102->y(marginTop + lineSpacing * 3);
    joystick1102->type(flJoystick1::HORIZONTALLY);
//    joystick1102->enabled(false);
    joystick1102->addEventListener(flJoystick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    addChild(joystick1102);
    
    textField = new flTextField();
    textField->text("Z");
    textField->x(marginLeft + spacing * 0 + (150 / 3) * 2 - 7 + 5 - 22.5);
    textField->y(marginTop + lineSpacing * 3 + 150 * 0.5 - 22.5 * 0.5);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1103 = new flJoystick1(150);
    joystick1103->label(textField);
    joystick1103->x(marginLeft + spacing * 0 + (150 / 3) * 2 - 7 + 5);
    joystick1103->y(marginTop + lineSpacing * 3);
    joystick1103->type(flJoystick1::HORIZONTALLY);
//    joystick1103->enabled(false);
    joystick1103->addEventListener(flJoystick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    addChild(joystick1103);
    
    text101 = new flTextField();
    text101->text("X : ");
    text101->x(marginLeft + spacing * 1);
    text101->y(marginTop + lineSpacing * 4);
    text101->autoSize(flTextFieldAutoSize::LEFT);
    text101->mouseEnabled(false);
    addChild(text101);
    text102 = new flTextField();
    text102->text("Y : ");
    text102->x(marginLeft + spacing * 1);
    text102->y(marginTop + lineSpacing * 5);
    text102->autoSize(flTextFieldAutoSize::LEFT);
    text102->mouseEnabled(false);
    addChild(text102);
    text103 = new flTextField();
    text103->text("Z : ");
    text103->x(marginLeft + spacing * 1);
    text103->y(marginTop + lineSpacing * 6);
    text103->autoSize(flTextFieldAutoSize::LEFT);
    text103->mouseEnabled(false);
    addChild(text103);
    //--------------------------------------
}

//--------------------------------------------------------------
//
void SubController1::_update() {
    //cout << "[SubController1]update()" << endl;
}

//--------------------------------------------------------------
//
void SubController1::_draw() {
    //cout << "[SubController1]draw()" << endl;
    
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
void SubController1::_uiEventHandler(flEvent& event) {
//    cout << "[SubController1]_uiEventHandler(" << event.type() << endl;
    
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
