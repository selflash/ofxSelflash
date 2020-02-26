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
        _redLabel = new flTextField();
        _redLabel->x(width + 5);
        _redLabel->y(height * 0);
        _redLabel->width(15);
        _redLabel->autoSize(flTextFieldAutoSize::CENTER);
        _redLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _redLabel->text("R");
        _redLabel->mouseEnabled(false);
        addChild(_redLabel);
        _greenLabel = new flTextField();
        _greenLabel->x(width + 5);
        _greenLabel->y(height * 1);
        _greenLabel->width(15);
        _greenLabel->autoSize(flTextFieldAutoSize::CENTER);
        _greenLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _greenLabel->text("G");
        _greenLabel->mouseEnabled(false);
        addChild(_greenLabel);
        _blueLabel = new flTextField();
        _blueLabel->x(width + 5);
        _blueLabel->y(height * 2);
        _blueLabel->width(15);
        _blueLabel->autoSize(flTextFieldAutoSize::CENTER);
        _blueLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _blueLabel->text("B");
        _blueLabel->mouseEnabled(false);
        addChild(_blueLabel);
        if(alphaEnabled == true) {
            _alphaLabel = new flTextField();
            _alphaLabel->x(width + 5);
            _alphaLabel->y(height * 3);
            _alphaLabel->width(15);
            _alphaLabel->autoSize(flTextFieldAutoSize::CENTER);
            _alphaLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
            _alphaLabel->text("A");
            _alphaLabel->mouseEnabled(false);
            addChild(_alphaLabel);
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
        _redLabel = new flTextField();
        _redLabel->x(width + 5);
        _redLabel->y(height * 0);
        _redLabel->width(15);
        _redLabel->autoSize(flTextFieldAutoSize::CENTER);
        _redLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _redLabel->text("R");
        _redLabel->mouseEnabled(false);
        addChild(_redLabel);
        _greenLabel = new flTextField();
        _greenLabel->x(width + 5);
        _greenLabel->y(height * 1);
        _greenLabel->width(15);
        _greenLabel->autoSize(flTextFieldAutoSize::CENTER);
        _greenLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _greenLabel->text("G");
        _greenLabel->mouseEnabled(false);
        addChild(_greenLabel);
        _blueLabel = new flTextField();
        _blueLabel->x(width + 5);
        _blueLabel->y(height * 2);
        _blueLabel->width(15);
        _blueLabel->autoSize(flTextFieldAutoSize::CENTER);
        _blueLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _blueLabel->text("B");
        _blueLabel->mouseEnabled(false);
        addChild(_blueLabel);
        _alphaLabel = NULL;
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
        _redLabel = new flTextField();
        _redLabel->x(width + 5);
        _redLabel->y(height * 0);
        _redLabel->width(15);
        _redLabel->autoSize(flTextFieldAutoSize::CENTER);
        _redLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _redLabel->text("R");
        _redLabel->mouseEnabled(false);
        addChild(_redLabel);
        _greenLabel = new flTextField();
        _greenLabel->x(width + 5);
        _greenLabel->y(height * 1);
        _greenLabel->width(15);
        _greenLabel->autoSize(flTextFieldAutoSize::CENTER);
        _greenLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _greenLabel->text("G");
        _greenLabel->mouseEnabled(false);
        addChild(_greenLabel);
        _blueLabel = new flTextField();
        _blueLabel->x(width + 5);
        _blueLabel->y(height * 2);
        _blueLabel->width(15);
        _blueLabel->autoSize(flTextFieldAutoSize::CENTER);
        _blueLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _blueLabel->text("B");
        _blueLabel->mouseEnabled(false);
        addChild(_blueLabel);
        _alphaLabel = new flTextField();
        _alphaLabel->x(width + 5);
        _alphaLabel->y(height * 3);
        _alphaLabel->width(15);
        _alphaLabel->autoSize(flTextFieldAutoSize::CENTER);
        _alphaLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _alphaLabel->text("A");
        _alphaLabel->mouseEnabled(false);
        addChild(_alphaLabel);
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
        _redLabel = new flTextField();
        _redLabel->x(width + 5);
        _redLabel->y(height * 0);
        _redLabel->width(15);
        _redLabel->autoSize(flTextFieldAutoSize::CENTER);
        _redLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _redLabel->text("R");
        _redLabel->mouseEnabled(false);
        addChild(_redLabel);
        _greenLabel = new flTextField();
        _greenLabel->x(width + 5);
        _greenLabel->y(height * 1);
        _greenLabel->width(15);
        _greenLabel->autoSize(flTextFieldAutoSize::CENTER);
        _greenLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _greenLabel->text("G");
        _greenLabel->mouseEnabled(false);
        addChild(_greenLabel);
        _blueLabel = new flTextField();
        _blueLabel->x(width + 5);
        _blueLabel->y(height * 2);
        _blueLabel->width(15);
        _blueLabel->autoSize(flTextFieldAutoSize::CENTER);
        _blueLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _blueLabel->text("B");
        _blueLabel->mouseEnabled(false);
        addChild(_blueLabel);
        _alphaLabel = new flTextField();
        _alphaLabel->x(width + 5);
        _alphaLabel->y(height * 3);
        _alphaLabel->width(15);
        _alphaLabel->autoSize(flTextFieldAutoSize::CENTER);
        _alphaLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _alphaLabel->text("A");
        _alphaLabel->mouseEnabled(false);
        addChild(_alphaLabel);
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

        delete _redLabel;
        _redLabel = NULL;
        
        delete _greenLabel;
        _greenLabel = NULL;
        
        delete _blueLabel;
        _blueLabel = NULL;
        
        delete _alphaLabel;
        _alphaLabel = NULL;
        
        //------------------------------------------
        _colorParam = NULL;
        _listeners.unsubscribeAll();
        //------------------------------------------
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
        _bChangedByOfParm["value"] = false;
    }
    
    //--------------------------------------------------------------
    void flColorSlider::_draw() {
//        //--------------------------------------
//        float height = 18 + 2;
//        ofPushStyle();
//        ofSetColor(255, 255, 255);
//        flFont::drawString("R", redSlider->width() + 5, height * 0);
//        flFont::drawString("G", redSlider->width() + 5, height * 1);
//        flFont::drawString("B", redSlider->width() + 5, height * 2);
//        ofPopStyle();
//        //--------------------------------------
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flColorSlider::label(flTextField* value) {
        _label = value;
        redSlider->label(_label);
        greenSlider->label(_label);
        blueSlider->label(_label);
        if(alphaSlider != NULL) alphaSlider->label(_label);
    }
    
    //--------------------------------------------------------------
    void flColorSlider::enabled(bool value) {
        _enabled = value;
        mouseChildren(_enabled);
        
//        mouseEnabled(_enabled);
        redSlider->enabled(_enabled);
        greenSlider->enabled(_enabled);
        blueSlider->enabled(_enabled);
        if(alphaSlider != NULL) alphaSlider->enabled(_enabled);
    }
    
    //--------------------------------------------------------------
    ofColor flColorSlider::colorValue() { return _colorValue; }
    void flColorSlider::colorValue(ofColor value, bool dispatch) {
//        ofLog() << "[flColorSlider]colorValue()";

        redSlider->value(value.r, dispatch);
        greenSlider->value(value.g, dispatch);
        blueSlider->value(value.b, dispatch);
        if(alphaSlider != NULL) alphaSlider->value(value.a, dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::hexValue() { return _hexValue; }
    void flColorSlider::hexValue(int value, bool dispatch) {
        ofColor tempValue = _colorValue;
        tempValue.setHex(value);
        
        redSlider->value(tempValue.r, dispatch);
        greenSlider->value(tempValue.g, dispatch);
        blueSlider->value(tempValue.b, dispatch);
        if(alphaSlider != NULL) alphaSlider->value(tempValue.a, dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::redValue() { return _colorValue.r; }
    void flColorSlider::redValue(int value, bool dispatch) {
        redSlider->value(value, dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::greenValue() { return _colorValue.g; }
    void flColorSlider::greenValue(int value, bool dispatch) {
        greenSlider->value(value, dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::blueValue() { return _colorValue.b; }
    void flColorSlider::blueValue(int value, bool dispatch) {
        blueSlider->value(value, dispatch);
    }
    
    //--------------------------------------------------------------
    int flColorSlider::alphaValue() { _colorValue.a; }
    void flColorSlider::alphaValue(int value, bool dispatch) {
        if(alphaSlider != NULL) alphaSlider->value(value, dispatch);
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flColorSlider::_changeValue(bool dispatch) {
        _hexText->text(ofToString(_hexValue, 2));
        
        //------------------------------------------
        if(dispatch) {
            flColorSliderEvent* colorSliderEvent = new flColorSliderEvent(flColorSliderEvent::CHANGE);
            colorSliderEvent->__color = _colorValue;
            dispatchEvent(colorSliderEvent);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flColorSlider::_updateColor() {
//        ofLog() << "[flColorSlider]_updateColor()";
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        if(alphaSlider != NULL) alphaSlider->barColor(_colorValue);
    }

    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flColorSlider::_eventHandler(flEvent& event) {
//        ofLog() << "[flColorSlider]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flColorSlider]this          = " << this << "," << ((flDisplayObject*) this)->name();
//        ofLog() << "[flColorSlider]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flColorSlider]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();

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
        
        //------------------------------------------
        if(preValue != _colorValue) {
            _changeValue();
        
            if(!_bChangedByOfParm["value"]) {
                if(_colorParam != NULL) {
                    _bChangedByMyself["value"] = true;
                    _colorParam->set(_colorValue);
                }
            }
        }
        //------------------------------------------
    }
    
}
