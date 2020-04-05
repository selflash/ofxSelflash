#include "flPad2D.h"

namespace fl2d {

    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
    flPad2D::flPad2D(float width, float height) {
        //ofLog() << "[flPad2D]flPad2D()";
        
        _target = this;
        name("flPad2D");

        _width = width;
        _height = height;
        _areaWidth = _width;
        _areaHeight = _height;
        
        buttonMode(true);

        flGraphics* g;
        
        //------------------------------------------
        area = new flSprite();
        area->name("flPad2D.body");
//        g = body->graphics();
//        g->enabledSmoothing(true);
        area->addEventListener(flMouseEvent::ROLL_OVER, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::ROLL_OUT, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::MOUSE_OVER, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::MOUSE_OUT, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::MOUSE_UP, this, &flPad2D::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_MOVE, this, &flPad2D::_mouseEventHandler);
        addChild(area);
        //------------------------------------------
        
        //------------------------------------------
        _rangeWidth = _rightValue - _leftValue;
        _rangeHeight = _bottomValue - _topValue;
        //------------------------------------------
        
        //------------------------------------------
        lever = new flSprite();
        lever->name("flPad2D.lever");
        g = lever->graphics();
        g->enabledSmoothing(true);
        lever->x(_n + _areaWidth * 0.5);
        lever->y(_n + _areaHeight * 0.5);
        lever->useHandCursor(true);
        lever->addEventListener(flMouseEvent::ROLL_OVER, this, &flPad2D::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::ROLL_OUT, this, &flPad2D::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad2D::_mouseEventHandler);
        addChild(lever);
        //------------------------------------------
        
        _xRatio = (lever->x() - _n) / _areaWidth;
        _yRatio = (lever->y() - _n) / _areaHeight;
        _value.x = _leftValue + _rangeWidth * _xRatio;
        _value.y = _topValue + _rangeHeight * _yRatio;

        //------------------------------------------
//        _ratioText = new flTextField();
//        _ratioText->name("flPad2D.ratioText");
//        _ratioText->x(_n);
//        _ratioText->y(18 * 0);
//        _ratioText->width(_areaWidth);
//        _ratioText->autoSize(flTextFieldAutoSize::LEFT);
//        _ratioText->text("x:" + ofToString(_xRatio, 2) + "\r\ny:" + ofToString(_yRatio, 2));
//        _ratioText->mouseEnabled(false);
//        addChild(_ratioText);

        _valueText = new flTextField();
        _valueText->name("flPad2D.velueText");
        _valueText->x(_n);
//        _valueText->y(18 * 2);
        _valueText->y(18 * 0);
        _valueText->width(_areaWidth);
        _valueText->autoSize(flTextFieldAutoSize::LEFT);
        _valueText->text("x:" + ofToString(_value.x, _digit) + "\r\ny:" + ofToString(_value.y, _digit));
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
//        _updateValue();
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    flPad2D::flPad2D(float width, float height, float left, float right, float top, float bottom) {
        //ofLog() << "[flPad2D]flPad2D()";
        
        _target = this;
        name("flPad2D");

        _n = 18;

        _width = width;
        _height = height;
        _areaWidth = _width - _n * 2;
        _areaHeight = _height - _n * 2;
        _leftValue = left;
        _rightValue = right;
        _topValue = top;
        _bottomValue = bottom;

        buttonMode(true);

        flGraphics* g;
        
        //------------------------------------------
        area = new flSprite();
        area->name("flPad2D.body");
//        g = body->graphics();
//        g->enabledSmoothing(true);
        area->addEventListener(flMouseEvent::ROLL_OVER, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::ROLL_OUT, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::MOUSE_OVER, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::MOUSE_OUT, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad2D::_mouseEventHandler);
        area->addEventListener(flMouseEvent::MOUSE_UP, this, &flPad2D::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_MOVE, this, &flPad2D::_mouseEventHandler);
        addChild(area);
        //------------------------------------------
        
        //------------------------------------------
        _rangeWidth = _rightValue - _leftValue;
        _rangeHeight = _bottomValue - _topValue;
        //------------------------------------------

        //------------------------------------------
        //左
        _dialer01 = new flNumericDialer(_areaWidth);
        _dialer01->name("flPad2D.leftDialer");
        _dialer01->x(0);
        _dialer01->y(_n);
        _dialer01->direction(flNumericDialer::VERTICALLY);
        _dialer01->max(_rightValue, false);
        _dialer01->value(_leftValue);
        _dialer01->dragDirection(flNumericDialer::HORIZONTALLY);
        _dialer01->addEventListener(flNumericDialerEvent::CHANGE, this, &flPad2D::_uiEventHandler);
        addChild(_dialer01);
        //上
        _dialer02 = new flNumericDialer(_areaWidth - 0);
        _dialer02->name("flPad2D.topDialer");
        _dialer02->x(_n);
        _dialer02->y(0);
        _dialer02->stepSize(-1);
        _dialer02->max(_bottomValue, false);
        _dialer02->value(_topValue);
        _dialer02->addEventListener(flNumericDialerEvent::CHANGE, this, &flPad2D::_uiEventHandler);
        addChild(_dialer02);
        //右
        _dialer03 = new flNumericDialer(_areaWidth);
        _dialer03->name("flPad2D.rightDialer");
        _dialer03->x(_n + _areaWidth);
        _dialer03->y(_n);
        _dialer03->direction(flNumericDialer::VERTICALLY);
        _dialer03->dragDirection(flNumericDialer::HORIZONTALLY);
        _dialer03->min(_leftValue, false);
        _dialer03->value(_rightValue);
        _dialer03->addEventListener(flNumericDialerEvent::CHANGE, this, &flPad2D::_uiEventHandler);
        addChild(_dialer03);
        //下
        _dialer04 = new flNumericDialer(_areaWidth - 0);
        _dialer04->name("flPad2D.bottomDialer");
        _dialer04->x(_n);
        _dialer04->y(_n + _areaHeight);
        _dialer04->stepSize(-1);
        _dialer04->min(_topValue, false);
        _dialer04->value(_bottomValue);
        _dialer04->addEventListener(flNumericDialerEvent::CHANGE, this, &flPad2D::_uiEventHandler);
        addChild(_dialer04);
        //------------------------------------------
        
        //------------------------------------------
        lever = new flSprite();
        lever->name("flPad2D.lever");
        g = lever->graphics();
        g->enabledSmoothing(true);
        lever->x(_n + _areaWidth * 0.5);
        lever->y(_n + _areaHeight * 0.5);
        lever->useHandCursor(true);
        lever->addEventListener(flMouseEvent::ROLL_OVER, this, &flPad2D::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::ROLL_OUT, this, &flPad2D::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad2D::_mouseEventHandler);
        addChild(lever);
        //------------------------------------------
        
        _xRatio = (lever->x() - _n) / _areaWidth;
        _yRatio = (lever->y() - _n) / _areaHeight;
        _value.x = _leftValue + _rangeWidth * _xRatio;
        _value.y = _topValue + _rangeHeight * _yRatio;

        //------------------------------------------
//        _ratioText = new flTextField();
//        _ratioText->name("flPad2D.ratioText");
//        _ratioText->x(_n);
//        _ratioText->y(_n + 18 * 0);
//        _ratioText->width(_areaWidth);
//        _ratioText->autoSize(flTextFieldAutoSize::LEFT);
//        _ratioText->text("x:" + ofToString(_xRatio, 2) + "\r\ny:" + ofToString(_yRatio, 2));
//        _ratioText->mouseEnabled(false);
//        addChild(_ratioText);
        
        _valueText = new flTextField();
        _valueText->name("flPad2D.velueText");
        _valueText->x(_n);
//        _valueText->y(_n + 18 * 2);
        _valueText->y(_n + 18 * 0);
        _valueText->width(_areaWidth);
        _valueText->autoSize(flTextFieldAutoSize::LEFT);
        _valueText->text("x:" + ofToString(_value.x, _digit) + "\r\ny:" + ofToString(_value.y, _digit));
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
//        _updateValue();
        _setNormalColor();
    }

    //--------------------------------------------------------------
    flPad2D::~flPad2D() {
        area->removeEventListener(flMouseEvent::ROLL_OVER, this, &flPad2D::_mouseEventHandler);
        area->removeEventListener(flMouseEvent::ROLL_OUT, this, &flPad2D::_mouseEventHandler);
        area->removeEventListener(flMouseEvent::MOUSE_OVER, this, &flPad2D::_mouseEventHandler);
        area->removeEventListener(flMouseEvent::MOUSE_OUT, this, &flPad2D::_mouseEventHandler);
        area->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad2D::_mouseEventHandler);
        area->removeEventListener(flMouseEvent::MOUSE_UP, this, &flPad2D::_mouseEventHandler);
        delete area;
        area = NULL;

        lever->removeEventListener(flMouseEvent::ROLL_OVER, this, &flPad2D::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::ROLL_OUT, this, &flPad2D::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flPad2D::_mouseEventHandler);
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

//        if(_ratioText != NULL) {
//            removeChild(_ratioText);
//            delete _ratioText;
//            _ratioText = NULL;
//        }
        
        if(_valueText != NULL) {
            removeChild(_valueText);
            delete _valueText;
            _valueText = NULL;
        }
                
        //------------------------------------------
        _vec2Param = NULL;
        _listeners.unsubscribeAll();
        //------------------------------------------
    }

    //==============================================================
    // Setup / Update / Draw
    //==============================================================

    //--------------------------------------------------------------
    void flPad2D::_setup() {
        //printf("[flPad2D]_setup()\n");

    }

    //--------------------------------------------------------------
    void flPad2D::_update() {
        flUIBase::_update();

        if(area->isMouseDown() || lever->isMouseDown()) {
            _onPress();
        }
        
        _bChangedByOfParm["value"] = false;
    }

    //--------------------------------------------------------------
    void flPad2D::_draw() {
        
    }

    //==============================================================
    // Public Method
    //==============================================================

    //--------------------------------------------------------------
    void flPad2D::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flPad2D::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        if(_dialer01 != NULL) _dialer01->enabled(_enabled);
        if(_dialer02 != NULL) _dialer02->enabled(_enabled);
        if(_dialer03 != NULL) _dialer03->enabled(_enabled);
        if(_dialer04 != NULL) _dialer04->enabled(_enabled);

        if (_enabled) {
            _setNormalColor();
        } else {
            _setDisableNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    float flPad2D::xRatio() { return _xRatio; }
    void flPad2D::xRatio(float value, bool dispatch) {
//        float temp = value;
//        if(temp <= 0.0) temp = 0.0;
//
//        lever->x(temp * _areaWidth);
//        _onPress();
//
//        //------------------------------------------
//        //値の更新
//        _updateValue();
//        //------------------------------------------
//
//        if(dispatch) {
//            _dispatchEvent();
//        }
    }
    
    //--------------------------------------------------------------
    float flPad2D::yRatio() { return _yRatio; }
    void flPad2D::yRatio(float value, bool dispatch) {
//        float temp = value;
//        if(temp >= 1.0) temp = 1.0;
//
//        lever->y(temp * _areaHeight);
//        _onPress();
//
//        //------------------------------------------
//        //値の更新
//        _updateValue();
//        //------------------------------------------
//
//        if(dispatch) {
//            _dispatchEvent();
//        }
    }

    //--------------------------------------------------------------
    float flPad2D::xValue() { return _value.x; }
    void flPad2D::xValue(float value, bool dispatch) {
        //------------------------------------------
        //Update Value.
        _value.x = value;
        
        if(_value.x <= _leftValue) _value.x = _leftValue;
        if(_value.x >= _rightValue) _value.x = _rightValue;
        
        _xRatio = ((_value.x - _leftValue) / _rangeWidth);
        
        lever->x(_n + (_xRatio * _areaWidth));
        //------------------------------------------
        
        _setNormalColor();
        
        //------------------------------------------
//        _ratioText->text("x:" + ofToString(_xRatio, _digit) + "\r\ny:" + ofToString(_yRatio, _digit));
        _valueText->text("x:" + ofToString(_value.x, _digit) + "\r\ny:" + ofToString(_value.y, _digit));
        if(dispatch) _dispatchEvent();
        
        if(!_bChangedByOfParm["value"]) {
            if(_vec2Param != NULL) {
                _bChangedByMyself["value"] = true;
                _vec2Param->set(_value);
            }
        }
        //------------------------------------------
    }

    //--------------------------------------------------------------
    float flPad2D::yValue() { return _value.y; }
    void flPad2D::yValue(float value, bool dispatch) {
        //------------------------------------------
        //Update Value.
        _value.y = value;
        
        if(_value.y <= _topValue) _value.y = _topValue;
        if(_value.y >= _bottomValue) _value.y = _bottomValue;
        
        _yRatio = ((_value.y - _topValue) / _rangeHeight);
        
        lever->y(_n + (_yRatio * _areaHeight));
        //------------------------------------------
        
        _setNormalColor();
        
        //------------------------------------------
//        _ratioText->text("x:" + ofToString(_xRatio, _digit) + "\r\ny:" + ofToString(_yRatio, _digit));
        _valueText->text("x:" + ofToString(_value.x, _digit) + "\r\ny:" + ofToString(_value.y, _digit));
        if(dispatch) _dispatchEvent();
        
        if(!_bChangedByOfParm["value"]) {
            if(_vec2Param != NULL) {
                _bChangedByMyself["value"] = true;
                _vec2Param->set(_value);
            }
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    vec2 flPad2D::value() { return _value; }
    void flPad2D::value(float xValue, float yValue, bool dispatch) {
        //------------------------------------------
        //Update Value.
        _value.x = xValue;
        _value.y = yValue;
        
        if(_value.x <= _leftValue) _value.x = _leftValue;
        if(_value.x >= _rightValue) _value.x = _rightValue;
        if(_value.y <= _topValue) _value.y = _topValue;
        if(_value.y >= _bottomValue) _value.y = _bottomValue;
        
        _xRatio = ((_value.x - _leftValue) / _rangeWidth);
        _yRatio = ((_value.y - _topValue) / _rangeHeight);
        
        lever->x(_n + (_xRatio * _areaWidth));
        lever->y(_n + (_yRatio * _areaHeight));
        //------------------------------------------
        
        _setNormalColor();
        
        //------------------------------------------
//        _ratioText->text("x:" + ofToString(_xRatio, _digit) + "\r\ny:" + ofToString(_yRatio, _digit));
        _valueText->text("x:" + ofToString(_value.x, _digit) + "\r\ny:" + ofToString(_value.y, _digit));
        if(dispatch) _dispatchEvent();

        if(!_bChangedByOfParm["value"]) {
            if(_vec2Param != NULL) {
                _bChangedByMyself["value"] = true;
                _vec2Param->set(_value);
            }
        }
        //------------------------------------------
    }
    void flPad2D::value(vec2 value, bool dispatch) {
        //------------------------------------------
        //Update Value.
        _value.x = value.x;
        _value.y = value.y;
        
        if(_value.x <= _leftValue) _value.x = _leftValue;
        if(_value.x >= _rightValue) _value.x = _rightValue;
        if(_value.y <= _topValue) _value.y = _topValue;
        if(_value.y >= _bottomValue) _value.y = _bottomValue;

        _xRatio = ((_value.x - _leftValue) / _rangeWidth);
        _yRatio = ((_value.y - _topValue) / _rangeHeight);
        
        lever->x(_n + (_xRatio * _areaWidth));
        lever->y(_n + (_yRatio * _areaHeight));
        //------------------------------------------

        _setNormalColor();
        
        //------------------------------------------
//        _ratioText->text("x:" + ofToString(_xRatio, _digit) + "\r\ny:" + ofToString(_yRatio, _digit));
        _valueText->text("x:" + ofToString(_value.x, _digit) + "\r\ny:" + ofToString(_value.y, _digit));
        if(dispatch) _dispatchEvent();

        if(!_bChangedByOfParm["value"]) {
            if(_vec2Param != NULL) {
                _bChangedByMyself["value"] = true;
                _vec2Param->set(_value);
            }
        }
        //------------------------------------------
    }

    //==============================================================
    // Protected / Private Method
    //==============================================================

    //--------------------------------------------------------------
    void flPad2D::_dispatchEvent() {
        flPadEvent* event = new flPadEvent(flPadEvent::CHANGE);
        event->__xRatio = _xRatio;
        event->__yRatio = _yRatio;
        event->__xValue = _value.x;
        event->__yValue = _value.y;
        dispatchEvent(event);
    }

    //--------------------------------------------------------------
    void flPad2D::_onOver() {
        if(area->isMouseDown() || lever->isMouseDown()) return;
        
        _setOverColor();
    }
    
    //--------------------------------------------------------------
    void flPad2D::_onOut() {
        if(area->isMouseDown() || lever->isMouseDown()) return;
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flPad2D::_onPress() {
        float preXValue = _value.x;
        float preYValue = _value.y;

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
        
        _value.x = _leftValue + _rangeWidth * _xRatio;
        _value.y = _topValue + _rangeHeight * _yRatio;
        //------------------------------------------

        _setActiveColor();

        //------------------------------------------
        if(preXValue != _value.x || preYValue != _value.y) {
            //        _ratioText->text("x:" + ofToString(_xRatio, _digit) + "\r\ny:" + ofToString(_yRatio, _digit));
            _valueText->text("x:" + ofToString(_value.x, _digit) + "\r\ny:" + ofToString(_value.y, _digit));
            _dispatchEvent();
            
            if(_vec2Param != NULL) {
                _bChangedByMyself["value"] = true;
                _vec2Param->set(_value);
            }
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flPad2D::_onRelease() {
        if(area->isMouseDown() || lever->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    void flPad2D::_onMove() {
        
    }
    
    //--------------------------------------------------------------
    void flPad2D::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
//        _ratioText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_ACTIVE_COLOR);
    }
    
    //--------------------------------------------------------------
    void flPad2D::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
//        _ratioText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR);
        _drawLeverGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR);
    }
    
    //--------------------------------------------------------------
    void flPad2D::_setSelectedOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
//        _ratioText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flPad2D::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
//        _ratioText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flPad2D::_setDisableNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
//        _ratioText->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);

        _drawAreaGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flPad2D::_setDisableActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
//        _ratioText->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);

        _drawAreaGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flPad2D::_drawAreaGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = area->graphics();
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
    void flPad2D::_drawLeverGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
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
    void flPad2D::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flPad2D]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flPad2D]this          = " << this << ", " << ((flDisplayObject*) this)->name();
//        ofLog() << "[flPad2D]currentTarget = " << event.currentTarget() << ", " << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flPad2D]target        = " << event.target() << ", " << ((flDisplayObject*) event.target())->name();
        
//        if(_dialer01->track->isMouseDown()) return;
//        if(_dialer02->track->isMouseDown()) return;
//        if(_dialer03->track->isMouseDown()) return;
//        if(_dialer04->track->isMouseDown()) return;

        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == area) _onOver();
            if(event.target() == lever) _onOver();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == area) _onOut();
            if(event.target() == lever) _onOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == area) {
                //_leverPress();

                _draggablePoint.x = 0.0;
                _draggablePoint.y = 0.0;
                _onPress();

                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flPad2D::_mouseEventHandler);
                }
            }
            if(event.target() == lever) {
                _draggablePoint.x = lever->x() - mouseX();
                _draggablePoint.y = lever->y() - mouseY();
                _onPress();
                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flPad2D::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            _draggablePoint.x = 0;
            _draggablePoint.y = 0;
            _onRelease();
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flPad2D::_mouseEventHandler);
            }
        }
        
        //Mouse Move
        if(event.type() == flMouseEvent::MOUSE_MOVE) {
            if(event.target() == lever) _onMove();
        }
    }
    
    //--------------------------------------------------------------
    void flPad2D::_uiEventHandler(flEvent& event) {
//        ofLog() << "[flPad2D]_uiEventHandler(" << event.type() << ")";
//        ofLog() << "[flPad2D]this          = " << this << ", " << ((flDisplayObject*) this)->name();
//        ofLog() << "[flPad2D]currentTarget = " << event.currentTarget() << ", " << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flPad2D]target        = " << event.target() << ", " << ((flDisplayObject*) event.target())->name();

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
            
            //------------------------------------------
            //Update value.
            if(_value.x <= _leftValue) _value.x = _leftValue;
            if(_value.x >= _rightValue) _value.x = _rightValue;
            if(_value.y <= _topValue) _value.y = _topValue;
            if(_value.y >= _bottomValue) _value.y = _bottomValue;
            
            _xRatio = ((_value.x - _leftValue) / _rangeWidth);
            _yRatio = ((_value.y - _topValue) / _rangeHeight);
            
            lever->x(_n + (_xRatio * _areaWidth));
            lever->y(_n + (_yRatio * _areaHeight));
            
//            _xRatio = (lever->x() - _n) / _areaWidth;
//            _yRatio = (lever->y() - _n) / _areaHeight;
//
//            _value.x = _leftValue + _rangeWidth * _xRatio;
//            _value.y = _topValue + _rangeHeight * _yRatio;
            //------------------------------------------

            //------------------------------------------
//            _ratioText->text("x:" + ofToString(_xRatio, _digit) + "\r\ny:" + ofToString(_yRatio, _digit));
            _valueText->text("x:" + ofToString(_value.x, _digit) + "\r\ny:" + ofToString(_value.y, _digit));
            _dispatchEvent();
            
            if(!_bChangedByOfParm["value"]) {
                if(_vec2Param != NULL) {
                    _bChangedByMyself["value"] = true;
                    _vec2Param->set(_value);
                }
            }
            //------------------------------------------
        }
    }
    
}
