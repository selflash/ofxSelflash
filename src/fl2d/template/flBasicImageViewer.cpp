#include "flBasicImageViewer.h"

namespace fl2d {

	//==============================================================
	// Constructor / Destructor
	//==============================================================

	//--------------------------------------------------------------
	flBasicImageViewer::flBasicImageViewer(flBitmap* bitmap, int w, int h) {
		//ofLog() << "[flBasicImageViewer]flBasicImageViewer()";

		_target = this;
		name("flBasicImageViewer");

		_title = "[flBasicImageViewer]";

		useHandCursor(true);

		_defaultImageWidth = w;
		_defaultImageHeight = h;
		_bitmap = bitmap;

		_dragEnabled = false;
	}

	//--------------------------------------------------------------
	flBasicImageViewer::~flBasicImageViewer() {
		ofLog() << "[flBasicImageViewer]~flBasicImageViewer()";

		_target = NULL;

		_bitmap = NULL;
	}

	//==============================================================
	// Setup / Update / Draw
	//==============================================================

	//--------------------------------------------------------------
	void flBasicImageViewer::_setup() {
		//ofLog() << "[flBasicImageViewer]_setup()";

		flBasicUIWindow::_setup();

		//addChildAt(_bitmap, getChildIndex(_sizingHandle));
		addChild(_bitmap);

		minimizeButton->visible(false);
		maximizeButton->visible(false);
		closeButton->visible(false);

		resize(_defaultImageWidth, _defaultImageHeight);
	}

	//--------------------------------------------------------------
	void flBasicImageViewer::_afterDraw() {
		//ofLog() << "[flBasicUIWindow]_afterDraw()";
		flBasicDraggableObject::_afterDraw();

		ofPushStyle();
		ofSetColor(255, 255, 255);
		ofDrawLine(0, 0, _backWidth, 0);
		ofDrawLine(_backWidth, 0, _backWidth, _backHeight);
		ofDrawLine(_backWidth, _backHeight, 0, _backHeight);
		ofDrawLine(0, _backHeight, 0, 0);
		ofPopStyle();
	}

	//==============================================================
	// Public Method
	//==============================================================

	//--------------------------------------------------------------
	void flBasicImageViewer::maximize() {
		if (_isMaximize) return;

		flBasicUIWindow::maximize();

		_updateGraphics(_backWidth, _backHeight);
	}

	//--------------------------------------------------------------
	void flBasicImageViewer::normalize() {
		if (!_isMinimize && !_isMaximize) return;

		flBasicUIWindow::normalize();

		_updateGraphics(_backWidth, _backHeight);
	}

	//--------------------------------------------------------------
	void flBasicImageViewer::resize(float w, float h) {
		flBasicUIWindow::resize(w, h);

		_updateGraphics(w, h);
	}

	//--------------------------------------------------------------
	bool flBasicImageViewer::active() { return _isActive; }
	void flBasicImageViewer::active(bool value) {
		//if (_bitmap->width() == 0.0 || _bitmap->height() == 0.0) return;

		if (_isActive == value) return;
		_isActive = value;

		if (_isActive) {
			dragEnabled(true);
			minimizeButton->visible(true);
			maximizeButton->visible(true);
			closeButton->visible(true);

			resize(_normalBackWidth * _scaleOnActive, _titleBarHeight + _normalBackHeight * _scaleOnActive);
		}
		else {
			dragEnabled(false);
			minimizeButton->visible(false);
			maximizeButton->visible(false);
			closeButton->visible(false);

			resize(_defaultImageWidth, _defaultImageHeight);
		}
	}

	//==============================================================
	// Protected / Private Method
	//==============================================================

	//--------------------------------------------------------------
	void flBasicImageViewer::_updateGraphics(float w, float h) {
		const float srcWidth = _defaultImageWidth;
		const float srcHeight = _defaultImageHeight;

		float dstWidth = 0.0;
		float dstHeight = 0.0;

		if (_isActive) {
			const float windowWidth = w;
			const float windowHeight = h - _titleBarHeight;

			flmath::mapImageSizeToWindowSize(srcWidth, srcHeight, windowWidth, windowHeight, dstWidth, dstHeight);

			_bitmap->width(dstWidth);
			_bitmap->height(dstHeight);

			_bitmap->x(windowWidth * 0.5 - dstWidth * 0.5);
			_bitmap->y(_titleBarHeight + (windowHeight * 0.5 - dstHeight * 0.5));
		}
		else {
			const float windowWidth = w;
			const float windowHeight = h;

			flmath::mapImageSizeToWindowSize(srcWidth, srcHeight, windowWidth, windowHeight, dstWidth, dstHeight);

			_bitmap->width(dstWidth);
			_bitmap->height(dstHeight);

			_bitmap->x(windowWidth * 0.5 - dstWidth * 0.5);
			_bitmap->y(windowHeight * 0.5 - dstHeight * 0.5);
		}
	}

	//==============================================================
	// Event Handler
	//==============================================================

	//--------------------------------------------------------------
	void flBasicImageViewer::_mouseEventHandler(flEvent& event) {
		//ofLog(OF_LOG_NOTICE) << "[flBasicImageViewer]_mouseEventHandler(" << event.type() << ")";
		//ofLog(OF_LOG_NOTICE) << "[flBasicImageViewer]this          = " << this;
		//ofLog(OF_LOG_NOTICE) << "[flBasicImageViewer]currentTarget = " << event.currentTarget();
		//ofLog(OF_LOG_NOTICE) << "[flBasicImageViewer]target        = " << event.target();
		
		flBasicUIWindow::_mouseEventHandler(event);

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
		if (event.type() == flMouseEvent::MOUSE_DOWN) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}

		//Mouse Up
		if (event.type() == flMouseEvent::MOUSE_UP) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();
		}
	}

	//--------------------------------------------------------------
	void flBasicImageViewer::_uiEventHandler(flEvent& event) {
		ofLog() << "[flBasicImageViewer]_uiEventHandler(" << event.type() << ")";

		flBasicUIWindow::_uiEventHandler(event);

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
		}
		if (event.type() == flButtonEvent::CHANGE) {
			flButtonEvent& buttonEvent = *(flButtonEvent*) &event;
			flButton* button = (flButton*)(event.currentTarget());
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
