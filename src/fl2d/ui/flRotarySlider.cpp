#include "flRotarySlider.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================

    //--------------------------------------------------------------
    flRotarySlider::flRotarySlider(float areaDiameter, float leverDiameter) {
        //ofLog() << "[flRotarySlider]flRotarySlider()";
        
        _target = this;
        name("flRotarySlider");
        
        _xValue = 0.0;
        _yValue = 0.0;
        
        _areaRadius = areaDiameter * 0.5;
        _leverRadius = leverDiameter * 0.5;
        
        _center = new ofPoint(_areaRadius, _areaRadius);
        
        flGraphics* g;
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
        g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        addEventListener(flMouseEvent::ROLL_OVER, this, &flRotarySlider::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flRotarySlider::_mouseEventHandler);
        //------------------------------------------
        //------------------------------------------
        lever = new flSprite();
        g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
        g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex());
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        lever->x(_center->x);
        lever->y(_center->y);
        lever->useHandCursor(true);
        lever->addEventListener(flMouseEvent::ROLL_OVER, this, &flRotarySlider::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::ROLL_OUT, this, &flRotarySlider::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRotarySlider::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_MOVE, this, &flRotarySlider::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::DRAGGING, this, &flRotarySlider::_mouseEventHandler);
        addChild(lever);
        
        _draggablePoint = new ofPoint(0, 0);
        //------------------------------------------
        
        //------------------------------------------
        _flgX = false;
        _flgY = false;
        _targetX = _center->x;
        _targetY = _center->y;
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    flRotarySlider::~flRotarySlider() {
        //ofLog() << "[flRotarySlider]~flRotarySlider()";
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flRotarySlider::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flRotarySlider::_mouseEventHandler);
        
        lever->removeEventListener(flMouseEvent::ROLL_OVER, this, &flRotarySlider::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::ROLL_OUT, this, &flRotarySlider::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRotarySlider::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_MOVE, this, &flRotarySlider::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::DRAGGING, this, &flRotarySlider::_mouseEventHandler);
        
        _xValue = 0.0;
        _yValue = 0.0;
        
        _areaRadius = 0.0;
        _leverRadius = 0.0;
        
        delete _center;
        _center = NULL;
        
        delete lever;
        lever = NULL;
        
        delete _draggablePoint;
        _draggablePoint = NULL;
        
        _flgX = false;
        _flgY = false;
        _targetX = 0.0;
        _targetY = 0.0;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================

    //--------------------------------------------------------------
    void flRotarySlider::_setup() {
        //ofLog() << "[SimpleSlider]setup()";
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_update() {
        //ofLog() << "isMouseDown" << lever->isMouseDown();
        
        flUIBase::_update();

        if(lever->isMouseDown()) {
            //------------------------------------------
            float shiftX; float shiftY;
            float tx; float ty;
            
            tx = mouseX() - _draggablePoint->x;
            ty = mouseY() - _draggablePoint->y;
            
            shiftX = tx - _center->x;
            shiftY = ty - _center->y;
            
            float distance = _center->distance(ofPoint(tx, ty));
            if((_areaRadius - _leverRadius - 2) < distance){
                float n = (_areaRadius - _leverRadius - 2) / distance;
                tx = _center->x + (shiftX * n);
                ty = _center->y + (shiftY * n);
            }
            
            lever->x(tx);
            lever->y(ty);
            //------------------------------------------
            //------------------------------------------
            _xValue = (lever->x() - _center->x) / (_areaRadius - _leverRadius);
            _yValue = -1 * (lever->y() - _center->y) / (_areaRadius - _leverRadius);
            
            flRotarySliderEvent* event;
            
            event = new flRotarySliderEvent(flRotarySliderEvent::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            
            if(_xValue > 0) {
                event = new flRotarySliderEvent(flRotarySliderEvent::RIGHT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_xValue < 0) {
                event = new flRotarySliderEvent(flRotarySliderEvent::LEFT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_yValue > 0) {
                event = new flRotarySliderEvent(flRotarySliderEvent::UP);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_yValue < 0) {
                event = new flRotarySliderEvent(flRotarySliderEvent::DOWN);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            //------------------------------------------
            
        } else if(_flgX || _flgY) {
            //------------------------------------------
            float shiftX; float shiftY;
            float tx; float ty;
            
            tx = _targetX;
            ty = _targetY;
            if(!_flgX) tx = lever->x() + (_center->x - lever->x()) * 0.4f;
            if(!_flgY) ty = lever->y() + (_center->y - lever->y()) * 0.4f;
            
            shiftX = tx - _center->x;
            shiftY = ty - _center->y;
            
            float distance = _center->distance(ofPoint(tx, ty));
            if((_areaRadius - _leverRadius - 2) < distance){
                float n = (_areaRadius - _leverRadius - 2) / distance;
                tx = _center->x + (shiftX * n);
                ty = _center->y + (shiftY * n);
            }
            
            lever->x(tx);
            lever->y(ty);
            //------------------------------------------
            //------------------------------------------
            _xValue = (lever->x() - _center->x) / (_areaRadius - _leverRadius);
            _yValue = -1 * (lever->y() - _center->y) / (_areaRadius - _leverRadius);
            
            flRotarySliderEvent* event;
            
            event = new flRotarySliderEvent(flRotarySliderEvent::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            
            if(_flgX && _xValue > 0) {
                event = new flRotarySliderEvent(flRotarySliderEvent::RIGHT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgX && _xValue < 0) {
                event = new flRotarySliderEvent(flRotarySliderEvent::LEFT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgY && _yValue > 0) {
                event = new flRotarySliderEvent(flRotarySliderEvent::UP);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgY && _yValue < 0) {
                event = new flRotarySliderEvent(flRotarySliderEvent::DOWN);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            //------------------------------------------
            
        } else {
            //------------------------------------------
            float distanceX = _center->x - lever->x();
            float distanceY = _center->y - lever->y();
            if(-0.5f < distanceX && distanceX < 0.5f &&
               -0.5f < distanceY && distanceY < 0.5f) {
                lever->x(_center->x);
                lever->y(_center->y);
            } else {
                lever->x(lever->x() + (_center->x - lever->x()) * 0.4f);
                lever->y(lever->y() + (_center->y - lever->y()) * 0.4f);
                
                _xValue = (lever->x() - _center->x) / (_areaRadius - _leverRadius);
                _yValue = -1 * (lever->y() - _center->y) / (_areaRadius - _leverRadius);
                
                flRotarySliderEvent* event = new flRotarySliderEvent(flRotarySliderEvent::CHANGE);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            //------------------------------------------
        }
        
        _flgX = false;
        _flgY = false;
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_draw() {
        
        
        ofPushStyle();
        ofSetColor(0);
        ofDrawLine(_center->x, _center->y, lever->x(), lever->y());
        ofPopStyle();
        
        ofPushStyle();
        ofTranslate(*_center);
        float angle = flmath::getDeg(lever->x() - _center->x, lever->y() - _center->y);
        ofDrawBitmapString(ofToString(angle), 0, 0);
        ofTranslate(-*_center);
        ofPopStyle();
    }
    
    //==============================================================
    // Public Method
    //==============================================================

    //--------------------------------------------------------------
    void flRotarySlider::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    float flRotarySlider::xValue() { return _xValue; }
    //--------------------------------------------------------------
    float flRotarySlider::yValue() { return _yValue; }
    
    //--------------------------------------------------------------
    void flRotarySlider::leverUp(float value) {
        //ofLog() << "[flRotarySlider]leverUp()";
        _targetY = lever->y() - (_areaRadius - _leverRadius - 2) * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    void flRotarySlider::leverDown(float value) {
        //ofLog() << "[flRotarySlider]leverDown()";
        _targetY = lever->y() + (_areaRadius - _leverRadius - 2) * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    void flRotarySlider::leverLeft(float value) {
        //ofLog() << "[flRotarySlider]leverLeft()";
        _targetX = lever->x() - (_areaRadius - _leverRadius - 2) * value;
        _flgX = true;
    }
    //--------------------------------------------------------------
    void flRotarySlider::leverRight(float value) {
        //ofLog() << "[flRotarySlider]leverRight()";
        _targetX = lever->x() + (_areaRadius - _leverRadius - 2) * value;
        _flgX = true;
    }
    
    //--------------------------------------------------------------
    bool flRotarySlider::enabled() { return _enabled; }
    void flRotarySlider::enabled(bool value) {
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
            g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        } else {
            g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        }
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        //------------------------------------------
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        if(_enabled) {
            g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        } else {
            g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
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
    void flRotarySlider::_areaOver() {
        //if(lever->isMouseDown()) return;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_BORDER_OVER_COLOR.getHex());
        g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_areaOut() {
        //if(lever->isMouseDown()) return;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
        g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_areaPress() {
        
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_areaRelease() {
        
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_ballOver() {
        if(lever->isMouseDown()) return;
        
        _areaOver();
        
        flGraphics* g;
        g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
        g->beginFill(flDefinition::UI_OVER_COLOR.getHex());
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_ballOut() {
        if(lever->isMouseDown()) return;
        
        _areaOut();
        
        flGraphics* g;
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
        g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex());
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_ballPress() {
        _draggablePoint->x = mouseX() - lever->x();
        _draggablePoint->y = mouseY() - lever->y();
        //ofLog() << _draggablePoint->x << " " << _draggablePoint->y;
        flGraphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, flDefinition::UI_BORDER_ACTIVE_COLOR.getHex());
        g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        //------------------------------------------
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
        g->beginFill(flDefinition::UI_ACTIVE_COLOR.getHex());
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_ballRelease() {
        _draggablePoint->x = 0;
        _draggablePoint->y = 0;
        
        flGraphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        if(isMouseOver()) {
            g->lineStyle(1, flDefinition::UI_BORDER_OVER_COLOR.getHex());
        } else {
            g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
        }
        g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        //------------------------------------------
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        g->beginFill(0xff0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, flDefinition::UI_BORDER_NORMAL_COLOR.getHex());
        if(lever->isMouseOver()) {
            g->beginFill(flDefinition::UI_OVER_COLOR.getHex());
        } else {
            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex());
        }
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flRotarySlider::_ballMove() {
        
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================

    //--------------------------------------------------------------
    void flRotarySlider::_mouseEventHandler(flEvent& event) {
        //ofLog() << "[flRotarySlider]_mouseEventHandler(" << event.type();
        
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
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRotarySlider::_mouseEventHandler);
            }
        }
        
        if(event.type() == flMouseEvent::MOUSE_UP) {
            //if(event.target() == this) _areaRelease();
            if(event.currentTarget() == stage()){
                _ballRelease();
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flRotarySlider::_mouseEventHandler);
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
