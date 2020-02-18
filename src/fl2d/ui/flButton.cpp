#include "flButton.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flButton::flButton(float width, float height) {
//        ofLog() << "[flButton]flButton()";
        
        _target = this;
        name("flButton");
        
        buttonMode(true);
        mouseChildren(false);

        _uiWidth = width;
        _uiHeight = height;
        
        _toggleEnabled = false;
        _selected = false;

        _labelTextNotSelected = "";
        _labelTextSelected = "";
        
        //------------------------------------------
        _buttonLabel = new flTextField();
        _buttonLabel->x(0);
        _buttonLabel->width(_uiWidth);
        _buttonLabel->autoSize(flTextFieldAutoSize::CENTER);
        _buttonLabel->text("Button");
        _buttonLabel->y(floor(_uiHeight * 0.5 - _buttonLabel->textHeight() * 0.5));
        _buttonLabel->mouseEnabled(false);
        addChild(_buttonLabel);
        //------------------------------------------

        _setNormalColor();

        _pointerValue = NULL;
        _stringValue = "";
        _floatValue = 0.0;
        _intValue = 0;
        
        addEventListener(flMouseEvent::ROLL_OVER, this, &flButton::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flButton::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flButton::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
    }
    
    //--------------------------------------------------------------
    flButton::~flButton() {
//        ofLog() << "[flButton]~flButton()";
        
        removeEventListener(flMouseEvent::ROLL_OVER, this, &flButton::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flButton::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flButton::_mouseEventHandler);
        //removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
        
        delete _buttonLabel;
        _buttonLabel = NULL;
        
        _toggleEnabled = false;
        _selected = false;
        
        _pointerValue = NULL;
        _stringValue = "";
        _floatValue = 0.0;
        _intValue = 0;
        
        _labelTextNotSelected = "";
        _labelTextSelected = "";
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    flTextField* flButton::label() { return _label; }
    void flButton::label(flTextField* value) { _label = value; }

    //--------------------------------------------------------------
    string flButton::labelText() { return _buttonLabel->text(); }
    void flButton::labelText(string value, string state) {
        if(state == "default") {
            _labelTextNotSelected = value;
            _labelTextSelected = value;
        }
        else if(state == "selected") {
			_labelTextSelected = value;
        }
        else if(state == "notSelected") {
			_labelTextNotSelected = value;
		}
        
        if(_selected) {
            _buttonLabel->text(_labelTextSelected);
        } else {
            _buttonLabel->text(_labelTextNotSelected);
        }
        
        _updateRect();
    }
    
    //--------------------------------------------------------------
    bool flButton::toggleEnabled() { return _toggleEnabled; }
    void flButton::toggleEnabled(bool value) { _toggleEnabled = value; }
    
    //--------------------------------------------------------------
    bool flButton::selected() { return _selected; }
    void flButton::selected(bool value, bool dispatch) {
        if(_selected == value) return;
        _selected = value;

        if(!_selected) {
            _buttonLabel->text(_labelTextNotSelected);
        } else {
            _buttonLabel->text(_labelTextSelected);
        }
        
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
        
        if(dispatch) {
            dispatchEvent(new flEvent(flEvent::CHANGE));
            dispatchEvent(new flButtonEvent(flButtonEvent::CHANGE));
        }
    }
    
    //--------------------------------------------------------------
    void* flButton::pointerValue() { return _pointerValue; }
    void flButton::pointerValue(void* value) { _pointerValue = value; }
    
    //--------------------------------------------------------------
    string flButton::stringValue() { return _stringValue; }
    void flButton::stringValue(string value) { _stringValue = value; }
    
    //--------------------------------------------------------------
    float flButton::floatValue() { return _floatValue; }
    void flButton::floatValue(float value) { _floatValue = value; }
    
    //--------------------------------------------------------------
    int flButton::intValue() { return _intValue; }
    void flButton::intValue(int value) { _intValue = value; }
    
    //--------------------------------------------------------------
    bool flButton::enabled() { return _enabled; }
    void flButton::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);

        if(!_selected) {
            _buttonLabel->text(_labelTextNotSelected);
        } else {
            _buttonLabel->text(_labelTextSelected);
        }
        
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
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flButton::_over() {
        if(isMouseDown()) return;
        
        if(!_selected) {
            _setOverColor();
        } else {
            _setSelectedOverColor();
        }
        
        dispatchEvent(new flButtonEvent(flButtonEvent::ROLL_OVER));
    }
    
    //--------------------------------------------------------------
    void flButton::_out() {
        if(isMouseDown()) return;
        
        if(!_selected) {
            _setNormalColor();
        } else {
            _setActiveColor();
        }
        
        dispatchEvent(new flButtonEvent(flButtonEvent::ROLL_OUT));
    }
    
    //--------------------------------------------------------------
    void flButton::_press() {
        if(_toggleEnabled) {
            selected(!selected());
        } else {
            _setActiveColor();
        }
        
        dispatchEvent(new flButtonEvent(flButtonEvent::MOUSE_DOWN));
        
        if(_toggleEnabled) {
            dispatchEvent(new flEvent(flEvent::CHANGE));
            dispatchEvent(new flButtonEvent(flButtonEvent::CHANGE));
        }
    }
    
    //--------------------------------------------------------------
    void flButton::_release() {
        if(!_selected) {
            if(isMouseOver()) {
                _setOverColor();
                dispatchEvent(new flButtonEvent(flButtonEvent::MOUSE_UP));
                dispatchEvent(new flButtonEvent(flButtonEvent::CLICK));
            } else {
                _setNormalColor();
                dispatchEvent(new flButtonEvent(flButtonEvent::MOUSE_UP));
            }
        } else {
            if(isMouseOver()) {
                _setSelectedOverColor();
                dispatchEvent(new flButtonEvent(flButtonEvent::MOUSE_UP));
            } else {
                _setActiveColor();
                dispatchEvent(new flButtonEvent(flButtonEvent::MOUSE_UP));
            }
        }
    }
    
    //--------------------------------------------------------------
    void flButton::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _buttonLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR);
    }
    
    //--------------------------------------------------------------
    void flButton::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR);
    }
    
    //--------------------------------------------------------------
    void flButton::_setSelectedOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR, flDefinition::UI_OVER_COLOR);
    }
    
    //--------------------------------------------------------------
    void flButton::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR);
    }
    
    //--------------------------------------------------------------
    void flButton::_setDisableNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR);
    }
    
    //--------------------------------------------------------------
    void flButton::_setDisableActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR);
    }
    
    //--------------------------------------------------------------
    void flButton::_drawGraphics(const ofColor& lineColor, const ofColor& fillColor, float thickness) {
        flGraphics* g = graphics();
        g->clear();
        g->lineStyle(thickness, lineColor.getHex());
        g->beginFill(fillColor.getHex(), fillColor.a / 255.0);
        g->drawRect(0, 0, _uiWidth, _uiHeight);
        g->endFill();
    }
    
    //==============================================================
    // Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flButton::_mouseEventHandler(flEvent& event) {
        if(!_enabled) return;
//        ofLog() << "[flButton]_mouseEventHandler(" << event.type() << ")";
//        ofLog() << "[flButton]this          = " << this << "," << ((DisplayObject*) this)->name();
//        ofLog() << "[flButton]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flButton]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) _over();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) _out();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) _press();
            addEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
            if(stage()) {
                stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
            }
            _release();
        }
    }
    
}
