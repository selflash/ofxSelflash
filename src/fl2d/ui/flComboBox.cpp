#include "flComboBox.h"

namespace fl2d {
    //水平
    string flComboBox::DROPDOWNLIST_UP = "up";
    //垂直
    string flComboBox::DROPDOWNLIST_DOWN = "down";
    
    //==============================================================
    // Constructor / Destructor
    //==============================================================
    
    //--------------------------------------------------------------
    flComboBox::flComboBox(float dropdownWidth) {
        //ofLog() << "[flComboBox]flComboBox()";
        
        _target = this;
        name("flComboBox");
        
        _dropdownWidth = dropdownWidth;
        
        //------------------------------------------
        //ボタン
        _topButton = new flButton(_dropdownWidth);
        _topButton->name("flComboBox.topButton");
        _topButton->labelText("");
        _topButton->x(0);
        _topButton->y(0);
        _topButton->toggleEnabled(true);
        _topButton->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flComboBox::_mouseEventHandler);
        _topButton->addEventListener(flFocusEvent::FOCUS_OUT, this, &flComboBox::_eventHandler);
        addChild(_topButton);
        
        _buttonContainer = new flSprite();
        _buttonContainer->name("flComboBox.buttonContainer");
        _buttonContainer->x(0);
        _buttonContainer->y(18);
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    flComboBox::~flComboBox() {
        //ofLog() << "[flComboBox]~flComboBox()";
        
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flComboBox::_mouseEventHandler);
        
        _dropdownWidth = 0;
        _rowCount = 0;
        
        _selectedIndex = 0;
        
        //------------------------------------------
        //ボタン
		if (_topButton != NULL) {
			_topButton->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flComboBox::_mouseEventHandler);
			_topButton->removeEventListener(flFocusEvent::FOCUS_OUT, this, &flComboBox::_eventHandler);
			if (contains(_topButton)) removeChild(_topButton);
			delete _topButton;
			_topButton = NULL;
		}

		if (_buttonContainer != NULL) {
			if (contains(_buttonContainer)) removeChild(_buttonContainer);
			delete _buttonContainer;
			_buttonContainer = NULL;
		}
        
        _buttonList.clear();
        _selectedButton = NULL;
        //------------------------------------------
        
        //------------------------------------------
        //アイテム
        _itemList.clear();
        _selectedItem = NULL;
        //------------------------------------------
        
        _mode = "";
        
        _pointerValue = NULL;
        _stringValue = "";
        _floatValue = 0.0;
        _intValue = 0;
        
        //------------------------------------------
        _intParam = NULL;
        _listeners.unsubscribeAll();
        //------------------------------------------
    }
    
    //==============================================================
    // Setup / Update / Draw
    //==============================================================
    
    //--------------------------------------------------------------
    void flComboBox::_setup() {
        
    }
    
    //--------------------------------------------------------------
    void flComboBox::_update() {
        flUIBase::_update();

        _bChangedByOfParm["value"] = false;
    }
    
    //--------------------------------------------------------------
    void flComboBox::_draw() {
        
    }
    
    //==============================================================
    // Public Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flComboBox::label(flTextField* value) {
        _label = value;
        
        int i; int l;
        l = _buttonList.size();
        for(i = 0; i < l; i++) {
            flButton* button = _buttonList[i];
            //button->label(_label);
        }
        
        //_topButton->label(_label);
        
        if (_label == NULL) return;
        
        if (_enabled) {
            _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
        }
    }
    
    //--------------------------------------------------------------
    void flComboBox::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        _topButton->enabled(_enabled);
        
        if(_enabled) {
            if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_NORMAL_COLOR);
        } else {
            if(_label != NULL) _label->textColor(flDefinition::UI_LABEL_DISABLE_NORMAL_COLOR);
            
            _topButton->selected(false);
            if(contains(_buttonContainer)) removeChild(_buttonContainer);
//            if(_topButton->isFocus()) { _topButton->focusOut(); }
        }
    }
    
    //--------------------------------------------------------------
//    void flComboBox::enabled(bool value) {
//        _enabled = value;
//        mouseEnabled(_enabled);
//        mouseChildren(_enabled);
//        
//        int i; int l;
//        l = _buttonList.size();
//        for(i = 0; i < l; i++) {
//            flButton* button = _buttonList[i];
//            button->enabled(_enabled);
//        }
//    }
    
    //--------------------------------------------------------------
    void flComboBox::removeItemByIndex(int index) {
        //--------------------------------------
        //_children()の箇所はリファクタリングとかで外に出したらダメ
        if(index < 0 || index > _buttonList.size() - 1) return;
        
        flButton* button = _buttonList[index];
        button->removeEventListener(flMouseEvent::ROLL_OVER, this, &flComboBox::_mouseEventHandler);
        button->removeEventListener(flMouseEvent::ROLL_OUT, this, &flComboBox::_mouseEventHandler);
        button->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flComboBox::_mouseEventHandler);
        //                button->removeAllEventListener();
        _buttonContainer->removeChild(button);
        delete button;
        _buttonList.erase(_buttonList.begin() + index);
        //--------------------------------------
        
        //--------------------------------------
        int l = _buttonList.size();
        for(int i = 0; i < l; i++) {
            flButton* button = _buttonList[i];
            button->setProperty<int>("index", i);
            if(_mode == "down") button->y(18 * i);
            if(_mode == "up") button->y(18 * i - (18 * l));
        }
        //--------------------------------------
        
        flGraphics* g;
        g = _buttonContainer->graphics();
        g->clear();
        g->beginFill(0x000000, 0.8);
        if(_mode == "down") {
            g->drawRect(0, 0, _dropdownWidth, 18 * _buttonList.size());
        }
        if(_mode == "up") {
            g->drawRect(0, 0, _dropdownWidth, -18 * _buttonList.size());
        }
        g->endFill();
        
        flObject* item = _itemList[index];
        delete item;
        _itemList.erase(_itemList.begin() + index);
        //--------------------------------------
        
        //--------------------------------------
        _selectedButton = NULL;
        _selectedItem = NULL;
        
        if(_buttonList.size() == 0) {
            _buttonList.clear();
            _itemList.clear();
            _topButton->labelText("");
            _selectedIndex = -1;
            _selectedItem = NULL;
        } else if(_selectedIndex == index) {
            if(index == 0) {
                selectedIndex(index);
            } else {
                selectedIndex(index - 1);
            }
        }
        //--------------------------------------
    }
    
    //--------------------------------------------------------------
    void flComboBox::mode(string value) {
        _mode = value;
        
        if(_mode == "down") {
            _buttonContainer->y(18 + 18);
            
            int l = _buttonList.size();
            for(int i = 0; i < l; i++) {
                flButton* button = _buttonList[i];
                button->y(18 * i);
            }
            
            flGraphics* g;
            g = _buttonContainer->graphics();
            g->clear();
            g->beginFill(0x000000, 0.8);
            g->drawRect(0, 0, _dropdownWidth, 18 * l);
            g->endFill();
        }
        if(_mode == "up") {
            _buttonContainer->y(18);
            
            int l = _buttonList.size();
            for(int i = 0; i < l; i++) {
                flButton* button = _buttonList[i];
                button->y(18 * i - (18 * l));
            }
            
            flGraphics* g;
            g = _buttonContainer->graphics();
            g->clear();
            g->beginFill(0x000000, 0.8);
            g->drawRect(0, 0, _dropdownWidth, -18 * l);
            g->endFill();
        }
    }
    
    //--------------------------------------------------------------
    void flComboBox::removeAllItems(bool dispatch) {
		if (!_buttonContainer) return;
		if (_buttonList.size() == 0) return;
		if (_itemList.size() == 0) return;

		if (contains(_buttonContainer)) removeChild(_buttonContainer);
        
        int i; int l;
        l = _buttonList.size();
        for(i = 0; i < l; i++) {
            flButton* button = _buttonList[i];
            button->removeEventListener(flMouseEvent::ROLL_OVER, this, &flComboBox::_mouseEventHandler);
            button->removeEventListener(flMouseEvent::ROLL_OUT, this, &flComboBox::_mouseEventHandler);
            button->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flComboBox::_mouseEventHandler);
            _buttonContainer->removeChild(button);
        }
        
        _buttonList.clear();
        _itemList.clear();
        
        flGraphics* g = _buttonContainer->graphics();
        g->clear();
        
        _topButton->labelText("");
        _selectedIndex = -1;
        _selectedItem = NULL;
        
        //------------------------------------------
		if (dispatch) {
			_dispatchEvent();
		}

		if (!_bChangedByOfParm["value"]) {
			if (_intParam != NULL) {
				_bChangedByMyself["value"] = true;
				_intParam->set(_selectedIndex);
			}
		}
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
	ofParameter<int>& flComboBox::selectedIndex() { return _selectedIndex; }
    void flComboBox::selectedIndex(int value, bool dispatch) {
        if(value < 0) value = 0;
        if(_itemList.size() - 1 <= value) value = _itemList.size() - 1;
        
		//------------------------------------------
        if(_selectedButton != NULL) {
            _selectedButton->selected(false);
            _selectedButton->alpha(0.7);
        }
        _selectedButton = _buttonList[value];
        
        _selectedItem = _itemList[value];
        
        //------------------------------------------
        _topButton->labelText(_selectedItem->getProperty<string>("label"));
        _topButton->selected(false);
		if (contains(_buttonContainer)) removeChild(_buttonContainer);
        //------------------------------------------
        
        //------------------------------------------
		if (dispatch) {
			_selectedIndex.set(value);

			_dispatchEvent();
		}
		else {
			_selectedIndex.setWithoutEventNotifications(value);
		}

        if(!_bChangedByOfParm["value"]) {
            if(_intParam != NULL) {
                _bChangedByMyself["value"] = true;
                _intParam->set(_selectedIndex);
            }
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    string flComboBox::selectedLabel() { return _selectedItem->getProperty<string>("label"); }
    
    //--------------------------------------------------------------
    int flComboBox::numItems() { return _itemList.size(); }
    
    //--------------------------------------------------------------
    void* flComboBox::pointerValue() { return _pointerValue; }
    void flComboBox::pointerValue(void* value) { _pointerValue = value; }
    
    //--------------------------------------------------------------
    string flComboBox::stringValue() { return _stringValue; }
    void flComboBox::stringValue(string value) { _stringValue = value; }
    
    //--------------------------------------------------------------
    float flComboBox::floatValue() { return _floatValue; }
    void flComboBox::floatValue(float value) { _floatValue = value; }
    
    //--------------------------------------------------------------
    int flComboBox::intValue() { return _intValue; }
    void flComboBox::intValue(int value) { _intValue = value; }
    
    //==============================================================
    // Protected / Private Method
    //==============================================================
    
    //--------------------------------------------------------------
    void flComboBox::_dispatchEvent() {
//            ofLog() << "DEBUG START ----- ";
//            flComboBoxEvent* event = new flComboBoxEvent(flComboBoxEvent::CHANGE);
//            flComboBoxEvent<float> event(flComboBoxEvent::CHANGE, 0.1f);

        flComboBoxEvent* event = new flComboBoxEvent(flComboBoxEvent::CHANGE);
//            ofLog() << "DEBUG END   ----- ";
//            event->__label = _selectedLabel;
//            event->__pointerValue = _selectedData;
//            event->__stringValue = _selectedText;
//            event->__floatValue = _selectedValue;
        dispatchEvent(event);
    }
    
    //==============================================================
    // Protected / Private Event Handler
    //==============================================================
    
    //--------------------------------------------------------------
    void flComboBox::_mouseEventHandler(flEvent& event) {
        ofLog() << "[flComboBox]_mouseEventHandler(" << event.type() << ")";
        ofLog() << "[flComboBox]this          = " << this << "," << ((flDisplayObject*) this)->name();
        ofLog() << "[flComboBox]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
        ofLog() << "[flComboBox]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
        //Roll Over
        if(event.type() == flMouseEvent::ROLL_OVER) {
            if(event.target() != this) {
                flButton* target = (flButton*) event.target();
//                _buttonContainer->addChild(target);
                target->alpha(1);
            }
        }
        
        //Roll Out
        if(event.type() == flMouseEvent::ROLL_OUT) {
            if(event.target() != this) {
                flButton* target = (flButton*) event.target();
                if(target != _selectedItem) target->alpha(0.7);
            }
        }
        
        //Mouse Down
        if(event.type() == flMouseEvent::MOUSE_DOWN) {
            flButton* target = (flButton*) event.target();
            if(target == _topButton) {
                if(_topButton->selected()){
                    addChild(_buttonContainer);
                    if(parent()) ((flDisplayObjectContainer*)parent())->addChild(this);
                } else {
                    removeChild(_buttonContainer);
                }
            } else {
				ofLog() << "Test1";
                //------------------------------------------
                if(_selectedButton) {
                    _selectedButton->selected(false);
                    _selectedButton->alpha(0.7);
                }
                _selectedButton = target;
                //------------------------------------------
                
                //------------------------------------------
                _selectedIndex = _selectedButton->getProperty<int>("index");
                _selectedItem = _itemList[_selectedIndex];
                //------------------------------------------
                
                //------------------------------------------
                _topButton->labelText(_selectedItem->getProperty<string>("label"));
                _topButton->selected(false);
				if (contains(_buttonContainer)) removeChild(_buttonContainer);
                //------------------------------------------
                
                //                //------------------------------------------
                //                int temp = 0;
                //                for(int i = 0; i < _itemList.size(); i++) {
                //                    if(_selectedItem == _itemList[i]) temp = i;
                //                }
                //                _selectedIndex = temp + 1;
                //                _selectedData = _dataList[temp];
                //                _selectedText = _textList[temp];
                //                _selectedValue = _valueList[temp];
                //                
                //------------------------------------------
				ofLog() << "Test2";

                //------------------------------------------
                _dispatchEvent();
				ofLog() << "Test3";

                if(_intParam != NULL) {
                    _bChangedByMyself["value"] = true;
                    _intParam->set(_selectedIndex);
                }
				ofLog() << "Test4";
				//------------------------------------------
            }
        }
        
        //Mouse Up
        if(event.type() == flMouseEvent::MOUSE_UP) {
            
        }
    }
    
    //--------------------------------------------------------------
    void flComboBox::_eventHandler(flEvent& event) {
		if (!_enabled) return;
//        ofLog() << "[flComboBox]_eventHandler(" << event.type() << ")";
//        ofLog() << "[flComboBox]this          = " << this << "," << ((flDisplayObject*) this)->name();
//        ofLog() << "[flComboBox]currentTarget = " << event.currentTarget() << "," << ((flDisplayObject*) event.currentTarget())->name();
//        ofLog() << "[flComboBox]target        = " << event.target() << "," << ((flDisplayObject*) event.target())->name();
        
        //Focus Out
        if(event.type() == flFocusEvent::FOCUS_OUT) {
            if(event.target() == _topButton) {
                _topButton->selected(false);
				if (contains(_buttonContainer)) removeChild(_buttonContainer);
            }
        }
    }
    
}
