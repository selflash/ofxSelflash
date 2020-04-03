#include "flVec3Slider.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flVec3Slider::flVec3Slider(
                           float width_,
                           float xMin, float xMax, float defaultXValue,
                           float yMin, float yMax, float defaultYValue,
                           float zMin, float zMax, float defaultZValue
                           ) {
        //ofLog() << "[flVec3Slider]flVec3Slider()";

        _target = this;
        name("flVec3Slider");
        
        float width = width_ - 15;
        float height = 18 + 2;
        
        //------------------------------------------
        flGraphics* g;
        g = graphics();
        g->clear();
//        g->lineStyle(1, f lDefinition::UI_LINE_NORMAL_COLOR.getHex());
        g->drawRect(0, 0, width_, 18 * 3 + 2 * 2);
        g->endFill();
        //------------------------------------------
        
        _value.x = defaultXValue;
        _value.y = defaultYValue;
        _value.z = defaultZValue;

        //------------------------------------------
        xSlider = new flSlider(width, xMin, xMax, _value.x);
        xSlider->name("flVec3Slider.xSlider");
        xSlider->x(0);
        xSlider->y(height * 0);
        xSlider->addEventListener(flSliderEvent::CHANGE, this, &flVec3Slider::_eventHandler);
        addChild(xSlider);
        ySlider = new flSlider(width, yMin, yMax, _value.y);
        ySlider->name("flVec3Slider.ySlider");
        ySlider->x(0);
        ySlider->y(height * 1);
        ySlider->addEventListener(flSliderEvent::CHANGE, this, &flVec3Slider::_eventHandler);
        addChild(ySlider);
        zSlider = new flSlider(width, zMin, zMax, _value.z);
        zSlider->name("flVec3Slider.zSlider");
        zSlider->x(0);
        zSlider->y(height * 2);
        zSlider->addEventListener(flSliderEvent::CHANGE, this, &flVec3Slider::_eventHandler);
        addChild(zSlider);
        //------------------------------------------

        //------------------------------------------
        _xLabel = new flTextField();
        _xLabel->name("flVec3Slider.xLabel");
        _xLabel->x(width + 3);
        _xLabel->y(height * 0);
        _xLabel->width(15);
        _xLabel->autoSize(flTextFieldAutoSize::CENTER);
        _xLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _xLabel->text("X");
        _xLabel->mouseEnabled(false);
        addChild(_xLabel);
        _yLabel = new flTextField();
        _yLabel->name("flVec3Slider.yLabel");
        _yLabel->x(width + 3);
        _yLabel->y(height * 1);
        _yLabel->width(15);
        _yLabel->autoSize(flTextFieldAutoSize::CENTER);
        _yLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _yLabel->text("Y");
        _yLabel->mouseEnabled(false);
        addChild(_yLabel);
        _zLabel = new flTextField();
        _zLabel->name("flVec3Slider.zLabel");
        _zLabel->x(width + 3);
        _zLabel->y(height * 2);
        _zLabel->width(15);
        _zLabel->autoSize(flTextFieldAutoSize::CENTER);
        _zLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _zLabel->text("Z");
        _zLabel->mouseEnabled(false);
        addChild(_zLabel);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    flVec3Slider::~flVec3Slider() {
        //ofLog() << "[flVec3Slider]~flVec3Slider()";
        
        xSlider->removeEventListener(flSliderEvent::CHANGE, this, &flVec3Slider::_eventHandler);
        delete xSlider;
        xSlider = NULL;
        
        ySlider->removeEventListener(flSliderEvent::CHANGE, this, &flVec3Slider::_eventHandler);
        delete ySlider;
        ySlider = NULL;
        
        zSlider->removeEventListener(flSliderEvent::CHANGE, this, &flVec3Slider::_eventHandler);
        delete zSlider;
        zSlider = NULL;
        
        delete _xLabel;
        _xLabel = NULL;
        
        delete _yLabel;
        _yLabel = NULL;
        
        delete _zLabel;
        _zLabel = NULL;
        
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
        flUIBase::_update();

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
    void flVec3Slider::_dispatchEvent() {
        flVec3SliderEvent* vec3SliderEvent = new flVec3SliderEvent(flVec3SliderEvent::CHANGE);
        vec3SliderEvent->__value = _value;
        dispatchEvent(vec3SliderEvent);
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
        _dispatchEvent();
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
