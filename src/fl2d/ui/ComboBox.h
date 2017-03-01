/**
  
 ActionScript3.0 Reference
 fl.controls.ComboBox
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/fl/controls/ComboBox.html
 
 */

#pragma once

#include "ofMain.h"

#include "../FlashConfig.h"
#include "../display/Sprite.h"
#include "../texts/TextField.h"
#include "Button.h"
#include "../events/FocusEvent.h"
#include "../events/ComboBoxEvent.h"

namespace fl2d {
    
    class ComboBox : public Sprite {
        
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

            TextField* _label;

            //------------------------------------------
            Button* _topButton;
            Sprite* _buttonContainer;
        
            vector<Button*> _buttonList;
            Button* _selectedButton;
            //------------------------------------------
        
            //------------------------------------------
            vector<Object*> _itemList;
            //ドロップダウンリストで選択されているアイテムの値を取得または設定します。
            Object* _selectedItem;
            //------------------------------------------
        
            string _mode;
        
            bool _enabled;
        
        public:
            ComboBox(float dropdownWidth = 150);
            virtual ~ComboBox();
            
            TextField* label();
            void label(TextField* value);

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
                Button* button = new Button(_dropdownWidth);
                button->labelText(label);
                button->setProperty<int>("index", _buttonList.size());
                button->x(0);
                button->alpha(0.5);
                button->toggleEnabled(true);
                button->addEventListener(MouseEvent::ROLL_OVER, this, &ComboBox::_mouseEventHandler);
                button->addEventListener(MouseEvent::ROLL_OUT, this, &ComboBox::_mouseEventHandler);
                button->addEventListener(MouseEvent::MOUSE_DOWN, this, &ComboBox::_mouseEventHandler);
                _buttonContainer->addChild(button);
                _buttonList.push_back(button);
                
                int l = _buttonList.size();
                for(int i = 0; i < l; i++) {
                    Button* button = _buttonList[i];
                    if(_mode == "down") button->y(18 * i);
                    if(_mode == "up") button->y(18 * i - (18 * l));
                }
                //--------------------------------------
                
                Graphics* g;
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
                
                Object* item = new Object();
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
                
                Button* button = _buttonList[index];
                button->removeEventListener(MouseEvent::ROLL_OVER, this, &ComboBox::_mouseEventHandler);
                button->removeEventListener(MouseEvent::ROLL_OUT, this, &ComboBox::_mouseEventHandler);
                button->removeEventListener(MouseEvent::MOUSE_DOWN, this, &ComboBox::_mouseEventHandler);
//                button->removeAllEventListener();
                _buttonContainer->removeChild(button);
                delete button;
                _buttonList.erase(_buttonList.begin() + index);
                //--------------------------------------
                
                //--------------------------------------
                int l = _buttonList.size();
                for(int i = 0; i < l; i++) {
                    Button* button = _buttonList[i];
                    button->setProperty<int>("index", i);
                    if(_mode == "down") button->y(18 * i);
                    if(_mode == "up") button->y(18 * i - (18 * l));
                }
                //--------------------------------------

                Graphics* g;
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
                
                Object* item = _itemList[index];
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
                        Button* button = _buttonList[i];
                        button->y(18 * i);
                    }
                    
                    Graphics* g;
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
                        Button* button = _buttonList[i];
                        button->y(18 * i - (18 * l));
                    }

                    Graphics* g;
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
        
            bool enabled();
            void enabled(bool value);

        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
            
        private:
            void _mouseEventHandler(Event& event);
            void _eventHandler(Event& event);
    };
    
}
