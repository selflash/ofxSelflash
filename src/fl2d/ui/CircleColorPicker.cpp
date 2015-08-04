#include "CircleColorPicker.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    CircleColorPicker::CircleColorPicker(float width, float height) {
        //cout << "[CircleColorPicker]CircleColorPicker()" << endl;
        
        _target = this;
        name("CircleColorPicker");
        
        _imageWidth = width;
        _imageHeight = height;
        
        _radius = _imageWidth * 0.5f - 2;
        
        _lineColor = FlashConfig::UI_LINE_COLOR;
        _normalColor = FlashConfig::UI_NORMAL_COLOR;
        _overColor = FlashConfig::UI_OVER_COLOR;
        _activeColor = FlashConfig::UI_ACTIVE_COLOR;
        
        buttonMode(true);
            
        Graphics* g;
        g = graphics();
        g->smoothing(true);
        g->clear();
        g->lineStyle(2, _lineColor);
        g->drawCircle(_radius + 2, 16 + _radius + 1.5, _radius);
        g->endFill();
        
        addEventListener(MouseEvent::MOUSE_OVER, this, &CircleColorPicker::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_OUT, this, &CircleColorPicker::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_DOWN, this, &CircleColorPicker::_mouseEventHandler);
        ///addEventListener(MouseEvent::MOUSE_UP, this, &CircleColorPicker::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_MOVE, this, &CircleColorPicker::_mouseEventHandler);
        
        //------------------------------------------
        _colorWheelImage = new ofImage();
        _colorWheelImage->loadImage(FlashConfig::_COLORWHEEL_IMAGE_PATH);
        //_colorWheelImage->setAnchorPercent(0.5,0.5);
//        this->width(_imageWidth);
//        this->height(20 + _imageWidth);
        
        _pixelCaptureImage = new ofImage();
        
        _selectedPixel = new ofColor(255, 255, 255);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _labelText = new TextField();
        _labelText->x(0);
        _labelText->y(0);
        _labelText->width(_imageWidth);
        _labelText->autoSize(TextFieldAutoSize::CENTER);
        _labelText->textColor(0x0);
        _labelText->text("COLOR PICKER");
        addChild(_labelText);
        //------------------------------------------    
    }

    //--------------------------------------------------------------
    //
    CircleColorPicker::~CircleColorPicker() {
        //cout << "[CircleColorPicker]~CircleColorPicker()" << endl;
        
        removeEventListener(MouseEvent::MOUSE_OVER, &CircleColorPicker::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_OUT, &CircleColorPicker::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_DOWN, &CircleColorPicker::_mouseEventHandler);
        //removeEventListener(MouseEvent::MOUSE_UP, &CircleColorPicker::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_MOVE, &CircleColorPicker::_mouseEventHandler);
        
        delete _colorWheelImage;
        _colorWheelImage = NULL;
        
        delete _pixelCaptureImage;
        _pixelCaptureImage = NULL;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void CircleColorPicker::_setup() {
        //cout << "[SimpleSlider]setup()" << endl;
    }

    //--------------------------------------------------------------
    //
    void CircleColorPicker::_update() {
        
    }

    //--------------------------------------------------------------
    //
    void CircleColorPicker::_draw() {
        ofSetColor(255, 255, 255, 255);
        _colorWheelImage->draw(0, 16, _imageWidth, _imageHeight);
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    string CircleColorPicker::label() { return _labelText->text(); }
    void CircleColorPicker::label(string value, int color) { _labelText->text(value, color); }
    //--------------------------------------------------------------
    //
    void CircleColorPicker::textColor(int color) {
        _labelText->textColor(color);
    }

    //--------------------------------------------------------------
    //
    const ofColor& CircleColorPicker::getPixel(int x, int y) {
        ofPoint point = localToGlobal(ofPoint(x, y));
        
        _pixelCaptureImage->grabScreen(point.x, point.y, 1, 1);
        
        int r = _pixelCaptureImage->getPixels()[0];
        int g = _pixelCaptureImage->getPixels()[1];
        int b = _pixelCaptureImage->getPixels()[2];
        
        _selectedPixel->r = r;
        _selectedPixel->g = g;
        _selectedPixel->b = b;
        
        dispatchEvent(new ColorPickerEvent(ColorPickerEvent::CHANGE));
        
        return *_selectedPixel;
    }

    //--------------------------------------------------------------
    //
    int CircleColorPicker::red() { return _selectedPixel->r; }
    //--------------------------------------------------------------
    //
    int CircleColorPicker::green() { return _selectedPixel->g; }
    //--------------------------------------------------------------
    //
    int CircleColorPicker::blue() { return _selectedPixel->b; }

    //--------------------------------------------------------------
    //
    string CircleColorPicker::hexCode() {
        _selectedPixel->a = 0;
        
        string returnValue;
        char outStr[256];
        //    sprintf(outStr,"%06x",pixColor.asHex(OF_COLOR_RGB));
        returnValue = outStr;
        
        return returnValue;
    }

    //--------------------------------------------------------------
    //
    int CircleColorPicker::hue() { return _selectedPixel->getHue(); }
    //--------------------------------------------------------------
    //
    int CircleColorPicker::saturation() { return _selectedPixel->getSaturation(); }
    //--------------------------------------------------------------
    //
    int CircleColorPicker::brightness() { return _selectedPixel->getBrightness(); }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void CircleColorPicker::_over() {
        if(isMouseDown()) return;
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(3, _overColor);
        g->drawCircle(_radius + 2, 16 + _radius + 1.5, _radius);
        g->endFill();
    }

    //--------------------------------------------------------------
    //
    void CircleColorPicker::_out() {
        if(isMouseDown()) return;
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(2, _lineColor);
        g->drawCircle(_radius + 2, 16 + _radius + 1.5, _radius);
        g->endFill();
    }

    //--------------------------------------------------------------
    //
    void CircleColorPicker::_press() {
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(3, _activeColor);
        g->drawCircle(_radius + 2, 16 + _radius + 1.5, _radius);
        g->endFill();
        
        getPixel(mouseX(), mouseY());
        
    //    cout << "Red: " << red() << endl;
    //    cout << "Green: " << green() << endl;
    //    cout << "Blue: " << blue() << endl;
    //    cout << "Hue: " << hue() << endl;
    //    cout << "Saturation: " << saturation() << endl;
    //    cout << "Brightness: " << brightness() << endl;
    //    cout << "Hexcode: " << hexCode() << endl;
    }

    //--------------------------------------------------------------
    //
    void CircleColorPicker::_release() {
        if(isMouseOver()) {
            _over();
            return;
        }
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(2, _lineColor);
        g->drawCircle(_radius + 2, 16 + _radius + 1.5, _radius);
        g->endFill();
    }

    //--------------------------------------------------------------
    //
    void CircleColorPicker::_move() {
        getPixel(mouseX(), mouseY());
    }

    //==============================================================
    // EVENT HANDLER
    //==============================================================

    //--------------------------------------------------------------
    //
    void CircleColorPicker::_mouseEventHandler(Event& event) {
        //cout << "[CircleColorPicker]_mouseEventHandler(" << event.type() << endl;
        //cout << "isMouseDown" << isMouseDown() << endl;
        
        if(event.type() == MouseEvent::MOUSE_OVER) {
            if(event.target() == this) _over();
        }
        if(event.type() == MouseEvent::MOUSE_OUT) {
            if(event.target() == this) _out();
        }
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            if(event.target() == this){
                _press();
                stage()->addEventListener(MouseEvent::MOUSE_UP, this, &CircleColorPicker::_mouseEventHandler);
            }
        }
        if(event.type() == MouseEvent::MOUSE_UP) {
            if(event.currentTarget() == stage()) {
                _release();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, &CircleColorPicker::_mouseEventHandler);
            }
        }
        if(event.type() == MouseEvent::MOUSE_MOVE) {
            if(event.target() == this){
                if(isMouseDown()) _move();
            }
        }
    }

}