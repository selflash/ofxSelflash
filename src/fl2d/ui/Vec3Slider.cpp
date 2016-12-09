#include "Vec3Slider.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Vec3Slider::Vec3Slider(
                           float width,
                           float xMin, float xMax, float defaultXValue,
                           float yMin, float yMax, float defaultYValue,
                           float zMin, float zMax, float defaultZValue
                           ) {
        //cout << "[Vec3Slider]Vec3Slider()" << endl;
        
        _target = this;
        name("Vec3Slider");
        
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
        xSlider->addEventListener(SliderEvent::CHANGE, this, &Vec3Slider::_eventHandler);
        addChild(xSlider);
        //Y
        ySlider = new Slider(width, yMin, yMax, defaultYValue);
//        ySlider->label("");
        ySlider->x(0);
        ySlider->y(height * 1);
        ySlider->addEventListener(SliderEvent::CHANGE, this, &Vec3Slider::_eventHandler);
        addChild(ySlider);
        //Z
        zSlider = new Slider(width, zMin, zMax, defaultZValue);
//        zSlider->label("");
        zSlider->x(0);
        zSlider->y(height * 2);
        zSlider->addEventListener(SliderEvent::CHANGE, this, &Vec3Slider::_eventHandler);
        addChild(zSlider);

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
        //Z
        _label3Text = new TextField();
        _label3Text->x(width + 5);
        _label3Text->y(height * 2 + 3);
        _label3Text->width(15);
        _label3Text->autoSize(TextFieldAutoSize::CENTER);
        _label3Text->textColor(_labelNormalColor);
        _label3Text->text("Z");
        _label3Text->mouseEnabled(false);
        addChild(_label3Text);
        //------------------------------------------
        
        _vec3Value.x = xSlider->value();
        _vec3Value.y = ySlider->value();
        _vec3Value.z = zSlider->value();
    }

    //--------------------------------------------------------------
    //
    Vec3Slider::~Vec3Slider() {
        //cout << "[Vec3Slider]~Vec3Slider()" << endl;
        
        _label = NULL;

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
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void Vec3Slider::_setup() {
        //cout << "[Vec3Slider]setup()" << endl;
    }

    //--------------------------------------------------------------
    //
    void Vec3Slider::_update() {

    }

    //--------------------------------------------------------------
    //
    void Vec3Slider::_draw(){
        
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    TextField* Vec3Slider::label() { return _label; }
    void Vec3Slider::label(TextField* value) { _label = value; }

    //--------------------------------------------------------------
    //
    void Vec3Slider::textColor(int color) {
        _label1Text->textColor(color);
        _label2Text->textColor(color);
        _label3Text->textColor(color);
    }

    //--------------------------------------------------------------
    //
    ofVec3f Vec3Slider::vec3Value() { return _vec3Value; }
    void Vec3Slider::vec3Value(ofVec3f value, bool dispatch) {
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
            Vec3SliderEvent* vec3SliderEvent = new Vec3SliderEvent(Vec3SliderEvent::CHANGE);
            vec3SliderEvent->_target = this;
            vec3SliderEvent->__vec3f = _vec3Value;
            dispatchEvent(vec3SliderEvent);
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
    void Vec3Slider::_eventHandler(Event& event) {
//        ofLog(OF_LOG_VERBOSE) << "[Vec3Slider]_eventHandler(" << event.type() << ")" << endl;
//        cout << "[Vec3Slider]_eventHandler(" << event.type() << ")" << endl;
        
        _vec3Value.x = xSlider->value();
        _vec3Value.y = ySlider->value();
        _vec3Value.z = zSlider->value();
        //------------------------------------------
        
        Vec3SliderEvent* vec3SliderEvent = new Vec3SliderEvent(Vec3SliderEvent::CHANGE);
        vec3SliderEvent->_target = this;
        vec3SliderEvent->__vec3f = _vec3Value;
        dispatchEvent(vec3SliderEvent);
    }

}
