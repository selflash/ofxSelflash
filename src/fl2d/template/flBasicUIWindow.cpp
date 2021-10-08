#include "flBasicUIWindow.h"

namespace fl2d {
    
    //==============================================================
	// Constructor / Destructor
	//==============================================================
    
    //--------------------------------------------------------------
    flBasicUIWindow::flBasicUIWindow() {
        //ofLog(OF_LOG_NOTICE) << "[flBasicUIWindow]flBasicUIWindow()";
        _target = this;
        name("flBasicUIWindow");

		_title = "[flBasicUIWindow]";

        useHandCursor(true);        
    }
    
    //--------------------------------------------------------------
    flBasicUIWindow::~flBasicUIWindow() {
        //ofLog(OF_LOG_NOTICE) << "[flBasicUIWindow]~flBasicUIWindow()";

		removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicUIWindow::_mouseEventHandler);
		
		//最小化ボタン
		removeChild(minimizeButton);
		minimizeButton->removeEventListener(flButtonEvent::CHANGE, this, &flBasicUIWindow::_uiEventHandler);
		delete minimizeButton;
		minimizeButton = NULL;

		//最大化ボタン
		removeChild(maximizeButton);
		maximizeButton->removeEventListener(flButtonEvent::CHANGE, this, &flBasicUIWindow::_uiEventHandler);
		delete maximizeButton;
		maximizeButton = NULL;

		//
		removeChild(_sizingHandle);
		_sizingHandle->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicUIWindow::_mouseEventHandler);
		delete _sizingHandle;
		_sizingHandle = NULL;

		_listeners.unsubscribeAll();
    }
    
    //==============================================================
	// Setup / Update / Draw
	//==============================================================
    
    //--------------------------------------------------------------
    void flBasicUIWindow::setup() {
		//ofLog() << "[flBasicUIWindow]setup()";

		_marginTop = _titleBarHeight;
		_minBackHeight = _titleBarHeight;

		int x, y, w, h = 0;
		flDisplayObject* displayObject = NULL;
		flTextField* label = NULL;
		flRadioButtonGroup* radioButtonGroup = NULL;
		//--------------------------------------

		//最小化ボタン
		{
			minimizeButton = new flButton(18, 18);
			minimizeButton->name("MinimizeButton");
			minimizeButton->y(_margin);
			minimizeButton->labelText("");
			minimizeButton->toggleEnabled(true);
			minimizeButton->toolTipEnabled(true);
			minimizeButton->toolTipText(u8"最小化。");
			minimizeButton->addEventListener(flButtonEvent::CHANGE, this, &flBasicUIWindow::_uiEventHandler);
			displayObject = addChild(minimizeButton);

			flShape* icon = new flShape();
			flGraphics* g = icon->graphics();
			g->clear();
			g->lineStyle(1, flDefinition::UI_LABEL_NORMAL_COLOR.getHex());
			g->moveTo(4, 9);
			g->lineTo(14, 9);
			g->endFill();
			minimizeButton->addChild(icon);

			//minimizeButton->visible(false);
		}

		//最大化ボタン
		{
			maximizeButton = new flButton(18, 18);
			maximizeButton->name("MaximizeButton");
			maximizeButton->y(_margin);
			maximizeButton->labelText("");
			maximizeButton->toggleEnabled(true);
			maximizeButton->toolTipEnabled(true);
			maximizeButton->toolTipText(u8"最大化。");
			maximizeButton->addEventListener(flButtonEvent::CHANGE, this, &flBasicUIWindow::_uiEventHandler);
			displayObject = addChild(maximizeButton);

			flShape* icon = new flShape();
			flGraphics* g = icon->graphics();
			g->clear();
			g->lineStyle(1, flDefinition::UI_LABEL_NORMAL_COLOR.getHex());
			g->moveTo(4, 4);
			g->lineTo(14, 4);
			g->lineTo(14, 14);
			g->lineTo(3, 14);
			g->lineTo(4, 4);
			g->endFill();
			maximizeButton->addChild(icon);

			//maximizeButton->visible(false);
		}

		//閉じるボタン
		{
			closeButton = new flButton(18, 18);
			closeButton->name("CloseButton");
			closeButton->y(_margin);
			closeButton->labelText("");
			closeButton->toolTipEnabled(true);
			closeButton->toolTipText(u8"閉じる。");
			closeButton->addEventListener(flButtonEvent::CLICK, this, &flBasicUIWindow::_uiEventHandler);
			displayObject = addChild(closeButton);

			flShape* icon = new flShape();
			flGraphics* g = icon->graphics();
			g->clear();
			g->lineStyle(1, flDefinition::UI_LABEL_NORMAL_COLOR.getHex());
			g->moveTo(4, 4);
			g->lineTo(14, 14);
			g->moveTo(14, 4);
			g->lineTo(4, 14);
			g->endFill();
			closeButton->addChild(icon);

			//closeButton->visible(false);
		}

		{
			_sizingHandle = new flBasicDraggableObject();
			_sizingHandle->setup();
			_sizingHandle->x(0);
			_sizingHandle->y(0);
			_sizingHandle->visible(false);
			_sizingHandle->dragEnabled(true);
			_sizingHandle->useHandCursor(true);
			_sizingHandle->toolTipEnabled(true);
			_sizingHandle->toolTipText(u8"ドラッグする事でウインドウサイズを変更します。");
			_sizingHandle->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicUIWindow::_mouseEventHandler);
			addChild(_sizingHandle);

			flGraphics* g = _sizingHandle->graphics();
			g->clear();
			g->beginFill(0xff0000, 0.0);
			g->drawCircle(0, 0, 12);
			g->endFill();
		}

		_normalBackWidth = displayObject->x() + displayObject->width() + _margin;
		_normalBackHeight = displayObject->y() + displayObject->height() + _margin;

		flBasicDraggableObject::setup();
    }

	//--------------------------------------------------------------
	void flBasicUIWindow::_setup() {
		resize(_normalBackWidth, _normalBackHeight);

		////----------------------------------
		//_minimalGraphics.clear();
		//_minimalGraphics.lineStyle(1, 0xffffff);
		//_minimalGraphics.beginFill(0x000000, 0.7);
		//_minimalGraphics.drawRect(0, 0, _normalBackWidth, _minBackHeight);
		//_minimalGraphics.endFill();
		////----------------------------------

		//_backWidth = _normalBackWidth;
		//_backHeight = _normalBackHeight;
		//_graphics = &_normalGraphics;

		//_relocateTitleBarButtons();

		//_updateRect();
	}

    //--------------------------------------------------------------
    void flBasicUIWindow::update() {
		//ofLog() << "[flBasicUIWindow]update()";

		flBasicDraggableObject::update();

		if (_sizingHandle->isGrabbed()) {
			int dx = abs(_sizingHandle->x() - _sizingHandle->startDragPoint().x);
			int dy = abs(_sizingHandle->y() - _sizingHandle->startDragPoint().y);
			if (dx == 0 && dy == 0) return;

			int x = _sizingHandle->x();
			int y = _sizingHandle->y();

			resize(x, y);
		}
    }
    
    //--------------------------------------------------------------
    void flBasicUIWindow::draw() {
		flBasicDraggableObject::draw();

		if (_title != "") {
			ofPushStyle();
			ofSetColor(255, 255, 255, 255);
			flFont::drawString(_title, 6, 20);
			ofPopStyle();
		}
    }

	//==============================================================
	// Public Method
	//==============================================================

	//--------------------------------------------------------------
	void flBasicUIWindow::minimize() {
		if (_isMinimize) return;

		_isMinimize = true;
		minimizeButton->selected(true, false);

		_isMaximize = false;
		maximizeButton->selected(false, false);
		maximizeButton->enabled(false);

		//----------------------------------
		_backHeight = _minBackHeight;
		_graphics = &_minimalGraphics;
		//----------------------------------

		//----------------------------------
		int i; int l;
		l = numChildren();
		for (i = 0; i < l; i++) {
			flDisplayObject* child = getChildAt(i);

			if (child == closeButton) continue;
			if (child == minimizeButton) continue;
			if (child == maximizeButton) continue;

			child->visible(false);
		}
		//----------------------------------

		_relocateTitleBarButtons();
	}

	//--------------------------------------------------------------
	void flBasicUIWindow::maximize() {
		if (_isMaximize) return;

		_preDragEnabled = dragEnabled();
		dragEnabled(false);

		_isMinimize = false;
		minimizeButton->selected(false, false);
		minimizeButton->enabled(false);

		_isMaximize = true;
		maximizeButton->selected(true, false);

		//----------------------------------
		_maxBackWidth = ofGetWidth();
		_maxBackHeight = ofGetHeight();
		_maximumGraphics.clear();
		_maximumGraphics.lineStyle(1, 0xffffff);
		_maximumGraphics.beginFill(0x000000, 0.7);
		_maximumGraphics.drawRect(0, 0, _maxBackWidth, _maxBackHeight);
		_maximumGraphics.endFill();
		//----------------------------------

		//----------------------------------
		_backWidth = _maxBackWidth;
		_backHeight = _maxBackHeight;
		_graphics = &_maximumGraphics;

		if (parent()) {
			ofPoint localPoint = parent()->globalToLocal(ofPoint(0, 0));
			x(roundf(localPoint.x));
			y(roundf(localPoint.y));
		}
		//----------------------------------

		//----------------------------------
		int i; int l;
		l = numChildren();
		for (i = 0; i < l; i++) {
			flDisplayObject* child = getChildAt(i);

			if (child == closeButton) continue;
			if (child == minimizeButton) continue;
			if (child == maximizeButton) continue;

			child->visible(true);
		}

		if (parent()) ((flDisplayObjectContainer*)parent())->addChild(this);
		//----------------------------------

		_relocateTitleBarButtons();
	}

	//--------------------------------------------------------------
	void flBasicUIWindow::normalize() {
		if (!_isMinimize && !_isMaximize) return;

		dragEnabled(_preDragEnabled);

		bool preModeIsMaximize = _isMaximize;

		_isMinimize = false;
		minimizeButton->selected(false, false);
		minimizeButton->enabled(true);

		_isMaximize = false;
		maximizeButton->selected(false, false);
		maximizeButton->enabled(true);

		//----------------------------------
		_backWidth = _normalBackWidth;
		_backHeight = _normalBackHeight;
		_graphics = &_normalGraphics;

		if (preModeIsMaximize) {
			if (parent()) {
				ofPoint localPoint = parent()->globalToLocal(
					ofPoint(
					(ofGetWidth() * 0.5) - (_backWidth * 0.5),
						(ofGetHeight() * 0.5) - (_backHeight * 0.5)
					)
				);
				x(roundf(localPoint.x));
				y(roundf(localPoint.y));
			}
		}
		//----------------------------------

		//----------------------------------
		int i; int l;
		l = numChildren();
		for (i = 0; i < l; i++) {
			flDisplayObject* child = getChildAt(i);

			if (child == closeButton) continue;
			if (child == minimizeButton) continue;
			if (child == maximizeButton) continue;

			child->visible(true);
		}

		if (parent()) ((flDisplayObjectContainer*)parent())->addChild(this);
		//----------------------------------

		_relocateTitleBarButtons();
	}

	//--------------------------------------------------------------
	void flBasicUIWindow::resize(float w, float h) {
		_normalBackWidth = w;
		_normalBackHeight = h;

		//----------------------------------
		_minimalGraphics.clear();
		_minimalGraphics.lineStyle(1, 0xffffff);
		_minimalGraphics.beginFill(0x000000, 0.7);
		_minimalGraphics.drawRect(0, 0, _normalBackWidth, _minBackHeight);
		_minimalGraphics.endFill();
		//----------------------------------

		//--------------------------------------
		_normalGraphics.clear();
		_normalGraphics.lineStyle(1, 0xffffff);
		_normalGraphics.beginFill(0x000000, 0.7);
		_normalGraphics.drawRect(0, 0, _normalBackWidth, _normalBackHeight);
		_normalGraphics.endFill();
		//--------------------------------------

		_backWidth = _normalBackWidth;
		_backHeight = _normalBackHeight;
		_graphics = &_normalGraphics;

		_relocateTitleBarButtons();

		_updateRect();

		_sizingHandle->x(_backWidth);
		_sizingHandle->y(_backHeight);
	}

	//--------------------------------------------------------------
	bool flBasicUIWindow::lock() { return _isLocked; }
	void flBasicUIWindow::lock(bool value) {
		_isLocked = value;

		for (int i = 0; i < numChildren(); i++) {
			flDisplayObject* displayObject = (flDisplayObject*)getChildAt(i);
			//ofLog(OF_LOG_VERBOSE) << "displayObject->name() = " << displayObject->name();

			if (displayObject->typeID() == FL_TYPE_UIBASE) {
				//ofLog(OF_LOG_VERBOSE) << "displayObject.name = " << displayObject->name();
				((flUIBase*)displayObject)->enabled(_isLocked);
			}
		}
	}

    //==============================================================
    // Protected / Private Method
    //==============================================================
 
	//--------------------------------------------------------------
	void flBasicUIWindow::_relocateTitleBarButtons() {
		float w = _backWidth;

		minimizeButton->x(w - (18 + 5) * 3);
		maximizeButton->x(w - (18 + 5) * 2);
		closeButton->x(w - (18 + 5) * 1);

		//addChild(minimizeButton);
		//addChild(maximizeButton);
		//addChild(closeButton);
	}

    //==============================================================
    // Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flBasicUIWindow::_mouseEventHandler(flEvent& event) {
		//ofLog(OF_LOG_NOTICE) << "[flBasicUIWindow]_mouseEventHandler(" << event.type() << ")";
		//ofLog(OF_LOG_NOTICE) << "[flBasicUIWindow]this          = " << this;
		//ofLog(OF_LOG_NOTICE) << "[flBasicUIWindow]currentTarget = " << event.currentTarget();
		//ofLog(OF_LOG_NOTICE) << "[flBasicUIWindow]target        = " << event.target();

		flBasicDraggableObject::_mouseEventHandler(event);

		//Roll Over
		if (event.type() == flMouseEvent::ROLL_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Roll Out
		if (event.type() == flMouseEvent::ROLL_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Over
		if (event.type() == flMouseEvent::MOUSE_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Out
		if (event.type() == flMouseEvent::MOUSE_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

			if (target == _sizingHandle) {
				stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicUIWindow::_mouseEventHandler);
			}

        }

		//Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

            //if(currentTarget == stage()) {
			if (target == stage()) {
				if (_dragEnabled) {
					_sizingHandle->x(_backWidth);
					_sizingHandle->y(_backHeight);
				}
			}
        }
    }
    
	//--------------------------------------------------------------
	void flBasicUIWindow::_uiEventHandler(flEvent& event) {
		ofLog() << "[flBasicUIWindow]_uiEventHandler(" << event.type() << ")";

		//flBasicDraggableObject::_uiEventHandler(event);

		//ボタン
		if (event.type() == flButtonEvent::ROLL_OVER) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());
		}
		if (event.type() == flButtonEvent::ROLL_OUT) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());
		}
		if (event.type() == flButtonEvent::MOUSE_OVER) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());
		}
		if (event.type() == flButtonEvent::MOUSE_OUT) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());
		}
		if (event.type() == flButtonEvent::MOUSE_DOWN) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());
		}
		if (event.type() == flButtonEvent::MOUSE_UP) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());
		}
		if (event.type() == flButtonEvent::CLICK) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());

			if (button == closeButton) {
				//if (stage()) stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_flBasicControllerMouseEventHandler);
				normalize();
				if (parent()) ((flDisplayObjectContainer*)parent())->removeChild(this);
				dispatchEvent(new flEvent(flEvent::CLOSE));
			}
		}
		if (event.type() == flButtonEvent::CHANGE) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());

			if (button == minimizeButton) {
				if (minimizeButton->selected()) {
					minimize();
				}
				else {
					normalize();
				}
			}

			if (button == maximizeButton) {
				if (maximizeButton->selected()) {
					maximize();
				}
				else {
					normalize();
				}
			}
		}

		//コンボボックス
		else if (event.type() == flComboBoxEvent::CHANGE) {
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
		else if (event.type() == flCheckBoxEvent::CHANGE) {
			flCheckBoxEvent& checkBoxEvent = *(flCheckBoxEvent*) &event;
			flCheckBox* checkBox = (flCheckBox*)(event.currentTarget());
		}

		//ラジオボタン
		else if (event.type() == flRadioButtonEvent::CHANGE) {
			flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
			flRadioButton* radio = (flRadioButton*)(event.currentTarget());
		}

		//ナンバーダイアラー
		else if (event.type() == flNumericDialerEvent::CHANGE) {
			flNumericDialerEvent& numberDialerEvent = *(flNumericDialerEvent*) &event;
			flNumericDialer* dialer = (flNumericDialer*)(event.currentTarget());
		}

		//2Dパッド
		else if (event.type() == flPadEvent::CHANGE) {
			flPadEvent& padEvent = *(flPadEvent*) &event;
			flPad2D* pad = (flPad2D*)(event.currentTarget());
		}

		//スライダー
		else if (event.type() == flSliderEvent::CHANGE) {
			flSliderEvent& sliderEvent = *(flSliderEvent*) &event;
			flSlider* slider = (flSlider*)(event.currentTarget());
		}

		//Vec2スライダー
		else if (event.type() == flVec2SliderEvent::CHANGE) {
			flVec2SliderEvent& sliderEvent = *(flVec2SliderEvent*) &event;
			flVec2Slider* slider = (flVec2Slider*)(event.currentTarget());
		}

		//Vec3スライダー
		else if (event.type() == flVec3SliderEvent::CHANGE) {
			flVec3SliderEvent& sliderEvent = *(flVec3SliderEvent*) &event;
			flVec3Slider* slider = (flVec3Slider*)(event.currentTarget());
		}

		//レンジスライダー
		else if (event.type() == flRangeSliderEvent::CHANGE) {
			flRangeSliderEvent& rangeSliderEvent = *(flRangeSliderEvent*) &event;
			flRangeSlider* slider = (flRangeSlider*)(event.currentTarget());
		}

		//カラースライダー
		else if (event.type() == flColorSliderEvent::CHANGE) {
			flColorSliderEvent& colorSliderEvent = *(flColorSliderEvent*) &event;
			flColorSlider* slider = (flColorSlider*)(event.currentTarget());
		}

		//ジョイスティック1D
		else if (event.type() == flJoyStick1Event::CHANGE) {
			flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
			flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
		}
		if (event.type() == flJoyStick1Event::UP) {
			flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
			flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
		}
		else if (event.type() == flJoyStick1Event::DOWN) {
			flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
			flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
		}
		else if (event.type() == flJoyStick1Event::LEFT) {
			flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
			flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
		}
		else if (event.type() == flJoyStick1Event::RIGHT) {
			flJoyStick1Event& joystickEvent = *(flJoyStick1Event*) &event;
			flJoyStick1* joystick = (flJoyStick1*)(event.currentTarget());
		}

		//ジョイスティック2D
		else if (event.type() == flJoyStick2Event::CHANGE) {
			flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
			flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
		}
		else if (event.type() == flJoyStick2Event::UP) {
			flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
			flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
		}
		else if (event.type() == flJoyStick2Event::DOWN) {
			flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
			flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
		}
		else if (event.type() == flJoyStick2Event::LEFT) {
			flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
			flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
		}
		else if (event.type() == flJoyStick2Event::RIGHT) {
			flJoyStick2Event& joystickEvent = *(flJoyStick2Event*) &event;
			flJoyStick2* joystick = (flJoyStick2*)(event.currentTarget());
		}
	}
}
