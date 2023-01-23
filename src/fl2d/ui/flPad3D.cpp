#include "flPad3D.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flPad3D::flPad3D(float width, float height) {
        //ofLog() << "[flPad3D]flPad3D()";
        
        _target = this;
        name("flPad3D");
        
        buttonMode(true);
        
        _width = width;
        _height = height;
        _areaWidth = _width;
        _areaHeight = _height;
        _leftValue = 0;
        _rightValue = 1;
        _topValue = 0;
        _bottomValue = 1;
        _n = 0;
        
        _leverRadius = 6;
        
        flGraphics* g;
        
        //------------------------------------------
        addEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_OVER, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_OUT, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_MOVE, this, &flPad3D::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        _rangeWidth = _rightValue - _leftValue;
        _rangeHeight = _bottomValue - _topValue;
        //------------------------------------------
        
        //------------------------------------------
        lever = new flSprite();
        lever->name("flPad3D.lever");
        g = lever->graphics();
        g->enabledSmoothing(true);
        lever->x(_n + _areaWidth * 0.5);
        lever->y(_n + _areaHeight * 0.5);
        lever->useHandCursor(true);
        lever->addEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        addChild(lever);
        //------------------------------------------
        
        _xRatio = (lever->x() - _n) / _areaWidth;
        _yRatio = (lever->y() - _n) / _areaHeight;
        _xValue = _leftValue + _rangeWidth * _xRatio;
        _yValue = _topValue + _rangeHeight * _yRatio;
        
        //------------------------------------------
        _ratioText = new flTextField();
        _ratioText->name("flPad3D.ratioText");
        _ratioText->x(_n);
        _ratioText->y(18 * 0);
        _ratioText->width(_areaWidth);
        _ratioText->autoSize(flTextFieldAutoSize::LEFT);
        _ratioText->text("x:" + ofToString(_xRatio, 2) + "\r\ny:" + ofToString(_yRatio, 2));
        _ratioText->mouseEnabled(false);
        addChild(_ratioText);
        
        _valueText = new flTextField();
        _valueText->name("flPad3D.velueText");
        _valueText->x(_n);
        _valueText->y(18 * 2);
        _valueText->width(_areaWidth);
        _valueText->autoSize(flTextFieldAutoSize::LEFT);
        _valueText->text("x:" + ofToString(_xValue, 2) + "\r\ny:" + ofToString(_yValue, 2));
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
        //        _updateValue();
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    flPad3D::flPad3D(float width, float height, float left, float right, float top, float bottom) {
        //ofLog() << "[flPad3D]flPad3D()";
        
        _target = this;
        name("flPad3D");
        
        buttonMode(true);
        
        _n = 18;
        
        _width = width;
        _height = height;
        _areaWidth = _width - _n * 2;
        _areaHeight = _height - _n * 2;
        _leftValue = left;
        _rightValue = right;
        _topValue = top;
        _bottomValue = bottom;
        
        _leverRadius = 6;
        
        flGraphics* g;
        
        //------------------------------------------
        addEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_OVER, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_OUT, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_MOVE, this, &flPad3D::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        _rangeWidth = _rightValue - _leftValue;
        _rangeHeight = _bottomValue - _topValue;
        //------------------------------------------
        
        //------------------------------------------
        //左
        _dialer01 = new flNumericDialer(_areaWidth);
        _dialer01->name("flPad3D.leftDialer");
        _dialer01->x(0);
        _dialer01->y(_n);
        _dialer01->direction(flNumericDialer::VERTICALLY);
        _dialer01->max(_rightValue, false);
        _dialer01->value(_leftValue);
        _dialer01->dragDirection(flNumericDialer::HORIZONTALLY);
        _dialer01->addEventListener(flNumericDialerEvent::CHANGE, this, &flPad3D::_uiEventHandler);
        addChild(_dialer01);
        //上
        _dialer02 = new flNumericDialer(_areaWidth - 0);
        _dialer02->name("flPad3D.topDialer");
        _dialer02->x(_n);
        _dialer02->y(0);
        _dialer02->stepSize(-1);
        _dialer02->max(_bottomValue, false);
        _dialer02->value(_topValue);
        _dialer02->addEventListener(flNumericDialerEvent::CHANGE, this, &flPad3D::_uiEventHandler);
        addChild(_dialer02);
        //右
        _dialer03 = new flNumericDialer(_areaWidth);
        _dialer03->name("flPad3D.rightDialer");
        _dialer03->x(_n + _areaWidth);
        _dialer03->y(_n);
        _dialer03->direction(flNumericDialer::VERTICALLY);
        _dialer03->dragDirection(flNumericDialer::HORIZONTALLY);
        _dialer03->min(_leftValue, false);
        _dialer03->value(_rightValue);
        _dialer03->addEventListener(flNumericDialerEvent::CHANGE, this, &flPad3D::_uiEventHandler);
        addChild(_dialer03);
        //下
        _dialer04 = new flNumericDialer(_areaWidth - 0);
        _dialer04->name("flPad3D.bottomDialer");
        _dialer04->x(_n);
        _dialer04->y(_n + _areaHeight);
        _dialer04->stepSize(-1);
        _dialer04->min(_topValue, false);
        _dialer04->value(_bottomValue);
        _dialer04->addEventListener(flNumericDialerEvent::CHANGE, this, &flPad3D::_uiEventHandler);
        addChild(_dialer04);
        //------------------------------------------
        
        //------------------------------------------
        lever = new flSprite();
        lever->name("flPad3D.lever");
        g = lever->graphics();
        g->enabledSmoothing(true);
        lever->x(_n + _areaWidth * 0.5);
        lever->y(_n + _areaHeight * 0.5);
        lever->useHandCursor(true);
        lever->addEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        addChild(lever);
        //------------------------------------------
        
        _xRatio = (lever->x() - _n) / _areaWidth;
        _yRatio = (lever->y() - _n) / _areaHeight;
        _xValue = _leftValue + _rangeWidth * _xRatio;
        _yValue = _topValue + _rangeHeight * _yRatio;
        
        //------------------------------------------
        _ratioText = new flTextField();
        _ratioText->name("flPad3D.ratioText");
        _ratioText->x(_n);
        _ratioText->y(_n + 18 * 0);
        _ratioText->width(_areaWidth);
        _ratioText->autoSize(flTextFieldAutoSize::LEFT);
        _ratioText->text("x:" + ofToString(_xRatio, 2) + "\r\ny:" + ofToString(_yRatio, 2));
        _ratioText->mouseEnabled(false);
        addChild(_ratioText);
        
        _valueText = new flTextField();
        _valueText->name("flPad3D.velueText");
        _valueText->x(_n);
        _valueText->y(_n + 18 * 2);
        _valueText->width(_areaWidth);
        _valueText->autoSize(flTextFieldAutoSize::LEFT);
        _valueText->text("x:" + ofToString(_xValue, 2) + "\r\ny:" + ofToString(_yValue, 2));
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
        //        _updateValue();
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    flPad3D::~flPad3D() {
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_OVER, this, &flPad3D::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_OUT, this, &flPad3D::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
        
        lever->removeEventListener(flMouseEvent::ROLL_OVER, this, &flPad3D::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::ROLL_OUT, this, &flPad3D::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad3D::_mouseEventHandler);
        delete lever;
        lever = NULL;
        
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
        
        removeChild(_ratioText);
        delete _ratioText;
        _ratioText = NULL;
        
        if(_valueText != NULL) {
            removeChild(_valueText);
            delete _valueText;
            _valueText = NULL;
        }
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================

    //--------------------------------------------------------------
    void flPad3D::_setup() {
        //printf("[flPad3D]_setup()\n");
        
    }
    
    //--------------------------------------------------------------
    void flPad3D::_update() {
        if(lever->isMouseDown()) {
            _leverPress();
        }
    }
    
    //--------------------------------------------------------------
    void flPad3D::_draw() {
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================

    //--------------------------------------------------------------
    void flPad3D::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    float flPad3D::xRatio() { return _xRatio; }
    void flPad3D::xRatio(float value, bool dispatch) {
        float temp = value;
        if(temp <= 0.0) temp = 0.0;
        
        lever->x(temp * _areaWidth);
        _areaPress();
        
        //------------------------------------------
        //値の更新
        _updateValue();
        //------------------------------------------
        
        if(dispatch) {
            flPadEvent* event = new flPadEvent(flPadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
    }
    
    //--------------------------------------------------------------
    float flPad3D::yRatio() { return _yRatio; }
    void flPad3D::yRatio(float value, bool dispatch) {
        float temp = value;
        if(temp >= 1.0) temp = 1.0;
        
        lever->y(temp * _areaHeight);
        _areaPress();
        
        //------------------------------------------
        //値の更新
        _updateValue();
        //------------------------------------------
        
        if(dispatch) {
            flPadEvent* event = new flPadEvent(flPadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
    }
    
    //--------------------------------------------------------------
    float flPad3D::xValue() { return _xValue; }
    void flPad3D::xValue(float value, bool dispatch) {
        //        float temp = value;
        //        if(temp <= 0.0) temp = 0.0;
        
        lever->x(value * _areaWidth);
        _areaPress();
        
        //------------------------------------------
        //値の更新
        _updateValue();
        //------------------------------------------
        
        if(dispatch) {
            flPadEvent* event = new flPadEvent(flPadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
    }
    
    //--------------------------------------------------------------
    float flPad3D::yValue() { return _yValue; }
    void flPad3D::yValue(float value, bool dispatch) {
        lever->y(value * _areaHeight);
        _areaPress();
        
        //------------------------------------------
        //値の更新
        _updateValue();
        //------------------------------------------
        
        if(dispatch) {
            flPadEvent* event = new flPadEvent(flPadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
        }
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    //値の更新
    void flPad3D::_updateValue() {
        _xRatio = (lever->x() - _n) / _areaWidth;
        _yRatio = (lever->y() - _n) / _areaHeight;
        _ratioText->text("x:" + ofToString(_xRatio, 2) + "\r\ny:" + ofToString(_yRatio, 2));
        
        _xValue = _leftValue + _rangeWidth * _xRatio;
        _yValue = _topValue + _rangeHeight * _yRatio;
        _valueText->text("x:" + ofToString(_xValue, 2) + "\r\ny:" + ofToString(_yValue, 2));
    }
    
    //--------------------------------------------------------------
    void flPad3D::_areaOver() {
        if(lever->isMouseDown()) return;
        
        _setOverColor();
    }
    //--------------------------------------------------------------
    void flPad3D::_areaOut() {
        if(lever->isMouseDown()) return;
        
        _setNormalColor();
    }
    //--------------------------------------------------------------
    void flPad3D::_areaPress() {
        if(lever->isMouseDown()) return;
        
        float preXValue = _xValue;
        float preYValue = _yValue;
        
        //------------------------------------------
        float tx = mouseX() + _draggablePoint.x;
        float ty = mouseY() + _draggablePoint.y;
        
        if(tx < _n) tx = _n;
        if(_n + _areaWidth < tx) tx = _n + _areaWidth;
        if(ty < _n) ty = _n;
        if(_n + _areaHeight < ty) ty = _n + _areaHeight;
        
        lever->x(tx);
        lever->y(ty);
        //------------------------------------------
        
        //------------------------------------------
        //Update value.
        _xRatio = (lever->x() - _n) / _areaWidth;
        _yRatio = (lever->y() - _n) / _areaHeight;
        
        _xValue = _leftValue + _rangeWidth * _xRatio;
        _yValue = _topValue + _rangeHeight * _yRatio;
        //------------------------------------------
        
        _setActiveColor();
        
        //------------------------------------------
        if(preXValue != _xValue || preYValue != _yValue) {
            _ratioText->text("x:" + ofToString(_xRatio, 2) + "\r\ny:" + ofToString(_yRatio, 2));
            _valueText->text("x:" + ofToString(_xValue, 2) + "\r\ny:" + ofToString(_yValue, 2));
            
            //------------------------------------------
            flPadEvent* event = new flPadEvent(flPadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            //------------------------------------------
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flPad3D::_areaRelease() {
        if(lever->isMouseDown()) return;
        
        if(isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    void flPad3D::_leverOver() {
        if(lever->isMouseDown()) return;
        
        _setOverColor();
    }
    
    //--------------------------------------------------------------
    void flPad3D::_leverOut() {
        if(lever->isMouseDown()) return;
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flPad3D::_leverPress() {
        float preXValue = _xValue;
        float preYValue = _yValue;
        
        //------------------------------------------
        float tx = mouseX() + _draggablePoint.x;
        float ty = mouseY() + _draggablePoint.y;
        
        if(tx < _n) tx = _n;
        if(_n + _areaWidth < tx) tx = _n + _areaWidth;
        if(ty < _n) ty = _n;
        if(_n + _areaHeight < ty) ty = _n + _areaHeight;
        
        lever->x(tx);
        lever->y(ty);
        //------------------------------------------
        
        //------------------------------------------
        //Update value.
        _xRatio = (lever->x() - _n) / _areaWidth;
        _yRatio = (lever->y() - _n) / _areaHeight;
        
        _xValue = _leftValue + _rangeWidth * _xRatio;
        _yValue = _topValue + _rangeHeight * _yRatio;
        //------------------------------------------
        
        _setActiveColor();
        
        //------------------------------------------
        if(preXValue != _xValue || preYValue != _yValue) {
            _ratioText->text("x:" + ofToString(_xRatio, 2) + "\r\ny:" + ofToString(_yRatio, 2));
            _valueText->text("x:" + ofToString(_xValue, 2) + "\r\ny:" + ofToString(_yValue, 2));
            
            //------------------------------------------
            flPadEvent* event = new flPadEvent(flPadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            //------------------------------------------
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flPad3D::_leverRelease() {
        if(lever->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    void flPad3D::_leverMove() {
        
    }
    
    //--------------------------------------------------------------
    void flPad3D::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _ratioText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_BORDER_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_BORDER_NORMAL_COLOR, flDefinition::UI_ACTIVE_COLOR);
    }
    
    //--------------------------------------------------------------
    void flPad3D::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _ratioText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_BORDER_OVER_COLOR, flDefinition::UI_NORMAL_COLOR);
        _drawLeverGraphics(flDefinition::UI_BORDER_OVER_COLOR, flDefinition::UI_OVER_COLOR);
    }
    
    //--------------------------------------------------------------
    void flPad3D::_setSelectedOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _ratioText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_BORDER_OVER_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_BORDER_OVER_COLOR, flDefinition::UI_OVER_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flPad3D::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _ratioText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_BORDER_ACTIVE_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_BORDER_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flPad3D::_setDisableNormalColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flPad3D::_setDisableActiveColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flPad3D::_drawAreaGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = graphics();
        g->clear();
        g->lineStyle(1, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        g->drawRect(_n, _n, _areaWidth, _areaHeight);
        //横線・縦線
        g->lineStyle(1, lineColor.getHex());
        g->moveTo(_n, lever->y());
        g->lineTo(_n + _areaWidth, lever->y());
        g->moveTo(lever->x(), _n);
        g->lineTo(lever->x(), _n + _areaHeight);
    }
    
    //--------------------------------------------------------------
    void flPad3D::_drawLeverGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 2.5);
        g->lineStyle(1, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flPad3D::_mouseEventHandler(flEvent& event) {
        //        ofLog() << "[flPad3D]_mouseEventHandler(" << event.type() << ")";
        //        ofLog() << "[flPad3D]this          = " << this << ", " << ((flDisplayObject*) this)->name();
        //        ofLog() << "[flPad3D]currentTarget = " << event.currentTarget() << ", " << ((flDisplayObject*) event.currentTarget())->name();
        //        ofLog() << "[flPad3D]target        = " << event.target() << ", " << ((flDisplayObject*) event.target())->name();
        
        //        if(_dialer01->track->isMouseDown()) return;
        //        if(_dialer02->track->isMouseDown()) return;
        //        if(_dialer03->track->isMouseDown()) return;
        //        if(_dialer04->track->isMouseDown()) return;
        
        if(_toolTipEnabled) _toolTip->visible(false);

        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) _areaOver();
            if(event.target() == lever) _leverOver();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) _areaOut();
            if(event.target() == lever) _leverOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) {
                _areaPress();
                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
                }
            }
            if(event.target() == lever) {
                _draggablePoint.x = lever->x() - mouseX();
                _draggablePoint.y = lever->y() - mouseY();
                _leverPress();
                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            _draggablePoint.x = 0;
            _draggablePoint.y = 0;
            _leverRelease();
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flPad3D::_mouseEventHandler);
            }
        }
        
        //Mouse Move
        if(event.type() == flMouseEvent::MOUSE_MOVE) {
            if(event.target() == lever) _leverMove();
        }
    }
    
    //--------------------------------------------------------------
    void flPad3D::_uiEventHandler(flEvent& event) {
        //        ofLog() << "[flPad3D]_uiEventHandler(" << event.type() << ")";
        //        ofLog() << "[flPad3D]this          = " << this << ", " << ((flDisplayObject*) this)->name();
        //        ofLog() << "[flPad3D]currentTarget = " << event.currentTarget() << ", " << ((flDisplayObject*) event.currentTarget())->name();
        //        ofLog() << "[flPad3D]target        = " << event.target() << ", " << ((flDisplayObject*) event.target())->name();
        
        //ナンバーダイアラー
        if(event.type() == flNumericDialerEvent::CHANGE) {
            flNumericDialerEvent& numberDialerEvent = *(flNumericDialerEvent*) &event;
            flNumericDialer* dialer = (flNumericDialer*)(event.currentTarget());
            
            //左
            if(dialer == _dialer01) {
                _leftValue = dialer->value();
                
                _dialer03->min(_leftValue, false);
                _rangeWidth = _rightValue - _leftValue;
            }
            //上
            else if(dialer == _dialer02) {
                _topValue = dialer->value();
                
                _dialer04->min(_topValue, false);
                _rangeHeight = _bottomValue - _topValue;
            }
            //右
            else if(dialer == _dialer03) {
                _rightValue = dialer->value();
                
                _dialer01->max(_rightValue, false);
                _rangeWidth = _rightValue - _leftValue;
            }
            //下
            else if(dialer == _dialer04) {
                _bottomValue = dialer->value();
                
                _dialer02->max(_bottomValue, false);
                _rangeHeight = _bottomValue - _topValue;
            }
            
            _updateValue();
            
            //------------------------------------------
            flPadEvent* event = new flPadEvent(flPadEvent::CHANGE);
            event->__xRatio = _xRatio;
            event->__yRatio = _yRatio;
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            //------------------------------------------
        }
    }
    
}
