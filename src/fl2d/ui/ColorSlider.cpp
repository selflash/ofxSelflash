#include "ColorSlider.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    ColorSlider::ColorSlider(float width, bool alpha) {
        //cout << "[ColorSlider]ColorSlider()" << endl;
        
        _target = this;
        name("ColorSlider");
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _label = NULL;
        
        //------------------------------------------
        //ラベル
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
        
        float height = 18 + 2;
        
        //------------------------------------------
        //赤
        redSlider = new Slider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(255);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(redSlider);
        //緑
        greenSlider = new Slider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(255);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(greenSlider);
        //青
        blueSlider = new Slider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(255);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(blueSlider);
        if(alpha == true) {
            //透明
            alphaSlider = new Slider(width, 0, 255);
            alphaSlider->x(0);
            alphaSlider->y(height * 3);
            alphaSlider->value(255);
            alphaSlider->roundEnabled(true);
            alphaSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
            addChild(alphaSlider);
        } else {
            alphaSlider = NULL;
        }
        
        //------------------------------------------
        //RED
        _label1Text = new TextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0);
        _label1Text->width(15);
        _label1Text->autoSize(TextFieldAutoSize::CENTER);
        _label1Text->textColor(_labelNormalColor);
        _label1Text->text("R");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //GREEN
        _label2Text = new TextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1);
        _label2Text->width(15);
        _label2Text->autoSize(TextFieldAutoSize::CENTER);
        _label2Text->textColor(_labelNormalColor);
        _label2Text->text("G");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //BLUE
        _label3Text = new TextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2);
        _label3Text->width(15);
        _label3Text->autoSize(TextFieldAutoSize::CENTER);
        _label3Text->textColor(_labelNormalColor);
        _label3Text->text("B");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        if(alphaSlider != NULL) {
            //ALPHA
            _label4Text = new TextField();
            _label4Text->x(width + 5);
            _label4Text->y(height * 3);
            _label4Text->width(15);
            _label4Text->autoSize(TextFieldAutoSize::CENTER);
            _label4Text->textColor(_labelNormalColor);
            _label4Text->text("A");
            _label4Text->mouseEnabled(false);
            addChild(_label4Text);
        }
        //------------------------------------------
        
        _colorValue.r = redSlider->value() / 255.0;
        _colorValue.g = greenSlider->value() / 255.0;
        _colorValue.b = blueSlider->value() / 255.0;
        if(alphaSlider != NULL) {
            _colorValue.a = alphaSlider->value() / 255.0;
        } else {
            _colorValue.a = 1.0;
        }
        _hexValue = _colorValue.getHex();
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        if(alphaSlider != NULL) alphaSlider->barColor(_colorValue);
        
        _hexText->text(ofToString(_hexValue));
    }
    
    //--------------------------------------------------------------
    //
    ColorSlider::ColorSlider(int r, int g, int b) {
        //cout << "[ColorSlider]ColorSlider()" << endl;
        
        float width = 200;
        
        _target = this;
        name("ColorSlider");
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;

        _label = NULL;
        
        //------------------------------------------
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
        
        float height = 18 + 2;
        
        //------------------------------------------
        //赤
        redSlider = new Slider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(r);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(redSlider);
        //緑
        greenSlider = new Slider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(g);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(greenSlider);
        //青
        blueSlider = new Slider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(b);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(blueSlider);
        //透明
        alphaSlider = NULL;
        
        //------------------------------------------
        //RED
        _label1Text = new TextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0);
        _label1Text->width(15);
        _label1Text->autoSize(TextFieldAutoSize::CENTER);
        _label1Text->textColor(_labelNormalColor);
        _label1Text->text("R");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //GREEN
        _label2Text = new TextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1);
        _label2Text->width(15);
        _label2Text->autoSize(TextFieldAutoSize::CENTER);
        _label2Text->textColor(_labelNormalColor);
        _label2Text->text("G");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //BLUE
        _label3Text = new TextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2);
        _label3Text->width(15);
        _label3Text->autoSize(TextFieldAutoSize::CENTER);
        _label3Text->textColor(_labelNormalColor);
        _label3Text->text("B");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        //ALPHA
        _label4Text = NULL;
        //------------------------------------------
        
        _colorValue.r = redSlider->value() / 255.0;
        _colorValue.g = greenSlider->value() / 255.0;
        _colorValue.b = blueSlider->value() / 255.0;
        _colorValue.a = 1.0;
        _hexValue = _colorValue.getHex();
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        
        _hexText->text(ofToString(_hexValue));
    }
    
    //--------------------------------------------------------------
    //
    ColorSlider::ColorSlider(int r, int g, int b, int a) {
        //cout << "[ColorSlider]ColorSlider()" << endl;
        
        float width = 200;
        
        _target = this;
        name("ColorSlider");
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _label = NULL;
        
        //------------------------------------------
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
        
        float height = 18 + 2;
        
        //------------------------------------------
        //赤
        redSlider = new Slider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(r);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(redSlider);
        //緑
        greenSlider = new Slider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(g);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(greenSlider);
        //青
        blueSlider = new Slider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(b);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(blueSlider);
        //透明
        alphaSlider = new Slider(width, 0, 255);
        alphaSlider->x(0);
        alphaSlider->y(height * 3);
        alphaSlider->value(a);
        alphaSlider->roundEnabled(true);
        alphaSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(alphaSlider);
        
        //------------------------------------------
        //RED
        _label1Text = new TextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0);
        _label1Text->width(15);
        _label1Text->autoSize(TextFieldAutoSize::CENTER);
        _label1Text->textColor(_labelNormalColor);
        _label1Text->text("R");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //GREEN
        _label2Text = new TextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1);
        _label2Text->width(15);
        _label2Text->autoSize(TextFieldAutoSize::CENTER);
        _label2Text->textColor(_labelNormalColor);
        _label2Text->text("G");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //BLUE
        _label3Text = new TextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2);
        _label3Text->width(15);
        _label3Text->autoSize(TextFieldAutoSize::CENTER);
        _label3Text->textColor(_labelNormalColor);
        _label3Text->text("B");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        //ALPHA
        _label4Text = new TextField();
        _label4Text->x(width + 5);
        _label4Text->y(height * 3);
        _label4Text->width(15);
        _label4Text->autoSize(TextFieldAutoSize::CENTER);
        _label4Text->textColor(_labelNormalColor);
        _label4Text->text("A");
        _label4Text->mouseEnabled(false);
        addChild(_label4Text);
        //------------------------------------------
        
        _colorValue.r = redSlider->value() / 255.0;
        _colorValue.g = greenSlider->value() / 255.0;
        _colorValue.b = blueSlider->value() / 255.0;
        _colorValue.a = alphaSlider->value() / 255.0;
        _hexValue = _colorValue.getHex();
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        alphaSlider->barColor(_colorValue);
        
        _hexText->text(ofToString(_hexValue));
    }
    
    //--------------------------------------------------------------
    //
    ColorSlider::ColorSlider(float width, int r, int g, int b, int a) {
        //cout << "[ColorSlider]ColorSlider()" << endl;
        
        _target = this;
        name("ColorSlider");
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _label = NULL;

        //------------------------------------------
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
        
        float height = 18 + 2;
        
        //------------------------------------------
        //赤
        redSlider = new Slider(width, 0, 255);
        redSlider->x(0);
        redSlider->y(height * 0);
        redSlider->value(r);
        redSlider->roundEnabled(true);
        redSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(redSlider);
        //緑
        greenSlider = new Slider(width, 0, 255);
        greenSlider->x(0);
        greenSlider->y(height * 1);
        greenSlider->value(g);
        greenSlider->roundEnabled(true);
        greenSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(greenSlider);
        //青
        blueSlider = new Slider(width, 0, 255);
        blueSlider->x(0);
        blueSlider->y(height * 2);
        blueSlider->value(b);
        blueSlider->roundEnabled(true);
        blueSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(blueSlider);
        //透明
        alphaSlider = new Slider(width, 0, 255);
        alphaSlider->x(0);
        alphaSlider->y(height * 3);
        alphaSlider->value(a);
        alphaSlider->roundEnabled(true);
        alphaSlider->addEventListener(SliderEvent::CHANGE, this, &ColorSlider::_eventHandler);
        addChild(alphaSlider);

        //------------------------------------------
        //RED
        _label1Text = new TextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0);
        _label1Text->width(15);
        _label1Text->autoSize(TextFieldAutoSize::CENTER);
        _label1Text->textColor(_labelNormalColor);
        _label1Text->text("R");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //GREEN
        _label2Text = new TextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1);
        _label2Text->width(15);
        _label2Text->autoSize(TextFieldAutoSize::CENTER);
        _label2Text->textColor(_labelNormalColor);
        _label2Text->text("G");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //BLUE
        _label3Text = new TextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2);
        _label3Text->width(15);
        _label3Text->autoSize(TextFieldAutoSize::CENTER);
        _label3Text->textColor(_labelNormalColor);
        _label3Text->text("B");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        //ALPHA
        _label4Text = new TextField();
        _label4Text->x(width + 5);
        _label4Text->y(height * 3);
        _label4Text->width(15);
        _label4Text->autoSize(TextFieldAutoSize::CENTER);
        _label4Text->textColor(_labelNormalColor);
        _label4Text->text("A");
        _label4Text->mouseEnabled(false);
        addChild(_label4Text);
        //------------------------------------------
        
        _colorValue.r = redSlider->value() / 255.0;
        _colorValue.g = greenSlider->value() / 255.0;
        _colorValue.b = blueSlider->value() / 255.0;
        _colorValue.a = alphaSlider->value() / 255.0;
        _hexValue = _colorValue.getHex();
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        alphaSlider->barColor(_colorValue);
        
        _hexText->text(ofToString(_hexValue));
    }

    //--------------------------------------------------------------
    //
    ColorSlider::~ColorSlider() {
        //cout << "[ColorSlider]~ColorSlider()" << endl;
        
        _label = NULL;
        
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
    TextField* ColorSlider::label() { return _label; }
    void ColorSlider::label(TextField* value) { _label = value; }

    //--------------------------------------------------------------
    //
    void ColorSlider::textColor(int color) {
        _label1Text->textColor(color);
        _label2Text->textColor(color);
        _label3Text->textColor(color);
        if(_label4Text != NULL) _label4Text->textColor(color);
    }

    //--------------------------------------------------------------
    //
    ofFloatColor ColorSlider::colorValue() { return _colorValue; }
    void ColorSlider::colorValue(ofFloatColor& value, bool dispatch) {
        redSlider->value(_colorValue.r * 255, false);
        greenSlider->value(_colorValue.g * 255, false);
        blueSlider->value(_colorValue.b * 255, false);
        if(alphaSlider != NULL) alphaSlider->value(_colorValue.a * 255, false);
        
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
    int ColorSlider::alphaValue() {
        if(alphaSlider != NULL) return 255;
        return alphaSlider->value();
    }
    void ColorSlider::alphaValue(int value, bool dispatch) {
        if(alphaSlider != NULL) alphaSlider->value(value, dispatch);
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================

    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void ColorSlider::_eventHandler(Event& event) {
        _colorValue.r = redSlider->value() / 255.0;
        _colorValue.g = greenSlider->value() / 255.0;
        _colorValue.b = blueSlider->value() / 255.0;
        if(alphaSlider != NULL) _colorValue.a = alphaSlider->value() / 255.0;
        _hexValue = _colorValue.getHex();
                
        //------------------------------------------
        
        redSlider->barColor(_colorValue);
        greenSlider->barColor(_colorValue);
        blueSlider->barColor(_colorValue);
        if(alphaSlider != NULL) alphaSlider->barColor(_colorValue);
        //------------------------------------------
        
        ColorSliderEvent* colorSliderEvent = new ColorSliderEvent(ColorSliderEvent::CHANGE);
        colorSliderEvent->_target = this;
        colorSliderEvent->__color = _colorValue;
        dispatchEvent(colorSliderEvent);
        
        _hexText->text(ofToString(_hexValue));
    }

}
