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
        
        _value.x = defaultXValue;
        _value.y = defaultYValue;
        
        //------------------------------------------
        xSlider = new flSlider(width, xMin, xMax, _value.x);
        xSlider->name("flVec2Slider.xSlider");
        xSlider->x(0);
        xSlider->y(height * 0);
        xSlider->addEventListener(flSliderEvent::CHANGE, this, &flVec2Slider::_eventHandler);
        addChild(xSlider);
        ySlider = new flSlider(width, yMin, yMax, _value.y);
        ySlider->name("flVec2Slider.ySlider");
        ySlider->x(0);
        ySlider->y(height * 1);
        ySlider->addEventListener(flSliderEvent::CHANGE, this, &flVec2Slider::_eventHandler);
        addChild(ySlider);
        //------------------------------------------

        //------------------------------------------
        _xLabel = new flTextField();
        _xLabel->name("flVec2Slider.xLabel");
        _xLabel->x(width + 5);
        _xLabel->y(height * 0 + 3);
        _xLabel->width(15);
        _xLabel->autoSize(flTextFieldAutoSize::CENTER);
        _xLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _xLabel->text("X");
        _xLabel->mouseEnabled(false);
        addChild(_xLabel);
        _yLabel = new flTextField();
        _yLabel->name("flVec2Slider.yLabel");
        _yLabel->x(width + 5);
        _yLabel->y(height * 1 + 3);
        _yLabel->width(15);
        _yLabel->autoSize(flTextFieldAutoSize::CENTER);
        _yLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _yLabel->text("Y");
        _yLabel->mouseEnabled(false);
        addChild(_yLabel);
        //------------------------------------------
        
    }
    
    //--------------------------------------------------------------
    flVec2Slider::~flVec2Slider() {
        //ofLog() << "[flVec2Slider]~flVec2Slider()";
        
        delete xSlider;
        xSlider = NULL;
        
        delete ySlider;
        ySlider = NULL;
        
        delete _xLabel;
        _xLabel = NULL;
        
        delete _yLabel;
        _yLabel = NULL;
        
        //------------------------------------------
        _vec2Param = NULL;
        _listeners.unsubscribeAll();
        //------------------------------------------
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flVec2Slider::_setup() {
        //ofLog() << "[flVec2Slider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    void flVec2Slider::_update() {
        _bChangedByOfParm["value"] = false;
    }
    
    //--------------------------------------------------------------
    void flVec2Slider::_draw(){
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flVec2Slider::label(flTextField* value) {
        _label = value;
        xSlider->label(_label);
        ySlider->label(_label);
        
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flVec2Slider::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        xSlider->enabled(_enabled);
        ySlider->enabled(_enabled);
    }
    
    //--------------------------------------------------------------
    float flVec2Slider::min() { xSlider->min(); }
    void flVec2Slider::min(float value, bool dispatch) {
        xSlider->min(value, dispatch);
        ySlider->min(value, dispatch);
    }
    
    //--------------------------------------------------------------
    float flVec2Slider::max() { xSlider->max(); }
    void flVec2Slider::max(float value, bool dispatch) {
        xSlider->max(value, dispatch);
        ySlider->max(value, dispatch);
    }
    
    //--------------------------------------------------------------
    vec2 flVec2Slider::value() {
        _value.x = xSlider->value();
        _value.y = ySlider->value();
        return _value;
    }
    void flVec2Slider::value(vec2 value, bool dispatch) {
        xSlider->value(value.x, dispatch);
        ySlider->value(value.y, dispatch);
    }
    
    //--------------------------------------------------------------
    float flVec2Slider::xValue() { return xSlider->value(); }
    void flVec2Slider::xValue(float value, bool dispatch) {
        xSlider->value(value, dispatch);
    }
    
    //--------------------------------------------------------------
    float flVec2Slider::yValue() { return ySlider->value(); }
    void flVec2Slider::yValue(float value, bool dispatch) {
        ySlider->value(value, dispatch);
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flVec2Slider::_changeValue(bool dispatch) {
        //------------------------------------------
        if(dispatch) {
            flVec2SliderEvent* vec2SliderEvent = new flVec2SliderEvent(flVec2SliderEvent::CHANGE);
            vec2SliderEvent->__value = _value;
            dispatchEvent(vec2SliderEvent);
        }
        //------------------------------------------
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flVec2Slider::_eventHandler(flEvent& event) {
//        ofLog() << "[flVec2Slider]_eventHandler(" << event.type() << ")";
        
        _value.x = xSlider->value();
        _value.y = ySlider->value();
        
        //------------------------------------------
        _changeValue();
        //------------------------------------------
        
        //------------------------------------------
        if(!_bChangedByOfParm["value"]) {
            if(_vec2Param != NULL) {
                _bChangedByMyself["value"] = true;
                _vec2Param->set(_value);
            }
        }
        //------------------------------------------
    }
    
}
