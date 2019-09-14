#include "Vec2Slider.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    Vec2Slider::Vec2Slider(
                           float width,
                           float xMin, float xMax, float defaultXValue,
                           float yMin, float yMax, float defaultYValue
                           ) {
        //cout << "[Vec2Slider]Vec2Slider()" << endl;
        
        _target = this;
        name("Vec2Slider");
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(FlashConfig::UI_LINE_COLOR);
        _normalColor.setHex(FlashConfig::UI_NORMAL_COLOR);
        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);
        
        _label = NULL;
        
        float height = 18 + 2;
        
        //------------------------------------------
        //X
        xSlider = new Slider(width, xMin, xMax, defaultXValue);
        //        xSlider->label("");
        xSlider->x(0);
        xSlider->y(height * 0);
        xSlider->addEventListener(SliderEvent::CHANGE, this, &Vec2Slider::_eventHandler);
        addChild(xSlider);
        //Y
        ySlider = new Slider(width, yMin, yMax, defaultYValue);
        //        ySlider->label("");
        ySlider->x(0);
        ySlider->y(height * 1);
        ySlider->addEventListener(SliderEvent::CHANGE, this, &Vec2Slider::_eventHandler);
        addChild(ySlider);
        
        //------------------------------------------
        //X
        _label1Text = new TextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0 + 3);
        _label1Text->width(15);
        _label1Text->autoSize(TextFieldAutoSize::CENTER);
        _label1Text->textColor(_labelNormalColor);
        _label1Text->text("X");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //Y
        _label2Text = new TextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1 + 3);
        _label2Text->width(15);
        _label2Text->autoSize(TextFieldAutoSize::CENTER);
        _label2Text->textColor(_labelNormalColor);
        _label2Text->text("Y");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //------------------------------------------
        
        _vec2Value.x = xSlider->value();
        _vec2Value.y = ySlider->value();
    }
    
    //--------------------------------------------------------------
    //
    Vec2Slider::~Vec2Slider() {
        //cout << "[Vec2Slider]~Vec2Slider()" << endl;
        
        _label = NULL;
        
        delete xSlider;
        xSlider = NULL;
        
        delete ySlider;
        ySlider = NULL;
        
        delete _label1Text;
        _label1Text = NULL;
        
        delete _label2Text;
        _label2Text = NULL;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Vec2Slider::_setup() {
        //cout << "[Vec2Slider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    //
    void Vec2Slider::_update() {
        
    }
    
    //--------------------------------------------------------------
    //
    void Vec2Slider::_draw(){
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    TextField* Vec2Slider::label() { return _label; }
    void Vec2Slider::label(TextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    void Vec2Slider::textColor(int color) {
        _label1Text->textColor(color);
        _label2Text->textColor(color);
    }
    
    //--------------------------------------------------------------
    //
    ofVec2f Vec2Slider::vec2Value() { return _vec2Value; }
    void Vec2Slider::vec2Value(ofVec2f value, bool dispatch) {
        _vec2Value = value;
        
        xSlider->value(_vec2Value.x, false);
        ySlider->value(_vec2Value.y, false);
        
        //------------------------------------------
        //色の更新
        _vec2Value.x = xSlider->value();
        _vec2Value.y = ySlider->value();
        //------------------------------------------
        
        if(dispatch) {
            Vec2SliderEvent* vec2SliderEvent = new Vec2SliderEvent(Vec2SliderEvent::CHANGE);
            vec2SliderEvent->_target = this;
            vec2SliderEvent->__vec2f = _vec2Value;
            dispatchEvent(vec2SliderEvent);
        }
    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Vec2Slider::_eventHandler(Event& event) {
        //        ofLog(OF_LOG_VERBOSE) << "[Vec2Slider]_eventHandler(" << event.type() << ")" << endl;
        //        cout << "[Vec2Slider]_eventHandler(" << event.type() << ")" << endl;
        
        _vec2Value.x = xSlider->value();
        _vec2Value.y = ySlider->value();
        //------------------------------------------
        
        Vec2SliderEvent* vec2SliderEvent = new Vec2SliderEvent(Vec2SliderEvent::CHANGE);
        vec2SliderEvent->_target = this;
        vec2SliderEvent->__vec2f = _vec2Value;
        dispatchEvent(vec2SliderEvent);
    }
    
}
