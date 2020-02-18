#include "flColorSlider.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
    flColorSlider::flColorSlider(float width, bool alphaEnabled) {
        //ofLog() << "[flColorSlider]flColorSlider()";
        
        _target = this;
        name("flColorSlider");
        
        float height = 18 + 2;
        
        //------------------------------------------
        redSlider = new flSlider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(255);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        redSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(redSlider);
        greenSlider = new flSlider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(255);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(greenSlider);
        blueSlider = new flSlider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(255);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(blueSlider);
        alphaSlider = NULL;
        if(alphaEnabled == true) {
            alphaSlider = new flSlider(width, 0, 255);
            alphaSlider->x(0);
            alphaSlider->y(height * 3);
            alphaSlider->value(255);
            alphaSlider->roundEnabled(true);
            alphaSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
            addChild(alphaSlider);
        }
        //------------------------------------------

        //------------------------------------------
        _hexText = new flTextField();
        _hexText->x(0);
        _hexText->y(0);
        _hexText->width(width);
        _hexText->autoSize(flTextFieldAutoSize::RIGHT);
        _hexText->textColor(0x0);
        _hexText->text("");
        _hexText->mouseEnabled(false);
        //addChild(_hexText);
        //------------------------------------------
        
        //------------------------------------------
        _redValueText = new flTextField();
        _redValueText->x(width + 5);
        _redValueText->y(height * 0);
        _redValueText->width(15);
        _redValueText->autoSize(flTextFieldAutoSize::CENTER);
        _redValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _redValueText->text("R");
        _redValueText->mouseEnabled(false);
        addChild(_redValueText);
        //GREEN
        _greenValueText = new flTextField();
        _greenValueText->x(width + 5);
        _greenValueText->y(height * 1);
        _greenValueText->width(15);
        _greenValueText->autoSize(flTextFieldAutoSize::CENTER);
        _greenValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _greenValueText->text("G");
        _greenValueText->mouseEnabled(false);
        addChild(_greenValueText);
        _blueValueText = new flTextField();
        _blueValueText->x(width + 5);
        _blueValueText->y(height * 2);
        _blueValueText->width(15);
        _blueValueText->autoSize(flTextFieldAutoSize::CENTER);
        _blueValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _blueValueText->text("B");
        _blueValueText->mouseEnabled(false);
        addChild(_blueValueText);
        if(alphaEnabled == true) {
            _alphaValueText = new flTextField();
            _alphaValueText->x(width + 5);
            _alphaValueText->y(height * 3);
            _alphaValueText->width(15);
            _alphaValueText->autoSize(flTextFieldAutoSize::CENTER);
            _alphaValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
            _alphaValueText->text("A");
            _alphaValueText->mouseEnabled(false);
            addChild(_alphaValueText);
        }
        //------------------------------------------
        
        //------------------------------------------
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        _colorValue.a = 255;
        if(alphaEnabled == true) {
            _colorValue.a = alphaSlider->value();
        }
        _hexValue = _colorValue.getHex();
        _hexText->text(ofToString(_hexValue));
        //------------------------------------------

        _updateColor();
        
        _param = NULL;
    }
    
    //--------------------------------------------------------------
    flColorSlider::flColorSlider(int r, int g, int b) {
        //ofLog() << "[flColorSlider]flColorSlider()";

        float width = 200;
        
        _target = this;
        name("flColorSlider");
        
        float height = 18 + 2;
        
        //------------------------------------------
        redSlider = new flSlider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(r);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(redSlider);
        greenSlider = new flSlider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(g);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(greenSlider);
        blueSlider = new flSlider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(b);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(blueSlider);
        alphaSlider = NULL;
        //------------------------------------------

        //------------------------------------------
        _hexText = new flTextField();
        _hexText->x(0);
        _hexText->y(0);
        _hexText->width(width);
        _hexText->autoSize(flTextFieldAutoSize::RIGHT);
        _hexText->textColor(0x0);
        _hexText->text("");
        _hexText->mouseEnabled(false);
        //addChild(_hexText);
        //------------------------------------------
        
        //------------------------------------------
        _redValueText = new flTextField();
        _redValueText->x(width + 5);
        _redValueText->y(height * 0);
        _redValueText->width(15);
        _redValueText->autoSize(flTextFieldAutoSize::CENTER);
        _redValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _redValueText->text("R");
        _redValueText->mouseEnabled(false);
        addChild(_redValueText);
        _greenValueText = new flTextField();
        _greenValueText->x(width + 5);
        _greenValueText->y(height * 1);
        _greenValueText->width(15);
        _greenValueText->autoSize(flTextFieldAutoSize::CENTER);
        _greenValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _greenValueText->text("G");
        _greenValueText->mouseEnabled(false);
        addChild(_greenValueText);
        _blueValueText = new flTextField();
        _blueValueText->x(width + 5);
        _blueValueText->y(height * 2);
        _blueValueText->width(15);
        _blueValueText->autoSize(flTextFieldAutoSize::CENTER);
        _blueValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _blueValueText->text("B");
        _blueValueText->mouseEnabled(false);
        addChild(_blueValueText);
        _alphaValueText = NULL;
        //------------------------------------------
        
        //------------------------------------------
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        _colorValue.a = 255;
        _hexValue = _colorValue.getHex();
        _hexText->text(ofToString(_hexValue));
        //------------------------------------------

        _updateColor();
        
        _param = NULL;
    }
    
    //--------------------------------------------------------------
    flColorSlider::flColorSlider(int r, int g, int b, int a) {
        //ofLog() << "[flColorSlider]flColorSlider()";

        float width = 200;
        
        _target = this;
        name("flColorSlider");
        
        float height = 18 + 2;
        
        //------------------------------------------
        redSlider = new flSlider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(r);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(redSlider);
        greenSlider = new flSlider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(g);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(greenSlider);
        blueSlider = new flSlider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(b);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(blueSlider);
        alphaSlider = new flSlider(width, 0, 255);
        alphaSlider->x(0);
        alphaSlider->y(height * 3);
        alphaSlider->value(a);
        alphaSlider->roundEnabled(true);
        alphaSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(alphaSlider);
        //------------------------------------------

        //------------------------------------------
        _hexText = new flTextField();
        _hexText->x(0);
        _hexText->y(0);
        _hexText->width(width);
        _hexText->autoSize(flTextFieldAutoSize::RIGHT);
        _hexText->textColor(0x0);
        _hexText->text("");
        _hexText->mouseEnabled(false);
        //addChild(_hexText);
        //------------------------------------------

        //------------------------------------------
        _redValueText = new flTextField();
        _redValueText->x(width + 5);
        _redValueText->y(height * 0);
        _redValueText->width(15);
        _redValueText->autoSize(flTextFieldAutoSize::CENTER);
        _redValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _redValueText->text("R");
        _redValueText->mouseEnabled(false);
        addChild(_redValueText);
        _greenValueText = new flTextField();
        _greenValueText->x(width + 5);
        _greenValueText->y(height * 1);
        _greenValueText->width(15);
        _greenValueText->autoSize(flTextFieldAutoSize::CENTER);
        _greenValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _greenValueText->text("G");
        _greenValueText->mouseEnabled(false);
        addChild(_greenValueText);
        _blueValueText = new flTextField();
        _blueValueText->x(width + 5);
        _blueValueText->y(height * 2);
        _blueValueText->width(15);
        _blueValueText->autoSize(flTextFieldAutoSize::CENTER);
        _blueValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _blueValueText->text("B");
        _blueValueText->mouseEnabled(false);
        addChild(_blueValueText);
        _alphaValueText = new flTextField();
        _alphaValueText->x(width + 5);
        _alphaValueText->y(height * 3);
        _alphaValueText->width(15);
        _alphaValueText->autoSize(flTextFieldAutoSize::CENTER);
        _alphaValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _alphaValueText->text("A");
        _alphaValueText->mouseEnabled(false);
        addChild(_alphaValueText);
        //------------------------------------------
        
        //------------------------------------------
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        _colorValue.a = alphaSlider->value();
        _hexValue = _colorValue.getHex();
        _hexText->text(ofToString(_hexValue));
        //------------------------------------------

        _updateColor();
        
        _param = NULL;
    }
    
    //--------------------------------------------------------------
    flColorSlider::flColorSlider(float width, int r, int g, int b, int a) {
        //ofLog() << "[flColorSlider]flColorSlider()";
        
        _target = this;
        name("flColorSlider");
    
        float height = 18 + 2;
        
        //------------------------------------------
        redSlider = new flSlider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(r);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(redSlider);
        greenSlider = new flSlider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(g);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(greenSlider);
        blueSlider = new flSlider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(b);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(blueSlider);
        alphaSlider = new flSlider(width, 0, 255);
        alphaSlider->x(0);
        alphaSlider->y(height * 3);
        alphaSlider->value(a);
        alphaSlider->roundEnabled(true);
        alphaSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(alphaSlider);
        //------------------------------------------

        //------------------------------------------
        _hexText = new flTextField();
        _hexText->x(0);
        _hexText->y(0);
        _hexText->width(width);
        _hexText->autoSize(flTextFieldAutoSize::RIGHT);
        _hexText->textColor(0x0);
        _hexText->text("");
        _hexText->mouseEnabled(false);
        //addChild(_hexText);
        //------------------------------------------
        
        //------------------------------------------
        _redValueText = new flTextField();
        _redValueText->x(width + 5);
        _redValueText->y(height * 0);
        _redValueText->width(15);
        _redValueText->autoSize(flTextFieldAutoSize::CENTER);
        _redValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _redValueText->text("R");
        _redValueText->mouseEnabled(false);
        addChild(_redValueText);
        _greenValueText = new flTextField();
        _greenValueText->x(width + 5);
        _greenValueText->y(height * 1);
        _greenValueText->width(15);
        _greenValueText->autoSize(flTextFieldAutoSize::CENTER);
        _greenValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _greenValueText->text("G");
        _greenValueText->mouseEnabled(false);
        addChild(_greenValueText);
        _blueValueText = new flTextField();
        _blueValueText->x(width + 5);
        _blueValueText->y(height * 2);
        _blueValueText->width(15);
        _blueValueText->autoSize(flTextFieldAutoSize::CENTER);
        _blueValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _blueValueText->text("B");
        _blueValueText->mouseEnabled(false);
        addChild(_blueValueText);
        _alphaValueText = new flTextField();
        _alphaValueText->x(width + 5);
        _alphaValueText->y(height * 3);
        _alphaValueText->width(15);
        _alphaValueText->autoSize(flTextFieldAutoSize::CENTER);
        _alphaValueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _alphaValueText->text("A");
        _alphaValueText->mouseEnabled(false);
        addChild(_alphaValueText);
        //------------------------------------------
        
        //------------------------------------------
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        _colorValue.a = alphaSlider->value();
        _hexValue = _colorValue.getHex();
        _hexText->text(ofToString(_hexValue));
        //------------------------------------------

        _updateColor();
        
        _param = NULL;
    }
    
    //--------------------------------------------------------------
    flColorSlider::~flColorSlider() {
        //ofLog() << "[flColorSlider]~flColorSlider()";
        
        redSlider->removeEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        delete redSlider;
        redSlider = NULL;
        
        greenSlider->removeEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        delete greenSlider;
        greenSlider = NULL;
        
        blueSlider->removeEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        delete blueSlider;
        blueSlider = NULL;
        
        if(alphaSlider != NULL) {
            alphaSlider->removeEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
            delete alphaSlider;
            alphaSlider = NULL;
        }
        
        delete _hexText;
        _hexText = NULL;

        delete _redValueText;
        _redValueText = NULL;
        
        delete _greenValueText;
        _greenValueText = NULL;
        
        delete _blueValueText;
        _blueValueText = NULL;
        
        delete _alphaValueText;
        _alphaValueText = NULL;
        
        if(_param != NULL) {
            _valueListener.unsubscribe();
            _param = NULL;
        };
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flColorSlider::_setup() {
        //ofLog() << "[flColorSlider]setup()";
    }
    
    //--------------------------------------------------------------
    void flColorSlider::_update() {
        
    }
    
    //--------------------------------------------------------------
    void flColorSlider::_draw() {
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flColorSlider::label() { return _label; }
    void flColorSlider::label(flTextField* value) {
        _label = value;
        redSlider->label(_label);
        greenSlider->label(_label);
        blueSlider->label(_label);
        if(alphaSlider != NULL) alphaSlider->label(_label);
    }
    
    //--------------------------------------------------------------
    ofColor flColorSlider::colorValue() { return _colorValue; }
    void flColorSlider::colorValue(ofColor& value, bool dispatch) {
        ofColor preValue = _colorValue;

        //------------------------------------------
        //Update value.
        _colorValue = value;
        _hexValue = _colorValue.getHex();
        
        redSlider->value(_colorValue.r, false);
        greenSlider->value(_colorValue.g, false);
        blueSlider->value(_colorValue.b, false);
        if(alphaSlider != NULL) alphaSlider->value(_colorValue.a, false);
        //------------------------------------------

        //------------------------------------------
        //Update color.
        _updateColor();
        //------------------------------------------
        
        if(preValue != _colorValue) _changeValue(dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::hexValue() { return _hexValue; }
    void flColorSlider::hexValue(int value, bool dispatch) {
        ofColor preValue = _colorValue;

        //------------------------------------------
        //Update value.
        _hexValue = value;
        _colorValue.setHex(_hexValue);

        redSlider->value(_colorValue.r, false);
        greenSlider->value(_colorValue.g, false);
        blueSlider->value(_colorValue.b, false);
        if(alphaSlider != NULL) alphaSlider->value(_colorValue.a, false);
        //------------------------------------------

        //------------------------------------------
        //Update color.
        _updateColor();
        //------------------------------------------
        
        if(preValue != _colorValue) _changeValue(dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::redValue() { return _colorValue.r; }
    void flColorSlider::redValue(int value, bool dispatch) {
        ofColor preValue = _colorValue;

        //------------------------------------------
        //Update value.
        _colorValue.r = value;
        _hexValue = _colorValue.getHex();
        
        redSlider->value(_colorValue.r, false);
        greenSlider->value(_colorValue.g, false);
        blueSlider->value(_colorValue.b, false);
        if(alphaSlider != NULL) alphaSlider->value(_colorValue.a, false);
        //------------------------------------------
        
        //------------------------------------------
        //Update color.
        _updateColor();
        //------------------------------------------
        
        if(preValue != _colorValue) _changeValue(dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::greenValue() { return _colorValue.g; }
    void flColorSlider::greenValue(int value, bool dispatch) {
        ofColor preValue = _colorValue;
        
        //------------------------------------------
        //Update value.
        _colorValue.g = value;
        _hexValue = _colorValue.getHex();
        
        redSlider->value(_colorValue.r, false);
        greenSlider->value(_colorValue.g, false);
        blueSlider->value(_colorValue.b, false);
        if(alphaSlider != NULL) alphaSlider->value(_colorValue.a, false);
        //------------------------------------------
        
        //------------------------------------------
        //Update color.
        _updateColor();
        //------------------------------------------
        
        if(preValue != _colorValue) _changeValue(dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::blueValue() { return _colorValue.b; }
    void flColorSlider::blueValue(int value, bool dispatch) {
        ofColor preValue = _colorValue;
        
        //------------------------------------------
        //Update value.
        _colorValue.b = value;
        _hexValue = _colorValue.getHex();
        
        redSlider->value(_colorValue.r, false);
        greenSlider->value(_colorValue.g, false);
        blueSlider->value(_colorValue.b, false);
        if(alphaSlider != NULL) alphaSlider->value(_colorValue.a, false);
        //------------------------------------------
        
        //------------------------------------------
        //Update color.
        _updateColor();
        //------------------------------------------
        
        if(preValue != _colorValue) _changeValue(dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::alphaValue() { _colorValue.a; }
    void flColorSlider::alphaValue(int value, bool dispatch) {
        ofColor preValue = _colorValue;
        
        //------------------------------------------
        //Update value.
        _colorValue.a = value;
        _hexValue = _colorValue.getHex();
        
        redSlider->value(_colorValue.r, false);
        greenSlider->value(_colorValue.g, false);
        blueSlider->value(_colorValue.b, false);
        if(alphaSlider != NULL) alphaSlider->value(_colorValue.a, false);
        //------------------------------------------
        
        //------------------------------------------
        //Update color.
        _updateColor();
        //------------------------------------------
        
        if(preValue != _colorValue) _changeValue(dispatch);
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flColorSlider::_changeValue(bool dispatch) {
        if(_param != NULL) {
            _changedValueByMyself = true;
            _param->set(_colorValue);
        }
        
        _hexText->text(ofToString(_hexValue, 2));
        
        //------------------------------------------
        if(dispatch) {
            flColorSliderEvent* colorSliderEvent = new flColorSliderEvent(flColorSliderEvent::CHANGE);
            colorSliderEvent->_target = this;
            colorSliderEvent->__color = _colorValue;
            dispatchEvent(colorSliderEvent);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flColorSlider::_updateColor() {
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        if(alphaSlider != NULL) alphaSlider->barColor(_colorValue);
    }

    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flColorSlider::_eventHandler(flEvent& event) {
        ofColor preValue = _colorValue;
        
        //------------------------------------------
        //Update value.
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        if(alphaSlider != NULL) _colorValue.a = alphaSlider->value();
        _hexValue = _colorValue.getHex();
        //------------------------------------------
        
        //------------------------------------------
        //Update color.
        _updateColor();
        //------------------------------------------
        
        if(preValue != _colorValue) _changeValue();
    }
    
}
