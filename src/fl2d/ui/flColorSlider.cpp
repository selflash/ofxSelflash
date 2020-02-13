#include "flColorSlider.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
    flColorSlider::flColorSlider(float width, bool alpha) {
        //cout << "[flColorSlider]flColorSlider()" << endl;
        
        _target = this;
        name("flColorSlider");
        
        _label = NULL;
        
        //------------------------------------------
        //ラベル
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
        
        float height = 18 + 2;
        
        //------------------------------------------
        //赤
        redSlider = new flSlider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(255);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(redSlider);
        //緑
        greenSlider = new flSlider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(255);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(greenSlider);
        //青
        blueSlider = new flSlider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(255);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(blueSlider);
        if(alpha == true) {
            //透明
            alphaSlider = new flSlider(width, 0, 255);
            alphaSlider->x(0);
            alphaSlider->y(height * 3);
            alphaSlider->value(255);
            alphaSlider->roundEnabled(true);
            alphaSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
            addChild(alphaSlider);
        } else {
            alphaSlider = NULL;
        }
        
        //------------------------------------------
        //RED
        _label1Text = new flTextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0);
        _label1Text->width(15);
        _label1Text->autoSize(flTextFieldAutoSize::CENTER);
        _label1Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label1Text->text("R");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //GREEN
        _label2Text = new flTextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1);
        _label2Text->width(15);
        _label2Text->autoSize(flTextFieldAutoSize::CENTER);
        _label2Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label2Text->text("G");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //BLUE
        _label3Text = new flTextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2);
        _label3Text->width(15);
        _label3Text->autoSize(flTextFieldAutoSize::CENTER);
        _label3Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label3Text->text("B");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        if(alphaSlider != NULL) {
            //ALPHA
            _label4Text = new flTextField();
            _label4Text->x(width + 5);
            _label4Text->y(height * 3);
            _label4Text->width(15);
            _label4Text->autoSize(flTextFieldAutoSize::CENTER);
            _label4Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
            _label4Text->text("A");
            _label4Text->mouseEnabled(false);
            addChild(_label4Text);
        }
        //------------------------------------------
        
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        if(alphaSlider != NULL) {
            _colorValue.a = alphaSlider->value();
        } else {
            _colorValue.a = 255;
        }
        _hexValue = _colorValue.getHex();
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        if(alphaSlider != NULL) alphaSlider->barColor(_colorValue);
        
        _hexText->text(ofToString(_hexValue));
    }
    
    //--------------------------------------------------------------
    flColorSlider::flColorSlider(int r, int g, int b) {
        //cout << "[flColorSlider]flColorSlider()" << endl;
        
        float width = 200;
        
        _target = this;
        name("flColorSlider");
        
        _label = NULL;
        
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
        
        float height = 18 + 2;
        
        //------------------------------------------
        //赤
        redSlider = new flSlider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(r);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(redSlider);
        //緑
        greenSlider = new flSlider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(g);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(greenSlider);
        //青
        blueSlider = new flSlider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(b);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(blueSlider);
        //透明
        alphaSlider = NULL;
        
        //------------------------------------------
        //RED
        _label1Text = new flTextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0);
        _label1Text->width(15);
        _label1Text->autoSize(flTextFieldAutoSize::CENTER);
        _label1Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label1Text->text("R");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //GREEN
        _label2Text = new flTextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1);
        _label2Text->width(15);
        _label2Text->autoSize(flTextFieldAutoSize::CENTER);
        _label2Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label2Text->text("G");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //BLUE
        _label3Text = new flTextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2);
        _label3Text->width(15);
        _label3Text->autoSize(flTextFieldAutoSize::CENTER);
        _label3Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label3Text->text("B");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        //ALPHA
        _label4Text = NULL;
        //------------------------------------------
        
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        _colorValue.a = 255;
        _hexValue = _colorValue.getHex();
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        
        _hexText->text(ofToString(_hexValue));
    }
    
    //--------------------------------------------------------------
    flColorSlider::flColorSlider(int r, int g, int b, int a) {
        //cout << "[flColorSlider]flColorSlider()" << endl;
        
        float width = 200;
        
        _target = this;
        name("flColorSlider");
        
        _label = NULL;
        
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
        
        float height = 18 + 2;
        
        //------------------------------------------
        //赤
        redSlider = new flSlider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(r);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(redSlider);
        //緑
        greenSlider = new flSlider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(g);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(greenSlider);
        //青
        blueSlider = new flSlider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(b);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(blueSlider);
        //透明
        alphaSlider = new flSlider(width, 0, 255);
        alphaSlider->x(0);
        alphaSlider->y(height * 3);
        alphaSlider->value(a);
        alphaSlider->roundEnabled(true);
        alphaSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(alphaSlider);
        
        //------------------------------------------
        //RED
        _label1Text = new flTextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0);
        _label1Text->width(15);
        _label1Text->autoSize(flTextFieldAutoSize::CENTER);
        _label1Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label1Text->text("R");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //GREEN
        _label2Text = new flTextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1);
        _label2Text->width(15);
        _label2Text->autoSize(flTextFieldAutoSize::CENTER);
        _label2Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label2Text->text("G");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //BLUE
        _label3Text = new flTextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2);
        _label3Text->width(15);
        _label3Text->autoSize(flTextFieldAutoSize::CENTER);
        _label3Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label3Text->text("B");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        //ALPHA
        _label4Text = new flTextField();
        _label4Text->x(width + 5);
        _label4Text->y(height * 3);
        _label4Text->width(15);
        _label4Text->autoSize(flTextFieldAutoSize::CENTER);
        _label4Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label4Text->text("A");
        _label4Text->mouseEnabled(false);
        addChild(_label4Text);
        //------------------------------------------
        
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        _colorValue.a = alphaSlider->value();
        _hexValue = _colorValue.getHex();
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        alphaSlider->barColor(_colorValue);
        
        _hexText->text(ofToString(_hexValue));
    }
    
    //--------------------------------------------------------------
    flColorSlider::flColorSlider(float width, int r, int g, int b, int a) {
        //cout << "[flColorSlider]flColorSlider()" << endl;
        
        _target = this;
        name("flColorSlider");
        
        _label = NULL;
        
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
        
        float height = 18 + 2;
        
        //------------------------------------------
        //赤
        redSlider = new flSlider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(r);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(redSlider);
        //緑
        greenSlider = new flSlider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(g);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(greenSlider);
        //青
        blueSlider = new flSlider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(b);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(blueSlider);
        //透明
        alphaSlider = new flSlider(width, 0, 255);
        alphaSlider->x(0);
        alphaSlider->y(height * 3);
        alphaSlider->value(a);
        alphaSlider->roundEnabled(true);
        alphaSlider->addEventListener(flSliderEvent::CHANGE, this, &flColorSlider::_eventHandler);
        addChild(alphaSlider);
        
        //------------------------------------------
        //RED
        _label1Text = new flTextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0);
        _label1Text->width(15);
        _label1Text->autoSize(flTextFieldAutoSize::CENTER);
        _label1Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label1Text->text("R");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //GREEN
        _label2Text = new flTextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1);
        _label2Text->width(15);
        _label2Text->autoSize(flTextFieldAutoSize::CENTER);
        _label2Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label2Text->text("G");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //BLUE
        _label3Text = new flTextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2);
        _label3Text->width(15);
        _label3Text->autoSize(flTextFieldAutoSize::CENTER);
        _label3Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label3Text->text("B");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        //ALPHA
        _label4Text = new flTextField();
        _label4Text->x(width + 5);
        _label4Text->y(height * 3);
        _label4Text->width(15);
        _label4Text->autoSize(flTextFieldAutoSize::CENTER);
        _label4Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label4Text->text("A");
        _label4Text->mouseEnabled(false);
        addChild(_label4Text);
        //------------------------------------------
        
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        _colorValue.a = alphaSlider->value();
        _hexValue = _colorValue.getHex();
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        alphaSlider->barColor(_colorValue);
        
        _hexText->text(ofToString(_hexValue));
    }
    
    //--------------------------------------------------------------
    flColorSlider::~flColorSlider() {
        //cout << "[flColorSlider]~flColorSlider()" << endl;
        
        _label = NULL;
        
        delete _hexText;
        _hexText = NULL;

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
        
        delete _label1Text;
        _label1Text = NULL;
        
        delete _label2Text;
        _label2Text = NULL;
        
        delete _label3Text;
        _label3Text = NULL;
        
        delete _label4Text;
        _label4Text = NULL;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flColorSlider::_setup() {
        //cout << "[flColorSlider]setup()" << endl;
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
    void flColorSlider::label(flTextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
//    void flColorSlider::textColor(int color) {
//        _label1Text->textColor(color);
//        _label2Text->textColor(color);
//        _label3Text->textColor(color);
//        if(_label4Text != NULL) _label4Text->textColor(color);
//    }
    
    //--------------------------------------------------------------
    ofColor flColorSlider::colorValue() { return _colorValue; }
    void flColorSlider::colorValue(ofColor& value, bool dispatch) {
        redSlider->value(_colorValue.r, false);
        greenSlider->value(_colorValue.g, false);
        blueSlider->value(_colorValue.b, false);
        if(alphaSlider != NULL) alphaSlider->value(_colorValue.a, false);
        
        //------------------------------------------
        //色の更新
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.g = blueSlider->value();
        if(alphaSlider != NULL) _colorValue.a = alphaSlider->value();
        _hexValue = _colorValue.getHex();
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        if(alphaSlider != NULL) alphaSlider->barColor(_colorValue);
        //------------------------------------------
        
        _hexText->text(ofToString(_hexValue));
        
        if(dispatch) {
            flColorSliderEvent* colorSliderEvent = new flColorSliderEvent(flColorSliderEvent::CHANGE);
            colorSliderEvent->_target = this;
            colorSliderEvent->__color = _colorValue;
            dispatchEvent(colorSliderEvent);
        }
    }
    
    //--------------------------------------------------------------
    int flColorSlider::hexValue() { return _hexValue; }
    void flColorSlider::hexValue(int value, bool dispatch) { _updateColor(); }
    
    //--------------------------------------------------------------
    int flColorSlider::redValue() { return redSlider->value(); }
    void flColorSlider::redValue(int value, bool dispatch) { redSlider->value(value, dispatch); _updateColor(); }
    
    //--------------------------------------------------------------
    int flColorSlider::greenValue() { return greenSlider->value(); }
    void flColorSlider::greenValue(int value, bool dispatch) { greenSlider->value(value, dispatch); _updateColor(); }
    
    //--------------------------------------------------------------
    int flColorSlider::blueValue() { return blueSlider->value(); }
    void flColorSlider::blueValue(int value, bool dispatch) { blueSlider->value(value, dispatch); _updateColor(); }
    
    //--------------------------------------------------------------
    int flColorSlider::alphaValue() {
        if(alphaSlider != NULL) return 255;
        return alphaSlider->value();
    }
    void flColorSlider::alphaValue(int value, bool dispatch) {
        if(alphaSlider != NULL) {
            alphaSlider->value(value, dispatch);
             _updateColor();
        }
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flColorSlider::_updateColor() {
        _colorValue.r = redSlider->value();
        _colorValue.g = greenSlider->value();
        _colorValue.b = blueSlider->value();
        if(alphaSlider != NULL) _colorValue.a = alphaSlider->value();
        _hexValue = _colorValue.getHex();
        
        //------------------------------------------
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        if(alphaSlider != NULL) alphaSlider->barColor(_colorValue);
        //------------------------------------------
        
        _hexText->text(ofToString(_hexValue));
    }

    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flColorSlider::_eventHandler(flEvent& event) {
        _updateColor();
        
        flColorSliderEvent* colorSliderEvent = new flColorSliderEvent(flColorSliderEvent::CHANGE);
        colorSliderEvent->_target = this;
        colorSliderEvent->__color = _colorValue;
        dispatchEvent(colorSliderEvent);
    }
    
}
