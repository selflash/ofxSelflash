/**
 
 ActionScript3.0 Reference
 flash.text.TextField
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/text/TextField.html
 
 */

#pragma once

#include "flstringutil.h"

#include "flDefinition.h"
#include "flTextFieldAutoSize.h"
#include "flTextFormat.h"
#include "flFont.h"
#include "flInteractiveObject.h"
#include "flGraphics.h"
#include "flMouseEvent.h"

//#define TEXT_FIELD_TYPE_DYNAMIC    "dynamic"
//#define TEXT_FIELD_TYPE_INPUT      "input"

using namespace flinternal;

namespace fl2d {
    
    class flTextField : public flInteractiveObject {
        
    public:
        static string TEXT_FIELD_TYPE_DYNAMIC;
        static string TEXT_FIELD_TYPE_INPUT;
        
    protected:
        
    private:
        flGraphics* _graphics;
        
        ofColor _textColor;
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

		flTextFormat* _defaultTextFormat = NULL;
        
        int _activeLineWidth;
        
        //            bool _enabledAntiAliasing;
        
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
        flTextField();
        virtual ~flTextField();
        
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
        
		virtual ofColor textColor();
		virtual void textColor(int value);
		virtual void textColor(const ofColor& value);
        
		virtual string autoSize();
		virtual void autoSize(string value);

		virtual const flTextFormat* defaultTextFormat();
		virtual void defaultTextFormat(flTextFormat* value);
        
		virtual bool active();
		virtual void active(bool value);
        
		virtual bool enabled();
		virtual void enabled(bool value);
        
        //            bool enabledAntiAliasing() { return _enabledAntiAliasing; }
        //            void enabledAntiAliasing(bool value) { _enabledAntiAliasing = value; }
        
        
    protected:
        virtual void update();
        virtual void draw(bool applyMatrix = true);
        virtual void _draw();
        
        virtual void __compoundAlpha(float value);
        
        virtual void _drawGraphics(const ofFloatColor& lineColor, const ofFloatColor& fillColor, float thickness = 1.0);
        virtual void _drawGraphics(int lineColor, int fillColor, float thickness = 1.0);
        
    private:
        void _addListeners();
        void _removeListeners();
        
        void _keyPressedEventHandler(ofKeyEventArgs& event);
        void _keyReleasedEventHandler(ofKeyEventArgs& event);
        
        void _mouseEventHandler(flEvent& event);
        
        void _eventHandler(flEvent& event);
    };
}
