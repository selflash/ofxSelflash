#include "flSlider.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flSlider::flSlider(float trackWidth, float min, float max, float defaultValue) {
        //cout << "[flSlider]flSlider()" << endl;
        
        //------------------------------------------
        _target = this;
        name("flSlider");
        
        _labelNormalColor = flDefinition::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = flDefinition::UI_LABEL_OVER_COLOR;
        _labelActiveColor = flDefinition::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = flDefinition::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(flDefinition::UI_LINE_COLOR);
		_deactiveLineColor.setHex(flDefinition::UI_DEACTIVE_LINE_COLOR);
		_normalColor.setHex(flDefinition::UI_NORMAL_COLOR);
        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
		_deactiveColor.setHex(flDefinition::UI_DEACTIVE_COLOR);

        _label = NULL;
        
        _min = min;
        _max = max;
        //        _range = _max - _min;
        if(_max > _min) {
            _range = _max - _min;
        } else {
            _range = _min - _max;
        }
        _value = defaultValue;
        
        _trackWidth = trackWidth;
        _trackHeight = 18;
        _thumbWidth = 20;
        //        _barWidth = (_value -_min) / (_range / _trackWidth);
        if(_max > _min) {
            _barWidth = (_value -_min) / (_range / _trackWidth);
        } else {
            _barWidth = (_min - _value) / (_range / _trackWidth);
        }
        _roundEnabled = false;
        //------------------------------------------
        
        flGraphics* g;
        
        //------------------------------------------
        //バーとつまみのコンテナ
        track = new flSprite();
        _drawTrackGraphics(_lineColor, _normalColor, 1);
        track->x(0);
        track->y(0);
        track->buttonMode(true);
        track->addEventListener(flMouseEvent::ROLL_OVER, this, &flSlider::_mouseEventHandler);
        track->addEventListener(flMouseEvent::ROLL_OUT, this, &flSlider::_mouseEventHandler);
        track->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flSlider::_mouseEventHandler);
        addChild(track);
        
        //------------------------------------------
        //バー
        bar = new flSprite();
        _drawBarGraphics(_lineColor, _activeColor, 1);
        bar->mouseEnabled(false);
        track->addChild(bar);
        
        //つまみ
        thumb = new flSprite();
        g = thumb->graphics();
        g->clear();
        g->beginFill(_labelNormalColor);
        g->drawRect(0, 0, 20, _trackHeight);
        g->endFill();
        thumb->x(_barWidth - (_thumbWidth * 0.5));
        thumb->y(0);
        thumb->alpha(0);
        thumb->useHandCursor(true);
        thumb->addEventListener(flMouseEvent::ROLL_OVER, this, &flSlider::_mouseEventHandler);
        thumb->addEventListener(flMouseEvent::ROLL_OUT, this, &flSlider::_mouseEventHandler);
        thumb->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flSlider::_mouseEventHandler);
        track->addChild(thumb);
        
        //------------------------------------------
        _valueText = new flTextField();
        _valueText->x(0);
        _valueText->width(_trackWidth);
        _valueText->autoSize(flTextFieldAutoSize::LEFT);
        _valueText->textColor(_labelNormalColor);
        _valueText->text(ofToString(_value));
        _valueText->mouseEnabled(false);
        _valueText->visible(false);
        _valueText->y(_trackHeight * 0.5 - _valueText->textHeight() * 0.5);
        addChild(_valueText);
        //------------------------------------------
        
        _draggablePoint = new ofPoint(0, 0);
        
        //        value(defaultValue, false);

		_enabled = true;
    }
    
    //--------------------------------------------------------------
    //
    flSlider::~flSlider() {
        //cout << "[flSlider]~flSlider()" << endl;
        
        _label = NULL;
        
        track->removeEventListener(flMouseEvent::ROLL_OVER, this, &flSlider::_mouseEventHandler);
        track->removeEventListener(flMouseEvent::ROLL_OUT, this, &flSlider::_mouseEventHandler);
        track->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flSlider::_mouseEventHandler);
        delete track;
        track = NULL;
        
        delete bar;
        bar = NULL;
        
        thumb->removeEventListener(flMouseEvent::ROLL_OVER, this, &flSlider::_mouseEventHandler);
        thumb->removeEventListener(flMouseEvent::ROLL_OUT, this, &flSlider::_mouseEventHandler);
        thumb->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flSlider::_mouseEventHandler);
        delete thumb;
        thumb = NULL;
        
        delete _valueText;
        _valueText = NULL;
        
        delete _draggablePoint;
        _draggablePoint = NULL;

		_enabled = false;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flSlider::_setup() {
        //cout << "[flSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    //
    void flSlider::_update() {
        if(thumb->isMouseDown()) {
            //------------------------------------------
            float temp = mouseX() - _draggablePoint->x;
            if(temp < 0) temp = 0;
            if(temp > _trackWidth) temp = _trackWidth;
            _percent = temp / _trackWidth;
            //------------------------------------------
            //------------------------------------------
            thumb->x(temp - _thumbWidth * 0.5);
            //------------------------------------------
            //------------------------------------------
            if(_max > _min) {
                _value = (_range * _percent) + _min;
                if(_roundEnabled) _value = flmath::roundd((_range * _percent) + _min);
            } else {
                _value = _min - (_range * _percent);
                if(_roundEnabled) _value = flmath::roundd(_min - (_range * _percent));
            }
            _valueText->text(ofToString(_value));
            //------------------------------------------
            //------------------------------------------
            _barWidth = thumb->x() + _thumbWidth * 0.5;
            _drawBarGraphics(_overColor, _activeColor, 1);
            //------------------------------------------
            
            //------------------------------------------
            //イベント
            flSliderEvent* event = new flSliderEvent(flSliderEvent::CHANGE);
            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
            //------------------------------------------
        }
    }
    
    //--------------------------------------------------------------
    //
    void flSlider::_draw() {
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flTextField* flSlider::label() { return _label; }
    void flSlider::label(flTextField* value) { 
		_label = value; 
		if (_label != NULL) {
			if (_enabled) {
				_label->textColor(_labelNormalColor);
			}
			else {
				_label->textColor(_labelDeactiveColor);
			}
		}
	}
    
    //--------------------------------------------------------------
    //
    void flSlider::textColor(int color) {
        _valueText->textColor(color);
    }
    
    //--------------------------------------------------------------
    //
    float flSlider::min() { return _min; }
    void flSlider::min(float value, bool dispatch) {
        _min = value;
        //        _range = _max - _min;
        if(_max > _min) {
            _range = _max - _min;
        } else {
            _range = _min - _max;
        }
        
        _percent = _barWidth / _trackWidth;
        _value = _range * _percent + _min;
        if(_roundEnabled) _value = flmath::roundd(_range * _percent + _min);
        
        _valueText->text(ofToString(_value));
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flSliderEvent* event = new flSliderEvent(flSliderEvent::CHANGE);
            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    float flSlider::max() { return _max; }
    void flSlider::max(float value, bool dispatch) {
        _max = value;
        //        _range = _max - _min;
        if(_max > _min) {
            _range = _max - _min;
        } else {
            _range = _min - _max;
        }
        
        _percent = _barWidth / _trackWidth;
        _value = _range * _percent + _min;
        if(_roundEnabled) _value = flmath::roundd(_range * _percent + _min);
        
        _valueText->text(ofToString(_value));
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flSliderEvent* event = new flSliderEvent(flSliderEvent::CHANGE);
            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    float flSlider::value() { return _value; }
    void flSlider::value(float value, bool dispatch) {
        
        //------------------------------------------
        _value = value;
        
        if(_roundEnabled) _value = flmath::roundd(_value);
        //        if(_value < _min) _value = _min;
        //        if(_value > _max) _value = _max;
        if(_max > _min) {
            if(_value < _min) _value = _min;
            if(_value > _max) _value = _max;
        } else {
            if(_value > _min) _value = _min;
            if(_value < _max) _value = _max;
        }
        
        _valueText->text(ofToString(_value));
        //------------------------------------------
        //------------------------------------------
        if(_max > _min) {
            _barWidth = (_value -_min) / (_range / _trackWidth);
        } else {
            _barWidth = (_min - _value) / (_range / _trackWidth);
        }
        //        _barWidth = (_min - _value) / (_range / _trackWidth);
        //        _barWidth = (_value - _min) / (_range / _trackWidth);
        //        _barWidth = _value / (_range / _trackWidth);
		if (_enabled) {
			_drawBarGraphics(_lineColor, _activeColor);
		}
		else {
			_drawBarGraphics(_deactiveLineColor, _deactiveColor);
		}
        //------------------------------------------
        //------------------------------------------
        thumb->x(_barWidth - (_thumbWidth * 0.5));
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flSliderEvent* event = new flSliderEvent(flSliderEvent::CHANGE);
            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    int flSlider::barColor() { return _activeColor.getHex(); }
    void flSlider::barColor(int value) {
        _activeColor.setHex(value);
        
        if(thumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    void flSlider::barColor(int red, int green, int blue, int alpha) {
        _activeColor.r = red;
        _activeColor.g = green;
        _activeColor.b = blue;
        _activeColor.a = alpha;
        
        if(thumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    void flSlider::barColor(const ofColor& color) {
        _activeColor.r = color.r;
        _activeColor.g = color.g;
        _activeColor.b = color.b;
        _activeColor.a = color.a;
        
        if(thumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    void flSlider::barColor(const ofFloatColor& color) {
        _activeColor.r = color.r;
        _activeColor.g = color.g;
        _activeColor.b = color.b;
        _activeColor.a = color.a;
        
        if(thumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    
    //--------------------------------------------------------------
    //
    bool flSlider::roundEnabled() { return _roundEnabled; }
    void flSlider::roundEnabled(bool value) { _roundEnabled = value; }

	//--------------------------------------------------------------
//
	bool flSlider::enabled() { return _enabled; }
	void flSlider::enabled(bool value) {
		_enabled = value;
		mouseEnabled(_enabled);
		mouseChildren(_enabled);

		if (_label != NULL) {
			if (_enabled) {
				_label->textColor(_labelNormalColor);
			}
			else {
				_label->textColor(_labelDeactiveColor);
			}
		}

		//バー
		if (_enabled) {
			_drawTrackGraphics(_lineColor, _normalColor, 1);
			_drawBarGraphics(_lineColor, _activeColor, 1);
		}
		else {
			_drawTrackGraphics(_deactiveLineColor, _normalColor, 1);
			_drawBarGraphics(_deactiveLineColor, _deactiveColor, 1);
		}
	}
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flSlider::_drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        flGraphics* g;
        g = track->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        //        g->drawRect(-10, 0, _trackWidth + 20, _trackHeight);
        g->drawRect(-5, 0, _trackWidth + 10, _trackHeight);
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex());
        g->drawRect(0, 0, _trackWidth, _trackHeight);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void flSlider::_drawBarGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        flGraphics* g;
        g = bar->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a);
        g->drawRect(0, 0, _barWidth, _trackHeight);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    //
    void flSlider::_trackOver() {
        if(track->isMouseDown()) return;
        if(thumb->isMouseDown()) return;
        
        //------------------------------------------
        _drawTrackGraphics(_overColor, _normalColor, 1);
        //------------------------------------------
        //------------------------------------------
        _drawBarGraphics(_overColor, _activeColor, 1);
        //------------------------------------------
        //------------------------------------------
        _valueText->textColor(_labelNormalColor);
        _valueText->visible(true);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flSlider::_trackOut() {
        if(track->isMouseDown()) return;
        if(thumb->isMouseDown()) return;
        
        //------------------------------------------
        _drawTrackGraphics(_lineColor, _normalColor, 1);
        //------------------------------------------
        //------------------------------------------
        _drawBarGraphics(_lineColor, _activeColor, 1);
        //------------------------------------------
        
        //------------------------------------------
        _valueText->visible(false);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flSlider::_trackPress() {
        //------------------------------------------
        float temp = mouseX() - _draggablePoint->x;
        if(temp < 0) temp = 0;
        if(temp > _trackWidth) temp = _trackWidth;
        _percent = temp / _trackWidth;
        //------------------------------------------
        //------------------------------------------
        thumb->x(temp - _thumbWidth * 0.5);
        //------------------------------------------
        //------------------------------------------
        //        _value = _range * _percent + _min;
        //        if(_roundEnabled) _value = MathUtil::roundd(_range * _percent + _min);
        if(_max > _min) {
            _value = (_range * _percent) + _min;
            if(_roundEnabled) _value = flmath::roundd((_range * _percent) + _min);
        } else {
            _value = _min - (_range * _percent);
            if(_roundEnabled) _value = flmath::roundd(_min - (_range * _percent));
        }
        _valueText->text(ofToString(_value));
        //------------------------------------------
        
        //------------------------------------------
        _barWidth = thumb->x() + _thumbWidth * 0.5;
        _drawBarGraphics(_overColor, _activeColor, 1);
        //------------------------------------------
        
        //------------------------------------------
        _valueText->textColor(0x999999);
        //------------------------------------------
        //------------------------------------------
        //イベント
        flSliderEvent* event = new flSliderEvent(flSliderEvent::CHANGE);
        event->_target = this;
        event->data<float>(_value);
        dispatchEvent(event);
        //------------------------------------------    
    }
    //--------------------------------------------------------------
    //
    void flSlider::_trackRelease() {
        
        if(track->isMouseOver()) {
            _drawTrackGraphics(_overColor, _normalColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _normalColor, 1);
        }
        
        //------------------------------------------
        _valueText->textColor(_labelNormalColor);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flSlider::_thumbOver() {
        if(track->isMouseDown()) return;
        
        //------------------------------------------
        _drawBarGraphics(_overColor, _activeColor, 1);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flSlider::_thumbOut() {
        if(track->isMouseDown()) return;
        if(track->isMouseOver()) return;
        
        _trackOut();
        
        //------------------------------------------
        _drawBarGraphics(_lineColor, _activeColor, 1);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flSlider::_thumbPress() {
        _draggablePoint->x = mouseX() - thumb->x() - _thumbWidth * 0.5;
        //------------------------------------------
        _valueText->textColor(0x999999);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flSlider::_thumbRelease() {
        //cout << "[flSlider]_thumbRelease()" << endl;
        
        if(thumb->isMouseOver() || track->isMouseOver()) {
            //------------------------------------------
            _drawTrackGraphics(_overColor, _normalColor, 1);
            //------------------------------------------
            //------------------------------------------
            _drawBarGraphics(_overColor, _activeColor, 1);
            //------------------------------------------
            
            _valueText->textColor(_labelNormalColor);
        } else {
            //------------------------------------------
            _drawTrackGraphics(_lineColor, _normalColor, 1);
            //------------------------------------------
            //------------------------------------------
            _drawBarGraphics(_lineColor, _activeColor, 1);
            //------------------------------------------
            
            _valueText->visible(false);
        }
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flSlider::_mouseEventHandler(flEvent& event) {
        //        cout << "[flSlider]_mouseEventHandler(" << event.type() << ")" << endl;
        //        cout << "[flSlider]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //        cout << "[flSlider]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //        cout << "[flSlider]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        //ROLL OVER
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == track) _trackOver();
            if(event.target() == thumb) _thumbOver();
        }
        
        //ROLL OUT
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == track) _trackOut();
            if(event.target() == thumb) _thumbOut();
        }
        
        //MOUSE DOWN
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == track) _trackPress();
            if(event.target() == thumb) _thumbPress();
            stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flSlider::_mouseEventHandler);
        }
        
        //MOUSE UP
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(event.currentTarget() == stage()) {
                _thumbRelease();
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flSlider::_mouseEventHandler);
            }
        }
    }
    
}
