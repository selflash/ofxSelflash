#include "flNumericDialer.h"

namespace fl2d {
    //水平
    string flNumericDialer::HORIZONTALLY = "horizontally";
    //垂直
    string flNumericDialer::VERTICALLY = "vertically";
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flNumericDialer::flNumericDialer(float width) {
        //ofLog() << "[flNumericDialer]flNumericDialer()";
        
        _target = this;
        name("flNumericDialer");

        _uiWidth = width;
        
        //------------------------------------------
        _track = new flSprite();
        _track->name("flNumericDialer.track");
        _track->buttonMode(true);
        _track->addEventListener(flMouseEvent::ROLL_OVER, this, &flNumericDialer::_mouseEventHandler);
        _track->addEventListener(flMouseEvent::ROLL_OUT, this, &flNumericDialer::_mouseEventHandler);
        _track->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flNumericDialer::_mouseEventHandler);
        addChild(_track);
        //------------------------------------------
        
        //------------------------------------------
        _valueText = new flTextField();
        _valueText->name("flNumericDialer.valueText");
        _valueText->width(_uiWidth);
        _valueText->autoSize(flTextFieldAutoSize::CENTER);
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _valueText->text("0");
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
        direction(HORIZONTALLY);
    }
    
    //--------------------------------------------------------------
    flNumericDialer::~flNumericDialer() {
        //ofLog() << "[flNumericDialer]~flNumericDialer()";

        _track->removeEventListener(flMouseEvent::ROLL_OVER, this, &flNumericDialer::_mouseEventHandler);
        _track->removeEventListener(flMouseEvent::ROLL_OUT, this, &flNumericDialer::_mouseEventHandler);
        _track->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flNumericDialer::_mouseEventHandler);
        delete _track;
        _track = NULL;
        
        delete _valueText;
        _valueText = NULL;
        
        //------------------------------------------
        _floatParam = NULL;
        _listeners.unsubscribeAll();
        //------------------------------------------
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flNumericDialer::_setup() {
        //ofLog() << "[flNumericDialer]_setup()";
    }

    //--------------------------------------------------------------
    void flNumericDialer::_update() {
        //ofLog() << "[flNumericDialer]_update()";

        if(_track->isMouseDown()) {
            _onPress();
        }
        
        _bChangedByOfParm["value"] = false;
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_draw() {
        
    }

    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flNumericDialer::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::enabled(bool value) {
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
    string flNumericDialer::direction() { return _direction; }
    void flNumericDialer::direction(string value) {
        _direction = value;
        
        //水平
        if(_direction == HORIZONTALLY) {
//            _track->x(0);
//            _track->y(0);

            _valueText->x(0);
//            _valueText->y(15 +  _uiHeight * 0.5 - _valueText->textHeight() * 0.5);
            _valueText->y(0);
            _valueText->rotation(0);
        }
        //垂直
        else if(_direction == VERTICALLY) {
//            _track->x(_uiHeight);
//            _track->y(0);

            _valueText->x(_uiHeight * 0.5 + _valueText->textHeight() * 0.5);
            _valueText->y(0);
            _valueText->rotation(90);
        }
        
        if(isMouseOver()) {
            _onOver();
        } else {
            _onOut();
        }
    }
    
    //--------------------------------------------------------------
    float flNumericDialer::value() { return _value; }
    void flNumericDialer::value(float value, bool dispatch) {
        if(_value == value) return;

        _value = value;
        if(_roundEnabled) _value = flmath::roundd(_value);
        if(_value < _min) _value = _min;
        if(_value > _max) _value = _max;
        
        //------------------------------------------
        //Update color.
        if(_enabled) {
            if(_track->isMouseDown()) {
                _setActiveColor();
            } else if(_track->isMouseOver()) {
                _setActiveColor();
            } else {
                _setNormalColor();
            }
        } else {
            _setDisableNormalColor();
        }
        //------------------------------------------
        
        //------------------------------------------
        _changeValue(dispatch);
        
        if(!_bChangedByOfParm["value"]) {
            if(_floatParam != NULL) {
                _bChangedByMyself["value"] = true;
                _floatParam->set(_value);
            }
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    float flNumericDialer::stepSize() { return _stepSize; }
    void flNumericDialer::stepSize(float value, bool dispatch) { _stepSize = value; }
    
    //--------------------------------------------------------------
    float flNumericDialer::min() { return _min; }
    void flNumericDialer::min(float value, bool dispatch) {
        if(_min == value) return;

        _min = value;
        if(_roundEnabled) _min = flmath::roundd(_min);
        
        if(_value <= _min) {
            _value = _min;
            
            //------------------------------------------
            _changeValue(dispatch);
            //------------------------------------------
        }
    }
    
    //--------------------------------------------------------------
    float flNumericDialer::max() { return _max; }
    void flNumericDialer::max(float value, bool dispatch) {
        if(_max == value) return;

        _max = value;
        if(_roundEnabled) _max = flmath::roundd(_max);
        
        if(_max <= _value) {
            _value = _max;
            
            //------------------------------------------
            _changeValue(dispatch);
            //------------------------------------------
        }
    }
    
    //--------------------------------------------------------------
    float flNumericDialer::weight() { return _weight; }
    void flNumericDialer::weight(float value) { _weight = value; }
    
    //--------------------------------------------------------------
    bool flNumericDialer::roundEnabled() { return _roundEnabled; }
    void flNumericDialer::roundEnabled(bool value) { _roundEnabled = value; }
    
    //--------------------------------------------------------------
    bool flNumericDialer::invertEnabled() { return _invertEnabled; }
    void flNumericDialer::invertEnabled(bool value) { _invertEnabled = value; }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flNumericDialer::_changeValue(bool dispatch) {
        _valueText->text(ofToString(_value, _digit));

        //------------------------------------------
        if(dispatch) {
            flNumericDialerEvent* event = new flNumericDialerEvent(flNumericDialerEvent::CHANGE);
            event->data<float>(_value);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_onOver() {
        if(_track->isMouseDown()) return;
        
        _setOverColor();
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_onOut() {
        if(_track->isMouseDown()) return;
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_onPress() {
        float preValue = _value;
        
        //------------------------------------------
        //水平
        if(_dragDirection == VERTICALLY) {
            if(!_invertEnabled) {
                _value = _tempValue + ((mouseY() - _startPos.y) * _weight) * -_stepSize;
            } else {
                _value = _tempValue - ((mouseY() - _startPos.y) * _weight) * -_stepSize;
            }
        }
        //垂直
        else if(_dragDirection == HORIZONTALLY) {
            if(!_invertEnabled) {
                _value = _tempValue + ((mouseX() - _startPos.x) * _weight) * _stepSize;
            } else {
                _value = _tempValue - ((mouseX() - _startPos.x) * _weight) * _stepSize;
            }
        }
        
        if(_roundEnabled) _value = flmath::roundd(_value);
        
        if(!isnan(_min)) if(_value <= _min) _value = _min;
        if(!isnan(_max)) if(_max <= _value) _value = _max;
        //------------------------------------------
        
        //------------------------------------------
        _setActiveColor();
        //------------------------------------------

        //------------------------------------------
        if(preValue != _value) _changeValue(true);
        
        if(!_bChangedByOfParm["value"]) {
            if(_floatParam != NULL) {
                _bChangedByMyself["value"] = true;
                _floatParam->set(_value);
            }
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_onRelease() {
        if(_track->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR);
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_setSelectedOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_setDisableNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_setDisableActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flNumericDialer::_drawGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = _track->graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        //水平
        if(_direction == HORIZONTALLY) g->drawRect(0, 0, _uiWidth, _uiHeight);
        //垂直
        else if(_direction == VERTICALLY) g->drawRect(0, 0, _uiHeight, _uiWidth);
        g->endFill();
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flNumericDialer::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flNumericDialer]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flNumericDialer]this          = " << this << ", " << ((DisplayObject*) this)->name();
//        ofLog() << "[flNumericDialer]currentTarget = " << event.currentTarget() << ", " << ((DisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flNumericDialer]target        = " << event.target() << ", " << ((DisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == _track) _onOver();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == _track) _onOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == _track) {
                _tempValue = _value;
                _startPos.x = mouseX();
                _startPos.y = mouseY();
                _onPress();
                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flNumericDialer::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            _onRelease();
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flNumericDialer::_mouseEventHandler);
            }
        }
    }
    
}
