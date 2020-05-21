//
//  SubController1.cpp
//  ofApp
//
//  Created by 横田達也 on 2016/06/07.
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
    
    name("SubController1");
    useHandCursor(true);
    
    titleTf->text("[" + title + "]");
    
    _status = "[Status]";
}

//--------------------------------------------------------------
//
SubController1::~SubController1() {
    cout << "[SubController1]~SubController1()" << endl;
    _target = NULL;
    
    _status = "";
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void SubController1::_setup() {
    cout << "[SubController1]_setup()" << endl;
    
    flBasicController::_setup();
    
    _normalBackWidth = 380;
    _normalBackHeight = 130 + 18;
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
    marginTop = 22.5;
    spacing = 65;
    lineSpacing = 22.5;
    
    check001 = new flCheckBox();
    check001->labelText("Lock [l]");
    check001->x(marginLeft + spacing * 0);
    check001->y(marginTop + lineSpacing * 0);
    addChild(check001);
    
    textField = new flTextField();
    textField->text("Index");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 1);
    textField->mouseEnabled(false);
    addChild(textField);
    
    text001 = new flTextField();
    text001->text("");
    text001->autoSize(flTextFieldAutoSize::LEFT);
    text001->x(marginLeft + spacing * 1);
    text001->y(marginTop + lineSpacing * 1);
    text001->mouseEnabled(false);
    addChild(text001);
    
    textField = new flTextField();
    textField->text("Total");
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 2);
    textField->mouseEnabled(false);
    addChild(textField);
    
    text002 = new flTextField();
    text002->text("");
    text002->autoSize(flTextFieldAutoSize::LEFT);
    text002->x(marginLeft + spacing * 1);
    text002->y(marginTop + lineSpacing * 2);
    text002->mouseEnabled(false);
    addChild(text002);
    
//    textField = new flTextField();
//    textField->text("Hoge :");
//    textField->x(marginLeft + spacing * 0);
//    textField->y(marginTop + lineSpacing * 2);
//    textField->mouseEnabled(false);
//    addChild(textField);
    
    text003 = new flTextField();
    text003->text("");
    text003->autoSize(flTextFieldAutoSize::LEFT);
    text003->x(marginLeft + spacing * 0);
    text003->y(marginTop + lineSpacing * 3);
    text003->mouseEnabled(false);
    addChild(text003);
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
    
    //    ofDrawBitmapString(_status, 10, 170);
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
void SubController1::_uiEventHandler(flEvent& event) {
    //    cout << "[NuiController]_uiEventHandler(" << event.type() << endl;
    
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
	else if(event.type() == flNumericDialerEvent::CHANGE) {
        flNumericDialerEvent& numericDialerEvent = *(flNumericDialerEvent*) &event;
        flNumericDialer* dialer = (flNumericDialer*)(event.currentTarget());
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
