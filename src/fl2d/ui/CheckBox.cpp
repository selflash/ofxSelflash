#include "CheckBox.h"

namespace fl2d {

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    CheckBox::CheckBox(float width) {
        _target = this;
        name("CheckBox");
        
        buttonMode(true);
        mouseChildren(false);

        _uiWidth = width;
        _uiHeight = 18;
        
        _labelNormalColor.setHex(FlashConfig::UI_LABEL_NORMAL_COLOR);
        _labelOverColor.setHex(FlashConfig::UI_LABEL_OVER_COLOR);
        _labelActiveColor.setHex(FlashConfig::UI_LABEL_ACTIVE_COLOR);
        _labelDeactiveColor.setHex(FlashConfig::UI_LABEL_DEACTIVE_COLOR);
        
        _lineColor.setHex(FlashConfig::UI_LINE_COLOR);
        _normalColor.setHex(FlashConfig::UI_NORMAL_COLOR);
        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);
        _deactiveColor.setHex(FlashConfig::UI_DEACTIVE_COLOR);
        
        _selected = false;
        
        //------------------------------------------
        _label = new TextField();
        _label->x(20);
        _label->autoSize(TextFieldAutoSize::LEFT);
        _label->textColor(_labelNormalColor.getHex());
        _label->text("Radio Button");
        _label->y(_uiHeight * 0.5 - _label->textHeight() * 0.5 - 3);
//        _label->mouseEnabled(false);
        addChild(_label);
        //------------------------------------------

        //Graphics* g = graphics();
        //g->enabledSmoothing(true);

        //------------------------------------------
        _normal();
        //------------------------------------------
        
        addEventListener(MouseEvent::MOUSE_OVER, this, &CheckBox::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_OUT, this, &CheckBox::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_DOWN, this, &CheckBox::_mouseEventHandler);
        addEventListener(MouseEvent::MOUSE_UP, this, &CheckBox::_mouseEventHandler);
        
        _enabled = true;
        
//        _hitAreaAlpha = 0.5;
    }

    //--------------------------------------------------------------
    //
    CheckBox::~CheckBox() {
        removeEventListener(MouseEvent::MOUSE_OVER, this, &CheckBox::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_OUT, this, &CheckBox::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_DOWN, this, &CheckBox::_mouseEventHandler);
        removeEventListener(MouseEvent::MOUSE_UP, this, &CheckBox::_mouseEventHandler);

        delete _label;
        _label = NULL;
        
        _enabled = false;
        _hitAreaAlpha = 0.0;
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================

    //--------------------------------------------------------------
    //
    TextField* CheckBox::label() { return _label; }
    
    //--------------------------------------------------------------
    //
    string CheckBox::labelText() { return _label->text(); }
    void CheckBox::labelText(string value) {
        _label->text(value);
        
        if(isMouseOver()) {
            _over();
        } else {
            _normal();
        }
        
        _updateRect();
    }

    //--------------------------------------------------------------
    //
    bool CheckBox::selected() { return _selected; }
    void CheckBox::selected(bool value, bool dispatch) {
        if(_selected == value) return;
        
        _selected = value;
        
//        if(_enabled) {
//            if(isMouseOver()){
//                _over();
//            } else {
//                _normal();
//            }
//            
//    //        if(_selected) {
//    //            if(isMouseOver()) {
//    //                _label->textColor(_labelOverColor);
//    //            } else {
//    //                _label->textColor(_labelNormalColor);
//    //            }
//    //        } else {
//    //            if(isMouseOver()) {
//    //                _label->textColor(_labelOverColor);
//    //            } else {
//    //                _label->textColor(_labelNormalColor);
//    //            }
//    //        }
//        }
        
        if(_enabled) {
//            _label->textColor(_labelNormalColor.getHex());
            
            if(_selected) {
                _label->textColor(_labelActiveColor.getHex());
                _drawGraphics(_lineColor, _activeColor);
            } else {
                _label->textColor(_labelNormalColor.getHex());
                _drawGraphics(_lineColor);
            }
        } else {
            _label->textColor(_labelDeactiveColor.getHex());
            
            if(_selected) {
                _drawGraphics(_labelDeactiveColor, _activeColor);
            } else {
                _drawGraphics(_labelDeactiveColor);
            }
        }
        
        
        if(dispatch) {
            dispatchEvent(new Event(Event::CHANGE));
            dispatchEvent(new CheckBoxEvent(CheckBoxEvent::CHANGE));
        }
    }

    //--------------------------------------------------------------
    //
    bool CheckBox::enabled() { return _enabled; }
    void CheckBox::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        
        if(_enabled) {
            _label->textColor(_labelNormalColor.getHex());
            
            if(_selected) {
                _drawGraphics(_lineColor, _activeColor);
            } else {
                _drawGraphics(_lineColor);
            }
        } else {
            _label->textColor(_labelDeactiveColor.getHex());
            
            if(_selected) {
                _drawGraphics(_labelDeactiveColor, _activeColor);
            } else {
                _drawGraphics(_labelDeactiveColor);
            }
        }
        
//        Graphics* g;
//        g = graphics();
//        g->clear();
//        g->lineStyle(1, _lineColor.getHex());
//        if(_enabled) {
//            g->beginFill(_normalColor.getHex());
//        } else {
//            g->beginFill(_deactiveColor.getHex());
//        }
//        g->drawRect(0, 0, _uiWidth, _uiHeight);
//        g->endFill();
    }

    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void CheckBox::_drawGraphics(const ofFloatColor& outerColor) {
        Graphics* g = graphics();
        g->clear();
        
        //ヒットエリア
        g->beginFill(0xff0000, _hitAreaAlpha);
        g->drawRect(0, 0, 6 + _label->x() + _label->width(), 15);
        g->endFill();
        
        //外側
        g->lineStyle(1, outerColor.getHex());
//        g->drawCircle(7, 8, 6);
        g->drawRect(0, 0, 15, 15);
        g->endFill();
    }
    
    void CheckBox::_drawGraphics(const ofFloatColor& outerColor, const ofFloatColor& innerColor) {
        Graphics* g = graphics();
        g->clear();
        
        //ヒットエリア
        g->beginFill(0xff0000, _hitAreaAlpha);
        g->drawRect(0, 0, 6 + _label->x() + _label->width(), 15);
        g->endFill();
        
        //外側
        g->lineStyle(1, outerColor.getHex());
//        g->drawCircle(7, 8, 6);
        g->drawRect(0, 0, 15, 15);
        g->endFill();
        
        //内側
        g->beginFill(innerColor.getHex());
//        g->drawCircle(7, 8, 3);
        g->drawRect(3, 3, 8, 8);
        g->endFill();
    }

    //--------------------------------------------------------------
    //
    void CheckBox::_over() {
        if(_selected) {
            _drawGraphics(_overColor, _activeColor);
        } else {
            _drawGraphics(_overColor);
        }
        
        _label->textColor(_labelOverColor.getHex());
    }

    //--------------------------------------------------------------
    //
    void CheckBox::_normal() {
        if(_selected) {
            _drawGraphics(_lineColor, _activeColor);
            _label->textColor(_overColor.getHex());
        } else {
            _drawGraphics(_lineColor);
            _label->textColor(_labelNormalColor.getHex());
        }
    }

    //--------------------------------------------------------------
    //
    void CheckBox::_press() {
        selected(!selected());
    }

    //==============================================================
    // EVENT HANDLER
    //==============================================================

    //--------------------------------------------------------------
    //
    void CheckBox::_mouseEventHandler(Event& event) {
        if(debug()) cout << "[CheckBox]_mouseEventHandler(" << ofToString(event.type()) << ")" << endl;
        
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
