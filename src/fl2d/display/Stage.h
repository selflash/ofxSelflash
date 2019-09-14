/**
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashStage.h
 
 ActionScript3.0 Reference
 flash.display.Stage
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Stage.html
 
 */

#pragma once

#include "ofMain.h"

#include "FlashConfig.h"
#include "BlendMode.h"
#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "MovieClip.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "FocusEvent.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"

namespace fl2d {
    
    class Stage : public DisplayObjectContainer {
    public:
        
    protected:
        
    private:
        static Stage* _instance;
        MovieClip* _root;
        
        int _stageWidth;
        int _stageHeight;
        
        bool _isTouchMode;
        
        int	_mouseX;
        int	_mouseY;
        
        //0 = 左クリック　2 = 右クリック
        int _mouseID;
        //左クリック以外をしたか
        bool _isMouseChanged;
        
        //キーボードキーを押されているか
        //bool _isKeyDown;
        //キーボードキーを押したか
        //bool _isKeyPressed;
        //キーボードキーを離したか
        //bool _isKeyReleased;
        
        //キーボードフォーカスを持つインタラクティブオブジェクト
        InteractiveObject* _focus;
        
        //最前面でマウスにヒットしているDisplayObject
        DisplayObject* _topMostHitDisplayObject;
        DisplayObject* _topMostHitDisplayObjectPrev;
        
        //最前面でマウスにヒットしているInteractiveObject
        InteractiveObject* _topMostHitInteractiveObject;
        InteractiveObject* _topMostHitInteractiveObjectPrev;
        
        //マウスダウン中のInteractiveObject
        InteractiveObject* _currentMouseDownInteractiveObject;
        
        //Stageからマウスヒットオブジェクトまでの順 [マウスヒットオブジェクト → Stageに最も近いオブジェクト]
        vector<InteractiveObject*> _lineTopDown;
        vector<InteractiveObject*> _lineTopDownPrev;
        //マウスヒットオブジェクトからStageまでの順 [Stageに最も近いオブジェクト → マウスヒットオブジェクト]
        vector<InteractiveObject*> _lineBottomUp;
        vector<InteractiveObject*> _lineBottomUpPrev;
        
        ofEventOrder _priority;
        
    public:
        static Stage* instance();
        static void clear();
        
        virtual void setup();
        virtual void update();
        virtual void draw();
        //            virtual void resize();
        
        int stageWidth();
        int stageHeight();
        
        virtual int mouseX();
        virtual int mouseY();
        
        //            virtual bool isMouseDown();
        
        InteractiveObject* focus();
        
        DisplayObject* topMostHitDisplayObject();
        DisplayObject* topMostHitDisplayObjectPrev();
        
        InteractiveObject* topMostHitInteractiveObject();
        InteractiveObject* topMostHitInteractiveObjectPrev();
        
        DisplayObject* getMostHitDisplayObject(int x, int y);
        
        void priority(ofEventOrder value);
        
    protected:
        
    private:
        Stage();
        virtual ~Stage();
        
        //update
        void _updateChildrenOne(DisplayObject* parent, vector<DisplayObject*>& children);
        void _updateMouse();
        //void _updateMouseInteraction();
        void _updateChildrenTwo(DisplayObject* parent, vector<DisplayObject*>& children);
        //draw
        void _drawChildren(DisplayObject* parent, vector<DisplayObject*>& children);
        
        void _mouseMove();
        
        DisplayObject* _getMostHitDisplayObject(DisplayObject* parent, vector<DisplayObject*>& children, int x, int y);
        
        void _debugDraw(DisplayObject* parent, vector<DisplayObject*>& children);
        
        void _updateEventHandler(ofEventArgs& event);
        void _drawEventHandler(ofEventArgs& event);
        
        void _mouseMoveEventHandler(ofMouseEventArgs& event);
        void _mouseDragEventHandler(ofMouseEventArgs& event);
        void _mouseDownEventHandler(ofMouseEventArgs& event);
        void _mouseUpEventHandler(ofMouseEventArgs& event);
        void _mouseScrolledEventHandler(ofMouseEventArgs& event);
        //            void _mouseScrolledEventHandler(int x, int y, float scrollX, float scrollY);
        void _resizeEventHandler(ofResizeEventArgs& event);
        
        void _keyDownEventHandler(ofKeyEventArgs& event);
        void _keyUpEventHandler(ofKeyEventArgs& event);
        
        bool _isInteractiveObject(DisplayObject* displayObject);
        bool _isDisplayObject(DisplayObject* displayObject);
        bool _isDisplayObjectContainer(DisplayObject* displayObject);
        bool _isSprite(DisplayObject* displayObject);
    };
    
}
