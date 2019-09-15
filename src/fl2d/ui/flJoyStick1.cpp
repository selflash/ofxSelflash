#include "flJoyStick1.h"

namespace fl2d {
    //水平
    string flJoyStick1::HORIZONTALLY = "horizontally";
    //垂直
    string flJoyStick1::VERTICALLY = "vertically";
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flJoyStick1::flJoyStick1(float length, float leverDiameter) {
        //cout << "[flJoyStick1D]flJoyStick1D()" << endl;
        
        _target = this;
        name("flJoyStick1");
        
        _value = 0.0;
        
        _uiLength = length;
        _leverRadius = leverDiameter * 0.5;
        
        _labelNormalColor = flDefinition::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = flDefinition::UI_LABEL_OVER_COLOR;
        _labelActiveColor = flDefinition::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = flDefinition::UI_LABEL_DEACTIVE_COLOR;
        
        _normalLineColor.setHex(flDefinition::UI_LINE_COLOR);
        _overLineColor.setHex(flDefinition::UI_OVER_LINE_COLOR);
        _activeLineColor.setHex(flDefinition::UI_ACTIVE_LINE_COLOR);
        _deactiveLineColor.setHex(flDefinition::UI_DEACTIVE_LINE_COLOR);
        
        _normalColor.setHex(flDefinition::UI_NORMAL_COLOR);
        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
        _deactiveColor.setHex(flDefinition::UI_DEACTIVE_COLOR);
        
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
        
        flGraphics* g;
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
        addEventListener(flMouseEvent::ROLL_OVER, this, &flJoyStick1::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flJoyStick1::_mouseEventHandler);
        //------------------------------------------
        //------------------------------------------
        lever = new flSprite();
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
        lever->addEventListener(flMouseEvent::ROLL_OVER, this, &flJoyStick1::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::ROLL_OUT, this, &flJoyStick1::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flJoyStick1::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_MOVE, this, &flJoyStick1::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::DRAGGING, this, &flJoyStick1::_mouseEventHandler);
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
    flJoyStick1::~flJoyStick1() {
        //cout << "[flJoyStick1D]~flJoyStick1D()" << endl;
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flJoyStick1::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flJoyStick1::_mouseEventHandler);
        
        lever->removeEventListener(flMouseEvent::ROLL_OVER, this, &flJoyStick1::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::ROLL_OUT, this, &flJoyStick1::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flJoyStick1::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_MOVE, this, &flJoyStick1::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::DRAGGING, this, &flJoyStick1::_mouseEventHandler);
        
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
    void flJoyStick1::_setup() {
        //cout << "[SimpleSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    //
    void flJoyStick1::_update() {
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
            flJoyStick1Event* event;
            event = new flJoyStick1Event(flJoyStick1Event::CHANGE);
            event->__value = _value;
            dispatchEvent(event);
            
            //水平
            if(_type == VERTICALLY) {
                if(_value > 0) {
                    event = new flJoyStick1Event(flJoyStick1Event::RIGHT);
                    event->__value = _value;
                    dispatchEvent(event);
                }
                if(_value < 0) {
                    event = new flJoyStick1Event(flJoyStick1Event::LEFT);
                    event->__value = _value;
                    dispatchEvent(event);
                }
            } else
                //垂直
                if(_type == HORIZONTALLY) {
                    if(_value > 0) {
                        event = new flJoyStick1Event(flJoyStick1Event::UP);
                        event->__value = _value;
                        dispatchEvent(event);
                    }
                    if(_value < 0) {
                        event = new flJoyStick1Event(flJoyStick1Event::DOWN);
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
            flJoyStick1Event* event;
            event = new flJoyStick1Event(flJoyStick1Event::CHANGE);
            event->__value = _value;
            dispatchEvent(event);
            
            //水平
            if(_type == VERTICALLY) {
                if(_value > 0) {
                    event = new flJoyStick1Event(flJoyStick1Event::RIGHT);
                    event->__value = _value;
                    dispatchEvent(event);
                }
                if(_value < 0) {
                    event = new flJoyStick1Event(flJoyStick1Event::LEFT);
                    event->__value = _value;
                    dispatchEvent(event);
                }
            } else
                //垂直
                if(_type == HORIZONTALLY) {
                    if(_value > 0) {
                        event = new flJoyStick1Event(flJoyStick1Event::UP);
                        event->__value = _value;
                        dispatchEvent(event);
                    }
                    if(_value < 0) {
                        event = new flJoyStick1Event(flJoyStick1Event::DOWN);
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
                    
                    flJoyStick1Event* event = new flJoyStick1Event(flJoyStick1Event::CHANGE);
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
                        
                        flJoyStick1Event* event = new flJoyStick1Event(flJoyStick1Event::CHANGE);
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
    void flJoyStick1::_draw() {
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flTextField* flJoyStick1::label() { return _label; }
    void flJoyStick1::label(flTextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    string flJoyStick1::type() { return _type; }
    void flJoyStick1::type(string value) {
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
    float flJoyStick1::value() { return _value; }
    
    //--------------------------------------------------------------
    //
    void flJoyStick1::moveLever(float value) {
        //cout << "[flJoyStick1D]moveLever()" << endl;
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
    bool flJoyStick1::enabled() { return _enabled; }
    void flJoyStick1::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        if(_enabled) {
            _label->textColor(_labelNormalColor);
        } else {
            _label->textColor(_labelDeactiveColor);
        }
        
        flGraphics* g;
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
    void flJoyStick1::_areaOver() {
        //if(lever->isMouseDown()) return;
        
        flGraphics* g;
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
    void flJoyStick1::_areaOut() {
        //if(lever->isMouseDown()) return;
        
        flGraphics* g;
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
    void flJoyStick1::_areaPress() {
        
    }
    //--------------------------------------------------------------
    //
    void flJoyStick1::_areaRelease() {
        
    }
    
    //--------------------------------------------------------------
    //
    void flJoyStick1::_ballOver() {
        if(lever->isMouseDown()) return;
        
        _areaOver();
        
        flGraphics* g;
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
    void flJoyStick1::_ballOut() {
        if(lever->isMouseDown()) return;
        
        _areaOut();
        
        flGraphics* g;
        
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
    void flJoyStick1::_ballPress() {
        _draggablePoint.x = mouseX() - lever->x();
        _draggablePoint.y = mouseY() - lever->y();
        
        flGraphics* g;
        
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
    void flJoyStick1::_ballRelease() {
        _draggablePoint.x = 0;
        _draggablePoint.y = 0;
        
        flGraphics* g;
        
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
    void flJoyStick1::_ballMove() {
        
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flJoyStick1::_mouseEventHandler(flEvent& event) {
        //cout << "[flJoyStick1D]_mouseEventHandler(" << event.type() << endl;
        
        if(event.type() == flMouseEvent::ROLL_OVER) {
            //if(event.target() == this) _areaOver();
            if(event.target() == lever) _ballOver();
        }
        
        if(event.type() == flMouseEvent::ROLL_OUT) {
            //if(event.target() == this) _areaOut();
            if(event.target() == lever) _ballOut();
        }
        
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            //if(event.target() == this) _areaPress();
            if(event.target() == lever){
                _ballPress();
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flJoyStick1::_mouseEventHandler);
            }
        }
        
        if(event.type() == flMouseEvent::MOUSE_UP) {
            //if(event.target() == this) _areaRelease();
            if(event.currentTarget() == stage()){
                _ballRelease();
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flJoyStick1::_mouseEventHandler);
            }
        }
        
        if(event.type() == flMouseEvent::MOUSE_MOVE) {
            if(event.target() == lever) _ballMove();
        }
        
        if(event.type() == flMouseEvent::DRAGGING) {
            if(event.target() == lever){
                
            }
        }    
    }
    
}
