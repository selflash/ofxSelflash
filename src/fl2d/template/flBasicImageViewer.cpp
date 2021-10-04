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

		//mouseChildren(false);
		useHandCursor(true);

		addEventListener(flMouseEvent::ROLL_OVER, this, &flBasicImageViewer::_mouseEventHandler);
		addEventListener(flMouseEvent::ROLL_OUT, this, &flBasicImageViewer::_mouseEventHandler);
		addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicImageViewer::_mouseEventHandler);
		//addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicImageViewer::_mouseEventHandler);

		float marginLeft; float marginTop;
		float spacing; float lineSpacing;
		//--------------------------------------
		marginLeft = 5;
		marginTop = 5;
		spacing = 100;
		lineSpacing = 22;

		//titleTf = new flTextField();
		//titleTf->x(marginLeft + spacing * 0);
		//titleTf->y(marginTop + lineSpacing * 0);
		//titleTf->width(120);
		//titleTf->textColor(0xffffff);
		//titleTf->text("[Contoller]");
		//titleTf->mouseEnabled(false);
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
		minimizeButton->addEventListener(flButtonEvent::CHANGE, this, &flBasicImageViewer::_uiEventHandler);
		addChild(minimizeButton);

		//閉じるボタン
		closeButton = new flButton(18, 18);
		closeButton->y(marginTop);
		closeButton->labelText("x");
		closeButton->visible(false);
		closeButton->addEventListener(flButtonEvent::MOUSE_DOWN, this, &flBasicImageViewer::_uiEventHandler);
		addChild(closeButton);

		_backWidth = 0;
		_backHeight = 0;

		_minBackWidth = 0;
		_minBackHeight = 18 + 10;

		_normalBackWidth = 0;
		_normalBackHeight = 0;




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

		{
			_rightBottomCorner = new flBasicDraggableObject();
			_rightBottomCorner->x(0);
			_rightBottomCorner->y(0);
			_rightBottomCorner->visible(false);
			_rightBottomCorner->dragEnabled(true);
			_rightBottomCorner->useHandCursor(true);
			_rightBottomCorner->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicImageViewer::_mouseEventHandler);
			addChild(_rightBottomCorner);

			flGraphics* g = _rightBottomCorner->graphics();
			g->clear();
			g->beginFill(0xff0000, 0.0);
			g->drawCircle(0, 0, 12);
			g->endFill();
		}

		_dragEnabled = false;
	}

	//--------------------------------------------------------------
	flBasicImageViewer::~flBasicImageViewer() {
		ofLog() << "[flBasicImageViewer]~flBasicImageViewer()";

		_target = NULL;

		_dragEnabled = false;

		removeEventListener(flMouseEvent::ROLL_OVER, this, &flBasicImageViewer::_mouseEventHandler);
		removeEventListener(flMouseEvent::ROLL_OUT, this, &flBasicImageViewer::_mouseEventHandler);
		removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flBasicImageViewer::_mouseEventHandler);
		//removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicController::_mouseEventHandler);

		//最小化ボタン
		minimizeButton->removeEventListener(flButtonEvent::CHANGE, this, &flBasicImageViewer::_uiEventHandler);
		delete minimizeButton;
		minimizeButton = NULL;

		//閉じるボタン
		closeButton->removeEventListener(flButtonEvent::MOUSE_UP, this, &flBasicImageViewer::_uiEventHandler);
		delete closeButton;
		closeButton = NULL;

		_backWidth = 0;
		_backHeight = 0;

		_minBackWidth = 0;
		_minBackHeight = 0;

		_normalBackWidth = 0;
		_normalBackHeight = 0;

		_listeners.unsubscribeAll();

		_bitmap = NULL;

		delete _rightBottomCorner;
		_rightBottomCorner = NULL;

		_scaleOnActive = 0;
	}

	//==============================================================
	// Setup / Update / Draw
	//==============================================================

	//--------------------------------------------------------------
	void flBasicImageViewer::setup() {
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
	void flBasicImageViewer::_setup() {
		ofLog() << "[flBasicImageViewer]_setup()";

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

		_rightBottomCorner->x(_backWidth);
		_rightBottomCorner->y(_backHeight);
	}

	//--------------------------------------------------------------
	//
	void flBasicImageViewer::_update() {
		//ofLog() << "[flBasicImageViewer]update()";

		int dx = abs(_rightBottomCorner->x() - _rightBottomCorner->startDragPoint().x);
		int dy = abs(_rightBottomCorner->y() - _rightBottomCorner->startDragPoint().y);
		if (dx == 0 && dy == 0) return;

		int x = _rightBottomCorner->x();
		int y = _rightBottomCorner->y();
		_updateGraphics(x, y);
	}

	//--------------------------------------------------------------
	//
	void flBasicImageViewer::_draw() {
		//ofLog() << "[flBasicImageViewer]draw()";

		if (_mode == 0) return;

		//    ofDrawBitmapString(_status, 10, 170);
	}

	//==============================================================
	// Public Method
	//==============================================================

	//--------------------------------------------------------------
	bool flBasicImageViewer::active() { return _isActive; }

	//--------------------------------------------------------------
	void flBasicImageViewer::_updateGraphics(int x, int y) {

		if (_isActive) {
			int borderWidth = 1;
			int imgW = x - borderWidth * 2;
			int imgH = y - borderWidth * 2 - (22 + 5);

			//_rightBottomCorner

			//if (dx > dy) {
			//	w = (_defaultImageWidth / _defaultImageHeight) * h;
			//}
			//else if (dx < dy) {
			//	h = (_defaultImageHeight / _defaultImageWidth) * w;
			//}

			//if (x > y) {
			//	//縦幅に横幅を合わせる
			//	w = (_defaultImageWidth / _defaultImageHeight) * h;
			//	if (x < w) {
			//		w = x - borderWidth * 2;
			//		//横幅に縦幅を合わせる
			//		h = (_defaultImageHeight / _defaultImageWidth) * w;
			//	}
			//}
			//else if (x < y) {
			//	//横幅に縦幅を合わせる
			//	h = (_defaultImageHeight / _defaultImageWidth) * w;
			//}

			//if (dx > dy) {
			//	//横幅に縦幅を合わせる
			//	h = (_defaultImageHeight / _defaultImageWidth) * w;
			//	//if (y < h) {
			//	//	h = y - borderWidth * 2 - (22 + 5);
			//	//	//縦幅に横幅を合わせる
			//	//	w = (_defaultImageWidth / _defaultImageHeight) * h;
			//	//}
			//}
			//else if (dx < dy) {
			//	//縦幅に横幅を合わせる
			//	w = (_defaultImageWidth / _defaultImageHeight) * h;
			//	//if (x < w) {
			//	//	w = x - borderWidth * 2;
			//	//	//横幅に縦幅を合わせる
			//	//	h = (_defaultImageHeight / _defaultImageWidth) * w;
			//	//}
			//}
			
			if (_defaultImageWidth > _defaultImageHeight) {
				//横幅に縦幅を合わせる
				imgH = (_defaultImageHeight / _defaultImageWidth) * imgW;
			}
			else {
				//縦幅に横幅を合わせる
				imgW = (_defaultImageWidth / _defaultImageHeight) * imgH;
			}
			_bitmap->width(imgW);
			_bitmap->height(imgH);

			_backWidth = imgW + borderWidth * 2;
			_backHeight = (22 + 5) + imgH + borderWidth * 2;

			flGraphics* g = graphics();
			g->clear();
			g->lineStyle(1, 0xffffff);
			g->beginFill(0x000000, 0.7);
			g->drawRect(0, 0, _backWidth, _backHeight);
			g->endFill();

			minimizeButton->x(_backWidth - (18 + 5 + 18 + 5));

			closeButton->x(_backWidth - (18 + 5));
		}
	}

	//--------------------------------------------------------------
	void flBasicImageViewer::active(bool value) {
		//if (_bitmap->width() == 0.0 || _bitmap->height() == 0.0) return;

		if (_isActive == value) return;
		_isActive = value;

		dragEnabled(_isActive);

		if (_isActive) {
			//_backWidth = _bitmap->width() + 2;
			//_backHeight = (22 + 5) + _bitmap->height() + 2;

			//_bitmap->x(1);
			_bitmap->y(1 + (22 + 5));

			//minimizeButton->x(_backWidth - (18 + 5 + 18 + 5));
			minimizeButton->visible(true);

			//closeButton->x(_backWidth - (18 + 5));
			closeButton->visible(true);

			_backHeight = _bitmap->y() + _bitmap->height() + 1;

			_rightBottomCorner->x(_backWidth * _scaleOnActive);
			_rightBottomCorner->y(_backHeight * _scaleOnActive);
			_rightBottomCorner->visible(true);

			int x = _rightBottomCorner->x();
			int y = _rightBottomCorner->y();
			_updateGraphics(x, y);
		}
		else {
			//_bitmap->x(1);
			_bitmap->y(1);

			_bitmap->width(_defaultImageWidth);
			_bitmap->height(_defaultImageHeight);

			_backWidth = _defaultImageWidth + 2;
			_backHeight = _defaultImageHeight + 2;

			minimizeButton->visible(false);
			closeButton->visible(false);

			_rightBottomCorner->x(_backWidth);
			_rightBottomCorner->y(_backHeight);
			_rightBottomCorner->visible(false);

			flGraphics* g = graphics();
			g->clear();
			g->lineStyle(1, 0xffffff);
			g->beginFill(0x000000, 0.7);
			g->drawRect(0, 0, _backWidth, _backHeight);
			g->endFill();
		}
	}

	//--------------------------------------------------------------
	void flBasicImageViewer::minimize() {
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

			//if (child == titleTf) continue;
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
	void flBasicImageViewer::normalize() {
		if (_mode == 1) return;
		_mode = 1;

	}

	//--------------------------------------------------------------
	void flBasicImageViewer::maximize() {
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

			//if (child == titleTf) continue;
			if (child == closeButton) continue;
			if (child == minimizeButton) continue;

			child->visible(true);
		}

		//if (parent()) ((flDisplayObjectContainer*)parent())->addChild(this);
		//----------------------------------
	}

	//--------------------------------------------------------------
	void flBasicImageViewer::resize(float w, float h) {

	}

	//==============================================================
	// Protected / Private Method
	//==============================================================

	//==============================================================
	// Event Handler
	//==============================================================

	//--------------------------------------------------------------
	void flBasicImageViewer::_mouseEventHandler(flEvent& event) {
		//ofLog(OF_LOG_NOTICE) << "[flBasicImageViewer]_mouseEventHandler(" << event.type() << ")";
		//ofLog(OF_LOG_NOTICE) << "[flBasicImageViewer]this          = " << this;
		//ofLog(OF_LOG_NOTICE) << "[flBasicImageViewer]currentTarget = " << event.currentTarget();
		//ofLog(OF_LOG_NOTICE) << "[flBasicImageViewer]target        = " << event.target();
		
		//flBasicDraggableObject::_mouseEventHandler(event);

		//Roll Over
		if (event.type() == flMouseEvent::ROLL_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

			if (target == this) {

			}
		}

		//Roll Out
		if (event.type() == flMouseEvent::ROLL_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

			if (target == this) {

			}
		}

		//Mouse Over
		if (event.type() == flMouseEvent::MOUSE_OVER) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

			if (target == this) {

			}
		}

		//Mouse Out
		if (event.type() == flMouseEvent::MOUSE_OUT) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

			if (target == this) {

			}
		}

		//Mouse Down
		if (event.type() == flMouseEvent::MOUSE_DOWN) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

			if (target == (hitArea() != NULL ? hitArea() : this)) {
				if (_dragEnabled) {
					((flDisplayObjectContainer*)parent())->addChild(this);
					startDrag();
					stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicImageViewer::_mouseEventHandler);
				}
			}

			if (target == _rightBottomCorner) {
				stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flBasicImageViewer::_mouseEventHandler);
			}
		}

		//Mouse Up
		if (event.type() == flMouseEvent::MOUSE_UP) {
			flMouseEvent& mouseEvent = *(flMouseEvent*) &event;
			void* target = event.target();
			void* currentTarget = event.currentTarget();

			//if(event.target() == this) ((DisplayObjectContainer*)parent())->addChild(this);
			if (target == stage()) {
				stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flBasicImageViewer::_mouseEventHandler);
				stopDrag();

				_rightBottomCorner->x(_backWidth);
				_rightBottomCorner->y(_backHeight);
			}
		}
	}

	//--------------------------------------------------------------
	void flBasicImageViewer::_uiEventHandler(flEvent& event) {
		//    ofLog() << "[flBasicImageViewer]_uiEventHandler(" << event.type();

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
