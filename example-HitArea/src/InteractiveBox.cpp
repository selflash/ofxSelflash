#include "InteractiveBox.h"

//==============================================================
// Constructor / Destructor
//==============================================================

//-------------------------------------------------------------
InteractiveBox::InteractiveBox(float graphicsWidth, float graphicsHeight, ofColor areaColor) {
    ofLog() << "[InteractiveBox]InteractiveBox()";
    
    _target = this;
    name("InteractiveBox");
    
    useHandCursor(true);
    
    _showHitArea = false;
    
    //--------------------------------------
    addEventListener(flMouseEvent::ROLL_OVER, this, &InteractiveBox::_mouseEventHandler);
    addEventListener(flMouseEvent::ROLL_OUT, this, &InteractiveBox::_mouseEventHandler);
    addEventListener(flMouseEvent::MOUSE_DOWN, this, &InteractiveBox::_mouseEventHandler);
    addEventListener(flMouseEvent::MOUSE_UP, this, &InteractiveBox::_mouseEventHandler);
    //--------------------------------------
    
    _graphicsWidth = graphicsWidth;
    _graphicsHeight = graphicsHeight;
    
    _areaColor = areaColor;
    _areaColor.a = 255 * 0.5;
    
    //--------------------------------------
    _label = new flTextField();
    _label->textColor(0x000000);
    _label->x(10);
    _label->y(10);
    _label->visible(false);
    _label->mouseEnabled(false);
    //    addChild(_label);
    //--------------------------------------
    
    _setNormalColor();
}

//-------------------------------------------------------------
InteractiveBox::~InteractiveBox() {
    ofLog() << "[InteractiveBox]~InteractiveBox()";
    
    //--------------------------------------
    removeEventListener(flMouseEvent::ROLL_OVER, this, &InteractiveBox::_mouseEventHandler);
    removeEventListener(flMouseEvent::ROLL_OUT, this, &InteractiveBox::_mouseEventHandler);
    removeEventListener(flMouseEvent::MOUSE_DOWN, this, &InteractiveBox::_mouseEventHandler);
    removeEventListener(flMouseEvent::MOUSE_UP, this, &InteractiveBox::_mouseEventHandler);
    //--------------------------------------
    
    _graphicsWidth = 0.0;
    _graphicsHeight = 0.0;
    
    _showHitArea = false;
    
    delete _label;
    _label = NULL;
}

//==============================================================
// Setup / Update / Draw
//==============================================================

//-------------------------------------------------------------
void InteractiveBox::_setup() {
    //ofLog() << "[InteractiveBox]_setup()";
    
}

//-------------------------------------------------------------
void InteractiveBox::_update() {
    
}

//-------------------------------------------------------------
void InteractiveBox::_draw() {
    //--------------------------------------
    //ヒットエリアの表示
    if(_showHitArea) {
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(1);
        //    ofSetColor(_areaColor);
        ofSetColor(_areaColor);
        ofDrawRectangle(_rect->x(), _rect->y(), _rect->width(), _rect->height());
        //    ofRect(getRect(this).x(), getRect(this).y(), getRect(this).width(), getRect(this).height());
        //    ofRect(_rect->left(), _rect->top(), _rect->right(), _rect->bottom());
        ofPopStyle();
    }
    //--------------------------------------
    
    //--------------------------------------
    string text = "";
    text += name() + "\n";
    text += "Parent is " + parent()->name() + "\n";
    text += "Mouse Enabled = " + ofToString(mouseEnabled() ? "True" : "False") + "\n";
    text += "Mouse Children = " + ofToString(mouseChildren() ? "True" : "False") + "\n";
    text += "X = " + ofToString(x()) + "\n";
    text += "Y = " + ofToString(y()) + "\n";
    //    text += "width = " + ofToString(width()) + "\n";
    //    text += "height = " + ofToString(height()) + "\n";
    //    text += "scaleX = " + ofToString(scaleX()) + "\n";
    //    text += "scaleY = " + ofToString(scaleY()) + "\n";
    
    ofPushStyle();
    //    ofSetColor(0x000000);
    ofSetColor(0xffffff);
    //    ofDrawBitmapString(text, 10, 50);
    flFont::drawString(text, 9, 10, 20);
    ofPopStyle();
    //--------------------------------------
}

//==============================================================
// Public Method
//==============================================================

//-------------------------------------------------------------
void InteractiveBox::title(string value) {
    _label->text(value);
    _label->visible(true);
}

//==============================================================
// Protected / Private Method
//==============================================================

//--------------------------------------------------------------
void InteractiveBox::_over() {
    if(isMouseDown()) return;
    
    _setOverColor();
}

//--------------------------------------------------------------
void InteractiveBox::_out() {
    if(isMouseDown()) return;
    
    _setNormalColor();
}

//--------------------------------------------------------------
void InteractiveBox::_press() {
    _setActiveColor();
}

//--------------------------------------------------------------
void InteractiveBox::_release() {
    if(isMouseOver()) {
        _setOverColor();
    } else {
        _setNormalColor();
    }
}

//--------------------------------------------------------------
void InteractiveBox::_setNormalColor() {
    if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
    
    _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR);
}

//--------------------------------------------------------------
void InteractiveBox::_setOverColor() {
    if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
    
    _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR);
}

//--------------------------------------------------------------
void InteractiveBox::_setSelectedOverColor() {
    if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
    
    _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR);
}

//--------------------------------------------------------------
void InteractiveBox::_setActiveColor() {
    if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
    
    _drawGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR);
}

//--------------------------------------------------------------
void InteractiveBox::_setDisableNormalColor() {
    if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
    
    _drawGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR);
}

//--------------------------------------------------------------
void InteractiveBox::_setDisableActiveColor() {
    if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
    
    _drawGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR);
}

//-------------------------------------------------------------
void InteractiveBox::_drawGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
    flGraphics* g = graphics();
    g->clear();
    g->lineStyle(thickness, lineColor.getHex());
    g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
    g->drawRect(0, 0, _graphicsWidth, _graphicsHeight);
    g->endFill();
}

//==============================================================
// Private Event Handler
//==============================================================

//-------------------------------------------------------------
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
        if(event.target() == stage()){
            _release();
            
            stopDrag();
            stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &InteractiveBox::_mouseEventHandler);
        }
    }
}
