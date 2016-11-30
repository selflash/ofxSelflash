#pragma once

#include "ofMain.h"
#include "STweenCore.h"

namespace fltw {

    class STweenCore;

    template <typename Arg>
    class CallBackFuncion {
        private:
            class Base {
                public:
                    virtual ~Base() { }
                    virtual void operator()(STweenCore* target) = 0;
            };
            Base* _pointerino;
        
            bool _assigned;
            
        public:
            template <typename Class>
            class T : public Base {
                typedef void (Class::*Func)(STweenCore* target);
                
                public:
                    T(Class* listener, void (Class::*listenerMethod)(STweenCore*)) : _listener(listener), _listenerMethod(listenerMethod) { }
                
                    virtual void operator()(STweenCore* currentTarget) { return (_listener->*_listenerMethod)(currentTarget); }
                
                private:
                    // Pointer to the object we are delegating to.
                    Class* _listener;
                    // Address of the function on the delegate object.
                    Func _listenerMethod;
            };
            
        public:
            
            //--------------------------------------------------------------
            //
            CallBackFuncion() {
                _assigned = false;
                _pointerino = NULL;
            }
            //--------------------------------------------------------------
            //
            ~CallBackFuncion() {
    /*
                if (_assigned) {
                    //cout << "there is a pointerino" << endl;
                    delete pointerino;
                    pointerino = NULL;
                }
                _assigned = false;
    */ 
            }
            
            //--------------------------------------------------------------
            //
            void destroy() {
                if (_assigned) {
                    //cout << "there is a pointerino" << endl;
                    delete _pointerino;
                    _pointerino = NULL;
                }
                _assigned = false;
                //cout << "deleting pointerino _assigned = " << _assigned << endl;
            }
            
            //--------------------------------------------------------------
            //
            CallBackFuncion& operator = (Base* aPtr) {
                _pointerino = aPtr;
                _assigned = true;
                return *this;
            }
            
            //--------------------------------------------------------------
            //
            bool operator == (const bool& b) { return _assigned; }
        
            //--------------------------------------------------------------
            //
            void operator()(STweenCore* currentTarget) {
                if (_pointerino) {
                    //cout << "TweenEvent :: operator args = " << args << "  _assigned = " << _assigned << endl;
                    (*_pointerino)(currentTarget);
                }
            }
    };

}