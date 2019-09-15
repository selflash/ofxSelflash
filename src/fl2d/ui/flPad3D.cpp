#include "flPad3D.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flPad3D::flPad3D(float width, float height) {
        //printf("[flPad3D]flPad3D()\n");
        
        _target = this;
        name("flPad3D");
        
        //mouseChildren(false);
        //buttonMode(false);
        
        _width = width;
        _height = height;
        
        _lineColor = flDefinition::UI_LINE_COLOR;
        
        _normalColor = flDefinition::UI_NORMAL_COLOR;
        _overColor = flDefinition::UI_OVER_COLOR;
        _activeColor = flDefinition::UI_ACTIVE_COLOR;
        
        _ballRadius = 6;
        
        flGraphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawRect(0, 0, _width, _height);
        
        g->lineStyle(1, _lineColor);
        g->moveTo(0, _height * 0.5);
        g->lineTo(_width, _height * 0.5);
        g->moveTo(_width * 0.5, 0);
        g->lineTo(_width * 0.5, _height);
        g->endFill();
        
        addEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_MOVE, this, &flPad3D::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        ball = new flSprite();
        ball->useHandCursor(true);
        g = ball->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        ball->x(_width * 0.5);
        ball->y(_height * 0.5);
        ball->addEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        ball->addEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        ball->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        addChild(ball);
        
        _draggablePoint = new ofPoint(0, 0);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _labelText = new flTextField();
        _labelText->x(0);
        _labelText->y(-15);
        _labelText->width(_width);
        _labelText->autoSize(flTextFieldAutoSize::CENTER);
        _labelText->textColor(0x000000);
        _labelText->text("Pad 2D");
        addChild(_labelText);
        
        _value1Text = new flTextField();
        //_value1Text->x(_trackWidth * 0.5);
        _value1Text->x(2);
        _value1Text->y(2);
        _value1Text->width(_width);
        _value1Text->autoSize(flTextFieldAutoSize::LEFT);
        _value1Text->textColor(0xffffff);
        addChild(_value1Text);
        
        _value2Text = new flTextField();
        _value2Text->x(2);
        _value2Text->y(17);
        _value2Text->width(_width);
        _value2Text->autoSize(flTextFieldAutoSize::LEFT);
        _value2Text->textColor(0xffffff);
        addChild(_value2Text);
        
        _xValue = ball->x() / _width;
        _yValue = ball->y() / _height;
        _value1Text->text("x:" + ofToString(_xValue));
        _value2Text->text("y:" + ofToString(_yValue));
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    flPad3D::~flPad3D() {
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
        
        ball->removeEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        ball->removeEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        ball->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        delete ball;
        ball = NULL;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flPad3D::_setup() {
        //printf("[flPad3D]_setup()\n");
        
    }
    
    //--------------------------------------------------------------
    //
    void flPad3D::_update() {
        
        if(!ball->isMouseDown()) return;
        
        //------------------------------------------
        float tx = mouseX() + _draggablePoint->x;
        float ty = mouseY() + _draggablePoint->y;
        
        if(tx < 0) tx = 0;
        if(_width < tx) tx = _width;
        if(ty < 0) ty = 0;
        if(_height < ty) ty = _height;
        
        ball->x(tx);
        ball->y(ty);
        
        _areaPress();
        //------------------------------------------
        
        //------------------------------------------
        float temp1 = _xValue;
        float temp2 = _yValue;
        
        _xValue = ball->x() / _width;
        _yValue = ball->y() / _height;
        _value1Text->text("x:" + ofToString(_xValue));
        _value2Text->text("y:" + ofToString(_yValue));
        
        if(temp1 != _xValue || temp2 != _yValue) {
            flPadEvent* event = new flPadEvent(flPadEvent::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flPad3D::_draw() {
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    string flPad3D::label() { return _labelText->text(); }
    void flPad3D::label(string value, int color) {
        _labelText->text(value);
        _labelText->textColor(color);
        //_valueText->textColor(color);
    }
    //--------------------------------------------------------------
    //
    void flPad3D::textColor(int color) {
        _labelText->textColor(color);
    }
    
    //--------------------------------------------------------------
    //
    float flPad3D::xValue() { return _xValue; }
    void flPad3D::xValue(float value) {
        ball->x(value * _width);
        _areaPress();
    }
    
    //--------------------------------------------------------------
    //
    float flPad3D::yValue() { return _yValue; }
    void flPad3D::yValue(float value) {
        ball->y(value * _height);
        _areaPress();
    }
    
    //==============================================================
    // PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flPad3D::_areaOver() {
        flGraphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _overColor);
        g->beginFill(_normalColor, 1);
        g->drawRect(0, 0, _width, _height);
        //横線・縦線
        g->lineStyle(1, _overColor);
        g->moveTo(0, ball->y());
        g->lineTo(_width, ball->y());
        g->moveTo(ball->x(), 0);
        g->lineTo(ball->x(), _width);
        //------------------------------------------
        //------------------------------------------
        g = ball->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _overColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        //------------------------------------------    
    }
    //--------------------------------------------------------------
    //
    void flPad3D::_areaOut() {
        flGraphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawRect(0, 0, _width, _height);
        //横線・縦線
        g->lineStyle(1, _lineColor);
        g->moveTo(0, ball->y());
        g->lineTo(_width, ball->y());
        g->moveTo(ball->x(), 0);
        g->lineTo(ball->x(), _height);
        //------------------------------------------
        
        _ballOut();
    }
    //--------------------------------------------------------------
    //
    void flPad3D::_areaPress() {
        flGraphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _activeColor);
        g->beginFill(_normalColor, 1);
        g->drawRect(0, 0, _width, _height);
        //横線・縦線
        g->lineStyle(1, _activeColor);
        g->moveTo(0, ball->y());
        g->lineTo(_width, ball->y());
        g->moveTo(ball->x(), 0);
        g->lineTo(ball->x(), _height);
        //------------------------------------------    
    }
    //--------------------------------------------------------------
    //
    void flPad3D::_areaRelease() {
        if(isMouseOver()) {
            _areaOver();
            return;
        }
        
        flGraphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawRect(0, 0, _width, _height);
        g->lineStyle(1, _lineColor);
        //横線・縦線
        g->lineStyle(1, _lineColor);
        g->moveTo(0, ball->y());
        g->lineTo(_width, ball->y());
        g->moveTo(ball->x(), 0);
        g->lineTo(ball->x(), _height);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    void flPad3D::_ballOver() {
        flGraphics* g;
        
        //------------------------------------------
        g = ball->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_overColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void flPad3D::_ballOut() {
        if(ball->isMouseDown()) return;
        
        if(isMouseOver()) {
            _areaOver();
            return;
        }
        
        flGraphics* g;
        
        //------------------------------------------
        g = ball->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flPad3D::_ballPress() {
        _areaPress();
        
        _draggablePoint->x = ball->x() - mouseX();
        _draggablePoint->y = ball->y() - mouseY();
        
        flGraphics* g;
        
        //------------------------------------------
        g = ball->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_activeColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flPad3D::_ballRelease() {
        _areaRelease();
        
        if(ball->isMouseOver()) {
            _ballOver();
            return;
        }
        
        flGraphics* g;
        //------------------------------------------
        g = ball->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void flPad3D::_ballMove() {
        
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flPad3D::_mouseEventHandler(flEvent& event) {
        //cout << "[SimpleSlider]_mouseEventHandler(" << event.type() << endl;
        
        //MOUSE OVER
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) _areaOver();
            if(event.target() == ball) _ballOver();
        }
        
        //MOUSE OUT
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) _areaOut();
            if(event.target() == ball) _ballOut();
        }
        
        //MOUSE DOWN
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == ball) {
                _ballPress();
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
            }
        }
        
        //MOUSE UP
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(event.target() == stage()) {
                _ballRelease();
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
            }
        }
        
        //MOUSE_MOVE
        if(event.type() == flMouseEvent::MOUSE_MOVE) {
            if(event.currentTarget() == this) {
                
            }
        }
    }
    
}
