/**
 
 ActionScript3.0 Reference
 flash.events.Event
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/events/Event.html
 
 */

#pragma once

#include <string>
#include "../core/Object.h"

namespace fl2d {
    
    class Event : public Object {
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
            //static string ENTER_FRAME;
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
        
            void* _currentTarget;
            void* _target;
            void* _listener;
        
        private:
        
        public:
            Event(string type);
            ~Event();
            
            virtual Event* clone();
            
            virtual const string& type();
        
//            virtual const string& data();

            virtual void* currentTarget();
            virtual void currentTarget(void* value);
        
            virtual void* target();
            virtual void target(void* value);
        
            virtual void* listener();
        
            template <class T>
            T data() { return getProperty<T>("data"); }
        
        protected:
            
        private:
            template <class T>
            void data(T value) { setProperty<T>("data", value); }
        
    };
    
}