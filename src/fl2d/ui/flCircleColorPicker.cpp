#include "flCircleColorPicker.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flCircleColorPicker::flCircleColorPicker(float width, float height) {
        //ofLog() << "[flCircleColorPicker]flCircleColorPicker()";
        
        _target = this;
        name("flCircleColorPicker");
        
        _uiWidth = width;
        _uiHeight = height;
        
        _radius = _uiWidth * 0.5 - 2;
        
        buttonMode(true);
        
        flGraphics* g;
        g = graphics();
        g->enabledSmoothing(true);
        g->clear();
        g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
        g->drawCircle(_radius + 2, _radius + 1.5, _radius);
        g->endFill();
        
        addEventListener(flMouseEvent::ROLL_OVER, this, &flCircleColorPicker::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flCircleColorPicker::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flCircleColorPicker::_mouseEventHandler);
        ///addEventListener(flMouseEvent::MOUSE_UP, this, &flCircleColorPicker::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_MOVE, this, &flCircleColorPicker::_mouseEventHandler);
        
        //------------------------------------------
        _colorWheelImage = new ofImage();
        _colorWheelImage->load(flDefinition::_COLORWHEEL_IMAGE_PATH);
        //_colorWheelImage->setAnchorPercent(0.5,0.5);
        //        this->width(_uiWidth);
        //        this->height(20 + _uiWidth);
        
        _pixelCaptureImage = new ofImage();
        
        _selectedPixel = new ofColor(255, 255, 255);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    flCircleColorPicker::~flCircleColorPicker() {
        //ofLog() << "[flCircleColorPicker]~flCircleColorPicker()";
        
        _uiWidth = 0.0;
        _uiHeight = 0.0;
        
        _radius = 0.0;
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flCircleColorPicker::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flCircleColorPicker::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flCircleColorPicker::_mouseEventHandler);
        //removeEventListener(flMouseEvent::MOUSE_UP, &flCircleColorPicker::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_MOVE, this, &flCircleColorPicker::_mouseEventHandler);
        
        delete _colorWheelImage;
        _colorWheelImage = NULL;
        
        delete _pixelCaptureImage;
        _pixelCaptureImage = NULL;
        
        delete _selectedPixel;
        _selectedPixel = NULL;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================

    //--------------------------------------------------------------
    void flCircleColorPicker::_setup() {
        //ofLog() << "[SimpleSlider]setup()";
    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_update() {
        flUIBase::_update();

    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_draw() {
        //        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        _colorWheelImage->draw(0, 0, _uiWidth, _uiHeight);
    }
    
    //==============================================================
    // Public Method
    //==============================================================

    //--------------------------------------------------------------
    void flCircleColorPicker::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    const ofColor& flCircleColorPicker::getPixel(int x, int y) {
        ofPoint point = localToGlobal(ofPoint(x, y));
        
        _pixelCaptureImage->grabScreen(point.x, point.y, 1, 1);
        
        int r = _pixelCaptureImage->getPixels()[0];
        int g = _pixelCaptureImage->getPixels()[1];
        int b = _pixelCaptureImage->getPixels()[2];
        
        _selectedPixel->r = r;
        _selectedPixel->g = g;
        _selectedPixel->b = b;
        
        dispatchEvent(new flColorPickerEvent(flColorPickerEvent::CHANGE));
        
        return *_selectedPixel;
    }
    
    //--------------------------------------------------------------
    int flCircleColorPicker::red() { return _selectedPixel->r; }
    //--------------------------------------------------------------
    int flCircleColorPicker::green() { return _selectedPixel->g; }
    //--------------------------------------------------------------
    int flCircleColorPicker::blue() { return _selectedPixel->b; }
    
    //--------------------------------------------------------------
    string flCircleColorPicker::hexCode() {
        _selectedPixel->a = 0;
        
        string returnValue;
        char outStr[256];
        //    sprintf(outStr,"%06x",pixColor.asHex(OF_COLOR_RGB));
        returnValue = outStr;
        
        return returnValue;
    }
    
    //--------------------------------------------------------------
    int flCircleColorPicker::hue() { return _selectedPixel->getHue(); }
    //--------------------------------------------------------------
    int flCircleColorPicker::saturation() { return _selectedPixel->getSaturation(); }
    //--------------------------------------------------------------
    int flCircleColorPicker::brightness() { return _selectedPixel->getBrightness(); }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================

    //--------------------------------------------------------------
    void flCircleColorPicker::_onOver() {
        if(isMouseDown()) return;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_OVER_COLOR.getHex());
        g->drawCircle(_radius + 2, _radius + 1.5, _radius);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_onOut() {
        if(isMouseDown()) return;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
        g->drawCircle(_radius + 2, _radius + 1.5, _radius);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_onPress() {
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_ACTIVE_COLOR.getHex());
        g->drawCircle(_radius + 2, _radius + 1.5, _radius);
        g->endFill();
        
        getPixel(mouseX(), mouseY());
        
        //    ofLog() << "Red: " << red();
        //    ofLog() << "Green: " << green();
        //    ofLog() << "Blue: " << blue();
        //    ofLog() << "Hue: " << hue();
        //    ofLog() << "Saturation: " << saturation();
        //    ofLog() << "Brightness: " << brightness();
        //    ofLog() << "Hexcode: " << hexCode();
    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_onRelease() {
        if(isMouseOver()) {
            _onOver();
            return;
        }
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
        g->drawCircle(_radius + 2, _radius + 1.5, _radius);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_onMove() {
        getPixel(mouseX(), mouseY());
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================

    //--------------------------------------------------------------
    void flCircleColorPicker::_mouseEventHandler(flEvent& event) {
        //ofLog() << "[flCircleColorPicker]_mouseEventHandler(" << event.type();
        //ofLog() << "isMouseDown" << isMouseDown();

        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) _onOver();
        }
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) _onOut();
        }
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this){
                _onPress();
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flCircleColorPicker::_mouseEventHandler);
            }
        }
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(event.currentTarget() == stage()) {
                _onRelease();
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flCircleColorPicker::_mouseEventHandler);
            }
        }
        if(event.type() == flMouseEvent::MOUSE_MOVE) {
            if(event.target() == this){
                if(isMouseDown()) _onMove();
            }
        }
    }
    
}
