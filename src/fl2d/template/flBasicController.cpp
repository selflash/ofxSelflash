#include "flBasicController.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flBasicController::flBasicController() {
        //    cout << "[flBasicController]flBasicController()";
        
        _target = this;
        name("flBasicController");
        
        useHandCursor(true);
        
        addEventListener(flMouseEvent::ROLL_OVER, this, &flBasicController::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flBasicController::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicController::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
        
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
        minimizeButton = new flButton(20, 13);
        minimizeButton->labelText(" -");
        minimizeButton->toggleEnabled(true);
        minimizeButton->addEventListener(flButtonEvent::CHANGE, this, &flBasicController::_uiEventHandler);
        addChild(minimizeButton);
        
        //閉じるボタン
        closeButton = new flButton(20, 13);
        closeButton->labelText(" x");
        closeButton->addEventListener(flButtonEvent::MOUSE_DOWN, this, &flBasicController::_uiEventHandler);
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
    flBasicController::~flBasicController() {
        //    cout << "[flBasicController]~flBasicController()";
        
        _target = NULL;
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flBasicController::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flBasicController::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicController::_mouseEventHandler);
        //removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
        
        //最小化ボタン
        minimizeButton->removeEventListener(flButtonEvent::CHANGE, this, &flBasicController::_uiEventHandler);
        delete minimizeButton;
        minimizeButton = NULL;
        
        //閉じるボタン
        closeButton->removeEventListener(flButtonEvent::MOUSE_UP, this, &flBasicController::_uiEventHandler);
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
        
        for(auto* radioButtonGroup : radioButtonGroups) {
            delete radioButtonGroup;
            radioButtonGroup = NULL;
        }
        radioButtonGroups.clear();
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flBasicController::setup() {
        //Sprite::setup();
        
        _setup();
        
        _updateRect();
        
        float w = width();
        minimizeButton->x(w - (18 + 5 + 18 + 5 + 5));
        minimizeButton->y(4);
        
        closeButton->x(w - (18 + 5 + 5));
        closeButton->y(4);
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flBasicController::minimize() {
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
            flDisplayObject* child = getChildAt(i);
            
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
    void flBasicController::normalize() {
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
            flDisplayObject* child = getChildAt(i);
            
            if(child == titleTf) continue;
            if(child == closeButton) continue;
            if(child == minimizeButton) continue;
            
            child->visible(true);
        }
        
        if(parent()) ((flDisplayObjectContainer*)parent())->addChild(this);
        //----------------------------------
    }
    
    //--------------------------------------------------------------
    void flBasicController::resize(float w, float h) {
        
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flBasicController::_uiEventHandler(flEvent& event) {
//        ofLog() << "[flBasicController]_uiEventHandler(" << event.type() << ")";
//        ofLog() << "[flBasicController]this          = " << this << "," << ((flDisplayObject*) this)->name();
//        ofLog() << "[flBasicController]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flBasicController]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();

        //ボタン
        if(event.type() == flButtonEvent::ROLL_OVER) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::ROLL_OUT) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::MOUSE_OVER) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::MOUSE_OUT) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::MOUSE_DOWN) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
            
            if(button == closeButton) dispatchEvent(new flEvent(flEvent::CLOSE));
        }
        if(event.type() == flButtonEvent::MOUSE_UP) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::CHANGE) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
            
            if(button == minimizeButton) {
                if(minimizeButton->selected()) {
                    minimize();
                } else {
                    normalize();
                }
            }
        }

        //コンボボックス
        if(event.type() == flComboBoxEvent::CHANGE) {
            flComboBoxEvent& comboBoxEvent = *(flComboBoxEvent*) &event;
            flComboBox* comboBox = (flComboBox*)(event.currentTarget());
            
//            ofLog() << "-------------";
//            ofLog() << comboBox->name() << " :";
//            ofLog() << "selectedIndex : " << comboBox->selectedIndex();
//            ofLog() << "selectedValue : " << comboBox->selectedValue<string>();
//            ofLog() << "selectedValue : " << comboBox->selectedValue<float>();
//            ofLog() << "selectedValue : " << comboBox->selectedValue<flComboBox*>()->name();
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
        
        //ジョイスティック2軸
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
    
    //--------------------------------------------------------------
    void flBasicController::_mouseEventHandler(flEvent& event) {
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            
            if(event.target() == this) {
                
            }
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            
            if(event.target() == this) {
                
            }
        }
        
        //Mouse Over
        if(event.type() == flMouseEvent::MOUSE_OVER) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            
            if(event.target() == this) {
                
            }
        }
        
        //Mouse Out
        if(event.type() == flMouseEvent::MOUSE_OUT) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            
            if(event.target() == this) {
                
            }
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            
            if(event.target() == this) {
                if(_dragEnabled) {
                    if(_onTop) ((flDisplayObjectContainer*)parent())->addChild(this);
                    startDrag();
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            
            //if(event.target() == this) ((DisplayObjectContainer*)parent())->addChild(this);
            if(event.target() == stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
                stopDrag();
            }
        }
    }
    
}
