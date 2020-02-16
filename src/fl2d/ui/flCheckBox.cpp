#include "flCheckBox.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flCheckBox::flCheckBox(float width) {
        _target = this;
        name("flCheckBox");
        
        buttonMode(true);
        mouseChildren(false);
        
        _uiWidth = width;
        _uiHeight = 18;
        
        _enabled = true;
        _selected = false;
        
        //------------------------------------------
        _label = new flTextField();
        _label->x(15);
        _label->autoSize(flTextFieldAutoSize::LEFT);
        _label->text("Check Box");
        _label->y(floor(_uiHeight * 0.5 - _label->textHeight() * 0.5) - 0);
        addChild(_label);
        //------------------------------------------
        
        _setNormalColor();

        addEventListener(flMouseEvent::MOUSE_OVER, this, &flCheckBox::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_OUT, this, &flCheckBox::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flCheckBox::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    flCheckBox::~flCheckBox() {
        removeEventListener(flMouseEvent::MOUSE_OVER, this, &flCheckBox::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_OUT, this, &flCheckBox::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flCheckBox::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
        
        delete _label;
        _label = NULL;
        
        _enabled = false;
        _selected = false;
        _hitAreaAlpha = 0.0;
        
        _shapeType = 0;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flCheckBox::label() { return _label; }
    
    //--------------------------------------------------------------
    string flCheckBox::labelText() { return _label->text(); }
    void flCheckBox::labelText(string value) {
        _label->text(value);
        _updateRect();
    }
    
    //--------------------------------------------------------------
    bool flCheckBox::selected() { return _selected; }
    void flCheckBox::selected(bool value, bool dispatch) {
        if(_selected == value) return;
        _selected = value;

        if(_enabled) {
            if(!_selected) {
                if(isMouseOver()) {
                    _setOverColor();
                } else {
                    _setNormalColor();
                }
            } else {
                if(isMouseOver()) {
                    _setSelectedOverColor();
                } else {
                    _setActiveColor();
                }
            }
        } else {
            if(!_selected) {
                _setDisableNormalColor();
            } else {
                _setDisableActiveColor();
            }
        }
        
        if(dispatch) {
            dispatchEvent(new flEvent(flEvent::CHANGE));
            dispatchEvent(new flCheckBoxEvent(flCheckBoxEvent::CHANGE));
        }
    }
    
    //--------------------------------------------------------------
    bool flCheckBox::enabled() { return _enabled; }
    void flCheckBox::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        
        if(_enabled) {
            if(_selected) {
                _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
                _drawGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR);
            } else {
                _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
                _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR);
            }
        } else {
            if(_selected) {
                _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
                _drawGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR);
            } else {
                _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
                _drawGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR);
            }
        }
        
        //        flGraphics* g;
        //        g = graphics();
        //        g->clear();
        //        g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
        //        if(_enabled) {
        //            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex());
        //        } else {
        //            g->beginFill(flDefinition::UI_NORMAL_COLOR.getHex());
        //        }
        //        g->drawRect(0, 0, _uiWidth, _uiHeight);
        //        g->endFill();
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flCheckBox::_over() {
        if(isMouseDown()) return;
        
        if(!_selected) {
            _setOverColor();
        } else {
            _setSelectedOverColor();
        }
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_out() {
        if(isMouseDown()) return;

        if(!_selected) {
            _setNormalColor();
        } else {
            _setActiveColor();
        }
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_press() {
        selected(!selected());
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_release() {
        if(!_selected) {
            if(isMouseOver()) {
                _setOverColor();
            } else {
                _setNormalColor();
            }
        } else {
            if(isMouseOver()) {
                _setSelectedOverColor();
            } else {
                _setActiveColor();
            }
        }
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_setNormalColor() {
        _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR);
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_setOverColor() {
        _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR.getHex());
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_setSelectedOverColor() {
        _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR);
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_setActiveColor() {
        _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR_2);
        _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_ACTIVE_COLOR);
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_setDisableNormalColor() {
        _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        _drawGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR);
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_setDisableActiveColor() {
        _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        _drawGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR);
    }

    //--------------------------------------------------------------
    void flCheckBox::_drawGraphics(const ofColor& outerColor) {
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
    
    //--------------------------------------------------------------
    void flCheckBox::_drawGraphics(const ofColor& outerColor, const ofFloatColor& innerColor) {
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
#ifdef __APPLE__
			case 0: g->drawRect(3, 4, 9, 9); break;
#elif defined _WIN32
			case 0: g->drawRect(3, 6, 7, 7); break;
#endif		
            case 1: g->drawCircle(7, 8, 3); break;
        }
        g->endFill();
    }

    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flCheckBox::_mouseEventHandler(flEvent& event) {
//        if(debug()) cout << "[flCheckBox]_mouseEventHandler(" << ofToString(event.type()) << ")" << endl;
        
        if(event.type() == flMouseEvent::MOUSE_OVER) {
            if(event.target() == this) _over();
        }
        if(event.type() == flMouseEvent::MOUSE_OUT) {
            if(event.target() == this) _out();
        }
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) _press();
            addEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
            if(stage()) {
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
            }
        }
        if(event.type() == flMouseEvent::MOUSE_UP) {
            removeEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
            }
            _release();
        }
    }
    
}
