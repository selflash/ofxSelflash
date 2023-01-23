/**
 
 forked from liranuna
 http://www.liranuna.com/implementing-eventdispatcher-in-cpp/
 
 ActionScript3.0 Reference
 flash.events.EventDispatcher
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/events/EventDispatcher.html
 
 */

#pragma once

#include <string>
#include <map>
#include <list>

#include "flObject.h"
#include "flEvent.h"

namespace fl2d {
    
    class flEventDispatcher : public flObject {
        
        public:
        
        protected:
            void* _target = NULL;
            map<string, ofEvent<flEvent>> _listeners;
        
        private:
            bool _debugEnabled;
        
        public:
            flEventDispatcher();
            virtual ~flEventDispatcher();
        
            //--------------------------------------------------------------
            //
            template <typename ArgumentsType, class ListenerClass>
            inline void addEventListener(
                                         string eventName,
                                         ListenerClass* listener,
                                         void(ListenerClass::*listenerMethod)(ArgumentsType&),
                                         int priority = OF_EVENT_ORDER_AFTER_APP
                                         ) {
                _listeners[eventName].remove(listener, listenerMethod, priority);
                _listeners[eventName].add(listener, listenerMethod, priority);
            }
        
            //--------------------------------------------------------------
            //
            template <typename ArgumentsType, class ListenerClass>
            inline void removeEventListener(
                                            string eventName,
                                            ListenerClass* listener,
                                            void(ListenerClass::*listenerMethod)(ArgumentsType&),
                                            int priority = OF_EVENT_ORDER_AFTER_APP
                                            ) {
                _listeners[eventName].remove(listener, listenerMethod, priority);
            }
        
            //--------------------------------------------------------------
            //
            inline void removeEventListeners(string eventName) {
                _listeners.erase(eventName);
            }
        
            //--------------------------------------------------------------
            //
            inline void removeAllEventListeners() { _listeners.clear(); }
        
            //--------------------------------------------------------------
            //
            inline bool hasEventListener(string type) {
                //if(_debugEnabled) cout << "[flEventDispatcher]hasEventListener(" + type + ")" << endl;
                //if(_handlers.size() == 0) return false;
                bool check = bool(_listeners.find(type) != _listeners.end());
                //if(_debugEnabled) cou・＿・t << "check = " << check << endl;
                return check;
            }
        
            virtual void dispatchEvent(flEvent* event, bool destry = true);
        
        protected:
            //            flEventDispatcher();
            //            ~flEventDispatcher();
        
        private:
        
    };
    
}
