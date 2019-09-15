//
//  SubController2.cpp
//  ofApp
//
//  Created by 横田達也 on 2016/06/07.
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
    
    name("SubController2");
    useHandCursor(true);
    
    titleTf->text("[" + title + "]");
    
    _status = "[Status]";
    
    _targetJointName = "";
}

//--------------------------------------------------------------
//
SubController2::~SubController2() {
    cout << "[SubController2]~SubController2()" << endl;
    _target = NULL;
    
    _status = "";
    
    _params.clear();
    _targetJointName = "";
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void SubController2::_setup() {
    cout << "[SubController2]_setup()" << endl;
    
    flBasicController::_setup();
    
    _normalBackWidth = 540;
    _normalBackHeight = 245 + 22.5;
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
    
    text000 = new flTextField();
    text000->text("");
    text000->x(marginLeft + spacing * 0);
    text000->y(marginTop + lineSpacing * 0);
    text000->autoSize(flTextFieldAutoSize::LEFT);
    text000->mouseEnabled(false);
    addChild(text000);
    
    button001 = new flButton(100);
    button001->labelText("Clear");
    button001->x(marginLeft + spacing * 1);
    button001->y(marginTop + lineSpacing * 0);
    button001->addEventListener(flButtonEvent::MOUSE_DOWN, this, &SubController2::_uiEventHandler);
    addChild(button001);
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 5;
    marginTop = 20 + 22.5;
    spacing = 155;
    lineSpacing = 22.5;
    
    textField = new flTextField();
    textField->text("Rotation");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 0);
    textField->autoSize(flTextFieldAutoSize::CENTER);
    textField->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
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
    joystick1001 = new flJoyStick1(150);
    joystick1001->label(textField);
    joystick1001->x(marginLeft + spacing * 0);
    joystick1001->y(marginTop + lineSpacing * 2);
    joystick1001->type(flJoyStick1::VERTICALLY);
    joystick1001->enabled(false);
    joystick1001->addEventListener(flJoyStick1Event::CHANGE, this, &SubController2::_uiEventHandler);
    addChild(joystick1001);
    
    textField = new flTextField();
    textField->text("X");
    textField->x(marginLeft + spacing * 0 + (150 / 3) * 1 - 7 - 5 - 22.5);
    textField->y(marginTop + lineSpacing * 3 + 150 * 0.5 - 22.5 * 0.5);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1002 = new flJoyStick1(150);
    joystick1002->label(textField);
    joystick1002->x(marginLeft + spacing * 0 + (150 / 3) * 1 - 7 - 5);
    joystick1002->y(marginTop + lineSpacing * 3);
    joystick1002->type(flJoyStick1::HORIZONTALLY);
    joystick1002->enabled(false);
    joystick1002->addEventListener(flJoyStick1Event::CHANGE, this, &SubController2::_uiEventHandler);
    addChild(joystick1002);
    
    textField = new flTextField();
    textField->text("Z");
    textField->x(marginLeft + spacing * 0 + (150 / 3) * 2 - 7 + 5 - 22.5);
    textField->y(marginTop + lineSpacing * 3 + 150 * 0.5 - 22.5 * 0.5);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1003 = new flJoyStick1(150);
    joystick1003->label(textField);
    joystick1003->x(marginLeft + spacing * 0 + (150 / 3) * 2 - 7 + 5);
    joystick1003->y(marginTop + lineSpacing * 3);
    joystick1003->type(flJoyStick1::HORIZONTALLY);
    joystick1003->enabled(false);
    joystick1003->addEventListener(flJoyStick1Event::CHANGE, this, &SubController2::_uiEventHandler);
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
    text004 = new flTextField();
    text004->text("W : ");
    text004->x(marginLeft + spacing * 1);
    text004->y(marginTop + lineSpacing * 7);
    text004->autoSize(flTextFieldAutoSize::LEFT);
    text004->mouseEnabled(false);
    addChild(text004);
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 5 + 150 + 5 + 100 + 5;
    marginTop = 20 + 22.5;
    spacing = 155;
    lineSpacing = 22.5;
    
    textField = new flTextField();
    textField->text("Position");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 0);
    textField->autoSize(flTextFieldAutoSize::CENTER);
    textField->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
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
    joystick1101 = new flJoyStick1(150);
    joystick1101->label(textField);
    joystick1101->x(marginLeft + spacing * 0);
    joystick1101->y(marginTop + lineSpacing * 2);
    joystick1101->type(flJoyStick1::VERTICALLY);
    joystick1101->enabled(false);
    joystick1101->addEventListener(flJoyStick1Event::CHANGE, this, &SubController2::_uiEventHandler);
    addChild(joystick1101);
    
    textField = new flTextField();
    textField->text("Y");
    textField->x(marginLeft + spacing * 0 + (150 / 3) * 1 - 7 - 5 - 22.5);
    textField->y(marginTop + lineSpacing * 3 + 150 * 0.5 - 22.5 * 0.5);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1102 = new flJoyStick1(150);
    joystick1102->label(textField);
    joystick1102->x(marginLeft + spacing * 0 + (150 / 3) * 1 - 7 - 5);
    joystick1102->y(marginTop + lineSpacing * 3);
    joystick1102->type(flJoyStick1::HORIZONTALLY);
    joystick1102->enabled(false);
    joystick1102->addEventListener(flJoyStick1Event::CHANGE, this, &SubController2::_uiEventHandler);
    addChild(joystick1102);
    
    textField = new flTextField();
    textField->text("Z");
    textField->x(marginLeft + spacing * 0 + (150 / 3) * 2 - 7 + 5 - 22.5);
    textField->y(marginTop + lineSpacing * 3 + 150 * 0.5 - 22.5 * 0.5);
    textField->mouseEnabled(false);
    addChild(textField);
    joystick1103 = new flJoyStick1(150);
    joystick1103->label(textField);
    joystick1103->x(marginLeft + spacing * 0 + (150 / 3) * 2 - 7 + 5);
    joystick1103->y(marginTop + lineSpacing * 3);
    joystick1103->type(flJoyStick1::HORIZONTALLY);
    joystick1103->enabled(false);
    joystick1103->addEventListener(flJoyStick1Event::CHANGE, this, &SubController2::_uiEventHandler);
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
void SubController2::_update() {
    //cout << "[SubController2]update()" << endl;
}

//--------------------------------------------------------------
//
void SubController2::_draw() {
    //cout << "[SubController2]draw()" << endl;
    
    if(_isMinimize) return;
    
    //    ofDrawBitmapString(_status, 10, 170);
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//--------------------------------------------------------------
//
void SubController2::targetJointName(string value) {
    _targetJointName = value;
    
    bool b = bool(_targetJointName != "");
    joystick1001->enabled(b);
    joystick1002->enabled(b);
    joystick1003->enabled(b);
    
    joystick1101->enabled(b);
    joystick1102->enabled(b);
    joystick1103->enabled(b);
    
    text000->text("Joint Name : " + _targetJointName);
}

//==============================================================
// EVENT HANDLER
//==============================================================

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void SubController2::_uiEventHandler(flEvent& event) {
    //    cout << "[NuiController]_uiEventHandler(" << event.type() << endl;
    
    //ボタン(マウスダウン)
    if(event.type() == flButtonEvent::MOUSE_DOWN) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        flEvent* newEvent = new flEvent("uiEvent");
        newEvent->target(button);
        dispatchEvent(newEvent);
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
        
        flEvent* newEvent = new flEvent("uiEvent");
        newEvent->target(joystick);
        dispatchEvent(newEvent);
    }
	else if(event.type() == flJoyStick1Event::UP) {
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
