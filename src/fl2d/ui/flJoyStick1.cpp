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
    flJoyStick1::flJoyStick1(float length) {
        //ofLog() << "[flJoyStick1]flJoyStick1()";

        _target = this;
        name("flJoyStick1");
        
        _leverRadius = 14 * 0.5;

        _uiLength = length;
        _maxDistance = (_uiLength * 0.5 - _leverRadius) - 2;

        //水平
        if(_type == HORIZONTALLY) {
            _uiWidth = _uiLength;
            _uiHeight = 18;

            _center = ofPoint(_uiWidth * 0.5, _leverRadius + (18 * 0.5 - _leverRadius));
            _targetValue = _center.x;
            
        }
        //垂直
        else if(_type == VERTICALLY) {
            _uiWidth = 18;
            _uiHeight = _uiLength;

            _center = ofPoint(_leverRadius + (18 * 0.5 - _leverRadius), _uiWidth * 0.5);
            _targetValue = _center.y;
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
//        lever->addEventListener(flMouseEvent::MOUSE_MOVE, this, &flJoyStick1::_mouseEventHandler);
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
        _valueText->text(ofToString(_value, _digit));
        _valueText->mouseEnabled(false);
        addChild(_valueText);
        //------------------------------------------
        
        _setNormalColor();
    }
    
    //--------------------------------------------------------------
    flJoyStick1::~flJoyStick1() {
        //ofLog() << "[flJoyStick1D]~flJoyStick1D()";
        
        lever->removeEventListener(flMouseEvent::ROLL_OVER, this, &flJoyStick1::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::ROLL_OUT, this, &flJoyStick1::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flJoyStick1::_mouseEventHandler);
//        lever->removeEventListener(flMouseEvent::MOUSE_MOVE, this, &flJoyStick1::_mouseEventHandler);
//        lever->removeEventListener(flMouseEvent::DRAGGING, this, &flJoyStick1::_mouseEventHandler);
        delete lever;
        lever = NULL;
        
        delete _valueText;
        _valueText = NULL;
        
        _floatParam = NULL;
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

        if(lever->isMouseDown()) {
            if(_type == HORIZONTALLY) {
                _targetValue = mouseX() - _draggablePoint.x;
            }
            else if(_type == VERTICALLY) {
                _targetValue = mouseY() - _draggablePoint.y;
            }
            _leverPress();
        } else {
            if(_type == HORIZONTALLY) {
                //------------------------------------------
                //Easing
                float dx = _targetValue - lever->x();
                if(dx < -0.5 || 0.5 < dx) {
                    _targetValue = lever->x() + dx * 0.4;
                }
                //------------------------------------------
                
                //------------------------------------------
                float tx = _targetValue;
                float ty = _center.y;

                //------------------------------------------
                //範囲内に収める
                float distance = _center.distance(ofPoint(tx, ty));
                if(_maxDistance < distance){
                    float d = tx - _center.x;
                    float ratio = _maxDistance / distance;
                    tx = _center.x + (d * ratio);
                }
                //------------------------------------------
                
                lever->x(tx);
                
                //------------------------------------------
                //Update value.
//                _value = (lever->x() - _center.x) / (_uiLength * 0.5 - _leverRadius);
                _value = (lever->x() - _center.x) / _maxDistance;
                //------------------------------------------
            }
            else if(_type == VERTICALLY) {
                //------------------------------------------
                //Easing
                float dy = _targetValue - lever->y();
                if(dy < -0.5 || 0.5 < dy) {
                    _targetValue = lever->y() + dy * 0.4;
                }
                //------------------------------------------
                
                //------------------------------------------
                float tx = _center.x;
                float ty = _targetValue;
                
                //------------------------------------------
                //範囲内に収める
                float distance = _center.distance(ofPoint(tx, ty));
                if(_maxDistance < distance){
                    float d = ty - _center.y;
                    float ratio = _maxDistance / distance;
                    ty = _center.y + (d * ratio);
                }
                //------------------------------------------
                
                lever->y(ty);
                
                //------------------------------------------
                //Update value.
//                _value = (lever->y() - _center.y) / (_uiLength * 0.5 - _leverRadius);
                _value = -1 * (lever->y() - _center.y) / _maxDistance;
                if(_value == -0) _value = 0;
                //------------------------------------------
            }
            
            //------------------------------------------
            if (_enabled) {
                if(lever->isMouseOver()) {
                    _setOverColor();
                } else {
                    _setNormalColor();
                }
            } else {
                _setDisableNormalColor();
            }
            //------------------------------------------
            
            //------------------------------------------
            _changeValue(_flg);
            
            if(!_bChangedByOfParm["value"]) {
                if(_floatParam != NULL) {
                    _bChangedByMyself["value"] = true;
                    _floatParam->set(_value);
                }
            }
            //------------------------------------------
        }

        _flg = false;
        if(_type == HORIZONTALLY) {
            _targetValue = _center.x;
        }
        else if(_type == VERTICALLY) {
            _targetValue = _center.y;
        }
        _value = 0.0f;
        _bChangedByOfParm["value"] = false;
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_draw() {
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flJoyStick1::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        if(_enabled) {
            _setNormalColor();
        } else {
            _setDisableNormalColor();
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    string flJoyStick1::type() { return _type; }
    void flJoyStick1::type(string value) {
        if(_type == value) return;
        
        string currentType = _type;
        _type = value;
        
//        //水平
//        if(_type == HORIZONTALLY) {
//            _center = ofPoint(_uiLength * 0.5, _leverRadius + 1);
//
//        }
//        //垂直
//        else if(_type == VERTICALLY) {
//            _center = ofPoint(_leverRadius + 1, _uiLength * 0.5);
//
//        }
        
        
        float currentWidth = _uiWidth;
        float currentHeight = _uiHeight;
        ofPoint currentCenter = _center;

        _uiWidth = currentHeight;
        _uiHeight = currentWidth;

        _center.x = currentCenter.y;
        _center.y = currentCenter.x;

        //水平
        if(_type == HORIZONTALLY) {
            _targetValue = _center.x;
            
            _valueText->x(2);
            _valueText->y(0);
            _valueText->rotation(0);
        }
        //垂直
        else if(_type == VERTICALLY) {
            _targetValue = _center.y;
            
            _valueText->x(_valueText->textHeight() - 0);
            _valueText->y(2);
            _valueText->rotation(90);
        }
        
        lever->x(_center.x);
        lever->y(_center.y);
        
        if(lever->isMouseDown()) {
            _setActiveColor();
        }
        else if(lever->isMouseOver()) {
            _setOverColor();
        } else {
            _setNormalColor();
        }
    }
    
    //--------------------------------------------------------------
    float flJoyStick1::value() { return _value; }
    
    //--------------------------------------------------------------
    void flJoyStick1::moveLever(float value) {
//        ofLog() << "[flJoyStick1]moveLever(" << value << ")";
        
        //水平
        if(_type == HORIZONTALLY) {
//            _targetValue = lever->x() - _maxDistance * value;
//            _targetValue = _center.x - _maxDistance * value;
            _targetValue = _center.x - (_maxDistance * value);
        }
        //垂直
        else if(_type == VERTICALLY) {
//            _targetValue = lever->y() - _maxDistance * value;
//            _targetValue = _center.y - _maxDistance * value;
            _targetValue = _center.y - (_maxDistance * value);
        }
        
        _flg = true;
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flJoyStick1::_changeValue(bool dispatch) {
        _valueText->text(ofToString(_value, _digit));
        
        //------------------------------------------
        if(dispatch) {
            flJoyStick1Event* event;
            event = new flJoyStick1Event(flJoyStick1Event::CHANGE);
            event->__value = _value;
            dispatchEvent(event);
            
            //水平
            if(_type == HORIZONTALLY) {
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
            else if(_type == VERTICALLY) {
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
        }
        //------------------------------------------
    }
    
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
        //------------------------------------------
        float tx = _targetValue;
        float ty = _targetValue;

        //------------------------------------------
        //水平
        if(_type == HORIZONTALLY) {
            //------------------------------------------
            tx = mouseX() - _draggablePoint.x;
            ty = _center.y;
            
            //------------------------------------------
            //範囲内に収める
            float distance = _center.distance(ofPoint(tx, ty));
            if(_maxDistance < distance) {
                float shiftX = tx - _center.x;
                float n = _maxDistance / distance;
                tx = _center.x + (shiftX * n);
            }
            //------------------------------------------
            
            lever->x(tx);
            
            //------------------------------------------
            //Update value.
//            _value = (lever->x() - _center.x) / (_uiLength * 0.5 - _leverRadius);
            _value = (lever->x() - _center.x) / _maxDistance;
            //------------------------------------------
        }
        //垂直
        else if(_type == VERTICALLY) {
            //------------------------------------------
            tx = _center.x;
            ty = mouseY() - _draggablePoint.y;
            
            //------------------------------------------
            //範囲内に収める
            float distance = _center.distance(ofPoint(tx, ty));
            if(_maxDistance < distance){
                float shiftY = ty - _center.y;
                float n = _maxDistance / distance;
                ty = _center.y + (shiftY * n);
            }
            //------------------------------------------
            
            lever->y(ty);
            
            //------------------------------------------
            //Update value.
//            _value = -1 * (lever->y() - _center.y) / (_uiLength * 0.5 - _leverRadius);
            _value = -1 * (lever->y() - _center.y) / _maxDistance;
            if(_value == -0) _value = 0;
            //------------------------------------------
        }
        //------------------------------------------
        
        //------------------------------------------
        _setActiveColor();
        //------------------------------------------

        //------------------------------------------
        _changeValue(true);
        
        if(_floatParam != NULL) {
            _bChangedByMyself["value"] = true;
            _floatParam->set(_value);
        }
        //------------------------------------------
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
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_setDisableActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        _valueText->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
        _drawAreaGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
        _drawLeverGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR, 1);
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_drawAreaGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        g->drawRoundRect(0, 0, _uiWidth, _uiHeight, _leverRadius + 2);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flJoyStick1::_drawLeverGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(thickness, lineColor.getHex());
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
                if(_type == HORIZONTALLY) {
                    _targetValue = mouseX() - _draggablePoint.x;
                }
                else if(_type == VERTICALLY) {
                    _targetValue = mouseY() - _draggablePoint.y;
                }
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
        
//        //Mouse Move
//        if(event.type() == flMouseEvent::MOUSE_MOVE) {
//            if(event.target() == lever) _leverMove();
//        }
//
//        //Dragging
//        if(event.type() == flMouseEvent::DRAGGING) {
//            if(event.target() == lever){
//
//            }
//        }
    }
    
}
