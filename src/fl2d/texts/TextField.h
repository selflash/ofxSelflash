/**
 
 ActionScript3.0 Reference
 flash.text.TextField
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/text/TextField.html
 
 */

#pragma once

#include "../../utils/StringUtil.h"

#include "../FlashConfig.h"
#include "TextFieldAutoSize.h"
#include "Font.h"
#include "../display/InteractiveObject.h"
#include "../display/Graphics.h"
#include "../events/MouseEvent.h"

//#define TEXT_FIELD_TYPE_DYNAMIC    "dynamic"
//#define TEXT_FIELD_TYPE_INPUT      "input"

namespace fl2d {
    
    class TextField : public InteractiveObject {
        
        public:
            static string TEXT_FIELD_TYPE_DYNAMIC;
            static string TEXT_FIELD_TYPE_INPUT;
        
        protected:
        
        private:
            float _labelNormalColor;
            float _labelOverColor;
            float _labelActiveColor;
            float _labelDeactiveColor;
        
            ofFloatColor _lineColor;
            ofFloatColor _normalColor;
            ofFloatColor _overColor;
            ofFloatColor _activeColor;
            ofFloatColor _deactiveColor;
        
            Graphics* _graphics;
        
            ofFloatColor _textColor;
            vector<string> _texts;
            string _text;
            
            string _type;
        
            //テキストの幅
            float _textWidth;
            //テキストの高さ
            float _textHeight;

            //テキストフィールドの自動的な拡大 / 縮小および整列を制御します。
            string _autoSize;
            float _tx;
            int _numLine;
        
            int _activeLineWidth;
        
            bool _enabledAntiAliasing;

//            //テキストフィールドに背景の塗りつぶしがあるかどうかを指定します。
//            bool _background;
//            //テキストフィールドの背景の色です。
//            int _backgroundColor;
        
//            //指定されたテキストフィールドに現在表示されている一番下の行を示す整数です（1 から始まるインデックス）。
//            int _bottomScrollV;
        
//            //カーソル（キャレット）位置のインデックスです。
//            int _caretIndex;
        
//            //テキストフィールド内の文字数です。
//            int _length;
        
//            //ユーザーが入力するときに、テキストフィールドに入力できる最大の文字数です。
//            int _maxChars;
        
//            //現在の水平スクロール位置です。
//            int _scrollH;
//            //テキストフィールドのテキストの垂直位置です。
//            int _scrollV;
//            //scrollH の最大値です。
//            int _maxScrollH;
//            //scrollV の最大値です。
//            int _maxScrollV;
        
//            //テキストフィールドが選択可能であるかどうかを示すブール値です。
//            bool _selectable;
        
            bool _addedListeners;
            
            bool _isActive;
            bool _enabled;

        public:
            TextField();
            ~TextField();
        
            virtual float width();
            virtual void width(float value);
            
            virtual float height();
            virtual void height(float value);
            
            virtual float textWidth();
            virtual float textHeight();
        
            virtual float alpha();
            virtual void alpha(float value);
                
            virtual const string text();
            virtual void text(const string& value, int color = -1);
            virtual void appendText(const string& value);
            
            virtual const string& type();
            virtual void type(const string& value);
            
            int textColor();
            void textColor(int value);
            void textColor(ofFloatColor value);
        
            string autoSize();
            void autoSize(string value);
            
            bool active();
            void active(bool value);
            
            bool enabled();
            void enabled(bool value);
        
            bool enabledAntiAliasing() { return _enabledAntiAliasing; }
            void enabledAntiAliasing(bool value) { _enabledAntiAliasing = value; }


        protected:
            virtual void update();
            virtual void draw();
            virtual void _draw();
        
            virtual void _drawGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness = 1.0);
            virtual void _drawGraphics(int lineColor, int fillColor, float thickness = 1.0);
        
        private:
            void _addListeners();
            void _removeListeners();
            
            void _keyPressedEventHandler(ofKeyEventArgs& event);
            void _keyReleasedEventHandler(ofKeyEventArgs& event);
            
            void _mouseEventHandler(Event& event);
        
            void _eventHandler(Event& event);
    };
}
