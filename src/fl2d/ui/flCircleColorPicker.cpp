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
        
        addEventListener(flMouseEvent::MOUSE_OVER, this, &flCircleColorPicker::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_OUT, this, &flCircleColorPicker::_mouseEventHandler);
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
        
        removeEventListener(flMouseEvent::MOUSE_OVER, this, &flCircleColorPicker::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_OUT, this, &flCircleColorPicker::_mouseEventHandler);
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
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_setup() {
        //ofLog() << "[SimpleSlider]setup()";
    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_update() {
        
    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_draw() {
        //        ofSetColor(255, 255, 255, 255 * _compoundAlpha);
        _colorWheelImage->draw(0, 0, _uiWidth, _uiHeight);
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flCircleColorPicker::label() { return _label; }
    void flCircleColorPicker::label(flTextField* value) { _label = value; }
    
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
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_over() {
        if(isMouseDown()) return;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_OVER_COLOR.getHex());
        g->drawCircle(_radius + 2, _radius + 1.5, _radius);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_out() {
        if(isMouseDown()) return;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
        g->drawCircle(_radius + 2, _radius + 1.5, _radius);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_press() {
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
    void flCircleColorPicker::_release() {
        if(isMouseOver()) {
            _over();
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
    void flCircleColorPicker::_move() {
        getPixel(mouseX(), mouseY());
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    void flCircleColorPicker::_mouseEventHandler(flEvent& event) {
        //ofLog() << "[flCircleColorPicker]_mouseEventHandler(" << event.type();
        //ofLog() << "isMouseDown" << isMouseDown();
        
        if(event.type() == flMouseEvent::MOUSE_OVER) {
            if(event.target() == this) _over();
        }
        if(event.type() == flMouseEvent::MOUSE_OUT) {
            if(event.target() == this) _out();
        }
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this){
                _press();
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flCircleColorPicker::_mouseEventHandler);
            }
        }
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(event.currentTarget() == stage()) {
                _release();
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flCircleColorPicker::_mouseEventHandler);
            }
        }
        if(event.type() == flMouseEvent::MOUSE_MOVE) {
            if(event.target() == this){
                if(isMouseDown()) _move();
            }
        }
    }
    
}
