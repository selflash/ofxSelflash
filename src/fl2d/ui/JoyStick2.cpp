#include "Joystick2.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    Joystick2::Joystick2(float areaDiameter, float leverDiameter) {
        //cout << "[Joystick2]Joystick2()" << endl;
        
        _target = this;
        name("Joystick2");
        
        _xValue = 0.0;
        _yValue = 0.0;
        
        _areaRadius = areaDiameter * 0.5;
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
        
        _center = new ofPoint(_areaRadius, _areaRadius);
        
        Graphics* g;
        //------------------------------------------
        g = graphics();
        g->enabledSmoothing(true);
        g->clear();
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        addEventListener(MouseEvent::ROLL_OVER, this, &Joystick2::_mouseEventHandler);
        addEventListener(MouseEvent::ROLL_OUT, this, &Joystick2::_mouseEventHandler);
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
        lever->x(_center->x);
        lever->y(_center->y);
        lever->useHandCursor(true);
        lever->addEventListener(MouseEvent::ROLL_OVER, this, &Joystick2::_mouseEventHandler);
        lever->addEventListener(MouseEvent::ROLL_OUT, this, &Joystick2::_mouseEventHandler);
        lever->addEventListener(MouseEvent::MOUSE_DOWN, this, &Joystick2::_mouseEventHandler);
        lever->addEventListener(MouseEvent::MOUSE_MOVE, this, &Joystick2::_mouseEventHandler);
        lever->addEventListener(MouseEvent::DRAGGING, this, &Joystick2::_mouseEventHandler);
        addChild(lever);
        
        _draggablePoint = new ofPoint(0, 0);
        //------------------------------------------
        
        //------------------------------------------
        _flgX = false;
        _flgY = false;
        _targetX = _center->x;
        _targetY = _center->y;
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _label = NULL;
        //------------------------------------------
        
        _enabled = true;
    }
    
    //--------------------------------------------------------------
    //
    Joystick2::~Joystick2() {
        //cout << "[Joystick2]~Joystick2()" << endl;
        
        removeEventListener(MouseEvent::ROLL_OVER, this, &Joystick2::_mouseEventHandler);
        removeEventListener(MouseEvent::ROLL_OUT, this, &Joystick2::_mouseEventHandler);
        
        lever->removeEventListener(MouseEvent::ROLL_OVER, this, &Joystick2::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::ROLL_OUT, this, &Joystick2::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::MOUSE_DOWN, this, &Joystick2::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::MOUSE_MOVE, this, &Joystick2::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::DRAGGING, this, &Joystick2::_mouseEventHandler);
        
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
        
        _label = NULL;
        
        _enabled = false;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Joystick2::_setup() {
        //cout << "[SimpleSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    //
    void Joystick2::_update() {
        //cout << "isMouseDown" << lever->isMouseDown() << endl;
        
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
            
            Joystick2Event* event;
            
            event = new Joystick2Event(Joystick2Event::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            
            if(_xValue > 0) {
                event = new Joystick2Event(Joystick2Event::RIGHT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_xValue < 0) {
                event = new Joystick2Event(Joystick2Event::LEFT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_yValue > 0) {
                event = new Joystick2Event(Joystick2Event::UP);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_yValue < 0) {
                event = new Joystick2Event(Joystick2Event::DOWN);
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
            
            Joystick2Event* event;
            
            event = new Joystick2Event(Joystick2Event::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            
            if(_flgX && _xValue > 0) {
                event = new Joystick2Event(Joystick2Event::RIGHT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgX && _xValue < 0) {
                event = new Joystick2Event(Joystick2Event::LEFT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgY && _yValue > 0) {
                event = new Joystick2Event(Joystick2Event::UP);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgY && _yValue < 0) {
                event = new Joystick2Event(Joystick2Event::DOWN);
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
                
                Joystick2Event* event = new Joystick2Event(Joystick2Event::CHANGE);
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
    //
    void Joystick2::_draw() {
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    TextField* Joystick2::label() { return _label; }
    void Joystick2::label(TextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    float Joystick2::xValue() { return _xValue; }
    //--------------------------------------------------------------
    //
    float Joystick2::yValue() { return _yValue; }
    
    //--------------------------------------------------------------
    //
    void Joystick2::leverUp(float value) {
        //cout << "[Joystick2]leverUp()" << endl;
        _targetY = lever->y() - (_areaRadius - _leverRadius - 2) * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    //
    void Joystick2::leverDown(float value) {
        //cout << "[Joystick2]leverDown()" << endl;
        _targetY = lever->y() + (_areaRadius - _leverRadius - 2) * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    //
    void Joystick2::leverLeft(float value) {
        //cout << "[Joystick2]leverLeft()" << endl;
        _targetX = lever->x() - (_areaRadius - _leverRadius - 2) * value;
        _flgX = true;
    }
    //--------------------------------------------------------------
    //
    void Joystick2::leverRight(float value) {
        //cout << "[Joystick2]leverRight()" << endl;
        _targetX = lever->x() + (_areaRadius - _leverRadius - 2) * value;
        _flgX = true;
    }
    
    //--------------------------------------------------------------
    //
    bool Joystick2::enabled() { return _enabled; }
    void Joystick2::enabled(bool value) {
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
        g->drawCircle(_center->x, _center->y, _areaRadius);
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
    void Joystick2::_areaOver() {
        //if(lever->isMouseDown()) return;
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _overLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void Joystick2::_areaOut() {
        //if(lever->isMouseDown()) return;
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void Joystick2::_areaPress() {
        
    }
    //--------------------------------------------------------------
    //
    void Joystick2::_areaRelease() {
        
    }
    
    //--------------------------------------------------------------
    //
    void Joystick2::_ballOver() {
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
    void Joystick2::_ballOut() {
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
    void Joystick2::_ballPress() {
        _draggablePoint->x = mouseX() - lever->x();
        _draggablePoint->y = mouseY() - lever->y();
        //cout << _draggablePoint->x << " " << _draggablePoint->y << endl;
        Graphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _activeLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
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
    void Joystick2::_ballRelease() {
        _draggablePoint->x = 0;
        _draggablePoint->y = 0;
        
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
        g->drawCircle(_center->x, _center->y, _areaRadius);
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
    void Joystick2::_ballMove() {
        
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Joystick2::_mouseEventHandler(Event& event) {
        //cout << "[Joystick2]_mouseEventHandler(" << event.type() << endl;
        
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
                stage()->addEventListener(MouseEvent::MOUSE_UP, this, &Joystick2::_mouseEventHandler);
            }
        }
        
        if(event.type() == MouseEvent::MOUSE_UP) {
            //if(event.target() == this) _areaRelease();
            if(event.currentTarget() == stage()){
                _ballRelease();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, this, &Joystick2::_mouseEventHandler);
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