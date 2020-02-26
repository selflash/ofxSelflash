#include "flVec3Slider.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flVec3Slider::flVec3Slider(
                           float width,
                           float xMin, float xMax, float defaultXValue,
                           float yMin, float yMax, float defaultYValue,
                           float zMin, float zMax, float defaultZValue
                           ) {
        //ofLog() << "[flVec3Slider]flVec3Slider()";

        _target = this;
        name("flVec3Slider");
        
        float height = 18 + 2;
        
        //------------------------------------------
        //X
        xSlider = new flSlider(width, xMin, xMax, defaultXValue);
        //        xSlider->label("");
        xSlider->x(0);
        xSlider->y(height * 0);
        xSlider->addEventListener(flSliderEvent::CHANGE, this, &flVec3Slider::_eventHandler);
        addChild(xSlider);
        //Y
        ySlider = new flSlider(width, yMin, yMax, defaultYValue);
        //        ySlider->label("");
        ySlider->x(0);
        ySlider->y(height * 1);
        ySlider->addEventListener(flSliderEvent::CHANGE, this, &flVec3Slider::_eventHandler);
        addChild(ySlider);
        //Z
        zSlider = new flSlider(width, zMin, zMax, defaultZValue);
        //        zSlider->label("");
        zSlider->x(0);
        zSlider->y(height * 2);
        zSlider->addEventListener(flSliderEvent::CHANGE, this, &flVec3Slider::_eventHandler);
        addChild(zSlider);
        
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
        //Z
        _label3Text = new flTextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2 + 3);
        _label3Text->width(15);
        _label3Text->autoSize(flTextFieldAutoSize::CENTER);
        _label3Text->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _label3Text->text("Z");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        //------------------------------------------
        
        _value.x = xSlider->value();
        _value.y = ySlider->value();
        _value.z = zSlider->value();
    }
    
    //--------------------------------------------------------------
    flVec3Slider::~flVec3Slider() {
        //ofLog() << "[flVec3Slider]~flVec3Slider()";
        
        delete xSlider;
        xSlider = NULL;
        
        delete ySlider;
        ySlider = NULL;
        
        delete zSlider;
        zSlider = NULL;
        
        delete _label1Text;
        _label1Text = NULL;
        
        delete _label2Text;
        _label2Text = NULL;
        
        delete _label3Text;
        _label3Text = NULL;
        
        //------------------------------------------
        _vec3Param = NULL;
        _listeners.unsubscribeAll();
        //------------------------------------------
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flVec3Slider::_setup() {
        //ofLog() << "[flVec3Slider]setup()";
    }
    
    //--------------------------------------------------------------
    void flVec3Slider::_update() {
        _bChangedByOfParm["value"] = false;
    }
    
    //--------------------------------------------------------------
    void flVec3Slider::_draw(){
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flVec3Slider::label(flTextField* value) {
        _label = value;
        xSlider->label(_label);
        ySlider->label(_label);
        zSlider->label(_label);
        
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flVec3Slider::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        xSlider->enabled(_enabled);
        ySlider->enabled(_enabled);
        zSlider->enabled(_enabled);
    }
    
    //----------------------------------
    float flVec3Slider::min() { xSlider->min(); }
    void flVec3Slider::min(float value, bool dispatch) {
        xSlider->min(value, dispatch);
        ySlider->min(value, dispatch);
        zSlider->min(value, dispatch);
    }
    
    //----------------------------------
    float flVec3Slider::max() { xSlider->max(); }
    void flVec3Slider::max(float value, bool dispatch) {
        xSlider->max(value, dispatch);
        ySlider->max(value, dispatch);
        zSlider->max(value, dispatch);
    }
    
    //--------------------------------------------------------------
    vec3 flVec3Slider::value() { return _value; }
    void flVec3Slider::value(vec3 value, bool dispatch) {
        xSlider->value(value.x, dispatch);
        ySlider->value(value.y, dispatch);
        zSlider->value(value.z, dispatch);
    }
    
    //----------------------------------
    float flVec3Slider::xValue() { return xSlider->value(); }
    void flVec3Slider::xValue(float value, bool dispatch) {
        xSlider->value(value, dispatch);
    }
    
    //----------------------------------
    float flVec3Slider::yValue() { return ySlider->value(); }
    void flVec3Slider::yValue(float value, bool dispatch) {
        ySlider->value(value, dispatch);
    }
    
    //----------------------------------
    float flVec3Slider::zValue() { return zSlider->value(); }
    void flVec3Slider::zValue(float value, bool dispatch) {
        zSlider->value(value, dispatch);
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flVec3Slider::_changeValue(bool dispatch) {
        //------------------------------------------
        if(dispatch) {
            flVec3SliderEvent* vec3SliderEvent = new flVec3SliderEvent(flVec3SliderEvent::CHANGE);
            vec3SliderEvent->__value = _value;
            dispatchEvent(vec3SliderEvent);
        }
        //------------------------------------------
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flVec3Slider::_eventHandler(flEvent& event) {
        _value.x = xSlider->value();
        _value.y = ySlider->value();
        _value.z = zSlider->value();
        
        //------------------------------------------
        _changeValue();
        //------------------------------------------
        
        //------------------------------------------
        if(!_bChangedByOfParm["value"]) {
            if(_vec3Param != NULL) {
                _bChangedByMyself["value"] = true;
                _vec3Param->set(_value);
            }
        }
        //------------------------------------------
    }
    
}
