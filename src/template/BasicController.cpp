#include "BasicController.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
BasicController::BasicController() {
//    cout << "[BasicController]BasicController()" << endl;
    
    _target = this;
    name("BasicController");
    
    useHandCursor(true);
    
    addEventListener(flMouseEvent::ROLL_OVER, this, &BasicController::_mouseEventHandler);
    addEventListener(flMouseEvent::ROLL_OUT, this, &BasicController::_mouseEventHandler);
    addEventListener(flMouseEvent::MOUSE_DOWN, this, &BasicController::_mouseEventHandler);
    //addEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_mouseEventHandler);
    
    float marginLeft; float marginTop;
    float spacing; float lineSpacing;
    //--------------------------------------
    marginLeft = 5;
    marginTop = 0;
    spacing = 100;
    lineSpacing = 22;
    
    titleTf = new flTextField();
    titleTf->x(marginLeft + spacing * 0);
    titleTf->y(marginTop + lineSpacing * 0);
    titleTf->width(120);
    titleTf->textColor(0xffffff);
    titleTf->text("[Contoller]");
    titleTf->mouseEnabled(false);
    addChild(titleTf);
    //--------------------------------------
    
    _isMinimize = false;
    
    //最小化ボタン
    minimizeButton = new flButton(18, 13);
    minimizeButton->labelText("-");
    minimizeButton->toggleEnabled(true);
    minimizeButton->addEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_buttonEventHandler);
    addChild(minimizeButton);
    
    //閉じるボタン
    closeButton = new flButton(18, 13);
    closeButton->labelText("x");
    closeButton->addEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_buttonEventHandler);
    addChild(closeButton);
    
    _backWidth = 0;
    _backHeight = 0;
    
    _minBackWidth = 0;
    _minBackHeight = 22;
    
    _normalBackWidth = 0;
    _normalBackHeight = 0;
    
    _onTop = true;
    
    _dragEnabled = true;
}

//--------------------------------------------------------------
//
BasicController::~BasicController() {
//    cout << "[BasicController]~BasicController()" << endl;
    
    _target = NULL;
    
    removeEventListener(flMouseEvent::ROLL_OVER, this, &BasicController::_mouseEventHandler);
    removeEventListener(flMouseEvent::ROLL_OUT, this, &BasicController::_mouseEventHandler);
    removeEventListener(flMouseEvent::MOUSE_DOWN, this, &BasicController::_mouseEventHandler);
    //removeEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_mouseEventHandler);
    
    //最小化ボタン
    minimizeButton->removeEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_buttonEventHandler);
    delete minimizeButton;
    minimizeButton = NULL;
    
    //閉じるボタン
    closeButton->removeEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_buttonEventHandler);
    delete closeButton;
    closeButton = NULL;
    
    _backWidth = 0;
    _backHeight = 0;
    
    _minBackWidth = 0;
    _minBackHeight = 0;
    
    _normalBackWidth = 0;
    _normalBackHeight = 0;
    
    _onTop = false;
    
    _dragEnabled = false;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void BasicController::setup() {
    //Sprite::setup();
    
    _setup();
    
    _updateRect();
    
    minimizeButton->x(width() - 53);
    minimizeButton->y(5);
    
    closeButton->x(width() - 28);
    closeButton->y(5);
}

//==============================================================
// PUBLIC MEHTOD
//==============================================================

//--------------------------------------------------------------
//
void BasicController::minimize() {
    if(_isMinimize) return;
    _isMinimize = true;
    minimizeButton->selected(true);
    
    //----------------------------------
    _backWidth = _minBackWidth;
    _backHeight = _minBackHeight;

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
        DisplayObject* child = getChildAt(i);
        
        if(child == titleTf) continue;
        if(child == closeButton) continue;
        if(child == minimizeButton) continue;
        
        child->visible(false);
    }
//    titleTf->visible(true);
//    minimizeButton->visible(true);
//    closeButton->visible(true);
    //----------------------------------
}
//--------------------------------------------------------------
//
void BasicController::normalize() {
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
        DisplayObject* child = getChildAt(i);
        
        if(child == titleTf) continue;
        if(child == closeButton) continue;
        if(child == minimizeButton) continue;
        
        child->visible(true);
    }
    
    if(parent()) ((DisplayObjectContainer*)parent())->addChild(this);
    //----------------------------------
}

//--------------------------------------------------------------
//
void BasicController::resize(float w, float h) {

}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void BasicController::_mouseEventHandler(flEvent& event) {
/*
    cout << "\n----------------------------------------------------------" << endl;
    printf("[BasicController]_mouseEventHandler(%s) %s\n", ofToString(event.type()).c_str(), name().c_str());
    cout << "target = " << ((DisplayObject*)event.target())->name().c_str() << endl;
    cout << "currnetTarget = " << ((DisplayObject*)event.currentTarget())->name().c_str() << endl;
    cout << "----------------------------------------------------------\n" << endl;
*/    
    
    //ボタン(ロールオーバー)
    if(event.type() == flMouseEvent::ROLL_OVER) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(event.target() == this) {
            
        }
    }
    //ボタン(ロールアウト)
    if(event.type() == flMouseEvent::ROLL_OUT) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());

        if(event.target() == this) {
            
        }
    }
    //ボタン(マウスオーバー)
    if(event.type() == flMouseEvent::MOUSE_OVER) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(event.target() == this) {
            
        }
    }
    //ボタン(マウスアウト)
    if(event.type() == flMouseEvent::MOUSE_OUT) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(event.target() == this) {
            
        }
    }
    //ボタン(マウスダウン)
    if(event.type() == flMouseEvent::MOUSE_DOWN) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        if(event.target() == this) {
            if(_dragEnabled) {
                if(_onTop) ((DisplayObjectContainer*)parent())->addChild(this);
                startDrag();
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_mouseEventHandler);
            }
        }
    }
    //ボタン(マウスアップ)
    if(event.type() == flMouseEvent::MOUSE_UP) {
        flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
        flButton* button = (flButton*)(event.currentTarget());
        
        //if(event.target() == this) ((DisplayObjectContainer*)parent())->addChild(this);
        if(event.target() == stage()) {
            stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &BasicController::_mouseEventHandler);
            stopDrag();
        }
    }
    
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
    
    //ジョイスティック1軸
    if(event.type() == flJoystick1Event::CHANGE) {
        flJoystick1Event& joystickEvent = *(flJoystick1Event*) &event;
        flJoystick1* joystick = (flJoystick1*)(event.currentTarget());
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
    
    //ジョイスティック2軸
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

//--------------------------------------------------------------
//
void BasicController::_buttonEventHandler(flEvent& event) {
    if(event.type() == flMouseEvent::MOUSE_UP) {
        if(event.target() == closeButton) dispatchEvent(new flEvent(flEvent::CLOSE));
        if(event.target() == minimizeButton) {
            if(minimizeButton->selected()) {
                minimize();
            } else {
                normalize();
            }
        }
    }
}
