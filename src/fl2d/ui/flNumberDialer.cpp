#include "flNumberDialer.h"

namespace fl2d {
    string flNumberDialer::HORIZONTALLY = "horizontally";
    string flNumberDialer::VERTICALLY = "vertically";
    
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flNumberDialer::flNumberDialer(float width, float height) {
        //cout << "[flNumberDialer]flNumberDialer()" << endl;
        
        _target = this;
        name("flNumberDialer");
        
        _uiWidth = width;
        _uiHeight = height;
        
        _labelNormalColor = flDefinition::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = flDefinition::UI_LABEL_OVER_COLOR;
        _labelActiveColor = flDefinition::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = flDefinition::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(flDefinition::UI_LINE_COLOR);
        _normalColor.setHex(flDefinition::UI_NORMAL_COLOR);
        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
        
        _dragVector = VERTICALLY;
        _type = HORIZONTALLY;
        
        //------------------------------------------
        track = new flSprite();
        track->buttonMode(true);
        _drawTrackGraphics(_lineColor, _normalColor, 1);
        //横
        track->y(0);
        //縦
        //        track->y(0);
        track->addEventListener(flMouseEvent::ROLL_OVER, this, &flNumberDialer::_mouseEventHandler);
        track->addEventListener(flMouseEvent::ROLL_OUT, this, &flNumberDialer::_mouseEventHandler);
        track->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flNumberDialer::_mouseEventHandler);
        addChild(track);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _label = NULL;
        //------------------------------------------
        
        //------------------------------------------
        //値
        _valueText = new flTextField();
        //        _valueText->x(15 -  _uiHeight * 0.5 + _valueText->textHeight() * 0.5);
        _valueText->width(_uiWidth);
        _valueText->autoSize(flTextFieldAutoSize::CENTER);
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
    flNumberDialer::~flNumberDialer() {
        //cout << "[flNumberDialer]~flNumberDialer()" << endl;
        
        _uiWidth = 0.0;
        _uiHeight = 0.0;
        
        _dragVector = "";
        _type = "";
        
        track->removeEventListener(flMouseEvent::ROLL_OVER, this, &flNumberDialer::_mouseEventHandler);
        track->removeEventListener(flMouseEvent::ROLL_OUT, this, &flNumberDialer::_mouseEventHandler);
        track->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flNumberDialer::_mouseEventHandler);
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
    void flNumberDialer::_update() {
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
                flNumberDialerEvent* event = new flNumberDialerEvent(flNumberDialerEvent::CHANGE);
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
    flTextField* flNumberDialer::label() { return _label; }
    void flNumberDialer::label(flTextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    string flNumberDialer::type() { return _type; }
    void flNumberDialer::type(string value) {
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
    float flNumberDialer::value() {
        if(_roundEnabled) return flmath::roundd(_value);
        return _value;
    }
    void flNumberDialer::value(float value, bool dispatch) {
        if(_value == value) return;
        
        _value = value;
        if(_roundEnabled) _value = flmath::roundd(_value);
        if(_value < _min) _value = _min;
        if(_value > _max) _value = _max;
        _valueText->text(ofToString(_value));
        
        //------------------------------------------
        if(dispatch) {
            //イベント
            flNumberDialerEvent* event = new flNumberDialerEvent(flNumberDialerEvent::CHANGE);
            //            event->_target = this;
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    float flNumberDialer::stepValue() { return _stepValue; }
    void flNumberDialer::stepValue(float value, bool dispatch) { _stepValue = value; }
    
    //--------------------------------------------------------------
    //
    float flNumberDialer::min() { return _min; }
    void flNumberDialer::min(float value, bool dispatch) {
        _min = value;
        if(_roundEnabled) _min = flmath::roundd(_min);
        
        if(_value <= _min) {
            _value = _min;
            _valueText->text(ofToString(_value));
            
            //------------------------------------------
            if(dispatch) {
                //イベント
                flNumberDialerEvent* event = new flNumberDialerEvent(flNumberDialerEvent::CHANGE);
                //                event->_target = this;
                event->data<float>(_value);
                dispatchEvent(event);
            }
            //------------------------------------------
        }
    }
    //--------------------------------------------------------------
    //
    float flNumberDialer::max() { return _max; }
    void flNumberDialer::max(float value, bool dispatch) {
        _max = value;
        if(_roundEnabled) _max = flmath::roundd(_max);
        
        if(_max <= _value) {
            _value = _max;
            _valueText->text(ofToString(_value));
            
            //------------------------------------------
            if(dispatch) {
                //イベント
                flNumberDialerEvent* event = new flNumberDialerEvent(flNumberDialerEvent::CHANGE);
                //                event->_target = this;
                event->data<float>(_value);
                dispatchEvent(event);
            }
            //------------------------------------------
        }
    }
    
    //--------------------------------------------------------------
    //
    float flNumberDialer::weight() { return _weight; }
    void flNumberDialer::weight(float value) { _weight = value; }
    
    //--------------------------------------------------------------
    //
    bool flNumberDialer::roundEnabled() { return _roundEnabled; }
    void flNumberDialer::roundEnabled(bool value) { _roundEnabled = value; }
    
    //--------------------------------------------------------------
    //
    bool flNumberDialer::invertEnabled() { return _invertEnabled; }
    void flNumberDialer::invertEnabled(bool value) { _invertEnabled = value; }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flNumberDialer::_drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness) {
        flGraphics* g;
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
    void flNumberDialer::_over() {
        if(track->isMouseDown()) return;
        
        _valueText->textColor(_labelNormalColor);
        
        _drawTrackGraphics(_overColor, _normalColor, 1);
    }
    
    //--------------------------------------------------------------
    //
    void flNumberDialer::_out() {
        if(track->isMouseDown()) return;
        
        _drawTrackGraphics(_lineColor, _normalColor, 1);
    }
    
    //--------------------------------------------------------------
    //
    void flNumberDialer::_press() {
        _tempValue = _value;
        _startPos->x = track->mouseX();
        _startPos->y = track->mouseY();
        
        //        _valueText->textColor(0x0);
        
        _drawTrackGraphics(_overColor, _activeColor, 1);
    }
    
    //--------------------------------------------------------------
    //
    void flNumberDialer::_release() {
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
    void flNumberDialer::_mouseEventHandler(flEvent& event) {
        //        cout << "[flNumberDialer]_mouseEventHandler(" << event.type() << ")" << endl;
        //        cout << "[flNumberDialer]this          = " << this << ", " << ((DisplayObject*) this)->name() << endl;
        //        cout << "[flNumberDialer]currentTarget = " << event.currentTarget() << ", " << ((DisplayObject*) event.currentTarget())->name() << endl;
        //        cout << "[flNumberDialer]target        = " << event.target() << ", " << ((DisplayObject*) event.target())->name() << endl;
        
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == track) _over();
        }
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == track) _out();
        }
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == track) {
                _press();
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flNumberDialer::_mouseEventHandler);
            }
        }
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(event.target() == stage()) {
                _release();
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flNumberDialer::_mouseEventHandler);
            }
        }
    }
    
}
