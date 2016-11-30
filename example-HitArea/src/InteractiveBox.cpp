#include "InteractiveBox.h"

//==============================================================
// CONSTRUCTOR / DESTRUCTOR
//==============================================================

//--------------------------------------------------------------
//
InteractiveBox::InteractiveBox(float graphicsWidth, float graphicsHeight, int areaColor) {
    cout << "[InteractiveBox]InteractiveBox()" << endl;
    _target = this;
    name("InteractiveBox");
    
    useHandCursor(true);
    
    _graphicsWidth = graphicsWidth;
    _graphicsHeight = graphicsHeight;
    
    _lineColor = new ofFloatColor();
    _lineColor->setHex(FlashConfig::UI_LINE_COLOR);
    
    _normalColor = new ofFloatColor();
    _normalColor->setHex(FlashConfig::UI_NORMAL_COLOR);
    
    _overColor = new ofFloatColor();
    _overColor->setHex(FlashConfig::UI_OVER_COLOR);
    
    _activeColor = new ofFloatColor();
    _activeColor->setHex(FlashConfig::UI_ACTIVE_COLOR);
    
    _areaColor = new ofFloatColor();
    _areaColor->setHex(areaColor);
    _areaColor->a = 0.5;
    
    //--------------------------------------
    //インフォ
    _titleTf = new flTextField();
    _titleTf->textColor(0x000000);
    _titleTf->x(10);
    _titleTf->y(10);
    _titleTf->visible(false);
    _titleTf->mouseEnabled(false);
    addChild(_titleTf);
    //--------------------------------------
}

//--------------------------------------------------------------
//
InteractiveBox::~InteractiveBox() {
    cout << "[InteractiveBox]~InteractiveBox()" << endl;
    
    delete _lineColor;
    _lineColor = NULL;
    
    delete _normalColor;
    _normalColor = NULL;
    
    delete _overColor;
    _overColor = NULL;
    
    delete _activeColor;
    _activeColor = NULL;
    
    delete _areaColor;
    _areaColor = NULL;
    
    _graphicsWidth = 0.0;
    _graphicsHeight = 0.0;

    _lineColor = 0;
    _normalColor = 0;
    _overColor = 0;
    _activeColor = 0;
    
    delete _titleTf;
    _titleTf = NULL;
}

//==============================================================
// SETUP / UPDATE / DRAW
//==============================================================

//--------------------------------------------------------------
//
void InteractiveBox::_setup() {
    //cout << "[InteractiveBox]_setup()" << endl;

    //--------------------------------------
    _drawTrackGraphics(*_lineColor, *_normalColor);
    //--------------------------------------
    
    //--------------------------------------
    addEventListener(flMouseEvent::ROLL_OVER, this, &InteractiveBox::_mouseEventHandler);
    addEventListener(flMouseEvent::ROLL_OUT, this, &InteractiveBox::_mouseEventHandler);
    addEventListener(flMouseEvent::MOUSE_DOWN, this, &InteractiveBox::_mouseEventHandler);
    addEventListener(flMouseEvent::MOUSE_UP, this, &InteractiveBox::_mouseEventHandler);
    //--------------------------------------
}

//--------------------------------------------------------------
//
void InteractiveBox::_update() {
    
}

//--------------------------------------------------------------
//
void InteractiveBox::_draw() {
    //--------------------------------------
    //ヒットエリアの表示
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(_areaColor->getNormalized());
    ofRect(_rect->x(), _rect->y(), _rect->width(), _rect->height());
//    ofRect(getRect(this).x(), getRect(this).y(), getRect(this).width(), getRect(this).height());
//    ofRect(_rect->left(), _rect->top(), _rect->right(), _rect->bottom());
    //--------------------------------------
    
    //--------------------------------------
    std::string text = "";
    text += name() + "\n";
    text += "X = " + ofToString(x()) + "\n";
    text += "Y = " + ofToString(y()) + "\n";
//    text += "width = " + ofToString(width()) + "\n";
//    text += "height = " + ofToString(height()) + "\n";
//    text += "scaleX = " + ofToString(scaleX()) + "\n";
//    text += "scaleY = " + ofToString(scaleY()) + "\n";
    
    ofPushStyle();
    ofSetColor(0x000000);
//    ofDrawBitmapString(text, 10, 50);
    flFont::drawString(text, 10, 50);
    ofPopStyle();
    //--------------------------------------
}

//==============================================================
// PUBLIC METHOD
//==============================================================

//--------------------------------------------------------------
//
void InteractiveBox::title(std::string value) {
    _titleTf->text(value);
    _titleTf->visible(true);
}

//==============================================================
// PRIVATE METHOD
//==============================================================

//--------------------------------------------------------------
//
void InteractiveBox::_drawTrackGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor) {
    flGraphics* g;
    g = graphics();
    g->clear();
    g->lineStyle(1, lineColor.getHex());
    g->beginFill(fillColor.getHex());
    g->drawRect(0, 0, _graphicsWidth, _graphicsHeight);
    g->endFill();
}

//--------------------------------------------------------------
//
void InteractiveBox::_over() {
    _drawTrackGraphics(*_lineColor, *_overColor);
}

//--------------------------------------------------------------
//
void InteractiveBox::_out() {
    _drawTrackGraphics(*_lineColor, *_normalColor);
}

//--------------------------------------------------------------
//
void InteractiveBox::_press() {
    _drawTrackGraphics(*_lineColor, *_activeColor);
}

//--------------------------------------------------------------
//
void InteractiveBox::_release() {
    if(isMouseOver()) {
        _over();
        return;
    }
    
    _drawTrackGraphics(*_lineColor, *_normalColor);
}

//==============================================================
// EVENT HANDLER
//==============================================================

//--------------------------------------------------------------
//
void InteractiveBox::_mouseEventHandler(flEvent& event) {
//    cout << "[InteractiveBox]_mouseEventHandler(" << event.type() << ")" << endl;
    
    if(event.type() == flMouseEvent::ROLL_OVER) {
        if(event.target() == this) _over();
    }
    
    if(event.type() == flMouseEvent::ROLL_OUT) {
        if(event.target() == this) _out();
    }
    
    if(event.type() == flMouseEvent::MOUSE_OVER) {
        if(event.target() == this) _over();
    }
    
    if(event.type() == flMouseEvent::MOUSE_OUT) {
        if(event.target() == this) _out();
    }
    
    if(event.type() == flMouseEvent::MOUSE_DOWN) {
        if(event.target() == this) {
            _press();
            
            startDrag();
            stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &InteractiveBox::_mouseEventHandler);
        }
    }
    
    if(event.type() == flMouseEvent::MOUSE_UP) {
        if(event.target() == stage()) {
            _release();
            
            stopDrag();
            stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &InteractiveBox::_mouseEventHandler);
        }
    }
}
