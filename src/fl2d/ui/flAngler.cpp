#include "flAngler.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flAngler::flAngler(float areaDiameter, float leverDiameter) {
        //cout << "[Angler]Angler()" << endl;
        
        _target = this;
        name("flAngler");
        
        _value = 0.0;
        
        _areaRadius = areaDiameter * 0.5;
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
        
        _center = new ofPoint(_areaRadius, _areaRadius);
        
        flGraphics* g;
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        addEventListener(flMouseEvent::ROLL_OVER, this, &flAngler::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flAngler::_mouseEventHandler);
        //------------------------------------------
        //------------------------------------------
        lever = new flSprite();
        g = lever->graphics();
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
        lever->addEventListener(flMouseEvent::ROLL_OVER, this, &flAngler::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::ROLL_OUT, this, &flAngler::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flAngler::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::MOUSE_MOVE, this, &flAngler::_mouseEventHandler);
        lever->addEventListener(flMouseEvent::DRAGGING, this, &flAngler::_mouseEventHandler);
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
    flAngler::~flAngler() {
        //cout << "[Angler]~Angler()" << endl;
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flAngler::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flAngler::_mouseEventHandler);
        
        lever->removeEventListener(flMouseEvent::ROLL_OVER, this, &flAngler::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::ROLL_OUT, this, &flAngler::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flAngler::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::MOUSE_MOVE, this, &flAngler::_mouseEventHandler);
        lever->removeEventListener(flMouseEvent::DRAGGING, this, &flAngler::_mouseEventHandler);
        
        _value = 0.0;
        
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
    void flAngler::_setup() {
        //cout << "[SimpleSlider]setup()" << endl;
    }
    
    //--------------------------------------------------------------
    //
    void flAngler::_update() {
        //cout << "isMouseDown" << lever->isMouseDown() << endl;
        
        float distance = _center->distance(ofVec2f(lever->x(), lever->y()));
        
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
            if(distance >= _areaRadius - _leverRadius - 2) {
                if(!_flg) {
                    float n = _areaRadius / (_areaRadius - _leverRadius);
                    _outPosition.x = _center->x + (lever->x() - _center->x) * n;
                    _outPosition.y = _center->y + (lever->y() - _center->y) * n;
                    
                    _flg = true;
                    _zeroAngle = flmath::getAngle(lever->x() - _center->x, lever->y() - _center->y);
                }
            }
            
            if(_flg) {
                //------------------------------------------
                _value = flmath::getAngle(lever->x() - _center->x, lever->y() - _center->y);
                _value = _value - _zeroAngle;
                if(_value > 180.0) { _value -= 360.0; }
                if(_value < -180.0) { _value += 360.0; }
                //------------------------------------------
            }
            //------------------------------------------
            
            //------------------------------------------
            flAnglerEvent* event = new flAnglerEvent(flAnglerEvent::CHANGE);
            event->__value = _value;
            dispatchEvent(event);
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
            }
            //------------------------------------------
            
            //------------------------------------------
            if(distance == 0.0) {
                _flg = false;
                _zeroAngle = 0.0;
            }
            
            _outPosition.x = _center->x;
            _outPosition.y = _center->y;
            _value = 0.0;
            //------------------------------------------
        }
    }
    
    //--------------------------------------------------------------
    //
    void flAngler::_draw() {
        if(lever->isMouseDown()) {
            GLboolean preLineSmooth = glIsEnabled(GL_LINE_SMOOTH);
            ofEnableSmoothing();
            
            ofPushStyle();
            ofSetHexColor(_normalLineColor.getHex());
            ofDrawLine(_center->x, _center->y, _outPosition.x, _outPosition.y);
            ofPopStyle();
            
            ofPushStyle();
            ofSetHexColor(_activeLineColor.getHex());
            ofDrawLine(_center->x, _center->y, lever->x(), lever->y());
            ofPopStyle();
            
            if(preLineSmooth == GL_FALSE) ofDisableSmoothing();
            
            ofPushStyle();
            ofTranslate(*_center);
            ofDrawBitmapString(ofToString(_value), -30, 15);
            ofTranslate(-*_center);
            ofPopStyle();
        }
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flTextField* flAngler::label() { return _label; }
    void flAngler::label(flTextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    float flAngler::value() { return _value; }
    
    //--------------------------------------------------------------
    //
    bool flAngler::enabled() { return _enabled; }
    void flAngler::enabled(bool value) {
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
    void flAngler::_areaOver() {
        //if(lever->isMouseDown()) return;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _overLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void flAngler::_areaOut() {
        //if(lever->isMouseDown()) return;
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _normalLineColor.getHex());
        g->beginFill(_normalColor.getHex(), 1);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void flAngler::_areaPress() {
        
    }
    //--------------------------------------------------------------
    //
    void flAngler::_areaRelease() {
        
    }
    
    //--------------------------------------------------------------
    //
    void flAngler::_ballOver() {
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
    void flAngler::_ballOut() {
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
    void flAngler::_ballPress() {
        _draggablePoint->x = mouseX() - lever->x();
        _draggablePoint->y = mouseY() - lever->y();
        //cout << _draggablePoint->x << " " << _draggablePoint->y << endl;
        flGraphics* g;
        
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
    void flAngler::_ballRelease() {
        _draggablePoint->x = 0;
        _draggablePoint->y = 0;
        
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
    void flAngler::_ballMove() {
        
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flAngler::_mouseEventHandler(flEvent& event) {
        //cout << "[Angler]_mouseEventHandler(" << event.type() << endl;
        
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
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flAngler::_mouseEventHandler);
            }
        }
        
        if(event.type() == flMouseEvent::MOUSE_UP) {
            //if(event.target() == this) _areaRelease();
            if(event.currentTarget() == stage()){
                _ballRelease();
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flAngler::_mouseEventHandler);
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
