#include "NumberDialer.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    NumberDialer::NumberDialer(float width, float height) {
        //cout << "[NumberDialer]NumberDialer()" << endl;
        
        _target = this;
        name("NumberDialer");
        
        _trackWidth = width;
        _trackHeight = height;
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        
        _lineColor = new ofFloatColor();
        _lineColor->setHex(FlashConfig::UI_LINE_COLOR);
        
        _normalColor = new ofFloatColor();
        _normalColor->setHex(FlashConfig::UI_NORMAL_COLOR);
        
        _overColor = new ofFloatColor();
        _overColor->setHex(FlashConfig::UI_OVER_COLOR);
        
        _activeColor = new ofFloatColor();
        _activeColor->setHex(FlashConfig::UI_ACTIVE_COLOR);
        
        _type = FL_HORIZONTALLY;
        
        //------------------------------------------
        track = new Sprite();
        track->buttonMode(true);
        _drawTrackGraphics(*_lineColor, *_normalColor);
        //横
        track->y(15);
        //縦
//        track->y(0);
        track->addEventListener(MouseEvent::ROLL_OVER, this, &NumberDialer::_mouseEventHandler);
        track->addEventListener(MouseEvent::ROLL_OUT, this, &NumberDialer::_mouseEventHandler);
        track->addEventListener(MouseEvent::MOUSE_DOWN, this, &NumberDialer::_mouseEventHandler);
        addChild(track);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _labelText = new TextField();
        //横
        _labelText->x(0);
        _labelText->y(0);
        //縦
//        _labelText->x(_trackHeight + 15);
//        _labelText->y(0);
//        _labelText->rotation(90);
        
        _labelText->width(_trackWidth);
        _labelText->autoSize(TextFieldAutoSize::CENTER);
        _labelText->textColor(_labelNormalColor);
        _labelText->text("NUMBER DIALER");
        addChild(_labelText);
        //------------------------------------------
        
        //------------------------------------------
        //値
        _valueText = new TextField();
//        _valueText->x(15 -  _trackHeight * 0.5 + _valueText->textHeight() * 0.5);
        _valueText->width(_trackWidth);
        _valueText->autoSize(TextFieldAutoSize::CENTER);
        _valueText->textColor(0xffffff);
        _valueText->text("0");
        //横
        _valueText->y(15 +  _trackHeight * 0.5 - _valueText->textHeight() * 0.5);
        //縦
//        _valueText->x(_trackHeight * 0.5 + _valueText->textHeight() * 0.5);
//        _valueText->rotation(90);
        
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
        //------------------------------------------
        _value = 0.0;
        _tempValue = 0.0;
        _stepValue = 1.0;
        
//        _min = 0 / 0.f;
//        _max = 0 / 0.f;
        _min = numeric_limits<float>::quiet_NaN();
        _max = numeric_limits<float>::quiet_NaN();
        
        _startPos = new ofPoint(0, 0);
        //------------------------------------------    
    }

    //--------------------------------------------------------------
    //
    NumberDialer::~NumberDialer() {
        //cout << "[NumberDialer]~NumberDialer()" << endl;
        
        delete _lineColor;
        _lineColor = NULL;
        
        delete _normalColor;
        _normalColor = NULL;
        
        delete _overColor;
        _overColor = NULL;
        
        delete _activeColor;
        _activeColor = NULL;
        
        track->removeEventListener(MouseEvent::ROLL_OVER, &NumberDialer::_mouseEventHandler);
        track->removeEventListener(MouseEvent::ROLL_OUT, &NumberDialer::_mouseEventHandler);
        track->removeEventListener(MouseEvent::MOUSE_DOWN, &NumberDialer::_mouseEventHandler);
        delete track;
        track = NULL;
        
        delete _labelText;
        _labelText = NULL;
        
        delete _valueText;
        _valueText = NULL;
        
        _value = 0.0;
        _tempValue = 0.0;
        _stepValue = 0.0;
        
        _min = 0.0;
        _max = 0.0;
        
        delete _startPos;
        _startPos = NULL;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void NumberDialer::_update() {
        if(track->isMouseDown()) {
            float valuePrev = _value;
            
            //水平
            if(_type == FL_HORIZONTALLY) _value = _tempValue + (track->mouseY() - _startPos->y) * -_stepValue;
            //垂直
            if(_type == FL_VERTICALLY) _value = _tempValue + (track->mouseX() - _startPos->x) * _stepValue;
            
            if(!isnan(_min)) if(_value <= _min) _value = _min;
            if(!isnan(_max)) if(_max <= _value) _value = _max;
            
            _valueText->text(ofToString(_value));
            
            //------------------------------------------
            //イベント
            if(valuePrev != _value) {
                NumberDialerEvent* event = new NumberDialerEvent(NumberDialerEvent::CHANGE);
//                event->_target = this;
                event->data<float>(_value);
                dispatchEvent(event);
            }
            //------------------------------------------
        }
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    string NumberDialer::label() { return _labelText->text(); }
    void NumberDialer::label(string value, int color) { _labelText->text(value, color); }

    //--------------------------------------------------------------
    //
    void NumberDialer::textColor(int color) {
        _labelText->textColor(color);
    }
    
    //--------------------------------------------------------------
    //
    string NumberDialer::type() { return _type; }
    void NumberDialer::type(string value) {
        _type = value;
        
        //水平
        if(_type == FL_HORIZONTALLY) {
            track->x(0);
            track->y(15);
            
            _labelText->x(0);
            _labelText->y(0);
            _labelText->rotation(0);
            
            _valueText->x(0);
            _valueText->y(15 +  _trackHeight * 0.5 - _valueText->textHeight() * 0.5);
            _valueText->rotation(0);
        }
        //垂直
        if(_type == FL_VERTICALLY) {
            track->x(0);
            track->y(0);
            
            _labelText->x(_trackHeight + 15);
            _labelText->y(0);
            _labelText->rotation(90);
            
            _valueText->x(_trackHeight * 0.5 + _valueText->textHeight() * 0.5);
            _valueText->y(0);
            _valueText->rotation(90);
        }
        
        if(isMouseOver()) {
            _over();
        } else {
            _out();
        }
    }

    //--------------------------------------------------------------
    //
    float NumberDialer::value() { return _value; }
    void NumberDialer::value(float value, bool dispatch) {
        if(_value == value) return;
        
        _value = value;
        _valueText->text(ofToString(_value));
        
        //------------------------------------------
        if(dispatch) {
            //イベント
            NumberDialerEvent* event = new NumberDialerEvent(NumberDialerEvent::CHANGE);
//            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }

    //--------------------------------------------------------------
    //
    float NumberDialer::stepValue() { return _stepValue; }
    void NumberDialer::stepValue(float value, bool dispatch) { _stepValue = value; }
    
    //--------------------------------------------------------------
    //
    float NumberDialer::min() { return _min; }
    void NumberDialer::min(float value, bool dispatch) {
        _min = value;
        
        if(_value <= _min) {
            _value = _min;
            _valueText->text(ofToString(_value));
            
            //------------------------------------------
            if(dispatch) {
                //イベント
                NumberDialerEvent* event = new NumberDialerEvent(NumberDialerEvent::CHANGE);
//                event->_target = this;
                event->data<float>(_value);
                dispatchEvent(event);
            }
            //------------------------------------------
        }
    }
    //--------------------------------------------------------------
    //
    float NumberDialer::max() { return _max; }
    void NumberDialer::max(float value, bool dispatch) {
        _max = value;
        
        if(_max <= _value) {
            _value = _max;
            _valueText->text(ofToString(_value));
            
            //------------------------------------------
            if(dispatch) {
                //イベント
                NumberDialerEvent* event = new NumberDialerEvent(NumberDialerEvent::CHANGE);
//                event->_target = this;
                event->data<float>(_value);
                dispatchEvent(event);
            }
            //------------------------------------------
        }
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void NumberDialer::_drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor) {
        Graphics* g;
        g = track->graphics();
        g->clear();
        g->lineStyle(1, lineColor.getHex());
        g->beginFill(fillColor.getHex());
        //水平
        if(_type == FL_HORIZONTALLY) g->drawRect(0, 0, _trackWidth, _trackHeight);
        //垂直
        if(_type == FL_VERTICALLY) g->drawRect(0, 0, _trackHeight, _trackWidth);
        g->endFill();
    }

    //--------------------------------------------------------------
    //
    void NumberDialer::_over() {
        if(track->isMouseDown()) return;
        
        _valueText->textColor(0xffffff);

        _drawTrackGraphics(*_overColor, *_normalColor);
    }

    //--------------------------------------------------------------
    //
    void NumberDialer::_out() {
        if(track->isMouseDown()) return;
        
        _drawTrackGraphics(*_lineColor, *_normalColor);
    }

    //--------------------------------------------------------------
    //
    void NumberDialer::_press() {
        _tempValue = _value;
        _startPos->x = track->mouseX();
        _startPos->y = track->mouseY();
        
        _valueText->textColor(0x0);
        
        _drawTrackGraphics(*_overColor, *_activeColor);
    }

    //--------------------------------------------------------------
    //
    void NumberDialer::_release() {
        if(track->isMouseOver()) {
            _over();
            return;
        }
        
        _valueText->textColor(0xffffff);
        
        _drawTrackGraphics(*_lineColor, *_normalColor);
    }

    //==============================================================
    // EVENT HANDLER
    //==============================================================

    //--------------------------------------------------------------
    //
    void NumberDialer::_mouseEventHandler(Event& event) {
//        cout << "[NumberDialer]_mouseEventHandler(" << event.type() << ")" << endl;
//        cout << "[NumberDialer]this          = " << this << ", " << ((DisplayObject*) this)->name() << endl;
//        cout << "[NumberDialer]currentTarget = " << event.currentTarget() << ", " << ((DisplayObject*) event.currentTarget())->name() << endl;
//        cout << "[NumberDialer]target        = " << event.target() << ", " << ((DisplayObject*) event.target())->name() << endl;
        
        if(event.type() == MouseEvent::ROLL_OVER) {
            if(event.target() == track) _over();
        }
        if(event.type() == MouseEvent::ROLL_OUT) {
            if(event.target() == track) _out();
        }
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            if(event.target() == track) {
                _press();
                stage()->addEventListener(MouseEvent::MOUSE_UP, this, &NumberDialer::_mouseEventHandler);
            }
        }
        if(event.type() == MouseEvent::MOUSE_UP) {
            if(event.target() == stage()) {
                _release();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, &NumberDialer::_mouseEventHandler);
            }
        }
    }

}