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
#include "../events/ComboBoxEvent.h"

namespace fl2d {
    
    class ComboBox : public Sprite {
        
        public:
        
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
        
            TextField* _labelText;
        
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
        
        public:
            ComboBox(float dropdownWidth = 150);
            ~ComboBox();
            
            string label();
            void label(string value, int color = 0xffffff);
            
//            void textColor(const int& color = 0xffffff);
        
            template <class T>
            void addItem(string label, const T& value, int color = 0xffffff) {
                int l = _itemList.size();

                //--------------------------------------
                Button* button = new Button(_dropdownWidth);
                button->label(label, color);
                button->setProperty<int>("index", l);
                button->x(0);
                button->y(20 * l);
                button->alpha(0.5);
                button->toggleEnabled(true);
                button->addEventListener(MouseEvent::ROLL_OVER, this, &ComboBox::_mouseEventHandler);
                button->addEventListener(MouseEvent::ROLL_OUT, this, &ComboBox::_mouseEventHandler);
                button->addEventListener(MouseEvent::MOUSE_DOWN, this, &ComboBox::_mouseEventHandler);
                _buttonContainer->addChild(button);
                _buttonList.push_back(button);
                //--------------------------------------

                Graphics* g;
                g = _buttonContainer->graphics();
                g->clear();
                g->beginFill(0x000000, 0.8);
                g->drawRect(0, 0, _dropdownWidth, 20 * (l + 1));
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
        
//            void removeItem(const string& label);
//            void removeItemAt(const int& index);
//            void replaceItemAt();
//            void sortItems();
            void removeAll();
        
            //0から始まるインデックス番号
            int selectedIndex();
            void selectedIndex(int value, bool dispatch = true);
        
            //ComboBox コンポーネントの TextInput 部分に表示されるストリングを取得します。
            string selectedLabel();
        
            template <class T>
            T selectedValue() { return _selectedItem->getProperty<T>("value"); }
        
            int numItems();
            
        protected:
            virtual void _setup();
            virtual void _update();
            virtual void _draw();
            
        private:
            void _mouseEventHandler(Event& event);
            void _eventHandler(Event& event);
    };
    
}