#pragma once

#include "ofMain.h"

#include "Event.h"

namespace fl2d {
    template <typename Arg>
    class EventHandler {
        //プライベートクラス
        private:
            class Base {
            public:
                virtual ~Base() { }
                virtual void operator()(Event& event) = 0;
            };
            Base* pointerino;
            bool _assigned;
        
        public:
            bool remove;
            
            bool inited;
            
            void* listener;
            void* func;
        
        private:
        
        public:
        
            //--------------------------------------------------------------
            //
            template <typename Class>
            class T : public Base {
                // Signature applied to a pointer-to-member for target class.
                typedef void (Class::*Func)(Event& event);
                    
                public:
                    T(Class* aThis, void (Class::*aFunc)(Event& event)) : mThis(aThis), mFunc(aFunc) { }
                    virtual void operator()(Event& event) { return (mThis->*mFunc)(event); }
                
                    // Pointer to the object we are delegating to.
                    Class* mThis;
                    // Address of the function on the delegate object.
                    Func mFunc;
                
                private:
                
            };
            
            //--------------------------------------------------------------
            //
            EventHandler() {
                _assigned = false;
                remove = false;
                listener = NULL;
                func = NULL;
                inited = true;
            }
            //--------------------------------------------------------------
            //
            ~EventHandler() {
                //delete pointerino;
                pointerino = NULL;
                _assigned = false;
                remove = false;
                listener = NULL;
                func = NULL;
                //destroy();
            }
        
            //--------------------------------------------------------------
            //
            void destroy() {
    /*
                cout << "EventHandler destry()" << inited << endl;
                if (_assigned) {
                    //cout << "there is a pointerino" << endl;
                    delete pointerino;
                    pointerino = NULL;
                }
                _assigned = false;
                //cout << "deleting pointerino _assigned = " << _assigned << endl;
                
                remove = false;
                func = NULL;
    */ 
            }
            
            //--------------------------------------------------------------
            //
            EventHandler& operator = (Base* aPtr) {
                pointerino = aPtr;
                _assigned = true;
                return *this;
            }
            
            //--------------------------------------------------------------
            //
            bool operator == (const bool& b) { return _assigned; }
            
            //--------------------------------------------------------------
            //
            void operator() (Event &event) {
                if (pointerino) {
                    //cout << "TweenEvent :: operator args = " << args << "  _assigned = " << _assigned << endl;
                    (*pointerino)(event);
                }
            }
    };
    
}