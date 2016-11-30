#include "Pad3D.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Pad3D::Pad3D(float width, float height) {
        //printf("[Pad3D]Pad3D()\n");
        
        _target = this;
        name("Pad3D");
        
        //mouseChildren(false);
        //buttonMode(false);
        
        _width = width;
        _height = height;
        
        _lineColor = FlashConfig::UI_LINE_COLOR;
        
        _normalColor = FlashConfig::UI_NORMAL_COLOR;
        _overColor = FlashConfig::UI_OVER_COLOR;
        _activeColor = FlashConfig::UI_ACTIVE_COLOR;
        
        _ballRadius = 6;
        
        Graphics* g;
        
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
        
        addEventListener(MouseEvent::ROLL_OVER, this, &Pad3D::_mouseEventHandler);
        addEventListener(MouseEvent::ROLL_OUT, this, &Pad3D::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_DOWN, this, &Pad3D::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_UP, this, &Pad3D::_mouseEventHandler);
        //addEventListener(MouseEvent::MOUSE_MOVE, this, &Pad3D::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        ball = new Sprite();
        ball->useHandCursor(true);
        g = ball->graphics();
        g->smoothing(true);
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        ball->x(_width * 0.5);
        ball->y(_height * 0.5);
        ball->addEventListener(MouseEvent::ROLL_OVER, this, &Pad3D::_mouseEventHandler);
        ball->addEventListener(MouseEvent::ROLL_OUT, this, &Pad3D::_mouseEventHandler);
        ball->addEventListener(MouseEvent::MOUSE_DOWN, this, &Pad3D::_mouseEventHandler);
        addChild(ball);
        
        _draggablePoint = new ofPoint(0, 0);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _labelText = new TextField();
        _labelText->x(0);
        _labelText->y(-15);
        _labelText->width(_width);
        _labelText->autoSize(TextFieldAutoSize::CENTER);
        _labelText->textColor(0x000000);
        _labelText->text("Pad 2D");
        addChild(_labelText);
        
        _value1Text = new TextField();
        //_value1Text->x(_trackWidth * 0.5);
        _value1Text->x(2);
        _value1Text->y(2);
        _value1Text->width(_width);
        _value1Text->autoSize(TextFieldAutoSize::LEFT);
        _value1Text->textColor(0xffffff);
        addChild(_value1Text);
        
        _value2Text = new TextField();
        _value2Text->x(2);
        _value2Text->y(17);
        _value2Text->width(_width);
        _value2Text->autoSize(TextFieldAutoSize::LEFT);
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
    Pad3D::~Pad3D() {
        removeEventListener(MouseEvent::ROLL_OVER, this, &Pad3D::_mouseEventHandler);
        removeEventListener(MouseEvent::ROLL_OUT, this, &Pad3D::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_DOWN, this, &Pad3D::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_UP, this, &Pad3D::_mouseEventHandler);
        
        ball->removeEventListener(MouseEvent::ROLL_OVER, this, &Pad3D::_mouseEventHandler);
        ball->removeEventListener(MouseEvent::ROLL_OUT, this, &Pad3D::_mouseEventHandler);
        ball->removeEventListener(MouseEvent::MOUSE_DOWN, this, &Pad3D::_mouseEventHandler);
        delete ball;
        ball = NULL;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void Pad3D::_setup() {
        //printf("[Pad3D]_setup()\n");

    }

    //--------------------------------------------------------------
    //
    void Pad3D::_update() {
        
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
            PadEvent* event = new PadEvent(PadEvent::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
        //------------------------------------------
    }

    //--------------------------------------------------------------
    //
    void Pad3D::_draw() {
        
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    string Pad3D::label() { return _labelText->text(); }
    void Pad3D::label(string value, int color) {
        _labelText->text(value);
        _labelText->textColor(color);
        //_valueText->textColor(color);
    }
    //--------------------------------------------------------------
    //
    void Pad3D::textColor(int color) {
        _labelText->textColor(color);
    }

    //--------------------------------------------------------------
    //
    float Pad3D::xValue() { return _xValue; }
    void Pad3D::xValue(float value) {
        ball->x(value * _width);
        _areaPress();
    }

    //--------------------------------------------------------------
    //
    float Pad3D::yValue() { return _yValue; }
    void Pad3D::yValue(float value) {
        ball->y(value * _height);
        _areaPress();
    }

    //==============================================================
    // PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void Pad3D::_areaOver() {
        Graphics* g;
        
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
    void Pad3D::_areaOut() {
        Graphics* g;
        
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
    void Pad3D::_areaPress() {
        Graphics* g;
        
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
    void Pad3D::_areaRelease() {
        if(isMouseOver()) {
            _areaOver();
            return;
        }
        
        Graphics* g;
        
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
    void Pad3D::_ballOver() {
        Graphics* g;
        
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
    void Pad3D::_ballOut() {
        if(ball->isMouseDown()) return;
        
        if(isMouseOver()) {
            _areaOver();
            return;
        }
        
        Graphics* g;
        
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
    void Pad3D::_ballPress() {
        _areaPress();

        _draggablePoint->x = ball->x() - mouseX();
        _draggablePoint->y = ball->y() - mouseY();
        
        Graphics* g;
        
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
    void Pad3D::_ballRelease() {
        _areaRelease();
        
        if(ball->isMouseOver()) {
            _ballOver();
            return;
        }
        
        Graphics* g;
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
    void Pad3D::_ballMove() {
        
    }

    //==============================================================
    // EVENT HANDLER
    //==============================================================

    //--------------------------------------------------------------
    //
    void Pad3D::_mouseEventHandler(Event& event) {
        //cout << "[SimpleSlider]_mouseEventHandler(" << event.type() << endl;
        
        //MOUSE OVER
        if(event.type() == MouseEvent::ROLL_OVER) {
            if(event.target() == this) _areaOver();
            if(event.target() == ball) _ballOver();
        }
        
        //MOUSE OUT
        if(event.type() == MouseEvent::ROLL_OUT) {
            if(event.target() == this) _areaOut();
            if(event.target() == ball) _ballOut();
        }
        
        //MOUSE DOWN
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            if(event.target() == ball) {
                _ballPress();
                stage()->addEventListener(MouseEvent::MOUSE_UP, this, &Pad3D::_mouseEventHandler);
            }
        }
        
        //MOUSE UP
        if(event.type() == MouseEvent::MOUSE_UP) {
            if(event.target() == stage()) {
                _ballRelease();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, this, &Pad3D::_mouseEventHandler);
            }
        }
        
        //MOUSE_MOVE
        if(event.type() == MouseEvent::MOUSE_MOVE) {
            if(event.currentTarget() == this) {
                
            }
        }
    }

}
