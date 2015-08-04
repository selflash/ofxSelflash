#include "Button.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    Button::Button(float buttonWidth, float buttonHeight) {
        //cout << "[Button]Button()" << endl;
        
        _target = this;
        name("Button");
        
        _buttonWidth = buttonWidth;
        _buttonHeight = buttonHeight;
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        
        _lineColor = FlashConfig::UI_LINE_COLOR;
        _normalColor = FlashConfig::UI_NORMAL_COLOR;
        _overColor = FlashConfig::UI_OVER_COLOR;
        _activeColor = FlashConfig::UI_ACTIVE_COLOR;
        
        buttonMode(true);
        
        Graphics* g;
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor);
        g->drawRect(0, 0, _buttonWidth, _buttonHeight);
        g->endFill();
        addEventListener(MouseEvent::ROLL_OVER, this, &Button::_mouseEventHandler);
        addEventListener(MouseEvent::ROLL_OUT, this, &Button::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_DOWN, this, &Button::_mouseEventHandler);
        //addEventListener(MouseEvent::MOUSE_UP, this, &Button::_mouseEventHandler);
        //------------------------------------------
        
        //------------------------------------------
        //ラベル
        _labelText = new TextField();
        _labelText->x(0);
        _labelText->width(_buttonWidth);
        _labelText->autoSize(TextFieldAutoSize::CENTER);
        _labelText->textColor(0xffffff);
        _labelText->text("BUTTON");
        _labelText->y(_buttonHeight * 0.5 - _labelText->textHeight() * 0.5);
        _labelText->mouseEnabled(false);
        addChild(_labelText);
        //------------------------------------------
        
        _toggleEnabled = false;
        _selected = false;
        
        _pointerValue = NULL;
        _stringValue = "";
        _floatValue = 0.0;
        _intValue = 0;
    }

    //--------------------------------------------------------------
    //
    Button::~Button() {
        //cout << "[Button]~Button()" << endl;
        
        removeEventListener(MouseEvent::ROLL_OVER, &Button::_mouseEventHandler);
        removeEventListener(MouseEvent::ROLL_OUT, &Button::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_DOWN, &Button::_mouseEventHandler);
        //removeEventListener(MouseEvent::MOUSE_UP, &Button::_mouseEventHandler);
        
        delete _labelText;
        _labelText = NULL;
        
        _toggleEnabled = false;
        _selected = false;
            
        _pointerValue = NULL;
        _stringValue = "";
        _floatValue = 0.0;
        _intValue = 0;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    //void Button::_update(){

    //}

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    string Button::label() { return _labelText->text(); }
    void Button::label(string value, int color) {
        _labelNormalColor = color;
        _labelText->text(value);
        _labelText->textColor(_labelNormalColor);
        
        //if(color == 0xffffff) _labelActiveColor = 0x000000;
    }

    //--------------------------------------------------------------
    //
    void Button::textColor(int color) {
        _labelNormalColor = color;
        _labelText->textColor(_labelNormalColor);
        
        //if(color == 0xffffff) _labelActiveColor = 0x000000;
    }

    //--------------------------------------------------------------
    //
    bool Button::toggleEnabled() { return _toggleEnabled; }
    void Button::toggleEnabled(bool value) { _toggleEnabled = value; }

    //--------------------------------------------------------------
    //
    bool Button::selected() { return _selected; }
    void Button::selected(bool value) {
        if(_selected == value) return;
        
        _selected = value;
        
        if(isMouseOver()) {
            _over();
        } else {
            _out();
        }
        
        Graphics* g;
        
        if(_selected) {
            if(isMouseOver()) {
                _labelText->textColor(_labelActiveColor);
            } else {
                _labelText->textColor(_labelNormalColor);
            }
            
            g = graphics();
            g->clear();
            g->lineStyle(1, _overColor);
            g->beginFill(_activeColor);
            g->drawRect(0, 0, _buttonWidth, _buttonHeight);
            g->endFill();
            
        } else {
            if(isMouseOver()) {
                _labelText->textColor(_labelActiveColor);
            } else {
                _labelText->textColor(_labelNormalColor);
            }
            
            g = graphics();
            g->clear();
            g->lineStyle(1, _overColor);
            g->beginFill(_normalColor);
            g->drawRect(0, 0, _buttonWidth, _buttonHeight);
            g->endFill();        
        }
        
        dispatchEvent(new Event(Event::CHANGE));
        //dispatchEvent(new ButtonEvent(RadioButtonEvent::CHANGE));
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
            _labelText->textColor(_labelActiveColor);
            
            Graphics* g;
            g = graphics();
            g->clear();
            g->lineStyle(2, _overColor);
            g->beginFill(_activeColor);
            g->drawRect(0, 0, _buttonWidth, _buttonHeight);
            g->endFill();
            return;
        }
        
        _labelText->textColor(_labelNormalColor);
        
        Graphics* g;
        g = graphics();
        g->clear();
        g->lineStyle(1, _overColor);
        g->beginFill(_normalColor);
        g->drawRect(0, 0, _buttonWidth, _buttonHeight);
        g->endFill();
    }

    //--------------------------------------------------------------
    //
    void Button::_out() {
        if(isMouseDown()) return;
        
        Graphics* g;
        
        if(_selected) {
            //------------------------------------------
            _labelText->textColor(_labelActiveColor);
            
            g = graphics();
            g->clear();
            g->lineStyle(1, _lineColor);
            g->beginFill(_activeColor);
            g->drawRect(0, 0, _buttonWidth, _buttonHeight);
            g->endFill();
            //------------------------------------------
            return;
        }
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor);
        g->drawRect(0, 0, _buttonWidth, _buttonHeight);
        g->endFill();
        //------------------------------------------
    }

    //--------------------------------------------------------------
    //
    void Button::_press() {
        if(_toggleEnabled) _selected = !_selected;
        
        _labelText->textColor(_labelNormalColor);
        
        Graphics* g;
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _overColor);
        g->beginFill(_activeColor);
        g->drawRect(0, 0, _buttonWidth, _buttonHeight);
        g->endFill();
        //------------------------------------------
    }

    //--------------------------------------------------------------
    //
    void Button::_release() {
        Graphics* g;
        
        _labelText->textColor(_labelNormalColor);
        
        if(_toggleEnabled) {
            if(_selected) {
                if(isMouseOver()) {
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _overColor);
                    g->beginFill(_activeColor);
                    g->drawRect(0, 0, _buttonWidth, _buttonHeight);
                    g->endFill();
                } else {
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _lineColor);
                    g->beginFill(_activeColor);
                    g->drawRect(0, 0, _buttonWidth, _buttonHeight);
                    g->endFill();
                }
            } else {
                if(isMouseOver()) {
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _overColor);
                    g->beginFill(_normalColor);
                    g->drawRect(0, 0, _buttonWidth, _buttonHeight);
                    g->endFill();
                } else {
                    g = graphics();
                    g->clear();
                    g->lineStyle(1, _lineColor);
                    g->beginFill(_normalColor);
                    g->drawRect(0, 0, _buttonWidth, _buttonHeight);
                    g->endFill();
                }
            }
            return;
        }
        
        if(isMouseOver()) {
            _over();
            return;
        }
        
        //------------------------------------------
        g = graphics();
        g->clear();
        g->lineStyle(1, _lineColor);
        g->beginFill(_normalColor);
        g->drawRect(0, 0, _buttonWidth, _buttonHeight);
        g->endFill();
        //------------------------------------------
    }

    //==============================================================
    // EVENT HANDLER
    //==============================================================

    //--------------------------------------------------------------
    //
    void Button::_mouseEventHandler(Event& event){
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
            if(stage()) stage()->addEventListener(MouseEvent::MOUSE_UP, this, &Button::_mouseEventHandler);
        }
        if(event.type() == MouseEvent::MOUSE_UP) {
            if(event.target() == stage()) _release();
        }
    }

}