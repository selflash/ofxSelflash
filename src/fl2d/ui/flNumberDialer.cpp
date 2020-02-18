#include "flNumberDialer.h"

namespace fl2d {
    //水平
    string flNumberDialer::HORIZONTALLY = "horizontally";
    //垂直
    string flNumberDialer::VERTICALLY = "vertically";
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flNumberDialer::flNumberDialer(float width, float height) {
        //ofLog() << "[flNumberDialer]flNumberDialer()";
        
        _target = this;
        name("flNumberDialer");
        
        _label = NULL;

        _uiWidth = width;
        _uiHeight = height;
        
        _dragVector = VERTICALLY;
        _type = HORIZONTALLY;
        
        //------------------------------------------
        _track = new flSprite();
        _track->buttonMode(true);
        _track->addEventListener(flMouseEvent::ROLL_OVER, this, &flNumberDialer::_mouseEventHandler);
        _track->addEventListener(flMouseEvent::ROLL_OUT, this, &flNumberDialer::_mouseEventHandler);
        _track->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flNumberDialer::_mouseEventHandler);
        addChild(_track);
        //------------------------------------------
        
        //------------------------------------------
        _valueText = new flTextField();
        _valueText->width(_uiWidth);
        _valueText->autoSize(flTextFieldAutoSize::CENTER);
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _valueText->text("0");
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
        //------------------------------------------
        _value = 0.0;
        _tempValue = 0.0;
        _stepValue = 1.0;
        _min = numeric_limits<float>::quiet_NaN();
        _max = numeric_limits<float>::quiet_NaN();
        
        _weight = 1.0;
        _roundEnabled = false;
        _invertEnabled = false;
        
        _startPos = ofPoint(0, 0);
        //------------------------------------------
        
        type(HORIZONTALLY);
    }
    
    //--------------------------------------------------------------
    flNumberDialer::~flNumberDialer() {
        //ofLog() << "[flNumberDialer]~flNumberDialer()";

//        removeChild(_track);
        _track->removeEventListener(flMouseEvent::ROLL_OVER, this, &flNumberDialer::_mouseEventHandler);
        _track->removeEventListener(flMouseEvent::ROLL_OUT, this, &flNumberDialer::_mouseEventHandler);
        _track->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flNumberDialer::_mouseEventHandler);
        delete _track;
        _track = NULL;
        
        _value = 0.0;
        _tempValue = 0.0;
        _stepValue = 0.0;
        _min = 0.0;
        _max = 0.0;
        
        _uiWidth = 0.0;
        _uiHeight = 0.0;
        
        _dragVector = "";
        _type = "";
        
        delete _valueText;
        _valueText = NULL;

        _label = NULL;
        
        _weight = 0.0;
        _roundEnabled = false;
        _invertEnabled = false;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flNumberDialer::_setup() {
        //ofLog() << "[flNumberDialer]_setup()";
    }

    //--------------------------------------------------------------
    void flNumberDialer::_update() {
        //ofLog() << "[flNumberDialer]_update()";

        if(_track->isMouseDown()) {
            float preValue = _value;
            
            //------------------------------------------
            //水平
            if(_dragVector == VERTICALLY) {
                if(!_invertEnabled) {
                    _value = _tempValue + ((mouseY() - _startPos.y) * _weight) * -_stepValue;
                } else {
                    _value = _tempValue - ((mouseY() - _startPos.y) * _weight) * -_stepValue;
                }
            }
            //垂直
            else if(_dragVector == HORIZONTALLY) {
                if(!_invertEnabled) {
                    _value = _tempValue + ((mouseX() - _startPos.x) * _weight) * _stepValue;
                } else {
                    _value = _tempValue - ((mouseX() - _startPos.x) * _weight) * _stepValue;
                }
            }
            
            if(_roundEnabled) _value = flmath::roundd(_value);
            
            if(!isnan(_min)) if(_value <= _min) _value = _min;
            if(!isnan(_max)) if(_max <= _value) _value = _max;
            //------------------------------------------
            
            //------------------------------------------
            //イベント
            if(preValue != _value) {
                _valueText->text(ofToString(_value, 2));

                flNumberDialerEvent* event = new flNumberDialerEvent(flNumberDialerEvent::CHANGE);
//                event->_target = this;
                event->data<float>(_value);
                dispatchEvent(event);
            }
            //------------------------------------------
        }
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_draw() {
        
    }

    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flNumberDialer::label() { return _label; }
    void flNumberDialer::label(flTextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    string flNumberDialer::type() { return _type; }
    void flNumberDialer::type(string value) {
        _type = value;
        
        //水平
        if(_type == HORIZONTALLY) {
//            _track->x(0);
//            _track->y(0);

            _valueText->x(0);
//            _valueText->y(15 +  _uiHeight * 0.5 - _valueText->textHeight() * 0.5);
            _valueText->y(0);
            _valueText->rotation(0);
        }
        //垂直
        else if(_type == VERTICALLY) {
//            _track->x(_uiHeight);
//            _track->y(0);

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
    float flNumberDialer::value() { return _value; }
    void flNumberDialer::value(float value, bool dispatch) {
        if(_value == value) return;
        
        float preValue = _value;

        _value = value;
        if(_roundEnabled) _value = flmath::roundd(_value);
        if(_value < _min) _value = _min;
        if(_value > _max) _value = _max;
        
        if(preValue != _value) {
            _valueText->text(ofToString(_value, 2));

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
    }
    
    //--------------------------------------------------------------
    float flNumberDialer::stepValue() { return _stepValue; }
    void flNumberDialer::stepValue(float value, bool dispatch) { _stepValue = value; }
    
    //--------------------------------------------------------------
    float flNumberDialer::min() { return _min; }
    void flNumberDialer::min(float value, bool dispatch) {
        _min = value;
        if(_roundEnabled) _min = flmath::roundd(_min);
        
        if(_value <= _min) {
            _value = _min;
            _valueText->text(ofToString(_value, 2));
            
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
    float flNumberDialer::max() { return _max; }
    void flNumberDialer::max(float value, bool dispatch) {
        _max = value;
        if(_roundEnabled) _max = flmath::roundd(_max);
        
        if(_max <= _value) {
            _value = _max;
            _valueText->text(ofToString(_value, 2));
            
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
    float flNumberDialer::weight() { return _weight; }
    void flNumberDialer::weight(float value) { _weight = value; }
    
    //--------------------------------------------------------------
    bool flNumberDialer::roundEnabled() { return _roundEnabled; }
    void flNumberDialer::roundEnabled(bool value) { _roundEnabled = value; }
    
    //--------------------------------------------------------------
    bool flNumberDialer::invertEnabled() { return _invertEnabled; }
    void flNumberDialer::invertEnabled(bool value) { _invertEnabled = value; }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================

    //--------------------------------------------------------------
    void flNumberDialer::_over() {
        if(_track->isMouseDown()) return;
        
        _setOverColor();
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_out() {
        if(_track->isMouseDown()) return;
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_press() {
        _setActiveColor();
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_release() {
        if(_track->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR);
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_setSelectedOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_setDisableNormalColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_setDisableActiveColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flNumberDialer::_drawGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = _track->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        //水平
        if(_type == HORIZONTALLY) g->drawRect(0, 0, _uiWidth, _uiHeight);
        //垂直
        else if(_type == VERTICALLY) g->drawRect(0, 0, _uiHeight, _uiWidth);
        g->endFill();
    }
    
    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flNumberDialer::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flNumberDialer]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flNumberDialer]this          = " << this << ", " << ((DisplayObject*) this)->name();
//        ofLog() << "[flNumberDialer]currentTarget = " << event.currentTarget() << ", " << ((DisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flNumberDialer]target        = " << event.target() << ", " << ((DisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == _track) _over();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == _track) _out();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == _track) {
                _tempValue = _value;
                _startPos.x = mouseX();
                _startPos.y = mouseY();
                _press();
                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flNumberDialer::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            _release();
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flNumberDialer::_mouseEventHandler);
            }
        }
    }
    
}
