/**
 
 ActionScript3.0 Reference
 flash.events.MouseEvent
 http://livedocs.adobe.com/flash/9.0_jp/ActionScriptLangRefV3/flash/events/MouseEvent.html
 
 */

#pragma once

#include <string>
#include "flEvent.h"
#include "flInteractiveObject.h"

namespace fl2d {
    
    class flInteractiveObject;
    class flStage;
    class flMouseEvent : public flEvent {
        friend flInteractiveObject;
        friend flStage;
        
    public:
        static string MOUSE_OVER;
        static string MOUSE_OUT;
        static string ROLL_OVER;
        static string ROLL_OUT;
        static string MOUSE_DOWN;
        static string MOUSE_UP;
        static string CLICK;
        //static string DOUBLE_CLICK;
        static string MOUSE_MOVE;
        static string DRAGGING;
        
        static string MOUSE_SCROLLED;
        
    protected:
        
    private:
        float __localX{ 0.0 };
        float __localY{ 0.0 };
        
        float __stageX{ 0.0 };
        float __stageY{ 0.0 };
        
        float __scrollX{ 0.0 };
        float __scrollY{ 0.0 };
        
    public:
        flMouseEvent(string type);
        virtual ~flMouseEvent();
        /*
         //Alt �L�[���A�N�e�B�u�ɂȂ��Ă��邩
         void altKey(bool value);
         bool altKey();
         //�}�E�X�̎�{�^����������Ă��邩
         void buttonDown(bool value);
         bool buttonDown();
         //Ctrl �L�[���A�N�e�B�u�ɂȂ��Ă��邩
         void ctrlKey(bool value);
         bool ctrlKey();
         //Shift �L�[���A�N�e�B�u�ɂȂ��Ă��邩
         void shiftKey(bool value);
         bool shiftKey();
         
         //�X�v���C�g����Ƃ���C�x���g�����ʒu�̐������W
         void localX(float value);
         float localX();
         //�X�v���C�g����Ƃ���C�x���g�����ʒu�̐������W
         void localY(float value);
         float localY();
         
         //�O���[�o���X�e�[�W���W����Ƃ���C�x���g�����ʒu�̐������W
         float stageX();
         //�O���[�o���X�e�[�W���W����Ƃ���C�x���g�����ʒu�̐������W
         float stageY();
         
         //�C�x���g�Ɋ֘A����\�����X�g�I�u�W�F�N�g�ւ̎Q��
         void relatedObject(InteractiveObject* value);
         InteractiveObject* relatedObject();
         */
        
        inline float localX() { return __localX; }
        inline float localY() { return __localY; }
        
        inline float stageX() { return __stageX; }
        inline float stageY() { return __stageY; }
        
        inline float scrollX() { return __scrollX; }
        inline float scrollY() { return __scrollY; }
        
    protected:
        
    private:
        
    };
    
}
