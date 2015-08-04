#include "ColorSlider.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    ColorSlider::ColorSlider(float width) {
        //cout << "[ColorSlider]ColorSlider()" << endl;
        
        _target = this;
        name("ColorSlider");
        
        //------------------------------------------
        //ラベル
        _labelText = new TextField();
        _labelText->x(0);
        _labelText->y(0);
        _labelText->width();
        _labelText->autoSize(TextFieldAutoSize::LEFT);
        _labelText->textColor(0x0);
        _labelText->text("COLOR SLIDER");
        _labelText->mouseEnabled(false);
        addChild(_labelText);
        
        _hexText = new TextField();
        _hexText->x(0);
        _hexText->y(0);
        _hexText->width(width);
        _hexText->autoSize(TextFieldAutoSize::RIGHT);
        _hexText->textColor(0x0);
        _hexText->text("");
        _hexText->mouseEnabled(false);
        //addChild(_hexText);
        //------------------------------------------
        
        float height = 15 + 2;
        
        //------------------------------------------
        //赤
        redSlider = new Slider(width, 0, 255);
        redSlider->label("");
        redSlider->x(0);
        redSlider->y(height * 1 - 15);
        redSlider->value(255);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(redSlider);
        //緑
        greenSlider = new Slider(width, 0, 255);
        greenSlider->label("");
        greenSlider->x(0);
        greenSlider->y(height * 2 - 15);
        greenSlider->value(255);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(greenSlider);
        //青
        blueSlider = new Slider(width, 0, 255);
        blueSlider->label("");
        blueSlider->x(0);
        blueSlider->y(height * 3 - 15);
        blueSlider->value(255);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(blueSlider);
        //透明
        alphaSlider = new Slider(width, 0, 255);
        alphaSlider->label("");
        alphaSlider->x(0);
        alphaSlider->y(height * 4 - 15);
        alphaSlider->value(255);
        alphaSlider->roundEnabled(true);
        alphaSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(alphaSlider);

        //------------------------------------------
        //RED
        _label1Text = new TextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 1 + 2);
        _label1Text->width(15);
        _label1Text->autoSize(TextFieldAutoSize::CENTER);
        _label1Text->textColor(0x0);
        _label1Text->text("R");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //GREEN
        _label2Text = new TextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 2 + 2);
        _label2Text->width(15);
        _label2Text->autoSize(TextFieldAutoSize::CENTER);
        _label2Text->textColor(0x0);
        _label2Text->text("G");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //BLUE
        _label3Text = new TextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 3 + 2);
        _label3Text->width(15);
        _label3Text->autoSize(TextFieldAutoSize::CENTER);
        _label3Text->textColor(0x0);
        _label3Text->text("B");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        //ALPHA
        _label4Text = new TextField();
        _label4Text->x(width + 5);
        _label4Text->y(height * 4 + 2);
        _label4Text->width(15);
        _label4Text->autoSize(TextFieldAutoSize::CENTER);
        _label4Text->textColor(0x0);
        _label4Text->text("A");
        _label4Text->mouseEnabled(false);
        addChild(_label4Text);
        //------------------------------------------
        
        _colorValue = new ofFloatColor();
        _colorValue->r = redSlider->value() / 255.0;
        _colorValue->g = greenSlider->value() / 255.0;
        _colorValue->b = blueSlider->value() / 255.0;
        _colorValue->a = alphaSlider->value() / 255.0;
        _hexValue = _colorValue->getHex();
        
        redSlider->barColor(*_colorValue);
        greenSlider->barColor(*_colorValue);
        blueSlider->barColor(*_colorValue);
        alphaSlider->barColor(*_colorValue);
        
        _hexText->text(ofToString(_hexValue));
    }

    //--------------------------------------------------------------
    //
    ColorSlider::~ColorSlider() {
        //cout << "[ColorSlider]~ColorSlider()" << endl;
        
        delete _labelText;
        _labelText = NULL;
        
        delete _hexText;
        _hexText = NULL;
        
        delete redSlider;
        redSlider = NULL;
        
        delete greenSlider;
        greenSlider = NULL;
        
        delete blueSlider;
        blueSlider = NULL;
        
        delete alphaSlider;
        alphaSlider = NULL;
        
        delete _label1Text;
        _label1Text = NULL;
        
        delete _label2Text;
        _label2Text = NULL;
        
        delete _label3Text;
        _label3Text = NULL;
        
        delete _label4Text;
        _label4Text = NULL;
        
        delete _colorValue;
        _colorValue = NULL;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void ColorSlider::_setup() {
        //cout << "[ColorSlider]setup()" << endl;
    }

    //--------------------------------------------------------------
    //
    void ColorSlider::_update() {

    }

    //--------------------------------------------------------------
    //
    void ColorSlider::_draw(){
        
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    string ColorSlider::label() { return _labelText->text(); }
    void ColorSlider::label(string value, int color) {
        _labelText->text(value);
        _labelText->textColor(color);
        _label1Text->textColor(color);
        _label2Text->textColor(color);
        _label3Text->textColor(color);
        _label4Text->textColor(color);
    }
    //--------------------------------------------------------------
    //
    void ColorSlider::textColor(int color) {
        _labelText->textColor(color);
        _label1Text->textColor(color);
        _label2Text->textColor(color);
        _label3Text->textColor(color);
        _label4Text->textColor(color);
    }

    //--------------------------------------------------------------
    //
    const ofFloatColor& ColorSlider::colorValue() { return *_colorValue; }
    void ColorSlider::colorValue(const ofFloatColor& value, bool dispatch) {
        redSlider->value(_colorValue->r * 255, false);
        greenSlider->value(_colorValue->g * 255, false);
        blueSlider->value(_colorValue->b * 255, false);
        alphaSlider->value(_colorValue->a * 255, false);
        
        //------------------------------------------
        //色の更新
        _colorValue->r = redSlider->value();
        _colorValue->g = greenSlider->value();
        _colorValue->g = blueSlider->value();
        _colorValue->a = alphaSlider->value();
        _hexValue = _colorValue->getHex();
        
        redSlider->barColor(*_colorValue);
        greenSlider->barColor(*_colorValue);
        blueSlider->barColor(*_colorValue);
        alphaSlider->barColor(*_colorValue);
        //------------------------------------------
        
        _hexText->text(ofToString(_hexValue));

        if(dispatch) {
            ColorSliderEvent* colorSliderEvent = new ColorSliderEvent(ColorSliderEvent::CHANGE);
            colorSliderEvent->_target = this;
            colorSliderEvent->__color = _colorValue;
            dispatchEvent(colorSliderEvent);
        }
    }

    //--------------------------------------------------------------
    //
    int ColorSlider::hexValue() { return _hexValue; }
    void ColorSlider::hexValue(int value, bool dispatch) { }

    //--------------------------------------------------------------
    //
    int ColorSlider::redValue() { return redSlider->value(); }
    void ColorSlider::redValue(int value, bool dispatch) { redSlider->value(value, dispatch); }

    //--------------------------------------------------------------
    //
    int ColorSlider::greenValue() { return greenSlider->value(); }
    void ColorSlider::greenValue(int value, bool dispatch) { greenSlider->value(value, dispatch); }

    //--------------------------------------------------------------
    //
    int ColorSlider::blueValue() { return blueSlider->value(); }
    void ColorSlider::blueValue(int value, bool dispatch) { blueSlider->value(value, dispatch); }

    //--------------------------------------------------------------
    //
    int ColorSlider::alphaValue() { return alphaSlider->value(); }
    void ColorSlider::alphaValue(int value, bool dispatch) { alphaSlider->value(value, dispatch); }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================

    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void ColorSlider::_eventHandler(Event& event) {
        _colorValue->r = redSlider->value() / 255.0;
        _colorValue->g = greenSlider->value() / 255.0;
        _colorValue->b = blueSlider->value() / 255.0;
        _colorValue->a = alphaSlider->value() / 255.0;
        _hexValue = _colorValue->getHex();
                
        //------------------------------------------
        
        redSlider->barColor(*_colorValue);
        greenSlider->barColor(*_colorValue);
        blueSlider->barColor(*_colorValue);
        alphaSlider->barColor(*_colorValue);
        //------------------------------------------
        
        ColorSliderEvent* colorSliderEvent = new ColorSliderEvent(ColorSliderEvent::CHANGE);
        colorSliderEvent->_target = this;
        colorSliderEvent->__color = _colorValue;
        dispatchEvent(colorSliderEvent);
        
        _hexText->text(ofToString(_hexValue));
    }

}