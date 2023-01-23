﻿#include "flButton.h"

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
        
        //------------------------------------------
        addEventListener(flMouseEvent::ROLL_OVER, this, &flButton::_mouseEventHandler);
        addEventListener(flMouseEvent::ROLL_OUT, this, &flButton::_mouseEventHandler);
        addEventListener(flMouseEvent::MOUSE_DOWN, this, &flButton::_mouseEventHandler);
        //addEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
        //------------------------------------------

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
    }
    
    //--------------------------------------------------------------
    flButton::~flButton() {
//        ofLog() << "[flButton]~flButton()";
        
		if (stage() && stage()->hasEventListener(flMouseEvent::MOUSE_UP)) {
			stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
		}

        removeEventListener(flMouseEvent::ROLL_OVER, this, &flButton::_mouseEventHandler);
        removeEventListener(flMouseEvent::ROLL_OUT, this, &flButton::_mouseEventHandler);
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flButton::_mouseEventHandler);
        //removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
        
		//_label = NULL;

		if (_buttonLabel != NULL) {
			if (contains(_buttonLabel)) removeChild(_buttonLabel);
			delete _buttonLabel;
			_buttonLabel = NULL;
		}
        
        _pointerValue = NULL;
        
        //------------------------------------------
        _boolParam = NULL;
        _listeners.unsubscribeAll();
        //------------------------------------------
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flButton::_setup() {
        //ofLog() << "[flButton]setup()";
    }
    
    //--------------------------------------------------------------
    void flButton::_update() {
        flUIBase::_update();

		if (!_toggleEnabled) {
			if (_boolParam) {
				if (_bChangedByMyself["value"]) _boolParam->setWithoutEventNotifications(false);
			}
		}
		_bChangedByOfParm["value"] = false;
		_bChangedByMyself["value"] = false;
    }
    
    //--------------------------------------------------------------
    void flButton::_draw() {
        if(_flg) {
            _flg = false;
            if(isMouseOver()) {
                _setOverColor();
            } else {
                _setNormalColor();
            }
        }
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
	//--------------------------------------------------------------
	flDisplayObject* flButton::stage() { return _stage; }
	void flButton::stage(flDisplayObject* value) {
		//cout << "[flButton]stage(" << value << ")" << name() << endl;

		//今までステージへの参照がもっていなくてvalueにステージへの参照が入る時
		if (!_stage && value) {
			_stage = value;

			flEvent* event = new flEvent(flEvent::ADDED_TO_STAGE);
			//            event->target(_target);
			//            event->_target = _target;
			dispatchEvent(event);
		}
		//既にステージへの参照がもっていてvalueにステージへの参照がなくなる時
		if (_stage && !value) {
			if (_stage->hasEventListener(flMouseEvent::MOUSE_UP)) {
				_stage->removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
			}

			_stage = value;

			flEvent* event = new flEvent(flEvent::REMOVED_FROM_STAGE);
			//            event->target(_target);
			dispatchEvent(event);
		}
	}

    //--------------------------------------------------------------
    void flButton::label(flTextField* value) {
        _label = value;
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }

    //--------------------------------------------------------------
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
	ofParameter<bool>& flButton::selected() { return _selected; }
    void flButton::selected(bool value, bool dispatch) {
        if(_selected == value) return;

        if(!value) {
            _buttonLabel->text(_labelTextNotSelected);
        } else {
            _buttonLabel->text(_labelTextSelected);
        }

        if(_enabled) {
            if(value) {
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
            if(!value) {
                _setDisableNormalColor();
            } else {
                _setDisableActiveColor();
            }
        }

        //------------------------------------------
        if(dispatch) {
			_selected.set(value);

//            dispatchEvent(new flEvent(flEvent::CHANGE));
            flButtonEvent* event = new flButtonEvent(flButtonEvent::CHANGE);
            dispatchEvent(event);
		}
		else {
			_selected.setWithoutEventNotifications(value);
		}

		if (!_bChangedByOfParm["value"]) {
			if (_boolParam != NULL) {
				_bChangedByMyself["value"] = true;
				_boolParam->set(_selected);
			}
		}
        //------------------------------------------
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
    void flButton::down(bool dispatch) {
        //ofLog() << "[flButton]down()";
        if(_toggleEnabled) {
            selected(!selected());
        } else {
            _setActiveColor();
            _flg = true;
        }
        
        //------------------------------------------
        if(dispatch) {
            flButtonEvent* event = new flButtonEvent(flButtonEvent::MOUSE_DOWN);
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
//    //--------------------------------------------------------------
//    void flButton::_changeValue(bool dispatch) {
//        //------------------------------------------
//        if(_boolParam != NULL) {
//            _bChangedByMyself["value"] = true;
////            _boolParam->set(_value);
//        }
//        //------------------------------------------
//
//        //------------------------------------------
//        //イベント
//        if(dispatch) {
//            flButtonEvent* event = new flButtonEvent(flButtonEvent::CHANGE);
//            dispatchEvent(event);
//        }
//        //------------------------------------------
//    }
    
    //--------------------------------------------------------------
    void flButton::_onOver() {
        if(isMouseDown()) return;
        
        if(!_selected) {
            _setOverColor();
        } else {
            _setSelectedOverColor();
        }
        
        //------------------------------------------
        flButtonEvent* event = new flButtonEvent(flButtonEvent::ROLL_OVER);
        dispatchEvent(event);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flButton::_onOut() {
        if(isMouseDown()) return;
        
        if(!_selected) {
            _setNormalColor();
        } else {
            _setActiveColor();
        }
        
        //------------------------------------------
        flButtonEvent* event = new flButtonEvent(flButtonEvent::ROLL_OUT);
        dispatchEvent(event);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    void flButton::_onPress() {
        if(_toggleEnabled) {
            selected(!selected());

			//------------------------------------------
			if (!_bChangedByOfParm["value"]) {
				if (_boolParam != NULL) {
					_bChangedByMyself["value"] = true;
					_boolParam->set(_selected);
				}
			}
			//------------------------------------------
        } else {
            _setActiveColor();

			//------------------------------------------
			if (!_bChangedByOfParm["value"]) {
				if (_boolParam != NULL) {
					_bChangedByMyself["value"] = true;
					_boolParam->set(true);
				}
			}
			//------------------------------------------
        }
        
        flButtonEvent* event = new flButtonEvent(flButtonEvent::MOUSE_DOWN);
        dispatchEvent(event);
    }
    
    //--------------------------------------------------------------
    void flButton::_onRelease() {
        if(!_selected) {
            if(isMouseOver()) {
                _setOverColor();
            } else {
                _setNormalColor();
            }
            
            //------------------------------------------
            flButtonEvent* event = new flButtonEvent(flButtonEvent::MOUSE_UP);
            dispatchEvent(event);
            
            if(isMouseOver()) {
                flButtonEvent* event = new flButtonEvent(flButtonEvent::CLICK);
                dispatchEvent(event);
            }
            //------------------------------------------
        } else {
            if(isMouseOver()) {
                _setSelectedOverColor();
            } else {
                _setActiveColor();
            }
            
            //------------------------------------------
            flButtonEvent* event = new flButtonEvent(flButtonEvent::MOUSE_UP);
            dispatchEvent(event);
            //------------------------------------------
        }
    }
    
    //--------------------------------------------------------------
    void flButton::_setNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _buttonLabel->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_BORDER_NORMAL_COLOR, flDefinition::UI_NORMAL_COLOR);

		for (auto& child : _children) {
			if (flUtil::isSprite(child)) {
				flGraphics* g = ((flSprite*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_NORMAL_COLOR.getHex());
				}
			}	
			if (flUtil::isShape(child)) {
				flGraphics* g = ((flShape*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_NORMAL_COLOR.getHex());
				}
			}
		}
	}
    
    //--------------------------------------------------------------
    void flButton::_setOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_BORDER_OVER_COLOR, flDefinition::UI_OVER_COLOR);

		for (auto& child : _children) {
			if (flUtil::isSprite(child)) {
				flGraphics* g = ((flSprite*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_OVER_COLOR.getHex());
				}
			}
			if (flUtil::isShape(child)) {
				flGraphics* g = ((flShape*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_OVER_COLOR.getHex());
				}
			}
		}
	}
    
    //--------------------------------------------------------------
    void flButton::_setSelectedOverColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_OVER_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_OVER_COLOR);
        
        _drawGraphics(flDefinition::UI_BORDER_OVER_COLOR, flDefinition::UI_OVER_COLOR);

		for (auto& child : _children) {
			if (flUtil::isSprite(child)) {
				flGraphics* g = ((flSprite*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_OVER_COLOR.getHex());
				}
			}
			if (flUtil::isShape(child)) {
				flGraphics* g = ((flShape*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_OVER_COLOR.getHex());
				}
			}
		}
	}
    
    //--------------------------------------------------------------
    void flButton::_setActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_ACTIVE_COLOR);
        
        _drawGraphics(flDefinition::UI_BORDER_ACTIVE_COLOR, flDefinition::UI_ACTIVE_COLOR);

		for (auto& child : _children) {
			if (flUtil::isSprite(child)) {
				flGraphics* g = ((flSprite*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_ACTIVE_COLOR.getHex());
				}
			}
			if (flUtil::isShape(child)) {
				flGraphics* g = ((flShape*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_ACTIVE_COLOR.getHex());
				}
			}
		}
	}
    
    //--------------------------------------------------------------
    void flButton::_setDisableNormalColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        
        _drawGraphics(flDefinition::UI_BORDER_DISABLE_NORMAL_COLOR, flDefinition::UI_DISABLE_NORMAL_COLOR);

		for (auto& child : _children) {
			if (flUtil::isSprite(child)) {
				flGraphics* g = ((flSprite*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR.getHex());
				}
			}
			if (flUtil::isShape(child)) {
				flGraphics* g = ((flShape*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR.getHex());
				}
			}
		}
	}
    
    //--------------------------------------------------------------
    void flButton::_setDisableActiveColor() {
        if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);

        _buttonLabel->textColor(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR);
        
        _drawGraphics(flDefinition::UI_BORDER_DISABLE_ACTIVE_COLOR, flDefinition::UI_DISABLE_ACTIVE_COLOR);

		for (auto& child : _children) {
			if (flUtil::isSprite(child)) {
				flGraphics* g = ((flSprite*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR.getHex());
				}
			}
			if (flUtil::isShape(child)) {
				flGraphics* g = ((flShape*)child)->graphics();
				if (g) {
					g->color(flDefinition::UI_LABEL_DISABLE_ACTIVE_COLOR.getHex());
				}
			}
		}
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
    // Protected / Private Event Handler
    //==============================================================

	//--------------------------------------------------------------
	void flButton::_eventHandler(flEvent& event) {
		//ofLog() << "[flButton]_eventHandler(" << event.type() << ")";
		//ofLog() << "[flButton]this          = " << this << "," << ((flDisplayObject*)this)->name();
		//ofLog() << "[flButton]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*)event.currentTarget())->name();
		//ofLog() << "[flButton]target        = " << event.target() << "," << ((flDisplayObject*)event.target())->name();


	}

    //--------------------------------------------------------------
    void flButton::_mouseEventHandler(flEvent& event) {
        if(!_enabled) return;
		//ofLog() << "[flButton]_mouseEventHandler(" << event.type() << ")";
		//ofLog() << "[flButton]this          = " << this << "," << ((flDisplayObject*)this)->name();
		//ofLog() << "[flButton]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*)event.currentTarget())->name();
		//ofLog() << "[flButton]target        = " << event.target() << "," << ((flDisplayObject*)event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() == this) _onOver();
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() == this) _onOut();
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
			if (event.target() == this) {
				//addEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
				if (stage()) {
					stage()->addEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
				}
				_onPress();
			}
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
//            removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
            if(stage()) {
                stage()->removeEventListener(flMouseEvent::MOUSE_UP, this, &flButton::_mouseEventHandler);
            }
            _onRelease();
        }
    }
    
}
