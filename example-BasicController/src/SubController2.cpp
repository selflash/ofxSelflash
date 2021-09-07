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
SubController2::SubController2(string title) {
    ofLog() << "[SubController2]SubController2()";
    _target = this;
    
    name(title);
    useHandCursor(true);
    
	_titleText = "[" + title + "]";
}

//--------------------------------------------------------------
SubController2::~SubController2() {
    ofLog() << "[SubController2]~SubController2()";
    _target = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
void SubController2::_setup() {
    ofLog() << "[SubController2]_setup()";
    
	//--------------------------------------
	int x, y, w, h = 0;
	flDisplayObject* displayObject = NULL;
	flTextField* label = NULL;
	flRadioButtonGroup* radioButtonGroup = NULL;
	//--------------------------------------
    
    //--------------------------------------
    _marginLeft = 5;
	_marginTop = 20;
	_spacing = 205;
	_lineSpacing = 22.5;
    
    label = new flTextField();
    label->text("Box Color");
    label->x(_marginLeft + _spacing * 0);
    label->y(_marginTop + _lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
	displayObject = addChild(label);
    colorSlider001 = new flColorSlider(185, false);
    colorSlider001->label(label);
    //    colorSlider001->label()->width(200);
    //    colorSlider001->label()->autoSize(flTextFieldAutoSize::CENTER);
    colorSlider001->x(_marginLeft + _spacing * 0);
    colorSlider001->y(_marginTop + _lineSpacing * 1);
    colorSlider001->redValue<float>(1.0);
    colorSlider001->greenValue<float>(1.0);
    colorSlider001->blueValue<float>(1.0);
    //    colorSlider001->addEventListener(flColorSliderEvent::CHANGE, this, &SubController2::_uiEventHandler);
	displayObject = addChild(colorSlider001);
    
    //スライダー
    label = new flTextField();
    label->text("Line Width");
    label->x(_marginLeft + _spacing * 1);
    label->y(_marginTop + _lineSpacing * 0);
    label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    label->mouseEnabled(false);
	displayObject = addChild(label);
    slider001 = new flSlider(185, 1, 20, 1);
    slider001->x(_marginLeft + _spacing * 1);
    slider001->y(_marginTop + _lineSpacing * 1);
    //    slider001->addEventListener(flSliderEvent::CHANGE, this, &SubController2::_uiEventHandler);
	displayObject = addChild(slider001);
    
    check001 = new flCheckBox();
    check001->labelText("Fill Enabled");
    check001->x(_marginLeft + _spacing * 1);
    check001->y(_marginTop + _lineSpacing * 2 + 10);
    //    check001->selected(true);
    //    check001->enabled(false);
    //    check001->addEventListener(flRadioButtonEvent::CHANGE, this, &SubController2::_uiEventHandler);
	displayObject = addChild(check001);
    //--------------------------------------

	_normalBackWidth = 400;
	_normalBackHeight = 105;

	//addEventListener(flEvent::CLOSE, this, &SubController2::_eventHandler);

	flBasicController::_setup();
}

//--------------------------------------------------------------
void SubController2::_update() {
    //ofLog() << "[SubController2]update()";
}

//--------------------------------------------------------------
void SubController2::_draw() {
    //ofLog() << "[SubController2]draw()";
    
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
void SubController2::_uiEventHandler(flEvent& event) {
    //    ofLog() << "[SubController2]_uiEventHandler(" << event.type();
    
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
