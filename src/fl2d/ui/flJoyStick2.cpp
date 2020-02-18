#include "flJoyStick2.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flJoyStick2::flJoyStick2(float areaDiameter) {
        //ofLog() << "[flJoyStick2]flJoyStick2()";
        
        _target = this;
        name("flJoyStick2");

        _xValue = 0.0;
        _yValue = 0.0;
        
        _areaRadius = areaDiameter * 0.5;
        _leverRadius = 14 * 0.5;
        _maxDistance = (_areaRadius - _leverRadius - 1);
        
        _center = ofPoint(_areaRadius, _areaRadius);
        
        flGraphics* g;
        
        //------------------------------------------
        g = graphics();
        g->enabledSmoothing(true);
        //------------------------------------------
        
        //------------------------------------------
        lever = new flSprite();
        lever->name("flJoyStick2.lever");
        g = lever->graphics();
        g->enabledSmoothing(true);
        lever->x(_center.x);
        lever->y(_center.y);
        lever->useHandCursor(true);
        lever->addEventListener(flMouseEvent::ROLL_OVER, this, &flJoyStick2::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::ROLL_OUT, this, &flJoyStick2::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flJoyStick2::_mouseEventHandler);
//        lever->addEventListener(flMouseEvent::MOUSE_MOVE, this, &flJoyStick2::_mouseEventHandler);
//        lever->addEventListener(flMouseEvent::DRAGGING, this, &flJoyStick2::_mouseEventHandler);
        addChild(lever);
        //------------------------------------------
        
        //------------------------------------------
        _valueText = new flTextField();
        _valueText->name("flJoyStick2.velueText");
        _valueText->x(_center.x - 30);
        _valueText->y(_center.y - 20);
        _valueText->width(areaDiameter * 0.6);
        _valueText->autoSize(flTextFieldAutoSize::LEFT);
        _valueText->text("x:" + ofToString(_xValue, 2) + "\r\ny:" + ofToString(_yValue, 2));
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
        //------------------------------------------
        _flgX = false;
        _flgY = false;
        _targetX = _center.x;
        _targetY = _center.y;
        //------------------------------------------
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    flJoyStick2::~flJoyStick2() {
        //ofLog() << "[flJoyStick2]~flJoyStick2()";
        
        _xValue = 0.0;
        _yValue = 0.0;
        
        _areaRadius = 0.0;
        _leverRadius = 0.0;
        
        lever->removeEventListener(flMouseEvent::ROLL_OVER, this, &flJoyStick2::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::ROLL_OUT, this, &flJoyStick2::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flJoyStick2::_mouseEventHandler);
//        lever->removeEventListener(flMouseEvent::MOUSE_MOVE, this, &flJoyStick2::_mouseEventHandler);
//        lever->removeEventListener(flMouseEvent::DRAGGING, this, &flJoyStick2::_mouseEventHandler);
        delete lever;
        lever = NULL;
        
        _flgX = false;
        _flgY = false;
        _targetX = 0.0;
        _targetY = 0.0;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flJoyStick2::_setup() {
        //ofLog() << "[SimpleSlider]setup()";
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_update() {
        //ofLog() << "isMouseDown" << lever->isMouseDown();
        
        float preXValue = _xValue;
        float preYValue = _yValue;

        if(lever->isMouseDown()) {
            //------------------------------------------
            float tx = mouseX() - _draggablePoint.x;
            float ty = mouseY() - _draggablePoint.y;
            float shiftX = tx - _center.x;
            float shiftY = ty - _center.y;

            float distance = _center.distance(ofPoint(tx, ty));
            if(_maxDistance < distance) {
                float n = _maxDistance / distance;
                tx = _center.x + (shiftX * n);
                ty = _center.y + (shiftY * n);
            }

            lever->x(tx);
            lever->y(ty);
            //------------------------------------------
            
            //------------------------------------------
            //Update value.
            _xValue = (lever->x() - _center.x) / _maxDistance;
            _yValue = -1 * (lever->y() - _center.y) / _maxDistance;
            if(_yValue == -0) _yValue = 0;
            //------------------------------------------
            
            _setActiveColor();
            
            //------------------------------------------
            if(preXValue != _xValue || preYValue != _yValue) {
                _valueText->text("x:" + ofToString(_xValue, 2) + "\r\ny:" + ofToString(_yValue, 2));
                
                //------------------------------------------
                flJoyStick2Event* event;
                event = new flJoyStick2Event(flJoyStick2Event::CHANGE);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
                
                if(_xValue > 0) {
                    event = new flJoyStick2Event(flJoyStick2Event::RIGHT);
                    event->__xValue = _xValue;
                    event->__yValue = _yValue;
                    dispatchEvent(event);
                }
                if(_xValue < 0) {
                    event = new flJoyStick2Event(flJoyStick2Event::LEFT);
                    event->__xValue = _xValue;
                    event->__yValue = _yValue;
                    dispatchEvent(event);
                }
                if(_yValue > 0) {
                    event = new flJoyStick2Event(flJoyStick2Event::UP);
                    event->__xValue = _xValue;
                    event->__yValue = _yValue;
                    dispatchEvent(event);
                }
                if(_yValue < 0) {
                    event = new flJoyStick2Event(flJoyStick2Event::DOWN);
                    event->__xValue = _xValue;
                    event->__yValue = _yValue;
                    dispatchEvent(event);
                }
                //------------------------------------------
            }
            //------------------------------------------
        } else if(_flgX || _flgY) {
            //------------------------------------------
            float tx = _targetX;
            float ty = _targetY;
            if(!_flgX) tx = lever->x() + (_center.x - lever->x()) * 0.4f;
            if(!_flgY) ty = lever->y() + (_center.y - lever->y()) * 0.4f;
            float shiftX = tx - _center.x;
            float shiftY = ty - _center.y;

            float distance = _center.distance(ofPoint(tx, ty));
            if(_maxDistance < distance){
                float n = _maxDistance / distance;
                tx = _center.x + (shiftX * n);
                ty = _center.y + (shiftY * n);
            }

            lever->x(tx);
            lever->y(ty);
            //------------------------------------------
            
            //------------------------------------------
            //Update value.
            _xValue = (lever->x() - _center.x) / _maxDistance;
            _yValue = -1 * (lever->y() - _center.y) / _maxDistance;
            if(_yValue == -0) _yValue = 0;
            //------------------------------------------

            //------------------------------------------
            if(lever->isMouseOver()) {
                _setOverColor();
            } else {
                _setNormalColor();
            }
            //------------------------------------------

            //------------------------------------------
            if(preXValue != _xValue || preYValue != _yValue) {
                _valueText->text("x:" + ofToString(_xValue, 2) + "\r\ny:" + ofToString(_yValue, 2));
                
                //------------------------------------------
                flJoyStick2Event* event;
                event = new flJoyStick2Event(flJoyStick2Event::CHANGE);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
                
                if(_flgX && _xValue > 0) {
                    event = new flJoyStick2Event(flJoyStick2Event::RIGHT);
                    event->__xValue = _xValue;
                    event->__yValue = _yValue;
                    dispatchEvent(event);
                }
                if(_flgX && _xValue < 0) {
                    event = new flJoyStick2Event(flJoyStick2Event::LEFT);
                    event->__xValue = _xValue;
                    event->__yValue = _yValue;
                    dispatchEvent(event);
                }
                if(_flgY && _yValue > 0) {
                    event = new flJoyStick2Event(flJoyStick2Event::UP);
                    event->__xValue = _xValue;
                    event->__yValue = _yValue;
                    dispatchEvent(event);
                }
                if(_flgY && _yValue < 0) {
                    event = new flJoyStick2Event(flJoyStick2Event::DOWN);
                    event->__xValue = _xValue;
                    event->__yValue = _yValue;
                    dispatchEvent(event);
                }
                //------------------------------------------
            }
            //------------------------------------------
        } else {
            //Easing
            float distanceX = _center.x - lever->x();
            float distanceY = _center.y - lever->y();
            if(
               -0.5f < distanceX && distanceX < 0.5f &&
               -0.5f < distanceY && distanceY < 0.5f
               ) {
                lever->x(_center.x);
                lever->y(_center.y);
                
                _xValue = 0;
                _yValue = 0;
            } else {
                lever->x(lever->x() + (_center.x - lever->x()) * 0.4f);
                lever->y(lever->y() + (_center.y - lever->y()) * 0.4f);

                //------------------------------------------
                //Update value.
                _xValue = (lever->x() - _center.x) / _maxDistance;
                _yValue = -1 * (lever->y() - _center.y) / _maxDistance;
                if(_yValue == -0) _yValue = 0;
                //------------------------------------------

                //------------------------------------------
                if(lever->isMouseOver()) {
                    _setOverColor();
                } else {
                    _setNormalColor();
                }
                //------------------------------------------
            }
            
            //------------------------------------------
            if(preXValue != _xValue || preYValue != _yValue) {
                _valueText->text("x:" + ofToString(_xValue, 2) + "\r\ny:" + ofToString(_yValue, 2));
                
                //------------------------------------------
                flJoyStick2Event* event = new flJoyStick2Event(flJoyStick2Event::CHANGE);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
                //------------------------------------------
            }
            //------------------------------------------
        }
        
        _flgX = false;
        _flgY = false;
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_draw() {
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flJoyStick2::label() { return _label; }
    void flJoyStick2::label(flTextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    float flJoyStick2::xValue() { return _xValue; }
    //--------------------------------------------------------------
    float flJoyStick2::yValue() { return _yValue; }
    
    //--------------------------------------------------------------
    void flJoyStick2::leverUp(float value) {
        //ofLog() << "[flJoyStick2]leverUp()";
        _targetY = lever->y() - _maxDistance * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    void flJoyStick2::leverDown(float value) {
        //ofLog() << "[flJoyStick2]leverDown()";
        _targetY = lever->y() + _maxDistance * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    void flJoyStick2::leverLeft(float value) {
        //ofLog() << "[flJoyStick2]leverLeft()";
        _targetX = lever->x() - _maxDistance * value;
        _flgX = true;
    }
    //--------------------------------------------------------------
    void flJoyStick2::leverRight(float value) {
        //ofLog() << "[flJoyStick2]leverRight()";
        _targetX = lever->x() + _maxDistance * value;
        _flgX = true;
    }
    
    //--------------------------------------------------------------
    bool flJoyStick2::enabled() { return _enabled; }
    void flJoyStick2::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        if(_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
        
        flGraphics* g;
        //------------------------------------------
        g = graphics();
        g->clear();
        if(_enabled) {
            g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        } else {
            g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        }
        g->drawCircle(_center.x, _center.y, _areaRadius);
        g->endFill();
        //------------------------------------------
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        if(_enabled) {
            g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        } else {
            g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        }
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        //------------------------------------------
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================

    //--------------------------------------------------------------
    void flJoyStick2::_leverOver() {
        if(lever->isMouseDown()) return;
        
        _setOverColor();
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_leverOut() {
        if(lever->isMouseDown()) return;
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_leverPress() {
        _setActiveColor();
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_leverRelease() {
        
        if(lever->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_leverMove() {
        
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_ACTIVE_COLOR);
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);

        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR);
        _drawLeverGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR);
    }

    //--------------------------------------------------------------
    void flJoyStick2::_setSelectedOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);

        _valueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_setDisableNormalColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_setDisableActiveColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_drawAreaGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = graphics();
        g->clear();
        g->lineStyle(1, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        g->drawCircle(_center.x, _center.y, _areaRadius);
        g->lineStyle(1, 0xffffff);
        g->moveTo(_center.x, _center.y);
        g->lineTo(lever->x(), lever->y());
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flJoyStick2::_drawLeverGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
    }
    
    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flJoyStick2::_mouseEventHandler(flEvent& event) {
        //ofLog() << "[flJoyStick2]_mouseEventHandler(" << event.type();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == lever) _leverOver();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == lever) _leverOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == lever){
                _draggablePoint.x = mouseX() - lever->x();
                _draggablePoint.y = mouseY() - lever->y();
                _leverPress();
                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flJoyStick2::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            _draggablePoint.x = 0;
            _draggablePoint.y = 0;
            _leverRelease();
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flJoyStick2::_mouseEventHandler);
            }
        }
        
        //Mouse Move
//        if(event.type() == flMouseEvent::MOUSE_MOVE) {
//            if(event.target() == lever) _leverMove();
//        }
        
        //Dragging
//        if(event.type() == flMouseEvent::DRAGGING) {
//            if(event.target() == lever){
//
//            }
//        }
    }
    
}
