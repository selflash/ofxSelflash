#include "NumberDialer.h"

namespace fl2d {
    string NumberDialer::HORIZONTALLY = "horizontally";
    string NumberDialer::VERTICALLY = "vertically";
    
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    NumberDialer::NumberDialer(float width, float height) {
        //cout << "[NumberDialer]NumberDialer()" << endl;
        
        _target = this;
        name("NumberDialer");
        
        _uiWidth = width;
        _uiHeight = height;
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(FlashConfig::UI_LINE_COLOR);
        _normalColor.setHex(FlashConfig::UI_NORMAL_COLOR);
        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);
        
        _dragVector = VERTICALLY;
        _type = HORIZONTALLY;
        
        //------------------------------------------
        track = new Sprite();
        track->buttonMode(true);
        _drawTrackGraphics(_lineColor, _normalColor, 1);
        //横
        track->y(0);
        //縦
        //        track->y(0);
        track->addEventListener(MouseEvent::ROLL_OVER, this, &NumberDialer::_mouseEventHandler);
        track->addEventListener(MouseEvent::ROLL_OUT, this, &NumberDialer::_mouseEventHandler);
        track->addEventListener(MouseEvent::MOUSE_DOWN, this, &NumberDialer::_mouseEventHandler);
        addChild(track);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _label = NULL;
        //------------------------------------------
        
        //------------------------------------------
        //値
        _valueText = new TextField();
        //        _valueText->x(15 -  _uiHeight * 0.5 + _valueText->textHeight() * 0.5);
        _valueText->width(_uiWidth);
        _valueText->autoSize(TextFieldAutoSize::CENTER);
        _valueText->textColor(_labelNormalColor);
        _valueText->text("0");
        //横
        _valueText->y(_uiHeight * 0.5 - _valueText->textHeight() * 0.5 - 1);
        //縦
        //        _valueText->x(_uiHeight * 0.5 + _valueText->textHeight() * 0.5);
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
        
        //        _weight = 0.025;
        _weight = 1.0;
        _roundEnabled = false;
        
        _invertEnabled = false;
        
        _startPos = new ofPoint(0, 0);
        //------------------------------------------    
    }
    
    //--------------------------------------------------------------
    //
    NumberDialer::~NumberDialer() {
        //cout << "[NumberDialer]~NumberDialer()" << endl;
        
        _uiWidth = 0.0;
        _uiHeight = 0.0;
        
        _dragVector = "";
        _type = "";
        
        track->removeEventListener(MouseEvent::ROLL_OVER, this, &NumberDialer::_mouseEventHandler);
        track->removeEventListener(MouseEvent::ROLL_OUT, this, &NumberDialer::_mouseEventHandler);
        track->removeEventListener(MouseEvent::MOUSE_DOWN, this, &NumberDialer::_mouseEventHandler);
        delete track;
        track = NULL;
        
        _label = NULL;
        
        delete _valueText;
        _valueText = NULL;
        
        _value = 0.0;
        _tempValue = 0.0;
        _stepValue = 0.0;
        
        _min = 0.0;
        _max = 0.0;
        
        _weight = 0.0;
        _roundEnabled = false;
        _invertEnabled = false;
        
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
            if(_dragVector == VERTICALLY) {
                if(!_invertEnabled) {
                    _value = _tempValue + ((track->mouseY() - _startPos->y) * _weight) * -_stepValue;
                } else {
                    _value = _tempValue - ((track->mouseY() - _startPos->y) * _weight) * -_stepValue;
                }
            }
            //垂直
            if(_dragVector == HORIZONTALLY) {
                if(!_invertEnabled) {
                    _value = _tempValue + ((track->mouseX() - _startPos->x) * _weight) * _stepValue;
                } else {
                    _value = _tempValue - ((track->mouseX() - _startPos->x) * _weight) * _stepValue;
                }
            }
            
            if(!isnan(_min)) if(_value <= _min) _value = _min;
            if(!isnan(_max)) if(_max <= _value) _value = _max;
            
            if(_roundEnabled) {
                _valueText->text(ofToString(flmath::roundd(_value)));
            } else {
                _valueText->text(ofToString(_value));
            }
            
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
    TextField* NumberDialer::label() { return _label; }
    void NumberDialer::label(TextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    string NumberDialer::type() { return _type; }
    void NumberDialer::type(string value) {
        _type = value;
        
        //水平
        if(_type == HORIZONTALLY) {
            track->x(0);
            track->y(15);
            
            //            _labelText->x(0);
            //            _labelText->y(0);
            //            _labelText->rotation(0);
            
            _valueText->x(0);
            _valueText->y(15 +  _uiHeight * 0.5 - _valueText->textHeight() * 0.5);
            _valueText->rotation(0);
        }
        //垂直
        if(_type == VERTICALLY) {
            track->x(0);
            track->y(0);
            
            //            _labelText->x(_uiHeight + 15);
            //            _labelText->y(0);
            //            _labelText->rotation(90);
            
            _valueText->x(_uiHeight * 0.5 + _valueText->textHeight() * 0.5);
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
    float NumberDialer::value() {
        if(_roundEnabled) return flmath::roundd(_value);
        return _value;
    }
    void NumberDialer::value(float value, bool dispatch) {
        if(_value == value) return;
        
        _value = value;
        if(_roundEnabled) _value = flmath::roundd(_value);
        if(_value < _min) _value = _min;
        if(_value > _max) _value = _max;
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
        if(_roundEnabled) _min = flmath::roundd(_min);
        
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
        if(_roundEnabled) _max = flmath::roundd(_max);
        
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
    
    //--------------------------------------------------------------
    //
    float NumberDialer::weight() { return _weight; }
    void NumberDialer::weight(float value) { _weight = value; }
    
    //--------------------------------------------------------------
    //
    bool NumberDialer::roundEnabled() { return _roundEnabled; }
    void NumberDialer::roundEnabled(bool value) { _roundEnabled = value; }
    
    //--------------------------------------------------------------
    //
    bool NumberDialer::invertEnabled() { return _invertEnabled; }
    void NumberDialer::invertEnabled(bool value) { _invertEnabled = value; }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void NumberDialer::_drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        Graphics* g;
        g = track->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex());
        //水平
        if(_type == HORIZONTALLY) g->drawRect(0, 0, _uiWidth, _uiHeight);
        //垂直
        if(_type == VERTICALLY) g->drawRect(0, 0, _uiHeight, _uiWidth);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    //
    void NumberDialer::_over() {
        if(track->isMouseDown()) return;
        
        _valueText->textColor(_labelNormalColor);
        
        _drawTrackGraphics(_overColor, _normalColor, 1);
    }
    
    //--------------------------------------------------------------
    //
    void NumberDialer::_out() {
        if(track->isMouseDown()) return;
        
        _drawTrackGraphics(_lineColor, _normalColor, 1);
    }
    
    //--------------------------------------------------------------
    //
    void NumberDialer::_press() {
        _tempValue = _value;
        _startPos->x = track->mouseX();
        _startPos->y = track->mouseY();
        
        //        _valueText->textColor(0x0);
        
        _drawTrackGraphics(_overColor, _activeColor, 1);
    }
    
    //--------------------------------------------------------------
    //
    void NumberDialer::_release() {
        if(track->isMouseOver()) {
            _over();
            return;
        }
        
        _valueText->textColor(_labelNormalColor);
        
        _drawTrackGraphics(_lineColor, _normalColor, 1);
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
                stage()->removeEventListener(MouseEvent::MOUSE_UP, this, &NumberDialer::_mouseEventHandler);
            }
        }
    }
    
}
