//
//  SubController1.cpp
//  ofApp
//
//  Created by 横田達也 on 2016/12/15.
//
//

#include "SubController1.h"

//==============================================================
// Constructor / Deconstructor
//==============================================================

//--------------------------------------------------------------
SubController1::SubController1(string title) {
    ofLog() << "[SubController1]SubController1()";
    _target = this;
    
    name(title);
    useHandCursor(true);
    
	_titleText = "[" + title + "]";
}

//--------------------------------------------------------------
SubController1::~SubController1() {
    ofLog() << "[SubController1]~SubController1()";

    _target = NULL;
}

//==============================================================
// Setup / Update / Draw
//==============================================================

//--------------------------------------------------------------
void SubController1::_setup() {
    ofLog() << "[SubController1]_setup()";
    
	//--------------------------------------
	_normalGraphics.clear();
	_normalGraphics.lineStyle(1, 0xffffff);
	_normalGraphics.beginFill(0x000000, 0.7);
	//--------------------------------------

	//--------------------------------------
	int x, y, w, h = 0;
	flDisplayObject* displayObject = NULL;
	flTextField* label = NULL;
	flRadioButtonGroup* radioButtonGroup = NULL;
	//--------------------------------------
    
    //--------------------------------------
	x = _marginLeft;
	y = _marginTop + _lineSpacing * 0;
    label = new flTextField();
    label->text("Rotation");
    label->autoSize(flTextFieldAutoSize::CENTER);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    displayObject = addChild(label, x, y);
    
    label = new flTextField();
    label->text("Y");
    label->x(_marginLeft + _spacing * 0);
    label->y(_marginTop + _lineSpacing * 1);
    label->width(100);
    label->autoSize(flTextFieldAutoSize::CENTER);
    label->mouseEnabled(false);
    displayObject = addChild(label);
    joystick1001 = new flJoyStick1();
    joystick1001->label(label);
    joystick1001->x(_marginLeft + _spacing * 0);
    joystick1001->y(_marginTop + _lineSpacing * 2);
    joystick1001->type(flJoyStick1::HORIZONTALLY);
    //    joystick1001->enabled(false);
    joystick1001->addEventListener(flJoyStick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    displayObject = addChild(joystick1001);
    
    label = new flTextField();
    label->text("X");
    label->x(_marginLeft + _spacing * 0 + (100 / 3) * 1 - 7 - 5 - 22);
    label->y(_marginTop + _lineSpacing * 3 + 100 * 0.5 - 22 * 0.5);
    label->mouseEnabled(false);
    displayObject = addChild(label);
    joystick1002 = new flJoyStick1();
    joystick1002->label(label);
    joystick1002->x(_marginLeft + _spacing * 0 + (100 / 3) * 1 - 7 - 5);
    joystick1002->y(_marginTop + _lineSpacing * 3);
    joystick1002->type(flJoyStick1::VERTICALLY);
    //    joystick1002->enabled(false);
    joystick1002->addEventListener(flJoyStick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    displayObject = addChild(joystick1002);
    
    label = new flTextField();
    label->text("Z");
    label->x(_marginLeft + _spacing * 0 + (100 / 3) * 2 - 7 + 5 - 22);
    label->y(_marginTop + _lineSpacing * 3 + 100 * 0.5 - 22 * 0.5);
    label->mouseEnabled(false);
    displayObject = addChild(label);
    joystick1003 = new flJoyStick1();
    joystick1003->label(label);
    joystick1003->x(_marginLeft + _spacing * 0 + (100 / 3) * 2 - 7 + 5);
    joystick1003->y(_marginTop + _lineSpacing * 3);
    joystick1003->type(flJoyStick1::VERTICALLY);
    //    joystick1003->enabled(false);
    joystick1003->addEventListener(flJoyStick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    displayObject = addChild(joystick1003);
    
    text001 = new flTextField();
    text001->text("X : ");
    text001->x(_marginLeft + _spacing * 1);
    text001->y(_marginTop + _lineSpacing * 4);
    text001->autoSize(flTextFieldAutoSize::LEFT);
    text001->mouseEnabled(false);
    displayObject = addChild(text001);
    text002 = new flTextField();
    text002->text("Y : ");
    text002->x(_marginLeft + _spacing * 1);
    text002->y(_marginTop + _lineSpacing * 5);
    text002->autoSize(flTextFieldAutoSize::LEFT);
    text002->mouseEnabled(false);
    displayObject = addChild(text002);
    text003 = new flTextField();
    text003->text("Z : ");
    text003->x(_marginLeft + _spacing * 1);
    text003->y(_marginTop + _lineSpacing * 6);
    text003->autoSize(flTextFieldAutoSize::LEFT);
    text003->mouseEnabled(false);
    displayObject = addChild(text003);
    //--------------------------------------
    
    //--------------------------------------
	x = _marginLeft + _margin + 100 + _margin;
	y = _marginTop + _lineSpacing * 0;
    label = new flTextField();
    label->text("Position");
    label->autoSize(flTextFieldAutoSize::CENTER);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
    displayObject = addChild(label, x, y);
    
    label = new flTextField();
    label->text("X");
    label->x(_marginLeft + _spacing * 1);
    label->y(_marginTop + _lineSpacing * 1);
    label->width(100);
    label->autoSize(flTextFieldAutoSize::CENTER);
    label->mouseEnabled(false);
    displayObject = addChild(label);
    joystick1101 = new flJoyStick1();
    joystick1101->label(label);
    joystick1101->x(_marginLeft + _spacing * 1);
    joystick1101->y(_marginTop + _lineSpacing * 2);
    joystick1101->type(flJoyStick1::HORIZONTALLY);
    //    joystick1101->enabled(false);
    joystick1101->addEventListener(flJoyStick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    displayObject = addChild(joystick1101);
    
    label = new flTextField();
    label->text("Y");
    label->x(_marginLeft + _spacing * 0 + (100 / 3) * 1 - 7 - 5 - 22);
    label->y(_marginTop + _lineSpacing * 3 + 100 * 0.5 - 22 * 0.5);
    label->mouseEnabled(false);
    displayObject = addChild(label);
    joystick1102 = new flJoyStick1();
    joystick1102->label(label);
    joystick1102->x(_marginLeft + _spacing * 1 + (100 / 3) * 1 - 7 - 5);
    joystick1102->y(_marginTop + _lineSpacing * 3);
    joystick1102->type(flJoyStick1::VERTICALLY);
    //    joystick1102->enabled(false);
    joystick1102->addEventListener(flJoyStick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    displayObject = addChild(joystick1102);
    
    label = new flTextField();
    label->text("Z");
    label->x(_marginLeft + _spacing * 1 + (100 / 3) * 2 - 7 + 5 - 22);
    label->y(_marginTop + _lineSpacing * 3 + 100 * 0.5 - 22 * 0.5);
    label->mouseEnabled(false);
    displayObject = addChild(label);
    joystick1103 = new flJoyStick1();
    joystick1103->label(label);
    joystick1103->x(_marginLeft + _spacing * 1 + (150 / 3) * 2 - 7 + 5);
    joystick1103->y(_marginTop + _lineSpacing * 3);
    joystick1103->type(flJoyStick1::VERTICALLY);
    //    joystick1103->enabled(false);
    joystick1103->addEventListener(flJoyStick1Event::CHANGE, this, &SubController1::_uiEventHandler);
    displayObject = addChild(joystick1103);
    
    text101 = new flTextField();
    text101->text("X : ");
    text101->x(_marginLeft + _spacing * 1);
    text101->y(_marginTop + _lineSpacing * 4);
    text101->autoSize(flTextFieldAutoSize::LEFT);
    text101->mouseEnabled(false);
    displayObject = addChild(text101);
    text102 = new flTextField();
    text102->text("Y : ");
    text102->x(_marginLeft + _spacing * 1);
    text102->y(_marginTop + _lineSpacing * 5);
    text102->autoSize(flTextFieldAutoSize::LEFT);
    text102->mouseEnabled(false);
    displayObject = addChild(text102);
    text103 = new flTextField();
    text103->text("Z : ");
    text103->x(_marginLeft + _spacing * 1);
    text103->y(_marginTop + _lineSpacing * 6);
    text103->autoSize(flTextFieldAutoSize::LEFT);
    text103->mouseEnabled(false);
    displayObject = addChild(text103);
    //--------------------------------------

	ofLog() << "joystick1103->height() " << joystick1103->y() + joystick1103->height();

	//--------------------------------------
	_normalBackWidth = 500;
	_normalBackHeight = 500;

	_normalGraphics.drawRect(0, 0, _normalBackWidth, _normalBackHeight);
	_normalGraphics.endFill();
	//--------------------------------------

	//addEventListener(flEvent::CLOSE, this, &SubController1::_eventHandler);
	
	flBasicController::_setup();
}

//--------------------------------------------------------------
void SubController1::_update() {
    //ofLog() << "[SubController1]update()";
}

//--------------------------------------------------------------
void SubController1::_draw() {
    //ofLog() << "[SubController1]draw()";
    
    if(_isMinimize) return;
    
    //Draw Anything
    //    ofDrawBitmapString(_status, 10, 170);
}

//==============================================================
// Public Method
//==============================================================

//==============================================================
// Protected / Private Method
//==============================================================

//==============================================================
// Event Handler
//==============================================================

//--------------------------------------------------------------
void SubController1::_uiEventHandler(flEvent& event) {
	//ofLog() << "----------------------------------------------------------";
	//ofLog() << "[SubController1]_uiEventHandler(" << event.type() << ")";
	//ofLog() << "name = " << name().c_str();
	//ofLog() << "target = " << ((flDisplayObject*)event.target())->name().c_str();
	//ofLog() << "currnetTarget = " << ((flDisplayObject*)event.currentTarget())->name().c_str();
	//ofLog() << "----------------------------------------------------------";
    
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
    if(event.type() == flNumericDialerEvent::CHANGE) {
        flNumericDialerEvent& numericDialerEvent = *(flNumericDialerEvent*) &event;
        flNumericDialer* dialer = (flNumericDialer*)(event.currentTarget());
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
    if(event.type() == flJoyStick1Event::CHANGE) {
        flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
        flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
        
        flEvent* newEvent = new flEvent("uiEvent");
        newEvent->target(joystick);
        dispatchEvent(newEvent);
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
