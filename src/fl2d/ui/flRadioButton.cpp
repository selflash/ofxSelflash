#include "flRadioButton.h"

namespace fl2d {
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flRadioButton::flRadioButton(float width) {
        _target = this;
        name("flRadioButton");
        
        buttonMode(true);
        mouseChildren(false);
        
        _uiWidth = width;
        _uiHeight = 18;
        
        //------------------------------------------
//        flGraphics* g;
//        g = graphics();
//        g->clear();
//        g->lineStyle(1, flDefinition::UI_LINE_NORMAL_COLOR.getHex());
//        g->drawRect(0, 0, _uiWidth, _uiHeight);
//        g->endFill();
        //------------------------------------------
        
        addEventListener(flMouseEvent::MOUSE_OVER, this, &flRadioButton::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_OUT, this, &flRadioButton::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flRadioButton::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_UP, this, &flRadioButton::_mouseEventHandler);

        //------------------------------------------
        _label = new flTextField();
        _label->name("flRadioButton.label");
        _label->x(15);
        _label->autoSize(flTextFieldAutoSize::LEFT);
        _label->text("Radio Button");
        _label->y(floor(_uiHeight * 0.5 - _label->textHeight() * 0.5) - 0);
        addChild(_label);
        //------------------------------------------

        _groupOwner = NULL;
        
//        _hitAreaAlpha = 0.5;
//        hitAreaVisible(true);

        _setNormalColor();
        
    }
    
    //--------------------------------------------------------------
    flRadioButton::~flRadioButton() {
        removeEventListener(flMouseEvent::MOUSE_OVER, this, &flRadioButton::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_OUT, this, &flRadioButton::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flRadioButton::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_UP, this, &flRadioButton::_mouseEventHandler);
        
        delete _label;
        _label = NULL;
        
        if(_groupOwner != NULL) {
            _groupOwner->_notice(this, "remove");
        }
        _groupOwner = NULL;
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flRadioButton::_setup() {
        //ofLog() << "[flRadioButton]setup()";
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_update() {
        flUIBase::_update();

    }
    
    //--------------------------------------------------------------
    void flRadioButton::_draw() {
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
    void flRadioButton::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flRadioButton::enabled(bool value) {
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
    string flRadioButton::labelText() { return _label->text(); }
    void flRadioButton::labelText(string value) {
        _label->text(value);
        _updateRect();
    }
    
    //--------------------------------------------------------------
    bool flRadioButton::selected() { return _selected; }
    void flRadioButton::selected(bool value, bool dispatch) {
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
        if(dispatch) {
//            dispatchEvent(new flEvent(flEvent::CHANGE));
            flRadioButtonEvent* event = new flRadioButtonEvent(flRadioButtonEvent::CHANGE);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flRadioButton::_dispatchEvent() {
//        if(_boolParam != NULL) {
//            _changedValueByMyself = true;
//            //            _boolParam->set(_value);
//        }
        flRadioButtonEvent* event = new flRadioButtonEvent(flRadioButtonEvent::CHANGE);
        dispatchEvent(event);
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_onOver() {
        if(isMouseDown()) return;
        
        if(!_selected) {
            _setOverColor();
        } else {
            _setSelectedOverColor();
        }
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_onOut() {
        if(isMouseDown()) return;
        
        if(!_selected) {
            _setNormalColor();
        } else {
            _setActiveColor();
        }
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_onPress() {
        selected(!selected());
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_onRelease() {
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
    void flRadioButton::_setNormalColor() {
        _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR);
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_setOverColor() {
        _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR.getHex());
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_setSelectedOverColor() {
        _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        _drawGraphics(flDefinition::UI_LINE_OVER_COLOR.getHex(), flDefinition::UI_ACTIVE_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_setActiveColor() {
        _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR_2);
        _drawGraphics(flDefinition::UI_LINE_NORMAL_COLOR, flDefinition::UI_ACTIVE_COLOR);
        
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_setDisableNormalColor() {
        _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_LINE_DISABLE_NORMAL_COLOR);
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_setDisableActiveColor() {
//        _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        _label->textColor(flDefinition::UI_DISABLE_ACTIVE_COLOR);

        _drawGraphics(flDefinition::UI_LINE_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR);
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_drawGraphics(const ofColor& outerColor, float thickness) {
        flGraphics* g = graphics();
        g->clear();
        
        //ヒットエリア
        g->beginFill(0xff0000, _hitAreaAlpha);
        g->drawRect(0, 0, _uiWidth, _uiHeight);
//        g->drawRect(0, 0, 6 + _label->x() + _label->width(), 15);
        g->endFill();
        
        //外側
        g->lineStyle(thickness, outerColor.getHex());
        switch(_shapeType) {
//            case 0: g->drawRect(0, 0, 18, 18); break;
            case 0:
                g->enabledSmoothing(false);
                g->drawRect(1, 3, 12, 12);
                break;
//            case 1: g->drawCircle(7, 8, 6); break;
            case 1:
                g->enabledSmoothing(true);
                g->drawCircle(7, 9, 7);
                break;
        }
        g->endFill();
    }
    
    //--------------------------------------------------------------
    void flRadioButton::_drawGraphics(const ofColor& outerColor, const ofColor& innerColor, float thickness) {
        flGraphics* g = graphics();
        g->clear();
        
        //ヒットエリア
        g->beginFill(0xff0000, _hitAreaAlpha);
        g->drawRect(0, 0, _uiWidth, _uiHeight);
//        g->drawRect(0, 0, 6 + _label->x() + _label->width(), 15);
        g->endFill();
        
        //外側
        g->lineStyle(thickness, outerColor.getHex());
        switch(_shapeType) {
//            case 0: g->drawRect(0, 0, 18, 18); break;
            case 0:
                g->enabledSmoothing(false);
                g->drawRect(1, 3, 12, 12);
                break;
//            case 1: g->drawCircle(7, 8, 6); break;
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
            case 0: g->drawRect(3, 4, 9, 9); break;
//            case 1: g->drawCircle(7, 8, 3); break;
            case 1: g->drawCircle(7, 9, 4); break;
        }
        g->endFill();
    }

    //--------------------------------------------------------------
    void flRadioButton::_setGroupOwner(flRadioButtonGroup* groupOwner) {
        _groupOwner = groupOwner;
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flRadioButton::_mouseEventHandler(flEvent& event) {
//        ofLog() << "[flRadioButton]_mouseEventHandler(" << ofToString(event.type()) << ")";
        
        //Mouse Over
        if(event.type() == flMouseEvent::MOUSE_OVER) {
            if(event.target() == this) _onOver();
        }
        
        //Mouse Out
        if(event.type() == flMouseEvent::MOUSE_OUT) {
            if(event.target() == this) _onOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            if(event.target() == this) {
                _onPress();
                if(stage()) {
                    stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flRadioButton::_mouseEventHandler);
                }
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flRadioButton::_mouseEventHandler);
            }
            _onRelease();
        }
    }
    
    //--------------------------------------------------------------
    // Constructor / Destructor
    //--------------------------------------------------------------
    
    //--------------------------------------------------------------
    flRadioButtonGroup::flRadioButtonGroup() {
        
    }
    //--------------------------------------------------------------
    flRadioButtonGroup::~flRadioButtonGroup() {
        vector<flRadioButton*>::iterator it = _radioButtonList.begin();
        while (it != _radioButtonList.end()) {
            flRadioButton* radioButton = ((flRadioButton*)*it);
            radioButton->_setGroupOwner(NULL);
            radioButton->removeEventListener(flRadioButtonEvent::CHANGE, this, &flRadioButtonGroup::_uiEventHandler);
            it = _radioButtonList.erase(it);
        }
        _radioButtonList.clear();
    }
    
    //==============================================================
    // Public Method
    //==============================================================

    //--------------------------------------------------------------
    flRadioButton* flRadioButtonGroup::createRadioButton() {
        //ofLog() << "[flRadioButtonGroup]createRadioButton()";
        flRadioButton* radioButton = new flRadioButton();
        radioButton->_setGroupOwner(this);
        radioButton->toolTipEnabled(_toolTipEnabled);
        radioButton->toolTipText(_toolTipText);
        radioButton->addEventListener(flRadioButtonEvent::CHANGE, this, &flRadioButtonGroup::_uiEventHandler);
        _radioButtonList.push_back(radioButton);
        return radioButton;
    }
    
    //--------------------------------------------------------------
	flRadioButton* flRadioButtonGroup::removeRadioButton(flRadioButton* radioButton) {
        vector<flRadioButton*>::iterator it = _radioButtonList.begin();
        while (it != _radioButtonList.end()) {
            if (*it == radioButton) {
                flRadioButton* radioButton = ((flRadioButton*)*it);
                radioButton->_setGroupOwner(NULL);
                radioButton->removeEventListener(flRadioButtonEvent::CHANGE, this, &flRadioButtonGroup::_uiEventHandler);
                it = _radioButtonList.erase(it);
            } else ++it;
        }
        
        it = _radioButtonList.begin();
        while (it != _radioButtonList.end()) {
            ofLog() << *it << endl;
            ++it;
        }
        
        return radioButton;
    }
    
    //--------------------------------------------------------------
    bool flRadioButtonGroup::toolTipEnabled() { return _toolTipEnabled; }
    void flRadioButtonGroup::toolTipEnabled(bool value) {
        _toolTipEnabled = value;
        
        vector<flRadioButton*>::iterator it = _radioButtonList.begin();
        while (it != _radioButtonList.end()) {
            flRadioButton* radioButton = ((flRadioButton*)*it);
            radioButton->toolTipEnabled(_toolTipEnabled);
        }
    }

    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flRadioButtonGroup::_notice(flRadioButton* radioButton, string message) {
        if(message == "remove") {
            removeRadioButton(radioButton);
        }
        
//        ofLog() << "_radioButtonList.size = " << _radioButtonList.size();
    }

    //==============================================================
    // Protected / Private Event Handler
    //==============================================================

    //--------------------------------------------------------------
    void flRadioButtonGroup::_uiEventHandler(flEvent& event) {
        //ofLog() << "[flRadioButtonGroup]_uiEventHandler()";
        flRadioButtonEvent& radioButtonEvent = *(flRadioButtonEvent*) &event;
        flRadioButton* radio = (flRadioButton*)(event.currentTarget());
        
        if(radio->selected()) {
            for(auto& b : _radioButtonList) {
                if(b != radio) {
                    b->selected(false);
                }
            }
        }
    }
    
}
