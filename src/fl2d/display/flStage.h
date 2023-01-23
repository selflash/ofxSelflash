﻿/**
 
 Original code is julapy :: ofxFlash
 https://github.com/julapy/ofxFlash/blob/master/src/display/ofxFlashStage.h
 
 ActionScript3.0 Reference
 flash.display.Stage
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/display/Stage.html
 
 */

#pragma once

#include "ofMain.h"

#include "flUtil.h"
#include "flDefinition.h"
#include "flBlendMode.h"
#include "flDisplayObject.h"
#include "flDisplayObjectContainer.h"
#include "flMovieClip.h"
#include "flMouse.h"
#include "flKeyboard.h"
#include "flFocusEvent.h"
#include "flKeyboardEvent.h"
#include "flMouseEvent.h"

namespace fl2d {
    struct flSettings {
        bool manualUpdate = false;
        ofEventOrder updatePriority = OF_EVENT_ORDER_AFTER_APP;
        bool manualDraw = true;
        ofEventOrder drawPriority = OF_EVENT_ORDER_AFTER_APP;
        ofEventOrder mousePriority = OF_EVENT_ORDER_BEFORE_APP;
        ofEventOrder keyboardPriority = OF_EVENT_ORDER_BEFORE_APP;
        ofEventOrder windowPriority = OF_EVENT_ORDER_BEFORE_APP;

		flSettings(
			bool manualUpdate = false,
			ofEventOrder updatePriority = OF_EVENT_ORDER_AFTER_APP,
			bool manualDraw = true,
			ofEventOrder drawPriority = OF_EVENT_ORDER_AFTER_APP,
			ofEventOrder mousePriority = OF_EVENT_ORDER_BEFORE_APP,
			ofEventOrder keyboardPriority = OF_EVENT_ORDER_BEFORE_APP,
			ofEventOrder windowPriority = OF_EVENT_ORDER_BEFORE_APP
		) {
			this->manualUpdate = manualUpdate;
			this->updatePriority = updatePriority;
			this->manualDraw = manualDraw;
			this->drawPriority = drawPriority;
			this->mousePriority = mousePriority;
			this->keyboardPriority = keyboardPriority;
			this->windowPriority = windowPriority;
		}
    };
    
    class flStage : public flDisplayObjectContainer {
        public:
        
        protected:
        
        private:
            bool _isSetuped = false;
            flSettings _settings;
        
            static flStage* _instance;
            flMovieClip* _root = nullptr;
        
            int _stageWidth;
            int _stageHeight;
        
            bool _isTouchMode;
        
            int	_mouseX;
            int	_mouseY;
        
            //0 is left click.　2 is right click.
            int _mouseID;
            //Did click except left click.
            bool _isMouseChanged;
        
            //キーボードキーを押されているか
            //bool _isKeyDown;
            //キーボードキーを押したか
            //bool _isKeyPressed;
            //キーボードキーを離したか
            //bool _isKeyReleased;
        
            //Interactive objcet that is focused.
            flInteractiveObject* _focus = nullptr;
        
            //最前面でマウスにヒットしているDisplayObject
            flDisplayObject* _topMostHitDisplayObject = nullptr;
            flDisplayObject* _topMostHitDisplayObjectPrev = nullptr;
        
            //最前面でマウスにヒットしているInteractiveObject
            flInteractiveObject* _topMostHitInteractiveObject = nullptr;
            flInteractiveObject* _topMostHitInteractiveObjectPrev = nullptr;
        
            //マウスダウン中のInteractiveObject
            flInteractiveObject* _currentMouseDownInteractiveObject = nullptr;
        
            //マウスヒットオブジェクトからStageまでの順 [マウスヒットオブジェクト → Stageに最も近いオブジェクト]
            //vector<flInteractiveObject*> _lineTopDown;
            //vector<flInteractiveObject*> _lineTopDownPrev;
            //Stageからマウスヒットオブジェクトまでの順 [Stageに最も近いオブジェクト → マウスヒットオブジェクト]
            vector<flInteractiveObject*> _lineBottomUp;
            vector<flInteractiveObject*> _lineBottomUpPrev;  
			vector<flInteractiveObject*> _lineBottomUpForFocus;

			//Stageからマウスヒットオブジェクトまでの順 [マウスヒットオブジェクト → Stageに最も近いオブジェクト]
			//vector<ofPtr<flInteractiveObject>> _lineTopDown;
			//vector<ofPtr<flInteractiveObject>> _lineTopDownPrev;
   //         //マウスヒットオブジェクトからStageまでの順 [Stageに最も近いオブジェクト → マウスヒットオブジェクト]
			//vector<ofPtr<flInteractiveObject>> _lineBottomUp;
			//vector<ofPtr<flInteractiveObject>> _lineBottomUpPrev;

			float _startTime = 0.0;
        
    //        ofEventOrder _priority;
            bool _isPaused = false;
        
        public:
            static flStage* instance();
            static void clear();
        
            virtual void setup(flSettings settings = flSettings());
            virtual void update();
            virtual void draw();
    //        virtual void resize();
        
            int stageWidth();
            int stageHeight();
        
            virtual int mouseX();
            virtual int mouseY();
        
    //        virtual bool isMouseDown();
        
            flInteractiveObject* focus();
        
            flDisplayObject* topMostHitDisplayObject();
            flDisplayObject* topMostHitDisplayObjectPrev();
        
            flInteractiveObject* topMostHitInteractiveObject();
            flInteractiveObject* topMostHitInteractiveObjectPrev();
        
            flDisplayObject* getMostHitDisplayObject(int x, int y);
        
    //        void priority(ofEventOrder value);
            inline bool pause() { return _isPaused; }
            inline void pause(bool value) { _isPaused = value; }

        protected:
			virtual void _childEventHandler(flEvent& event);

        private:
            flStage();
            virtual ~flStage();
        
            //update
            void _updateChildrenOne(flDisplayObject* parent, vector<flDisplayObject*>& _children);
            void _updateMouse();
            //void _updateMouseInteraction();
            void _updateChildrenTwo(flDisplayObject* parent, vector<flDisplayObject*>& _children);
            //draw
            void _drawChildren(flDisplayObject* parent, vector<flDisplayObject*>& _children);
        
            void _mouseMove();
        
            flDisplayObject* _getMostHitDisplayObject(flDisplayObject* parent, vector<flDisplayObject*>& _children, int x, int y);
        
            void _debugDraw(flDisplayObject* parent, vector<flDisplayObject*>& _children);
        
            void _updateEventHandler(ofEventArgs& event);
            void _drawEventHandler(ofEventArgs& event);
        
            void _mouseMoveEventHandler(ofMouseEventArgs& event);
            void _mouseDragEventHandler(ofMouseEventArgs& event);
            void _mouseDownEventHandler(ofMouseEventArgs& event);
            void _mouseUpEventHandler(ofMouseEventArgs& event);
            void _mouseScrolledEventHandler(ofMouseEventArgs& event);
    //        void _mouseScrolledEventHandler(int x, int y, float scrollX, float scrollY);
            void _resizeEventHandler(ofResizeEventArgs& event);
        
            void _keyDownEventHandler(ofKeyEventArgs& event);
            void _keyUpEventHandler(ofKeyEventArgs& event);

			void _removeFromList(flDisplayObject* displayObject);

    };
    
}
