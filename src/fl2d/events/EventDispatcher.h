/**
 
 forked from liranuna
 http://www.liranuna.com/implementing-eventdispatcher-in-cpp/
 
 ActionScript3.0 Reference
 flash.events.EventDispatcher
 http://help.adobe.com/ja_JP/FlashPlatform/reference/actionscript/3/flash/events/EventDispatcher.html
 
 [memo]
 * allFunctions = 2次元配列
 */

#pragma once

#include <string>
#include <map>
#include <list>

#include "../core/Object.h"
#include "Event.h"
#include "EventHandler.h"

namespace fl2d {
    
    class EventDispatcher : public Object {
        
        public:
            
        protected:
            void *_target;
            
        private:
            bool _debugEnabled;
        
            typedef EventHandler<float> Handler;
            Handler handler;
            std::map<const string, std::map<int, std::vector<Handler> > > _eventHandlerList;
            
            string _isDispatchEvent;
            string _removeEventType;
            
        public:
            EventDispatcher();
            ~EventDispatcher();
            
            //--------------------------------------------------------------
            //
            template <class ListenerClass>
            void addEventListener(const string& type, ListenerClass* listener, void(ListenerClass::*listenerMethod)(Event& event), const bool& useCapture = false, const int& priority = 0) {
                if(_debugEnabled) cout << "======================================" << endl;
                if(_debugEnabled) cout << "[EventDispatcher]addEventListener(" << type << ", " << listener << ", " << &listenerMethod << ")" << endl;
                
                //------------------------------------
                //登録されているか調べる
                bool check = false;
                
                std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[type];
                std::map<int, std::vector<Handler> >::iterator i1 = allFunctions.begin();
                std::map<int, std::vector<Handler> >::iterator l1 = allFunctions.end();
                if(_debugEnabled) cout << "allFunctions.size = " << allFunctions.size() << endl;
                
                for(i1; i1 != l1; ++i1) {
                    std::vector<Handler> &funcList = i1->second;
                    std::vector<Handler>::iterator i2 = funcList.begin();
                    std::vector<Handler>::iterator l2 = funcList.end();
                    
                    if(_debugEnabled) cout << "funcList.size = " << funcList.size() << endl;
                    
                    for(i2; i2 != l2; ++i2) {
                        if(_debugEnabled) cout << "i2->listener = " << i2->listener << endl;
                        if(_debugEnabled) cout << "i2->func = " << i2->func << endl;
                        if(_debugEnabled) cout << "&listenerMethod = " << &listenerMethod << endl;
                        if(_debugEnabled) cout << "check = " << bool(i2->listener == listener && i2->func == &listenerMethod) << endl;
                        //↓魔法のおまじない。これがないとなぜかダメ、、
                        //cout << "[EventDispatcher]hasEventListener2 " << listenerMethod << endl;
                        check = bool(i2->listener == listener && i2->func == &listenerMethod);
                    }
                }
                if(check) {
                    if(_debugEnabled) cout << type << "イベントのハンドラは既に登録済みです" << endl;
                    return;
                }
                //------------------------------------
                
                //------------------------------------
                //ÁôªÈå≤„Åô„Çã
                handler = new Handler::T<ListenerClass>(listener, listenerMethod);
                handler.listener = listener;
                handler.func = &listenerMethod;
                if(_debugEnabled) cout << "登録する" << endl;
                if(_debugEnabled) cout << "listener " << listener << endl;
                if(_debugEnabled) cout << "&listenerMethod " << &listenerMethod << endl;
                if(_debugEnabled) cout << "handler.func " << handler.func << endl;
                _eventHandlerList[type][priority].push_back(handler);
                //------------------------------------
                if(_debugEnabled) cout << "======================================" << endl;
            }
        
            //--------------------------------------------------------------
            //
            template <class ListenerClass>
            void removeEventListener(const string& type, ListenerClass* listener, void (ListenerClass::*listenerMethod)(Event& event)) {
                if(_debugEnabled) cout << "======================================" << endl;
                if(_debugEnabled) cout << "[EventDispatcher]removeEventListener(" << type <<  ", " << listener << ", " << &listenerMethod << ")" << endl;
                
                //------------------------------------
                //登録されているか調べる
                if(!hasEventListener(type)) {
                    if(_debugEnabled) cout << type << "は登録されていません" << endl;
                    return;
                }
                //------------------------------------
                
                //------------------------------------
                if(_isDispatchEvent == type) {
                    if(_debugEnabled) cout << type << "イベントはDispath中です" << endl;
                    
                    //あとでRemoveしないといけないイベントのタイプを保持しておく
                    _removeEventType = type;
                    
                    
                    std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[type];
                    std::map<int, std::vector<Handler> >::iterator i1 = allFunctions.begin();
                    std::map<int, std::vector<Handler> >::iterator l1 = allFunctions.end();
                    
                    for(i1; i1 != l1; ++i1) {
                        std::vector<Handler> &funcList = i1->second;
                        std::vector<Handler>::iterator i2 = funcList.begin();
                        std::vector<Handler>::iterator l2 = funcList.end();
                        for(i2; i2 != l2; ++i2) {
                            if(_debugEnabled) cout << "i2->listener = " << i2->listener << endl;
                            if(_debugEnabled) cout << "i2->func = " << i2->func << endl;
                            if(_debugEnabled) cout << "&listenerMethod = " << &listenerMethod << endl;
                            if(_debugEnabled) cout << "check = " << bool(i2->func == &listenerMethod) << endl;
                            //↓魔法のおまじない。これがないとなぜかダメ、、
                            //if(_debugEnabled) cout << "[EventDispatcher]removeEventListener" << listenerMethod << endl;
                            //if(_debugEnabled) cout << "[EventDispatcher]removeEventListener" << &listenerMethod << endl;
                            bool check = bool(i2->func == &listenerMethod);
                            //TODO
                            if(check) i2->remove = true;
                            if(_debugEnabled) cout << "[remove] = " << i2->remove << endl;
                        }
                    }
                } else {
                    if(_debugEnabled) cout << type << "のハンドラは今すぐRemoveできます" << endl;
                    
                    std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[type];
                    std::map<int, std::vector<Handler> >::iterator i1 = allFunctions.begin();
                    std::map<int, std::vector<Handler> >::iterator l1 = allFunctions.end();
                    
                    if(_debugEnabled) cout << "allFunctions.size = " << allFunctions.size() << endl;
                    
                    for(i1; i1 != l1; ++i1) {
                        std::vector<Handler> &funcList = i1->second;
                        std::vector<Handler>::iterator i2 = funcList.begin();
                        std::vector<Handler>::iterator l2 = funcList.end();
                        
                        if(_debugEnabled) cout << "[削除前]funcList.size = " << funcList.size() << endl;
                        
                        for(i2; i2 != l2; ++i2) {
                            if(_debugEnabled) cout << "i2->listener = " << i2->listener << endl;
                            if(_debugEnabled) cout << "i2->func = " << i2->func << endl;
                            if(_debugEnabled) cout << "&listenerMethod = " << &listenerMethod << endl;
                            if(_debugEnabled) cout << "check = " << bool(i2->func == &listenerMethod) << endl;
                            //↓魔法のおまじない。これがないとなぜかダメ、、
                            //if(_debugEnabled) cout << "[EventDispatcher]removeEventListener" << listenerMethod << endl;
                            if(i2->func == &listenerMethod) funcList.erase(i2);
                        }
                        
                        if(i1->second.empty()) allFunctions.erase(i1);
                        
                        if(_debugEnabled) cout << "[削除後]funcList.size = " << funcList.size() << endl;
                    }
                    
                    if(allFunctions.empty()) _eventHandlerList.erase(type);
                    
                    if(_debugEnabled) cout << type << " " << allFunctions.size() << endl;
                }
                //------------------------------------
                if(_debugEnabled) cout << "======================================" << endl;
            }
        
            //--------------------------------------------------------------
            //
            template <class ListenerClass>
            void removeEventListener(const string& type, void (ListenerClass::*listenerMethod)(Event& event)) {
                if(_debugEnabled) cout << "======================================" << endl;
                if(_debugEnabled) cout << "[EventDispatcher]removeEventListener(" << type <<  ", " << &listenerMethod << ")" << endl;
                
                //------------------------------------
                //登録されているか調べる
                if(!hasEventListener(type)) {
                    if(_debugEnabled) cout << type << "は登録されていません" << endl;
                    return;
                }
                //------------------------------------
                
                //------------------------------------
                if(_isDispatchEvent == type) {
                    if(_debugEnabled) cout << type << "イベントはDispath中です" << endl;
                    
                    //あとでRemoveしないといけないイベントのタイプを保持しておく
                    _removeEventType = type;
                    
                    
                    std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[type];
                    std::map<int, std::vector<Handler> >::iterator i1 = allFunctions.begin();
                    std::map<int, std::vector<Handler> >::iterator l1 = allFunctions.end();
                    
                    for(i1; i1 != l1; ++i1) {
                        std::vector<Handler> &funcList = i1->second;
                        std::vector<Handler>::iterator i2 = funcList.begin();
                        std::vector<Handler>::iterator l2 = funcList.end();
                        for(i2; i2 != l2; ++i2) {
                            if(_debugEnabled) cout << "i2->listener = " << i2->listener << endl;
                            if(_debugEnabled) cout << "i2->func = " << i2->func << endl;
                            if(_debugEnabled) cout << "&listenerMethod = " << &listenerMethod << endl;
                            if(_debugEnabled) cout << "check = " << bool(i2->func == &listenerMethod) << endl;
                            //↓魔法のおまじない。これがないとなぜかダメ、、
                            //if(_debugEnabled) cout << "[EventDispatcher]removeEventListener" << listenerMethod << endl;
                            //if(_debugEnabled) cout << "[EventDispatcher]removeEventListener" << &listenerMethod << endl;
                            bool check = bool(i2->func == &listenerMethod);
                            //TODO
                            if(check) i2->remove = true;
                            if(_debugEnabled) cout << "[remove] = " << i2->remove << endl;
                        }
                    }
                } else {
                    if(_debugEnabled) cout << type << "のハンドラは今すぐRemoveできます" << endl;
                    
                    std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[type];
                    std::map<int, std::vector<Handler> >::iterator i1 = allFunctions.begin();
                    std::map<int, std::vector<Handler> >::iterator l1 = allFunctions.end();
                    
                    if(_debugEnabled) cout << "allFunctions.size = " << allFunctions.size() << endl;
                    
                    for(i1; i1 != l1; ++i1) {
                        std::vector<Handler> &funcList = i1->second;
                        std::vector<Handler>::iterator i2 = funcList.begin();
                        std::vector<Handler>::iterator l2 = funcList.end();
                        
                        if(_debugEnabled) cout << "[削除前]funcList.size = " << funcList.size() << endl;
                        
                        for(i2; i2 != l2; ++i2) {
                            if(_debugEnabled) cout << "i2->listener = " << i2->listener << endl;
                            if(_debugEnabled) cout << "i2->func = " << i2->func << endl;
                            if(_debugEnabled) cout << "&listenerMethod = " << &listenerMethod << endl;
                            if(_debugEnabled) cout << "check = " << bool(i2->func == &listenerMethod) << endl;
                            //↓魔法のおまじない。これがないとなぜかダメ、、
                            //if(_debugEnabled) cout << "[EventDispatcher]removeEventListener" << listenerMethod << endl;
                            if(i2->func == &listenerMethod) funcList.erase(i2);
                        }
                        
                        if(i1->second.empty()) allFunctions.erase(i1);
                        
                        if(_debugEnabled) cout << "[削除後]funcList.size = " << funcList.size() << endl;
                    }
                    
                    if(allFunctions.empty()) _eventHandlerList.erase(type);
                }
                //------------------------------------
                if(_debugEnabled) cout << "======================================" << endl;
            }
        
            //--------------------------------------------------------------
            //
            void removeEventListener(const string& type) {
                if(_debugEnabled) cout << "======================================" << endl;
                if(_debugEnabled) cout << "[EventDispatcher]removeEventListener(" << type << ")" << endl;
                
                //------------------------------------
                //登録されているか調べる
                if(!hasEventListener(type)) {
                    if(_debugEnabled) cout << type << "は登録されていません" << endl;
                    return;
                }
                //------------------------------------
                
                //------------------------------------
                if(_isDispatchEvent == type) {
                    if(_debugEnabled) cout << type << "イベントはDispath中です" << endl;
                    
                    //あとでRemoveしないといけないイベントのタイプを保持しておく
                    _removeEventType = type;
                    
                    std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[type];
                    std::map<int, std::vector<Handler> >::iterator i1 = allFunctions.begin();
                    std::map<int, std::vector<Handler> >::iterator l1 = allFunctions.end();
                    
                    for(i1; i1 != l1; ++i1) {
                        std::vector<Handler> &funcList = i1->second;
                        std::vector<Handler>::iterator i2 = funcList.begin();
                        std::vector<Handler>::iterator l2 = funcList.end();
                        for(i2; i2 != l2; ++i2) {
                            if(_debugEnabled) cout << "i2->func = " << i2->func << endl;
                            i2->remove = true;
                        }
                    }
                } else {
                    if(_debugEnabled) cout << type << "のハンドラは今すぐRemoveできます" << endl;
                    
                    std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[type];
                    if(_debugEnabled) cout << "allFunctions.size = " << allFunctions.size() << endl;
                    allFunctions.clear();
                    _eventHandlerList.erase(type);
                    if(_debugEnabled) cout << "allFunctions.size = " << allFunctions.size() << endl;
                }
                //------------------------------------
                if(_debugEnabled) cout << "======================================" << endl;
            }
        
            //--------------------------------------------------------------
            //
            template <class ListenerClass>
            void removeEventListener(const string& type, ListenerClass* listener) {
                if(_debugEnabled) cout << "======================================" << endl;
                if(_debugEnabled) cout << "[EventDispatcher]removeEventListener(" << type <<  ", " << listener << ")" << endl;
                
                //------------------------------------
                //登録されているか調べる
                if(!hasEventListener(type)) {
                    if(_debugEnabled) cout << type << "は登録されていません" << endl;
                    return;
                }
                //------------------------------------
                
                //------------------------------------
                if(_isDispatchEvent == type) {
                    if(_debugEnabled) cout << type << "イベントはDispath中です" << endl;
                    
                    //あとでRemoveしないといけないイベントのタイプを保持しておく
                    _removeEventType = type;
                    
                    std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[type];
                    std::map<int, std::vector<Handler> >::iterator i1 = allFunctions.begin();
                    std::map<int, std::vector<Handler> >::iterator l1 = allFunctions.end();
                    
                    for(i1; i1 != l1; ++i1) {
                        std::vector<Handler> &funcList = i1->second;
                        std::vector<Handler>::iterator i2 = funcList.begin();
                        std::vector<Handler>::iterator l2 = funcList.end();
                        for(i2; i2 != l2; ++i2) {
                            if(_debugEnabled) cout << "i2->listener = " << i2->listener << endl;
                            if(_debugEnabled) cout << "&listener = " << listener << endl;
                            if(_debugEnabled) cout << "i2->func = " << i2->func << endl;
                            
                            bool check = bool(i2->listener == listener);
                            if(_debugEnabled) cout << "check = " << check << endl;
                            if(check) i2->remove = true;
                            if(_debugEnabled) cout << "[remove] = " << i2->remove << endl;
                        }
                    }
                } else {
                    if(_debugEnabled) cout << type << "のハンドラは今すぐRemoveできます" << endl;
                    
                    std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[type];
                    std::map<int, std::vector<Handler> >::iterator i1 = allFunctions.begin();
                    std::map<int, std::vector<Handler> >::iterator l1 = allFunctions.end();
                    
                    if(_debugEnabled) cout << "allFunctions.size = " << allFunctions.size() << endl;
                    
                    for(i1; i1 != l1; ++i1) {
                        std::vector<Handler> &funcList = i1->second;
                        std::vector<Handler>::iterator i2 = funcList.begin();
                        std::vector<Handler>::iterator l2 = funcList.end();
                        
                        if(_debugEnabled) cout << "[削除前]funcList.size = " << funcList.size() << endl;
                        
                        for(i2; i2 != l2; ++i2) {
                            if(_debugEnabled) cout << "i2->listener = " << i2->listener << endl;
                            if(_debugEnabled) cout << "&listener = " << listener << endl;
                            if(_debugEnabled) cout << "i2->func = " << i2->func << endl;
                            
                            bool check = bool(i2->listener == listener);
                            if(_debugEnabled) cout << "check = " << check << endl;
                            if(check) funcList.erase(i2);
                        }
                        
                        if(i1->second.empty()) allFunctions.erase(i1);
                        
                        if(_debugEnabled) cout << "[削除後]funcList.size = " << funcList.size() << endl;
                    }
                    
                    if(allFunctions.empty()) _eventHandlerList.erase(type);
                    
                    if(_debugEnabled) cout << type << " " << allFunctions.size() << endl;
                }
                //------------------------------------
                if(_debugEnabled) cout << "======================================" << endl;
            }
        
            //--------------------------------------------------------------
            //
            void removeAllEventListener() {
                if(_debugEnabled) cout << "======================================" << endl;
                if(_debugEnabled) cout << "[EventDispatcher]removeAllEventListener()" << endl;
                
                if(_debugEnabled) cout << _eventHandlerList.size() << endl;
                _eventHandlerList.clear();
                if(_debugEnabled) cout << _eventHandlerList.size() << endl;
            }
        
            //--------------------------------------------------------------
            //
            bool hasEventListener(const string& type) {
                //if(_debugEnabled) cout << "[EventDispatcher]hasEventListener(" + type + ")" << endl;
                //if(_eventHandlerList.size() == 0) return false;
                bool check = bool(_eventHandlerList.find(type) != _eventHandlerList.end());
                //if(_debugEnabled) cou・＿・t << "check = " << check << endl;
                return check;
            }
        
            //--------------------------------------------------------------
            //
            void dispatchEvent(Event* event) {
                if(_debugEnabled) cout << "======================================" << endl;
                if(_debugEnabled) cout << "[EventDispatcher]dispatchEvent(" + event->type() + ")" << endl;
                
                //------------------------------------
                if(!hasEventListener(event->type())) return;
                //------------------------------------
                
                _isDispatchEvent = event->type();
                
                //------------------------------------
                event->currentTarget(_target);
                if(!event->target()) event->target(_target);
                //------------------------------------
                
                //------------------------------------
                std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[event->type()];
                std::map<int, std::vector<Handler> >::reverse_iterator i1 = allFunctions.rbegin();
                std::map<int, std::vector<Handler> >::reverse_iterator l1 = allFunctions.rend();
                for(i1; i1 != l1; ++i1) {
                    std::vector<Handler> &funcList = i1->second;
                    std::vector<Handler>::iterator i2 = funcList.begin();
                    std::vector<Handler>::iterator l2 = funcList.end();
                    for(i2; i2 != l2; ++i2) {
                        if(_debugEnabled) cout << "i2->listener = " << i2->listener << endl;
                        if(_debugEnabled) cout << "i2->func = " << i2->func << endl;
//                        if(_debugEnabled) cout << "&listenerMethod = " << &listenerMethod << endl;
                        
                        (*i2)(*event);
                    }
                }
                //------------------------------------
                
                _isDispatchEvent = "";
                
                //------------------------------------
                //Removeしないといけないイベントハンドラがあったら仕事をこなす
                if(event->type() == _removeEventType) {
                    if(_debugEnabled) cout << event->type() << "イベントがDispath中でRemoveできなかったハンドラを削除します" << endl;
                    
                    if(_eventHandlerList.count(event->type()) == 0) {
                        if(_debugEnabled) cout << event->type() << "キーは存在しない " << endl;
                        _removeEventType = "";
                        delete event;
                        if(_debugEnabled) cout << "======================================" << endl;
                        return;
                    }
                    
                    std::map<int, std::vector<Handler> > &allFunctions = _eventHandlerList[event->type()];
                    std::map<int, std::vector<Handler> >::iterator _i1 = allFunctions.begin();
                    std::map<int, std::vector<Handler> >::iterator _l1 = allFunctions.end();
                    
                    if(_debugEnabled) cout << "allFunctions.size = " << allFunctions.size() << endl;
                    
//                    int i; int l;
//                    int j; int k;
//                    l = allFunctions.size();
//                    for(i = 0; i < l; i++) {
//                        std::vector<Handler> handler = allFunctions[i];
//                        k = handler.size();
//                        for(j = 0; j < k; j++) {
//
//                        }
//                    }

//                    cout << "_eventHandlerList.count(event->type()) == 1 =" << _eventHandlerList.count(event->type()) << endl;
//                    cout << "allFunctions.size() = " << allFunctions.size() << endl;
//                    cout << "_i1 = " << &_i1 << endl;
//                    cout << "_l1 = " << &_l1 << endl;
                    if(_eventHandlerList.count(event->type()) == 1 && allFunctions.size() != 0) {
//                        _eventHandlerList.erase(event->type());
//                        goto SKIP1;
                        
                        for(_i1; _i1 != _l1; ++_i1) {
                            std::vector<Handler> &funcList = _i1->second;
                            std::vector<Handler>::iterator _i2 = funcList.begin();
                            std::vector<Handler>::iterator _l2 = funcList.end();
                            
                            if(_debugEnabled) cout << "[削除前]funcList.size = " << funcList.size() << endl;
                            
                            for(_i2; _i2 != _l2; ++_i2) {
                                if(_debugEnabled) cout << "[remove] = " << _i2->remove << endl;
                                if(_i2->remove) funcList.erase(_i2);
                            }
                            
                            if(_i1->second.empty()) allFunctions.erase(_i1);
                            
                            if(_debugEnabled) cout << "[削除後]funcList.size = " << funcList.size() << endl;
                        }
                    }
                    
                    if(allFunctions.empty()) _eventHandlerList.erase(event->type());
                    
                    _removeEventType = "";
                    
                    if(_debugEnabled) cout << "allFunctions.size = " << allFunctions.size() << endl;
                }
                //------------------------------------
                
                SKIP1:
                
                //ÂæåÂßãÊú´
                delete event;
                if(_debugEnabled) cout << "======================================" << endl;
            }
        
        protected:
//            EventDispatcher();
//            ~EventDispatcher();
        
        private:
        
    };
    
}
