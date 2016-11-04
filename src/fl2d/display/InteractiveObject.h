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

#include "DisplayObject.h"
#include "../events/FocusEvent.h"
#include "../events/MouseEvent.h"

namespace fl2d {
    class Stage;

    class InteractiveObject : public DisplayObject {
        
        public:
            // friends! http://www.cplusplus.com/doc/tutorial/inheritance/
            friend class Stage;
            
        protected:
            bool _mouseEnabled;
            bool _buttonMode;
            bool _doubleClickEnabled;
            bool _mouseUpOutside;
            
            bool _tabEnabled;
            int	_tabIndex;
            
            //Stageから操作される
            bool __isMouseOver;
            bool __isRollOver;
            //マウスが押されているか
            bool __isMouseDown;
            //マウスを押したか
            bool __isMousePressed;
            //マウスを離したか
            bool __isMouseReleased;
            //フォーカス
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
            virtual bool isFocus();
        
        protected:
            InteractiveObject();
            ~InteractiveObject();
            
        private:
            
    };
    
}