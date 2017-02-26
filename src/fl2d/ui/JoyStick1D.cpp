//
//  Joystick1D.cpp
//  ofApp
//
//  Created by 横田達也 on 2016/07/26.
//
//

#include "Joystick1D.h"

namespace fl2d {
    //水平
    string Joystick1D::HORIZONTALLY = "horizontally";
    //垂直
    string Joystick1D::VERTICALLY = "vertically";
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    Joystick1D::Joystick1D(float length, float leverDiameter) {
        //cout << "[Joystick1D]Joystick1D()" << endl;
        
        _target = this;
        name("Joystick1D");
        
        _value = 0.0;
        
        _uiLength = length;
        _leverRadius = leverDiameter * 0.5;
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _normalLineColor.setHex(FlashConfig::UI_LINE_COLOR);
        _overLineColor.setHex(FlashConfig::UI_OVER_LINE_COLOR);
        _activeLineColor.setHex(FlashConfig::UI_ACTIVE_LINE_COLOR);
        _deactiveLineColor.setHex(FlashConfig::UI_DEACTIVE_LINE_COLOR);
        
        _normalColor.setHex(FlashConfig::UI_NORMAL_COLOR);
        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);
        _deactiveColor.setHex(FlashConfig::UI_DEACTIVE_COLOR);
        
        _type = HORIZONTALLY;
        //        _type = VERTICALLY;
        
        //水平
        if(_type == VERTICALLY) {
            _center = ofPoint(_uiLength * 0.5, _leverRadius);
        } else
        //垂直
        if(_type == HORIZONTALLY) {
            _center = ofPoint(_leverRadius, _uiLength * 0.5);
        }
        
        Graphics* g;
        //------------------------------------------
        g = graphics();
        g->enabledSmoothing(true);
        g->clear();
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        //水平
        if(_type == VERTICALLY) {
            g->drawRoundRect(
                             0,
                             0,
                             _uiLength,
                             _leverRadius * 2,
                             _leverRadius
                             );
        } else
        //垂直
        if(_type == HORIZONTALLY) {
            g->drawRoundRect(
                             0,
                             0,
                             _leverRadius * 2,
                             _uiLength,
                             _leverRadius
                             );
        }
        g->endFill();
        addEventListener(MouseEvent::ROLL_OVER, this, &Joystick1D::_mouseEventHandler);
        addEventListener(MouseEvent::ROLL_OUT, this, &Joystick1D::_mouseEventHandler);
        //------------------------------------------
        //------------------------------------------
        lever = new Sprite();
        g = lever->graphics();
        g->enabledSmoothing(true);
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_normalColor.getHex());
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        lever->x(_center.x);
        lever->y(_center.y);
        lever->useHandCursor(true);
        lever->addEventListener(MouseEvent::ROLL_OVER, this, &Joystick1D::_mouseEventHandler);
        lever->addEventListener(MouseEvent::ROLL_OUT, this, &Joystick1D::_mouseEventHandler);
        lever->addEventListener(MouseEvent::MOUSE_DOWN, this, &Joystick1D::_mouseEventHandler);
        lever->addEventListener(MouseEvent::MOUSE_MOVE, this, &Joystick1D::_mouseEventHandler);
        lever->addEventListener(MouseEvent::DRAGGING, this, &Joystick1D::_mouseEventHandler);
        addChild(lever);
        
        _draggablePoint = ofPoint(0, 0);
        //------------------------------------------
        
        //------------------------------------------
        _flg = false;
        
        //水平
        if(_type == VERTICALLY) {
            _targetValue = _center.x;
        } else
        //垂直
        if(_type == HORIZONTALLY) {
            _targetValue = _center.y;
        }
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _label = NULL;
        //------------------------------------------
        
        _enabled = true;
    }
    
    //--------------------------------------------------------------
    //
    Joystick1D::~Joystick1D() {
        //cout << "[Joystick1D]~Joystick1D()" << endl;
        
        removeEventListener(MouseEvent::ROLL_OVER, this, &Joystick1D::_mouseEventHandler);
        removeEventListener(MouseEvent::ROLL_OUT, this, &Joystick1D::_mouseEventHandler);
        
        lever->removeEventListener(MouseEvent::ROLL_OVER, this, &Joystick1D::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::ROLL_OUT, this, &Joystick1D::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::MOUSE_DOWN, this, &Joystick1D::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::MOUSE_MOVE, this, &Joystick1D::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::DRAGGING, this, &Joystick1D::_mouseEventHandler);
        
        _value = 0.0;
        
        _uiLength = 0.0;
        _leverRadius = 0.0;
        
        delete lever;
        lever = NULL;
        
        _flg = false;
        _targetValue = 0.0;
        
        _label = NULL;
        
        _enabled = false;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Joystick1D::_setup() {
        //cout << "[SimpleSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    //
    void Joystick1D::_update() {
        //cout << "isMouseDown" << lever->isMouseDown() << endl;
        
        if(lever->isMouseDown()) {
            //------------------------------------------
            //水平
            if(_type == VERTICALLY) {
                //------------------------------------------
                float tx = mouseX() - _draggablePoint.x;
                float shiftX = tx - _center.x;
                
                float distance = _center.distance(ofPoint(tx, _center.y));
                if((_uiLength * 0.5 - _leverRadius - 1) < distance) {
                    float n = (_uiLength * 0.5 - _leverRadius - 1) / distance;
                    tx = _center.x + (shiftX * n);
                }
                lever->x(tx);
                
                _value = (lever->x() - _center.x) / (_uiLength * 0.5 - _leverRadius);
            } else
                //垂直
                if(_type == HORIZONTALLY) {
                    //------------------------------------------
                    float ty = mouseY() - _draggablePoint.y;
                    float shiftY = ty - _center.y;
                    
                    float distance = _center.distance(ofPoint(_center.x, ty));
                    if((_uiLength * 0.5 - _leverRadius - 1) < distance){
                        float n = (_uiLength * 0.5 - _leverRadius - 1) / distance;
                        ty = _center.y + (shiftY * n);
                    }
                    lever->y(ty);
                    
                    _value = -1 * (lever->y() - _center.y) / (_uiLength * 0.5 - _leverRadius);
                }
            //------------------------------------------
            
            //------------------------------------------
            Joystick1DEvent* event;
            event = new Joystick1DEvent(Joystick1DEvent::CHANGE);
            event->__value = _value;
            dispatchEvent(event);
            
            //水平
            if(_type == VERTICALLY) {
                if(_value > 0) {
                    event = new Joystick1DEvent(Joystick1DEvent::RIGHT);
                    event->__value = _value;
                    dispatchEvent(event);
                }
                if(_value < 0) {
                    event = new Joystick1DEvent(Joystick1DEvent::LEFT);
                    event->__value = _value;
                    dispatchEvent(event);
                }
            } else
                //垂直
                if(_type == HORIZONTALLY) {
                    if(_value > 0) {
                        event = new Joystick1DEvent(Joystick1DEvent::UP);
                        event->__value = _value;
                        dispatchEvent(event);
                    }
                    if(_value < 0) {
                        event = new Joystick1DEvent(Joystick1DEvent::DOWN);
                        event->__value = _value;
                        dispatchEvent(event);
                    }
                }
            //------------------------------------------
        } else if(_flg) {
            //------------------------------------------
            //水平
            if(_type == VERTICALLY) {
                float tx = _targetValue;
                if(!_flg) tx = lever->x() + (_center.x - lever->x()) * 0.4f;
                float shiftX = tx - _center.y;
                
                float distance = _center.distance(ofPoint(tx, _center.y));
                if((_uiLength * 0.5 - _leverRadius - 1) < distance){
                    float n = (_uiLength * 0.5 - _leverRadius - 1) / distance;
                    tx = _center.x + (shiftX * n);
                }
                lever->x(tx);
                
                _value = (lever->x() - _center.x) / (_uiLength * 0.5 - _leverRadius);
            } else
            //垂直
            if(_type == HORIZONTALLY) {
                float ty = _targetValue;
                if(!_flg) ty = lever->y() + (_center.y - lever->y()) * 0.4f;
                float shiftY = ty - _center.y;
                
                float distance = _center.distance(ofPoint(_center.x, ty));
                if((_uiLength * 0.5 - _leverRadius - 1) < distance){
                    float n = (_uiLength * 0.5 - _leverRadius - 1) / distance;
                    ty = _center.y + (shiftY * n);
                }
                lever->y(ty);
                
                _value = -1 * (lever->y() - _center.y) / (_uiLength * 0.5 - _leverRadius);
            }
            //------------------------------------------
            
            //------------------------------------------
            Joystick1DEvent* event;
            event = new Joystick1DEvent(Joystick1DEvent::CHANGE);
            event->__value = _value;
            dispatchEvent(event);
            
            //水平
            if(_type == VERTICALLY) {
                if(_value > 0) {
                    event = new Joystick1DEvent(Joystick1DEvent::RIGHT);
                    event->__value = _value;
                    dispatchEvent(event);
                }
                if(_value < 0) {
                    event = new Joystick1DEvent(Joystick1DEvent::LEFT);
                    event->__value = _value;
                    dispatchEvent(event);
                }
            } else
                //垂直
                if(_type == HORIZONTALLY) {
                    if(_value > 0) {
                        event = new Joystick1DEvent(Joystick1DEvent::UP);
                        event->__value = _value;
                        dispatchEvent(event);
                    }
                    if(_value < 0) {
                        event = new Joystick1DEvent(Joystick1DEvent::DOWN);
                        event->__value = _value;
                        dispatchEvent(event);
                    }
                }
            //------------------------------------------
        } else {
            //------------------------------------------
            //水平
            if(_type == VERTICALLY) {
                float distanceX = _center.x - lever->x();
                if(-0.5f < distanceX && distanceX < 0.5f) {
                    lever->x(_center.x);
                } else {
                    lever->x(lever->x() + (_center.x - lever->x()) * 0.4f);
                    _value = (lever->x() - _center.x) / (_uiLength * 0.5 - _leverRadius);
                    
                    Joystick1DEvent* event = new Joystick1DEvent(Joystick1DEvent::CHANGE);
                    event->__value = _value;
                    dispatchEvent(event);
                }
            } else
                //垂直
                if(_type == HORIZONTALLY) {
                    float distanceY = _center.y - lever->y();
                    if(-0.5f < distanceY && distanceY < 0.5f) {
                        lever->y(_center.y);
                    } else {
                        lever->y(lever->y() + (_center.y - lever->y()) * 0.4f);
                        _value = -1 * (lever->y() - _center.y) / (_uiLength * 0.5 - _leverRadius);
                        
                        Joystick1DEvent* event = new Joystick1DEvent(Joystick1DEvent::CHANGE);
                        event->__value = _value;
                        dispatchEvent(event);
                    }
                }
            //------------------------------------------
        }
        
//        _flgX = false;
        _flg = false;
    }
    
    //--------------------------------------------------------------
    //
    void Joystick1D::_draw() {
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    TextField* Joystick1D::label() { return _label; }
    void Joystick1D::label(TextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    string Joystick1D::type() { return _type; }
    void Joystick1D::type(string value) {
        _type = value;
        
        //水平
        if(_type == VERTICALLY) {
            _center = ofPoint(_uiLength * 0.5, _leverRadius);
        } else
            //垂直
            if(_type == HORIZONTALLY) {
                _center = ofPoint(_leverRadius, _uiLength * 0.5);
            }
        
        lever->x(_center.x);
        lever->y(_center.y);
        
        if(isMouseOver()) {
            _ballOver();
        } else {
            _ballOut();
        }
    }
    
    //--------------------------------------------------------------
    //
    float Joystick1D::value() { return _value; }
    
    //--------------------------------------------------------------
    //
    void Joystick1D::moveLever(float value) {
        //cout << "[Joystick1D]moveLever()" << endl;
        if(_type == VERTICALLY) {
            _targetValue = lever->x() - (_uiLength * 0.5 - _leverRadius - 1) * value;
        } else
        if(_type == HORIZONTALLY) {
            _targetValue = lever->y() - (_uiLength * 0.5 - _leverRadius - 1) * value;
        }

        _flg = true;
    }
    
    //--------------------------------------------------------------
    //
    bool Joystick1D::enabled() { return _enabled; }
    void Joystick1D::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        if(_enabled) {
            _label->textColor(_labelNormalColor);
        } else {
            _label->textColor(_labelDeactiveColor);
        }
        
        Graphics* g;
        //------------------------------------------
        g = graphics();
        g->clear();
        if(_enabled) {
            g->lineStyle(1, _normalLineColor.getHex());
            g->beginFill(_normalColor.getHex(), 1);
        } else {
            g->lineStyle(1, _deactiveLineColor.getHex());
            g->beginFill(_deactiveColor.getHex(), 1);
        }
        //水平
        if(_type == VERTICALLY) {
            g->drawRoundRect(
                             0,
                             0,
                             _uiLength,
                             _leverRadius * 2,
                             _leverRadius
                             );
        } else
        //垂直
        if(_type == HORIZONTALLY) {
            g->drawRoundRect(
                             0,
                             0,
                             _leverRadius * 2,
                             _uiLength,
                             _leverRadius
                             );
        }
        g->endFill();
        //------------------------------------------
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        if(_enabled) {
            g->lineStyle(1, _normalLineColor.getHex());
            g->beginFill(_normalColor.getHex(), 1);
        } else {
            g->lineStyle(1, _deactiveLineColor.getHex());
            g->beginFill(_deactiveColor.getHex(), 1);
        }
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        //------------------------------------------
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Joystick1D::_areaOver() {
        //if(lever->isMouseDown()) return;
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _overLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        //水平
        if(_type == VERTICALLY) {
            g->drawRoundRect(
                             0,
                             0,
                             _uiLength,
                             _leverRadius * 2,
                             _leverRadius
                             );
        } else
        //垂直
        if(_type == HORIZONTALLY) {
            g->drawRoundRect(
                             0,
                             0,
                             _leverRadius * 2,
                             _uiLength,
                             _leverRadius
                             );
        }
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void Joystick1D::_areaOut() {
        //if(lever->isMouseDown()) return;
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        //水平
        if(_type == VERTICALLY) {
            g->drawRoundRect(
                             0,
                             0,
                             _uiLength,
                             _leverRadius * 2,
                             _leverRadius
                             );
        } else
            //垂直
            if(_type == HORIZONTALLY) {
                g->drawRoundRect(
                                 0,
                                 0,
                                 _leverRadius * 2,
                                 _uiLength,
                                 _leverRadius
                                 );
            }
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void Joystick1D::_areaPress() {
        
    }
    //--------------------------------------------------------------
    //
    void Joystick1D::_areaRelease() {
        
    }
    
    //--------------------------------------------------------------
    //
    void Joystick1D::_ballOver() {
        if(lever->isMouseDown()) return;
        
        _areaOver();
        
        Graphics* g;
        g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_overColor.getHex());
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void Joystick1D::_ballOut() {
        if(lever->isMouseDown()) return;
        
        _areaOut();
        
        Graphics* g;
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_normalColor.getHex());
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Joystick1D::_ballPress() {
        _draggablePoint.x = mouseX() - lever->x();
        _draggablePoint.y = mouseY() - lever->y();
        
        Graphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _activeLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        //水平
        if(_type == VERTICALLY) {
            g->drawRoundRect(
                             0,
                             0,
                             _uiLength,
                             _leverRadius * 2,
                             _leverRadius
                             );
        } else
            //垂直
            if(_type == HORIZONTALLY) {
                g->drawRoundRect(
                                 0,
                                 0,
                                 _leverRadius * 2,
                                 _uiLength,
                                 _leverRadius
                                 );
            }
        g->endFill();
        //------------------------------------------
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_activeColor.getHex());
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Joystick1D::_ballRelease() {
        _draggablePoint.x = 0;
        _draggablePoint.y = 0;
        
        Graphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        if(isMouseOver()) {
            g->lineStyle(1, _overLineColor.getHex());
        } else {
            g->lineStyle(1, _normalLineColor.getHex());
        }
        g->beginFill(_normalColor.getHex(), 1);
        //水平
        if(_type == VERTICALLY) {
            g->drawRoundRect(
                             0,
                             0,
                             _uiLength,
                             _leverRadius * 2,
                             _leverRadius
                             );
        } else
            //垂直
            if(_type == HORIZONTALLY) {
                g->drawRoundRect(
                                 0,
                                 0,
                                 _leverRadius * 2,
                                 _uiLength,
                                 _leverRadius
                                 );
            }
        g->endFill();
        //------------------------------------------
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _normalLineColor.getHex());
        if(lever->isMouseOver()) {
            g->beginFill(_overColor.getHex());
        } else {
            g->beginFill(_normalColor.getHex());
        }
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Joystick1D::_ballMove() {
        
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Joystick1D::_mouseEventHandler(Event& event) {
        //cout << "[Joystick1D]_mouseEventHandler(" << event.type() << endl;
        
        if(event.type() == MouseEvent::ROLL_OVER) {
            //if(event.target() == this) _areaOver();
            if(event.target() == lever) _ballOver();
        }
        
        if(event.type() == MouseEvent::ROLL_OUT) {
            //if(event.target() == this) _areaOut();
            if(event.target() == lever) _ballOut();
        }
        
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            //if(event.target() == this) _areaPress();
            if(event.target() == lever){
                _ballPress();
                stage()->addEventListener(MouseEvent::MOUSE_UP, this, &Joystick1D::_mouseEventHandler);
            }
        }
        
        if(event.type() == MouseEvent::MOUSE_UP) {
            //if(event.target() == this) _areaRelease();
            if(event.currentTarget() == stage()){
                _ballRelease();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, this, &Joystick1D::_mouseEventHandler);
            }
        }
        
        if(event.type() == MouseEvent::MOUSE_MOVE) {
            if(event.target() == lever) _ballMove();
        }
        
        if(event.type() == MouseEvent::DRAGGING) {
            if(event.target() == lever){
                
            }
        }    
    }
    
}
