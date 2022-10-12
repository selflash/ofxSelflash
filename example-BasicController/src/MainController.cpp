#include "MainController.h"

//==============================================================
// Constructor / Deconstructor
//==============================================================

//--------------------------------------------------------------
MainController::MainController() {
    ofLog() << "[MainController]MainController()";
    _target = this;
    
    name("MainController");
    useHandCursor(true);

    _title = "[MainController]";
}

//--------------------------------------------------------------
MainController::~MainController() {
    ofLog() << "[MainController]~MainController()";
    _target = NULL;
    
    //サブコントローラー
    delete _controller1;
    _controller1 = NULL;
    
    delete _controller2;
    _controller2 = NULL;
}

//==============================================================
// Setup / Update / Draw
//==============================================================

//--------------------------------------------------------------
void MainController::_setup() {
    ofLog() << "[MainController]_setup()";
    
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
    button001 = new flButton(150);
    button001->labelText("Full Screen");
    button001->toggleEnabled(true);
    button001->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
	displayObject = addChild(button001, x, y);
    
	label = new flTextField();
	label->text("Window Depth");
	label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
	label->mouseEnabled(false);
	displayObject = addChild(label, displayObject->x(), displayObject->y() + displayObject->height() + _margin);
    comboBox001 = new flComboBox(150);
    comboBox001->label(label);
    comboBox001->addItem<string>("Default", "default");
    comboBox001->addItem<string>("Always on Bottom", "alwaysOnBottom");
    comboBox001->addItem<string>("Always on Top", "alwaysOnTop");
    comboBox001->selectedIndex(0);
    comboBox001->addEventListener(flComboBoxEvent::CHANGE, this, &MainController::_uiEventHandler);
	displayObject = addChild(comboBox001, displayObject->x(), displayObject->y() + displayObject->height() + _margin);
    //--------------------------------------
    
    //--------------------------------------
	label = new flTextField();
	label->text("Sub Controllers");
	label->width(150);
	label->autoSize(flTextFieldAutoSize::LEFT);
	label->mouseEnabled(false);
	displayObject = addChild(label, displayObject->x(), displayObject->y() + displayObject->height() + _margin);
    
    button101 = new flButton(150);
    button101->labelText("Controller 1");
    button101->toggleEnabled(true);
    button101->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
	displayObject = addChild(button101, displayObject->x(), displayObject->y() + displayObject->height() + _margin);
    
    button102 = new flButton(150);
    button102->labelText("Controller 2");
    button102->toggleEnabled(true);
    button102->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
	displayObject = addChild(button102, displayObject->x(), displayObject->y() + displayObject->height() + _margin);
    //--------------------------------------
    
    //--------------------------------------
    //コントローラー1
    _controller1 = new SubController1("Transform Controller");
    _controller1->setup();
    _controller1->normalize();
    _controller1->x(315);
    _controller1->y(0);
    _controller1->addEventListener(flEvent::CLOSE, this, &MainController::_uiEventHandler);
    _controller1->addEventListener("uiEvent", this, &MainController::_uiEventHandler);
    //--------------------------------------
    //--------------------------------------
    //コントローラー2
    _controller2 = new SubController2("Style Controller");
    _controller2->setup();
    _controller2->normalize();
    _controller2->x(315);
    _controller2->y(0);
    _controller2->addEventListener(flEvent::CLOSE, this, &MainController::_uiEventHandler);
    _controller2->addEventListener("uiEvent", this, &MainController::_uiEventHandler);
    //--------------------------------------

	//--------------------------------------
    _defaultWindowWidth = displayObject->x() + displayObject->width() + _margin;
    _defaultWindowHeight = displayObject->y() + displayObject->height() + _margin;

	_normalGraphics.drawRect(0, 0, _defaultWindowWidth, _defaultWindowHeight);
	_normalGraphics.endFill();
	//--------------------------------------

	flBasicController::_setup();

	closeButton->visible(false);
}

//--------------------------------------------------------------
void MainController::_update() {
    //ofLog() << "[MainController]update()";
    
}

//--------------------------------------------------------------
void MainController::_draw() {
    //ofLog() << "[MainController]draw()";
    
    if(_isMinimize) return;
    
    //ofPushStyle();
    //ofSetColor(255, 255, 255, 255 * _compoundAlpha);
    //flFont::drawString("When the stage has a focus.\nScroll to change scale.\nDrag to change rotatin.", 5, 105);
    //ofPopStyle();
}

//==============================================================
// Public Method
//==============================================================

//--------------------------------------------------------------
void MainController::toggleShowAll() {
    visible(!visible());
    
    _controller1->visible(visible());
    _controller2->visible(visible());
}

//==============================================================
// Protected / Private Method
//==============================================================

//==============================================================
// Event Handler
//==============================================================

//--------------------------------------------------------------
void MainController::_uiEventHandler(flEvent& event) {
	//ofLog() << "----------------------------------------------------------";
	//ofLog() << "[MainController]_uiEventHandler(" << event.type() << ")";
	//ofLog() << "name = " << name().c_str();
	//ofLog() << "target = " << ((flDisplayObject*)event.target())->name().c_str();
	//ofLog() << "currnetTarget = " << ((flDisplayObject*)event.currentTarget())->name().c_str();
	//ofLog() << "----------------------------------------------------------";
    
    if(event.type() == flEvent::CLOSE) {
        flBasicController* target = (flBasicController*)(event.currentTarget());
        //コントローラー1
        if(target == _controller1) {
			if(target->parent()) ((flDisplayObjectContainer*)target->parent())->removeChild(target);
            button101->selected(false, false);
        }
        //コントローラー2
        if(target == _controller2) {
			if (target->parent()) ((flDisplayObjectContainer*)target->parent())->removeChild(target);
			button102->selected(false, false);
        }
    }
    
    if(event.type() == "uiEvent") {
        flBasicController* target = (flBasicController*)(event.currentTarget());
        
        if(target == _controller1) {
            flEvent* newEvent = new flEvent("uiEvent1");
            newEvent->target(event.target());
            dispatchEvent(newEvent);
        }
    }
    
    //ボタン(マウスダウン)
    if(event.type() == flButtonEvent::MOUSE_DOWN) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
    }
    
    //ボタン(チェンジ)
    if(event.type() == flButtonEvent::CHANGE) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(button == button001) {
            if(button->selected()) {
                ofSetFullscreen(true);
            } else {
                ofSetFullscreen(false);
            }
        }
        
        if(button == button101) {
            if(button->selected()) {
                ((flStage*)stage())->addChild(_controller1);
            } else {
                ((flStage*)stage())->removeChild(_controller1);
            }
        }
        if(button == button102) {
            if(button->selected()) {
                ((flStage*)stage())->addChild(_controller2);
            } else {
                ((flStage*)stage())->removeChild(_controller2);
            }
        }
    }
    
    //コンボボックス
    if(event.type() == flComboBoxEvent::CHANGE) {
        flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
        flComboBox* comboBox = (flComboBox*)(event.currentTarget());
        ofLog() << "-------------";
        ofLog() << comboBox->name() << " :";
        ofLog() << "selectedIndex : " << comboBox->selectedIndex();
        
        //        if(comboBox == comboBox001) {
        //            if(comboBox->selectedValue<string>() == "develop") {
        //                ofSetFullscreen(false);
        //                ofSetWindowPosition(0, 0);
        //                ofSetWindowShape(1080, 1920);
        //            }
        //            if(comboBox->selectedValue<string>() == "release") {
        //                ofSetWindowPosition(1925, 0);
        //                ofSetFullscreen(true);
        //            }
        //        }
        
        if(comboBox == comboBox001) {
            if(comboBox->selectedValue<string>() == "default") {
                NativeWindow::orderToDefault();
            }
            if(comboBox->selectedValue<string>() == "alwaysOnBottom") {
                NativeWindow::orderToBack();
            }
            if(comboBox->selectedValue<string>() == "alwaysOnTop") {
                NativeWindow::orderToFront();
            }
        }
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
