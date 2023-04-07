/**
 
 ActionScript3.0 Reference
 flash.events.Event
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/events/Event.html
 
 */

/**
e.target =マウスの下にあるもの（ベンが言うように...イベントをトリガーするもの）。 e.currentTarget =ドットの前のもの...（以下を参照）

したがって、インスタンス名が「btns」のクリップ内に10個のボタンがあり、次のようにするとします。

---------------------------------------------------
btns.addEventListener(MouseEvent.MOUSE_OVER, onOver);
// btns = the thing before the dot of an addEventListener call

function onOver(e:MouseEvent):void{
	trace(e.target.name, e.currentTarget.name);
}
---------------------------------------------------

e.targetは10個のボタンの1つであり、e.currentTargetは常に「btns」クリップです。

MouseEventをROLL_OVERに変更した場合、またはプロパティbtns.mouseChildrenをfalseに設定した場合、e.targetとe.currentTargetは両方とも常に「btns」になることに注意してください。

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

			//[読み取り専用] イベントがバブリングイベントかどうかを示します。
			bool _bubbles = false;
			//[読み取り専用] イベントに関連付けられた動作を回避できるかどうかを示します。
			bool _cancelable = false;
			//[読み取り専用] イベントフローの現在の段階です。
			int _eventPhase = 0;

            //イベントリスナーを登録した EventDispatcher と必ず一致するのは currentTarget
			//イベントリスナーで Event オブジェクトをアクティブに処理しているオブジェクトです。
			//例えば、ユーザーが「OK」をクリックした場合、currentTarget は、そのボタンまたは、そのイベントに対してイベントリスナーを登録している祖先の 1 つを含むノードになります。
            void* __currentTarget;

			//直接または DisplayObject インスタンスが含まれているサブツリーを追加することで、オンステージ表示リストに追加される DisplayObject インスタンスです。
			//DisplayObject インスタンスが直接追加される場合、このイベントの前に added イベントが発生します。
			//イベントターゲットです。このプロパティにはターゲットノードが含まれます。
			//例えば、ユーザーが「OK」をクリックした場合、ターゲットノードはそのボタンを含む表示リストノードです。
            void* __target;
        
        private:
        
        public:
            flEvent(string type, bool bubbles = false, bool cancelable = false);
            virtual ~flEvent();
        
			//Event サブクラスのインスタンスを複製します。
            virtual inline flEvent* clone() { return new flEvent(_type); }

			//カスタム ActionScript 3.0 Event クラスに toString() メソッドを実装するためのユーティリティ関数です。
			//virtual inline string formatToString(string className, ... arguments);
			//イベントで preventDefault() メソッドが呼び出されたかどうかを確認します。
			//virtual bool isDefaultPrevented();
			//イベントのデフォルト動作をキャンセルできる場合に、その動作をキャンセルします。
			//virtual void preventDefault();
			//イベントフローの現在のノードおよび後続するノードで、イベントリスナーが処理されないようにします。
			//virtual void stopImmediatePropagation();
			//イベントフローの現在のノードに後続するノードで、イベントリスナーが処理されないようにします。
			//virtual void stopPropagation();

        
            virtual inline string type() { return _type; }
        
            //virtual const string& data();
        
            //https://n2works.net/columns/16
            //直接クリックされたオブジェクトがtargetプロパティに格納され、currentTargetにはイベントリスナが関連付けられたオブジェクトが格納される。
            //イベントリスナを関連付けているオブジェクトをEvent継承クラスから取得するにはcurrentTargetを参照するべき。
            virtual inline void* currentTarget() { return __currentTarget; }
            virtual inline void currentTarget(void* value) { __currentTarget = value; }
        
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
