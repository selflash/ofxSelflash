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
         //Alt キーがアクティブになっているか
         void altKey(bool value);
         bool altKey();
         //マウスの主ボタンが押されているか
         void buttonDown(bool value);
         bool buttonDown();
         //Ctrl キーがアクティブになっているか
         void ctrlKey(bool value);
         bool ctrlKey();
         //Shift キーがアクティブになっているか
         void shiftKey(bool value);
         bool shiftKey();
         
         //スプライトを基準とするイベント発生位置の水平座標
         void localX(float value);
         float localX();
         //スプライトを基準とするイベント発生位置の垂直座標
         void localY(float value);
         float localY();
         
         //グローバルステージ座標を基準とするイベント発生位置の水平座標
         float stageX();
         //グローバルステージ座標を基準とするイベント発生位置の垂直座標
         float stageY();
         
         //イベントに関連する表示リストオブジェクトへの参照
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
