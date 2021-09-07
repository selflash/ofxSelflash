#include "flBasicController.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flBasicController::flBasicController() {
		//ofLog() << "[flBasicController]flBasicController()";
        
        _target = this;
        name("flBasicController");

		_titleText = "[Contoller]";
		_titleBarHeight = (_margin + 18) + _margin;

        useHandCursor(true);
        
        addEventListener(flMouseEvent::ROLL_OVER, this, &flBasicController::_flBasicControllerMouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flBasicController::_flBasicControllerMouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicController::_flBasicControllerMouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
        
		//x = marginLeft;
		//y = marginTop;
        //titleTf = new flTextField();
        //titleTf->x(x);
        //titleTf->y(y);
        //titleTf->width(120);
        //titleTf->textColor(0xffffff);
        //titleTf->text("[Contoller]");
        //titleTf->mouseEnabled(false);
        //addChild(titleTf);
        //--------------------------------------
	}
    
    //--------------------------------------------------------------
    flBasicController::~flBasicController() {
		//ofLog() << "[flBasicController]~flBasicController()";
        
        _target = NULL;
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flBasicController::_flBasicControllerMouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flBasicController::_flBasicControllerMouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicController::_flBasicControllerMouseEventHandler);
        //removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);
        
        //最小化ボタン
        minimizeButton->removeEventListener(flButtonEvent::CHANGE, this, &flBasicController::_flBasicControllerEventHandler);
        delete minimizeButton;
        minimizeButton = NULL;
        
        //閉じるボタン
        closeButton->removeEventListener(flButtonEvent::MOUSE_UP, this, &flBasicController::_flBasicControllerEventHandler);
        delete closeButton;
        closeButton = NULL;
        
        for(auto* radioButtonGroup : radioButtonGroups) {
            delete radioButtonGroup;
            radioButtonGroup = NULL;
        }
        radioButtonGroups.clear();

		_listeners.unsubscribeAll();
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flBasicController::setup() {
        //_setup();

		//_margin = 6;
		//_marginLeft = _margin;
		//_marginTop = (_margin + 18) + _margin;
		//_spacing = 150;
		//_lineSpacing = 18 + _margin;
        
        _updateRect();

		int x, y, w, h = 0;
		flDisplayObject* displayObject = NULL;
		flTextField* label = NULL;
		flRadioButtonGroup* radioButtonGroup = NULL;
		//--------------------------------------

		//最小化ボタン
		minimizeButton = new flButton(18, 18);
		//minimizeButton->x(w - (18 + 5 + 18 + 5));
		minimizeButton->y(_margin);
		minimizeButton->labelText("-");
		minimizeButton->toggleEnabled(true);
		minimizeButton->addEventListener(flButtonEvent::CHANGE, this, &flBasicController::_flBasicControllerEventHandler);
		displayObject = addChild(minimizeButton);

		//閉じるボタン
		closeButton = new flButton(18, 18);
		//closeButton->x(w - (18 + 5));
		closeButton->y(_margin);
		closeButton->labelText("x");
		closeButton->addEventListener(flButtonEvent::MOUSE_DOWN, this, &flBasicController::_flBasicControllerEventHandler);
		displayObject = addChild(closeButton);

		_normalBackWidth = displayObject->x() + displayObject->width() + _margin;
		_normalBackHeight = displayObject->y() + displayObject->height() + _margin;

		//_minBackWidth = _normalBackWidth;
		_minBackHeight = _margin + 18 + _margin;

		flSprite::setup();
    }

	//--------------------------------------------------------------
	void flBasicController::_setup() {
		_minBackWidth = _normalBackWidth;
		_backWidth = _normalBackWidth;
		_backHeight = _normalBackHeight;

		//--------------------------------------
		_normalGraphics.clear();
		_normalGraphics.lineStyle(1, 0xffffff);
		_normalGraphics.beginFill(0x000000, 0.3);
		_normalGraphics.drawRect(0, 0, _backWidth, _backHeight);
		_normalGraphics.endFill();
		//--------------------------------------

		//----------------------------------
		_minimalGraphics.clear();
		_minimalGraphics.lineStyle(1, 0xffffff);
		_minimalGraphics.beginFill(0x000000, 0.3);
		_minimalGraphics.drawRect(0, 0, _minBackWidth, _minBackHeight);
		_minimalGraphics.endFill();
		//----------------------------------

		_graphics = &_normalGraphics;

		{
			float w = _backWidth;
			minimizeButton->x(w - (18 + 5 + 18 + 5));
			addChild(minimizeButton);
			closeButton->x(w - (18 + 5));
			addChild(closeButton);
		}

		_updateRect();

		//addEventListener(flEvent::CLOSE, this, &flBasicController::_eventHandler);
	}

    //--------------------------------------------------------------
    void flBasicController::_draw() {
		flSprite::_draw();

		ofPushStyle();
		ofSetColor(255, 255, 255, 255);
		flFont::drawString(_titleText, 6, 20);
		ofPopStyle();
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flBasicController::minimize() {
        if(_isMinimize) return;
        _isMinimize = true;

        minimizeButton->selected(true, false);
        
        ////----------------------------------
        //_backWidth = _minBackWidth;
        //_backHeight = _minBackHeight;
        //
        //flGraphics* g;
        //g = graphics();
        //g->clear();
        //g->lineStyle(1, 0xffffff);
        //g->beginFill(0x000000, 0.7);
        //g->drawRect(0, 0, _backWidth, _backHeight);
        //g->endFill();
        ////----------------------------------

		//----------------------------------
		_backWidth = _minBackWidth;
		_backHeight = _minBackHeight;
		_graphics = &_minimalGraphics;
		//----------------------------------
        
        //----------------------------------
        int i; int l;
        l = numChildren();
        for(i = 0; i < l; i++) {
            flDisplayObject* child = getChildAt(i);
            
            //if(child == titleTf) continue;
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
        
        minimizeButton->selected(false, false);
        
        ////----------------------------------
        //_backWidth = _normalBackWidth;
        //_backHeight = _normalBackHeight;
        //
        //flGraphics* g;
        //g = graphics();
        //g->clear();
        //g->lineStyle(1, 0xffffff);
        //g->beginFill(0x000000, 0.7);
        //g->drawRect(0, 0, _backWidth, _backHeight);
        //g->endFill();
        ////----------------------------------

		//----------------------------------
		_backWidth = _normalBackWidth;
		_backHeight = _normalBackHeight;
		_graphics = &_normalGraphics;
		//----------------------------------
        
        //----------------------------------
        int i; int l;
        l = numChildren();
        for(i = 0; i < l; i++) {
            flDisplayObject* child = getChildAt(i);
            
            //if(child == titleTf) continue;
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
    void flBasicController::_flBasicControllerEventHandler(flEvent& event) {
        //ofLog() << "[flBasicController]_flBasicControllerEventHandler(" << event.type() << ")";
        //ofLog() << "[flBasicController]this          = " << this << "," << ((flDisplayObject*) this)->name();
        //ofLog() << "[flBasicController]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
        //ofLog() << "[flBasicController]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();

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
            
			if (button == closeButton) {
				if(parent()) ((flDisplayObjectContainer*)parent())->removeChild(this);
				dispatchEvent(new flEvent(flEvent::CLOSE));
			}
        }
        if(event.type() == flButtonEvent::MOUSE_UP) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
        }
        if(event.type() == flButtonEvent::CHANGE) {
            flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
            flButton* button = (flButton*)(event.currentTarget());
            
			//ofLog() << "flBasicController change";

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
        if(event.type() == flNumericDialerEvent::CHANGE) {
            flNumericDialerEvent& numberDialerEvent = *(flNumericDialerEvent*) &event;
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
    void flBasicController::_flBasicControllerMouseEventHandler(flEvent& event) {
		//ofLog() << "[flBasicController]_flBasicControllerMouseEventHandler(" << event.type() << ")";
		//ofLog() << "[flBasicController]this          = " << this << "," << ((flDisplayObject*)this)->name();
		//ofLog() << "[flBasicController]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*)event.currentTarget())->name();
		//ofLog() << "[flBasicController]target        = " << event.target() << "," << ((flDisplayObject*)event.target())->name();

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
            
            if(event.target() == (hitArea() != NULL ? hitArea() : this)) {
                if(_dragEnabled) {
                    if(_onTop) ((flDisplayObjectContainer*)parent())->addChild(this);
                    startDrag();
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_flBasicControllerMouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
            
            //if(event.target() == this) ((DisplayObjectContainer*)parent())->addChild(this);
            if(event.target() == stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_flBasicControllerMouseEventHandler);
                stopDrag();
            }
        }
    }
    
}
