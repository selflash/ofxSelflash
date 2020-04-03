/**
 
 Ported from ofxMSAInteractiveObject.
 https://github.com/of/ofx-msa/tree/master/ofxMSAInteractiveObject/
 
 Original code ported from julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashInteractiveObject.h
 
 ActionScript3.0 Reference
 flash.display.InteractiveObject
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/InteractiveObject.html
 
 */

#pragma once

#include "flDisplayObject.h"
#include "flFocusEvent.h"
#include "flMouseEvent.h"

namespace fl2d {
    
    class flStage;
    class flInteractiveObject : public flDisplayObject {
        // friends! http://www.cplusplus.com/doc/tutorial/inheritance/
        friend class flStage;

        public:
        
        protected:
            bool _mouseEnabled;
            bool _buttonMode;
            bool _doubleClickEnabled;
            bool _mouseUpOutside;
        
            bool _tabEnabled;
            int	_tabIndex;
        
            //Stage���瑀�삳���
            bool __isMouseOver;
            bool __isRollOver;
            //�}�E�X����������
            bool __isMousePressed;
            //�}�E�X�𗣂�����
            bool __isMouseReleased;
            //�}�E�X��������Ă��邩
            bool __isMouseDown;
            //�t�H�[�J�X
            bool __isFocus;
        
        private:
        
        public:
            virtual void drop(ofDragInfo& info);
        
            virtual bool mouseEnabled();
            virtual void mouseEnabled(bool value);
        
            virtual bool buttonMode();
            virtual void buttonMode(bool value);
        
            virtual bool doubleClickEnabled();
            virtual void doubleClickEnabled(bool value);
        
            virtual bool mouseUpOutside();
            virtual void mouseUpOutside(bool value);
        
            virtual bool isMouseOver();
            virtual bool isRollOver();
            virtual bool isMouseDown();
    //        virtual bool isMousePressed();
    //        virtual bool isMouseReleased();
            virtual bool isFocus();
        
            //            virtual void focusOut();
        
        protected:
            flInteractiveObject();
            virtual ~flInteractiveObject();
        
        private:
        
    };
    
}
