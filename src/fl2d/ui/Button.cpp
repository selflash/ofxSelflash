#include "Button.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    Button::Button(float width, float height) {
        //cout << "[Button]Button()" << endl;
        
        _target = this;
        name("Button");
        
        buttonMode(true);
        
        _uiWidth = width;
        _uiHeight = height;
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(FlashConfig::UI_LINE_COLOR);
        _normalColor.setHex(FlashConfig::UI_NORMAL_COLOR);
        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);
        _deactiveColor.setHex(FlashConfig::UI_DEACTIVE_COLOR);
        
        _labelTextNotSelected = "";
        _labelTextSelected = "";
        
        //------------------------------------------
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor.getHex());
        g->beginFill(_normalColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
        addEventListener(MouseEvent::ROLL_OVER, this, &Button::_mouseEventHandler);
        addEventListener(MouseEvent::ROLL_OUT, this, &Button::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_DOWN, this, &Button::_mouseEventHandler);
        //addEventListener(MouseEvent::MOUSE_UP, this, &Button::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _label = new TextField();
        _label->x(0);
        _label->width(_uiWidth);
        _label->autoSize(TextFieldAutoSize::CENTER);
        _label->textColor(_labelNormalColor);
        _label->text("Button");
        _label->y(_uiHeight * 0.5 - _label->textHeight() * 0.5);
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
    Button::~Button() {
        //cout << "[Button]~Button()" << endl;
        
        removeEventListener(MouseEvent::ROLL_OVER, this, &Button::_mouseEventHandler);
        removeEventListener(MouseEvent::ROLL_OUT, this, &Button::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_DOWN, this, &Button::_mouseEventHandler);
        //removeEventListener(MouseEvent::MOUSE_UP, this, &Button::_mouseEventHandler);
        
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
    TextField* Button::label() { return _label; }
    
    //--------------------------------------------------------------
    //
    string Button::labelText() { return _label->text(); }
    void Button::labelText(string value, string state) {
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
    bool Button::toggleEnabled() { return _toggleEnabled; }
    void Button::toggleEnabled(bool value) { _toggleEnabled = value; }
    
    //--------------------------------------------------------------
    //
    bool Button::selected() { return _selected; }
    void Button::selected(bool value, bool dispatch) {
        if(_selected == value) return;
        
        _selected = value;
        
        if(_enabled) {
            if(isMouseOver()) {
                _over();
            } else {
                _out();
            }
            
            Graphics* g;
            
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
            dispatchEvent(new Event(Event::CHANGE));
            dispatchEvent(new ButtonEvent(ButtonEvent::CHANGE));
            //dispatchEvent(new ButtonEvent(RadioButtonEvent::CHANGE));
        }
    }
    
    //--------------------------------------------------------------
    //
    void* Button::pointerValue() { return _pointerValue; }
    void Button::pointerValue(void* value) { _pointerValue = value; }
    
    //--------------------------------------------------------------
    //
    string Button::stringValue() { return _stringValue; }
    void Button::stringValue(string value) { _stringValue = value; }
    
    //--------------------------------------------------------------
    //
    float Button::floatValue() { return _floatValue; }
    void Button::floatValue(float value) { _floatValue = value; }
    
    //--------------------------------------------------------------
    //
    int Button::intValue() { return _intValue; }
    void Button::intValue(int value) { _intValue = value; }
    
    //--------------------------------------------------------------
    //
    bool Button::enabled() { return _enabled; }
    void Button::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        
        if(_enabled) {
            _label->textColor(_labelNormalColor);
        } else {
            _label->textColor(_labelDeactiveColor);
        }
        
        Graphics* g;
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
    void Button::_over() {
        //    cout << "[Button]_over()" << endl;
        //    cout << this->isMouseOver() << endl;
        //    cout << this->isRollOver() << endl;
        //    cout << this->isMouseDown() << endl;
        
        if(isMouseDown()) return;
        
        if(_selected) {
            //------------------------------------------
            _label->textColor(_labelActiveColor);
            
            Graphics* g;
            g = graphics();
            g->clear();
            g->lineStyle(1, _overColor.getHex());
            g->beginFill(_activeColor.getHex());
            g->drawRect(0, 0, _uiWidth, _uiHeight);
            g->endFill();
            //------------------------------------------
            
            dispatchEvent(new ButtonEvent(ButtonEvent::ROLL_OVER));
            return;
        }
        
        _label->textColor(_labelNormalColor);
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _overColor.getHex());
        g->beginFill(_normalColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
        
        dispatchEvent(new ButtonEvent(ButtonEvent::ROLL_OVER));
    }
    
    //--------------------------------------------------------------
    //
    void Button::_out() {
        if(isMouseDown()) return;
        
        Graphics* g;
        
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
            
            dispatchEvent(new ButtonEvent(ButtonEvent::ROLL_OUT));
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
        
        dispatchEvent(new ButtonEvent(ButtonEvent::ROLL_OUT));
    }
    
    //--------------------------------------------------------------
    //
    void Button::_press() {
        _label->textColor(_labelNormalColor);
        
        Graphics* g;
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _overColor.getHex());
        g->beginFill(_activeColor.getHex());
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
        //------------------------------------------
        
        if(_toggleEnabled) _selected = !_selected;
        
        dispatchEvent(new ButtonEvent(ButtonEvent::MOUSE_DOWN));
        
        if(_toggleEnabled) {
            dispatchEvent(new Event(Event::CHANGE));
            dispatchEvent(new ButtonEvent(ButtonEvent::CHANGE));
        }
    }
    
    //--------------------------------------------------------------
    //
    void Button::_release() {
        Graphics* g;
        
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
            dispatchEvent(new ButtonEvent(ButtonEvent::MOUSE_UP));
            dispatchEvent(new ButtonEvent(ButtonEvent::CLICK));
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
        
        dispatchEvent(new ButtonEvent(ButtonEvent::MOUSE_UP));
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void Button::_mouseEventHandler(Event& event) {
        if(!_enabled) return;
        //cout << "[Button]_mouseEventHandler(" << event.type() << ")" << endl;
        //cout << "[Button]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //cout << "[Button]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //cout << "[Button]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        if(event.type() == MouseEvent::ROLL_OVER) {
            if(event.target() == this) _over();
        }
        if(event.type() == MouseEvent::ROLL_OUT) {
            if(event.target() == this) _out();
        }
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            if(event.target() == this) _press();
            addEventListener(MouseEvent::MOUSE_UP, this, &Button::_mouseEventHandler);
            if(stage()) stage()->addEventListener(MouseEvent::MOUSE_UP, this, &Button::_mouseEventHandler);
        }
        if(event.type() == MouseEvent::MOUSE_UP) {
            removeEventListener(MouseEvent::MOUSE_UP, this, &Button::_mouseEventHandler);
            if(stage()) stage()->removeEventListener(MouseEvent::MOUSE_UP, this, &Button::_mouseEventHandler);
            //            if(event.target() == stage()) _release();
            _release();
        }
    }
    
}
