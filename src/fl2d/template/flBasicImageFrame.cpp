#include "flBasicImageFrame.h"

namespace fl2d {

	//==============================================================
	// Constructor / Destructor
	//==============================================================

	//--------------------------------------------------------------
	flBasicImageFrame::flBasicImageFrame(flBitmap* bitmap, int w, int h) {
		ofLog() << "[flBasicImageFrame]flBasicImageFrame()";
		_target = this;

		name("flBasicImageFrame");

		//mouseChildren(false);
		useHandCursor(true);
		dragEnabled(false);

		addEventListener(flMouseEvent::ROLL_OVER, this, &flBasicImageFrame::_mouseEventHandler);
		addEventListener(flMouseEvent::ROLL_OUT, this, &flBasicImageFrame::_mouseEventHandler);
		addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicImageFrame::_mouseEventHandler);
		//addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicImageFrame::_mouseEventHandler);

		float marginLeft; float marginTop;
		float spacing; float lineSpacing;
		//--------------------------------------
		marginLeft = 5;
		marginTop = 5;
		spacing = 100;
		lineSpacing = 22;

		titleTf = new flTextField();
		titleTf->x(marginLeft + spacing * 0);
		titleTf->y(marginTop + lineSpacing * 0);
		titleTf->width(120);
		titleTf->textColor(0xffffff);
		titleTf->text("[Contoller]");
		titleTf->mouseEnabled(false);
		//titleTf->text("[" + title + "]");
		//addChild(titleTf);
		//--------------------------------------

		_mode = 0;

		//最小化ボタン
		minimizeButton = new flButton(18, 18);
		minimizeButton->y(marginTop);
		minimizeButton->labelText("-");
		minimizeButton->toggleEnabled(true);
		minimizeButton->visible(false);
		minimizeButton->addEventListener(flButtonEvent::CHANGE, this, &flBasicImageFrame::_uiEventHandler);
		addChild(minimizeButton);

		//閉じるボタン
		closeButton = new flButton(18, 18);
		closeButton->y(marginTop);
		closeButton->labelText("x");
		closeButton->visible(false);
		closeButton->addEventListener(flButtonEvent::MOUSE_DOWN, this, &flBasicImageFrame::_uiEventHandler);
		addChild(closeButton);

		_backWidth = 0;
		_backHeight = 0;

		_minBackWidth = 0;
		_minBackHeight = 18 + 10;

		_normalBackWidth = 0;
		_normalBackHeight = 0;

		_onTop = true;

		_dragEnabled = false;




		_defaultImageWidth = w;
		_defaultImageHeight = h;
		_bitmap = bitmap;
		addChild(_bitmap, 1, 1);


		_normalBackWidth = _defaultImageWidth + 2;
		_normalBackHeight = _defaultImageHeight + 2;

		flGraphics* g = graphics();
		g->clear();
		g->lineStyle(1, 0xffffff);
		g->beginFill(0x000000, 0.7);
		g->drawRect(0, 0, _normalBackWidth, _normalBackHeight);
		g->endFill();

		//_updateRect();
	}

	//--------------------------------------------------------------
	flBasicImageFrame::~flBasicImageFrame() {
		ofLog() << "[flBasicImageFrame]~flBasicImageFrame()";

		_target = NULL;

		removeEventListener(flMouseEvent::ROLL_OVER, this, &flBasicImageFrame::_mouseEventHandler);
		removeEventListener(flMouseEvent::ROLL_OUT, this, &flBasicImageFrame::_mouseEventHandler);
		removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicImageFrame::_mouseEventHandler);
		//removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);

		//最小化ボタン
		minimizeButton->removeEventListener(flButtonEvent::CHANGE, this, &flBasicImageFrame::_uiEventHandler);
		delete minimizeButton;
		minimizeButton = NULL;

		//閉じるボタン
		closeButton->removeEventListener(flButtonEvent::MOUSE_UP, this, &flBasicImageFrame::_uiEventHandler);
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

		_listeners.unsubscribeAll();

		_bitmap = NULL;
	}

	//==============================================================
	// Setup / Update / Draw
	//==============================================================

	//--------------------------------------------------------------
	void flBasicImageFrame::setup() {
		//Sprite::setup();

		_setup();

		//_updateRect();

		//float w = width();
		//minimizeButton->x(w - (18 + 5 + 18 + 5));
		////minimizeButton->y(4);

		//closeButton->x(w - (18 + 5));
		////closeButton->y(4);
	}

	//--------------------------------------------------------------
	void flBasicImageFrame::_setup() {
		ofLog() << "[flBasicImageFrame]_setup()";

		//_normalBackWidth = 380 + 350;
		//_normalBackHeight = 759 + 5;
		_minBackWidth = _normalBackWidth;
		_backWidth = _normalBackWidth;
		_backHeight = _normalBackHeight;

		//flGraphics* g;
		//g = graphics();
		//g->clear();
		//g->lineStyle(1, 0xffffff);
		//g->beginFill(0x000000, 0.7);
		//g->drawRect(0, 0, _backWidth, _backHeight);
		//g->endFill();

		float marginLeft; float marginTop;
		float spacing; float lineSpacing;
		flTextField* label = NULL;
		////--------------------------------------



	}

	//--------------------------------------------------------------
	//
	void flBasicImageFrame::_update() {
		//ofLog() << "[flBasicImageFrame]update()";


	}

	//--------------------------------------------------------------
	//
	void flBasicImageFrame::_draw() {
		//ofLog() << "[flBasicImageFrame]draw()";

		if (_mode == 0) return;

		//    ofDrawBitmapString(_status, 10, 170);
	}

	//==============================================================
	// Public Method
	//==============================================================

	//--------------------------------------------------------------
	bool flBasicImageFrame::active() { return _isActive; }

	//--------------------------------------------------------------
	void flBasicImageFrame::active(bool value) {
		//if (_bitmap->width() == 0.0 || _bitmap->height() == 0.0) return;

		if (_isActive == value) return;
		_isActive = value;

		dragEnabled(_isActive);

		if (_isActive) {
			//mouseChildren(true);

			_bitmap->scaleX(0.5);
			_bitmap->scaleY(0.5);
			addChild(_bitmap, 1, 1 + (22 + 5));

			int w = _bitmap->width();
			int h = _bitmap->height();

			flGraphics* g = graphics();
			g->clear();
			g->lineStyle(1, 0xffffff);
			g->beginFill(0x000000, 0.7);
			g->drawRect(0, 0, w + 2, h + 2 + (22 + 5));
			g->endFill();

			{
				_updateRect();

				float w = width();
				minimizeButton->x(w - (18 + 5 + 18 + 5));

				closeButton->x(w - (18 + 5));

				minimizeButton->visible(true);
				closeButton->visible(true);
			}
		}
		else {
			//mouseChildren(false);

			_bitmap->width(_defaultImageWidth);
			_bitmap->height(_defaultImageHeight);
			addChild(_bitmap, 1, 1);

			flGraphics* g = graphics();
			g->clear();
			g->lineStyle(1, 0xffffff);
			g->beginFill(0x000000, 0.7);
			g->drawRect(0, 0, _normalBackWidth, _normalBackHeight);
			g->endFill();

			minimizeButton->visible(false);
			closeButton->visible(false);
		}
	}

	//--------------------------------------------------------------
	void flBasicImageFrame::minimize() {
		if (_mode == 0) return;
		_mode = 0;
		minimizeButton->selected(true);

		//----------------------------------
		_backWidth = _minBackWidth;
		_backHeight = _minBackHeight;

		//flGraphics* g;
		//g = graphics();
		//g->clear();
		//g->lineStyle(1, 0xffffff);
		//g->beginFill(0x000000, 0.7);
		//g->drawRect(0, 0, _backWidth, _backHeight);
		//g->endFill();
		//----------------------------------

		//----------------------------------
		int i; int l;
		l = numChildren();
		for (i = 0; i < l; i++) {
			flDisplayObject* child = getChildAt(i);

			if (child == titleTf) continue;
			if (child == closeButton) continue;
			if (child == minimizeButton) continue;

			child->visible(false);
		}
		//    titleTf->visible(true);
		//    minimizeButton->visible(true);
		//    closeButton->visible(true);
		//----------------------------------
	}


	//--------------------------------------------------------------
	void flBasicImageFrame::normalize() {
		if (_mode == 1) return;
		_mode = 1;

	}

	//--------------------------------------------------------------
	void flBasicImageFrame::maximize() {
		if (_mode == 2) return;
		_mode = 2;

		minimizeButton->selected(false);

		//----------------------------------
		//_backWidth = _normalBackWidth;
		//_backHeight = _normalBackHeight;

		//flGraphics* g;
		//g = graphics();
		//g->clear();
		//g->lineStyle(1, 0xffffff);
		//g->beginFill(0x000000, 0.7);
		//g->drawRect(0, 0, _backWidth, _backHeight);
		//g->endFill();
		//----------------------------------

		//----------------------------------
		int i; int l;
		l = numChildren();
		for (i = 0; i < l; i++) {
			flDisplayObject* child = getChildAt(i);

			if (child == titleTf) continue;
			if (child == closeButton) continue;
			if (child == minimizeButton) continue;

			child->visible(true);
		}

		//if (parent()) ((flDisplayObjectContainer*)parent())->addChild(this);
		//----------------------------------
	}

	//--------------------------------------------------------------
	void flBasicImageFrame::resize(float w, float h) {

	}

	//==============================================================
	// Protected / Private Method
	//==============================================================

	//==============================================================
	// Event Handler
	//==============================================================

	//--------------------------------------------------------------
	void flBasicImageFrame::_mouseEventHandler(flEvent& event) {
		//ofLog() << "[flBasicImageFrame]_mouseEventHandler(" << event.type() << ")";
		//ofLog() << "[flBasicImageFrame]this          = " << this;
		//ofLog() << "[flBasicImageFrame]currentTarget = " << event.currentTarget();
		//ofLog() << "[flBasicImageFrame]target        = " << event.target();
			//Roll Over
		if (event.type() == flMouseEvent::ROLL_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			if (event.target() == this) {

			}
		}

		//Roll Out
		if (event.type() == flMouseEvent::ROLL_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			if (event.target() == this) {

			}
		}

		//Mouse Over
		if (event.type() == flMouseEvent::MOUSE_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			if (event.target() == this) {

			}
		}

		//Mouse Out
		if (event.type() == flMouseEvent::MOUSE_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			if (event.target() == this) {

			}
		}

		//Mouse Down
		if (event.type() == flMouseEvent::MOUSE_DOWN) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			if (event.target() == this) {
				if (_dragEnabled) {
					//if (_onTop) ((flDisplayObjectContainer*)parent())->addChild(this);
					startDrag();
					stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicImageFrame::_mouseEventHandler);
				}
			}
		}

		//Mouse Up
		if (event.type() == flMouseEvent::MOUSE_UP) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;

			//if(event.target() == this) ((DisplayObjectContainer*)parent())->addChild(this);
			if (event.target() == stage()) {
				stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicImageFrame::_mouseEventHandler);
				stopDrag();
			}
		}
	}

	//--------------------------------------------------------------
	void flBasicImageFrame::_uiEventHandler(flEvent& event) {
		//    ofLog() << "[flBasicImageFrame]_uiEventHandler(" << event.type();

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

			if (button == closeButton) {
				//((flDisplayObjectContainer*)parent())->removeChild(this);
				dispatchEvent(new flEvent(flEvent::CLOSE));
			}
		}
		if (event.type() == flButtonEvent::MOUSE_UP) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());
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
