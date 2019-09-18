#include "flCheckBox.h"

namespace fl2d {
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flCheckBox::flCheckBox(float width) {
        _target = this;
        name("flCheckBox");
        
        buttonMode(true);
        mouseChildren(false);
        
        _uiWidth = width;
        _uiHeight = 18;
        
        _labelNormalColor.setHex(flDefinition::UI_LABEL_NORMAL_COLOR);
        _labelOverColor.setHex(flDefinition::UI_LABEL_OVER_COLOR);
        _labelActiveColor.setHex(flDefinition::UI_LABEL_ACTIVE_COLOR);
        _labelDeactiveColor.setHex(flDefinition::UI_LABEL_DEACTIVE_COLOR);
        
        _lineColor.setHex(flDefinition::UI_LINE_COLOR);
        _normalColor.setHex(flDefinition::UI_NORMAL_COLOR);
        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
        _deactiveColor.setHex(flDefinition::UI_DEACTIVE_COLOR);
        
        _selected = false;
        
        //------------------------------------------
        _label = new flTextField();
        _label->x(15);
        _label->autoSize(flTextFieldAutoSize::LEFT);
        _label->textColor(_labelNormalColor.getHex());
        _label->text("Check Box");
        _label->y(floor(_uiHeight * 0.5 - _label->textHeight() * 0.5) - 1);
        //        _label->mouseEnabled(false);
        addChild(_label);
        //------------------------------------------
        
        //flGraphics* g = graphics();
        //g->enabledSmoothing(true);
        
        //------------------------------------------
        _normal();
        //------------------------------------------
        
        addEventListener(flMouseEvent::MOUSE_OVER, this, &flCheckBox::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_OUT, this, &flCheckBox::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flCheckBox::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
        
        _enabled = true;
        
        //        _hitAreaAlpha = 0.5;
    }
    
    //--------------------------------------------------------------
    //
    flCheckBox::~flCheckBox() {
        removeEventListener(flMouseEvent::MOUSE_OVER, this, &flCheckBox::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_OUT, this, &flCheckBox::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flCheckBox::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
        
        delete _label;
        _label = NULL;
        
        _enabled = false;
        _hitAreaAlpha = 0.0;
        
        _shapeType = 0;
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flTextField* flCheckBox::label() { return _label; }
    
    //--------------------------------------------------------------
    //
    string flCheckBox::labelText() { return _label->text(); }
    void flCheckBox::labelText(string value) {
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
    bool flCheckBox::selected() { return _selected; }
    void flCheckBox::selected(bool value, bool dispatch) {
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
            dispatchEvent(new flEvent(flEvent::CHANGE));
            dispatchEvent(new flCheckBoxEvent(flCheckBoxEvent::CHANGE));
        }
    }
    
    //--------------------------------------------------------------
    //
    bool flCheckBox::enabled() { return _enabled; }
    void flCheckBox::enabled(bool value) {
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
        
        //        flGraphics* g;
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
    void flCheckBox::_drawGraphics(const ofFloatColor& outerColor) {
        flGraphics* g = graphics();
        g->clear();
        
        //ヒットエリア
        g->beginFill(0xff0000, _hitAreaAlpha);
        g->drawRect(0, 0, 6 + _label->x() + _label->width(), 15);
        g->endFill();
        
        //外側
        g->lineStyle(1, outerColor.getHex());
        switch(_shapeType) {
//            case 0: g->drawRect(0, 0, 18, 18); break;
            case 0: g->drawRect(1, 3, 12, 12); break;
            case 1: g->drawCircle(7, 8, 6); break;
        }
        g->endFill();
    }
    
    void flCheckBox::_drawGraphics(const ofFloatColor& outerColor, const ofFloatColor& innerColor) {
        flGraphics* g = graphics();
        g->clear();
        
        //ヒットエリア
        g->beginFill(0xff0000, _hitAreaAlpha);
        g->drawRect(0, 0, 6 + _label->x() + _label->width(), 15);
        g->endFill();
        
        //外側
        g->lineStyle(1, outerColor.getHex());
        switch(_shapeType) {
//            case 0: g->drawRect(0, 0, 18, 18); break;
            case 0: g->drawRect(1, 3, 12, 12); break;
            case 1: g->drawCircle(7, 8, 6); break;
        }
        g->endFill();
        
        //内側
        g->beginFill(innerColor.getHex());
        switch(_shapeType) {
//            case 0: g->drawRect(4, 3, 11, 11); break;
            case 0: g->drawRect(3, 4, 9, 9); break;
            case 1: g->drawCircle(7, 8, 3); break;
        }
        g->endFill();
    }
    
    //--------------------------------------------------------------
    //
    void flCheckBox::_over() {
        if(_selected) {
            _drawGraphics(_overColor, _activeColor);
        } else {
            _drawGraphics(_overColor);
        }
        
        _label->textColor(_labelOverColor.getHex());
    }
    
    //--------------------------------------------------------------
    //
    void flCheckBox::_normal() {
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
    void flCheckBox::_press() {
        selected(!selected());
    }
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flCheckBox::_mouseEventHandler(flEvent& event) {
        if(debug()) cout << "[flCheckBox]_mouseEventHandler(" << ofToString(event.type()) << ")" << endl;
        
        if(event.type() == flMouseEvent::MOUSE_OVER) {
            if(event.target() == this) _over();
        }
        if(event.type() == flMouseEvent::MOUSE_OUT) {
            if(event.target() == this) _normal();
        }
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) _press();
        }
        if(event.type() == flMouseEvent::MOUSE_UP) {
            //if(event.target() == this) _normal();
        }
    }
    
}
