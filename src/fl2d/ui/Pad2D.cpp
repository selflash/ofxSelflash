#include "Pad2D.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Pad2D::Pad2D(float width, float height) {
        //printf("[Pad2D]Pad2D()\n");
        
        _target = this;
        name("Pad2D");
        
        //mouseChildren(false);
        //buttonMode(false);
        
        _width = width;
        _height = height;
        _areaWidth = _width;
        _areaHeight = _height;
        _leftValue = 0;
        _rightValue = 1;
        _topValue = 0;
        _bottomValue = 1;
        _n = 0;
        
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
        g->drawRect(_n, _n, _areaWidth, _areaHeight);
        
        g->lineStyle(1, _lineColor);
        g->moveTo(_n, _n + _areaHeight * 0.5);
        g->lineTo(_n + _areaWidth, _n + _areaHeight * 0.5);
        g->moveTo(_n + _areaWidth * 0.5, _n);
        g->lineTo(_n + _areaWidth * 0.5, _n + _areaHeight);
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
        _rangeWidth = _rightValue - _leftValue;
        _rangeHeight = _bottomValue - _topValue;
        //------------------------------------------
        
        //------------------------------------------
        ball = new Sprite();
        ball->useHandCursor(true);
        g = ball->graphics();
        g->enabledSmoothing(true);
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        ball->x(_n + _areaWidth * 0.5);
        ball->y(_n + _areaHeight * 0.5);
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
        _xRatioText->x(_n);
        _xRatioText->y(18 * 0);
        _xRatioText->width(_areaWidth);
        _xRatioText->autoSize(TextFieldAutoSize::LEFT);
        _xRatioText->textColor(_labelNormalColor);
        addChild(_xRatioText);
        
        _yRatioText = new TextField();
        _yRatioText->x(_n);
        _yRatioText->y(18 * 1);
        _yRatioText->width(_areaWidth);
        _yRatioText->autoSize(TextFieldAutoSize::LEFT);
        _yRatioText->textColor(_labelNormalColor);
        addChild(_yRatioText);
        
        _xValueText = new TextField();
        //_xValueText->x(_trackWidth * 0.5);
        _xValueText->x(_n);
        _xValueText->y(18 * 2);
        _xValueText->width(_areaWidth);
        _xValueText->autoSize(TextFieldAutoSize::LEFT);
        _xValueText->textColor(_labelNormalColor);
        //addChild(_xValueText);
        
        _yValueText = new TextField();
        _yValueText->x(_n);
        _yValueText->y(18 * 3);
        _yValueText->width(_areaWidth);
        _yValueText->autoSize(TextFieldAutoSize::LEFT);
        _yValueText->textColor(_labelNormalColor);
        //addChild(_yValueText);
        
        _xRatio = ball->x() / _areaWidth;
        _yRatio = ball->y() / _areaHeight;
        _xRatioText->text("x:" + ofToString(_xRatio));
        _yRatioText->text("y:" + ofToString(_yRatio));
        
        _xValue = ball->x() / _areaWidth;
        _yValue = ball->y() / _areaHeight;
        _xValueText->text("x:" + ofToString(_xValue));
        _yValueText->text("y:" + ofToString(_yValue));
        //------------------------------------------
        
        _updateValue();
    }
    
    //--------------------------------------------------------------
    //
    Pad2D::Pad2D(float width, float height, float left, float right, float top, float bottom) {
        //printf("[Pad2D]Pad2D()\n");
        
        _target = this;
        name("Pad2D");
        
        //mouseChildren(false);
        //buttonMode(false);
        
        _width = width;
        _height = height;
        _areaWidth = _width - 40;
        _areaHeight = _height - 40;
        _leftValue = left;
        _rightValue = right;
        _topValue = top;
        _bottomValue = bottom;
        _n = 20;

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
        g->drawRect(_n, _n, _areaWidth, _areaHeight);
        
        g->lineStyle(1, _lineColor);
        g->moveTo(_n, _n + _areaHeight * 0.5);
        g->lineTo(_n + _areaWidth, _n + _areaHeight * 0.5);
        g->moveTo(_n + _areaWidth * 0.5, _n);
        g->lineTo(_n + _areaWidth * 0.5, _n + _areaHeight);
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
        _dialer01 = new NumberDialer(_areaWidth);
        _dialer01->x(1);
        _dialer01->y(_n);
        _dialer01->type(NumberDialer::VERTICALLY);
        _dialer01->max(_rightValue, false);
        _dialer01->value(_leftValue);
        _dialer01->addEventListener(NumberDialerEvent::CHANGE, this, &Pad2D::_uiEventHandler);
        addChild(_dialer01);
        //上
        _dialer02 = new NumberDialer(_areaWidth - 0);
        _dialer02->x(_n);
        _dialer02->y(2);
        _dialer02->stepValue(-1);
        _dialer02->max(_bottomValue, false);
        _dialer02->value(_topValue);
        _dialer02->addEventListener(NumberDialerEvent::CHANGE, this, &Pad2D::_uiEventHandler);
        addChild(_dialer02);
        //右
        _dialer03 = new NumberDialer(_areaWidth);
        _dialer03->x(_n + _areaWidth);
        _dialer03->y(_n);
        _dialer03->type(NumberDialer::VERTICALLY);
        _dialer03->min(_leftValue, false);
        _dialer03->value(_rightValue);
        _dialer03->addEventListener(NumberDialerEvent::CHANGE, this, &Pad2D::_uiEventHandler);
        addChild(_dialer03);
        //下
        _dialer04 = new NumberDialer(_areaWidth - 0);
        _dialer04->x(_n);
        _dialer04->y(_n + _areaHeight);
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
        g->enabledSmoothing(true);
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _ballRadius * 2.5);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 1);
        g->drawCircle(0, 0, _ballRadius);
        g->endFill();
        ball->x(_n + _areaWidth * 0.5);
        ball->y(_n + _areaHeight * 0.5);
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
        _xRatioText->x(_n);
        _xRatioText->y(_n * 1);
        _xRatioText->width(_areaWidth);
        _xRatioText->autoSize(TextFieldAutoSize::LEFT);
        _xRatioText->textColor(_labelNormalColor);
        addChild(_xRatioText);
        
        _yRatioText = new TextField();
        _yRatioText->x(_n);
        _yRatioText->y(_n * 2);
        _yRatioText->width(_areaWidth);
        _yRatioText->autoSize(TextFieldAutoSize::LEFT);
        _yRatioText->textColor(_labelNormalColor);
        addChild(_yRatioText);
        
        _xValueText = new TextField();
        //_xValueText->x(_trackWidth * 0.5);
        _xValueText->x(_n);
        _xValueText->y(_n * 3);
        _xValueText->width(_areaWidth);
        _xValueText->autoSize(TextFieldAutoSize::LEFT);
        _xValueText->textColor(_labelNormalColor);
        addChild(_xValueText);
        
        _yValueText = new TextField();
        _yValueText->x(_n);
        _yValueText->y(_n * 4);
        _yValueText->width(_areaWidth);
        _yValueText->autoSize(TextFieldAutoSize::LEFT);
        _yValueText->textColor(_labelNormalColor);
        addChild(_yValueText);
        
        _xRatio = ball->x() / _areaWidth;
        _yRatio = ball->y() / _areaHeight;
        _xRatioText->text("x:" + ofToString(_xRatio));
        _yRatioText->text("y:" + ofToString(_yRatio));
        
        _xValue = ball->x() / _areaWidth;
        _yValue = ball->y() / _areaHeight;
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
        
        if(_dialer01 != NULL) {
            removeChild(_dialer01);
            delete _dialer01;
            _dialer01 = NULL;
        }
        
        if(_dialer02 != NULL) {
            removeChild(_dialer02);
            delete _dialer02;
            _dialer02 = NULL;
        }

        if(_dialer03 != NULL) {
            removeChild(_dialer03);
            delete _dialer03;
            _dialer03 = NULL;
        }

        if(_dialer04 != NULL) {
            removeChild(_dialer04);
            delete _dialer04;
            _dialer04 = NULL;
        }

        removeChild(_xRatioText);
        delete _xRatioText;
        _xRatioText = NULL;
        
        removeChild(_yRatioText);
        delete _xRatioText;
        _xRatioText = NULL;
        
        if(_xValueText != NULL) {
            removeChild(_xValueText);
            delete _xValueText;
            _xValueText = NULL;
        }

        if(_yValueText != NULL) {
            removeChild(_yValueText);
            delete _yValueText;
            _yValueText = NULL;
        }
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
        
        if(tx < _n) tx = _n;
        if(_n + _areaWidth < tx) tx = _n + _areaWidth;
        if(ty < _n) ty = _n;
        if(_n + _areaHeight < ty) ty = _n + _areaHeight;
        
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
        
        ball->x(temp * _areaWidth);
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
        
        ball->y(temp * _areaHeight);
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
        
        ball->x(value * _areaWidth);
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
        ball->y(value * _areaHeight);
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
        
        _xRatio = (ball->x() - _n) / _areaWidth;
        _yRatio = (ball->y() - _n) / _areaHeight;
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
        g->drawRect(_n, _n, _areaWidth, _areaHeight);
        //横線・縦線
        g->lineStyle(1, _overColor);
        g->moveTo(_n, ball->y());
        g->lineTo(_n + _areaWidth, ball->y());
        g->moveTo(ball->x(), _n);
        g->lineTo(ball->x(), _n + _areaHeight);
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
        g->drawRect(_n, _n, _areaWidth, _areaHeight);
        //横線・縦線
        g->lineStyle(1, _lineColor);
        g->moveTo(_n, ball->y());
        g->lineTo(_n + _areaWidth, ball->y());
        g->moveTo(ball->x(), _n);
        g->lineTo(ball->x(), _n + _areaHeight);
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
        g->drawRect(_n, _n, _areaWidth, _areaHeight);
        //横線・縦線
        g->lineStyle(1, _activeColor);
        g->moveTo(_n, ball->y());
        g->lineTo(_n + _areaWidth, ball->y());
        g->moveTo(ball->x(), _n);
        g->lineTo(ball->x(), _n + _areaHeight);
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
        g->drawRect(_n, _n, _areaWidth, _areaHeight);
        //横線・縦線
        g->lineStyle(1, _lineColor);
        g->moveTo(_n, ball->y());
        g->lineTo(_n + _areaWidth, ball->y());
        g->moveTo(ball->x(), _n);
        g->lineTo(ball->x(), _n + _areaHeight);
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
