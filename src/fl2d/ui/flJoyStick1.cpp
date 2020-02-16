#include "flJoyStick1.h"

namespace fl2d {
    //水平
    string flJoyStick1::HORIZONTALLY = "horizontally";
    //垂直
    string flJoyStick1::VERTICALLY = "vertically";
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flJoyStick1::flJoyStick1(float length, float leverDiameter) {
        //ofLog() << "[flJoyStick1]flJoyStick1()";

        _target = this;
        name("flJoyStick1");
        
        _value = 0.0;
        
        _label = NULL;
        
        _uiLength = length;
        _leverRadius = leverDiameter * 0.5;
        _maxDistance = (_uiLength * 0.5 - _leverRadius);
        
        _type = HORIZONTALLY;
//        _type = VERTICALLY;
        
        //水平
        if(_type == VERTICALLY) {
            _center = ofPoint(_uiLength * 0.5, _leverRadius);
        }
        //垂直
        else if(_type == HORIZONTALLY) {
            _center = ofPoint(_leverRadius, _uiLength * 0.5);
        }
        
        flGraphics* g;
        
        //------------------------------------------
        g = graphics();
        g->enabledSmoothing(true);
        //------------------------------------------
        
        //------------------------------------------
        lever = new flSprite();
        lever->name("flJoyStick1.lever");
        g = lever->graphics();
        g->enabledSmoothing(true);
        lever->x(_center.x);
        lever->y(_center.y);
        lever->useHandCursor(true);
        lever->addEventListener(flMouseEvent::ROLL_OVER, this, &flJoyStick1::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::ROLL_OUT, this, &flJoyStick1::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flJoyStick1::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_MOVE, this, &flJoyStick1::_mouseEventHandler);
//        lever->addEventListener(flMouseEvent::DRAGGING, this, &flJoyStick1::_mouseEventHandler);
        addChild(lever);
        //------------------------------------------
        
        //------------------------------------------
        _valueText = new flTextField();
        _valueText->name("flJoyStick1.velueText");
        _valueText->x(2);
        _valueText->y(0);
        _valueText->width(_uiLength - 4);
        _valueText->autoSize(flTextFieldAutoSize::LEFT);
        _valueText->text(ofToString(_value, 2));
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
        //------------------------------------------
        _flg = false;
        
        //水平
        if(_type == VERTICALLY) {
            _targetValue = _center.x;
        }
        //垂直
        else if(_type == HORIZONTALLY) {
            _targetValue = _center.y;
        }
        //------------------------------------------
        
        _enabled = true;
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    flJoyStick1::~flJoyStick1() {
        //ofLog() << "[flJoyStick1D]~flJoyStick1D()";
        
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
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flJoyStick1::_setup() {
        //ofLog() << "[flJoyStick1]_setup()";
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_update() {
        //ofLog() << "[flJoyStick1]_update()";

        float preValue = _value;

        if(lever->isMouseDown()) {
            //------------------------------------------
            //水平
            if(_type == VERTICALLY) {
                //------------------------------------------
                float tx = mouseX() - _draggablePoint.x;
                float shiftX = tx - _center.x;
                
                float distance = _center.distance(ofPoint(tx, _center.y));
                if(_maxDistance < distance) {
                    float n = _maxDistance / distance;
                    tx = _center.x + (shiftX * n);
                }
                lever->x(tx);
                
                //------------------------------------------
                //Update value.
                _value = (lever->x() - _center.x) / (_uiLength * 0.5 - _leverRadius);
                //------------------------------------------
            }
            //垂直
            else if(_type == HORIZONTALLY) {
                //------------------------------------------
                float ty = mouseY() - _draggablePoint.y;
                float shiftY = ty - _center.y;
                
                float distance = _center.distance(ofPoint(_center.x, ty));
                if(_maxDistance < distance){
                    float n = _maxDistance / distance;
                    ty = _center.y + (shiftY * n);
                }
                lever->y(ty);
                
                //------------------------------------------
                //Update value.
                _value = -1 * (lever->y() - _center.y) / (_uiLength * 0.5 - _leverRadius);
                //------------------------------------------
            }
            //------------------------------------------
            
            //------------------------------------------
            if(preValue != _value) {
                _valueText->text(ofToString(_value, 2));
                
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
                }
                //垂直
                else if(_type == HORIZONTALLY) {
                    if(_value > 0) {
                        event = new flJoyStick1Event(flJoyStick1Event::UP);
                        event->__value = _value;
                        dispatchEvent(event);
                    }
                    if(_value <= 0) {
                        event = new flJoyStick1Event(flJoyStick1Event::DOWN);
                        event->__value = _value;
                        dispatchEvent(event);
                    }
                }
                //------------------------------------------
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
                if(_maxDistance < distance){
                    float n = _maxDistance / distance;
                    tx = _center.x + (shiftX * n);
                }
                lever->x(tx);
                
                //------------------------------------------
                //Update value.
                _value = (lever->x() - _center.x) / (_uiLength * 0.5 - _leverRadius);
                //------------------------------------------
            }
            //垂直
            else if(_type == HORIZONTALLY) {
                float ty = _targetValue;
                if(!_flg) ty = lever->y() + (_center.y - lever->y()) * 0.4f;
                float shiftY = ty - _center.y;
                
                float distance = _center.distance(ofPoint(_center.x, ty));
                if(_maxDistance < distance){
                    float n = _maxDistance / distance;
                    ty = _center.y + (shiftY * n);
                }
                lever->y(ty);
                
                //------------------------------------------
                //Update value.
                _value = -1 * (lever->y() - _center.y) / (_uiLength * 0.5 - _leverRadius);
                //------------------------------------------
            }
            //------------------------------------------
            
            //------------------------------------------
            if(preValue != _value) {
                _valueText->text(ofToString(_value, 2));
                
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
                }
                //垂直
                else if(_type == HORIZONTALLY) {
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
            }
            //------------------------------------------
        } else {
            //Easing
            //------------------------------------------
            //水平
            if(_type == VERTICALLY) {
                float distanceX = _center.x - lever->x();
                if(-0.5f < distanceX && distanceX < 0.5f) {
                    lever->x(_center.x);
                    _value = 0.0;
                } else {
                    lever->x(lever->x() + (_center.x - lever->x()) * 0.4f);
                    
                    //------------------------------------------
                    //Update value.
                    _value = (lever->x() - _center.x) / (_uiLength * 0.5 - _leverRadius);
                    //------------------------------------------
                }
                
            }
            //垂直
            else if(_type == HORIZONTALLY) {
                float distanceY = _center.y - lever->y();
                if(-0.5f < distanceY && distanceY < 0.5f) {
                    lever->y(_center.y);
                    _value = 0.0;
                } else {
                    lever->y(lever->y() + (_center.y - lever->y()) * 0.4f);
                    
                    //------------------------------------------
                    //Update value.
                    _value = -1 * (lever->y() - _center.y) / (_uiLength * 0.5 - _leverRadius);
                    //------------------------------------------
                }
            }
            //------------------------------------------
            
            //------------------------------------------
            if(preValue != _value) {
                _valueText->text(ofToString(_value, 2));
                
                //------------------------------------------
                flJoyStick1Event* event = new flJoyStick1Event(flJoyStick1Event::CHANGE);
                event->__value = _value;
                dispatchEvent(event);
                //------------------------------------------
            }
            //------------------------------------------
        }
        
        _flg = false;
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_draw() {
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flJoyStick1::label() { return _label; }
    void flJoyStick1::label(flTextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    string flJoyStick1::type() { return _type; }
    void flJoyStick1::type(string value) {
        _type = value;
        
        //水平
        if(_type == VERTICALLY) {
            _center = ofPoint(_uiLength * 0.5, _leverRadius);
            
            _valueText->x(2);
            _valueText->y(0);
            _valueText->rotation(0);
        }
        //垂直
        else if(_type == HORIZONTALLY) {
            _center = ofPoint(_leverRadius, _uiLength * 0.5);
            
            _valueText->x(_valueText->textHeight() - 0);
            _valueText->y(2);
            _valueText->rotation(90);
        }
        
        lever->x(_center.x);
        lever->y(_center.y);
        
        if(lever->isMouseOver()) {
            _leverOver();
        } else {
            _leverOut();
        }
    }
    
    //--------------------------------------------------------------
    float flJoyStick1::value() { return _value; }
    
    //--------------------------------------------------------------
    void flJoyStick1::moveLever(float value) {
        //cout << "[flJoyStick1D]moveLever()" << endl;
        if(_type == VERTICALLY) {
            _targetValue = lever->x() - _maxDistance * value;
        } else
            if(_type == HORIZONTALLY) {
                _targetValue = lever->y() - _maxDistance * value;
            }
        
        _flg = true;
    }
    
    //--------------------------------------------------------------
    bool flJoyStick1::enabled() { return _enabled; }
    void flJoyStick1::enabled(bool value) {
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
    void flJoyStick1::_leverOver() {
        if(lever->isMouseDown()) return;
        
        _setOverColor();
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_leverOut() {
        if(lever->isMouseDown()) return;
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_leverPress() {
        _setActiveColor();
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_leverRelease() {
        
        if(lever->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }

    //--------------------------------------------------------------
    void flJoyStick1::_leverMove() {
        
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_ACTIVE_COLOR);
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR);
        _drawLeverGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR);
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_setSelectedOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _valueText->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_setDisableNormalColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_setDisableActiveColor() {
        //        _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_drawAreaGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = graphics();
        g->clear();
        g->lineStyle(1, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        //水平
        if(_type == VERTICALLY) g->drawRoundRect(0, 0, _uiLength, _leverRadius * 2, _leverRadius);
        //垂直
        else if(_type == HORIZONTALLY) g->drawRoundRect(0, 0, _leverRadius * 2, _uiLength, _leverRadius);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_drawLeverGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
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
    void flJoyStick1::_mouseEventHandler(flEvent& event) {
        //ofLog() << "[flJoyStick1D]_mouseEventHandler(" << event.type();
        
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
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flJoyStick1::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            _draggablePoint.x = 0;
            _draggablePoint.y = 0;
            _leverRelease();
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flJoyStick1::_mouseEventHandler);
            }
        }
        
        //Mouse Move
        if(event.type() == flMouseEvent::MOUSE_MOVE) {
            if(event.target() == lever) _leverMove();
        }
        
        //Dragging
        if(event.type() == flMouseEvent::DRAGGING) {
            if(event.target() == lever){
                
            }
        }    
    }
    
}
