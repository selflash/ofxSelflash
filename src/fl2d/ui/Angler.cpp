#include "Angler.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    Angler::Angler(float areaDiameter, float leverDiameter) {
        //cout << "[Angler]Angler()" << endl;
        
        _target = this;
        name("Angler");
        
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
        g->smoothing(true);
        g->clear();
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        addEventListener(MouseEvent::ROLL_OVER, this, &Angler::_mouseEventHandler);
        addEventListener(MouseEvent::ROLL_OUT, this, &Angler::_mouseEventHandler);
        //------------------------------------------
        //------------------------------------------
        lever = new Sprite();
        g = lever->graphics();
        g->smoothing(true);
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
        lever->addEventListener(MouseEvent::ROLL_OVER, this, &Angler::_mouseEventHandler);
        lever->addEventListener(MouseEvent::ROLL_OUT, this, &Angler::_mouseEventHandler);
        lever->addEventListener(MouseEvent::MOUSE_DOWN, this, &Angler::_mouseEventHandler);
        lever->addEventListener(MouseEvent::MOUSE_MOVE, this, &Angler::_mouseEventHandler);
        lever->addEventListener(MouseEvent::DRAGGING, this, &Angler::_mouseEventHandler);
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
    Angler::~Angler() {
        //cout << "[Angler]~Angler()" << endl;
        
        removeEventListener(MouseEvent::ROLL_OVER, this, &Angler::_mouseEventHandler);
        removeEventListener(MouseEvent::ROLL_OUT, this, &Angler::_mouseEventHandler);
        
        lever->removeEventListener(MouseEvent::ROLL_OVER, this, &Angler::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::ROLL_OUT, this, &Angler::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::MOUSE_DOWN, this, &Angler::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::MOUSE_MOVE, this, &Angler::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::DRAGGING, this, &Angler::_mouseEventHandler);
        
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
    void Angler::_setup() {
        //cout << "[SimpleSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    //
    void Angler::_update() {
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
            
            AnglerEvent* event;
            
            event = new AnglerEvent(AnglerEvent::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            
            if(_xValue > 0) {
                event = new AnglerEvent(AnglerEvent::RIGHT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_xValue < 0) {
                event = new AnglerEvent(AnglerEvent::LEFT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_yValue > 0) {
                event = new AnglerEvent(AnglerEvent::UP);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_yValue < 0) {
                event = new AnglerEvent(AnglerEvent::DOWN);
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
            
            AnglerEvent* event;
            
            event = new AnglerEvent(AnglerEvent::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            
            if(_flgX && _xValue > 0) {
                event = new AnglerEvent(AnglerEvent::RIGHT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgX && _xValue < 0) {
                event = new AnglerEvent(AnglerEvent::LEFT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgY && _yValue > 0) {
                event = new AnglerEvent(AnglerEvent::UP);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgY && _yValue < 0) {
                event = new AnglerEvent(AnglerEvent::DOWN);
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
                
                AnglerEvent* event = new AnglerEvent(AnglerEvent::CHANGE);
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
    void Angler::_draw() {
        float distance = _center->distance(ofVec2f(lever->x(), lever->y()));
        
        if(lever->isMouseDown()) {
            ofPushStyle();
            ofSetHexColor(_labelActiveColor);
            ofDrawLine(_center->x, _center->y, lever->x(), lever->y());
            ofPopStyle();
            
            if(distance >= _areaRadius - _leverRadius - 2) {
                if(!_flg) {
                    _flg = true;
                    _zeroAngle = MathUtil::getAngle(lever->x() - _center->x, lever->y() - _center->y);
                }
            }
            
            if(_flg) {
                //------------------------------------------
                ofPushStyle();
                ofTranslate(*_center);
                float angle = MathUtil::getAngle(lever->x() - _center->x, lever->y() - _center->y);
                
                angle = angle - _zeroAngle;
                if(angle > 180.0) { angle -= 360.0; }
                if(angle < -180.0) { angle += 360.0; }
                
                ofDrawBitmapString(ofToString(angle), -30, 15);
                ofTranslate(-*_center);
                ofPopStyle();
                //------------------------------------------
            }
        } else {
            if(distance == 0.0) {
                _flg = false;
                _zeroAngle = 0.0;
            }
        }
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    TextField* Angler::label() { return _label; }
    void Angler::label(TextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    float Angler::xValue() { return _xValue; }
    //--------------------------------------------------------------
    //
    float Angler::yValue() { return _yValue; }
    
    //--------------------------------------------------------------
    //
    void Angler::leverUp(float value) {
        //cout << "[Angler]leverUp()" << endl;
        _targetY = lever->y() - (_areaRadius - _leverRadius - 2) * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    //
    void Angler::leverDown(float value) {
        //cout << "[Angler]leverDown()" << endl;
        _targetY = lever->y() + (_areaRadius - _leverRadius - 2) * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    //
    void Angler::leverLeft(float value) {
        //cout << "[Angler]leverLeft()" << endl;
        _targetX = lever->x() - (_areaRadius - _leverRadius - 2) * value;
        _flgX = true;
    }
    //--------------------------------------------------------------
    //
    void Angler::leverRight(float value) {
        //cout << "[Angler]leverRight()" << endl;
        _targetX = lever->x() + (_areaRadius - _leverRadius - 2) * value;
        _flgX = true;
    }
    
    //--------------------------------------------------------------
    //
    bool Angler::enabled() { return _enabled; }
    void Angler::enabled(bool value) {
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
    void Angler::_areaOver() {
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
    void Angler::_areaOut() {
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
    void Angler::_areaPress() {
        
    }
    //--------------------------------------------------------------
    //
    void Angler::_areaRelease() {
        
    }
    
    //--------------------------------------------------------------
    //
    void Angler::_ballOver() {
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
    void Angler::_ballOut() {
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
    void Angler::_ballPress() {
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
    void Angler::_ballRelease() {
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
    void Angler::_ballMove() {
        
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Angler::_mouseEventHandler(Event& event) {
        //cout << "[Angler]_mouseEventHandler(" << event.type() << endl;
        
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
                stage()->addEventListener(MouseEvent::MOUSE_UP, this, &Angler::_mouseEventHandler);
            }
        }
        
        if(event.type() == MouseEvent::MOUSE_UP) {
            //if(event.target() == this) _areaRelease();
            if(event.currentTarget() == stage()){
                _ballRelease();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, this, &Angler::_mouseEventHandler);
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