//
//  MainController.cpp
//  ofApp
//
//  Created by 横田達也 on 2016/12/15.
//
//

#include "MainController.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
MainController::MainController() {
    cout << "[MainController]MainController()" << endl;
    _target = this;
    
    name("MainController");
    useHandCursor(true);
}

//--------------------------------------------------------------
//
MainController::~MainController() {
    cout << "[MainController]~MainController()" << endl;
    _target = NULL;
    
    //サブコントローラー
    delete _controller1;
    _controller1 = NULL;
    
    delete _controller2;
    _controller2 = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void MainController::_setup() {
    cout << "[MainController]_setup()" << endl;
    
    BasicController::_setup();
    
//    minimizeButton->visible(false);
    closeButton->visible(false);
//    isDraggable(false);
    
    _normalBackWidth = 315;
    _normalBackHeight = 145;
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
    
    titleTf->text("Main Controller");
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    flTextField* textField = NULL;
    
    //--------------------------------------
    marginLeft = 5;
    marginTop = 5;
    spacing = 155;
    lineSpacing = 22.5;
    
    button001 = new flButton(150);
    button001->labelText("Full Screen");
    button001->x(marginLeft + spacing * 0);
    button001->y(marginTop + lineSpacing * 1);
    button001->toggleEnabled(true);
    button001->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
    addChild(button001);
    
    textField = new flTextField();
    textField->text("Window Depth");
    textField->x(marginLeft + spacing * 1);
    textField->y(marginTop + lineSpacing * 0);
    textField->textColor(FlashConfig::UI_LABEL_NORMAL_COLOR);
    textField->mouseEnabled(false);
    addChild(textField);
    comboBox001 = new flComboBox(150);
    comboBox001->label(textField);
    comboBox001->x(marginLeft + spacing * 1);
    comboBox001->y(marginTop + lineSpacing * 1);
    comboBox001->addItem<string>("Default", "default");
    comboBox001->addItem<string>("Always on Bottom", "alwaysOnBottom");
    comboBox001->addItem<string>("Always on Top", "alwaysOnTop");
    comboBox001->selectedIndex(0);
    comboBox001->addEventListener(flComboBoxEvent::CHANGE, this, &MainController::_uiEventHandler);
    addChild(comboBox001);
    //--------------------------------------
    
    //--------------------------------------
    marginLeft = 5;
    marginTop = 5;
    spacing = 155;
    lineSpacing = 22.5;
    
    textField = new flTextField();
    textField->x(marginLeft + spacing * 0);
    textField->y(marginTop + lineSpacing * 2);
    textField->text("Sub Controllers");
    textField->width(300);
    textField->autoSize(flTextFieldAutoSize::CENTER);
    textField->mouseEnabled(false);
    addChild(textField);
    
    button101 = new flButton(150);
    button101->labelText("Controller 1");
    button101->x(marginLeft + spacing * 0);
    button101->y(marginTop + lineSpacing * 3);
    button101->toggleEnabled(true);
    button101->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
    addChild(button101);
    
    button102 = new flButton(150);
    button102->labelText("Controller 2");
    button102->x(marginLeft + spacing * 1);
    button102->y(marginTop + lineSpacing * 3);
    button102->toggleEnabled(true);
    button102->addEventListener(flButtonEvent::CHANGE, this, &MainController::_uiEventHandler);
    addChild(button102);
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
}

//--------------------------------------------------------------
//
void MainController::_update() {
    //cout << "[MainController]update()" << endl;
    
}

//--------------------------------------------------------------
//
void MainController::_draw() {
    //cout << "[MainController]draw()" << endl;
    
    if(_isMinimize) return;
    
    ofPushStyle();
    ofSetColor(255, 255, 255, 255 * _compoundAlpha);
    flFont::drawString("When the stage has a focus.\nScroll to change scale.\nDrag to change rotatin.", 5, 105);
    ofPopStyle();
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//--------------------------------------------------------------
//
void MainController::normalize() {
    if(!_isMinimize) return;
    _isMinimize = false;
    
    minimizeButton->selected(false);
    
    //----------------------------------
    _backWidth = _normalBackWidth;
    _backHeight = _normalBackHeight;
    
    flGraphics* g;
    g = graphics();
    g->clear();
    g->lineStyle(1, 0xffffff);
    g->beginFill(0x000000, 0.7);
    g->drawRect(0, 0, _backWidth, _backHeight);
    g->endFill();
    //----------------------------------
    
    //----------------------------------
    int i; int l;
    l = numChildren();
    for(i = 0; i < l; i++) {
        getChildAt(i)->visible(true);
    }
    
    if(parent()) ((DisplayObjectContainer*)parent())->addChild(this);
    //----------------------------------
}

//--------------------------------------------------------------
//
void MainController::toggleShowAll() {
    visible(!visible());
    
    _controller1->visible(visible());
    _controller2->visible(visible());
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void MainController::_uiEventHandler(flEvent& event) {
    //    cout << "[MainController]_uiEventHandler(" << event.type() << endl;
    
    if(event.type() == flEvent::CLOSE) {
        BasicController* target = (BasicController*)(event.currentTarget());
        //コントローラー1
        if(target == _controller1) {
            ((flStage*)stage())->removeChild(target);
            button101->selected(false, false);
        }
        //コントローラー2
        if(target == _controller2) {
            ((flStage*)stage())->removeChild(target);
            button102->selected(false, false);
        }
    }
    
    if(event.type() == "uiEvent") {
        BasicController* target = (BasicController*)(event.currentTarget());
        
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
        cout << "-------------" << endl;
        cout << comboBox->name() << " :" << endl;
        cout << "selectedIndex : " << comboBox->selectedIndex() << endl;
        
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
    if(event.type() == flJoystick1DEvent::CHANGE) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::UP) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::DOWN) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::LEFT) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    if(event.type() == flJoystick1DEvent::RIGHT) {
        flJoystick1DEvent& joystickEvent = *(flJoystick1DEvent*) &event;
        flJoystick1D* joystick = (flJoystick1D*)(event.currentTarget());
    }
    
    //ジョイスティック2D
    if(event.type() == flJoystick2DEvent::CHANGE) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::UP) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::DOWN) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::LEFT) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
    if(event.type() == flJoystick2DEvent::RIGHT) {
        flJoystick2DEvent& joystickEvent = *(flJoystick2DEvent*) &event;
        flJoystick2D* joystick = (flJoystick2D*)(event.currentTarget());
    }
}
