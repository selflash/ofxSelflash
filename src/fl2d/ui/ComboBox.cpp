#include "ComboBox.h"

namespace fl2d {
    //水平
    string ComboBox::DROPDOWNLIST_UP = "up";
    //垂直
    string ComboBox::DROPDOWNLIST_DOWN = "down";

    //==============================================================
    // CONSTRUCTOR / DESTRUCTOR
    //==============================================================

    //--------------------------------------------------------------
    //
    ComboBox::ComboBox(float dropdownWidth) {
        //cout << "[ComboBox]ComboBox()" << endl;
        
        _target = this;
        name("ComboBox");
        
        _dropdownWidth = dropdownWidth;
        _rowCount = 0;
        
        _selectedIndex = 0;
        
        _labelNormalColor = FlashConfig::UI_LABEL_NORMAL_COLOR;
        _labelOverColor = FlashConfig::UI_LABEL_OVER_COLOR;
        _labelActiveColor = FlashConfig::UI_LABEL_ACTIVE_COLOR;
        _labelDeactiveColor = FlashConfig::UI_LABEL_DEACTIVE_COLOR;
        
        _lineColor.setHex(FlashConfig::UI_LINE_COLOR);
        _normalColor.setHex(FlashConfig::UI_NORMAL_COLOR);
        _overColor.setHex(FlashConfig::UI_OVER_COLOR);
        _activeColor.setHex(FlashConfig::UI_ACTIVE_COLOR);

        //------------------------------------------
        //ラベル
        _label = NULL;
        //------------------------------------------
        
        //------------------------------------------
        //ボタン
        _topButton = new Button(_dropdownWidth);
        _topButton->labelText("");
        _topButton->x(0);
        _topButton->y(0);
        _topButton->toggleEnabled(true);
        _topButton->addEventListener(MouseEvent::MOUSE_DOWN, this, &ComboBox::_mouseEventHandler);
        _topButton->addEventListener(FocusEvent::FOCUS_OUT, this, &ComboBox::_eventHandler);
        addChild(_topButton);
        
        _buttonContainer = new Sprite();
        _buttonContainer->x(0);
        _buttonContainer->y(18);
        
        _selectedButton = NULL;
        //------------------------------------------
        
        //------------------------------------------
        //アイテム
        _selectedItem = NULL;
        //------------------------------------------
        
        _mode = "down";
        
        _enabled = true;
    }

    //--------------------------------------------------------------
    //
    ComboBox::~ComboBox() {
        //cout << "[ComboBox]~ComboBox()" << endl;
        
        removeEventListener(MouseEvent::MOUSE_DOWN, &ComboBox::_mouseEventHandler);
        
        _dropdownWidth = 0;
        _rowCount = 0;

        _selectedIndex = 0;
        
        //------------------------------------------
        //ラベル
        _label = NULL;
        //------------------------------------------
        
        //------------------------------------------
        //ボタン
        _topButton->removeEventListener(MouseEvent::MOUSE_DOWN, &ComboBox::_mouseEventHandler);
        _topButton->removeEventListener(FocusEvent::FOCUS_OUT, &ComboBox::_eventHandler);
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
        
        _enabled = false;
    }

    //==============================================================
    // SETUP / UPDATE / DRAW
    //==============================================================

    //--------------------------------------------------------------
    //
    void ComboBox::_setup() {
        
    }

    //--------------------------------------------------------------
    //
    void ComboBox::_update() {
        
    }

    //--------------------------------------------------------------
    //
    void ComboBox::_draw() {
        
    }

    //==============================================================
    // PUBLIC METHOD
    //==============================================================
    
    //--------------------------------------------------------------
    //
    TextField* ComboBox::label() { return _label; }
    void ComboBox::label(TextField* value) { _label = value; }
    
    //--------------------------------------------------------------
    //
    void ComboBox::removeAllItems() {
        if(_buttonContainer->parent()) removeChild(_buttonContainer);
        
        int i; int l;
        l = _buttonList.size();
        for(i = 0; i < l; i++) {
            Button* button = _buttonList[i];
            button->removeEventListener(MouseEvent::ROLL_OVER, &ComboBox::_mouseEventHandler);
            button->removeEventListener(MouseEvent::ROLL_OUT, &ComboBox::_mouseEventHandler);
            button->removeEventListener(MouseEvent::MOUSE_DOWN, &ComboBox::_mouseEventHandler);
            _buttonContainer->removeChild(button);
        }
        
        _buttonList.clear();
        _itemList.clear();
        
        Graphics* g;
        g = _buttonContainer->graphics();
        g->clear();
        
        _topButton->labelText("");
        _selectedIndex = 0;
        _selectedItem = NULL;
    }

//    //--------------------------------------------------------------
//    //
    int ComboBox::selectedIndex() { return _selectedIndex; }
    void ComboBox::selectedIndex(int value, bool dispatch) {
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
            ComboBoxEvent* event = new ComboBoxEvent(ComboBoxEvent::CHANGE);
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
    string ComboBox::selectedLabel() { return _selectedItem->getProperty<string>("label"); }

    //--------------------------------------------------------------
    //
    int ComboBox::numItems() { return _itemList.size(); }

    //--------------------------------------------------------------
    //
    bool ComboBox::enabled() { return _enabled; }
    void ComboBox::enabled(bool value) {
        _enabled = value;
        mouseEnabled(_enabled);
        mouseChildren(_enabled);
        
        _topButton->enabled(_enabled);
        
        if(_enabled) {
            if(_label != NULL) _label->textColor(_labelNormalColor);
        } else {
            if(_label != NULL) _label->textColor(_labelDeactiveColor);
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
    void ComboBox::_mouseEventHandler(Event& event) {
//    cout << "[ComboBox]_mouseEventHandler(" << event.type() << ")" << endl;
//    cout << "[ComboBox]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
//    cout << "[ComboBox]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
//    cout << "[ComboBox]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        //ROLL OVER
        if(event.type() == MouseEvent::ROLL_OVER) {
            Button* target = (Button*) event.target();
            
            _buttonContainer->addChild(target);
            target->alpha(1);
        }
        
        //ROLL OUT
        if(event.type() == MouseEvent::ROLL_OUT) {
            Button* target = (Button*) event.target();
            
            if(target != _selectedItem) target->alpha(0.5);
        }
        
        //MOUSE DOWN
        if(event.type() == MouseEvent::MOUSE_DOWN) {
            Button* target = (Button*) event.target();
            
            if(target == _topButton) {
                if(_topButton->selected()){
                    addChild(_buttonContainer);
                    if(parent()) ((DisplayObjectContainer*)parent())->addChild(this);
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
//                ComboBoxEvent* event = new ComboBoxEvent(ComboBoxEvent::CHANGE);
//                ComboBoxEvent<float> event(ComboBoxEvent::CHANGE, 0.1f);
                
//                new ComboBoxEvent<float>(ComboBoxEvent::CHANGE, 0.1f);
                ComboBoxEvent* event = new ComboBoxEvent(ComboBoxEvent::CHANGE);
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
        if(event.type() == MouseEvent::MOUSE_UP) {
            
        }
    }

    //--------------------------------------------------------------
    //
    void ComboBox::_eventHandler(Event& event) {
//        cout << "[ComboBox]_eventHandler(" << event.type() << ")" << endl;
//        cout << "[ComboBox]this          = " << this << "," << ((DisplayObject*) this)->name() << endl;
//        cout << "[ComboBox]currentTarget = " << event.currentTarget() << "," << ((DisplayObject*) event.currentTarget())->name() << endl;
//        cout << "[ComboBox]target        = " << event.target() << "," << ((DisplayObject*) event.target())->name() << endl;
        
        if(event.type() == FocusEvent::FOCUS_OUT) {
            if(event.target() == _topButton) {
                _topButton->selected(false);
                if(_buttonContainer->parent()) removeChild(_buttonContainer);
            }
        }
    }

}