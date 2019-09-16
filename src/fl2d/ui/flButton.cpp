#include "flButton.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flButton::flButton(float width, float height) {
        //cout << "[flButton]flButton()" << endl;
        
        _target = this;
        name("flButton");
        
        buttonMode(true);
        
        _uiWidth = width;
        _uiHeight = height;
        
        _labelNormalColor = flDefinition::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = flDefinition::UI_LABEL_OVER_COLOR;
        _labelActiveColor = flDefinition::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = flDefinition::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(flDefinition::UI_LINE_COLOR);
        _normalColor.setHex(flDefinition::UI_NORMAL_COLOR);
        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
        _deactiveColor.setHex(flDefinition::UI_DEACTIVE_COLOR);
        
        _labelTextNotSelected = "";
        _labelTextSelected = "";
        
        //------------------------------------------
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor.getHex());
        g->beginFill(_normalColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
        addEventListener(flMouseEvent::ROLL_OVER, this, &flButton::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flButton::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flButton::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _label = new flTextField();
        _label->x(0);
        _label->width(_uiWidth);
        _label->autoSize(flTextFieldAutoSize::CENTER);
        _label->textColor(_labelNormalColor);
        _label->text("Button");
        _label->y(floor(_uiHeight * 0.5 - _label->textHeight() * 0.5) - 1);
        _label->mouseEnabled(false);
        addChild(_label);
        //------------------------------------------
        
        _toggleEnabled = false;
        _selected = false;
        
        _pointerValue = NULL;
        _stringValue = "";
        _floatValue = 0.0;
        _intValue = 0;
        
        _enabled = true;
    }
    
    //--------------------------------------------------------------
    //
    flButton::~flButton() {
        //cout << "[flButton]~flButton()" << endl;
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flButton::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flButton::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flButton::_mouseEventHandler);
        //removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
        
        _labelTextNotSelected = "";
        _labelTextSelected = "";
        
        delete _label;
        _label = NULL;
        
        _toggleEnabled = false;
        _selected = false;
        
        _pointerValue = NULL;
        _stringValue = "";
        _floatValue = 0.0;
        _intValue = 0;
        
        _enabled = false;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flTextField* flButton::label() { return _label; }
    
    //--------------------------------------------------------------
    //
    string flButton::labelText() { return _label->text(); }
    void flButton::labelText(string value, string state) {
        if(state == "default") {
            _labelTextNotSelected = value;
            _labelTextSelected = value;
        }
        else if(state == "selected") {
            _labelTextNotSelected = value;
        }
        else if(state == "notSelected") {
            _labelTextSelected = value;
        }
        
        if(_selected) {
            _label->text(_labelTextSelected);
        } else {
            _label->text(_labelTextNotSelected);
        }
    }
    
    //--------------------------------------------------------------
    //
    bool flButton::toggleEnabled() { return _toggleEnabled; }
    void flButton::toggleEnabled(bool value) { _toggleEnabled = value; }
    
    //--------------------------------------------------------------
    //
    bool flButton::selected() { return _selected; }
    void flButton::selected(bool value, bool dispatch) {
        if(_selected == value) return;
        
        _selected = value;
        
        if(_enabled) {
            if(isMouseOver()) {
                _over();
            } else {
                _out();
            }
            
            flGraphics* g;
            
            if(_selected) {
                _label->text(_labelTextSelected);
                if(isMouseOver()) {
                    _label->textColor(_labelActiveColor);
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _overColor.getHex());
                    g->beginFill(_activeColor.getHex());
                    g->drawRect(0, 0, _uiWidth, _uiHeight);
                    g->endFill();
                } else {
                    _label->textColor(_labelNormalColor);
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _lineColor.getHex());
                    g->beginFill(_activeColor.getHex());
                    g->drawRect(0, 0, _uiWidth, _uiHeight);
                    g->endFill();
                }
            } else {
                _label->text(_labelTextNotSelected);
                if(isMouseOver()) {
                    _label->textColor(_labelActiveColor);
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _overColor.getHex());
                    g->beginFill(_normalColor.getHex());
                    g->drawRect(0, 0, _uiWidth, _uiHeight);
                    g->endFill();
                } else {
                    _label->textColor(_labelNormalColor);
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _lineColor.getHex());
                    g->beginFill(_normalColor.getHex());
                    g->drawRect(0, 0, _uiWidth, _uiHeight);
                    g->endFill();
                }
            }
        }
        
        if(dispatch) {
            dispatchEvent(new flEvent(flEvent::CHANGE));
            dispatchEvent(new flButtonEvent(flButtonEvent::CHANGE));
        }
    }
    
    //--------------------------------------------------------------
    //
    void* flButton::pointerValue() { return _pointerValue; }
    void flButton::pointerValue(void* value) { _pointerValue = value; }
    
    //--------------------------------------------------------------
    //
    string flButton::stringValue() { return _stringValue; }
    void flButton::stringValue(string value) { _stringValue = value; }
    
    //--------------------------------------------------------------
    //
    float flButton::floatValue() { return _floatValue; }
    void flButton::floatValue(float value) { _floatValue = value; }
    
    //--------------------------------------------------------------
    //
    int flButton::intValue() { return _intValue; }
    void flButton::intValue(int value) { _intValue = value; }
    
    //--------------------------------------------------------------
    //
    bool flButton::enabled() { return _enabled; }
    void flButton::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        
        if(_enabled) {
            _label->textColor(_labelNormalColor);
        } else {
            _label->textColor(_labelDeactiveColor);
        }
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor.getHex());
        if(_enabled) {
            g->beginFill(_normalColor.getHex());
        } else {
            g->beginFill(_deactiveColor.getHex());
        }
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flButton::_over() {
        //    cout << "[flButton]_over()" << endl;
        //    cout << this->isMouseOver() << endl;
        //    cout << this->isRollOver() << endl;
        //    cout << this->isMouseDown() << endl;
        
        if(isMouseDown()) return;
        
        if(_selected) {
            //------------------------------------------
            _label->textColor(_labelActiveColor);
            
            flGraphics* g;
            g = graphics();
            g->clear();
            g->lineStyle(1, _overColor.getHex());
            g->beginFill(_activeColor.getHex());
            g->drawRect(0, 0, _uiWidth, _uiHeight);
            g->endFill();
            //------------------------------------------
            
            dispatchEvent(new flButtonEvent(flButtonEvent::ROLL_OVER));
            return;
        }
        
        _label->textColor(_labelNormalColor);
        
        flGraphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _overColor.getHex());
        g->beginFill(_normalColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
        
        dispatchEvent(new flButtonEvent(flButtonEvent::ROLL_OVER));
    }
    
    //--------------------------------------------------------------
    //
    void flButton::_out() {
        if(isMouseDown()) return;
        
        flGraphics* g;
        
        if(_selected) {
            //------------------------------------------
            _label->textColor(_labelNormalColor);
            
            g = graphics();
            g->clear();
            g->lineStyle(1, _lineColor.getHex());
            g->beginFill(_activeColor.getHex());
            g->drawRect(0, 0, _uiWidth, _uiHeight);
            g->endFill();
            //------------------------------------------
            
            dispatchEvent(new flButtonEvent(flButtonEvent::ROLL_OUT));
            return;
        }
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor.getHex());
        g->beginFill(_normalColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
        //------------------------------------------
        
        dispatchEvent(new flButtonEvent(flButtonEvent::ROLL_OUT));
    }
    
    //--------------------------------------------------------------
    //
    void flButton::_press() {
        _label->textColor(_labelNormalColor);
        
        flGraphics* g;
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _overColor.getHex());
        g->beginFill(_activeColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
        //------------------------------------------
        
        if(_toggleEnabled) _selected = !_selected;
        
        dispatchEvent(new flButtonEvent(flButtonEvent::MOUSE_DOWN));
        
        if(_toggleEnabled) {
            dispatchEvent(new flEvent(flEvent::CHANGE));
            dispatchEvent(new flButtonEvent(flButtonEvent::CHANGE));
        }
    }
    
    //--------------------------------------------------------------
    //
    void flButton::_release() {
        flGraphics* g;
        
        _label->textColor(_labelNormalColor);
        
        if(_toggleEnabled) {
            if(_selected) {
                _label->text(_labelTextSelected);
                if(isMouseOver()) {
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _overColor.getHex());
                    g->beginFill(_activeColor.getHex());
                    g->drawRect(0, 0, _uiWidth, _uiHeight);
                    g->endFill();
                } else {
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _lineColor.getHex());
                    g->beginFill(_activeColor.getHex());
                    g->drawRect(0, 0, _uiWidth, _uiHeight);
                    g->endFill();
                }
            } else {
                _label->text(_labelTextNotSelected);
                if(isMouseOver()) {
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _overColor.getHex());
                    g->beginFill(_normalColor.getHex());
                    g->drawRect(0, 0, _uiWidth, _uiHeight);
                    g->endFill();
                } else {
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _lineColor.getHex());
                    g->beginFill(_normalColor.getHex());
                    g->drawRect(0, 0, _uiWidth, _uiHeight);
                    g->endFill();
                }
            }
            return;
        }
        
        if(isMouseOver()) {
            _over();
            dispatchEvent(new flButtonEvent(flButtonEvent::MOUSE_UP));
            dispatchEvent(new flButtonEvent(flButtonEvent::CLICK));
            return;
        }
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor.getHex());
        g->beginFill(_normalColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
        //------------------------------------------
        
        dispatchEvent(new flButtonEvent(flButtonEvent::MOUSE_UP));
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flButton::_mouseEventHandler(flEvent& event) {
        if(!_enabled) return;
        //cout << "[flButton]_mouseEventHandler(" << event.type() << ")" << endl;
        //cout << "[flButton]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //cout << "[flButton]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //cout << "[flButton]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) _over();
        }
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) _out();
        }
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) _press();
            addEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
            if(stage()) stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
        }
        if(event.type() == flMouseEvent::MOUSE_UP) {
            removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
            if(stage()) stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
            //            if(event.target() == stage()) _release();
            _release();
        }
    }
    
}
