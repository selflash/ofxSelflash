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
        
        _vec3Value.x = xSlider->value();
        _vec3Value.y = ySlider->value();
        _vec3Value.z = zSlider->value();
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
    ofVec3f flVec3Slider::vec3Value() { return _vec3Value; }
    void flVec3Slider::vec3Value(ofVec3f value, bool dispatch) {
        _vec3Value = value;
        
        xSlider->value(_vec3Value.x, false);
        ySlider->value(_vec3Value.y, false);
        zSlider->value(_vec3Value.z, false);
        
        //------------------------------------------
        //色の更新
        _vec3Value.x = xSlider->value();
        _vec3Value.y = ySlider->value();
        _vec3Value.z = zSlider->value();
        //------------------------------------------
        
        if(dispatch) {
            flVec3SliderEvent* vec3SliderEvent = new flVec3SliderEvent(flVec3SliderEvent::CHANGE);
            vec3SliderEvent->_target = this;
            vec3SliderEvent->__vec3f = _vec3Value;
            dispatchEvent(vec3SliderEvent);
        }
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flVec3Slider::_eventHandler(flEvent& event) {
        _vec3Value.x = xSlider->value();
        _vec3Value.y = ySlider->value();
        _vec3Value.z = zSlider->value();
        
        flVec3SliderEvent* vec3SliderEvent = new flVec3SliderEvent(flVec3SliderEvent::CHANGE);
        vec3SliderEvent->_target = this;
        vec3SliderEvent->__vec3f = _vec3Value;
        dispatchEvent(vec3SliderEvent);
    }
    
}
