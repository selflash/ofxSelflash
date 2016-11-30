#include "Pad2D.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Pad2D::Pad2D(float width, float height, float left, float right, float top, float bottom) {
        //printf("[Pad2D]Pad2D()\n");
        
        _target = this;
        name("Pad2D");
        
        //mouseChildren(false);
        //buttonMode(false);
        
        _width = width - 40;
        _height = height - 40;
        _leftValue = left;
        _rightValue = right;
        _topValue = top;
        _bottomValue = bottom;
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;

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
        g->drawRect(18, 18, _width, _height);
        
        g->lineStyle(1, _lineColor);
        g->moveTo(18, 18 + _height * 0.5);
        g->lineTo(18 + _width, 18 + _height * 0.5);
        g->moveTo(18 + _width * 0.5, 18);
        g->lineTo(18 + _width * 0.5, 18 + _height);
        g->endFill();
        
        addEventListener(MouseEvent::ROLL_OVER, this, &Pad2D::_mouseEventHandler);
        addEventListener(MouseEvent::ROLL_OUT, this, &Pad2D::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_OVER, this, &Pad2D::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_OUT, this, &Pad2D::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_DOWN, this, &Pad2D::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_UP, this, &Pad2D::_mouseEventHandler);
        //addEventListener(MouseEvent::MOUSE_MOVE, this, &Pad2D::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        //左
        _dialer01 = new NumberDialer(_width);
        _dialer01->x(0);
        _dialer01->y(18);
        _dialer01->type(NumberDialer::VERTICALLY);
        _dialer01->max(_rightValue, false);
        _dialer01->value(_leftValue);
        _dialer01->addEventListener(NumberDialerEvent::CHANGE, this, &Pad2D::_uiEventHandler);
        addChild(_dialer01);
        //上
        _dialer02 = new NumberDialer(_width);
        _dialer02->x(18);
        _dialer02->y(0);
        _dialer02->stepValue(-1);
        _dialer02->max(_bottomValue, false);
        _dialer02->value(_topValue);
        _dialer02->addEventListener(NumberDialerEvent::CHANGE, this, &Pad2D::_uiEventHandler);
        addChild(_dialer02);
        //右
        _dialer03 = new NumberDialer(_width);
        _dialer03->x(18 + _width);
        _dialer03->y(18);
        _dialer03->type(NumberDialer::VERTICALLY);
        _dialer03->min(_leftValue, false);
        _dialer03->value(_rightValue);
        _dialer03->addEventListener(NumberDialerEvent::CHANGE, this, &Pad2D::_uiEventHandler);
        addChild(_dialer03);
        //下
        _dialer04 = new NumberDialer(_width);
        _dialer04->x(18);
        _dialer04->y(18 + _height);
        _dialer04->stepValue(-1);
        _dialer04->min(_topValue, false);
        _dialer04->value(_bottomValue);
        _dialer04->addEventListener(NumberDialerEvent::CHANGE, this, &Pad2D::_uiEventHandler);
        addChild(_dialer04);
        
        _rangeWidth = _dialer03->value() - _dialer01->value();
        _rangeHeight = _dialer04->value() - _dialer02->value();
        //------------------------------------------
        
        //------------------------------------------
        ball = new Sprite();
        ball->useHandCursor(true);
        g = ball->graphics();
        g->smoothing(true);
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        ball->x(18 + _width * 0.5);
        ball->y(18 + _height * 0.5);
        ball->addEventListener(MouseEvent::ROLL_OVER, this, &Pad2D::_mouseEventHandler);
        ball->addEventListener(MouseEvent::ROLL_OUT, this, &Pad2D::_mouseEventHandler);
        ball->addEventListener(MouseEvent::MOUSE_DOWN, this, &Pad2D::_mouseEventHandler);
        addChild(ball);
        
        _draggablePoint = new ofPoint(0, 0);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _label = NULL;
        
        _xRatioText = new TextField();
        //_xRatioText->x(_trackWidth * 0.5);
        _xRatioText->x(18);
        _xRatioText->y(18 * 1);
        _xRatioText->width(_width);
        _xRatioText->autoSize(TextFieldAutoSize::LEFT);
        _xRatioText->textColor(_labelNormalColor);
        addChild(_xRatioText);
        
        _yRatioText = new TextField();
        _yRatioText->x(18);
        _yRatioText->y(18 * 2);
        _yRatioText->width(_width);
        _yRatioText->autoSize(TextFieldAutoSize::LEFT);
        _yRatioText->textColor(_labelNormalColor);
        addChild(_yRatioText);
        
        _xValueText = new TextField();
        //_xValueText->x(_trackWidth * 0.5);
        _xValueText->x(18);
        _xValueText->y(18 * 3);
        _xValueText->width(_width);
        _xValueText->autoSize(TextFieldAutoSize::LEFT);
        _xValueText->textColor(_labelNormalColor);
        addChild(_xValueText);
        
        _yValueText = new TextField();
        _yValueText->x(18);
        _yValueText->y(18 * 4);
        _yValueText->width(_width);
        _yValueText->autoSize(TextFieldAutoSize::LEFT);
        _yValueText->textColor(_labelNormalColor);
        addChild(_yValueText);
        
        _xRatio = ball->x() / _width;
        _yRatio = ball->y() / _height;
        _xRatioText->text("x:" + ofToString(_xRatio));
        _yRatioText->text("y:" + ofToString(_yRatio));
        
        _xValue = ball->x() / _width;
        _yValue = ball->y() / _height;
        _xValueText->text("x:" + ofToString(_xValue));
        _yValueText->text("y:" + ofToString(_yValue));
        //------------------------------------------
        
        _updateValue();
    }

    //--------------------------------------------------------------
    //
    Pad2D::~Pad2D() {
        removeEventListener(MouseEvent::ROLL_OVER, this, &Pad2D::_mouseEventHandler);
        removeEventListener(MouseEvent::ROLL_OUT, this, &Pad2D::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_OVER, this, &Pad2D::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_OUT, this, &Pad2D::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_DOWN, this, &Pad2D::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_UP, this, &Pad2D::_mouseEventHandler);
        
        ball->removeEventListener(MouseEvent::ROLL_OVER, this, &Pad2D::_mouseEventHandler);
        ball->removeEventListener(MouseEvent::ROLL_OUT, this, &Pad2D::_mouseEventHandler);
        ball->removeEventListener(MouseEvent::MOUSE_DOWN, this, &Pad2D::_mouseEventHandler);
        delete ball;
        ball = NULL;
        
        _label = NULL;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void Pad2D::_setup() {
        //printf("[Pad2D]_setup()\n");

    }

    //--------------------------------------------------------------
    //
    void Pad2D::_update() {
        
        if(!ball->isMouseDown()) return;
        
        //------------------------------------------
        float tx = mouseX() + _draggablePoint->x;
        float ty = mouseY() + _draggablePoint->y;
        
        if(tx < 18) tx = 18;
        if(18 + _width < tx) tx = 18 + _width;
        if(ty < 18) ty = 18;
        if(18 + _height < ty) ty = 18 + _height;
        
        ball->x(tx);
        ball->y(ty);
        
        _areaPress();
        //------------------------------------------
        
        //------------------------------------------
        float temp1 = _xValue;
        float temp2 = _yValue;
        
        //------------------------------------------
        //値の更新
        _updateValue();
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(temp1 != _xValue || temp2 != _yValue) {
            PadEvent* event = new PadEvent(PadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
        //------------------------------------------
    }

    //--------------------------------------------------------------
    //
    void Pad2D::_draw() {
        
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    TextField* Pad2D::label() { return _label; }
    void Pad2D::label(TextField* value) { _label = NULL; }
    
    //--------------------------------------------------------------
    //
    float Pad2D::xRatio() { return _xRatio; }
    void Pad2D::xRatio(float value, bool dispatch) {
        float temp = value;
        if(temp <= 0.0) temp = 0.0;
        
        ball->x(temp * _width);
        _areaPress();
        
        //------------------------------------------
        //値の更新
        _updateValue();
        //------------------------------------------
        
        if(dispatch) {
            PadEvent* event = new PadEvent(PadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
    }
    
    //--------------------------------------------------------------
    //
    float Pad2D::yRatio() { return _yRatio; }
    void Pad2D::yRatio(float value, bool dispatch) {
        float temp = value;
        if(temp >= 1.0) temp = 1.0;
        
        ball->y(temp * _height);
        _areaPress();
        
        //------------------------------------------
        //値の更新
        _updateValue();
        //------------------------------------------
        
        if(dispatch) {
            PadEvent* event = new PadEvent(PadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
    }

    //--------------------------------------------------------------
    //
    float Pad2D::xValue() { return _xValue; }
    void Pad2D::xValue(float value, bool dispatch) {
//        float temp = value;
//        if(temp <= 0.0) temp = 0.0;
        
        ball->x(value * _width);
        _areaPress();
        
        //------------------------------------------
        //値の更新
        _updateValue();
        //------------------------------------------
        
        if(dispatch) {
            PadEvent* event = new PadEvent(PadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
    }

    //--------------------------------------------------------------
    //
    float Pad2D::yValue() { return _yValue; }
    void Pad2D::yValue(float value, bool dispatch) {
        ball->y(value * _height);
        _areaPress();
        
        //------------------------------------------
        //値の更新
        _updateValue();
        //------------------------------------------
        
        if(dispatch) {
            PadEvent* event = new PadEvent(PadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
    }

    //==============================================================
    // PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //値の更新
    void Pad2D::_updateValue() {
        
        _xRatio = (ball->x() - 18) / _width;
        _yRatio = (ball->y() - 18) / _height;
        _xRatioText->text("x:" + ofToString(_xRatio));
        _yRatioText->text("y:" + ofToString(_yRatio));
        
        _xValue = _leftValue + _rangeWidth * _xRatio;
        _yValue = _topValue + _rangeHeight * _yRatio;
        _xValueText->text("x:" + ofToString(_xValue));
        _yValueText->text("y:" + ofToString(_yValue));
    }
    
    //--------------------------------------------------------------
    //
    void Pad2D::_areaOver() {
        Graphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _overColor);
        g->beginFill(_normalColor, 1);
        g->drawRect(18, 18, _width, _height);
        //横線・縦線
        g->lineStyle(1, _overColor);
        g->moveTo(18, ball->y());
        g->lineTo(18 + _width, ball->y());
        g->moveTo(ball->x(), 18);
        g->lineTo(ball->x(), 18 + _height);
        //------------------------------------------

        _ballOver();
        
//        //------------------------------------------
//        g = ball->graphics();
//        g->clear();
//        g->beginFill(0xff0000, 0);
//        g->drawCircle(0, 0, _ballRadius * 2.5);
//        g->lineStyle(1, _overColor);
//        g->beginFill(_normalColor, 1);
//        g->drawCircle(0, 0, _ballRadius);
//        g->endFill();
//        //------------------------------------------    
    }
    //--------------------------------------------------------------
    //
    void Pad2D::_areaOut() {
        Graphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawRect(18, 18, _width, _height);
        //横線・縦線
        g->lineStyle(1, _lineColor);
        g->moveTo(18, ball->y());
        g->lineTo(18 + _width, ball->y());
        g->moveTo(ball->x(), 18);
        g->lineTo(ball->x(), 18 + _height);
        //------------------------------------------
        
        _ballOut();
    }
    //--------------------------------------------------------------
    //
    void Pad2D::_areaPress() {
        Graphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _activeColor);
        g->beginFill(_normalColor, 1);
        g->drawRect(18, 18, _width, _height);
        //横線・縦線
        g->lineStyle(1, _activeColor);
        g->moveTo(18, ball->y());
        g->lineTo(18 + _width, ball->y());
        g->moveTo(ball->x(), 18);
        g->lineTo(ball->x(), 18 + _height);
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Pad2D::_areaRelease() {
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
        g->drawRect(18, 18, _width, _height);
        //横線・縦線
        g->lineStyle(1, _lineColor);
        g->moveTo(18, ball->y());
        g->lineTo(18 + _width, ball->y());
        g->moveTo(ball->x(), 18);
        g->lineTo(ball->x(), 18 + _height);
        //------------------------------------------
    }

    //--------------------------------------------------------------
    //
    void Pad2D::_ballOver() {
        Graphics* g;
        
        //------------------------------------------
        g = ball->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_overColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void Pad2D::_ballOut() {
        if(ball->isMouseDown()) return;
        
        if(isMouseOver()){
            _areaOver();
            return;
        }
        
        Graphics* g;
        
        //------------------------------------------
        g = ball->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Pad2D::_ballPress() {
        _areaPress();

        _draggablePoint->x = ball->x() - mouseX();
        _draggablePoint->y = ball->y() - mouseY();
        
        Graphics* g;
        
        //------------------------------------------
        g = ball->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_activeColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Pad2D::_ballRelease() {
        _areaRelease();
        
        if(ball->isMouseOver()) {
            _ballOver();
            return;
        }
        
        Graphics* g;
        //------------------------------------------
        g = ball->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Pad2D::_ballMove() {
        
    }

    //==============================================================
    // EVENT HANDLER
    //==============================================================

    //--------------------------------------------------------------
    //
    void Pad2D::_mouseEventHandler(Event& event) {
//        cout << "[Pad2D]_mouseEventHandler(" << event.type() << ")" << endl;
//        cout << "[Pad2D]this          = " << this << ", " << ((DisplayObject*) this)->name() << endl;
//        cout << "[Pad2D]currentTarget = " << event.currentTarget() << ", " << ((DisplayObject*) event.currentTarget())->name() << endl;
//        cout << "[Pad2D]target        = " << event.target() << ", " << ((DisplayObject*) event.target())->name() << endl;
        
//        if(_dialer01->track->isMouseDown()) return;
//        if(_dialer02->track->isMouseDown()) return;
//        if(_dialer03->track->isMouseDown()) return;
//        if(_dialer04->track->isMouseDown()) return;
        
        //MOUSE OVER
        if(event.type() == MouseEvent::ROLL_OVER) {
//        if(event.type() == MouseEvent::MOUSE_OVER) {
            if(event.target() == this) _areaOver();
            if(event.target() == ball) _ballOver();
        }
        
        //MOUSE OUT
        if(event.type() == MouseEvent::ROLL_OUT) {
//        if(event.type() == MouseEvent::MOUSE_OUT) {
            if(event.target() == this) _areaOut();
            if(event.target() == ball) _ballOut();
        }
        
        //MOUSE DOWN
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            if(event.target() == ball) {
                _ballPress();
                stage()->addEventListener(MouseEvent::MOUSE_UP, this, &Pad2D::_mouseEventHandler);
            }
        }
        
        //MOUSE UP
        if(event.type() == MouseEvent::MOUSE_UP) {
            if(event.target() == stage()) {
                _ballRelease();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, this, &Pad2D::_mouseEventHandler);
            }
        }
        
        //MOUSE_MOVE
        if(event.type() == MouseEvent::MOUSE_MOVE) {
            if(event.currentTarget() == this) {
                
            }
        }
    }
    
    //--------------------------------------------------------------
    //
    void Pad2D::_uiEventHandler(Event& event) {
//        cout << "[Pad2D]_mouseEventHandler(" << event.type() << ")" << endl;
//        cout << "[Pad2D]this          = " << this << ", " << ((DisplayObject*) this)->name() << endl;
//        cout << "[Pad2D]currentTarget = " << event.currentTarget() << ", " << ((DisplayObject*) event.currentTarget())->name() << endl;
//        cout << "[Pad2D]target        = " << event.target() << ", " << ((DisplayObject*) event.target())->name() << endl;

        //ナンバーダイアラー
        if(event.type() == NumberDialerEvent::CHANGE) {
            NumberDialerEvent& numberDialerEvent = *(NumberDialerEvent*) &event;
            NumberDialer* dialer = (NumberDialer*)(event.currentTarget());
            
            //左
            if(dialer == _dialer01) {
                _leftValue = dialer->value();
                
                _dialer03->min(_leftValue, false);
                _rangeWidth = _rightValue - _leftValue;
            }
            //上
            if(dialer == _dialer02) {
                _topValue = dialer->value();
                
                _dialer04->min(_topValue, false);
                _rangeHeight = _bottomValue - _topValue;
            }
            //右
            if(dialer == _dialer03) {
                _rightValue = dialer->value();
                
                _dialer01->max(_rightValue, false);
                _rangeWidth = _rightValue - _leftValue;
            }
            //下
            if(dialer == _dialer04) {
                _bottomValue = dialer->value();
                
                _dialer02->max(_bottomValue, false);
                _rangeHeight = _bottomValue - _topValue;
            }
            
            _updateValue();
            
            //------------------------------------------
            PadEvent* event = new PadEvent(PadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            //------------------------------------------
        }
    }
    
}
