#include "Slider.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Slider::Slider(float trackWidth, float min, float max, float defaultValue) {
        //cout << "[Slider]Slider()" << endl;
        
        //------------------------------------------
        _target = this;
        name("Slider");
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(FlashConfig::UI_LINE_COLOR);
        _normalColor.setHex(FlashConfig::UI_NORMAL_COLOR);
        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);
        
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
        
        Graphics* g;
        
        //------------------------------------------
        //バーとつまみのコンテナ
        track = new Sprite();
        _drawTrackGraphics(_lineColor, _normalColor, 1);
        track->x(0);
        track->y(0);
        track->buttonMode(true);
        track->addEventListener(MouseEvent::ROLL_OVER, this, &Slider::_mouseEventHandler);
        track->addEventListener(MouseEvent::ROLL_OUT, this, &Slider::_mouseEventHandler);
        track->addEventListener(MouseEvent::MOUSE_DOWN, this, &Slider::_mouseEventHandler);
        addChild(track);
        
        //------------------------------------------
        //バー
        bar = new Sprite();
        _drawBarGraphics(_lineColor, _activeColor, 1);
        bar->mouseEnabled(false);
        track->addChild(bar);
        
        //つまみ
        thumb = new Sprite();
        g = thumb->graphics();
        g->clear();
        g->beginFill(_labelNormalColor);
        g->drawRect(0, 0, 20, _trackHeight);
        g->endFill();
        thumb->x(_barWidth - (_thumbWidth * 0.5));
        thumb->y(0);
        thumb->alpha(0);
        thumb->useHandCursor(true);
        thumb->addEventListener(MouseEvent::ROLL_OVER, this, &Slider::_mouseEventHandler);
        thumb->addEventListener(MouseEvent::ROLL_OUT, this, &Slider::_mouseEventHandler);
        thumb->addEventListener(MouseEvent::MOUSE_DOWN, this, &Slider::_mouseEventHandler);
        track->addChild(thumb);

        //------------------------------------------
        _valueText = new TextField();
        _valueText->x(0);
        _valueText->width(_trackWidth);
        _valueText->autoSize(TextFieldAutoSize::LEFT);
        _valueText->textColor(_labelNormalColor);
        _valueText->text(ofToString(_value));
        _valueText->mouseEnabled(false);
        _valueText->visible(false);
        _valueText->y(_trackHeight * 0.5 - _valueText->textHeight() * 0.5);
        addChild(_valueText);
        //------------------------------------------
        
        _draggablePoint = new ofPoint(0, 0);
        
//        value(defaultValue, false);
    }

    //--------------------------------------------------------------
    //
    Slider::~Slider() {
        //cout << "[Slider]~Slider()" << endl;
        
        _label = NULL;

        track->removeEventListener(MouseEvent::ROLL_OVER, &Slider::_mouseEventHandler);
        track->removeEventListener(MouseEvent::ROLL_OUT, &Slider::_mouseEventHandler);
        track->removeEventListener(MouseEvent::MOUSE_DOWN, &Slider::_mouseEventHandler);
        delete track;
        track = NULL;
        
        delete bar;
        bar = NULL;
        
        thumb->removeEventListener(MouseEvent::ROLL_OVER, &Slider::_mouseEventHandler);
        thumb->removeEventListener(MouseEvent::ROLL_OUT, &Slider::_mouseEventHandler);
        thumb->removeEventListener(MouseEvent::MOUSE_DOWN, &Slider::_mouseEventHandler);
        delete thumb;
        thumb = NULL;
        
        delete _valueText;
        _valueText = NULL;
        
        delete _draggablePoint;
        _draggablePoint = NULL;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void Slider::_setup() {
        //cout << "[Slider]setup()" << endl;
    }

    //--------------------------------------------------------------
    //
    void Slider::_update() {
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
                if(_roundEnabled) _value = MathUtil::roundd((_range * _percent) + _min);
            } else {
                _value = _min - (_range * _percent);
                if(_roundEnabled) _value = MathUtil::roundd(_min - (_range * _percent));
            }
            _valueText->text(ofToString(_value));
            //------------------------------------------
            //------------------------------------------
            _barWidth = thumb->x() + _thumbWidth * 0.5;
            _drawBarGraphics(_overColor, _activeColor, 1);
            //------------------------------------------
            
            //------------------------------------------
            //イベント
            SliderEvent* event = new SliderEvent(SliderEvent::CHANGE);
            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
            //------------------------------------------
        }
    }

    //--------------------------------------------------------------
    //
    void Slider::_draw() {
        
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    TextField* Slider::label() { return _label; }
    void Slider::label(TextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    void Slider::textColor(int color) {
        _valueText->textColor(color);
    }

    //--------------------------------------------------------------
    //
    float Slider::min() { return _min; }
    void Slider::min(float value, bool dispatch) {
        _min = value;
//        _range = _max - _min;
        if(_max > _min) {
            _range = _max - _min;
        } else {
            _range = _min - _max;
        }
        
        _percent = _barWidth / _trackWidth;
        _value = _range * _percent + _min;
        if(_roundEnabled) _value = MathUtil::roundd(_range * _percent + _min);
        
        _valueText->text(ofToString(_value));
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            SliderEvent* event = new SliderEvent(SliderEvent::CHANGE);
            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    float Slider::max() { return _max; }
    void Slider::max(float value, bool dispatch) {
        _max = value;
//        _range = _max - _min;
        if(_max > _min) {
            _range = _max - _min;
        } else {
            _range = _min - _max;
        }
        
        _percent = _barWidth / _trackWidth;
        _value = _range * _percent + _min;
        if(_roundEnabled) _value = MathUtil::roundd(_range * _percent + _min);
        
        _valueText->text(ofToString(_value));
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            SliderEvent* event = new SliderEvent(SliderEvent::CHANGE);
            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }

    //--------------------------------------------------------------
    //
    float Slider::value() { return _value; }
    void Slider::value(float value, bool dispatch) {
        
        //------------------------------------------
        _value = value;
        
        if(_roundEnabled) _value = MathUtil::roundd(_value);
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
        _drawBarGraphics(_lineColor, _activeColor);
        //------------------------------------------
        //------------------------------------------
        thumb->x(_barWidth - (_thumbWidth * 0.5));
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            SliderEvent* event = new SliderEvent(SliderEvent::CHANGE);
            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }

    //--------------------------------------------------------------
    //
    int Slider::barColor() { return _activeColor.getHex(); }
    void Slider::barColor(int value) {
        _activeColor.setHex(value);
        
        if(thumb->isMouseOver() || track->isMouseOver()) {
            _drawBarGraphics(_overColor, _activeColor, 1);
        } else {
            _drawBarGraphics(_lineColor, _activeColor, 1);
        }
    }
    void Slider::barColor(int red, int green, int blue, int alpha) {
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
    void Slider::barColor(const ofColor& color) {
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
    void Slider::barColor(const ofFloatColor& color) {
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
    bool Slider::roundEnabled() { return _roundEnabled; }
    void Slider::roundEnabled(bool value) { _roundEnabled = value; }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Slider::_drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        Graphics* g;
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
    void Slider::_drawBarGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        Graphics* g;
        g = bar->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a);
        g->drawRect(0, 0, _barWidth, _trackHeight);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    //
    void Slider::_trackOver() {
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
    void Slider::_trackOut() {
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
    void Slider::_trackPress() {
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
            if(_roundEnabled) _value = MathUtil::roundd((_range * _percent) + _min);
        } else {
            _value = _min - (_range * _percent);
            if(_roundEnabled) _value = MathUtil::roundd(_min - (_range * _percent));
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
        SliderEvent* event = new SliderEvent(SliderEvent::CHANGE);
        event->_target = this;
        event->data<float>(_value);
        dispatchEvent(event);
        //------------------------------------------    
    }
    //--------------------------------------------------------------
    //
    void Slider::_trackRelease() {
        
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
    void Slider::_thumbOver() {
        if(track->isMouseDown()) return;
        
        //------------------------------------------
        _drawBarGraphics(_overColor, _activeColor, 1);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Slider::_thumbOut() {
        if(track->isMouseDown()) return;
        if(track->isMouseOver()) return;
        
        _trackOut();
        
        //------------------------------------------
        _drawBarGraphics(_lineColor, _activeColor, 1);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Slider::_thumbPress() {
        _draggablePoint->x = mouseX() - thumb->x() - _thumbWidth * 0.5;
        //------------------------------------------
        _valueText->textColor(0x999999);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Slider::_thumbRelease() {
        //cout << "[Slider]_thumbRelease()" << endl;
        
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
    void Slider::_mouseEventHandler(Event& event) {
//        cout << "[Slider]_mouseEventHandler(" << event.type() << ")" << endl;
//        cout << "[Slider]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
//        cout << "[Slider]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
//        cout << "[Slider]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        //ROLL OVER
        if(event.type() == MouseEvent::ROLL_OVER) {
            if(event.target() == track) _trackOver();
            if(event.target() == thumb) _thumbOver();
        }
        
        //ROLL OUT
        if(event.type() == MouseEvent::ROLL_OUT) {
            if(event.target() == track) _trackOut();
            if(event.target() == thumb) _thumbOut();
        }
        
        //MOUSE DOWN
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            if(event.target() == track) _trackPress();
            if(event.target() == thumb) _thumbPress();
            stage()->addEventListener(MouseEvent::MOUSE_UP, this, &Slider::_mouseEventHandler);
        }
        
        //MOUSE UP
        if(event.type() == MouseEvent::MOUSE_UP) {
            if(event.currentTarget() == stage()) {
                _thumbRelease();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, &Slider::_mouseEventHandler);
            }
        }
    }

}