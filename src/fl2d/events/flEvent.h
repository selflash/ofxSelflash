/**
 
 ActionScript3.0 Reference
 flash.events.Event
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/events/Event.html
 
 */

/**
e.target =�}�E�X�̉��ɂ�����́i�x���������悤��...�C�x���g���g���K�[������́j�B e.currentTarget =�h�b�g�̑O�̂���...�i�ȉ����Q�Ɓj

���������āA�C���X�^���X�����ubtns�v�̃N���b�v����10�̃{�^��������A���̂悤�ɂ���Ƃ��܂��B

---------------------------------------------------
btns.addEventListener(MouseEvent.MOUSE_OVER, onOver);
// btns = the thing before the dot of an addEventListener call

function onOver(e:MouseEvent):void{
	trace(e.target.name, e.currentTarget.name);
}
---------------------------------------------------

e.target��10�̃{�^����1�ł���Ae.currentTarget�͏�Ɂubtns�v�N���b�v�ł��B

MouseEvent��ROLL_OVER�ɕύX�����ꍇ�A�܂��̓v���p�e�Bbtns.mouseChildren��false�ɐݒ肵���ꍇ�Ae.target��e.currentTarget�͗����Ƃ���Ɂubtns�v�ɂȂ邱�Ƃɒ��ӂ��Ă��������B

*/


#pragma once

#include <string>
#include "flObject.h"

namespace fl2d {
    
    class flEventDispatcher;
    class flDisplayObjectContainer;
    class flEvent : public flObject {
        friend flEventDispatcher;
        friend flDisplayObjectContainer;

        public:
            static string ADDED;
            static string ADDED_TO_STAGE;
        
            static string REMOVED;
            static string REMOVED_FROM_STAGE;
        
            //static string ACTIVATE;
            //static string DEACTIVATE;
            //static string CANCEL;
            static string CHANGE;
            static string CLOSE;
            static string COMPLETE;
            //static string CONNECT;
            static string ENTER_FRAME;
            static string EXIT_FRAME;
            //static string FULLSCREEN;
            //static string ID3;
   //         static string INIT;
			//static string DEINIT;
			//static string MOUSE_LEAVE;
            //static string OPEN;
            //static string RENDER;
            //static string RESIZE;
            //static string SCROLL;
            //static string SELECT;
            //static string SOUND_COMPLETE;
            //static string TAB_CHILDREN_CHANEG;
            //static string TAB_ENABLED_CHANGE;
            //static string TAB_INDEX_CHANGE;
            //static string UNLOAD;

        protected:
            string _type;

			//[�ǂݎ���p] �C�x���g���o�u�����O�C�x���g���ǂ����������܂��B
			bool _bubbles = false;
			//[�ǂݎ���p] �C�x���g�Ɋ֘A�t����ꂽ���������ł��邩�ǂ����������܂��B
			bool _cancelable = false;
			//[�ǂݎ���p] �C�x���g�t���[�̌��݂̒i�K�ł��B
			int _eventPhase = 0;

            //�C�x���g���X�i�[��o�^���� EventDispatcher �ƕK����v����̂� currentTarget
			//�C�x���g���X�i�[�� Event �I�u�W�F�N�g���A�N�e�B�u�ɏ������Ă���I�u�W�F�N�g�ł��B
			//�Ⴆ�΁A���[�U�[���uOK�v���N���b�N�����ꍇ�AcurrentTarget �́A���̃{�^���܂��́A���̃C�x���g�ɑ΂��ăC�x���g���X�i�[��o�^���Ă���c��� 1 ���܂ރm�[�h�ɂȂ�܂��B
            void* __currentTarget;

			//���ڂ܂��� DisplayObject �C���X�^���X���܂܂�Ă���T�u�c���[��ǉ����邱�ƂŁA�I���X�e�[�W�\�����X�g�ɒǉ������ DisplayObject �C���X�^���X�ł��B
			//DisplayObject �C���X�^���X�����ڒǉ������ꍇ�A���̃C�x���g�̑O�� added �C�x���g���������܂��B
			//�C�x���g�^�[�Q�b�g�ł��B���̃v���p�e�B�ɂ̓^�[�Q�b�g�m�[�h���܂܂�܂��B
			//�Ⴆ�΁A���[�U�[���uOK�v���N���b�N�����ꍇ�A�^�[�Q�b�g�m�[�h�͂��̃{�^�����܂ޕ\�����X�g�m�[�h�ł��B
            void* __target;
        
        private:
        
        public:
            flEvent(string type, bool bubbles = false, bool cancelable = false);
            virtual ~flEvent();
        
			//Event �T�u�N���X�̃C���X�^���X�𕡐����܂��B
            virtual inline flEvent* clone() { return new flEvent(_type); }

			//�J�X�^�� ActionScript 3.0 Event �N���X�� toString() ���\�b�h���������邽�߂̃��[�e�B���e�B�֐��ł��B
			//virtual inline string formatToString(string className, ... arguments);
			//�C�x���g�� preventDefault() ���\�b�h���Ăяo���ꂽ���ǂ������m�F���܂��B
			//virtual bool isDefaultPrevented();
			//�C�x���g�̃f�t�H���g������L�����Z���ł���ꍇ�ɁA���̓�����L�����Z�����܂��B
			//virtual void preventDefault();
			//�C�x���g�t���[�̌��݂̃m�[�h����ь㑱����m�[�h�ŁA�C�x���g���X�i�[����������Ȃ��悤�ɂ��܂��B
			//virtual void stopImmediatePropagation();
			//�C�x���g�t���[�̌��݂̃m�[�h�Ɍ㑱����m�[�h�ŁA�C�x���g���X�i�[����������Ȃ��悤�ɂ��܂��B
			//virtual void stopPropagation();

        
            virtual inline string type() { return _type; }
        
            //            virtual const string& data();
        
            //https://n2works.net/columns/16
            //���ڃN���b�N���ꂽ�I�u�W�F�N�g��target�v���p�e�B�Ɋi�[����AcurrentTarget�ɂ̓C�x���g���X�i���֘A�t����ꂽ�I�u�W�F�N�g���i�[�����B
            //�C�x���g���X�i���֘A�t���Ă���I�u�W�F�N�g��Event�p���N���X����擾����ɂ�currentTarget���Q�Ƃ���ׂ��B
            virtual inline void* currentTarget() { return __currentTarget; }
    //        virtual inline void currentTarget(void* value) { _currentTarget = value; }
        
            virtual inline void* target() { return __target; }
            virtual inline void target(void* value) { __target = value; }
        
            template <class T>
            T data() { return getProperty<T>("data"); }
        
        protected:
			template <class T>
			void data(T value) { setProperty<T>("data", value); }

        private:
        
    };
    
}
