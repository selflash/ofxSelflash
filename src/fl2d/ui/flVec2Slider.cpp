#include "flVec2Slider.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flVec2Slider::flVec2Slider(
                           float width,
                           float xMin, float xMax, float defaultXValue,
                           float yMin, float yMax, float defaultYValue
                           ) {
        //ofLog() << "[flVec2Slider]flVec2Slider()";

        _target = this;
        name("flVec2Slider");
        
        float height = 18 + 2;
        
        //------------------------------------------
        //X
        xSlider = new flSlider(width, xMin, xMax, defaultXValue);
        //        xSlider->label("");
        xSlider->x(0);
        xSlider->y(height * 0);
        xSlider->addEventListener(flSliderEvent::CHANGE, this, &flVec2Slider::_eventHandler);
        addChild(xSlider);
        //Y
        ySlider = new flSlider(width, yMin, yMax, defaultYValue);
        //        ySlider->label("");
        ySlider->x(0);
        ySlider->y(height * 1);
        ySlider->addEventListener(flSliderEvent::CHANGE, this, &flVec2Slider::_eventHandler);
        addChild(ySlider);
        
        //------------------------------------------
        //X
        _label1Text = new flTextField();
        _label1Text->x(width + 5);
        _label1Text->y(height * 0 + 3);
        _label1Text->width(15);
        _label1Text->autoSize(flTextFieldAutoSize::CENTER);
        _label1Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label1Text->text("X");
        _label1Text->mouseEnabled(false);
        addChild(_label1Text);
        //Y
        _label2Text = new flTextField();
        _label2Text->x(width + 5);
        _label2Text->y(height * 1 + 3);
        _label2Text->width(15);
        _label2Text->autoSize(flTextFieldAutoSize::CENTER);
        _label2Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label2Text->text("Y");
        _label2Text->mouseEnabled(false);
        addChild(_label2Text);
        //------------------------------------------
        
        _vec2Value.x = xSlider->value();
        _vec2Value.y = ySlider->value();
    }
    
    //--------------------------------------------------------------
    flVec2Slider::~flVec2Slider() {
        //ofLog() << "[flVec2Slider]~flVec2Slider()";
        
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
    void flVec2Slider::_setup() {
        //ofLog() << "[flVec2Slider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    void flVec2Slider::_update() {
        
    }
    
    //--------------------------------------------------------------
    void flVec2Slider::_draw(){
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flVec2Slider::label() { return _label; }
    void flVec2Slider::label(flTextField* value) {
        _label = value;
        xSlider->label(_label);
        ySlider->label(_label);
    }

    //--------------------------------------------------------------
    ofVec2f flVec2Slider::vec2Value() { return _vec2Value; }
    void flVec2Slider::vec2Value(ofVec2f value, bool dispatch) {
        _vec2Value = value;
        
        xSlider->value(_vec2Value.x, false);
        ySlider->value(_vec2Value.y, false);
        
        //------------------------------------------
        //色の更新
        _vec2Value.x = xSlider->value();
        _vec2Value.y = ySlider->value();
        //------------------------------------------
        
        if(dispatch) {
            flVec2SliderEvent* vec2SliderEvent = new flVec2SliderEvent(flVec2SliderEvent::CHANGE);
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
    void flVec2Slider::_eventHandler(flEvent& event) {
//        ofLog(OF_LOG_VERBOSE) << "[flVec2Slider]_eventHandler(" << event.type() << ")";
//        ofLog() << "[flVec2Slider]_eventHandler(" << event.type() << ")";
        
        _vec2Value.x = xSlider->value();
        _vec2Value.y = ySlider->value();
        //------------------------------------------
        
        flVec2SliderEvent* vec2SliderEvent = new flVec2SliderEvent(flVec2SliderEvent::CHANGE);
        vec2SliderEvent->_target = this;
        vec2SliderEvent->__vec2f = _vec2Value;
        dispatchEvent(vec2SliderEvent);
    }
    
}
