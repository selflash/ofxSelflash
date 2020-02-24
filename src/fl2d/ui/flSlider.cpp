#include "flSlider.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
    flSlider::flSlider(float trackWidth, float min, float max, float defaultValue) {
        //ofLog() << "[flSlider]flSlider()";

        //------------------------------------------
        _target = this;
        name("flSlider");

        //------------------------------------------
        _min = min;
        _max = max;
        if(_max > _min) {
            _range = _max - _min;
        } else {
            _range = _min - _max;
        }
        _value = defaultValue;
        //------------------------------------------

        //------------------------------------------
        _normalBarColor.setHex(flDefinition::UI_NORMAL_COLOR.getHex());
        _overBarColor.setHex(flDefinition::UI_OVER_COLOR.getHex());
        _activeBarColor.setHex(flDefinition::UI_ACTIVE_COLOR.getHex());
        _disableNormalBarColor.setHex(flDefinition::UI_DISABLE_NORMAL_COLOR.getHex());
        _disableActiveBarColor.setHex(flDefinition::UI_DISABLE_ACTIVE_COLOR.getHex());
        
        _trackWidth = trackWidth;
        if(_max > _min) {
            _barWidth = (_value -_min) / (_range / _trackWidth);
        } else {
            _barWidth = (_min - _value) / (_range / _trackWidth);
        }
        //------------------------------------------
        
        _percent = _barWidth / _trackWidth;

        flGraphics* g;
        
        //------------------------------------------
        track = new flSprite();
        track->name("flSlider.track");
        track->x(0);
        track->y(0);
        track->buttonMode(true);
        track->useHandCursor(true);
        track->addEventListener(flMouseEvent::ROLL_OVER, this, &flSlider::_mouseEventHandler);
        track->addEventListener(flMouseEvent::ROLL_OUT, this, &flSlider::_mouseEventHandler);
        track->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flSlider::_mouseEventHandler);
        addChild(track);
        //------------------------------------------

        //------------------------------------------
        bar = new flSprite();
        bar->name("flSlider.bar");
        bar->mouseEnabled(false);
        track->addChild(bar);
        //------------------------------------------

        //------------------------------------------
        thumb = new flSprite();
        thumb->name("flSlider.thumb");
        g = thumb->graphics();
        g->clear();
        g->beginFill(_normalBarColor.getHex());
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

        //------------------------------------------
        _valueText = new flTextField();
        _valueText->name("flSlider.velueText");
        _valueText->x(0);
        _valueText->width(_trackWidth);
        _valueText->autoSize(flTextFieldAutoSize::LEFT);
        _valueText->text(ofToString(_value));
        _valueText->mouseEnabled(false);
        _valueText->y(round(_trackHeight * 0.5 - _valueText->textHeight() * 0.5) - 0);
        addChild(_valueText);
        //------------------------------------------
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    flSlider::~flSlider() {
        //ofLog() << "[flSlider]~flSlider()";
        
        //------------------------------------------
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
        //------------------------------------------

        //------------------------------------------
        _floatParam = NULL;
        _intParam = NULL;
        //------------------------------------------
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flSlider::_setup() {
        //ofLog() << "[flSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    void flSlider::_update() {
        if(thumb->isMouseDown()) {
            _press();
        }
        
        _bChangedByOfParm["value"] = false;
    }
    
    //--------------------------------------------------------------
    void flSlider::_draw() {
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================

    //--------------------------------------------------------------
    void flSlider::label(flTextField* value) {
		_label = value; 
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
	}
    
    //--------------------------------------------------------------
    void flSlider::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        if (_enabled) {
            _setNormalColor();
        } else {
            _setDisableNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    bool flSlider::roundEnabled() { return _roundEnabled; }
    void flSlider::roundEnabled(bool value) {
        _roundEnabled = value;
        if(_roundEnabled) {
            _digit = 0;
        } else {
            _digit = 2;
        }
    }
    
    //--------------------------------------------------------------
    float flSlider::min() { return _min; }
    void flSlider::min(float value, bool dispatch) {
        _min = value;
        if(_max > _min) {
            _range = _max - _min;
        } else {
            _range = _min - _max;
        }
        
        _percent = _barWidth / _trackWidth;
        
        float preValue = _value;
        _value = _range * _percent + _min;
        if(_roundEnabled) _value = flmath::roundd(_range * _percent + _min);
        
        //------------------------------------------
        if(preValue != _value) {
            _changeValue(dispatch);
        
            if(!_bChangedByOfParm["value"]) {
                if(_floatParam != NULL) {
                    _bChangedByMyself["value"] = true;
                    _floatParam->set(_value);
                }
                else if(_intParam != NULL) {
                    _bChangedByMyself["value"] = true;
                    _intParam->set(_value);
                }
            }
        }
        //------------------------------------------
    }
    //--------------------------------------------------------------
    float flSlider::max() { return _max; }
    void flSlider::max(float value, bool dispatch) {
        _max = value;
        if(_max > _min) {
            _range = _max - _min;
        } else {
            _range = _min - _max;
        }
        
        _percent = _barWidth / _trackWidth;
        
        float preValue = _value;
        _value = _range * _percent + _min;
        if(_roundEnabled) _value = flmath::roundd(_range * _percent + _min);
        
        //------------------------------------------
        if(preValue != _value) {
            _changeValue(dispatch);
        
            if(!_bChangedByOfParm["value"]) {
                if(_floatParam != NULL) {
                    _bChangedByMyself["value"] = true;
                    _floatParam->set(_value);
                }
                else if(_intParam != NULL) {
                    _bChangedByMyself["value"] = true;
                    _intParam->set(_value);
                }
            }
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    float flSlider::value() { return _value; }
    void flSlider::value(float value, bool dispatch) {
        float preValue = _value;
        
        //------------------------------------------
        //Update value.
        _value = value;
        
        if(_roundEnabled) _value = flmath::roundd(_value);
        if(_max > _min) {
            if(_value < _min) _value = _min;
            if(_value > _max) _value = _max;
        } else {
            if(_value > _min) _value = _min;
            if(_value < _max) _value = _max;
        }
        //------------------------------------------
        
        //------------------------------------------
        if(_max > _min) {
            _barWidth = (_value -_min) / (_range / _trackWidth);
        } else {
            _barWidth = (_min - _value) / (_range / _trackWidth);
        }
        thumb->x(_barWidth - (_thumbWidth * 0.5));
        //------------------------------------------
        
        //------------------------------------------
        //Update color.
        if(track->isMouseDown() || thumb->isMouseDown()) {
            _setActiveColor();
        } else if(track->isMouseOver()) {
            _setTrackOverColor();
        } else if(thumb->isMouseOver()) {
            _setThumbOverColor();
        } else {
            _setNormalColor();
        }
        //------------------------------------------

        //------------------------------------------
        if(preValue != _value) {
            _changeValue(dispatch);
        
            if(!_bChangedByOfParm["value"]) {
                if(_floatParam != NULL) {
                    _bChangedByMyself["value"] = true;
                    _floatParam->set(_value);
                }
                else if(_intParam != NULL) {
                    _bChangedByMyself["value"] = true;
                    _intParam->set(_value);
                }
            }
        }
        //------------------------------------------        
    }
    
    //--------------------------------------------------------------
    int flSlider::barColor() { return _activeBarColor.getHex(); }
    void flSlider::barColor(int value) {
        _activeBarColor.setHex(value);
        _overBarColor = _activeBarColor;
        _disableActiveBarColor = _activeBarColor;
        
        if(track->isMouseDown() || thumb->isMouseDown()) {
            _setActiveColor();
        } else if(track->isMouseOver()) {
            _setTrackOverColor();
        } else if(thumb->isMouseOver()) {
            _setThumbOverColor();
        } else {
            _setNormalColor();
        }
    }
    void flSlider::barColor(int red, int green, int blue, int alpha) {
        _activeBarColor.r = red;
        _activeBarColor.g = green;
        _activeBarColor.b = blue;
        _activeBarColor.a = alpha;
        _overBarColor = _activeBarColor;
        _disableActiveBarColor = _activeBarColor;

        if(track->isMouseDown() || thumb->isMouseDown()) {
            _setActiveColor();
        } else if(track->isMouseOver()) {
            _setTrackOverColor();
        } else if(thumb->isMouseOver()) {
            _setThumbOverColor();
        } else {
            _setNormalColor();
        }
    }
    void flSlider::barColor(const ofColor& color) {
        _activeBarColor.r = color.r;
        _activeBarColor.g = color.g;
        _activeBarColor.b = color.b;
        _activeBarColor.a = color.a;
        _overBarColor = _activeBarColor;
        _disableActiveBarColor = _activeBarColor;

        if(track->isMouseDown() || thumb->isMouseDown()) {
            _setActiveColor();
        } else if(track->isMouseOver()) {
            _setTrackOverColor();
        } else if(thumb->isMouseOver()) {
            _setThumbOverColor();
        } else {
            _setNormalColor();
        }
    }
    void flSlider::barColor(const ofFloatColor& color) {
        _activeBarColor.r = color.r;
        _activeBarColor.g = color.g;
        _activeBarColor.b = color.b;
        _activeBarColor.a = color.a;
        _overBarColor = _activeBarColor;
        _disableActiveBarColor = _activeBarColor;

        if(track->isMouseDown() || thumb->isMouseDown()) {
            _setActiveColor();
        } else if(track->isMouseOver()) {
            _setTrackOverColor();
        } else if(thumb->isMouseOver()) {
            _setThumbOverColor();
        } else {
            _setNormalColor();
        }
    }

    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flSlider::_changeValue(bool dispatch) {
        _valueText->text(ofToString(_value, _digit));
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flSliderEvent* event = new flSliderEvent(flSliderEvent::CHANGE);
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flSlider::_trackOver() {
        if(track->isMouseDown()) return;
        if(thumb->isMouseDown()) return;

        _setTrackOverColor();
    }
    
    //--------------------------------------------------------------
    void flSlider::_thumbOver() {
        if(track->isMouseDown()) return;
        
        _setThumbOverColor();
    }

    //--------------------------------------------------------------
    void flSlider::_trackOut() {
        if(track->isMouseDown()) return;
        if(thumb->isMouseDown()) return;
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flSlider::_thumbOut() {
        if(track->isMouseDown()) return;
        if(thumb->isMouseDown()) return;
        
        if(track->isMouseOver()) {
            _setTrackOverColor();
        } else {
            _setNormalColor();
        }
    }

    //--------------------------------------------------------------
    void flSlider::_press() {
        float preValue = _value;

        //------------------------------------------
        float temp = mouseX() - _draggablePoint.x;
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
        } else {
            _value = _min - (_range * _percent);
        }
        if(_roundEnabled) _value = flmath::roundd(_value);
        
        _barWidth = thumb->x() + _thumbWidth * 0.5;
        //------------------------------------------
        
        //------------------------------------------
        _setActiveColor();
        //------------------------------------------
        
        //------------------------------------------
        if(preValue != _value) _changeValue(true);

        if(_floatParam != NULL) {
            _bChangedByMyself["value"] = true;
            _floatParam->set(_value);
        }
        else if(_intParam != NULL) {
            _bChangedByMyself["value"] = true;
            _intParam->set(_value);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flSlider::_release() {
        if(track->isMouseOver()) {
            _setTrackOverColor();
        } else {
            _setNormalColor();
        }
    }

    //--------------------------------------------------------------
    void flSlider::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_NORMAL_COLOR, _normalBarColor, 1);
        _drawBarGraphics(flDefinition::UI_LINE_NORMAL_COLOR, _activeBarColor, 1);
    }
    
    //--------------------------------------------------------------
    void flSlider::_setTrackOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawTrackGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_OVER_COLOR, _overBarColor, 1);
    }

    //--------------------------------------------------------------
    void flSlider::_setThumbOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_OVER_COLOR, _overBarColor, 1);
    }

    //--------------------------------------------------------------
    void flSlider::_setSelectedTrackOverColor() {
        
    }

    //--------------------------------------------------------------
    void flSlider::_setSelectedThumbOverColor() {
        
    }

    //--------------------------------------------------------------
    void flSlider::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);

        _drawTrackGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, _activeBarColor, 1);
    }
    
    //--------------------------------------------------------------
    void flSlider::_setDisableNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
        _drawTrackGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, _disableActiveBarColor, 1);
    }
    
    //--------------------------------------------------------------
    void flSlider::_setDisableActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
        _drawTrackGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
        _drawBarGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, _disableActiveBarColor, 1);
    }
    
    //--------------------------------------------------------------
    void flSlider::_drawTrackGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = track->graphics();
        g->clear();
        g->beginFill(0xff0000, 0.0);
//        g->drawRect(-10, 0, _trackWidth + 20, _trackHeight);
        g->drawRect(-6, 0, _trackWidth + 12, _trackHeight);
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex());
        g->drawRect(0, 0, _trackWidth, _trackHeight);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flSlider::_drawBarGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = bar->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        g->drawRect(0, 0, _barWidth, _trackHeight);
        g->endFill();
    }

    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flSlider::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flSlider]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flSlider]this          = " << this << "," << ((flDisplayObject*) this)->name();
//        ofLog() << "[flSlider]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flSlider]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == track) _trackOver();
            if(event.target() == thumb) _thumbOver();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == track) _trackOut();
            if(event.target() == thumb) _thumbOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(thumb->isMouseOver()) {
                if(event.target() == thumb) {
                    _draggablePoint.x = mouseX() - thumb->x() - _thumbWidth * 0.5;
                    _press();
                    if(stage()) {
                        stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flSlider::_mouseEventHandler);
                    }
                }
            } else {
                if(event.target() == track) {
                    _press();
                    if(stage()) {
                        stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flSlider::_mouseEventHandler);
                    }
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flSlider::_mouseEventHandler);
            }
            _release();
        }
    }
    
}
