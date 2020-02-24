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
        
        addEventListener(flMouseEvent::MOUSE_OVER, this, &flCheckBox::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_OUT, this, &flCheckBox::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flCheckBox::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);

        //------------------------------------------
        _label = new flTextField();
        _label->x(15);
        _label->autoSize(flTextFieldAutoSize::LEFT);
        _label->text("Check Box");
        _label->y(floor(_uiHeight * 0.5 - _label->textHeight() * 0.5) - 0);
        addChild(_label);
        //------------------------------------------
        
        _setNormalColor();
        
//        _showHitArea = true;
    }
    
    //--------------------------------------------------------------
    flCheckBox::~flCheckBox() {
        removeEventListener(flMouseEvent::MOUSE_OVER, this, &flCheckBox::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_OUT, this, &flCheckBox::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flCheckBox::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
        
        delete _label;
        _label = NULL;
        
        _boolParam = NULL;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flCheckBox::_setup() {
        //ofLog() << "[flCheckBox]setup()";
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_update() {
        _bChangedByOfParm["value"] = false;
    }
    
    //--------------------------------------------------------------
    void flCheckBox::_draw() {
//        if(_flg) {
//            _flg = false;
//            if(isMouseOver()) {
//                _setOverColor();
//            } else {
//                _setNormalColor();
//            }
//        }
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flCheckBox::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }

    //--------------------------------------------------------------
    void flCheckBox::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        
        if(_enabled) {
            if(_selected) {
                if(isMouseOver()) {
                    _setOverColor();
                } else {
                    _setActiveColor();
                }
            } else {
                if(isMouseOver()) {
                    _setSelectedOverColor();
                } else {
                    _setNormalColor();
                }
            }
        } else {
            if(!_selected) {
                _setDisableNormalColor();
            } else {
                _setDisableActiveColor();
            }
        }
    }
    
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
        
        //------------------------------------------
        _changeValue(dispatch);
        
        if(!_bChangedByOfParm["value"]) {
            if(_boolParam != NULL) {
                _bChangedByMyself["value"] = true;
                _boolParam->set(_selected);
            }
        }
        //------------------------------------------
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flCheckBox::_changeValue(bool dispatch) {
        //------------------------------------------
        if(dispatch) {
            flCheckBoxEvent* event = new flCheckBoxEvent(flCheckBoxEvent::CHANGE);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
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
        
        //------------------------------------------
        if(!_bChangedByOfParm["value"]) {
            if(_boolParam != NULL) {
                _bChangedByMyself["value"] = true;
                _boolParam->set(_selected);
            }
        }
        //------------------------------------------
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
            case 0:
                g->enabledSmoothing(false);
                g->drawRect(1, 3, 12, 12);
                break;
            case 1:
                g->enabledSmoothing(true);
                g->drawCircle(7, 9, 7);
                break;
        }
//        g->drawRect(1, 3, 12, 12);
//        g->drawCircle(8, 9, 7);
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
            case 0:
                g->enabledSmoothing(false);
                g->drawRect(1, 3, 12, 12);
                break;
            case 1:
                g->enabledSmoothing(true);
                g->drawCircle(7, 9, 7);
                break;
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
            case 1: g->drawCircle(7, 9, 4); break;
        }
        g->endFill();
    }

    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flCheckBox::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flCheckBox]_mouseEventHandler(" << ofToString(event.type()) << ")";
        
        //Mouse Over
        if(event.type() == flMouseEvent::MOUSE_OVER) {
            if(event.target() == this) _over();
        }
        
        //Mouse Out
        if(event.type() == flMouseEvent::MOUSE_OUT) {
            if(event.target() == this) _out();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) {
                _press();
//                addEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
//            removeEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flCheckBox::_mouseEventHandler);
            }
            _release();
        }
    }
    
}
