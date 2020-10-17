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
        
        //�e�L�X�g�̕�
        float _textWidth;
        //�e�L�X�g�̍���
        float _textHeight;
        
        //�e�L�X�g�t�B�[���h�̎����I�Ȋg�� / �k������ѐ���𐧌䂵�܂��B
        string _autoSize;
        float _tx;
        int _numLine;

		flTextFormat* _defaultTextFormat = NULL;
        
        int _activeLineWidth;
        
        //            bool _enabledAntiAliasing;
        
        //            //�e�L�X�g�t�B�[���h�ɔw�i�̓h��Ԃ������邩�ǂ������w�肵�܂��B
        //            bool _background;
        //            //�e�L�X�g�t�B�[���h�̔w�i�̐F�ł��B
        //            int _backgroundColor;
        
        //            //�w�肳�ꂽ�e�L�X�g�t�B�[���h�Ɍ��ݕ\������Ă����ԉ��̍s�����������ł��i1 ����n�܂�C���f�b�N�X�j�B
        //            int _bottomScrollV;
        
        //            //�J�[�\���i�L�����b�g�j�ʒu�̃C���f�b�N�X�ł��B
        //            int _caretIndex;
        
        //            //�e�L�X�g�t�B�[���h���̕������ł��B
        //            int _length;
        
        //            //���[�U�[�����͂���Ƃ��ɁA�e�L�X�g�t�B�[���h�ɓ��͂ł���ő�̕������ł��B
        //            int _maxChars;
        
        //            //���݂̐����X�N���[���ʒu�ł��B
        //            int _scrollH;
        //            //�e�L�X�g�t�B�[���h�̃e�L�X�g�̐����ʒu�ł��B
        //            int _scrollV;
        //            //scrollH �̍ő�l�ł��B
        //            int _maxScrollH;
        //            //scrollV �̍ő�l�ł��B
        //            int _maxScrollV;
        
        //            //�e�L�X�g�t�B�[���h���I���\�ł��邩�ǂ����������u�[���l�ł��B
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
