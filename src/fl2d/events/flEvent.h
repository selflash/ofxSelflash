/**
 
 ActionScript3.0 Reference
 flash.events.Event
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/events/Event.html
 
 */

#pragma once

#include <string>
#include "flObject.h"

namespace fl2d {
    
    class flEventDispatcher;
    class flEvent : public flObject {
        friend flEventDispatcher;

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
            static string INIT;
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
        
            //イベントリスナーを登録した EventDispatcher と必ず一致するのは currentTarget
            void* __currentTarget;
            void* __target;
        
        private:
        
        public:
            flEvent(string type);
            virtual ~flEvent();
        
            virtual inline flEvent* clone() { return new flEvent(_type); }
        
            virtual inline string type() { return _type; }
        
            //            virtual const string& data();
        
            //https://n2works.net/columns/16
            //直接クリックされたオブジェクトがtargetプロパティに格納され、currentTargetにはイベントリスナが関連付けられたオブジェクトが格納される。
            //イベントリスナを関連付けているオブジェクトをEvent継承クラスから取得するにはcurrentTargetを参照するべき。
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
