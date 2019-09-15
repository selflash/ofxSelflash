/**
 
 ActionScript3.0 Reference
 fl.controls.ComboBox
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/fl/controls/ComboBox.html
 
 */

#pragma once

#include "ofMain.h"

#include "flDefinition.h"
#include "flSprite.h"
#include "flTextField.h"
#include "flButton.h"
#include "flFocusEvent.h"
#include "flComboBoxEvent.h"

namespace fl2d {
    
    class flComboBox : public flSprite {
        
    public:
        static string DROPDOWNLIST_UP;
        static string DROPDOWNLIST_DOWN;
        
    protected:
        
    private:
        //------------------------------------------
        //ドロップダウンリストの最大幅（ピクセル単位）を取得または設定します。
        float _dropdownWidth;
        //スクロールバーを持たないドロップダウンリストに表示できる最大行数を取得または設定します。
        int _rowCount;
        //単一選択リストで選択されたアイテムのインデックスを取得または設定します。
        int _selectedIndex;
        //------------------------------------------
        
        float _labelNormalColor;
        float _labelOverColor;
        float _labelActiveColor;
        float _labelDeactiveColor;
        
        ofFloatColor _lineColor;
        ofFloatColor _normalColor;
        ofFloatColor _overColor;
        ofFloatColor _activeColor;
        
        flTextField* _label;
        
        //------------------------------------------
        flButton* _topButton;
        flSprite* _buttonContainer;
        
        vector<flButton*> _buttonList;
        flButton* _selectedButton;
        //------------------------------------------
        
        //------------------------------------------
        vector<flObject*> _itemList;
        //ドロップダウンリストで選択されているアイテムの値を取得または設定します。
        flObject* _selectedItem;
        //------------------------------------------
        
        string _mode;
        
        void* _pointerValue;
        string _stringValue;
        float _floatValue;
        int _intValue;
        
        bool _enabled;
        
    public:
        flComboBox(float dropdownWidth = 150);
        virtual ~flComboBox();
        
        flTextField* label();
        void label(flTextField* value);
        
        string itemLabelText(int index) {
            if(index < 0 || index > _buttonList.size() - 1) return "";
            
            return _itemList[index]->getProperty<string>("label");
        }
        void itemLabelText(string value, int index) {
            if(index < 0 || index > _buttonList.size() - 1) return;
            
            _buttonList[index]->labelText(value);
            _itemList[index]->setProperty<string>("label", value);
        }
        
        template <class T>
        void addItem(string label, const T& value) {
            //--------------------------------------
            flButton* button = new flButton(_dropdownWidth);
            button->labelText(label);
            button->setProperty<int>("index", _buttonList.size());
            button->x(0);
            button->alpha(0.5);
            button->toggleEnabled(true);
            button->addEventListener(flMouseEvent::ROLL_OVER, this, &flComboBox::_mouseEventHandler);
            button->addEventListener(flMouseEvent::ROLL_OUT, this, &flComboBox::_mouseEventHandler);
            button->addEventListener(flMouseEvent::MOUSE_DOWN, this, &flComboBox::_mouseEventHandler);
            _buttonContainer->addChild(button);
            _buttonList.push_back(button);
            
            int l = _buttonList.size();
            for(int i = 0; i < l; i++) {
                flButton* button = _buttonList[i];
                if(_mode == "down") button->y(18 * i);
                if(_mode == "up") button->y(18 * i - (18 * l));
            }
            //--------------------------------------
            
            flGraphics* g;
            g = _buttonContainer->graphics();
            g->clear();
            g->beginFill(0x000000, 0.8);
            if(_mode == "down") {
                g->drawRect(0, 0, _dropdownWidth, 18 * l);
            }
            if(_mode == "up") {
                g->drawRect(0, 0, _dropdownWidth, -18 * l);
            }
            g->endFill();
            
            //--------------------------------------
            if (typeid(T) == typeid(float)) {
                
            }
            if (typeid(T) == typeid(int)) {
                
            }
            
            flObject* item = new flObject();
            item->setProperty<string>("label", label);
            item->setProperty<T>("value", value);
            _itemList.push_back(item);
            //--------------------------------------
            
            //--------------------------------------
            if(l == 0) {
                
            }
        }
        
        void removeItemByIndex(int index) {
            //--------------------------------------
            //children()の箇所はリファクタリングとかで外に出したらダメ
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
                _selectedIndex = 0;
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
        
        inline void mode(string value) {
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
        
        //            void removeItem(const string& label);
        //            void removeItemAt(const int& index);
        //            void replaceItemAt();
        //            void sortItems();
        void removeAllItems();
        
        //0から始まるインデックス番号
        int selectedIndex();
        void selectedIndex(int value, bool dispatch = true);
        
        //ComboBox コンポーネントの TextInput 部分に表示されるストリングを取得します。
        string selectedLabel();
        
        template <class T>
        T selectedValue() { return _selectedItem->getProperty<T>("value"); }
        
        int numItems();        
        
        void* pointerValue();
        void pointerValue(void* value);
        
        string stringValue();
        void stringValue(string value);
        
        float floatValue();
        void floatValue(float value);
        
        int intValue();
        void intValue(int value);
        
        bool enabled();
        void enabled(bool value);
        
    protected:
        virtual void _setup();
        virtual void _update();
        virtual void _draw();
        
    private:
        void _mouseEventHandler(flEvent& event);
        void _eventHandler(flEvent& event);
    };
    
}
