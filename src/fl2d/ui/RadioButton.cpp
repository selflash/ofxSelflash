#include "RadioButton.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    RadioButton::RadioButton(float width) {
        _target = this;
        name("RadioButton");
        
        buttonMode(true);
        mouseChildren(false);
        
        _lineColor = new ofFloatColor();
        _lineColor->setHex(FlashConfig::UI_LINE_COLOR);
        
        _normalColor = new ofFloatColor();
        _normalColor->setHex(FlashConfig::UI_NORMAL_COLOR);
        
        _overColor = new ofFloatColor();
        _overColor->setHex(FlashConfig::UI_OVER_COLOR);
        
        _activeColor = new ofFloatColor();
        _activeColor->setHex(FlashConfig::UI_ACTIVE_COLOR);
        
        _bSelected = false;
        
        //------------------------------------------
        _labelText = new TextField();
        _labelText->x(20);
        _labelText->y(0);
        _labelText->autoSize(TextFieldAutoSize::LEFT);
        _labelText->textColor(0x0);
        _labelText->text("RADIO BUTTON");
        addChild(_labelText);
        //------------------------------------------

        //------------------------------------------
        _normal();
        //------------------------------------------
        
        addEventListener(MouseEvent::MOUSE_OVER, this, &RadioButton::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_OUT, this, &RadioButton::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_DOWN, this, &RadioButton::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_UP, this, &RadioButton::_mouseEventHandler);
    }

    //--------------------------------------------------------------
    //
    RadioButton::~RadioButton() {
        
        delete _lineColor;
        _lineColor = NULL;
        
        delete _normalColor;
        _normalColor = NULL;
        
        delete _overColor;
        _overColor = NULL;
        
        delete _activeColor;
        _activeColor = NULL;
        
        removeEventListener(MouseEvent::MOUSE_OVER, &RadioButton::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_OUT, &RadioButton::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_DOWN, &RadioButton::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_UP, &RadioButton::_mouseEventHandler);
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    string RadioButton::label() { return _labelText->text(); }
    void RadioButton::label(string value, int color) {
        _labelText->text(value);
        _labelText->textColor(color);
        
        if(isMouseOver()) {
            _over();
        } else {
            _normal();
        }
    }
    //--------------------------------------------------------------
    //
    void RadioButton::textColor(int color) {
        _labelText->textColor(color);
    }

    //--------------------------------------------------------------
    //
    bool RadioButton::selected() { return _bSelected; }
    void RadioButton::selected(bool value, bool dispatch) {
        if(_bSelected == value) return;
        
        _bSelected = value;
        
        if(isMouseOver()){
            _over();
        } else {
            _normal();
        }
        
        if(_bSelected) {
            if(isMouseOver()) {
                _labelText->textColor(_activeColor->getHex());
            } else {
                _labelText->textColor(_overColor->getHex());
            }
        } else {
            if(isMouseOver()) {
                _labelText->textColor(_activeColor->getHex());
            } else {
                _labelText->textColor(0xffffff);
            }
        }
        
        if(dispatch) {
            dispatchEvent(new Event(Event::CHANGE));
            dispatchEvent(new RadioButtonEvent(RadioButtonEvent::CHANGE));
        }
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void RadioButton::_drawGraphics(const ofFloatColor& outerColor, const ofFloatColor* innerColor) {
        Graphics* g = graphics();
        g->clear();
        
        //ヒットエリア
        g->beginFill(0xff0000, 0.0);
        g->drawRect(0, 0, 6 + _labelText->x() + _labelText->width(), 15);
        g->endFill();
        
        //外側
        g->lineStyle(2, outerColor.getHex());
        g->drawCircle(7, 7.5, 6);
        g->endFill();
        
        //内側
        if(innerColor == NULL) return;
        g->beginFill(innerColor->getHex());
        g->drawCircle(7, 7.5, 3);
        g->endFill();
    }

    //--------------------------------------------------------------
    //
    void RadioButton::_over() {
        if(_bSelected) {
            _drawGraphics(*_overColor, _activeColor);
        } else {
            _drawGraphics(*_overColor);
        }
        
        _labelText->textColor(_activeColor->getHex());
    }

    //--------------------------------------------------------------
    //
    void RadioButton::_normal() {
        if(_bSelected) {
            _drawGraphics(*_normalColor, _activeColor);
            _labelText->textColor(_overColor->getHex());
        } else {
            _drawGraphics(*_normalColor);
            _labelText->textColor(0xffffff);
        }
    }

    //--------------------------------------------------------------
    //
    void RadioButton::_press() {
        selected(!selected());
    }

    //==============================================================
    // EVENT HANDLER
    //==============================================================

    //--------------------------------------------------------------
    //
    void RadioButton::_mouseEventHandler(Event& event) {
        if(debug()) cout << "[RadioButton]_mouseEventHandler(" << ofToString(event.type()) << ")" << endl;
        
        if(event.type() == MouseEvent::MOUSE_OVER) {
            if(event.target() == this) _over();
        }
        if(event.type() == MouseEvent::MOUSE_OUT) {
            if(event.target() == this) _normal();
        }
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            if(event.target() == this) _press();
        }
        if(event.type() == MouseEvent::MOUSE_UP) {
            //if(event.target() == this) _normal();
        }
    }

}