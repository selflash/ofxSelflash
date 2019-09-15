#include "flComboBox.h"

namespace fl2d {
    //水平
    string flComboBox::DROPDOWNLIST_UP = "up";
    //垂直
    string flComboBox::DROPDOWNLIST_DOWN = "down";
    
    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flComboBox::flComboBox(float dropdownWidth) {
        //cout << "[flComboBox]flComboBox()" << endl;
        
        _target = this;
        name("flComboBox");
        
        _dropdownWidth = dropdownWidth;
        _rowCount = 0;
        
        _selectedIndex = 0;
        
        _labelNormalColor = flDefinition::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = flDefinition::UI_LABEL_OVER_COLOR;
        _labelActiveColor = flDefinition::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = flDefinition::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(flDefinition::UI_LINE_COLOR);
        _normalColor.setHex(flDefinition::UI_NORMAL_COLOR);
        _overColor.setHex(flDefinition::UI_OVER_COLOR);
        _activeColor.setHex(flDefinition::UI_ACTIVE_COLOR);
        
        //------------------------------------------
        //ラベル
        _label = NULL;
        //------------------------------------------
        
        //------------------------------------------
        //ボタン
        _topButton = new flButton(_dropdownWidth);
        _topButton->labelText("");
        _topButton->x(0);
        _topButton->y(0);
        _topButton->toggleEnabled(true);
        _topButton->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flComboBox::_mouseEventHandler);
        _topButton->addEventListener(flFocusEvent::FOCUS_OUT, this, &flComboBox::_eventHandler);
        addChild(_topButton);
        
        _buttonContainer = new flSprite();
        _buttonContainer->x(0);
        _buttonContainer->y(18);
        
        _selectedButton = NULL;
        //------------------------------------------
        
        //------------------------------------------
        //アイテム
        _selectedItem = NULL;
        //------------------------------------------
        
        _mode = "down";
        
        _pointerValue = NULL;
        _stringValue = "";
        _floatValue = 0.0;
        _intValue = 0;
        
        _enabled = true;
    }
    
    //--------------------------------------------------------------
    //
    flComboBox::~flComboBox() {
        //cout << "[flComboBox]~flComboBox()" << endl;
        
        removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flComboBox::_mouseEventHandler);
        
        _dropdownWidth = 0;
        _rowCount = 0;
        
        _selectedIndex = 0;
        
        //------------------------------------------
        //ラベル
        _label = NULL;
        //------------------------------------------
        
        //------------------------------------------
        //ボタン
        _topButton->removeEventListener(flMouseEvent::MOUSE_DOWN, this, &flComboBox::_mouseEventHandler);
        _topButton->removeEventListener(flFocusEvent::FOCUS_OUT, this, &flComboBox::_eventHandler);
        delete _topButton;
        _topButton = NULL;
        
        delete _buttonContainer;
        _buttonContainer = NULL;
        
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
        
        _enabled = false;
    }
    
    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flComboBox::_setup() {
        
    }
    
    //--------------------------------------------------------------
    //
    void flComboBox::_update() {
        
    }
    
    //--------------------------------------------------------------
    //
    void flComboBox::_draw() {
        
    }
    
    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    flTextField* flComboBox::label() { return _label; }
    void flComboBox::label(flTextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    void flComboBox::removeAllItems() {
        if(_buttonContainer->parent()) removeChild(_buttonContainer);
        
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
        
        flGraphics* g;
        g = _buttonContainer->graphics();
        g->clear();
        
        _topButton->labelText("");
        _selectedIndex = 0;
        _selectedItem = NULL;
    }
    
    //    //--------------------------------------------------------------
    //    //
    int flComboBox::selectedIndex() { return _selectedIndex; }
    void flComboBox::selectedIndex(int value, bool dispatch) {
        _selectedIndex = value;
        if(value < 0) _selectedIndex = 0;
        if(_itemList.size() - 1 <= value) _selectedIndex = _itemList.size() - 1;
        //------------------------------------------
        if(_selectedButton != NULL) {
            _selectedButton->selected(false);
            _selectedButton->alpha(0.5);
        }
        _selectedButton = _buttonList[_selectedIndex];
        
        _selectedItem = _itemList[_selectedIndex];
        
        //------------------------------------------
        _topButton->labelText(_selectedItem->getProperty<string>("label"));
        _topButton->selected(false);
        if(_buttonContainer->parent()) removeChild(_buttonContainer);
        //------------------------------------------
        
        //------------------------------------------
        //イベント
        if(dispatch) {
            flComboBoxEvent* event = new flComboBoxEvent(flComboBoxEvent::CHANGE);
            event->_target = this;
            //            event->__label = _selectedLabel;
            //            event->__pointerValue = _selectedData;
            //            event->__stringValue = _selectedText;
            //            event->__floatValue = _selectedValue;
            dispatchEvent(event);
        }
        //------------------------------------------
    }
    
    //--------------------------------------------------------------
    //
    string flComboBox::selectedLabel() { return _selectedItem->getProperty<string>("label"); }
    
    //--------------------------------------------------------------
    //
    int flComboBox::numItems() { return _itemList.size(); }
    
    //--------------------------------------------------------------
    //
    void* flComboBox::pointerValue() { return _pointerValue; }
    void flComboBox::pointerValue(void* value) { _pointerValue = value; }
    
    //--------------------------------------------------------------
    //
    string flComboBox::stringValue() { return _stringValue; }
    void flComboBox::stringValue(string value) { _stringValue = value; }
    
    //--------------------------------------------------------------
    //
    float flComboBox::floatValue() { return _floatValue; }
    void flComboBox::floatValue(float value) { _floatValue = value; }
    
    //--------------------------------------------------------------
    //
    int flComboBox::intValue() { return _intValue; }
    void flComboBox::intValue(int value) { _intValue = value; }
    
    //--------------------------------------------------------------
    //
    bool flComboBox::enabled() { return _enabled; }
    void flComboBox::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        _topButton->enabled(_enabled);
        
        if(_enabled) {
            if(_label != NULL) _label->textColor(_labelNormalColor);
        } else {
            if(_label != NULL) _label->textColor(_labelDeactiveColor);
            
            _topButton->selected(false);
            if(_buttonContainer->parent()) removeChild(_buttonContainer);
            //            if(_topButton->isFocus()) { _topButton->focusOut(); }
        }
    }
    
    //==============================================================
    // PROTECTED / PRIVATE METHOD
    //==============================================================
    
    //==============================================================
    // EVENT HANDLER
    //==============================================================
    
    //--------------------------------------------------------------
    //
    void flComboBox::_mouseEventHandler(flEvent& event) {
        //    cout << "[flComboBox]_mouseEventHandler(" << event.type() << ")" << endl;
        //    cout << "[flComboBox]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //    cout << "[flComboBox]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //    cout << "[flComboBox]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        //ROLL OVER
        if(event.type() == flMouseEvent::ROLL_OVER) {
            flButton* target = (flButton*) event.target();
            
            _buttonContainer->addChild(target);
            target->alpha(1);
        }
        
        //ROLL OUT
        if(event.type() == flMouseEvent::ROLL_OUT) {
            flButton* target = (flButton*) event.target();
            
            if(target != _selectedItem) target->alpha(0.5);
        }
        
        //MOUSE DOWN
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
                //------------------------------------------
                if(_selectedButton) {
                    _selectedButton->selected(false);
                    _selectedButton->alpha(0.5);
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
                if(_buttonContainer->parent()) removeChild(_buttonContainer);
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
                //イベント
                //                cout << "DEBUG START ----- " << endl;
                //                flComboBoxEvent* event = new flComboBoxEvent(flComboBoxEvent::CHANGE);
                //                flComboBoxEvent<float> event(flComboBoxEvent::CHANGE, 0.1f);
                
                //                new flComboBoxEvent<float>(flComboBoxEvent::CHANGE, 0.1f);
                flComboBoxEvent* event = new flComboBoxEvent(flComboBoxEvent::CHANGE);
                //                cout << "DEBUG END   ----- " << endl;
                event->_target = this;
                //                event->__label = _selectedLabel;
                //                event->__pointerValue = _selectedData;
                //                event->__stringValue = _selectedText;
                //                event->__floatValue = _selectedValue;
                dispatchEvent(event);
                //------------------------------------------
            }
        }
        
        //MOUSE UP
        if(event.type() == flMouseEvent::MOUSE_UP) {
            
        }
    }
    
    //--------------------------------------------------------------
    //
    void flComboBox::_eventHandler(flEvent& event) {
        //        cout << "[flComboBox]_eventHandler(" << event.type() << ")" << endl;
        //        cout << "[flComboBox]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
        //        cout << "[flComboBox]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
        //        cout << "[flComboBox]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        if(event.type() == flFocusEvent::FOCUS_OUT) {
            if(event.target() == _topButton) {
                _topButton->selected(false);
                if(_buttonContainer->parent()) removeChild(_buttonContainer);
            }
        }
    }
    
}
