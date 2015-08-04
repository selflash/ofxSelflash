#include "Joystick.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Joystick::Joystick(float diameter) {
        //cout << "[Joystick]Joystick()" << endl;
        
        _target = this;
        name("Joystick");
        
        _xValue = 0;
        _yValue = 0;
        
        _diameter = diameter;
        
        _areaRadius = _diameter * 0.5f;
        _leverRadius = _diameter * 0.25f;
        _lineColor = FlashConfig::UI_LINE_COLOR;
        _normalColor = FlashConfig::UI_NORMAL_COLOR;
        _overColor = FlashConfig::UI_OVER_COLOR;
        _activeColor = FlashConfig::UI_ACTIVE_COLOR;
        
        _center = new ofPoint(_areaRadius, 16 + _areaRadius);
        
        Graphics* g;
        //------------------------------------------
        g = graphics();
        g->smoothing(true);
        g->clear();
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 0.3);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        addEventListener(MouseEvent::ROLL_OVER, this, &Joystick::_mouseEventHandler);
        addEventListener(MouseEvent::ROLL_OUT, this, &Joystick::_mouseEventHandler);    
        //------------------------------------------
        //------------------------------------------
        lever = new Sprite();
        g = lever->graphics();
        g->smoothing(true);
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor);
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();
        lever->x(_center->x);
        lever->y(_center->y);
        lever->useHandCursor(true);
        lever->addEventListener(MouseEvent::ROLL_OVER, this, &Joystick::_mouseEventHandler);
        lever->addEventListener(MouseEvent::ROLL_OUT, this, &Joystick::_mouseEventHandler);
        lever->addEventListener(MouseEvent::MOUSE_DOWN, this, &Joystick::_mouseEventHandler);
        lever->addEventListener(MouseEvent::MOUSE_MOVE, this, &Joystick::_mouseEventHandler);
        lever->addEventListener(MouseEvent::DRAGGING, this, &Joystick::_mouseEventHandler);
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
        _labelText = new TextField();
        _labelText->x(0);
        _labelText->y(0);
        _labelText->width(_diameter);
        _labelText->autoSize(TextFieldAutoSize::CENTER);
        _labelText->textColor(0x0);
        _labelText->text("JOIYSTICK");
        addChild(_labelText);
        //------------------------------------------    
    }

    //--------------------------------------------------------------
    //
    Joystick::~Joystick() {
        //cout << "[Joystick]~Joystick()" << endl;
        
        removeEventListener(MouseEvent::ROLL_OVER, &Joystick::_mouseEventHandler);
        removeEventListener(MouseEvent::ROLL_OUT, &Joystick::_mouseEventHandler);
        
        lever->removeEventListener(MouseEvent::ROLL_OVER, &Joystick::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::ROLL_OUT, &Joystick::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::MOUSE_DOWN, &Joystick::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::MOUSE_MOVE, &Joystick::_mouseEventHandler);
        lever->removeEventListener(MouseEvent::DRAGGING, &Joystick::_mouseEventHandler);
        
        _diameter = 0;
        
        delete _center;
        _center = NULL;
        
        delete lever;
        lever = NULL;
        
        delete _draggablePoint;
        _draggablePoint = NULL;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void Joystick::_setup() {
        //cout << "[SimpleSlider]setup()" << endl;
    }

    //--------------------------------------------------------------
    //
    void Joystick::_update() {
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
            
            JoystickEvent* event;
            
            event = new JoystickEvent(JoystickEvent::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            
            if(_xValue > 0) {
                event = new JoystickEvent(JoystickEvent::RIGHT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_xValue < 0) {
                event = new JoystickEvent(JoystickEvent::LEFT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_yValue > 0) {
                event = new JoystickEvent(JoystickEvent::UP);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_yValue < 0) {
                event = new JoystickEvent(JoystickEvent::DOWN);
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
            
            JoystickEvent* event;
            
            event = new JoystickEvent(JoystickEvent::CHANGE);
            event->__xValue = _xValue;
            event->__yValue = _yValue;
            dispatchEvent(event);
            
            if(_flgX && _xValue > 0) {
                event = new JoystickEvent(JoystickEvent::RIGHT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgX && _xValue < 0) {
                event = new JoystickEvent(JoystickEvent::LEFT);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgY && _yValue > 0) {
                event = new JoystickEvent(JoystickEvent::UP);
                event->__xValue = _xValue;
                event->__yValue = _yValue;
                dispatchEvent(event);
            }
            if(_flgY && _yValue < 0) {
                event = new JoystickEvent(JoystickEvent::DOWN);
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
                
                JoystickEvent* event = new JoystickEvent(JoystickEvent::CHANGE);
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
    void Joystick::_draw() {
        
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    string Joystick::label() { return _labelText->text(); }
    void Joystick::label(string value, int color) {
        _labelText->text(value);
        _labelText->textColor(color);
    }
    //--------------------------------------------------------------
    //
    void Joystick::textColor(int color) {
        _labelText->textColor(color);
    }

    //--------------------------------------------------------------
    //
    float Joystick::xValue() { return _xValue; }
    //--------------------------------------------------------------
    //
    float Joystick::yValue() { return _yValue; }

    //--------------------------------------------------------------
    //
    void Joystick::leverUp(float value) {
        //cout << "[Joystick]leverUp()" << endl;
        _targetY = lever->y() - (_areaRadius - _leverRadius - 2) * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    //
    void Joystick::leverDown(float value) {
        //cout << "[Joystick]leverDown()" << endl;
        _targetY = lever->y() + (_areaRadius - _leverRadius - 2) * value;
        _flgY = true;
    }
    //--------------------------------------------------------------
    //
    void Joystick::leverLeft(float value) {
        //cout << "[Joystick]leverLeft()" << endl;
        _targetX = lever->x() - (_areaRadius - _leverRadius - 2) * value;
        _flgX = true;
    }
    //--------------------------------------------------------------
    //
    void Joystick::leverRight(float value) {
        //cout << "[Joystick]leverRight()" << endl;
        _targetX = lever->x() + (_areaRadius - _leverRadius - 2) * value;
        _flgX = true;
    }


    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    void Joystick::_areaOver() {
        //if(lever->isMouseDown()) return;
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _overColor);
        g->beginFill(_normalColor, 0.3);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void Joystick::_areaOut() {
        //if(lever->isMouseDown()) return;
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor, 0.3);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
    }
    //--------------------------------------------------------------
    //
    void Joystick::_areaPress() {
        
    }
    //--------------------------------------------------------------
    //
    void Joystick::_areaRelease() {
        
    }

    //--------------------------------------------------------------
    //
    void Joystick::_ballOver() {
        if(lever->isMouseDown()) return;
        
        _areaOver();
        
        Graphics* g;
        g = lever->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _lineColor);
        g->beginFill(_overColor);
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();    
    }
    //--------------------------------------------------------------
    //
    void Joystick::_ballOut() {
        if(lever->isMouseDown()) return;
        
        _areaOut();
            
        Graphics* g;
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor);
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();    
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Joystick::_ballPress() {
        _draggablePoint->x = mouseX() - lever->x();
        _draggablePoint->y = mouseY() - lever->y();
        //cout << _draggablePoint->x << " " << _draggablePoint->y << endl;
        Graphics* g;

        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _activeColor);
        g->beginFill(_normalColor, 0.3);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        //------------------------------------------
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _lineColor);
        g->beginFill(_activeColor);
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();    
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Joystick::_ballRelease() {
        _draggablePoint->x = 0;
        _draggablePoint->y = 0;
        
        Graphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        if(isMouseOver()) {
            g->lineStyle(1, _overColor);
        } else {
            g->lineStyle(1, _lineColor);
        }
        g->beginFill(_normalColor, 0.3);
        g->drawCircle(_center->x, _center->y, _areaRadius);
        g->endFill();
        //------------------------------------------
        
        //------------------------------------------
        g = lever->graphics();
        g->clear();
        g->beginFill(0xFF0000, 0);
        g->drawCircle(0, 0, _leverRadius * 1.8);
        g->lineStyle(1, _lineColor);
        if(lever->isMouseOver()) {
            g->beginFill(_overColor);
        } else {
            g->beginFill(_normalColor);
        }
        g->drawCircle(0, 0, _leverRadius);
        g->endFill();    
        //------------------------------------------
    }
    //--------------------------------------------------------------
    //
    void Joystick::_ballMove() {
        
    }

    //==============================================================
    // EVENT HANDLER
    //==============================================================

    //--------------------------------------------------------------
    //
    void Joystick::_mouseEventHandler(Event& event) {
        //cout << "[Joystick]_mouseEventHandler(" << event.type() << endl;
        
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
                stage()->addEventListener(MouseEvent::MOUSE_UP, this, &Joystick::_mouseEventHandler);
            }
        }
        
        if(event.type() == MouseEvent::MOUSE_UP) {
            //if(event.target() == this) _areaRelease();
            if(event.currentTarget() == stage()){
                _ballRelease();
                stage()->removeEventListener(MouseEvent::MOUSE_UP, &Joystick::_mouseEventHandler);
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